{
  description = "Qt-based WhatsApp desktop client";

  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixos-26.05";

  outputs =
    { self, nixpkgs }:
    let
      systems = [ "x86_64-linux" ];
      forAllSystems = nixpkgs.lib.genAttrs systems;

      mkPkgs = system: import nixpkgs { inherit system; };

      mkWhatsappQt =
        pkgs:
        pkgs.stdenv.mkDerivation {
          pname = "whatsapp-qt";
          version = "unstable";

          src = self;

          nativeBuildInputs = with pkgs; [
            cmake
            ninja
            qt6.wrapQtAppsHook
          ];

          buildInputs = with pkgs.qt6; [
            qtbase
            qtwebengine
          ];

          cmakeBuildType = "Release";

          qtWrapperArgs = [
            "--set"
            "WHATSAPP_QT_SKIP_APP_REGISTRATION"
            "1"
          ];

          meta = {
            description = "Qt-based WhatsApp desktop client";
            homepage = "https://github.com/Napolitain/whatsapp-qt";
            license = pkgs.lib.licenses.mit;
            mainProgram = "whatsapp-qt";
            platforms = pkgs.lib.platforms.linux;
          };
        };
    in
    {
      packages = forAllSystems (
        system:
        let
          pkgs = mkPkgs system;
          whatsappQt = mkWhatsappQt pkgs;
        in
        {
          default = whatsappQt;
          whatsapp-qt = whatsappQt;
        }
      );

      apps = forAllSystems (
        system:
        let
          package = self.packages.${system}.default;
        in
        {
          default = {
            type = "app";
            program = "${package}/bin/whatsapp-qt";
            meta.description = "Run WhatsApp Qt";
          };
          whatsapp-qt = {
            type = "app";
            program = "${package}/bin/whatsapp-qt";
            meta.description = "Run WhatsApp Qt";
          };
        }
      );

      devShells = forAllSystems (
        system:
        let
          pkgs = mkPkgs system;
        in
        {
          default = pkgs.mkShell {
            packages = with pkgs; [
              cmake
              ninja
              qt6.qtbase
              qt6.qtwebengine
              qt6.wrapQtAppsHook
            ];
          };
        }
      );
    };
}
