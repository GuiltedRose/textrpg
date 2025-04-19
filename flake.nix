{
  description = "TextRPG - Linux-only C++17 game using CMake";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";
  inputs.flake-utils.url = "github:numtide/flake-utils";

  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [];
        };

        nativeBuildInputs = with pkgs; [
          cmake
          ninja
          clang
          pkg-config
        ];

        buildInputs = with pkgs; [
          xorg.libX11
          xorg.libXcursor
          xorg.libXrandr
          xorg.libXi
          wayland
        ];
      in
      {
        packages.default = pkgs.stdenv.mkDerivation {
          pname = "TextRPG";
          version = "1.0";

          src = ./.;

          nativeBuildInputs = nativeBuildInputs;
          buildInputs = buildInputs;

          cmakeFlags = [
            "-DCMAKE_BUILD_TYPE=Release"
          ];

          installPhase = ''
            mkdir -p $out/bin
            cp TextRPG $out/bin/
          '';
        };

        devShells.default = pkgs.mkShell {
          nativeBuildInputs = nativeBuildInputs;
          buildInputs = buildInputs;

          shellHook = ''
            echo "TextRPG dev shell loaded. Use 'cmake -B build && cmake --build build' to compile."
          '';
        };
      });
}