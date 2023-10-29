#ifndef CUBEARTISAN_CARDDB_CARD_HPP
#define CUBEARTISAN_CARDDB_CARD_HPP  // NOLINT(llvm-header-guard)

#include <optional>
#include <string>
#include <vector>

namespace cubeartisan::carddb {
struct alignas(128) CardFace {  // NOLINT(readability-magic-numbers)
  std::string name = {};
  std::vector<std::string> mana_cost = {};
  // images
  double cmc = 0.0;
  std::vector<std::string> color_indicator = {};
  std::vector<std::string> colors = {};
  std::optional<std::string> layout = std::nullopt;
  std::optional<std::string> loyalty = std::nullopt;
  std::optional<std::string> power = std::nullopt;
  std::optional<std::string> toughness = std::nullopt;
  std::string type_line = {};
  std::optional<std::string> flavor_text = std::nullopt;
  std::optional<std::string> illustration_id = std::nullopt;
  std::optional<std::string> printed_name = std::nullopt;
  std::optional<std::string> printed_text = std::nullopt;
  std::optional<std::string> printed_type_line = std::nullopt;
  std::optional<std::string> watermark = std::nullopt;
  std::optional<std::string> artist = std::nullopt;
  std::optional<std::vector<int>> attraction_lights = std::nullopt;
  std::string border_color = {};
  std::optional<std::string> flavor_name = std::nullopt;
  std::optional<std::vector<std::string>> frame_effects = std::nullopt;
  std::string frame = {};
  std::optional<std::string> security_stamp = std::nullopt;
  bool full_art = false;
  bool highres_image = false;
  bool story_spotlight = false;
  bool textless = false;
};

struct alignas(128) CardMetadata {  // NOLINT(readability-magic-numbers)
  std::vector<std::string> tags = {};
  std::optional<double> price = std::nullopt;
  std::string notes = {};
  std::string added_timestamp = {};
  std::string finish = {};
  std::string status = {};
};

struct alignas(64) RelatedCard {  // NOLINT(readability-magic-numbers)
  std::string id = {};
  std::string kind = {};
};

struct alignas(128) CardLegalities {  // NOLINT(readability-magic-numbers)
  std::string standard = {};
  std::string future = {};
  std::string historic = {};
  std::string gladiator = {};
  std::string pioneer = {};
  std::string explorer = {};
  std::string modern = {};
  std::string legacy = {};
  std::string pauper = {};
  std::string vintage = {};
  std::string penny = {};
  std::string commander = {};
  std::string brawl = {};
  std::string historic_brawl = {};
  std::string alchemy = {};
  std::string pauper_commander = {};
  std::string duel = {};
  std::string old_school = {};
  std::string premodern = {};
};

struct alignas(128) CardPrices {  // NOLINT(readability-magic-numbers)
  std::optional<std::string> usd = std::nullopt;
  std::optional<std::string> usd_foil = std::nullopt;
  std::optional<std::string> usd_etched = std::nullopt;
  std::optional<std::string> eur = std::nullopt;
  std::optional<std::string> tix = std::nullopt;
};

struct alignas(128) CardPreviewInfo {  // NOLINT(readability-magic-numbers)
  std::optional<std::string> previewed_at = std::nullopt;
  std::optional<std::string> source_uri = std::nullopt;
  std::optional<std::string> source = std::nullopt;
};

struct Card {  // NOLINT(altera-struct-pack-align)
  CardLegalities legalities = {};
  CardPrices prices = {};
  std::optional<CardPreviewInfo> preview = std::nullopt;
  std::optional<CardMetadata> metadata = std::nullopt;
  std::string id = {};
  std::string source = {};
  std::string name = {};
  std::string layout = {};
  std::string collector_number = {};
  std::string color_identity = {};
  std::string rarity = {};
  std::string released_at = {};
  std::string set_name = {};
  std::string set_type = {};
  std::string set = {};
  std::string set_id = {};
  std::optional<std::string> hand_modifier = std::nullopt;
  std::optional<std::string> life_modifier = std::nullopt;
  std::optional<std::string> variation_of = std::nullopt;
  std::vector<std::string> colors = {};
  std::vector<CardFace> card_faces = {};
  std::vector<RelatedCard> related = {};
  std::vector<std::string> keywords = {};
  std::vector<std::string> finishes = {};
  std::vector<std::string> games = {};
  std::vector<std::string> promo_types = {};
  std::optional<double> ehdrec_rank = std::nullopt;
  std::optional<double> penny_rank = std::nullopt;
  double cmc = 0.0;
  bool oversized = false;
  bool reserved = false;
  bool booster = false;
  bool digital = false;
  bool promo = false;
  bool reprint = false;
  bool variation = false;
  // purchaseUris
  // relatedUris
};
}  // namespace cubeartisan::carddb

#endif  // CUBEARTISAN_CARDDB_CARD_HPP
