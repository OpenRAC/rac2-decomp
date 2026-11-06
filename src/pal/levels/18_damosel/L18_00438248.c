#include "include_asm.h"

/* func_PAL_L18_00438248, the PAL copy of func_L18_004331D0: the same C, where the two particle
 * arguments 3 become 2, the integer argument 30 becomes 25, 0.0019444445f (both signs) becomes
 * 0.0028000001f (times 36/25) and the two 0.25f become 0.3f. That last edit makes them the same
 * value as the 0.3f before them, so all three share $f20 and z moves to $f21. */

typedef unsigned char u8;
typedef short s16;
typedef int s32;

extern int func_002A77E0(int);
extern u8 *func_002C65A0(void *, void *, int, unsigned, int, int, int,
                          float, float, float, int);
extern u8 D_L18_001A8F20[] __attribute__((sda));
extern u8 *D_L18_001FF414[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_L00_0031CDD0(void *, void *, int, float, float);
extern u8 *func_L18_00437AA0(void *, void *, void *, int, float, float);
extern void func_002E5CF8(s32 arg0, s32 arg1, u8 *arg2);
extern void func_0029FCC0(s32 arg0, s32 arg1, void *arg2);

void func_PAL_L18_00438248(u8 *a)
{
    float pos[4], delta[4], end[4], vel[4];
    u8 *s = *(u8 **)(a + 0x68), *p, *particle;
    int c;
    float z;

    if (*(s16 *)(s + 0x7FC) == 0)
        return;
    *(s16 *)(s + 0x804) = 0;
    func_0029FCC0(*(s32 *)(s + 0x7C8), 0, pos);
    c = func_002A77E0(255);
    particle = func_002C65A0(pos, D_L18_001A8F20, 2, 0x808080, c, 127, 16,
                            840000.0f, 840000.0f, 0.0f, 0);
    if (particle)
        particle[2] = D_L18_001FF414[0][0];
    particle = func_002C65A0(pos, D_L18_001A8F20, 2, 0x608080, (c + 128) % 255,
                            127, 16, 840000.0f, 840000.0f, 0.0f, 0);
    if (particle)
        particle[2] = D_L18_001FF414[0][0];
    func_00282CF0(delta, s + 0x760, pos);
    func_00282F20(delta, delta, 0.3f);
    func_00282CC0(pos, pos, delta);
    func_00282F20(delta, delta, 3.0f);
    func_00282CF0(end, s + 0x760, delta);
    z = func_L00_0031CDD0(pos, end, 0, 0.3f, -0.0028000001f);
    func_00282CF0(vel, end, pos);
    vel[2] = 0.0f;
    func_00282F20(vel, vel, 0.3f);
    vel[2] = z;
    p = func_L18_00437AA0(a, pos, vel, 25, 0.0028000001f,
                         (float)s[0x35]);
    func_002E5CF8(7, 0, a);
    *(float *)(p + 0x2C) = 0.005f;
}
