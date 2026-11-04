/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 444/444 bytes, 0/27 placements; first difference 0x0.
 * Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * The timer decomposition helper and sprintf keep their defined int returns. sprintf has its
 * actual two-named-argument variadic interface. These repairs retain the frame and saved-FP-
 * constant allocation residual.
 * Earlier measurements below are historical where superseded by this note.
 */
/* Batch 3 (2026-10-28) handoff notes:
# func_L00_003DDEC8 (444 B, 27 places) -- w5 handoff, size exact, allocation differs

draft.c is the nonmatching/ draft in its own unit: L00_003DDEC8-g8.c with cflags `-O2 -G8 -ffunction-sections -mno-split-addresses` (compiles to 444 B). Differences are all allocation: retail saves $s0 (unused) and $s1 = 0x8710, frame 0xA0, FP saves f20-f24 (0.5, 0.0, -0.5, 1.0, 380.0); ours frame 0x90, $s0 = 0x8710, f20-f25: it also hoists 454.0f into a saved FP register, retail loads 454.0f straight into $f12 at each call (`lui at,0x43E3 ; mtc1 at,f12` twice) while still sharing -0.5/1.0/0.0 between the two calls (`mov.s f14,f22`...). The unused saved $s0 suggests a pseudo that is constant-folded away at reload (e.g. an int constant used only in a (f32) conversion that cse folds late). Tried: 454.0f literal vs (f32)454 (same), int local `x = 454` (runtime cvt, 452 B), and the 5 consts' order. 
Ours differs in where the constants are materialised: ours sets all of them before the first inner call, retail sets 380.0/0.5 before it and -0.5/1.0/0.0 after it, right before the outer call.

## check.py --diff (masked, differing lines only; ours | retail)
```
00_aranos_tutorial: instruction at +0x0 differs
  003DDEC8  addiu       $sp, $sp, -0x90              | addiu       $sp, $sp, -0xA0
  003DDED4  sd          $ra, 0x58($sp)               | sd          $s1, 0x58($sp)
  003DDED8  swc1        $f25, 0x88($sp)              | sd          $ra, 0x60($sp)
  003DDEDC  swc1        $f24, 0x80($sp)              | swc1        $f24, 0x90($sp)
  003DDEE0  swc1        $f23, 0x78($sp)              | swc1        $f23, 0x88($sp)
  003DDEE4  swc1        $f22, 0x70($sp)              | swc1        $f22, 0x80($sp)
  003DDEE8  swc1        $f21, 0x68($sp)              | swc1        $f21, 0x78($sp)
  003DDEF0  swc1        $f20, 0x60($sp)              | swc1        $f20, 0x70($sp)
  003DDEFC  ori         $s0, $zero, 0x8710           | ori         $s1, $zero, 0x8710
  003DDF08  mtc1        $at, $f25                    | mtc1        $at, $f24
  003DDF18  addu        $a0, $a0, $s0                | addu        $a0, $a0, $s1
  003DDF1C  lui         $at, 0x43E3                  | lui         $at, 0x1B
  003DDF20  mtc1        $at, $f24                    | lwc1        $f0, 0x2704($at)
  003DDF24  lui         $at, 0x0                     | daddu       $a0, $v0, $zero
  003DDF28  lwc1        $f0, 0x0($at)                | mul.s       $f0, $f0, $f24
  003DDF2C  daddu       $a0, $v0, $zero              | add.s       $f0, $f0, $f20
  003DDF30  lui         $at, 0xBF00                  | .word       0x46000064                   # cvt.w.s     $f1, $f0 # 00000000 <InstrIdType: CPU_CO
  003DDF34  mtc1        $at, $f23                    | mfc1        $v1, $f1
  003DDF38  lui         $a1, 0x6044                  | mtc1        $v1, $f13
  003DDF3C  mul.s       $f0, $f0, $f25               | nop
  003DDF40  lui         $at, 0x3F80                  | cvt.s.w     $f13, $f13
  003DDF44  mtc1        $at, $f21                    | lui         $at, 0xBF00
  003DDF48  mtc1        $zero, $f22                  | mtc1        $at, $f22
  003DDF4C  mov.s       $f12, $f24                   | lui         $at, 0x3F80
  003DDF50  mov.s       $f14, $f23                   | mtc1        $at, $f23
  003DDF54  mov.s       $f15, $f21                   | lui         $a1, 0x6044
  003DDF58  add.s       $f0, $f0, $f20               | mtc1        $zero, $f21
  003DDF5C  mov.s       $f16, $f22                   | ori         $a1, $a1, 0x2D00
  003DDF60  .word       0x46000064                   # cvt.w.s     $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS> | lui         $at, 0x43E3
  003DDF64  mfc1        $v0, $f1                     | mtc1        $at, $f12
  003DDF68  mtc1        $v0, $f13                    | mov.s       $f14, $f22
  003DDF6C  nop                                      | mov.s       $f15, $f23
  003DDF70  cvt.s.w     $f13, $f13                   | jal         func_380530
  003DDF74  jal         func_000000                  | mov.s       $f16, $f21
  003DDF78  ori         $a1, $a1, 0x2D00             | lui         $a0, 0x1B
  003DDF7C  lui         $a0, 0x0                     | lw          $a0, -0x6FB4($a0)
  003DDF80  lw          $a0, 0x0($a0)                | addiu       $a1, $zero, 0xC2
  003DDF84  addiu       $a1, $zero, 0xC2             | jal         func_42C678
  003DDF88  jal         func_000000                  | addu        $a0, $a0, $s1
  003DDF8C  addu        $a0, $a0, $s0                | lui         $at, 0x1B
01_oozla: instruction at +0x0 differs
02_maktar_nebula: instruction at +0x0 differs
03_endako: instruction at +0x0 differs
04_barlow: instruction at +0x0 differs
05_feltzin_system: instruction at +0x0 differs
06_notak: instruction at +0x0 differs
07_siberius: instruction at +0x0 differs
08_tabora: instruction at +0x0 differs
09_dobbo: instruction at +0x0 differs
```
*/

#include "common.h"
extern s32 D_001B043C __attribute__((sda));
extern s32 D_001A904C;
extern f32 D_001B2704;
extern s32 D_001B2B40;
extern char D_001B0450[];

extern void func_00300A00(s32, s32, f32, f32, f32, f32, f32);
extern s32 func_00336D50(s32, s32);
extern int func_002ED578(s32, s32 *, s32 *, s32 *);
extern int func_00115DA8(char *, char *, ...);
extern s32 func_00283CF0(f32);
extern void func_0027F5B8(s32, s32, u64, void *, s32);

/* Draws the two coloured bars of the overlay at the screen scale and, below them, the text block. */
s32 func_L00_003DDEC8(void)
{
    s32 a, b, c;
    char buffer[0x40];

    if (D_001B043C != 0) {
        func_00300A00(func_00336D50(D_001A904C + 0x8710, 0xC1), 0x60442D00, (f32)454, (f32)(s32)(D_001B2704 * 380.0f + 0.5f), -0.5f, 1.0f, 0.0f);
        func_00300A00(func_00336D50(D_001A904C + 0x8710, 0xC2), 0x55F0C070, (f32)454, (f32)(s32)(D_001B2704 * 380.0f + 0.5f), -0.5f, 1.0f, 0.0f);
        func_002ED578(D_001B2B40, &a, &b, &c);
        func_00115DA8(buffer, D_001B0450, a, b, c);
        func_0027F5B8(func_00283CF0(405.0f), (s32)(D_001B2704 * 372.0f + 0.5f), 0x80808080, buffer, 0x80);
    }
    return 1;
}
