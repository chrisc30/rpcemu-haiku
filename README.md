# RPCEmu for Haiku

A port of [RPCEmu](https://www.marutan.net/rpcemu/) — the Acorn Risc PC and A7000 emulator — to the [Haiku operating system](https://www.haiku-os.org/).

Based on the [Cloverleaf fork](https://github.com/riscoscloverleaf/rpcemu) (v0.9.4) with additional patches for Haiku.

## Features

- Runs RISC OS 3.x and RISC OS 5 on Haiku (x86_64)
- Two build modes: **interpreter** (stable) and **recompiler/dynarec** (faster)
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
git clone https://github.com/chrisc30/rpcemu-haiku.git
cd rpcemu-haiku/src/qt5
```

**Interpreter** (stable, recommended):
```sh
/boot/system/bin/qmake rpcemu.pro
make -j$(nproc)
```

**Recompiler** (faster, experimental):
```sh
/boot/system/bin/qmake CONFIG+=dynarec rpcemu.pro
make -j$(nproc)
```

> **Note:** Run `make clean` between switching build types (interpreter ↔ recompiler), otherwise shared object files from the previous build may be reused incorrectly.

The binaries are placed in the repository root as `rpcemu-interpreter` or `rpcemu-recompiler`.

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
   or
   ```sh
   ./rpcemu-recompiler
   ```

The emulator must be run from its own directory so it can find `roms/`, `hostfs/`, `rpc.cfg` etc. When launched from Haiku's Tracker, a wrapper script is recommended:

```sh
#!/bin/sh
cd "$(dirname "$0")"
exec ./rpcemu-interpreter "$@"
```

## Networking

NAT networking is enabled by default. Set in `rpc.cfg`:

```ini
network_type=nat
```

Slirp assigns IP `10.10.10.10` to the emulated machine with gateway `10.10.10.2` and DNS at `10.10.10.3`. Configure these in RISC OS's `!Internet` settings or via DHCP.

## Haiku-specific patches

### Interpreter and recompiler

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
| `src/qt5/main_window.cpp` | Use `event->key()` on Haiku; stop audio on close; queued connection for mouse signal |
| `src/qt5/rpc-qt5.cpp` | Set data dir from `applicationDirPath()`; stop audio before exit; use `QMetaObject::invokeMethod` for video update; SIGSEGV handler for clean shutdown; disable mouse warp signal (cross-thread crash) |
| `src/qt5/plt_sound.cpp` | Clean `QAudioOutput` shutdown to prevent `BSoundPlayer` crash |
| `src/qt5/plt_sound.h` | Declare `plt_sound_stop()` with C linkage |
| `src/cp15.c` | Return NULL instead of `fatal()` for unknown PC addresses |

### Recompiler only

| File | Change |
|---|---|
| `src/codegen_amd64.c` | Allocate JIT code buffer via `mmap` near BSS (within 32-bit RIP-relative range) instead of static array — fixes PIE/ASLR crash on Haiku |
| `src/codegen_amd64.h` | Update `rcodeblock` declaration to pointer type |
| `src/ArmDynarec.c` | Add `__HAIKU__` to `set_memory_executable` mprotect guard |
| `src/arm.c` | Make `arm_unpredictable()` non-static for dynarec linkage |
| `src/arm.h` | Declare `arm_unpredictable()` extern |
| `src/arm_common.c` | Add `arm_unpredictable()` for dynarec build |

## Known issues

- The recompiler may produce a crash report on some shutdowns due to Haiku's `BSoundPlayer` lifecycle — this is cosmetic and can be dismissed
- Mouse warp (follows-host-mouse mode) is disabled in the recompiler due to a Qt cross-thread signal limitation on Haiku
- TUN/TAP bridging and IP tunnelling not available (NAT only)

## Upstream

- [RPCEmu](https://www.marutan.net/rpcemu/) by Matthew Howkins and contributors
- [Cloverleaf fork](https://github.com/riscoscloverleaf/rpcemu) with clipboard and macOS support
- Licensed under GPL v2
