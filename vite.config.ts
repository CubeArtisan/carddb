import { resolve } from 'path';

import dts from 'vite-plugin-dts';
import { defineConfig } from 'vitest/config';

export default defineConfig({
  plugins: [dts()],
  resolve: {
    alias: {
        '@cubeartisan/carddb': __dirname,
    },
  },
  build: {
    lib: {
      entry: resolve(__dirname, 'index.ts'),
      name: "CubeArtisan CardDB",
      formats: ['es'],
    },
  },
  envDir: __dirname,
  test: {
    globals: true,
    isolate: true,
  },
});
