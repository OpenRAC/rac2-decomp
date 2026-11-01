# The three releases

One repository, one C source, three discs. USA v1.01 stays the primary target: the C in `src/`
was matched against it, and its paths, build and report are the ones this repository always
had. The other two are built and counted the same way from the same C.

| Version (`--version`) | Release | Serial (boot) | Disc image SHA-256 | ByteMatch version |
| --- | --- | --- | --- | --- |
| `us` (default) | USA v1.01 | `SCUS_972.68` | `9db2e33e276133cc283647fa3279b37911955e123d6199d10065547eaa9b1ce5` | `SCUS_972.68` |
| `pal` | Europe/Australia v1.00 | `SCES_516.07` | `519f9fa78b8e821b6bb7fa501fc10e8b10f378e27a6410f68d0dd8952860b41a` | `SCES_516.07` |
| `us2` | USA v2.00 (Greatest Hits) | `SCUS_972.68` | `eda31b4519d16014164090e8a36733af63ef8e458a96d37d6054b65c00ec6e72` | `SCUS_972.68_v2` |

Put the discs in `baserom/` as `SCUS_972.68.iso`, `SCES_516.07.iso` and
`SCUS_972.68_v2.00.iso`. Both US releases carry the serial `SCUS_972.68`, so v2.00's version
id is `SCUS_972.68_v2`: ByteMatch's artifact pattern `^(?<version>.+)_report$` reads
`SCUS_972.68_v2_report` as that version and `SCUS_972.68_report` as v1.01.

Every tool takes `--version us|pal|us2` (or `$RAC2_VERSION`):

| | v1.01 | PAL, v2.00 |
| --- | --- | --- |
| dumps | `baserom/SCUS_972.68`, `baserom/levels/` | `baserom/<version>/` |
| catalogues | `config/boot/`, `config/levels/` | `config/<version>/boot/`, `config/<version>/levels/` |
| the release's own C | `src/` | `src/<version>/` (functions named `func_PAL_...`, `func_US2_...`) |
| build | `build/<program>/` | `build/<version>/<program>/` |
| report | `progress/report.json` | `progress/<version>/report.json` |

## Dumps

    python3 tools/levels.py dump                   # and --version pal, --version us2

Each release has the same layout: the boot executable in the ISO's root and 27 level programs
in `G/LEVELn.WAD` (docs/LEVELS.md). `dump` writes them, checks that every level's dump
converts back to the bytes the disc stores (its section records and sections, a `.bss` as
zeros), and records every program's SHA-1, size and entry point in `config/programs.tsv`;
`tools/levels.py check` compares the dumps with it, without the disc.

| | v1.01 | PAL | v2.00 |
| --- | --- | --- | --- |
| boot entry, `$gp` | `0x131AE8`, `0x1AEFF0` | `0x131B48`, `0x1AF070` | `0x131AE8`, `0x1AEFF0` |
| a level's program from | `0x1A7C80` | `0x1A7D00` | `0x1A7C80` |
| boot `core.text` / `.text` | `0x1E950` / `0xE35C0` | `0x1E9B0` / `0xE5A28` | `0x1E950` / `0xE4308` |
| level 00's `.text` | `0x2A3B80` +`0x1A3D80` | `0x2A3980` +`0x1A99F8` | `0x2A3B80` +`0x1A51B0` |

**How v2.00 differs from v1.01.** It is not a re-press: no program of the disc equals
v1.01's. The boot is 2,572 bytes longer (`.text` +3,400 bytes, `core.lit` +8 and `.lit` -96 bytes, `.bss`
and `.data` 0x80 lower, `legal.data` and `mc1.data` other bytes) and every level
program is about 5 KB longer. In code, 2,604 of v2.00's 3,145 boot functions and 6,589 of its
7,506 distinct level functions are v1.01's code; the rest changed (fixes; field offsets of
the game's large structures moved, as the not-carried list shows). The PAL release changes
more: 50 Hz timing (30 frames become 25, 60 become 50, `60.0f` becomes `50.0f`), localised
text ids, and larger structures.

## Building every release from assembly

    python3 tools/build.py all --version pal       # and --version us2; v1.01 as before

The build is v1.01's: splat disassembles the release's program, SN's assembler and linker
rebuild it, the C takes the place of its functions and every loaded byte is compared. All 28
programs of each release come out equal: from assembly alone, and with every C function the
release's catalogues place (`--strict` passes on each). Names in C state v1.01's addresses,
so in another release every symbol's value is read from that release's bytes (the build
checks that each has one value per program).

## Catalogues: carried by identical code

    python3 tools/carry.py --version pal           # and --version us2

`tools/carry.py` compares every program of the release with v1.01's, one code section at a
time, and cuts the release's code where v1.01's catalogue cuts it:

