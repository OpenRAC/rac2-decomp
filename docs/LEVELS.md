# Levels

## The programs

The disc holds the boot executable (`SCUS_972.68`) and 27 levels, each with its own program.
Loading a level copies its program over the boot's memory from `0x1A7C80`: every level
carries its own copy of much of the engine, at addresses of its own, alongside its own code.
Everything below `0x1A7C80` (the boot's resident code and data) is the same in every program,
and all of them share `$gp = 0x1AEFF0`.

`tools/levels.py dump` reads them with its own ISO9660 and archive reader:

- A level's archive is `G/LEVELn.WAD`; the level's number is the archive's own word at
  `+0x08`, which is the file's number except for `G/LEVEL21.WAD`, level 30 (Insomniac Museum).
- The archive header's word pair at `+0x10` is the level data (sector offset, sector count).
- The level data opens with twelve (offset, size) slots; slot 0 is the program: a list of
  sections, each a 16-byte record (destination, size, type, entry point) followed by its
  bytes, a NOBITS section's included. Every section of one program repeats the entry
  point, and the list ends where it changes.
- Seven sections per level: `.lit` (always at `0x1A7C80`), `.bss`, `.data`, the three
  vtables (`vtbl`, `camvtbl`, `sndvtbl`) and `.text`.

The dump is checked against the boot's pinned hash, every level's entry point and the raw
hash of every function extent of the earlier catalogues (106,337 extents, all equal).

## The catalogue

`config/boot/functions.tsv` lists the boot's 3,390 functions (name, address, size).
`config/levels/functions.tsv` lists every distinct function of the levels once, with all its
places:

    name  kind  size  fingerprint  levels  places (level:address, ...)

- **kind**: `boot` (the boot has it too, and its name is the boot's), `shared` (several
  levels) or `level` (one).
- **name**: the boot's name, or `func_LNN_XXXXXXXX`, its address in the lowest-numbered
  level that has it.

Two places are one function when their instructions are equal apart from what linking
changes: jump targets and address halves are masked, except those pointing below
`0x1A7C80`, which every program shares; constants, stack slots and field offsets on
pointer arguments are compared. Two places in one program are always two functions (the
k-th copy of identical code in each level, by address, is one function), the same
instructions with different padding are two functions, and a level function takes a boot
function's name only when the pairing is unambiguous or recorded in
`config/levels/boot_pairs.tsv`.

The 27 programs hold 106,337 placements (47.4 MB); they are 7,765 distinct functions
(5.3 MB), 2,055 of them copies of boot functions. With the boot, the game is about 9,100
distinct functions, 5.5 MB of code.

An inferred function extent can start inside the preceding function's epilogue.
`tools/levels.py` corrects three measured Aranos entries before fingerprinting:
`00354DE8` to `00354DF8`, `003D54A8` to `003D54B0`, and `0040EA98` to `0040EAA0`.
Retail data and virtual-table pointers reference the corrected entries; the original
end addresses stay unchanged, and the skipped prefixes remain assembly in the build.
Correcting the second entry also groups it with Siberius's `003EBC90`, so the two
places share one definition. These corrections apply to level 00 only; regenerate
the catalogue with `tools/levels.py catalogue`, rather than editing its rows.

Level 23 has another measured entry correction: `004277B0` to `004277B8`,
referenced by the data pointer at `002ABE40`. Its 44-byte two-call wrapper ends
at `004277E4`; the eight skipped bytes remain assembly. The preceding return
at `004277A4` already restores its own frame in its delay slot, so the positive
stack adjustment at `004277B0` is a separate residue. Regenerating v1.01's
catalogue and carrying it with `tools/carry.py --version us2` gives the same
canonical wrapper at v2.00's `00428CB8`, with its end also unchanged. PAL keeps
its separate version-specific wrapper and catalogue entry.

Two mixed boot/level extents have measured entry corrections too:
`func_002C38A0` skips eight leading bytes (64 to 56 bytes), and `func_00335918`
skips 32 (68 to 36 bytes). Their canonical names and original ends are retained.
References identify the corrected entries in all 28 programs of each of the
three releases; the skipped stores/stack adjustments remain in assembly.
`FUNCTION_ENTRY_OFFSETS` applies these named corrections before fingerprinting.
The original full-extent identity preserves the level-to-boot pairing when a
shortened body becomes identical to another boot method. Regeneration validates
and retains that pairing, including on replay, rather than guessing a new name.
Regenerate the primary catalogue with `tools/levels.py catalogue`. For existing
release catalogues, apply the measured repairs with `tools/carry.py --version us2
--entries` and `tools/carry.py --version pal --entries`.

The same named rule now covers the remaining measured entries, including core
library bodies and level-only functions. Each correction is supported by an
incoming call, branch or code/data address reference at the shortened entry in every
affected program; the original ends and all skipped bytes are preserved. A rule
does not apply to a separately named method just because its full code is identical.
Both original and shortened identity collisions preserve existing names and kinds,
and replay checks all corrected copies against their measured identity.

A further 71 open catalogue rows (46 with an 8-byte prefix, 25 with 12 to 104 bytes) were
corrected the same way. In every placement of each row the prefix follows a completed
`jr $ra` and its delay slot (only filler words in between), no branch, jump or
address pair reaches it, and a GCC `addiu $sp,$sp,-N` prologue follows it; 45 of the 71
have a call, branch, address pair or data pointer at the shortened entry and 26 have
no static reference. Where the prefix holds non-filler
words (a leftover store or compare followed by a nop), these are unreachable tails of
the preceding body and stay in assembly like the rest.

Seven core functions (`func_0011F9E4`, `func_00125D94`, `func_00126104`, `func_00126DBC`
skip 4 bytes; `func_00127340` and `func_00128F48` skip 8; `func_001246D0` skips 16) were corrected
the same way. Each prefix follows a completed `jr $ra` and its delay slot, holds only linker
filler (0xCDCDCDCD) or unreachable leftovers, and every jump, address pair or data pointer that
reaches the function already targets the shortened entry.

`func_00282848` is another corrected mixed extent (72 to 16 bytes, skip 56)
in the boot and all 27 levels. Its prefix follows a completed return and
contains six positive stack adjustments plus eight nops. Across all 28
programs, no direct branch or jump, nearby address pair, or aligned loaded
word points into that prefix or at the shortened entry. The retained 16-byte
body is the float load/nop/return-delay-multiply form covered by blocker 4;
the catalogue correction does not claim a C match.

Three more rows were corrected on 26 October 2026: `func_00120354` and `func_00130A8C` skip
4 bytes (one 0xCDCDCDCD fill word; two data words point at `func_00120354`'s shortened
entry), and `func_0028FF50` skips 8 (a leftover `sw $v0,0x6C($a1)` and a nop after the
previous body's completed return) in the boot and its 27 level copies, in USA v1.01 and
v2.00 (PAL has no such row). Each prefix follows a completed `jr $ra` and its delay slot.
`func_L00_00428EE0` skips 24 bytes of filler in all 15 of its levels and in every release,
leaving an 8-byte `return 0` method that a data pointer in each level reaches.

One open row is two functions and still needs a split: `func_00115E28` (64 bytes) is
`abort` at +0 followed by a separate noreturn assert-style printer at `00115E38`, which
four `jal`s reach. Splitting it adds a boot row and changes the function count, so it
is left as one row for now. Both functions have C, newlib's `abort` and `__assert`, in
`nonmatching/core/func_00115E28.c`: the boot links byte-identical with it, and it can move
into `src/core/00115200.c` once the row is split into 16 and 48 bytes.

Release-specific rows have their own named corrections. `tools/carry.py --entries`
repairs established extents while retaining their existing identities and kinds,
rather than renaming them for the new address or merging identical short methods.
Unexpected sizes or divergent shortened copies are errors, checked before either
catalogue is written. The normal carry command still performs full cross-release
alignment and may revisit correspondences; entry maintenance does not do that or
change source files. These are catalogue repairs, not compiler changes or new C matches.

`FUNCTION_RESIDUES` excludes individually verified remnants by name and size. The
one-word entries' immediate predecessors finish with a return and its delay slot
across alignment nops, or a closed tail jump before debug-fill bytes. The static scan
found no incoming branch/call, literal pointer or straight-line address-construction
reference to those remnants. `func_002702B8` is the measured 12-byte exception: it
follows a completed return across alignment nops, has no incoming direct reference
or aligned literal pointer, and falls through into the next prologue. An identical
instruction with a different name is left alone. Removed bytes remain in assembly,
and surviving identities remain stable when the number of identical copies changes.
The rule does not classify arbitrary code without a return as filler.

`func_00335E28` is a measured 12-byte residue in the boot and all 27 levels. The
preceding function returns at `0x00335E20`, with `lw $v0,0xC($a0)` in its delay
slot at `0x00335E24`. The extent then adjusts `$sp` upward by `0x20`, has a nop,
stores `$f0` through `$v1` at offset `0xC`, and has no return; the next function
starts after a nop at `0x00335E38`. Every placement has this same boundary. The
row has no frame to restore and does not establish `$v1`. Across all 28 images,
no direct branch or call, aligned literal pointer, or nearby `lui` plus low-half
construction references it. `FUNCTION_RESIDUES` removes only this named extent
and leaves the retail bytes in place.

A boundary-only PR leaves progress reports for the later maintainer refresh.
The non-strict report check tolerates obsolete rows only for these named remnants,
with zero matching credit and no missing new entry. Unknown deletions, duplicate
rows and any retained matching credit still fail; `--check --strict` requires the
report to be regenerated. No report is rewritten by a check.

Two more kinds of row are measured from the retail bytes, not from a list of
addresses. An extent whose words are only stack adjustments and nops is the linker's
filler between two bodies, not a function, and leaves the catalogue: 257 level rows
and 225 boot rows are such filler. The absence of a `jr $ra` does not decide this on
its own - a body that ends in a trap or a tail call has no `jr $ra` and is still code
(`func_00115E90` is matched C) - and neither does the arithmetic: `addu $t0,$t1,$t2`
and `addiu $sp,$a0,16` are not filler, though the operands alone would say they
were. A four-byte extent right after a body that ends with `jr $ra` and its delay
slot is the word that body left behind: 25 level rows and 26 boot rows are such, and
they leave the catalogue as well.

Five additional boot extents are residual instructions between completed bodies:

| Former entry | Bytes | Observation |
| --- | ---: | --- |
| `func_00289018` | 4 | An isolated store through `$v0`, which the extent does not initialise |
| `func_002A77C0` | 28 | Orphan float operations reading `$f0` and `$f1`, without a complete entry/exit |
| `func_002FDB40` | 148 | A sequence of unmatched stack restores and a store through an uninitialised register |
| `func_002FED78` | 12 | A return-value assignment followed by a stack restore with no corresponding frame |
| `func_002FF0B0` | 36 | Several unmatched stack restores and a GP-relative store |

All five follow a completed return across alignment padding. The 148-byte extent
also occurs in 22 levels. Across these 27 extents, the retail scan found no direct
branch/call or aligned literal pointer into any part of them; nearby `lui` plus
address-construction pairs also supplied no entry. The qualified R5900 Ghidra boot
analysis has no function or incoming reference at these extents. Arbitrary computed
indirect targets are outside those checks. The conclusion uses the complete
neighborhood and operand lifetimes, not just the absence of `jr $ra` or FPU nops.

One further row, `func_002702B8` (12 bytes), is the same extent in the boot and all 27
levels. The previous function returns at `0x002702AC` with its delay slot at
`0x002702B0`; a nop fills `0x002702B4`. The row is `daddu $v0,$zero,$zero`, nop,
`sw $zero,0($a0)`, then falls through across a nop into the next function's prologue
at `0x002702C8`. The level placements have the same neighborhood. Across all 28
disassemblies there is no direct branch or call to the row, and scanning the loaded
program segments found no aligned literal pointer to any placement. The measured C
attempt emits the store before `jr $ra`; it cannot reproduce the row's fallthrough.
`FUNCTION_RESIDUES` removes this exact named extent by name and size; it does not
classify other return-less rows. Its fingerprint is identical in PAL and US2. Together
with the five entries above, regeneration
removes six distinct catalogue rows and 49 level placements, without changing retail
bytes.

`func_0029CF48` (12 bytes) is another measured residue in the boot and all 27 levels.
In the boot, the preceding function returns at `0x0029CF3C` with its delay slot at
`0x0029CF40`; a nop fills `0x0029CF44`. The row stores `$v0` through `$gp`, has a nop,
then adjusts `$sp` by `0x50` without a function entry or return; a nop follows before
the next prologue at `0x0029CF58`. All level placements have the same instruction
pattern and neighborhood. Across all 28 disassemblies, no direct branch or call,
aligned literal pointer, or adjacent `lui` plus low-half construction references the
row. `FUNCTION_RESIDUES` removes only this named 12-byte extent; its normalized
fingerprint is identical in PAL and US2.

`func_002DE7F0` (28 bytes) is an orphan sequence in the boot and all 27 levels.
The preceding function returns at `0x002DE7E8` with its delay slot at `0x002DE7EC`.
The row then adjusts `$sp` by `0x70`, assigns `-1` to `$v0`, stores `$v1` through
`$gp` at offset `-0x3EEC`, and adjusts `$sp` by another `0x10`; it has no entry
sequence or return and falls into the next catalogue entry's initializer at
`0x002DE810`. Across all 28 disassemblies, no direct branch or call, aligned literal
pointer, or adjacent `lui` plus low-half construction references the row.
`FUNCTION_RESIDUES` removes only this named 28-byte extent; its normalized
fingerprint is identical in PAL and US2.

`func_002E3E50` (4 bytes) is a one-instruction extent in the boot and 26 levels.
The previous function returns at `0x002E3E44` with its delay slot at
`0x002E3E48`; a nop fills `0x002E3E4C`. The row is `sd $t0,0($t1)` immediately
before the separate handwritten routine at `0x002E3E54`. Every placement has
the same return/delay/padding/isolated-store boundary. Across all 27 program
images, no direct branch or call, aligned literal pointer, or nearby `lui` plus
low-half construction references the row. `FUNCTION_RESIDUES` removes only
this named four-byte extent; it leaves the retail word in place.

`func_003411B0` (12 bytes) is a two-store fragment in the boot and all 27 levels.
The preceding 380-byte function returns at `0x003411A4` with its delay slot at
`0x003411A8`; a nop fills `0x003411AC`. The row stores zero through `$v1` at offset
`0xC`, has a nop, stores `$f12` through `$a0` at offset `0x1B8`, then has a nop before
the next function prologue at `0x003411C0`. The same neighborhood appears at every
level placement. Across all 28 disassemblies, no direct branch or call, aligned
literal pointer, or adjacent `lui` plus low-half construction references the row.
`FUNCTION_RESIDUES` removes only this named 12-byte extent; its normalized
fingerprint is identical in PAL and US2.

`BOOT_RESIDUES` in `tools/levels.py` records these measured extents. The generator
derives their normalised fingerprints from the private retail input and excludes
only matching size/fingerprint pairs in the boot and levels. It does not widen
`is_padding` to accept arbitrary stores or float operations. Their bytes remain in
the assembly rebuilt from the disc, and no C or handwritten-assembly credit is
awarded. Regeneration removes five distinct functions and 22 level placements;
it does not decompile additional code.

## The C

The layout is rac1-decomp's: every function of both catalogues appears once in `src/`, in
address order, as its C or as an `INCLUDE_ASM("...", name);` marker (`include/include_asm.h`;
here the marker is empty, since the build takes a function without C from the disassembly).

- `src/core/<ADDR>.c`: the boot's `core.text` (SDK, libc), one file per original object, as the
  linker's `0xCDCDCDCD` fill between objects shows.
- `src/game/<ADDR>.c`: the boot's `.text`.
- `src/levels/shared/LNN_<ADDR>.c` and `src/levels/NN_name/LNN_<ADDR>.c`: level functions in
  several levels and in one, in their canonical level's order.

A file is compiled one way (`config/cflags.txt`), so a file ends where the next C needs another
compiler profile. Names carried from rac1-decomp with no rac2 counterpart yet keep an `r1_`
prefix: they state no address, and the build reads their values.

A function's name says where it goes; `tools/build.py` links it at every place the
catalogue gives it. What it refers to is named by what it is: other functions by their
catalogue names, the boot's resident data `D_XXXXXXXX`, a level's data `D_LNN_XXXXXXXX`
(its address in level NN), the k-th external a function uses with no address of its own
`ref_LNN_XXXXXXXX_kk`. The value each symbol has in each program is read from the retail
bytes under the relocations of the placed functions; uses must agree, and a name that
states an address must have it (a boot address inside a level's memory is not checked
there: the level has its own copy).
