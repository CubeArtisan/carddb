import fs from 'node:fs';
import { readFile, writeFile } from 'node:fs/promises';
import { Readable } from 'node:stream';
import { finished } from 'node:stream/promises';

import { parseChunked } from '@discoveryjs/json-ext';
import { assert, assertParse, assertStringify, createAssert, createIs, createValidate } from 'typia';

import type {
  ScryfallBulkDataObject,
  ScryfallBulkList,
  ScryfallCard,
  ScryfallRuling,
} from '@cubeartisan/carddb/types/scryfall';

export const assertBulkData = createAssert<ScryfallBulkList>();

export const getBulkDataInfo = async () => {
  const res = await fetch('https://api.scryfall.com/bulk-data');
  if (res.status !== 200) {
    throw new Error(`Invalid response status of ${res.status}.`);
  }
  const value = await res.json();
  return assertBulkData(value);
};

export const downloadBulkData = async (bulkData: ScryfallBulkDataObject, dest?: string) => {
  dest ??= `data/${bulkData.type}.json`;
  const fileStream = fs.createWriteStream(dest);
  const res = await fetch(bulkData.download_uri);
  if (res.status !== 200) {
    throw new Error(`Invalid response status of ${res.status}.`);
  }
  const { body } = res;
  if (!body) {
    throw new Error('Body of download_uri was null');
  }
  await finished(Readable.fromWeb(body).pipe(fileStream));
  return dest;
};

export const readLargeJson = async (path: string) => {
  const contents = fs.createReadStream(path);
  return parseChunked(contents);
};

export const validateCardArray = createValidate<ScryfallCard[]>();
export const validateRulingArray = createValidate<ScryfallRuling[]>();

export const isBulkData = createIs<ScryfallBulkList>();

export type LastUpdatedDates = { [K in ScryfallBulkDataObject['type']]?: Date };

const VERIFIER = {
  oracle_cards: validateCardArray,
  unique_artwork: validateCardArray,
  default_cards: validateCardArray,
  all_cards: validateCardArray,
  rulings: validateRulingArray,
};

const updateSpecificBulkData = async (bulkInfo: ScryfallBulkDataObject, lastUpdated: LastUpdatedDates) => {
  const updated = lastUpdated[bulkInfo.type];
  const trueUpdate = new Date(bulkInfo.updated_at);
  if (updated && updated >= trueUpdate) {
    console.info(`Skipping ${bulkInfo.type} since it is already the latest version.`);
  } else {
    const filePath = await downloadBulkData(bulkInfo);
    const verification = VERIFIER[bulkInfo.type](await readLargeJson(filePath));
    if (!verification.success) {
      console.error(`${bulkInfo.type} failed validation. ${verification.errors.toString()}`);
      delete lastUpdated[bulkInfo.type];
    } else {
      lastUpdated[bulkInfo.type] = trueUpdate;
    }
  }
};

export const getLastUpdated = async (path = 'data/last_updated.json') => {
  const contents = await readFile(path);
  return assert<LastUpdatedDates>(
    Object.fromEntries(
      Object.entries(JSON.parse(contents.toString()) as Record<keyof LastUpdatedDates, string>).map(([key, value]) => [
        key,
        new Date(value),
      ]),
    ),
  );
};

export const writeLastUpdated = async (lastUpdated: LastUpdatedDates, path = 'data/last_updated.json') => {
  const contents = assertStringify<LastUpdatedDates>(lastUpdated);
  await writeFile(path, contents);
  return path;
};

export const updateAllBulkData = async (lastUpdated?: LastUpdatedDates) => {
  if (!lastUpdated) {
    try {
      lastUpdated = await getLastUpdated();
    } catch (e) {
      console.warn(`Failed to load data/last_updated.json: ${e?.toString?.() ?? 'undefined'}`);
      lastUpdated = {};
    }
  }
  const bulkData = await getBulkDataInfo();
  const newLastUpdated = { ...lastUpdated };
  await Promise.all(bulkData.data.map((bulkInfo) => updateSpecificBulkData(bulkInfo, newLastUpdated)));
  await writeLastUpdated(newLastUpdated);
  return newLastUpdated;
};
