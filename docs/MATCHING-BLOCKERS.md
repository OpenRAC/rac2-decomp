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

These summaries do not award additional matching credit or replace the build. Check current
source before relying on any older count, profile or pending-PR label in the imported notes.

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

The two independent witnesses remain nonmatching: `func_L00_003A2668`
is 1204/1204 bytes, 0/81 present placements, first difference +0x8.
`func_L23_0041D398` remains 1432/1432, 0/1; a real phase-lifetime split
instead gives 1412 bytes and a 0xC0 frame. Useful alternatives stay private.
These negative controls do not establish a general allocator failure or
justify repeating the same attempts without new evidence.

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

**24 October 2026, shared record lookup:** `func_002F6510` remains a
244/248-byte near miss under game `-O2 -G8 -ffunction-sections`, with 0/28
placements in each release. Six checker invocations (no scratch compiles)
measured 232-byte raw-index, 264-byte duplicated-call and 244-byte shared-call
forms. A named-table computed-goto probe did not preserve retail arm offsets
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

## 7. Annulled integer branch delay slots

Historical mismatches involved bnel/beql with a taken-path slot where retail used a normal branch and fall-through work, often one word different. The wave 9 correction counted 342 then-matched functions containing a likely branch: the compiler does emit them from ordinary C. That count is historical, not today's corpus size.

Hoisting genuinely shared work before the condition changed slot selection in some bodies. It is a measured source lever, not a guarantee that every likely branch can be rewritten to a normal one. Five workers had previously discarded 9, 10, 11, 14 and 15 targets using that signature alone; those exclusions were not justified without exact decoding/profile checks.

