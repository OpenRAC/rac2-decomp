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

- **master** merges #396–#399 on top of #393 (functional C round 2). OpenRAC's default branch is
  `develop`; it pins `99f35ac2`, branch `master`. The next repin carries the 27 rows returned below.
- **Reports after #399:**

  | Release | Functions in C |
  |---|---|
  | US | 7,950 of 8,580 (87.68% of code) |
  | PAL | 7,074 of 8,672 (54.76%) |
  | US2 | 7,741 of 8,634 (82.92%) |

  At #393 they were 7,793, 7,006 and 7,612. `tools/progress.py --check` passes: the three
  reports agree on every function they share.
- **472 functional rows.** Each was re-checked with the corrected gate (below). Two real slips
  turned up and are fixed:
  - `func_003486A8`: read a chain of `func_00335E20` results one element late, so the pause
    menu's bars drew in the highlight colour (the "whited-out pause menu").
  - `func_003489E8`: called `func_00335F88` with fewer float arguments than it takes, so the
    callee read register garbage.
  - One more row differs by 1 ulp: `func_00283028`, a VU `rsqrt` against an exact sqrt. It is
    left as it is.
- **The drift blamed on left-out rows was a generator bug, fixed in OpenRAC #236.**
  - hostgen ignored an argument saved to the frame, so `func_L00_00303990` lost its second
    argument. Retail tests that argument at `0x304610` to choose its resume path,
    `func_L00_00358B30`. The port always passed 0, so it could never take that path.
  - `func_L00_00303990` and `func_L00_002A3B88` each declare two arguments, which restored it.
    That is why each row alone changed levels 4, 9, 11, 12, 14 and 16. With #236 and no rows,
    the tours are the same as with either row, so these rows were not the culprits.
  - Level 14's retail capture takes states from `func_L00_00358B30`.
  - **Retail comparison, level 14:** with the runs aligned at the hero's first big move, he
    settles at z `109.9896` in retail, `109.9895` with #236 and `109.9942` without it, for about
    305 fields each. After the two builds part in level 9 the fix is closer to retail on 828
    fields and further on 532, which is weaker evidence. The other four levels were not compared.
- **Level 26's drift no longer reproduces.** On `develop` (`498c04408`) each of the four suspects
  alone matches the build without them on level 26, and all 38 left-out rows together match the
  #236 build on all 26 tours. Tours compare rounded values, so an ulp-sized difference can hide.
  The cause was not traced.
- **27 helper rows are back, 408 rows in all.** Each has a current SAME verdict in OpenRAC's
  `fcheck.tsv`.
- **11 rows stay out of `functional.tsv`, files kept in `nonmatching/functional/`.** Ten are
  `unchecked` (loaders, main loops, FMV, code no capture calls) and `func_L03_003E4680` has no
  verdict. A clean tour does not count as SAME; a row returns only when it is proven.
- **Rows waiting on retail captures:** `func_L08_003CD708` and `func_L08_003CDB78`. Retail never
  called them in the `fcheck` play of levels 8, 9 and 19, so they need a route that reaches the
  object using them. They have near misses in `nonmatching/levels/` but no functional files yet.
  `func_L20_0036AE68` is matched and needs no row.
