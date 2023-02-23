import type {
  Color,
  ScryfallBorderColor,
  ScryfallCardFinish,
  ScryfallCardFrame,
  ScryfallCardLayout,
  ScryfallCardPrices,
  ScryfallCardRarity,
  ScryfallCardSecurityStamp,
  ScryfallFrameEffect,
  ScryfallGame,
  ScryfallLegalities,
  ScryfallPromoType,
  ScryfallWatermark,
} from '@cubeartisan/carddb/types/scryfall';

export type ManaSymbol =
  | Color
  | 'W'
  | 'U'
  | 'B'
  | 'R'
  | 'G'
  | 'C'
  | 'W/U'
  | 'U/B'
  | 'B/R'
  | 'R/G'
  | 'G/W'
  | 'W/B'
  | 'U/R'
  | 'B/G'
  | 'R/W'
  | 'G/U'
  | '2/W'
  | '2/U'
  | '2/B'
  | '2/R'
  | '2/G'
  | 'P'
  | 'W/P'
  | 'U/P'
  | 'B/P'
  | 'R/P'
  | 'G/P'
  | 'W/U/P'
  | 'U/B/P'
  | 'B/R/P'
  | 'R/G/P'
  | 'G/W/P'
  | 'W/B/P'
  | 'U/R/P'
  | 'B/G/P'
  | 'R/W/P'
  | 'G/U/P'
  | 'S'
  | '0'
  | '½'
  | '1'
  | '2'
  | '3'
  | '4'
  | '5'
  | '6'
  | '7'
  | '8'
  | '9'
  | '10'
  | '11'
  | '12'
  | '13'
  | '14'
  | '15'
  | '16'
  | '17'
  | '18'
  | '19'
  | '20'
  | '100'
  | '1000000'
  | '∞'
  | 'X'
  | 'Y'
  | 'Z'
  | 'HW'
  | 'HR';

export type CardImages = {
  /**
   * @format url
   */
  small?: string;
  /**
   * @format url
   */
  normal?: string;
  /**
   * @format url
   */
  large?: string;
  /**
   * @format url
   */
  png?: string;
  /**
   * @format url
   */
  border_crop?: string;
  /**
   * @format url
   */
  art_crop?: string;
};

export type ExternalCardIds = {
  /**
   * @type uint
   */
  arena_id?: number;
  /**
   * @format uuid
   */
  scryfall_id?: string;
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
  /**
   * @type uuid
   */
  oracle_id?: string;
};

export type CardSource = 'scryfall' | 'custom';

export type CardFace = {
  name: string;
  mana_cost: ManaSymbol[];
  images: CardImages;
  cmc: number;
  color_indicator?: Color[];
  colors: Color[];
  layout?: ScryfallCardLayout;
  loyalty?: string;
  oracle_text: string;
  power?: string;
  produced_mana?: (Color | 'C')[];
  toughness?: string;
  type_line: string;
  flavor_text?: string;
  /**
   * @format uuid
   */
  illustration_id?: string;
  /**
   * @format uuid
   */
  oracle_id?: string;
  printed_name?: string;
  printed_text?: string;
  printed_type_line?: string;
  watermark?: ScryfallWatermark;
  artist?: string;
  attraction_lights?: number[];
  border_color: ScryfallBorderColor;
  collector_number: string;
  flavor_name?: string;
  frame_effects?: ScryfallFrameEffect[];
  frame: ScryfallCardFrame;
  full_art: boolean;
  highres_image: boolean;
  story_spotlight: boolean;
  textless: boolean;
  security_stamp?: ScryfallCardSecurityStamp;
};

export type RelatedCard = {
  id: string;
  kind: 'token' | 'meld_part' | 'meld_result' | 'combo_piece';
};

export type ColorCategory =
  | 'White'
  | 'Blue'
  | 'Black'
  | 'Red'
  | 'Green'
  | 'Hybrid'
  | 'Multicolored'
  | 'Colorless'
  | 'Land';

export type Card = {
  id: string;
  source: CardSource;
  externalIds: ExternalCardIds;
  /**
   * Face specific details of the card
   *
   * @minLength 1
   */
  cardFaces: CardFace[];
  color_category: ColorCategory;
  color_identity: Color[];
  related?: RelatedCard[];
  legalities: ScryfallLegalities;
  edhrec_rank?: number;
  hand_modifier?: string;
  keywords: string[];
  life_modifier?: string;
  oversized: boolean;
  penny_rank?: number;
  reserved: boolean;
  booster: boolean;
  content_warning?: boolean;
  digital: boolean;
  finishes: ScryfallCardFinish[];
  games: ScryfallGame[];
  prices: ScryfallCardPrices;
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
  set_name: string;
  set_type: string;
  set: string;
  set_id: string;
  variation: boolean;
  variation_of?: string;
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
