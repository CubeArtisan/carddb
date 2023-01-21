{
  description = "CubeArtisan Card Database";
  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:nixos/nixpkgs/nixpkgs-unstable";
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
      };
      nodejs = pkgs.stdenv.mkDerivation {
        name = "corepack-shims";
        buildInputs = [ pkgs.nodejs-18_x ];
        phases = [ "installPhase" ];
        installPhase = ''
          mkdir -p $out/bin
          corepack enable --install-directory=$out/bin
        '';
      };
      drv = pkgs.mkShell {
        name = "cubeartisan-carddb";
        buildInputs = [
          nodejs
          pkgs.nodejs-18_x
        ];
        shellHook = ''
          export PNPM_HOME=$HOME/node_modules
          export PATH=$PATH:$PNPM_HOME
        '';
      };
    in
    {
      devShell = drv;
      defaultPackage = drv;
    }
  );
}
