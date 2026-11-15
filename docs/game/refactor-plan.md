# Refactor plan: readable C, same bytes

Every function is matched in USA v1.01, PAL and USA v2.00. The next goal is C a person
(and the native port) can read: names, types and fields instead of addresses and offsets.
This plan follows rac1-decomp's camera pilot (`docs/game/camera.md` and
`docs/game/conventions.md` there): design first, pilot one system, then fan out.

## 1. The one rule

A refactor edit changes types, names and comments only. The bytes stay the same.

- After every edit: `python3 tools/build.py all --strict` prints `OK` for every program of
  every release. A local `tools/check.py` result is not enough.
- A rename-only or comment-only edit gets the build too: a changed declaration type or
  section can change code.
- AGENTS.md wins over this page: no new `__asm__`, `volatile`, register pins, aliases or
  other steering. A conversion that only keeps its bytes that way is not done.
- Retail data, disassembly and build output never land in git.

## 2. Phases

| Phase | What | Done when |
| --- | --- | --- |
| P0 Names | `include/names.h` macros for known functions; rename `r1_...` to their `D_`/`func_` address; readable names for globals (`g` + CamelCase) | names used in definitions and calls of the touched files |
| P1 Camera pilot | map camera symbols and users; write `include/structs/camera.h`; convert the three or four densest files | those files use fields, no raw camera offsets, build `OK` |
| P2 Camera readers | the other files that read the camera state; private views of the same memory | no private camera views left that convert byte-neutrally |
| P3+ Next systems | hero, mobys (with pvars), HUD, weapons/gadgets | same method, one system at a time |
| Later | file names by system instead of by address (`src/core/00115200.c`) | only through `tools/levels.py` and the build config; never a hand edit of a catalogue |

For each system: map the symbols and their users, write the header and the rules, convert the
densest files as a pilot, then fan out.

## 3. Camera pilot

Start points (camera code is mostly level code):

- `src/levels/shared/L00_004224D0-main-g8.c`
- `src/levels/shared/L00_004233F8-g8.c`
- `src/levels/shared/L00_002D7940-setup-g8.c`
- `src/levels/shared/L05_00428350-camera-g8.c`
- `src/levels/shared/L13_00438D88.c`

and their `src/pal/` and `src/us2/` copies. The pilot writes, in order:

1. A map: the camera state blocks, their symbols per level, the functions and callers.
2. `include/structs/camera.h`: the layouts (`unkXXX` for accessed but unknown fields,
   `padXXX` for gaps), sized and checked against the code.
3. Names for the camera functions and globals in `include/names.h`.
4. The conversions, one function or one file at a time, build after each.

## 4. Byte-neutral rules

From rac1's camera pilot, where each rule was measured by the build.

1. **Same access path.** A local pointer stays a local pointer; a direct global stays direct.
   `char *c = &blk; *(int *)(c + 0x398)` becomes `CameraSystem *c = &blk; c->frames`, not
   `blk.frames`.
2. **A sub-block reached through its own symbol or pointer keeps a pointer to it.** Writing it
   as a field of the parent shares the parent's base register and changes bytes. This rule
   cost bytes every time rac1 skipped it.
3. **Arithmetic that leaves a sub-block stays arithmetic**, with a comment naming the field it
   lands on.
4. **Cast the value, not the address:** `x = (s32)p->field`, never `*(s32 *)&p->field`.
5. **A declaration flip is per file.** `extern char D_x[];` and `extern Camera D_x;` cannot both
   be in one file: change every use in the same edit.
6. **Existing aliases may stay** when removing one changes bytes; say why in a comment. Never
   add a new one.
7. **Comments use field names.** Provenance notes stay word for word.

## 5. Three releases

USA v1.01 (`src/`), PAL (`src/pal/`) and USA v2.00 (`src/us2/`) have their own copies of many
functions. A refactor changes all copies of a function in the same change, and the build must
be `OK` for all three. The level-name rule stays: a level's own file uses only that level's
`D_LNN_` names (`tests/check_repository.py` checks it).

## 6. Naming

- Functions keep their catalogue symbol; readable names are `#define`s in `include/names.h`.
  New camera names: `Camera_<Verb><Object>`.
- Globals: `g` + CamelCase. Types: CamelCase (`Camera`, `CameraSystem`). Fields: `snake_case`.
- Locals by role (`cam` for a `Camera *`, `cs` for a `CameraSystem *`). A rename never changes a
  local's type, declaration order or scope.
- Rebase before a rename wave: names from other branches collide.

## 7. Who does what

As in AGENTS.md "Which model does what":

- Opus designs a system: the map, the header, the rules and a task list. The task list lives
  in `build/`, never in git.
- Haiku and Sonnet take one function or one file per run, with its checklist. rac1 measured
  that small workers stall on long chains where each edit depends on the last build: split
  those into separate runs.
- The design is most of the cost. With the header and rules written first, workers have
  little left to decide.

## 8. Tools

rac1's `tools/tidy/` (`conv.py`, `fake_bases.py`, `drop_aliases.py`, `fieldren.py`) shows the
kind of tool that helps. A new tool here goes in `tools/` with a test; ask a maintainer first
(AGENTS.md "If something seems to need a new mechanism").