1. **The same code.** Each v1.01 function is looked for where the previous one found
   predicts, else among the places that start with the same four words. It is found where
   the words are equal with only what the linker fills in masked (`levels.cross_identity()`:
   jump targets, address halves, `$gp` offsets; constants, stack slots and field offsets are
   compared), at the same size, and it calls the same functions (each `jal` reaches the
   release's place of the same callee). It keeps its cut and its v1.01 name.
2. **Changed code.** Between two such functions, a stretch as long as v1.01's takes v1.01's
   cuts at the same offsets (a constant changed). Another stretch is cut where functions
   start: its first word, `jal` targets, the first non-zero word after a return.
3. **One function.** A branch never leaves its function: extents one branches into are
   joined, unless both are v1.01's same code and v1.01 branches the same way.
4. **What the build disproves.** Some functions equal v1.01's with every address masked and
   still differ, because an offset inside an address moved (a field of a large global, the
   accessors of `src/game/0029BCC8.c`, `func_L00_0030D*`). `tools/carry.py --demote` reads the
   release's last build and lists them in `config/<version>/not_carried.tsv`: they and
   their callers are the release's own functions. The demotion does not realign the release
   again: the measured functions and the carried callers of them take the release's names
   (`func_<TAG>_XXXXXXXX`, `func_<TAG>_LNN_XXXXXXXX`) and get INCLUDE_ASM markers in
   `src/<version>/`, and every other row of the release's catalogues keeps its name, its
   address and its places. A caller the release already owns keeps its name. The demotion
   needs the release's dumps (for the calls) and the build's `placed.json` (for the
   measurements).

Then the catalogue rules of `tools/levels.py` apply unchanged: the linker's filler and an
epilogue's residue are not functions, and identical code is one function, counted once (the
k-th copy in each level being one), whatever the number of levels that have it.

Functions with no v1.01 code are named for the release (`func_PAL_XXXXXXXX` in the boot,
`func_PAL_LNN_XXXXXXXX` in the levels, the address the release's; `func_US2_` likewise) and
have `INCLUDE_ASM` markers in `src/<version>/`, laid out as `src/` is (`core/`, `game/`,
`levels/shared/`, `levels/NN_name/`). Their C goes there, with per-file flags in
`config/cflags.txt` like every other file.

## One C, kept in step

A function every release has under one name is the same code, and has one definition, in
`src/`: a match made against any release is linked into all of them by the next build.
Version-specific C exists only where the bytes differ. The checks hold this:

- `tests/check_repository.py`: a release's own functions are defined in its `src/<version>/`
  only, nothing there redefines a v1.01 function, every catalogued function of every release
  appears exactly once.
- `tools/progress.py --check` (CI, every release, no disc needed): besides the report being
  current, the three reports must agree: a function two releases share is matched in both
  or in neither. A C change that matches one release and not another (an address written as
  a number, a struct offset that moved) fails it until the C is fixed or `--demote` records
  the difference.

Before pushing a change to C, check it on every release that has it:

    python3 tools/check.py func_XXXXXXXX            # v1.01
    python3 tools/check.py func_XXXXXXXX --version pal
    python3 tools/check.py func_XXXXXXXX --version us2

After merging, a maintainer regenerates the three reports together (they must agree):

    python3 tools/build.py all --strict
    python3 tools/build.py all --strict --version pal
    python3 tools/build.py all --strict --version us2
    python3 tools/carry.py --version pal --demote   # only if a build left C out; then rebuild that release
    python3 tools/carry.py --version us2 --demote
    python3 tools/progress.py && python3 tools/progress.py --version pal && python3 tools/progress.py --version us2
    python3 tools/progress.py --check

## Totals, old and new

The original multi-release inventory recorded **8,601 functions, 5,529,156 bytes**
for v1.01 (3,134 boot functions, 5,467 level functions the boot does not have).
The following inventory is that historical snapshot. Later entry corrections
preserve all loaded bytes while changing the code counted by the catalogues;
the generated coverage table below uses the current totals.

| | v1.01 | PAL | v2.00 |
| --- | ---: | ---: | ---: |
| boot functions (bytes) | 3,134 (1,046,952) | 3,138 (1,056,500) | 3,145 (1,050,472) |
| ... of them v1.01's same code | - | 2,274 | 2,604 |
| distinct level functions | 7,483 | 7,571 | 7,506 |
| ... the boot's too (counted with it) | 2,016 | 2,016 | 1,996 |
| ... shared by several levels / in one | 3,000 / 2,467 | 3,043 / 2,512 | 3,038 / 2,472 |
| level code counted (bytes) | 5,467 (4,482,204) | 5,555 (4,650,756) | 5,510 (4,532,644) |
| **total** | **8,601 (5,529,156)** | **8,693 (5,707,256)** | **8,655 (5,583,116)** |
| level placements | 101,292 | 101,843 | 101,807 |
| functions of the release's own (markers in `src/<version>/`) | - | 3,575 | 1,101 |
| v1.01 functions not carried (`not_carried.tsv`) | - | 98 | 58 |

Current matched coverage (the three reports from validated builds):

| Version | Release | Functions | Boot code | Level code | Total code |
| --- | --- | ---: | ---: | ---: | ---: |
| `SCUS_972.68` | USA v1.01 | 7,760 of 8,579 | 868,332 of 1,044,736 | 3,815,940 of 4,483,200 | 4,684,272 of 5,527,936 (84.74%) |
| `SCES_516.07` | Europe/Australia v1.00 | 6,996 of 8,672 | 727,328 of 1,054,716 | 2,361,316 of 4,648,968 | 3,088,644 of 5,703,684 (54.15%) |
| `SCUS_972.68_v2` | USA v2.00 (Greatest Hits) | 7,595 of 8,634 | 817,024 of 1,048,320 | 3,703,080 of 4,531,436 | 4,520,104 of 5,579,756 (81.01%) |

`tools/progress.py --version us|pal|us2` maintains the corresponding coverage row.
In the original layout sample, 1,036 of v1.01's then-matched functions differed in
PAL, and 508 in v2.00 (50 Hz constants, moved fields and their callers). Those are
historical sample counts, not the current difference between the totals above.
Such functions need C of their own in `src/<version>/`, often v1.01's C with the
release's constants. Exact and fuzzy are kept apart in every report; until near misses
carry a measured closeness, each report's fuzzy figure equals its exact one.
