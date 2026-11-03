# Handoff: rac2-decomp and the native port (2026-11-03)

This is for an agent or contributor picking up work where this repository meets OpenRAC's
native port of Going Commando (NTSC-U, SCUS_972.68). It covers four things:

- how the two repositories connect;
- what state the work is in;
- the bugs found in two days of player testing, and which of them traced back to this repository;
- the methods and lessons that saved time.

Matching itself is covered by [AGENT_WORKFLOW.md](AGENT_WORKFLOW.md) and
[COMPILER-NOTES.md](COMPILER-NOTES.md). This document is about **behaviour**: C that has to do
what the retail code does when the port runs it.

## How this repository feeds the port

- **The pin.** OpenRAC's `games/rac2/game.json` pins a commit of this repository and a branch.
  The port is generated from `src/` at that commit by OpenRAC's `port/tools/hostgen`.
  - Matched C is used as it is.
  - Functions still in `INCLUDE_ASM` are translated from assembly, unless a functional row
    replaces them (next item).
- **Functional C.** `nonmatching/functional.tsv` lists C written for the port only. Each row
  does what a still-assembly function does without matching its bytes. See
  `nonmatching/README.md` and OpenRAC's `docs/port/BACKFILL.md`.
  - The matching build never reads these files.
  - `tests/check_repository.py` checks that each listed function is still `INCLUDE_ASM` in `src/`.
  - When a row's function gets matched, the matched C wins and the row must go.
- **Two tables on OpenRAC's side, regenerated at each repin:**
  - `call_copies` / `data_copies` / `level_twins` (`copycalls.py --twins`): how a level's
    copy of a boot routine maps to its own callees and globals.
  - `docs/SOURCES.md` (`tools/openrac.py tables`).
  - A catalogue entry correction here (a function that starts later, a size change) changes
    those tables. Mention it in your PR.
- **Host functions.** OpenRAC's `port/game/rac2-ntsc/libraries.tsv` lists functions the port
  replaces with host code: the 989snd sound RPCs, the kernel, the SIF and the card.
  - A busy-wait on an IOP reply in decompiled code hangs the port unless its RPC is hosted.
    See "Maktar arena freeze" below.
- **`ps2_float`.** OpenRAC's `port/game/rac2-ntsc/hostgen.json` lists functions that must
  compute in EE single-precision rules: no NaN where the EE gives 0, the same rounding, and the
  EE's `sqrt.s`. Collision, steering and camera code drifts from retail without it.

## State at this handoff

- **master** `93f76357e` merges #393 (functional C round 2). OpenRAC #212 pins `2990ba7e1`,
  branch `port/backfill-2`.
- **Reports at #393:**

  | Release | Functions in C |
  |---|---|
  | US | 7,793 of 8,580 |
  | PAL | 7,006 of 8,672 |
  | US2 | 7,612 of 8,634 |

  `tools/progress.py --check` passes: the three reports agree on every function they share.
- **472 functional rows.** Each was re-checked with the corrected gate (below). Two real slips
  turned up and are fixed:
  - `func_003486A8`: read a chain of `func_00335E20` results one element late, so the pause
    menu's bars drew in the highlight colour (the "whited-out pause menu").
  - `func_003489E8`: called `func_00335F88` with fewer float arguments than it takes, so the
    callee read register garbage.
  - One more row differs by 1 ulp: `func_00283028`, a VU `rsqrt` against an exact sqrt. It is
    left as it is.
- **40 rows written but left out of `functional.tsv`** until each is proven. Their files stay in
  `nonmatching/functional/`.
  - **13 unchecked rows:** loaders, main loops, FMV, menu state entry, glow sprites. Retail
    never returns from them within the gate's budget.
    - Leaving all 13 out fixes play drift in levels 4, 9, 11, 12, 14 and 16. The culprit
      narrowed to `func_L00_00303990` (the level loader driver) or `func_L00_002B30E8`.
  - **27 hand-written helper rows.** Level 26 drifts with them in. There are two culprits, each
    narrowed to a pair:
    - `func_00283430` (Euler rotation) or `func_002A04E8`;
    - `func_00282EB0` or `func_00283098`.
    - The other 25 rows are innocent and can return once the two culprits are settled.
- **Rows waiting on retail captures:**
  - `func_L08_003CD708` and `func_L08_003CDB78`;
  - `func_L20_0036AE68`: #392 moved its entry to `0x36AE78`, 272 bytes; re-capture it at the
    new entry.
- **Contributor PRs #396–#399** (about 160 newly matched functions) were in review when this
  was written. Any of them that matches a functional row retires that row at the next repin.
- **Levels 22 and 23 changed on purpose.** `func_L00_00424BB8` has a split variant for the
  levels whose copy writes `+0x3C/+0x40`. It gates SAME against retail states from both levels;
  level 0's form differs on all 8. So a tour that "diverges" there against an older build is
  the fix.

## The gate (`tools/fcheck.py`) and what SAME means

