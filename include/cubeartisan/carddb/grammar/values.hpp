#ifndef CUBEARTISAN_CARDDB_GRAMMAR_VALUES
#define CUBEARTISAN_CARDDB_GRAMMAR_VALUES

#include <optional>

#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>

#include "cubeartisan/carddb/grammar/utils.hpp"

namespace cubeartisan::carddb::grammar {

struct dollar_frac : lexy::token_production {
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

struct positive_integer : lexy::token_production {
  static constexpr auto rule =
      dsl::plus_sign +
      dsl::integer<unsigned int>(dsl::digits<>.no_leading_zero());
  static constexpr auto value = lexy::as_integer<unsigned int>;
};

struct integer : lexy::token_production {
  static constexpr auto rule =
      dsl::sign + dsl::integer<unsigned int>(dsl::digits<>.no_leading_zero());
  static constexpr auto value = lexy::as_integer<int>;
};

struct five_float : lexy::token_production {
  static constexpr auto rule = dsl::period + dsl::lit_c<'5'>;
  static constexpr auto value = lexy::constant(0.f);
};

struct zero_float : lexy::token_production {
  static constexpr auto rule = dsl::period + dsl::lit_c<'0'>;
  static constexpr auto value = lexy::constant(0.f);
};

struct positive_half_integer : lexy::token_production {
  static constexpr auto rule =
      dsl::p<positive_integer> + dsl::opt(one_of<zero_float, five_float>);
  static constexpr auto value = lexy::callback<float>(
      [](const unsigned int &value, const std::optional<float> &half) {
        return static_cast<float>(value) + half.value_or(0.f);
      });
};

struct dollars : lexy::token_production {
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

using status = one_of_lit_rule<"owned", "proxied", "ordered", "notowned",
                               "premiumowned">::named<"status">;

using rarity =
    one_of_lit_rule<"s", "special", "m", "mythic", "r", "rare", "u", "uncommon",
                    "c", "common", "l", "land">::named<"rarity">;

struct alpha_num : lexy::token_production {
  static constexpr auto rule = [] {
    auto item = dsl::capture(dsl::ascii::alpha_digit);
    return dsl::list(item);
  }();

  // Same as `lexy::as_string`.
  static constexpr auto value =
      lexy::as_string<std::string, lexy::utf8_encoding>;
};

enum class color_value : std::uint8_t {
  colorless = 0b00000,
  white = 0b10000,
  blue = 0b01000,
  black = 0b00100,
  red = 0b00010,
  green = 0b00001,
  azorious = 0b11000,
  dimir = 0b01100,
  rakdos = 0b00110,
  gruul = 0b00011,
  selesnya = 0b10001,
  orzhov = 0b10100,
  izzet = 0b01010,
  golgari = 0b00101,
  boros = 0b10010,
  simic = 0b01001,
  bant = 0b11001,
  esper = 0b11100,
  grixis = 0b01110,
  jund = 0b00111,
  naya = 0b10011,
  mardu = 0b10110,
  temur = 0b01011,
  abzan = 0b10101,
  jeskai = 0b11010,
  sultai = 0b01101,
  notwhite = 0b01111,
  notblue = 0b10111,
  notblack = 0b11011,
  notred = 0b11101,
  notgreen = 0b11110,
  fivecolor = 0b11111,
};

struct colors {
  static constexpr auto color_table = lexy::symbol_table<color_value>
        .map<LEXY_SYMBOL("w")>(color_value::white)
        .map<LEXY_SYMBOL("u")>(color_value::blue)
        .map<LEXY_SYMBOL("b")>(color_value::black)
        .map<LEXY_SYMBOL("r")>(color_value::red)
        .map<LEXY_SYMBOL("g")>(color_value::green)
        .case_folding(dsl::unicode::simple_case_folding);

  static constexpr auto color_name_table =
      lexy::symbol_table<color_value>
        .map<LEXY_SYMBOL("brown")>(color_value::colorless)
        .map<LEXY_SYMBOL("colorless")>(color_value::colorless)
        .map<LEXY_SYMBOL("c")>(color_value::colorless)
        .map<LEXY_SYMBOL("white")>(color_value::white)
        .map<LEXY_SYMBOL("blue")>(color_value::blue)
        .map<LEXY_SYMBOL("black")>(color_value::black)
        .map<LEXY_SYMBOL("red")>(color_value::red)
        .map<LEXY_SYMBOL("green")>(color_value::green)
        .map<LEXY_SYMBOL("azorious")>(color_value::azorious)
        .map<LEXY_SYMBOL("dimir")>(color_value::dimir)
        .map<LEXY_SYMBOL("rakdos")>(color_value::rakdos)
        .map<LEXY_SYMBOL("gruul")>(color_value::gruul)
        .map<LEXY_SYMBOL("selesnya")>(color_value::selesnya)
        .map<LEXY_SYMBOL("orzhov")>(color_value::orzhov)
        .map<LEXY_SYMBOL("izzet")>(color_value::izzet)
        .map<LEXY_SYMBOL("golgari")>(color_value::golgari)
        .map<LEXY_SYMBOL("boros")>(color_value::boros)
        .map<LEXY_SYMBOL("simic")>(color_value::simic)
        .map<LEXY_SYMBOL("bant")>(color_value::bant)
        .map<LEXY_SYMBOL("esper")>(color_value::esper)
        .map<LEXY_SYMBOL("grixis")>(color_value::grixis)
        .map<LEXY_SYMBOL("jund")>(color_value::jund)
        .map<LEXY_SYMBOL("naya")>(color_value::naya)
        .map<LEXY_SYMBOL("mardu")>(color_value::mardu)
        .map<LEXY_SYMBOL("temur")>(color_value::temur)
        .map<LEXY_SYMBOL("abzan")>(color_value::abzan)
        .map<LEXY_SYMBOL("jeskai")>(color_value::jeskai)
        .map<LEXY_SYMBOL("sultai")>(color_value::sultai)
        .map<LEXY_SYMBOL("notwhite")>(color_value::notwhite)
        .map<LEXY_SYMBOL("notblue")>(color_value::notblue)
        .map<LEXY_SYMBOL("notblack")>(color_value::notblack)
        .map<LEXY_SYMBOL("notred")>(color_value::notred)
        .map<LEXY_SYMBOL("notgreen")>(color_value::notgreen)
        .map<LEXY_SYMBOL("fivecolor")>(color_value::fivecolor)
        .map<LEXY_SYMBOL("rainbow")>(color_value::fivecolor)
        .case_folding(dsl::unicode::simple_case_folding);

