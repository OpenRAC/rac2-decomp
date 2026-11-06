/* 6 November 2026: the ghost-save idiom that matched func_00326A10 and its three siblings
 * (an inline rounding helper with a dead display-mode test, `if (result != 0 &&
 * D_L02_001B3E00 == active) scaled = 1.0f;`, active an int local = 1; -fno-gcse; the
 * 0x8710 offset and the 203.0f factor as named locals) gives the ghost save and retail's
 * post-rounding constant order here too: 744/752 with the note's profile plus -fno-gcse.
 * Left: the ghost takes $s0 and 0x8710 $s1 (retail the reverse), FP roles f21/f23 swapped,
 * and the `id` copy to $a0 placed late. Next: the 326A10 source shape (early return, one
 * call per statement, ox/sc set after the rounding).
 */
/* Near miss (opus-1, v1659): 744/752 bytes, 0/8 USA v1.01 places.
 * Profile: its own unit (e.g. L02_003C43F0-menu-g8.c) with
 *   -O2 -G8 -fno-expensive-optimizations -ffunction-sections -fno-builtin,
 * the profile of the matched sibling widget draws (src/game/002CDD88-g8.c, 002CFDA8-g8.c).
 * What this recovers: frame 0x40, s0 = 0x8710, the absolute macro loads of the registry
 * pointer and scale, and retail's FP allocation (f22 = 203, f23 = 0.5, f20 = 1.0,
 * f21 = 0.0) with 258.0 reloaded into $f12 before each call: without expensive
 * optimizations cse keeps the literal argument constants, so 1.0 and 0.0 are cached
 * only because they are locals, as in the siblings' `zero`.
 * What still differs:
 *  - retail saves $s1 and never uses it (obj is in $s2); here obj takes $s1 and the
 *    function is two words short (docs/MATCHING-BLOCKERS.md, "A register saved and never
 *    used"; func_00326A10 is the same family).
 *  - retail sets every call's constant arguments after the rounding chain
 *    (lwc1/mul/add/cvt/mfc1 v1/mtc1/cvt), as if a block boundary followed each
 *    (int)(scale * k + 0.5f); here both schedulers move them into the chain's stalls.
 *    A do { y = ...; } while (0) around each rounding, as a diagnostic only, gives that
 *    order and $v1 for the fix result (756 bytes); an inline rounding helper ties this
 *    source. -fno-schedule-insns does not help (sched2 still fills the stalls).
 * Callees and data are named by their catalogue/USA v1.01 level 02 addresses; the
 * registry lookup is the boot's func_00336D50 copy, the draws func_00300A00 and
 * func_0027FBD8.
 */
#include "common.h"

extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_002FC560(int, int);
extern char *func_00288FB8(int);
extern void func_0027FBD8(int, int, u64, char *, int);
extern char *D_L02_001A904C;
extern float D_L02_001B3E04;

void func_L02_003C43F0(char *obj) {
    char *text;
    int state;
    float one = 1.0f, zero = 0.0f;

    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x70), 0x60442D00, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x6F), 0x60442D00, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x71), 0x55F0C070, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + 0x8710, 0x72), 0x55F0C070, 258.0f,
                  (float)(int)(D_L02_001B3E04 * 203.0f + 0.5f), one, one, zero);
    func_002FC560(0x47, 0x5360B);
    state = *(unsigned char *)(obj + 0x20);
    if (state == 7) {
        text = func_00288FB8(0x2F5C);
        func_0027FBD8(254, (int)(D_L02_001B3E04 * 23.0f + 0.5f), 0x88FFFFFF, text, -1);
    } else if (state != 8 && state != 5) {
        text = func_00288FB8(0x2F5B);
        func_0027FBD8(262, (int)(D_L02_001B3E04 * 23.0f + 0.5f), 0x88FFFFFF, text, -1);
    }
    text = func_00288FB8(0x2F5A);
    func_0027FBD8(254, (int)(D_L02_001B3E04 * 373.0f + 0.5f), 0x88FFFFFF, text, -1);
}
