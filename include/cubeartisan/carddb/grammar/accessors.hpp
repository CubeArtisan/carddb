#ifndef CUBEARTISAN_CARDDB_GRAMMAR_ACCESSORS_HPP
#define CUBEARTISAN_CARDDB_GRAMMAR_ACCESSORS_HPP  // NOLINT(llvm-header-guard)

#include <array>
#include <concepts>
#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>

#include "cubeartisan/carddb/card.hpp"
#include "cubeartisan/carddb/grammar/utils.hpp"

namespace cubeartisan::carddb {
template <typename Queryable, typename ResultType>
struct alignas(64) rec_fn {  // NOLINT(readability-magic-numbers)
 private:
  struct rec_fn_inter {  // NOLINT(altera-struct-pack-align)
    rec_fn_inter() noexcept = default;
    rec_fn_inter(const rec_fn_inter &) = delete;
    auto operator=(const rec_fn_inter &) -> rec_fn_inter & = delete;
    rec_fn_inter(rec_fn_inter &&) = delete;
    auto operator=(rec_fn_inter &&) noexcept -> rec_fn_inter & = delete;
    virtual auto operator()(const Queryable &query) const
        -> std::tuple<ResultType, rec_fn> = 0;
    virtual explicit operator bool() const = 0;
    virtual auto move_to(void *buf) noexcept -> rec_fn_inter * = 0;
    virtual ~rec_fn_inter() = default;
  };

  template <typename T>
  struct rec_fn_impl final : rec_fn_inter {
    rec_fn_impl(const rec_fn_impl &) = delete;
    auto operator=(const rec_fn_impl &) -> rec_fn_impl & = delete;
    rec_fn_impl(rec_fn_impl &&) = delete;
    auto operator=(rec_fn_impl &&) -> rec_fn_impl & = delete;

    template <typename U>
      requires(not std::same_as<std::remove_cvref_t<U>, rec_fn_impl>)
    explicit rec_fn_impl(U &&arg)
        : obj{static_cast<decltype(arg)>(arg)} {
    }  // NOLINT(bugprone-forwarding-reference-overload)

    auto operator()(const Queryable &query) const
        -> std::tuple<ResultType, rec_fn> override {
      auto inner_result = obj(query);
      return {std::get<0>(inner_result), std::move(std::get<1>(inner_result))};
    }

    explicit operator bool() const override { return static_cast<bool>(obj); }

    auto move_to(void *buf) noexcept -> rec_fn_impl * override {
      return new (buf) rec_fn_impl{// NOLINT(cppcoreguidelines-owning-memory)
                                   std::move(obj)};
    }

    ~rec_fn_impl() = default;

   private:
    T obj;
  };

  std::array<std::byte, 56> t_buff = {};  // NOLINT(readability-magic-numbers)

  rec_fn_inter *impl;

  void del_impl() {
    if (impl) {
      impl->~rec_fn_inter();
      impl = new (&t_buff)  // NOLINT(cppcoreguidelines-owning-memory)
          rec_fn_default_impl{};
    }
  }

 public:
  struct rec_fn_default_impl final  // NOLINT(altera-struct-pack-align)
      : rec_fn_inter {
    rec_fn_default_impl() = default;

    auto operator()(
        const Queryable &) const  // NOLINT(readability-named-parameter)
        -> std::tuple<ResultType, rec_fn> override {
      return {ResultType{}, rec_fn{}};
    }

    explicit operator bool() const override { return false; };

    auto move_to(void *buf) noexcept -> rec_fn_default_impl * override {
      return new (buf)  // NOLINT(cppcoreguidelines-owning-memory)
          rec_fn_default_impl{};
    }
  };

  rec_fn() : impl(new(&t_buff) rec_fn_default_impl{}) {}

  template <typename T>
    requires(not std::same_as<std::remove_cvref_t<T>, rec_fn_default_impl> and
             not std::same_as<std::remove_cvref_t<T>, rec_fn>)
  explicit rec_fn(  // NOLINT(google-explicit-constructor,bugprone-forwarding-reference-overload)
      T &&ref)
      : impl{new(&t_buff) rec_fn_impl<std::remove_cvref_t<T>>{
            static_cast<decltype(ref)>(ref)}} {}

  rec_fn(const rec_fn &) = delete;
  auto operator=(const rec_fn &) -> rec_fn = delete;
  rec_fn(rec_fn &&other) noexcept : impl{new(&t_buff) rec_fn_default_impl{}} {
    *this = std::move(other);
  }
  auto operator=(rec_fn &&other) noexcept -> rec_fn & {
    del_impl();
    if (other.impl) {
      impl = other.impl->move_to(&t_buff);
      other.del_impl();
    } else {
      impl = new (&t_buff)  // NOLINT(cppcoreguidelines-owning-memory)
          rec_fn_default_impl{};
    }
    return *this;
  }

  auto operator()(const Queryable &query) const
      -> std::tuple<ResultType, rec_fn> {
    if (!impl) {
      return {ResultType{}, rec_fn_default_impl{}};
    }
    return (*impl)(query);
  }

  explicit operator bool() const { return impl && static_cast<bool>(*impl); }

