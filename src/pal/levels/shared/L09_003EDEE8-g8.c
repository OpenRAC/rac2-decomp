#include "include_asm.h"

#include "common.h"
extern int func_002A7820(int a0, int a1);
extern void func_0029FCC0(char *object, int joint, void *out);
extern float func_00282E80(void *a, void *b);
extern void func_00282F20(void *dst, void *src, float scale);
extern int func_002A8C28(void *owner, void *start, int queryMode, int first, int second, int mode,
                         f32 radius, f32 distance, f32 scale);
extern int func_002A77E0(int a0);
extern float func_002A7878(float lo, float hi);
extern char *func_002BAE50(void *pos, void *vel, unsigned int color, int a3, int size, int life,
                           int fade, int a7);
extern char D_00189EA0[];
extern float D_L09_001B0C40 __attribute__((sda));
extern float D_L09_001B0C44 __attribute__((sda));
extern float D_L09_001B0C48 __attribute__((sda));
extern float D_L09_001B2390 MACRO_ADDR;
extern float D_L09_001B238C MACRO_ADDR;
extern int D_L09_001B2388 MACRO_ADDR;
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad_L09_003E9AA0;

/* For joints 5 to 7: queries near D_00189EA0 when close enough, then spawns falling particles
   (two colours by the toggle word, then a third). While neither level weight is above 0.95
   and +0x31 is set, joints 3 and 4 also spawn particles along the +0xC0 vector. */
void func_PAL_L09_003EDFA8(char *object) {
    char *data = *(char **)(object + 0x68);
    Quad_L09_003E9AA0 pos, vel, zero;
    int i, j, size, life;

    for (i = 5; i < 8; i++) {
        func_0029FCC0(object, i, &pos);
        if (func_00282E80(&pos, D_00189EA0) < D_L09_001B0C40) {
            qcopy(&vel, &pos);
            vel.f[2] -= D_L09_001B0C44;
            func_002A8C28(object, &vel, 0x10001, 0, 1, 0, D_L09_001B0C48,
                          (float)*(unsigned char *)(data + 0x35), 2.0f);
        }
        if ((!(D_L09_001B2390 > 0.95f) && !(D_L09_001B238C > 0.95f) && *(unsigned char *)(object + 0x31))
            || func_002A77E0(2)) {
            zero.q = 0;
            zero.f[2] = -(func_002A7878(4.5f, 5.5f) * (0.020000001f));
            vel.q = zero.q;
            if (D_L09_001B2388 & 1)
                func_002BAE50(&pos, &vel, 0xCF0000FF, 207, ((s32)(func_002A7820(18, 22)) * 5 + 2) / 6, 180, -10, 1);
            else
                func_002BAE50(&pos, &vel, 0x6000FFFF, 128, ((s32)(func_002A7820(20, 24)) * 5 + 2) / 6, 350, -10, 1);
            life = func_002A7820(20, 90);
            size = ((s32)(func_002A7820(10, 15)) * 5 + 2) / 6;
            func_002BAE50(&pos, &vel, 0xEFFF7F4F, 0xFF0000, size, life, -life, 1);
        }
    }
    if (!(D_L09_001B2390 > 0.95f) && !(D_L09_001B238C > 0.95f) && *(unsigned char *)(object + 0x31)) {
        for (j = 3; j < 5; j++) {
            func_00282F20(&vel, object + 0xC0, -(func_002A7878(4.5f, 5.5f) * (0.020000001f)));
            func_0029FCC0(object, j, &pos);
            if (D_L09_001B2388 & 1)
                func_002BAE50(&pos, &vel, 0xCF0000FF, 207, ((s32)(func_002A7820(18, 22)) * 5 + 2) / 6, 50, -10, 1);
            else
                func_002BAE50(&pos, &vel, 0x6000FFFF, 128, ((s32)(func_002A7820(20, 24)) * 5 + 2) / 6, 100, -10, 1);
            life = func_002A7820(10, 25);
            size = ((s32)(func_002A7820(10, 15)) * 5 + 2) / 6;
            func_002BAE50(&pos, &vel, 0xEFFF7F4F, 0xFF0000, size, life, -life, 1);
        }
    }
}
