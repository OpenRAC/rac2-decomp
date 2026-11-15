#include "common.h"

typedef struct {
    u8 pad00[0x268];
    f32 phase;
} Vars_L10_0041EE00;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x68 - 0x20];
    Vars_L10_0041EE00 *vars;
    u8 pad6C[0xC0 - 0x6C];
    f32 axis[4];
} Moby_L10_0041EE00;

extern u16 *D_L10_001FB1E0[];
extern char *D_L10_001B251C[] __attribute__((sda));
extern void func_00281EB8(void *, s32, u32, s32, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00283180(float);
extern int func_00283CF0(float);
extern float func_002A7940(void);
extern char *func_002ED688(void *);

/* Draw a pulsing glow at every live moby of this moby's group. */
void func_L10_0041EE00(u8 *moby)
{
    f32 glowPos[4] __attribute__((aligned(16)));
    u16 *first = D_L10_001FB1E0[moby[0x21]];
    u16 *list;
    Moby_L10_0041EE00 *target;
    Vars_L10_0041EE00 *vars;
    u32 color;

    if (first != 0) {
        list = first;
        do {
            target = (Moby_L10_0041EE00 *)(D_L10_001B251C[0] + ((*list & 0x7FFF) << 8));
            if (*(s32 *)(GetMobyMotionData(target) + 0x110) != 0) {
                vars = target->vars;
                FastVecScale(glowPos, target->axis, 0.25f);
                FastVecAdd(glowPos, target->pos, glowPos);
                color = (FloatToInt((FastSinOrCosA(vars->phase) + 1.0f) * 0.5f * 64.0f) << 24) | 0x63B4FF;
                DrawBillboardQuad_00281EB8(glowPos, 0x31, color, 1, 7.5f, 2.0f, RandomAngle());
            }
        } while ((s16)*list++ >= 0);
    }
}
