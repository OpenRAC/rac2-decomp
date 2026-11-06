# The game's C compiler

The retail code was built with GNU EE-GCC 2.9-ee-991111b. `build.sh` rebuilds its `cpp`,
`cc1` and `as` from the public source archive:

- `patches/`: Lombyte's `sce-991111b` stack (MIT, github.com/mateuszklysz/Lombyte) and the
  project's opt-in `0057` and `0058` extensions, applied in
  the order `build.sh` lists, with two pinned versions: `0034`, which Lombyte has since
  retired, and the earlier `0020` (Lombyte c260794). `0001` is applied and then reversed: the
  retail saves registers in 8-byte slots.
- `transformers/`: the source edits measured for this game, each a script carrying its exact
  replacement text, in the order `build.sh` runs them. `u3_frame_order_on.py` and
  `u4_mtc1_helper.py` are two earlier steps the later ones build on.
  `r5900_mfc1_interlock.py` drops gas's coprocessor-load `nop` after `mfc1` on the R5900,
  which interlocks it. `tidy_condjump_fallthru.py` lets flow delete a conditional jump to the
  next block, as GCC 2.95 does. `zero_ti_store_barrier.py` adds the opt-in
  `-frac2-zero-ti-barrier` model of the inferred quadword-clear macro
  (docs/COMPILER-NOTES.md); default compilation retains ordinary scheduling.
  `ti_one_gpr.py` makes reload count a TImode value as one general register on the R5900,
  as `HARD_REGNO_NREGS` already does, so quadword reloads (a `por` zero for `sq`) take
  single spill registers as retail's do; it is unconditional (docs/COMPILER-NOTES.md).
  `reload_reg_used_guard.py` puts back the archive's test that keeps reload from inheriting
  a value into a register a pseudo of the insn holds, which patch 0047 drops; it is
  unconditional. It snapshots the non-spill exclusions before reloads add their own marks,
  so self-inheritance reaches the existing lifetime checks (docs/COMPILER-NOTES.md).
  `count_asm_words.py` counts copy words and inserted loop nops, including nops before an
  already-visited branch. It also counts an unannounced external SI load/address as its
  two emitted words, preserving the scheduler's lengths and the explicit GP/PIC/buffering
  exclusions. `pad_div_erratum_nops.py` counts a known non-PIC relaxation
  alternative once when measuring the code-label distance. Both have authored output
  controls; neither changes compiler-authored operations or selects individual functions.
  `gcse_store_kills_loads.py` gives gcse GCC 2.95.3's memory model, where every store kills
  every load, in place of this tree's alias-analysis queries; it is unconditional too.
  `trap_delay_barrier.py` ends reorg's backward delay-slot search at a division guard
  (`trap_if`), as at a jump, as retail's compiler does; it is unconditional too.
  `swap_branch_slots.py` adds the opt-in assembler option `--r5900-swap-branch-slots`: gas
  fills a reorder-mode delay slot from the previous instruction, as the GNU as that built the
  SDK libraries does (this tree's swap guard reads `&&` for `&` and never swaps). SDK units
  pass it as `-Wa,--r5900-swap-branch-slots` (docs/COMPILER-NOTES.md).
  `inline_li_d.py` makes gas build every `li.d` into a 64-bit general register inline
  (load_register's dli form) instead of pooling the values that lack a zero 16-bit chunk in
  each half in `.lit8`, as the game's own code does; this is the default. The SDK objects
  pool, so `tools/build.py` passes the opt-out `--r5900-pool-li-d` to every `sdk`-profile unit
  (docs/COMPILER-NOTES.md).
  `no_recombine_givs.py` drops strength_reduce's call to `recombine_givs` (loop.c), as the
  gcc-2.95 release branch did, so address givs stay on the giv combine_givs chose, as in
  retail; it is unconditional too.
  `gcse_unsplit_edges.py` and `keep_block_order.py` add the opt-in
  `-frac2-gcse-unsplit-edges` and `-frac2-keep-block-order`, which leave out two
  Cygnus-local pieces of this tree that GCC 2.95 does not have.

Patch `0057` adds the opt-in `-mastra-split-trunc-slot` switch. It splits the
two-word `truncdisi2` pattern after reload, before delay-slot scheduling, so
the sign-extension can occupy a return slot. The default compiler output is
unchanged. Use the switch only on a dedicated C file in `config/cflags.txt`;
`src/core/0012E8C8.c` is the measured witness.

Patch `0058` adds the opt-in `-mastra-quad-saves` switch. It widens every GPR save slot to
TImode, so the prologue and the epilogue emit `sq`/`lq` as the two measured `src/core` units
are saved, and it keeps the released descending save order for those units (the default profile
keeps the ascending order measured for the 8-byte slots). Without the switch the output is
unchanged. Use it only on a dedicated C file in `config/cflags.txt`; `src/core/00119BC8.c`,
`src/core/00115F28.c` and `src/core/00115C90.c` are the measured witnesses.

The clear model is enabled per file in `config/cflags.txt`, currently for
`src/levels/shared/L00_003B9CB8.c`. It is a measured heuristic, including for
nonzero-displacement stores, not proof of a recovered original macro. Qualify
every function in a unit before enabling it there. `-fno-rac2-zero-ti-barrier`
disables it again. `build.sh` runs `tests/test_zero_ti_store.py` against the newly
built tools: selector boundaries, isolated/shared/offset clears, calls, branches
and the default/disabled controls. The host selector tests also run in ordinary
CI; the EE output tests require the public-built compiler, never game data.

The separate `fold_zero_ti_store.py` pass folds a materialized zero only when
the store address is a register with no displacement. Offset stores keep their
`por` producer and register-source `sq`, as measured in the retained vector
helpers. This address rule applies in every scheduling profile; it does not
enable `-frac2-zero-ti-barrier` for additional files. Authored positive and
negative offset controls verify it alongside the zero-displacement controls.

`-frac2-gcse-unsplit-edges` lets gcse's block LCM run on the unsplit flow graph: this tree's
`gcse_main` first splits each critical edge that needs no new jump (Cygnus, 1998), so a
hoisted `%hi` gets a block of its own in front of a label reached only by jumps; GCC 2.95's
does not split, and its PRE inserts at the end of a block. `-frac2-keep-block-order` skips
`cygnus_merge_blocks` (Cygnus, 1998), which moves a block reached only by a jump up behind
its predecessor after the early jump passes; GCC 2.95 has no such pass. A switch whose
default is its last case keeps its `b default` and the default body last with it. Both are
inferred from retail's code, so both are off by default and enabled per file in
`config/cflags.txt`: the gcse switch for `src/levels/02_maktar_nebula/L02_003DB310-g8.c`
and `src/game/002CD620.c`, the block-order switch for `src/levels/shared/L18_00427BE0.c`,
and both for `src/levels/02_maktar_nebula/L02_003F5430-g8.c`. `build.sh` runs
`tests/test_gcse_unsplit_edges.py` and `tests/test_keep_block_order.py` against the newly
built tools: each transformer's insertion points, the case each switch changes, controls
that keep ordinary output, and the default/disabled equality.

`qcopy_pattern.py` adds `-frac2-qcopy`, enabled only for qualified files in
`config/cflags.txt`. It lowers an aligned TImode memory assignment to a grouped
`lq`/`sq` pair with register addresses and a declared `$v0` scratch. Sources
remain ordinary C assignments. The default keeps normal displacement addressing;
`-fno-rac2-qcopy` restores that default. Memory flags and alias sets are retained,
explicitly unaligned accesses take the ordinary path, and no memory barrier is
added. Scalar transfers and zero stores are not selected by this pattern.
Qualify every function in an opted-in unit; address formation alone does not
settle allocation or scheduling. The recipe requires the authored copy controls
and RTL-contract tests, including volatile accesses and integer/FPU branches.

`qcopy_barrier.py` adds `-frac2-qcopy-barrier`, which matters only together with
`-frac2-qcopy` and is enabled only for qualified files in `config/cflags.txt`. Both
schedulers then give the grouped copy the dependences, cost and unit of a volatile asm,
through the block `-frac2-zero-ti-barrier` uses for the clear, so independent instructions
stay on their side of the copy, as they do around retail's copy, most likely an inline-asm
macro. Instructions, operands, register-allocation inputs and memory flags are unchanged,
and `-fno-rac2-qcopy-barrier` disables it again. Without the switch no object of `src/`
changes; forced on in the eight `-frac2-qcopy` units, it changes none of their objects.
Twelve functions (59 places) are the measured witnesses, each a unit of its own with both
switches (docs/COMPILER-NOTES.md). It models only the schedulers' view of such an asm:
jump2, for one, still deletes a redundant register move across the copy, which a volatile
asm keeps. `tests/test_qcopy_barrier.py` covers the selector, the default/disabled
equality, and authored copies among neighbours, calls, branches and volatile accesses.

`zero_ti_por.py` adds `-frac2-zero-ti-por`, enabled only for qualified files in
`config/cflags.txt`. `rac2_fold_zero_ti_store` then leaves a quadword zero store to `0($sp)`
alone: the zero keeps its `por $rX,$zero,$zero` and the store its register source, as plain C
compiles without the fold, while a store through any other register still folds to `sq $zero`.
Retail clears 396 quadwords with `sq $zero,0(reg)` (263 functions), which the fold models, but
it also stores a `por`-materialised zero at displacement 0 183 times in 153 functions, always to
`0($sp)` and never through another register; 82 of the `sq $zero` stores are to `0($sp)` too,
so the address alone does not decide it and a unit says that its stack clears are plain C.
`-fno-rac2-zero-ti-por` disables it again. Without the switch no object of `src/` changes;
forced on everywhere, it changes only the four units whose functions retail clears `0($sp)`
with `sq $zero`. Five functions are the measured witnesses, each a unit of its own
(docs/COMPILER-NOTES.md). `tests/test_zero_ti_por.py` covers the transformer's anchors, the
default/disabled equality, and authored zero stores to the stack, through pointers, to a global
and in loops, a function with both kinds, nonzero displacements, shared and live zeros and the
function-value fold.

`hazard_labels.py` adds `-frac2-hazard-labels`, enabled only for qualified files in
`config/cflags.txt`. cc1 then writes `.set rac2_hazard_labels` at the top of its output, and
gas keeps a code label in front of the coprocessor hazard `nop` it inserts after the label
(an FPU compare before its `bc1f`/`bc1t`, an `mtc1` before a reader of the register), where
GNU `as` moves the label behind the nop. Retail has the label on the nop at all 198 such
branch targets, and SN ProDG 2.0's `Ps2EeAs` keeps it there for forward, backward, `j` and
`.word` references alike (docs/COMPILER-NOTES.md). Without the switch neither program's
output changes. `src/levels/18_damosel/L18_004308F0.c` and `src/levels/shared/L02_00411530.c`
are the measured witnesses; forcing the switch on every unit changes only the `.mdebug` of
one `-g` unit. `tests/test_hazard_labels.py` covers the fixed cases and the controls.

`no_annulled_wide_stores.py` adds `-frac2-no-annulled-wide-stores`, enabled only for qualified
files in `config/cflags.txt`. When reorg fills the delay slot of a conditional branch from the
branch's target (`fill_slots_from_thread`, `steal_delay_list_from_target` in `reorg.c`), a store
wider than 32 bits (`sd`, `sq`) no longer goes into the annulled slot of a branch-likely, and
the search of that thread stops at it. `optimize_skip`, which annuls the one instruction a branch
skips, is unchanged. In retail's compiled code the annulled slots hold 2,895 stores and none is
wider than 32 bits, while the other slots hold 547 `sq` and 497 `sd` (docs/COMPILER-NOTES.md).
Without the switch the output is unchanged, and forcing it on every other game-compiler unit
of `src/` changes no object. `src/levels/23_damosel_orbit/L23_00422668.c` (with
`-frac2-qcopy`) and `src/levels/shared/L02_0042EDD0-g8.c` (with `-frac2-zero-ti-barrier`)
are the measured witnesses. `tests/test_no_annulled_wide_stores.py` covers both paths and the
controls.

Patch `0052` also preserves the original sign-extending expansion for the isolated
64-bit sign bit and a sign bit followed by a contiguous low run of at least 32
ones. Positive contiguous runs wider than 32 bits, with zero bits at both ends,
use the existing shift-based mask expansion. This includes
`0x0FFFFFFFFFFFFFFE`: three instructions instead of seven. Runs of 32 bits or
fewer retain their previous expansion, including the 20-bit shifted mask used
by already-matched C. Regression controls exercise every shifted long-run
interval, neighboring masks, holes and four destination registers.

Some SDK objects use the zero-extending seed for the isolated sign bit instead.
Patch `0059` adds `--r5900-sign-bit=unsigned` for those measured cases;
`--r5900-sign-bit=signed` explicitly restores the default. Only the isolated
64-bit sign-bit constant changes, from `addiu -1; dsll32 31` to
`ori 0x8000; dsll32 16`. Other constants keep their previous encoding.

Patch `0061` adds the separate opt-in `--r5900-unsigned32-mask=sn` profile.
For the positive 64-bit value `0x00000000ffffffff`, SN's constant loader uses
`addiu -1; dsrl32 0`; the default GNU profile uses `lui 0xffff; dsrl32 0`.
Both produce the same value in two instructions. The option selects only that
seed when loading a 64-bit constant on the R5900. `--r5900-unsigned32-mask=gnu`
explicitly restores the unchanged default; SDK objects are not opted in.

The choice follows [RAC1's public assembler model](https://github.com/OpenRAC/rac1-decomp/blob/1d8228cc0c81da7bc2bdc3e77479ee050e0ef434/tools/ps2eeas_dli.py)
and an independent authored SN assembly control. It does not rewrite compiler
instructions or depend on a function/address. The `test_dli_masks.py` controls
cover three spellings of the positive mask, its neighbors, negative and wider
masks, five registers plus a zero-register selector control, unchanged
word/address macros, option rejection and
composition with the isolated sign-bit profile. Use standard per-file
`-Wa,--r5900-unsigned32-mask=sn` flags and qualify each complete unit and release.

Pass assembler options per file through standard `-Wa,` syntax in
`config/cflags.txt`, for example:

```text
src/core/00122B00.c	sdk -O2 -G2 -ffunction-sections -Wa,--r5900-sign-bit=unsigned
```

Both compiler profiles stop at assembly, so `tools/build.py` separates these
arguments and forwards them to the assembler explicitly. The complete flag
string and assembler binary remain part of the object-cache key. Empty options
are rejected, and the tests exercise actual argument transport for both
frontends, default/explicit profiles, invalid values and unchanged controls.

`no_null_pointer_checks.py` adds `-frac2-no-null-pointer-checks`: the two Cygnus
`delete_null_pointer_checks` calls in rest_of_compilation are skipped, as GCC 2.95 has neither.
With `-frac2-keep-block-order` no block count runs before cse, so a call that ends a block whose
label cse later threads away leaves no `(use (const_int 0))` behind to move through the merged
block (func_L20_002CD928 case 0x7C). It is off by default, enabled per unit in
`config/cflags.txt`, and `-fno-rac2-no-null-pointer-checks` disables it;
`tests/test_no_null_pointer_checks.py` covers the anchors, the default/disabled equality and an
authored check the pass deletes.

`narrow_saves_below.py` adds `-frac2-narrow-saves-below`: with `-mastra-quad-saves`, the GPR
saves at the slot's full width take the upper slots and the saves narrowed by the stock
`register_precision` attribute the lower ones, so `sd $ra` sits below `sq $s0`
(func_L01_00324550, func_L08_00389B68). A frame with one save width is unchanged, and without
`-mastra-quad-saves` the option does nothing. It is off by default, enabled per unit in
`config/cflags.txt`, and `-fno-rac2-narrow-saves-below` disables it;
`tests/test_narrow_saves_below.py` covers the anchors, the default/disabled equality, a
mixed-width frame and a one-width control.

`keep_block_zero_copy.py` adds `-frac2-keep-block-zero-copy`: cse keeps a copy from one
pseudo to another whose value is known to be 0 when the source is set earlier in the same
basic block, instead of folding it to `move $rd,$0` (func_002F7320: `daddu $a3,$t1,$zero`).
A zero learnt in an earlier block is folded as before. It is off by default, enabled per unit
in `config/cflags.txt`, and `-fno-rac2-keep-block-zero-copy` disables it;
`tests/test_keep_block_zero_copy.py` covers the anchors, the default/disabled equality, the
kept copy and a control across a call.

`build.sh` stops unless `mips.c`, `mips.h`, `mips.md`, `toplev.c`, `flags.h`,
`haifa-sched.c`, `gcse.c`, `flow.c`, `reorg.c`, `reload1.c`, `loop.c`, `cse.c` and `tc-mips.c` hash as it
lists. The binaries' own hashes depend on the build host and path, so check a compiler by its
output: `tools/build.py` compiles every matched function to the retail bytes.
