import { createValidate } from 'typia';

import type {
  Card,
  CardFace,
  CardImages,
  ColorCategory,
  ExternalCardIds,
  ManaSymbol,
} from '@cubeartisan/carddb/types/cards';
import type { Color, ScryfallCard, ScryfallCardFace } from '@cubeartisan/carddb/types/scryfall';

const toColorCategory = (faces: CardFace[]): ColorCategory => {
  let seen: ManaSymbol | null = null;
  for (const face of faces) {
    if (face.typeLine.includes('Land')) return 'Land';
  }
  for (const face of faces) {
    for (let symbol of face.manaCost) {
      if (symbol.startsWith('H')) symbol = symbol[1] as ManaSymbol;
      if (['W', 'U', 'B', 'R', 'G'].includes(symbol)) {
        if (seen && seen !== symbol) return 'Multicolored';
        seen = symbol;
      } else if (
        !(symbol.includes('P') || symbol.includes('2') || Array.from(symbol).every((c) => '0123456789S½∞'.includes(c)))
      ) {
        if (symbol.includes('/')) return 'Hybrid';
        return 'Multicolored';
      }
    }
  }
  if (seen === 'W') return 'White';
  if (seen === 'U') return 'Blue';
  if (seen === 'B') return 'Black';
  if (seen === 'R') return 'Red';
  if (seen === 'G') return 'Green';
  return 'Colorless';
};

const COLOR_COMBINATIONS: Color[][] = [
  [],
  ['W'],
  ['U'],
  ['B'],
  ['R'],
  ['G'],
  ['W', 'U'],
  ['U', 'B'],
  ['B', 'R'],
  ['R', 'G'],
  ['G', 'W'],
  ['W', 'B'],
  ['U', 'R'],
  ['B', 'G'],
  ['R', 'W'],
  ['G', 'U'],
  ['G', 'W', 'U'],
  ['W', 'U', 'B'],
  ['U', 'B', 'R'],
  ['B', 'R', 'G'],
  ['R', 'G', 'W'],
  ['R', 'W', 'B'],
  ['G', 'U', 'R'],
  ['W', 'B', 'G'],
  ['U', 'R', 'W'],
  ['B', 'G', 'U'],
  ['U', 'B', 'R', 'G'],
  ['B', 'R', 'G', 'W'],
  ['R', 'G', 'W', 'U'],
  ['G', 'W', 'U', 'B'],
  ['W', 'U', 'B', 'R'],
  ['W', 'U', 'B', 'R', 'G'],
];

const arraysAreEqualSets = <T>(a1: T[], a2: T[]): boolean => {
  if (a1.length !== a2.length) {
    return false;
  }
  const set1 = new Set(a1);
  const set2 = new Set(a2);
  return a1.every((x) => set2.has(x)) && a2.every((x) => set1.has(x));
};

const sortColors = (colors: Color[]): Color[] => {
  for (let i = 0; i < COLOR_COMBINATIONS.length; i++) {
    if (arraysAreEqualSets(colors, COLOR_COMBINATIONS[i])) return COLOR_COMBINATIONS[i];
  }
  throw new Error(`Unknown color combination ${colors.join('')}`);
};

const toManaCost = (stringCost: string): ManaSymbol[] => {
  if (stringCost.length === 0) return [];
  return stringCost.slice(1, stringCost.length - 1).split('}{') as ManaSymbol[];
};

const copyIfExists = <U, T extends U>(original: T, assignee: U, keys: (keyof T & keyof U)[]): U => {
  for (const field of keys) {
    if ((original[field] ?? null) !== null) assignee[field] = original[field];
  }
  return assignee;
};

