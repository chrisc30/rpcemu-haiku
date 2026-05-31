# RPCEmu for Haiku

A port of [RPCEmu](https://www.marutan.net/rpcemu/) — the Acorn Risc PC and A7000 emulator — to the [Haiku operating system](https://www.haiku-os.org/).

Based on the [Cloverleaf fork](https://github.com/riscoscloverleaf/rpcemu) (v0.9.4) with additional patches for Haiku.

![RPCEmu running RISC OS 5 on Haiku](screenshot.png)

## Features

- Runs RISC OS 3.x and RISC OS 5 on Haiku (x86_64)
- NAT networking with internet access (HTTP, DNS)
- HostFS integration (share files between Haiku and RISC OS)
- Sound output via Haiku Media Kit
- Keyboard and mouse input
- CD-ROM ISO image support

## Requirements

- Haiku R1 Beta 4 or later (x86_64)
- Qt5 (`qt5`, `qt5_devel`, `qt5_multimedia`, `qt5_multimedia_devel`)
- A RISC OS ROM image (see [RISC OS Open](https://www.riscosopen.org/content/downloads/common))
- Optionally: a hard disc image (Easy Start Bundle recommended)

## Building

Install dependencies:

```sh
pkgman install qt5 qt5_devel qt5_multimedia qt5_multimedia_devel make
```

Clone and build:

```sh
git clone https://github.com/YOUR_USERNAME/rpcemu-haiku.git
cd rpcemu-haiku/src/qt5
/boot/system/bin/qmake rpcemu.pro
make -j$(nproc)
```

The binary is placed in the repository root as `rpcemu-interpreter`.

## Setup

1. Place a RISC OS ROM image in `roms/` named `riscos` (no extension)
2. Optionally place a hard disc image (`hd4.hdf`) in the repository root and add to `rpc.cfg`:
   ```ini
   hd_file=hd4.hdf
   ```
3. Run from the repository root:
   ```sh
   ./rpcemu-interpreter
   ```

The emulator must be run from its own directory so it can find `roms/`, `hostfs/`, `rpc.cfg` etc. When launched from Haiku's Tracker, a wrapper script is recommended:

```sh
#!/bin/sh
cd "$(dirname "$0")"
exec ./rpcemu-interpreter
```

## Networking

NAT networking is enabled by default. Set in `rpc.cfg`:

```ini
network_type=nat
```

Slirp assigns IP `10.10.10.10` to the emulated machine with gateway `10.10.10.2` and DNS at `10.10.10.3`. Configure these in RISC OS's `!Internet` settings or via DHCP.

## Haiku-specific patches

| File | Change |
|---|---|
| `src/rpcemu.h` | LFS64 compat (`fopen64` etc.) and `RPCEMU_NETWORKING` for Haiku |
| `src/rpc-machdep.c` | Expose `rpcemu_set_datadir()` on Haiku |
| `src/rpcemu.c` | Stop audio before sound thread close on Haiku |
| `src/network-haiku.c` | TUN/TAP stub (Haiku has no `/dev/net/tun`) |
| `src/network-nat.c` | NULL guard; background thread for slirp polling; restore `network_nat_reset()` |
| `src/slirp/slirp.c` | Use `/boot/system/settings/network/resolv.conf` for DNS |
| `src/qt5/rpcemu.pro` | `haiku {}` platform block |
| `src/qt5/keyboard_haiku.c` | Qt::Key → PS/2 Set 2 mapping (Haiku Qt returns 0 for nativeScanCode) |
| `src/qt5/main_window.cpp` | Use `event->key()` on Haiku; stop audio on close |
| `src/qt5/rpc-qt5.cpp` | Set data dir from `applicationDirPath()`; stop audio before exit |
| `src/qt5/plt_sound.cpp` | Clean `QAudioOutput` shutdown to prevent `BSoundPlayer` crash |
| `src/qt5/plt_sound.h` | Declare `plt_sound_stop()` with C linkage |

## Known issues

- Dynarec (recompiler) not tested — interpreter mode works
- TUN/TAP bridging and IP tunnelling not available (NAT only)
- Some keyboard shortcuts may not map correctly on non-US layouts
- Sound may produce a crash report on exit if closed mid-playback (harmless)

## Upstream

- [RPCEmu](https://www.marutan.net/rpcemu/) by Matthew Howkins and contributors
- [Cloverleaf fork](https://github.com/riscoscloverleaf/rpcemu) with clipboard and macOS support
- Licensed under GPL v2
