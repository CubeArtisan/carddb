import fs from 'node:fs';
import { Readable } from 'node:stream';
import { finished } from 'node:stream/promises';

import type { ScryfallBulkDataObject } from '@cubeartisan/carddb/types/scryfall';

export const getBulkDataInfo = async () => {
  const res = await fetch('https://api.scryfall.com/bulk-data');
  if (res.status !== 200) {
    throw new Error(`Invalid response status of ${res.status}.`);
  }
  return res.json();
};

export const downloadBulkData = async (bulkData: ScryfallBulkDataObject, dest?: string) => {
  dest ??= `${bulkData.type}.json`;
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
