#ifndef CUBEARTISAN_CARDDB_CARD
#define CUBEARTISAN_CARDDB_CARD

#include <optional>
#include <string>
#include <vector>

namespace cubeartisan::carddb {
struct CardFace {
  std::string name;
  std::vector<std::string> mana_cost;
  // images
  double cmc;
  std::vector<std::string> color_indicator;
  std::vector<std::string> colors;
  std::optional<std::string> layout;
  std::optional<std::string> loyalty;
  std::optional<std::string> power;
  std::optional<std::string> toughness;
  std::string type_line;
  std::optional<std::string> flavor_text;
  std::optional<std::string> illustration_id;
  std::optional<std::string> printed_name;
  std::optional<std::string> printed_text;
  std::optional<std::string> printed_type_line;
  std::optional<std::string> watermark;
  std::optional<std::string> artist;
  std::optional<std::vector<double>> attraction_lights;
  std::string border_color;
  std::optional<std::string> flavor_name;
  std::optional<std::vector<std::string>> frame_effects;
  std::string frame;
  bool full_art;
  bool highres_image;
  bool story_spotlight;
  bool textless;
  std::optional<std::string> security_stamp;
};

struct CardMetadata {
  std::vector<std::string> tags;
  std::optional<double> price;
  std::string notes;
  std::string added_tmsp;
  std::string finish;
  std::string status;
};

struct RelatedCard {
  std::string id;
  std::string kind;
};

struct CardLegalities {
  std::string standard;
  std::string future;
  std::string historic;
  std::string gladiator;
  std::string pioneer;
  std::string explorer;
  std::string modern;
  std::string legacy;
  std::string pauper;
  std::string vintage;
  std::string penny;
  std::string commander;
  std::string brawl;
  std::string historicbrawl;
  std::string alchemy;
  std::string paupercommander;
  std::string duel;
  std::string oldschool;
  std::string premodern;
};

struct CardPrices {
  std::optional<std::string> usd;
  std::optional<std::string> usd_foil;
  std::optional<std::string> usd_etched;
  std::optional<std::string> eur;
  std::optional<std::string> tix;
};

struct CardPreviewInfo {
  std::optional<std::string> previewed_at;
  std::optional<std::string> source_uri;
  std::optional<std::string> source;
};

struct Card {
  std::string id;
  std::string source;
  std::string name;
  std::string layout;
  std::vector<CardFace> card_faces;
  std::string collector_number;
  double cmc;
  std::vector<std::string> colors;
  std::string color_category;
  std::string color_identity;
  std::vector<RelatedCard> related;
  CardLegalities legalities;
  std::optional<double> ehdrec_rank;
  std::optional<std::string> hand_modifier;
  std::optional<std::string> life_modifier;
  std::vector<std::string> keywords;
  bool oversized;
  std::optional<double> penny_rank;
  bool reserved;
  bool booster;
  bool digital;
  std::vector<std::string> finishes;
  std::vector<std::string> games;
  CardPrices prices;
  bool promo;
  std::vector<std::string> promo_types;
  std::string rarity;
  std::string released_at;
  bool reprint;
  std::string set_name;
  std::string set_type;
  std::string set;
  std::string set_id;
  bool variation;
  std::optional<std::string> variation_of;
  std::optional<CardPreviewInfo> preview;
  std::optional<CardMetadata> metadata;
  // purchaseUris
  // relatedUris
};
}; // namespace cubeartisan::carddb

#endif
