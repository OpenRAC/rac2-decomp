<p align="center">
  <a href="https://openrac.dev/">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="docs/assets/openrac-logo-dark.svg">
      <img src="docs/assets/openrac-logo-light.svg" alt="OpenRAC" width="360">
    </picture>
  </a>
</p>

<h3 align="center">Ratchet &amp; Clank: Going Commando decompilation project</h3>

<p align="center">
  <a href="https://bytematch.dev/OpenRAC/rac2-decomp"><img src="https://bytematch.dev/OpenRAC/rac2-decomp.svg?mode=shield&label=Code&measure=matched_code_percent" alt="Code matched"></a>
  <a href="https://github.com/OpenRAC/rac2-decomp/actions/workflows/progress.yml"><img src="https://github.com/OpenRAC/rac2-decomp/actions/workflows/progress.yml/badge.svg" alt="Progress report"></a>
  <a href="https://openrac.dev/"><img src="https://img.shields.io/badge/website-openrac.dev-e8a317" alt="openrac.dev"></a>
  <a href="https://discord.gg/Sfd2B54PDG"><img src="https://img.shields.io/badge/Discord-join%20us-5865F2?logo=discord&logoColor=white" alt="Discord"></a>
</p>

<p align="center">
  A work-in-progress, matching decompilation of <i>Ratchet &amp; Clank: Going Commando</i> (2003) for PlayStation 2.<br>
  The boot executable and its 27 level programs, rebuilt as C that compiles back to the same bytes as retail.
</p>

> [!WARNING]
> This repository has no game data, executables, disc images or proprietary toolchains.
> You need your own copy of the game. Read [LEGAL.md](LEGAL.md) before contributing.

## Progress

USA v1.01, counted by `tools/progress.py` (each function once, however many levels share it).
Live numbers for every release are on [ByteMatch](https://bytematch.dev/OpenRAC/rac2-decomp).

<!-- progress -->
| | Functions | Code |
| --- | ---: | ---: |
| Boot executable | 3,060 of 3,078 | 1,005,500 of 1,041,544 bytes |
| Levels | 5,431 of 5,449 | 4,453,760 of 4,482,516 bytes |
| **Total** | 8,491 of 8,527 | 5,459,260 of 5,524,060 bytes (98.83%) |

The 27 levels hold 100,562 function placements; C covers 94,363 of them.
449 of the matched functions are the original's own assembly (`ASM_FUNC`), kept as assembly.
<!-- /progress -->

## Supported versions

| Release | Region | Boot executable | Notes |
| --- | --- | --- | --- |
| v1.01 | USA | `SCUS_972.68` | Primary version |
| v1.00 | Europe/Australia | `SCES_516.07` | |
| v2.00 (Greatest Hits) | USA | `SCUS_972.68` | Report id `SCUS_972.68_v2` |

All releases share one C source. Expected SHA-256 of the primary disc image:

```text
9db2e33e276133cc283647fa3279b37911955e123d6199d10065547eaa9b1ce5
```

The other hashes and how the releases fit together: [docs/build/versions.md](docs/build/versions.md).

## Quick setup

You need x86-64 Linux with 32-bit support (`gcc -m32`), Wine and Python 3.12, or the build container.
SN ProDG's assembler and linker go in `toolchain/` first: [docs/build/building.md](docs/build/building.md#get-the-sn-tools).

```sh
git clone https://github.com/OpenRAC/rac2-decomp.git && cd rac2-decomp
python3 -m pip install -r requirements.txt
cp /path/to/your-disc.iso baserom/SCUS_972.68.iso
tools/compiler/build.sh
python3 tools/compiler/sdk/build.py
python3 tools/levels.py dump
python3 tools/build.py all        # one "OK" per program
```

macOS, Windows, the container and the other releases: [docs/build/building.md](docs/build/building.md).

## Contributing

Start with [CONTRIBUTING.md](CONTRIBUTING.md) and [AGENTS.md](AGENTS.md). Reserve your functions in
[issue #152](https://github.com/OpenRAC/rac2-decomp/issues/152) first. All docs are listed in [docs/README.md](docs/README.md):

- [docs/build/](docs/build) - building, versions, levels and the compiler
- [docs/contributing/](docs/contributing) - matching blockers and the permuter
- [docs/game/](docs/game) - how the game works: symbols, moby dispatch, VU microprograms
- [docs/research/](docs/research) - prototype builds and what carries over from the first game
- [docs/port/](docs/port) - where this repository meets the native port
- [docs/agents/](docs/agents) - instructions for AI agents

Keep the build matching retail. Never commit game images, extracted game data or proprietary tool binaries.

## Credits

Every outside project and person this repository uses is listed in [CREDITS.md](CREDITS.md). The main ones:

- [rac1-decomp](https://github.com/OpenRAC/rac1-decomp) - layout of `src/`, units and report categories.
- [rac3-decomp](https://github.com/OpenRAC/rac3-decomp), [rac3-uya-decomp](https://github.com/OpenRAC/rac3-uya-decomp)
  and [rac5-sm-decomp](https://github.com/OpenRAC/rac5-sm-decomp) - the other OpenRAC decompilations.
- [OpenRAC](https://github.com/OpenRAC/OpenRAC) - the native port, and the reference for the shared engine.
- [Lombyte](https://github.com/lombyte-project/Lombyte) - compiler patch stack and the SDK compiler recipe.
- [Promises/RC2-Going-Decompiled](https://github.com/Promises/RC2-Going-Decompiled) - symbol maps and names, as leads.
- [splat](https://github.com/ethteck/splat), [spimdisasm](https://github.com/Decompollaborate/spimdisasm),
  [rabbitizer](https://github.com/Decompollaborate/rabbitizer), [objdiff](https://github.com/encounter/objdiff)
  and [ByteMatch](https://bytematch.dev).

## License

Code written for this project is under the [GNU General Public License v3.0](LICENSE). Code reconstructed from
third-party binaries belongs to its copyright holders; see [THIRD_PARTY_NOTICES.md](THIRD_PARTY_NOTICES.md).
