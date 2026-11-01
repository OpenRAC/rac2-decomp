#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad000[0x264];
    float f264;
    u8 pad268[0x334 - 0x268];
    float f334;
} ResidentState_A220;
extern void func_002AF000(char *, float, float, float);
extern char D_00189EA0[];
extern int D_001A79F0 __attribute__((sda));
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_00283CF0(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_002BAE50(void *, void *, unsigned, int, int, int, int, int);

/* Emit ten particles radially around the hero, using the saved height outside level 6. */
void func_PAL_L00_002BA198(void)
{
    float pos[4], vec[4];
    char *origin = D_00189EA0;
    ResidentState_A220 *state = (ResidentState_A220 *)(origin - 0x80);
    int i;
    int life, fade;
    float speed, angle, elevation, radius;

    i = 9;
    do {
        life = func_00283CF0(func_002A7878(4200.0f, 7350.0f) * 0.001f);
        fade = func_00283CF0(func_002A7878(21000.0f, 31500.001953125f) * 0.001f);
        speed = func_002A7878(0.0030000003f, 0.014f);
        qcopy(pos, origin);
        if (D_001A79F0 != 6)
            pos[2] = state->f334;
        i--;
        angle = func_002A7940();
        elevation = func_002A7878(0.349065899848938f, 1.396263599395752f);
        radius = func_002A7878(0.05f, state->f264 + 0.2f);
        func_002AF000((char *)vec, speed, angle, elevation);
        pos[0] += func_00283180(angle) * radius;
        pos[1] += func_00283198(angle) * radius;
        func_002BAE50(pos, vec, 0x7000c0f0, 0x70f0, 33, life, fade, 1);
    } while (i >= 0);
}
