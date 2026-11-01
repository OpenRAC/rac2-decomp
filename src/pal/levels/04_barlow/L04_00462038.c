#include "include_asm.h"

#include "common.h"
extern int func_002A9640(unsigned char *obj, int a1, int a2);
extern void func_002E5CF8(int a0, int a1, unsigned char *obj);
extern void func_002A7A00(float *vec, float f12, float f13);
extern float func_00282C48(float value);
extern void func_PAL_L00_00328480(unsigned char *obj, float *pos, int a2, int a3, float *vel, float f12, float f13, float f14, float f15, int color, int t2);
extern void func_0029F338(unsigned char *obj);

/* Throws two puffs of the effect at the object's position, lifted by 0.75, then flags the object and updates it twice. */
void func_PAL_L04_00462038(unsigned char *obj)
{
    float vel[4];
    float pos[4];

    if (func_002A9640(obj, 0x10000, 0) != 0) {
        func_002E5CF8(0, 0, obj);
        qcopy(pos, obj + 0x10);
        pos[2] += 0.75f;
        func_002A7A00(vel, 0.080000006f, 0.120000005f);
        vel[2] = func_00282C48(vel[2]) * 1.5f;
        func_PAL_L00_00328480(obj, pos, 15, 1, vel, 0.5f, 3.0f, 0.75f, 1.25f, 0x50404040, 0);
        func_002A7A00(vel, 0.080000006f, 0.120000005f);
        vel[2] = func_00282C48(vel[2]) * 1.5f;
        func_PAL_L00_00328480(obj, pos, 15, 1, vel, 0.5f, 3.0f, 0.75f, 1.25f, 0x50404040, 0);
        obj[0xA8] = 0xFF;
        func_0029F338(obj);
        func_0029F338(obj);
    }
}

