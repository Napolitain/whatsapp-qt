# whatsapp-qt

A Qt 6 desktop client for WhatsApp Web with native system integration.

## Features

- Native desktop notifications
- System tray with controls
- Audio/video call support
- Camera and microphone access
- Wayland and X11 support

## Installation

### From Snap Store

```bash
sudo snap install whatsapp-qt
```

### Build from Source

#### Prerequisites

- CMake 3.28+
- Qt 6.x with WebEngine module
- vcpkg
- C++20 compatible compiler (GCC 13+, Clang 16+)

#### Build Steps

```bash
# Clone repository
git clone https://github.com/napolitain/whatsapp-qt.git
cd whatsapp-qt

# Clone and bootstrap vcpkg
git clone https://github.com/microsoft/vcpkg.git
./vcpkg/bootstrap-vcpkg.sh

# Configure
cmake -B build -S . \
  -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=./vcpkg/scripts/buildsystems/vcpkg.cmake

# Build
cmake --build build -j$(nproc)

# Run
./build/WhatsApp
```

### Building the Snap Package

```bash
# Install LXD (required for containerized builds)
sudo snap install lxd
sudo lxd init --auto
sudo usermod -aG lxd $USER
newgrp lxd

# Build
snapcraft --use-lxd

# Install locally
sudo snap install --dangerous ./whatsapp-qt_*.snap
```

## Usage

Launch from your application menu or run:

```bash
whatsapp-qt
```

The application will open WhatsApp Web in a native window with system tray integration.

## Permissions

The snap requires the following permissions:
- `audio-playback` / `audio-record` - Voice/video calls
- `camera` - Video calls
- `network` / `network-bind` - WhatsApp connectivity
- `desktop` / `wayland` - Desktop integration
- `screen-inhibit-control` - Prevent screen sleep during calls

## License

See LICENSE file.
