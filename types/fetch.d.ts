declare global {
  export const { fetch, FormData, Headers, Request, Response }: typeof import('undici');
  export type { RequestInit } from 'undici';
}

export {};