Integer BEQL/BNEL execute the slot on taken paths and annul it on non-taken paths. The earlier unconditional/inverted-slot claim is withdrawn. This was checked against the [official PCSX2 R5900 interpreter](https://github.com/PCSX2/pcsx2/blob/0f71e668b8adc950db7de1b1b15c2f5080c102e9/pcsx2/Interpreter.cpp#L387-L410), not a new hardware experiment. Do not generalize this statement to a differently decoded instruction.

<a id="blocker-08"></a>

## 8. Single-register `%hi`/`%lo` addresses

**Signature:** retail may use base == destination, a separate address register, a `$at` macro, or `$gp`. Declaration type/size, unit flags, cc1 output and assembler macro context all participate. Earlier waves inferred contradictory universal rules from different units; those universal rules are withdrawn.

**Measured levers:** scalar/array forms, complete/incomplete array size, sda/nosda, a -g8 sibling, and per-file -mno-split-addresses. Check every existing C function using an affected declaration: historically one attribute change turned an existing 2/2 into 0/2 and was reverted.

The historical sample is retained: 47 of 240 notes mentioned gp/sda/G8; one 23-target survey used 11 plain-G0, six G0+sda and six G8 units. Those counts are not a selection algorithm. Inspect relocations and retail accesses. GP is 0x001AEFF0 in boot and levels; a small-data declaration needs a known eligible size.

**Current witnesses:** func_L05_0030C930, formerly listed as unresolved, is C, as are func_L05_00444D60, func_L00_00427290 and func_L00_002E73E0. PR #246's func_L20_00444138 passes 1/1 in its dedicated G8/mno-split-addresses unit with separate sda/nosda declarations for one measured bound.

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
results remain near misses, with loop lifetimes and saved-register allocation
still different. The allocator diagnostic reproduces the ordinary compiled
objects; it measures interference and priorities, not semantic correctness.

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

The wave 8 correction correctly identified 0x700014A9 as por, not mtsa or an undecodable word. The recorded mtsa zero encoding was 0x00000029. A por-plus-sq zero mismatch remains separate from a decoder error (section 17).

lq/sq are not VU0/COP2 and can be emitted from a TImode C assignment. Four targets were nearly misclassified because the reader used a generic instruction category. Use `rabbitizer.Instruction(word, address, rabbitizer.InstrCategory.R5900).disassemble()`; not every generic INVALID word is lq/sq, so decode each exact word. The reviewed qcopy/qzero helpers are also permitted under the updated source-method rule; none of these instructions alone proves a complete match.

`func_L00_00391398` provides a further plain-C control: its 324-byte body, including
`por` plus `sq` zero initialization, passed `tools/check.py` at 27/27 placements in
both USA releases (the name is absent from PAL). The previous MMI-impossible screen
was incorrect. A union with TImode and float-array members keeps the scalar field
at a fixed stack offset; casting a TImode local to `float *` instead retained a
pointer across calls and added one saved register (340 bytes). Profile: default
`-O2 -G0 -ffunction-sections`. The combined tree passes all 84 strict program builds.

The retained [func_L11_0046BD18](../nonmatching/levels/func_L11_0046BD18.c)
provides a separate integer-address control: decode its multiply-add as R5900
`madd`, and its quadword transfers as ordinary TI assignments. The reconstruction
compiles those instruction families but remains 1060/1024 bytes, 0/2 placements
in each release. This supersedes the historical MMI-only screen without claiming
a whole-body match; frame and address-expression lifetimes remain open.

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

<a id="blocker-20"></a>

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

<a id="blocker-23"></a>

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

**Consequence:** retain unresolved attempts and their bounded stopping reasons. Do not label the whole category unexpressible or add volatile/artificial uses solely to preserve an operation.

<a id="blocker-27"></a>

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

**23 October 2026, retained near miss:** `func_0028E2A8` has a 332-byte plain-C `-G8` draft against 348 retail bytes, 0/28 in USA v1.01. Ten target runs included one checker environment failure and an incomplete-array compile failure. A separate 344-byte section-annotated diagnostic matched 0/28 in USA v1.01, PAL, and USA v2.00. Recomputing the second record lookup and moving to a G8 sibling improved the draft, but register allocation, branch layout, and external-address materialization remain different. The marker is restored; reopen with verified global storage and argument-layout evidence.

**23 October 2026, retained near miss:** `func_0028B160` uses the default game -G0 profile in `src/game/00288D88.c`; its 292-byte body has 28 placements in each release. Six plain-C candidates were measured, and the best three reached 280 bytes, 0/28 in USA v1.01, PAL, and USA v2.00. Since the size differed, the checker did not perform relocation-adjusted byte comparisons. The retained draft models the count loop, renderer call, and scaled offset update. Its object diff shows different register allocation and layout; the proposed cause is unverified. Reopen with `.lreg` lifetime evidence or a new source-shape hypothesis. The marker is restored and no full build was run.

**23 October 2026, retained near miss:** `func_00280670` is 160 bytes with 28 placements in each release. Ten plain-C forms reached 152 bytes and 0/28 in USA v1.01, PAL, and USA v2.00. The retained record-based counted-threshold loop still differs in register allocation and loop setup. Reopen with verified record-layout or argument-liveness evidence; the marker is restored and no full build was run.

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

## 43. Block ordering: distinguish source structure from unavailable flags

Historically seven loop forms in two five-member families retained a different block order from retail, changing branch polarity and delay slots. The proposed freorder-blocks/fno-reorder-blocks remedy was a hypothesis, not an available flag or a measured fix.

The qualified cc1 rejects **both** `-freorder-blocks` and `-fno-reorder-blocks` as Invalid option(exit 33). Do not add them to cflags.txt. `-mastra-keep-frame-order` is accepted, but controls frame-related scheduling rather than arbitrary block ordering.

Meaningful return/break arrangements have matched some loops. PR #238's tidy_condjump_fallthru.py removes a jump to the next block early enough for flow to remove its dead input in six documented rotated id-list walks. Neither remedy establishes a solution for every block-order mismatch.

<a id="blocker-44"></a>

## 44. Relocated instructions are validated in a separate pass

Placement.derive initially skips raw comparison of words carrying relocations because their address fields are not linked. It then validates unaffected opcode/register fields of HI16, LO16 and GPREL16, opcode bits of jumps, derived symbol values and relocation consistency. R_MIPS_32 is a full-word address relocation, not an instruction relocation.

A relocated register mismatch is therefore **not invisible**. The old claim that check.py skips instruction validation is withdrawn. The first reported mismatch is not an exhaustive list of all differences.

The displayed object column is unrelocated, so zero call/address addends can look different without being wrong. Use explicit size/instruction/relocation/binding rejection reasons and the full linked build. A quick per-function pass does not validate dependent sections or the whole program.

<a id="blocker-45"></a>

## 45. Source shapes that move a body

Historical examples, to requalify in the final unit:

- Removing a seemingly unused duplicate extern changed 180 to 188 bytes because the remaining declaration followed the call and implicit-int/default promotions altered floating arguments. Preserve correct visible prototypes.
- Mixed integer/float parameter order changed setup order even when final argument registers agreed. Determine the real ABI rather than choosing a false signature for scheduling.
- Else-if versus independent ifs changed float-constant rematerialisation; signedness changed immediate/branch forms. These were bounded examples, not guaranteed transformations.
- Stack-local ordering/layout examples remain in L00_002B91C0.c and L09_003F9468.c. A measured aligned struct containing TI128 plus a byte array expressed a frame that separate locals did not reproduce.
- func_L16_00404A60(988 bytes) matched after 24 store permutations; the winning order was neither retail order nor simple reversal. Do not infer one universal scheduler permutation.
- **Encoding correction:**0x700014A9 is por v0,zero,zero, not pcpyld. TI zero materialisation is reachable in appropriate cases; retention/folding depends on current source/profile(section 17). The word alone neither proves handwritten assembly nor proves a complete C match.

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
* **The frame's register set follows from the address form.** `func_L05_004268E8`
  and its three colour twins come out with nine callee-saved registers against the
  retail's eight, because the retail has no register at all for the base of the int
  array: it re-materialises it in the loop (`addiu $v1,$s4,0x20`) and adds the offset
  to it, while a base held in a local lets the compiler fold the offset into the store.
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
`func_L00_002DA390`, `func_0031E6D8`, `func_0031D350`, `func_00326CA8`,
`func_L00_003D1B48`, `func_002B80B8`, `func_L00_0037B408`, `func_L00_0037B4B8`,
`func_L00_0037B5C0`, `func_00280660`. They are the same shape: a four- to
sixteen-byte extent that reads a register it never sets, or branches outside its own
bytes, or is the linker's padding between two bodies. Each is deposited with its
evidence.


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

The historical full core scan reported 60 fill-starting entries rather than the earlier 26. Many simple cases were subsequently removed; mixed examples such as func_001158F4, func_0011A7F8, func_0011E920, func_0011ED28, func_0011F364, func_0011FB8C, func_00120354, func_00125D94, func_0012646C, func_0012F998 and func_00130A8C need their own boundary evidence. The old table and prose disagreed on func_0011F364: 28-byte prefix/608-byte body at 11F380 versus 4/632 at 11F368. Neither historical figure is adopted here as a verified correction. Preserve the real code until the discrepancy is resolved.

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

#### The five catalogue extents have evidence of residual code

| Row | Size | Placements checked | Preceding boot return |
| --- | ---: | ---: | --- |
| `func_00289018` | 4 | 1 | `0x0028900C` |
| `func_002A77C0` | 28 | 1 | `0x002A77AC` |
| `func_002FED78` | 12 | 1 | `0x002FED68` |
| `func_002FF0B0` | 36 | 1 | `0x002FF0A4` |
| `func_002FDB40` | 148 | 23 (boot + 22 levels) | `0x002FDB30` |

Every checked placement follows a preceding `jr $ra` and its delay slot. A scan of the corresponding program's text found no direct branch/jump target inside any of these extents; a scan of the loaded non-code sections found no aligned literal pointer into them. The mixed arithmetic/store fragments are therefore supported as catalogue residues by their surrounding code and reference audit, not merely by their lack of `jr $ra` or by FPU nops.

**Decision:** keep these as catalogue-correction cases, not C-matching targets or handwritten-function credit. #243 retains the observations but does not change the catalogue. A separate generator change should verify every affected placement, preserve the original image bytes, and include regression tests before dropping these rows. This static audit does not establish the absence of computed indirect targets, so do not generalize it into an opcode-only deletion rule.

### game/00308600 follow-up — PR #287 merged; original near miss retained

- `func_00308600` remains a near miss. The old draft incorrectly used the return of `func_002A0488` for the +0x30 byte, and wrote +0xBC after `func_002A0F48`; retail writes both before their calls. The corrected draft remains in `nonmatching`. With current master compiler sources, `-frac2-qcopy -frac2-qcopy-barrier -fno-gcse` produces 356/360 bytes, 0/28 USA v1.01 places. The copy pairs, saved f20/f21 and 0x50 frame agree, but the initial stores merge two retail 255 materializations and GPR allocation differs. Typed fields, a short argument and scheduling/CSE controls did not resolve it; the short argument's 360-byte result contains unwanted sign extension. Reopen with independent field-type or constant-lifetime evidence, rather than repeating those variants.
- `func_0030E700`, in the same source unit, is now a merged 424-byte plain-C implementation: 28/28 USA v1.01 places pass `tools/check.py` with default flags. The first candidate differed only around `func_002ABBB8` argument setup. Its integer/float interleaving already used in `src/levels/04_barlow/L04_00422A00-g8.c` resolves those differences without a compiler change. USA v1.01 `tools/build.py all --strict --jobs 8`: all 28 programs OK, no C fallback; 139 unit tests, repository checks under Ubuntu, progress --check and diff checks pass. Merged in [PR #287](https://github.com/OpenRAC/rac2-gc-decomp/pull/287), commit `76254265`. The qualified USA v2.00 input also passes all 28 target places and all 28 full strict builds, with zero C fallback. Both PR CI checks passed. This adds one distinct 424-byte C function, with 28 placements per applicable USA release; no report was regenerated. No PAL implementation or new matching credit is claimed.

### Findings contributed by bigmak94

Source: [original contributor comment](https://github.com/OpenRAC/rac2-gc-decomp/issues/157#issuecomment-6321947233). The measurements below are
attributed for provenance, not exclusive ownership.

| Function / family | Status | Evidence and next action |
| --- | --- | --- |
| **Vector copy as a scheduling barrier:** `func_002B5E48`, `func_002EE988`, `func_L23_00418650`, `func_L23_003C01F8`, `func_L23_00418DC0`, `func_L23_004256F0`, `func_L02_003DB158`, `func_L02_003D47B0`, `func_L26_003D4930`, `func_L12_00413CE0` (close: `func_002B50E0`, `func_L23_0041D0A0`); from today's first attempts at level 2, also `func_L02_00401BF8`, `func_L02_003F1A88`, `func_L02_003EE938`, `func_L02_003E8CE8` | Merged, #275 | Each is retail's size with `-frac2-qcopy` in a unit of its own. Each is exact when the copy is the volatile asm `lq $2,0(%1) ; sq $2,0(%0)`, in scratch copies only. The profile's grouped pair lets independent instructions cross it. About 50 single flags and many source orders, including `-frac2-zero-ti-barrier`, do not. #275 (merged) adds the opt-in `-frac2-qcopy-barrier`, the clear's block in `sched_analyze_insn` applied to the qcopy insn. Twelve witnesses landed with it. Twenty-three more near misses are exact with it as their records stand, in #283; two more follow. `func_002B50E0` is still 3 words off, a sched1 tie on argument moves. |
| **The barrier copy's link costs:** `func_L02_003F1A88` | Qualified with reviewed helper | The TI/barrier profile was five words off because its producer-link latency differed from the real macro dependency graph. The approved `qcopy` helper closes the 228-byte function under default G0, 1/1 in each release. No compiler link-cost patch is needed. Preserve the original distinction: modeling only part of an inline helper's optimizer effects need not reproduce the actual helper. |
| **A TImode zero reloaded as a register pair:** `func_L02_004388A0` | Open, measured | 5 words off with the barrier: its 16-byte zero clear is reloaded as a group of two general registers, though the R5900 holds it in one. That makes `$v1` a spill register, so a hoisted sentinel -1 left unassigned gets `$v1` where retail has `$v0`. Without the clear (diagnostic only), every -1 is in `$v0`. |
| **A register saved and never used:** `func_L02_003FF6E8` | Open, measured | Retail saves `$s2` and never uses it; 21 retail game functions do so, and none of them is C. A plain C spelling reproduces the frame and register roles but keeps the value in `$s2`, 700 bytes against 696. |
| **Clear through a register address at a nonzero offset:** `func_002B5678` | Open | Retail has `addiu $v0,$s1,0x60 ; sq $zero,0($v0)`, the clear macro's register operand. After #258, C gives `por` + `sq $v0,0x60($s1)`. **Next:** a profile that materializes the address of a displaced const-0 TImode store. |
| **A `por` clear at a zero displacement:** `func_L02_003DB200`, `func_L02_00423520`, `func_L23_00422798`, and with the copy barrier `func_L02_003DBA70`, `func_L23_00429DC8` | Proposed: PR #281 | These functions clear a stack vector with `por $v0,$zero,$zero` + `sq $v0,0($sp)`. Since #258, the fold still makes that `sq $zero,0($sp)`, because the address is register-only.<br><br>A finer retail count (one place per catalogue row, boot game code from 0x26EA00, a store counted when every path into it starts from the `por`) finds 183 `por`-fed stores at a zero displacement, in 153 functions. Every one of them is to `0($sp)`; none goes through another register. Against that, 396 `sq $zero,0(reg)` stores in 263 functions, of which 82 (58 functions) are also to `0($sp)`.<br><br>PR #281 adds the opt-in `-frac2-zero-ti-por`: with it, the fold leaves a store to `0($sp)` alone, and stores through any other register still fold. It is neutral by default (806 of 806 units). Forced on everywhere, it changes exactly the 4 units whose matched functions clear `0($sp)` with `sq $zero`. The five functions above are exact with it. `func_L23_003C16D8` stays out: three of its clears go through a computed stack address. |
| **A cse block boundary that leaves no instruction:** `func_L02_003D26B0`; the five 632-byte twins `func_L11_00436D08`, `func_L11_00449C70`, `func_L11_0044C850`, `func_L11_004530E0`, `func_L11_004566C0`; `func_L02_003F1BA8`, `func_L02_0040BBD8`; `func_L07_00378898` | Open | Retail keeps a gcse (PRE) copy, for example `daddu $s5,$s4,$zero` of `e + 0x10`, that this cc1 makes only when cse1 and cse2 both see a label at that spot. Adding `\|\| x == 7 \|\| y == 9` to the test reproduces it, with extra code. An empty `do { } while (0)` reproduces it exactly but is rejected (#257, fc4a6c6). For `func_L07_00378898`, `-fno-cse-follow-jumps -fno-cse-skip-blocks` reproduces the block, as a probe only. **Next:** the original's construct at that spot, or a measured cse rule. |
| **A non-empty `do { ... } while (0)` as a block barrier:** `func_L02_003FB000` (288 bytes) and `func_0033A520` (360 bytes, 28 places) | Question for maintainers | `func_L02_003FB000` is exact with its last store wrapped in `do { ... } while (0);`. The loop notes give the shared `jr $ra` retail's alignment `nop`, which cc1 adds only after a loop. `func_0033A520` needs a block boundary after its rounding of `D_001B23A4 * 300`; the wrapper gets that block right, and six allocation words remain.<br><br>Two merged functions use the same wrapper as a documented scheduling barrier: `func_00124818` and `func_L23_0041C8C0` (ours). The repository check rejects only the empty form. Since AGENTS.md rules out artificial barriers, we have not landed more. **Question:** is a non-empty wrapper acceptable as a macro-shaped statement, or should the two precedents be revisited? |
| **Jump tables the build cannot place:** `func_L06_003FDA08`, `func_L13_00422CB8`, `func_L03_003C4578`, `func_L02_003F9AF0`, `func_L02_003F9B70`, `func_L02_003FE1B0` | Solved, PR pending | A computed goto through retail's own table, in the form of `func_00310A40`, matches all six. The three level 2 records' in-order switches were wrong: retail's tables map the values to the bodies in another order. Decode the table before trusting a record's `switch`. |
| **Labels behind hazard nops:** `func_L18_004308F0`, `func_L02_00411530` | Merged, #264 | Opt-in `-frac2-hazard-labels`. 198 retail branch targets after a compare or `mtc1` sit on the nop, and SN's `Ps2EeAs` agrees. Forced on everywhere it is neutral (778 of 779, one `.mdebug`). |
| **gcse critical-edge split, Cygnus block merge:** `func_002CD720`, `func_L02_003E79F8`, `func_L02_003FCCA0`, `func_L18_004283F0` | Merged, #261 | Opt-in `-frac2-gcse-unsplit-edges` and `-frac2-keep-block-order`. `func_L23_0041B9F0` reaches retail's size with the gcse switch and still stops at the copy order. |
| **PRE keeps a load across a store to another offset:** `func_L02_003EEC58` (and `func_L23_0041C0E8`) | Open | Retail reloads the index after a store to a disjoint offset of the same base. A historical `volatile` probe reproduces it. Current RAC1 also uses volatile fields; this is not a blanket-forbidden source method (see COMPILER-NOTES.md). **Next:** establish whether a faithful field qualifier describes the target's actual accesses before considering an opt-in PRE rule. The old probe alone does not qualify either solution. |
| **Wide store in an annulled slot:** `func_L02_0042EDD0`, `func_L23_00422668`, `func_L02_003E7370` | Merged, #279 | Retail's game code has no `sd` or `sq` among the 2,895 stores in annulled slots. Ordinary slots hold 547 `sq` and 497 `sd`, and annulled slots do take wide loads.<br><br>PR #279 adds the opt-in `-frac2-no-annulled-wide-stores` (reorg's thread and steal paths; `optimize_skip` is kept). It is neutral by default (796 of 796 units); forced on in every game-compiler unit, it changes only the two witnesses. `func_L02_0042EDD0` (2 places, with the clear barrier) and `func_L23_00422668` (with `-frac2-qcopy`) are exact with it. `func_L02_003E7370` also needs the clear barrier in a call slot, and the barrier then also catches a plain C clear. |
| **Catalogue rows that are not functions:** `func_00288D40` (20 bytes), `func_00290718` (4), `func_00298D10` (20), `func_002B4068` (36), `func_002B49A0` (12), `func_002ED570` (4), `func_002FC460`, `func_002FC510`, `func_002FC618`, `func_002FC868` (4 each), `func_0033B538` (4) | Evidence, left as markers | Each row starts right after a complete function, its `jr $ra` and the delay slot, and ends at the next function. No branch or jump in any catalogued boot function reaches it (scan of every boot row). Their words, like `sw $v0,-0x3D14($gp)` or `addiu $sp,$sp,0x10 ; nop`, read as unreachable tails.<br><br>Three level rows fit the same pattern (DrLegitamate, 28 October 2026, USA v1.01): `func_L09_003FB780` (4 bytes; levels 09, 22, 23: `daddu $v0,$zero,$zero`), `func_L25_00373ED0` (4: `addiu $v0,$v0,0`) and `func_L25_00373F08` (4: `sw $a0,0x48($v0)`). Each of the five placements follows a `jr $ra`, its delay slot and padding, and is followed by a `nop` and the next function. No branch or jump label in its program's disassembly reaches it, and no aligned word in the level's `text.bin`, `data.bin`, `lit.bin` or vtables equals its address. Left as markers. **Next:** a `tools/levels.py` rule for unreachable inter-function words, if maintainers want one. |
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
- `func_L11_003F2A30` dispatches through a compiler jump table of 11 entries based at
  D_L11_002BAA10 (`lw $a0,0($v1); jr $a0`, cases reached from `a0[0x42]`). wslcmp
  checks only the function bytes, so a `switch` whose case *order* differs can look
  close; `tools/build.py`'s jump-table qualification is the real check.
- `func_L18_00428138` repeats its last two guards (`D_L18_001AFBB0 != 0` and
  `D_L18_00189E20+0x2294 == 0x6F`) inside each case of its kind switch after checking
  them before the switch. The duplication is in retail, so the retained C has to spell
  it twice; merging it changes the branch layout.
