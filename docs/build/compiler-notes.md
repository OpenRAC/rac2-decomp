# Compiler and assembler compatibility notes

## Source methods shared with RAC1

As of 25 October 2026, reviewed shared EE transfer helpers (`qcopy`, `qcopy_nc`,
`qzero`, `qzero_nc` in `include/common.h`) and original public runtime-library target
primitives are permitted, following RAC1. Older plain-C-only observations remain
measurements of those attempts, not a current ban on these routes. Quadword
addresses must be 16-byte aligned. `qcopy` and `qzero` declare memory clobbers;
`qcopy_nc` follows RAC1's non-clobbering variant and requires an independent
check of surrounding memory dependencies. `qzero_nc` is RAC1's own `qzero`, which
declares no clobbers at all; the same check applies. Its pattern is a bare volatile
`ASM_OPERANDS`, at which cse flushes its whole table (cse.c, `cse_insn`), so an
address used before the clear is built again after it: func_L22_002C9898's states
0x59/0x5A rebuild the hero base with retail's only fresh `lui` there, which
neither a label nor `qzero` reproduces (a label lets gcse's PRE replace the lui). Do not replace a function with arbitrary
inline assembly, pin registers or invent barriers/interfaces. Keep upstream
provenance and licences, and recheck every affected function through the strict
linked build.

`CpuSync` and `CpuEnableInt` are shared EE hardware primitives, not compiler
patches or replacements for entire functions. The interrupt-enable primitive
is taken unchanged from [RAC1's common header at `868f8114`](https://github.com/OpenRAC/rac1-decomp/blob/868f81145904e021802a7dffa4a3addd33b7c97c/include/common.h).
The movie callbacks `func_00350190` and `func_0034FFC0` call these helpers around
their real interrupt epilogues. A local instruction helper inside a game unit
is unnecessary. Their MMIO/interrupt dependencies remain target-specific; a
matching rebuild does not establish a native implementation of those services.

Check the current RAC1 source **and its active build inputs** before rejecting a
source method or adding a compiler mechanism. At revision
[`e7e787ed`](https://github.com/OpenRAC/rac1-decomp/tree/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec),
`config/text.objects` and `Makefile.sn` include these examples:

- [`movie/vobuf.c`](https://github.com/OpenRAC/rac1-decomp/blob/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec/src/game/movie/vobuf.c#L68)
  and [`hud.c`](https://github.com/OpenRAC/rac1-decomp/blob/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec/src/game/hud.c#L469)
  use volatile memory fields to retain reloads. That route is not available here:
  `volatile` describes memory, so it is for hardware registers and memory a second
  context writes, never for a measured reload in ordinary data (AGENTS.md, Rules). A
  function that only matches with it stays in `nonmatching/`.
- [`map.c`](https://github.com/OpenRAC/rac1-decomp/blob/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec/src/game/map.c#L642)
  declares the same target with different integer/FP interleavings. The EE assigns
  the two banks independently. A typed interleaving may change argument setup
  scheduling while preserving the call, provided order, count and widths within
  each bank, stack slots, return contract and side effects remain unchanged.
  This does not justify permuting arguments inside a bank or omitting an argument.

RAC2 already uses this call-shape method in `func_0030E700` and Barlow helpers.
Meaningful one-pass statement groups are also present in active RAC1 game C at
[`1d8228cc`](https://github.com/OpenRAC/rac1-decomp/tree/1d8228cc0c81da7bc2bdc3e77479ee050e0ef434):
[`taxi_and_mine_layer.c`](https://github.com/OpenRAC/rac1-decomp/blob/1d8228cc0c81da7bc2bdc3e77479ee050e0ef434/src/overlays/l03_kerwan/taxi_and_mine_layer.c#L1391)
groups an actual mission-field read, and
[`map_menu_filters.c`](https://github.com/OpenRAC/rac1-decomp/blob/1d8228cc0c81da7bc2bdc3e77479ee050e0ef434/src/overlays/shared/map_menu_filters.c#L212)
groups an actual inner loop. `tools/overlay_asm.py` discovers these overlay
sources; the public release maps include matched entries from them. Following
the current RAC1 source-practice rule, a nonempty `do { real_operation; } while (0)`
can group necessary operations here too. It may preserve compiler loop notes,
scheduling or label alignment without adding runtime instructions. Empty loops,
dummy values, false tests, extra accesses and changed call contracts remain
excluded; a group must preserve the original control flow and side effects.
The three centered-text draws (`func_002CDA20`, `func_002CF2B8`, `func_002D53F0`)
group their real formatter call, preserving its 64-bit style argument and the
text getter's signed 32-bit EE address result. `func_L02_003FB000` groups its
final 16-bit report-state store. All 84 strict release programs pass, with the
functions present in each carrying program. These are source forms, not compiler patches.

Different C declarations across units need a consistent interface or adapter for
a native ABI; an EE match alone does not establish a working native port.
Qualify the actual RAC2 source/profile and every carrying release, rather than
assuming that an example in RAC1 guarantees a match here.

An unused incoming argument also needs caller evidence. The retail
`func_002CD3C0` explicitly passes its owner pointer to `func_0034EBE0` and
`func_0034EC70`, although both helpers initialize resident state without reading
that parameter. Their definitions now accept the same ignored pointer as the
caller; the complete compiled helper object is unchanged. An unused register
left at return is a separate question and does not establish a return value.
Separating the screen-coordinate lifetime from the borrowed owner pointer
resolves the title/setup caller's allocation difference without sharing a
misleading integer local between those roles.

The rectangle setup forwarders (`func_0029B658`, `func_US2_0029C448`,
`func_PAL_0029BFF0`) also preserve four FP inputs. Retail leaves `f12` through
`f15` unchanged in the wrapper, and `func_003384C0` consumes all four before
its first call. Declare and forward those bounds explicitly, using the typed
renderer interface already used in `00336A78.c`. The three complete objects
remain identical. A native 32-bit C regression tests the context, flags, four
bounds and null-context path; its prior-source control fails on the lost FP
arguments. Ambient register contents are not a C argument-forwarding contract.
[PR #420](https://github.com/OpenRAC/rac2-decomp/pull/420) contains the source
repairs, the regression and the linked-placement checks.

`func_L02_003D0408` uses one borrowed actor-field view for all six measured
byte reads at offset `0x60`. Its volatile qualifier reproduces the complete
reload sequence, including two snapshots before the distance test on its
abandon path. The animation writer `func_002A7470` clears the same bit after
updating the sequence/frame. It landed before `volatile` was ruled out of
matched C (AGENTS.md, Rules) and needs plain C without it, or a move back to
`nonmatching/`. Both local vectors own their full 16 bytes; the xyz-only
random-vector helper does not justify inventing an initialized fourth lane.
The interleaved particle call preserves four integer and four FP arguments,
including its actual vector pointer and byte tag. The ignored-pointer hook
`func_L00_0042AB40` retains its constant-minus-one return with a consistent
incoming-owner parameter. These EE contracts still need native ABI review
before reuse in a PC port.
The [implementation and checks](https://github.com/OpenRAC/rac2-decomp/commit/96a2e817a258351edbd25db3583ab416e8fdcbcf)
pass the strict linked build in every carrying release; PAL has no identity
for this Maktar body.

### Diagnosing allocation before changing source

Run `python3 tools/regalloc.py func_XXXXXXXX --version us` on a current C
definition, or add `--json` for structured output. The command compiles the actual
source unit with its per-file profile in a unique private `build/regalloc/`
directory, then repeats with allocator/loop/scheduling dump flags. The complete
objects must be byte-identical; it never writes the production object cache or
changes source or flags. A marker alone has no C allocation to diagnose.

Reference counts, live lengths, call crossings, allocation queues, conflicts and
hard-register assignments come from the dumps. The displayed priority
`floor_log2(refs) * refs / live_length` is explicitly an inferred score. Missing
or invalid metadata stays unknown. Dumps explain one source/profile; they do
not compare retail or prove that a proposed change will match it.

Use that evidence to shorten a real pointer lifetime, compute an address where
it is used, or reconstruct a justified object/union view. Standard whole-file
options such as `-fno-force-mem`, `-fno-sched-spec`, `-fno-sched-interblock` and
`-fno-rerun-loop-opt` are diagnostic candidates for the relevant compiler pass,
not a blanket profile. Confirm acceptance and improvement, isolate incompatible
units, then recheck their existing C and all carrying releases. Stop a tied
approach instead of manufacturing references or trying equivalent permutations.

### A copy tied to a counter

When a local-alloc dump shows retail's assignment only with one extra insn tied to a value (that
value's quantity gaining the insn's references), retail may keep a copy that emits nothing:
`mips_move_1word` prints no code for a move between equal registers. By default this tree
never keeps one. cse makes the copy's source the canonical register and flow deletes the copy;
combine folds a single-use copy into its user; and regmove's copy rules run under
`-fexpensive-optimizations` even with `-fno-regmove`. The opt-in `-frac2-keep-user-copies`
([keep_user_copies.py](../../tools/compiler/transformers/keep_user_copies.py)) keeps a register
copy into a user variable: cse makes the variable canonical, and combine does not fold the copy.
Write the copy as a named local where retail needs it, typically right after the value's last
other use, so the source dies in the copy and local-alloc ties the two. In
func_PAL_L09_0040FD68 and func_PAL_L00_003B9E80 a frame counter copied after its store then
takes the first free register, and the conversion follows the 1/6 constant (L09), as in retail.
`tests/test_keep_user_copies.py` checks the default, enabled and disabled outputs.
### Function-address quantities in local-alloc (opt-in)
`-frac2-la-funcref-weight` adds one to a block-local quantity's reference count when the
quantity is set from a function's address (a SYMBOL_REF, directly or through its LO_SUM, whose
file-scope binding is a FUNCTION_DECL), before `block_alloc` sorts quantities by
`QTY_CMP_PRI` (`floor_log2(refs) * refs * size / life`). Data addresses, constants and hard
registers are unchanged. The default compiler is unchanged.
It models one retail block, case 8 of `func_002CA070` (pause and cinema state): page, c, 0x18
and the two callbacks are stored, then the init callback is called through its register.
Stock priorities are 0x18 3750, init 3125, page 2941, c 2857, upd 2857; retail's registers
follow init, 0x18, upd, page, c. No sched1 rank-key order (6,331 variants), no random sched1
order (30,000) and no source order reaches that from the natural source; one more reference on
each callback quantity does. It is not retail's global behaviour: forced on for every USA
v1.01 C unit it changes 13 functions. Use it only in a unit of its own (owner ruling,
12 November 2026), as `src/game/002CA070-pause.c` does. Controls:
[test_la_funcref_weight.py](../../tests/test_la_funcref_weight.py) (a positive fixture whose
callback address moves ahead of two data addresses, and a data-only twin that must stay
byte-identical).

### Consecutive truncations sharing a scratch (opt-in)

`fix_truncsfsi2` clobbers an integer SCRATCH that the R5900 template never emits: it prints
`cvt.w.s` into the FP scratch and moves that to the destination. reload still names a
general register for it, and that register's dependences decide which loads sched2 may lift
above the truncation. `-frac2-fix-scratch-reuse` makes `order_regs_for_reload` put the general
register used by the previous reloaded insn of the same block first, when both insns are such
truncations; stock reload takes the first free register in `REG_ALLOC_ORDER`.

In `func_002FA270` the icon height truncation (insn 698) follows the y rounding's (676). Stock
gives it `$4`, which orders sched2's D_001AD3C0/scale/clamp loads differently from retail;
retail's order is the one with `$6`, 676's scratch. Forced on for every USA v1.01 C unit the
switch changes no function's bytes. It renames the unemitted scratch of 5 insns in 4 functions.
Only the immediately preceding reloaded insn counts: skipping insns that took no register would
change `func_0028F410`. Any integer scratch changes 17 functions, any GPR reload 39. A per-unit
model (owner ruling, 12 November 2026), used by `src/game/002FA270-ammo-g8.c`. Controls:
[test_fix_scratch_reuse.py](../../tests/test_fix_scratch_reuse.py) reads the scratch from the
post-reload RTL dump (`-dg`).

### Constant loads beside a dying store (opt-in)

`-frac2-sched-defer-const`: before reload, Haifa does not issue a constant load (a pseudo set
to a CONST_INT) in the slot right after a same-cycle store that is the single use of a
one-set pseudo; the load waits one cycle, once per insn. local-alloc pads each quantity's
life by an insn at each end, so a birth beside such a death conflicts with the freed
register. In `func_00285030` this lets 0x8000 share `$a2` with 0xE as retail. Forced on for
every USA v1.01 C unit it changes 163 functions; the same-shape `func_0028E640` shows retail
does not always defer. Per-unit model, landed under the owner's standard of 12 November 2026
(any generally worded opt-in rule that makes a function match). Controls:
[test_sched_defer_const.py](../../tests/test_sched_defer_const.py).

### Hard-register sets first on a full sched1 tie (opt-in)

`-frac2-sched-global-yield`: when sched1 reaches the final LUID tie between a single set of a
pseudo live in more than one block and a single set of a hard register, the hard-register set
goes first. In `func_L22_003A5018` this issues `a0 = text` before the colour load and lets
reorg put the load in the call's delay slot, as retail. Forced on for every USA v1.01 C unit it
changes 211 functions; 8 matched functions with the same shape and a `%lo` load keep the load
first. Per-unit model under the same standard. Controls:
[test_sched_global_yield.py](../../tests/test_sched_global_yield.py).

### Call-clobbered stores first on a full sched2 tie (opt-in)

`-frac2-sched-store-clobbered-first`: when sched2 reaches the final LUID tie between two SImode
stores of hard registers, the store whose source is call-clobbered goes first. In
`func_0034B2C8` the two PRE copies spilled before a call become `sw $v1,0x30($sp)` then the call
with `sw $s5,0x48($sp)` in its delay slot, as retail; stock order follows PRE's expression index.
Forced on for every USA v1.01 C unit it changes 89 functions. Per-unit model under the owner's
standard of 12 November 2026. Controls:
[test_sched_store_clobbered_first.py](../../tests/test_sched_store_clobbered_first.py).

### A quadword clear holds its cycle's store slot (opt-in)

`-frac2-sched-clear-holds-store`: before reload, once a quadword clear (a TImode store of const
0) issues in a cycle, no further memory store issues in that cycle; loads, ALU and FP insns may
still take the second slot. In `func_L04_0040DCA8` (block 2, t26) the clear then pairs with a
copy instead of a store, and the h stores reach the packet ahead of c1.w as retail. Forced on
for every USA v1.01 C unit it changes 5 functions. Per-unit model under the owner's standard
of 12 November 2026. Controls: [test_sched_clear_holds_store.py](../../tests/test_sched_clear_holds_store.py).

### A call's address and pending FP stores; FP user variables last in local-alloc (opt-in)

`-frac2-sched-call-addr-float`: in Haifa's dependence analysis the MEM inside a CALL (the
function address) does not get a true dependence from a pending floating-point store. In
`func_L11_004580E8` case 5 that drops store 819's priority from the call's link, and it issues
after both `li`s as retail (136 functions change when forced on).

`-frac2-la-float-vars-last`: local-alloc's `qty_compare`/`qty_compare_1` order floating-point
quantities whose first pseudo is a user variable after every other quantity; within each group
the stock priority and quantity order stand. In case 0 the temporary holding 0.1 takes `$f0`
before gravity and limit, as retail (436 functions change when forced on). Both are per-unit
models under the owner's standard of 12 November 2026. Controls:
[test_sched_call_addr_float.py](../../tests/test_sched_call_addr_float.py),
[test_la_float_vars_last.py](../../tests/test_la_float_vars_last.py).

### Reload round robin: lone classes and pseudo reuse (opt-in)

`-frac2-reload-lone-class-no-rotate`: a reload whose class holds a single spill register does
not move `last_spill_reg`. `-frac2-reload-reuse-pseudo-reg`: an input reload of a pseudo goes
back to the spill register that last loaded that pseudo, if no insn has stored into it since,
and does not move the round robin. In `func_0028A670` draw 1's truncation FP scratch (`$f1`, a
one-register class) no longer moves the pointer and draw 2's 0x8710 reload returns to `$a2`;
the later scratch and loop-counter reloads then land as retail. Forced on together they change
266 functions (142 and 185 alone). Per-unit models under the owner's standard of
12 November 2026; `src/game/00288D88.c` uses them (none of its other 45 C functions change).
Controls: [test_reload_rotation.py](../../tests/test_reload_rotation.py).

### cse canonical registers, hard-register argument loads and reload_cse at branch targets (opt-in)

Three switches (tools/compiler/transformers/cse_arg_rules.py) for `func_002900B8`:
`-frac2-cse2-keep-multi-set-reg` (after loop, a set-once pseudo does not displace a
several-set pseudo as a quantity's canonical register; keeps case 1/2's 128 multiply on r206),
`-frac2-cse-arg-hard-reg` (a hard-register load from a constant or hard register is not
rewritten to read a several-set pseudo; a constant takes another hard register of its quantity)
and `-frac2-reload-cse-branch-to-next` (reload_cse keeps register values at a label used only by
the conditional branches directly in front of it). The last two give text call 2's
`mov.s $f14,$f22 ... mov.s $f15,$f14`. Forced on they change 13, 9 and 0 functions (22
together). Per-unit models under the owner's standard of 12 November 2026. Controls:
[test_cse_arg_rules.py](../../tests/test_cse_arg_rules.py).

### sched2 holds lower-priority insns behind a pending barrier (opt-in)

`-frac2-sched2-barrier-hold`: after reload, while the result of a scheduling barrier (an insn
carrying saved loop notes) is pending (clock < issue cycle + `insn_cost`), only insns of the
highest ready priority issue; an insn held this way ranks ahead of equal-priority insns once the
hold ends. In `func_L03_003C7018` draw 2's barrier is a `cvt.s.w` with latency 3, and retail
issues `lwc1 $f14` alone, then `ori $a1,0xC070` ahead of `mov.s`. Forced on for every USA v1.01
C unit it changes no other function. Per-unit model under the owner's standard of
12 November 2026. Controls: [test_sched2_barrier_hold.py](../../tests/test_sched2_barrier_hold.py).

### PRE at a call-result test, cse block skipping, and two sched2 tie-breaks (opt-in)

Four switches for `func_L06_004587E8` (tools/compiler/transformers/l06_rules.py):
`-frac2-pre-call-test` (gcse PRE treats a block ending in a call, a copy of the return register
and a conditional jump on it as ending in the call, so it inserts before the call's first
parameter load; 254 functions change when forced on), `-frac2-cse-noskip-store` (cse does not
skip a block containing a memory store; 737), `-frac2-sched-retstore` (after reload, on equal
priority and class, a store of an FP return-value register goes before a load of a call argument
register; 412) and `-frac2-sched-stackaddr` (on a full sched2 tie, `reg = $sp + offset` goes
before `reg = const_int`; 266). Per-unit models under the owner's standard of 12 November 2026.
Controls: [test_l06_rules.py](../../tests/test_l06_rules.py).

### Constant user variables in cse2, barrier anti-dependences, loop-exit duplication, constant deferral (opt-in)

For `func_0028D1E8` (tools/compiler/transformers/d1e8_rules.py): `-frac2-cse2-keep-const-vars`
(in cse after loop, a user variable set to a constant does not join another register's quantity
for that constant; 26 functions change when forced on) and `-frac2-sched-barrier-anti` (a read
of a register the scheduling-barrier insn does not really set is only an anti-dependence on it;
0). For `func_002D4948` (d4948_rules.py): `-frac2-loop-exit-dup-first-pass` (jump duplicates a
loop's exit test only on its first pass, as its comment requires; 173) and
`-frac2-sched-defer-const-after-death` (sched1 defers a constant load one cycle after an insn
that ends a block-local single-use pseudo, generalising `-frac2-sched-defer-const`; 637).
Per-unit models under the owner's standard of 12 November 2026. Controls:
[test_d1e8_rules.py](../../tests/test_d1e8_rules.py), [test_d4948_rules.py](../../tests/test_d4948_rules.py).

### Frame-pointer PRE hash, paired giv initial values, cse2 temporary sums (opt-in)

For the L00 ring twins (tools/compiler/transformers/l00_rules.py): `-frac2-gcse-hash-fp-117`
(the frame-pointer REG hashes 117 further on in gcse; with `ring` declared first this gives
retail's PRE reaching-register and spill-slot order; offsets 113..120 fit; 100 functions change
when forced on), `-frac2-giv-pair-init` (two reduced givs of one biv with initial values
BASE+PRODUCT and (BASE+C)+PRODUCT are emitted as PRODUCT+BASE and (BASE+PRODUCT)+C; 2) and
`-frac2-cse2-skip-temp-sum` (after loop, a register+register sum into a several-set non-user
pseudo is not recorded; 10). The last two were fitted to retail's bytes. Per-unit models under
the owner's standard of 12 November 2026. Controls: [test_l00_rules.py](../../tests/test_l00_rules.py).

### PRE hash spread and pseudo base, reorg branch reversal, sched2 issue holds (opt-in)

- `func_002B44C0` (b44c0_rules.py): `-frac2-gcse-hash-pseudo-spread` (a pseudo hashes as
  regno + 16 * (regno - LAST_VIRTUAL_REGISTER) in gcse; with `-frac2-gcse-hash-111`; 92 units
  change when forced on) and `-frac2-reorg-reverse-filled-branch` (in the last reorg pass a
  filled, not-taken conditional branch followed by an unfilled jump has its targets swapped; 185).
- `func_002859C8` (d59c8_rules.py): `-frac2-sched2-fp-load-holds-store` (after an FP load in a
  cycle, a store blocked by the memory unit keeps lower-priority insns out of that cycle; 474)
  and `-frac2-sched2-stack-store-first` (on a sched2 tie a stack store goes before an
  argument-register copy; 198).
- `func_003478F0` (d78f0_rules.py): `-frac2-pseudo-base` (pseudo numbering starts 128 higher;
  107), `-frac2-gcse-hash-171` (171 PRE buckets; 133) and `-frac2-sched-elapsed-latency` (sched1's
  class test counts an elapsed latency as independent; 4).
Per-unit models under the owner's standard of 12 November 2026. Controls:
[test_b44c0_rules.py](../../tests/test_b44c0_rules.py), [test_d59c8_rules.py](../../tests/test_d59c8_rules.py),
[test_d78f0_rules.py](../../tests/test_d78f0_rules.py).

### FP constant first in a two-quantity block (opt-in)

`-frac2-la-fp-const-first` (tools/compiler/transformers/la_fp_const_first.py): in local-alloc,
when a block has exactly two quantities, both floating point, and the first born is a constant
(REG_EQUIV), the constant is allocated first. In `func_002D3FA0`'s y3 block the 187.0 constant
then takes `$f0`, as in the three-quantity sibling blocks. 110 functions change when forced on.
Per-unit model under the owner's standard of 12 November 2026. Controls:
[test_la_fp_const_first.py](../../tests/test_la_fp_const_first.py).

### Frame-pointer PRE hash offset 112 (opt-in)

`-frac2-gcse-hash-fp-112` (tools/compiler/transformers/gcse_hash_fp_112.py), a sibling of
`-frac2-gcse-hash-fp-117`: gcse hashes the frame pointer 112 buckets further on, which gives
`func_L20_0039BEC8` retail's PRE reaching-register and spill-slot order at sp+0x148..0x168
(111..113 fit). 102 functions change when forced on; none in `L20_002DEBE0-g8.c`, which builds with
it. Per-unit model under the owner's standard of 12 November 2026. Controls:
[test_gcse_hash_fp_112.py](../../tests/test_gcse_hash_fp_112.py).

### Four global-alloc and sched2 rules of func_L04_0040AD28 (opt-in)

tools/compiler/transformers/l04_ad28_rules.py adds four opt-in switches:
- `-frac2-ga-no-lo-sum-pref`: in global-alloc's set_preference a LO_SUM source gives its
  destination no register preference (211 functions change when forced on);
- `-frac2-ga-divisor-first`: a pseudo set once from a const_int and used as a division or modulo
  divisor is allocated first (48);
- `-frac2-sched2-call-copy-fp-wait`: after reload no floating-point load issues in the cycle of a
  copy that saves a call's value register in a call-saved register right after the call (69);
- `-frac2-sched2-const-low-reg-first`: on a full sched2 tie between two constant loads into hard
  registers, the lower-numbered register goes first (986).
Each is needed by `func_L04_0040AD28` (name row, time / 60, 0x96 row, 0x2F79/0x2F99 order).
Per-unit models under the owner's standard of 12 November 2026. Controls:
[test_l04_ad28_rules.py](../../tests/test_l04_ad28_rules.py).

### Eleven rules of func_0034CEA0 (opt-in)

tools/compiler/transformers/cea0_rules.py adds, all default off (forced-on corpus counts in
brackets): `-frac2-gcse-hash-fp-54` (89), `-frac2-gcse-hash-parm-85` (31) and
`-frac2-gcse-hash-415` (136), fitted PRE hash offsets and table size like hash-111/fp-117;
`-frac2-sched2-pair-units` (1224): after reload a cycle's second slot goes to an equal-priority
ready insn of another unit; `-frac2-sched2-pair-after-higher` (883 with pair-units): only after a
higher-priority insn issued; `-frac2-equiv-const-keep-length` (126): a once-set integer-constant
pseudo with 7 or more refs keeps its live length (update_equiv_regs does not double it);
`-frac2-reload-const-in-out-reg` (24): an integer constant input reload uses the insn's free
output register; `-frac2-reload-reuse-until-label` (162 with reuse-pseudo-reg): the reuse memory
is forgotten at labels; `-frac2-output-dep-no-alias-sets` (808 with -fstrict-aliasing): alias
sets do not remove output dependences; `-frac2-unsized-sda-no-cond-slot` (115): a load of an
sda variable of unknown size stays out of conditional delay slots; `-frac2-regmove-cmove-copy`
(9): a conditional move with a live register arm and a zero arm gets a copy of that arm into its
destination. Per-unit models under the owner's standard of 12 November 2026; `func_0034CEA0` is
also a FAKEMATCH unit (config/fakematch.tsv). Controls:
[test_cea0_rules.py](../../tests/test_cea0_rules.py).

### Two PRE hash offsets of the PAL and USA v2.00 func_0034CEA0 copies (opt-in)

tools/compiler/transformers/gcse_hash_fp_59.py adds, default off, `-frac2-gcse-hash-fp-59` and
`-frac2-gcse-hash-parm-91`: siblings of fp-54 and parm-85 above, the frame pointer hashes 59
buckets further on and an incoming argument's pseudo register 91. With `-frac2-gcse-hash-415`
they give retail's spill-slot order in `func_PAL_0034F068` and `func_US2_0034DBE0`, whose larger
menu object moves PRE's buckets (owner ruling, 14 November 2026). Forced on together for every
USA v1.01 C unit they change 117 functions. Controls:
[test_gcse_hash_fp_59.py](../../tests/test_gcse_hash_fp_59.py).

### Two rules of the PAL func_L11_004580E8 copy (opt-in)

tools/compiler/transformers/l11_dce0_rules.py adds, default off (forced-on corpus counts in
brackets): `-frac2-sched-fp-const-temp-first` (43): before reload, on a full tie between two
floating-point constant loads into pseudos live beyond their block, the load into a compiler
temporary goes before the load into a user variable (a sibling of
`-frac2-sched-frame-temp-first`); `-frac2-ga-addr-equiv-no-new-save` (16): in global-alloc a
call-crossing user variable set once to a constant address (REG_EQUIV of a SYMBOL_REF, LABEL_REF
or CONST) does not take the only register left that nothing has used so far, one that would add a
callee save; left without a register, reload rematerialises the address at each use. Together
they match `func_PAL_L11_0045DCE0` (owner ruling, 14 November 2026). Controls:
[test_l11_dce0_rules.py](../../tests/test_l11_dce0_rules.py).

### The after-reload order hint and two rules of func_US2_002CD670 (opt-in)

tools/compiler/transformers/sched2_order.py adds `-frac2-sched2-order`, the after-reload
sibling of `-frac2-sched1-order`: the second scheduling pass issues the insns named by
`#pragma rac2_sched2_order UID...` in list order, through the same hooks. It is an
instruction-order hint, not a model of the retail compiler: a fakematch mechanism allowed only
where AGENTS.md says. tools/compiler/transformers/cd670_rules.py adds, default off (forced-on
corpus counts in brackets): `-frac2-sched-keep-live-length` (1315): the first scheduling pass
may lengthen a register's recorded live length but never shortens it; and
`-frac2-combine-keep-dead-sets` (1): combine marks a set left without uses REG_UNUSED instead of
deleting it, for flow2 to remove. With dead user-variable copies and both order hints they match
`func_US2_002CD670` (owner rulings, 14 November 2026). Controls:
[test_sched2_order.py](../../tests/test_sched2_order.py),
[test_cd670_rules.py](../../tests/test_cd670_rules.py).

### A local-alloc rule of func_PAL_002CD520 (opt-in)

tools/compiler/transformers/cd520_rules.py adds, default off, `-frac2-la-unweighted-refs` (229
forced-on corpus changes): local-alloc ranks a block's quantities by their reference counts
divided by the block's loop depth (rounded, at least 1), so references inside do { } while (0)
groups are not weighted. With -frac2-combine-keep-dead-sets, dead stand-in loads and both order
hints it matches `func_PAL_002CD520` (owner rulings, 14 November 2026). Controls:
[test_cd520_rules.py](../../tests/test_cd520_rules.py).

### Four rules of func_002CC6B0 (opt-in)

tools/compiler/transformers/cc6b0_rules.py adds, all default off (forced-on corpus counts in
brackets): `-frac2-flow2-trap-mem` (0): after reload a trap insn ends flow's dead-store tracking;
`-frac2-la-multi-death-locals` (154): local-alloc also takes a block-local user variable that dies
more than once, as one quantity from its first set to its last death; `-frac2-sched-const-first`
(965): before reload, on a priority tie and ahead of the weight test, a constant load into a
pseudo goes before a two-operand arithmetic set of a pseudo; `-frac2-sched-temp-store-after-args`
(1109): before reload, on a priority tie, a store of a compiler temporary goes after a set of a
call-argument register. Per-unit models under the owner's standard of 12 November 2026;
`func_002CC6B0` is also a FAKEMATCH unit (config/fakematch.tsv). Controls:
[test_cc6b0_rules.py](../../tests/test_cc6b0_rules.py).

### Eleven rules of func_L04_00417308 (opt-in)

tools/compiler/transformers/l04_17308_rules.py adds, all default off (forced-on corpus counts in
brackets): `-frac2-loop-align-in-loop-only` (6): a loop's alignment goes only to a label inside it;
`-frac2-la-const-longer-first` (810): of two integer-constant quantities with equal refs, the
longer-lived is allocated first; `-frac2-sched-hoisted-first` (528): on a full sched1 tie, an insn
moved out of a loop goes first; `-frac2-cse-path-11` (20): a cse path follows 11 jumps;
`-frac2-loop-move-temps` (398): loop invariant motion may move a conditionally set temporary;
`-frac2-sched-arg-sum-first` (1063): on a full sched1 tie, an argument-register sum before a pseudo
copy; `-frac2-ga-hoisted-var-first` (1): a hoisted float user variable counts 3% higher in
global-alloc; `-frac2-sched-call-last` (54): a call heading the ready list issues after the next
ready insn of its cycle when that came first originally; `-frac2-sched-argreg-wait` (2317): an
argument-register set that depends on a preceding call waits two cycles (constant loads after a
call without a value excepted); `-frac2-sched-frame-temp-first` (64): of two frame-address sets,
the temporary first; `-frac2-sched-call-with-arg-copy` (2 with argreg-wait): a call with a value
issues in the cycle of the delayed argument copy that readies it. Per-unit models under the
owner's standard of 12 November 2026; `func_L04_00417308` is a FAKEMATCH unit
(config/fakematch.tsv). Controls: [test_l04_17308_rules.py](../../tests/test_l04_17308_rules.py).

### Nine rules of func_L17_003E8A58 (opt-in)

tools/compiler/transformers/l17_rules.py adds, all default off (forced-on corpus counts in
brackets): `-frac2-register-scope` (0): when optimizing, a `register` variable stays live to the end
of its scope; `-frac2-sched-flush-30` (37): the scheduler flushes its pending memory lists beyond 30
entries; `-frac2-sched1-priority-only` (4338): before reload, ties after priority skip the weight
and dependent-count keys; `-frac2-sched-uservar-const-no-boost` (22): a constant loaded into a user
variable is not promoted as a register birth; `-frac2-sched2-fp-symbol-load-latency-3` (750): after
reload an FP load from a symbol address has latency 3; `-frac2-keep-user-copies-strict` (98):
combine substitutes nothing into a pseudo-to-pseudo copy into a user variable (beside upstream's
`-frac2-keep-user-copies`); `-frac2-sched-uservar-copy-priority` (114): a copy into a user variable
adds 4 to its dependences' priority; `-frac2-sched2-fp-const-first-consumer` (90): of two tied FP
constant loads, the one whose first dependent comes first goes first;
`-frac2-sched2-qi-store-offset` (282): of two tied byte stores to one base, the lower displacement
first. Per-unit models under the owner's standard of 12 November 2026; `func_L17_003E8A58` is a
FAKEMATCH unit (config/fakematch.tsv). Controls: [test_l17_rules.py](../../tests/test_l17_rules.py).

### Eight switches of func_L05_0042B2C0 (opt-in)

tools/compiler/transformers/l05_42b2c0_rules.py adds, all default off (forced-on corpus counts in
brackets): `-frac2-loop-no-equal-copy-subst` (317): loop does not fold a pseudo copy that carries a
REG_EQUAL note into its single use; `-frac2-loop-move-high-copy` (4): loop motion moves a pseudo
copy of a symbol's high part as the copy; `-frac2-rerun-loop-move-consts` (59): the second pass of
`-frerun-loop-opt` always moves an invariant symbolic constant out of a loop;
`-frac2-rerun-loop-no-reverse` (462): that second pass does not reverse a loop;
`-frac2-loop-ivs-in-order` (9): strength reduction visits the induction variable classes in the
order their bivs were found; `-frac2-cse2-loop-end-forgets-arith` (14): after loop, at a loop end,
cse forgets pseudos set inside that loop from a sum or product, so an address formed in a
`do { } while (0)` group is formed again after it; `-frac2-sched-phony-loop-notes` (249): the loop
notes of a `do { } while (0)` group are deleted before scheduling, so the group is no scheduling
barrier (stock: a barrier in both scheduler passes, and its references count one loop level deeper
in flow). These seven are per-unit models under the owner's standard of 12 November 2026.

`-frac2-sched1-order` (0) is not a model. Before reload the scheduler issues the insns named by
`#pragma rac2_sched1_order UID...` in the listed order, one per cycle and without waiting for a
function unit, wherever the dependences allow; unlisted insns are scheduled as usual. The list
belongs to the next function compiled and is dropped after its first scheduling pass; without the
switch the pragma is ignored. It exists for `func_L05_0042B2C0` alone (owner ruling,
14 November 2026): the function's plain C gives retail's instructions, but no general rule or
source form was found for the order of its first scheduling pass, on which local-alloc's
priorities and reload's round-robin scratch registers depend. The list names insn UIDs, so it
holds for one source text and one set of flags. `func_L05_0042B2C0` is a FAKEMATCH unit
(config/fakematch.tsv). Controls: [test_l05_42b2c0_rules.py](../../tests/test_l05_42b2c0_rules.py).

This reference groups qualified compiler mechanisms and useful C source shapes by
topic. Open cases belong in [matching-blockers.md](../contributing/matching-blockers.md). The source
recipe, per-file flags and complete linked build take precedence over historical
observations; this document is not a progress report or a reconstruction of the
unknown shipping toolchain.

Source-shape observations cited from [PR #295](https://github.com/OpenRAC/rac2-decomp/pull/295)
were measured on both USA releases. Their integration status and PAL qualification
belong to that PR; they are not additional project-progress claims.

## Identity, tools and reproduction

| Input | Maintained implementation | Role |
| --- | --- | --- |
| Game C | [tools/compiler/build.sh](../../tools/compiler/build.sh) | Public GNU EE 2.9-ee-991111b cpp/cc1, pinned Lombyte sce-991111b patches and measured transformers |
| SDK C | [tools/compiler/sdk/build.py](../../tools/compiler/sdk/build.py) | Public-source Sony EE-GCC 2.9-ee-991111-01, selected with the sdk prefix in config/cflags.txt |
| Assembly from either C frontend | Source-built game GNU as | Qualified immediate, hazard and padding rules |
| Remaining assembly reconstructed from the disc | Locally supplied SN ProDG 2.0 Ps2EeAs.exe | Separate from the GNU-assembled C-object path |
| Final link | Locally supplied SN ld.exe | Places the objects before comparison against retail |

The GNU archive is `gnu-ee-binutils-gcc-1.1.tar.gz`, SHA-256
`1f518043e252d6eda726386971d52eda26541ab936ea73a9783d73712b595f92`, target
`mips64r5900-sf-elf`. [CREDITS.md](../../CREDITS.md) records the public sources.
Proprietary SDK source, samples and headers are not inputs.

Matching bodies establishes compatibility, not Insomniac's exact original binary,
patch set, flags or directives. The earlier SN 2.95.3 profile matched simple leaves
but disagreed on saves, sibling calls and block moves. Leaf-only controls do not
exercise those mechanisms.

Prefixes such as `8bed6eae` identify historical local binaries, not compiler versions
or selectable tools. Binary hashes depend on the host. The maintained recipe owns
the patch order and source-hash checkpoints; do not replay obsolete hash tables,
copied shell recipes or the removed `scripts/` workflow.

```sh
bash tools/compiler/build.sh
python3 tools/compiler/sdk/build.py
python3 tools/check.py func_XXXXXXXX --diff
python3 tools/build.py all --strict --jobs 8
```

See [building.md](building.md) for setup and [versions.md](versions.md) for releases.
Flags are per file in [config/cflags.txt](../../config/cflags.txt). A `*-g8.c` sibling
gets `-G8` unless an earlier explicit rule matches. Qualify every C definition in a
unit after changing its profile.

The old tools need 32-bit Linux support and bison 1.28. Generate `insn-flags.h`,
`insn-codes.h` and `insn-config.h` before parallel compilation: the 1999 Makefile
omits the `flow.o` dependency. Linux filesystem intermediates avoid old 32-bit
`stat` failures on Windows filesystem inodes. The maintained recipe/container
handles these constraints.

## Selecting a profile

Read the retail frame and instructions before changing C. Do not compensate for a
wrong profile with extra operations or knowingly false prototypes.

| Observed difference | Profile or mechanism | Measured example |
| --- | --- | --- |
| Ordinary 8-byte GPR saves | Default game -O2 -G0 -ffunction-sections | func_002889B8 |
| Missing GP-relative access | Game compiler, -G8 sibling and correct known-size declaration | func_L00_003206B8 |
| Public SDK/libgcc source differs under game compiler | sdk profile, accurate types and inline declarations | func_00122800, func_00122B00 |
| libgcc `_eh.o` (L_eh): preserve the frame at final calls and place the exception-return stub correctly | sdk profile with -fexceptions, as GCC's libgcc Makefile builds _eh.o (rac3-decomp builds its copy the same way) | func_00120A30, func_001208E8; paired throw/rethrow func_00120F00 and func_001210E0 |
| Whole GPR save area uses sq/lq | -mastra-quad-saves | func_00119BC8, func_00115F28, func_00115C90 |
| Quad slots: `sd $ra` below `sq $s0` | -mastra-quad-saves -frac2-narrow-saves-below, `register_precision(ra, 64)` | func_L01_00324550, func_L08_00389B68 |
| 8-byte slots, but a TImode-held saved GPR gets `sq` in a 16-byte slot below them | -frac2-wide-saves-below | func_L02_00411D18 |
| Reduced giv start `x*16 + (i*400 + (D-16))`, not flattened | -frac2-mult-add-no-flatten | func_L20_0039F968 |
| Copy of a zero set in the same block stays a register copy | -frac2-keep-block-zero-copy | func_002F7320 |
| A volatile asm ends the forward delay-slot search past later loads | -frac2-sticky-volatile-refs | func_L00_002A9460 |
| `jal` slot empty after a plain store and then a volatile store | Default (GCC 2.95's set-side rule); -fno-rac2-sticky-volatile-sets restores the EE tree's | func_L00_002A3B88, func_00131DE8 |
| Branch slot setting `$fp` annulled (`bnel`), retail `bne`; no frame pointer | -frac2-frame-pointer-liveness | func_L07_0040EC08, func_L04_00414698 |
| Callee saves issued at the top, retail has them among stores through `$v0` | -frac2-no-static-chain-base (with -frac2-frame-pointer-liveness) | func_002BA0E0 |
| A word stored into a float read twice: `lui`/`ori $v0` after the previous call, one `mtc1` into a saved FPR, `mov.s` per read | -frac2-keep-float-pun-source, write `*(s32 *)&f = K` | func_00349D58 |
| A frame counter allocated as if a copy of it were tied to it: the counter takes the first free register ahead of `counter + 1` and constants | -frac2-keep-user-copies, write the copy as a named local after the counter's store | func_PAL_L09_0040FD68, func_PAL_L00_003B9E80 |
| A cursor advanced several times per iteration is split into reduced pointers (`sd 0/8/16/24` and one add); retail stores and adds after each | -frac2-no-extra-increment-givs (with -fno-rerun-loop-opt) | func_00284268 |
| Two-word truncation cannot fill return slot | -mastra-split-trunc-slot | func_0012E8C8 |
| SDK unit: a volatile access or sign extension fills a `jal`/`jr` slot | -Wa,--r5900-swap-branch-slots | func_001253A8, func_0012E378, func_0011C000 |
| Arguments spilled and branch to common epilogue | Measured -O0 unit, not an invented varargs helper | func_001175F0 |
| Absolute load must reuse its destination as address temporary | -mno-split-addresses and assembler symbol model | func_001339B0, func_L20_0043F460, func_L16_00411D00, func_L08_00429350 (declaration order of the pointer inits) |
| Register addresses and grouped 16-byte transfer | -frac2-qcopy | func_L20_0039E158, func_L20_0039F210, func_00305058 (with -g for the pre-div.s nop pair) |
| Correct copy, wrong motion across it | -frac2-qcopy-barrier, with qcopy | func_002B5E48, func_002EE988 |
| Stack quadword zero kept as `por` + `sq` beside a qcopy | -frac2-zero-ti-por | func_L04_0046D6A8 |
| Absolute load must reuse its destination as address temporary | -mno-split-addresses and assembler symbol model | func_001339B0, func_L20_0043F460, func_L16_00411D00 |
| Nop pair before div.s (float rounding helper) | -g | func_002AEAE0 |
| Register addresses and grouped 16-byte transfer | -frac2-qcopy | func_L20_0039E158, func_L20_0039F210, func_00305058 (with -g for the pre-div.s nop pair) |
| Correct copy, wrong motion across it | -frac2-qcopy-barrier, with qcopy | func_002B5E48, func_002EE988, func_L01_003BC490, func_L08_003D3D80 |
| Loop constants hoisted though the loop is over `threshold` for them | -fmove-all-movables on a file of its own | func_L00_004287E8, func_L16_004117A8 |
| Hoisted addresses, branch joined with an empty edge block | -frac2-gcse-unsplit-edges | func_L00_00370408 |
| Float min/max expands into compare and branch | -ffast-math; optimization level still affects allocation | func_L01_003BD560, func_L00_002EE050 |
| A loop constant stays in the loop where retail hoists it: loop.c's threshold is 61 in this tree, retail's 64 | -fcall-used-hi1 -fcall-used-lo1 -fcall-used-accum1 on a file of its own (see below) | func_0026EDE8 |

`-G8` can change allocation even without GP accesses: `func_L17_003BCBC8` puts
colour constants in different registers. The effect can be a loop hoist: with
`-G0`, cc1 lifts the `lui` of a level global's address out of the loop into a
callee-saved register and saves it; with `-G8` it re-materialises `lui`/`lw` at
each use, which is what retail does (`func_L10_004174C8`, `func_L02_003CCFE8`).
A successful profile is not proof of the original SDK flags.

Patch 0055 (r5900-no-second-hilo) keeps the r5900's second hi/lo pair (`HI1`, `LO1`,
`ACCUM1`) fixed, because retail game code never uses it. A side effect is that loop.c
counts fewer allocatable registers, which lowers its hoisting threshold from 64 to 61
in every unit. In `func_0026EDE8`'s memory-card wait loop retail hoists constants
that this tree keeps in the loop: measured from loop.c's pass-2 decisions, the
function needs a threshold of 64 or more and below 67. `-fcall-used-hi1
-fcall-used-lo1 -fcall-used-accum1` make the pair call-used instead of fixed, which
restores the threshold of 64 for that unit only; no code uses the registers. Applied
to every unit the flags change 6 of 160 sampled matched units, so retail's register
setup is not simply one or the other everywhere and the flags stay per unit. Use them
only when a function's own loop.c dump shows the threshold is the blocker, and give
the measured threshold in the commit.

7 November 2026 (round 9): patch 0055 only flips `fixed_regs`; it does not change
`FIRST_PSEUDO_REGISTER` or pseudo numbering, and gcse runs before loop.c, so it cannot
explain the gcse PRE hash-order near misses. Measured on func_00281A08, func_L20_0039BEC8,
func_L00_003E5BD8, func_0034CEA0 and func_L00_002EC970: the three flags leave four
unchanged and add one word to func_0034CEA0. With a test cc1 that adds a constant to
pseudo numbers in `hash_expr_1` (-90..200) or to `n_insns` in `alloc_expr_hash_table`
(-240..240), no pseudo offset matches any of the five; cuid offsets match only
func_00281A08 (-142,-140,-94,-92) and func_L00_002EC970 (20 values, none shared). On the
full grid (pseudo -100..100 x cuid -240..240 step 2) the only shared point is +93/-142,
and it leaves the other three unchanged, so no single pseudo/cuid offset explains them.

8 November 2026: `alloc_expr_hash_table` sizes the PRE table as `max_cuid / 2 | 1` (at least 11).
On the same input, the five EE cc1 builds in hand (this tree, 991111a, 991111-01,
991111b-r4 and SN 2.95.2 273a) print the same table size in their `-dG` dumps, so they
share the rule. A test cc1 that forced every odd size 11..401 gives 0 diffs for
func_L00_0038E880 at 20 sizes, func_L13_0041AD00 at 49/103/137/147/181 and func_00281A08 at
23/47; func_L00_003E5BD8 (best 8) and func_002B44C0 (best 21) never reach 0. No size base
fits two targets: max_cuid, get_max_uid(), all or non-NOTE insns, cuid plus notes, labels or
blocks, max_reg_num(), or the real-insn count after expand, jump1, cse1 or dead-insn removal,
each over 1-4, or a prime size. Forced on all 8775 game units, the expand-time count changes
170 units, get_max_uid() 142, non-NOTE insns 188 and prime sizes 87, so none is safe.

## Frames, calls and ABI

### Object extent and stack allocation

A physical stack slot does not establish a C object's size. In
`func_L01_003DD3A0`, the iterator helper reads and updates one pointer; replacing a
padded 16-byte cursor struct with a plain `char *` cursor preserves all 776 bytes
in each carrying release's local check. Keep the compiler's padding implicit.
Likewise, adjacent GP-relative addresses establish spacing, not the complete size
of each external object. A known field prefix does not justify a bounded small-data
declaration when the owning allocation or remaining consumers are unknown.

The three matrix buffers in `func_L02_003D6EE0` are independently 48, 48 and
64 bytes, rather than three equal stack-slot guesses. `func_002833F0` writes
three vectors; `func_00283678` copies three; `func_00283698` reads three and
writes four. The later `func_00283738` consumes only three vectors from each
input. Check every producer and consumer before enlarging or shrinking a buffer.

A full-width transfer does not establish that every lane is interpreted as a
value. The type-2 particle path used by `func_L00_003E7E40` transfers sampled
position W, while its normal renderer computes XYZ and replaces output W before
consumption. The constructor clears the controlling flag and its updater retains
that state. This permits the observed opaque transfer, not a 12-byte allocation:
the complete 16-byte storage is still required. Verify the same lifecycle before
reusing this conclusion, and do not invent a W initialization for matching.

The water context in `func_L20_00447748` is thirteen words (0x34 bytes), not
the fourteen words suggested by its old stack-layout screen. Its final callback
field occupies +0x30 and no consumer reads a fourteenth word. Preserve the actual
callback signatures and initialize the real field groups; extra stack space is
not a reason to invent another member.

### Save order and loop padding

The default game profile uses 8-byte GPR slots and ascending GPR save/restore order.
FPR order stays descending. Source emission is **GPR before FPR on both saves and
restores**; scheduling may interleave them. The former FPR-first reconstruction
was a regression, not an alternate rule to restore.

In the original 28-program mixed-frame survey, 92.5% of 31,278 frames began with a
GPR save, but only 34.8% of the tutorial's mixed frames kept the whole GPR block
before every FPR save. Emission order is not final scheduled order. Fixing a frame
does not fix unrelated entry-block allocation or address formation.

The implementations are
[neutralise_timode_anchor.py](../../tools/compiler/transformers/neutralise_timode_anchor.py),
[ascending_save_order.py](../../tools/compiler/transformers/ascending_save_order.py) and
[reorder_save_blocks.py](../../tools/compiler/transformers/reorder_save_blocks.py).
The reorder consumes the ascending-order transformer's output. Replacing `mips.c`
with an older file also removes the zero-fold code called by `toplev.c`.

[disable_frame_order_default.py](../../tools/compiler/transformers/disable_frame_order_default.py)
keeps generic frame scheduling by default; `-mastra-keep-frame-order` is an explicit
experiment. `func_002B7170` needs the generic order plus measured source lifetimes
and stores. No frame-order option fixes arbitrary entry-block allocation.

### Short-loop padding

Short-loop padding must run after delay-slot scheduling: this C pipeline uses GNU
`as`, rather than the assembler assumed by patch 0054.
[enable_loop_padding.py](../../tools/compiler/transformers/enable_loop_padding.py)
restores the hook.
[count_trap_length.py](../../tools/compiler/transformers/count_trap_length.py) counts a
`TRAP_IF` by its machine-description length: a division guard is branch plus break,
not one word. Counting one overpads `func_0028B950`; `func_0034FB20` is the 168-byte
polling-loop witness.

[count_block_move_length.py](../../tools/compiler/transformers/count_block_move_length.py)
does the same for block moves. A structure copy of 0x40 bytes or more becomes a loop
of one `movstrsi_internal2` insn (its loads) and one `movstrsi_internal3` insn (its
stores); counted as one word each, every such loop looked five words long and got two
NOPs before its branch. Retail never pads them: the unaligned `ldl`/`ldr`/`sdl`/`sdr`
loop is 19 words and the aligned `ld`/`sd` loop 11. Counting the two insns by their MD
length (20 and 1) keeps both above the seven-word threshold. Retail witnesses, all
unpadded: `func_L08_003C6AB0` (both loops, three places), `func_002F7738` (seven
loops), `func_L00_002FC980` (27 places), `func_L30_0040B9D8`, `func_002AF0A8`. No
matched function changes: `build.py all --strict` is OK with and without the patch.
Control: [test_block_move_loop.py](../../tests/test_block_move_loop.py), where a
four-word store loop keeps its three NOPs.

[block_move_quad.py](../../tools/compiler/transformers/block_move_quad.py) gives those loops
retail's quadword form. `expand_block_move` capped the alignment at the 8-byte word, so a
structure of 16-byte alignment copied by `ld`/`sd`: four scratch registers per 32-byte round
and four more for the leftover. Retail has `lq ; lq ; sq ; sq ; addiu ; bne ; addiu` with
`lq ; sq` for the leftover, the shape of `block_move_loop` (`src + bytes`, unaligned label,
`bne` on the source pointer) and not of a C loop. The alignment now reaches
`output_block_move`, which has a quadword case. Copies of 0x40 bytes or less still go through
`move_by_pieces` at word alignment. Witnesses: `func_L12_00418418` (one place) and
`func_L03_003E4148` (eight) become exact, `func_L12_0041BF88`'s six copies each lose their six
extra words. All 5,849 compilable units give the same assembly with and without the patch, so
nothing already matched moves. Control: [test_block_move_quad.py](../../tests/test_block_move_quad.py),
where an 8-byte-aligned page keeps `ld`/`sd` and a 0x40-byte copy keeps its pieces.

The padding counts words, as the retail assembler does, for the two 16-byte copies too:
[count_asm_words.py](../../tools/compiler/transformers/count_asm_words.py) counts an asm
statement by its instruction count (`qcopy` is `lq` plus `sq`) and the grouped
`rac2_qcopy` pattern by its length of 2. Counted as one, a copy loop got one NOP too many.
Retail evidence: in levels 0, 4 and 11, 44 seven-word loops holding an `lq`/`sq` pair
(`lq ; lq ; sq ; sq ; addiu ; bne ; addiu`, `func_00288870`, `func_002DE990`) carry no pad,
and six-word ones (`lq ; sq ; addiu ; addiu ; bgtz ; addiu`, `func_L00_003ABEC0`) carry
exactly one. Witness: the three-row matrix copy in `func_L00_0041CB80` (27 places).
It runs after count_block_move_length.py and extends the same counter condition.
No matched function changes: `build.py all --strict` is OK with both patches.
Test: [test_count_asm_words.py](../../tests/test_count_asm_words.py).

Inserted padding also advances the running word count. The pass places nops
before the branch it is already visiting, so they will not be visited later.
Without accounting for them, a second back edge to the same label adds redundant
padding. Both filled and assembler-filled delay-slot paths now count those nops.
Authored single-pair, independent-pair and volatile polling controls inspect the
actual assembled backward spans; the previous compiler fails all three. This
recovers `func_00294420`'s two tests of a shared search-loop head without changing
its C operations. Symbolic macro-length estimation is a separate limitation.

The counter also handles one measured symbolic class: an ordinary, external
32-bit register load/address whose assembler metadata has not been emitted yet.
GAS expands it to two words in reorder mode, even when the scheduler length is
one. `SYMBOL_REF_USED` establishes external provenance during expansion, and
the existing `TREE_ASM_WRITTEN` markers distinguish prior announcements and
definitions. Definitions are marked at `-G0` too, without changing emitted
assembly. Both raw `*name` and ordinary name spellings are respected.

This applies only to simple SI register SETs on R5900/GAS: not delay-slot
sequences, stores, FP/wide operations, PIC or buffered extern output. Explicit
`SDATA` aliases are excluded because their `__gp` metadata is supplied by the
existing assembly-input pass. Scheduler lengths and compiler-authored operations
are untouched. [test_symbolic_loop_words.py](../../tests/test_symbolic_loop_words.py)
checks unknown addresses/loads, early SDA, incomplete SDATA, both alias spellings
and an external defined between functions. The previous compiler produces
eight-word loops in the three positive cases; all seven controls pass with the
corrected counter. The linked C witnesses are `func_002EEBC8` (one place per USA
release and 28 in PAL) and `func_002F0FA0` (28 in each release). The complete
84-program strict qualification preserves every existing match and accepts
all 114 placements of these two bodies.

### Quadword saves and return slots

Patch 0058 enables `-mastra-quad-saves` per file: all GPR slots widen to TImode and
the GPR order retains the released descending walk; default output is unchanged.
Witnesses include `func_00119BC8` (48 bytes), `func_00115F28` (80) and
`func_00115C90` (92). The last also needs its failure value compared as unsigned
`0xFFFFFFFF` to preserve the immediate sequence.

Two variadic level functions mix widths in quad slots: func_L01_00324550 (132 bytes,
11 places; `sd $ra,0x200` below `sq $s0,0x210`) and func_L08_00389B68 (264 bytes, 4 places;
`sd $ra,0x0` below `sq $s0,0x10`), each restoring `lq $s0` before `ld $ra`. A scan of every
catalogue prologue finds one other frame mixing `sq` and `sd` GPR saves, func_L02_00411D18
(`sq $s2` in a 16-byte slot below 8-byte ones), which `-frac2-wide-saves-below` covers
(below). The stock EE attribute `register_precision(ra, 64)` on the prototype narrows the
`$ra` save to `sd`, but the save loop still gives `$ra` the top slot.
[narrow_saves_below.py](../../tools/compiler/transformers/narrow_saves_below.py) adds
`-frac2-narrow-saves-below`: with `-mastra-quad-saves` the loop walks the registers saved at
the slot's full width first, then the narrower ones, so the narrower save sits below. A frame
whose saves all have one width keeps `$ra` on top, as func_00115C90 and func_00115FC0 do;
without `-mastra-quad-saves` the option has no effect. Forced on in every game unit, it changes
none of 7,572 (144 SDK units use another compiler). `register_precision` sets the mode for the
rest of the unit, so each function has a file of its own. The attribute is an inference from
the save widths, not a recovered source line.

func_L02_00411D18 (1,928 bytes, one place in each of USA v1.01, v2.00 and PAL) holds a TImode
value in `$s2` across calls. Retail saves it with `sq $s2,0x620` below `sd $s0,0x630`,
`sd $s1,0x638` and `$s3`..`$ra` at 0x640..0x670, with `$f20`/`$f21` at 0x680/0x688 in a
0x690-byte frame, and restores in register order (`ld $s0`, `ld $s1`, `lq $s2`, `ld $s3` ...).
It is the only one of 7,980 framed retail functions that holds TImode in a saved GPR. Without
`-mastra-quad-saves` every GPR slot is 8 bytes, but save_restore_insns saves a register in the
widest mode the function writes it in, so stock cc1 gives a 0x680 frame and `sq $s2,0x630` in an
8-byte slot. `sq` ignores the low four address bits, so that store overwrites `$s3`'s save.
[wide_saves_below.py](../../tools/compiler/transformers/wide_saves_below.py) adds
`-frac2-wide-saves-below`. In a unit without `-mastra-quad-saves`, a saved GPR whose save is
wider than the slot then takes a 16-byte slot at the bottom of the GPR save area. The other
GPRs keep 8-byte slots above it in register order, and compute_frame_size adds 8 bytes for
each such register. The switch keys on the mode of the save, never on a function. **The layout
is inferred from this one witness.** Retail has no frame with two or more wide GPR saves, so
their order is not evidenced: the switch places them upwards from the bottom in register
order. A frame whose only GPR saves are wide is not evidenced either.

The frame size fixes the arg-pointer offsets during reload, before the prologue scans the save
modes, so the switch computes its mask while reload runs too. It reads the insns, whose pseudos
alter_reg has already renumbered to their hard registers (through `reg_renumber` for any it has
not), and adds the modes `mips_reg_mode` and `register_precision` give. The mask from the last
call before reload completes is kept for the rest of the function; that call is the one
verify_initial_elim_offsets checks against the offsets reload used. If the prologue then finds a
save wider than its slot, cc1 stops with an error instead of emitting an overlapping store. A
build that takes no mask during reload, as an earlier private patch did, gives the fixture's
stack-argument function a 48-byte frame (32 without the switch) but still reads the arguments at
32 and 40 (`$sp`), in the save area; `tests/test_wide_saves_below.py` fails on it.
`mips_reg_mode` stays widened for the rest of a unit, with or without the switch: a later
function that saves `$s2` saves it with `sq` too. So the witness has a unit of its own,
`src/levels/02_maktar_nebula/L02_00411D18.c`, which all three releases link. With
`-mastra-quad-saves` every slot is already 16 bytes and the switch does nothing, so it leaves
that switch and `-frac2-narrow-saves-below` unchanged. Without the switch, all 8,629
game-compiler units of `src/` (the three releases' C) compile to the same assembly as before.
Forced on in every one of them, it changes only func_L02_00411D18 and none of 11,949 other
functions in 8,628 other units (144 SDK units use another compiler).

func_L20_0039F968 (996 bytes, one place in USA v1.01) shifts a history row with
`qcopy_nc(&D[i][h], &D[i][h - 1])`. Retail starts the source cursor as `D-16; i*400 + (D-16);
last*16 + that`. loop.c reduces both cursors to givs whose start emit_iv_add_mult builds with
expand_mult_add (expmed.c), which folds the tree `last*16 + ((i*400 + -16) + D)`. In this
Cygnus-based tree fold runs the CYGNUS LOCAL reduce_expression_tree_depth on every PLUS while
-fschedule-insns is on, so the start becomes `(last*16 + i*400) + (D-16)`: 10 rows differ at
+0xC8..+0xF8. SN's "GNU C version 2.95.2 SN BUILD v2.73a" cc1 (FSF 2.95.2, which has no CYGNUS
LOCAL code) builds the same giv (its loop dump matches) but emits retail's nested sum; Sony's
991111a/-01/b-r4 cc1 flatten like ours. Only that observable output was used.
[mult_add_no_flatten.py](../../tools/compiler/transformers/mult_add_no_flatten.py) adds
`-frac2-mult-add-no-flatten`: the fold calls inside expand_mult_add run with
flag_schedule_insns clear, so the flattening is skipped there and nowhere else. Without the
switch all 8,733 game-compiler units of `src/` compile to the same assembly as before. Forced
on in every one of them, no unit changes; across the 1,139 `nonmatching/` notes (two profiles each) it
changes only func_L20_0039F968 and two others (func_L00_00395428, func_L00_003C48D0), both
further from retail (253 -> 271 and 138 -> 141 differing rows, lengths unchanged). Skipping
the flattening in every fold instead changes one matched unit (func_L30_00382FB8), so the
switch is limited to expand_mult_add. The witness has a unit of its own,
`src/levels/20_yeedil/L20_0039F968-g8.c`.

func_002F7320 (132 bytes, 28 places) starts `daddu $t1,$zero,$zero ... daddu $a3,$t1,$zero`
for `int result = 0; int i = result;`. Stock cse folds that copy to `move $a3,$0`: CONST_INT
costs 0 and a pseudo 1. With the copy alive, result=0 has a dependent, sched1 moves it ahead
of the argument copies and allocation becomes retail's (a0 value, a3 i, t1 result).
[keep_block_zero_copy.py](../../tools/compiler/transformers/keep_block_zero_copy.py) adds
`-frac2-keep-block-zero-copy`: cse keeps a copy from one pseudo to another whose value is known
to be 0 when its source is set earlier in the same basic block; the REG_EQUAL note still gives
loop.c the zero start. Without the same-block limit, forced on, it changes one matched body,
func_00349680, where jump1's duplicated loop-exit copy `lo = hi` sees a zero from an earlier
block and retail keeps `move $18,$0`. With the limit, forced on in every game unit, it changes
none of 7,577 others (144 SDK units use another compiler).

func_L00_002A9460 (412 bytes, 27 places) differs from stock cc1 in one delay slot: retail puts
`addiu $s1,$s1,%lo(D_00189E20)` in the slot of its second call, stock in the first. reorg's
forward search from the first call passes the second qcopy asm (volatile). The EE tree's
resource.c predates GCC 2.95's 6 May 1999 change (Mark Mitchell: "Make volatil monotonically
increasing"): mark_referenced_resources assigns `res->volatil = MEM_VOLATILE_P (x)`, so the
next ordinary load clears the flag and the search goes on to the addiu. Upstream 2.95 and
2.95.3 use `|=` there. [sticky_volatile_refs.py](../../tools/compiler/transformers/sticky_volatile_refs.py)
adds `-frac2-sticky-volatile-refs`: the MEM and ASM_OPERANDS cases of
mark_referenced_resources keep the flag set. Forced on in every game unit it changes none of
8,510 others. The mark_set_resources half of the same upstream change is the compiler's
default since 8 November 2026 ("reorg: a volatile store stays marked" below).
History, 7 November 2026, round 9: the set-side `|=` alone (env probe in mark_set_resources) makes
func_00131DE8 match (1 of 1 in us, pal, us2) but, forced on in all 8,734 game units, changes only
that unit and matched func_00132498 (1 -> 0 of 1): sched2 puts the hoisted
`lui $s0,%hi(D_001A7578)` before the plain D_001A74D0 and volatile D_001A74D8 stores, and retail
fills the `b` slot with it past the volatile store. func_00132498 reads no SIF field; dropping
its volatile D_001A74D8 gives 0 of 1 with or without the rule. Not landed. (Superseded: an sda
array element form of that store matches with and without the rule; see below.)

func_L07_0040EC08 (952 bytes, 1 place in each USA release) and func_L04_00414698 (6,032 bytes, 2
places in each) differ from stock cc1 in one opcode each: retail fills a branch slot with a set of
`$fp` from the branch target without annulling it (`bne`, slots `lw $fp,0x50($sp)` and
`addiu $fp,$s7,0x10`), stock annuls it (`bnel`). Neither function keeps a frame pointer; `$fp`
holds an ordinary value. The EE tree's flow.c still treats HARD_FRAME_POINTER_REGNUM as always
live after reload: mark_regs_live_at_end marks it live at the end, mark_set_1 never kills it,
mark_used_regs gives it no REG_DEAD note, insn_dead_p never deletes a set of it, and
haifa-sched.c's attach_deaths gives it no REG_DEAD note after sched2. reorg's
mark_target_live_regs (resource.c) starts from those live sets and notes; when
find_dead_or_set_registers' budget (one conditional branch) runs out before the fall-through
path sets `$fp`, `$fp` stays live there and the slot must be annulled. GCC 2.95 has John Wehle's
change of 2 June 1999 (gcc/ChangeLog: "Only give FRAME_POINTER_REGNUM and
HARD_FRAME_POINTER_REGNUM special treatment if reload hasn't run or the frame pointer is
needed"). [frame_pointer_liveness.py](../../tools/compiler/transformers/frame_pointer_liveness.py)
adds `-frac2-frame-pointer-liveness`, which puts that condition, `! reload_completed ||
frame_pointer_needed`, on the five flow.c tests and attach_deaths. Checked against
gcc-core-2.95.tar.gz from ftp.gnu.org (flow.c 2276, 2965/2968, 3278/3281, 3740/3746, 3923/3926;
haifa-sched.c 4633/4636): with the condition substituted, the five functions equal 2.95's token
for token. The exceptions are an extra pair of parentheses and 2.95's ASM_OPERANDS case in
mark_used_regs, which belongs to another change and is not added. sched.c, also in the
ChangeLog entry, is not built for the r5900. Without the switch, stock and patched cc1 give
identical assembly for every one of the 8,628 game-compiler units of `src/` in the three
releases (144 SDK units use another compiler). Forced on in all of them, it changes none of
their 11,949 functions. Among the retained drafts, forced on, it changes the two witnesses
(`bnel` to `bne`, nothing else), func_002BA0E0 and func_L02_003FDDE8; in the last two, flow2
now deletes a dead set of `$fp` (insn_dead_p). A REG_DEAD note on an insn that reorg moves into
a delay slot is erased (emit_delay_sequence), so the option only matters where the last use of
`$fp` stays out of a slot.

func_002BA0E0 (1,472 bytes, 28 places in each of USA v1.01, PAL and v2.00) fills the 111-entry
callback table D_001F2340. After reload the table's address is in `$v0`, set by `addiu
$v0,$a1,%lo(D_001F2340)` from the register holding its `%hi`. Retail issues the callee saves
`sd $s0`, `$s1`, `$s3`..`$s7` right before the slot-24 store `sw $fp,0x60($v0)`; stock cc1 issues
all nine at the top of the function. In sched2 every slot store `(mem (plus $v0 C))` has an
output dependence on every save. init_alias_analysis (alias.c) seeds a few hard registers with a
base address: the argument registers, the stack, frame and argument pointers, and, as in GCC 2.95,
the static-chain register (`$v0`, STATIC_CHAIN_REGNUM) and the struct-value register (none on
MIPS: STRUCT_VALUE is 0). A seeded register keeps its base only while each set of it is relative
to itself, so record_set drops `$v0`'s at `$v0 = lo_sum ($a1, D_001F2340)`. find_base_term then
finds no base for the stores, and write_dependence_p reports a conflict with the `$sp` saves.
An unseeded hard register, `$v1` for one, takes the base of its first set (find_base_value), here
the symbol, which cannot alias a stack slot. GCC removed both seeds: Richard Henderson's change of
22 August 2000 (gcc-3.0 ChangeLog.4: "alias.c (init_alias_analysis): Do not register
struct_value_incoming_rtx or static_chain_rtx as pointing to stack memory.") reverses an addition
of October 1997 (ChangeLog.0) and is in gcc-2.95.3. A Pmode ADDRESS is the base the stack, frame and
argument pointers get, so the seed declared the static chain, which points into another
function's frame, a stack reference. [no_static_chain_base.py](../../tools/compiler/transformers/no_static_chain_base.py)
adds `-frac2-no-static-chain-base`, which leaves both seeds out. Checked against gcc-core-2.95 and
gcc-core-2.95.3 from ftp.gnu.org: their alias.c files differ only in the copyright line and these
nine lines (2.95 lines 1458-1466); gcc-3.0, 3.4.0 and 4.0.0 have neither seed (3.4 moves the other
seeds to init_alias_once's static_reg_base_value). This tree's init_alias_analysis equals 2.95's
token for token apart from 2.95's extra `! reg_overlap_mentioned_p` test on REG_EQUIV notes,
another change; with the switch it equals 2.95.3's apart from the same test and, in nested
functions only, one more line (below). The archive's compiler is dated 11 November 1999, before the
GCC change, so the switch is inferred from retail's schedule, not a recovered patch.

Neither GCC version gets a GNU C nested function right, where `$v0` arrives holding the parent's
frame address. In a nested body `x = a*b*c*a; *p = 5;` (x the parent's, reached through the chain)
called with `p == &x`, the store to x must come first. With the 2.95 seed (the default, and stock
cc1) the chain is a stack reference, which base_alias_check says cannot alias an argument, and
sched2 issues `sw $3,0($4)` (the `*p` store) before `sw $5,0($2)`: the bug GCC's change fixed.
Without the seed, as in 2.95.3, `$v0` takes the base of its first set, and record_set does not
follow the flow: if the same body then returns a local's address (`r = local; return r;`), the only
set of `$v0` is `addu $2,$sp,16`, every use of the incoming chain gets that stack base, and the two
stores swap again; 2.95.3 has the same code. So for nested functions the switch departs from pure
2.95.3: when `current_function_needs_context` is set it also sets `reg_seen` for the chain
register, so no set gives it a base, and stores through it conflict with every other store. That
puts both stores in source order. A function that takes no static chain is unaffected by the extra
line: `$v0` has no seed and takes the base of its first set, as in 2.95.3. The test fixture holds
both nested bodies (`store_twice`, `store_and_local`) with their store orders, and `bump`, whose
only change is that the chain stays in `$v0` instead of being copied to `$v1`.

Without the switch, stock cc1 (upstream's recipe) and patched cc1 give identical assembly for all
8,730 game-compiler units of `src/` in the three releases (12,091 functions; 144 SDK units use
another compiler). Forced on in every one of them, it changes only func_002BA0E0's unit. Forced on
for the 1,076 drafts in `nonmatching/` that compile (default flags, -G8, and with
`-frac2-frame-pointer-liveness`), it changes one: the port-only func_00283A58 (plain floats for VU0
code, 320 bytes for 152) has its loop rescheduled, with 80 differing words either way. Before the
match, the same sweep also changed both func_002BA0E0 drafts: the port-only one, in ascending slot
order, then matched with `-frac2-frame-pointer-liveness` and is now the unit; the older hill-climb
order of the near-miss draft stayed 0 of 28. Only `$v0` loses its seed, so outside nested
functions the switch matters only where the first set of `$v0` gives it a base and the stores
through it compete with stack accesses. The witness has a unit of its own, `src/game/002BA0E0.c`,
with both switches. With either alone it is 0 of 28 places in each release (1,476 bytes without
`-frac2-frame-pointer-liveness`, which deletes a dead `lui $fp`). Round 9 (below) describes
Lombyte's sce-991111b candidate 0060 the same way; it was swept enabled by default, before the
frame-pointer switch existed.

Patch 0057 enables `-mastra-split-trunc-slot`: split `truncdisi2` after reload and
before scheduling so its second shift can fill the return slot. `func_0012E8C8`
changes from 32 to retail's 28 bytes. Dedicated files prevent either option from
silently changing neighbouring definitions.

### Prototypes, lifetimes and varargs

- Preserve actual argument count and return width. A value-returning call defines
  `$v0` and can move the next constant to `$v1` (`func_00339F28`, `func_00343A30`).
  Do not invent a void return or an assembler-name alias to steer allocation.
  `func_L04_003FA7E0` is a larger witness: the current quadword block-move support
  closes its template copy, but the retained caller's incorrect `void` declarations
  still place a camera-timer store before the call-argument moves. Restoring the
  helpers' actual float, integer and pointer returns closes that last ordering
  difference. Its 4,516-byte body is shared by Barlow and Joba in both USA releases;
  it needs no new compiler patch, register pin or artificial dependency.
  Consuming callers support the scalar/particle contracts; the other factories
  explicitly move their saved object pointer to `$v0` after their initialization
  calls, rather than merely leaving an incidental result live.
- An existing reconstructed declaration is evidence to audit, not an oracle.
  `func_002AE730` writes its packed word through an output pointer; its last
  packing call also leaves that value in v0. Current RAC1 and 146 direct calls
  in each RAC2 release support an output-only interface: none consumes that
  residual result. Correcting the definition and caller declarations together
  preserves matching bytes. Do not infer a returned value solely from a register
  left live at the epilogue, or infer void solely because result paths differ.
  `func_002B60B0` is the same case: its pointer only stays in `$v0` from
  `func_002B5D28`. A `void` definition with the stores in parameter order gives the
  same bytes at all 23 places, and none of its 505 retail calls reads `$v0`. Its
  callers' allocation depends on it: a value-returning declaration moves the
  first load after the call from `$v0` to `$v1` (`func_L11_00420C88`,
  `func_L11_00424A60`).
- A body that ignores a formal does not prove a zero-argument API.
  `func_001261F0` retains the real 32-bit `sceGsSyncV` mode argument, supported
  by the public OpenGOAL interface and the game's zero-valued callers. The
  matched preview helper `func_00300048` similarly retains its observed unused
  object argument. Check callers or an independent interface before changing a
  canonical declaration, and never add a synthetic use of an unused formal.
  The packet builder `func_002B6480` similarly retains its unused mode word:
  the movie callback supplies zero, and the frame builders in all three releases
  supply one. Its definition and caller views now agree on pointer plus mode;
  the body does not invent a use of that argument.

- A 64-bit colour/result must keep its ABI width. `func_001175F0` forwards a long
  result; explicit 32-bit truncation adds two instructions.
- A colour constant's declared argument width selects its materialisation. Through
  an `unsigned long`/`long long` parameter, 0x80F0F0F0 becomes `ori`+`dsll`+`ori`;
  through `unsigned int` the same value is `lui`+`ori`. The icon colours of
  `func_L00_003781B0` and `func_L00_00378388` take the wider form (measured
  2026-10-25 with the game cc1 at `-O2 -G0`/`-G8`, scratch objects).
- Integer and FP arguments use separate register banks. Their declaration order
  can affect setup while preserving the measured ABI: `func_0030E700` and existing
  Barlow effect-helper declarations are witnesses. A float declared third among
  integers still travels in `$f12`; moving it before an integer is what puts the
  `lwc1` on the other side of the call (`func_L16_003E70E0`, `func_L02_003CCFE8`).
  Check the whole call site.
- Check the canonical helper and its live inputs before writing a prototype.
  An omitted FP argument or a float result consumed as an integer is an ABI
  error, even in a retained draft. A wrapper's current C signature can also be
  incomplete: inspect forwarded registers before discarding a caller argument.
  Already matching bytes can hide such a source defect: `func_L02_00329410`
  forwards an optional matrix in `$a2` to `func_00283098`, then returns the
  float result of `func_00283248`. Its former void/two-argument declarations
  left those registers live accidentally. Explicit matrix forwarding and a
  float return preserve the bytes while making the C contract accurate; the
  consumer declarations must agree too.
- A pointer live across a call can need a saved register and a larger frame.
  Creating it later, or keeping genuinely distinct guard and walk variables,
  can recover the live ranges (`func_L08_00328BB0`).
- Preserve a public upstream helper's `static __inline__`; omitting it may emit a
  real call (`func_00123C28`).
- This compiler is C89: declarations precede statements in their block. Put
  typedefs before externs using them. Do not name a typedef `TI`: it conflicts
  with a later `mode(TI)` attribute. `TI128` avoids the collision.

The unsigned widened postfix pattern is useful beyond a single counter. In
`func_L00_003B63D8`, load the 16-bit timer into an unsigned 32-bit local, retain
the old value while incrementing, then store the narrowed value back. This
preserves the retail comparison and wrap without the unwanted HImode mask.
Its query call also uses the documented bank-preserving argument interleaving;
the six integer/pointer and three FP arguments keep their order within each bank.

Pointer lifetime changes must preserve the actual C objects. The camera prefix
used there starts at `D_L00_001B8DC0`, with its position at zero and its three-row
basis at `+0x230`; subtracting `0x230` from a separately declared basis array
would form a pointer before that array. The inverse needs **four output rows**:
`func_00283698` reads three input rows but also writes an identity row at `+0x30`.
Its 64-byte output is required even though `func_00283098` reads only the first
three rows. This is distinct from `func_00283678`/`func_00283738`'s 48-byte operations.

Check each helper's footprint independently. `func_00283658` also reads 48 bytes
and writes 64, placing the fourth row in its return delay slot. `func_00283410`
writes 64 bytes; `func_00283788` reads 64 from each input and writes 64;
`func_002830C0` and `func_002AB6D8` consume all four matrix rows. Input size does
not establish output size, and adjacent local arrays do not form one C object.
Use a complete matrix, or a union for an independently measured stack reuse.

For `func_L06_00403130`, the matched renderer proves that the two UV addresses
are columns of one owning table. That view restores a reload lost with separate
extern arrays. Separating the real scale computation under the existing `-g`
profile then restores two division nops. The 1,504-byte draft still has setup and
branch-slot differences; neither a size tie nor an improved frame is a match.

The public-newlib `func_00131424` square-root wrapper supplies another ordinary
source remedy: its NaN classifier `func_001313C8` depends only on its argument's
bits and has no side effects, so a truthful `const` declaration preserves the
cached library mode across that call. Keep newlib's Sun permission notice.
The complete generated NaN constant pool still needs the strict linked build;
text equality alone does not qualify it.

The recipe installs its public `gcc/ginclude/*.h`. Here `va_start` uses
`__builtin_next_arg(last)`, the **stack arguments**, while some retail shims pass
the **register save area**: `sp+0x50` in a 0x80 frame with two named arguments, or
`sp+0x58` in a 0x90 frame with one. The area above named arguments is
`(8 - named_count) * 8` bytes. Witnesses: `src/core/0011E0D8.c`, `func_00115CF0`,
`func_00115D48`, `func_00115DA8`. Do not use this to explain an ordinary -O0 shim.

### Habits of large bodies

Observations from eleven passes each over two unmatched bodies,
`func_L11_0042F018` (10,312 bytes) and `func_L04_002E7C08` (14,304 bytes), whose
records and block maps are in `nonmatching/levels/`
([#288](https://github.com/OpenRAC/rac2-decomp/pull/288)). They are source-shape
observations, not qualified rules:

- The frame size follows from allocation: locals, the 8-byte GPR slots, then the
  FPR slots, each block rounded to 16. A body that keeps one more value across a
  call gets a bigger frame; reproduce the prologue by keeping retail's values live,
  not by choosing a size.
- Local allocation ranks values by `QTY_CMP_PRI`, `floor_log2(refs) * refs * size /
  live length`, ties by pseudo number: the shortest dense ranges are placed first.
- Retail's split `%hi`/`%lo` address comes from casting the global's name to a
  struct (`((Actor *)D_00189E20)->field`): one `lui` kept in a callee-saved
  register and an `addiu %lo` at each use. A pointer variable gives the same shape;
  a per-case `p = &D` gave 264 `lui`. The anchor's register moves when the body
  around it changes (four extra calls moved it).
- A value passed as a call's argument does not live across that call, which keeps
  it in `$f0` rather than `$f20`. Splitting a multi-definition local gives each part
  its own live range.
- Reload can give a call result inside a compound expression another variable's
  stack slot: `f = func(0.2f, 0.9f) * 0.2f` multiplied the reloaded value, two
  statements multiplied `$f0`.
- `if (cond) goto Lelse;` lays the body out as the fall-through. `if (a || b)` as
  one condition got its second test inverted; two separate `if` blocks gave
  retail's two branch-likelys to the same block.
- `idx--` gives retail's `addiu` plus `movn` where `idx = -1` materializes a
  constant; an unsigned comparison turns that `-1` into a separate `lui`/`ori`.
- Check struct offsets against retail rather than inheriting them: in these
  bodies padding was four bytes out from 0xAA0 and two from 0x1492.
- `__builtin_expect` does nothing on MIPS here (the expect optab is empty); a
  branch-likely comes only from reorg's heuristics.
- Switch bodies are emitted in source order and jump-table gaps take the default
  label, so the source switch needs a default.

## Symbols, addresses and small data

Use catalogue function identities, resident `D_XXXXXXXX` within the resident region
described in [AGENTS.md](../../AGENTS.md#naming-in-c), and level `D_LNN_XXXXXXXX`
data names. When a callee/data pairing changes by
program, use `ref_LNN_XXXXXXXX_kk`. Zero-padding a level address is not enough to
identify its canonical function. See [levels.md](levels.md).

GP and overlay base depend on the release. USA v1.01 uses GP `0x001AEFF0`; take
other releases' constants from the selected layout, not a copied literal.

An explicitly measured GP address view can use the existing `SDATA` macro:
`extern float tuning[] SDATA(tuning);`. Keep an unknown owner incomplete, or use
its independently established full type; never shorten an array for a `-G` threshold.
`tools/sdata_aliases.py` recognizes only the reserved `__gp` spelling emitted by
that macro, supplies its assembler small-address metadata before the first `.ent`,
and binds it to the same canonical storage. The metadata size is an address-class
selector, not the canonical object's extent. Incomplete arrays emit no `.extern`,
so references also identify this explicit request. Ordinary assembly and operands
are unchanged; conflicting bindings or alias storage definitions fail closed.

This adapts RAC1's explicit-alias route, without its broader delay-slot pass.
Both C compiler chains and the allocation diagnostic apply it before assembly;
its contents participate in the C object cache key. Authored 14-/28-byte controls
retain unknown canonical ELF extents, read every byte from the same full storage,
and preserve GP relocations and offsets. Link controls cover signed displacement
edges and reject addresses outside the GP window. A same-prefix decoy is not an
address source: binding is by canonical symbol, never by matching a scalar prefix.
These controls qualify the address view, not any game function; every consumer
still needs all carrying releases' placement checks and strict linked builds.

The backend's symbol model, declaration size, -G threshold and assembler mode all
matter; neither `sda` nor `nosda` is a universal opcode selector:

- At -G0 a macro symbol operand may expand to `lui` plus low-half access in ordinary
  flow, or one GP instruction in a `.set nomacro` delay slot.
- `sda` can restore the backend's one-instruction model. At -G8, a suitable known
  size and emitted `.extern NAME,size` enable GP addressing. An incomplete array
  prevented it in `func_00132DF0`; a sized two-element array provided the control.
  The declared size must fit the `-G` threshold, not merely exist: `extern float D[16]`
  (64 bytes) falls back to `lui`/`addiu` under `-G8`, while a two-element array takes
  `addiu $r,$gp,offset` (`func_L00_003C8608`). This describes a code-generation
  effect, not permission to understate an object's extent. Declare its measured
  size or leave it incomplete; never index outside a fabricated small array.
- `nosda` can preserve an absolute access but can also add a temporary or hoist
  the address across a call. It is not neutral at -G8.
- `-mno-split-addresses` changes pseudos, not all GP loads uniformly. An FP repair
  can permute the prologue. Witnesses include `func_L00_003959C0`,
  `func_L05_00397F48` and `func_L01_00416A50`.
- A body using both GP and absolute forms needs measured declarations/bindings,
  not a guessed global rule. Split-address uses can keep `%hi` in a saved register
  and add `%lo` at each use (`src/levels/shared/L00_002C2DE8.c`).
  In retained `func_L01_003B5878` at `-G8`, one `MACRO_ADDR` declaration emits
  an ordinary absolute load and a GP delay-slot load of the same frame counter.
  Both retail addresses independently resolve to `0x001B2088` in both USA
  releases. An additional C declaration with the same assembler name and
  explicit `sda` instead forces both uses to GP. Adding `MACRO_ADDR` while
  retaining that alias is object-neutral; removing the alias restores the
  measured mix. Prefer a single truthful declaration before inventing bindings.
  This fixes those accesses, not the full caller: it remains nonmatching.
- Base evaluation and pointer construction can have different orders. In
  `func_002980D0`, forming both bases first and then the pointers preserves both.

An `sda` attribute on an incomplete array (`extern int D[] __attribute__((sda));`, read as
`D[0]`) at `-G0` is the practical way to get retail's tied absolute macro form
(`lui $r,%hi; lw $r,%lo($r)` with the destination as the address temporary, `lui $at; sw`
for stores) without `-mno-split-addresses`; the sized `sda` spelling of the same address
gives the GP form, and two names for one address are how retail's mixed reads (absolute)
and writes ($gp) of `D_001B1DD4`, `D_001A7478` and `D_001B1B00` are written. The same
incomplete-array table base in a loop keeps cc1 from hoisting its `%hi` (`func_L01_003CBCD8`).
A macro load can be moved into a call's delay slot, where the assembler turns it into the
$gp form; that is not a defect of the declaration. Witnesses: `func_002C8610`,
`func_L00_003A0C00` (the callee reached through `ref_L00_003A0C00_00` in the levels where the
catalogue splits it), `func_L00_00329520`, `func_L01_003CBCD8`. A 20-byte menu table read
through $gp (`func_002D16C8`) needs the declared size to fit the threshold, so its unit uses
`-G32 -Wa,-G32`; a TImode copy whose address carries an offset (`lq $v0,0x10($v0)`) is the
default profile, not qcopy (`func_L11_00448AA8`).

Odd-address byte globals are valid absolute bindings (`0x001A7B94/95`,
`0x001A7BB2/B3`); there is no universal four-byte alignment requirement. A low half
with bit 15 set also needs the correct signed-low-half relocation. Compare bound
addresses and words, not just textual `lui` operands.

Keep external object sizes truthful. A 16-byte vector read needs a vector-sized
declaration; a known 15-byte label must not be declared as eight bytes to make it
fit `-G8`. Dedicated files for `func_L16_00411B40`, `func_L16_00411900` and
`func_00339078` use the standard per-file `-G16 -Wa,-G16` profile. Both thresholds
matter because the GNU assembler is invoked separately from cc1. With the existing
copy profiles where needed, these declarations preserve the earlier instruction
bytes and relocations and pass every carrying release's placement checks.
The complete strict builds remain the acceptance gate. This is a reconstruction
profile, not evidence of the shipping compiler's flags.

A small-data object read at a nonzero offset is the other tied form. cc1 does not split it (the
symbol carries `SYMBOL_REF_FLAG`), and `simple_memory_operand` rejects the offset, so the insn has
length 2: it never fills a slot, and the assembler expands it to `lui $r; lw $r,lo($r)` or
`lui $at; sw`. Declare the block `extern int D[] __attribute__((sda));` at its real start and read
`D[1]`, or use an incomplete struct array and its fields. `func_L00_004266E8` (`D_001A7BA0[1]`),
`func_0029D830` (a three-word block at `D_001B1A50`), retained `func_002FF0D8` and
`func_L00_0036F488`. A bare `D[0]` has length 1 and does fill slots.

The same size rule applies beyond vectors. The particle emitters
`func_L18_003FCD70` and `func_L18_003FCC48` declare their measured 24-byte
settings records and use `-G32 -Wa,-G32`. `func_L00_00396078` keeps its complete
four-vector, 64-byte template with `-G64 -Wa,-G64`. Isolate these profiles per
file; do not shorten an object or raise the global threshold to obtain GP loads.

## Quadword copies

### Address formation and grouped lowering

A `mode(TI)` integer assignment reaches `lq`/`sq`; an aggregate may instead use
scalar/unaligned transfers or `memcpy`. `find_best_addr` prefers a register plus
small constant over a register at equal address cost; reload accepts TImode
displacements in `[-32768, 32752]`. An intended `addiu; sq 0(reg)` therefore folds
into a displaced store. This is not evidence of handwritten assembly.

An out-of-range displacement, memory-loaded pointer, loop-carried pointer or join
with distinct incoming values can retain a register address. An artificial volatile
pointer adds a stack round trip and is not a production remedy. Never change the
real offset or add fake barriers just to force that shape.

[qcopy_pattern.py](../../tools/compiler/transformers/qcopy_pattern.py) implements the
default-off, per-file `-frac2-qcopy`: aligned TImode memory-to-memory assignments,
register addresses, grouped lq/sq and a declared `$v0` scratch. Memory flags/alias
sets survive; it adds no memory barrier. The MD length is two instructions. Scalar
moves, zero stores and explicitly unaligned accesses retain ordinary lowering.
`-fno-rac2-qcopy` restores the default.

Witnesses: `func_L20_0039E158` (140 bytes), `func_L20_0039F210` (32), one place
each. The latter also needs `-fno-schedule-insns` and measured field-store order.
Restricting every TImode address to a register gave sizes without correct allocation.
The ordinary folded-copy witness `func_L00_00395240` stays on its default profile.

### Scheduling around copies

[qcopy_barrier.py](../../tools/compiler/transformers/qcopy_barrier.py) adds
`-frac2-qcopy-barrier`, effective only with qcopy. Its TImode memory-to-memory SET
plus `(clobber (reg:TI 2))` gets both schedulers' volatile-copy dependences, cost 1
and unit classification. Operands, allocation inputs and memory flags stay unchanged;
`-fno-rac2-qcopy-barrier` disables it.

The original twelve witnesses total 3,616 bytes at 59 places: `func_002B5E48`,
`func_002EE988`, `func_L02_003DB158`, `func_L02_003D47B0`, `func_L02_00401BF8`,
`func_L12_00413CE0`, `func_L23_00418650`, `func_L23_003C01F8`,
`func_L23_00418DC0`, `func_L23_004256F0`, `func_L23_0041D0A0`,
`func_L26_003D4930`. Named destination pointers and the point where the second
copy's address is taken remain source requirements in two cases.

`func_L20_0039C448` (248 bytes) and `func_L20_0043D470` (100 bytes), one place each
in level 20, are exact together in `L20_0039C448-qcopy.c` with qcopy and the barrier
([#291](https://github.com/OpenRAC/rac2-decomp/pull/291)). Qcopy alone fixed the
first body's load but left its saves in this cc1's ascending order where retail has
`sd $s0; sd $s2; sd $s1`; the barrier fixed both. In the second body, qcopy also
produced retail's float register order (8.0f in `$f1`, 2.5f in `$f0`), which its
record had blamed on the allocator itself: the copy's address registers change the
allocator's inputs. A residue that looks like a compiler difference can be the
profile's. Of level 20's 3,978 functions, 359 have retail's `addiu` plus
zero-displacement `lq`/`sq` shape.

This models the schedulers, not every optimizer effect of inline assembly. Incoming
links retain producer latencies; interblock motion sees a store; jump2 can remove a
move that a volatile operation retains. `func_002B50E0` retained three argument-move
differences. Artificial clobbers and register pins remain forbidden; reviewed
shared helpers and public runtime primitives follow the source-method rules above.

24 October 2026: the barrier closed five retained near misses whose notes had named the
missing inline-asm copy barrier: `func_00270EA8` (56 bytes), `func_00270E30` (116),
`func_00302A20` (100), `func_003353C8` (88) and `func_002AD6F0` (196), in qualified
qcopy/barrier units. Before the barrier they were one restore or one copy-address
allocation away; after it each is 28/28 in USA v1.01, PAL and USA v2.00. This is further
evidence for the dependence model, not a blanket claim that every copy near miss closes.

The same profile closed four more near misses: `func_002BB838` (236 bytes), `func_00313678`
(84), and the boot-only G8 twins `func_00304AD0` and `func_00307298` (148 each; 1/1 in both
USA releases, no PAL row). For `func_00313678` the copy source had to stay in a `char *`
local while the call passed the same pointer; qcopy alone folded the load.

The retained `func_00335370` exposes another latency gap: sched2 moves an independent
return-address restore between a field load and address formation. Correct copy size
alone did not qualify its epilogue; a repaired tail with scheduling disabled changed
the prologue instead. Its measured reopening conditions remain in the blocker notes.

Stack layout is separate: `func_L00_0032A1A8` needs one `char buf[32]` for `sp+0`
and `sp+0x10`; two separate locals reverse their placement.

## Quadword zero stores

### Default fold and live return values

[fold_zero_ti_store.py](../../tools/compiler/transformers/fold_zero_ti_store.py) folds a
materialized zero to `sq $zero,0(reg)` only for a bare register address and no other
live reader. Its bounded search stops at calls/jumps/labels and looks back at most
twelve instructions. Shared zeros feeding several stores keep their register.
Displaced stores keep por and register-source sq even when the zero dies there.

The fold runs after reload **before sched2**, through
`MACHINE_DEPENDENT_REORG_AFTER_RELOAD`. Running it later changes `func_002E5FE0`'s
loop store order. Positive controls: `func_00282C88` (8 bytes), `func_002E5FE0`
(168). Negative control: three-store family `41eb487e64fb6b76`. Displaced-store
witnesses: `func_L20_0044AB68` (204), `func_L20_00443908` (264),
`func_L00_003ACC88` (112 at 27 places).

[fold_zero_ti_return_value.py](../../tools/compiler/transformers/fold_zero_ti_return_value.py)
admits exactly one reconstructible function-value USE of that same
`REG_FUNCTION_VALUE_P` register, without an intervening call/jump. The store fold
and conversion of USE back into an explicit zero return SET form one
`validate_change`/`apply_change_group` transaction. If either is unrecognized,
abandon both. Other readers still prevent the fold.

Ignoring USE without restoring the zero return silently returns a preceding call's
value. Re-admitting J globally in `movti_internal` also regresses shared-register
stores by letting CSE substitute zero everywhere. The retired
`allow_zero_ti_store.patch` must not be restored. These are correctness conditions,
not harmless one-word differences.

### Reload registers for quadword values

[ti_one_gpr.py](../../tools/compiler/transformers/ti_one_gpr.py) is unconditional. The
sce-991111b stack makes `HARD_REGNO_NREGS` 1 for TImode in a general register, but
`CLASS_MAX_NREGS` still answered 16/`UNITS_PER_WORD` = 2 for every non-FP class.
Reload sizes its needs and its reload registers by the latter, so each TImode reload
was a two-register group: a reloaded zero for `sq` (`por $rX,$0,$0`) made reload
spill pairs, and `allocate_reload_reg`'s round-robin from `last_spill_reg + 1` then
skipped the second register of each pair or landed on it. The transformer answers 1
for TImode in `GR_REGS` and the MIPS16 subsets before it, so the two macros agree;
FP_REGS and the hi/lo classes keep their counts.

Witnesses: `func_L23_002C38B0`'s four reloaded quadword zeros are `$a0`, `$v0`,
`$a0`, `$v0` in retail and come out so with the fix, while the pair model gave `$v1`
where retail has `$a0`. Ten more unmatched retail functions clear with
`por $a0,$0,$0`, among them `func_002ABBB8` and `func_L00_0038ADD0` (where `$v0`
holds a call's value and `$v1` a constant across the clear). Every matched function
of the 28 programs compiles to the same bytes with and without it, so it changes only
code that had no matching C yet. A non-quadword pseudo can move too, since regclass
and local-alloc read the same macro. [tests/test_ti_one_gpr.py](../../tests/test_ti_one_gpr.py)
checks authored controls: five reloaded zeros between calls rotate `$v1`, `$v0`,
`$v1`, `$v0`, `$v1` (the pair model: `$a1`, `$v0`, ...), a shared stack zero beside a
live call value takes `$v1` (pair model: `$a1`), and a lone zero keeps `$v0`.

### Inheritance into a register the insn's pseudos hold

[reload_reg_used_guard.py](../../tools/compiler/transformers/reload_reg_used_guard.py) is
unconditional. The archive's `reload_reg_free_for_value_p` returns 0 for a register in
`reload_reg_used`, which `choose_reload_regs` fills with every register outside the insn's
spill set (`IOR_COMPL_HARD_REG_SET (reload_reg_used, chain->used_spill_regs)`). Patch 0047,
the GCC 2.95.2 reload1.c in Lombyte's stack, drops that test, so reload could inherit a
spilled pseudo's value into a hard register that a pseudo of the same insn holds. The
transformer restores that exclusion without changing the rest of 0047.

The excluded set is a snapshot taken immediately after the spill-set complement.
The mutable `reload_reg_used` also accumulates `RELOAD_OTHER` marks later in the
instruction: testing those marks at entry rejects a reload's own register before
the existing lifetime loop can skip `i == reloadnum`. The immutable snapshot
rejects genuinely unavailable registers while that loop continues to reject
overlapping reloads. This removes the intermediate color spills in the trail,
quad and grid renderers without deleting the count-reload safeguard below.

The visible case is a count in a stack slot, incremented and then compared: the increment's
output reload leaves the value in `$v0`, and local-alloc gives the `slt` result `$v0` too.
Without the test the compare inherits it (`addiu $v0,$v0,1; sw $v0,n; slti $v0,$v0,128`);
with it the compare reloads the slot (`sw $v0,n; lw $v1,n; slti $v0,$v1,128`), and the
round-robin reload registers after it move on by one, as retail's do.

Historical qualification: `func_L00_003C5B88` (1,804 bytes) and its 22 copies in other levels were exact
under it: the count reload after `n++` and the index reloads in `$a0` were their only
differences. Every matched function of the 28 programs compiles to the same bytes with and
without it (`tools/build.py all --strict`, 28 of 28). Of 625 profiled near misses in
`nonmatching/`, 57 compile differently; 9 of their functions come closer to retail,
3 move further and the rest are unchanged. [tests/test_reload_reg_used_guard.py](../../tests/test_reload_reg_used_guard.py)
checks the anchors and the two original object controls. A native harness additionally
compiles the actual prepared GCC predicate and covers self-inheritance, non-spill
exclusions, other reload lifetimes, equal read-only inputs, multi-register overlaps
and reset at the next instruction. The old mutable-set guard fails the self case;
removing the guard fails the unavailable-register case. These are negative controls,
not substitutes for linked game builds.

### Clear scheduling and materialized stack zeros

| Option | Effect | Limit |
| --- | --- | --- |
| -frac2-zero-ti-barrier | Selected isolated zero stores get a scheduling barrier | The pre-reload heuristic also selects some displaced clears; it is not a recovered macro detector |
| -frac2-zero-ti-por | Suppress zero folding at bare 0($sp) | Other register addresses still fold; mixed forms at the same address cannot be distinguished per file |

[zero_ti_store_barrier.py](../../tools/compiler/transformers/zero_ti_store_barrier.py)
selects before reload an isolated const-zero TImode store between calls/labels/jumps;
shared zeros keep normal C lowering. After reload it selects an architectural-zero
TImode store. Lowering ready cost alone did not reproduce the dependences.
`func_L00_003BFF68` matches 12/12 with the switch and 0/12 without it.

[zero_ti_por.py](../../tools/compiler/transformers/zero_ti_por.py) is a statement about
a unit's stack clears, not a detector. The control-flow-aware retail census found
183 register-fed zero stores in 153 functions, all at `0($sp)`, but also 396
architectural-zero stores in 263 functions, including 82 at `0($sp)`. The address
alone cannot decide the form a particular function needs.

Witnesses include `func_L02_003DB200` (236 bytes), `func_L02_00423520` (788),
`func_L23_00422798` (532), `func_L02_003DBA70` (252), `func_L23_00429DC8` (560):
2,368 bytes at five places. The first needs a scalar, rather than an incomplete
array declaration, for its absolute load. The last also needs measured payload,
store and halfword ordering and its closing loop's independent counter.
The fno forms restore defaults. A nonzero offset, computed stack address or mixed
forms at the same address remains distinct: `func_L07_003E4BD0` mixes both at
`0($sp)`, and `func_L02_003E7370` exposes the displaced-clear scheduler heuristic.
Combining both switches affects sched1/sched2 differently and needs its own proof.

## Control flow and delay slots

### Useful C shapes

- A flag set to 1 only by a test in a block of its own is `flag = 0; ... if (test) flag = 1;`. jump.c makes a
  conditional move from it and puts the 1 in a fresh pseudo set once, which loop.c hoists and cse reuses, so retail
  shows `daddu a2,s7` / `movn a2,zero,v0` (`func_L00_00323958`, near miss) or `addiu s5,1` / `daddu s1,s5` (`func_003248A8`, near miss).
  `flag = 1; if (other) flag = 0;` has the constant in the same block and combine folds it to `sltiu`.
- A loop index read after the loop keeps its loop.c rewrite honest: `for (j = 0; j < 8; j++) h[j] = h[j * 2];
  func(h + j, data + 32, n);` has the counter reversed (`addiu a2,7` / `bgez a2`), two pointers reduced, and the final
  value of `h + j` computed after the loop as `addiu a0,a3,0x10`, while the plain `data + 32` is hoisted before it by PRE
  (`func_002934F8`). If retail recomputes a pointer it just walked, look for the index in the call.
- A register copy of a global's load that appears near a branch, with no variable to explain it, is PRE's reaching
  copy: read the global inline at every use rather than through a local (`func_003248A8`).
- Read branch direction and operand width: signed countdowns and unsigned increment
  loops need not share a layout. A switch can retain branches that if/else folds
  into sltu/xori/conditional moves (`func_L18_002E4090`).
- A single final return after a guarded body can preserve the saved-pointer move
  (`func_L00_00338D28`). An early null return changes the exit structure.
- A named threshold can retain addiu+slt where a literal becomes slti:
  `func_L00_00410840` needs this at its lower thresholds, not the highest test.
- A chain of `||` comparisons against adjacent constants is combined into a
  range test: `st == 0xFE || st == 0xFD || st == 3` becomes
  `(st + 3) & 0xFF < 2` plus one compare. A right-nested spelling
  `st == 0xFE || (st == 0xFD || st == 3)` keeps the three separate compares in
  source order (measured in `func_L08_0042F440`/`0042FAC0`, 544-byte twins).
- A copy before a loop that gcse's cprop keeps deleting can come from cse2: read the global inside the loop, loop.c
  hoists the `la`, and cse2 following `-fcse-skip-blocks` around the preceding `if` turns it into a copy of the earlier
  pseudo (`func_L00_00376600`, `daddu $fp,$s0`). The source of the copy can then share its register with a later local.
- A constant used in another basic block than its set stays in a body after a `continue`, because loop.c will not
  move a cross-block set when `maybe_never` holds: `tint = 0xF0F0B0` early in the body (`func_L00_00376600`).
- `addiu v1,s0,1 / daddu s3,v1 / slt v1,v1,a0` is gcse PRE's reaching copy: write `i + 1` at each use and `i++`
  in the loop, with no variable for it. The index register can then be reused for the record pointer
  (`func_002E3BD8`, `func_002E3998`).
- `sll 3 / srl 3 / addiu 0xF / srl 4 / sll 4` is a plain VLA of bytes, `u8 frame[count]`: bits to bytes, then
  rounding (`func_002E3BD8`).
- A body with no loop.c work (constants unhoisted, counter neither reversed nor eliminated) matches row for row
  when the loop is written with labels, which leave no loop notes (`func_00329488`, near miss: the alignment nop
  shows retail did have a loop note, so a real loop rejected as invalid is still possible).
- A value `r` from `if (a || (b && c)) r = 1; else r = 0;` or a helper with `return 1; return 0;` reads
  `beqz x / r = 0 / r = 1 / beqz r` in retail: reorg steals `r = 0` into each branch slot and the else goes
  (`func_L00_002D5EB8`, near miss). Flag sets inside a switch or a call stay out of r's life this way.
- Under `-g` a line label before a division costs the two-word floor. Statements on one source line share a
  label, so `bb = cos(x); D = aa / bb;` written on one line keeps the locals with no padding, where putting the division
  in the call's statement changes allocation (`func_L00_00429568`).
- A branch label on those nops when the division follows a branch group needs `-frac2-hazard-labels`: without it
  gas moves the label behind the padding (`func_L00_00429568`).
- `i + 1` written at each use also stops PRE from keeping `(i + 1) << 2`, since each shift then has its own
  operand pseudo; `i << 2` for the same loop is still kept (`func_L00_00429568`).
- `x = load; if (flag) x = 0.0f;` differs from a ternary in branch polarity and
  likely slots (`func_L00_0042A460`). Store order affects allocation, but there is
  no universal reversal or permutation rule.
- A delay-slot store runs **before** the callee. Put the source write before the
  call (`D_L00_001B0CA0 = obj` in `func_L00_004005B0`).
- **All branch-likely forms execute their slot when taken and annul it when not
  taken**, including beql/bnel and bc1tl/bc1fl. Earlier opposite statements were
  wrong. A jal slot also executes before control enters its callee.
- Loop heads/jump tables can receive eight-byte `.p2align 3`, ordinary merge labels
  four-byte alignment. Preserve genuine structure; an artificial empty loop is
  not an acceptable alignment device.
- Initializing a counter after its guards, retaining real guard/walk variables,
  a found-block break instead of return, or indexing rather than pointer walking
  can reproduce a specific loop (`func_002EE6E0`, `func_002ED368`). Duplicating a
  genuine tail can preserve another layout (`func_00116300`). Stop unchanged
  retries under AGENTS.md rather than treating these examples as universal rules.

One measured zero-valued guard uses `x & ~x` in a different block from the test:
this old front end leaves that expression for combine, after GCSE, so GCSE does
not propagate a constant zero into the loop. Same-block CSE folds it earlier.
The observations on `func_L20_0039E0A0`, `func_L20_0039DBC8`,
`func_L20_00440398` and `func_L20_0044AC38` describe pass ordering, not permission
to add a fictitious guard just to prevent optimization.

Four shapes from `func_L01_003B9798`, `func_L00_003E8A98` and the near misses
`func_L20_004441D8` and `func_L00_003C8A90`:

- A retail loop with no hoisted constants that still has its alignment nop is a real
  loop entered in the middle: `goto test; do { ...; test: ...; } while (...);`. The loop
  note stays, and loop.c refuses to hoist because of the outside jump. A loop written
  only with labels loses the nop and the loop weight on its registers.
- A call in two arms merges when something other than a call ends each arm at flow:
  flow puts `(use 0)` after a call that ends a block, and jump2 can't match it to the
  other arm's jump. A real following statement in both arms is the usual fix; the two
  `func_002A7750` arms of `func_L01_003B9798` carry the sound check.
- Spill slots go up with pseudo number, and gcse reaching registers follow by hash
  bucket. Raising a parameter's pseudo with a late `unsigned char *object = arg;` or
  naming an address (`first = attachments[0]; dst = first;`) moves its slot or gives
  the reaching register retail's reference count. A pointer loop has fewer insns at
  gcse than an indexed one, which is an honest way to change the bucket count.
- A byte table that is a field of a larger object adds base first (`T.flags[i]`, retail
  `addu base, index`); a plain array adds index first.

### gcse: every store kills every load

[gcse_store_kills_loads.py](../../tools/compiler/transformers/gcse_store_kills_loads.py) is
unconditional: it is the real compiler's memory model, not an option. This Cygnus tree's gcse
keeps a list of each block's stores and asks alias analysis (`mems_conflict_for_gcse_p`,
`true_dependence`) whether a store kills a load, so a load of a global survives stores to other
globals and to other offsets of the same record and is reused from a register. GCC 2.95.3's
gcse only records that a block stores to memory (`mem_set_in_block`, `mem_first_set`,
`mem_last_set`), so any store kills every load, and retail reloads after every store. The
transformer makes `mems_conflict_for_gcse_p` report a conflict for every memory destination,
which is what `mem_set_in_block` amounts to; it is the one place where gcse's availability,
anticipation, transparency and store motion decide whether a store kills a load. Calls
already killed every load.

Retail evidence: `func_L19_002C44F8`'s inlined statistics updates load `D_001A7390` and
`D_001A79F0` again after every store to a record (3,879 to 3,901 of 3,956 opcodes in place
under 2.95's model). `func_L00_002CB3A8` (26,432 bytes/11 places) reloads the hero fields
0x2294 after the 0x1239 byte store (on the store's path only, PRE's insertion), 0x31C after
0x1D0, 0x34E after 0x1EE and 0x1B4 after 0xC20, which no access spelling gets from alias
analysis (26,404 to 26,428 bytes). `func_L19_002CAAB0` (19,192 bytes) reaches 4,798 of 4,798
instructions with registers. `-dG` dumps and an instrumented cc1 place the surviving loads in
gcse's availability decisions. Of every matched function in the 28 programs only
`func_L00_00310048` (27 places) compiled differently; its C had been shaped around alias
analysis and matches as a plain `for (p = start; p < end; p += 256)` loop.
The decider family (`func_L04_002EDBC8`, `func_L08_002D90C8`, `func_L09_002C9738`,
`func_L19_002CAAB0`) had read case 0x32's 0x1B4 through a `char *hb` copy of the hero
pointer to force retail's reload; under this model it reads the field directly and matches.
[tests/test_gcse_store_kills_loads.py](../../tests/test_gcse_store_kills_loads.py) checks the
transformer and authored controls: a global is loaded again after stores to another record,
reused when no store intervenes, and loaded again after a call.

### reorg: a division guard ends the delay-slot search

[trap_delay_barrier.py](../../tools/compiler/transformers/trap_delay_barrier.py) is
unconditional: it is the real compiler's delay-slot rule, not an option. `fill_simple_delay_slots`
(reorg.c) fills a call's slot by scanning backward from the call for an independent insn, and
stops at a label, a jump or an insn that already holds a slot (`stop_search_p`). On the R5900 an
integer division is preceded by its divide-by-zero guard, a `trap_if` insn
(`beql $rN,$zero,1f; break 7`), and this Cygnus tree lets the scan pass it, so an argument setup
above the guard moves into the call's slot. Retail's compiler stops there, as at a jump; the
transformer makes the scan end at a `TRAP_IF` insn.

Retail evidence: 68 calls in the 28 programs keep a `nop` slot although an independent argument
setup (`li`/`move`/`addiu` into `$a0`-`$t3`, its register untouched up to the call) stands above
a division guard in the call's block; this tree's search would have moved it into the slot. To
see one, open the disassembly of level 0 (`build/00_aranos_tutorial/asm/52830.s`) at
0x002A4448: `addiu $a0,$zero,0x755D` sits at 0x002A4424, just above the `beql $s0,$zero` /
`break 0,7` guard, and `jal f_002F9E78` keeps its `nop` (0x00354924's `li $a0,0x2E0C` is the
same; the code repeats in every level). The census looks for that shape: a `jal` with a `nop`
slot, a `break 7` earlier in its block, and above the guard an argument-register setup that
nothing after it reads or writes. `func_L00_002CB3A8` (26,432 bytes/11 places) shows the
effect on a whole block: case 0x40 calls `func_L00_002D2168` twice after `(n * k / m + c) % n`;
retail sets `li $a0,2`/`li $a0,3` in the preceding `beq` slot (fill_eager_delay_slots) and
leaves both `jal` slots empty, where this tree filled the `jal` slots first and the `beq` took
an insn from its target (12 instructions). `func_L12_002CF7B0` and `func_L11_002DE9E0`, members
of that family, match with the barrier; of every other matched function in the 28 programs none
compiled differently. [tests/test_trap_delay_barrier.py](../../tests/test_trap_delay_barrier.py)
checks the transformer and authored controls: an argument set above a guard stays there and the
call keeps an empty slot, and without a division the call's slot is filled as before.

### reorg: a division guard ends the redundant-insn search

[trap_redundant_barrier.py](../../tools/compiler/transformers/trap_redundant_barrier.py) is
unconditional: like the barrier above, it is the real compiler's rule, not an option, and no
file needs a switch for it. It is that barrier's companion for reorg's other backward search. When
`fill_slots_from_thread` takes an insn from a branch's target for the slot, it first asks
`redundant_insn` whether an identical insn on the branch's path already computed the value; if
so it drops the insn and branches past it instead of copying it. This tree's search passes a
division guard (`trap_if`); retail's does not, so a load above a guard is never taken as the
earlier copy of the target's load. The transformer ends the first scan of `redundant_insn`,
finding nothing, at a `TRAP_IF` insn.

Retail evidence: `func_L00_002C2DE8` (708 bytes, 27 places) tests a frame counter as
`clock % 3`, then `clock % 5`. The `bnez` over the first block, taken while `$a0` still holds the
counter read above the `% 3` guard, has the target's reload `lw $a0,clock($gp)` in its slot and
branches to the `li $v0,5` after it; this tree dropped the reload, stole the `li` and branched a
word further (3 words). A census of the 28 programs finds 331 branches whose target starts just
past a reload of the value the register already holds (reorg dropped it as redundant), none of
them with a division guard between the earlier load and the branch; and the converse, a slot
holding such a reload across a guard with no store in between, only in this function's 27
placements. A second witness is a register restore: `func_L18_002C4000` (496 bytes, 3 places)
ends with a `% 6` test whose `beqz` goes to the epilogue's `ld $s0` in retail; this tree took the
restore already in an earlier `bne` slot as redundant and branched one word further. M10's draft
(26 October 2026) differed only there and matches 3/3 in us, pal and us2 with the barrier. Of
every matched function in `tools/build.py all --strict`, none compiled differently.
[tests/test_trap_redundant_barrier.py](../../tests/test_trap_redundant_barrier.py)
checks the transformer and authored controls: across a guard the reload fills the slot, and
without a division the redundant reload is still dropped.

A volatile asm ends the same scan. `func_0030E8A8` (1,052 bytes, 28 places) has a `bc1f` to the
epilogue past `ld $s0` with that restore in its slot, then a `qcopy` and a `b` to the epilogue.
Retail's `b` lands on the restore; this tree took the slot's copy as redundant across the asm and
branched one word further, the last word of the function. In the 28 retail programs, 30 such
shapes (a branch slot holding a `$sp` restore, then `lq`/`sq`, then a `b` to that restore or
the word after it) land on the restore and none past it, including `func_L22_003F5580`. With the
rule, none of the 5,846 units under `src/` compiles differently and `func_0030E8A8` is 28/28 in
both USA releases. The search stops at volatile asm alone: a plain store in that place keeps
the dropped restore, which the test's `stored` control checks.

### reorg: a volatile store stays marked

[sticky_volatile_sets.py](../../tools/compiler/transformers/sticky_volatile_sets.py) is the
default: it is the real compiler's rule, so no file needs a switch for it, and
`-fno-rac2-sticky-volatile-sets` restores the EE tree's rule for a unit (none uses it). The lead
maintainer chose this shape on 8 November 2026. It supersedes the note of 11876eec6 (7 November)
that the set-side rule should not land: that note rested on matched func_00132498, whose C then
stored its callback argument through a volatile no second context writes, and that store now has
a volatile-free form that matches with either rule.

func_L00_002A3B88 (3,432 bytes, 27 places in USA v1.01) and func_00131DE8 (576 bytes, the boot
of each of USA v1.01, PAL and v2.00) differ from the EE tree's rule in one `jal` slot each:
retail leaves it empty, the EE tree fills it from before two stores (`daddu $s3,$zero,$zero`,
the loop accumulator's clear, and `daddu $a2,$sp,...`). fill_simple_delay_slots searches back
from the call and gathers what each insn it passes sets (mark_set_resources) and needs;
resource_conflicts_p rejects every later candidate once `set.volatil` is on. Nearest the call is
a volatile store (the EE timer 0 count clear; the IOP-written 0x001A7110 field), which turns the
flag on, then a plain store (`sd` of D_001A7200; the request payload), which the EE tree's MEM
case turns off again with `res->volatil = MEM_VOLATILE_P (x)`, so the register-only insn before
them is taken. GCC 2.95's `|=` keeps it on and the search ends with the slot empty.

The change is Mark Mitchell's of 6 May 1999 (gcc-2.95 gcc/ChangeLog 1363-1367: "resource.c
(mark_referenced_resources): Make volatil monotonically increasing. (mark_set_resources):
Likewise."). The ChangeLog names only `volatil`, but 2.95's MEM case of mark_set_resources has
both lines as `|=`, `res->unch_memory |= RTX_UNCHANGING_P (x); res->volatil |= MEM_VOLATILE_P
(x);` (gcc-core-2.95 resource.c 713-714; resource.c is byte-identical in 2.95, 2.95.1, 2.95.2
and 2.95.3, SHA-256 4bc46d9aa1658a02f5d5178c0bdd888a10ba2fcd9cd7ec297ab5fcf2fad0c521), and the
transformer applies both; no test or sweep here exercises `unch_memory`. 2.95 also changes the
ASM_OPERANDS case of mark_set_resources to `|=` (2.95 line 753). That hunk is not applied: the
case comes, with UNSPEC_VOLATILE, ASM_INPUT and TRAP_IF, from Mark Mitchell's change of 4 May 1999
(gcc/ChangeLog 1406-1410), which the EE tree lacks, so there is nothing for it to change. The
EE archive's compiler is dated 11 November 1999, but its resource.c has neither change, so the
rule is inferred from retail's slots, not a recovered patch.

Measured on 8 November 2026, with func_00132498 in its volatile-free form: stock cc1
(upstream's recipe) and this cc1 give identical assembly for all 8,761 game-compiler units of
`src/` in the three releases (12,125 functions; 144 SDK units use another compiler), and so
does `-fno-rac2-sticky-volatile-sets`. Of the 1,029 drafts in `nonmatching/` that compile
(-G0 or -G8), three change, all closer to retail: func_00131DE8's (572 to 576 of 576 bytes,
15 to 0 differing words; 1 of 1 in us, pal and us2), the retained func_L00_002A3B88 draft
(3,428 to 3,432 bytes, 556 to 4 words) and its port-only functional copy (3,420 to 3,424
bytes, 808 to 722 words). The four words left in the retained draft are a `$v0`/`$v1` swap at
0x002A3D7C: func_002C9C20 was declared `int`, and the call's unused `$v0` shifts local-alloc's
fake lifetimes. Its true type is `void`: it has no return statement, and none of its callers
reads `$v0` after the call, in C or in assembly, in any release (one call per program; in each
the call's slot is a nop and the next instructions write `$v0` or call another function).
With both, func_L00_002A3B88 is 27 of 27. The two functions are `src/core/00131DE8.c` (a game
unit; 00131780.c is an SDK unit) and `src/levels/shared/L00_002A3B88-g8.c`, with no switch.
00131DE8.c's comment gives the RAC2 evidence that the IOP writes 0x001A7100..0x001A713F.

The signature: retail's `jal` slot is a nop while the insns just before the call are a plain
store and then a volatile store. A store retail lets into a slot past a volatile store is a
store the rule cannot see as plain: func_00132498's argument, stored as the second element of an
incomplete sda array (`D_001A74D0_1[1]`), is the length-2 `m` alternative and never a slot
candidate (below). [tests/test_sticky_volatile_sets.py](../../tests/test_sticky_volatile_sets.py)
checks the transformer's anchors and authored controls: the empty slot by default, the filled
slot with the opt-out, that `-frac2-sticky-volatile-refs` alone does not empty it, and three
controls that no rule changes.

### SDK objects: the assembler fills the slots the compiler leaves

[swap_branch_slots.py](../../tools/compiler/transformers/swap_branch_slots.py) adds the opt-in
assembler option `--r5900-swap-branch-slots`, passed per file as
`-Wa,--r5900-swap-branch-slots` after `sdk` in `config/cflags.txt`. It is an assembler
profile, not a compiler change: the SDK compiler's output is identical either way.

When reorg cannot fill a delay slot, cc1 writes the branch or call in `.set reorder` mode and
leaves the slot to the assembler, which may swap the branch with the instruction before it
(`append_insn` in gas/config/tc-mips.c). Reorg never fills a slot with a volatile memory
reference (`resource_conflicts_p` treats a `volatil` resource as a conflict; 2.9-ee only marks
the access with `#.set volatile` comments under GNU as) or with a two-word pattern such as
`truncdisi2`'s `dsll 32; dsra 32` (`define_delay` asks for length 1). This tree's gas never
swaps: the last guard reads `(prev_pinfo && INSN_SYNC)`, a logical `&&` where the bit test was
meant, so every instruction refuses and a `nop` follows. The game's C, assembled that way,
matches retail. With the option the guard tests `prev_pinfo & INSN_SYNC`, as GNU
2.10-ee-001003-1 does; every other swap rule stays as it is.

Retail evidence: the unmodified output of the SDK compiler, assembled by the original GNU
2.10-ee-001003-1 or by the DTL-S13010 build of GNU as 2.9-ee-991111 (rac1-decomp's toolchain
mirrors, docs/TOOLCHAIN.md there), gives retail's bytes for six boot functions in four Sony
libraries, which this tree leaves one or two words long or orders differently:

| Function | Library | Moved into the slot |
| --- | --- | --- |
| func_001253A8 | libcdvd (sceCdRead) | a volatile `lw` before `jal` |
| func_0012E378, func_0012E608 | libipu | volatile IPU register stores before `jal` |
| func_001307B0 | libmpeg | a volatile store before `jal` |
| func_0012CDB0 | libmpeg (_pictureCodingExtension) | the `sw` half of a store to IPU_CTRL, a `lui $at` macro, before `jal` (three times) |
| func_0011C000 | libc (printf's float helper) | the `dsra32` of a sign extension before `jr $ra` |

The option on, these match, and so do the 17 functions already matched in their five units.
On the whole objects of those five units, this tree's assembler with the option disassembles
identically to the DTL-S13010 assembler (GNU 2.10-ee differs elsewhere in the printf unit).
With the option on every one of the 112 SDK-profile units, only `func_00133988`
(989snd's snd_GetDopplerPitchMod, `mflo` before `jr $ra`) changes: retail keeps its `nop`.
rac1-decomp shows that 989snd was assembled with SN's ps2eeas, not GNU as, so the option is a
per-object profile, like rac1's `gas210` column. Game C and 989snd units leave it off.
[tests/test_swap_branch_slots.py](../../tests/test_swap_branch_slots.py) checks the transformer
and authored controls: without the option every slot gets a `nop`; with it a store, a load and
a sign extension move into the slot, and a branch that reads the previous result or carries a
label still gets a `nop`.

### reorg: which global loads may fill a slot

No compiler change: reorg.c, resource.c and jump.c in this tree are the 2.9-ee-991111b
archive's apart from the documented RAC2 switches (the archive's reorg.c is stock GCC 2.95.2's
plus Cygnus's `condjump_expect_p` prediction; its resource.c predates 2.95's volatile and
`TRAP_IF` handling. Retail's compiler had at least the set-side volatile rule, now the default,
and stopped at a division guard, see the sections above). When this cc1 and retail disagree about a
slot that holds, or could hold, a global load, the cause so far has been the declaration, and
the slot tells which one it was:

- `define_delay` takes only length-1 insns. A load or store of a small-data symbol is length 1
  only when the address is the bare `SYMBOL_REF` (`simple_memory_operand`, the Cygnus
  "symbol_ref_5900" case); `symbol+offset` stays under the archive's `#if 0`, is the `m`
  alternative and length 2, so it never fills a slot, from either thread. A `$gp` or macro
  access in a retail slot is therefore a word with its own name (or element 0); a global
  word retail never steals into a slot where this cc1 does was read at an offset from an
  earlier symbol (an array element or a field).
- A load through a register other than `$sp`/`$fp` may trap (`may_trap_p`), so
  `fill_slots_from_thread` does not put it into a plain (non-annulled) slot from either
  thread. If retail has one there, it came from `fill_simple_delay_slots`: the load stood
  before the branch, so the source reads that value before the test.

Witnesses: `func_L10_00425888` matches (1/1, all three releases) once its four clamped words
are one block, the first an sda scalar and the other three read at +4/+8/+12 from the
block's absolute name: retail's three branch slots hold the fall-through `li 127`, the fourth
steals the bare `$gp` load from its target, exactly what this cc1 then does.
`func_L11_0043E1A0`'s three wrong slots close the same way: the sound slot at 0x001B3774 is
element 1 of a pair at 0x001B3770 (retail leaves the two owner-test slots empty, the bare
element 0 is stolen), the height band's second bound at 0x001B1584 is its own sda scalar
(retail fills the `bc1f` slot from the fall-through with it), and the `(u16)` class read that
retail keeps in a `bnez` slot is read into a local before the wave test.

### loop: no giv recombination

[no_recombine_givs.py](../../tools/compiler/transformers/no_recombine_givs.py) is unconditional:
it is the real compiler's strength reduction, not an option. After `combine_givs` has chosen the
reduced giv each address giv is expressed from, this tree's `strength_reduce` (loop.c) calls
`recombine_givs`, which moves every combined giv onto the most recently set DEST_REG giv it can
be expressed from and then derives DEST_REG givs from earlier ones. The FSF disabled that call
for the gcc-2.95 release (`#if 0`, "There are still some problems with giv recombination",
gcc-patches, June 1999); the development tree this Cygnus snapshot comes from kept it. Retail's
compiler behaves like the release branch, and the transformer removes the call (the function
stays, unused).

Retail evidence: `func_00298F00` (7,840 bytes, boot + 27 levels, the memory-card state machine)
walks the card directory with three reduced pointers, the entry, its name and name + 5, and
reads the slot digit `entry->name[4]` after the second name compare. Retail reads it as
`lbu $v0,0x24($s2)` from the entry pointer; this tree recombined the read onto name + 5, the
pointer set for the call just before it (`lbu $v0,-1($s2)`), and the two pointers swapped
registers: six instructions at every place, and no spelling moves them, because the name + 5
giv's last use is the call. Without the call the function matches at all 28 places. Of every
matched function in `tools/build.py all --strict`, none compiled differently; of the 922
compilable near-miss drafts in nonmatching/, 9 compile differently, none close to a match.
The same release-branch change also turned off the biv-to-giv conversion of extra biv
increments (`n_extra_increment`); that half is the opt-in `-frac2-no-extra-increment-givs`
(below), with func_00284268 as its witness. [tests/test_no_recombine_givs.py](../../tests/test_no_recombine_givs.py)
checks the transformer and an authored loop: the digit read stays on the entry pointer
(`lbu 36(entry)`, not `-1(name + 5)`), and a one-pointer loop is unchanged.

### loop: extra biv increments stay bivs

When a biv is incremented more than once per iteration, as a cursor is by `*p++ = a; *p++ = b;`,
this tree's `strength_reduce` (loop.c, "If a biv is unconditionally incremented several times in
a row, convert all but the last increment into a giv") counts the extra increments
(`n_extra_increment`, biv_count - 1 per biv) and, under `if (n_extra_increment && !
loop_has_volatile)`, turns every increment but the last into a DEST_REG giv of the biv: the uses
after it read the new register, `bl->biv_count` drops by one and `bl->giv_count` grows by one
for each. The reduced givs then become separate pointers stepped once per iteration, or offsets
from the last one (`sd 0($a)`, `sd 0($b)`, `sd -24($c)` ... and one add of 32 each). The FSF
disabled the conversion for the gcc-2.95 release: Jeffrey A Law, 10 June 1999 (gcc-2.95
gcc/ChangeLog: "loop.c (strength_reduce): Disable biv->giv translations and giv recombination.
For the release branch only."), the change that also put `recombine_givs` under `#if 0`
(no_recombine_givs.py, above). [no_extra_increment_givs.py](../../tools/compiler/transformers/no_extra_increment_givs.py)
adds `-frac2-no-extra-increment-givs`, which adds `! flag_rac2_no_extra_increment_givs` to that
guard, so every increment stays a biv increment: store, add, store, add.

GCC history, from gcc-core-2.95.tar.gz, 2.95.1, 2.95.2 and 2.95.3 downloaded from ftp.gnu.org
(SHA-256 70250b26..., 5f25da6a..., 65e68d39..., 56811ee6...; nothing in them run). All four ship
the guard as `if (0 && n_extra_increment  && ! loop_has_volatile)` (2.95 and 2.95.1 gcc/loop.c
line 4151, 2.95.2 line 4185, 2.95.3 line 4208) under the comment "Disabled for the gcc-2.95
release.  There are still some problems with giv recombination.  We have a patch from Joern which
should fix those problems.  But the patch is fairly complex and not really suitable for the
gcc-2.95 branch at this stage.", the same words as the `#if 0` around `recombine_givs` (2.95
lines 4757-4763). The ChangeLog entry is in each release's gcc/ChangeLog (2.95 lines 476-479) and
none of them re-enables either half. This tree is the Cygnus development snapshot of 11 November
1999, and its own loop.c runs the conversion (the guard has no `0 &&`). That Cygnus kept the
conversion on is inferred from that source alone; no Cygnus ChangeLog entry or other Cygnus source
says so. Its block differs from 2.95's dead one only by later development fixes (a `loc_mentioned_in_p` walk to the insn that holds the next increment's location, and no
`reg_single_usage` growth). With the switch the conversion is skipped as in every 2.95 release; it
is inferred from retail's loops, not a recovered patch.

`loop_has_volatile` also gates check_dbra_loop's loop reversal (`num_nonfixed_reads <= 1 && !
loop_has_call && ! loop_has_volatile && ...`). The switch does not edit that test or anything else
in check_dbra_loop. Its input changes, though: a loop counter incremented more than once keeps all
its increments, so check_dbra_loop sees biv_count 2 where the default had converted one to a giv
and left 1. In the fixture's `pairs` (`p[i] = 0; i++; p[i] = 1; i++;` while `i < 32`) the default
reverses the loop into a count-down from 30 (`bgez`), and with the switch it counts up as written
(`slt $2,$3,32`); GCC 2.95, which never converts, gives check_dbra_loop both increments too. A
loop whose counter has one increment (`clear16`) is reversed by
both. A volatile read in the loop already skips the conversion in the default, so its output is
the same with the switch (`fill_volatile`); that is the volatile view's only loop.c effect in
func_00284268 too.

Retail witness: func_00284268 (2,988 bytes, boot + 27 levels in USA v1.01, PAL and v2.00) sets up
the anti-aliased frame-buffer packets and has seven loops whose cursors advance two or four times
per iteration; retail stores and adds after each (`sd 0($c); addiu $c,$c,8` four times). The
retained draft matched 28 of 28 places in every release only through a volatile view of the state
pointer D_001A742C (one read per loop), which AGENTS.md does not allow. Its only loop.c effect
is `loop_has_volatile`: with insn numbers masked, the gcse dumps with and without it differ only
in the seven reads' MEM flag (`mem/v` for `mem/f`), and the volatile draft without the switch and
the plain one with it give the same assembly apart from the seven `.set volatile` markers. With
the switch the plain C, RAC1's own `*p++` wording (framebuf.c, SetupFS_AA_buffer), matches all
seven loops: 2,988 bytes and 28 of 28 places in each release. Without the switch it
is 3,036 bytes (0 of 28); without `-fno-rerun-loop-opt` 2,980 (0 of 28). The two D_001A6860 loops
need the index form `store(&q[n], X); n++`, a reduced giv of n whose init comes last in the
pre-header; a plain `*p++` cursor there is a biv equal to its own giv and keeps its init first.
The function has a unit of its own, `src/game/00284268.c`, with both flags. The retained volatile
draft, compiled without the switch, is bit-equivalent: it also matched 28 of 28 places in each release. The switch is chosen over
that volatile reading on policy grounds, because AGENTS.md does not allow `volatile` on ordinary
data, not because the bytes tell them apart.

Without the switch, stock cc1 (upstream's recipe) and patched cc1 give identical assembly for all
8,731 game-compiler units of `src/` in the three releases (12,092 functions; 144 SDK units use
another compiler), with no compile errors. Forced on in every one of them, it changes only
func_00284268's own unit: no matched function has a loop the conversion splits. Forced on for the
1,074 drafts in `nonmatching/` that compile (of 1,134; default flags, -G8, -fno-rerun-loop-opt and
both), it changes one, func_L05_0042B2C0, whose note already says retail "increments one output
pointer twice by 12 bytes": with its own profile it goes from 2,112 to 1,984 bytes (retail 2,128),
0 of 4 places either way, so other differences dominate. Retail does not split a cursor there:
its inner strip loop (USA v1.01 level 5, 0x0042B730-0x0042B83C) keeps both increments of the
output index (`addiu $s7,$s7,1` at 0x0042B74C and 0x0042B75C) and steps each of its four reduced
address registers twice per iteration (`$s2` and `$s5` by 12, `$s0` by 8, `$s4` by 4). The draft
gives that shape only with the switch (two steps of 12, 8 and 4, two `+1`s); without it, one step
of 24, 16 and 8 and one `+2`. So retail's compiler kept every increment in this function too, as in
func_00284268, and the switch is not a per-function one. The goto-loop record copy of
`func_L00_00300618` (below) does not change: a goto loop has no loop notes.
[tests/test_no_extra_increment_givs.py](../../tests/test_no_extra_increment_givs.py) and
[no_extra_increment_givs.c](../../tests/fixtures/no_extra_increment_givs.c) cover the anchors (the
option table on its own), the default/disabled equality, a pointer cursor and an index cursor
whose four increments the default splits and the switch keeps, the twice-incremented counter
above, and controls that do not change: one increment, a volatile read, increments under a test
and a reversed single-increment loop.

A scalar global read across pointer stores is `fixed_scalar_and_varying_struct_p`: cc1 assumes a
fixed scalar cannot alias a varying array element, so the load is hoisted or moved over the stores.
Where retail reloads, declare the global as an array and read `[0]`: `D_L00_001B2B58[0][i] = 0` keeps
the reload and the integer index in `func_L00_003E4BF0`, and the cursor `D_001B22A8[0]` stays behind
the `t[]` stores in retained `func_00285030`, with no fence. An integer index that survives inside a
loop means no loop notes: loop.c reduces every `for` or `do` form, a `goto` loop keeps it (`func_L00_003769C0`,
matched 9 November 2026).

The section-8 record copy in retained `func_L00_00300618` is another source-level
case. A `do` loop turns its four cursor advances into address induction variables;
an explicit `goto` loop keeps the advances and reproduces the entire 24-word
sequence in all 27 USA v1.01 placements. Other loops retain their required strength
reduction. This removes that local obstruction without disabling extra-increment
conversion in the compiler; the complete loader still does not match (11,280 versus
11,348 bytes). Absolute macro-global stores and other loops remain separate issues.

### Compiler control-flow passes

[tidy_condjump_fallthru.py](../../tools/compiler/transformers/tidy_condjump_fallthru.py)
lets flow remove a conditional jump to its immediate successor and its now-dead
input load. The rule follows GCC fixes from April/August 1999; witnesses include
`func_L02_003FD070`, `func_L02_003FC268`, `func_L02_003FC518`, `func_L02_003FD228`,
`func_L02_003CD4A8`, `func_L02_003CD298`.

| Per-file option | Change | Witnesses |
| --- | --- | --- |
| -frac2-gcse-unsplit-edges | Build predecessor/successor lists without Cygnus critical-edge splitting; PRE inserts at the preceding block | func_L02_003E79F8, 352 bytes/1 place; func_002CD720, 340/28; a shared high half hoisted above the first branch, each block forming its own low half: func_L00_002EA668 160/5, func_L04_002CC748 144/2, func_L01_002A7248 128/4, func_L01_00323310 112/18 |
| -frac2-keep-block-order | Skip cygnus_merge_blocks; keep default-last switch body and its branch | func_L18_004283F0, 56 bytes/3 places |
| Both | Compose the two independent changes | func_L02_003FCCA0 |
| -frac2-no-null-pointer-checks | Skip the Cygnus delete_null_pointer_checks calls (after jump1 and after the jump pass behind cse); with keep-block-order no block count runs before cse | func_L20_002CD928 case 0x7C, 34,964 bytes/1 place |

Implementations: [gcse_unsplit_edges.py](../../tools/compiler/transformers/gcse_unsplit_edges.py),
[keep_block_order.py](../../tools/compiler/transformers/keep_block_order.py),
[no_null_pointer_checks.py](../../tools/compiler/transformers/no_null_pointer_checks.py). These are
inferences from retail and comparison with GCC 2.95, not the recovered original
patches. A lone lui at a branch target is not a unique signature of edge splitting.

**6 November 2026, round 9 (not adopted):** three Lombyte sce-991111b candidates were
env-gated in cc1 and swept over all 8595 non-SDK units and all 1206 near-miss files
(-G0/-G8, labels renumbered). 0060 (no ADDRESS base for the static-chain/struct-value
registers): 0 units change; one near miss moves (func_002BA0E0, 285 to 273 real rows, still
1476/1472 bytes), and cc1 crashes on nonmatching/levels/func_L04_00441100.c. (Since adopted as the
opt-in `-frac2-no-static-chain-base`, above, which with `-frac2-frame-pointer-liveness` matches
func_002BA0E0. That draft no longer compiles today, and stock cc1 also crashes on it.) 0061 (unshared
stack MEMs): 0 units, 0 near misses. 0065 (unsplit gcse edges by default): 33 matched units
change (11 functions in three releases, e.g. L04_002E04A8.c), so it stays opt-in; it moves no
listed near miss. The 13 scheduler/gcse near misses (func_00342BE8 ... func_L06_00382608)
under 7 profiles at -G0/-G8 are unchanged by all three.

Both Cygnus passes that run before cse (delete_null_pointer_checks and cygnus_merge_blocks,
one "CYGNUS LOCAL law" block) start with find_basic_blocks, which puts a
`(use (const_int 0))` after a call that ends a block. When cse then threads a branch past the
label behind that call, the blocks merge with the no-op still in them; sched1 moves it, and
local-alloc counts it, so two back-to-back address pseudos stop sharing a register. A
spawn-and-initialise block ending in a call before a re-test of the new pointer shows it:
retail has the re-test in the call's block and no no-op effect. Skipping only one of the two
passes leaves the other's count, so such a unit needs both options.

### Wide stores and annulled slots

[no_annulled_wide_stores.py](../../tools/compiler/transformers/no_annulled_wide_stores.py)
adds `-frac2-no-annulled-wide-stores`. Thread search stops at a wide store that
cannot occupy an ordinary slot; target-delay-list stealing refuses it for an
annulled slot. Searching past the store selects a different instruction.

This default-off policy is **not a hardware prohibition**. Ordinary slots and
`optimize_skip` remain unchanged: matched `func_00116460` has two bnel/sd pairs.
The original 7,825-function game census found no sd/sq in branch-likely slots,
497/547 in ordinary slots, and wide loads in likely slots. SDK/handwritten code
was excluded; do not promote a scoped census into an ISA rule.

Witnesses: `func_L23_00422668` (300 bytes/1 place, also qcopy) and
`func_L02_0042EDD0` (476/2, -G8 and zero-ti-barrier). Ordinary wide stores, scalar
stores and wide loads are controls. The fno form disables the option.

## Floating-point instructions and hazards

### Literals and min/max

Compare actual constant words rather than rounded mathematical values. Measured
retail examples include `1.0471977f` (`0x3F860A93`) and `0.78539824f`
(`0x3F490FDC`). The old assembler also converted some long decimal spellings
unexpectedly; check the final lui/ori/mtc1 words before blaming allocation.

Min.s/max.s **are reachable with -ffast-math**: fold admits floating MIN/MAX_EXPR
under that option. `func_L01_003BD560` and `func_L03_00384340` (a max.s of two float results in a 16-entry loop, own -G8 unit) are min/max witnesses. For the 8-byte maximum
`func_L00_002EE050`, -O1 -ffast-math retains the argument registers, whereas -O2
adds a move and gives 12 bytes. The older blanket impossibility claim is false.

### Integer words stored into floats

The HUD widgets pass packed colours as float arguments. Retail has both forms for the same kind
of bit pattern. In func_0034B2C8 and func_00349D58 every colour read once comes out as `li.s`
(`lui $at`, `ori $at`, `mtc1 $at`, also for values as odd as 0x70242335), while a colour read
twice is set in `$v0` right after the previous call, moved once into a saved FPR and copied for
each read:

```text
lui   $v0,0x6044; ...; ori $v0,$v0,0x2D00; ...; mtc1 $v0,$f20; ...; mov.s $f13,$f20; jal ...
...; mov.s $f13,$f20; jal ...
```

The denormals that `mips_const_double_ok` refuses (0x442D00, 0x1EFF, 0x80001EFF) look the same
as the second form. A retail scan (boot and the 27 levels, 54,127 `lui`/`mtc1` sites, 13 of them
normal values built outside `$at`) finds this form only here: of the other eight, seven are in
`ASM_FUNC` routines and one is 1.0f in the unmatched func_002A1130. `lui` and `ori` are apart, so
the constant is an SImode `movsi` split at RTL level, not a `li.s` macro. `mov.s` waits out the `mtc1` latency, so it is real movsf RTL.

The source form is the write-side pun, `f32 f; *(s32 *)&f = K;`, used for every colour of both
functions. purge_addressof turns it into `(set (reg:SI g) K)` and
`(set (subreg:SI (reg:SF f) 0) (reg:SI g))` after cse1. In this tree g does not survive when f is
read twice:

- cse2 writes K into the SUBREG store, or, if K is live in an older register, that register;
- if not, combine's combinable_i3pat moves the SUBREG to the source (expand_field_assignment) and
  gen_lowpart_common folds K: `(set f const_double)`, a `li.s` that sched1 hoists to the block start;
- sched1 splits `(set (subreg:SI f) K)` into hi/ior (mips.md's `large_int` split). Three operands
  against the two reads make f a GR_REGS pseudo in a saved GPR, with an `mtc1` per read. With
  three reads, two reads in a loop, or reads across a branch, f stays FP_REGS, and the ior's
  output reload is lost: **`lui; mtc1` and no `ori`, wrong code from the default compiler** (see
  the known issue below).

With `-frac2-keep-float-pun-source` ([keep_float_pun_source.py](../../tools/compiler/transformers/keep_float_pun_source.py))
cse_insn leaves that insn's source register alone, and combinable_i3pat refuses it as I3 unless
f has a single use (find_single_use, which finds the use even where it returns 0). g crosses no
call, so sched_analyze_1 keeps its set after the previous call; f, with one SUBREG store against
two reads, is FP_REGS; g dies in the store, so reload's output for it is the `mtc1`. A single
use folds as before (`(set (subreg f) g)` + `(set $f13 f)`), and a read-side pun
(`*(f32 *)&i`) has no SUBREG store and is not touched. The insn test is RAC2_FLOAT_PUN_SET_P in
`flags.h`: SImode SUBREG of an SFmode pseudo, register source, nothing about a function.

**Known issue: the default compiler loses the low half.** Without the switch, a word with a
nonzero low half stored through `*(s32 *)&f = K` and read three times, twice in a loop, or on both
sides of a branch compiles to `lui $v0,hi; mtc1 $v0,$fN` with no `ori`: f gets the wrong value,
silently. Measured (tests/fixtures/keep_float_pun_source.c, `three_reads`, `reads_in_loop`,
`reads_across_branches`; tests/test_keep_float_pun_source.py asserts it so that the default stays
stock) with four compilers: this tree, whose reload1.c and cse.c are GCC 2.95.2's (patches 0047
and 0048); the same patch and transformer stack without 0047 and 0048; the
gnu-ee-binutils-gcc-1.1 archive (2.9-ee-991111b) with only patch 0000's host fixes; and the
unmodified SDK compiler (2.9-ee-991111-01, tools/compiler/sdk). All four drop the `ori`, so the
defect is the EE 2.9 base's, not 0047's or 0048's. In the global-alloc dump the ior reads the
`$v0` left by the `lui`'s output reload (no input reload insn) and has no output reload into the
FPR. The default stays as it is: an unconditional guard would change the default compiler's
output, so this entry records the defect instead (no guard was built). C in `src/` that links is
compared with retail's bytes, so it cannot carry the defect unnoticed. C built with the default
compiler outside `src/`, notably
`nonmatching/functional/` and native-port references, can contain it: compile such a unit with
the switch, or check that every `lui` feeding an `mtc1` of a pun has its `ori`.

What is measured, and what is not:

- Measured: retail's form at the colour sites (above). With the switch, func_00349D58 matches,
  28 of 28 places in us, pal and us2. func_0034B2C8 is a near miss, not a match: all 16 colour
  sites take retail's form, down to `$at` against `$v0`, the FPR numbers and 0x1EFF's `$v0`, but
  the function gives 6,048 of 6,048 bytes with 12 words differing and 0 of 28 places, from two
  jal-slot orders that have nothing to do with the colours (its draft header). The forms tried in
  stock cc1 are listed in nonmatching/game/func_0034B2C8.c's header; none gave retail's form.
- The circularity, said plainly: the switch was designed to produce retail's form at these
  sites, so the two functions it matches are not independent evidence that SCE's compiler had
  such a rule. What does not depend on that design is the sweep: no other unit of `src/` changes
  under the switch, so it reproduces this form and nothing else.
- Not a backport. gcc-core 2.95, 2.95.1, 2.95.2 and 2.95.3 from ftp.gnu.org and this tree agree on
  fold_rtx's SUBREG case, gen_lowpart_if_possible, gen_lowpart_common's SFmode case,
  gen_lowpart_for_combine, combine's SUBREG simplification, expand_field_assignment,
  split_block_insns and the `large_int` split (token comparison), and no ChangeLog entry concerns
  them. For the lost output reload, gcc-core 3.0, 3.0.4, 3.1, 3.2, 3.2.3, 3.3, 3.3.6, 3.4.0 and
  3.4.6 were compared too (sources read, nothing built or run from them). reload1.c is largely
  rewritten by 3.0 (3,278 lines added and 4,068 removed against 2.95.2) and reload.c much changed,
  so no fix can be read off a diff; no ChangeLog entry up to 3.4.6 describes a lost output reload
  of a SUBREG store, an inherited input reload dropping an output, or this split. The nearest,
  2000-09-18 (forget_old_reloads_1 clears spill_reg_store when a hard register is stored), is
  about a different case and was not tested. The `large_int` split is unchanged through 3.3.6;
  3.4 removed it (2003-05-03, mips_move_integer: constants are built at expansion), so the RTL
  that loses the `ori` no longer forms there, which is a different design, not a reload fix. The
  public EE-GCC releases checked are the two above (2.9-ee-991111b and 2.9-ee-991111-01); no other
  EE-GCC release was available here.
- Speculation: that SCE's game compiler could not have kept a path that loses the `ori`, and so
  fixed it locally, is a guess. The measured part is narrower: no tested compiler gives retail's
  two-read form by default, the publicly released EE compilers lose the `ori` too, and retail's
  code at these sites shows neither the defect nor the stock forms. Where retail's behaviour comes
  from is unverified; the option states the behaviour, not a patch.
- Unsafe cases: none known. g and f hold the same bits either way, and the rule only keeps a
  register that the unchanged RTL already uses.

Sweep (8 November 2026), with stock and patched compilers from the pinned toolchain: without the
switch, all 8,740 game-compiler units of `src/` (us, pal and us2; 144 SDK units use the other
compiler) give identical assembly. Forced on everywhere, it changes func_00349D58 and none of the
other 12,100 functions. Over the 1,123 files of `nonmatching/` (1,063 compile, at -G0 and at
-G8) it changes only func_0034B2C8's two drafts. In func_00349D58 the first fade's two keys, 0x80F0C070 and
0x80F0F0F0, are colours read once, `li.s` through `$at` each; both go through the helper like
every other colour. (An earlier note took key 1 for a second read of 0x80F0C070: its literal,
`-2.2126951167197445e-38f`, is 0x80F0F0F0.)

### Transfer hazards

Mtc1 uses the next instruction's FPR read, not distance from the GPR's last write.
The expanded retail survey found 915 immediate dependencies: 897 delayed, 18 not;
the original 598 sites (587 delayed) are a subset. Cleared assembler history can
occur within a function and is not a function-boundary detector.

[u4_mtc1_helper.py](../../tools/compiler/transformers/u4_mtc1_helper.py) and
[restrict_mtc1_exemption.py](../../tools/compiler/transformers/restrict_mtc1_exemption.py)
retain two measured cleared-history exemptions: a0 to f0 before cvt.s.w f0,f0,
and zero to f0 before c.lt.s f12,f0. Eight first-transfer witnesses split four
requiring a nop and four not. A distance-two producer rule failed `func_002A7878`.
Both apply only to an mtc1 appended to a forgotten history (`prev_insn_valid` clear).
`tests/test_mtc1_exemption.py`.

gas empties both history slots in two ways. mips_no_prev_insn (md_begin, a section change,
`.align`, data) forgets the history: it also clears `prev_insn_valid`. append_insn empties
both slots after every unconditional branch (`b`, `j`, `jal`, `jr`), filled or not, but sets
`prev_insn_valid`. A forgotten history is a section start, and every game unit is built with
-ffunction-sections, so in practice it is a function start. `.ent`, `.end` and stabs do not
forget it: a function start inside a section, after `j $31`, keeps the nop. Until 8 November
2026 the exemption also applied behind an unconditional branch, so an mtc1 behind a `b` lost
its nop. Two known limits stay exempt, because `.align` and `.set reorder` forget the history:
`b; .align 3; L: mtc1` and `b; .set noreorder; .set reorder; L: mtc1`. cc1 emits neither (code
labels get `.p2align`, which does not forget it); the fixture pins both.

Retail census of both pairs, every program (boot and 27 levels) of us, pal and us2, by
scanning the retail text for each pair with and without a nop between: the a0 pair has no
nop only at the start of `func_00283CE0` (84 sites: the boot and its 27 level copies, such as
us level 00 `0x002EF240`) and the zero pair only at the starts of the handwritten
`func_00129218`/`2C0`/`368` (9). Every other site keeps the nop. Behind a `b`: zero pair 429
sites with a filled slot (143 per release) and 27 with a nop slot
(`b; nop; L: mtc1 $0,$f0; nop; c.lt.s`, `func_PAL_L00_003874B8`), a0 pair 6 with a filled
slot. Behind a conditional branch: a0 pair 81 with a nop slot (`func_L00_002E2958`, 27 per
release) and 56 filled, zero pair 16 filled. No site follows `j`, `jal` or `jr`. cc1 writes a
noreorder `b` only with a filled slot (its template is `%*b`), so the unfilled `b` reaches gas
in reorder mode.

Ten original no-nop sites in `0x00283C28`, `0x002A677C`, `0x002E0408`,
`0x002E0558` can also be reproduced with explicit instruction ordering; ISA
selection offers another sufficient mechanism. Original directives remain unknown.
The private 89-case fixture history does not qualify every transfer in the game.

Mfc1 is interlocked on R5900: the measured boot text had 88 immediate readers in
47 functions; its only extra-nop example used handwritten VU code.
[r5900_mfc1_interlock.py](../../tools/compiler/transformers/r5900_mfc1_interlock.py)
removes the MIPS-I coprocessor-load delay in append_insn for mfc1 only. Cfc2 and
label padding are not waived. `func_002ED4B8` and `func_00290680` match at 28 places.

### Overlapping variants in md_convert_frag

A relaxable macro keeps its `$gp` form in the frag and its absolute form behind it;
`md_convert_frag` slides the absolute form down with `memcpy (fixptr - old, fixptr, new)`.
For a load or store with a base register and a symbol of unknown size
(`lbu $2,_ctype_+1($18)`), `old` is 8 and `new` is 12, so the ranges overlap: undefined, and
host-dependent. An assembler built on 3 November 2026 emitted `lui; addu; lbu`; the ones built
from the same sources on and after 8 November copied backwards and left the second word in the
first slot (`lbu $2,0($2); addu; lbu`), so `func_00117278` (strtol, the -O0 unit that uses
this form) and `func_00132498` stopped matching in `tools/build.py boot --strict` on those hosts.
[convert_frag_memmove.py](../../tools/compiler/transformers/convert_frag_memmove.py) makes the
copy a `memmove`; [the test](../../tests/test_convert_frag_memmove.py) assembles the two forms.
The 4/8-byte pairs overlap the same way; patch 0020 already rebuilds their first word, and
that rebuild is kept unchanged.

### Labels on hazard nops

[hazard_labels.py](../../tools/compiler/transformers/hazard_labels.py) adds
`-frac2-hazard-labels`: cc1 emits `.set rac2_hazard_labels`, and gas retains labels
on the needed nop rather than moving them behind it, including the noreorder
flush. This connects a per-file option to the assembler without patching output.

The retail census found 198 relevant targets in 148 functions (71 compares,
127 mtc1 readers), all forward and on the nop. Aligned loop-head fill whose next
instruction does not read the producer is not a hazard counterexample. No needed
target reached only backward, or branch target after ctc1/cfc1/COP2, was sampled.

SN 2.0 authored controls retained labels for forward/backward branches, j, data
.word references, multiple labels, li.s and alignment. This supports the rule,
not the shipping assembler's identity. Witnesses: `func_L18_004308F0` (1,384/1),
`func_L02_00411530` (80/7). The fno option restores default behaviour.

### Division/root scheduling and padding

Compose these three mechanisms; none replaces the others:

1. [neutralise_div_dslot.py](../../tools/compiler/transformers/neutralise_div_dslot.py)
   keeps single-precision division/root operations out of compiler-selected delay
   slots. Retail had 0 of 19,806 div.s in slots, but 61 integer HI/LO divisions.
   Sqrt.s/rsqrt.s are extrapolated: neither occurred in that retail census and GNU
   as does not assemble rsqrt.s.
2. [pad_div_erratum_nops.py](../../tools/compiler/transformers/pad_div_erratum_nops.py)
   models a measured SN 3.01 two-slot incoming floor after code labels for div.s,
   sqrt.s and rsqrt.s. Needed hazard nops count toward it; labels stay on padding.
   Sync.p imposes one nop, unlike sync/sync.l.
3. [pad_div_erratum_branch.py](../../tools/compiler/transformers/pad_div_erratum_branch.py)
   extends the floor to branch groups: bc1t/ld/div.s gains two nops; one intervening
   instruction gains one, two gain none. Conditional/likely branches and b trigger
   it; j/jal/jr/jalr do not. Integer division is unaffected. It consumes the label
   transformer's anchors, so order matters.

The floor is placed after a **code label**. A unit built with `-g` carries line
labels, which is enough: `func_L22_003AD090` reached 264 of retail's 272 bytes
without the pre-`div.s` `nop` pair and matched once its file had `-g` in
`config/cflags.txt`, with no change to the other nine functions of that unit.
Before treating such a pair as unreachable, try `-g` on the file.

The floor also holds when the label follows a compiler `.set noreorder` group.
GCC writes every call with its delay slot inside one, so under `-g` the line
label of the next statement comes right after an unreordered instruction, and
gas's own `prev_insn_unreordered` reset used to cancel the floor there. Retail
pads it: level 00 alone has 24 functions with jal, delay slot, nop, nop, div.s
(func_L00_0040A4A8 at +0x200 among them), none of which had matched. The label
test now runs after that reset (rule D in pad_div_erratum_nops.py). This is the
assembler's default behaviour, not an option: no file needs a switch for it. A full strict
build changed one matched function, func_002C3280, whose C had the second call and
the division in separate statements; retail has no padding there, so the division
now sits in the call's statement (no line label between), which matches with and
without the change. A division emitted inside a noreorder region still gets no new
floor. [test_div_label_after_call.py](../../tests/test_div_label_after_call.py) covers
the label, no-label and noreorder cases.

Across a non-PIC GP relaxation fragment, the label-distance calculation follows
the selected expansion when its symbol already has a size or section. The
alternative `lui`/load words stored for relaxation are not additional emitted
instructions. Thus a labelled GP load followed by `div.s` receives one nop,
just like an explicit GP operand; an absolute two-word expansion receives none.
Unknown forward symbols, alignment and unsupported fragment kinds retain the
previous fallback. This is a bounded distance correction, not general relaxation
or SDK equivalence. [test_div_gp_fragments.py](../../tests/test_div_gp_fragments.py)
checks authored GP, absolute, two-load, `.word` and unknown-symbol controls. The
previous assembler fails only the one-load GP macro control. The corresponding
C witnesses are `func_L05_00419CC8` and `func_L00_00424F98`, at four and 27
placements respectively in each USA release; neither identity is carried in PAL.

The strict USA regression exposed one existing source dependency on the old
overcount: `func_L30_00383398` gained a nop before its brightness division.
Its final pixel-address arithmetic is scheduled between the bounds loads;
separate debug source lines introduced a label before the last GP load.
Keeping the whole brightness calculation, clamp and store on one source line
preserves retail's lack of that label and restores all 1,424 bytes. No C
operation or evaluation order changes. This existing function earns no new
matching credit.

The genuine SDK 3.01 oracle Ps2EeAs has SHA-256
`cb5adda955e64626564212ef7e0c1434708c4e1ef423344a92ec8033306ed3aa`.
The SN 2.0 full-image assembler has SHA-256
`c839dd63facabe7b76573c114056be61eaa7b3aa2329dd546930ab8f98898c76`.
They disagree on 44 of 97 synthetic outputs; neither is proven to be the shipping
assembler, and a matching subset does not establish equivalence to both.

The strict 97-fixture battery gave **84 pass, 13 fail, 0 error**, comparing text,
labels, branches, delay words and relocations. An earlier 49-case subset reached
47 strict passes after fixing eleven displaced labels. Remaining failures: two
integer macros, two local-relocation addends, three post-division noreorder hazards,
four other SDK-version-dependent noreorder cases, and two cross-fragment
alignment/.word-distance cases. No masking/cropping converts these into matches.

SDK 3.01 **warns and still returns success** when it cannot pad a branch delay
slot; it does not refuse object creation. General fragment/alignment behaviour
and ordinary noreorder padding are not established. Many retail pre-division nops
follow sequences the oracle does not pad and need a separate source/compiler
explanation. A correct division region did not make the retained 572-/220-byte
witness families match.

## 64-bit immediates and SDK helper types

Patch 0052 selects bounded R5900 dli value classes:

| Class | Expansion or boundary |
| --- | --- |
| Isolated sign bit | Signed default addiu -1, then dsll32 31 |
| Sign bit plus contiguous low run of at least 32 ones | Existing sign-extending lui path |
| Positive contiguous run wider than 32 bits, zero at both ends | Shift construction: three instructions for 0x0FFFFFFFFFFFFFFE instead of seven |
| Runs at most 32 bits, holes, neighbouring masks | Preserve previous paths; 20-bit 0x00FFFFF000000000 must stay unchanged |
| Top 16 bits all ones, hi32 not 0xFFFFFFFF, not -1 << k (patch 0060) | First field is a sign-extending lui of the 16 bits ending at the lowest bit of the leading run of ones; the next shift is 16 shorter. 0xFFFF0000FFFF0000 becomes lui 0x8000; dsll 1; ori 0xFFFF; dsll 16 (was ori 0xFFFF; dsll32 0; ori 0xFFFF; dsll 16) |

The selector uses unsigned arithmetic without division/undefined shifts and is
keyed to a value class, never a game address or function. SDK-profile witnesses:
`_fpadd_parts` / `func_00122800` (576 bytes), `_strtol_r` / `func_00117278` (884),
`__pack_d` / `func_00122630` (300). Do not substitute the game profile.

`dpmul` / `func_00122B00` (680) needs the public fraction union in the shared
24-byte DoubleParts declaration:

```c
union { unsigned long long ll; unsigned int l[2]; }
```

Its member access has alias-set zero under the SDK compiler. Restoring the union
creates the real store dependence for rounding and the bnel fraction-store slot.
The scalar simplification lost that dependence; barriers/pins are not a remedy.
Four existing users retained identical object sections. Disabling sched1 fixed
only the tail and grew it to 688 bytes; disabling sched2 changed the prologue.

Patch 0060's evidence is one compiled constant: the lockB mask 0xFFFF0000FFFF0000 in
`func_0030A348` (boot) and its 27 level copies (family F4, 28 occurrences), GCC output by
its frame, delay-slot filling and $gp loads, next to the lockA mask 0x0000FFFF0000FFFF that
already matched. A scan of every boot and level text for 64-bit ori/lui/dsll chains finds no
other compiled constant in the class, so nothing else changes (`build.py all --strict` 28/28).
The only other lui-led chains are hand-written (`ASM_FUNC`) or the SDK's `__pack_d`, outside
the class. The rule is the one rac1's ps2eeas model (tools/ps2eeas_dli.py, checked against
871 assembler outputs) uses for the same class. Values with hi32 0xFFFFFFFF keep the old
path: retail's 0xFFFFFFFF00FFFFFF is addiu -1; dsll 16; ori 0xFF; dsll 16; ori 0xFFFF.

### Double constants in general registers (li.d)

cc1 writes a DFmode constant bound for a general register (a double argument of a
variadic call under `-msingle-float`, such as `printf(fmt, 0.1f)`) as the macro
`li.d $r,<value>`. The archive's gas builds it inline only when each 32-bit half has a
zero 16-bit chunk and otherwise pools it in `.lit8` (`lui $at` plus `ld $r,%lo(..)($at)`).
The game's own code builds it inline every time with load_register's 64-bit form:
(double)0.1f, 0x3FB99999A0000000, is `ori 0xFEE6; dsll 17; ori 0xCCCD; dsll 29` in
`func_002ADB78` (boot) and its 27 level copies (`func_L00_00321878`); (double)1e-4f in
`func_002D36A0` and its level copies and the constants of `func_00284268` have the same
form, and no compiled game code in the boot or any level loads a `.lit8` value (every
`lui $at`/`ld` pair reads the scratchpad in hand-written blocks). The SDK's objects pool:
`func_0011C090` (libc's exponent formatter, SDK profile) loads 0.1 and 10.0 from `.lit8`
and matches only that way. So the game code's form is the assembler's default:
[inline_li_d.py](../../tools/compiler/transformers/inline_li_d.py) takes the whole value for every
`li.d` into a GPR on a 64-bit ISA (the `F` operand of M_LI_D) and builds it with load_register;
FPR forms and 32-bit ISAs are unchanged. `--r5900-pool-li-d` restores the archive's pooling, and
`tools/build.py` (`split_flags`) passes it to every unit of the SDK profile (`sdk` flags in
`config/cflags.txt`), so no flags line changes and the SDK objects assemble as before; no game
unit needs a switch. `--r5900-inline-li-d` states the default explicitly. An earlier default-on
trial without the SDK opt-out broke `func_0011C090`. With the default, no matched function in
any release compiled differently (`build.py all --strict`: us 28/28; pal and us2 only their
known failures). [tests/test_inline_li_d.py](../../tests/test_inline_li_d.py) checks the
transformer, both profiles' words, and that only SDK units get the opt-out.

Two sign-bit loads need a zero-extending seed. Patch 0059 exposes per-object
`--r5900-sign-bit=unsigned`; pass it with `-Wa,--r5900-sign-bit=unsigned` in the
same per-file flag table. Explicit signed restores default; invalid/missing values
fail. Same value does not mean the same retail encoding.

### Positive 32-bit masks in 64-bit registers

The libm word-insertion sequences use a second assembler choice. For the
positive value `0x00000000ffffffff`, the GNU seed is `lui 0xffff; dsrl32 0`,
while SN uses `addiu -1; dsrl32 0`. Both produce the same 64-bit value in two
instructions. The SN form is present at five independent sites in `floor`,
`fmod`, `log` and `log10` in each release. It also follows
[RAC1's public assembler model](https://github.com/OpenRAC/rac1-decomp/blob/1d8228cc0c81da7bc2bdc3e77479ee050e0ef434/tools/ps2eeas_dli.py)
and independently authored SN controls.

Patch 0061 exposes `-Wa,--r5900-unsigned32-mask=sn` per file. The default and
explicit `gnu` profile retain the previous output, including SDK objects.
Selection requires a 64-bit R5900 load with an actually zero high word and
an all-ones low word; a destination of `$zero` must not broaden that condition.
No compiler-authored operation, register, value or relocation is rewritten.
The 16 DLI tests cover exact encodings, values, neighbors, wider/signed masks,
five ordinary registers, zero destinations, unchanged `li`/`la`, invalid options
and composition with the independent sign-bit profile.

The complete native-double `log` and `log10` bodies use this profile together
with their existing quad-save/fast-math settings. Their compiler-owned scalar
pools are 96 and 32 bytes, respectively, contiguous and disjoint in each
release. In `log10`, `two54` and zero are immediate expressions: declaring
storage for them produced text that matched but a wrong 48-byte pool overlapping
`log`. No pool bytes, aliases or padding were invented to fix it. Whole-program
validation must include these complete pools, not just the text comparisons.

The caption routines `func_L00_002E3340` and `func_L00_002E3520` also use this
existing profile, with `-O2 -G0 -ffunction-sections` on their shared source unit.
Their positive 64-bit font-style masks need the same measured SN seed; no
compiler change or narrowed font interface is required. The real 40-byte
caption records and twelve initialized layout halfwords replace the older
scratch-buffer guesses. Both routines have 27 placements in each release;
the whole-file option must preserve every existing C definition in that unit.
All 81 placements of each caption and the unit's existing C were verified
through the three complete strict builds, with no fallback to assembly.

The linked build also encountered an existing 48-byte formatter pool containing
four string records with padding followed by numeric constants. Its source,
profile, old assembler object and new assembler object are byte-identical; the
failure was the numeric-only assembly-input grammar. The interleaver now accepts
only annotated `.asciz` records whose literal/NUL bytes and explicit zero
alignment agree. It still requires a whole, byte-equal, relocation-free input
section and rejects ambiguous or partial records. Bare strings without that
evidence remain unsupported. Tests cover mixed records, aliases, adjacent pools,
escaping and rejection cases; no string or compiler section is rewritten.

### `la` of a gp symbol with an addend

Retail mixes forms for one gp table: `la D` is `addiu reg,$gp,D` but `la D+4`,
`D+8`, `D+12` are absolute `lui; addiu` (func_00294F10 at -G64,
func_L01_003801B8 at -G8). Our gas, like SCE's 991111 `as.exe`, keeps `$gp`
for every addend. SN's `ps2eeas` (checked under wine on authored controls,
-G8 and -G64) uses the absolute pair for any nonzero addend, whatever the
symbol size, `.extern` size or local `.sdata` definition. It does the same
for loads and stores, but retail does not: forcing that half on changes 17
matched units, so only the `la` half is modelled.

Patch 0062 exposes it as `-Wa,--r5900-la-addend=sn`; the default and `gnu`
keep the old output. Forced on over all 8905 units of the three releases it
changes one matched unit, `L00_003F9570-g8.c`, whose `$gp` `la` was written as
table+16. That address is past the 4-float table, so it is a separate retail
object; the unit now names it `D_L00_001B0A80` (owner ruling 8 November 2026)
and the forced-on sweep changes nothing. With every access through the SDATA
alias, func_00294F10's coefficient loops and func_L01_003801B8's column
pointers take retail's form. [tests/test_la_addend.py](../../tests/test_la_addend.py)
covers both profiles, unchanged loads/stores and invalid options.

## Reading output and identifying limits

Compare R5900 words and resolved relocations, not mnemonics alone. Move can become
daddu; immediate addu becomes addiu; immediate sltu becomes sltiu. R5900 c.lt.s
and generic-MIPS c.olt.s may name the same word. A listing may display raw file
bytes in opposite order from a numeric instruction word.

Mult/mult1 can write a GPR: decode rd (bits 15-11) and follow its consumers.
Missing mflo does not imply a dead multiply. Por, lq/sq, unaligned doubleword
transfers and broad MMI prefixes alone are not handwritten-code evidence. Neither
compiler supplies a sync pattern; ASM_FUNC classification still needs the
evidence/review required by AGENTS.md.

A positive stack adjustment at an entry may be residual epilogue/fill. Establish
surrounding flow/returns and incoming references; missing jr alone is insufficient.
Change the generator in tools/levels.py, never the generated catalogue by hand.

Tools/check.py can pass while linking fails: other local C sections, symbol-value
consistency and data placement are whole-program constraints. The build now places
complete compiler `.rodata`/`.rdata` branch-table sections when every R_MIPS_32
entry resolves to the correct already-placed C case destination. It interleaves
the unchanged compiler section with the remaining retail data, then compares all
loaded bytes. Dependencies are object-scoped; unrelated sections cannot satisfy
them. Complete relocation-free scalar `.rodata`/`.rdata` sections are also
accepted when their text-derived address, alignment and complete bytes agree
with exactly one initialized retail data section and load segment. Conflicting
addresses within an object, cross-object borrowing, overlapping claims, partial
spans, and relocated/mixed pools are rejected. No generated section is rewritten;
data credit is not inferred from placing it. Unsupported `.sdata` remains
unplaceable. See
[switch-table qualification and limits](../contributing/matching-blockers.md#blocker-06).

A legacy table already in retail can use its measured symbol and computed goto;
a static label-address array keeps legitimate arms in discarded data. That array
must describe the right arms and earns no matched-data credit. New table support
does not independently requalify those existing source constructs.
Do not assume every jtbl_/D_ spelling binds identically across releases.

## Qualification and controls

Rebuild the complete recipe after toolchain changes. Compose transforms, rather
than restoring an earlier file that drops a division/frame/zero fix. The recipe
pins sources, checks insertion points and runs authored EE controls. Never edit
generated compiler output.

For opt-ins compare default, enabled and explicitly disabled modes, including
negative controls; then compare the same configured corpus under both tools.
Separate non-debug differences from .mdebug. Synthetic fixtures have no retail
oracle, and a same-size draft screen is not a match or current progress.

| Mechanism | Maintained controls |
| --- | --- |
| Zero folding/clear scheduling | [test_zero_ti_store.py](../../tests/test_zero_ti_store.py) |
| CSE edges/block order | [test_gcse_unsplit_edges.py](../../tests/test_gcse_unsplit_edges.py), [test_keep_block_order.py](../../tests/test_keep_block_order.py) |
| gcse load kills | [test_gcse_store_kills_loads.py](../../tests/test_gcse_store_kills_loads.py) |
| Division-guard slot barrier | [test_trap_delay_barrier.py](../../tests/test_trap_delay_barrier.py), [test_trap_redundant_barrier.py](../../tests/test_trap_redundant_barrier.py) |
| SDK assembler slot swaps | [test_swap_branch_slots.py](../../tests/test_swap_branch_slots.py) |
| Division label floor after a call | [test_div_label_after_call.py](../../tests/test_div_label_after_call.py) |
| No giv recombination | [test_no_recombine_givs.py](../../tests/test_no_recombine_givs.py) |
| Copies and RTL contract | [test_qcopy.py](../../tests/test_qcopy.py), [test_qcopy_rtl.py](../../tests/test_qcopy_rtl.py) |
| Copy scheduling | [test_qcopy_barrier.py](../../tests/test_qcopy_barrier.py) |
| Annulled wide stores | [test_no_annulled_wide_stores.py](../../tests/test_no_annulled_wide_stores.py) |
| Stack por form | [test_zero_ti_por.py](../../tests/test_zero_ti_por.py) |
| TImode reload count | [test_ti_one_gpr.py](../../tests/test_ti_one_gpr.py) |
| Inheritance into non-spill registers | [test_reload_reg_used_guard.py](../../tests/test_reload_reg_used_guard.py) |
| Null-pointer-check pass | [test_no_null_pointer_checks.py](../../tests/test_no_null_pointer_checks.py) |
| Width-ordered quad saves | [test_narrow_saves_below.py](../../tests/test_narrow_saves_below.py) |
| 16-byte slots for TImode GPR saves | [test_wide_saves_below.py](../../tests/test_wide_saves_below.py), [wide_saves_below.c](../../tests/fixtures/wide_saves_below.c) |
| Unflattened giv start | [test_mult_add_no_flatten.py](../../tests/test_mult_add_no_flatten.py), [mult_add_no_flatten.c](../../tests/fixtures/mult_add_no_flatten.c) |
| Static-chain alias seed | [test_no_static_chain_base.py](../../tests/test_no_static_chain_base.py), [no_static_chain_base.c](../../tests/fixtures/no_static_chain_base.c) |
| Integer words stored into floats | [test_keep_float_pun_source.py](../../tests/test_keep_float_pun_source.py), [keep_float_pun_source.c](../../tests/fixtures/keep_float_pun_source.c) |
| Extra biv increments | [test_no_extra_increment_givs.py](../../tests/test_no_extra_increment_givs.py), [no_extra_increment_givs.c](../../tests/fixtures/no_extra_increment_givs.c) |
| Sticky volatile sets (default) | [test_sticky_volatile_sets.py](../../tests/test_sticky_volatile_sets.py), [sticky_volatile_sets.c](../../tests/fixtures/sticky_volatile_sets.c) |
| Masks/sign seed | [test_dli_masks.py](../../tests/test_dli_masks.py) |
| Inline li.d into GPRs | [test_inline_li_d.py](../../tests/test_inline_li_d.py) |
| Hazard labels | [test_hazard_labels.py](../../tests/test_hazard_labels.py), [hazard_labels.s](../../tests/fixtures/hazard_labels.s) |
| Block-move loop padding | [test_block_move_loop.py](../../tests/test_block_move_loop.py) |
| Function-address weight in local-alloc | [test_la_funcref_weight.py](../../tests/test_la_funcref_weight.py), [la_funcref_weight.c](../../tests/fixtures/la_funcref_weight.c) |
| Consecutive truncation scratch reuse | [test_fix_scratch_reuse.py](../../tests/test_fix_scratch_reuse.py), [fix_scratch_reuse.c](../../tests/fixtures/fix_scratch_reuse.c) |
| Constant loads beside a dying store | [test_sched_defer_const.py](../../tests/test_sched_defer_const.py) |
| Hard-register sets first on a sched1 tie | [test_sched_global_yield.py](../../tests/test_sched_global_yield.py) |
| Call-clobbered stores first on a sched2 tie | [test_sched_store_clobbered_first.py](../../tests/test_sched_store_clobbered_first.py) |
| Quadword clear holds the store slot | [test_sched_clear_holds_store.py](../../tests/test_sched_clear_holds_store.py) |
| Call address vs pending FP stores | [test_sched_call_addr_float.py](../../tests/test_sched_call_addr_float.py) |
| FP user variables last in local-alloc | [test_la_float_vars_last.py](../../tests/test_la_float_vars_last.py) |
| Reload round robin rules | [test_reload_rotation.py](../../tests/test_reload_rotation.py) |
| cse/reload_cse argument rules | [test_cse_arg_rules.py](../../tests/test_cse_arg_rules.py) |
| sched2 barrier hold | [test_sched2_barrier_hold.py](../../tests/test_sched2_barrier_hold.py) |
| L06 PRE/cse/sched2 rules | [test_l06_rules.py](../../tests/test_l06_rules.py) |
| func_0028D1E8 rules | [test_d1e8_rules.py](../../tests/test_d1e8_rules.py) |
| func_002D4948 rules | [test_d4948_rules.py](../../tests/test_d4948_rules.py) |
| L00 ring twin rules | [test_l00_rules.py](../../tests/test_l00_rules.py) |
| func_002B44C0 rules | [test_b44c0_rules.py](../../tests/test_b44c0_rules.py) |
| func_002859C8 rules | [test_d59c8_rules.py](../../tests/test_d59c8_rules.py) |
| func_003478F0 rules | [test_d78f0_rules.py](../../tests/test_d78f0_rules.py) |
| FP constant first (local-alloc) | [test_la_fp_const_first.py](../../tests/test_la_fp_const_first.py) |
| Frame-pointer PRE hash 112 | [test_gcse_hash_fp_112.py](../../tests/test_gcse_hash_fp_112.py) |
| func_L04_0040AD28 rules (global-alloc, sched2) | [test_l04_ad28_rules.py](../../tests/test_l04_ad28_rules.py) |
| func_0034CEA0 rules (gcse, sched2, reload, alias, reorg, regmove) | [test_cea0_rules.py](../../tests/test_cea0_rules.py) |
| PRE hash offsets fp-59 / parm-91 (PAL and USA v2.00 func_0034CEA0 copies) | [test_gcse_hash_fp_59.py](../../tests/test_gcse_hash_fp_59.py) |
| PAL func_L11_004580E8 copy rules (sched1, global-alloc) | [test_l11_dce0_rules.py](../../tests/test_l11_dce0_rules.py) |
| After-reload order hint (fakematch) | [test_sched2_order.py](../../tests/test_sched2_order.py) |
| func_US2_002CD670 rules (sched1 live length, combine) | [test_cd670_rules.py](../../tests/test_cd670_rules.py) |
| func_PAL_002CD520 rule (local-alloc) | [test_cd520_rules.py](../../tests/test_cd520_rules.py) |
| func_002CC6B0 rules (flow, local-alloc, sched1) | [test_cc6b0_rules.py](../../tests/test_cc6b0_rules.py) |
| func_L04_00417308 rules (final, local-alloc, sched1, cse, loop, global-alloc) | [test_l04_17308_rules.py](../../tests/test_l04_17308_rules.py) |
| func_L17_003E8A58 rules (stmt, combine, sched1, sched2) | [test_l17_rules.py](../../tests/test_l17_rules.py) |
| func_L05_0042B2C0 switches (loop, cse, sched1 order hint) | [test_l05_42b2c0_rules.py](../../tests/test_l05_42b2c0_rules.py) |
| Quadword block moves | [test_block_move_quad.py](../../tests/test_block_move_quad.py) |
| Asm-word loop padding | [test_count_asm_words.py](../../tests/test_count_asm_words.py) |

Copy controls cover volatile/unaligned/scalar/quadword memory, calls, integer/FP
branches, loop placement and complete pairs outside slots. Clear controls cover
shared/live/returned zeros and signed displacements. The mask test covers 465
positive long-run intervals in four registers plus 32 boundary controls: 1,988
outputs in each default/signed/unsigned profile.

Historical same-source scopes measured on 21 October 2026, not current totals:

| Change | Scope and result |
| --- | --- |
| Clear scheduling | 767 preceding units: 756 identical, ten debug-only, one witness code change |
| Displaced zero fold | 775 preceding units: no non-debug change, eleven debug-only |
| CSE/block-order options | 775 preceding units: identical with options off, individually forced and combined |
| Grouped copies/masks | 779 units: four new witness units change non-debug sections; eleven debug-only |
| Positive long-run masks | 780 units: only new double-adder changes non-debug sections; eleven debug-only |
| Fraction union/sign seed | 781 units: only new multiplier changes code; eleven debug-only |
| Hazard labels | 779 other units: no code change even when forced; one debug-only |
| Copy barrier | 794 preceding units plus twelve default witnesses identical; forcing eight existing qcopy units also changes none |
| Wide-store policy | 796 preceding units: default unchanged; forced option changes only two new witnesses |
| Stack por option | 806 preceding units: default unchanged; forced option changes four former architectural-zero stack-clear units |

These scopes qualify mechanisms, not an unknown shipping toolchain. Default
neutrality does not prove that enabling an option in another unit is safe.

Final acceptance is tools/build.py with --strict for every affected program: all
C placements accepted and every loaded byte, segment property and entry point
equal to the matching private reference. Check every applicable release under
versions.md. Progress consistency uses --check; regeneration is separate.
Keep unresolved attempts and reopening evidence in nonmatching/ and the shared
blocker document, rather than appending session diaries here.