`fcheck check NAME` runs the candidate C and retail's code from real captured calls. It compares
memory, the result and the kept registers. Know its limits before trusting it:

- **Coverage.** A SAME verdict only covers the blocks the captured calls ran. Early captures ran
  about half the functional rows' bytes. Use `fcheck cover` and read the unrun blocks against
  the assembly. Most real slips were found that way.
- **Fixed on 2026-11-02 (OpenRAC `106145b4d`, `98de8c523`):**
  - The gate used to skip memory up to 1 MiB below the caller's `$sp` as "dead stack", which
    also hid heap stores. Now only the frames the two calls used are skipped.
  - Two dead-stack addresses left in memory compare as equal.
  - Re-gate any verdict from before this fix.
- **Data names match by position.** A wrong `D_` symbol can still gate SAME while the port then
  uses the wrong address. Check names against the level's `data_copies`.
- **Argument counts.** A missing float argument leaves whatever the register held. The gate sees
  it only if that value reaches memory. Check every callee's real integer and float argument
  counts.

## Player-reported bugs from this round and their causes

Most user-visible bugs were in the port's renderer or host code, not here. The table lists them
all, so you can tell which kind of fault looks like what. "Decomp" marks the ones fixed in this
repository or in a functional row.

| What the player saw | Cause | Where |
|---|---|---|
| Pause menu whited out | `func_003486A8` read a pointer chain one element late (functional row) | **Decomp** (row fixed) |
| Crash on nanotech level-up | Level-up sparks' slots (`D_00232760`) were paired through the particle loop's end pointer, not their own address. They landed on the fade list, which then read a spark as a moby. | Port symbol pairing |
| Dynamo targets only once | A jump table was cut short by six-digit level names | Port generator |
| Level 3 bolt callback to a non-function | A `lui` in a likely branch's delay slot was paired on the fall-through | Port generator |
| Saves wiped on New Game | A host file (`.DS_Store`) in the card folder hid the saves, plus a mis-aligned call table | Port host |
| Feltzin ship fight drifts from retail at tick 613 | Sound callbacks ran a tick early, collision and steering ran on host floats, and the generator stripped all-digit addresses as a suffix | Port host and generator, plus `ps2_float` |
| Same drift came back at tick 837 after a repin | New functional C for `func_002761F8` (CollLine) and `func_00277258` (CollSphere) did its maths in static helpers and `sqrtf`, which `ps2_float` didn't reach | **Decomp + port**: the generator now covers a candidate's helpers |
| Maktar arena entrance froze | `func_00132318` (snd_BankLoadByLoc) busy-waits on the 989snd loader's reply word; the port only answered SIF server 0x11 | Port host (`libraries.tsv` row) |
| Six levels' play drifted after a repin | An unchecked functional row: the level loader driver (`func_L00_00303990`) or a sibling | **Decomp** (rows left out) |
| Level 26 play drifted after a repin | Two hand-written vector helpers | **Decomp** (rows left out) |
| Weapon upgrade trails, vendor view covered, Lancer trail lines, ship exhaust ahead of the ship, arena curtain flat, cockpit screen empty, shield flicker, letterbox 1–2 px short | Frame composition in the port's renderer | Port renderer (OpenRAC #212) |

**The pattern:** when a repin changes play, suspect the newest rows first, especially unchecked
ones and anything with float maths. A row is innocent only after a retail comparison, not after
a clean build.

## Methods that worked

- **Retail reference.** OpenRAC's test-only interpreter runs the retail program (it is never
  shipped or played).
  - Set `OPENRAC_BOOT_CPI=1`, or it drops ticks and invents differences.
  - Pin the clock with `OPENRAC_CLOCK`: the title seeds random numbers from it, and two
    unpinned runs differ.
  - `--watch-stores ADDRESS:BYTES` with `OPENRAC_BOOT_WATCH_STACK=WORDS` shows who wrote a word,
    callers included.
  - Retail field `f+1` is port tick `f`.
- **Find the first difference, then walk back.**
  - Compare the random-number state every tick: rac2 keeps it at `0x133BE0`.
  - Compare positions bit for bit, and the level's state words.
  - From the first differing value, follow retail's store watches back to the function that
    wrote it.
- **Bisect in parallel.** Build several candidate trees at once, then run the same scripted
  route through each:
  - with and without a group of rows;
  - with each merge reverted.
  
  A one-at-a-time bisect over 30-minute builds wastes hours.
- **Tours.** OpenRAC's regress tour drives each level to control and compares the runs.
  - "Diverges from the previous build" is not "wrong". Check the diverging level against retail
    before reverting anything: levels 22 and 23 were a fix, and the 14-level change after the
    ship-fight merge moved toward retail.
- **Teleport for repros.**
  - `OPENRAC_TELEPORT=FRAME:X:Y:Z` (frames after control) and `OPENRAC_WRITE=cFRAME:ADDR:VALUE`
    reach a spot or a menu state quickly. Example: Maktar's arena entry is
    `--level 2 OPENRAC_TELEPORT=30:485.6:700.1:123.0 OPENRAC_WRITE=c300:1A7904:2`.
  - The same writes work in the interpreter.

