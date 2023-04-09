#ifndef CUBEARTISAN_CARDDB_GRAMMAR_UTILS_HPP
#define CUBEARTISAN_CARDDB_GRAMMAR_UTILS_HPP // NOLINT(llvm-header-guard)

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

template <lexy::_detail::string_literal... values>
struct one_of_lit_rule : lexy::token_production {
  static constexpr auto rule = dsl::capture(
      dsl::literal_set(dsl::unicode::simple_case_folding(dsl::lit<values>)...));
  static constexpr auto value =
      lexy::as_string<std::string, lexy::utf8_encoding>;

  template <lexy::_detail::string_literal name_v>
  struct named : public one_of_lit_rule {
    static constexpr const char *name = name_v.data;
  };
};

} // namespace cubeartisan::carddb::grammar

#endif // CUBEARTISAN_CARDDB_GRAMMAR_UTILS_HPP
