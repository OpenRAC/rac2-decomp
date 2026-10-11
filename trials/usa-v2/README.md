# USA v2.00 first trials

This directory is deliberately outside `src/` and `candidates/`: nothing here is reserved, integrated or credited. A function moves into `src/` only through a reservation and a PR of Type `matching` (see `docs/CONTINUE.md`).

Exploratory C for the USA v2.00 target, checked with `scripts/try_function.py` against the
retail words of `baserom/SCUS_972.68` using the locally built GNU EE chain (`tools/linux/`).
The chain's source hashes equal the qualified ones (`docs/V2-SETUP.md`), but v2.00 has no campaign task,
no reservation and no register entry, so these add no credit.

| Function | Address | Size | Result |
| --- | --- | --- | --- |
| `IntToFloat` | `0x284690` | 16 | all 4 words equal |
| `HasMobyGroup` | `0x31B508` | 16 | all 4 words equal (`!= 0xFF`, not `^ 0xFF`) |
| `SetPopupItemEnabled` | `0x349368` | 16 | all 4 words equal (struct array member, not pointer arithmetic) |
| `MapSetCurrentLevel` | `0x296500` | 32 | all words equal except 3 relocated fields (call, global); `-O2 -G0` |
| `ApplyGsDisplayEnv` | `0x285830` | 36 | same, `-O2 -G8` (the unit flag matters: `-G0` fails) |
| `LoadDiscToc` | `0x133A78` | 40 | same, `-O2 -G0` (also `-G8`) |
| `ListScrollerSelectNext` | `0x2CA9F8` | 60 | loop; all words equal, `-O2 -G0` |
| `ListScrollerSelectPrev` | `0x2CA9B8` | 60 | loop; all words equal. Needs a second variable and the store after the merge: `n = cur - 1; cur = n; i = n; if (i <= 0) i = count; cur = i;` |
| `CalcSaveSectionsSize` | `0x29BC68` | 56 | loop; all words equal. Pointer advanced in place with `*section` tests, `size = (size + 3) & -4` after `+= 8` and `+= section[1]` |
| `FloatToInt` | `0x2846A0` | 16 | not matched: retail converts in place (`cvt.w.s $f12,$f12`); the chain always picks `$f0` for `(int)x` at -O1/-O2/-O3, so the original was probably handwritten |

`FloatToInt` was also tried with the real `2.96-ee-001003-1` `cc1` (`-O2`, `-G0` and `-G8`, three source spellings) and with
SN `2.95.3`: all allocate `$f0` for the result. Going Native reaches the same conclusion (no C spelling reproduces the in-place
`cvt.w.s $f12,$f12` under cc1 2.9 or the 2.96 arm) and lists six functions with that pattern: `FloatToInt 0x2846A0`,
`0x283240`, `0x283278`, `0x2832B0`, `0x2A1628/0x2A1630` and `0x2BAB68`. Treat them as handwritten assembly (an assembly unit),
not as C targets.

## Real 2.96 `cc1` on the call-bearing functions

Run with `--mask-relocs` (calls and globals are linker-filled). Stock `2.96-ee-001003-1` needs `-fno-optimize-sibling-calls`
(it otherwise emits a tail `j`). Then `MapSetCurrentLevel` matches at `-G0`, like the patched 2.9 chain, but `ApplyGsDisplayEnv` and
`LoadDiscToc` do not, even with `-fno-schedule-insns -fno-strict-aliasing`: it orders the argument loads before the
`addiu $sp` while the retail starts with the frame, which the patched 2.9 chain (frame-save-first) reproduces. So the patched chain is
the better model so far; the 2.96 arm is not needed for these.

## Loops tried and not matched yet

| Function | Address | Closest result | What differs |
| --- | --- | --- | --- |
| `ReleasePlasmaSparksOwnedBy` | `0x31F320` | 3 words (`-G8`) | retail compares with `beql` and stores `$zero` in the annulled delay slot; the chain emits `bne` and puts the loop decrement in the slot. Four source spellings and the `-mastra-*` options did not change it |
| `CountSkillPointsCompleted` | `0x2B1DA8` | 4 words | retail initialises both counters before `lui/addiu` of the array base into one register; the chain hoists `lui` first and uses a second register |
| `MarkVendorSlotByItemId` | `0x2FBBF0` | 5 words | retail keeps the structure base in a register (`lui` + `addiu`, then `lw 0x740(base)`); the chain folds the count into a `%lo` load |

The real 2.96 `cc1` did worse on every loop here except `ListScrollerSelectNext` (11 words differ) and `CalcSaveSectionsSize` (10).
