# Names

Carried from rac1-decomp's `docs/contributing/names.md`; the same scheme, without RAC1's
import sources.

Every symbol keeps its address name: `func_<ADDR>` in the boot, `func_LNN_<ADDR>` in level
code, `D_<ADDR>` / `D_LNN_<ADDR>` for data. The build and every tool read the address (and
level) out of that name, so it is the linker symbol, what `INCLUDE_ASM`/`ASM_FUNC` name and
what the catalogues list.

Readable names sit on top, as macros:

| File | What it is |
|---|---|
| `config/names.tsv` | the table: one row per named symbol, its name, tier, source, evidence and alternatives |
| `config/names_local.tsv` | names this project gives from reading the code (`symbol`, `name`, `evidence`, optional `override`) |
| `include/names.h`, `include/names/*.h` | generated from the table, one part per level plus `executable.h` and `shared_levels.h`: `#define yeti_update func_L19_0041B078`; included by `common.h` |
| `tools/names.py` | `local` (names_local.tsv into the table), `header` (table to names.h), `apply-defs` (definitions use the names), `apply` (bodies, `extern` lines and prototypes use them), `check`, `rename`, and lookup: `python3 tools/names.py func_L19_0041B078` or `... yeti_update` |
| `tools/srcnames.py` | source text with readable names turned back into address names, for tools that find definitions by address |

C writes the readable name in function definitions, inside function bodies, on `extern`
lines and in prototypes. `INCLUDE_ASM`/`ASM_FUNC` lines, preprocessor lines, `__asm__` labels
and `SDATA()` arguments (stringified into the label) keep the address name. The preprocessor
turns one into the other, so the objects are byte for byte the same either way. Comments use
the readable name too.

A name that is already an identifier in `src/`, `include/` or `nonmatching/` (a library
function C calls by its own name, a struct field, a local) is left out of `names.h`, so no
macro silently renames anything; `tools/names.py header` lists what it left out.

## Tiers

| Tier | In names.h | Meaning |
|---|---|---|
| recovered | yes | an original identifier (research documents, the 8 August 2003 prototype's symbols); never respelled |
| descriptive | yes | a later name with evidence: a RAC1 counterpart's name, or one this project gives from reading the code |
| candidate | no | weaker; for workers only |

A name is given to one symbol only. `config/names_local.tsv` fills a symbol with no name or
only a candidate; `override` replaces a wrong recovered or descriptive name, which goes to the
alternatives.

## Adding or changing names

```sh
$EDITOR config/names_local.tsv      # a row: symbol, name, evidence
python3 tools/names.py local        # merge it into config/names.tsv
python3 tools/names.py rename       # names.h, then definitions and uses in src/
python3 tools/names.py check
```

`rename` turns every use of a name names.h no longer gives that symbol back into the address
name in code (the new spelling in comments), then runs `header`, `apply-defs` and `apply`.
Then rebuild (`tools/build.py all --strict`, and `--version pal`/`us2`, whose sources use the
same header) and check that nothing but source text changed.

## Spelling

[style.md](style.md): functions `snake_case`, system first (`yeti_update`,
`hero_set_move_state`); a level's own copy of a routine other levels also have puts the level
after the system (`hero_l04_update_state_machine`); globals `g_` + `snake_case`. Library and
SDK routines keep their own spelling (`memchr`, `sceSifSendCmd`). Recovered names keep theirs.
Names express observed behaviour unless their tier is recovered.

A release's own symbols (`func_PAL_...`, `func_US2_...`, `D_PAL_...`, `D_US2_...`; see
[../build/versions.md](../build/versions.md)) are named in the same table and go in
`include/names/pal.h` and `us2.h`. A release's version of a USA v1.01 function takes the
v1.01 name plus `_pal` or `_us2` (`hit_trigger_update_pal`); the counterpart comes from
`build/<version>/carry.json` (changed code at the same place) or an identical fingerprint.
Data names in release C state v1.01 addresses, so v1.01's global names apply there unchanged.
