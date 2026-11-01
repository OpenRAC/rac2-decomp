#include "include_asm.h"

typedef int s32;
typedef float f32;

extern int func_001157AC(int);
extern int func_L00_002E9100(int, int);
extern void func_L00_002E3A68(f32, f32, f32);
extern void func_002802E0(void *, int, int, int, int, int, int);
extern void func_L00_002D6FD8(void *, int, int, int);
extern void func_0027DE50(void *, int, int, int, int);
extern void func_00282B78(void);
extern int D_001A7340;
extern int D_001A8450;

/* First attempt at func_L00_002E30B8 (level 00, 0x002E30B8, 644 bytes, 27
 * placements).  Current check: 724 bytes, 0 of 27 places match.
 *
 * What retail does (USA v1.01, all 27 placements identical apart from the
 * level's own addresses):
 *
 *  - The caller func_L00_002E2C30 passes (pointer, mode, colour, position,
 *    flags, float) - the float travels in $f12, the fifth integer in $t0.
 *  - It calls func_001157AC(text) and then
 *    func_L00_002E9100(text, that result); the second result is kept as
 *    "handle" ($s1).
 *  - A switch on the mode: 0 and 1 share a block that sets the scale to 1.0
 *    and adds half of a base to the offset (the base is 2 for mode 0 and
 *    D_001A7340 for mode 1, where the offset also starts at (int)amount);
 *    mode 2 and mode 3 call func_L00_002E3A68 with the float at 0x1BC574 and
 *    differ in the third argument (amount, or 1.0 - amount) and in the sign
 *    of the offset; every other mode leaves the scale at 0 and the offset
 *    at 0 and only loads D_001A7340, which is dead.  The base is halved with
 *    a signed division by two ((x + (x >> 31)) >> 1).
 *  - The flags word selects the tail: 0 calls func_002802E0 and
 *    func_L00_002D6FD8, 1 calls func_0027DE50 with (int)(scale * 96.0f)
 *    shifted left by 24, anything else does nothing; all three end in a tail
 *    jump to func_00282B78.
 *
 * The reconstruction keeps that shape, but the remaining difference is large:
 * the frame is 0x70 here and 0x80 in retail (retail saves seven GPRs, this
 * build eight), the switch's branches are laid out differently, the tail
 * call is a plain call here (the compiler is built without sibling calls),
 * the float arguments are scheduled differently, and retail loads
 * D_001A7340 once through $gp (lw $v0, -0x7CB0($gp)), which needs the unit
 * to be built with -G8; this unit is built with -G0, so the load is
 * absolute.
 *
 * Two things are hypotheses rather than measurements: the value 2 that
 * mode 0 uses as its base, and the exact meaning of the scale (1.0,
 * amount, 1.0 - amount) in the three modes.  The level-dependent calls
 * (func_L00_002E9100, func_L00_002E3A68 twice, func_L00_002D6FD8) and the
 * level data at 0x1BC220, 0x1BC574 and 0x1BC588 need ref_L00_002E30B8_kk
 * names before this can be linked.
 */
void func_L00_002E30B8(int text, int mode, int colour, int position, int flags, float amount)
{
    struct { int w[4]; } work;
    float scale = 0.0f;
    int handle;
    int offset = 0;
    int base;

    handle = func_L00_002E9100(text, func_001157AC(text));
    switch (mode) {
    case 0:
        base = 2;
        scale = 1.0f;
        offset += base / 2;
        break;
    case 1:
        offset = (int)amount;
        base = D_001A7340;
        scale = 1.0f;
        offset += base / 2;
        break;
    case 2:
        base = D_001A7340 / 2;
        func_L00_002E3A68(*(float *)0x001BC574, (float)base + (float)handle, amount);
        offset = base - handle;
        break;
    case 3:
        base = D_001A7340 / 2;
        func_L00_002E3A68(*(float *)0x001BC574, (float)base + (float)handle,
                          1.0f - amount);
        scale = 1.0f - amount;
        offset = handle + D_001A7340 - base;
        break;
    default:
        base = D_001A7340;
        break;
    }
    if (flags == 0) {
        int tag = 3;
        int field = *(short *)0x001BC220;
        int *entry = (int *)(0x001BC588 + field * 40);
        int value = entry[8];

        func_002802E0(&work, position, field * 40, -D_001A7340,
                      D_001A7340 * 2, offset, position + value / 2);
        func_L00_002D6FD8(&work, colour, text, -1);
    } else if (flags == 1) {
        int field = *(short *)0x001BC220;
        int *entry = (int *)(0x001BC588 + field * 40);
        int value = entry[8];

        func_0027DE50(&work, position + value - 2, -D_001A7340,
                      D_001A7340 * 2, (int)(scale * 96.0f) << 24);
    }
    func_00282B78();
}