const getCardFace = (originalFace: ScryfallCard | ScryfallCardFace, originalCard: ScryfallCard): CardFace => {
  const images: CardImages = {};
  if (originalFace.image_uris) {
    images.small = originalFace.image_uris.small;
    images.normal = originalFace.image_uris.normal;
    images.large = originalFace.image_uris.large;
    images.png = originalFace.image_uris.png;
    images.borderCrop = originalFace.image_uris.border_crop;
    images.artCrop = originalFace.image_uris.art_crop;
  }
  const face: CardFace = {
    name: originalFace.name,
    manaCost: toManaCost(originalFace.mana_cost ?? ''),
    images,
    cmc: originalFace.cmc ?? 0,
    colors: originalFace.colors ?? [],
    oracleText: originalFace.oracle_text ?? '',
    producedMana: (originalCard.produced_mana?.filter((x) => x !== 'T' && x !== '2') ?? []) as (Color | 'C')[],
    typeLine: originalFace.type_line ?? '',
    borderColor: originalCard.border_color,
    frame: originalCard.frame,
    fullArt: originalCard.full_art,
    highresImage: originalCard.highres_image,
    storySpotlight: originalCard.story_spotlight,
    textless: originalCard.textless,
  };
  if ((originalFace.color_indicator ?? null) !== null) face.colorIndicator = originalFace.color_indicator;
  if ((originalFace.flavor_text ?? null) !== null) face.flavorText = originalFace.flavor_text;
  if ((originalFace.illustration_id ?? null) !== null) face.illustrationId = originalFace.illustration_id;
  if ((originalFace.printed_name ?? null) !== null) face.printedName = originalFace.printed_name;
  if ((originalFace.printed_text ?? null) !== null) face.printedText = originalFace.printed_text;
  if ((originalFace.printed_type_line ?? null) !== null) face.printedTypeLine = originalFace.printed_type_line;
  if ((originalCard.attraction_lights ?? null) !== null) face.attractionLights = originalCard.attraction_lights;
  if ((originalCard.flavor_name ?? null) !== null) face.flavorName = originalCard.flavor_name;
  if ((originalCard.frame_effects ?? null) !== null) face.frameEffects = originalCard.frame_effects;
  if ((originalCard.security_stamp ?? null) !== null) face.securityStamp = originalCard.security_stamp;
  copyIfExists<
    { [K in keyof CardFace & keyof ScryfallCardFace]?: ScryfallCardFace[K] },
    ScryfallCardFace | ScryfallCard
  >(originalFace, face, ['layout', 'loyalty', 'power', 'toughness', 'watermark', 'artist']);
  return face;
};
export const convertCard = (originalCard: ScryfallCard): Card => {
  const externalIds: ExternalCardIds = {
    scryfallId: originalCard.id,
  };

  if ((originalCard.arena_id ?? null) !== null) externalIds.arenaId = originalCard.arena_id;
  if ((originalCard.mtgo_id ?? null) !== null) externalIds.mtgoId = originalCard.mtgo_id;
  if ((originalCard.mtgo_foil_id ?? null) !== null) externalIds.mtgoFoilId = originalCard.mtgo_foil_id;
  if ((originalCard.multiverse_ids ?? null) !== null) externalIds.multiverseIds = originalCard.multiverse_ids;
  if ((originalCard.tcgplayer_id ?? null) !== null) externalIds.tcgplayerId = originalCard.tcgplayer_id;
  if ((originalCard.tcgplayer_etched_id ?? null) !== null) {
    externalIds.tcgplayerEtchedId = originalCard.tcgplayer_etched_id;
  }
  if ((originalCard.cardmarket_id ?? null) !== null) externalIds.cardmarketId = originalCard.cardmarket_id;
  if ((originalCard.oracle_id ?? null) !== null) externalIds.oracleId = originalCard.oracle_id;
  const cardFaces: CardFace[] = [];
  if (originalCard.card_faces) {
    for (const originalFace of originalCard.card_faces) {
      cardFaces.push(getCardFace(originalFace, originalCard));
    }
  } else {
    cardFaces.push(getCardFace(originalCard, originalCard));
  }
  const card: Card = {
    id: `scry:${originalCard.id}`,
    source: 'scryfall',
    externalIds,
    cardFaces,
    colorCategory: toColorCategory(cardFaces),
    colorIdentity: sortColors(originalCard.color_identity),
    legalities: originalCard.legalities,
    oversized: originalCard.oversized,
    reserved: originalCard.reserved,
    booster: originalCard.booster,
    digital: originalCard.digital,
    finishes: originalCard.finishes,
    games: originalCard.games,
    prices: originalCard.prices,
    promo: originalCard.promo,
    rarity: originalCard.rarity,
    relatedUris: originalCard.related_uris,
    releasedAt: originalCard.released_at,
    reprint: originalCard.reprint,
    setName: originalCard.set_name,
    setType: originalCard.set_type,
    set: originalCard.set,
    setId: originalCard.set_id,
    variation: originalCard.variation,
    keywords: originalCard.keywords,
    collectorNumber: originalCard.collector_number,
  };
  if (originalCard.all_parts) {
    card.related = originalCard.all_parts.map(({ id, component }) => ({ id: `scry:${id}`, kind: component }));
  }
  if (originalCard.edhrec_rank) card.edhrecRank = originalCard.edhrec_rank;
  if ((originalCard.hand_modifier ?? null) !== null) card.handModifier = originalCard.hand_modifier;
  if ((originalCard.life_modifier ?? null) !== null) card.lifeModifier = originalCard.life_modifier;
  if ((originalCard.penny_rank ?? null) !== null) card.pennyRank = originalCard.penny_rank;
  if ((originalCard.content_warning ?? null) !== null) card.contentWarning = originalCard.content_warning;
  if ((originalCard.promo_types ?? null) !== null) card.promoTypes = originalCard.promo_types;
  if ((originalCard.purchase_uris ?? null) !== null) card.purchaseUris = originalCard.purchase_uris;
  if ((originalCard.variation_of ?? null) !== null) card.variationOf = originalCard.variation_of;
  copyIfExists<{ [K in keyof Card & keyof ScryfallCard]?: ScryfallCard[K] }, ScryfallCard>(originalCard, card, [
    'preview',
  ]);
  return card;
};

export const validateCardArray = createValidate<Card[]>();
