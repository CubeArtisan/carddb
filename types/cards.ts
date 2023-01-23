import type { Color } from '@cubeartisan/carddb/types/scryfall';

export type ManaSymbol = Color;

export type CardImages = {
  small: URL;
  normal: URL;
  large: URL;
  png: URL;
  border_crop: URL;
  art_crop: URL;
};

export type CardFace = {
  name: string;
  mana_cost: ManaSymbol[];
  image_uris: CardImages;
};

export type RelatedCard = {
  id: string;
};

export type Card = {
  /**
   * Face specific details of the card
   * @minLength 1
   */
  cardFaces: CardFace[];
  related?: RelatedCard[];
  oracleId: string;
};
