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
  borderCrop?: string;
  /**
   * @format url
   */
  artCrop?: string;
};

export type ExternalCardIds = {
  /**
   * @type uint
   */
  arenaId?: number;
  /**
   * @format uuid
   */
  scryfallId?: string;
  /**
   * @type uint
   */
  mtgoId?: number;
  /**
   * @type uint
   */
  mtgoFoilId?: number;
  multiverseIds?: number[];
  /**
   * @type uint
   */
  tcgplayerId?: number;
  /**
   * @type uint
   */
  tcgplayerEtchedId?: number;
  /**
   * @type uint
   */
  cardmarketId?: number;
  /**
   * @format uuid
   */
  oracleId?: string;
};

export type CardSource = 'scryfall' | 'custom';

export type CardFace = {
  name: string;
  manaCost: ManaSymbol[];
  images: CardImages;
  colorIndicator?: Color[];
  /**
   * The colors of the card face.
   */
  colors: Color[];
  /**
   * The cmc of the card face.
   */
  cmc: number;
  layout?: ScryfallCardLayout;
  loyalty?: string;
  oracleText: string;
  power?: string;
  producedMana?: (Color | 'C')[];
  toughness?: string;
  typeLine: string;
  flavorText?: string;
  /**
   * @format uuid
   */
  illustrationId?: string;
  printedName?: string;
  printedText?: string;
  printedTypeLine?: string;
  watermark?: ScryfallWatermark;
  artist?: string;
  attractionLights?: number[];
  borderColor: ScryfallBorderColor;
  flavorName?: string;
  frameEffects?: ScryfallFrameEffect[];
  frame: ScryfallCardFrame;
  fullArt: boolean;
  highresImage: boolean;
  storySpotlight: boolean;
  textless: boolean;
  securityStamp?: ScryfallCardSecurityStamp;
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

export type CardStatus = 'Not Owned' | 'Ordered' | 'Owned' | 'Premium Owned' | 'Proxied';

export type CardMetadata = {
  tags: string[];
  price?: number;
  notes: string;
  /**
   * @format date
   */
  addedTmsp: string;
  finish: ScryfallCardFinish;
  status: CardStatus;
};

export type Card = {
  id: string;
  source: CardSource;
  externalIds: ExternalCardIds;
  /**
   * The name that can be used for importing this card.
   */
  name: string;
  layout: ScryfallCardLayout;
  /**
   * Face specific details of the card
   */
  cardFaces: CardFace[];
  /**
   * The colors of the card in zones other than the stack/battlefield.
   */
  colors: Color[];
  /**
   * The cmc of the card in zones other than the stack/battlefield.
   */
  cmc: number;
  collectorNumber: string;
  colorCategory: ColorCategory;
  colorIdentity: Color[];
  related: RelatedCard[];
  legalities: ScryfallLegalities;
  edhrecRank?: number;
  handModifier?: string;
  lifeModifier?: string;
  keywords: string[];
  oversized: boolean;
  pennyRank?: number;
  reserved: boolean;
  booster: boolean;
  digital: boolean;
  finishes: ScryfallCardFinish[];
  games: ScryfallGame[];
  prices: ScryfallCardPrices;
  promo: boolean;
  promoTypes: ScryfallPromoType[];
  purchaseUris?: Record<string, string>;
  rarity: ScryfallCardRarity;
  relatedUris?: Record<string, string>;
  /**
   * @format date
   */
  releasedAt: string;
  reprint: boolean;
  setName: string;
  setType: string;
  set: string;
  setId: string;
  variation: boolean;
  variationOf?: string;
  preview?: {
    /**
     * @format date
     */
    previewedAt?: string;
    /**
     * @format uri
     */
    sourceUri?: string;
    source?: string;
  };
  metadata?: CardMetadata;
};
