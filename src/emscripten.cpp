#include <emscripten/bind.h>

#include <string>
#include <vector>

#include "cubeartisan/carddb/card.hpp"
#include "cubeartisan/carddb/grammar/accessors.hpp"
#include "cubeartisan/carddb/grammar/utils.hpp"
#include "cubeartisan/carddb/grammar/values.hpp"

using namespace cubeartisan::carddb;
using namespace emscripten;

EMSCRIPTEN_BINDINGS(carddb) {
  register_vector<std::string>("VectorString");
  register_vector<int>("VectorInt");

  value_object<CardFace>("CardFace")
      .field("name", &CardFace::name)
      .field("manaCost", &CardFace::mana_cost)
      // images
      .field("cmc", &CardFace::cmc)
      .field("colorIndicator", &CardFace::color_indicator)
      .field("colors", &CardFace::colors)
      .field("layout", &CardFace::layout)
      .field("loyalty", &CardFace::loyalty)
      .field("power", &CardFace::power)
      .field("toughness", &CardFace::toughness)
      .field("typeLine", &CardFace::type_line)
      .field("flavorText", &CardFace::flavor_text)
      .field("illustrationId", &CardFace::illustration_id)
      .field("printedName", &CardFace::printed_name)
      .field("printedText", &CardFace::printed_text)
      .field("printedTypeLine", &CardFace::printed_type_line)
      .field("watermark", &CardFace::watermark)
      .field("artist", &CardFace::artist)
      .field("attractionLights", &CardFace::attraction_lights)
      .field("borderColor", &CardFace::border_color)
      .field("flavorName", &CardFace::flavor_name)
      .field("frameEffects", &CardFace::frame_effects)
      .field("frame", &CardFace::frame)
      .field("fullArt", &CardFace::full_art)
      .field("highresImage", &CardFace::highres_image)
      .field("storySpotlight", &CardFace::story_spotlight)
      .field("textless", &CardFace::textless)
      .field("securityStamp", &CardFace::security_stamp);

  register_vector<CardFace>("VectorCardFace");

  value_object<CardMetadata>("CardMetadata")
      .field("tags", &CardMetadata::tags)
      .field("price", &CardMetadata::price)
      .field("notes", &CardMetadata::notes)
      .field("addedTmsp", &CardMetadata::added_timestamp)
      .field("finish", &CardMetadata::finish)
      .field("status", &CardMetadata::status);

  value_object<RelatedCard>("RelatedCard")
      .field("id", &RelatedCard::id)
      .field("kind", &RelatedCard::kind);

  register_vector<RelatedCard>("VectorRelatedCard");

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
      .field("historicbrawl", &CardLegalities::historic_brawl)
      .field("alchemy", &CardLegalities::alchemy)
      .field("paupercommander", &CardLegalities::pauper_commander)
      .field("duel", &CardLegalities::duel)
      .field("oldschool", &CardLegalities::old_school)
      .field("premodern", &CardLegalities::premodern);

  value_object<CardPrices>("CardPrices")
      .field("usd", &CardPrices::usd)
      .field("usdFoil", &CardPrices::usd_foil)
      .field("usdEtched", &CardPrices::usd_etched)
      .field("eur", &CardPrices::eur)
      .field("tix", &CardPrices::tix);

  value_object<CardPreviewInfo>("CardPreviewInfo")
      .field("previewedAt", &CardPreviewInfo::previewed_at)
      .field("sourceUri", &CardPreviewInfo::source_uri)
      .field("source", &CardPreviewInfo::source);

  value_object<Card>("Card")
      .field("id", &Card::id)
      .field("source", &Card::source)
      .field("name", &Card::name)
      .field("layout", &Card::layout)
      .field("cardFaces", &Card::card_faces)
      .field("collectorNumber", &Card::collector_number)
      .field("cmc", &Card::cmc)
      .field("colors", &Card::colors)
      .field("colorIdentity", &Card::color_identity)
      .field("related", &Card::related)
      .field("legalities", &Card::legalities)
      .field("ehdrecRank", &Card::ehdrec_rank)
      .field("handModifier", &Card::hand_modifier)
      .field("lifeModifier", &Card::life_modifier)
      .field("keywords", &Card::keywords)
      .field("oversized", &Card::oversized)
      .field("pennyRank", &Card::penny_rank)
      .field("reserved", &Card::reserved)
      .field("booster", &Card::booster)
      .field("digital", &Card::digital)
      .field("finishes", &Card::finishes)
      .field("games", &Card::games)
      .field("prices", &Card::prices)
      .field("promo", &Card::promo)
      .field("promoTypes", &Card::promo_types)
      .field("rarity", &Card::rarity)
      .field("releasedAt", &Card::released_at)
      .field("reprint", &Card::reprint)
      .field("setName", &Card::set_name)
      .field("setType", &Card::set_type)
      .field("set", &Card::set)
      .field("setId", &Card::set_id)
      .field("variation", &Card::variation)
      .field("variationOf", &Card::variation_of)
      .field("preview", &Card::preview)
      .field("metadata", &Card::metadata);
}
