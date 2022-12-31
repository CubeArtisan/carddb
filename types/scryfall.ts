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
