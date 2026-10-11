# USA v1.01 trials in the `-G8` units

Exploratory candidates for the accepted v1.01 target. Each file is one clean small function whose extent comes from Ghidra's function body and whose flags come from `config/segments/ntsc-u-unit-flags.tsv`. They add **no matching credit**: the comparison masks relocation fields (`jal`, `%hi`/`%lo`, `$gp`-relative immediates) and uses a rebuilt compiler chain, not the qualified one. None is reserved or integrated.

Check one with `python scripts/try_function.py trials/usa-v1/<Name>.c --region ntsc-u --elf <reference>/boot.elf --address <addr> --size <n> --mask-relocs --flags "-O2 -G8 -ffunction-sections[ -fno-gcse]"`. Small data needs `extern T x __attribute__((sda));` for a `$gp`-relative access; a plain extern or array gives the absolute `lui` form.

| Function | Address | Bytes | Extra flags | Result |
| --- | --- | ---: | --- | --- |
| SetD1A8A60To3 | 0x00287E60 | 12 | | words equal |
| SetD1A8A64To1 | 0x00287E98 | 12 | | words equal |
| GetShortD1BAD04 | 0x00287E70 | 12 | | words equal |
| ClearShortD1BAD04 | 0x00287E80 | 12 | | words equal |
| IsD1A8B84Set | 0x00288D30 | 12 | | words equal |
| SetD1A7B8CTo1 | 0x00288D70 | 12 | | words equal |
| IsByteD1A7A0ASet | 0x00288D58 | 16 | | words equal (scalar extern; arrays gave a different register) |
| SetD1A9018To1 | 0x00290670 | 12 | -fno-gcse | words equal |
| IsD1A9020Three | 0x00290748 | 16 | -fno-gcse | words equal |
| SetD1A9A58ToMinus1 | 0x0029BCC8 | 12 | -fno-gcse | words equal |
| ReadIndirect68Plus18 | 0x002B5D28 | 12 | -fno-gcse | words equal |
| GetWordD1F2A30 | 0x002C9A50 | 12 | -fno-gcse | words equal |

Not attempted: the four 16-byte scale accessors at `0x2828B8`, `0x2828F0`, `0x282928`, `0x282938` (`lwc1; nop; jr; mul.s`): the rebuilt chain omits the `nop` after the load. Ghidra has no function at `0x2828B8`, so those extents are heuristic.
