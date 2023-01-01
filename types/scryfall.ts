export type ScryfallError = {
  object: 'error';
  code: string;
  status: number;
  details: string;
  warnings?: string[];
  type?: string;
};

export type ScryfallList<T> = {
  object: 'list';
  has_more: boolean;
  data: T[];
  next_page?: string;
  total_cards?: number;
  warnings?: string[];
};

export type ScryfallBulkDataObject = {
  object: 'bulk_data';
  id: string;
  uri: string;
  type: 'oracle_cards' | 'unique_artwork' | 'default_cards' | 'all_cards' | 'rulings';
  name: string;
  description: string;
  download_uri: string;
  updated_at: string;
  size: number;
  content_type: string;
  content_encoding: string;
};

export type ScyfallBulkList = ScryfallList<ScryfallBulkDataObject>;

export type ScryfallMigration = {
  object: 'migration';
  uri: string;
  id: string;
  created_at: string;
  migration_strategy: 'merge' | 'delete';
  old_scryfall_id: string;
  new_scryfall_id?: string;
  note?: string;
};

export type ScryfallCoreCard = {
  object: 'card';
  arena_id?: number;
  id: string;
  mtgo_id?: number;
  mtgo_foil_id?: number;
  multiverse_ids?: number[];
  tcgplayer_id?: number;
  tcgplayer_etched_id?: number;
  cardmarket_id?: number;
  oracle_id: string;
  prints_search_uri: string;
  rulings_uri: string;
  scryfall_uri: string;
  uri: string;
};

export type ScryfallRelatedCard = {
  object: 'related_card';
  id: string;
  component: 'token' | 'meld_part' | 'meld_result' | 'combo_piece';
  type_line: string;
  uri: string;
};

export type Color = 'W' | 'U' | 'B' | 'R' | 'G';

export type ScryfallImageStatus = 'missing' | 'placeholder' | 'lowres' | 'highres_scan';

export type ScryfallCardImages = {
  png: string;
  border_crop: string;
  art_crop: string;
  large: string;
  normal: string;
  small: string;
};

export type ScryfallCardImageStatuses = {
  png: ScryfallImageStatus;
  border_crop: ScryfallImageStatus;
  art_crop: ScryfallImageStatus;
  large: ScryfallImageStatus;
  normal: ScryfallImageStatus;
  small: ScryfallImageStatus;
};

export type ScryfallCardLayout = string;

export type ScryfallWatermark = string;

export type ScryfallCardFace = {
  object: 'card_face';
  name: string;
  mana_cost: string;
  artist?: string;
  cmc?: number;
  color_indicator?: Color[];
  colors?: Color[];
  flavor_text?: string;
  illustration_id?: string;
  image_uris?: ScryfallCardImages;
  layout?: ScryfallCardLayout;
  loyalty?: string;
  oracle_id?: string;
  oracle_text?: string;
  power?: string;
  printed_name?: string;
  printed_text?: string;
  printed_type_line?: string;
  toughness?: string;
  type_line?: string;
  watermark?: ScryfallWatermark;
};

export type ScryfallBorderColor = 'black' | 'white' | 'borderless' | 'silver' | 'gold';

export type ScryfallCardFinish = 'foil' | 'nonfoil' | 'etched';

export type ScryfallCardFrame = '1993' | '1997' | '2003' | '2015' | 'future';

export type ScryfallFrameEffect =
  | 'legendary'
  | 'miracle'
  | 'nyxtouched'
  | 'draft'
  | 'devoid'
  | 'tombstone'
  | 'colorshifted'
  | 'inverted'
  | 'sunmoondfc'
  | 'compasslanddfc'
  | 'originpwdfc'
  | 'monoeldrazidfc'
  | 'waxingandwaningmoondfc'
  | 'showcase'
  | 'extendedart'
  | 'companion'
  | 'etched'
  | 'snow'
  | 'lesson'
  | 'shatteredglass'
  | 'convertdfc'
  | 'fandfc'
  | 'upsidedowndfc';

export type ScryfallGame = 'paper' | 'arena' | 'mtgo';

export type ScryfallCardPrices = {
  usd: string | null;
  usd_foil: string | null;
  usd_etched: string | null;
  eur: string | null;
  tix: string | null;
};

export type ScryfallPromoType = string;

export type ScryfallCardRarity = 'common' | 'uncommon' | 'rare' | 'special' | 'mythic' | 'bonus';

export type ScryfallCardSecurityStamp = 'oval' | 'triangle' | 'acorn' | 'circle' | 'arena' | 'heart';

export type ScryfallPrintFields = {
  artist?: string;
  attraction_lights?: number[];
  booster: boolean;
  border_color: ScryfallBorderColor;
  card_back_id: string;
  collector_number: string;
  content_warning?: boolean;
  digital: boolean;
  finishes: ScryfallCardFinish[];
  flavor_name?: string;
  flavor_text?: string;
  frame_effects?: ScryfallFrameEffect[];
  frame: ScryfallCardFrame;
  full_art: boolean;
  games: ScryfallGame[];
  highres_image: boolean;
  illustration_id?: string;
  image_status: ScryfallCardImageStatuses;
  image_uris?: ScryfallCardImages;
  prices: ScryfallCardPrices;
  printed_name?: string;
  printed_text?: string;
  printed_type_line?: string;
  promo: boolean;
  promo_types?: ScryfallPromoType[];
  purchase_uris: Record<string, string>;
  rarity: ScryfallCardRarity;
  related_uris: Record<string, string>;
  released_at: string;
  reprint: boolean;
  scryfall_set_uri: string;
  set_name: string;
  set_search_uri: string;
  set_type: string;
  set_uri: string;
  set: string;
  set_id: string;
  story_spotlight: boolean;
  textless: boolean;
  variation: boolean;
  variation_of?: string;
  security_stamp?: ScryfallCardSecurityStamp;
  watermark?: ScryfallWatermark;
  preview?: {
    previewed_at?: string;
    source_uri?: string;
    source?: string;
  };
};

export type ScryfallLegality = 'legal' | 'not_legal' | 'restricted' | 'banned';

export type ScryfallLegalities = {
  standard: ScryfallLegality;
  future: ScryfallLegality;
  historic: ScryfallLegality;
  gladiator: ScryfallLegality;
  pioneer: ScryfallLegality;
  explorer: ScryfallLegality;
  modern: ScryfallLegality;
  legacy: ScryfallLegality;
  pauper: ScryfallLegality;
  vintage: ScryfallLegality;
  penny: ScryfallLegality;
  commander: ScryfallLegality;
  brawl: ScryfallLegality;
  historicbrawl: ScryfallLegality;
  alchemy: ScryfallLegality;
  paupercommander: ScryfallLegality;
  duel: ScryfallLegality;
  oldschool: ScryfallLegality;
  premodern: ScryfallLegality;
};

export type ScryfallGameplayFields = {
  all_parts?: ScryfallRelatedCard[];
  card_faces?: ScryfallCardFace[];
  cmc: number;
  color_identity: Color[];
  color_indicator?: Color[];
  colors?: Color[];
  edhrec_rank?: number;
  hand_modifier?: string;
  keywords: string[];
  layout: ScryfallCardLayout;
  legalities: ScryfallLegalities;
  life_modifier?: string;
  loyalty?: string;
  mana_cost?: string;
  name: string;
  oracle_text?: string;
  oversized: boolean;
  penny_rank?: number;
  power?: string;
  produced_mana: (Color | 'C')[];
  reserved: boolean;
  toughness?: string;
  type_line: string;
};
