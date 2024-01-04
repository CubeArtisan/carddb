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
      drv = pkgs.stdenv.mkDerivation{
        name = "cubeartisan-carddb";
        buildInputs = [
          nodejs
          pkgs.nodejs_20
          pkgs.pkg-config
          pkgs.emscripten
          pkgs.clang_16
          pkgs.clang-tools_16
          pkgs.cmake
          pkgs.ninja
          pkgs.closurecompiler
        ];
        shellHook = ''
          export CXX=clang++
          export EM_CACHE=`pwd`/.emscripten_cache
          if [[ ! -d $EM_CACHE ]] then
            cp -r ${pkgs.emscripten}/share/emscripten/cache $EM_CACHE
            chmod u+rwX -R $EM_CACHE
          fi
        '';
      };
    in
    {
      devShell = drv;
      defaultPackage = drv;
    }
  );
}
