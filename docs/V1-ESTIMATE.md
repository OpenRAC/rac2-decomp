Heuristic decomp.dev report for the accepted USA v1.01 target. It adds no matching credit. Commands that mention `v2` setup need the experimental route in `V2-SETUP.md` (separate PR); everything here uses your v1.01 reference.

# Deduplicated v1.01 report, names and datamining

The accepted v1.01 target counts 48.8 MB of loaded code because the engine is repeated in each of the 27 overlays.
`scripts/unique_estimate.py` builds a separate decomp.dev report laid out like rac1-decomp's: categories *Executable*
(`core/<addr>` objects cut at the linker's `0xCDCDCDCD` fill, `game/<addr>`), *Level code* (*Shared level code* = a body present in two
or more overlays, *Level-specific code*) and one category per level ("Level 01: Oozla"). Each structural digest counts once.
The register-tracking mask is destructive: it erases all jump targets and `lui` immediates, as well as address-like immediates and member offsets.
For example, floating constants 1.0 and 2.0 loaded through `lui` can collapse to the same digest. Equal digests are naming/repetition hints,
not proof of identical behavior or relocation equivalence. This is neither the official physical total nor the official unique-code denominator.

The estimate provides **no matching credit**. It reads no candidate or integration proofs; neither kind can certify all bodies merged by this mask.
All objdiff matched/complete measures are zero to represent unavailable credit, including when reading an older catalogue with stale credit flags.
Zero here must not be interpreted as official progress or a loss of accepted C coverage. The committed catalogue retains only structural size estimates;
it has no current-progress claim. Regeneration checks the pinned boot and every overlay hash before recording their identities.
CI uploads it as `SCUS_972.68_unique_estimate`; the maintainer's `SCUS_972.68_report` is unchanged.

Keep your private runtime inside the repository in the git-ignored `extracted/` folder if you prefer
(`python scripts/setup.py --iso <iso> --runtime extracted/v101 --wrench <wrenchbuild>`); nothing under it is ever tracked.

```bash
R=$(echo extracted/v101/runs/*/reference)
python scripts/unique_estimate.py catalog --reference $R --elf $R/boot.elf   # commit config/estimates/ntsc-u.json
python scripts/unique_estimate.py report --output build/decomp/unique-estimate-report.json
```

Source files are not identified yet: units are named by start address (or `lib_<member>` for SDK library objects) until a real file name is known.
`scripts/map_segments.py --yaml <SCUS_972.68.yaml> --v1 <reference>/boot.elf` carries 53 of the 64 code boundaries of Promises' v2.00 split over to v1.01 by function digest (padding-aligned starts are snapped to the next function; 11 have no unique match or are data and are left out). Add `<address> <name>` rows to
`config/segments/ntsc-u-boot.tsv` to split or rename a boot unit once a boundary is proven. Existing splits to cross-check
(addresses and names only; Going Native is GPL-2.0, never copy its code): `going-decompiled/config/usa/SCUS_972.68.yaml` in
`Promises/RC2-Going-Decompiled` (USA v2.00 segments) and the engine file names in `OpenRAC/rac1-decomp` (`src/game/`) and `OpenRAC/rac3-uya-decomp`.

`scripts/name_units_from_rac1.py` (needs your own rac1 PAL boot `SCES_509.16` and rac1-decomp's `progress/report.json`) digests each rac1 source file's
functions and finds them in the v1.01 boot. Five units are named after a rac1 file (`drawquad`, `miscproc`, `pause`, `tfragproc`, `movie_readbuf`);
the 146 function-level matches of 35 rac1 files (for example 56 of 78 `fastfunc` functions) are kept in `config/segments/ntsc-u-rac1-matches.tsv`
as reference data for renaming further units. Most files match only partly, so a unit is named only when its first function and at least one more match in order.

**Names and file anchors for v1.01.** `scripts/transfer_names.py --v1 <reference>/boot.elf` carries the v2.00 function names (Promises) over by
unique digest match: 897 names are now in `symbol_addrs/usa/symbol_addrs.txt` below a generated marker, and the report shows them.
`scripts/ghidra_anchors.py` lists the functions that reference a source-file name string in the boot (`hud.cpp`, `loaders.cpp`, `map.cpp`,
`gui/behaviors.cpp`, `gui/memoryManagement.cpp`, `gui/mathUtil.cpp`; seven functions in `config/segments/ntsc-u-file-anchors.tsv`). It talks to a headless
Ghidra MCP container started on your own private project folder, for example:

```bash
podman run -d --name ghidra-rac2-v101 --security-opt label=disable -p 127.0.0.1:18089:8089 -p 127.0.0.1:18081:8081 \
  -v $PWD/extracted/ghidra:/projects -v "$R:/baserom:ro" -e PS2_BINARY=/baserom/boot.elf -e PROJECT_NAME=rac2 \
  -e GHIDRA_MCP_AUTH_TOKEN=rac2-local ghcr.io/lynder063/rac1-ghidra-ps2-mcp:latest      # image from rac1-decomp's container workflow
GHIDRA_MCP_AUTH_TOKEN=rac2-local python scripts/ghidra_anchors.py --url http://127.0.0.1:18089
```

**Datamining the boot.** `scripts/datamine.py --elf <reference>/boot.elf` writes identifier-only tables to `config/datamine/` (source-file strings with referencing functions,
message-spelled function names, identifier tables, SDK tags, section map); full strings stay in `extracted/datamine/`. `scripts/match_sdk_libs.py` matches boot
functions to your SDK mirror's library objects (196 matches, mostly `libkernl`, `libmpeg`, libc); `transfer_names.py` adds those names to the symbol file.

`match_sdk_libs.py` also writes `config/datamine/ntsc-u-sdk-objects.tsv` (17 SDK library objects located in the boot; they become `lib_<object>` units).
`name_overlay_functions.py --reference <reference>` finds no SDK or named function that exists only in an overlay; 66,248 overlay functions are copies of boot functions.
No newer Sony SDK mirror is public (ps2dev/ps2sdk is a different implementation), so remaining libraries need your own SDK 2.5-era libraries.

`scripts/ghidra_name_hints.py` scans the boot and all 27 overlays (loaded into the Ghidra project with `analyzeHeadless`, then `load_program_from_project` / `switch_program?program=`)
for class-like names in referenced strings: 608 hints, 46 of them function names a diagnostic spells out (`Camera_CollPrimTest` in 27 overlays, `NPC_showMessage`, `Path_setWtoDist`).
`name_overlay_functions.py` writes those to `config/datamine/ntsc-u-overlay-names.tsv`, which the report uses for level units.

**Data names.** `scripts/transfer_data_names.py` carries Promises' v2.00 global-variable names (`g_cameraState`, `g_boltCount`, ...) to v1.01. Functions that are identical
in both boots build their globals at the same instruction positions, so the paired addresses give an address map; a name moves only when all votes for its address agree
(521 names, vote count in each comment). Credit: Promises/RC2-Going-Decompiled; permission record: OpenRAC/rac2-gc-decomp PR #74.

**Compiler flags per unit.** `scripts/unit_flags.py --script <objdiff_build.sh> --v1 <reference>/boot.elf` maps the per-unit `-G` and `cc1` flags Promises measured on v2.00 to
v1.01 (`config/segments/ntsc-u-unit-flags.tsv`: 18 units, all `-G8`, most with `-fno-gcse`). Everything else is `-G0`. The SDK/engine compiler arm boundary is `0x131D98` in both builds
(below it 16-byte `sq` saves, from it 8-byte `sd` saves). Facts only; no code is copied (PR #74).
