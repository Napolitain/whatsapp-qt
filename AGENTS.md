# Agent Instructions

This document provides guidance for AI agents working on this codebase.

## Project Overview

whatsapp-qt is a Qt 6 desktop client for WhatsApp Web, providing native system integration including notifications and system tray controls.

## Tech Stack

- **Language**: C++20
- **Framework**: Qt 6 (Core, Gui, Widgets, WebEngineWidgets)
- **Build System**: CMake 3.28+
- **Package Manager**: vcpkg (for fmt, glog)
- **Packaging**: Snapcraft (kde-neon-6 extension)

## Building

### Prerequisites

- CMake 3.28+
- Qt 6.x with WebEngine
- vcpkg
- C++20 compatible compiler (GCC 13+, Clang 16+)

### Normal CMake Build

```bash
# Clone and bootstrap vcpkg (if not already installed)
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh

# Configure with vcpkg toolchain
cmake -B build -S . \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build -j$(nproc)

# Run
./build/WhatsApp
```

### Snapcraft Build

Requires LXD for containerized builds:

```bash
# Install LXD (one-time setup)
sudo snap install lxd
sudo lxd init --auto
sudo usermod -aG lxd $USER
newgrp lxd

# Build snap
cd /path/to/whatsapp-qt
snapcraft --use-lxd

# Install locally
sudo snap install --dangerous ./whatsapp-qt_*.snap
```

## Project Structure

```
whatsapp-qt/
├── CMakeLists.txt          # Main build configuration
├── snapcraft.yaml          # Snap packaging configuration
├── vcpkg.json              # vcpkg dependencies manifest
├── include/                # Header files
│   ├── AppRegistration.hpp
│   ├── AutoStart.hpp
│   ├── Constants.hpp
│   ├── Tray.hpp
│   ├── WebProfile.hpp
│   └── WhatsAppView.hpp
├── src/                    # Source files
├── resources/              # Qt resources (icons, qrc)
└── tests/                  # Test files
```

## Key Files

- `src/main.cpp` - Application entry point
- `include/WhatsAppView.hpp` - Main WebEngine view
- `include/Tray.hpp` - System tray integration
- `snapcraft.yaml` - Snap build configuration using kde-neon-6 extension

## Testing

```bash
cmake --build build --target test
```

## Common Issues

### Snap Build Linker Errors

If you see undefined references to `xkb_*`, `event_*`, or `duk_*` symbols during snap builds, ensure the cmake-parameters in snapcraft.yaml include proper linker flags pointing to the SDK snap's library directory.
