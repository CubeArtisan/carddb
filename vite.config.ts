import { resolve } from 'path';

import typescript from '@rollup/plugin-typescript';
import ttypescript from 'ttypescript';
import dts from 'vite-plugin-dts';
import { defineConfig } from 'vitest/config';

export default defineConfig({
  plugins: [
    dts(),
    typescript({
      typescript: ttypescript,
    }),
  ],
  resolve: {
    alias: {
      '@cubeartisan/carddb': __dirname,
    },
  },
  build: {
    rollupOptions: {
      external: ['node:fs', 'node:stream', 'node:stream/promises', 'node:fs/promises'],
    },
    lib: {
      entry: resolve(__dirname, 'index.ts'),
      name: 'CubeArtisan CardDB',
      formats: ['es'],
    },
  },
  envDir: __dirname,
  test: {
    globals: true,
    isolate: true,
    passWithNoTests: true,
  },
});
