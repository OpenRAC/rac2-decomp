# Matching blockers

This is the shared, versioned reference for matching blockers and measured remedies.
**Every contributor may edit any entry**, including findings originally written by someone
else. Work in this repository through a fork or topic branch and submit a pull request.
Maintainers review and merge contributions; they are not the only people who can write here.
A coding AI can edit this Markdown file with ordinary file and Git commands.

Discuss proposed changes in the relevant code or documentation PR.
[Issue #157](https://github.com/OpenRAC/rac2-gc-decomp/issues/157) is retired and preserved
only as historical provenance. [Issue #152](https://github.com/OpenRAC/rac2-gc-decomp/issues/152)
remains the reservation noticeboard. Neither a personal comment nor the wiki is a second knowledge
register. The code and qualified linked builds remain the authority for matching status.

## How to contribute

1. Read the relevant entry, `AGENTS.md`, the retained C in `nonmatching/` and current master.
   Reopen an attempt only with a new hypothesis, changed input or additional evidence.
2. Edit the existing entry directly in your branch. Add a section only for a distinct blocker.
   Do not create one file or one record per contributor, agent, session or experiment.
3. Record the target/family, applicable release and placements, compiler/assembler profile,
   hypothesis, measured outcome, remaining difference and next useful experiment. Negative
   results are useful when they rule something out; repeated identical attempts add no facts.
4. Distinguish **hypothesis**, **retained near miss**, **local match**, **PR pending** and
   **merged fix**. Link the PR/commit and the real checks. Equal size is not a match. Preserve
   superseded measurements as dated history and explain which later evidence supersedes them.
5. Submit a normal PR, in English. Anyone can propose a correction to any entry. Only the
   merge is reviewed by a maintainer; no special documentation ownership is required.

Keep game data, generated assembly, SDK material, trial objects and logs private. Do not
copy them into a PR or this document. Knowledge edits do not waive the source policy or
matching gates. Discuss an uncertain finding in the relevant PR, then incorporate the
agreed result here. A persistent personal issue comment is no longer required for blocker notes.

## Recent verified updates

### Three-quantity local allocation

**1 November 2026, retained near miss.** `block_alloc` sorts two or three quantities by hand:
`qty_compare (0, 1)`, `(1, 2)`, `(0, 1)` take fixed quantity numbers while `EXCHANGE` moves
`qty_order`, so the result depends on birth order; four or more go through `qsort`, which is
correct. `func_L07_002B3580` misses by a $v0/$v1 swap for this reason: block 2 holds the constant 2,
the 2.2f constant and the mode load, the last two tie, and the load is allocated last. Taking 2.2f
out of the block gives retail's pair but moves the FPRs. When two integer registers swap in a
block with few locals, count its quantities before trying spellings.

### 16-bit counters read through a wider local

**1 November 2026, local match.** `x++ > n` on a `u16` field keeps the old value in a HImode pseudo
and compares through `zero_extend`, which `func_L03_00409248` shows as `andi` where retail has
`daddu`. `unsigned c = x, old = c++; x = c;` gives retail's SImode copy. An `int` pair is one word
off (signed compare), and a true bitfield does not help.

### Complete matrix storage and loop lifetimes

`func_L09_003FEAE8` needs one 64-byte joint matrix, with its position at
+0x30. A detached position variable beside a 48-byte buffer did not represent
`func_0029FC20`'s output. The complete matrix and the real helper return types
recover the 520-byte body in both USA releases; PAL has no carried identity.

`func_L16_0041F360` uses 33 complete 16-byte ring points and separate counters
for generation, collision and final-W updates. Combined with the existing
`MACRO_ADDR` views and closing-point `qcopy`, these restore the 576-byte body
in all three releases. Strict linked checks pass in all three carrying programs.
The 48-byte collision buffer covers the query's 40-byte copy. The constructor
and caller initialize through +0x23; +0x24..+0x27 is transported to queue field
+0x34 without an identified semantic read in the inspected consumers. Do not
call it padding or invent zero initialization: other constructors assign that
field, and the whole indirect consumer graph has not been established. Point W
is only copied by the XYZ vector addition, then assigned before the next use.

The corrected `func_L07_0040FA90-matrix.c` near miss likewise uses a full
64-byte matrix and `func_00283658`'s actual two-pointer interface. Its historical
split storage and false third argument are superseded. The result remains
444/444 bytes and 0/1 in each release; state/current-pointer allocation differs.
Equal-size `func_L04_003EC140` and `func_L05_00420A88` drafts also remain near
misses: respectively six loop-pointer ordering words and four FP-register words
still differ. Their source headers record the profiles and reopening evidence.

### Ring geometry and path-controller storage

`func_L09_003FD128` uses the public RAC1
[heavy-interceptor light-ring body](https://github.com/OpenRAC/rac1-decomp/blob/a23a07114bae7547adffb442b0f23fc295a48238/src/overlays/l14_oltanis/heavy_interceptor_and_turrets.c)
under GPL-3.0. Independent RAC2 frame/table measurements retain its four-row
matrix, 82 XYZ vertices, 84 colors and complete temporary vector. The texture
and GS interfaces carry full 64-bit values. Its 824-byte C body qualifies in all
three releases; equal-looking geometry is not a reason to shorten its buffers.

The two Smolg path controllers `func_L17_003C6CE8` and `func_L17_003C69A8`
retain complete 16-byte path/working vectors. Their voice-active field and
sound-bank byte are unsigned; the latter uses an incomplete byte view and only
reads element zero. The yaw declaration targets the same canonical smoothing
helper and preserves all three integer-bank arguments, four FP arguments and
the float result. These source lifetimes recover the 812/828-byte bodies in
US and US2; their canonical identities are absent from PAL.

`func_L07_003EEE28` keeps the speed cap's actual lifetime and samples each next
phase/rate before storing the preceding phase. Its final distance result stays
float. The 832-byte body qualifies in US and US2, with no carried PAL identity.
All four additions passed the complete 84-program strict build without C
fallback; the separate entry repair in section 18 adds no matching credit.

`func_L00_003ADCD8` remains deferred. Its historical draft accesses 16 bytes
through addresses of four-byte pointer-parameter spills. The caller passes
ordinary object pointers, not vector values. Hardware alignment behavior does
not make those out-of-bounds C objects valid. A complete object and a truthful
lowering must be established before reopening it; no handwritten-assembly
classification follows merely from this failed reconstruction.

**29 October 2026 cross-release integration:** `func_L15_00434D28` passed its
local PAL check but failed strict linking because its direct in-unit call needed
the C section for `func_L15_004351E0`, whose body is not carried into PAL.
The documented `ref_L15_00434D28_00` external binds the actual particle helper
in each release. Strict Gorn builds now pass in USA v1.01, USA v2.00 and PAL.
Keep the helper's real arguments; local text equality alone does not validate
the caller's linked dependencies.

**29 October 2026 maintainer ABI correction:** the qualified game compiler
measures `sizeof(long) == sizeof(long long) == 8` and `sizeof(void *) == 4`.
The `unsigned long` style argument of `func_0027FAA8` is therefore 64 bits.
PR #365's 32-bit-style probes for `func_002CF2B8`, `func_002CDA20` and
`func_002D53F0` used an incorrect interface; their 132/136, 136/140 and 136/140
byte measurements do not establish an ABI-preserving improvement. The earlier
wide-argument near misses are retained. Reopen on register/lifetime evidence
while preserving the complete colour argument, not by narrowing its prototype.

**28 October 2026 recheck:** `func_0029DD30`'s old retained note blamed a limitation
in build relocation derivation. A common-base source probe using `D_00140000` and
the measured `-0x6A48`/`-0x6898` offsets compiles to 132/140 bytes and 0/28 USA
v1.01 placements; the size check stops before relocation derivation, so it does
not establish whether that body can be placed. The immediate measured blocker is
cc1 sharing the base and simplifying retail's branch-likely layout. The corrected
candidate remains in `nonmatching/`; no build-tool change is proposed. A simplified
volatile-read control-flow probe compiles to 88/140 bytes and 0/28, losing the
retail's independent address materializations and branch-likely paths. This is
weaker than the retained candidate and does not change its status. Replacing the
common-base expressions with the already named `D_001395D5` and `D_001397C4`
symbols in the retained branch structure still compiles to 132/140 and 0/28;
cc1 continues to share the address setup, so this spelling does not recover the
retail layout. A 29 October explicit-goto form with repeated volatile reads
also compiles to 132/140 bytes and 0/28; it retains ordinary bnez/bltz branches
and the shared base, so this control-flow spelling does not recover retail's
branch-likely layout.

**28 October 2026 recheck:** `func_002B9390`'s retained `-O2 -G8`
candidate is 140/140 bytes and 0/28 in current-master USA v1.01. Retail saves
`$ra` at `$gp+0x2DB8`, keeps the scan end pointer in GP storage and uses
branch-likely flow; cc1 adds a stack frame and differs in the loop and handler
call setup. Five earlier source forms measured 164, 152, 140, 156 and 152 bytes;
the remaining work has no new plain-C hypothesis within the documented small
function budget. PAL and USA v2.00 checks are historical and were not rerun
because those ROMs are absent from this checkout. Keep the marker and retained
candidate; do not classify it as handwritten based on difficulty.

**28 October 2026 recheck:** `func_002B6658`'s dedicated `-G8` candidate is
152/148 bytes and 0/28 in current-master USA v1.01. Five source forms covering
`while`/`continue`, `if`/`else`, a counted loop, a condition-label goto and a
local flag copy retain the same core mismatch: retail's `bltzl`/`beqz`/`bnel`
forms and delay-slot advance, plus the global-store and vtable register choices.
The marker remains; this result does not support an `ASM_FUNC` classification.

**28 October 2026 recheck:** `func_00282AB0`'s retained `-O2 -G0` candidate
is 156/160 bytes and 0/28 in USA v1.01. The retail `add`/`addi` operations
and plain `beqz` layout remain distinct from cc1's `addu`/`addiu` and
branch-likely layout; the source also records the load and delay-slot
differences. No new C hypothesis changes the retained measurements. Keep the
marker; any `ASM_FUNC` classification requires maintainer agreement.

**28 October 2026 recheck:** `func_002AD7B8`'s `-G8` source using
`while (delay++ < 28) {}` compiles to 164 bytes and 0/28 in current-master USA
v1.01. It reproduces the increasing delay count with the increment in the
branch delay slot; the counter register and later allocation remain different.
The separate delay variable used to select retail's counter register adds a
copy before the compare. Keep the marker and the retained best source.

**28 October 2026 recheck:** `func_002A0250`'s retained `-G8` candidate is
172/172 bytes and 0/28 in current-master USA v1.01, with the first mismatch
at `+0x60`. Naming the u16 at `0x10FFB0` recovers the entry sequence; the
remaining tail differs in when the old packet pointer is stored and incremented.
The prior 1,080 statement-order and 192 type-combination trials did not close
that difference. Keep the marker and retained near miss.

**28 October 2026 recheck:** `func_002DE618`'s break-then-clear source
hypothesis compiles to 212 bytes and 0/28 in current-master USA v1.01. It keeps
the final bit clear outside the scan but diverges from retail's loop and call
layout; the first mismatch is `+0x10`. PR #362 subsequently supplied the retained 212-byte candidate with reduced
key/flag pointer registers swapped. That newer source supersedes the 188-byte
merged-clear draft; the older trials remain history, not the current best result.

**28 October 2026 recheck:** `func_002F5D40`'s retained `-G8` candidate is
236/224 bytes and 0/28 in current-master USA v1.01. Its `func_002EF010`
result is declared at the callee's full `unsigned long` width, which adds
conversions before the 32-bit address shifts; conditional and address
scheduling also differ. Keep the marker pending a real return-contract audit
or independently justified source-lifetime evidence.

**28 October 2026 recheck:** `func_002798A0`'s retained plain-C draft is
224/228 bytes and 0/28 in current-master USA v1.01. Its table/state loop is
reconstructed, but size differs so relocation-adjusted instruction comparison
does not run; register allocation and branch layout remain open. A historical
228-byte form also missed at `+0x4`. Keep the marker and best retained source.

**28 October 2026 recheck:** `func_00304128`'s `-O2 -G0` candidate is
228/228 bytes and 0/28 in current-master USA v1.01, first differing at `+0x44`.
The remaining differences are the symbol-to-local 16-byte copy's register and
destination choices, the frame-backed float store, and later call argument
scheduling. Retained pointer, union, struct and temporary spellings did not
resolve those differences. Keep the marker pending a materially new source
hypothesis.

**28 October 2026 recheck:** `func_00298298`'s retained `-G8` candidate is
216/232 bytes and 0/28 in current-master USA v1.01. Its control flow, state
values and loop edges are recovered. Retail's dead `~0x80` constants in two
loop-head delay slots, register allocation and separate state 21/20 tails
remain unresolved. Keep the marker and retained candidate.

**28 October 2026 recheck:** `func_002A8600`'s `-G0` candidate is 216/232
bytes and 0/28 in current-master USA v1.01. It retains the measured iterator
state accesses and four-argument helper ABI; the active/inactive filter and
shared return/call layout still differ. Keep the marker and retained source;
do not add redundant stores or artificial dependencies to force the retail
control flow.

**28 October 2026 recheck:** `func_00305438`'s `-frac2-qcopy` indexed-loop
candidate is 172/172 bytes and 0/28 in current-master USA v1.01, with the first
mismatch at `+0x3C`. The body, calls and copies align; cc1 duplicates and folds
the first loop exit test and puts the body before the test, while retail enters
with an unconditional branch to the rotated test. Keep the marker and the
retained C; no generated loop machinery is warranted by this one shape.

**Source-method update, 25 October 2026:** RAC1's reviewed shared EE helpers
(`qcopy`, `qcopy_nc`, `qzero`) and original public runtime-library target
primitives are now permitted under `AGENTS.md`. Earlier prohibitions below are
historical for those specific routes; they do not establish that the affected
functions now match. Requalify the retained C, its interfaces and every applicable
linked placement. Arbitrary game-function assembly, register pins, artificial
barriers and false declarations remain forbidden. Proprietary SDK source is
still outside the permitted sourcing policy.

The imported observations below are dated measurements, not a fresh census. In particular,
older claims that the following mechanisms are universally impossible are superseded:

| Topic | Verified update |
| --- | --- |
| Complete compiler constant pools and RAC1 source methods | [#318](https://github.com/OpenRAC/rac2-decomp/pull/318) records the 25 October qualification: six functions (4,420 distinct C bytes), 240/240 placements and all 84 strict programs passing. `__divdi3`, `__moddi3` and the decimal formatter retain their original compiler sections (560 constant bytes per boot release). Reviewed transfer helpers close two copy/clear bodies; accurate scalar stores close a sixth. All 225 runtime tests pass. Reports are unchanged; constants receive no new Data credit. |
| Vector-copy address formation and scheduling | [#262](https://github.com/OpenRAC/rac2-gc-decomp/pull/262) and [#275](https://github.com/OpenRAC/rac2-gc-decomp/pull/275) provide opt-in copy profiles. They solve qualified witnesses, not every copy/allocation case. |
| Wide-store annulled slots | [#279](https://github.com/OpenRAC/rac2-gc-decomp/pull/279) restricts two search paths with an opt-in profile; it is not a hardware prohibition. |
| A register-fed clear of `0($sp)` | [#281](https://github.com/OpenRAC/rac2-gc-decomp/pull/281) is merged; older source notes calling it proposed are historical. |
| `_fpadd_parts` and `dpmul` | [#265](https://github.com/OpenRAC/rac2-gc-decomp/pull/265) and [#267](https://github.com/OpenRAC/rac2-gc-decomp/pull/267) are merged SDK-profile matches. |
| `game/00308600` follow-up | [#287](https://github.com/OpenRAC/rac2-gc-decomp/pull/287) adds `func_0030E700`, 424 bytes at 28/28 places in each USA release, with 28 strict programs per release and 139 tests passing. `func_00308600` remains retained at 356/360 bytes, 0/28 USA v1.01 places. |
| Existing compiler profiles, argument ABIs and shared-data identities | Qualification on 23 October 2026 adds 39 primary shared functions (9,208 distinct bytes): ten in [#300](https://github.com/OpenRAC/rac2-decomp/pull/300), then 29 and a separate 148-byte PAL timer in [#301](https://github.com/OpenRAC/rac2-decomp/pull/301). The combined source tree passes 28 strict programs in each release (84 total), 143 tests and all 2,781 new-function placements. Three existing ABI controls add 171 placement checks. No report was regenerated. |
| Truthful external sizes and shared update helpers | [Source qualification](https://github.com/OpenRAC/rac2-decomp/commit/609753de4e58218805f4ff0983f36bdb15648d9e) adds 18 primary C functions (9,236 distinct bytes): 168 USA v1.01, 140 USA v2.00 and 77 PAL placements. All 84 strict programs, 385 placement checks and 143 tests pass. Three dedicated units use measured 16-byte vectors or a 15-byte label with standard compiler/assembler `-G16 -Wa,-G16`, preserving every instruction and relocation. See [the small-data notes](COMPILER-NOTES.md#symbols-addresses-and-small-data). Four obsolete no-C screens are retired; the remaining reconstructions stay unlinked. No report was regenerated. |
| GP addresses of objects whose full extent is unknown | The existing `SDATA(symbol)` macro now has the explicit alias-metadata support used by current RAC1. Four callers (`func_L08_003CFE68`, `func_L12_00421110`, `func_L12_00429868`, `func_L09_003B6550`) retain their local matches with incomplete arrays, replacing false 4-/8-byte declarations. The alias names the same canonical storage; its assembler metadata does not define a C object size. Independent compiled/link controls cover full 14-/28-byte reads, ordinary-code identity, signed GP limits and same-prefix decoys. The separate `func_L18_003FB620` repair uses its measured 24-byte settings type with `-G32 -Wa,-G32`. These are source-contract repairs with no additional matching credit; see [the address-view method](COMPILER-NOTES.md#symbols-addresses-and-small-data). |

These summaries do not award additional matching credit or replace the build. Check current
source before relying on any older count, profile or pending-PR label in the imported notes.

The SDATA route also closes `func_L20_004435A0` (492 bytes): the unknown-sized vector
keeps an incomplete declaration, while `func_L20_00442F80` is declared with its
actual pointer return. Its failure path returns null; its other paths forward the
child pointers returned by `func_L20_00443328` or `func_L20_004431E0`. This correct
contract closes the last temporary-register difference. Both USA placements and
their strict linked builds pass; PAL has no corresponding catalogue identity.
The same address-alias attempt on `func_00132028` remains 484/488 bytes: metadata
does not force a separately materialized indexed address. Its retained C records
that negative result.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_002798A0` is C in `src/game/00274128.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_00298298` is C in `src/game/00294BC8.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_002A0250` is C in `src/game/0029DE38-textures-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_002A8600` is C in `src/game/002A7750.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_002DE618` is C in `src/game/002DDEC8.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_002F5D40` is C in `src/game/002F5220.c` (`-O2 -G8 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_00304128` is C in `src/game/00304128.c` (`-O2 -G0 -ffunction-sections -mno-split-addresses`), placed at 28 US, 28 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

## Topic index

The 52 original section numbers are preserved for existing references. Anyone may improve
these entries; their original authors do not hold exclusive editing ownership.

| Entry | Topic |
| --- | --- |
| [01](#blocker-01) | Register allocation on long bodies (the dominant wall) |
| [02](#blocker-02) | LICM: the retail re-materialises a base inside a loop |
| [03](#blocker-03) | If-conversion |
| [04](#blocker-04) | `nop` before `jr $ra` |
| [05](#blocker-05) | `nop nop` before `div.s` |
| [06](#blocker-06) | Switch tables that travel with the function |
| [07](#blocker-07) | Annulled integer branch delay slots |
| [08](#blocker-08) | Single-register `%hi`/`%lo` addresses |
| [09](#blocker-09) | Folded addresses where retail materialises the base |
| [10](#blocker-10) | Equal-address branch folding |
| [11](#blocker-11) | MMI and undecodable words |
| [12](#blocker-12) | A catalogue entry whose body differs between programs |
| [13](#blocker-13) | Floating-point literals are calibrated, not computed |
| [14](#blocker-14) | Store order is not one universal rotation |
| [15](#blocker-15) | A `nop` after `mfc1` that retail does not have |
| [16](#blocker-16) | If-conversion of constant selections |
| [17](#blocker-17) | A 128-bit zero: por plus sq against sq zero |
| [18](#blocker-18) | Catalogue entries that are not functions |
| [19](#blocker-19) | The delay slot's filler is chosen by the scheduler, not by you |
| [20](#blocker-20) | Two exits where cc1 keeps one |
| [21](#blocker-21) | Varargs: the saveregs prologue is exact, the call is not |
| [22](#blocker-22) | Vector copies: address materialisation is only part of the mismatch |
| [23](#blocker-23) | Keeping a branch in step with master (tooling, not a wall) |
| [24](#blocker-24) | Prologue and entry-block ordering |
| [25](#blocker-25) | Small constants: rematerialised against reused (both directions) |
| [26](#blocker-26) | A dead store or dead load that retail keeps |
| [27](#blocker-27) | The missing `andi reg,0xFF` |
| [28](#blocker-28) | Commutative `addu`: base first against index first |
| [29](#blocker-29) | Loop-form canonicalisation: countdown and one-step unroll |
| [30](#blocker-30) | Loop-alignment padding |
| [31](#blocker-31) | lui at / low-half access: an existing per-file profile |
| [32](#blocker-32) | The output for a body depends on the other functions of its unit |
| [33](#blocker-33) | The 64-bit difference in specific attempts |
| [34](#blocker-34) | The catalogue's fingerprint merges two bodies |
| [35](#blocker-35) | The catalogue's linker-fill rows |
| [36](#blocker-36) | -mno-split-addresses also keeps some symbol addresses together |
| [37](#blocker-37) | Decode the exact R5900 instruction, not a broad prefix |
| [38](#blocker-38) | What this cc1 has no spelling for |
| [39](#blocker-39) | Source shapes that moved a body |
| [40](#blocker-40) | Smaller things worth knowing |
| [41](#blocker-41) | The productive route |
| [42](#blocker-42) | Register-allocation ties: a stopping signal for tested forms |
| [43](#blocker-43) | Block ordering: distinguish source structure from unavailable flags |
| [44](#blocker-44) | Relocated instructions are validated in a separate pass |
| [45](#blocker-45) | Source shapes that move a body |
| [46](#blocker-46) | The `dli` expansion of all-ones masks |
| [47](#blocker-47) | Catalogue filler rules applied; mixed prefixes remain separate |
| [48](#blocker-48) | The wave 12 census: historical sample, not today's inventory |
| [49](#blocker-49) | The wave 13 census: correct the screens before selecting work |
| [50](#blocker-50) | Five specifically audited residual extents — resolved by PR #253 |
| [51](#blocker-51) | The wave 14 census: a call inside one object, and a screen that was too broad |
| [52](#blocker-52) | What a C body cannot carry: the measurement, and the rule |

The following material was moved from issue #157 on 22 October 2026 (UTC). Its dates,
counts and conclusions retain their original scope. The old issue summary is retained
below as historical context; the newer verified updates above take precedence where they
explicitly supersede it. Earlier issue revisions and original contributor comments remain
available through GitHub history and their source links.

## Imported issue observations and historical measurements

## Status — 21 October 2026

The numbered history below is retained, with obsolete conclusions and incorrect mechanisms corrected directly. A historical failure applies to its source, compiler, profile and placements; it does not prove that a whole instruction class is unreachable from C.

| Topic | Current status |
|---|---|
| Extra nop after mfc1 | Resolved by the qualified **gas** interlock correction in [PR #222](https://github.com/OpenRAC/rac2-gc-decomp/pull/222). [Issue #247](https://github.com/OpenRAC/rac2-gc-decomp/issues/247) is closed as completed following strict validation. The named witness func_L22_003A2DF8 passes 2/2. |
| Cache invalidation and assembly fallback | [PR #252](https://github.com/OpenRAC/rac2-gc-decomp/pull/252) is merged. Toolchain changes invalidate objects; `tools/build.py all --strict` rejects C fallback to assembly. |
| Catalogue filler/residues | Earlier measured rules landed through [#239](https://github.com/OpenRAC/rac2-gc-decomp/pull/239)/[#241](https://github.com/OpenRAC/rac2-gc-decomp/pull/241). [PR #253](https://github.com/OpenRAC/rac2-gc-decomp/pull/253) is now merged for the five specific extents in section 50 and matching level placements. Other mixed boundaries remain separate. |
| Clear scheduling | [PR #251](https://github.com/OpenRAC/rac2-gc-decomp/pull/251) is merged: `-frac2-zero-ti-barrier` is qualified, default-off and per file. It does not solve every single-zero/nonzero-offset case. |
| Displaced zero stores | [PR #258](https://github.com/OpenRAC/rac2-gc-decomp/pull/258) corrects the fold from [issue #248](https://github.com/OpenRAC/rac2-gc-decomp/issues/248): only a register-only store address can fold to architectural zero. A/B over 775 preceding units found zero non-debug section changes and 11 `.mdebug` differences. Three clean witnesses match 204/204 bytes at 1/1, 264/264 at 1/1, and 112/112 at 27/27. The final tree passes all 28 programs with --strict and all 57 tests. Vector-copy address materialization remains open. |
| Reviewed source additions | [PR #246](https://github.com/OpenRAC/rac2-gc-decomp/pull/246) is merged at 5f4ced8; [PR #249](https://github.com/OpenRAC/rac2-gc-decomp/pull/249) at 8444cb6. [PR #244](https://github.com/OpenRAC/rac2-gc-decomp/pull/244) is merged at fc02388 with 38 additions across 307/307 placements. The combined strict build passes all 28 programs with no rejected C placements. |
| Diagnostics and source-policy checks | [PR #257](https://github.com/OpenRAC/rac2-gc-decomp/pull/257) is merged. The differ explicitly decodes R5900 instructions, tests cover EE operands and relocated instruction bits, and the repository check rejects empty source barriers. AGENTS.md now distinguishes missing returns and live three-operand multiplies from evidence of fragments or handwritten code. |
| Old examples rechecked | 27 already-C witnesses cited below pass 192/192 placements under the qualified compiler. Other named cases were covered by the PR #244/#246 touched-unit reviews. These results resolve those examples, not every similar historical near miss. |

**Acceptance is the full linked build with every expected C placement accepted.** Use `tools/build.py all --strict`; an image rebuilt with assembly fallback is not a new C match. Inline assembly, fake barriers, register pins, fabricated symbol identities and knowingly false prototypes are not remedies. Missing jr, mult without mflo, or por/lq/sq/ldl/ldr alone does not establish handwritten assembly or a catalogue fragment.

**Historical scope.** The original 12 October report covered six waves, approximately eight workers in each of the first five and 49 in the sixth, 521 functions in all (PRs #149/#151/#153/#155/#156/#159). Wave 8 added 40 workers and 122 attempts. Later counts describe later dated samples, not today's unfinished-work inventory.

<a id="blocker-01"></a>

## 1. Register allocation on long bodies (the dominant wall)

**Ties and spill slots, 1 November 2026:**
global allocation orders pseudos by `floor_log2(refs) * refs / live length`. With equal refs, the
order of two sets decides. `func_00306680` swapped $s7/$fp until its `%hi` was set first, through a
local for the address (same bytes otherwise). Its PAL copy needs the plain form.
Spill slots of hoisted addresses follow gcse's reaching-register numbers, and those follow hash
bucket order: `(14030 + K) % size` for a frame address K, with size `max_cuid / 2 | 1`. A rotated
slot order therefore means a different insn count at gcse, not a different allocation.
`func_L00_003A6538` closed with 3 fewer insns: the second spin read inline instead of a local, a
`color` local dropped and an `int` last argument. `func_L00_003A53E8` needs at least 12 more,
`func_L00_003A1580` about 10 to 20 fewer. Forcing the size in a diagnostic cc1 is enough to test
this: a two-line `getenv` in `alloc_expr_hash_table`, never in the real compiler.
Honest insns for the count: a value set before a label and read only past it survives cse1, is
counted, and gcse's cprop folds it, so the bytes stay. `func_L08_0042A0B0` needed 12: small named
constants read in the loop (`last = 19`, `total = 20`, `mask = 3`, two counts, `mode`, `flags`) and
argument copies read only in it (`segment`, `path`, `entry`, `row`, `w0`). No dead initial values.
A literal float gains nothing (it already takes two insns), nor a constant read in its own block,
nor a large constant (it stays in a register).

**Sub operands and one-cycle-late insns, 1 November 2026:**
`sub.s $f13,$f0,$f13` (the subtrahend in the argument register): local-alloc suggests the hard
register to both dying operands, so the minuend takes it unless it is not local. A variable with
two deaths goes to global-alloc: `t = p[5]; t = f(z, t - q[5]);` closed `func_L02_00401638`. With two
local operands the shorter life wins, which is sched1's order.
An ALU insn retail issues after a call that sched2 here puts before it (`func_00334A88`) can be a
block-placement matter: `$a0`, `$a1` and the insn compete for two issue slots, and one more insn in
the block delays the call by a cycle. Setting `axis` before the branch moved that insn into the
previous block, so the call became ready together with the set, and `reorg` filled its slot with
the argument. Check this before looking for a hidden insn. `func_L12_00300410` has the same shape
with no such insn to move, and stays open: its $s0 set would need a barrier or a dependence.
An argument pair `lui`/`addiu` kept together among other argument moves is a `MACRO_ADDR` object:
that alone closed `func_L00_003B3450` and took 7 rows from `func_L02_00401638`.
Sched ties: `rank_for_schedule` compares priority, register weight, class against the last insn,
then the count of dependents, then the original order. An insn that reads the frame register gets
one more dependent from a following call in its block (`func_L23_0041A3B8`).
Later the same day: `func_L00_003DCC48` lost its slot rotation with two locals for its `color | K`
values, set at the top of the loop body. loop.c hoists them only from before the body's first
conditional; set after it they stay in the loop (1632 bytes). `func_L00_002ACF88`: jump.c turns
`if (c) goto L; x = a; goto M; L: x = b` into `x = a; if (c) ...` when both arms start by setting
the same register, so `v0 = 0` took the slot `object = 0` needs. A `goto fail` to the function's last
`return 0` leaves no such arm; retail's `found` test after the increment is a plain `break`.
`func_002BBF40`: `optabs.c` swaps a commutative pair when the target is the second operand, so
`x = y * x` emits `x, y`; a new target keeps `y, x`. A float constant written inline gets a pseudo that
crosses no call, and sched then keeps it after the call, unlike a named local. Under `-g`, two
statements on one line share their note, so no `nop` before their `div.s`.
`func_L00_00421C50`: the unit's copies through `p + 0x60` kept `p` alive and rotated every saved
register; check each long-lived pointer's last use against retail first. Pseudos of PRE copies at an
arm's end prefer the next call's argument register, which puts that copy in a branch's slot.
`func_L00_00420C38`: retail's `lbu`, `andi` at every use and raw `sb` act like an unpromoted QImode
pseudo; `int state` with `(u8)state` gives only the first `andi`, as combine knows the upper bits.
Fresh drafts from m2c, same day: `func_L00_004212B8`, `func_L00_00421C50`, `func_L00_0041C2D0` and
`func_L00_002A67F8` closed in 5 to 15 rounds each, after the older drafts had plateaued. What did it:
a frame or field address written inline at every use, with no pointer local, so gcse makes retail's
reaching copies (`s0 = cam + 0x30` in each arm, `s1 = s0` before the join; a local for it gives one
pseudo). The local goes after the arms if retail needs one. `d = f(a); v = tmp; g(v, c, d)` keeps a
call's result apart from a frame address, and stops a tail cross-jumping further back than retail's.
`lhu; sll 16; sra 16; sh` is a `u16` local read once and cast at the call, `lhu` then `addiu; sll; sra`
is `s->h = s->h + 1; if (s->h >= K)`. `sb` or `sw` behind `lui $at`, with no `$gp` form in a slot, is a
small-data object at a nonzero offset (`D_001A7A70[0xD]`, `D_001A79F8[2]`). `lui; addiu; lbu 0x16` is a
complete struct larger than `-G` read by field; an incomplete array folds to `%lo`.
`addu rd, shift, sum` needs the index in an address, `pp[i]` used twice; `pp + i` gives the operands
the other way, whatever the source order. `func_L00_002A67F8`: `li v0, K; sw zero; sw v0` in two arms is
a post-reload cross-jump. Written with one `next_state` variable the stores swap, as sched's register
weight prefers the store that kills it, and no spelling of the two stores moves that. The permuter's
exact result for this needed a zero local unset on the `goto` path, refused as an uninitialised read
(reload substitutes the constant only after sched1). Per-arm statements match under the plain profile,
so its old `-frac2-gcse-unsplit-edges -frac2-keep-block-order` were not needed.
Next run, 2026-11-01: `func_L00_002B2318`, `func_L00_003FEEA0`, `func_L00_003A9C58`, `func_L00_003EF560`
and `func_L00_003A0F30`. A callee's real return type matters even when the value is ignored: a call
declared `void` leaves $v0 free, one declared `int` marks it set and unused, and that moved the
next block's registers in `func_L00_003FEEA0` and `func_L00_003A48D0` (take the type other units agree on).
A dead read in a loop with both arms identical is `if (flag) A else A`, cross-jumped at jump2. Whole arms
written out also lengthen a pseudo that spans them, which is how `func_L00_002B2318`'s $s4/$s5 swap went:
priority is `floor(log2(refs)) * refs / live`, and 396 against 402 was enough. A constant that is
rematerialised after a call where cse should have reused it means a label with a second use at cse time, so
the destroy calls are written at each exit and cross-jump later, instead of a `goto`.
Under `-g` the two-slot `div.s` floor counts from the line note, so `x = 1.0f / w->rate` after a statement
computing `w` gives retail's single nop, and a statement of its own gives two. Loop labels are 8-aligned, so
a nop before one comes back by itself once the size is right.
A frame or base address in a call-clobbered temp with a copy in a saved register (`daddu fp, s0`) is gcse's
reaching register: the first computation must go through a pseudo, and the later one is a local set in a
later block (`vp = &velocity` after the first loop, `base2 = object + 0xC0` before the last). If nothing else
has a saved register left, the reaching register is spilled, which accounts for a lone `sw` of a base
(`func_L00_003EF560`, frame 0x110). Splitting one float variable in two can decide a frame size and the whole
FPR order (`func_L00_003A9C58`: `scale`, `bounce`, `speed2`). An allocno also keeps off a register that a
lower-priority conflicting allocno prefers (global.c's `regs_someone_prefers`): that function's `scale` ranks
below the loop's `one`, so `scale = f(age); scale /= f(7);` loses $f20 to it, but
`scale = f(age) / f(7);` copies from a temp that took $f20, the copy makes $f20 `scale`'s preference, and `one`
moves to $f21. Fewer refs on `scale`, and no wrapper needed. Try the expression form before counting refs.
Constants hoisted from a loop have to be
body locals or literals by the same measure, and `short life = 50` before the loop gives $fp to the 2.
A byte read of a short that keeps the short's allocation is `int l = r->life & 0xFF`.
Open: `func_L00_0041EE58` and its twin `func_L00_003E2510` keep their first frame address in a
call-clobbered temp with a copy in the call's delay slot, and every later use on the copy; ours is one
pseudo over the calls. A local after the call merges into it, and `-fno-regmove` changes nothing there.
`func_L00_003F4210` has one word left, `mul.s f1, f0, f1`: the target has to tie to the second operand,
so `speed` must not die at the multiply or be a global pseudo; a new target ties to the first. Inline
helpers with float parameters and named locals for both operands were tried on 2026-11-01 and change nothing.
`func_PAL_L00_004266C8`, the PAL copy of `func_L00_004212B8`: the 50 Hz timers are `(D * 5 + 2) / 6`
and all its sizes match, with only $s3/$s4 swapped, as the extra insns change the live lengths.
A sweep of forced bucket counts gives every size that fixes a draft, so read the whole list: `func_002B88F0` was 199,
with 161 to 183, 191, 193, 201 and up all exact, so it needed 2 more buckets (4 insns) and nothing else. Plain indexed
loops give them: `for (i = 0; i < 16; i++) a[i] = 0;` has an address computation per element at gcse, and loop.c turns it
into the same pointer countdown as `*dst++` over a reversed counter. Check loop spellings first when a near miss is
all stack offsets; they change nothing after loop.c.

**Qualified field and call-lifetime remedies, 25 October 2026:**
`func_002B52A0` is now a 980-byte C implementation at 21 places in each
USA release; PAL has no matching canonical identity. Its controller +0x90
field has two independently observed loads, faithfully represented by a
volatile field. Complete 16-byte vectors preserve the real helper extents.
The 200-byte `func_L14_003D18C8` matches its one place in all three releases:
the true float return, bank-preserving call setup and separate matrix-basis
pointer recover its actual lifetimes. Both are accepted in all 84 strict
linked programs, with no new compiler mechanism.

The existing 72-byte `func_L09_0033E8B0` wrapper now explicitly forwards
all five GPR arguments and the FP step to the actual deep consumer. Its
allocated sections remain byte-identical and all nine existing places pass;
this repairs an interface, not additional coverage. Audit the complete call
chain before deciding that apparently unused incoming registers are dead.

**Truthful return types and EE call setup, 25 October 2026:**
`func_L16_004110D0` is a 664-byte C implementation with its real 0x90
frame. The earlier draft already matched through its first 356 bytes.
Auditing every `func_002AAA00` return path established an explicit float
result, including the early zero and normal updated-rate paths; the caller
ignores it. Correcting the old void declaration changes four setup slots
without changing arguments or introducing a result use. An independent
source-only control confirms this effect.

The actual lower/upper state stores and a typed `func_002A8D70` argument
interleaving close the remaining differences. It preserves object, bone,
mode, first, second and third in A0-A3/T0-T1 and x/y/z in F12-F14, with
no stack arguments. This follows the current RAC1 call-shape practice in
COMPILER-NOTES.md; it does not fabricate a prototype or reorder a bank.
Six targeted trials required no compiler change. Both USA placements pass,
PAL has no corresponding catalogue identity, and all 84 strict programs
pass with the integrated source set. Different source declarations still
need a consistent native interface or adapter before a PC-port claim.

**Output-only packing and unused formals, 28 October 2026:**
`func_002AE730` had an inferred integer return in its C definition, while some
callers declared void. Propagating that inference changed the delay-slot store
in `func_002BAA28`. The current RAC1 counterpart is output-only; an independent
scan of all three RAC2 releases found 146 direct calls per release and no use
of the residual v0 before an overwrite or another call. The canonical definition
and visible callers now agree on `void(float *, int *)`; the written packed word
is preserved. This is an interface correction supported independently of the
desired instruction order. The contrasting `func_002AAA00` has explicit float
return paths and keeps that result even when a caller ignores it.

The real unused object formal of `func_00300048` is supported by repeated retail
caller setup. The 32-bit mode of `func_001261F0` is also documented by the public
[OpenGOAL interface](https://github.com/open-goal/jak-project/blob/78cde74d5addf8c787dc461ff9016c1d25300d48/game/graphics/sceGraphicsInterface.h).
These changes use existing source methods; no artificial argument use or new
compiler mechanism is involved. See [PR #364](https://github.com/OpenRAC/rac2-decomp/pull/364)
for the integrated checks.

The two independent witnesses were nonmatching when measured: `func_L00_003A2668`
was 1204/1204 bytes, 0/81 present placements, first difference +0x8.
`func_L23_0041D398` remains 1432/1432, 0/1; a real phase-lifetime split
instead gives 1412 bytes and a 0xC0 frame. Useful alternatives stay private.
These negative controls do not establish a general allocator failure or
justify repeating the same attempts without new evidence.

**Update, 28 October 2026 (pending review):** `func_L00_003A2668` is C in its own
unit, `src/levels/shared/L00_003A2668-ribbon.c` (default flags), and is placed at
81/81 (27 in each of US, PAL and US2;
[PR #348](https://github.com/OpenRAC/rac2-decomp/pull/348)).
`tools/build.py all --strict` passes in all three releases. `func_L23_0041D398`
is unchanged.

**Measured phase-storage remedies, 25 October 2026:**
In retained `func_L00_00398150`, the 96-byte collision query and later
attachment transform have disjoint lifetimes; their real union restores
the retail 0x1B0 frame, but 1,724/1,728 bytes remain 0/27 in each USA
release with game `-O2 -G0 -ffunction-sections` (PAL absent). In
`func_L06_003D64C0`, initializing the distance at its measured post-selection
phase restores 0x440 instead of 0x450; 5,692/5,868 bytes remain 0/1 in
USA v1.01 with game `-O2 -G8 -ffunction-sections` (other releases absent).
Keep the full collision arrays and matrix outputs. Neither observation
justifies padding or invented reference counts; reopen with independent
phase/CFG or floating-live-range evidence. [Retained C](https://github.com/OpenRAC/rac2-decomp/commit/e73fb043ed96233298f7aaf60854484c0046ee16).

Historically 148 of 240 notes mentioned allocation disagreements. A common signature was identical instruction order/size with different caller-saved registers, or an entry copy coalesced away. The approximate 250-byte threshold was a sample observation, not a compiler limit.

Named counterexamples now pass: func_L09_004081F0 and func_L12_0041BDF8 each 1/1; func_L17_003E6F20 1/1; func_L22_003A2CB8 2/2. Other examples included func_L01_00416B30(five unsuccessful attempts), func_L07_003F8C38(a declaration-order observation), func_L20_00444018, and func_L00_00409480. Their status is not inferred from these successes.

**23 October 2026 retained near miss:** `func_002F71B8` (356 bytes, boot plus 27 levels; game `-O2 -G8 -ffunction-sections`) remains unmatched after ten checker invocations across four plain-C forms. The best draft is exactly 356 bytes but 0/28 in USA v1.01, PAL and USA v2.00; each reports its first mismatch at +0x8. The five-word table copy, guarded call and three 12-byte record stores are recovered, while the prologue/base live ranges and initial register allocation still differ. Explicit SDA declarations produce the two GP-relative references in the size-exact draft; a no-SDA form was 348 bytes. Retained in `nonmatching/game/func_002F71B8.c`; reopen with a measured source-lifetime hypothesis, not artificial barriers.

**Further qualified lifetime remedies, 25 October 2026:**
`func_L00_004284B0` separates its initialization-only pointer from the
reloaded persistent state; `func_L00_00427BE8` forms its target
pointer where the copy and subsequent weight store actually use it.
`func_L02_003C0890` uses separate metadata, snapshot and flag views for the
three real child-pointer reloads. These are ordinary object/scope changes,
without register pins or artificial references. The latter body and
`func_L02_00348420` retain ordinary TImode transfers where their retail
scheduling requires them; replacing every vector assignment with `qcopy`
is not a remedy. All three releases accept their linked placements in the
84-program strict build.
[Qualified sources](https://github.com/OpenRAC/rac2-decomp/commit/3ba5ed46c8f1e03dd770bf80f181acf1f78de6e8).

**Real scratch storage and live inputs, 25 October 2026:**
`func_L20_00443B60` uses a 48-byte, three-row rotation basis alongside two
16-byte records. The old 16-byte basis under-allocated the real output by
32 bytes; the actual layout gives the retail 0xD0 frame and closes the
396-byte body without padding. `func_L20_00443790` supplies the object's
angles at `object + 0xF0` to the rotation helper, not the object base.
Scoped constructor results in `func_L16_004050D8` also close its allocation
while preserving the actual null-result store. These are measured source
and storage remedies, not general evidence that larger frames need padding.
[Qualified sources](https://github.com/OpenRAC/rac2-decomp/commit/bf60a47f1dacbbda3eb97762998188e3b4fd89ee).

The wave 8 allocator investigation remains useful: global.c prioritizes approximately floor_log2(n_refs)*n_refs/live_length, with loop-weighted references; cc1 -dl exposes refs/live_length. In two samples, changing actual references moved a saved-register assignment while 15 declaration permutations did not. Inspect real live ranges and distinct pseudos before editing reference counts. Several identical compiles justify stopping one approach, not declaring every other meaningful source/profile impossible.

**func_002A7470 (23 October 2026):** With `-O2 -G8 -ffunction-sections`, six plain-C forms reached a best 356/364 bytes and 0/28 placements in both USA v1.01 and USA v2.00; PAL has no catalogue row. The retained draft reconstructs the early helper, threshold guard and state updates, but its dynamic 16-byte-copy allocation and final table-byte access differ. A 360-byte form matched the `lq`/`sq` copy sequence but kept the animation index in `$s5`, expanding the frame from 0x40 to 0x50. **Next:** preserve the copy's pointer allocation while recomputing the animation index without a callee-saved live range. The size mismatch means the checker did not reach relocation-aware comparison.

**28 October 2026 requalification:** the retained 364-byte `-O2 -G8 -ffunction-sections -frac2-qcopy` candidate still matches 0/28 USA v1.01 placements; the first difference is at +0x20 in head register allocation. Its later copy and table-byte observations remain as recorded.

**Large state dispatchers (23 October 2026).** The retained
[`func_L22_002BF1B0`](../nonmatching/levels/func_L22_002BF1B0.c) now contains the
complete Dobbo Orbit state body: 147 selector values, 63 retail destinations and
all 135 distinct direct callees. Its 37,268-byte extent has one normal epilogue
and no external non-call branches; its size does not justify splitting the
catalogue or classifying it as handwritten assembly.

With the qualified game compiler/SN assembler and `-O2 -G8 -ffunction-sections`,
the first ordinary-local form compiled to 37,460 bytes with a `0x5A0` frame.
`-frac2-qcopy` tied; restoring whole-case retail order gave 37,464 bytes.
The state arms do not keep their temporary vector/probe pointers across common
tails, so a typed union can share their storage. This and an explicit entry
selector snapshot produce **37,280 bytes, 0/1 USA v1.01 places**, warning-free
with `-Wall -Werror`. The frame is `0x1A0` against `0x1B0`, with six saved FPRs
against five; register/block allocation and the emitted 588-byte switch table
still differ or remain unqualified. No PAL/USA v2.00 row carries this name.

The next useful experiment is the actual resident-object field model and saved
object lifetime, followed by complete switch-table placement. Do not add padding,
duplicate extern aliases or artificial references to close a size difference.
Preserve the measured 48-byte probe and 64-byte matrix outputs and the live
integer/FP inputs and return values; several older helper declarations omit
them. A compiled complete draft and a small size delta are neither a byte match
nor a runtime validation.

**25 October allocator follow-up:** `tools/regalloc.py` confirms identical normal
and dump-enabled objects for this retained body. The entry-object pseudo has
11 references, a 7,229-instruction live length and crosses 801 static call sites;
it is not assigned a hard register. One resident-high pseudo has 51 references
over 4,032 instructions and takes `$s6`. These are dump observations, not dynamic
execution counts. Typed-object and field-at-use variants and the bounded loop/
scheduling options did not close the body; the best remains 37,280/37,268 bytes.
The three-function address follow-up adds no C match. Keep the retained body and
reopen with independent object/lifetime evidence, not fabricated reference counts.

**Complete table topology recovered, 25 October 2026:** the previous 588-byte
compiler-owned table had 147 relocations but only 62 destinations. It merged
selectors `0x3C`/`0x64` with `0x60`/`0x61`, although retail keeps their two
clear-state blocks separate. Following RAC1's
[real tail-layout method](https://github.com/OpenRAC/rac1-decomp/blob/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec/docs/DECOMP_PROGRESS.md#two-exits-that-end-the-same-way-get-cross-jumped--arm-order-decides),
repeating the actual two final tests/stores, in order, before returning from
the first clear-state arm restores all 63 destination equivalence classes.
No operation is added to a runtime path. The complete table has 147 self-text
`R_MIPS_32` relocations and 16-byte alignment. An independent object parse
confirms the complete selector partition.

That structurally faithful form measured **37,336/37,268 bytes,
0/1 USA v1.01 places**; the other canonical release identities are absent.
Its table addresses and text do not match, so it is not linked or credited.
The frame remains 0x1A0 rather than 0x1B0, with six saved FPRs rather than five,
and the original object pointer still spilled. The former 37,280-byte baseline
and useful alternatives remain private. `-fno-thread-jumps` did not fix the
merge; this compiler rejects `-fno-crossjumping`. Next: identify the real
address temporaries competing for `$fp` and their phase lifetimes while
preserving the recovered topology. A smaller size delta is not a better
reconstruction when it loses a measured control-flow distinction.

**Resident-field and predicate follow-up:** the retained form is now
**37,308/37,268 bytes**, still 0/1 USA v1.01 and absent under the other canonical
release identities. A partial resident view of the actual float at `+0xA2C`
and signed halfword at `+0xADC`, together with capturing the combined pose
predicate before the path calls, restores the entry object to `$fp`. The
configuration-table read remains unconditional. Its twelve references and
all actual field reloads are preserved; no extra reference or padding is added.
The isolated field and predicate controls do not recover that allocation.
All 147 selector slots retain the 63 retail destination classes, complete
588-byte table and self-text relocations. The frame is still `0x1A0` versus
`0x1B0`, with six saved FPRs versus five; entry-load order, real workspace
lifetimes and later address/scheduling differences remain. Investigate those
measured residuals rather than repeating the archived whole-object views.

**Large Snivelak and Oozla source remedies, 25 October 2026:**
`func_L16_0040ECC0` captures the actual yaw-field pointer before its eight
angle calculations. This restores the observed object/state/constant register
roles and 0x90 frame; that corrected baseline measured 6476/6484 bytes.
The retained follow-up is **6464/6484 bytes**, still 0/1 in each USA release,
with PAL absent. Three `MACRO_ADDR` declarations restore the observed mixed
address forms. A partial sound-anchor view keeps the actual owner pointer
at `+0x88` and active byte at `+0x74`, independently of the 112-byte index
stride; it does not claim an array element extent. Real sound phase scopes,
the projectile-result lifetime joined to one store, positive-first state4
guard and state19 set/clear order retain the measured operations and unordered
behavior. The first aligned operation difference moves from `+0x25C` to
`+0x568`; state3 joins, FP scheduling and later allocation remain unresolved.
Private diagnostic branch mapping still leaves seven targets unproved and
cannot substitute for exact text or linked table equality.
`func_L16_00403900` represents the four
observed firing phases and two bone sites explicitly, instead of the old
shared loop skeleton: 2816 becomes 4396/4444 bytes with the real 0x80 frame.
It remains 0/1 USA v1.01, with the other identities absent. Seven ordered
floating guards and three helper-return contracts were independently corrected;
`!(x < y)` must not be silently replaced by `x >= y` on an unordered input.
`func_L16_0040D258` remains 660/656 bytes and 0/1 in both USA releases.
Its AAA00 declaration is unused in the body: changing that declaration is
not a causal explanation of its generated instructions.

The Oozla body `func_L01_003B5878` is 4968/4972 bytes with the real 0x150
frame, 0/1 in both USA releases and PAL absent. It preserves measured mixed
absolute/GP reads of one mutable frame counter, actual raw-word snapshots,
complete matrices and the dispatcher's 64-bit return; only its low flag bits
are consumed. The corrected AAA00 return declaration alone is object-neutral
here. Separate scalar locals after the complete vector/matrix workspace recover
the retail F21 zero across the scale call, duration store and comparison at
`+0x270..+0x2F8`, with unchanged measured scalar slots and frame. A single
`MACRO_ADDR` frame-counter declaration recovers the absolute read at `+0x6C4`
and GP read at `+0x99C`; the old explicit SDA alias forced both reads to GP.
Neither improvement changes the nonmatching status: airborne F0/F1 roles,
branch layout, target-address lifetimes and final easing setup still differ.
Keep the useful alternatives private and reopen these bodies with the measured
field/address and phase-lifetime evidence, not equivalent source permutations.

The shorter retained `func_L00_003A2258` is still 420/420 bytes: its first
pointer has 7 references over a live length of 60, versus the index's 9 over
114. The ordinary and diagnostic objects agree, but the first-input/index
roles still take the wrong saved registers at +0x3C. Earlier increments and
non-clobbering local copies did not close that allocation. In
`func_L00_003A8670`, a measured 112-byte record and explicit configuration
branches improve 364 bytes to the retail 356; column/index association and
three address/schedule words remain different after the matching prefix
through +0xFC. Neither equal size nor a neutral allocator-dump build is a match.

<a id="blocker-02"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L16_0040D258` is C in `src/levels/16_snivelak/L16_0040D258.c` (`-O2 -G0 -ffunction-sections -fno-sched-interblock`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

## 2. LICM: the retail re-materialises a base inside a loop

**Signature:** retail emits `lui $r,%hi(D)` + `lw`/`addiu` *inside* the loop body; cc1 hoists the address into a callee-saved register, so the loop loses an instruction, the 8-byte alignment `nop` before the label disappears, and the frame grows by two saves.

**Measured:** `for` and `do/while` both fold. Those tested loop forms did not move the original attempts. Later source/profile remedies mean this is not a universal impossibility claim; wave 8 recorded the two observations below.

`__attribute__((sda))` in a `-G0` file on an **absolute** symbol stops the hoist: `lui %hi ; lw %lo` stay inside the loop as retail has them (side effect: the prologue's index/base register pair swaps). And there is a sub-case of its own: an **absolute global addressed in a loop that contains calls** - cc1 hoists the address into a callee-saved register (`lui $s1,%hi`, frame 0x20, two extra saves) where retail re-materialises `lui $v1,%hi ; lw $v1,%lo($v1)` at every iteration with one register (`func_L11_00440868`, one instruction off; `func_L11_004411C8`, 8 bytes off - bodies otherwise identical instruction for instruction). In those tested units the attribute produced an unwanted `$gp` form; qualify the actual unit instead of generalizing the declaration rule.

**28 October 2026, `func_L11_004411C8` closed (DrLegitamate, USA v1.01, 1/1 place, `tools/build.py level 11 --strict` OK):** the loop-with-calls sub-case above yields to the incomplete-array `sda` alias from COMPILER-NOTES.md. Declaring the class table base as `extern u8 *D_L11_001B359C_base[] __asm__("D_L11_001B359C") __attribute__((sda));` and reading `D_L11_001B359C_base[0]` inside the loop gives retail's per-iteration `lui $v1,%hi ; lw $v1,%lo($v1)` with no hoist and no extra saves in the `-G0` unit; the head then needs the list in its own variable (`list = table[index]; if (list == 0) return; p = list;`). The same declaration is the next experiment for `func_L11_00440868`.

**25 October 2026, saved-pair swap closed by block scope (measured, `func_L00_003EB400`, 528 bytes, 2/2 places):** the remaining disagreement was `$s1`/`$s2` only - retail kept the actor pointer in `$s1` and the precomputed `i + 1` in `$s2`, cc1 the other way. Declaring the loop index **inside the `if` block that owns the loop** (`if (state == 1) { int i; for (i = 0; i < 4; i++) ... }`) instead of at function scope reproduces retail's pair, because the parameter copy then sorts below the loop's live-across-call temporary. In the same body a named `char *row = (char *)state + i * 4;` before `id = *(int *)row;` gives retail's `addu $s0,$s4,$v0` operand order where the inline indexed read gives `addu $s0,$v0,$s4`. Both levers together closed the function; keep the block-scoped index for any similar 4-iteration loop whose counter lands in the wrong one of `$s1`/`$s2`.

<a id="blocker-03"></a>

## 3. If-conversion

**Signature:** a trailing `if (X) r = 1;` in an if/else chain comes out as `sltu`/`xori`/`sltiu`/`movz` where retail keeps `beql`/`bnez` plus the assignment in the delay slot; or `if (X) return A; return B;` folds to `movn` where retail keeps the branch.

**Workarounds that worked:** a `switch` keeps the retail shape in some bodies; `if (...) goto done;` with one shared `done:` label keeps two separate compares where `&&` folds them into a range test; `if (c) GLOBAL = A; else GLOBAL = B;` (two memory stores) keeps the branch where the local-variable form is if-converted.

**What is not if-converted:** `movz`/`movn` are emitted by this cc1 (`c ? a : b` gives `movz $2,$5,$6`, `if (b) r = 0;` gives `movz $2,$4,$5`), so a retail body that uses them is reachable - the shape to try is section 16's, not a constant selection.

**23 October 2026 linked C qualification:** `func_L00_003266D8` stores the incremented
counter before clamping it with a second conditional store. This meaningful source
shape preserves retail's branch and both stores, unlike the earlier ternary's
conditional move. A dedicated `-G8` unit passes `check.py` at 27/27 placements in
USA v1.01, PAL and USA v2.00. The two absolute/SDA aliases are checked to bind the
same respective words at every placement. The combined tree passes all 84 strict
program builds; the placement count does not multiply distinct-function credit.

<a id="blocker-04"></a>

## 4. `nop` before `jr $ra`

**Scope:** these load/return/label observations are separate from the resolved mfc1 case (section 15) and the qualified `-mastra-split-trunc-slot` profile (PR #184). A historical volatile experiment is not authorization to invent a memory effect for matching.

**Signature:** retail has a residual load-delay `nop` then fills the branch slot (`lwc1 ; nop ; jr $ra ; mul.s`); the pinned compiler emits the compact three-instruction form. A single-word discrepancy; reachability requires actual control-flow evidence.

**Not always a wall:** `*(volatile TI128 *)out = *(TI128 *)p0;` makes the two missing `nop`s reappear in the two early-return delay slots - measured on the three members of the family `2ae8dc3c64a3dcc0`: 280 bytes without, 288 (exact) with.

**A second form of the class stays a wall:** on `func_L02_00411530` the missing `nop` is a **cop1 latency fill between `mtc1` and `sub.s`**, and retail places the join label *before* it while cc1 glues the nop to the reload. Twenty-nine source variants tested, none moves the label.

`func_00282848`'s corrected 16-byte body is another instance of the first
form: `lwc1 $f0,-0x76E4($gp) ; nop ; jr $ra ; mul.s $f0,$f0,$f12`. Its C
candidate has the same 12-byte missing-nop result as the previously measured
`func_L00_002EDCB8` family; the catalogue prefix correction does not change
that compiler blocker.

**29 October 2026 follow-up:** `func_002828B8` also remains a 12-byte candidate
against its 16-byte extent under isolated `-fno-schedule-insns2`. It retains
`lwc1 $f0,0($gp) ; jr $ra ; mul.s $f0,$f0,$f12`, so this later scheduler pass
does not restore either retail's load-delay `nop` or its `-0x76E0($gp)` offset.
The same isolated profile leaves sibling `func_002828F0` at 12/16 bytes and
0/1, with `0($gp)` instead of `-0x76DC($gp)` and the same compact sequence.

**28 October 2026 follow-up:** retail's `func_00282890` sequence loads
`D_001A790C`, seeds the COP1 accumulator with `0.25f + 0.25f` via `adda.s`,
then computes `ACC + (float)a0 * D_001A790C` via `madd.s` before conversion.
The resulting C expression, `(int)((float)a0 * D_001A790C + 0.5f)`, is
semantically supported by the decoded instructions. In the proper `-G8`
sibling it compiles to 44 bytes against retail's 40 and matches 0/1: cc1 emits
separate `mul.s`/`add.s`, directly materializes 0.5, and references the global
at `0($gp)` rather than `-0x76E4($gp)`. `__builtin_fmaf` instead emits an
80-byte helper-call sequence. Keep the marker; the accumulator schedule and
small-data reference remain unresolved, and these probes do not justify
`ASM_FUNC`. A 28 October 2026 `-ffast-math` check does expose `adda.s` and
`madd.s` and corrects the GP-relative load, but the 0.5f expression still
measures 44/40 bytes and seeds the accumulator from 0.5f; spelling the offset
as two `0.25f` additions measures 48/40 bytes. Adding `-fno-schedule-insns`
to the 0.5f form leaves its 44-byte output unchanged. No tested C form matches
the retail ordering. The same operation appears at `func_002828C8` with
`D_001A7910`: its corrected semantic C probe also measures 44/40 bytes, 0/1,
with the same separate arithmetic and `0($gp)` load in place of retail's
`-0x76E0($gp)` reference. A 28 October 2026 `-ffast-math` probe for this sibling
is also 44/40 bytes and 0/1; it exposes `adda.s`/`madd.s` and fixes the
GP-relative displacement, but seeds ACC from 0.5f and schedules that constant
before the global load. The explicit `(x * D + 0.25f) + 0.25f` form measures
48/40 bytes. `func_00282900` repeats the same result for
`D_001A7914`, with retail `-0x76DC($gp)` and a 44/40-byte, 0/1 semantic C
probe. The 28 October 2026 `-ffast-math` probe is 44/40 and 0/1; the explicit
`(x * D + 0.25f) + 0.25f` form is 48/40. It exposes the accumulator
instructions but does not match the retail order or size. A 29 October 2026
`__builtin_fmaf((float)a0, D_001A7914, 0.5f)` probe in the actual `-G8`
sibling compiles to 80/40 bytes and emits unresolved helper calls instead of
the retail EE accumulator sequence; the temporary unit edits were restored.

<a id="blocker-05"></a>

## 5. `nop nop` before `div.s`

Several historical attempts lost two nops before float division. This is not uniformly unreachable today: compiler notes describe qualified division-padding rules and a separate debug-label remedy. `func_002B5EF8` uses a dedicated `-g` unit with division on its own source line, allowing gas to reproduce label-related padding.

`func_L00_003DB0A8` is another plain-C witness for the debug-label route:
its real integer-to-float helper is `func_00283CE0(int)`, followed by division
on its own source line and `func_00283CF0(float)`. The default profile emitted
100/108 bytes; a dedicated `-O2 -G0 -ffunction-sections -g` unit passes 27/27
placements in each release, followed by all 84 strict program builds of the combined tree.

Other division/label-boundary failures remain bounded near misses. Retain exact source, line layout and profile; do not add dummy instructions or manual padding.

**23 October 2026, retained near miss:** `func_002A88A0` (default game -G0, 264 bytes, 28 placements in each release) has a 244-byte plain-C draft; four source forms matched 0/28 in USA v1.01, PAL, and USA v2.00. Its non-NOP instruction sequence aligns after accounting for relocated calls and branch displacements, but retail has five extra `nop` words around three divisions. The cause is unknown and may not be the label-padding case above. Reopen with compiler/source-shape evidence; do not add artificial barriers. The marker is restored and no full build was run.

`func_L00_003A2408` provides another control: the complete reconstructed body is
348/356 bytes with the default profile, differing only by the two pre-division nops.
Putting the conversion call and division on separate C source lines in a dedicated
`-g` unit gives 27/27 checks in each of USA v1.01, PAL and USA v2.00. The combined
tree passes all 84 strict builds; this is an existing debug-label mechanism.

**23 October 2026 linked C qualification:** `func_L00_0031C3D0` passes `check.py`
at 27/27 placements in each of USA v1.01, PAL and USA v2.00 in its dedicated
`-O2 -G0 -ffunction-sections -g` unit. The debug labels account for the two
missing pre-division nops. The retained draft also needed the real integer
conversion ABI, an initialized interpolation fraction, distinct vector arguments
and the boolean return value. Its former allocation mismatch was not a compiler
impossibility. The combined tree subsequently passes all 84 strict program builds.

<a id="blocker-06"></a>

## 6. Switch tables that travel with the function

Five early-wave bodies passed quick checks but failed full placement with “needs .rodata at its place, which is not C.” This was a linker-placement limitation, not evidence that ordinary C switches cannot match. A named retail table is different: its dispatch match alone does not validate every computed-goto target or internal case-label placement.

Historical control, 24 October 2026: `func_L04_004323F8` (312 bytes) and
`func_L04_00432530` (224 bytes) each pass 5/5 local placements in all three releases,
but actual USA strict builds reject their generated `.rodata` dependencies.
An object-dependency audit found the same issue in `func_L19_00421E80` (760 bytes),
whose local USA checks pass 1/1 in each USA release; an actual USA level19 strict
build confirmed its rejection. PAL has no catalogue entry for that name.

**Compiler-owned branch tables:** `tools/build.py` now derives a complete
`.rodata`/`.rdata` input section's address from its C text relocations, checks every
table word against the independently placed C case destination, and links that
original compiler section in place of the corresponding retail data span. It
preserves surrounding assembly data and its labels. Section dependencies are
scoped to their object, so an unrelated object's `.text` cannot satisfy a binding.
Overlapping claims, unsupported relocations, missing destinations, scalar pools,
mixed data and incomplete spans remain rejected. No compiler instruction, table
entry or source-level switch is patched. Full strict loaded-byte comparison is
still the acceptance gate.

This follows RAC1's
[table/data interleaving](https://github.com/OpenRAC/rac1-decomp/blob/de14440819093b81c00a1e219d4fef54d6fccd16/tools/jump_tables.py)
principle. RAC2 uses existing object relocations instead of renaming compiler
assembly sections or committing an address registry. The two color conversions,
Grelbin's `func_L19_00421E80`, format dispatch `func_00118CC8` and DWARF interpreter
`func_00123D30` are the qualification witnesses. The format dispatch needs game
`-O2 -G2 -ffunction-sections -mastra-quad-saves`; the current parent unit's SDK
profile emits a different body. Its own ordinary C translation unit records that
profile in `config/cflags.txt`.

All five witnesses are integrated as C: 2,420 distinct primary code bytes.
Qualification passes all 84 strict programs (boot plus 27 levels in USA v1.01,
USA v2.00 and PAL), with equal loaded bytes and no assembly fallback, plus 171
tests. The colors pass five placements each per release; Grelbin passes its one
placement in each USA release and is absent from PAL; both core functions pass
their boot placement in every release. Generated progress reports are unchanged.

**Additional switch candidates:** the retained Joba converters
`func_L11_0043E090` (116 bytes) and `func_L11_0043E108` (148 bytes) illustrate why
instruction equality alone is insufficient: their old C bodies matched, but
their generated tables sent several indices to the wrong return-value arms.
Table qualification rejected both with inconsistent text-section bindings.
Correcting the ordinary C `case` labels preserves the instruction layout while
reproducing the actual dispatch mapping; neither table words nor case addresses
are patched. Their separate translation units preserve retail's spacing between
tables without adding source padding. The shared message selector
`func_L02_004114A0` (144 bytes) also brings a branch table, rather than a scalar
lookup pool, and needs no additional build mechanism.

These three functions are integrated with 408 additional distinct primary code
bytes. The shared selector passes seven USA v1.01 placements and is absent under
that name in USA v2.00/PAL; each Joba converter passes one placement per release.
All 13 function/table placements are linked and audited. The full 84 strict
program builds, 171 tests and all three progress checks pass; reports are unchanged.

This supports complete input sections, including several tables when their
original relative layout agrees. It does not split a mixed compiler section,
repair a switch comparison tree, change arm order, resolve register allocation
differences, or grant blanket acceptance to legacy external case-label arrays.

A switch's comparison tree is also a separate source problem: func_L19_00423CC0 resisted the tested case permutations, whereas explicit comparisons/gotos matched func_L20_00442C10. Wave8 associated one tree form with three labels, one sharing default; this is a bounded recipe.

Historical boot candidates func_00119BF8(3072 bytes, table 0x13A7B0) and func_00118D98(3368 bytes, table 0x13A6C0) remain markers. The recorded binary comparison distinguished their vfprintf-family implementation from the public newlib tree: PRINT used memcpy/writer calls instead of iovecs/sprint; cvt returned via a static buffer rather than a digit pointer; the observed Inf/NaN strings differed. func_001185E8's attempted reconstruction was 1508 versus 1496 bytes. These are historical implementation clues, not permission to use prohibited SDK sources or headers.

**24–29 October 2026, shared record lookup:** `func_002F6510`'s retained
semantic switch remains a 244/248-byte near miss under game `-O2 -G8
-ffunction-sections`, with 0/28 placements in each release. Six checker
invocations (no scratch compiles) measured 232-byte raw-index, 264-byte
duplicated-call and 244-byte shared-call forms. A 29 October direct-mode switch
(mode 2 by default, mode 1 in the selected cases) compiles to 196/248 and
0/28; it removes the later selection branch but changes the shared tail and
register layout. A named-table computed-goto probe did not preserve retail arm offsets
+0x60/+0x64; the retained semantic switch in `nonmatching/game/func_002F6510.c`
avoids that invalid binding assumption. Root/index lifetime and address setup
still differ. Reopen with independent type/lifetime evidence and exact arm
layout; neither generated switch data nor linking has been qualified.

**Complete constant pools, 25 October 2026:** the same interleaving principle
now retains complete relocation-free `.rodata`/`.rdata` sections. Their base is
derived from that object's accepted text relocations; every byte and padding
byte, alignment, allocated non-executable retail owner and non-overlap must
agree. A real ELF-parser regression checks section flags, not only handcrafted
metadata. The two public libgcc modules and the formatter provide the witnesses:
`func_0011FC68` (1,772 bytes), `func_00121450` (1,640) and `func_0011C090` (360),
one boot placement each per release. Their 256/256/48-byte pools are unchanged
compiler input sections; all 84 strict programs pass. Mixed relocated/scalar
pools, `.sdata` and unsupported assembly data directives remain rejected.

<a id="blocker-07"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L19_00423CC0` is C in `src/levels/19_grelbin/L19_00423CC0.c` (`-O2 -G0 -ffunction-sections`), placed at 1 US, 1 PAL, 1 US2 places. The measurements above are kept as history.

## 7. Annulled integer branch delay slots

Historical mismatches involved bnel/beql with a taken-path slot where retail used a normal branch and fall-through work, often one word different. The wave 9 correction counted 342 then-matched functions containing a likely branch: the compiler does emit them from ordinary C. That count is historical, not today's corpus size.

Hoisting genuinely shared work before the condition changed slot selection in some bodies. It is a measured source lever, not a guarantee that every likely branch can be rewritten to a normal one. Five workers had previously discarded 9, 10, 11, 14 and 15 targets using that signature alone; those exclusions were not justified without exact decoding/profile checks.

Integer BEQL/BNEL execute the slot on taken paths and annul it on non-taken paths. The earlier unconditional/inverted-slot claim is withdrawn. This was checked against the [official PCSX2 R5900 interpreter](https://github.com/PCSX2/pcsx2/blob/0f71e668b8adc950db7de1b1b15c2f5080c102e9/pcsx2/Interpreter.cpp#L387-L410), not a new hardware experiment. Do not generalize this statement to a differently decoded instruction.

**28 October 2026, retained near miss:** `func_002958B8` (USA v1.01, 344 bytes,
boot and 27 levels) is 336/344 bytes and 0/28 in the current source unit. The
scan loop still emits a plain `beq` where retail uses `beql` with the index
delta in its annulled slot. Rewriting the pointer walk as a counted `for` loop
or a pre-incremented `do` loop leaves the same 336-byte output. A separate
`long long` delta trial changes the size to 352 bytes, and a 32-bit update
expression assigned back to that value gives 372; neither is a match. The
retained candidate records the other delay-slot and prologue differences.

**29 October 2026 current-master replay:** `func_00118460`'s retained
pointer-induction candidate is 100/112 bytes and 0/1 under an isolated game
unit with `-O2 -G2 -ffunction-sections`. It uses `$a0` instead of retail's
`$v1` from +0x08, and emits `bne` plus a separate `bgtz` loop back edge rather
than retail's `beql` with the zero store in its delay slot. A nested equality
form (`if (*p == '9') *p = '0'; else { *p += 1; return *p; }`) compiles
byte-identically to the retained candidate. Recomputing `buf + len` inside the
loop measures 116/112 and peels the loop; returning directly from the first
non-nine case was previously measured at 96/112. The source was also replayed
in its original SDK unit (`sdk -O2 -G2`), with 0/1 and different instruction
allocation. The entry's early branch targets the final return-1 block inside
this function, not a sibling. A new condition-led carry loop
(`while (count > 0 && *--p == '9')`) emits retail's `beql` with the zero store
in its delay slot, but expands to 136/112 bytes and remains 0/1 because it
duplicates the count and character checks. No strict linked match is claimed.

<a id="blocker-08"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_00118460` is C in `src/core/00118460.c` (`-O2 -G2 -ffunction-sections`), placed at 1 US, 1 PAL, 1 US2 places; `func_002958B8` is C in `src/game/00294BC8.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places. The measurements above are kept as history.

## 8. Single-register `%hi`/`%lo` addresses

**Signature:** retail may use base == destination, a separate address register, a `$at` macro, or `$gp`. Declaration type/size, unit flags, cc1 output and assembler macro context all participate. Earlier waves inferred contradictory universal rules from different units; those universal rules are withdrawn.

**Measured levers:** scalar/array forms, complete/incomplete array size, sda/nosda, a -g8 sibling, and per-file -mno-split-addresses. Check every existing C function using an affected declaration: historically one attribute change turned an existing 2/2 into 0/2 and was reverted.

The historical sample is retained: 47 of 240 notes mentioned gp/sda/G8; one 23-target survey used 11 plain-G0, six G0+sda and six G8 units. Those counts are not a selection algorithm. Inspect relocations and retail accesses. GP is 0x001AEFF0 in boot and levels; a small-data declaration needs a known eligible size.

**Current witnesses:** func_L05_0030C930, formerly listed as unresolved, is C, as are func_L05_00444D60, func_L00_00427290 and func_L00_002E73E0. PR #246's func_L20_00444138 passes 1/1 in its dedicated G8/mno-split-addresses unit with separate sda/nosda declarations for one measured bound.

**28 October 2026, retained near miss:** `func_002CC528` is 40 bytes in its
`-G0` unit. The saved candidate and two source-shape variants (declaration
order and direct conditional store) retain the same allocation: retail's
`movn` selects in `$a1` using `$v1`, while the candidate selects in `$v1`
using `$a1`, then stores `$v1` instead of `$a1`. A dedicated `-G8` replay is
32/40 bytes. `tools/check.py func_002CC528 --diff` reports 0/28 placements
for these attempts; the C remains in `nonmatching/game/func_002CC528.c`.

Two documented names may express different addressing forms of one real global. They must derive the same true identity; malformed names, invented addresses or aliases hiding inconsistent bindings are not remedies. PR #244's review corrected such naming defects. Use ref_LNN_XXXXXXXX_kk where a target's identity genuinely varies by placement, not as a substitute for a known correct data name.

**24 October 2026, one declaration for both forms at -G0 (wave 10):** in the level-08 twins `func_L08_0042F440`/`0042FAC0`, `extern s32 D_L08_001B3AA0 __attribute__((sda));` under the file's `-O2 -G0` emits `lui`+`%lo` in ordinary flow and the single `$gp` form inside a `jal`/branch delay slot. Retail's body shows exactly that mix for the same word (absolute `lui a0`/`lw a0` for the increment, `lw`/`sw 0x4AB0($gp)` in two slots), so one sda declaration covers it: no -g8 sibling and no second name were needed. This does not contradict the -G8 `func_002721C8` note below, where the same attribute gives GP throughout; the threshold/profile decides. The lever did not close these two bodies' residual setup order.

**24 October 2026, retained near miss:** `func_002721C8` (game `-O2 -G8 -ffunction-sections`) is 176/184 bytes and 0/28 placements in each of USA v1.01, PAL and USA v2.00. A typed partial camera-state view recovers the 0x30 frame and saved registers; a raw byte view was 168 bytes and a `nosda` scalar grew to 200. Retail uses absolute address/first-load forms and a later GP read of the same scalar, while the retained single canonical SDA declaration uses GP throughout. Six checker invocations, no scratch compiles; size mismatch prevents relocation-qualified binding checks. The actual C is in `nonmatching/game/func_002721C8.c`, with its source marker restored. Reopen with evidence for the real scalar storage/declaration and its two addressing forms, without duplicate invented identities or scheduling barriers.

A bounded `-mno-split-addresses` trial for `func_L00_00396288` and
`func_L00_00392530` fails in the qualified GNU assembler with the internal
assertion at `tc-mips.c:11867`. The retained drafts use their ordinary profiles;
this is a failure of that tested path, not evidence of handwritten game code
or a reason to rewrite the output instructions.

<a id="blocker-09"></a>

## 9. Folded addresses where retail materialises the base

**Qualified route:** [PR #262](https://github.com/OpenRAC/rac2-gc-decomp/pull/262) adds the default-off per-file `-frac2-qcopy`
profile for aligned TImode C assignments. It keeps addresses in registers and
groups `lq`/`sq` with a declared temporary; memory flags/alias sets are retained,
unaligned accesses take the ordinary path, and no source asm or memory barrier
is added. `func_L20_0039E158` (140 bytes) and `func_L20_0039F210` (32 bytes) now
match completely. Default folded copies remain intact. Three improved near
misses still differ in ordinary allocation/scheduling; the profile is not an
automatic match for all historical candidates. Issue #248 records the full
scope. All 28 programs pass --strict and all 71 tests pass in the final tree.

**Signature:** retail `addiu $v1,$base,N ; lq/sq $v0,0($v1)` where cc1 folds to `lq $v0,N($base)`. One instruction, and it drags the register allocation with it.

**Helper route reopened on 25 October 2026:** `qcopy(dst, src)` / `qzero(p)` from
`include/common.h` force the address into a register and are now approved shared
helpers under `AGENTS.md`. Their real memory effects still need source/ABI and
strict linked qualification. Seventeen bodies that had been landed with helpers
were removed under the earlier policy on 2026-10-13
and their retained drafts require fresh qualification under the approved helper policy.
The historical `mode(TI)` and aggregate/`memcpy` experiments did not reproduce those
transfers; those failures do not rule out the now-approved helpers. A sibling shape was re-confirmed on the `func_L00_003B0AB0` / `B0A28` / `B0CE8` family in wave 8: retail keeps `lui %hi(D) ; addiu %lo(D) ; addiu rd,rs,CONST` with the constant in a **separate** `addiu`, and all seven source forms tried (`D+0xC+idx*0x1C`, `(char *)&D[idx*0x1C]+0x10`, `((char (*)[0x1C])D)[idx]+0x10`, a local base, ...) folded `D+CONST` into the `%lo`. Those seven forms did not close that family; this is a bounded result, not a proof about every legal source form.

**25 October 2026 helper and lifetime follow-up:** nineteen functions totaling
7,580 distinct C bytes pass all 84 strict program builds across USA v1.01,
USA v2.00 and PAL; all 162 carrying placements use C without fallback.
Catalogue absences are recorded separately, not counted as checks or matches.
[Qualified source and retained reconstructions](https://github.com/OpenRAC/rac2-decomp/commit/f8236cfde5556b48cb745ba3907af9d8c94b1c8f).
The approved helpers recover complete transfers without guessing local extents.
`func_L23_00428490` keeps its measured 144-byte packet and sixth integer argument;
`func_L07_003F8010` needs a single 64-byte affine matrix, rather than separate
48-byte and 16-byte locals. The ribbon drafts `func_L00_003973E8` and
`func_L00_00395A88` now copy all four components on the zero-length ray path;
the old drafts copied only the last two. Their 1480/1488 and 1508/1516-byte
results were near misses then, with loop lifetimes and saved-register allocation
still different. The allocator diagnostic reproduces the ordinary compiled
objects; it measures interference and priorities, not semantic correctness.

**Update, 28 October 2026 (pending review):** both ribbon functions are C, each in
its own unit (`src/levels/shared/L00_003973E8-g8.c` and `L00_00395A88-g8.c`, flags
`-O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-hazard-labels`),
at their full 1488 and 1516 bytes, placed 27/27 in each of US, PAL and US2
([PR #348](https://github.com/OpenRAC/rac2-decomp/pull/348)).
`tools/build.py all --strict` passes in all three releases.

Copy independence includes later writes: the fourth matrix row in
`func_L23_0042A018` and `func_L23_0042A8C0` is followed by a write to its W
component, so it uses clobbering `qcopy`. Only the first three independent rows
use `qcopy_nc`. Rechecking this repair leaves the measured object bytes
unchanged; equality alone would not have justified the weaker memory contract.
The existing `func_002B5678` definition also now declares the unused fourth
scratch-pointer slot supplied by its C caller. The retail body does not read
that input; no dummy use or instruction is added.

Two residuals need source evidence, not padding or instruction rewriting:
`func_L18_003FD630` is 252/252 bytes with a 0x90 frame instead of 0xF0;
only four input control vectors are established, so an extra 0x60-byte local
would be unsupported. `func_L18_002CFF48` is 504/504 bytes and agrees through
+0x194; a plain branch at +0x198 differs from the retail likely branch, with
a different global-mode temporary. Duplicate calls worsen it to 520 bytes;
natural switch/goto forms tie. Reopen with independent storage or conditional
lifetime evidence. Final profiles, release coverage and reopening conditions
remain beside the retained C in `nonmatching/`.

**24 October 2026 linked C qualification:** `func_00270D50` (220 bytes) passes 28/28 placements in each of USA v1.01, PAL and USA v2.00 in its dedicated `-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier` unit. The default profile gave 204 bytes; qcopy alone recovered retail size but still moved address/call setup and restores across the copies. The existing barrier profile reproduces the complete body without a source barrier. The C keeps the camera fields within the canonical `D_L00_001B8C80` object and the established six-pointer `func_00270B58` interface; the helper also passes 28/28 checks per release. All 84 strict program builds pass with the candidate linked, without C fallback. This is one distinct function, not one per placement.

**24 October 2026, barrier-profile near-miss requalification:** five retained near misses whose notes named the missing inline-asm copy barrier were closed by moving them to dedicated `-frac2-qcopy -frac2-qcopy-barrier` units: `func_00270EA8` (56 bytes), `func_00270E30` (116), `func_00302A20` (100), `func_003353C8` (88) and `func_002AD6F0` (196). Before the barrier they were one restore or one copy-address allocation away: `func_002AD6F0` was 195/196 bytes, `func_00270E30` 112/116, `func_00302A20` 97/100, `func_003353C8` 88/88 with the epilogue restore hoisted above the copy, and `func_00270EA8` 56/56 with only the copy-address registers wrong. Each passes 28/28 in USA v1.01, PAL and USA v2.00, and the existing `func_002718B8` in the shared `0026EA00-qcopy` unit still passes. The retained drafts are removed once the linked build confirms them.

**24 October 2026, second barrier requalification:** four more reserved near misses close with the same profile: `func_002BB838` (236 bytes, 28 places in all three releases), `func_00313678` (84 bytes, 28 places in all three), and the boot-only twins `func_00304AD0` (148) and `func_00307298` (148), each 1/1 in USA v1.01 and USA v2.00 with no PAL catalogue row. `func_00313678` additionally needed the source to keep the copy source in a `char *` local while the call passes the same pointer; qcopy alone folded the load. The G8 twins needed the barrier to reproduce their first-call argument setup.

<a id="blocker-10"></a>

## 10. Equal-address branch folding

**Signature:** two case arms whose addresses are algebraically identical (`base+idx*4+0x210` vs `base+(idx-0x14)*4+0x260`) are merged by cc1 into one; retail keeps both branches. The recorded forms did not preserve both arms; this observation alone does not establish universal impossibility.

<a id="blocker-11"></a>

## 11. MMI and undecodable words

`func_002A0A28` has a retained review observation about working-register `$at`
use and trapping arithmetic. The proposed `nonmatching/` file contained only
that note, not a C reconstruction, so the observation belongs here instead.
The `INCLUDE_ASM` marker is unchanged: instruction-set/control-flow review and
the handwritten-assembly acceptance rule still apply before `ASM_FUNC` credit.

**28 October 2026 current-master review evidence:** `func_002E31E8` is a 376-byte
body in the boot and 27 level placements. Its retail body uses `$at` as a live
table cursor, `lqc2`/VU0 vector arithmetic/`qmfc2.ni`, and trapping `addi`. No C
attempt was made; this supports an `ASM_FUNC` proposal pending maintainer
agreement.

**28 October 2026 current-master review evidence:** `func_0029D0E0` is a 376-byte
body in the boot and 27 level placements. Retail uses `$at` to carry table values
from loads at +0x2C/+0xB8 into stores at +0x98/+0x140 (record field +0x64),
and has trapping
`addi` instructions. This supports a handwritten-assembly proposal; no C attempt
was made. Keep `INCLUDE_ASM` pending maintainer agreement to `ASM_FUNC`.

**28 October 2026 current-master review evidence:** `func_002A0A28` is 352 bytes
in the boot and 27 level placements. Rabbitizer's R5900 decode shows `$at` used
as a live scan pointer (`addi $at,$t7,0xD00`, then `lbu` through it, followed
by `addi $at,$at,1` and a loop comparison) and again as a second table cursor.
The body also uses trapping `addi` at +0x0C, +0x20, +0xC0 and +0xDC. This
supports a handwritten-assembly proposal under the repository rule; no C attempt
was made, and `INCLUDE_ASM` remains until a maintainer agrees to `ASM_FUNC`.

**28 October 2026 evidence:** `func_002F0B78` is 392 bytes in the boot and 27 level placements. USA v1.01 retail uses `$at` as a live cursor, trapping `addi`, and COP2/VU0 operations including `lqc2`, `qmtc2.ni`, vector arithmetic, `qmfc2.ni` and accumulator instructions. No C attempt was made; retain `INCLUDE_ASM` pending maintainer agreement to `ASM_FUNC`.

**28 October 2026 evidence:** `func_002A0558` is 80 bytes in the boot and four level placements. USA v1.01 retail uses COP2/VU0 operations (`lqc2`, vector arithmetic, `vsqrt`, `vwaitq`, `qmtc2.ni`, `qmfc2.ni`) and `$at` as a working register; and returns a computed vector value through a COP2-to-GPR/FP transfer. No C attempt was made. This supports handwritten-assembly review; leave `INCLUDE_ASM` pending maintainer agreement to `ASM_FUNC`.

**28 October 2026 evidence:** `func_002A08A0` is 392 bytes in the boot and 27 level placements. USA v1.01 retail uses `$at` as a live pointer, trapping `addi`, and COP2/VU0 instructions including `lqc2`, `vaddw.xyz`, `vsub.xyz`, `qmfc2.ni` and VU0 accumulator operations. No C attempt was made; this supports handwritten-assembly review, but keep `INCLUDE_ASM` until a maintainer agrees to `ASM_FUNC`.

**28 October 2026 evidence:** the 264-byte `func_002F0D00` routine in USA v1.01
uses `$at` as a working register in the shift at +0x30 and add at +0x38, and a
trapping `addi` at +0x28. It is catalogued in the boot and at 27 level
placements. No C attempt was made; retain `INCLUDE_ASM` until a maintainer
agrees with the handwritten classification.

The 264-byte `func_002F5118` sibling in USA v1.01 uses `$at` as a working
register in shifts/addition at +0x28/+0x30 and a trapping `addi` at +0x20. It
is catalogued in the boot and at 27 level placements. No C attempt was made;
retain `INCLUDE_ASM` until a maintainer agrees with the handwritten
classification.

The 280-byte `func_002A1378` routine in USA v1.01 provides further evidence:
it uses `$at` as a working register, multiple trapping `addi` instructions,
`qmtc2`/`qmfc2` transfers, VU0 vector arithmetic and `vsqrt`. It is catalogued
in the boot and at 27 level placements. No C attempt was made; retain
`INCLUDE_ASM` until a maintainer agrees with the handwritten classification.

The 288-byte `func_002F3D20` routine in USA v1.01 combines MMI `pext*` and
`pminw`/`pmaxw`, COP2/VU0 transfers and vector operations, working-register
`$at`, and multiple trapping `addi` instructions. It is catalogued in the boot
and at 27 level placements. No C attempt was made; retain `INCLUDE_ASM` until
a maintainer agrees with the handwritten classification.

**28 October 2026 evidence:** the 320-byte `func_0029D258` body in USA v1.01
(boot and 27 level placements) contains interleaved COP2/VU0 vector operations
(`lqc2`, `qmtc2`, `vmulax`, `vmadday`, `qmfc2`) and MMI packed-integer
operations (`pextlb`, `pextlh`, `pmulth`, `pmfhl.sh`, `ppacb`, `ppach`). The
sequence transforms four vector records and packs output colours. This is
evidence for handwritten-assembly review, not a C match; its source marker
remains `INCLUDE_ASM` pending maintainer agreement.

**28 October 2026 evidence:** `func_00283698` is an 80-byte routine in the boot
and 27 levels. Its USA v1.01 body loads three vector rows with `lqc2`, performs
VU0 vector additions/subtractions, stores three results with `sqc2`, then puts
the final `sqc2 $vf6,0x20($a0)` in the live `jr $ra` delay slot. All 27 level
placements contain the VU0 store opcode. These COP2/VU0 operations are outside
the compiler's C output; this supports handwritten-assembly review, not a C
match. Leave `INCLUDE_ASM` until a maintainer agrees to `ASM_FUNC`.

**28 October 2026 evidence:** `func_002836E8` is an 80-byte routine in the boot
and 27 levels. USA v1.01 loads three vector rows with `lqc2`, performs VU0
vector additions/subtractions, stores three results with `sqc2`, and returns
with a `nop` delay slot. All 27 level placements contain the `lqc2` opcode.
This supports handwritten-assembly review, not a C match; leave `INCLUDE_ASM`
until a maintainer agrees to `ASM_FUNC`.

**28 October 2026 evidence:** `func_00283738` is an 80-byte routine in the boot
and 27 levels. USA v1.01 loads two 3x4 matrices with `lqc2`, multiplies and
accumulates their rows with VU0 vector operations, stores three result rows
with `sqc2`, and places the final store in the live return delay slot. All 27
level placements contain `lqc2`. This supports handwritten-assembly review,
not a C match; leave `INCLUDE_ASM` until a maintainer agrees to `ASM_FUNC`.

The wave 8 correction correctly identified 0x700014A9 as por, not mtsa or an undecodable word. The recorded mtsa zero encoding was 0x00000029. A por-plus-sq zero mismatch remains separate from a decoder error (section 17).

lq/sq are not VU0/COP2 and can be emitted from a TImode C assignment. Four targets were nearly misclassified because the reader used a generic instruction category. Use `rabbitizer.Instruction(word, address, rabbitizer.InstrCategory.R5900).disassemble()`; not every generic INVALID word is lq/sq, so decode each exact word. The reviewed qcopy/qzero helpers are also permitted under the updated source-method rule; none of these instructions alone proves a complete match.

`func_L00_00391398` provides a further plain-C control: its 324-byte body, including
`por` plus `sq` zero initialization, passed `tools/check.py` at 27/27 placements in
both USA releases (the name is absent from PAL). The previous MMI-impossible screen
was incorrect. A union with TImode and float-array members keeps the scalar field
at a fixed stack offset; casting a TImode local to `float *` instead retained a
pointer across calls and added one saved register (340 bytes). Profile: default
`-O2 -G0 -ffunction-sections`. The combined tree passes all 84 strict program builds.

The retained near miss of `func_L11_0046BD18` (formerly
`nonmatching/levels/func_L11_0046BD18.c`) provided a separate integer-address
control: decode its multiply-add as R5900 `madd`, and its quadword transfers as
ordinary TI assignments. That reconstruction compiled those instruction families
but remained 1060/1024 bytes, 0/2 placements in each release. This supersedes the
historical MMI-only screen without claiming a whole-body match.

**Update, 28 October 2026 (pending review):** `func_L11_0046BD18` is C in
[L11_0046BD18-g8.c](../src/levels/shared/L11_0046BD18-g8.c)
(`-O2 -G8 -ffunction-sections -g`), at 1024 bytes and placed 2/2 in each of US, PAL
and US2 ([PR #348](https://github.com/OpenRAC/rac2-decomp/pull/348));
the near-miss file is removed. `tools/build.py all --strict` passes in all three
releases.

<a id="blocker-12"></a>

## 12. A catalogue entry whose body differs between programs

**23 October 2026 linked timer qualification:** `func_L00_002A5480` has genuine
USA/PAL timing differences at +0x38 and +0x70: 30/20 frames in both USA releases,
25/17 in PAL. An address relocation cannot represent them. Adding only this timer
to PAL's `not_carried.tsv` and running the maintained `carry.py --version pal`
renames exactly two PAL level rows: the timer becomes `func_PAL_L00_002A5310`, and
its already-ASM direct caller becomes `func_PAL_L00_002A53A8`. No other row or
existing C is demoted; the caller remains an `INCLUDE_ASM` marker. Repeating the
generator produces identical catalogues. Separate G8 C bodies pass 27/27 places
for each applicable release, including equality of the tick word's SDA/absolute
aliases. The 148-byte extents end at entry+0x94 and retain the four-byte gap before
the next entry at +0x98. The combined tree passes all 84 strict program builds.

The PAL timer uses the shared resident identity `D_00189E20`, whose PAL binding is
`0x00189EA0`. The canonical `D_00189EA0` instead names the distinct mutable resident vector
used by `func_00334710` (PAL binding `0x00189F20`). Per-function relocation checks
alone did not expose the collision from naming the timer base by its PAL physical
address. A joint binding control with `func_L00_002D3248` and `func_00334710`
checks these identities together at every PAL placement. Subsequent strict builds
pass all 28 PAL programs with both identities present and no C fallback.

The resident vector is not a constant or a guaranteed zero: the retail initialization
body `func_L00_002A4928` writes the chosen actor's position into `D_00189E20 + 0x80`,
the canonical `D_00189EA0`. Earlier zero/constant labels described a mistaken
interpretation of `func_00334710`, which returns this stored vector. Preserve the
shared identities without inventing constness or zero initialization at each read.

**Current scope:** func_L00_00424BB8 remains a marker. The 23/27 report is historical; section 34 describes different field offsets. Re-extract the current extents before changing their grouping.

**Signature:** `tools/check.py` reports a partial count (`23 of 27 places match`) and
`instruction at +0xNN differs` on an `addiu` **immediate** or a **store displacement** - a word
that carries no relocation, so it is a real difference, not the usual unrelocated column. The C
is right in most programs and retail genuinely holds other constants in the rest.

**Measured example:** `func_L00_00424BB8` (`src/levels/shared/L00_004224D0.c`) is `q + 0x60` with
fields `+0xE4/+0xE8` in 23 programs, and `q + 0x20` with `+0x1C/+0x20` in `16_snivelak`,
`22_dobbo_orbit`, `23_damosel_orbit` and `26_jamming_array`.

**Consequence:** placement is per program. Rejected C can fall back to assembly in an affected program while it still prints OK; rejection does not mean every other program dropped the function. Merged PR #252 adds `tools/build.py all --strict`, which rejects fallback. A wave's own count is therefore only true if you read the
`do not match` numbers too. `ref_LNN_XXXXXXXX_kk` cannot help here: it names a symbol *value*,
not an immediate constant. Report the entry and keep the marker in place.

**Byte-identical stubs do not establish one source ABI.**
`func_L00_00345AF0` has 27 placements per release, all an eight-byte zero
return. Across USA v1.01, USA v2.00 and PAL, three direct call sites treat V0
as a nullable pointer; another prepares A0 and clears A1 while ignoring V0.
Twenty-four initialized `.lit` words per release equal these addresses,
but their indirect-call contracts have not been traced. Twenty-one canonical
names share this fingerprint. Preserve observed caller arguments/results;
do not impose one fixed arity from the stub body, invent a variadic
signature, or silently drop arguments to agree with its historical C
prototype. The shared callback family needs reference/ABI qualification.

Four existing C interfaces now agree with independently measured call sites:
`func_00291450` explicitly forwards the part index; `func_L06_003660F0`
forwards all three node-initializer inputs; `func_L02_003FC248` retains its
two unused integer callback slots; and `func_L02_003CAE68` retains the unused
output pointer supplied by its update caller. Their 94 carrying checker
placements and the complete 84-program strict build pass with the same retail
operations. These are source-contract repairs, not new decompiled bytes; the
ambiguous zero-stub family above remains unchanged.
[Measured caller-interface repairs](https://github.com/OpenRAC/rac2-decomp/commit/623184a4e99a331b23db8b90f4defb1708f96f75).

Five further existing caller interfaces preserve their actual inputs:
`func_L09_00404F90`, `func_L02_003CE8B0` and their PAL-specific wrappers
explicitly forward the two incoming pointers to integer-returning
`func_L01_00321178`. The old no-argument calls happened to leave those
registers intact. `func_L00_003BFF68` forwards its fourth incoming pointer as
the third argument of `func_002B04E0`, without the invented
duplicate fourth slot. All 51 carrying placements and the 84 strict programs
pass. These repairs add no decompiled-byte credit.
[Caller-interface corrections](https://github.com/OpenRAC/rac2-decomp/commit/a541245e66b8dfc8303cb72e07a4718e47301c76).

Eight further existing interfaces pass 104 carrying placements without
new byte credit. The two `func_002B60B0` callers retain the object plus four
float inputs and the real pointer return; `func_L00_00323F28` explicitly
forwards three floats. `func_L03_00419BD8` and `func_L03_00419B10` propagate
the query result, point pointers, optional output pointers and floating
inputs. The Aranos emitter preserves its caller-provided unused F12 slot,
and `func_L02_003CE8B0` plus its PAL wrapper forward both pointers to the
first entry hook. All 84 strict programs pass.
[Caller-interface corrections](https://github.com/OpenRAC/rac2-decomp/commit/4a81f40f3099c9996fe4d8f5224133de7fd03040).

Two explicit alternatives remain unlinked. `func_L03_0041F090` still has
an existing byte-matched body whose first call relies on the incoming A0
register being preserved implicitly. Its retained explicit-entity call is
228/228 bytes but 0/1 in each USA release: a redundant A0 copy occupies
retail's nop at +0x38. `-fcse-follow-jumps` ties; PAL has no canonical row.
Do not use the old unspecified-argument declaration as a native interface.
`func_L03_00419C00` retains corrected three-pointer/integer-return C at
84/84 bytes and 0/2 in each release; sentinel stores and setup scheduling
still differ from +0x1C. Neither case justifies a false prototype, pin or
assembly classification. Reopen with independent reaching-value or output-
lifetime evidence; the complete alternatives are in `nonmatching/`.

Five existing C interfaces now preserve another measured call contract:
the Maktar and Dobbo wrappers, including their PAL forms, explicitly pass
the live object and target pointers plus the float amount to
`func_002B4FF0`. `func_003225C0` accepts an object pointer and gives
`func_0029FCC0` its full aligned 16-byte output instead of a 12-byte local.
All 24 carrying placements and 84 strict programs pass, without new byte
credit. [Interface and storage repairs](https://github.com/OpenRAC/rac2-decomp/commit/3638916fe51ef118070c96fd7eae30d3f580269b).

The callback retains a real retail constraint: it reads its own uninitialized
Z slot, adds the first RNG result and stores it before the bone helper
initializes the output. Its existing matched C preserves that sequence;
byte equality does not make it defined native C. The complete alternative
in `nonmatching/game/func_003225C0.c` keeps the RNG call for its state
effect and removes the dead, indeterminate calculation. It is 176/188
bytes, 0/3 placements in each release, and remains unlinked. Native execution
and floating-point exception-state equivalence have not been tested.
Likewise, retained `func_L00_003EEE90` normalizes an impulse before its
first fill, as retail does; do not conceal that constraint with invented
initialization or describe every complete reconstruction as native-safe.

Two indexed animation wrappers now preserve independently observed live
inputs. `func_L09_00329178` forwards count/value in A2/A3 to
`func_002B6228`; `func_L09_0033E690` forwards its F12 base to
`func_L06_00382850`. Their L18 caller already supplies all these arguments
and is unchanged. The former two-argument declarations matched because
the register contents survived implicitly. The explicit contracts pass
all 33 carrying placements and all 84 strict programs, with no new credit.
[Measured wrapper repairs](https://github.com/OpenRAC/rac2-decomp/commit/e9253b20eda332eba59ec959541bf25013fbc7ec).

Keep unused results distinct from unproved results. The actual allocation
paths of `func_002C2210`, `func_002C16C0` and `func_002BFB38` return a
pointer or null; `func_00277F48` returns a 32-bit count. Retained callers
that ignore these results must not invent a void contract. Conversely,
a live F0 scratch value alone does not establish a floating return:
inspect a real consuming caller before changing an unrelated helper's
interface. Physical input banks and stack words need the same control.

<a id="blocker-13"></a>

## 13. Floating-point literals are calibrated, not computed

The decimal in your C is parsed by the pinned 1999 `cc1` with its own rounding, which does not
always agree with a correctly-rounded decimal -> binary32 conversion. The retail word is what
counts, so read the constant's bits and bisect the decimal until the compiled word is equal -
a placed body is the only proof. The usual way to lose a body by one word is writing the short
decimal that "obviously" means the same (`0.000290888f` for `0.000290888245f`).

Two literals verified against this toolchain, their bodies placed by the build (so `cc1`'s word
*is* the retail word): `0.017453294f` (pi/180) in `src/levels/12_todano/L12_00398E50.c`, and
`0.055268768f` in `src/levels/shared/L01_00397110.c`.

**Measured 2026-10-25, the loss is in `as`, not `cc1`:** for `pi/4` and `pi/6` the
`li.s` line in `cc1`'s `.s` already holds the retail word (`7.85398185253143310547e-1` =
`0x3F490FDC`, `5.23598790168762207031e-1` = `0x3F060A93`), but the assembled object holds one
ulp less (`0x3F490FDB`, `0x3F060A92`). The pinned `as` re-parses the printed decimal
imprecisely, so bisect the *object* word, not the `.s`. The pair that lands correctly is
`0.78539825f` and `0.52359885f` (each makes `cc1` print the next float up, which `as` then
rounds down onto the retail word). Debug recipe: compile a one-line probe with
the configured compiler/profile and inspect the object, not only the assembly.

<a id="blocker-14"></a>

## 14. Store order is not one universal rotation

Some historical integer-store blocks emitted the last source store first; blocks interleaving TI/FPU stores behaved differently. Calibrate per block and verify final bytes instead of applying a universal rotation.

The 436-byte family func_L00_003DC910/003E0088/003E0F58 was recorded at 27 places each: retail-order source matched first try where inverse rotation failed on a sw/sd pair. That is a historical witness, not a rule for every store block or a fresh all-family check.

<a id="blocker-15"></a>

## 15. A `nop` after `mfc1` that retail does not have

**Historical signature:** func_L22_003A2DF8 was four bytes too long because a nop followed mfc1 before its integer consumer.

**Resolved:** gas inserted the delay, not cc1's R5900 latency model. The qualified r5900_mfc1_interlock.py transformer exempts mfc1 on R5900 from the MIPS-I coprocessor-load delay in append_insn. PR #222 landed it, and issue #247 is now closed as completed. The named witness passes 2/2 placements.

Qualification recorded 88 immediate mfc1 readers in the boot text. Scope is mfc1, not every coprocessor move: cfc2 and label-boundary padding remain separate. The old “unreachable; walk away” conclusion is withdrawn.

<a id="blocker-16"></a>

## 16. If-conversion of constant selections

**Signature:** retail keeps two compares and a branch to choose between two constants; cc1
if-converts, giving `sltiu`/`movz` (plus a word, or the same size with one instruction
exchanged). Seen where a value equal to 5 or 7 selects constants: a `switch` did not keep the
branches either. If `--diff` shows `movz` where retail has a branch, try the spelling below once, then walk away.

**Workaround measured in wave 8 - the only one of 14+ spellings that held:** two `goto`s and two `return`s.

```c
if (c) goto one; goto zero;
one: r = 1; return r;
zero: r = 0; return r;
```

That keeps `bnez` + `addiu $2,zero,1` + `daddu $2,zero,$zero` where `if/else`, two `return`s and the ternary all collapse to `sltu`. It matched a body first try.

<a id="blocker-17"></a>

## 17. A 128-bit zero: por plus sq against sq zero

Separate zero materialisation, register-to-zero store folding, and scheduling of a clear relative to other memory operations.

Historically rac2_fold_zero_ti_store removed por when its store was the final use. A naturally shared zero feeding multiple stores could retain materialisation; later inspection also identified block boundaries, scan distance and intervening control flow. Do not manufacture a second use solely to force codegen.

Merged PR #251 provides the qualified, default-off per-file `-frac2-zero-ti-barrier` clear-scheduling profile. It is a heuristic, not proof of an original macro. Qualify every function in an opted-in unit and the full build. It does not resolve every single por plus nonzero-displacement store.

[PR #258](https://github.com/OpenRAC/rac2-gc-decomp/pull/258) restricts the existing fold to a register-only memory address, retaining materialized zero registers for offset stores. Its 775-unit A/B run found no non-debug section changes and 11 mdebug differences. The integrated clean witnesses are func_L20_0044AB68 (204 bytes, 1/1 placement), func_L20_00443908 (264 bytes, 1/1) and func_L00_003ACC88 (112 bytes, 27/27 in its G8 unit). All 28 programs pass --strict and all 57 tests pass. This corrects the zero-store rule; it does not resolve all TI-copy address families or all historically screened near misses.

**Copy-epilogue qualification, 25 October 2026:** `func_00335370` is now
C in `src/game/00335370-copy.c`, 88 bytes at 28/28 placements in each release.
The real shared `qcopy` helper reproduces the memory dependence that keeps the
return-address restore after the copy, with the default game profile. The earlier
TI-only frame-order and sched2 experiments were near misses, not proof of an
unreachable epilogue. `func_002B5678` similarly qualifies its snapshot and clear
through `qcopy`/`qzero`: 432 bytes at 21/21 placements per release. Both are
included in the 84 strict program builds; old drafts remain in Git history.

<a id="blocker-18"></a>

## 18. Catalogue entries that are not functions

A start inside a prior epilogue, measured linker filler, or an implausible entry warrants an extent/reference audit before matching.

No jr, two returns, a short size, or a register read before its local definition is not proof by itself. Trap/tail-call bodies may lack jr; ABI-defined live-ins must be considered. A four-byte residue needs its surrounding completed return and reference evidence, not just its size.

**Resolved entry, 30 October 2026, `func_L05_0042AFE0`:** callback address
construction in `func_L05_0042AC30` (US/US2) and the distinct PAL caller
`func_PAL_L05_00430828` reaches the GP load into F1 before the stack prologue.
This is verified in levels 5, 10, 15 and 25 of all three releases. The original
732-byte extent must skip eight bytes, not twelve: the twelve entries move
back four bytes and grow from 720 to 724, retaining their ends and names.
For example, USA level 5 changes `0042AFEC` to `0042AFE8` and still ends at
`0042B2BC`. This supersedes the earlier hypothesis that lacked entry evidence;
do not invent an F1 formal parameter or discard the live load.

The existing generator accepts only this measured legacy 720-byte form when
recovering the original span. Synthetic catalogue/carry regressions preserve
the pre-prologue load, names and ends, reject unexpected sizes and replay
without changes. The complete retained C now emits the leading load naturally
and reaches 724 bytes, but remains nonmatching at all twelve places. There is
no C or handwritten-assembly credit for the boundary repair itself.

Primary regeneration uses `python3 tools/levels.py catalogue --version us`.
To reproduce only this repair in the other two releases with the existing API:

```sh
python3 -c "import sys; sys.path.insert(0, 'tools'); import levels, carry; levels.select(sys.argv[1]); levels.FUNCTION_ENTRY_OFFSETS = {'func_L05_0042AFE0': levels.FUNCTION_ENTRY_OFFSETS['func_L05_0042AFE0']}; carry.refresh_entries()" us2
python3 -c "import sys; sys.path.insert(0, 'tools'); import levels, carry; levels.select(sys.argv[1]); levels.FUNCTION_ENTRY_OFFSETS = {'func_L05_0042AFE0': levels.FUNCTION_ENTRY_OFFSETS['func_L05_0042AFE0']}; carry.refresh_entries()" pal
```

The unfiltered `carry.py --entries` also exposes an older, unrelated
`func_00282848` repair in the release catalogues. Those rows are unchanged here;
they need their own review. The scoped regeneration and its replay change only
the three AFE0 rows. Always select the intended release explicitly when invoking
tools from a process that has used `levels.select`, which also sets `RAC2_VERSION`.

**Unresolved extent/entry hypothesis: `func_002D9730` (USA v1.01, PAL, USA v2.00).** Its 100-byte body has the same decoded sequence across the three releases apart from release-specific call targets. At the USA v1.01 start, the preceding function returns at `0x2D9728` with its stack adjustment in the delay slot; the next word clears object offset `0x44`. The target then makes four positive stack adjustments (`+0x10`, `+0x30`, `+0x10`, `+0x130`), each followed by `nop`, before allocating a 16-byte call frame, saving `$ra`, making three calls and returning 8. A direct branch/call scan of USA v1.01 boot text found no target inside the extent; indirect references have not been traced. The retained C draft compiles to 64 bytes under the default game profile and matches 0/28 places in each release. A 96-byte `__builtin_alloca` probe still emitted the compiler's normal frame-pointer/RA prologue before the clear. This does not distinguish a hidden indirect entry from an extent boundary; do not change the catalogue or classify it handwritten. Next: trace indirect references and the incoming stack/argument ABI before another C attempt.

The 49-worker wave reported roughly 30 suspects. Those are historical candidates; later rules in PRs #239/#241/#253 resolve specific filler/residue cases. Mixed prefix/body boundaries and the appendix's other proposals remain separate individually evidenced tasks.

**Independent discovery control, USA v1.01 (23 October 2026).**
[PS2Recomp's ELF parser](https://github.com/ran-j/PS2Recomp/blob/e5636981a1c9de368f6b71e819c3dc188dfedbf4/ps2xRecomp/src/lib/elf_parser.cpp)
was built and run without our catalogue, Ghidra map or signature database, against the original boot and lossless, symbol-free ELF wrappers of levels 00, 02, 23 and 30. Each input was checked against `config/programs.tsv`. This confirms some historical entry proposals, but does not qualify a catalogue change or new C:

- It finds `001158F8`, `004277B8` in level 23 and `00404610` in level 30, respectively 4, 8 and 8 bytes after the entries in baseline `375b90d9`. Retail direct calls confirm the first; the level-23 data pointer at `002ABE40` confirms the second. Its inferred ends for both level functions include four extra padding bytes: their bodies are 44 and 228 bytes, not the parser's 48 and 232.
- It misses level 02's `0035BD70` despite the retail data pointer at `00289490`; the 16-byte prefix proposal remains an independent audit. It also misses boot `0011F380`: the current `0011F364` extent has seven fill words (28 bytes), settling the appendix's conflicting prefix counts for this release only.
- It overextends `func_00308600` to 376 bytes, swallowing 16 bytes of `func_00308768`. This does not resolve the retained 356/360 C near miss. As a positive control, it recovers `_fpadd_parts` at `00122800` with exactly 576 bytes.
- It splits `func_L00_002B1308` into 40/24/8-byte extents at `002B1308`, `002B1330` and `002B1348`. The latter two are switch targets inside the existing 72-byte function. Its analyzer detects no table even when supplied that complete range; its separate recompiler control-flow pass does recover both internal targets. Reading all 31 retail table entries independently confirms action cases 14, 26, 27, 43 and 44. Do not promote these labels to functions.

For level 23, the preceding return is at `004277A4`, its delay slot restores `0xD0` at `004277A8`, and `004277AC` is padding. The positive `0x190` adjustment at `004277B0` is an unmatched residue after that completed return, **not** its delay slot. Future boundary fixes must preserve skipped bytes, verify other entry evidence and all applicable releases, regenerate through `tools/levels.py`, and pass strict linked builds. This control adds no integrated C, catalogue correction or progress credit.

**Level-23 entry correction and wrapper ([PR #299](https://github.com/OpenRAC/rac2-decomp/pull/299)).** Following the controls recorded in [PR #298](https://github.com/OpenRAC/rac2-decomp/pull/298), the measured entry correction yields `func_L23_004277B8`, a 44-byte, two-call plain-C wrapper with the default game compiler profile. Both USA releases match at their single placement (`004277B8` / `00428CB8`), with the original end and eight skipped bytes preserved. The generator changes only this v1.01 row; `tools/carry.py --version us2` changes only its v2.00 counterpart. No direct branch/jump or aligned data pointer targets either skipped word in either level program; the data pointer at `002ABE40` targets the corrected entry in both. Arbitrary computed indirect targets are outside that reference scan. PAL retains its distinct version-specific wrapper. Adding this wrapper leaves the emitted bytes and normalized relocation records of the unit's five existing C functions unchanged. The obsolete retained attempt is removed; the other boundary proposals below remain separate.

<a id="blocker-19"></a>

## 19. The delay slot's filler is chosen by the scheduler, not by you

Check the actual callee ABI before treating a slot difference as a scheduler wall.
`func_L00_00413870` was 164/164 bytes with a +0x54 argument-setup difference when
its draft declared `func_002FC560(int, int)`. The callee stores its second input
as a 64-bit packet value. Its real unsigned 64-bit declaration and literal recover
27/27 checks in both USA releases; the name is absent from PAL's catalogue.
No flag or artificial scheduling dependency is needed beyond the existing G8 unit.

**Named examples now resolved:** func_L18_0042FAA8, func_L02_003D69F0 and func_L23_003C0E98 each pass1/1. Their older measurements below are retained as history, not current blockers.

**Signature:** the multiset of instructions is right and the size is right (or off by one), but
the instruction that sits in a branch or `jal` delay slot is not the one retail put there - our
column has the load/store/copy *before* the branch where retail has it *in* the slot, or the
other way round. Also shows up as a store landing in the second `jal` delay slot instead of the
first. This is `reorg`'s forward-fill choice and it is the single most common near miss in the
six waves' drafts (37 of 240 worker notes mention a delay slot).

**28 October 2026 follow-up:** `func_002B68C8`'s current candidate is 112 bytes
against the 108-byte boot extent, with zero matches at its one placement. Retail
places the ordinary `-1` state store in the call-delay slot; the compiler moves
it before the final flag store. Making the state writes volatile restores their
order but leaves the call slot empty. A temporary current-unit check confirms
the same slot mismatch; no strict linked match is claimed.

**28 October 2026 recheck:** with the state pointer acquired after the first
helper and the `-1` value materialized after that call, an all-ordinary-store
candidate reaches the correct 108-byte size. It still matches 0/1: cc1 moves the
`+0x24` store before the `+0x3C` store instead of keeping it after the other
fields in the `func_002B66F0` delay slot. Marking only the final store volatile
produces the same order; making all stores volatile retains their order but
leaves a nop in the call delay slot. No artificial reads, barriers or fake
dependencies are used. This supersedes the earlier 112-byte size measurement.
An explicitly laid out naturally aligned state struct also gives 112 bytes;
packing it gives 156 bytes of byte/partial stores. Neither layout improves the
ordinary-store candidate.

**28 October 2026 follow-up:** `func_0011B140` has two retail `sync` barriers
around the `0x1000F000` handshake and returns the unsigned 64-bit value
initialized through `func_0011AF90`. The current semantic candidate, checked in
the marker unit's default game profile with complete helper declarations,
volatile flag/MMIO accesses and two `__sync_synchronize()` calls, is 184 bytes
against retail's 164 (0/1). The candidate does emit both `sync` instructions; it saves the helper result
in `$s0` and repeatedly materializes the MMIO address. A branch-shaped source
that duplicates each real store in both callback arms grows to 212 bytes and
moves both callbacks before polling. This supersedes the earlier 192-byte
measurement. A 29 October 2026 actual-unit probe replacing `__sync_synchronize()`
with `__atomic_thread_fence(5)` is also 184/164 and 0/1, but this GCC 2.9
frontend treats the unsupported spelling as an implicit helper call, emitting
`jal func_000000` with argument 5 rather than `sync`; the probe was discarded.
No strict match is established.

**28 October 2026 follow-up:** `func_0029DC90` is 60 bytes at 28 USA v1.01 places.
Its retail result in `$v0` is boolean and it is referenced through a data
table. The earlier inference from a residual `$v1` was invalid: EE 64-bit
integer results occupy `$v0`, not an o32 `$v0`/`$v1` pair. The callback's
original declared width remains unverified. An earlier 64-bit-result C probe was
64 bytes (0/28); a nested `int` result variable compiles to 52 bytes (0/28), and
explicit early returns compile to 64 bytes (0/28). These variants differ in
allocation and branch layout. The neighboring `func_0029DCD0` also uses ordinary
global reads, so volatile qualifiers are not evidence-based here.
**28 October 2026 source-symbol recheck:** the retained C now names the three
bytes as boot-resident `D_001395C1`, `D_001A7B05` and `D_001A7B0C`. Rechecked
in the marker unit with the three absolute data expressions, the nested-return
form is 60/60 bytes and 0/28 USA v1.01 places. Every word now agrees except the
first `lbu` destination (`$v0` in C, `$v1` in retail). The external-symbol
form leaves its relocations at zero; the named-result form is 52 bytes, the
conditional-expression form is 64, and a shared-failure-label form ties the
nested body. The callback return width remains unresolved
because no direct callers are present and its table prototype is unknown.
**28 October 2026 short-circuit probe:** spelling the predicate as a direct
`D_001395C1 && D_001A7B05 && D_001A7B0C` chain produces 52 bytes, 0/28.
It allocates the first load to `$v1` like retail and the second to `$v0`, but
puts the third load in `$v1`, changes the branch layout, and does not reproduce
the return-value move in the retail delay slot. The 60-byte nested-return body
remains the closest candidate; no additional source shape is justified by this
result.

**29 October 2026 scheduling probe:** a dedicated `-O2 -G8
-ffunction-sections -fno-schedule-insns` unit with the nested-return body stays
60/60 bytes and 0/28. The first `lbu` remains in `$v0` instead of retail's
`$v1`; the remaining body is aligned. Disabling scheduling does not resolve
the allocation difference.

**29 October 2026 scheduling follow-up:** `func_002A0488` remains 48/48 bytes
and 0/28 with isolated `-fno-schedule-insns2`. The probe exchanges the first
`dsll32` and `ld`, while the final store remains before `jr $ra` instead of in
its delay slot. This later scheduler setting does not resolve the return-slot
mismatch.

**29 October 2026 corrected-base follow-up:** `func_00295870` is a 68-byte
table predicate at 28 USA v1.01 placements. Retail's table base is
`0x0010B540` (`D_0010B540`), with path offsets `0x14F4` and `0x15D4`; the
previous near-miss source used the wrong `D_00105540` base and is superseded.
The corrected array candidate in the original source unit compiles to 64/68
bytes and 0/28. It preserves the two paths but allocates the mask, base and
loaded word to `$v1`, `$v0` and `$v0`, where retail uses `$v0`, `$v1` and `$a0`.
`-fno-schedule-insns` remains 0/28 and leaves the mask outside the branch delay
slot. A corrected byte-offset pointer form is 56/68, 0/28, and hoists the
index. Do not introduce artificial dependencies or memory accesses to force
the retail allocation.

**28 October 2026 follow-up:** `func_002FFCF8` is a 124-byte function with a current
120-byte candidate at 28 USA v1.01 placements. A temporary explicit statement order
(initial helper call, short load, angle helper call, float load and calculation) remained
120/124 and 0/28: the compiler still scheduled the short load in the angle call's delay
slot, while retail leaves the slot empty. Address materialization and register choices
also differ. Isolated-unit `-fno-schedule-insns` and `-fno-schedule-insns2` probes
also remain 120/124 and 0/28; neither moves the short load, and the latter changes
stack-save and float-constant order. No artificial dependency or volatile access is
justified to force the slot.

**28 October 2026 follow-up:** `func_002F7320` is 132 bytes at 28 USA v1.01 placements.
The retained nested-condition candidate was 132/132 but 0/28. A temporary explicit
single-loop/goto form, with the same table-search and comparison semantics, compiled to
120/132 (0/28); it exposes the shared loop exit but still differs in table-base setup,
cursor/index allocation, branch layout and return-value scheduling. Retain the smaller
candidate as the current near miss; no strict linked match is established. A structured
`for (;;)` loop with `break` at the same zero-entry/key/limit conditions compiles to
144/132 (0/28), with additional cursor/index work and a less similar branch layout.

**29 October 2026 FPU scheduling probe:** `func_00282C68` remains 16/16 bytes
and 0/28 with isolated `-O2 -G0 -ffunction-sections -ffast-math
-fno-schedule-insns2`. The max operation moves to the first word and min fills
the return delay slot, but the max destination and min source still use the
wrong FPRs. Reversing both comparisons is byte-identical; the fast-math
if-chain is 44/16. No match is established.

**Measured examples:** `func_L18_0042FAA8` (56 bytes, 13 of 14 instructions identical, "the delay-slot filler takes" the other value); `func_L02_003D69F0` (48 against 44, the
`sw $zero` lands in the second `jal` delay slot instead of the first); `func_L23_003C0E98`
(prologue reordered, the `lw` in the slot instead of before it).

**Workaround that sometimes works:** section 7's - hoist the instruction the paths share above
the `if` so the scheduler can fill the slot itself. Otherwise retain the exact near miss/profile and a bounded stopping reason; a few unchanged forms do not prove that no meaningful source/profile lever exists.

A remaining setup-order control is
[func_L00_003A8238](../nonmatching/levels/func_L00_003A8238.c): 720/720 bytes,
0/27 placements in each USA release, with no carried PAL name. Only the two
non-relocation instructions materializing `-1` and `7` exchange positions.
Typed effect records and the measured floating/integer call interface resolve
the other observed differences. Nine bounded trials include three forms that
end in the same two-word tie. Reopen with an independently justified constant
or loop-lifetime model; another equivalent spelling is not new evidence.

**24 October 2026, retained near miss:** `func_L08_0042F440` and
`func_L08_0042FAC0` are 544/544 bytes and 0/1 each, byte-identical through
+0x128. Only two func_334BB0 argument-setup blocks and case 3's counter register
differ: retail keeps `daddu $a0,$s0` in the `beqz` delay slot and materialises
the a2 address after a1, this cc1 hoists `lui $a2,%hi` into the slot. Moving the
last integer argument's declaration after the four floats (the integer/FP bank
split of COMPILER-NOTES) puts only that argument in the `jal` slot; it does not
move a2. Two different source orders and the `x = x + 1` / `x++` / named-temp
counter forms measured. Retained: `nonmatching/levels/func_L08_0042F440.c`,
`func_L08_0042FAC0.c`.

**28 October 2026, retained near miss:** `func_0027A9F0` (USA v1.01, 332 bytes,
boot and 27 levels; default `-O2 -G0`) compiles to 328 bytes and 0/28. Retail
stores the width before a helper call and places the argument copy in the `jal`
delay slot; the candidate's width store occupies that slot. Moving the width
store ahead of all other screen-state stores leaves the same 328-byte output.
This is one unchanged source-order result, not evidence that all scheduling
forms are exhausted; the retained file records the other measured store orders.

<a id="blocker-20"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L00_003A8238` is C in `src/levels/shared/L00_003A8238-impact.c` (`-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier`), placed at 27 US, 27 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_0027A9F0` is C in `src/game/00274128.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_002B68C8` is C in `src/game/002B68C8.c` (`-O2 -G0 -ffunction-sections -fno-schedule-insns`), placed at 1 US, 28 PAL, 1 US2 places. The measurements above are kept as history.

## 20. Two exits where cc1 keeps one

Historical symptoms included merged versus duplicated epilogues, reversed branch polarity, out-of-line versus inlined returns, or an early return folded to a constant. Examples were func_L08_00318F90(68 versus 76 bytes), func_L08_003289D0, func_L23_0041E220, func_L19_0041C328 and func_L14_00427210.

func_L08_003289D0 now passes 2/2 and func_L23_0041E220 1/1; the other cases are not assumed resolved. Meaningful recipes included separate literal returns carrying the real computed value, both condition polarities, and an inverted early guard placing a longer block out of line. A shared goto sometimes merged tails further.

PR #238's conditional-fallthrough cleanup is narrower: it removes a jump to the immediately following block early enough for flow to remove its dead input in documented rotated id-list walks. Neither that fix nor one successful return shape solves arbitrary epilogue/block ordering.

<a id="blocker-21"></a>

## 21. Varargs: the saveregs prologue is exact, the call is not

**Named example resolved:** func_L08_0033CD18 now passes 2/2 using the register-save-area recipe below. The offset depends on the ABI/named arguments; do not transplant it blindly.

**Signature:** `__builtin_saveregs()` gives the retail's register-save prologue exactly, then
one `jal`+`nop` too many remains where retail passes the save area directly
(`addiu $a2,$sp,0x50`).

**Measured example:** `func_L08_0033CD18` (76 against 68: "the varargs register-save prologue
from `__builtin_saveregs()` is EXACT; one jal+nop too many remains: retail materialises
`addiu a2,sp,0x50` directly"). **Recipe, measured in wave 8 (matched 2 of 2 first try):** hand the save area to the callee directly instead of rebuilding it -

```c
void f(s32 a0, s32 a1, ...) { worker(a0, a1, (char *)__builtin_next_arg(a1) - 0x30); }
```

reproduces retail's `sd a2..t3` + `swc1 f12..f18` save prologue **and** the frame, and passes the save area the way the missing `addiu $a2,$sp,0x50` above does; the `-0x30` is six registers of eight bytes. Prefer it to `__builtin_saveregs()`, and reach for it before declaring a varargs body stuck.

<a id="blocker-22"></a>

## 22. Vector copies: address materialisation is only part of the mismatch

**Qualified packet and call-contract remedies, 25 October 2026:**
The 2,192-byte Damosel beam uses the real 144-byte packet, clobbering
`qcopy` transfers and corner addresses formed at use. Its color packing
casts to `u32` before shifting: the updater reaches fade 64, making signed
alpha shifts undefined. The 168-byte effect wrapper preserves the optional
fifth-GPR vector pointer; the 308-byte query wrapper preserves its integer
mode and canonical interleaved FP arguments. Together with the target and
constructor helpers, 7 functions (3,848 distinct bytes) pass 47
carrying placements and all 84 strict programs without a compiler change.
Profiles are game `-O2 -ffunction-sections`: `-G0` for the query and Dobbo
helpers, `-G8` for the beam, effect wrapper, spawn and target helpers.
[Qualified sources](https://github.com/OpenRAC/rac2-decomp/commit/e73fb043ed96233298f7aaf60854484c0046ee16).

Retained storage repairs are not matches. `func_L23_0042ADB0` needs the
rotation helper's full three-row, 48-byte output. `func_L06_003D64C0`
uses a 32-bit cooldown with `func_00282948(int *)`, while its fork timers
remain 16-bit with `func_00282978(short *)`. Preserve those measured widths
and the complete buffers when revisiting their scheduling differences.

**25 October 2026 linked helper qualification:**
`func_L08_003D8290` (96 bytes) and `func_L08_003D0508` (192) pass their
USA v1.01, USA v2.00 and PAL placement checks with the reviewed `qcopy` helper
and default G0 profiles, then link successfully in all three editions.
The combined tree passes all 84 strict programs without C fallback.
[Qualified helper source and retained reconstructions](https://github.com/OpenRAC/rac2-decomp/commit/a49d016ad8f366dce34aebbcdeaa7c9472c074ef). The latter
draft also needed a semantic repair: only
initialization is conditional; projection, update and the final position
snapshot execute unconditionally. Scratch vectors have explicit
16-byte alignment. The historical folded-copy experiments did not establish
an impossibility of C or require a new compiler pass.

`func_L08_003D3D80` remains a 128/128-byte near miss. Its addressed copy now
agrees, but the constant, source-byte and payload-pointer scratch roles and
initialization stores differ from +0x24. Three meaningful record/lifetime
forms produce identical text; keep the complete retained C and reopen with
independent allocation or constructor-layout evidence, not another cosmetic
permutation or an assembly classification.

**Further qualified copy remedies, 25 October 2026:**
`func_L02_002EF968` uses the real 144-byte packet and normal memory-clobbering
`qcopy`; `func_L02_0032EF10` keeps its first transfer ordinary and uses
`qcopy` for the conditional output transfers, preserving the subsequent Z
write. `func_L07_003E5C78` captures the state pointer before the state-change
call, then performs exactly two copies. The Joba position-choice family and
the Dobbo Orbit constructors/update bodies also close with the reviewed
helper and actual value lifetimes. The combined source change adds 17
functions, 4,224 distinct bytes and 365 accepted placements across the three
releases; all 84 strict programs pass. No new compiler mechanism was needed.
[Source remedies and retained reconstructions](https://github.com/OpenRAC/rac2-decomp/commit/3ba5ed46c8f1e03dd770bf80f181acf1f78de6e8).

The retained Feltzin color constructors now pass the packed-color result
to the spawner independently of the converted angle; their smaller frames
and timer/state lifetimes still differ. The half-speed store in
`func_L05_00426568` is unconditional in retail and in its corrected draft.
`func_L22_003C9D48` clears and copies local vectors, not controller fields.
These semantic repairs are not matches. The three Joba visibility bodies
remain 628/632 bytes with a 0x70 frame instead of 0x80 after restoring the
true absolute entity-pool pointer and integer dispatcher interface.
Preserve those fixes; their former invented array extent was not valid.

Large Snivelak trail renderers still need independent packet/state-lifetime
evidence. In `func_L07_003E5070`, the two observed 144-byte packets and the
64-byte/48-byte matrix outputs leave an additional retail local range
unqualified. Do not invent a third packet, padding or a complete global
extent to reproduce the frame. Complete corrected C and measured reopening
conditions remain in `nonmatching/`.

**Additional qualified source remedies, 25 October 2026:**
Three Aranos constructors/updates, four Yeedil handlers, a Snivelak
constructor, two shared list/counter handlers and an Oozla effect add
11 functions, 2,976 distinct bytes and 42 accepted carrying placements.
The source keeps actual pointer returns, full aligned transfers, correct
guard polarity and the real integer counter identity. All 84 strict
programs pass; complete host/runtime source sets and hashes agree before
and after qualification, with no compiler change or report regeneration.
[Source remedies and retained large reconstructions](https://github.com/OpenRAC/rac2-decomp/commit/bf60a47f1dacbbda3eb97762998188e3b4fd89ee).

Larger Endako, Jamming Array and Snivelak bodies remain near misses.
Their corrected C preserves actual record strides, audio-bank views,
aggregate alignment and context overlaps instead of fabricated extents.
Store scheduling, state branches, floating setup and saved-value lifetimes
remain measured constraints; equal sizes and matching prefixes are not
matches. Keep the per-source residuals and reopening conditions when
revisiting them. The Yeedil handler with a remaining post-branch nop
is another witness for the scheduling issue in [section 30](#blocker-30),
not proof that the function is handwritten or impossible in C.

**Mixed transfers and independently bounded storage, 25 October 2026:**
`func_L00_003F3518` keeps its two stack copies as ordinary TImode
assignments and uses `qcopy` for two external transfers. Its real scratch
storage is a 0x460-byte buffer, a 0x120-byte color array and six vectors;
blanket helper substitution gives 648 bytes rather than the qualified 644.
`func_L02_003D6690` uses four `qcopy_nc` table writes only after checking
source and destination independence, including later accesses. Its
captures and dependent transfers still clobber memory. The existing
per-file `-frac2-hazard-labels` profile is unchanged.
`func_L11_00442B60` restores the dot helper's second vector input and three
full aligned vectors. These three functions add 1,792 distinct bytes and
41 accepted placements across the releases; all 84 strict programs pass.
[Qualified sources and retained reconstructions](https://github.com/OpenRAC/rac2-decomp/commit/db63b6b650a4765c84221ea7e3dfdda96f9ce1fc).

Retained renderers require semantic review before allocator tuning. The
actual `func_00283678` output is 48 bytes, whereas `func_00283698` writes
64; qualify each producer independently rather than transferring an extent
between similar names. The corrected Yeedil beam stores noise Z before
publishing its vector, changing its frame from 0x440 to 0x430 while leaving
the 5,716/5,868-byte residual unchanged. Preserve that order even when an
older, incorrect variant fit the frame better. Its Aranos counterpart
remains 5,828/5,868 with independently measured scratch ranges and a
0x440 frame. Neither frame agreement nor a size improvement is a match.

**Storage and source identity before allocator tuning, 25 October 2026:**
Retained `func_L02_0043F4C8` had three matrix rows but calls
`func_00283698`, whose output needs four rows. `func_L02_00421860` had
a 32-byte impact record, but its initializer writes a word at +0x20;
the aligned record needs 48 bytes. The real phase-local union and complete
query fields recover the corresponding retail frames without invented
padding. They remain near misses. For the beam packet, the initializer
touches 36 bytes and the handwritten query consumer copies 40; the
existing aligned 48-byte record covers both observed spans.

`func_L00_003A3B58` also loads a quadword using a scalar's eight-aligned
address. [PCSX2's LQ implementation](https://github.com/PCSX2/pcsx2/blob/master/pcsx2/R5900OpcodeImpl.cpp)
rounds the effective address down to 16 bytes. This does not establish
the surrounding C object's ownership or extent. The retained diagnostic
stays unlinked; do not invent a vector global or bypass the reviewed
copy helper's alignment precondition to claim a match.

Check the generated behavior as well as the source. Two identifiers with
the same assembler label can still hide their overlap from the compiler.
In retained `func_L23_0041A7A0`, separate GP/absolute views made a clamp
compare the old value: old 9 plus increment 2 with maximum 10 would leave 11.
One scalar identity restores the compare against the sum, even though
mixed retail address selection remains unmatched. Similarly,
`func_L23_0041D398` now represents its observed ten pointer slots as one
array with two five-slot windows; indexing past a declared five-element
array was invalid even when another array followed it physically.

Verify initialization and comparison polarity in each body's own retail.
The Aranos/Grelbin beams zero Z before publishing the vector. Two burst
effects also contain unconditional drift clears omitted by their older
drafts; this is different from a genuinely uninitialized retail read.
Preserve unordered branch behavior instead of rewriting every inverted
comparison as an ordered `<=` or `>=`. Complete corrected reconstructions,
their actual release coverage and reopening conditions remain unlinked;
equal size, matching frames and prefixes receive no matching credit.
[Retained source corrections](https://github.com/OpenRAC/rac2-decomp/commit/7799e607437c4e999af6be52050c904bbc5ef069).

**28 October 2026, retained near miss:** `func_002A8F70` (USA v1.01, 340 bytes,
boot and 27 level placements) has a 312-byte C candidate under the default
`-O2 -G0 -ffunction-sections` profile, 0/28. It models the existing-entry
owner/time test, flag merge, ring insertion, VU helper call and two real
16-byte transfers with reviewed `qcopy`. Retail saves s0-s7 in a 0x50 frame;
the candidate's 0x40 frame saves fewer registers. An explicit threshold
`if`/`else` compiled to 316 bytes; a reused local ring-table base gave 304.
Both alternatives also match 0/28. On 29 October 2026, temporarily integrating the retained body into its actual `src/game/002A7750.c` translation unit and reusing its existing `L_A8E20Entry` and table declarations compiled to 324 bytes, 0/28; retail is 340 bytes with a 0x50 frame and saves s0-s7, while the integrated candidate keeps the 0x40 frame. The previously recorded standalone 312-byte result was not reproduced in that translation-unit context. Reopen with an independently justified value-lifetime or register-allocation shape; do not add dummy state to force saves.

<a id="blocker-23"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L02_00421860` is C in `src/levels/shared/L02_00421860-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 2 US, 2 US2 places (PAL catalogue has no function of this name); `func_L22_003C9D48` is C in `src/levels/shared/L22_003C9D48-g8.c` (`-O2 -G8 -ffunction-sections -mno-split-addresses`), placed at 2 US, 2 PAL, 2 US2 places. The measurements above are kept as history.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_002A8F70` is C in `src/game/002A7750-records.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places. The measurements above are kept as history.

## 23. Keeping a branch in step with master (tooling, not a wall)

Contributor PRs leave the generated README progress table and progress/report.json alone. A maintainer regenerates them on master after the strict build. The old advice to regenerate them on every contributor branch is superseded by AGENTS.md. Resolve source/nonmatching conflicts against current master while preserving concurrent work.

When a maintainer does regenerate on Windows, inspect the actual diff and line endings; do not assume Git normalized them or rewrite files unnecessarily.

Merged PR #252 invalidates cached objects on toolchain changes and supplies `tools/build.py all --strict`. It rejects C fallback even if the reconstructed program otherwise equals retail. Cached output, a quick check or an OK line with rejected C is not sufficient acceptance evidence.

<a id="blocker-24"></a>

## 24. Prologue and entry-block ordering

**All named examples now resolved:** func_L01_002F1888 passes 5/5, func_L00_003ECB00 passes 27/27 and func_L20_0039DE88 passes 1/1 in the PR #246 touched-unit review. Old ordering differences do not establish a current universal wall.

**Signature:** the same instructions, in the opposite order at the top of the function: retail
`addiu $sp,$sp,-0x10` then `lui`, or `sd $s1,0x8($sp)` before `sd $ra,0x10($sp)` where cc1 emits
the reverse; also a constant materialised before the frame adjustment in retail and after it
here. About 18 of the 240 worker notes carry this shape, in bodies that are otherwise exact.

**Measured examples:** `func_L01_002F1888` ("retail does `addiu sp,sp,-0x10` THEN `lui
v0,0x1B`; gcc reorders it"); `func_L20_0039DE88` (retail `sd $s1,0x8($sp); sd $ra,0x10($sp);
jal ...; daddu $s0,$a0,$zero` against ours `sd $ra,0x10($sp); daddu $s0,$a0,$zero; sd
$s1,0x8($sp)`); `func_L00_003ECB00` (retail `addiu $v1,$zero,0x3` before `lui $v0,0x1B`).

**Current approach:** compare matched source lifetimes and per-file profiles. The accepted -mastra-keep-frame-order option controls frame-related scheduling, not every prologue/block-order discrepancy; qualify the entire affected unit.

`func_L00_002D71A0` has a complete retained 32-record selector and dispatch body:
1108/1104 bytes, 0/27 placements in each release with `-O2 -G8 -ffunction-sections`.
Its first difference at +0x4 accompanies the pool's high address being materialized
in v0 and copied to s4, where retail keeps that value directly in s4. Later pointer
lifetimes, slots and return joins also differ. A typed-array source was 1132 bytes;
the byte-offset record view reduced it to 1108. Disabling GCSE gave 1116; disabling
sched1 and changing scan/declaration spelling were neutral. A positive selected
guard plus a named zero gave 1112. Reopen with an independently supported source
shape for the shared global-address lifetime, rather than repeating those forms.

<a id="blocker-25"></a>

## 25. Small constants: rematerialised against reused (both directions)

**Signature:** retail materialises a small constant once and keeps it in a register, often also
using that register as a later call argument; cc1 rematerialises it at each use. The reverse also
happens: retail materialises the same constant twice and cc1 CSEs the two into one.

**Measured examples:** `func_L14_00425C08` (retail materialises `addiu $t0,$zero,0x1` once and
`$t0` is argument 5); `func_L11_00456438` (the constant 1 materialised twice in retail, `$t0` for
the stores and `$a3` for the argument, where cc1 reuses `$a3`); `func_L18_00437AA0` (retail
materialises `0xFF` **twice**, `addiu $v0` then `addiu $v1`, cc1 keeps one).

**Historical result:** these attempts did not close the named cases, which remain markers. Temporaries sometimes changed materialisation; that is a case-specific observation, neither a guaranteed repair nor proof that none exists.

**25 October 2026 phase isolation:** `func_00308600` is still 356/360 bytes,
0/28 in both USA releases; its PAL catalogue name is absent. The initial RTL
contains separate HI- and QI-mode constants of 255. CSE1 removes the QI
pseudo and substitutes the low byte of the HI pseudo, before scheduling or
allocation. Writing the byte sentinel as `-1` while retaining its unsigned
field type canonicalizes to the same QI constant and gives an identical
complete object. Changing field signedness or inserting a barrier is not
justified by that observation.

The pinned public GCC `cse_insn` path searches wider integer modes for this
constant and builds a low-part view. That path has no
`flag_expensive_optimizations` guard; nearby guarded AND/MEM transformations
are different paths. The maintained game patch 0048 does not change this
block. Do not infer that `-fno-expensive-optimizations` controls it or start
another flag sweep. The measured pointer/count priority tie could change if
a real source change restored an instruction within their live intervals;
that arithmetic model is a hypothesis, not a matching result. A compatibility
proposal would need independent witnesses and neutral controls first.

<a id="blocker-26"></a>

## 26. A dead store or dead load that retail keeps

**First example resolved:** func_L20_004095D0 is C and passes 1/1 with two measured addressing forms of the same real global. func_L18_00432630 remains open; its liveness diagnosis must include exact R5900 operands and control flow.

**Signature:** cc1 proves a store (or a load whose result is never read) dead and deletes it;
retail keeps it. The body is then one instruction short in the tested source. Establish genuine deadness under the ABI/control flow before assigning a cause.

**Measured examples:** `func_L20_004095D0` ("gcc removes the first store (a dead store to the
same symbol); retail keeps both"); `func_L18_00432630` ("`lh $v0,0x7FC($v1)` is missing -
it is a DEAD load in retail (`$v0` never read again), which the old note treated as a dead-load blocker; that inference needs its exact ABI/control-flow evidence").

`func_L00_002A4928` contains two measured gathers of seven resident slot words
into the same local storage, around the state clear; the second loop is not a
scatter back to the global slots. The retained complete C preserves that ordering
without volatile or artificial uses. It reaches 1000/1008 bytes, 0/27 USA v1.01
placements; its canonical name is absent from both other release catalogues.
Direct resident references remove a spilled full-base pointer and recover retail's
0x90 frame, but high/base address lifetimes and scheduling still differ. A typed
field view shortens the body to 984 bytes; disabling GCSE or sched1 gives 996.
Independent alias/lifetime evidence is the next useful input, not more identical
loop spellings.

The way out that closed two of these: jump2 cross-jumps two arms that end the same, the branch
goes, and the load that fed it stays dead, because flow ran before jump2. `func_L18_00432630`
keeps two equal arms on `0x7FC`. `func_L18_002CA350` (1 November 2026, local match) keeps
`if (hero[0x340]) { if (mode == -1) return; } else { if (mode == -1) return; }`, which gives the
dead `lw`; it also ends the extended block, so the hero address is built again in the next block.

**Consequence:** retain unresolved attempts and their bounded stopping reasons. Do not label the whole category unexpressible or add volatile/artificial uses solely to preserve an operation.

<a id="blocker-27"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L18_00432630` is C in `src/levels/18_damosel/L18_003F80A0.c` (`-O2 -G0 -ffunction-sections`), placed at 1 US, 1 PAL, 1 US2 places. The measurements above are kept as history.

## 27. The missing `andi reg,0xFF`

**All three named examples now resolved:** func_L12_003DE4B0, func_L18_00432E28 and func_L12_00404778 each pass1/1. The missing-mask descriptions below are historical.

**Signature:** retail narrows an incoming byte with `andi $v1,$a1,0xFF` - the mask comes from the
`u8` to `int` promotion, compared in SImode - while cc1 folds the mask away and the body comes
out one instruction short.

**Measured examples:** `func_L12_003DE4B0` ("the `andi $a0,$v1,0xFF` instruction is missing: retail
compares the WIDENED value in SImode (the mask comes from the u8 -> int promotion), and this
compiler folds it away"); `func_L18_00432E28`; `func_L12_00404778` (the same mask missing).

**Current conclusion:** consult each matched source/profile. Those earlier folds did not prove every legal extension form would fail. Other bodies need their own measurements.

**Byte range tests (2026-10-26):** `x == 6 || x == 7` on a byte becomes `(u8)(x - 6) <= 1`, and
combine's stock range fold (simplify_comparison, SUBREG case) drops the `andi 0xFF` whenever
the byte's nonzero bits are known, which is what retail shows at most sites. In the moby
animation idiom (the anim byte re-read at the join after two call arms, an `== K` test,
then the range test) retail keeps the `andi`: re-read the field in both tests instead of
caching it in a local (`if (*(u8 *)(self + 0x43) == 0xB) ... else if (*(u8 *)(self + 0x43) == 6
|| *(u8 *)(self + 0x43) == 7)`). Measured in func_00322CC0; the same idiom is in
func_L04_003E2438, func_L04_0044C598, func_L11_0042F018 and func_L17_003E31E8.

<a id="blocker-28"></a>

## 28. Commutative `addu`: base first against index first

**Current update:** func_L00_002AE070 is among PR #244's newly reviewed additions and passes 27/27. This resolves that example, not all commutative allocation ties.

**Signature:** retail computes `addu dst,base,index`, cc1 emits `addu dst,index,base` (or the
register numbers differ for the same reason). The instruction count and everything else are
right.

**Measured examples:** `func_L23_00419088` (`addu $v1,$a3,$v1` against `addu $v3,$v3,$a3`);
`func_L00_002A7DE8` (three `addu` with the scaled index first where retail puts the base first);
`func_L00_002AE070`.

**Workaround, measured later:** `p += ((a1 << 5) + 0x10); p[2] = v;` gives `addu $a0,$a0,$v1` (destination = the base register, as retail writes it) where the inline `p + 0x12 + (a1 << 5)` gives `addu $v1,$v1,$a0`; the pointer-increment form is the one to reach for when retail writes into the base. Otherwise none - "every other spelling tried (flat, `[idx]`, int pointer, index-first) gave the same order". **Wave 8 measured two more for the materialised-base case:** hoist the pointer - `char *q = st + idx * 4;` then `*(int *)(q + 0x70)` gives `addu $a0,$a2,$a0` (base first, as retail writes it) where the inline `st + idx*4 + 0x70` gives `addu $a0,$a0,$a2` - and a `(u32)` cast on the pointer (`(u32)D_x`) forces base first where the indexed spelling gives index first. The first matched a body first try.

<a id="blocker-29"></a>

## 29. Loop-form canonicalisation: countdown and one-step unroll

**Signature:** retail keeps an ascending signed counter with `slti` + `bnez`; cc1 rewrites the
loop as a countdown, or unrolls the body once. Distinct from section 2: nothing is hoisted here,
the loop's own form is changed.

**Measured examples:** `func_L05_0041C7E8` (retail runs 0,1,2 with `slti $v0,$a1,0x3` + `bnez`,
every source shape compiles to a countdown); `func_L00_00403CB8` ("the scanning loop is compiled
as a loop unrolled once by cc1").

**Historical result:** the tested while/for/do-while forms folded for those versions. Current notes also record a guard/count-up/break shape for func_002ED368. No loop syntax alone guarantees emission order. But one **skeleton** measured in wave 8 is not rewritten: a pointer loop written as `for (cur = G_start; cur != G_end; cur += 0x100)` - **both bounds read from the globals in the condition** - comes out as written, neither counted down nor unrolled; keep the comparison against the globals in the test rather than copying them into locals first.

<a id="blocker-30"></a>

## 30. Loop-alignment padding

**Partial resolution:** func_L22_003A48F8 passes 2/2 and func_L23_00419CA0 passes 1/1. The historical qcopy experiment below predates the reviewed-helper exception and still needs its own current linked check.

**Signature:** the `nop`s the R5900 pass puts in front of a loop head are missing, or there is
one too many, shifting the loop by a word. The pass is named in one note
(`mips_r5900_pad_loops`).

**Measured examples:** `func_L05_003D02C8` ("the 8-byte loop-alignment nop before the loop label
does not appear"); `func_L23_00419CA0` (64-byte target, attempt comes out 68 - one extra `nop`);
`func_L22_003A48F8`.

**Mechanism, measured 2026-10-13:** the R5900 pass (`mips_r5900_pad_loops`, a post-DBR hook)
pads every loop to seven **counted** instructions, and an `asm_operands` - which is what
`qcopy` is - counts as one while emitting two words (`lq`+`sq`). A retail loop that counts
seven therefore gets a parasitic `nop` when the body uses `qcopy`. Writing the same loop in
`mode(TI)` drops the pad but makes cc1 strength-reduce the counter to the decrementing form
(`addiu -1`/`bgez`) where retail increments with `slti`/`bnez`: the two levers fight, and no tested source closed that particular combination in the recorded attempts.

**Current guidance:** retain exact unresolved loop/profile evidence. Do not add dummy statements or instructions for alignment; qualify a meaningful source/profile change.

<a id="blocker-31"></a>

## 31. lui at / low-half access: an existing per-file profile

Wave 8 probes found -mno-split-addresses produced the required absolute-access form in particular units, and originally presented it as future infrastructure.

The infrastructure now exists: many dedicated units already use the flag in config/cflags.txt. It is not the only way to produce every at-based access; declaration size/attributes, profile and assembler context still matter (section 8). A probe's “only” must not become a universal rule.

PR #246's func_L20_00444138 is a current 1/1 witness in a G8/mno-split-addresses unit, also using the two true addressing forms of one bound. Isolate incompatible profiles in separate files and recheck all C in a changed unit.

**25 October scalar-store witness:** `func_0028A278` qualifies at 128 bytes,
28/28 placements in each release, in its own `-mno-split-addresses` unit. The
ordinary independent stores must also use the correct canonical globals and
order; a size-only result hid reversed bindings. The existing canonical helper
interface is preserved. The final tree passes all 84 strict programs.

<a id="blocker-32"></a>

## 32. The output for a body depends on the other functions of its unit

**Current update:** func_0032B3E0 now passes 1/1 in its actual reviewed PR #244 unit, with touched-unit regression checks passing. func_0032FDD0 is also C, but was not separately rechecked in this audit. Other listed attempts are not assumed resolved.

**Signature:** a body that `tools/check.py` reports as exact in one file comes out several words
over in another file, with **identical sources and identical declarations**. The compiler emits a
different body for the same source depending on what else the file holds.

**Measured (waves 10 and 11, on the upstream merge):** `func_00328F18` 444 bytes against 436,
`func_0032B3E0` 452 against 436, `func_0032FDD0` 228 against 216, `func_L00_003CC030` 424
against 360, `func_L00_003E6F48` 160 against 124, `func_L00_003E70B8` 500 against 436,
`func_L01_002E1680` 428 against 416, and `func_L00_002F46C8` one instruction off at +0x20. Each
matched first try in the agent's own file; the upstream file holds more functions than the
agent's did.

**Consequence:** a match has to be **re-checked in the file it will live in**, and the check
that counts is `tools/build.py`, not `tools/check.py` in the worker's tree. Where a body's own
unit cannot hold it, it needs a file of its own.

**Exception-runtime profile, qualified on 28 October 2026:** the historical
`func_00120F00` near miss was 480/476 bytes, with the exception-return stub in
the wrong position; thirteen source rewrites had not fixed it. Its paired
`func_001210E0` was incorrectly screened as geometry code. Both are public
GNU EE libgcc `L_eh` routines (`__throw` and `__rethrow`). The existing SDK
`-O2 -G2 -ffunction-sections -fexceptions` profile closes both in isolated units:
476 and 484 bytes, one boot placement each in USA v1.01, USA v2.00 and PAL.
Their real `frame_state` objects are each 0x2F0 bytes; the compiler's public
unwind builtins provide register preservation and exception return.
[The source change](https://github.com/OpenRAC/rac2-decomp/commit/78e70068441cbc77f608ea2b685e233a682fc8d5)
passes all 84 strict programs after integration, with 313 unit tests. This is
the existing runtime profile, not an instruction patch or a general remedy
for unrelated save-order and register-allocation differences.

**A separate linked-section dependency, verified on 24 October 2026:**
`func_00306040` passed local checks while its direct same-unit call required
`.text.func_00305838`, a boot-only catalogue identity. The level programs instead
call the already-C `func_L00_003883B8`. All 84 retail call sites resolve to these
144-byte, byte-identical packet initializers, each consuming one output pointer.
Using the genuine per-program external `ref_00306040_01(void *packet)` preserves
both catalogue identities and resolves the dependency; the existing build then
passes all 84 programs with `--strict`. This is an application of scoped references,
not an alias or a reason to import a boot-only section into every level. A local
match cannot establish that the complete program can resolve its C dependencies.

<a id="blocker-33"></a>

## 33. The 64-bit difference in specific attempts

Three historical candidates differed in pointer/index width, retained copies, sign extension or constant expansion: func_00349610, func_0028AB20 and func_00288970. They remain markers. Approximately twenty source forms per selected case and the SDK profile did not close those attempts.

Those results do not establish that all retail 64-bit arithmetic differs from the reconstructed compiler or that most shared game rows are blocked. Existing exact C uses 64-bit packet fields and operations; opt-in conversion support also covers measured patterns. Preserve each candidate's exact ABI, instructions and profile before assigning a mechanism; a variable's inferred 64-bit type is not by itself an impossibility test.

<a id="blocker-34"></a>

## 34. The catalogue's fingerprint merges two bodies

**Unresolved hypothesis:** the 23/27 report was not remeasured here. Its field offsets differ from section 12's description; re-extract current extents before a generator change. The 82 historical candidates are not 82 proven collisions.

**Suspected mechanism:** address-taint masking can group constants treated as address fields. The current generator compares ordinary untainted small immediates; it does not blindly mask every small immediate. Same-fingerprint candidates require byte-level review.

**Measured:** `func_L00_00424BB8` is the level's float setter in 23 levels (base `q + 0x60`,
fields at `+0xDC`/`+0xE0`) and another body in levels 16, 22, 23 and 26 (base `q + 0x20`,
fields at `+0x1C`/`+0x20`); the matching body in level 16 sits at `0x0042FB58` in its own row,
`func_L16_0042FB58`. No source shape can produce both, because the offsets are constants.

**Extent:** 82 of the 2,509 single-place rows carry the fingerprint of a multi-place row and are
candidates for the same collision (`func_L01_003BAFB0` against `func_L00_0037E668`,
`func_L02_003E9BB0` against `func_L00_003973E8`, `func_L02_00401298` against
`func_L00_002E94B8`). It is a `tools/levels.py` fix - the masking of the small immediates on a
non-tainted base - not a C problem.

<a id="blocker-35"></a>

## 35. The catalogue's linker-fill rows

The historical scan estimated about 6,000 of the then 106,337 placements opened with stack-adjustment/nop forms. Those are dated observations, not today's remaining denominator.

The old claim that C always ends in jr is false: trap and tail-call functions can have no jr. func_00115E90 is a concrete matched trap-ending example. Removal needs measured words/operands and surrounding extent/reference evidence.

The earlier filler and immediate epilogue-residue rules are implemented through PRs #239/#241; section 47 retains their historical counts. A mixed filler prefix followed by real code needs a boundary correction, not wholesale deletion.

<a id="blocker-36"></a>

## 36. -mno-split-addresses also keeps some symbol addresses together

The flag can keep lui and its low-half calculation together where the tested default profile split them. This is a measured unit-level effect, not a universal address rule.

Current witnesses: func_L00_003EA7D0 has its dedicated profile and passes 27/27; func_002A90C8 passes 23/23 in its existing profile. Older examples func_002B0C28 and func_002B0CE0 remain markers and are not resolved by those successes.

Section31's proposed infrastructure is present. Requalify every C function when changing a unit's flags; isolate incompatible profiles.

**1 November 2026 (local matches):** `func_L17_003A4740` and `func_L00_003A09F8` (17 places)
needed no `-mno-split-addresses`. The viewport words are one `MACRO_ADDR` array: `[2]`, `[3]`,
`[0]`, `[1]` keep their `lui` in the destination register, and an offset element is two
instructions, so it cannot fill a slot, which `[0]` of a scalar would. The phase word's
`lui; addiu; lwc1 0(reg)` is reload's: a pointer set outside the inner loop is hoisted by loop,
gets no register because every saved register is taken, and its constant is not a valid split
address, so reload builds it beside the load. The hoisted pointer also uses up the threshold
that stopped the colour constants at the inner pre-header.

`func_L00_003B9310` (same date, local match): a `MACRO_ADDR` scalar read by `lui`/`lwc1` and
written by `$gp` in a slot is one symbol to sched, so the read stays above the store and gets the
store's height in the priority chain. Two names for the word (`sda` or `SDATA` views) lose that
dependence and the load sinks. Its other 9 words were a prototype: the integer target is the
last parameter, after five floats.

<a id="blocker-37"></a>

## 37. Decode the exact R5900 instruction, not a broad prefix

The earlier classification and formula were wrong. lq/sq are load/store major opcodes 0x1E/0x1F, not MMI1/MMI3. Their encoding is `opcode << 26 | base << 21 | target << 16 | (offset & 0xFFFF)`. Thus 0x78A20010 is lq v0,0x10(a1) and 0x7FA20020 is sq v0,0x20(sp). 0x78/0x7C are high-byte shapes, not six-bit opcodes to shift by 26.

**0x700014A9 is por v0,zero,zero, not pcpyld.** Major opcode 0x1C contains multiple EE operations, including compiler-emitted cases. It is not a universal “MMI0, no C spelling” category.

Use `rabbitizer.Instruction(word, address, rabbitizer.InstrCategory.R5900).disassemble()`. Generic INVALID output, a broad 0x7000 prefix, or por/lq/sq/ldl/ldr alone is not handwritten-assembly evidence. Inspect exact operands and control flow.

<a id="blocker-38"></a>

## 38. What this cc1 has no spelling for

**Scope correction:** these are particular builtin/source probes. A missing builtin makes that route unavailable, not every equivalent arithmetic expression impossible. Re-evaluate mfc1 observations under the qualified fix; no blanket floor/sync solution is claimed.

- **No `__sync` builtin.** `__sync_synchronize()` becomes a call to an undefined external and only
  inline asm emits the `sync` instruction, so that particular builtin does not lower to sync in this compiler. Inline assembly remains prohibited in matched C.
- **No floor builtin.** `floorf`, `__builtin_floor` and `__builtin_floorf` all become calls to
  undefined symbols, and a `(s32)` cast is a plain truncating `cvt.w.s`, so those forms did not reproduce the recorded branchless-floor sequence; other ordinary-C formulations are not thereby disproved.
- **The tree-level fold merges `pi + pi`** into one 2¤Ç constant, where retail doubles ¤Ç at run
  time (`add.s $f1,$f14,$f14`); two separate statements are not folded, so the retail's two
  `add.s` need them.
- **A float-bit return may need the full R5900-width value.** In `func_002829D8`, retail moves
  the float bits to a GPR, shifts them into the high word, and compares the signed 64-bit result
  with 1 before subtracting 2. The -G8 C form using an unsigned 64-bit shift is 76/64 bytes;
  the union-word form is 100/64. Both match 0/28 USA placements. Do not simplify its first arm
  to an unconditional -1: positive and nonpositive input bit patterns return different values.
- **A float's sign bit comes out as `mfc1` plus a sign extension** where retail has `mfc1` plus
  `sra`; the tested union, cast and file-scope forms did not remove it in their recorded profile.

<a id="blocker-39"></a>

## 39. Source shapes that moved a body

These are measured source/ABI effects, not permission to invent barriers or false types:

- func_002FC560's stored second argument needed its measured 64-bit type; changing it to int changed emission.
- Two true names for one measured global sometimes preserved repeated address materialisation; a separately retained base sometimes preserved a later addiu. Every alias must state the real identity and pass all bindings.
- Named masks and block-local lifetimes sometimes changed allocation/frame size. Outcomes are per body, not universal declaration-order rules.
- A guard that genuinely exits can leave a different delay slot from one followed by live work. Some store permutations also moved scheduling; other blocks behaved differently.
- Return declarations affect v0/f0 availability, even when a caller ignores a result. Ignoring it does not prove the callee is void: use ABI evidence, not knowingly false prototypes.
- `func_L00_003D5358` is a retained 336/336-byte near miss in all three releases
  (0/27 each, `-O2 -G8 -ffunction-sections -g`): only the float target move and
  velocity-pointer setup exchange order at +0x104/+0x108. Its real
  `func_002AA898(position, velocity, direction, target, acceleration, damping, limit)`
  declaration is preserved. The same prototype constraint affects the retained
  `func_L00_002B9380`; a direction-last declaration cannot be used to obtain a match.
- A dead-store observation differed between ordinary code and a delay slot in the sample. Reconfirm actual liveness and control flow; do not manufacture a memory effect to preserve it.

**28 October 2026, loop-layout probe:** `func_0029CF78` polls `0x1000D400`.
In its original `-O2 -G0` source unit, an explicit forward `goto` to the exit
followed by a `goto` to the loop compiled to a 40-byte conditional-backedge
loop (0/28 USA placements). cc1 canonicalized the requested branch-plus-jump
shape, and the three nops remained after the mask instead of between the load
and mask. Its retained best remains 44/56 bytes; this confirms that this
particular label spelling does not unblock the loop layout.

<a id="blocker-40"></a>

## 40. Smaller things worth knowing

- **The fifth to the eighth arguments travel in `$t0`-`$t3`,** not on the stack. A body that
  reads `$t0` without a fifth parameter is not a catalogue defect.
- **Audit the whole call interface before fitting register allocation.** A current C wrapper
  can omit live forwarded inputs or a return. `func_002AFF08`, `func_L02_00329C48`
  and `func_L00_00341A88` leave a floating result in `$f0`; their declarations must
  return it. `func_L02_00329C48` also forwards its third pointer to `func_002B04E0`.
  `func_L00_003253A0` forwards two pointers and a float to `func_002B00D8` after
  adjusting only its first pointer. Explicit contracts reproduce the existing
  instructions; these repairs add no new-function credit. Check stack arguments
  beyond the eight GPR slots as well: the retained `func_L03_003C3220` calls
  `func_0032C700` with four additional slots, `1, 0, 0, NULL`. The helper
  consumes eight GPR inputs, two floating inputs and those four stack slots;
  its last slot is a nullable pointer, and it returns the allocated object pointer.
- **A byte match can hide an incomplete C interface.** Existing wrappers can leave
  an incoming register or final result untouched without naming it in C. Restoring
  explicit forwarding makes the contract usable beyond that accidental preservation.
  `func_002AA738(float, int, float)` preserves the established interleaved parameter
  order and forwards both floats to `func_00283BE0`; `func_L00_002B9B38` returns
  its float result. Its `func_002830C0` scratch is four floats, even though only
  the first two components are read afterward. The old two-float declaration
  understated the vector write; the honest 16-byte buffer preserves retail's frame.
  The same input/output audit restores `func_L01_0031BC68`'s live float and integer
  result, `func_002703B0`'s float result, and the live pointers in
  `func_L00_003252A8` and `func_L10_0039D728`. Verify the caller, callee and all
  carrying placements before accepting
  such repairs; they add no new-function credit.
- **A pointer-shaped prototype can conceal a numeric argument.** The third GPR
  input of `func_L16_004116C8` is a signed 32-bit transition duration: its callee
  tests it with `bgtz`, converts it through `func_00283CE0(int)` and takes a
  reciprocal. Preserve the separate float input and use an integer duration;
  casts of frame counts to `void *` are not the semantic contract.
- **An integer register does not imply an `int` result.** The retained
  `func_L00_002A3B88` forwards `func_0028E640`'s complete 64-bit texture descriptor
  to `func_0028F410`. The callee builds it with a shift and OR; truncating to
  32 bits would be a false interface even if a later allocation looked closer.
- **The dialect is C89:** `long` and `long long` are 64-bit, `int` and pointers are 32-bit, and
  there is no declaration after a statement.
- **The patched gas expands `move $rd,$zero` into `daddu $rd,$zero,$zero` and `li $v0,1` into
  `addiu $v0,$zero,1`:** in a disassembly neither is a difference.
- **A `sda` declaration needs a size,** and the relevant extern/assembler behavior depends on the unit profile and context; the recorded G8 result is not a universal declaration rule.
- **`__attribute__((sda))` on a global in a `-G0` unit gives retail's `lui %hi ; sw %lo($at)`
  form.**
- **Integer branch-likely slots execute on taken paths:** `beql`/`bnel` run their delay slot only
  when the branch is **taken**, which is taken-only behavior, not an inverted-annul rule. Do not generalize this to a differently decoded instruction.
- **`movz`/`movn` are emitted** (`c ? a : b` gives `movz $2,$5,$6`, `if (b) r = 0;` gives
  `movz $2,$4,$5`), so a retail body that uses them is reachable. Where `--diff` shows one
  against a retail branch, section 16's spelling is the thing to try.

<a id="blocker-41"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_0028E640` is C in `src/game/0028E640-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places. The measurements above are kept as history.

## 41. The productive route

Historically 16 of wave 8's 24 matches came from matched siblings/fingerprints. Four workers over 104 already-attempted functions found no match in that survey.

The conclusion that the entire near-miss corpus is exhausted is withdrawn. New source forms, qualified profiles and diagnostics can change old results. PR #244's reviewed seven-function delta includes five matches obtained by permuting earlier near misses. That does not promise every old attempt now matches; it does show why one dated sample cannot exclude the corpus permanently.

Use measured siblings, final unit/profile checks and a bounded budget. Reopen a stopping point with concrete new evidence, not merely more equivalent spellings.

<a id="blocker-42"></a>

## 42. Register-allocation ties: a stopping signal for tested forms

**Current counterexample:** func_L22_00328220 passes 2/2. The other named attempts remain open. Eight identical variants establish a stopping point for those variants, not the absence of every source/profile lever.

**Signature:** two values compete and the tested source forms did not change their allocation. The
`.lreg` dump (`cc1 -dl`; each pseudo carries `refs`, `live_length`, `crosses N calls`) shows the
tie: two pseudos with *identical* statistics, and `local-alloc` breaks it by pseudo number.

**Measured:** `func_L05_0037AC00` and `func_L22_00328220` - **eight** source spellings of the
same arithmetic produce the same allocation. On `func_L05_004424B8` the `.lreg` RTL shows `cse`
folded `head = a1 + 0x30` into `(plus (reg 84) (const_int 48))` at every use, so `a1` and `head`
are **one** pseudo living across three calls: no reference count can make it eligible for `$a1`.

**Consequence:** check the `.lreg` for a separate pseudo before touching reference counts. A value present only as `(plus (reg N) K)` explains why edits to a nonexistent separate pseudo cannot help; it is not a universal impossibility proof.

**23 October 2026, retained near miss:** `func_002D5048`, USA v1.01 only, 164 bytes at 28 places. The existing game compiler with `-G8` gives 164/164 bytes, 0/28; six tail words differ from the checker first mismatch at +0x70. A named first-path pointer and `nosda` output binding recover the prefix. Six compiles included the stub; the last three source forms gave identical bytes. The real C remains in `nonmatching/game/func_002D5048.c`, its source marker restored. Reopen with independent lifetime/allocation evidence for the second update path; this is neither a match nor a universal compiler limitation.

**23 October 2026, retained near miss:** func_00290B48, default game -G0 profile, 280 bytes at 28 places in each release. Four source arrangements reached retail size but left central allocation, immediate construction and store scheduling different. The retained C corrects memset to its destination-pointer return type; that corrected source is 280 bytes, 0/28 in us, pal and us2, first difference +0x3C. Nine checker invocations total. Boundary-reference roles are inferred and successful per-placement derivation remains unproven. Source marker restored; reopen with state-layout/store-order or matched-equivalent evidence.

**23 October 2026, semantic draft only:** func_00278EB0 remains a marker. Nine checker invocations measured an earlier default -G0 draft at 204 bytes, 0/28 placements in every release, with two independent additions swapped at +0x70/+0x74. Coordinator review found inaccurate callee declarations. The retained nonmatching/game/func_00278EB0.c now uses the existing 64-bit wait-mask and no-argument field-query signatures; its current bytes and placements are unmeasured. The earlier results are superseded as qualification evidence. Reopen with coordinate-type/scheduling evidence and validate the accurate ABI before claiming size or equality.

**23 October 2026, requalified 28 October 2026, retained near miss:** `func_0028E2A8` has a 332-byte plain-C `-G8` draft against 348 retail bytes, 0/28 in USA v1.01. Ten earlier target runs included one checker environment failure and an incomplete-array compile failure; the current-master `-O2 -G8 -ffunction-sections` check confirms the same 332-byte result. A separate 344-byte section-annotated diagnostic matched 0/28 in USA v1.01, PAL, and USA v2.00. Recomputing the second record lookup and moving to a G8 sibling improved the draft, but register allocation, branch layout, and external-address materialization remain different. The marker is restored; reopen with verified global storage and argument-layout evidence.

**23 October 2026, retained near miss; rechecked 28 October:** `func_0028B160` uses the default game -G0 profile in `src/game/00288D88.c`; retail is 292 bytes with 28 placements in each release. Six plain-C candidates were measured, and the best three reached 280 bytes, 0/28 in USA v1.01, PAL, and USA v2.00. Since the size differed, the checker did not perform relocation-adjusted byte comparisons. The retained draft models the count loop, renderer call, and scaled offset update. `python3 tools/regalloc.py func_0028B160 --version us` reports byte-identical baseline/dump objects under -O2 -G0; the candidate holds the address of `D_001B1894` in a saved register across the loop, while retail rematerializes the address each pass and uses `$s6` for the shift base 1 (candidate uses `$fp`). This narrows the allocation difference but supplies no source-level remedy yet. The marker is restored; no full build was run.

**23 October 2026, rechecked 28 October 2026, retained near miss:** `func_00280670` is 160 bytes with 28 USA v1.01 placements. The retained record-based counted-threshold loop compiles to 152 bytes, 0/28 in current-master USA v1.01. Reversing the `count`/`total` declaration order leaves the output unchanged. The body still differs in total/count and input-pointer allocation, loop setup and result-pointer reconstruction. Ten earlier plain-C forms were also 152 bytes; PAL/USA v2.00 checks are historical because those ROMs are absent from this checkout. Reopen with verified record-layout or argument-liveness evidence; the marker is restored and no full build was run.

**23 October 2026, retained near miss:** `func_002BCB00` is 340 bytes with 28 placements in USA v1.01 and USA v2.00; PAL has no catalogue entry for the name. Nine default-game-profile source compiles included one failed literal form; the eight compiled variants measured 328, 324, 328, 332, 332, 332, 332 and 336 bytes. The best candidate matched 0/28 in both releases. Its saved-register assignment, pointer setup, and scheduling around vector copies and the float constant still differ. Reopen with ABI or allocation evidence; the marker is restored and no full build was run.

A separate argument-setup tie remains in `func_L00_002A5048`: the retained C
produces 800/800 bytes with `-O2 -G0 -ffunction-sections -frac2-qcopy
-frac2-qcopy-barrier`, but passes 0/27 in both US releases (no PAL catalogue
entry under this name). Only four words differ: the `$f15` zero move and
`$a2 = 2` exchange order in its first two `func_002AA898` calls, beginning
at +0x1F8. Idle-first AND tests and the grouped copy reproduce all other
instructions. Debug compilation, explicit shared parameter locals and GCSE
disabled preserve that residue; sched1 disabled changes allocation elsewhere.
The canonical helper prototype is retained. Reopen on new argument-setup
scheduling/source evidence, rather than changing its signature to steer moves.


<a id="blocker-43"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_00290B48` is C in `src/game/00290A40.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places. The measurements above are kept as history.

## 43. Block ordering: distinguish source structure from unavailable flags

Historically seven loop forms in two five-member families retained a different block order from retail, changing branch polarity and delay slots. The proposed freorder-blocks/fno-reorder-blocks remedy was a hypothesis, not an available flag or a measured fix.

The qualified cc1 rejects **both** `-freorder-blocks` and `-fno-reorder-blocks` as Invalid option(exit 33). Do not add them to cflags.txt. `-mastra-keep-frame-order` is accepted, but controls frame-related scheduling rather than arbitrary block ordering.

Meaningful return/break arrangements have matched some loops. PR #238's tidy_condjump_fallthru.py removes a jump to the next block early enough for flow to remove its dead input in six documented rotated id-list walks. Neither remedy establishes a solution for every block-order mismatch.

**28 October 2026, `func_00335960`:** the retained 360-byte USA v1.01 body rechecks
at 316/360 bytes and 0/28 placements in its current source unit. The attempted
`for`/`while`/split-condition forms all lower to a jump into a shared tail; retail
uses a rotated loop with its head peeled. The loop also makes cc1 hoist the mode
load that retail performs afterward. Retain the marker; reopen with independent
block-order or live-range evidence, not another equivalent loop spelling.

<a id="blocker-44"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_00335960` is C in `src/game/0032EB28-track.c` (`-O2 -G0 -ffunction-sections -g -frac2-gcse-unsplit-edges`), placed at 28 US, 28 PAL, 28 US2 places. The measurements above are kept as history.

## 44. Relocated instructions are validated in a separate pass

Placement.derive initially skips raw comparison of words carrying relocations because their address fields are not linked. It then validates unaffected opcode/register fields of HI16, LO16 and GPREL16, opcode bits of jumps, derived symbol values and relocation consistency. R_MIPS_32 is a full-word address relocation, not an instruction relocation.

A relocated register mismatch is therefore **not invisible**. The old claim that check.py skips instruction validation is withdrawn. The first reported mismatch is not an exhaustive list of all differences.

The displayed object column is unrelocated, so zero call/address addends can look different without being wrong. Use explicit size/instruction/relocation/binding rejection reasons and the full linked build. A quick per-function pass does not validate dependent sections or the whole program.

<a id="blocker-45"></a>

## 45. Source shapes that move a body

Measured on `func_L00_004096B0` (1 November 2026, 94 to 28 words, retained near miss):

- A spilled slot plus a callee-saved register holding the same address over a few calls is one spilled PRE copy, with
  reload inheriting its reload register. Write the address inline at each use, with no local, and the frame and
  spill slots appear. A stack struct standing in for those slots hides the real pressure.
- A hoisted constant that is rematerialised at its use lost its register to a higher-priority pseudo: loop.c did move
  it. Compare `floor_log2(refs) * refs / live` before looking for a reason it wasn't hoisted.
- `(index + table)->field` gives `mult; addu mult, base` where `table[index].field` gives `addu base, mult`.
- Local-alloc first tries each qty with `fake_birth`/`fake_death`, one insn wider on each side, so a qty avoids the
  registers of its neighbours (`find_free_reg`, `-fschedule-insns2` only). This is why a register seems occupied with
  no instruction using it, and it's worth checking before assuming a hidden insn (`func_002F8178`).

Historical examples, to requalify in the final unit:

- Removing a seemingly unused duplicate extern changed 180 to 188 bytes because the remaining declaration followed the call and implicit-int/default promotions altered floating arguments. Preserve correct visible prototypes.
- Mixed integer/float parameter order changed setup order even when final argument registers agreed. Determine the real ABI rather than choosing a false signature for scheduling.
- Else-if versus independent ifs changed float-constant rematerialisation; signedness changed immediate/branch forms. These were bounded examples, not guaranteed transformations.
- Stack-local ordering/layout examples remain in L00_002B91C0.c and L09_003F9468.c. A measured aligned struct containing TI128 plus a byte array expressed a frame that separate locals did not reproduce.
- func_L16_00404A60(988 bytes) matched after 24 store permutations; the winning order was neither retail order nor simple reversal. Do not infer one universal scheduler permutation.
- A register that varies between sites means different pseudos, not a tie. func_L09_003F8AE0 went from 53 words to exact by giving each site its own block-local (`child`, a fresh `u8 *t` per test, a separate counter `j`), reading `vars` in the arm that uses it (retail's bnel slot), and reading a byte twice instead of keeping a local so that the copy reaches the delay slot.
- A pointer that retail recomputes while cc1 hoists it early: move it to where it is used. In func_L05_0042AC30 `float *base = state + 0x24` before the loop is partially redundant and PRE places it on the other edge of the `if`; declared inside the innermost `if`, loop.c hoists it to the preheader, as retail has it. An ascending loop puts the reversed counter and the biv after that hoist. A local pointer read at `[0]` is folded back to the base register by cse, so `0x24($s5)` next to `4($s4)` still means one local.
- Spill slots that move with several unrelated registers can be a bucket count too: func_002DE990 went from 77 words to exact when `*gameState = savedState` lost its pointer local, which took the count from 159 to 157. `*(table + i)` gives (plus index sp) where `table[i]` gives (plus sp index).
- Hoist order in a preheader follows the source's expressions. In func_L12_0041BF88 the 0.5 from the inner loop always came before `-(width * 0.5f)`, scanned last from the rotated test. A `halfWidth` local takes the multiply out of the test, and the two copies swap.
- Before tuning a near miss, compare it with its matched relatives by masked opcodes. func_L02_00421DA0 needed func_L15_00438B00's `for` loop and `angle` local, func_L07_002B3580 the `scale` local of the ground probes (a constant set before an `if`, used after it), and func_L13_0040DFC0 is func_L16_003E7248 with other data. Copy the relative's flags too: func_L10_0039DA48 went from 131 to 26 words on func_L00_0040D058's.
- A rule table loop with an unreduced `mult` at an aligned label is a loop that loop.c skipped (func_L05_00444840): `for` with a `break` gets the same tail, but jump1 copies the test and the found arm ahead of the loop, which gives "multiple entry points".
- A float kept off a free register: a pseudo set by local-alloc in a hard register gives its operands a preference that keeps other pseudos off that register (global.c regs_someone_prefers). In func_L12_0041BF88 a scratch float shared with a later loop made the pseudo global and freed $f1.
- **A variable reused across blocks is a global pseudo (1 November 2026).** Local-alloc only takes pseudos of one block. A function-scope `f`, `n`, `id` or `history` reused for an unrelated later job goes to global-alloc after the block-local temporaries, which swaps whole register groups around it. A fresh block-local closed func_L22_003FC870 (f0/f1 group), func_L18_00428AE8 (a0/a2), and the history pointers of func_L08_003D4190. Check this before reading allocator dumps.
- **Byte-pointer stores pin later loads.** `*(float *)(m + 0xF8) = x` is not in a struct, so a following scalar global load cannot pass it; a store through a struct view can (`MEM_IN_STRUCT_P`). Where retail reads a global ahead of an object field just after a store, view the store's object as a struct: func_L08_003E5BB8, func_L05_004170C8.
- **Loop inits after the hoisted constants mean an indexed loop.** Strength reduction emits its inits at the loop start, after the movables, so `for (j = 0; j < 5; j++) { p = links + j * 8; ...` gives retail's order where a walking pointer does not (func_L06_003E1498, the UV loop of func_L06_003E57E8). Giv init order then follows the expression forms: func_L13_004388C8 needed `first->point[i]` in the projection loops and `(i << 4)` for base-first `addu`.
- **`s7 = i + 1` beside `i` is a real `next` variable.** Writing `next = i + 1` in the body and `i = next` as the step fixed the setup order and the s4/s5 swap of func_L06_003E57E8.
- **A saved register holding a small constant is a local.** func_L05_004170C8's `s5 = 1` and a stored register known equal to a constant (`sw a0` after `mode == 1`): keep the variable; cse only folds it in register sets. The extra saved register also explained that function's 0x10 frame difference.
- **gcse cprop and colour locals (open).** func_L05_003CF350 keeps 0x7FFFFFFF in s5 only as a `long` local, since cprop cannot substitute into the SImode subreg; `li` then stays one RTL insn and the body is 4 bytes over, while retail splits lui/ori. A SImode source shape that blocks cprop is still unknown.
- **A variable shared by two loops or two cases can be the whole difference (1 November 2026).** func_L02_003C26F0 (6,516 B, eight places) closed its last eleven words with one `vars` local shared by case 10's two loops and one function-scope `record` shared by cases 3 and 9, both global pseudos, plus `int` parameters for `func_002A0468`. func_L08_003C5940 needed the reverse: single-set block locals for the short-lived floats.
- **`same = a && b && c` is not `if (a && b) same = c`.** func_L11_004590F0's movn tail with a nop slot came only from the whole test in one condition; every nested flag spelling collapses to sltiu.
- **Close a colour pack by enumerating the or-chain.** func_L06_003FB050 took 144 spellings in one sweep: `0x7F000000 | (b << 16) | (b << 8)`, then `|= b`.
- **Stores ordered by sched1 still choose registers.** func_L03_003C3220 had been written off as needing a vanishing test between its stores and a call. A hill climb over seven store statements closed the f1/f2 swap in 94 compiles: no boundary was needed.
- **Read the branch targets before the registers.** A draft's `return` in a guard was retail's jump to the delete call (func_L08_003D4190), and an `else` was a fall-through into the following call. Both showed up only as a few bytes of size and branch offsets.
- **A shared tail in C can be cross-jumped arms in retail (1 November 2026).** A `goto remove` or `goto destroy` to one `func_0029F338(m); return;` looks right, because retail shows one tail. Jump2 merges the arms only after both schedulers and the allocators have run, so before that retail had the tail in each arm. The copies add references to `m`, which raises its allocation priority, and they keep later argument setters in the same block, so `rank_for_schedule`'s later-dependence count puts `a0` ahead of `t0`. Writing the tail in every arm took func_L16_003A8D58 from 32 rows to 0, func_L09_003FEF00 from 30 to 0 (no shared variable was needed after all), and func_L04_003F9718 from 73 to 18, closing its s1/s2/s3/s4 rotation. When a saved-register rotation or an argument-order swap resists, look for a label first.
- **A counted loop whose counter runs down after the moved constants was written ascending.** func_L04_003F9718's `addiu s3, 0xF` came after the hoisted setup only with `for (count = 0; count < 16; count++)`; loop.c reverses it. Written as a countdown it swapped two registers.
- **The address of a member can leave a base pseudo.** With one union for a frame area, `scratch.fx.a` sets a pseudo for `&scratch` first. Cse folds the member but keeps that pseudo for the base member, so its `addiu` appears too early (func_L18_004401E0). Retail's overlap of four vectors and a request block is block-scoped storage: declare the vectors in a block nested one level inside the `if`, with nothing after them, as the slots are then freed for the request block's own nested scope.
- **A catalogue row's name is not always its address.** func_L05_0033D3A0 sits at 0x33D3A8 and func_L16_003A8D58 at 0x3A8D60; the eight bytes before each are the previous function's end. Read the address from the row before generating assembly. Fuzzy twin screens should use it too: func_L05_0033D3A0 turned out to be func_002B1350 with a data name changed.
- **An `sda` read at a nonzero offset stays out of delay slots (1 November 2026).** func_L01_003980D0 read a byte at 0x001A7A0A. As a plain global it splits into `lui` + `lbu` with two registers, and the `lui` fills the branch slot. As an `sda` scalar it is a one-word load that reorg moves into the slot, where it becomes a $gp load. Declared as `D_001A7A00[]` under `sda` and read at `[0xA]`, it is a length-2 macro load: tied `lui v0 / lbu v0`, not eligible for the slot, so reorg takes retail's `beql` from the target. The offset's value is real: 0x001A7A00 is a known object elsewhere in `src/`. Try this where retail has a tied load after a branch-likely.
- **A table field through a struct orders the `addu` (1 November 2026).** func_L00_0039E7A8 indexed two level tables at +0x464 through local byte pointers, which put the index first. `struct { char pad[0x464]; u8 disabled[1]; }` read as `table.disabled[i]` puts the base first at all three sites and closed the function; func_L01_003980D0 already read its table that way. It did not move func_L00_003D3388, whose retail order is the other way round (index first after a `mult`).
- **Encoding correction:**0x700014A9 is por v0,zero,zero, not pcpyld. TI zero materialisation is reachable in appropriate cases; retention/folding depends on current source/profile(section 17). The word alone neither proves handwritten assembly nor proves a complete C match.
- **A register copy retail keeps means its source was overwritten.** gcse's cprop removes `b = a` whenever `a` is untouched between the copy and b's uses, so a surviving `daddu` in front of a long stretch says `a` is set again later: one scratch variable doing two jobs. func_0028C6D0 (37 words to 0): `scratch` holds the colour, is copied into `color`, then takes the string length. func_L00_003ED198 (57 words to 0, size 1712 to 1720): an int holds &delta, is copied into the loop's pointer, then takes the random phase in the loop; a block-local `float *t` used only up to the call gives retail's `$v0`-then-`$s5` pair. Measured with cprop switched off in a research cc1: most near misses get worse, so cprop itself runs in retail.
- A value pseudo with no user variable gives a different local-alloc tie. func_0028C6D0's last four words closed by dropping `record` and writing the table read into the call's argument.
- Reads of a `$gp` scalar pass struct stores (section 1, MEM_IN_STRUCT). If retail keeps such a load behind the stores, write the stores through a char view: func_00342BE8, 19 words to 2.
- An int under -G8 can fill a branch slot from the target thread. If retail has the two-word form there, it is part of a larger object: func_002F8178's screen size as one 8-byte struct, 66 words to 33.
- A hill climb over statement order (48 orders a round, 1 to 3 moves each, on box2) closed func_002F8178's store blocks where 18 statements are too many to enumerate: 33 words to 8.

**Update, 1 November 2026 (closer D).** Before tuning a near miss, walk its branch targets against retail's: `func_L02_003EB8F8` went from 132 rows to 0 by fixing three wrong targets, nothing else; a jump into the middle of what looks like an arm is the sign. A table reached through two `la` with reloads between stores (`func_L09_003806A0`) is one structure array declared `MACRO_ADDR`: separate arrays give the `la` but no aliasing, pointers walk it into a reversed loop. A base kept unfolded for a hero field can be a pointer local inside the arm, which loop.c hoists: it reaches the loop's preheader without being available at the next use, so gcse leaves that use alone. A pointer local set before the branch on the path where PRE must not insert (`d = delta;` in one `case`) gives one insertion instead of three. loop.c's `threshold` falls by 3 per register moved: when retail hoists some constants of a loop and not others, make one a local so the count works out (`func_L10_0039DA48`).

<a id="blocker-46"></a>

## 46. The `dli` expansion of all-ones masks

**The named witnesses are resolved**, with bounded rules rather than a universal mask heuristic:

- [PR #262](https://github.com/OpenRAC/rac2-gc-decomp/pull/262): `func_00117278` (`_strtol_r`, 884 bytes) and `func_00122630` (`__pack_d`, 300 bytes), one placement each. The isolated sign bit uses the sign-extending seed; a sign bit plus a contiguous low run of at least 32 ones retains the existing sign-extending `lui` path. `_strtol_r`'s wrapper forwards its actual long return; an explicit 32-bit truncation adds two instructions absent from retail.
- [PR #265](https://github.com/OpenRAC/rac2-gc-decomp/pull/265): `func_00122800` (`_fpadd_parts`, 576 bytes), one placement. Two shifted masks take three instructions instead of seven, reducing the SDK-profile body from 608 to 576 bytes. Positive shifted runs wider than 32 bits use the existing mask path; shorter runs, holes and other sign-bit cases retain their prior paths. The width bound preserves a 20-bit mask used by already-matched game code.
- [PR #267](https://github.com/OpenRAC/rac2-gc-decomp/pull/267): `func_00122B00` (`dpmul`, 680 bytes), one placement. Two separate causes were resolved: the fraction union's alias dependence and the assembler's isolated-sign-bit seed.

**The union was essential.** Public `fp-bit.c` uses a fraction union. Simplifying it to a scalar removed a real store dependence: restoring the union makes the access alias-set zero, keeps the fraction store before the class constant during the first scheduling pass, and lets `reorg` emit the retail `bnel`/annulled-store pair. No scheduler patch is needed. Disabling pre-reload scheduling repaired only the tail and produced a 688-byte body. All four existing units use the shared record; their complete object sections remain identical after the union correction.

**Both sign-bit encodings occur.** The multiplier needs `ori 0x8000; dsll32 16` at two sites, while the default `addiu -1; dsll32 31` remains required by existing game code. Per-file `-Wa,--r5900-sign-bit=unsigned` selects this bounded assembler option; explicit `signed` restores the default. No output rewriting or function/address special case is involved.

Fresh recipe, 80 container tests and all 28 strict programs pass with zero C fallback. Same-source A/B across 781 units changes code only in the new multiplier; eleven units differ only in `.mdebug`. The 1,980 authored assembler cases are checked in each of three profiles. Details and source references are in [COMPILER-NOTES.md](https://github.com/OpenRAC/rac2-gc-decomp/blob/master/docs/COMPILER-NOTES.md). Progress regeneration remains deferred.

**Public runtime modules, 25 October 2026:** `__divdi3` and `__moddi3`
qualify with the original public GCC MIPS multiplication primitive and the
complete `count_leading_zeros` macro, including its portable constant-size
branch wrapper. Flattening that wrapper changed padding even with equivalent
arithmetic. No instructions or nops were patched. Dedicated SDK-profile units
and the complete constant-pool placement above give 1/1 in each release and
all 84 strict builds. Original GNU notices and the linking exception remain
in both source files; no proprietary SDK source was used.

<a id="blocker-47"></a>

## 47. Catalogue filler rules applied; mixed prefixes remain separate

The historical 21 October scan removed 257 level and 225 boot rows with the measured padding forms. A separate immediate-epilogue-residue rule removed 25 level and 26 boot rows. These are correction counts, not today's unfinished inventory. PRs #239/#241 implemented the generator changes and removed corresponding markers.

Words **and operands** matter: qualifying sp-by-sp adjustments, zero moves and nops are different from addu t0,t1,t2 or addiu sp,a0,16. Missing jr alone is insufficient. func_00115E90 is valid trap-ending C; func_0011F364 contains real code despite its padding-like prefix.

The four-byte residue rule also needs its measured position after a completed return and delay slot. PR #253 now handles five additional specifically audited mixed-instruction residues (section 50), not an opcode-only generalization.

An extent beginning inside a prior epilogue but containing a later real function needs an entry correction, not deletion. Positive stack adjustment is only a clue. Verify call/data/vtable entries, preserve ends and raw bytes, and preserve boot/level identity when regenerating fingerprints. Other mixed boundaries remain open.

One boot example remains open: USA v1.01 callers `func_0027B440` and
`func_00291850` enter `0x00126288`, four bytes after the catalogued
`ASM_FUNC` entry `func_00126284`. A direct read of the boot's loaded ELF bytes
confirms `0xCDCDCDCD` at `0x00126284`; decoding that filler as `pref` is misleading.
The following `sll` at `0x00126288` begins the observed call target. Keep the caller
reconstructions unlinked until the entry, neighbouring extents and corresponding
release identities are qualified. No catalogue correction, invented symbol or
additional matching/assembly credit is implied by this observation.

<a id="blocker-48"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_00291850` is C in `src/game/00291850.c` (`-O2 -G0 -ffunction-sections -frac2-keep-block-order`), placed at 28 US, 28 PAL, 28 US2 places. The measurements above are kept as history.

## 48. The wave 12 census: historical sample, not today's inventory

The sample covered twelve game/shared files, 470 unfinished functions and 9,638 placements, with nine workers. Its 4,932 filler placements preceded the corrections above and are not current remaining work.

- **Exact instruction decoding comes first.** The sample reported 30 COP2/VU0 and 9 broadly classified MMI bodies in src/game/0027F128.c. Opcode families alone cannot determine C reachability or ASM_FUNC credit. 0x1C includes compiler-emitted operations, and one body does not disqualify its whole source file.
- **Trapping arithmetic is a specific compiler-origin clue.** The tested C additions emitted addu/addiu, and ftrapv was unsupported; func_00283150 has its own reviewed evidence. Do not classify every other row automatically.
- **Encoding correction:** COP1 major opcode is 0x11 and COP2 is 0x12; these are not opposite halves relative to ordinary MIPS. lq/sq base is bits 25–21, as in ordinary MIPS base-plus-offset loads/stores, not 15–11.
- **Conversion/OR observations were bounded.** Seventeen conversion spellings and the sampled OR forms failed. That does not prove every conversion must use a fresh FPR or every left-to-right OR sequence is unreachable.
- **TI offset materialisation:** fixed offsets folded in tested attempts, but opaque pointer arguments are not the only documented zero-displacement shape. Notes also record loop-carried pointers, memory-loaded pointers, join-dependent values and out-of-range offsets. These do not solve all remaining fixed-offset copies.
- **G0/G8 can change addressing and allocation.** Actual form also depends on declaration size/attributes and assembler context. Qualify the complete unit instead of inferring a universal recipe.

<a id="blocker-49"></a>

## 49. The wave 13 census: correct the screens before selecting work

The historical screen selected 145 proposed functions in fifteen files. Other files with many unfinished rows were dropped using broad opcode classes. Those are selection counts, not verified current reachability; a file of 81 functions was not proved to contain zero reachable functions.

- **The six alleged unused multiplies are live.** No mflo was the wrong criterion: R5900 mult/mult1 can write a GPR destination. The [maintainer follow-up](https://github.com/OpenRAC/rac2-gc-decomp/issues/157#issuecomment-6305695078) decodes rd and follows its uses in all six bodies. Withdraw the unused-result/compiler-origin hypothesis and any ASM_FUNC inference for those cases.
- **Decode exact operations.** 0x1A/0x1B are ldl/ldr, not COP2/VU0. 0x1C covers multiple EE operations, including compiler-emitted ones; it is not universally unreachable MMI0. lq/sq use 0x1E/0x1F. Inspect operands/control flow and never reject unrelated bodies by association.
- **TI folding remains a bounded problem.** Roughly thirty historical forms folded a fixed offset. This does not prove all computed addresses unreachable; distinguish documented pointer/loop/join shapes from unresolved fixed-offset copies and issue #248's narrower zero-store experiment.
- **Allocation can cascade.** One stack-local-address difference changed saves, scratch FPRs and branch-likely choice in a sample. That does not establish that allocation is never source-sensitive.
- **Types and volatile must describe semantics.** The sample changed codegen by altering a return declaration or loop-bound qualifier. An ignored return does not prove void, and a forced memory read is not a justified matching barrier without real semantics.
- **Split addressing does not inherently change the address.** Correct relocation/addend handling can make lui-plus-load and lui-plus-addiu-plus-field refer to the same data. Derive validates the compiled form; a false symbol identity is a defect, not another valid binding.
- **Not all level data needs ref_.** D_LNN_XXXXXXXX is the normal level-data name; its canonical address and other placements are checked/bound under repository rules. Ref_ is for genuinely variable target identity. Preserve resident-data and boot/level naming conventions.

Use current R5900 decoding, profile evidence and bounded per-function checks. This section is not justification for a blanket file exclusion or unreviewed handwritten classification.

**Additional measured corrections:** `func_L00_002ADFE8` (136 bytes) and
`func_L00_00421A98` (184 bytes) each pass 27/27 placements in US, PAL and US2
with computed gotos through their actual retail tables, using default flags.
Their former "jump table, no C" records were screens, not proof of an assembly
origin. `func_L00_00420638` (324 bytes) also passes 27/27 in each release with
`-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier`: retaining the
axis pointer's two real uses and the projection copied at the owner's +0x70
reproduces the allocation. The combined tree passes all 84 strict program builds.
The neighboring `func_L00_00420388`
remains a 280/280-byte near miss, first difference +0x1C in all 27 placements of
each release; its `func_L00_002DB350` call must forward the float margin, which
the callee saves from `$f12` and uses in its radius test.


<a id="blocker-50"></a>

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L00_002DB350` is C in `src/levels/shared/L00_002D7940-grid.c` (`-O2 -G0 -ffunction-sections`), placed at 27 US, 27 PAL, 27 US2 places. The measurements above are kept as history.

## 50. Five specifically audited residual extents — resolved by PR #253

The wave 13 report found five suspects. Missing jr or local register definitions were clues, not proof. Subsequent review checked positions after completed returns and direct-target/aligned-pointer references at every affected placement. That audit does not prove absence of all computed indirect targets and must not become a general deletion rule.

| Historical row | Recorded extent | Resolution |
|---|---|---|
| func_00289018 |4 bytes, isolated store after return |Measured residue mapping |
| func_002A77C0 |28 bytes, orphan float operations |Measured residue mapping |
| func_002FED78 |12 bytes, unmatched restore context |Measured residue mapping |
| func_002FF0B0 |36 bytes, restore/GP-store context |Measured residue mapping |
| func_002FDB40 |148 bytes, restores/orphan store, 22 level copies |Boot and matching 22 level placements |

PR #253 is merged. Generator, catalogue, markers and tests account for these specific extents while preserving reconstructed program bytes. They are catalogue corrections, not new C or handwritten-function credit. Other historical boundary proposals below remain independent.

**28 October 2026 USA v1.01 follow-up, still pending:** `func_0029B848` is a 12-byte catalogue row whose bytes decode to `daddu $v0,$zero,$zero; nop; addiu $sp,$sp,0x10`. In the boot and all 25 level placements, it follows a completed `jr $ra`, its delay-slot `nop`, and one further `nop`; scans found no direct branch/jump target inside the row and no aligned literal pointer into it. A temporary `return 0` C probe emitted 8 bytes and matched 0/26 placements. This resembles the recorded return-value/unmatched-restore residue `func_002FED78`, but `func_0029B848` is catalogued in PAL and USA v2.00 as well, and those retail dumps are unavailable in this checkout. Keep its marker and catalogue row unchanged pending maintainer decision and release-qualified audit; it has not been added to `FUNCTION_RESIDUES`.  **28 October 2026 follow-up:** USA v1.01 boot-only `func_003356E8` spans 0x003356E8-0x00335794 (172 bytes), between `func_003355A8` ending at 0x003356E4 and `func_00335798` at 0x00335798. The extent starts with `sb $a0,0x88($v1)` and then contains stack adjustments, delay-slot nops and stores, without a function prologue, branch/jump body or return. A scan of boot load segments found no direct branch/jump target or aligned literal pointer into the extent. Treat as a residue hypothesis only; leave the marker/catalogue unchanged pending maintainer and release audit.

**28 October 2026 USA v1.01 follow-up, pending release-qualified audit:** `func_00288D40` is catalogued as 20 bytes at boot 0x00288D40 and 25 level placements. The boot listing shows a completed `func_00288D30` return at 0x00288D34 with its delay-slot `sltu`, followed by `nop` at 0x00288D3C; the row then contains `daddu $v0,$zero,$zero; nop; addiu $sp,$sp,0x10; nop; addiu $sp,$sp,0x10`, followed by another `nop` at 0x00288D54 and the next function at 0x00288D58. No boot assembly listing references the `f_00288D40` label. A `void` stub compiles to 8 bytes; a `return 0` trial was not retained. This is a residue hypothesis only: aligned-pointer and all-placement/release audits remain outstanding. Keep the marker and catalogue unchanged pending maintainer review; do not count it as a match or handwritten function.

**28 October 2026 USA v1.01 follow-up, pending release-qualified audit:** `func_002ED570` is catalogued as 4 bytes in boot and 23 levels. The boot listing places its sole `lw $v0,0x24($v1)` after the completed `func_002ED508` epilogue (return at 0x002ED560, delay slot at 0x002ED564, then two nops) and before the `func_002ED578` prologue; the label is an `alabel`, not a function entry. A `void` stub compiles to 8 bytes. Keep the marker and catalogue unchanged pending maintainer review and aligned-pointer/all-placement audits; this is not a match or handwritten-function claim.

**28 October 2026 USA v1.01 follow-up, pending release-qualified audit:** `func_0029CEC8` is catalogued as 12 bytes in boot and 23 levels. In the boot listing it follows `func_0029CE80`'s completed return at 0x0029CEC0 and delay-slot stack restore at 0x0029CEC4; the extent is `sw $a0,-0x4000($gp); nop; addiu $sp,$sp,0x10; nop`, then the next label at 0x0029CED8 is an `alabel` starting a new stack frame. The label `f_0029CEC8` is itself an `alabel`; no direct branch reference to it appears in the boot listing. A `void` C stub is 8 bytes. Keep the marker/catalogue unchanged pending maintainer and aligned-pointer/all-placement audits; do not count it as a match or handwritten function.

**29 October 2026 USA v1.01 all-placement audit:** `func_002EEBB0` is 20 bytes in the boot and 23 levels. All 24 placements have the same boundary: completed `jr $ra` and stack-adjust delay slot, then `daddu $v0,$zero,$zero; nop; addiu $sp,$sp,0x140; nop; addiu $sp,$sp,0xC0; nop`, followed by the next catalogue entry. Scans of all 24 loaded programs found no direct branch/jump target, aligned loaded-word pointer or adjacent `lui` plus `addiu`/`ori` construction to the row. The earlier temporary empty-C probe compiled to 8 bytes and matched 0/24. This supports an orphaned epilogue-fragment hypothesis but does not rule out computed indirect entry; PAL and USA v2.00 retail dumps are unavailable here. Keep the marker/catalogue unchanged pending maintainer review; this is not a C match or handwritten-function claim.

**28 October 2026 USA v1.01 follow-up, pending release-qualified audit:** `func_002ED880` is catalogued as 28 bytes in boot and 23 levels. The boot listing labels this extent `alabel`; it contains two stores, a load, three nops and `addiu $sp,$sp,0xB0`, followed by a nop and another `alabel` at 0x002ED8A0. It sits within a cluster of `alabel` extents after completed returns, and no direct boot-listing branch reference to `f_002ED880` was found. A `void` stub compiles to 8 bytes. Treat it as a residue hypothesis only; keep marker/catalogue unchanged pending maintainer and aligned-pointer/all-placement audits.

**28 October 2026 USA v1.01 follow-up, pending release-qualified audit:** `func_002ED9A8` is catalogued as 20 bytes in boot and 23 levels. Its boot extent follows `func_002ED990`'s completed return at 0x002ED9A0 and delay-slot stack restore at 0x002ED9A4; it contains `lw $v0,0xC($v1); nop; addiu $sp,$sp,0x20; nop; addiu $sp,$sp,0x20`, then a nop before the next `alabel` at 0x002ED9C0. The label is an `alabel`, and no direct branch reference to `f_002ED9A8` appears in the boot listing. A `void` stub compiles to 8 bytes. Keep marker/catalogue unchanged pending maintainer and aligned-pointer/all-placement audits; do not count it as a match or handwritten function.


**28 October 2026 USA v1.01 follow-up, pending maintainer review:** boot-only `func_0026FEF0` is 20 bytes and follows `func_0026FEB8`'s completed return at 0x0026FEE8 and stack-adjustment delay slot at 0x0026FEEC. The extent is `sw $v0,0x38($a0); nop; addiu $sp,$sp,0x10; nop; addiu $sp,$sp,0x20`, followed by padding and the next prologue at 0x0026FF08. No direct target in catalogued boot code or aligned loaded-word pointer enters the row. A temporary empty C probe emits 8 bytes and matches 0/1. Keep marker and catalogue row pending maintainer review; do not count it as a match or handwritten function.

**28 October 2026 USA v1.01 follow-up, pending maintainer review:** boot-only `func_002725C8` is 20 bytes and follows `func_00272550`'s completed return at 0x002725C0 and stack-adjustment delay slot at 0x002725C4. The extent is `addiu $sp,$sp,0x80; nop; nop; nop; sw $zero,0x4($v0)`, followed by padding before the next frame at 0x002725E0. No direct target in catalogued boot code or aligned loaded-word pointer enters the row. A temporary empty C probe emits 8 bytes and matches 0/1. Keep marker and catalogue row pending maintainer review; do not count it as a match or handwritten function.

**28 October 2026 USA v1.01 follow-up, pending maintainer review:** boot-only `func_00298D10` is 20 bytes, labelled `alabel`, after `func_00298CEC`'s completed return at 0x00298D04 and stack-adjustment delay slot at 0x00298D08. The extent is `daddu $v0,$zero,$zero; nop; daddu $v0,$v1,$zero; nop; addiu $sp,$sp,0x40`, followed by padding before the next frame at 0x00298D28. It has no local prologue or return. A temporary empty C probe emits 8 bytes and matches 0/1. Keep marker and catalogue row pending maintainer review; do not count it as a match or handwritten function.

**29 October 2026 USA v1.01 follow-up, pending maintainer review:** boot-only `func_002B8530` is catalogued as 20 bytes and disassembles to `lwc1 $f0,0x2D0($a2); nop; lwc1 $f0,0x258($a2); nop; addiu $sp,$sp,0x30`. The previous extent ends with a completed return/delay slot, the disassembler labels this address `alabel`, and a new frame begins at `func_002B8548`. This local boundary evidence is insufficient to edit the release-shared catalogue; retain the marker and row pending maintainer review.

**28 October 2026 USA v1.01 follow-up, pending maintainer review:** boot-only `func_002B4068` is 36 bytes, labelled `alabel`, after `func_002B4040`'s completed return at 0x002B4054, delay-slot result operation, and padding. Its body is `sw $zero,0($gp); nop; sw $zero,0($gp); nop; addiu $sp,$sp,0x60; nop; addiu $sp,$sp,0x90; nop; addiu $sp,$sp,0x150; nop`, followed by the next frame at 0x002B4090. It has no local prologue or return. A temporary empty C probe emits 8 bytes and matches 0/1. Keep marker and catalogue row pending maintainer review; do not count it as a match or handwritten function.

<a id="blocker-51"></a>

## 51. The wave 14 census: a call inside one object, and a screen that was too broad

The wave 14 reserved forty-three files of `src/game/` and `src/levels/shared/` and
479 unfinished functions, screened **per function** on the retail bytes (8,883
placements). Ten workers, one file each, no two workers on one file.

**The result: three matches, 59 placements**, and one more match handed to the
contributor that holds the body.

| function | places | unit |
|---|---:|---|
| `func_L00_003E70B8` | 27 | `src/levels/shared/L00_003E70B8.c` (a unit of its own) |
| `func_L05_00418508` | 4 | `src/levels/shared/L05_003D33E8.c` |
| `func_00291788` | 28 | `src/game/00291758.c` |

Twenty-nine near misses were deposited in `nonmatching/`, each with the difference
that was measured and the spellings that were tried. The census is those
measurements, not the three matches.

### A call inside one object fixes the distance between the two

`func_L00_003E70B8` calls two bodies that `L00_003E3258.c` holds, and it was written
in that file. The assembler resolves a call to a body of the same object to an
offset, so the two are placed together — and the retail does not keep them
together in every level. The body was placed in **18 of the 27 levels** and dropped
in the other nine, and the build gave it no credit there, even though
`tools/check.py` said the bytes matched at every place. `tools/check.py` reads the
symbol values from the retail's bytes under the relocations; `tools/build.py`
compares the **linked** addresses, and a local call cannot move.

**The rule, measured over the whole tree: no C function of `src/levels/shared/`
calls another C function of the same file.** Not one of the 180 shared files does
it. A body that needs a sibling gets a sibling file, and a call that crosses a file
is a global one the linker places per program.

### The bodies the game linked more than once

The retail keeps **more than one copy** of some shared bodies: three copies of the
reset routine `func_L00_003E6FC8` (also `func_L00_003F0A20` and `func_L00_003F1DC8`),
two of the scale routine `func_L00_003E7050` (also `func_L00_003F0AA8`), and the
caller itself has seven twins. Which copy a program calls changes from one program
to the next, so a C that names one copy is right in 18 programs and wrong in 9.

**The way out is the `ref_` name**: `ref_L00_003E70B8_00` and `ref_L00_003E70B8_01`
for the two calls, whose value the build reads from the retail's bytes, with no
address in the name. That is what the project already does for a call whose target
moves between programs (`src/levels/shared/L00_002E5918-g8.c` and its neighbours).
With the body in a unit of its own and the two calls renamed, it is 27 of 27.

**How to see which calls need a `ref_` name.** For every call of a body, read the
retail's jump word in every program and look up which catalogue row the target
belongs to. A call whose target is the same row everywhere takes the row's name; a
call whose target moves between rows takes a `ref_` name. Measured on
`func_L00_003E70B8`: eight of its ten calls name one row in all 27 programs, and the
other two move.

### The screen of sections 48 and 49 was too broad

Those sections dropped a body that carried *any* word of a list of opcodes (COP2/VU0,
COP3, COP2X, COP3X, the whole MMI space, and the double-precision FPU words the PS2
does not have). In the forty-three files of the wave there are **1,184** unfinished
bodies: 479 were kept, 705 were dropped, and of the 705 only **101** carry an
instruction no C body can carry (section 52). The other **604 are reachable** and
were left on the table for nothing. The over-broad classes are:

* **0x1A and 0x1B** are `ldl` and `ldr`, the R5900's quad load. A 16-byte struct copy
  reaches them: the compiler emits them.
* **The MMI space** (0x1C) holds the compiler's own `por $rd,$zero,$rt` (section 17)
  and the constant words a literal pool leaves in the instruction stream. A body
  carrying one of those is not hand-written.
* A **literal pool inside a function** is data. A float constant can decode as an
  MMI word; a branch's delay slot can hold one.

### The walls this wave measured, in order of cost

* **The 128-bit copy, and the way out of it.** Retail materialises the address of a
  16-byte copy (`addiu $a2,$s2,0x10 ; sq $v0,0x0($a2)`); this cc1 always folds a
  constant offset into the `lq`/`sq` pair. About forty spellings were measured across
  three workers and all of them fold. Two spellings keep the address in a register: a
  plain pointer with no offset, and a symbol address. The opt-in profile
  `-frac2-qcopy` reaches the retail's shape; it is already in `config/cflags.txt` for
  two files, and the need for the others is reported here rather than applied, because
  `config/cflags.txt` is not a worker's file.
  **2026-10-23 recheck:** dedicated units using the already qualified qcopy and
  qcopy-barrier profiles close `func_L00_003E5650`, `func_L00_003E9490`,
  `func_L00_003E7650` and `func_L00_003E51C0` locally. Each passes all 27
  placements in both USA releases; 5650, 9490 and 51C0 also pass PAL's 27
  placements, while 7650's canonical name is absent there. The combined tree then
  passes all 84 strict program builds. The older retained drafts also needed real input
  and ABI corrections: 9490 subtracts the source from the other vector; 51C0
  preserves the half-angle across sine/cosine calls and releases the previous
  global object. Its byte view of the resident pointer and header store order
  recover the remaining allocation and scheduling.
  **51C0 ordering caveat:** retail level 00 executes `lw a0,0x68(s4)` in
  the unconditional delay slot of `beqz s4` at offsets +0x34/+0x38. The C
  preserves that read before its null test; no non-null allocator guarantee has
  been established, and an allocation-failure path has not been runtime-tested.
  Three natural guarded forms were measured with the same qualified profile:
  loading at first use or at guarded-block entry stays 356 bytes but changes
  scheduling (first difference +0x14); an early null return gives 364 bytes in US.
  The private first-use guarded draft is 0/27 in each of US, PAL and US2;
  it does not reproduce the observed unconditional load. This is a preserved
  retail-ordering caveat, not evidence that allocation always succeeds.
* **The floating-point register allocation is not a source detail.**
  `func_L00_003E9540` and `func_L00_003BC108` have retail's size and retail's
  instruction sequence, and differ only in which of $f2..$f8 holds which value.
  Eleven and nine spellings were measured. The allocation follows the first textual
  use of a value, so the source's *expression tree* decides it, and a permutation
  search over the statement order is the lever.
  *Update, 28 October 2026 (pending review):* both are C and placed 27/27 in each of
  US, PAL and US2: `func_L00_003E9540` in place in `src/levels/shared/L00_003E3258.c`
  ([PR #348](https://github.com/OpenRAC/rac2-decomp/pull/348)),
  `func_L00_003BC108` in its own unit `L00_003BC108-qcopy.c`
  (`-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier`;
  [PR #348](https://github.com/OpenRAC/rac2-decomp/pull/348)).
* **The frame's register set follows from the address form.** `func_L05_004268E8`
  and its three colour twins come out with nine callee-saved registers against the
  retail's eight, because the retail has no register at all for the base of the int
  array: it re-materialises it in the loop (`addiu $v1,$s4,0x20`) and adds the offset
  to it, while a base held in a local lets the compiler fold the offset into the store.
  *Update, 28 October 2026 (pending review):* `func_L05_004268E8` is C in place in
  `src/levels/shared/L05_003D33E8.c`, placed 4/4 in US and in US2 (it has no C
  placement in PAL;
  [PR #348](https://github.com/OpenRAC/rac2-decomp/pull/348)).
  Its colour twins are not individually rechecked here.
* **A dead `mult` is a body this compiler did not write.** `func_L00_002FCF18` and
  `func_L00_003FEAC8` carry a `mult` whose result the retail never reads; cc1 does
  not emit a multiply whose result is unused.
* **An indirect call has no sibling-call form.** `func_002B9380` is a tail call in the
  retail (`jr $v0`) and comes out as `jalr $v0` with an epilogue; five spellings were
  measured and `-mastra-sibcall` does not change the indirect target.
* `func_002B9390` remains a local near miss under `-O2 -G8 -ffunction-sections`:
  six plain-C forms model the 0x40-byte record scan and indexed handler call, but the
  140-byte best form matches 0/28 places in US, PAL and US2. Its prologue saves `$ra`
  in a stack frame; retail stores it at `$gp+0x2DB8`. Next: find a plain-C source shape
  that reproduces that return-address slot and the loop branch layout. This is not
  evidence for handwritten assembly.
* **A body that a worker could not close in a hundred spellings is a wall to record**,
  not a near miss to retry.

### The catalogue defects this wave found

(the fix belongs in `tools/levels.py`, outside every worker's lane):
`func_L00_00400F30`, `func_003495B8`, `func_0034CE88`, `func_002EEBB0`,
`func_L00_002DA390`, `func_0031E6D8`, `func_00326CA8`,
`func_L00_003D1B48`, `func_002B80B8`, `func_L00_0037B408`, `func_L00_0037B4B8`,
`func_L00_0037B5C0`, `func_00280660`. They are the same shape: a four- to
sixteen-byte extent that reads a register it never sets, or branches outside its own
bytes, or is the linker's padding between two bodies. Each is deposited with its
evidence. **28 October 2026 USA v1.01 follow-up for `func_002B80B8`:** unlike the
short extents grouped above, this 76-byte boot row begins at `alabel f_002B80B8`
after `func_002B80A8`'s completed return at `0x002B80AC`, its delay slot, and a
padding nop. It consists only of positive `$sp` adjustments separated by nops,
two more nops, and `addiu $v0,$zero,-1`; the following `func_002B8108` starts a
fresh frame at `0x002B8108`. The boot assembly has no direct reference to the
alabel. This supports a catalogue-fragment hypothesis, but the 15 USA v1.01
level placements and the PAL/USA v2.00 copies have not been audited here. Keep
the generated rows and source markers pending maintainer review; no catalogue
mechanism change is made. **28 October 2026 USA v1.01 follow-up for `func_0031D350`:** this
boot-only catalogue row is 132 bytes, so it is distinct from the short extents
above. Its bytes are stack-pointer additions interleaved with nops, plus one
`addiu $v0,$zero,1`. It begins after `func_0031D308`'s completed `jr $ra`, its
stack-restore delay slot, and a nop; the next prologue starts at `0x0031D3E0`.
The assembly labels the start `alabel`, has no direct reference to
`f_0031D350`, and the linked boot ELF contains no aligned word equal to the
entry address. A temporary empty C body measures 8 bytes against 132. This
supports a catalogue-fragment hypothesis, not a match; keep the marker and
generated row pending maintainer review. Other releases are not audited and
the row has not been added to release-shared residue handling. **28 October
2026 follow-up for `func_0029B848`:** this generated 12-byte row has no
standalone body at the boot or checked USA v1.01 level placement. In boot it
is `daddu $v0,$zero,$zero; nop; addiu $sp,$sp,0x10; nop`, followed at
`0x0029B858` by the next function's `addiu $sp,$sp,-0x10` prologue. All 25
level placements have the same 12 bytes; at level 00, the `0x0030C920` extent
is followed at `0x0030C930` by the next prologue. It contains no `jr $ra`; the
preceding `func_0029B810` has already returned, and a scan of direct boot
branches found no target at its start. The 8-byte C zero-return probe cannot
represent the 12-byte row across all 26 placements. Leave the marker and
generated catalogue unchanged pending maintainer catalogue review; no C match
is claimed. **28 October 2026 follow-up for `func_002ED9A8`:** the generated
20-byte extent is `lw $v0,0xC($v1); nop; addiu $sp,$sp,0x20; nop; addiu
$sp,$sp,0x20` in boot and all 23 USA v1.01 level placements. It follows the
previous function's completed `jr $ra` at boot `0x002ED9A0` and stack-adjustment
delay slot at `0x002ED9A4`; the next row starts with a prologue at `0x002ED9C0`.
There is no return in this row, and a scan of direct boot branches found no
target at its start. This supports a catalogue-fragment diagnosis; retain the
generated row and marker pending maintainer review.
**28 October 2026 follow-ups for `func_002ED848`, `func_002ED880` and `func_002ED8F0`:** these extents are byte-identical across all 23 USA v1.01 level placements. `func_002ED848` is 36 bytes of unrelated `$gp`/stack stores and zero-base stores; it follows the previous function's return at boot `0x002ED83C` and stack-adjustment delay slot at `0x002ED840`. `func_002ED880` is 28 bytes of stores, loads, nops and a stack add after `func_002ED870`'s completed return and delay slot. `func_002ED8F0` is 84 bytes of stack adjustments and loads ending with a stack add, after `func_002ED8A0`'s completed return and delay slot. None contains a return, and direct boot branch/jump scans found no target at any of the three starts. These support catalogue-fragment diagnoses; retain markers and generated rows pending maintainer review.
**28 October 2026 follow-up for `func_0029CEC8`:** the generated 12-byte extent is `sw $a0,-0x4000($gp); nop; addiu $sp,$sp,0x10; nop` in boot and all 23 USA v1.01 level placements. It follows the prior function's completed `jr $ra` at boot `0x0029CEC0` and stack-adjustment delay slot at `0x0029CEC4`; the next function's prologue begins at `0x0029CED8`. The row contains no return, and a scan of direct boot branches found no target at its start. This supports a catalogue-fragment diagnosis; retain the generated row and marker pending maintainer review.
**28 October 2026 follow-up for `func_002ED570`:** this generated 4-byte extent is `lw $v0,0x24($v1)` in the boot and all 23 USA v1.01 level placements. It follows the preceding function's completed `jr $ra` at boot `0x002ED560`, its stack-adjustment delay slot at `0x002ED564` and two nops; the next function's frame setup begins at `0x002ED578`. The row itself has no prologue or return, and a scan of direct boot branches found no target at `0x002ED570`. This supports a catalogue-fragment diagnosis; retain the generated row and marker pending maintainer review.
**28 October 2026 follow-up for `func_00288D40`:** its 20-byte generated extent is identical across all 25 USA v1.01 level placements and consists of `daddu $v0,$zero,$zero; nop; addiu $sp,$sp,0x10; nop; addiu $sp,$sp,0x10`. It follows `func_00288D30`'s completed return (`jr $ra` at boot `0x00288D34`) and has no return of its own; the next catalogue row starts at `0x00288D58`. A direct boot branch/jump scan found no target at `0x00288D40`. This supports a catalogue-fragment/padding diagnosis; retain the generated row and marker pending maintainer review.
**29 October 2026 USA v1.01 all-placement audit for `func_003495B8`:** this 4-byte row is `swc1 $f1,0x18($a0)` in the boot and all 27 level placements. Every placement has the same boundary: it follows `func_003495A0`'s completed `jr $ra`, its `sw $zero,0x18($a0)` delay slot, and a nop; after the row's own nop, `func_003495C0` starts with `jr $ra`. Scans across all 28 loaded programs found no direct branch/jump target, aligned loaded-word pointer or adjacent `lui` plus `addiu`/`ori` construction to the row. The instruction reads `$f1` without a local definition, so no source-defined C computation accounts for it. This supports a catalogue-residue hypothesis but cannot rule out computed indirect entry; leave the marker and row unchanged pending maintainer review.
**29 October 2026 USA v1.01 all-placement audit for `func_0034CE88`:** this 12-byte row contains `sw $v0,0x156C($a0); nop; sw $v0,0x1564($a0)` in the boot and all 27 level placements. Every placement follows the preceding function's completed `jr $ra` and `addiu $sp,$sp,0x10` delay slot; after the two stores and nops, `func_0034CE98` starts with its own `jr $ra`. Scans across all 28 loaded programs found no direct branch/jump target, aligned loaded-word pointer or adjacent `lui` plus `addiu`/`ori` construction to the row. The stores use `$v0` without a local definition. This supports a catalogue-residue hypothesis but does not rule out computed indirect entry; keep the catalogue row and marker unchanged pending maintainer review.
**28 October 2026 recheck of `func_00280660`:** 12 bytes in the boot and 22 level placements; its body is `sw $zero,0x14($v1); nop; sw $zero,0x1C($a0)`, after a completed return and stack-adjustment delay slot in every USA v1.01 copy. The boot function-range scan and aligned loaded-word scan found no incoming target/reference; the empty C probe is 8 bytes, 0/23. Keep its marker pending the maintainer’s catalogue-rule decision.


<a id="blocker-52"></a>

## 52. What a C body cannot carry: the measurement, and the rule

`AGENTS.md` allows the `ASM_FUNC` marker for a body that "uses instructions the
compiler never emits". That needs a measurement, not an impression: the wave 14
workers reported such bodies and left them unclassified, and the wave's own screen
(section 51) was too broad for the same reason.

**The measurement.** Every C object of the project was scanned, word by word, over
the code of each function (the body cut at its `jr $ra` and its delay slot, so a
literal pool after the epilogue is not counted as code):

```
the C objects: 861
   VU0 (COP2) 0
   COP3       0
   MMI        12, of which 12 are the compiler's own form
```

So **the compiler emits no VU0 instruction at all**, and no COP3 one. Of the MMI
unit it emits only two things:

* the R5900's own SPECIAL2 arithmetic — `mult1` and `madd` (opcode 0x1C, the
  `R5900_MMI` category), and
* the form `por $rd,$zero,$rt`, which copies or zeroes a register. Section 17
  already records it: `src/levels/shared/L00_002B91C0.c` is a **matched** function
  and its `por $v0,$zero,$zero` is the compiler's own, zeroing the GPR half of a
  128-bit store before the `sq`.

Every other MMI word — `pmaxw`, `pminw`, `pcpyld`, `pcpyud`, `pexch`, `pextlw` —
never comes out of a C body.

`func_002829A8` is a 48-byte example at the boot and all 27 level placements.
The same body uses `pmaxw $at,$at,$v0` in the `beqz` delay slot and `$at` as
the byte counter. A behaviorally equivalent C reconstruction, adapted from
RAC1's functional timer note, compiles to 48 bytes but matches 0/28 placements;
it replaces the `pmaxw` and branch layout. Keep it in
`nonmatching/game/func_002829A8.c`; the evidence supports maintainer review,
not an automatic `ASM_FUNC` classification.

`func_00282DF0` is another reachable example: its identical 48-byte body at
all 28 placements loads a VU0 vector, squares and sums xyz, computes `vsqrt`
through Q, waits for the result, and transfers it back with `qmfc2`. No C
attempt is useful under this compiler; leave its marker pending maintainer
agreement for `ASM_FUNC`.

`func_00282F70` is a 72-byte VU0 vector-scaling helper at all 28 placements.
It loads an xy vector, forms its squared length, computes a reciprocal square
root with `vrsqrt`, waits for Q, scales with `vmulq`, and stores with `sqc2`;
the zero path also uses VU0. The qualified compiler has no C route for this
body. Keep its marker pending maintainer agreement for `ASM_FUNC`.

`func_00282E80` is the related 48-byte xy-distance helper at all 28
placements. It subtracts two vectors, squares and sums xy, computes `vsqrt`
through Q and returns the scalar result through `qmfc2`; its VU0 body likewise
has no C route under this compiler. Keep the marker pending maintainer review.

`func_002830C0` is a 48-byte vector-matrix transform at all 28 placements.
It loads the input and four matrix columns with `lqc2`, accumulates the
products using `vmulax`/`vmadd*`, and writes the result using `sqc2`. The
qualified compiler has no C route for its COP2/VU0 body; keep the marker
pending maintainer review.

`func_00283388` is a 48-byte VU0 helper at all 28 placements. It builds four
vectors with `vmulx`, `vmr32`, `vmove` and `vaddw`, then stores them using
`sqc2`. As with the other decoded COP2 bodies, it has no C route under the
qualified compiler; retain the marker pending maintainer review.

`func_00282E48` is the 56-byte xyz-distance counterpart to `func_00282E80`,
identical across all 28 placements. It subtracts two vectors, squares and sums
xyz, computes `vsqrt` through Q, and returns the scalar result with `qmfc2`.
This body likewise has no C route under the qualified compiler; keep the
marker pending maintainer review.

`func_002833B8` is a 56-byte VU0 matrix initializer at all 28 placements. It
moves the scalar input to a VU0 register, forms rows using `vmulx`/`vaddx` and
`vmove`, and stores four quadwords with `sqc2`. No C route exists under the
qualified compiler; retain its marker pending maintainer review.

`func_00283D00` is a 56-byte scalar division/remainder helper at all 28
placements. It uses `vdiv` and Q, converts the quotient through `vftoi0` /
`vitof0`, and finishes the remainder calculation with VU0 instructions. Its
body likewise has no C route under the qualified compiler; keep the marker
pending maintainer review.

`func_002837D0` is a 64-byte vector transform at all 28 placements. It loads
two vectors, forms componentwise and cross-product terms with
`vopmula`/`vopmsub`, accumulates a dot-product component, and stores the
result with `sqc2`. Its COP2/VU0 body has no C route under the qualified
compiler; retain the marker pending maintainer review.

`func_00283360` is a 40-byte example: its body is identical in the boot and all
27 levels, and it uses `vmulx.xyzw`, `vmr32.xyzw`, `vaddw.x/y` and `sqc2`.
There are 151 direct calls to its placements across the 28 programs, confirming
that these are reachable instructions in a real function. No C attempt is
appropriate; leave `INCLUDE_ASM` until a maintainer agrees to `ASM_FUNC`.

**The rule that follows, and the traps it avoids:**

* A decoded COP2 instruction on a reachable path from a verified entry is evidence
  for original assembly under the qualified plain-C toolchain. An opcode-shaped
  data word alone is not evidence, and the function's extent must be coherent.
* A word of opcode 0x1C is evidence **unless** it is the SPECIAL2 arithmetic or the
  `por $rd,$zero,$rt` form. A body that carries only a `por` is not hand-written:
  `func_00308768` and `func_00322138` carry one and are ordinary C with a 128-bit
  store.
* `lq`/`sq` (0x1E/0x1F) and `ldl`/`ldr` (0x1A/0x1B) are **not** evidence: a
  `mode(TI)` type and a 16-byte struct copy reach them. Section 11 and this section
  replace the wave 13 screen's opcode list, which dropped 604 reachable bodies for
  nothing.
* **Decode with the R5900 category and the real address.**
  `rabbitizer.Instruction(word, address, rabbitizer.InstrCategory.R5900)`.
  Without the category a valid MMI word is printed `INVALID`, and a data word is
  printed as an instruction; both misclassifications happen.
* **A constant in a literal pool is data, not code.** It sits in the instruction
  stream, between two instructions, and decodes as an MMI word. The matched functions
  show the shape: `por $v0,$zero,$zero` before a `sq`.
* The six bodies that rest on an MMI word alone were read by hand, in their context,
  before being classified: two `pminw` in a sixteen-byte body, a `pmaxw` in a
  branch's delay slot, eleven `pcpyld` in a row, a `pcpyld` in a body, and a `pmaxw`
  in the block a row holds after its tail call.

**What it buys.** 101 bodies in the forty-three files of the wave 14 are hand-written.
56 of them are marked `ASM_FUNC` in pull request #270; the other 45 are in another
contributor's reservation, and the measurement is handed over with them, because the
holder of a body is the one who decides its marker. The marker changes no link — the
build takes those bodies from the game's own assembly whatever the marker says — it
only changes the count `tools/progress.py` reports, as rac1-decomp counts them.

### Reachable-instruction classification

The remaining available bodies were checked across all three releases. **27
functions, 990 placements** have a decoded instruction outside the qualified C
output, an external call/branch or code/data address witness at the entry, and
coherent reachable exits. They are marked `ASM_FUNC`, with no byte or C change.
This classification records the assembly required by these bodies; it does not
claim to recover whether their historical source was a separate assembler file
or mixed C/assembly.

The discriminating operations include real VU transfers/arithmetic and packed
integer operations, not the compiler's ordinary `por`, `mult1`/`madd`, quadword
copies or unaligned scalar loads. In particular:

- `func_00115250` uses parallel byte tests (`psubb`, `pnor`, `pand`, `pxor`) and
  packing, not just an ordinary `lq`/`sq` copy.
- `func_00282A18` uses `plzcw` with trapping `addi` and `sub`; the finding is about
  those exact instructions, not every opcode in the MMI space.
- `func_00283658` stores `$vf0` with `sqc2` in the return delay slot. That slot is
  executable evidence, unlike words beyond the return and its slot.
- The level vector/matrix helpers and the release-specific packed-rendering
  counterparts have the same instruction evidence at every applicable placement.

As negative controls, the reachable code of **4,863 current C functions in 1,484
compiled objects** contained none of the selected discriminating instructions.
Eight synthetic controls cover reachable vector/packed operations, live delay
slots, literals after a return or behind an unconditional branch, truncated
extents and compiler-reachable copies/zeroing. Separate TI, bit-count and scalar
arithmetic probes were compiled under the game and SDK profiles: successful
probes did not emit those operations; unsupported wide-integer expressions were
recorded as compilation errors, not evidence of a match. Absence from the C
control set alone is not a general impossibility proof for arbitrary compilers.

Four entries are deliberately still open: `func_001158F4` has no external witness
at its current entry, `func_00129410` is an incomplete fallthrough extent, and
`func_US2_L01_00305170` / `func_PAL_L01_00305C50` have outgoing-flow/extent
uncertainty. Their bytes and retained notes remain untouched; none receives
assembly-completion credit. Other contributors' reservations were excluded.

Retained attempts stay in `nonmatching/`, with their historical status made
explicit; this does not turn them into matched C or validated portable replacements.
Report checks distinguish pending C from pending original assembly, without
regenerating the reports or changing the progress policy.


## Historical catalogue-boundary proposals and follow-up

**Measured generator corrections:** `func_002C38A0` now starts eight bytes later
and spans 56 bytes; `func_00335918` starts 32 bytes later and spans 36 bytes.
The correction covers the boot and 27 level copies in each release, preserves
ends and canonical names, and leaves all prefix bytes in assembly. The shortened
first body collides with other boot bodies under normalized comparison, so the
generator retains its proven original pairing rather than renaming its level
copies. These are catalogue corrections, with no new C-match credit. Their
retained notes in `nonmatching/` are starting points for future source work.

**Further measured entries:** the generator also corrects the remaining supported
core, game and level entries, with separate rules for release-specific bodies.
Canonical names and original ends stay fixed; prefix bytes remain assembly.
The full original code alone does not justify changing a separately named method.
Likewise, an identity collision after shortening or removing a remnant does not
justify renaming unaffected methods. Synthetic tests cover both collision types,
stable replay, invalid extents and disagreement between corrected copies.

`func_L00_0032D208`'s resident boundary is now resolved: both direct calls reach
`0x00132828`, the corrected 44-byte body of canonical `func_00132818`, after sixteen
bytes of stack-restoration remnants. Its retained C uses that canonical name and
remains unlinked; historical results were 248/260 bytes, 0/27 placements in each
release with `-g`. The catalogue correction does not resolve its register and
address-reuse differences or qualify a new C match.

The individually checked one-word remnants in `FUNCTION_RESIDUES` follow closed
returns or a terminal jump and have no measured incoming references. They leave
the catalogue while their bytes remain in assembly; identical instructions at
other named entries remain untouched. Original notes and partial C in `nonmatching/`
remain available as history, rather than being silently discarded.

**Evidence limits remain:** a positive stack adjustment alone is not enough to
move an entry. `func_L00_002F74F0` has an incoming reference into its proposed prefix;
`func_00304210` lacks a corrected-entry witness at one placement. Neither is changed
by these rules. Other candidates without entry witnesses retain their extents;
arbitrary computed indirect targets are not disproved by the static scans.

In USA v1.01, the retained `func_L07_002B3580` exposes a different case: two calls reach
`func_001290BC + 0x24`, a measured VU normalization entry with `(output, input)`
in `$a0/$a1` and a vector store in the return delay slot. The parent row includes
preceding stores and padding. A plain C function-pointer expression using that
canonical symbol plus the addend currently fails assembly (`illegal operands`
for `jal`, followed by an `elf32-mips.c:2847` assertion), rather than producing a
measured mismatch. Its full C reconstruction is retained without a fake alias or
new function boundary. Reopen with a qualified canonical interior-call route or
an independently established catalogue correction; preserve the original bytes.

The old appendix is an investigation record, not a current work queue. Filler removals, mixed entry corrections and different-callee bindings must remain separate:

- func_L02_0035BD60 was reported 288 bytes with a proposed entry 0035BD70/268 bytes after a preceding tail. This audit does not adopt that correction without current extent/reference verification.
- Fourteen level 23 candidates were reported eight bytes early: 2F7478,306630,327208,32F798,33F9B0,3427C8,36CE80,3D8EC8,3DFC20,4277B0,441DC8,442300,443788,44D7B8. The recorded positive witness was a vtable/data pointer to 004277B8 for func_L23_004277B0. Level 30 candidates003557F0,003E1BA0,00404608 were reported similarly; the prior caller referenced 00404610. These remain individually checked boundary proposals, not blanket deletion rules.
- func_L16_00424B48's eight-byte restore/nop prefix is now independently verified and excluded; its 160-byte body starts at 00424B50. func_L11_00440790 remains a separate historical proposal (212 bytes, candidate 192-byte body and an apparently unreachable block). An old size or apparently dead block alone does not establish that second correction or handwritten code.
- **Differing-callee case resolved:** func_L00_003F5660 now uses ref_L00_003F5660_00 and passes 27/27, including levels 08,09,19,30. The old assertion that no single definition could represent it was wrong. Genuine nonrelocated immediate differences remain a different problem.

The historical full core scan reported 60 fill-starting entries rather than the earlier 26. Many simple cases were subsequently removed; mixed examples such as func_001158F4, func_0011A7F8, func_0011E920, func_0011ED28, func_0011F364, func_0011FB8C, func_00120354, func_00125D94, func_0012646C, func_0012F998 and func_00130A8C need their own boundary evidence. For `func_0012F998`, a 28 October 2026 USA v1.01 scan found no direct boot branch/jump target or aligned loaded-word pointer into the 16-byte row, which follows `func_0012F948`’s completed return and delay slot; PAL and USA v2.00 extents remain unaudited, so no correction is adopted. The old table and prose disagreed on func_0011F364: 28-byte prefix/608-byte body at 11F380 versus 4/632 at 11F368. Neither historical figure is adopted here as a verified correction. Preserve the real code until the discrepancy is resolved. **28 October 2026 follow-up for `func_0011A7F8`:** USA v1.01 decodes its 24-byte body as two `pref 0x0D,-0x3233($t6)` words, `addiu $v1,$zero,0`, `syscall 0`, `jr $ra`, `nop`. It follows the preceding function’s completed return and stack-adjustment delay slot. Scanning catalogued boot functions and aligned loaded words found no direct/pointer reference to the extent, but computed indirect entries are untraced and the syscall body itself is coherent. No C or handwritten classification is proposed; retain the marker pending entry/ABI and compiler review.

A known entry pointer is strong positive evidence; one pointer lookup is not proof that all other entry points or indirect targets are absent. Verify every affected placement and preserve raw bytes.

## Reading --diff correctly

The object column is unrelocated, so a zero call/address addend can differ visually without being wrong. Derive separately validates relocated opcode/register fields and consistent symbol bindings (section 44). All explicit size, instruction, relocation and binding rejection reasons matter. The first diagnostic is not exhaustive. Final acceptance requires the full strict linked build and every expected C placement.

## Aranos follow-up — historical linked results and current limits

PR #168 recorded 30 plain-C definitions (five level-specific, 25 shared), a 28-program build and a placement-preservation audit. This records that work's original measurements, not a newly rerun full build or a current pending-review claim.

Current checks reconfirm func_L00_002D4A38 at 27/27 using its real opaque absolute symbol, func_L00_003618D8 at 1/1 and func_L00_003E7768 at 1/1. The last body's historical size was 1308 bytes. These meaningful source/ABI witnesses do not authorize attributing every global or falsifying callee returns.

The original near misses remain distinct: func_L00_0038D750 improved from a retained pointer's 8 references/107 live instructions/9 calls to 7/58/7, but remained 1036/1044 bytes; func_L00_003D54B0 had a 4404/4424 attempt at 0/2; 003EE288 was 564/564 but differed; 00412E68 was 384/400 with a zero-store difference. Equal size also hid func_L00_0040EAA0's 0x60 versus 0x50 frame, bit-test and retained-constant differences. None of those historical attempts is promoted here.

The generator's Aranos corrections 00354DE8→00354DF8, 003D54A8→003D54B0 and 0040EA98→0040EAA0 preserve ends and are present in current source. Their positive evidence was actual data/vtable references; skipped prefixes remain assembly. The 4424-byte body then grouped with Siberius 003EBC90, changing the historical 9101 total to 9100 before later catalogue work. These old totals are not current progress. Other suspected boundaries were not resolved by that change.

## Additional measured findings

These attributed notes were imported from the existing contributor comments. They are now
shared entries that any contributor may correct through a PR. Their original dates and
pending labels are historical; reconcile them with current source and the updates above.
The original comment-workflow introductions are omitted because the shared editing rules
above replace them. The technical measurements are retained.

### Findings contributed by llesieur99

Source: [original contributor comment](https://github.com/OpenRAC/rac2-gc-decomp/issues/157#issuecomment-6305695078). The measurements below are
attributed for provenance, not exclusive ownership.

### Current findings

| Function / family | Status | Evidence and next action |
| --- | --- | --- |
| `_fpadd_parts`, `func_00122800` | **Merged, #265** | 576 bytes, 1/1 boot placement with the SDK profile. The assembler's bounded positive shifted-mask rule reduced two constants from seven to three instructions each. Full 28-program strict build passed. |
| `dpmul`, `func_00122B00` | **Merged, #267** | 680 bytes, 1/1 boot placement. Restoring the public fraction union restores the real alias dependence and the rounding `bnel`/store slot. Two sign-bit loads use the per-file unsigned assembler seed; the signed default remains unchanged. All 80 tests and 28 strict programs passed. |
| Late-issued ALU insn, `func_0032D758`, `func_0027BA68`, `func_L03_003C1BF0` | **Open, 1 November** | Each is 3 to 5 rows off with the structure exact. sched2's ready lists show the insn ready at t with the highest priority (`func_0032D758`: insn 20 p9 against p6), while retail's order needs it at t+1. The same compiler sources can only give that from a different RTL input, so a hidden insn is the likely cause, as in `func_002EE000` and `func_L00_00426C78`. To read the lists, rebuild `haifa-sched.o` privately with `BUF_LEN` 4096 and `-U_FORTIFY_SOURCE`, and print `INSN_PRIORITY` in `debug_ready_list`: `-dR -fsched-verbose-4` then works where `-dS` aborts. Tied: nine spellings of the table read, inline helpers, `-g`, `-frac2-qcopy`, sched flags. |
| Spill-slot order, `func_L00_003E5BD8` | **Open, 1 November** | 1108/1108, only 19 stack offsets differ. A private cc1 overriding `expr_hash_table_size` shows the slots follow gcse's bucket order: 133 buckets gives 7 rows, no odd size from 101 to 501 gives 0, and declaration order has no effect. Three pseudos remain rotated, so retail differs in more than the table size. |
| Weighted refs, `func_002FDBD8` | **Open, 1 November** | Global-alloc priority is `floor_log2(refs) * refs / live`, refs weighted by loop depth. With the shared `off` the colour block is exact but `n` falls to 15 refs; 16 would pass `direction`. One more read of `n` inside the loop is what is missing. |
| Copy epilogue, `func_00335370` | **Qualified C, 25 October** | Default game profile plus the reviewed shared `qcopy`: 88 bytes, 28/28 per release, all 84 strict programs pass. Prior TI-only measurements are historical; source is `src/game/00335370-copy.c`. |

For #267, a same-source comparison of 781 configured units changed code only in the new multiplier; eleven differences were debug-only. The shared union changed no object section in the four existing users. Source, flags and durable explanations are in the merged repository; partial C remains in `nonmatching/`. No progress report was regenerated.

### Camera and effect-record follow-up (23 October 2026)

Placement checks, followed by all 84 strict builds of the combined tree: `func_L00_002D9D98`
(228 bytes) and `func_L00_0033C638` (400 bytes) pass 27/27 placements in USA,
PAL and USA v2. `func_L00_0033E888` (372 bytes) passes 27/27 in USA and USA v2;
that name is absent from PAL's catalogue. All use the qualified qcopy/barrier
profile. The camera copy needs a retained local active pointer and ordinary
three-component scalar copies after the quadword assignment. The effect-record
sources require full-width incoming integer arguments, with narrowing at their
byte/halfword stores; the narrower drafts added unwanted sign-extension work.

The retained `func_L00_003B77A8` now contains actual C: its alleged unreachable
MMI words are `por` zero materialization, and its copies are compiler-reachable
quadwords. The current candidate is 372/352 bytes, 0/27 USA placements; it is
not handwritten-assembly evidence. Other measured camera/effect drafts and their
next source hypotheses are retained in `nonmatching/`. Equal-size candidates
`func_L00_003B6858` (384 bytes), `func_L00_002DB350` (356 bytes) and
`func_L00_0033AA40` (384 bytes) still differ at +0x40, +0x4 and +0x24 respectively.
The collision-grid function consumes both the incoming position pointer and f12
margin. No progress report was regenerated.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L00_002DB350` is C in `src/levels/shared/L00_002D7940-grid.c` (`-O2 -G0 -ffunction-sections`), placed at 27 US, 27 PAL, 27 US2 places; `func_L00_0033AA40` is C in `src/levels/shared/L00_0033AA40.c` (`-O2 -G0 -ffunction-sections`), placed at 27 US, 27 PAL, 27 US2 places; `func_L00_003B6858` is C in `src/levels/shared/L00_003B6858-g8.c` (`-O2 -G32 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-barrier`), placed at 27 US, 27 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

### Shared object-vector and effect helpers

The retained C for `func_L00_00387BB0` and `func_L00_0038A650` reaches the
248-byte target size with `-frac2-qcopy -frac2-qcopy-barrier -g`, but matches
0/27 USA placements: allocation differs at +0x10 and CSE forwards a copy from
the original input instead of reloading the first local. Their `por` zero and
`lq`/`sq` operations are compiler-reachable. The former MMI-only exclusions
were screens, not measured C impossibility proofs.

`func_L00_0038D650` likewise reaches 252 bytes with `-frac2-zero-ti-por` and
matches 0/27: the final packed-colour shift/OR order first differs at +0xC0.
The retained sources and concise `nonmatching/README.md` entries identify the
remaining lifetime and source-shape hypotheses. Equal size gives no matching
credit, and these bodies retain their `INCLUDE_ASM` markers.

The effect callers also expose an ABI requirement: `func_002A7A00` forwards its
incoming two floating bounds unchanged into `func_002A7878` before drawing the
two angles. The bounds belong in the prototype and in that first call; an
argument-free declaration can preserve incidental registers while describing
the wrong C interface. Caller reconstruction must account for these bounds.

### Eight-slot envelope aggregation, `func_L00_002D6BA8`

Retained, not matched (23 October 2026): default `-O2 -G0 -ffunction-sections`,
1068/1068 bytes, 0/27 placements in each of USA, PAL and USA v2, first difference
+0x18. The actual C covers signed short lifetime/phase updates, all six real
retail dispatch arms, seven canonical conversion/sine calls, and both additive
and multiplicative channel averages. Separate final walking pointers recover
the retail body size; merging them gives 1060 bytes. The remaining count-array
bases occupy the opposite s3/s4 registers, with entry/final-loop scheduling and
two pointer-add operand orders still different. The qualified `-g` experiment
instead gives 1084 bytes. Eight bounded source/profile trials were retained
privately; reopen on independent evidence for the original counter-array
lifetimes, rather than repeating the declaration permutations. No assembly
classification or matching credit is claimed.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L00_002D6BA8` is C in `src/levels/shared/L00_002D67A8-envelope.c` (`-O2 -G0 -ffunction-sections`), placed at 27 US, 27 PAL, 27 US2 places. The measurements above are kept as history.

### Packet-rendering and effect-state constraints

The retained `func_L00_003EFA98`/`func_L00_003EFD00` quad renderers reach
612/600 bytes with game O2/G8, but remain 0/27 in all three releases. Their
transform is one three-row object: `func_00283098` reads rows at +0/+16/+32.
UV cursors walk the containing 144-byte packet, rather than stepping past an
eight-float subarray after the last vertex. Object/pointer lifetimes, flag packing
and store scheduling still differ; a related matched renderer is the next useful
allocation witness.

`func_L00_003F7268` reaches 872 bytes; its rectangle helper `func_0027DE50`
stores the fifth argument with `sd`, so the observed colour is the full 64-bit
`0xFFFFFFFF80808080`, not a guessed 32-bit interface. Its two effect-call sites
need a function-scoped reference: the callee identity is shared at 25 places and
different at two. The binder at the end of `func_L00_003F87B0` likewise has
23/4 identities in both USA releases. These references and all real arguments
remain in the retained C even though neither body matches. The latter's normalize
call precedes initialization of its packet input in retail; the source preserves
that ordering and does not invent a zero vector.

The same review issue prevents integrating PR #361's `func_00333048` draft.
In USA v1.01, the call at +0x36C normalizes the hit packet at stack +0x40;
its first identified initialization follows at +0x3CC. This reads meaningful
XYZ components before their producer. The draft remains in `nonmatching`
with corrected allocator return declarations; the source marker stays assembly.
Resolve the packet's producer/lifetime before claiming defined C or adding
initialization that the retail body does not perform.

The 320-record state machine `func_L00_003F0680` reaches 796 bytes with O2/G0
and its SDA declaration, reproducing the initial absolute and later GP table load;
index/constant/local-vector registers remain permuted. `func_L00_003F6B10`
reaches 916 bytes and the retail seven-FPR frame after shortening modulation
lifetimes, but pointer/FPR assignment and scheduling still differ. All six bodies
remain assembly-backed; the retained sources and README specify their measured
coverage and one reopening condition each.

### Newly qualified compiler profiles and review findings

- **Copy scheduling, merged #275:** `-frac2-qcopy-barrier` supplies the schedulers' conservative volatile-copy dependence model while game sources remain ordinary C assignments. Twelve witnesses pass 59 placements. Independently checked: 113 tests, all 28 strict programs, and an 814-unit comparison with no code changes by default; only the twelve selected units change. This models scheduling, not every optimizer effect of inline assembly, and does not establish the original macro or justify `ASM_FUNC` classification.
- **Wide-store delay-slot searches, merged #279:** `-frac2-no-annulled-wide-stores` restricts two thread/target search paths; optimize_skip and ordinary delay slots remain unchanged. Two witnesses pass three placements. Independently checked with #275: 123 tests, all 28 strict programs and 816 units with no default code changes; only the two newly selected units change. The PR's census counts were not independently reproduced in this review. This is an opt-in compiler policy, not a hardware prohibition.
- **Names and interfaces:** new calls must use catalogue identities rather than abbreviated level-address aliases. The new predicate caller in #277 now shares one two-argument definition with its callee, leaving the candidate pointer unused, instead of using an assembler-name alias with a different parameter count. Both the 88-byte callee and 832-byte caller remain exact.

The review integrated #272, #273, #274, #275, #277, #278 and #279: 57 new functions, 24,940 distinct bytes at 198 placements. The final target/unit check covers 86 functions at 414 placements. Partial work remains retained; no progress report was regenerated. Contributors need a compiler rebuilt from the new recipe before using the new per-file options.

### Historical catalogue and multiply audit

The audit below preceded the catalogue correction subsequently merged in #253. Its measurements are preserved as history; the five residue rows are no longer a pending generator task. The six multiply bodies were not evidence of unused multiplication or handwritten assembly: their R5900 GPR destinations are consumed.

#### Original audit during PR #243

I checked the qualified USA v1.01 retail bytes and the current compiler while integrating #243.

#### The six multiplications are used

The two-operand disassembly omitted R5900 `mult`'s GPR destination (`rd`). All seven multiply sites in the six reported boot bodies write a nonzero destination register, which the following address calculation consumes:

| Function | Multiply site(s) | Destination | Observed use |
| --- | --- | --- | --- |
| `func_00291788` | `0x002917A0` | `$v1` | address addition at `0x002917AC` |
| `func_00288208` | `0x00288270` | `$v0` | address addition at `0x00288274` |
| `func_00288308` | `0x0028835C` | `$a0` | address addition at `0x00288368` |
| `func_002883E8` | `0x00288408` | `$v1` | address addition at `0x0028840C` |
| `func_002887B0` | `0x002887DC` | `$v0` | address addition at `0x002887E0` |
| `func_002B65B8` | `0x002B660C`, `0x002B6624` | `$a0` | both paths reach the address addition at `0x002B663C` |

The qualified GNU opcode table includes the `mult d,s,t` form with `WR_d`. As an independent control, the current compiler translates ordinary `return index * stride;` into a three-operand `mult` writing the return register, without `mflo`.

**Decision:** withdraw the unused-multiply/compiler-origin hypothesis for these six bodies. This evidence does not justify `ASM_FUNC` and is not a compiler barrier. The absence of `mflo` alone is insufficient; decode `rd` and follow its uses.

**28 October 2026, retained source control:** `func_L00_0042AC18` now has a complete game `-O2 -G0 -ffunction-sections` attempt in `nonmatching/levels/func_L00_0042AC18.c`. Ordinary C emits both three-operand multiplications; the former screen claiming otherwise is retired. Five trials reach 380/380 bytes but 0/4 placements in each USA release (PAL has no row): sound-record pointer and handle allocation still differ. This is a source-lifetime near miss, with no linked or matching credit.

#### The five catalogue extents have evidence of residual code

| Row | Size | Placements checked | Preceding boot return |
| --- | ---: | ---: | --- |
| `func_00289018` | 4 | 1 | `0x0028900C` |
| `func_002A77C0` | 28 | 1 | `0x002A77AC` |
| `func_002FED78` | 12 | 1 | `0x002FED68` |
| `func_002FF0B0` | 36 | 1 | `0x002FF0A4` |
| `func_002FDB40` | 148 | 23 (boot + 22 levels) | `0x002FDB30` |
| `func_0033B538` | 4 | 1 (boot) | `0x0033B52C` |
| `func_003172D0` | 188 | 1 (boot) | `0x00316E08` ends at `0x003172CC`; this row starts four bytes later |

Every checked placement follows a preceding `jr $ra` and its delay slot. A scan of the corresponding program's text found no direct branch/jump target inside any of these extents; a scan of the loaded non-code sections found no aligned literal pointer into them. The mixed arithmetic/store fragments are therefore supported as catalogue residues by their surrounding code and reference audit, not merely by their lack of `jr $ra` or by FPU nops.

**28 October 2026 USA v1.01 follow-up:** `func_003172D0` is a 188-byte boot-only row between the end of `func_00316E08` at `0x003172CC` and `func_00317390`. Its bytes are 24 stack-pointer increments with interleaved `nop`s, one `swc1 $f0,0($a1)`, and a final stack increment; they have no new frame setup or return. Scanning all catalogued boot functions found no direct branch/jump target into the row, and no aligned loaded-word value points into its extent. This supports a catalogue-boundary concern; it is not proof against computed indirect entry. Leave its marker and catalogue row untouched pending maintainer review.

**Decision:** keep these as catalogue-correction cases, not C-matching targets or handwritten-function credit. #243 retains the observations but does not change the catalogue. A separate generator change should verify every affected placement, preserve the original image bytes, and include regression tests before dropping these rows. This static audit does not establish the absence of computed indirect targets, so do not generalize it into an opcode-only deletion rule.

**29 October 2026 USA v1.01 all-placement audit:** `func_0033B538` is a four-byte boot row containing only `daddu $v0,$a0,$zero`. In the boot and all 27 level placements, it follows the preceding function’s completed `jr $ra` and stack-adjust delay slot, then a nop; the next catalogue entry starts with a new frame prologue. Across all 28 loaded programs, scans found no direct branch/jump target at the row, no aligned loaded-word pointer to it, and no adjacent `lui` plus `addiu`/`ori` construction of its address. This strengthens the catalogue-residue hypothesis but does not rule out computed indirect entry. Keep its marker and catalogue row unchanged pending maintainer review; do not add it to residue handling before that review.

**29 October 2026 USA v1.01 screening:** `func_003495B8` and `func_0034CE88` have boundary patterns audited across all 28 placements and no direct branch/jump, aligned pointer or adjacent high/low address-pair references; see the placement-specific entries above. These support catalogue-residue hypotheses but cannot rule out computed indirect entry or establish other-release behavior. Keep both markers and rows unchanged pending maintainer review. Do not add either to residue handling without that review.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_00288208` is C in `src/game/002880E0.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_L00_0042AC18` is C in `src/levels/shared/L00_0042AC18.c` (`-O2 -G0 -ffunction-sections`), placed at 4 US, 4 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

### game/00308600 follow-up — PR #287 merged; original near miss retained

- `func_00308600` remains a near miss. The old draft incorrectly used the return of `func_002A0488` for the +0x30 byte, and wrote +0xBC after `func_002A0F48`; retail writes both before their calls. The corrected draft remains in `nonmatching`. With current master compiler sources, `-frac2-qcopy -frac2-qcopy-barrier -fno-gcse` produces 356/360 bytes, 0/28 USA v1.01 places. The copy pairs, saved f20/f21 and 0x50 frame agree, but the initial stores merge two retail 255 materializations and GPR allocation differs. Typed fields, a short argument and scheduling/CSE controls did not resolve it; the short argument's 360-byte result contains unwanted sign extension. Reopen with independent field-type or constant-lifetime evidence, rather than repeating those variants.
- `func_0030E700`, in the same source unit, is now a merged 424-byte plain-C implementation: 28/28 USA v1.01 places pass `tools/check.py` with default flags. The first candidate differed only around `func_002ABBB8` argument setup. Its integer/float interleaving already used in `src/levels/04_barlow/L04_00422A00-g8.c` resolves those differences without a compiler change. USA v1.01 `tools/build.py all --strict --jobs 8`: all 28 programs OK, no C fallback; 139 unit tests, repository checks under Ubuntu, progress --check and diff checks pass. Merged in [PR #287](https://github.com/OpenRAC/rac2-gc-decomp/pull/287), commit `76254265`. The qualified USA v2.00 input also passes all 28 target places and all 28 full strict builds, with zero C fallback. Both PR CI checks passed. This adds one distinct 424-byte C function, with 28 placements per applicable USA release; no report was regenerated. No PAL implementation or new matching credit is claimed.

### Findings contributed by bigmak94

Source: [original contributor comment](https://github.com/OpenRAC/rac2-gc-decomp/issues/157#issuecomment-6321947233). The measurements below are
attributed for provenance, not exclusive ownership.

| Function / family | Status | Evidence and next action |
| --- | --- | --- |
| **Vector copy as a scheduling barrier:** `func_002B5E48`, `func_002EE988`, `func_L23_00418650`, `func_L23_003C01F8`, `func_L23_00418DC0`, `func_L23_004256F0`, `func_L02_003DB158`, `func_L02_003D47B0`, `func_L26_003D4930`, `func_L12_00413CE0` (close: `func_002B50E0`, `func_L23_0041D0A0`); from today's first attempts at level 2, also `func_L02_00401BF8`, `func_L02_003F1A88`, `func_L02_003EE938`, `func_L02_003E8CE8` | Merged, #275 | Each is retail's size with `-frac2-qcopy` in a unit of its own. Each is exact when the copy is the volatile asm `lq $2,0(%1) ; sq $2,0(%0)`, in scratch copies only. The profile's grouped pair lets independent instructions cross it. About 50 single flags and many source orders, including `-frac2-zero-ti-barrier`, do not. #275 (merged) adds the opt-in `-frac2-qcopy-barrier`, the clear's block in `sched_analyze_insn` applied to the qcopy insn. Twelve witnesses landed with it. Twenty-three more near misses are exact with it as their records stand, in #283; two more follow. `func_002B50E0` is still 3 words off, a sched1 tie on argument moves. A 29 October aligned 48-byte character-buffer probe under `-O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier` preserves the same `+0x124` three-move difference, so byte-buffer storage does not change the soft-frame-pointer tie. |
| **The barrier copy's link costs:** `func_L02_003F1A88` | Qualified with reviewed helper | The TI/barrier profile was five words off because its producer-link latency differed from the real macro dependency graph. The approved `qcopy` helper closes the 228-byte function under default G0, 1/1 in each release. No compiler link-cost patch is needed. Preserve the original distinction: modeling only part of an inline helper's optimizer effects need not reproduce the actual helper. |
| **A TImode zero reloaded as a register pair:** `func_L02_004388A0` | Open, measured | 5 words off with the barrier: its 16-byte zero clear is reloaded as a group of two general registers, though the R5900 holds it in one. That makes `$v1` a spill register, so a hoisted sentinel -1 left unassigned gets `$v1` where retail has `$v0`. Without the clear (diagnostic only), every -1 is in `$v0`. |
| **A register saved and never used:** `func_L02_003FF6E8` | Open, measured | Retail saves `$s2` and never uses it; 21 retail game functions do so, and none of them is C. A plain C spelling reproduces the frame and register roles but keeps the value in `$s2`, 700 bytes against 696. Also `func_00326A10` (28 October 2026): retail saves `$s0` unused beside `$s1` = 0x8710; the C reaches 444/444 bytes with frame 0x90 and the constant in `$s0` ([record](../nonmatching/game/func_00326A10.c)). |
| **Clear through a register address at a nonzero offset:** `func_002B5678` | Open | Retail has `addiu $v0,$s1,0x60 ; sq $zero,0($v0)`, the clear macro's register operand. After #258, C gives `por` + `sq $v0,0x60($s1)`. **Next:** a profile that materializes the address of a displaced const-0 TImode store. |
| **A `por` clear at a zero displacement:** `func_L02_003DB200`, `func_L02_00423520`, `func_L23_00422798`, and with the copy barrier `func_L02_003DBA70`, `func_L23_00429DC8` | Proposed: PR #281 | These functions clear a stack vector with `por $v0,$zero,$zero` + `sq $v0,0($sp)`. Since #258, the fold still makes that `sq $zero,0($sp)`, because the address is register-only.<br><br>A finer retail count (one place per catalogue row, boot game code from 0x26EA00, a store counted when every path into it starts from the `por`) finds 183 `por`-fed stores at a zero displacement, in 153 functions. Every one of them is to `0($sp)`; none goes through another register. Against that, 396 `sq $zero,0(reg)` stores in 263 functions, of which 82 (58 functions) are also to `0($sp)`.<br><br>PR #281 adds the opt-in `-frac2-zero-ti-por`: with it, the fold leaves a store to `0($sp)` alone, and stores through any other register still fold. It is neutral by default (806 of 806 units). Forced on everywhere, it changes exactly the 4 units whose matched functions clear `0($sp)` with `sq $zero`. The five functions above are exact with it. `func_L23_003C16D8` stays out: three of its clears go through a computed stack address. |
| **A cse block boundary that leaves no instruction:** `func_L02_003D26B0`; the five 632-byte twins `func_L11_00436D08`, `func_L11_00449C70`, `func_L11_0044C850`, `func_L11_004530E0`, `func_L11_004566C0`; `func_L02_003F1BA8`, `func_L02_0040BBD8`; `func_L07_00378898` | Open | Retail keeps a gcse (PRE) copy, for example `daddu $s5,$s4,$zero` of `e + 0x10`, that this cc1 makes only when cse1 and cse2 both see a label at that spot. Adding `\|\| x == 7 \|\| y == 9` to the test reproduces it, with extra code. An empty `do { } while (0)` reproduces it exactly but is rejected (#257, fc4a6c6). For `func_L07_00378898`, `-fno-cse-follow-jumps -fno-cse-skip-blocks` reproduces the block, as a probe only. **Next:** the original's construct at that spot, or a measured cse rule. |
| **A non-empty `do { ... } while (0)` as a block barrier:** `func_L02_003FB000` (288 bytes), `func_0033A520` (360 bytes, 28 places), `func_002D53F0` (140 bytes, 28 places) and `func_L20_004450D8` (232 bytes) | Question for maintainers | `func_L02_003FB000` is exact with its last store wrapped in `do { ... } while (0);`. The loop notes give the shared `jr $ra` retail's alignment `nop`, which cc1 adds only after a loop. `func_0033A520` needs a block boundary after its rounding of `D_001B23A4 * 300`; the wrapper gets that block right, and six allocation words remain. `func_002D53F0` is exact with its draw call wrapped and 329.0f held in a local; its rounding of `D_001B23A4 * 329.0f + 0.5f` is the same shape as `func_0033A520`'s. `func_L20_004450D8` is exact with the entry jump of its group walk wrapped (`do { goto check; } while (0)`), which keeps gcse's `%hi` copy of the table last; without it, eight entry-block words differ.<br><br>Two merged functions use the same wrapper as a documented scheduling barrier: `func_00124818` and `func_L23_0041C8C0` (ours). The repository check rejects only the empty form. Since AGENTS.md rules out artificial barriers, we have not landed more. **Question:** is a non-empty wrapper acceptable as a macro-shaped statement, or should the two precedents be revisited? |
| **Jump tables the build cannot place:** `func_L06_003FDA08`, `func_L13_00422CB8`, `func_L03_003C4578`, `func_L02_003F9AF0`, `func_L02_003F9B70`, `func_L02_003FE1B0` | Solved, PR pending | A computed goto through retail's own table, in the form of `func_00310A40`, matches all six. The three level 2 records' in-order switches were wrong: retail's tables map the values to the bodies in another order. Decode the table before trusting a record's `switch`. |
| **Labels behind hazard nops:** `func_L18_004308F0`, `func_L02_00411530` | Merged, #264 | Opt-in `-frac2-hazard-labels`. 198 retail branch targets after a compare or `mtc1` sit on the nop, and SN's `Ps2EeAs` agrees. Forced on everywhere it is neutral (778 of 779, one `.mdebug`). |
| **gcse critical-edge split, Cygnus block merge:** `func_002CD720`, `func_L02_003E79F8`, `func_L02_003FCCA0`, `func_L18_004283F0` | Merged, #261 | Opt-in `-frac2-gcse-unsplit-edges` and `-frac2-keep-block-order`. `func_L23_0041B9F0` reaches retail's size with the gcse switch and still stops at the copy order. |
| **PRE keeps a load across a store to another offset:** `func_L02_003EEC58` (and `func_L23_0041C0E8`) | Open | Retail reloads the index after a store to a disjoint offset of the same base. A historical `volatile` probe reproduces it. Current RAC1 also uses volatile fields; this is not a blanket-forbidden source method (see COMPILER-NOTES.md). **Next:** establish whether a faithful field qualifier describes the target's actual accesses before considering an opt-in PRE rule. The old probe alone does not qualify either solution. |
| **Wide store in an annulled slot:** `func_L02_0042EDD0`, `func_L23_00422668`, `func_L02_003E7370` | Merged, #279 | Retail's game code has no `sd` or `sq` among the 2,895 stores in annulled slots. Ordinary slots hold 547 `sq` and 497 `sd`, and annulled slots do take wide loads.<br><br>PR #279 adds the opt-in `-frac2-no-annulled-wide-stores` (reorg's thread and steal paths; `optimize_skip` is kept). It is neutral by default (796 of 796 units); forced on in every game-compiler unit, it changes only the two witnesses. `func_L02_0042EDD0` (2 places, with the clear barrier) and `func_L23_00422668` (with `-frac2-qcopy`) are exact with it. `func_L02_003E7370` also needs the clear barrier in a call slot, and the barrier then also catches a plain C clear. |
| **Catalogue rows that are not functions:** `func_0011B320` (4 bytes), `func_0011B450` (4 bytes), `func_0011E920` (24 bytes), `func_0012FB10` (52 bytes), `func_00131CB0` (8 bytes), `func_00288D40` (20 bytes), `func_00290718` (4), `func_00298D10` (20), `func_0029CEC8` (12), `func_00130AAC` (4), `func_002B0A08` (12), `func_002B4068` (36), `func_002B49A0` (12), `func_002B8530` (20), `func_0026FEF0` (20), `func_00272540` (12), `func_002725C8` (20), `func_002DF630` (12), `func_002ED570` (4), `func_002ED848` (36), `func_002ED880` (28), `func_002ED8F0` (84), `func_002ED9A8` (20), `func_002EEBB0` (20), `func_002FC460`, `func_002FC510`, `func_002FC618`, `func_002FC868` (4 each), `func_0033B538` (4), `func_003380A8` (4) | Evidence, left as markers | Each row starts after a completed return or tail jump and its delay slot, possibly with alignment padding, and ends at the next function. No branch or jump in any catalogued boot function reaches it (scan of every boot row). Their words, like `sw $v0,-0x3D14($gp)` or `addiu $sp,$sp,0x10 ; nop`, read as unreachable tails. **28 October 2026 follow-up:** `func_0029CEC8` is 12 bytes in the boot and 23 level placements. Each USA v1.01 copy is `sw $a0,-0x4000($gp); nop; addiu $sp,$sp,0x10`, immediately after the preceding completed return and its stack-adjustment delay slot; there are no direct branch/jump targets or aligned non-text pointers into the extent in any of the 24 programs. A temporary `return 0` probe emits 8 bytes and matches 0/24. PAL and USA v2.00 retail dumps are unavailable here, so retain the catalogue row and marker pending release-qualified review. **28 October 2026 follow-up:** `func_002ED9A8` is 20 bytes in the boot and 23 level placements. Every USA v1.01 copy begins immediately after the preceding completed return and its stack-adjustment delay slot; its body is `lw $v0,0xC($v1); nop; addiu $sp,$sp,0x20; nop; addiu $sp,$sp,0x20`. No direct branch/jump targets or aligned non-text pointers enter the extent in any of the 24 programs. A temporary empty C probe emits 8 bytes and matches 0/24. PAL and USA v2.00 retail dumps are unavailable, so leave the marker and catalogue row pending release-qualified maintainer review. **28 October 2026 follow-up:** `func_002ED848` is 36 bytes in the boot and 23 level placements. Its USA v1.01 body is an orphan GP store, register no-ops, zero assignments, and two stores through the zero register; all 24 copies follow a completed return, its delay slot and padding, with no direct branch/jump target or aligned non-text pointer into the extent. The empty C probe emits 8 bytes, 0/24. PAL and USA v2.00 dumps are unavailable; keep the marker and row pending maintainer review. **28 October 2026 follow-up:** `func_002EEBB0` is 20 bytes in the boot and 23 level placements. Each USA v1.01 copy begins immediately after the preceding completed return and its stack-adjustment delay slot; the body is `daddu $v0,$zero,$zero; nop; addiu $sp,$sp,0x140; nop; addiu $sp,$sp,0xC0`. No direct branch/jump target or aligned non-text pointer enters the extent in any of the 24 programs. An empty C probe emits 8 bytes and matches 0/24. PAL and USA v2.00 retail dumps are unavailable, so keep the marker and catalogue row pending maintainer review. **28 October 2026 follow-up:** `func_002ED8F0` is 84 bytes in the boot and 23 level placements. All USA v1.01 copies follow a completed return and its value-move delay slot, then one `nop`; the 21-word extent contains only stack adjustments with nops, one float load, one word load, and `daddu $v0,$a2,$zero`. No direct branch/jump target or aligned non-text pointer enters the extent in any of the 24 programs. An empty C probe emits 8 bytes and matches 0/24. Other-release dumps are absent; leave the marker/catalogue row pending maintainer review. **28 October 2026 follow-up:** `func_002ED880` is 28 bytes in the boot and 23 level placements. Each USA v1.01 copy follows a completed return and its load delay slot, then one `nop`; the body is `sw $a0,0x48($v0); lw $v0,0x48($v1); nop; nop; nop; addiu $sp,$sp,0xB0`. No direct branch/jump target or aligned non-text pointer enters the extent in any of the 24 programs. An empty C probe emits 8 bytes and matches 0/24. PAL and USA v2.00 retail dumps are unavailable, so the marker/catalogue row remain pending maintainer review. **28 October 2026 follow-up:** `func_002B0A08` is 12 bytes in the boot and three level placements. Its four USA v1.01 copies begin with `sh $zero,0x1C($a0); nop; addiu $sp,$sp,0x30`, immediately after the preceding completed return and its stack-adjustment delay slot; no direct branch/jump target or aligned non-text pointer enters the extent. An empty C probe emits 8 bytes and matches 0/4. PAL and USA v2.00 dumps are unavailable; leave the marker and row pending maintainer review.<br><br>Three level rows fit the same pattern (DrLegitamate, 28 October 2026, USA v1.01): `func_L09_003FB780` (4 bytes; levels 09, 22, 23: `daddu $v0,$zero,$zero`), `func_L25_00373ED0` (4: `addiu $v0,$v0,0`) and `func_L25_00373F08` (4: `sw $a0,0x48($v0)`). Each of the five placements follows a `jr $ra`, its delay slot and padding, and is followed by a `nop` and the next function. No branch or jump label in its program's disassembly reaches it, and no aligned word in the level's `text.bin`, `data.bin`, `lit.bin` or vtables equals its address. Left as markers. **28 October 2026 follow-up:** `func_0011B320` is a single `daddu $v0,$zero,$zero` word at the boot address. It follows `func_0011B270`’s completed `jr $ra`, its `addiu $sp,$sp,0x40` delay slot and one padding `nop`; no direct branch/jump target in any catalogued boot function or aligned word reference in the loaded boot image points into it. A temporary empty C probe is 8 bytes, 0/1. Keep its marker/catalogue row pending maintainer review; do not add it to the residue mechanism without release-qualified review.  **28 October 2026 follow-up:** `func_0011B450` is a single `and $a0,$a0,$v0` word. It follows `func_0011B3D0`’s completed `jr $ra`, stack-adjustment delay slot and one padding `nop`; a scan of catalogued boot functions found no direct incoming target, and no aligned loaded-word pointer equals its address. The empty C probe emits 8 bytes, 0/1. Leave the marker pending the maintainer’s catalogue-rule decision.  **28 October 2026 follow-up:** `func_00130AAC` is the single word `pref 0x0D,-0x3233($t6)` between `func_00130AA0`’s tail jump and the `func_00130AB0` prologue. The preceding jump is `j func_130C68` with its `addiu $a0,$a0,0x4C` delay slot. No direct boot branch/jump target or aligned loaded-word pointer enters the one-word row. The empty C probe is 8 bytes and matches 0/1. Keep its marker/catalogue row pending maintainer review.  **28 October 2026 follow-up:** `func_003380A8` is the word `sw $zero,0($v0)`, after the completed return and padding of `func_00338098` and before `func_003380B0`’s prologue. No direct branch/jump target in a catalogued boot function or aligned loaded-word pointer enters the row. The empty C probe is 8 bytes, 0/1. Leave the marker/catalogue row pending maintainer review.  **28 October 2026 follow-up:** `func_00131CB0` is 8 bytes: `addiu $v1,$zero,0x23; syscall 0`. It follows `func_00131CA8`’s completed tail jump to `func_11FA20` and its `daddu $a0,$zero,$zero` delay slot; the next row begins with a new prologue. No direct boot branch/jump target or aligned loaded-word pointer enters this row. An empty C probe is also 8 bytes but emits `jr $ra; nop`, matching 0/1. Keep its marker/catalogue row pending maintainer review.  **28 October 2026 follow-up:** boot-only `func_00272540` is 12 bytes: `daddu $v0,$a1,$zero; nop; addiu $sp,$sp,0x10`, immediately after the preceding function’s return/delay sequence and before the next stack-frame prologue. No direct target in a catalogued boot function or aligned loaded-word pointer enters the row. A temporary empty C probe emits 8 bytes and matches 0/1. Leave its marker and row pending maintainer review.  **28 October 2026 follow-up:** boot-only `func_002DF630` is `daddu $v0,$zero,$zero; nop; addiu $sp,$sp,0x30`, after a completed return, its stack-adjustment delay slot and one `nop`, and before the next prologue. No direct target in a catalogued boot function or aligned loaded-word pointer enters it. The empty C probe is 8 bytes, 0/1. Keep the marker and catalogue row pending maintainer review.  **28 October 2026 follow-up:** boot-only `func_0026FEF0` is 20 bytes: `sw $v0,0x38($a0); nop; addiu $sp,$sp,0x10; nop; addiu $sp,$sp,0x20`. It follows a completed return and its `+0x80` stack-adjustment delay slot, immediately before a new frame prologue. No direct target in catalogued boot code or aligned loaded-word pointer enters the row. An empty C probe is 8 bytes, 0/1. Leave its marker and row pending maintainer review.  **28 October 2026 follow-up:** boot-only `func_002725C8` is 20 bytes: `addiu $sp,$sp,0x80; nop; nop; nop; sw $zero,0x4($v0); nop`. It follows the preceding function’s completed return and stack-adjustment delay slot, then three `nop`s; the next row starts a new frame. No direct boot target or aligned loaded-word pointer enters the extent. An empty C probe is 8 bytes, 0/1. Keep the marker and row pending maintainer review.  **28 October 2026 follow-up:** boot-only `func_002B8530` is 20 bytes: `lwc1 $f0,0x2D0($a2); nop; lwc1 $f0,0x258($a2); nop; addiu $sp,$sp,0x30`. It follows a completed `jr $ra`, its `sh $zero,0x18E($v0)` delay slot and one padding `nop`; a new stack prologue follows the row. No direct target in catalogued boot code or aligned loaded-word pointer enters it. An empty C probe is 8 bytes, 0/1. Keep its marker/row pending maintainer review.  **28 October 2026 follow-up:** boot-only `func_0011E920` is 24 bytes: `addiu $sp,$sp,0x10; nop; addiu $sp,$sp,0x30; nop; addiu $sp,$sp,0x30; pref 0x0D,-0x3233($t6)`. It follows a completed return and its stack-adjustment delay slot; a fresh `-0x50` frame follows the row. No direct target in catalogued boot code or aligned loaded-word pointer enters it. An empty C probe is 8 bytes, 0/1. Keep its marker and row pending maintainer review.  **28 October 2026 follow-up:** boot-only `func_0012FB10` is 52 bytes and follows a completed return, its stack-adjustment delay slot and one `nop`. Its store/load/offset-add sequence has no direct branch/jump target in catalogued USA v1.01 boot functions and no aligned loaded-word pointer into the range. The row exists in PAL and USA v2.00 catalogues, but those dumps are absent; preserve its marker and row pending release-qualified maintainer review. **Next:** a `tools/levels.py` rule for unreachable inter-function words, if maintainers want one. |
| **Rows that begin inside the previous epilogue:** 113 unmatched level-catalogue rows, 8 of them reserved by me (`func_L02_003EA180`, `func_L02_004004D0`, `func_L02_00439CD8`, `func_L03_00421398`, `func_L19_003DCCC8`, `func_L19_003DD9D8`, `func_L23_00415988`, `func_L23_004277B0`) | Evidence for §47's entry corrections | Each row starts with 8 to 104 bytes of epilogue words (a positive `addiu $sp,$sp,N`, `nop`), then directly a prologue `addiu $sp,$sp,-N`. None of the 137 rows that begin with such words is C. In all 1,065 placements, no branch or jump reaches the leading words.<br><br>106 rows have a reference to the prologue (a code address pair, a data pointer or a call) and none into the leading words. Two also have a data word equal to a leading address. Five have no reference found.<br><br>`func_L02_004004D0` is one of them: `func_L02_003FAF28` passes `D_L02_004004D8` as a callback, and its C equals retail from +8 except for the copy barrier. **Next:** entry corrections such as `LEVEL_ENTRY_OFFSETS`, keyed so that boot and level identity holds. I can prepare them for my eight if wanted. The list is below the table. |

<details><summary>The 113 rows, with the reference found at the prologue (programs counted per row)</summary>

- `func_002BB050` (176 bytes, 8 leading): address pair in 25 programs
- `func_002BC508` (604 bytes, 8 leading): address pair in 27 programs
- `func_002BCA08` (244 bytes, 8 leading): address pair in 27 programs
- `func_002BEBC0` (688 bytes, 8 leading): address pair in 13 programs
- `func_002BEE70` (1312 bytes, 8 leading): address pair in 22 programs
- `func_002BF518` (468 bytes, 8 leading): address pair in 27 programs
- `func_002C00F0` (260 bytes, 8 leading): address pair in 27 programs
- `func_002C01F8` (244 bytes, 8 leading): address pair in 27 programs
- `func_002C0C70` (80 bytes, 8 leading): address pair in 17 programs
- `func_002C14D8` (488 bytes, 8 leading): address pair in 27 programs
- `func_002C1DB0` (160 bytes, 8 leading): address pair in 8 programs
- `func_002C1E50` (160 bytes, 8 leading): address pair in 26 programs
- `func_002C29A0` (228 bytes, 8 leading): address pair in 27 programs
- `func_002C38A0` (64 bytes, 8 leading): address pair in 26 programs
- `func_002C3B08` (632 bytes, 8 leading): address pair in 27 programs
- `func_002C43C8` (312 bytes, 8 leading): address pair in 27 programs
- `func_002C47E8` (808 bytes, 8 leading): address pair in 27 programs
- `func_002C4B50` (456 bytes, 8 leading): address pair in 24 programs
- `func_002C5068` (180 bytes, 8 leading): address pair in 27 programs
- `func_002C5400` (332 bytes, 8 leading): address pair in 27 programs
- `func_002C64D8` (196 bytes, 8 leading): address pair in 26 programs
- `func_002C7620` (296 bytes, 8 leading): address pair in 25 programs
- `func_002C8348` (224 bytes, 8 leading): address pair in 26 programs
- `func_002DB1B0` (524 bytes, 8 leading): pointer at 00:001AB158 (+134 more)
- `func_002DC900` (436 bytes, 8 leading): pointer at 00:002866DC (+26 more) **(a data word also equals a residue address: needs review)**
- `func_002DE0D0` (716 bytes, 16 leading): none **(no reference found)**
- `func_00304210` (2240 bytes, 104 leading): pointer at 00:002A2EFC (+23 more)
- `func_00335C60` (96 bytes, 16 leading): pointer at 00:001ADC34 (+26 more)
- `func_00336288` (128 bytes, 8 leading): pointer at 00:001ADDAC (+26 more)
- `func_00336468` (44 bytes, 8 leading): pointer at 00:001ADD4C (+26 more)
- `func_003367C0` (104 bytes, 8 leading): pointer at 00:001ADD8C (+26 more)
- `func_L00_002F74F0` (120 bytes, 64 leading): address pair in 27 programs **(a data word also equals a residue address: needs review)**
- `func_L00_003B3158` (756 bytes, 8 leading): pointer at 00:002A3190 (+26 more)
- `func_L00_003B3450` (1396 bytes, 8 leading): pointer at 00:002A319C (+26 more)
- `func_L00_003B7D48` (1008 bytes, 8 leading): pointer at 00:002A31D8 (+2 more)
- `func_L00_003CA650` (52 bytes, 8 leading): address pair in 27 programs
- `func_L00_003DC640` (476 bytes, 24 leading): address pair in 27 programs
- `func_L00_00410D20` (952 bytes, 8 leading): pointer at 00:002A3838 (+11 more)
- `func_L00_004195C8` (156 bytes, 8 leading): pointer at 00:002A38A4 (+5 more)
- `func_L00_00419A80` (212 bytes, 16 leading): pointer at 00:002A38B0 (+1 more)
- `func_L01_003B1F08` (1676 bytes, 8 leading): pointer at 01:002A562C (+2 more)
- `func_L01_003D8358` (1116 bytes, 8 leading): pointer at 01:002A5890
- `func_L01_00410AD0` (1548 bytes, 8 leading): pointer at 01:002A5BB4
- `func_L01_00412E00` (280 bytes, 8 leading): pointer at 01:002A5C98
- `func_L01_0041C890` (204 bytes, 8 leading): pointer at 01:002A5D1C (+7 more)
- `func_L02_003EA180` (772 bytes, 8 leading): pointer at 02:002A6670 (+1 more)
- `func_L02_004004D0` (384 bytes, 8 leading): address pair in 1 program
- `func_L02_00439CD8` (1548 bytes, 8 leading): pointer at 02:002A6AB4
- `func_L03_0038AA20` (268 bytes, 24 leading): address pair in 1 program
- `func_L03_003C5FE8` (540 bytes, 8 leading): pointer at 03:002A98DC
- `func_L03_003C7E20` (2008 bytes, 8 leading): pointer at 03:002A9900 (+2 more)
- `func_L03_00421398` (1428 bytes, 8 leading): pointer at 03:002AA008
- `func_L04_003AB458` (512 bytes, 104 leading): pointer at 04:002CA84C
- `func_L04_003EE7C0` (1056 bytes, 8 leading): pointer at 04:002CAC90 (+1 more)
- `func_L04_00404068` (152 bytes, 8 leading): address pair in 2 programs
- `func_L04_0041AD18` (968 bytes, 8 leading): pointer at 04:002CAE10 (+1 more)
- `func_L04_0044BC90` (612 bytes, 8 leading): pointer at 04:002CB104
- `func_L05_0033D3A0` (1848 bytes, 8 leading): none **(no reference found)**
- `func_L05_00414F90` (1548 bytes, 8 leading): pointer at 05:002BBF64
- `func_L05_00419888` (1084 bytes, 16 leading): pointer at 05:002BBFB8 (+3 more)
- `func_L05_0041A228` (2164 bytes, 8 leading): address pair in 4 programs
- `func_L05_00441F30` (1128 bytes, 8 leading): pointer at 05:002BC304 (+3 more)
- `func_L06_003E1040` (104 bytes, 8 leading): address pair in 2 programs
- `func_L06_004012B0` (1388 bytes, 8 leading): pointer at 06:002E2800
- `func_L06_00455BC0` (1548 bytes, 8 leading): pointer at 06:002E2CB0
- `func_L07_003791E8` (36 bytes, 8 leading): pointer at 07:002A3640
- `func_L07_003B72E8` (1264 bytes, 8 leading): address pair in 1 program
- `func_L07_00409300` (172 bytes, 8 leading): pointer at 07:002A3DE4 (+3 more)
- `func_L07_00416510` (2048 bytes, 8 leading): pointer at 07:002A3F70 (+3 more)
- `func_L09_003FEF00` (4028 bytes, 8 leading): pointer at 09:002A6FBC
- `func_L09_0041D650` (976 bytes, 8 leading): pointer at 09:002A7238
- `func_L10_00415A50` (1548 bytes, 8 leading): pointer at 10:002BE41C
- `func_L11_0046D660` (1548 bytes, 8 leading): pointer at 11:002BCA74
- `func_L11_0046F8F0` (2220 bytes, 8 leading): pointer at 11:002BCB58 (+1 more)
- `func_L11_0047A310` (2184 bytes, 8 leading): pointer at 11:002BCC18
- `func_L12_00417690` (1548 bytes, 8 leading): pointer at 12:002A9238
- `func_L12_00418418` (2144 bytes, 8 leading): address pair in 1 program
- `func_L12_00420660` (468 bytes, 8 leading): pointer at 12:002A93F4
- `func_L12_00429D60` (236 bytes, 8 leading): address pair in 3 programs
- `func_L13_003C5908` (456 bytes, 8 leading): pointer at 13:002AE20C (+1 more)
- `func_L13_0041CD18` (1548 bytes, 8 leading): pointer at 13:002AE710
- `func_L13_0041F8B8` (808 bytes, 8 leading): pointer at 13:002AE800
- `func_L14_003E4208` (2104 bytes, 8 leading): pointer at 14:002AAB38
- `func_L14_00421BC0` (1548 bytes, 8 leading): pointer at 14:002AAED4
- `func_L15_0041F2F8` (1548 bytes, 8 leading): pointer at 15:002BC54C
- `func_L16_003A8D58` (904 bytes, 8 leading): pointer at 16:002A4A78 (+2 more)
- `func_L16_003E70E0` (220 bytes, 8 leading): address pair in 1 program
- `func_L16_004165B0` (1880 bytes, 8 leading): pointer at 16:002A5084
- `func_L16_00424B48` (168 bytes, 8 leading): pointer at 16:002A51E0
- `func_L17_00417DB0` (1548 bytes, 8 leading): pointer at 17:002A4CA8
- `func_L17_0041A4C0` (468 bytes, 8 leading): pointer at 17:002A4DB0
- `func_L18_0042FBC8` (1568 bytes, 8 leading): pointer at 18:002C15C8
- `func_L18_00436B80` (1548 bytes, 8 leading): pointer at 18:002C1610
- `func_L18_00439960` (1636 bytes, 8 leading): pointer at 18:002C16F4
- `func_L18_0043C778` (896 bytes, 16 leading): pointer at 18:002C1730
- `func_L18_00447128` (2056 bytes, 16 leading): pointer at 18:002C1880
- `func_L19_003D2E38` (1308 bytes, 8 leading): pointer at 19:002A6EB4
- `func_L19_003DCCC8` (2568 bytes, 16 leading): none **(no reference found)**
- `func_L19_003DD9D8` (3336 bytes, 8 leading): none **(no reference found)**
- `func_L19_003DFD68` (4696 bytes, 8 leading): none **(no reference found)**
- `func_L19_00412140` (3316 bytes, 8 leading): address pair in 1 program
- `func_L19_0041C3D8` (148 bytes, 8 leading): pointer at 19:002A728C
- `func_L20_00438F98` (1548 bytes, 8 leading): pointer at 20:002B62A0
- `func_L20_004451C0` (1392 bytes, 16 leading): pointer at 20:002B6408
- `func_L22_003AD090` (280 bytes, 8 leading): pointer at 22:002A71A0 (+1 more)
- `func_L22_0040F1C0` (1548 bytes, 8 leading): pointer at 22:002A7668
- `func_L22_004135F8` (1388 bytes, 8 leading): pointer at 22:002A7758
- `func_L23_00415988` (1548 bytes, 8 leading): pointer at 23:002ABCE4
- `func_L23_004277B0` (52 bytes, 8 leading): pointer at 23:002ABE40
- `func_L24_003EFA38` (1376 bytes, 8 leading): pointer at 24:002A2948 (+1 more)
- `func_L30_003E1BA0` (724 bytes, 8 leading): pointer at 30:002AA3A0
- `func_L30_00404608` (236 bytes, 8 leading): address pair in 1 program
- `func_L30_0040E660` (236 bytes, 8 leading): address pair in 1 program

</details>

One more row outside the census above, because its first leading word is a store
(DrLegitamate, 28 October 2026, USA v1.01): `func_L12_0035A838` (288 bytes, one
placement) begins with `sw $t3,0x40($v1) ; nop ; addiu $sp,$sp,0x20 ; nop`, the previous
body's tail, and its leaf body starts at `0x0035A848`. The word at `12:00288180` points
to `0x0035A848`; no code label, `jal` or aligned word in the level's files reaches
`0x0035A838`..`0x0035A844`. Adding `(12, 0x0035A838): 16` to `LEVEL_ENTRY_OFFSETS` and
rerunning `catalogue` changes exactly that row, to `func_L12_0035A848` (272 bytes). Not
applied: the PAL and v2.00 catalogues and reports name the row `func_L12_0035A838` at
their own addresses, so the repair should be carried to all three releases together
(`tools/carry.py --entries`). The same body, with the same 16 leading bytes, is the row
`func_L05_00367340` (pointer at `05:0029D4F0` -> `0x00367350`) and `func_L20_0036AE68`
(pointer at `20:00292390` -> `0x0036AE78`), likewise unreferenced in their leading
words. Measured with all three `LEVEL_ENTRY_OFFSETS` entries and the three
`FUNCTION_RESIDUES` above applied: `catalogue` changes exactly those six rows and the three
bodies stay separate rows (272 bytes each; their data references differ), unit tests pass,
but `tests/check_repository.py` reports that the PAL and v2.00 catalogues still name all six
rows, so the repair needs `tools/carry.py` with those releases' dumps. The L20 row is also
described as a catalogue defect in `nonmatching/README.md`.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_002BC508` is C in `src/game/002BC508-g8.c` (`-O2 -G8 -ffunction-sections -g`), placed at 28 US, 28 US2 places (PAL catalogue has no function of this name); `func_002BEBC0` is C in `src/game/002BEBC0-hazard-labels.c` (`-O2 -G0 -ffunction-sections -frac2-hazard-labels`), placed at 28 US, 28 US2 places (PAL catalogue has no function of this name); `func_002C3B08` is C in `src/game/002BF6F0.c` (`-O2 -G0 -ffunction-sections -g`), placed at 28 US, 28 US2 places (PAL catalogue has no function of this name); `func_L00_003B3158` is C in `src/levels/shared/L00_003B3158-shard.c` (`-O2 -G0 -ffunction-sections -frac2-zero-ti-por -fno-gcse`), placed at 27 US, 27 US2 places (PAL catalogue has no function of this name); `func_L02_003D26B0` is C in `src/levels/02_maktar_nebula/L02_003D26B0-aim-g8.c` (`-O2 -G8 -ffunction-sections -frac2-keep-block-order`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L02_003F1BA8` is C in `src/levels/02_maktar_nebula/L02_003DB310-aim-g8.c` (`-O2 -G8 -ffunction-sections -frac2-keep-block-order`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L02_0040BBD8` is C in `src/levels/02_maktar_nebula/L02_0040A4A8-aim-g8.c` (`-O2 -G8 -ffunction-sections -frac2-keep-block-order`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L05_00441F30` is C in `src/levels/shared/L05_00441F30-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 4 US, 4 US2 places (PAL catalogue has no function of this name); `func_L07_00378898` is C in `src/levels/07_siberius/L07_002BE770-rotation-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L07_00416510` is C in `src/levels/shared/L07_00416510-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 4 US, 4 US2 places (PAL catalogue has no function of this name); `func_L11_00449C70` is C in `src/levels/11_joba/L11_004465F8-aim-g8.c` (`-O2 -G8 -ffunction-sections -frac2-zero-ti-por -frac2-keep-block-order`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L11_0044C850` is C in `src/levels/11_joba/L11_004465F8-aim-0044C850-g8.c` (`-O2 -G8 -ffunction-sections -frac2-zero-ti-por -frac2-keep-block-order`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L11_004530E0` is C in `src/levels/11_joba/L11_004465F8-aim-004530E0-g8.c` (`-O2 -G8 -ffunction-sections -frac2-zero-ti-por -frac2-keep-block-order`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L11_004566C0` is C in `src/levels/11_joba/L11_00453358-aim-g8.c` (`-O2 -G8 -ffunction-sections -frac2-zero-ti-por -frac2-keep-block-order`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L12_00429D60` is C in `src/levels/shared/L12_003E1CB0-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 3 US, 3 PAL, 3 US2 places; `func_L18_0042FBC8` is C in `src/levels/18_damosel/L18_0042FBC8-g8.c` (`-O2 -G16 -Wa,-G16 -ffunction-sections -g`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L18_00447128` is C in `src/levels/18_damosel/L18_00447128-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L19_003D2E38` is C in `src/levels/19_grelbin/L19_002CAAB0-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L23_0041B9F0` is C in `src/levels/23_damosel_orbit/L23_0041B9F0-g8.c` (`-O2 -G8 -ffunction-sections -frac2-gcse-unsplit-edges`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L30_003E1BA0` is C in `src/levels/30_insomniac_museum/L30_003E1BA0-g8.c` (`-O2 -G8 -ffunction-sections -Wa,-G32`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

## Shared hero table and object helpers

The retained `func_L00_002D1DA0` attempt now passes its input to the canonical
identity helper and calls `func_002A7820(0, count - 1)`. The latter's two-argument
implementation selects an inclusive integer range: the live second argument was
missing from the old draft, not a dead instruction to preserve artificially.
With game `-O2 -G8`, the corrected C is 312/312 bytes but still 0/27 in each of
USA v1.01, PAL and USA v2.00. The first difference is +0x9C: two loop-preheader
words exchange the pointer copy and terminator, and the final record address has
the opposite `addu` operand order. Scheduling-profile alternatives did not fix it.

`func_L00_002D1B70` now has a real C selector/search attempt rather than a screen.
The GP word at -0x60F0 in `func_L00_002D6418` is the level mode
`D_L00_001A8F00`; the old retained note incorrectly identified it as the resident
state base. Its shared rejection label recovers the block order but is not exact.
The retained sources and measured profiles are in `nonmatching/levels/`.

### Shared hero selection and transition interfaces

**Linked qualification, 23 October 2026:** [the three C definitions](https://github.com/OpenRAC/rac2-decomp/commit/112b1c8333a75a9e435614f3e17db541d8e6d734)
add 1,912 distinct bytes. `func_L00_002C3BB0` and `func_L00_002C3E18` pass
26/26 places each in all three releases; `func_L00_002CA898` passes 20/20 in
both USA releases and is absent from PAL's catalogue: 196 placements total.
The combined tree passes all 84 strict program builds, 143 tests, repository
hygiene and progress checks, without C fallback or report regeneration.

The selector reconstructions use the actual `func_L00_002AE388` interface:
two integer-register pointers and four floats. The region predicate is
`func_002ACBC8(point, index)`, and the probe's object predicate is
`func_002ABB78(object)`; omitting the live index or object would be a false ABI.
In `func_L00_002C3E18`, private record +4 is loaded/stored as a float, not an
integer copy, and its private pointer is captured before updating the shared
outputs. Unsigned node bytes and a heading snapshot before default-range
selection are material source details in `func_L00_002C3BB0`.

`func_L00_002CA898` has two genuinely variable external identities: its five
dispatch calls and three selector calls use separate function-scoped references,
with `int(int, int)` and `int(int)` interfaces respectively. A per-function byte
check alone can pass a misleading direct catalogue name at these call sites.
The retained `func_L00_002CAB08` dispatcher and `func_L00_002C2DE8` first callee
likewise use scoped references for measured placement-dependent families.
Duplicate numbered data externs used during clock/range experiments were removed:
the retained drafts preserve each actual containing object under one canonical
identity and report the resulting nonmatching measurements.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L00_002AE388` is C in `src/levels/shared/L00_002AE388-range.c` (`-O2 -G0 -ffunction-sections -ffast-math -g -frac2-hazard-labels`), placed at 27 US, 27 PAL, 27 US2 places; `func_L00_002CAB08` is C in `src/levels/shared/L00_002CAB08.c` (`-O2 -G0 -ffunction-sections`), placed at 27 US, 27 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

### Level-shared bodies that read $gp (wave 10, 25 October 2026)

Three retained near misses from this wave (`func_L09_003FE0C0`, `func_L10_00423788`,
`func_L12_003E1EE8`) plus the observations below.

- A `disp($gp)` access in a body that is byte-identical at several places reads the
  **same absolute address** in every program (GP is 0x1AEFF0 everywhere), so the C name
  is the defining level's `D_LNN_XXXXXXXX` (GP + disp) in a `-g8.c` sibling, declared
  `__attribute__((sda))` when it must stay a scalar. Measured in this wave:
  0x1550/0x1554/0x1560/0x1564/0x1568 -> D_L11_001B0540/..44/..50/..54/..58,
  0x1390/0x13A0 -> D_L17_001B0380/001B0390, 0x3758 -> D_L17_001B2748,
  0xAB0 -> D_L05_001AFAA0, 0x2250/0x227C/0x2290/0x2294 -> D_L18_001B1240/..6C/..80/..84,
  0x1B20 -> D_L12_001B1B10, -0x3FEC -> D_L17_001AB004, -0x66F0 -> D_L00_001A8900.
  The `L12_003E1CB0-g8.c` header records the sda-size and second-name tricks needed to
  keep a nearby `lui`/`lw` bare while the scalar takes the `$gp` form.
- `func_L17_003A4740` starts with `sw $a0,-0x3FEC($gp); nop` **before** `addiu $sp,-0xB0`.
  This cc1 never schedules a store ahead of the frame adjustment, so plain C cannot
  produce the first two words. The extent itself is not suspect: the preceding row
  `func_L04_003C6FE8` ends exactly at 0x3A4740. Do not call it handwritten on this
  alone; the entry needs an indirect-reference audit first.
  **Update, 1 November 2026 (local match):** v1.01's and v2.00's catalogues start the function
  after those two words, and its C is in `L17_0032C070-grid.c`. PAL's row
  (`func_PAL_L17_003A7DB0`, 528 bytes) still includes them, as `func_PAL_L01_0039A174` (524
  bytes, 12 places) includes a leading `nop`; those two PAL rows stay assembly until the
  catalogue cuts them the same way.
- `func_L11_003F2A30` dispatches through a compiler jump table of 11 entries based at
  D_L11_002BAA10 (`lw $a0,0($v1); jr $a0`, cases reached from `a0[0x42]`). wslcmp
  checks only the function bytes, so a `switch` whose case *order* differs can look
  close; `tools/build.py`'s jump-table qualification is the real check.
- `func_L18_00428138` repeats its last two guards (`D_L18_001AFBB0 != 0` and
  `D_L18_00189E20+0x2294 == 0x6F`) inside each case of its kind switch after checking
  them before the switch. The duplication is in retail, so the retained C has to spell
  it twice; merging it changes the branch layout.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L04_003C6FE8` is C in `src/levels/shared/L04_003C6FE8-timer.c` (`-O2 -G0 -ffunction-sections -g`), placed at 3 US, 3 US2 places (PAL catalogue has no function of this name); `func_L10_00423788` is C in `src/levels/10_hrugis_cloud/L10_003170D0-collision.c` (`-O2 -G0 -ffunction-sections`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L11_003F2A30` is C in `src/levels/11_joba/L11_003F2A30-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 1 US, 1 US2 places (PAL catalogue has no function of this name); `func_L12_003E1EE8` is C in `src/levels/shared/L12_003E1EE8-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 2 US, 2 US2 places (PAL catalogue has no function of this name); `func_L18_00428138` is C in `src/levels/shared/L18_00428138-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 3 US, 3 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

### Particle and effect pointer lifetimes (28 October 2026)

The following are retained C near misses, not linked matches. Measurements use
the maintained game compiler at this revision, with the profiles stated below.
Default `qcopy` is used where a grouped transfer needs register addresses;
no non-clobbering copy, register pin, false call interface or synthetic access is
part of these attempts.

- `func_002C3B08`: 628/624 bytes in every US placement with the source unit's
  `-O2 -G0 -ffunction-sections -g` profile. Plain TI transfers reproduce the
  object-relative stores; default `qcopy` gives 632 bytes. Raw and typed particle
  layouts tie with object/current/motion in s1/s2/s0 instead of s2/s0/s1 and one
  repeated collision-argument move. The current callable extent is 624 bytes;
  the older 632-byte extent measurement above includes its repaired prefix.
- `func_002C5120`: 716/732 bytes with the same profile. Raw and typed follower
  state views retain a 0x60 rather than 0x70 frame and a different interpolation
  schedule. Delaying the velocity pointer's source declaration does not close it.
- `func_00316400`: 712/708 bytes at `-O2 -G0 -ffunction-sections`. Explicit
  `MACRO_ADDR` views of both tables reach 708 bytes, but table/parameter allocation
  and two floating bound-register pairs differ. Explicit bound locals are worse
  (772 bytes); a typed 0xA0 record view ties.
- `func_003166C8`: 772/772 bytes with that profile and `MACRO_ADDR` on the vector
  constant. The first copy address remains live across the angular updates,
  shifting record/index/position allocation. A plain TI first copy gives 760
  bytes and folds its store address.
- `func_L18_0043EA90`: 852/852 bytes in US levels 18 and 20 at
  `-O2 -G8 -ffunction-sections`, with state/count swapping s0/s1. Diagnostic
  objects are identical: state has 12 references, live length 99 and 15 call
  crossings; count has 6, 66 and 9. Declaration order, aligned point storage and
  a truthful FP-first declaration of the first helper tie. The dynamic frame and
  unrolled effect sequence already agree.
- `func_L30_00415090`: 840/840 bytes at `-O2 -G0 -ffunction-sections`; the final
  outgoing-argument schedule differs from +0x2C8. The actual `func_002B0CE0`
  returns a status in v0, including 3 on its success path; retaining its integer
  return closes the earlier pad-load register difference. Pad scalar/array views,
  color temporaries/regrouping and a truthful FP-last interleaving do not close
  the argument setup after nine compiles.

Reopen these deposits with evidence about the original pointer lifetimes or
argument-evaluation schedule, rather than repeating the tied spellings. Only US
local checks were run for these near misses; other releases and strict linked
qualification remain unverified.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_002C3B08` is C in `src/game/002BF6F0.c` (`-O2 -G0 -ffunction-sections -g`), placed at 28 US, 28 US2 places (PAL catalogue has no function of this name); `func_00316400` is C in `src/game/0030F7B0.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 US2 places (PAL catalogue has no function of this name); `func_L18_0043EA90` is C in `src/levels/shared/L18_00427BE0-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 2 US, 2 PAL, 2 US2 places. The measurements above are kept as history.

### Effect helpers reopened with current source methods

The reconnaissance stubs for `func_L11_00456EA0`, `func_L11_00458C38`,
`func_L05_00445B58` and `func_L05_00445C38` have been replaced by real C in
the linked source tree. Local checks pass every carrying place in US, US2 and
PAL, and all 84 strict linked programs pass with these implementations. Their old
GP/quadword-only screens were not evidence against C. The basis helper's
three homogeneous zeros use a chained float assignment, retaining `mtc1`
and the measured `swc1` order without volatile accesses. The Joba burst's
typed integer/FP interleaving keeps both register banks' actual arguments;
the nested random expressions retain the observed call order.

The related `func_L05_00427E10` impact reconstruction passes all four US and
US2 places and is absent from PAL. Its packet has a 16-byte direction,
attacker, flags, byte kind/mode, halfword class, float damage and enable word, followed by the callee-read float at +0x24.
The complete request occupies 0x28 bytes; retail leaves its final word unwritten.
The indexed target-list loop, unlike the equivalent early pointer
initialization, retains retail's guarded pointer setup and GPR allocation.

The remaining recovered drafts are still near misses, with real C and
measurements in `nonmatching/`: `func_L11_00456938` (260/268, retreat-branch
folding and probe-copy placement), `func_L05_00445D60` (560/560, index-view
and output-pointer allocation), and `func_L05_004276E8` (644/640, constant
hoisting). `func_L00_00300438` now uses the actual `double` return of
`func_001234F0` and the variadic formatter. That contract correction does
not match it: scalar pair swaps restore the retail frame but leave
444/468 bytes. The discarded aggregate swap needed another 16 stack bytes.
Do not restore the old false integer return to influence allocation.

`func_L18_00428138` was also withdrawn as a local candidate on 28 October 2026:
`src/game/002B60B0.c` establishes that its helper returns `void *`, while the
candidate had incorrectly declared `void`. The corrected retained C is 512/512
bytes at `-O2 -G8 -ffunction-sections`, but its post-call control `lhu`/`sh` use v1
instead of retail v0 at +0x14C/+0x16C in all three US and US2 placements. Explicit
discard, the truthful all-four-FP-first argument view, an explicit SDATA alias and
`-fno-force-mem` tie; `-fno-schedule-insns` worsens the result. Its marker is
restored. Reopen with evidence for the post-call halfword value lifetime; a false
helper return type is not an acceptable match.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L11_00456938` is C in `src/levels/11_joba/L11_00453358-retreat-g8.c` (`-O2 -G8 -ffunction-sections -frac2-zero-ti-por -g`), placed at 1 US, 1 PAL, 1 US2 places; `func_L18_00428138` is C in `src/levels/shared/L18_00428138-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 3 US, 3 US2 places (PAL catalogue has no function of this name). The measurements above are kept as history.

### Scalar-SDA table walks and packet construction

PR #357 review also withdraws `func_L01_003EC0C0` and `func_L01_00405300`
from matching C. Removing the volatile table/index accesses preserves their
752- and 736-byte sizes, but changes the load and floating-argument schedule
after interpolation calls (USA first differences +0x1CC and +0x204). A measured
128-byte pose-record view, separate scalar locals and short-lived record pointers
tie. The ordinary reconstructions remain in `nonmatching/`; every release fails
its one local place. Their former byte matches do not justify forced reloads.

The same review removes the `damoselSetState` assembler-name alias. The source
unit uses one canonical `void func_002A7750(void *, int, int)` declaration;
`func_L18_00441438` retains its local match with that real interface.

`func_L04_00456860` keeps the isolated `-fno-gcse` profile for a measured reason.
With GCSE enabled, `m + 0x10` is hoisted into the positive-count loop preheader
and held in s3: the frame grows from retail's 0x90 to 0xA0 and the body from
396 to 408 bytes. `-frac2-gcse-unsplit-edges`, `-frac2-keep-block-order` and their
combination all retain that result. Disabling GCSE preserves the in-loop address
evaluation and the 396-byte body. This is a per-file choice, not a global setting.

`func_L00_00303418` now has C passing all 27 local places in US, US2 and PAL.
The previous comment misread the first flag update: `ori` in an unconditional
branch's delay slot is live. The mixed table-pointer loads use ordinary
`__attribute__((sda))` declarations with game -G0. They give cc1 a bare scalar
access; the assembler expands absolute forms in ordinary flow and GP forms in
branch slots. This preserves the measured duplicated initializer reads without
inventing volatile accesses. Explicit all-GP or all-absolute views are not the
same source/profile.

`func_0027DE50` passes all 28 local places in each release. Review of PR #357
removed the volatile qualifiers and the separate assembler-name write alias:
one ordinary declaration of the packet cursor preserves the measured reloads
and stores. Each header has its own pointer lifetime; the two 16-byte templates
are separate measured objects. The coordinate-offset globals are ordinary
integer objects too; no forced access is needed for this sequence.
Coordinate-offset snapshots retain the real load order before the first writer
reload. Signed halfword assignments preserve the actual 0x8001/0x8004 writes.
The separate native-only packet draft corroborates the template extents and
64-bit fifth argument; its functional-table row is retired in favor of the real
source definition. Both implementations pass every carrying placement and the
strict linked builds in all three releases.

The former diagnostic-only `func_L05_00441D40` and `func_002FF0D8` screens now
retain meaningful C in `nonmatching/` with the remaining allocation, address and
store-order differences. Neither is counted as matching C.

The old diagnostic-only refusal of `func_L09_003F9970` is superseded by qualified
C (28 October 2026): its four formerly invalid words are ordinary
quadword transfers, reproduced by default `qcopy`. A measured `MACRO_ADDR` view
of the scratch symbol keeps its final address setup together. The 256-byte body
matches both placements in US, US2 and PAL at the default `-O2 -G0
-ffunction-sections` profile. The actual float returns of `func_002A7E08` and
`func_002AA458`, and the void return of `func_L02_00332D28`, are retained from
their existing definitions. The strict linked builds pass in all three releases.

`func_L20_00443A10` is also qualified as of 28 October 2026, matching its
332-byte placement in US, US2 and PAL at the default `-O2 -G8
-ffunction-sections` profile. A typed 128-byte heading-reference record selects
the measured index/base registers; updating the existing heading value keeps
the branch result in its old FP register. Loading the last reference pointer
after the sine call and before the output stores fixes the tail schedule.
The float return banks of the math helpers were checked against their retail
bodies. The old source-order/register trials remain historical measurements;
strict linked builds now pass in all three releases.

Further bounded controller measurements on 28 October 2026 are retained outside
the linked sources. None is a local match, and only US was measured:

- `func_L09_0041A700`: 900/916 bytes, default G8 profile, five compiles. Computing
  each saturating nibble update's address inside its parity branch improves the
  first 836-byte version. Retail preserves the counter's high address in s2
  across the later proximity path; the retained source rebuilds it. The real
  `enabled` field is reloaded after the counter test even on a path without a call.
- `func_L15_004353E8`: 1104/1104 bytes, default G0 profile, nine compiles. Moving
  independent initialization writes closes the FP-vector register and most store
  residues, leaving two initial stores, the -1 temporary and the final timer store
  versus six FP stores. Prefix struct/union views and `-g` tie; disabling second
  scheduling worsens. Helper contracts follow the existing definitions.
- `func_L20_004433B0`: 344/344 bytes, default G8 profile, three compiles. Branch-local
  initial index reads and reloading the loop index before its condition label
  reproduce the branch structure and length, but object/table-high/best cycle
  s4/s5/s3 rather than s3/s4/s5. The pointer return remains explicit; promotion
  would require the caller's pointer declaration and explicit stored-address cast.
- `func_L20_00445890`: retained at 564/568 bytes, default G8 profile, six compiles.
  Naming the real missing-object sentinel before the state change fixes the
  object/loop-count register swap. Remaining differences include the list-index
  GPR, color-tail store merge and high-bit constant slots. A switch worsens to
  596 bytes; explicit color temporaries and `-frac2-keep-block-order` do not close
  it. An SDATA view and the absolute view address the same canonical object table.

These deposits need measured pointer-lifetime or scheduling evidence before
another retry. Their prior diagnostic-only refusals remain historical notes,
not proof that current helpers or address aliases cannot express the bodies.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L20_00445890` is C in `src/levels/20_yeedil/L20_00445890-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 1 US places (PAL and US2 catalogues have no function of this name). The measurements above are kept as history.

### Prison oscillator: the ignored message result still affects allocation

`func_L14_00426F28` has a retained game `-O2 -G8` draft at 744/744 bytes.
Its scalar SDATA views, unsigned timer snapshot and actual float return of
`func_002AA2E8` reproduce the remainder/FP paths. The query `func_002A9640`
returns a hit pointer, and `func_L00_0030DD70` returns an integer, as shown by
its implementation in `L00_002FC7A0.c`. With those contracts the final object
flag update uses v1 instead of retail's v0 (+0x248 through +0x268). Unsigned
16-/32-bit snapshots tie; a 64-bit snapshot grows to 752 bytes. A void message
prototype produced a local byte match but was rejected, and its source marker
was restored. **Next:** an evidenced object-field scope or allocator-lifetime
explanation; do not recover the apparent match by discarding the integer return.

`func_L07_003F7968` is likewise a size-exact retained controller (632 bytes,
game `-O2 -G8 -frac2-qcopy -frac2-qcopy-barrier`). Its sole remaining instruction
is bnel instead of bnez at +0xE4 in the bounded tier selector. The observed
child-pointer reloads need no invented volatile fields: ordinary byte/halfword
accesses already retain them. Independent clamps shorten the body, reversing
the arms changes block order, and debug labels do not change the branch. This
compiler rejects `-mno-branch-likely`; no compiler change was made.


**28 October–29 October 2026 near-miss rechecks:** `func_00280510` remains 248/240 bytes and 0/28 on current-master USA v1.01 with the actual `func_002FC560(u32, u64)` prototype supplied in a temporary probe; helper relocations resolve, but the resident global load and branch/control layout differ. `func_0029CD48`'s retained candidate used a false integer parameter for the actual no-argument `func_0029CD20`; with the real helper interface and pointer conversion, it is 232/240 bytes and 0/28, so the earlier exact-size result and its tail analysis are superseded. A temporary `noinline` attribute on `func_0029CD20` leaves the candidate at 232/240. `func_0029FDF0` remains 176/240 and 0/28; direct-global cursor/tag variants measured 196/240 and 180/240, also 0/28. The retained candidate has a 0x30-byte frame against retail's 0x20-byte frame and coalesces pointer loads/stores. A 29 October `func_0029EFD0` probe using `(p - base) >> 1` measures 252/248 and 0/28 in the default profile, versus 256/248 for the retained explicit-label form. The lower-size source is not retained because mutable `D_001B1B60` is reloaded after a helper call, so the stride alignment needed to justify the expression is not established. These are USA v1.01 measurements only.


**28 October 2026 current-master near-miss checks:** `func_0029FDF0` remains 176/240 bytes and 0/28, with direct-global variants at 196/240 and 180/240; `func_002FE8D8` replay in the actual unit is 240/248 and 0/28 (the previously reported exact size was not reproducible); `func_0034AC10` remains 256/256 and 0/28, first mismatch +0x18; `func_002E3360` remains 168/264 and 0/28; `func_002CA790` remains 280/276 and 0/28; `func_00290B48` remains 280/280 and 0/28, first mismatch +0x3C; `func_00291640` remains 292/280 and 0/28; `func_003427C0` remains 284/284 and 0/28, first mismatch +0x88; `func_0027C540` remains 252/288 and 0/28; `func_0029F840` remains 284/288 and 0/28; `func_003462A8`'s original candidate is 296/288 and 0/28 in a `-G8` probe; moving its local copy later produces 276/288 and 0/28, while the volatile-array trial is 252/288 and 0/28; `func_0028B160` remains 280/292 and 0/28; `func_002B6480` remains 308/308 and 0/28, first mismatch +0xBC; `func_002D1590` remains 296/308 and 0/28; `func_00291CA8` remains 316/312 and 0/28; `func_002CB510` remains 312/312 and 0/28, first mismatch +0x48; an explicit state/table-pointer form measures 300/312 and 0/28; `func_00350240` remains 304/312 and 0/28. These are USA v1.01 measurements.

**29 October 2026 current-master recheck:** `func_0011BEE0` (public SDK `kputchar`, USA v1.01 boot, default game profile `-O2 -G0 -ffunction-sections`) was replayed in its isolated source unit. A volatile SIO register-block view with status at `0x1000F130` and data at offset `0x50` compiles to 48/56 bytes and 0/1. It matches the materialized `$v1` data address and the volatile byte store in the `jr` delay slot; GCC instead forms the status access as `lui $v0,0x1001` plus `lw $v0,-0xED0($v0)`, shortens the wait loop, and places the return-value copy differently. This is a meaningful, hardware-backed alternative to the earlier register-pinned probe, but not a match. See `nonmatching/core/func_0011BEE0.c`.

**29 October 2026 current-master recheck:** `func_00133580` was compiled in a temporary dedicated `-G8` unit with its fallback accurately declared as `func_00124B88(int)` and called with `arg0`. Under `-O2 -G8 -ffunction-sections` it remains 180/188 bytes, 0/1; `-fno-gcse` produces byte-identical output and this compiler rejects `-fno-cse`. The helper prototype correction preserves semantics but does not change code generation. Retail's `$s0`/`$s1`/`$s2` allocation and repeated `D_001A7100` address materialization remain unresolved. No temporary source or flag changes remain.

**29 October 2026 follow-up:** a volatile-qualified `D_001A7100` hypothesis, based on its load-in-progress polling role, was measured in the same isolated `-O2 -G8 -ffunction-sections` unit. It remains 180/188 bytes and 0/1, with flag-address materialization before both calls but incorrect saved-register allocation and control flow. The asynchronous-write contract is unverified; do not retain the volatile declaration unless independent evidence establishes it.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_L07_003F7968` is C in `src/levels/07_siberius/L07_003F7968-g32.c` (`-O2 -G32 -Wa,-G32 -ffunction-sections`), placed at 1 US, 1 PAL, 1 US2 places. The measurements above are kept as history.

**Update, 29 October 2026 (pending review):** matched by the tiered-wave series; `func_00133580` is C in `src/core/00133580-g8.c` (`-O2 -G8 -ffunction-sections -mno-split-addresses -fno-gcse`), placed at 1 US, 1 PAL, 1 US2 places; `func_00290B48` is C in `src/game/00290A40.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_00291640` is C in `src/game/00290A40.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_00291CA8` is C in `src/game/00291758.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_0029EFD0` is C in `src/game/0029DE38.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_0029FDF0` is C in `src/game/0029DE38-textures-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_002B6480` is C in `src/game/002B6120.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US places (PAL and US2 catalogues have no function of this name); `func_002CA790` is C in `src/game/002CA790.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US places (PAL and US2 catalogues have no function of this name); `func_002CB510` is C in `src/game/002CB510.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_002FE8D8` is C in `src/game/002FC8D0.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places; `func_003427C0` is C in `src/game/003427B0-fade.c` (`-O2 -G0 -ffunction-sections -frac2-hazard-labels`), placed at 28 US, 28 PAL, 28 US2 places; `func_003462A8` is C in `src/game/00345358-descriptor-g8.c` (`-O2 -G8 -ffunction-sections`), placed at 28 US places (PAL and US2 catalogues have no function of this name); `func_0034AC10` is C in `src/game/00345358.c` (`-O2 -G0 -ffunction-sections`), placed at 28 US, 28 PAL, 28 US2 places. The measurements above are kept as history.

## F4, the lock-on tether: closing a slot rotation

**1 November 2026, USA v1.01.** `func_0030A348` and its 26 level copies (5,868 bytes each) are exact at `-O2 -G8 -g -frac2-qcopy -frac2-qcopy-barrier -frac2-hazard-labels`. Every instruction but the spill slots had matched for a while. What closed the slots:

- The count that sets gcse's buckets is `max_cuid`, the number of real insns in the `-ds` dump: `grep -cE '^\((insn|jump_insn|call_insn)(/[a-z]+)? ' x.i.cse`. Buckets are `max_cuid / 2 | 1`. This is exact where the bucket count moves in steps of two.
- Sweep buckets widely before aiming. Forcing them here showed six good windows: 617-625, 647-653, 677-685, 711-719, 747-757, 789-799. A frame address `14030 + K` wraps at multiples of the count, so windows repeat at about `14100 / n`.
- Spellings that add insns at gcse and leave the bytes alone. A `short` local between an int value and a narrow store (`short fade = f(); D[k] = fade;`) is +2: the two sign-extension shifts die at combine. Not through an unsigned load, where `lhu` turns into `lh`. A named pointer copying a register into an asm operand (`float *from = st->a; qcopy(x, from);`) is +1: cse doesn't replace asm operands, so the copy reaches gcse. Sharing one such pointer between two `qcopy`s is +1 only and costs 36 rows.
- Spellings that do nothing: local pointers for call arguments, inline helpers returning a value, inline wrappers around `qcopy`. A macro `qcopy` loses 72 bytes, so the helper really is an inline.
- A swap of two slots is a tie, not a count. `(plus k 1)` hashes on the pseudo number, `14029 + regno + 1`, and sat in bucket 649, ahead of `&vA0` in 650. One more function-scope local declared before `k` moved it. List `PRE: ... reaching reg is N` against the `-dG` expression table for two variants and diff them: that names the expression that moved.
- `if (i == 9 || i == 0x13)` is byte-identical to two identical arms, so the repeated arm was never needed. `if (sm == 0.0f) continue;` replaces a `goto` with the same bytes.
- `sa2 = 0.0f` is dead on every path, but retail keeps it, because its zero register is reused by the `sm` test (`mtc1 $zero, $f21`, then `c.eq.s $f0, $f21`). Removing it costs 68 rows.
- A block-local `cm` keeps the `&v80` copy's life at 9, so `55 * 9 >= 451` and it moves in loop pass 1, which is retail's preheader order at 0x7AC. Up to 44 more real loop insns stay safe.
- `func_002C2210` takes `(pos, ticks, a, b, colour, 0, spin, dir, 1, 0.0f)`, as RAC1's spawn call and the matched `L06_00458138.c`.

The steering locals are live, and are commented in the source. They are spellings that reach the right count, not proof of what the original said.
## Families F4 and F7, and what the beam chain loop showed

**1 November 2026, USA v1.01.** Opcode lists confirm two untried families: F4 is nine functions of 5,868 bytes (L03, L07, L10, L11, L14, L15, L18, L22, L30) and F7 is five of 1,540 bytes (L06, L10, L15, L18, L22). All 14 are compiled code, no COP2. One match in each family ports to its siblings: about 60 KB. `func_0030CCD0` carries F4's chain loop in small form, so close it first.

Spellings measured on `func_0030CCD0` (`-O2 -G8 -ffunction-sections -g -frac2-qcopy`), which took it from 442 raw rows to 25:

- Index the chain arrays directly (`D[i - 1]`, `D[i]`, `D[i + 20]`, `D2[i]`) and let strength reduction build the pointers. Explicit pointers were worse in every combination.
- A `mov.s` copy of `(float)i` beside a reused register is gcse's reaching copy: write `(float)i` at each later use instead of one local.
- `sll` of the index stored to a slot while the register stays in use is the same thing for `i * 4`: an early `i * 4` local plus a later `D[i]`.
- A reload-rebuilt constant or address inside a loop (`addiu v1, 1`, `lui`/`addiu` beside the use) means loop.c hoisted it and global-alloc gave it no register. Check `Register N, refs, live_length` in `-dg`; ordering is `floor_log2(refs) * refs / live_length`.
- Spill slots 0x78 and 0x7C follow the bucket count; the other rows did not move under `RAC_S`, so they need spellings.

`func_L06_00455BC0` stops on the third point: its flag has 3 refs across 118 insns, the hoisted `1` 3 across 86. An added set gives 4 refs, which fixes the frame and the loop's registers at three extra instructions; two rows in cases 3 and 4 stay open (the draft header lists them). Not tried yet: a real 4th reference that later passes remove.

**1 November 2026, later: `func_0030A348` (boot's F4 member) at 5860 of 5868 bytes, 173 rows off with relocations masked.** F4 is 27 functions, 158,436 bytes. The chain loop, its allocation (`$s1` near, `$s2` i, `$s3` the `&s2B0` copy, `$s4` far, `$s7` `&v80`, `$fp` `&hit1`) and every spill slot now equal retail. What closed it, in order of effect:

- RAC1's counterpart is `update_electric_water_bolt_effect` (rac1-decomp `src/overlays/shared/electric_water.c`). Its shape is the guide. The chain is a two-dimensional array of a union vector, `P2[2][20]`, read `P2[0][i].f[2]` and `P2[1][i]`. That alone gives retail's giv order (`func_0030CCD0` too) with no pointer locals, and `0x148($s1)` for the far z. `float[][4]` with `[2]` leaves the z address in its own giv.
- One float variable holds the amplitude, the radius and the near-arm value (`func_0030CCD0`'s f20/f21 swap closed the same way).
- `func_002A8E20(ht, &hit1)` written once per arm: jump2 cross-jumps them, and the two extra in-loop refs lift `&hit1` above `best` (13 refs, 0.0565 against 0.0527). That was the whole `$fp` question of the earlier runs.
- `&D_002295D0[k].v[1]`, not a separate `D_002295E0` symbol: the addend is then the hoisted register and `r5900_madd_profitable_p` accepts it (it refuses an addend set in the same block).
- loop.c's move test is `T * savings * life >= insns`, T about 48 on these targets (61 in older notes is wrong: `func_0030CCD0` fails at 198 insns with savings 2, life 2). Non-line notes count towards life, so a block end between a movable's set and its last use adds one. Block-scoped `bearing` and `radial` around the near-arm `qcopy` (life 8) hoist the `&vA0` copy, slot 0x370; `{ char *ax = D_00189E20.ent + 0xE0; ...}` hoists the base so it is rematerialised at both uses.
- `for (t = D_001EE960[0]; t != 0; t = D_001EE960[++sn])`: the pre-increment gives the lo_sum life enough to hoist and form the pointer giv, slot 0x3AC, with the head read and the giv init on the right sides of the branch.
- `k` must be pseudo 161 or above so `k + 1` lands after `&vA0` in the PRE slots: more function-level scalars before `int k`.
- A load's delay-slot `nop` before `jal func_00282948` is `la` (one RTL insn of length 2, not eligible) plus a store reading `$a0`.

Still open: reload's spill registers run one step behind retail from `0x1F4` to about `0x690` and again from `0xF44`. The first wrong choice is the `high` of `D_00189E20` in the scan preheader: retail takes `$a0`, here `$v1`, because sched1 puts the list `lo_sum` (it kills its `high`, smaller reg weight) ahead of `s2`'s `lo_sum`. Fixing that is likely worth about 100 rows. Others: the `&vA0` copy is not inherited for the `a2` of `func_00282CC0` (`0xBD4`); `sw $s7,0x36C` order in the chain preheader; `addu` operand order and `D_001B23E8[k]` block order in the k loop; `tsize` argument order in the last spark.

`func_0030CCD0`: 1888/1888, 12 rows with the two-dimensional array, one float variable and a `zero` local set after the `func_00282D08` call (the 0.0 then hoists in loop pass 1, in scan order, as retail). Left: slots 0x78/0x7C (bucket count), `s2` against `s5` in the preheader (issue parity: `1311` must issue with `300`), `mov.s $f12` order in the last call.

**1 November 2026, later: `func_0030A348` at 5868/5868, all rows outside spill slots 0x370 to 0x39F equal retail, at all 27 members.** Only the bucket count is left. What closed the rest, on top of closer D5's section "F4 from the level side" on `match/opus-next-d-quad`:

- `&D_00189E20.x`, not a separate `D_00189EA0`: the related address depends on the base in the preheader, so the base's `lo_sum` has priority 2 and is scheduled ahead of the list giv's `lo_sum`. Reload then rebuilds `high` while `$v1` is still live, which closes the round-robin shift from `0x1F4`.
- Reload's spill registers are a round robin that skips what is live, so a one-step shift over many rows comes from one insn order earlier. Read sched1's order at the first wrong row.
- Statement order `st->lockA = best; st->u.s.h40 = 0;`: sched2 puts the `sh` back ahead of the `sw` once reload has added the load, so retail's order is not the source's. The memory unit takes one store a cycle, so with the `sh` first the `la` passes the `sw`.
- cse's wider-mode lookup replaces a QImode constant with `(subreg:QI reg)` when any reg holds it in a wider mode, even across calls: it beats the plain reg on equal cost. `hb.kind = 5` then reads `$s1`.
- Loop.c's threshold is 61 minus 3 per move made. A block local (`{ float cm = ...; if ... }`) adds a block note, so life 9 moved the `&v80` copy in pass 1, ahead of the 0.0: 55 * 9 >= 451.
- `func_002C2210`: the prototype matched L06 and L18 callers use, in RAC1's argument order. The definition's own order is 6 rows worse.

`func_L06_00455BC0` (F7): retail allocates `missing` first (`$s5`), then `fail`, -1 and the high, leaving the hoisted 1 unallocated. So `missing` must outrank `fail` (0.0615), which at live 118 takes 4 refs. The 1 must stay a hoisted register: with `1 << n` inline, combine folds it to `srav` plus `andi`. Setting `missing = 0` at the loop's end gives the 4 refs, the frame and 33 rows, but it is not retail's shape (preheader) and `continue` skips it, so it does not land.

`func_0030CCD0` closed at 1888 bytes, 28 of 28 places, in `src/game/00308600-chain-g8.c`. Unused locals in the draft held the pseudo numbers that rotated slots 0x78/0x7C: dropping them closed the slots at the same bucket count. `func_002C2210`'s prototype with the pointer first fixed the `mov.s` order. The preheader needed one more priority-3 insn so that `r175`'s copy issues first in its cycle and `i = 1` pairs with it, since `sched2` keeps `sched1`'s tie order. A local `to = &last` set before `func_00282D30` gives the in-loop copy life 5 or more, so loop.c hoists it; the copy is tied and leaves no code.

`func_L06_00455BC0` (F7), same day: 34 raw rows. `notify = 1` after the 0x18 test lands in the `beq` delay slot through reorg's target thread, and case 4 has its own flag. Only the 4th reference for `missing` is left.