  ~rec_fn() { del_impl(); }
};

template <auto accessor>
struct each_face {
  using result_type = std::remove_cvref_t<
      std::invoke_result_t<decltype(accessor), const CardFace &>>;
  using rec_fn_t = rec_fn<Card, result_type>;
  auto operator()(const Card &query) const
      -> std::tuple<result_type, rec_fn_t> {
    return {query.card_faces.size() > i && i >= 0 ? query.card_faces[i]
                                                  : result_type{},
            query.card_faces.size() - i > 1
                ? rec_fn_t{each_face{i + 1}}
                : typename rec_fn_t::rec_fn_default_impl{}};
  }

  explicit operator bool() const { return i >= 0; }

 private:
  int i = 0;
};

template <typename T>
using card_rec = rec_fn<Card, T>;

namespace grammar {

// TODO: legalities

// TODO: prices

// TODO: preview

// TODO: metadata

struct source_accessor : one_of_lit_rule<"source"> {
  static constexpr auto value =
      lexy::callback<card_rec<std::string>>([](auto...) {
        return [](const Card &card) {
          return std::tuple{card.source, card_rec<std::string>{}};
        };
      });
};

struct name_accessor : one_of_lit_rule<"name", "n"> {
  static constexpr auto value =
      lexy::callback<card_rec<std::string>>([](auto...) {
        return [](const Card &card) {
          return std::tuple{
              card.name,
              each_face<[](const CardFace &face) { return face.name; }>{}};
        };
      });
};

struct layout_accessor : one_of_lit_rule<"layout"> {
  static constexpr auto value = lexy::callback<card_rec<std::string>>([](auto...) {
    return [](const Card &card) {
      return std::tuple{card.layout, each_face<[](const CardFace &face) { return face.layout; }>{}};
    };
  });
};

// TODO: collector_number

// TODO: color_identity

struct rarity_accessor : one_of_lit_rule<"rarity", "r"> {
  static constexpr auto value = lexy::callback<card_rec<std::string>>([](auto...) {
    return [](const Card &card) { return std::tuple{ card.rarity, card_rec<std::string>{}}; };
  });
};

// TODO: released_at

struct set_name_accessor : one_of_lit_rule<"setname"> {
  static constexpr auto value = lexy::callback<card_rec<std::string>>([](auto...) {
    return [](const Card &card) { return std::tuple{ card.set_name, card_rec<std::string>{}}; };
  });
};

struct set_type_accessor : one_of_lit_rule<"settype"> {
  static constexpr auto value = lexy::callback<card_rec<std::string>>([](auto...) {
    return [](const Card &card) { return std::tuple{ card.set_type, card_rec<std::string>{}}; };
  });
};

struct set_accessor : one_of_lit_rule<"set", "s"> {
  static constexpr auto value = lexy::callback<card_rec<std::string>>([](auto...) {
    return [](const Card &card) { return std::tuple{ card.set, card_rec<std::string>{}}; };
  });
};

// TODO: Hand modifier

// TODO: life modifier

// TODO: variation_of

// TODO: colors

// TODO: related

// TODO: keywords

// TODO: finishes

// TODO: games

// TODO: promo_types

// TODO: edhrec_rank

// TODO: penny_rank

struct cmc_accessor : one_of_lit_rule<"cmc"> {
  static constexpr auto value = lexy::callback<card_rec<double>>([](auto...) {
   return [](const Card& card) { return std::tuple { card.cmc, each_face<[](const CardFace &face) { return face.cmc; }>{}}; };
});
};

// TODO: oversized

// TODO: reserved

// TODO: booster

// TODO: digital

// TODO: promo

// TODO: reprint

// TODO: variation

// TODO: mana_cost

// TODO: color_indicator

// TODO: loyalty

// TODO: power

// TODO: toughness

// TODO: flavor_text

// TODO: printed_name

// TODO: printed_text

// TODO: printed_type_line

// TODO: watermark

// TODO: artist

// TODO: attraction_lights

struct border_accessor : one_of_lit_rule<"border"> {
  static constexpr auto value = lexy::callback<card_rec<std::string>>([](auto...){
        return each_face<[](const CardFace &face) { return face.border_color; }>{}; });
};

// TODO: flavor_name

// TODO: frame_effects

struct frame_accessor : one_of_lit_rule<"frame"> {
  static constexpr auto value = lexy::callback<card_rec<std::string>>([](auto...){
    return each_face<[](const CardFace &face) { return face.frame; }>{}; });
};

// TODO: security_stamp

// TODO: full_art

// TODO: highres_image

// TODO: story_spotlight

// TODO: textless

struct type_accessor : one_of_lit_rule<"type"> {
  static constexpr auto value =
      lexy::callback<card_rec<std::string>>([](auto...) {
        return each_face<[](const CardFace &face) { return face.type_line; }>{};
      });
};

struct string_field {
  static constexpr auto rule =
      one_of<source_accessor, name_accessor, type_accessor, layout_accessor, rarity_accessor>;

  static constexpr auto value = lexy::forward<card_rec<std::string>>;
};

}  // namespace grammar
}  // namespace cubeartisan::carddb
#endif
