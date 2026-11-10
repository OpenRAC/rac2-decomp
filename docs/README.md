# Docs

Every doc of this repository, by folder. New here? Read [building.md](build/building.md), then
[CONTRIBUTING.md](../CONTRIBUTING.md).

## build/: build and check the match

| Doc | What it covers |
|---|---|
| [building.md](build/building.md) | Setup, the SN tools, the build, the container, CI, the compilers |
| [versions.md](build/versions.md) | USA v1.01, PAL and USA v2.00: dumps, catalogues, builds and reports |
| [levels.md](build/levels.md) | The 27 level programs and the function catalogue |
| [compiler-notes.md](build/compiler-notes.md) | The compiler and what was measured of it |

## contributing/: write and review code

| Doc | What it covers |
|---|---|
| [matching-blockers.md](contributing/matching-blockers.md) | Shared matching blockers: what was tried and what is open |
| [permuter.md](contributing/permuter.md) | decomp-permuter for near misses |

## game/: how the game works

| Doc | What it covers |
|---|---|
| [engine-symbol-names.md](game/engine-symbol-names.md) | Engine symbol names from the August 8 prototype |
| [assert-message-names.md](game/assert-message-names.md) | Names from assert messages ([table](game/assert-message-names.tsv)) |
| [moby-dispatch-tables.md](game/moby-dispatch-tables.md) | Moby dispatch tables ([table](game/moby-dispatch.tsv)) |
| [vu-microprograms.md](game/vu-microprograms.md) | VU microprograms |
| [community-engine-reference.md](game/community-engine-reference.md) | Community research on the engine |

## research/: other builds and games

| Doc | What it covers |
|---|---|
| [prototype-builds.md](research/prototype-builds.md) | Public prototype builds |
| [aug6-retail-anchors.md](research/aug6-retail-anchors.md) | Code shared by the August preview and retail |
| [rac1-decomp-findings.md](research/rac1-decomp-findings.md) | Findings from rac1-decomp |
| [rac1-to-rac2.md](research/rac1-to-rac2.md) | What carries over from the first game |

## port/: the native port

| Doc | What it covers |
|---|---|
| [port-handoff.md](port/port-handoff.md) | Functional C, the behaviour gate, bugs traced here, what is open |

## agents/: AI agents

| Doc | What it covers |
|---|---|
| [agent-workflow.md](agents/agent-workflow.md) | Which model takes which function, and how a wave is spread |

## How it works

- `tools/levels.py dump` reads the boot executable and the 27 level programs from the disc.
- `config/boot/functions.tsv` and `config/levels/functions.tsv` list every function once,
  with its places ([docs/build/levels.md](build/levels.md)).
- `src/` lists every function once, in address order, as its C or as an `INCLUDE_ASM` marker,
  as rac1-decomp does.
- `tools/build.py all` disassembles each program, links the C in place of its assembly, and
  compares every loaded byte with the retail program ([docs/build/building.md](build/building.md)).

## Tools

| Tool | Purpose |
|---|---|
| `tools/levels.py` | The disc's programs and the catalogue of their functions |
| `tools/build.py` | The build: one `OK` per program, or the first byte that differs |
| `tools/check.py` | Compiles one function with its file's flags and diffs it against retail |
| `tools/todo.py` | Sorts the functions still to match into size tiers |
| `tools/progress.py` | The counts and `progress/report.json` |
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
