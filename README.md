<p align="center">
  <img src="assets/rac2-logo.png" alt="RAC2 — Going Commando" width="560">
</p>
<p align="center"><strong>Ratchet &amp; Clank: Going Commando</strong></p>

<p align="center">
  <a href="https://openrac.dev"><img src="https://img.shields.io/badge/Website-openrac.dev-ff8a00?logo=googlechrome&logoColor=white" alt="OpenRAC website"></a>
  <a href="https://discord.gg/Sfd2B54PDG"><img src="https://img.shields.io/badge/Discord-Join%20Community-5865F2?logo=discord&logoColor=white" alt="OpenRAC Discord"></a>
  <a href="https://github.com/OpenRAC/rac2-gc-decomp/actions/workflows/progress.yml"><img src="https://github.com/OpenRAC/rac2-gc-decomp/actions/workflows/progress.yml/badge.svg" alt="Progress report"></a>
  <a href="https://bytematch.dev/OpenRAC/rac2-gc-decomp"><img src="https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Code&measure=matched_code_percent" alt="Code matched"></a>
  <a href="https://bytematch.dev/OpenRAC/rac2-gc-decomp"><img src="https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Functions&measure=matched_functions" alt="Functions matched"></a>
</p>

A work-in-progress **matching decompilation** of *Ratchet & Clank: Going Commando* (Insomniac
Games, 2003) for the PlayStation 2 (USA v1.01, `SCUS_972.68`), part of the
**[OpenRAC](https://openrac.dev)** initiative.

The disc's boot executable and its 27 level programs are rebuilt from C and assembly until
every loaded byte equals retail:

| Program | What it is | Code |
| --- | --- | ---: |
| `SCUS_972.68` | the boot executable: the engine core and the game | 1,046,952 bytes |
| `G/LEVELn.WAD` | the level programs, one per level, 27 of them | 4,482,204 bytes |

The objective is to produce C source code that, when compiled with the original toolchain,
generates a byte-identical copy of the retail programs. Matched code is then refactored
toward readable, idiomatic C with accurate types and naming, using matching builds as
continuous regression tests.

> [!NOTE]
> This repository contains **no game assets, retail executables, or disassembly**. To build,
> you must provide your own legally obtained copy of the game. Please review
> [`LEGAL.md`](LEGAL.md) before contributing.

---

## Progress

Decompilation progress is tracked live on **[openrac.dev](https://openrac.dev)** and
**[bytematch.dev/OpenRAC/rac2-gc-decomp](https://bytematch.dev/OpenRAC/rac2-gc-decomp)**.

| Version | Region | Target ID | Code Matched | Functions Matched |
|---|---|---|---|---|
| v1.01 | USA | `SCUS_972.68` | [![](https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Code&measure=matched_code_percent)](https://bytematch.dev/OpenRAC/rac2-gc-decomp) | [![](https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Functions&measure=matched_functions)](https://bytematch.dev/OpenRAC/rac2-gc-decomp) |
| v1.00 | Europe/Australia | `SCES_516.07` | [![](https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Code&measure=matched_code_percent&version=SCES_516.07)](https://bytematch.dev/OpenRAC/rac2-gc-decomp/SCES_516.07) | [![](https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Functions&measure=matched_functions&version=SCES_516.07)](https://bytematch.dev/OpenRAC/rac2-gc-decomp/SCES_516.07) |
| v2.00 (Greatest Hits) | USA | `SCUS_972.68_v2` | [![](https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Code&measure=matched_code_percent&version=SCUS_972.68_v2)](https://bytematch.dev/OpenRAC/rac2-gc-decomp/SCUS_972.68_v2) | [![](https://bytematch.dev/OpenRAC/rac2-gc-decomp.svg?mode=shield&label=Functions&measure=matched_functions&version=SCUS_972.68_v2)](https://bytematch.dev/OpenRAC/rac2-gc-decomp/SCUS_972.68_v2) |

<!-- progress -->
| | Functions | Code |
| --- | ---: | ---: |
| Boot executable | 2,417 of 3,132 | 518,316 of 1,044,872 bytes |
| Levels | 3,206 of 5,452 | 1,970,604 of 4,481,044 bytes |
| **Total** | 5,623 of 8,584 | 2,488,920 of 5,525,916 bytes (45.04%) |

The 27 levels hold 101,064 function placements; C covers 66,099 of them.
334 of the matched functions are the original's own assembly (`ASM_FUNC`), kept as assembly.
<!-- /progress -->

Every distinct function counts once: the boot executable's functions and the level functions
that the boot does not also have. A function many levels share is one function, however many
places it has. A function is C when its C links into a program that comes out equal to the
retail one ([`progress/report.json`](progress/report.json), `tools/progress.py`). The table is
v1.01's; the PAL and v2.00 releases are built and counted the same way from the same C
([docs/VERSIONS.md](docs/VERSIONS.md)).

The report also gives the boot executable's data (383,391 bytes of initialised data, for the
Data bar on [ByteMatch](https://bytematch.dev)). None of it is matched yet: the build places C
functions' code and discards their objects' data, so all of it still comes from retail's dumps.
The levels' data is not measured.

Every function links at its original retail address. Functions not yet decompiled are built
from disassembly, so a program links and matches retail byte for byte until a C function
differs; the build then stops at that byte and says which function it was.

### What counts as a match

Only `tools/build.py` saying `OK` counts: the C has to link into a program that comes out
equal to the retail one. A compiled object, a few matching instructions or a masked
comparison do not. A near miss belongs in [`nonmatching/`](nonmatching), never in `src/`.

---

## Quick Start

### Prerequisites

- **The disc**: your own copy of *Ratchet & Clank: Going Commando*, USA v1.01, as
  `baserom/SCUS_972.68.iso` (SHA-256
  `9db2e33e276133cc283647fa3279b37911955e123d6199d10065547eaa9b1ce5`).
- **Python 3.12** with the pinned tools: `pip install -r requirements.txt` (splat, spimdisasm,
  rabbitizer).
- **SN ProDG 2.0**'s assembler and linker, as
  `toolchain/sn-prodg-2.0/ee/bin/{Ps2EeAs,ld}.exe`. Proprietary: bring your own, never commit
  them.
- **A 32-bit capable Linux** (`gcc -m32`) and **Wine** for the SN tools, or the container
  image that has both (`tools/docker/run.sh`).

### Setup & Build

1. **Clone the repository:**
   ```sh
   git clone https://github.com/OpenRAC/rac2-gc-decomp.git
   cd rac2-gc-decomp
   ```

2. **Provide your own disc:**
   ```sh
   cp /path/to/SCUS_972.68.iso baserom/SCUS_972.68.iso
   # sha256sum baserom/SCUS_972.68.iso
   # 9db2e33e276133cc283647fa3279b37911955e123d6199d10065547eaa9b1ce5
   ```

3. **Install the dependencies and build the compilers:**
   ```sh
   python3 -m pip install -r requirements.txt
   tools/compiler/build.sh               # the game's compiler, into build/compiler/tools/
   python3 tools/compiler/sdk/build.py   # the SDK units' compiler, into build/compiler/sdk/
   ```

4. **Dump the disc, build and report:**
   ```sh
   python3 tools/levels.py dump          # the boot executable and the 27 level programs
   python3 tools/build.py all            # one "OK" per program, or the first byte that differs
   python3 tools/progress.py             # progress/report.json and the table above
   ```

`tools/build.py boot`, `tools/build.py level 04` and `tools/build.py levels` build a part of
it. `tools/check.py func_XXXXXXXX --diff` compiles one function with its file's flags and
shows its instructions beside the retail ones, in seconds.

On macOS, on Windows or on any other host, run the same commands in the build image
(32-bit Debian with Wine, Python and the build tools):

```sh
bash tools/docker/run.sh python3 tools/levels.py dump
bash tools/docker/run.sh python3 tools/build.py all
```

For the details:

- [`docs/BUILDING.md`](docs/BUILDING.md) – the build, the toolchain, the container, CI
- [`docs/LEVELS.md`](docs/LEVELS.md) – the 27 level programs and the function catalogue
- [`docs/COMPILER-NOTES.md`](docs/COMPILER-NOTES.md) – the compiler and what was measured of it
- [`docs/PERMUTER.md`](docs/PERMUTER.md) – decomp-permuter for near misses, through OpenRAC's shared tool
- [`docs/VERSIONS.md`](docs/VERSIONS.md) – the three releases (v1.01, PAL, v2.00): their dumps, catalogues, builds and reports

---

## How it works

- `tools/levels.py dump` reads the boot executable and the 27 level programs from the disc.
- `config/boot/functions.tsv` and `config/levels/functions.tsv` list every function once,
  with its places ([docs/LEVELS.md](docs/LEVELS.md)).
- `src/` lists every function once, in address order, as its C or as an `INCLUDE_ASM` marker,
  as rac1-decomp does.
- `tools/build.py all` disassembles each program, links the C in place of its assembly, and
  compares every loaded byte with the retail program ([docs/BUILDING.md](docs/BUILDING.md)).

## Tools

| Tool | Purpose |
|---|---|
| `tools/levels.py` | The disc's programs and the catalogue of their functions |
| `tools/build.py` | The build: one `OK` per program, or the first byte that differs |
| `tools/check.py` | Compiles one function with its file's flags and diffs it against retail |
| `tools/todo.py` | Sorts the functions still to match into size tiers |
| `tools/progress.py` | The counts, the README table and `progress/report.json` |
| `tools/expand_asm.py` | Adapts splat's assembly to SN ProDG's assembler |
| `tools/elf.py` | The ELF32 reading and writing the build needs |
| `tools/compiler/` | The game's compiler, rebuilt from public source, with its patches |
| `tools/docker/run.sh` | Runs a command in the `rac2-build` image (32-bit Linux, Wine, Python) |
| `tests/check_repository.py` | The pre-commit check: catalogues, sources, no game data (CI runs it) |

## Layout

| Path | What |
| --- | --- |
| `src/core/` | the boot's core code (SDK, libc), one file per original object |
| `src/game/` | the boot's own program |
| `src/levels/shared/`, `src/levels/NN_name/` | level functions in several levels, and in one |
| `nonmatching/` | near misses, never linked |
| `config/` | the function catalogues, per-file compiler flags, naming research |
| `tools/` | disc reader and catalogue, build, progress, the compiler recipes |
| `include/` | shared headers |
| `ports/pal-functional/` | functional C for the PAL release (not matching) |
| `docs/` | building, the level format, the compiler, game research |

## Contributing

Contributions are warmly welcome! Whether you are interested in decompiling functions,
researching engine quirks, or improving documentation:

- Read [`AGENTS.md`](AGENTS.md) and [`CONTRIBUTING.md`](CONTRIBUTING.md) first; they hold the
  rules.
- [`docs/AGENT_WORKFLOW.md`](docs/AGENT_WORKFLOW.md) says which tier of model takes which
  function, and how a wave is spread over the workers.
- `python3 tools/todo.py` sorts the functions still to match into buckets, and
  `tools/check.py func_XXXXXXXX --diff` shows a draft beside retail in seconds.
- Everyone can improve the [shared matching blockers](docs/MATCHING-BLOCKERS.md) through a
  pull request, with discussion in the relevant PR. Coordinate scopes in
  [issue #152](https://github.com/OpenRAC/rac2-gc-decomp/issues/152).
- Join our **[Discord Community](https://discord.gg/Sfd2B54PDG)** to discuss progress, ask
  questions, and collaborate!

## Credits

- [`CREDITS.md`](CREDITS.md) is the record of every outside project and person this
  repository uses, and of what was taken from each.
- **[rac1-decomp](https://github.com/OpenRAC/rac1-decomp)** – the first game's matching
  decompilation: the layout of `src/`, the units and the categories of the report follow it.
- **[rac3-decomp](https://github.com/OpenRAC/rac3-decomp)** (PAL *Up Your Arsenal*),
  **[rac3-uya-decomp](https://github.com/OpenRAC/rac3-uya-decomp)** (NTSC) and
  **[rac5-sm-decomp](https://github.com/OpenRAC/rac5-sm-decomp)** (*Size Matters*) – the other
  OpenRAC decompilations, with the same tools and the same rules.
- **[OpenRAC](https://github.com/OpenRAC/OpenRAC)** – the native PC port of the first game:
  the reference for the engine this game shares, and for what this work is for.
- **[Lombyte](https://github.com/lombyte-project/Lombyte)** by mateuszklysz – the NTSC
  decompilation of the first game: its compiler patch stack and the SDK compiler recipe come
  from it.
- **[Promises/RC2-Going-Decompiled](https://github.com/Promises/RC2-Going-Decompiled)** – the
  other *Going Commando* decompilation: symbol maps and names, as leads.
- **[splat](https://github.com/ethteck/splat)**,
  **[spimdisasm](https://github.com/Decompollaborate/spimdisasm)** and
  **[rabbitizer](https://github.com/Decompollaborate/rabbitizer)** – the disassembler and the
  instruction decoder.
- **[objdiff](https://github.com/encounter/objdiff)** – the report format, and
  **[ByteMatch](https://bytematch.dev)** – the progress dashboard.

## Licence

- Code written for this project is licensed under the
  [GNU General Public License v3.0](LICENSE).
- Reconstructed libraries and third-party components retain their original licenses (see
  [`THIRD_PARTY_NOTICES.md`](THIRD_PARTY_NOTICES.md) and [`LEGAL.md`](LEGAL.md)).
- The decompiled game code in `src/` is a derivative of the original game (copyright Sony
  Interactive Entertainment LLC): no copyright is claimed over it and it is not licensed.
- *Ratchet & Clank* is a registered trademark of Sony Interactive Entertainment. This project
  is not affiliated with or endorsed by Sony or Insomniac Games.
