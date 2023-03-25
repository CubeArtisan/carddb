#include <string>
#include <vector>

#include <emscripten/bind.h>

#include "cubeartisan/carddb/card.hpp"

using namespace cubeartisan::carddb;
using namespace emscripten;

// Bindings for std::vector
namespace emscripten {
namespace internal {

template <typename T, typename Allocator>
struct BindingType<std::vector<T, Allocator>> {
  using ValBinding = BindingType<val>;
  using WireType = ValBinding::WireType;

  static WireType toWireType(const std::vector<T, Allocator> &vec) {
    return ValBinding::toWireType(val::array(vec));
  }

  static std::vector<T, Allocator> fromWireType(WireType value) {
    return vecFromJSArray<T>(ValBinding::fromWireType(value));
  }
};

template <typename T>
struct TypeID<
    T,
    typename std::enable_if_t<std::is_same<
        typename Canonicalized<T>::type,
        std::vector<typename Canonicalized<T>::type::value_type,
                    typename Canonicalized<T>::type::allocator_type>>::value>> {
  static constexpr TYPEID get() { return TypeID<val>::get(); }
};

} // namespace internal
} // namespace emscripten

EMSCRIPTEN_BINDINGS(carddb) {

  value_object<CardFace>("CardFace")
      .field("name", &CardFace::name)
      .field("mana_cost", &CardFace::mana_cost)
      // images
      .field("cmc", &CardFace::cmc)
      .field("color_indicator", &CardFace::color_indicator)
      .field("colors", &CardFace::colors)
      .field("layout", &CardFace::layout)
      .field("loyalty", &CardFace::loyalty)
      .field("power", &CardFace::power)
      .field("toughness", &CardFace::toughness)
      .field("type_line", &CardFace::type_line)
      .field("flavor_text", &CardFace::flavor_text)
      .field("illustration_id", &CardFace::illustration_id)
      .field("printed_name", &CardFace::printed_name)
      .field("printed_text", &CardFace::printed_text)
      .field("printed_type_line", &CardFace::printed_type_line)
      .field("watermark", &CardFace::watermark)
      .field("artist", &CardFace::artist)
      .field("attraction_lights", &CardFace::attraction_lights)
      .field("border_color", &CardFace::border_color)
      .field("flavor_name", &CardFace::flavor_name)
      .field("frame_effects", &CardFace::frame_effects)
      .field("frame", &CardFace::frame)
      .field("full_art", &CardFace::full_art)
      .field("highres_image", &CardFace::highres_image)
      .field("story_spotlight", &CardFace::story_spotlight)
      .field("textless", &CardFace::textless)
      .field("security_stamp", &CardFace::security_stamp);

  value_object<CardMetadata>("CardMetadata")
      .field("tags", &CardMetadata::tags)
      .field("price", &CardMetadata::price)
      .field("notes", &CardMetadata::notes)
      .field("added_tmsp", &CardMetadata::added_tmsp)
      .field("finish", &CardMetadata::finish)
      .field("status", &CardMetadata::status);

  value_object<RelatedCard>("RelatedCard")
      .field("id", &RelatedCard::id)
      .field("kind", &RelatedCard::kind);

  value_object<CardLegalities>("CardLegalities")
      .field("standard", &CardLegalities::standard)
      .field("future", &CardLegalities::future)
      .field("historic", &CardLegalities::historic)
      .field("gladiator", &CardLegalities::gladiator)
      .field("pioneer", &CardLegalities::pioneer)
      .field("explorer", &CardLegalities::explorer)
      .field("modern", &CardLegalities::modern)
      .field("legacy", &CardLegalities::legacy)
      .field("pauper", &CardLegalities::pauper)
      .field("vintage", &CardLegalities::vintage)
      .field("penny", &CardLegalities::penny)
      .field("commander", &CardLegalities::commander)
      .field("brawl", &CardLegalities::brawl)
      .field("historicbrawl", &CardLegalities::historicbrawl)
      .field("alchemy", &CardLegalities::alchemy)
      .field("paupercommander", &CardLegalities::paupercommander)
      .field("duel", &CardLegalities::duel)
      .field("oldschool", &CardLegalities::oldschool)
      .field("premodern", &CardLegalities::premodern);

  value_object<CardPrices>("CardPrices")
      .field("usd", &CardPrices::usd)
      .field("usdFoil", &CardPrices::usd_foil)
      .field("usdEtched", &CardPrices::usd_etched)
      .field("eur", &CardPrices::eur)
      .field("tix", &CardPrices::tix);

  value_object<CardPreviewInfo>("CardPreviewInfo")
      .field("previewed_at", &CardPreviewInfo::previewed_at)
      .field("source_uri", &CardPreviewInfo::source_uri)
      .field("source", &CardPreviewInfo::source);

  value_object<Card>("Card")
      .field("id", &Card::id)
      .field("source", &Card::source)
      .field("card_faces", &Card::card_faces)
      .field("collector_number", &Card::collector_number)
      .field("cmc", &CardFace::cmc)
      .field("colors", &CardFace::colors)
      .field("color_category", &Card::color_category)
      .field("color_identity", &Card::color_identity)
      .field("related", &Card::related)
      .field("legalities", &Card::legalities)
      .field("ehdrec_rank", &Card::ehdrec_rank)
      .field("hand_modifier", &Card::hand_modifier)
      .field("life_modifier", &Card::life_modifier)
      .field("keywords", &Card::keywords)
      .field("oversized", &Card::oversized)
      .field("penny_rank", &Card::penny_rank)
      .field("reserved", &Card::reserved)
      .field("booster", &Card::booster)
      .field("digital", &Card::digital)
      .field("finishes", &Card::finishes)
      .field("games", &Card::games)
      .field("prices", &Card::prices)
      .field("promo", &Card::promo)
      .field("promo_types", &Card::promo_types)
      .field("rarity", &Card::rarity)
      .field("released_at", &Card::released_at)
      .field("reprint", &Card::reprint)
      .field("set_name", &Card::set_name)
      .field("set_type", &Card::set_type)
      .field("set", &Card::set)
      .field("set_id", &Card::set_id)
      .field("variation", &Card::variation)
      .field("variation_of", &Card::variation_of)
      .field("preview", &Card::preview)
      .field("metadata", &Card::metadata);
}
