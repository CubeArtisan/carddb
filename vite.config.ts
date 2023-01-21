import { resolve } from 'path';

import dts from 'vite-plugin-dts';
import { nodePolyfills } from 'vite-plugin-node-polyfills';
import { defineConfig } from 'vitest/config';

export default defineConfig({
  plugins: [
    dts(),
    // nodePolyfills({
    //   // Whether to polyfill `node:` protocol imports.
    //   protocolImports: true,
    // }),
  ],
  resolve: {
    alias: {
      '@cubeartisan/carddb': __dirname,
    },
  },
  build: {
    rollupOptions: {
      external: ['node:fs', 'node:stream', 'node:stream/promises'],
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
