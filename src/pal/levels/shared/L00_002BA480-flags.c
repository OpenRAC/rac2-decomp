#include "include_asm.h"

typedef unsigned char u8;
typedef float f32;
extern u8 D_00189E20_7[];
extern void func_002AA3A8(f32 *a, f32 *b, f32 c, f32 d, f32 e, f32 f);
extern f32 func_00282C48_1(f32 v);
extern char D_00189E20[];
extern float func_00282DF0(char *arg0);
extern float func_00282E80(char *arg0, char *arg1);
extern float func_00283248(float arg0, float arg1);
extern float func_00283180(float arg0);
extern float func_00283198(float arg0);

/* Walks the resident player block: when the player is moving, has a short range and a
 * small health, the state word selects a new sub-state. The sub-state then drives a turn
 * towards a target point, which writes a velocity and a speed into the block.
 * The base is taken from the symbol again after the nested tests, and the sub-state store
 * goes through a second name for the block: the retail bytes keep the block's address in
 * $s1 and rebuild it (addiu $s0,$s1,-0x61E0) on every path that reaches the merge point,
 * and they build it a second time for the store, so both spellings are kept here. */
void func_PAL_L00_002C39D8(void)
{
    char *p = D_00189E20;
    f32 v;
    f32 dist, range, ang;

    if (*(u8 *)(p + 0x287) != 0) {
        if (0.0f < *(f32 *)(p + 0x31C)) {
            if (*(f32 *)(p + 0x170) < 0.060000002f) {
                dist = func_00282DF0(p + 0xF0);
                if (dist < 0.060000002f) {
                    if (*(f32 *)(p + 0x24B8) < 0.2f) {
                        int state = *(int *)(p + 0x229C);

                        if (state == 0 || state == 2 || state == 4 || state == 10
                            || state == 1) {
                            char *q = D_00189E20;

                            *(short *)(q + 0x20A) = 4;
                        }
                    }
                }
            }
        }
    }
    p = D_00189E20;
    if (*(short *)(p + 0x20A) != 0) {
        dist = func_00282E80(p + 0x80, p + 0x240);
        range = *(f32 *)(p + 0x264) * 0.9f;
        if (dist < range) {
            f32 dx = *(f32 *)(p + 0x80) - *(f32 *)(p + 0x240);
            f32 dy = *(f32 *)(p + 0x84) - *(f32 *)(p + 0x244);

            ang = func_00283248(dx, dy);
            if (dist < *(f32 *)(p + 0x264) * 0.05f)
                ang = *(f32 *)(p + 0x98);
            v = dist - range;
            func_002AA3A8(&v, (f32 *)(p + 0x274), 0.0f, 0.0432f, 0.43200004f, 0.056f);
            *(f32 *)(p + 0x100) = func_00283180(ang) * *(f32 *)(p + 0x274);
            *(f32 *)(p + 0x104) = func_00283198(ang) * *(f32 *)(p + 0x274);
            *(f32 *)(p + 0x108) = 0.0f;
        }
    } else {
        *(int *)(p + 0x274) = 0;
    }
}
