/* 6 November 2026, round 3: best body below (752/752, 0/8 USA, about 21 words).
 * Profile: own unit L02_003C43F0-menu-g8.c, -O2 -G8 -fno-expensive-optimizations
 * -ffunction-sections -fno-builtin -fno-gcse. The func_00326A10 idiom (inline rounding
 * helper with the dead `result != 0 && D_L02_001B3E00 == active` test) gives the ghost
 * $s1, s0 = 0x8710, retail's FP roles and post-rounding constant order. Measured levers:
 * the helper for all seven coordinates (the 23.0f ones add `half`, the 373.0f one a
 * literal 0.5f), `on` only in the four draws (literal 1 in the text calls swaps s0/s1
 * into retail order), the u64 colour argument of func_002FC560 (its a0 then goes in the
 * jal slot). Left: the fourth draw's f14/f15 moves (retail `mov.s f15, f14`) and
 * local-alloc FP choices in the 23.0f/373.0f roundings (f0/f1/f2 rotated).
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
extern void func_002FC560(int, unsigned long);
extern char *func_00288FB8(int);
extern void func_0027FBD8(int, int, u64, char *, int);
extern char *D_L02_001A904C;
extern float D_L02_001B3E04;

extern int D_L02_001B3E00;

static __inline__ int menu_coord(float value, float half, int active)
{
    float scaled = D_L02_001B3E04 * value + half;
    int result = (int)scaled;

    if (result != 0 && D_L02_001B3E00 == active)
        scaled = 1.0f;
    return result;
}

void func_L02_003C43F0(char *obj) {
    char *text;
    int state;
    char *id;
    int y, on, entry;
    float one, zero, half, k;

    entry = 0x8710;
    k = 203.0f;
    half = 0.5f;
    on = 1;
    id = func_00336D50(D_L02_001A904C + entry, 0x70);
    y = menu_coord(k, half, on);
    one = 1.0f;
    zero = 0.0f;
    func_00300A00(id, 0x60442D00, 258.0f, (float)y, one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x6F), 0x60442D00, 258.0f,
                  (float)menu_coord(k, half, on), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x71), 0x55F0C070, 258.0f,
                  (float)menu_coord(k, half, on), one, one, zero);
    func_00300A00(func_00336D50(D_L02_001A904C + entry, 0x72), 0x55F0C070, 258.0f,
                  (float)menu_coord(k, half, on), one, one, zero);
    func_002FC560(0x47, 0x5360BUL);
    state = *(unsigned char *)(obj + 0x20);
    if (state == 7) {
        text = func_00288FB8(0x2F5C);
        func_0027FBD8(254, menu_coord(23.0f, half, 1), 0x88FFFFFF, text, -1);
    } else if (state != 8 && state != 5) {
        text = func_00288FB8(0x2F5B);
        func_0027FBD8(262, menu_coord(23.0f, half, 1), 0x88FFFFFF, text, -1);
    }
    text = func_00288FB8(0x2F5A);
    func_0027FBD8(254, menu_coord(373.0f, 0.5f, 1), 0x88FFFFFF, text, -1);
}
