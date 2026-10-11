# Compiler setup for USA v2.00: what is known and what was measured

Source of the claims below: Going Native (`Promises/RC2-Going-Decompiled`, `tools/ee/objdiff_build.sh` and `build.sh`) unless
marked **measured here**. Its text is GPL-2.0-or-later; only facts and ideas are used, nothing is copied.

## Retail is a mixed-compiler build

| Arm | Compiler | Where it comes from | Used for |
| --- | --- | --- | --- |
| `sdk29` | GCC 2.9-ee-991111, 16-byte (`sq`) callee saves | ProDG 2.0 mirror (`cc1.exe`, via wibo) | the SDK/runtime start of `core.text` |
| `engine96` | GCC 2.96-ee-001003-1, 8-byte (`sd`) callee saves | SDK 2.4 mirror (`cc1`, native i386 ELF) | the game engine, plus `-G8 -fno-schedule-insns -fno-strict-aliasing` |
| `s136os` | SN 2.95.3 BUILD 1.36 `-fopt-stack` | ProDG 3.01 mirror (`cc1.exe`) | a short list of functions |

Going Native also builds each unit with `-O2 -G0` or `-G8`, sometimes `-fno-gcse`, chosen per unit, and routes whole functions to an arm
(a unit compiles under one scheduler setting, so a unit cannot be moved to another compiler wholesale).

## Measured here on the v2.00 executable

- **Callee-save width by address.** Only 32 functions save with `sq`, all between `0x115228` and `0x119BF8`. The other 2,007 that save
  registers use `sd`, including 272 below Going Native's stated `0x131D98` boundary. So the 16-byte arm covers a small region at the
  start of `core.text`, not everything below `0x131D98`.
- **Compilers run on Linux.** `2.96-ee-001003-1/cc1` runs natively inside the rac2-linux container (copy it out of the mirror and
  `chmod +x`; clones lose the exec bit). A test function gets `sd $16,0($sp); sd $17,8($sp); sd $31,16($sp)`. ProDG 3.01's `2.95.3`
  `cc1.exe` (via wibo) gives `sq $16,32($sp); sq $17,16($sp)`, a different profile again.
- **Our chain matches the 8-byte model.** The rebuilt GNU EE chain (`docs/V2-SETUP.md`) removes the quad-save widening
  (`0001-r5900-quad-saves` reversed), so it reproduces the `sd` layout; it is the right model for about 98% of saving functions.
  The 32 `sq` functions need the same source with `0001` kept.
- **Stock 2.96 is not a drop-in.** It rejects the `sda` attribute our sources use (`candidates/boot.c`), so comparing it against the
  v1.01 proofs would not be like for like.

## Consequences

1. Keep the patched 2.9 chain for engine code; add a second chain (with `0001`) only for the 32 `sq` functions at `0x115228-0x119BF8`.
2. If a leaf function will not match, try `-G8` and `-fno-gcse` per function before rewriting the C.
3. Functions that never match under 2.9 may belong to `engine96` or `s136os`; the real `cc1` from the mirrors can be tried. `FloatToInt` was: the 2.96 and 2.95.3 `cc1` also give `$f0`, so it is handwritten (see `trials/usa-v2/README.md`).
4. Everything here is a candidate result. v2.00 has no campaign task, reservation or qualified proof yet.
