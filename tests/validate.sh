#!/bin/bash

# Default desktop file path
DEFAULT_DESKTOP="$HOME/.local/share/applications/WhatsApp.desktop"

DESKTOP_FILE="${1:-$DEFAULT_DESKTOP}"

if ! command -v desktop-file-validate &> /dev/null; then
  echo "Error: desktop-file-validate command not found. Please install 'desktop-file-utils'."
  exit 2
fi

echo "Validating $DESKTOP_FILE..."
desktop-file-validate "$DESKTOP_FILE"

if [ $? -eq 0 ]; then
  echo "No errors found in $DESKTOP_FILE."
else
  echo "Errors/warnings found in $DESKTOP_FILE."
fi

# Optional: update icon cache if icon directory exists
ICON_DIR="$HOME/.local/share/icons/hicolor"
if [ -d "$ICON_DIR" ]; then
  echo "Updating icon cache for $ICON_DIR ..."
  gtk-update-icon-cache -f -t "$ICON_DIR"
fi
