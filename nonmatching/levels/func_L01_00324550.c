/* 5 November 2026: rechecked with the unit's real func_L01_00324410(char *, char *, int *) prototype: 132/132, 0/11, only the frame differs (retail 0x2A0, sd ra 0x200 below sq s0 0x210). No existing flag gives ra below s0; needs a compiler change, so not retried. */
/* opus-1 (v2139, 2026-11-03): FAILED, 132/132 bytes, 0/11 places with -mastra-quad-saves (frame 0x2A0 and the
 * varargs spill area exact; 5 save/restore instructions differ), default profile 0x290 frame with sd/ld s0.
 * Why s0 is `sq` but ra `sd`: the EE cc1 (stock 2.9-ee mips.c) keeps a per-register save mode, mips_reg_mode[],
 * set once in override_options and only widened by mips_check_reg_mode() when an insn sets that GPR in a wider
 * mode; it is never reset between functions. So a function compiled EARLIER in the same original unit that set
 * $s0 in TImode makes every later function in that unit save $s0 with sq, while $ra stays DImode (sd).
 * Measured on this checkout's cc1 with a scratch unit (a TImode value held in $s0 across a call, then this body):
 * the default profile then emits `sq $16,512($sp)` / `sd $31,520($sp)` on a 0x290 frame, i.e. the mixed widths
 * but 8-byte slot spacing (the sq overlaps ra's slot). Retail uses 16-byte slots with $ra at 0x200 below $s0 at
 * 0x210 (0x2A0 frame); -mastra-quad-saves gives the 0x2A0 frame but $s0 at 0x200 and $ra as sq at 0x210.
 * Needed: compiler support for 16-byte slots with per-register widths in retail's order (tools change), plus
 * the earlier TImode $s0 user of the same unit. Not handwritten: the shape is the compiler's own.
 */

/* Current retained result, 28 October 2026: 132/132 bytes with game -mastra-quad-saves, but
 * mixed s0/ra save widths and order differ. The SDK profile emits 116/132 and lacks FP spills.
 * The real variadic forwarding body is retained without fabricated frame padding. No strict
 * match. Older diagnostic notes below are historical and do not rule out C. */

/* Retained readable C; not matching and no exact-C credit.
 * 2026-10-28 bounded retry: Game profile -O2 -G0 -ffunction-sections -mastra-quad-saves: 132/132 bytes, exact varargs forwarding/body but both s0 and ra save width/order differ from retail mixed saves. SDK profile: 116/132 and missing FP argument spills. The register-save area is reached with the existing builtin-next-arg convention; no fabricated frame padding was used.
 * Reopen with an independently measured save-profile or allocation witness.
 * No strict linked-build claim. Historical screen-only notes follow the source.
 */
#include "common.h"
extern int func_00288FB8(int);
extern void func_L01_00324410(char *, int, void *);
extern void func_0028BCA0(int);
extern void func_0026FEB8(const char *, ...);
extern const char D_001AA590[];
void func_L01_00324550(int id, ...)
{
    char text[0x200];
    int format = func_00288FB8(id);
    if (format) {
        /* Retail forwards the seven saved integer argument slots. */
        func_L01_00324410(text, format, (char *)__builtin_next_arg(id) - 0x38);
        func_0028BCA0((int)text);
    } else func_0026FEB8(D_001AA590, id);
}

/* func_L01_00324550 (132 bytes, 11 places) - diagnosis only, no C measured this wave.
 *
 * The body is ordinary: v0 = func_2E99D0(a0); when v0 is nonzero it runs
 * func_324410(sp, v0, sp+0x268) then func_2ECB20(sp), otherwise func_2A6CF0(0x001AA590, a0).
 * What blocks it is the prologue.  Before that first call retail has already stored
 * $a1-$a3 and $t0-$t3 to 0x268..0x298($sp) and $f12/$f14/$f16/$f18 to 0x258..0x264($sp)
 * on a 0x2A0 frame - the variadic register-save area - and it holds $s0 in a 128-bit slot
 * at 0x210($sp) with `sq $s0,0x210($sp)` (0x7FB00210), reading it back with
 * `lq $s0,0x210($sp)` (0x7BB00210) in the delay slot of the branch at 0x003245AC and
 * storing it again at 0x003245C4.  $s0 is an ordinary 64-bit value (`daddu $s0,$a0,$zero`
 * in the first delay slot), so the quad slot is the prologue's own register-save shape and
 * not a 128-bit object.
 * Missing: a C spelling for that variadic prologue (the natural `...` + va_start route was
 * not measured here, and the saved-integer area is passed on to func_324410, so the two
 * are the same mechanism).  ASM_FUNC candidate until a lever appears.
 */