  static constexpr auto color_class = dsl::ascii::one_of<"wubrgWUBRG">;

  static constexpr auto rule =
      dsl::symbol<color_name_table>(dsl::identifier(dsl::ascii::alpha)) |
      (dsl::peek(color_class) >>
       dsl::flags(dsl::symbol<color_table>(color_class)));

  static constexpr auto value = lexy::forward<color_value>;
};

using color = one_of_lit_rule<"w", "u", "b", "r", "g">::named<"color">;

// A json value that is a string.
struct string : lexy::token_production {
  struct invalid_char {
    static LEXY_CONSTEVAL auto name() {
      return "invalid character in string literal";
    }
  };

  // A mapping of the simple escape sequences to their replacement values.
  static constexpr auto escaped_symbols = lexy::symbol_table<char> //
                                              .map<'\''>('\'')
                                              .map<'"'>('"')
                                              .map<'\\'>('\\')
                                              .map<'/'>('/')
                                              .map<'b'>('\b')
                                              .map<'f'>('\f')
                                              .map<'n'>('\n')
                                              .map<'r'>('\r')
                                              .map<'t'>('\t');

  // In JSON, a Unicode code point can be specified by its encoding in UTF-16:
  // * code points <= 0xFFFF are specified using `\uNNNN`.
  // * other code points are specified by two surrogate UTF-16 sequences.
  // However, we don't combine the two surrogates into the final code point,
  // instead keep them separate and require a later pass that merges them if
  // necessary. (This behavior is allowed by the standard).
  struct code_point_id {
    // We parse the integer value of a UTF-16 code unit.
    static constexpr auto rule =
        LEXY_LIT("u") >> dsl::code_unit_id<lexy::utf8_encoding, 4>;
    // And convert it into a code point, which might be a surrogate.
    static constexpr auto value = lexy::construct<lexy::code_point>;
  };

  static constexpr auto rule = [] {
    // Everything is allowed inside a string except for control characters.
    auto code_point = (-dsl::unicode::control).error<invalid_char>;

    // Escape sequences start with a backlash and either map one of the symbols,
    // or a Unicode code point.
    auto escape = dsl::backslash_escape.symbol<escaped_symbols>().rule(
        dsl::p<code_point_id>);

    // String of code_point with specified escape sequences, surrounded by ".
    // We abort string parsing if we see a newline to handle missing closing ".
    return (dsl::peek(dsl::lit_c<'"'>) >>
            dsl::quoted.limit(dsl::unicode::newline)(code_point, escape)) |
           (dsl::peek(dsl::lit_c<'\''>) >>
            dsl::single_quoted.limit(dsl::unicode::newline)(code_point,
                                                            escape)) |
           (dsl::peek(dsl::unicode::alpha_digit) >>
            dsl::identifier(dsl::unicode::alpha_digit));
  }();

  static constexpr auto value =
      lexy::as_string<std::string, lexy::utf8_encoding>;
};

using inner_mana_symbol =
    one_of_lit_rule<"w", "u", "b", "r", "g", "c", "w/u", "u/b", "b/r", "r/g",
                    "g/w", "w/b", "u/r", "b/g", "r/w", "g/u", "2/w", "2/u",
                    "2/b", "2/r", "2/g", "p", "w/p", "u/p", "b/p", "r/p", "g/p",
                    "w/u/p", "u/b/p", "b/r/p", "r/g/p", "g/w/p", "w/b/p",
                    "u/r/p", "b/g/p", "r/w/p", "g/u/p", "s", "0", "1", "2", "3",
                    "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
                    "15", "16", "17", "18", "19", "20", "100", "1000000", "x",
                    "y", "z", "hw", "hr">::named<"inner_mana_symbol">;

struct mana_symbol : lexy::token_production {
  static constexpr auto rule =
      (dsl::peek(dsl::lit_c<'{'>) >>
       (dsl::lit_c<'{'> + dsl::p<inner_mana_symbol> + dsl::lit_c<'}'>)) |
      (dsl::peek(dsl::lit_c<'('>) >>
       (dsl::lit_c<'('> + dsl::p<inner_mana_symbol> + dsl::lit_c<')'>)) |
      dsl::p<inner_mana_symbol>;

  static constexpr auto value = lexy::forward<std::string>;
};

} // namespace cubeartisan::carddb::grammar

#endif