## Lessons for writing functional C

1. **Read the unrun blocks.** SAME from a capture that didn't run a branch says nothing about
   that branch.
2. **Delay slots.** A store in a `jal`'s delay slot runs before the call. A store in a likely
   branch's delay slot belongs to the taken path only.
3. **Host floats are not EE floats.** Infinity times 0 is NaN on the host and 0 on the EE.
   Vector maths drifts by an ulp per step.
   - Keep retail's compare sense and operand order (`c.lt.s` against `c.le.s` differ on NaN).
   - Write helpers so `ps2_float` can cover them: in the candidate block, not shared with
     host-float code.
4. **Per-level copies differ.** The same short `func_XXXXXX` name can be different code in
   different levels. In level 22, `0x2E4708` is `func_002761F8`'s copy, not boot
   `func_002E4708`.
   - Map every callee through `config/levels/functions.tsv` places.
   - Level-named data in boot C, and `_sda`/`_base`/`_b` views, caused most crashes.
5. **Field widths and prototypes are behaviour.** A byte flag written as a word clobbers its
   neighbours. Keep helpers' real argument widths: `func_002A0468` takes four 64-bit command
   fields.
6. **Pool high-water words are inclusive slot indices.** rac2's particle word `0x1B1D98` is the
   highest live slot. A loop of `i < word` drops the newest particle every tick (the Lancer
   flicker).
7. **m2c-era drafts are not safe donors.** They carry `M2C_ERROR` zeros and name level-copy
   addresses as boot functions. Check callees and grep for placeholders before taking one.
8. **Retail sometimes relies on luck.** Some code reads a field before writing it and gets 0
   from the PS2's stack. On the host the same memory holds other bits. Compare the value at
   spawn against retail.
9. **PS2 scales.** Colour and alpha 0x80 mean 1.0. Texture sizes come from a nibble table.
10. **Busy-waits on the IOP.** A loop on an RPC reply word (FlushCache until it is no longer -1)
    needs its RPC hosted in the port. Search for other callers of the same client when you host
    one: `D_001A7140` is used by `func_00132318`, `func_00132498` and `func_001326D8`.

## Save format notes

OpenRAC's launcher now edits Going Commando saves. The map of the save, with its chunks, CRC
and progress flags, is in OpenRAC `launcher/docs/RAC2_SAVE_FORMAT.md` (PR #226). A few facts
there come from this repository's code and help when naming progress code:

- **Story bytes** are chunk 5, at `0x1395B8`. Each level's code indexes them by constants.
  Examples:
  - Maktar arena entered: byte 0x05;
  - Maktar arena challenges: 0x31–0x3B and 0x91–0x93;
  - Joba arena entered: 0x4A;
  - Feltzin, Hrugis and Gorn ship challenge wins: 0x61–0x64, 0x66–0x69, 0x6B–0x6E;
  - Snivelak boss: 0x83, where 2 means beaten.
- **Cinematic "seen" bits** are chunk 43, at `0x139768`. Scene `id` is bit `id & 31` of word
  `id >> 2`. Scene ids are numbered by level from the table at `0x1AD030`. The data-driven
  scene triggers skip a scene whose bit is set.
- **Per-level object-group states** are chunk 3004, at `0x19B2E8`. Bit 0x80 of each level's
  16 group bytes marks a group done. Naming groups needs each level's object data.

## Open items

- Settle the two level-26 helper culprits and the loader-driver culprit. Gate each one or
  rewrite it, then return the 25 innocent helpers and as many of the 13 unchecked rows as can
  be proven.
- Capture and gate the three waiting rows (two in level 8, `func_L20_0036AE68` at its new
  entry).
- Feltzin still splits from retail at about tick 1,937: the port fires one extra projectile.
  Projectile positions are 1–3 ulps off from the first spawn, likely the joint target
  (`func_0029FCC0` → `func_002A3F10`, the bone matrix) on host floats.
- Gorn's arrival differs from retail: the rain moby's region test (`func_002ACD38` against
  `0x1C4F40`) reads 0 in the port.
- Hrugis's arrival differs because the port doesn't model the EE time a load takes. Retail
  catches up 2–3 game ticks per field after it. That is a port model gap, not a slip.
- Name Maktar's other 13 arena challenges and Joba's challenges from the game text, for the save
  editor.

## Rules that still apply

- Honest flags only: per-file flags; no per-function overrides, inline asm, `GLOBAL_ASM`,
  `#define` aliases, `volatile` barriers or hardcoded addresses in matched C.
- Never Sony SDK source, samples or headers. Refer to the third-party rac1 decompilation only
  as "the NTSC decomp".
- PRs never touch the report. After merging, the maintainer rebuilds every release and pushes
  `chore(progress)` on its own.
