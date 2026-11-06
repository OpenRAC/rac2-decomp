/* func_PAL_L11_0044C6C0, the PAL copy of func_L11_00446C78: the same C, where expr 0.016666668f becomes 0.020000001f; wrap func_002A7820(D_L11_001B1918[0], D_L11_001B1918[1]) (((. */
#include "common.h"
extern u8 *D_L11_001B359C[] __attribute__((sda));
extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern float D_L11_001B1590[] __attribute__((sda));
extern float D_L11_001B1598[] __attribute__((sda));
extern s32 D_L11_001B1928 __attribute__((sda));
extern float D_L11_001B1900[] __attribute__((sda));
extern float D_L11_001B1908 __attribute__((sda));
extern s32 D_L11_001B1910 __attribute__((sda));
extern s32 D_L11_001B1914[] __attribute__((sda));
extern s32 D_L11_001B1918[] __attribute__((sda));
extern float D_L11_001B1920 __attribute__((sda));
extern float D_L11_001B1924[] __attribute__((sda));
extern float D_L11_001B1930[4] __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern float func_002A7940(void);
extern s32 func_002A7820(s32, s32);
extern void *func_002C3150(void *, void *, s32, float, s32, s32, s32);

/* Advances four animation phases and emits particles around the referenced object.
   The bounds share their measured parameter block; offset reads retain the
   absolute form while the separate scalar scale bound uses small data.
   func_002C3150 keeps the EE integer and FP argument banks in order. */
void func_PAL_L11_0044C6C0(char *object)
{
    float position[4], velocity[4];
    char *state = *(char **)(object + 0x68);
    float *p = (float *)(state + 0xB0);
    int i, j;
    float angle, radius, scale;
    int color, kind;
    u8 life;
    u8 shade;

    for (j = 3; j >= 0; j--, p++) {
        p[-4] += p[0];
        if (p[-4] >= 1.0f) {
            p[-4] = 0;
            p[0] = func_002A7878(D_L11_001B1590[0], D_L11_001B1590[1]) * (0.020000001f);
            p[-8] = func_002A7878(D_L11_001B1598[0], D_L11_001B1598[1]);
        }
    }
    for (i = 0; i < D_L11_001B1928; i++) {
        qzero_nc(velocity);
        velocity[2] = func_002A7878(D_L11_001B1900[0], D_L11_001B1900[1]) * (0.020000001f);
        func_00283098(velocity, velocity, D_L11_001B359C[0] + (*(int *)(state + 0x1D0) << 8) + 0xC0);
        angle = func_002A7940();
        radius = func_002A7878(D_L11_001B1920, D_L11_001B1924[0]);
        position[0] = func_00283180(angle) * radius;
        position[1] = func_00283198(angle) * radius;
        position[2] = 0;
        func_00283098(position, position, D_L11_001B359C[0] + (*(int *)(state + 0x1D0) << 8) + 0xC0);
        func_00282CC0(position, position, D_L11_001B359C[0] + (*(int *)(state + 0x1D0) << 8) + 0x10);
        func_00282CC0(position, position, D_L11_001B1930);
        color = (((int)(func_002A7820(D_L11_001B1918[0], D_L11_001B1918[1])) * 5 + 2) / 6);
        scale = func_002A7878(D_L11_001B1908, D_L11_001B1900[3]);
        kind = func_002A77E0(2) ? D_L11_001B1910 : D_L11_001B1914[0];

        life = color;
        shade = func_002A77E0(255);
        func_002C3150(position, velocity, kind, scale, life, shade, 0);
    }
}
