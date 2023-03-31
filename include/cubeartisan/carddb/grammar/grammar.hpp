#ifndef CUBEARTISAN_CARDDB_GRAMMAR
#define CUBEARTISAN_CARDDB_GRAMMAR

#include <optional>
#include <string>

#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>

namespace cubeartisan::carddb::grammar {
namespace dsl = lexy::dsl;

template <typename... Types>
constexpr auto one_of = ((dsl::peek(Types::rule) >> dsl::p<Types>) | ...);

template <auto... rules>
constexpr auto one_of_value = ((dsl::peek(rules) >> rules) | ...);

template <typename T> struct no_extra {
  static constexpr auto rule = dsl::p<T> + dsl::eof;
  static constexpr auto value =
      lexy::forward<typename decltype(T::value)::return_type>;
};

template <lexy::_detail::string_literal... values> struct one_of_lit_rule {
  static constexpr auto rule = dsl::capture(
      dsl::literal_set(dsl::ascii::case_folding(dsl::lit<values>)...));
  static constexpr auto value = lexy::as_string<std::string>;

  template <lexy::_detail::string_literal name_v>
  struct named : public one_of_lit_rule {
    static constexpr const char *name = name_v.data;
  };
};

struct dollar_frac {
  static constexpr auto rule = dsl::capture(dsl::digit<dsl::decimal>) +
                               dsl::if_(dsl::peek(dsl::digit<dsl::decimal>) >>
                                        dsl::capture(dsl::digit<dsl::decimal>));
  static constexpr auto value = lexy::callback<float>(
      [](auto v) { return static_cast<float>(*v.begin() - '0') / 10.f; },
      [](auto v1, auto v2) {
        return static_cast<float>(*v1.begin() - '0') / 10.f +
               static_cast<float>(*v2.begin() - '0') / 100.f;
      });
};

struct positive_integer {
  static constexpr auto rule =
      dsl::plus_sign +
      dsl::integer<unsigned int>(dsl::digits<>.no_leading_zero());
  static constexpr auto value = lexy::as_integer<unsigned int>;
};

struct integer {
  static constexpr auto rule =
      dsl::sign + dsl::integer<unsigned int>(dsl::digits<>.no_leading_zero());
  static constexpr auto value = lexy::as_integer<int>;
};

struct five_float {
  static constexpr auto rule = dsl::period + dsl::lit_c<'5'>;
  static constexpr auto value = lexy::constant(0.f);
};

struct zero_float {
  static constexpr auto rule = dsl::period + dsl::lit_c<'0'>;
  static constexpr auto value = lexy::constant(0.f);
};

struct positive_half_integer {
  static constexpr auto rule =
      dsl::p<positive_integer> + dsl::opt(one_of<zero_float, five_float>);
  static constexpr auto value = lexy::callback<float>(
      [](const unsigned int &value, const std::optional<float> &half) {
        return static_cast<float>(value) + half.value_or(0.f);
      });
};

struct dollars {
  static constexpr auto rule =
      dsl::p<positive_integer> + dsl::opt(dsl::period >> dsl::p<dollar_frac>);
  static constexpr auto value =
      lexy::callback<float>([](unsigned int v, std::optional<float> frac) {
        return static_cast<float>(v) + frac.value_or(0.f);
      });
};

using finish = one_of_lit_rule<"foil", "nonfoil", "etched">::named<"finish">;

using format =
    one_of_lit_rule<"standard", "future", "historic", "gladiator", "pioneer",
                    "explorer", "modern", "legacy", "pauper", "vintage",
                    "penny", "commander", "brawl", "historicbrawl", "alchemy",
                    "paupercommander", "duel", "oldschool",
                    "premodern">::named<"format">;

using legality = one_of_lit_rule<"legal", "not_legal", "restricted",
                                 "banned">::named<"legality">;

} // namespace cubeartisan::carddb::grammar

#endif