- **Contributor PRs #396–#399 are merged** and match 157 functions. 91 of them had functional
  rows; those rows and their files are gone, so `functional.tsv` has 381 rows. Three of the 40
  left-out files are matched now: `func_00293F98`, `func_002EC408` and `func_L00_002B30E8` (one
  of the two suspects for the level 4/9/11/12/14/16 drift). The matching C replaces them at the
  next repin. #397 moved `func_002CC528`'s catalogue entry 8 bytes later, to `0x002CC530`
  (32 bytes), in all three releases.
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
| Six levels' play drifted after a repin | hostgen dropped the loader's second argument; the rows that declared it restored the argument and changed play | Port generator (OpenRAC #236) |
| Level 26 play drifted after a repin | Not traced; no longer reproduces on `develop` | Unknown |
| Weapon upgrade trails, vendor view covered, Lancer trail lines, ship exhaust ahead of the ship, arena curtain flat, cockpit screen empty, shield flicker, letterbox 1–2 px short | Frame composition in the port's renderer | Port renderer (OpenRAC #212) |

**The pattern:** when a repin changes play, suspect the newest rows first, especially unchecked
ones and anything with float maths. A row is innocent only after a retail comparison, not after
a clean build. A row can also be right where the build without it is wrong: when two unrelated
rows give the same run, diff the generated code (`games/rac2-ntsc/gen`) for what they share.

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
- **Aligning a port run with retail.** Tick numbers part after a load, because the port doesn't
  model load time. Hold the level write through the boot, find the hero's first big move in each
  run, and shift the play inputs by the difference. Level 14 then stays within 0.05 for 685 ticks.
- **Shift every press after the load.** An arrival scene ends on a press, so a press that keeps its
  absolute frame lands at the wrong moment. Shift all of them by the load offset.
- **A hold is not a split.** The random state stands still in a pause and in load holds. Count a
  stretch across those gaps before calling it a divergence.
- **Random draws per tick.** `--watch-stores 133BE0:4` lists each draw with its callers. Place the
  port's state in that sequence, and compare draws per tick to find what ran or did not run.
- **Drop the row.** To clear a functional row, remove it so the port translates retail's own code.
  Most rows suspected this way were innocent. A temporary print can move stack data, so an
  uninitialized read may change value in the instrumented build.
- **Same bytes, each engine alone.** Playing one bank's sound in both sound engines showed they
  agree, which pointed at the commands the game sends.
- **Memory at one field.** At a field where the random state matches, count the floats within a few
  ulps of retail, with and without a change. OpenRAC #241's `ps2_float` additions lowered the count
  in all five levels tested, slightly in levels 19 and 22.
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

- Prove and return the 11 rows still left out.
- Find a route to the two level 8 rows, write their functional C, then capture and gate them.
- Feltzin: on `fcheck`'s level 5 route the random state now matches retail for 2,864 fields, to
  about 2,900 ticks after control, apart from a 1-field pause gap (OpenRAC #241). It parts at
  retail field 5061, after a level restart; not traced. The extra projectile at tick 1,937 came
  from a different input route and was not re-run.
- Levels 12, 14, 19, 22 and 26 part from retail at fields 2852, 3274, 2675, 1909 and 2463 on the
  same routes. Level 14's cause is the catch-up below; the others are not traced. Level 23 never
  lined up.
- Hrugis (level 10): on this route it stays in step for 1,056 fields after arrival, to field 2732,
  so its arrival is not where it parts here. The earlier report came from another route.

## Limits of the retail reference

"Retail" in these comparisons is the test-only interpreter, not a console. Its CPU matches well,
but its sound side is a model, and it can be wrong:

- **Sound parameter mask.** It read the mask of the set-params command wrongly, so the sound's
  pitch bend was cleared and sound slots ended at the wrong tick. That alone caused Feltzin's split
  at field 3328 (OpenRAC #241). The game's own masks settled it: 0xF comes with a pitch modifier,
  0x1F with a bend.
- **Catch-up after a hold.** After level 14's 9-field hold at field 3274, the interpreter runs about
  three game ticks in one field. The port stays at one per field. This is the load-time gap.
- **Frame load.** Gorn's weather (`func_L01_00399510`) scales its rain by `0x1B2150` and `0x1B214C`,
  which look like frame-load values: 0.87 and 1.25 on the arrival tick, then about 0.25. In the port
  they stay 0. That moves the random chain by a tick's draws, so level 15 never lines up. Not
  confirmed as timers.
- **Uninitialized `v[2]`.** `func_L01_003993C8` reads a third component it never writes, so its
  base count depends on leftover stack data: 6 in the interpreter, 4 in the port. Do not zero it
  alone: with no load scaling the port would draw more rain than retail.

When a run differs, check which side is right before changing the port. The Gorn lead this
document used to give (the region test reads 0) was not the cause: retail reads 0 there too.

## Rules that still apply

- Honest flags only: per-file flags; no per-function overrides, inline asm, `GLOBAL_ASM`,
  `#define` aliases, `volatile` barriers or hardcoded addresses in matched C.
- Never Sony SDK source, samples or headers. Refer to the third-party rac1 decompilation only
  as "the NTSC decomp".
- PRs never touch the report. After merging, the maintainer rebuilds every release and pushes
  `chore(progress)` on its own.
