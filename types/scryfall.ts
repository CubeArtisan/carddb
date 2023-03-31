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
  /**
   * @format uri
   */
  next_page?: string;
  total_cards?: number;
  warnings?: string[];
};

export type ScryfallBulkDataObject = {
  object: 'bulk_data';
  /**
   * @format uuid
   */
  id: string;
  type: 'oracle_cards' | 'unique_artwork' | 'default_cards' | 'all_cards' | 'rulings';
  /**
   * @format date-time
   */
  updated_at: string;
  /**
   * @format uri
   */
  uri: string;
  name: string;
  description: string;
  /**
   * @type uint
   */
  size: number;
  /**
   * @format uri
   */
  download_uri: string;
  content_type: string;
  content_encoding: string;
};

export type ScryfallBulkList = ScryfallList<ScryfallBulkDataObject>;

export type ScryfallMigration = {
  object: 'migration';
  /**
   * @format uri
   */
  uri: string;
  /**
   * @format uuid
   */
  id: string;
  /**
   * @format date-time
   */
  created_at: string;
  migration_strategy: 'merge' | 'delete';
  /**
   * @format uuid
   */
  old_scryfall_id: string;
  /**
   * @format uuid
   */
  new_scryfall_id?: string;
  note?: string;
};

export type ScryfallRulingSource = 'wotc' | 'scryfall';

export type ScryfallRuling = {
  source: ScryfallRulingSource;
  /**
   * @format date-time
   */
  published_at: string;
  comment: string;
};

export type ScryfallCoreCard = {
  object: 'card';
  /**
   * @type uint
   */
  arena_id?: number;
  /**
   * @format uuid
   */
  id: string;
  /**
   * @type uint
   */
  mtgo_id?: number;
  /**
   * @type uint
   */
  mtgo_foil_id?: number;
  multiverse_ids?: number[];
  /**
   * @type uint
   */
  tcgplayer_id?: number;
  /**
   * @type uint
   */
  tcgplayer_etched_id?: number;
  /**
   * @type uint
   */
  cardmarket_id?: number;
  oracle_id?: string;
  /**
   * @format uri
   */
  prints_search_uri: string;
  /**
   * @format uri
   */
  rulings_uri: string;
  /**
   * @format uri
   */
  scryfall_uri: string;
  /**
   * @format uri
   */
  uri: string;
};

export type ScryfallRelatedCard = {
  object: 'related_card';
  /**
   * @format uuid
   */
  id: string;
  component: 'token' | 'meld_part' | 'meld_result' | 'combo_piece';
  type_line: string;
  /**
   * @format uri
   */
  uri: string;
};

export type Color = 'W' | 'U' | 'B' | 'R' | 'G';

export type ScryfallImageStatus = 'missing' | 'placeholder' | 'lowres' | 'highres_scan';

export type ScryfallCardImages = {
  /**
   * @format uri
   */
  png: string;
  /**
   * @format uri
   */
  border_crop: string;
  /**
   * @format uri
   */
  art_crop: string;
  /**
   * @format uri
   */
  large: string;
  /**
   * @format uri
   */
  normal: string;
  /**
   * @format uri
   */
  small: string;
};

export type ScryfallCardImageStatuses =
  | {
      png: ScryfallImageStatus;
      border_crop: ScryfallImageStatus;
      art_crop: ScryfallImageStatus;
      large: ScryfallImageStatus;
      normal: ScryfallImageStatus;
      small: ScryfallImageStatus;
    }
  | ScryfallImageStatus;

export type ScryfallFaceLayout = string;

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
  layout?: ScryfallFaceLayout;
  loyalty?: string;
  /**
   * @format uuid
   */
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
  | 'colorshifted'
  | 'companion'
  | 'compasslanddfc'
  | 'convertdfc'
  | 'devoid'
  | 'draft'
  | 'etched'
  | 'extendedart'
  | 'fandfc'
  | 'fullart'
  | 'inverted'
  | 'legendary'
  | 'lesson'
  | 'miracle'
  | 'mooneldrazidfc'
  | 'nyxtouched'
  | 'originpwdfc'
  | 'shatteredglass'
  | 'showcase'
  | 'snow'
  | 'sunmoondfc'
  | 'textless'
  | 'tombstone'
  | 'upsidedowndfc'
  | 'waxingandwaningmoondfc';

export type ScryfallGame = 'paper' | 'arena' | 'mtgo' | 'astral' | 'sega';

export type ScryfallCardPrices = {
  /**
   * @pattern \d+.\d\d
   */
  usd: string | null;
  /**
   * @pattern \d+.\d\d
   */
  usd_foil: string | null;
  /**
   * @pattern \d+.\d\d
   */
  usd_etched: string | null;
  /**
   * @pattern \d+.\d\d
   */
  eur: string | null;
  /**
   * @pattern \d+.\d\d
   */
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
  card_back_id?: string;
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
  /**
   * @format uuid
   */
  illustration_id?: string;
  image_status: ScryfallCardImageStatuses;
  image_uris?: ScryfallCardImages;
  prices: ScryfallCardPrices;
  printed_name?: string;
  printed_text?: string;
  printed_type_line?: string;
  promo: boolean;
  promo_types?: ScryfallPromoType[];
  purchase_uris?: Record<string, string>;
  rarity: ScryfallCardRarity;
  related_uris: Record<string, string>;
  /**
   * @format date
   */
  released_at: string;
  reprint: boolean;
  /**
   * @format uri
   */
  scryfall_set_uri: string;
  set_name: string;
  /**
   * @format uri
   */
  set_search_uri: string;
  set_type: string;
  /**
   * @format uri
   */
  set_uri: string;
  set: string;
  /**
   * @format uuid
   */
  set_id: string;
  story_spotlight: boolean;
  textless: boolean;
  variation: boolean;
  variation_of?: string;
  security_stamp?: ScryfallCardSecurityStamp;
  watermark?: ScryfallWatermark;
  preview?: {
    /**
     * @format date
     */
    previewed_at?: string;
    /**
     * @format uri
     */
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
  cmc?: number;
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
  produced_mana?: (Color | 'C' | 'T' | '2')[];
  reserved: boolean;
  toughness?: string;
  type_line?: string;
};

export type ScryfallCard = ScryfallCoreCard &
  ScryfallGameplayFields &
  ScryfallPrintFields & {
    card_faces?: ScryfallCardFace[];
    all_parts?: ScryfallRelatedCard[];
  };
