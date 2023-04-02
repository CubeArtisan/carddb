#ifndef CUBEARTISAN_CARDDB_GRAMMAR_ACCESSORS
#define CUBEARTISAN_CARDDB_GRAMMAR_ACCESSORS

#include <concepts>
#include <memory>
#include <string>
#include <tuple>
#include <type_traits>

#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>

#include "cubeartisan/carddb/card.hpp"
#include "cubeartisan/carddb/grammar/utils.hpp"

namespace cubeartisan::carddb {
template <typename Queryable, typename ResultType> struct rec_fn {
private:
  struct rec_fn_inter {
    virtual std::tuple<ResultType, rec_fn>
    operator()(const Queryable &query) const = 0;
    virtual explicit operator bool() const = 0;
    virtual rec_fn_inter *move_to(void *buf) = 0;
    virtual ~rec_fn_inter() = default;
  };

  template <typename T> struct rec_fn_impl final : rec_fn_inter {
    template <typename U>
      requires(not std::same_as<std::remove_cvref_t<U>, rec_fn_impl>)
    rec_fn_impl(U &&arg) : obj{static_cast<decltype(arg)>(arg)} {}

    T obj;

    std::tuple<ResultType, rec_fn>
    operator()(const Queryable &query) const override {
      auto inner_result = obj(query);
      return {std::get<0>(inner_result), std::move(std::get<1>(inner_result))};
    }

    explicit operator bool() const override { return static_cast<bool>(obj); }

    rec_fn_impl *move_to(void *buf) override {
      return new (buf) rec_fn_impl{std::move(obj)};
    }

    ~rec_fn_impl() = default;
  };

  alignas(void *) std::byte t_buff[32];

  rec_fn_inter *impl;

  void del_impl() {
    if (impl) {
      impl->~rec_fn_inter();
      impl = new (&t_buff) rec_fn_default_impl{};
    }
  }

public:
  struct rec_fn_default_impl final : rec_fn_inter {
    std::tuple<ResultType, rec_fn>
    operator()(const Queryable &) const override {
      return {ResultType{}, *this};
    }

    explicit operator bool() const override { return false; };

    rec_fn_default_impl *move_to(void *buf) override {
      return new (buf) rec_fn_default_impl{};
    }
  };

  rec_fn(const rec_fn_default_impl &)
      : impl(new(&t_buff) rec_fn_default_impl{}) {}

  rec_fn(rec_fn_default_impl &&) : impl(new(&t_buff) rec_fn_default_impl{}) {}

  template <typename T>
    requires(not std::same_as<std::remove_cvref_t<T>, rec_fn_default_impl> and
             not std::same_as<std::remove_cvref_t<T>, rec_fn>)
  rec_fn(T &&ref)
      : impl{new(&t_buff) rec_fn_impl<std::remove_cvref_t<T>>{
            static_cast<decltype(ref)>(ref)}} {}

  rec_fn(const rec_fn &) = delete;
  rec_fn operator=(const rec_fn &) = delete;
  rec_fn(rec_fn &&other) : impl{new(&t_buff) rec_fn_default_impl{}} {
    *this = std::move(other);
  }
  rec_fn &operator=(rec_fn &&other) {
    del_impl();
    if (other.impl) {
      impl = other.impl->move_to(&t_buff);
      other.del_impl();
    } else {
      impl = new (&t_buff) rec_fn_default_impl{};
    }
    return *this;
  }

  std::tuple<ResultType, rec_fn> operator()(const Queryable &query) const {
    if (!impl)
      return {ResultType{}, rec_fn_default_impl{}};
    return (*impl)(query);
  }

  explicit operator bool() const { return impl && static_cast<bool>(*impl); }

  ~rec_fn() { del_impl(); }
};

template <auto accessor> struct each_face {
  using result_type = std::remove_cvref_t<
      std::invoke_result_t<decltype(accessor), const CardFace &>>;
  using rec_fn_t = rec_fn<Card, result_type>;
  const int i = 0;
  std::tuple<result_type, rec_fn_t> operator()(const Card &query) const {
    return {query.card_faces.size() > i && i >= 0 ? query.card_faces[i]
                                                  : result_type{},
            query.card_faces.size() - i > 1
                ? rec_fn_t{each_face{i + 1}}
                : typename rec_fn_t::rec_fn_default_impl{}};
  }

  operator bool() const { return i >= 0; }
};

template <typename T> using card_rec = rec_fn<Card, T>;

namespace grammar {

struct source_accessor : one_of_lit_rule<"source"> {
  static constexpr auto value = lexy::callback<
      card_rec<std::string>>([](auto...) {
    return [](const Card &c) {
      return std::tuple{c.source, card_rec<std::string>::rec_fn_default_impl{}};
    };
  });
};

struct name_accessor : one_of_lit_rule<"name", "n"> {
  static constexpr auto value =
      lexy::callback<card_rec<std::string>>([](auto...) {
        return [](const Card &c) {
          return std::tuple{
              c.name, each_face<[](const CardFace &f) { return f.name; }>{}};
        };
      });
};

} // namespace grammar
} // namespace cubeartisan::carddb
#endif
