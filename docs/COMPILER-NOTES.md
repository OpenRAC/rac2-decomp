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

Check the current RAC1 source **and its active build inputs** before rejecting a
source method or adding a compiler mechanism. At revision
[`e7e787ed`](https://github.com/OpenRAC/rac1-decomp/tree/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec),
`config/text.objects` and `Makefile.sn` include these examples:

- [`movie/vobuf.c`](https://github.com/OpenRAC/rac1-decomp/blob/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec/src/game/movie/vobuf.c#L68)
  and [`hud.c`](https://github.com/OpenRAC/rac1-decomp/blob/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec/src/game/hud.c#L469)
  use volatile memory fields to retain reloads. Such a field need not be MMIO:
  establish the actual access widths, offsets and ordering from the retail body.
  A synthetic volatile local or extra access is not equivalent evidence.
- [`map.c`](https://github.com/OpenRAC/rac1-decomp/blob/e7e787ed94f0d56c1ab617e7abdb83ac6db787ec/src/game/map.c#L642)
  declares the same target with different integer/FP interleavings. The EE assigns
  the two banks independently. A typed interleaving may change argument setup
  scheduling while preserving the call, provided order, count and widths within
  each bank, stack slots, return contract and side effects remain unchanged.
  This does not justify permuting arguments inside a bank or omitting an argument.

RAC2 already uses this call-shape method in `func_0030E700` and Barlow helpers.
Different C declarations across units need a consistent interface or adapter for
a native ABI; an EE match alone does not establish a working native port.
Qualify the actual RAC2 source/profile and every carrying release, rather than
assuming that an example in RAC1 guarantees a match here.

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

This reference groups qualified compiler mechanisms and useful C source shapes by
topic. Open cases belong in [MATCHING-BLOCKERS.md](MATCHING-BLOCKERS.md). The source
recipe, per-file flags and complete linked build take precedence over historical
observations; this document is not a progress report or a reconstruction of the
unknown shipping toolchain.

Source-shape observations cited from [PR #295](https://github.com/OpenRAC/rac2-decomp/pull/295)
were measured on both USA releases. Their integration status and PAL qualification
belong to that PR; they are not additional project-progress claims.

## Identity, tools and reproduction

| Input | Maintained implementation | Role |
| --- | --- | --- |
| Game C | [tools/compiler/build.sh](../tools/compiler/build.sh) | Public GNU EE 2.9-ee-991111b cpp/cc1, pinned Lombyte sce-991111b patches and measured transformers |
| SDK C | [tools/compiler/sdk/build.py](../tools/compiler/sdk/build.py) | Public-source Sony EE-GCC 2.9-ee-991111-01, selected with the sdk prefix in config/cflags.txt |
| Assembly from either C frontend | Source-built game GNU as | Qualified immediate, hazard and padding rules |
| Remaining assembly reconstructed from the disc | Locally supplied SN ProDG 2.0 Ps2EeAs.exe | Separate from the GNU-assembled C-object path |
| Final link | Locally supplied SN ld.exe | Places the objects before comparison against retail |

The GNU archive is `gnu-ee-binutils-gcc-1.1.tar.gz`, SHA-256
`1f518043e252d6eda726386971d52eda26541ab936ea73a9783d73712b595f92`, target
`mips64r5900-sf-elf`. [CREDITS.md](../CREDITS.md) records the public sources.
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

See [BUILDING.md](BUILDING.md) for setup and [VERSIONS.md](VERSIONS.md) for releases.
Flags are per file in [config/cflags.txt](../config/cflags.txt). A `*-g8.c` sibling
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

`-G8` can change allocation even without GP accesses: `func_L17_003BCBC8` puts
colour constants in different registers. The effect can be a loop hoist: with
`-G0`, cc1 lifts the `lui` of a level global's address out of the loop into a
callee-saved register and saves it; with `-G8` it re-materialises `lui`/`lw` at
each use, which is what retail does (`func_L10_004174C8`, `func_L02_003CCFE8`).
A successful profile is not proof of the original SDK flags.

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
[neutralise_timode_anchor.py](../tools/compiler/transformers/neutralise_timode_anchor.py),
[ascending_save_order.py](../tools/compiler/transformers/ascending_save_order.py) and
[reorder_save_blocks.py](../tools/compiler/transformers/reorder_save_blocks.py).
The reorder consumes the ascending-order transformer's output. Replacing `mips.c`
with an older file also removes the zero-fold code called by `toplev.c`.

[disable_frame_order_default.py](../tools/compiler/transformers/disable_frame_order_default.py)
keeps generic frame scheduling by default; `-mastra-keep-frame-order` is an explicit
experiment. `func_002B7170` needs the generic order plus measured source lifetimes
and stores. No frame-order option fixes arbitrary entry-block allocation.

Short-loop padding must run after delay-slot scheduling: this C pipeline uses GNU
`as`, rather than the assembler assumed by patch 0054.
[enable_loop_padding.py](../tools/compiler/transformers/enable_loop_padding.py)
restores the hook.
[count_trap_length.py](../tools/compiler/transformers/count_trap_length.py) counts a
`TRAP_IF` by its machine-description length: a division guard is branch plus break,
not one word. Counting one overpads `func_0028B950`; `func_0034FB20` is the 168-byte
polling-loop witness.

[count_block_move_length.py](../tools/compiler/transformers/count_block_move_length.py)
does the same for block moves. A structure copy of 0x40 bytes or more becomes a loop
of one `movstrsi_internal2` insn (its loads) and one `movstrsi_internal3` insn (its
stores); counted as one word each, every such loop looked five words long and got two
NOPs before its branch. Retail never pads them: the unaligned `ldl`/`ldr`/`sdl`/`sdr`
loop is 19 words and the aligned `ld`/`sd` loop 11. Counting the two insns by their MD
length (20 and 1) keeps both above the seven-word threshold. Retail witnesses, all
unpadded: `func_L08_003C6AB0` (both loops, three places), `func_002F7738` (seven
loops), `func_L00_002FC980` (27 places), `func_L30_0040B9D8`, `func_002AF0A8`. No
matched function changes: `build.py all --strict` is OK with and without the patch.
Control: [test_block_move_loop.py](../tests/test_block_move_loop.py), where a
four-word store loop keeps its three NOPs.

[block_move_quad.py](../tools/compiler/transformers/block_move_quad.py) gives those loops
retail's quadword form. `expand_block_move` capped the alignment at the 8-byte word, so a
structure of 16-byte alignment copied by `ld`/`sd`: four scratch registers per 32-byte round
and four more for the leftover. Retail has `lq ; lq ; sq ; sq ; addiu ; bne ; addiu` with
`lq ; sq` for the leftover, the shape of `block_move_loop` (`src + bytes`, unaligned label,
`bne` on the source pointer) and not of a C loop. The alignment now reaches
`output_block_move`, which has a quadword case. Copies of 0x40 bytes or less still go through
`move_by_pieces` at word alignment. Witnesses: `func_L12_00418418` (one place) and
`func_L03_003E4148` (eight) become exact, `func_L12_0041BF88`'s six copies each lose their six
extra words. All 5,849 compilable units give the same assembly with and without the patch, so
nothing already matched moves. Control: [test_block_move_quad.py](../tests/test_block_move_quad.py),
where an 8-byte-aligned page keeps `ld`/`sd` and a 0x40-byte copy keeps its pieces.

The padding counts words, as the retail assembler does, for the two 16-byte copies too:
[count_asm_words.py](../tools/compiler/transformers/count_asm_words.py) counts an asm
statement by its instruction count (`qcopy` is `lq` plus `sq`) and the grouped
`rac2_qcopy` pattern by its length of 2. Counted as one, a copy loop got one NOP too many.
Retail evidence: in levels 0, 4 and 11, 44 seven-word loops holding an `lq`/`sq` pair
(`lq ; lq ; sq ; sq ; addiu ; bne ; addiu`, `func_00288870`, `func_002DE990`) carry no pad,
and six-word ones (`lq ; sq ; addiu ; addiu ; bgtz ; addiu`, `func_L00_003ABEC0`) carry
exactly one. Witness: the three-row matrix copy in `func_L00_0041CB80` (27 places).
It runs after count_block_move_length.py and extends the same counter condition.
No matched function changes: `build.py all --strict` is OK with both patches.
Test: [test_count_asm_words.py](../tests/test_count_asm_words.py).

### Quadword saves and return slots

Patch 0058 enables `-mastra-quad-saves` per file: all GPR slots widen to TImode and
the GPR order retains the released descending walk; default output is unchanged.
Witnesses include `func_00119BC8` (48 bytes), `func_00115F28` (80) and
`func_00115C90` (92). The last also needs its failure value compared as unsigned
`0xFFFFFFFF` to preserve the immediate sequence.

Patch 0057 enables `-mastra-split-trunc-slot`: split `truncdisi2` after reload and
before scheduling so its second shift can fill the return slot. `func_0012E8C8`
changes from 32 to retail's 28 bytes. Dedicated files prevent either option from
silently changing neighbouring definitions.

### Prototypes, lifetimes and varargs

- Preserve actual argument count and return width. A value-returning call defines
  `$v0` and can move the next constant to `$v1` (`func_00339F28`, `func_00343A30`).
  Do not invent a void return or an assembler-name alias to steer allocation.
- An existing reconstructed declaration is evidence to audit, not an oracle.
  `func_002AE730` writes its packed word through an output pointer; its last
  packing call also leaves that value in v0. Current RAC1 and 146 direct calls
  in each RAC2 release support an output-only interface: none consumes that
  residual result. Correcting the definition and caller declarations together
  preserves matching bytes. Do not infer a returned value solely from a register
  left live at the epilogue, or infer void solely because result paths differ.
- A body that ignores a formal does not prove a zero-argument API.
  `func_001261F0` retains the real 32-bit `sceGsSyncV` mode argument, supported
  by the public OpenGOAL interface and the game's zero-valued callers. The
  matched preview helper `func_00300048` similarly retains its observed unused
  object argument. Check callers or an independent interface before changing a
  canonical declaration, and never add a synthetic use of an unused formal.
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
described in [AGENTS.md](../AGENTS.md#naming-in-c), and level `D_LNN_XXXXXXXX`
data names. When a callee/data pairing changes by
program, use `ref_LNN_XXXXXXXX_kk`. Zero-padding a level address is not enough to
identify its canonical function. See [LEVELS.md](LEVELS.md).

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

[qcopy_pattern.py](../tools/compiler/transformers/qcopy_pattern.py) implements the
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

[qcopy_barrier.py](../tools/compiler/transformers/qcopy_barrier.py) adds
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

[fold_zero_ti_store.py](../tools/compiler/transformers/fold_zero_ti_store.py) folds a
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

[fold_zero_ti_return_value.py](../tools/compiler/transformers/fold_zero_ti_return_value.py)
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

[ti_one_gpr.py](../tools/compiler/transformers/ti_one_gpr.py) is unconditional. The
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
and local-alloc read the same macro. [tests/test_ti_one_gpr.py](../tests/test_ti_one_gpr.py)
checks authored controls: five reloaded zeros between calls rotate `$v1`, `$v0`,
`$v1`, `$v0`, `$v1` (the pair model: `$a1`, `$v0`, ...), a shared stack zero beside a
live call value takes `$v1` (pair model: `$a1`), and a lone zero keeps `$v0`.

### Inheritance into a register the insn's pseudos hold

[reload_reg_used_guard.py](../tools/compiler/transformers/reload_reg_used_guard.py) is
unconditional. The archive's `reload_reg_free_for_value_p` returns 0 for a register in
`reload_reg_used`, which `choose_reload_regs` fills with every register outside the insn's
spill set (`IOR_COMPL_HARD_REG_SET (reload_reg_used, chain->used_spill_regs)`). Patch 0047,
the GCC 2.95.2 reload1.c in Lombyte's stack, drops that test, so reload could inherit a
spilled pseudo's value into a hard register that a pseudo of the same insn holds. The
transformer restores the archive's test and leaves the rest of 0047 alone.

The visible case is a count in a stack slot, incremented and then compared: the increment's
output reload leaves the value in `$v0`, and local-alloc gives the `slt` result `$v0` too.
Without the test the compare inherits it (`addiu $v0,$v0,1; sw $v0,n; slti $v0,$v0,128`);
with it the compare reloads the slot (`sw $v0,n; lw $v1,n; slti $v0,$v1,128`), and the
round-robin reload registers after it move on by one, as retail's do.

Witnesses: `func_L00_003C5B88` (1,804 bytes) and its 22 copies in other levels are exact
under it: the count reload after `n++` and the index reloads in `$a0` were their only
differences. Every matched function of the 28 programs compiles to the same bytes with and
without it (`tools/build.py all --strict`, 28 of 28). Of 625 profiled near misses in
`nonmatching/`, 57 compile differently; 9 of their functions come closer to retail,
3 move further and the rest are unchanged. [tests/test_reload_reg_used_guard.py](../tests/test_reload_reg_used_guard.py)
checks the anchor and two authored controls: a count compared after its increment is
reloaded into `$v1`, and an increment whose reload register is a spill register of the
compare is still inherited.

### Clear scheduling and materialized stack zeros

| Option | Effect | Limit |
| --- | --- | --- |
| -frac2-zero-ti-barrier | Selected isolated zero stores get a scheduling barrier | The pre-reload heuristic also selects some displaced clears; it is not a recovered macro detector |
| -frac2-zero-ti-por | Suppress zero folding at bare 0($sp) | Other register addresses still fold; mixed forms at the same address cannot be distinguished per file |

[zero_ti_store_barrier.py](../tools/compiler/transformers/zero_ti_store_barrier.py)
selects before reload an isolated const-zero TImode store between calls/labels/jumps;
shared zeros keep normal C lowering. After reload it selects an architectural-zero
TImode store. Lowering ready cost alone did not reproduce the dependences.
`func_L00_003BFF68` matches 12/12 with the switch and 0/12 without it.

[zero_ti_por.py](../tools/compiler/transformers/zero_ti_por.py) is a statement about
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

[gcse_store_kills_loads.py](../tools/compiler/transformers/gcse_store_kills_loads.py) is
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
[tests/test_gcse_store_kills_loads.py](../tests/test_gcse_store_kills_loads.py) checks the
transformer and authored controls: a global is loaded again after stores to another record,
reused when no store intervenes, and loaded again after a call.

### reorg: a division guard ends the delay-slot search

[trap_delay_barrier.py](../tools/compiler/transformers/trap_delay_barrier.py) is
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
compiled differently. [tests/test_trap_delay_barrier.py](../tests/test_trap_delay_barrier.py)
checks the transformer and authored controls: an argument set above a guard stays there and the
call keeps an empty slot, and without a division the call's slot is filled as before.

### reorg: a division guard ends the redundant-insn search

[trap_redundant_barrier.py](../tools/compiler/transformers/trap_redundant_barrier.py) is
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
[tests/test_trap_redundant_barrier.py](../tests/test_trap_redundant_barrier.py)
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

### SDK objects: the assembler fills the slots the compiler leaves

[swap_branch_slots.py](../tools/compiler/transformers/swap_branch_slots.py) adds the opt-in
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
[tests/test_swap_branch_slots.py](../tests/test_swap_branch_slots.py) checks the transformer
and authored controls: without the option every slot gets a `nop`; with it a store, a load and
a sign extension move into the slot, and a branch that reads the previous result or carries a
label still gets a `nop`.

### reorg: which global loads may fill a slot

No compiler change: reorg.c, resource.c and jump.c in this tree are the 2.9-ee-991111b
archive's apart from the documented RAC2 switches (the archive's reorg.c is stock GCC 2.95.2's
plus Cygnus's `condjump_expect_p` prediction; its resource.c predates 2.95.2's volatile and
`TRAP_IF` handling, and that is what retail used). When this cc1 and retail disagree about a
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

[no_recombine_givs.py](../tools/compiler/transformers/no_recombine_givs.py) is unconditional:
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
increments (`n_extra_increment`); that has no retail witness yet and stays on (turning it off
also changes no matched function). [tests/test_no_recombine_givs.py](../tests/test_no_recombine_givs.py)
checks the transformer and an authored loop: the digit read stays on the entry pointer
(`lbu 36(entry)`, not `-1(name + 5)`), and a one-pointer loop is unchanged.

A scalar global read across pointer stores is `fixed_scalar_and_varying_struct_p`: cc1 assumes a
fixed scalar cannot alias a varying array element, so the load is hoisted or moved over the stores.
Where retail reloads, declare the global as an array and read `[0]`: `D_L00_001B2B58[0][i] = 0` keeps
the reload and the integer index in `func_L00_003E4BF0`, and the cursor `D_001B22A8[0]` stays behind
the `t[]` stores in retained `func_00285030`, with no fence. An integer index that survives inside a
loop means no loop notes: loop.c reduces every `for` or `do` form, a `goto` loop keeps it (retained
`func_L00_003769C0`).

### Compiler control-flow passes

[tidy_condjump_fallthru.py](../tools/compiler/transformers/tidy_condjump_fallthru.py)
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

Implementations: [gcse_unsplit_edges.py](../tools/compiler/transformers/gcse_unsplit_edges.py),
[keep_block_order.py](../tools/compiler/transformers/keep_block_order.py),
[no_null_pointer_checks.py](../tools/compiler/transformers/no_null_pointer_checks.py). These are
inferences from retail and comparison with GCC 2.95, not the recovered original
patches. A lone lui at a branch target is not a unique signature of edge splitting.

Both Cygnus passes that run before cse (delete_null_pointer_checks and cygnus_merge_blocks,
one "CYGNUS LOCAL law" block) start with find_basic_blocks, which puts a
`(use (const_int 0))` after a call that ends a block. When cse then threads a branch past the
label behind that call, the blocks merge with the no-op still in them; sched1 moves it, and
local-alloc counts it, so two back-to-back address pseudos stop sharing a register. A
spawn-and-initialise block ending in a call before a re-test of the new pointer shows it:
retail has the re-test in the call's block and no no-op effect. Skipping only one of the two
passes leaves the other's count, so such a unit needs both options.

### Wide stores and annulled slots

[no_annulled_wide_stores.py](../tools/compiler/transformers/no_annulled_wide_stores.py)
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

### Transfer hazards

Mtc1 uses the next instruction's FPR read, not distance from the GPR's last write.
The expanded retail survey found 915 immediate dependencies: 897 delayed, 18 not;
the original 598 sites (587 delayed) are a subset. Cleared assembler history can
occur within a function and is not a function-boundary detector.

[u4_mtc1_helper.py](../tools/compiler/transformers/u4_mtc1_helper.py) and
[restrict_mtc1_exemption.py](../tools/compiler/transformers/restrict_mtc1_exemption.py)
retain two measured cleared-history exemptions: a0 to f0 before cvt.s.w f0,f0,
and zero to f0 before c.lt.s f12,f0. Eight first-transfer witnesses split four
requiring a nop and four not. A distance-two producer rule failed `func_002A7878`.

Ten original no-nop sites in `0x00283C28`, `0x002A677C`, `0x002E0408`,
`0x002E0558` can also be reproduced with explicit instruction ordering; ISA
selection offers another sufficient mechanism. Original directives remain unknown.
The private 89-case fixture history does not qualify every transfer in the game.

Mfc1 is interlocked on R5900: the measured boot text had 88 immediate readers in
47 functions; its only extra-nop example used handwritten VU code.
[r5900_mfc1_interlock.py](../tools/compiler/transformers/r5900_mfc1_interlock.py)
removes the MIPS-I coprocessor-load delay in append_insn for mfc1 only. Cfc2 and
label padding are not waived. `func_002ED4B8` and `func_00290680` match at 28 places.

### Labels on hazard nops

[hazard_labels.py](../tools/compiler/transformers/hazard_labels.py) adds
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

1. [neutralise_div_dslot.py](../tools/compiler/transformers/neutralise_div_dslot.py)
   keeps single-precision division/root operations out of compiler-selected delay
   slots. Retail had 0 of 19,806 div.s in slots, but 61 integer HI/LO divisions.
   Sqrt.s/rsqrt.s are extrapolated: neither occurred in that retail census and GNU
   as does not assemble rsqrt.s.
2. [pad_div_erratum_nops.py](../tools/compiler/transformers/pad_div_erratum_nops.py)
   models a measured SN 3.01 two-slot incoming floor after code labels for div.s,
   sqrt.s and rsqrt.s. Needed hazard nops count toward it; labels stay on padding.
   Sync.p imposes one nop, unlike sync/sync.l.
3. [pad_div_erratum_branch.py](../tools/compiler/transformers/pad_div_erratum_branch.py)
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
floor. [test_div_label_after_call.py](../tests/test_div_label_after_call.py) covers
the label, no-label and noreorder cases.

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
[inline_li_d.py](../tools/compiler/transformers/inline_li_d.py) takes the whole value for every
`li.d` into a GPR on a 64-bit ISA (the `F` operand of M_LI_D) and builds it with load_register;
FPR forms and 32-bit ISAs are unchanged. `--r5900-pool-li-d` restores the archive's pooling, and
`tools/build.py` (`split_flags`) passes it to every unit of the SDK profile (`sdk` flags in
`config/cflags.txt`), so no flags line changes and the SDK objects assemble as before; no game
unit needs a switch. `--r5900-inline-li-d` states the default explicitly. An earlier default-on
trial without the SDK opt-out broke `func_0011C090`. With the default, no matched function in
any release compiled differently (`build.py all --strict`: us 28/28; pal and us2 only their
known failures). [tests/test_inline_li_d.py](../tests/test_inline_li_d.py) checks the
transformer, both profiles' words, and that only SDK units get the opt-out.

Two sign-bit loads need a zero-extending seed. Patch 0059 exposes per-object
`--r5900-sign-bit=unsigned`; pass it with `-Wa,--r5900-sign-bit=unsigned` in the
same per-file flag table. Explicit signed restores default; invalid/missing values
fail. Same value does not mean the same retail encoding.

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
[switch-table qualification and limits](MATCHING-BLOCKERS.md#blocker-06).

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
| Zero folding/clear scheduling | [test_zero_ti_store.py](../tests/test_zero_ti_store.py) |
| CSE edges/block order | [test_gcse_unsplit_edges.py](../tests/test_gcse_unsplit_edges.py), [test_keep_block_order.py](../tests/test_keep_block_order.py) |
| gcse load kills | [test_gcse_store_kills_loads.py](../tests/test_gcse_store_kills_loads.py) |
| Division-guard slot barrier | [test_trap_delay_barrier.py](../tests/test_trap_delay_barrier.py), [test_trap_redundant_barrier.py](../tests/test_trap_redundant_barrier.py) |
| SDK assembler slot swaps | [test_swap_branch_slots.py](../tests/test_swap_branch_slots.py) |
| Division label floor after a call | [test_div_label_after_call.py](../tests/test_div_label_after_call.py) |
| No giv recombination | [test_no_recombine_givs.py](../tests/test_no_recombine_givs.py) |
| Copies and RTL contract | [test_qcopy.py](../tests/test_qcopy.py), [test_qcopy_rtl.py](../tests/test_qcopy_rtl.py) |
| Copy scheduling | [test_qcopy_barrier.py](../tests/test_qcopy_barrier.py) |
| Annulled wide stores | [test_no_annulled_wide_stores.py](../tests/test_no_annulled_wide_stores.py) |
| Stack por form | [test_zero_ti_por.py](../tests/test_zero_ti_por.py) |
| TImode reload count | [test_ti_one_gpr.py](../tests/test_ti_one_gpr.py) |
| Inheritance into non-spill registers | [test_reload_reg_used_guard.py](../tests/test_reload_reg_used_guard.py) |
| Null-pointer-check pass | [test_no_null_pointer_checks.py](../tests/test_no_null_pointer_checks.py) |
| Masks/sign seed | [test_dli_masks.py](../tests/test_dli_masks.py) |
| Inline li.d into GPRs | [test_inline_li_d.py](../tests/test_inline_li_d.py) |
| Hazard labels | [test_hazard_labels.py](../tests/test_hazard_labels.py), [hazard_labels.s](../tests/fixtures/hazard_labels.s) |
| Block-move loop padding | [test_block_move_loop.py](../tests/test_block_move_loop.py) |
| Quadword block moves | [test_block_move_quad.py](../tests/test_block_move_quad.py) |
| Asm-word loop padding | [test_count_asm_words.py](../tests/test_count_asm_words.py) |

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
VERSIONS.md. Progress consistency uses --check; regeneration is separate.
Keep unresolved attempts and reopening evidence in nonmatching/ and the shared
blocker document, rather than appending session diaries here.
