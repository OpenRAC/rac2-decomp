/* 5 November 2026 (w-c4): no new C lever; the body already matches and only the save layout differs (retail sd ra 0x0, sq s0 0x10, 0xA0 frame). Same compiler gap as func_L01_00324550/func_L02_00411D18: per-register save width (mips_reg_mode) with 16-byte slots for sq-saved GPRs. Not retried. */
/* 5 November 2026 (w-c2): same frame as func_L01_00324550: register_precision is stock but only sets widths; mips.c 6497-6611 always puts $ra in the top GP slot, retail has s0 above ra. Not retried. */
/* Opus-1 v0735, 29 October 2026: recompiled with this cc1 (scratch, both
 * profiles): unchanged, 264 bytes; with -mastra-quad-saves only the four
 * save/restore words differ (last check.py record: 264/264, 0/4 places).
 * New evidence: a scan of every catalogue function's prologue in the boot
 * and all 27 levels finds only three frames that mix `sq` and `sd` GPR saves:
 * this one, func_L01_00324550 (also a stdarg function; `sq $s0,0x210`,
 * `sd $ra,0x200`) and func_L02_00411D18 (`sq $s2` in its own 16-byte slot
 * below the 8-byte ones). The two stdarg frames share the shape seen here:
 * 16-byte slots, `ra` with `sd` at the lower slot, `s0` (the copy of the
 * named count) with `sq` above it. This cc1 has no profile for it: the default
 * keeps 8-byte slots (and saves a TImode-holding callee register with `sq`
 * into an 8-byte slot, overlapping its neighbour), and -mastra-quad-saves
 * widens `ra` too and puts it in the upper slot. The SDK compiler gives a
 * different body. <stdarg.h> va_start yields sp+160 under this cc1, not
 * retail's sp+0x68, so the explicit __builtin_next_arg - 0x38 stays.
 * Needs a measured compiler model of the stdarg save layout.
 */
/* Sol high v0505, 28 October 2026: rechecked both profiles. Default gives
 * 264/264 bytes but a 0x90 frame instead of 0xA0, 0/4 places. Dedicated
 * -O2 -G0 -ffunction-sections -mastra-quad-saves reproduces the body and frame,
 * leaving the same four save/restore instructions described below. No C
 * body operations require the observed mixed-width GPR save convention;
 * neither available profile supplies it. Compiler/tool changes are out of scope.
 */
/* Sol low, v0290, 2026-10-28: 264/264 bytes, 0/4 places.
 * Profile: -O2 -G0 -ffunction-sections -mastra-quad-saves.
 * Body matches apart from relocation values; four save/restore instructions
 * differ. Retail sq/lq s0 at sp+0x10, sd/ld ra at sp+0; this profile sq/lq
 * s0 at sp+0 and sq/lq ra at sp+0x10. Default uses doubleword saves for both.
 * The builtin_next_arg -0x38 accesses the seven saved integer argument words.
 * Volatile packet pointer/data are supported by retail's repeated pointer
 * loads and ordered packet writes. sda metadata reproduces the macro loads.
 * Need a measured mixed-width save remedy; lq/sq alone is not handwritten.
 */
#include "common.h"
extern volatile u32 * volatile ref_L08_00389B68_00 __attribute__((sda));
extern u32 *ref_L08_00389B68_01 MACRO_ADDR;
extern void func_00282AB0(void *, void *, int);
void func_L08_00389B68(int count, ...) {
    if (count) {
        ref_L08_00389B68_00[0] = (count + 1) | 0x10000000;
        ref_L08_00389B68_00[1] = 0;
        ref_L08_00389B68_00[2] = 0;
        ref_L08_00389B68_00[3] = (count + 1) | 0x50000000;
        ref_L08_00389B68_00[4] = count + 0x8000;
        ref_L08_00389B68_00[5] = 0x10000000;
        ref_L08_00389B68_00[6] = 14;
        ref_L08_00389B68_00[7] = 0;
        ref_L08_00389B68_01 = (u32 *)(ref_L08_00389B68_00 + 8);
        func_00282AB0(ref_L08_00389B68_01, (char *)__builtin_next_arg(count) - 0x38, count * 16);
        ref_L08_00389B68_00 = (u32 *)((char *)ref_L08_00389B68_00 + count * 16);
    }
}
