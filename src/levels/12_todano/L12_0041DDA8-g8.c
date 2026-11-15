#include "common.h"

typedef union {
    f32 f[4];
    u32 q __attribute__((mode(TI)));
} VecDDA8;

extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
typedef struct {
    u8 pad[0x38];
    f32 z;
    u8 pad3C[0x44];
} NodeDDA8;
extern NodeDDA8 *D_L12_001B2F8C;
extern NodeDDA8 *D_L12_001B2F8C_gp SDATA(D_L12_001B2F8C);
typedef struct {
    u8 pad[0x110];
    f32 direction[4];
    u8 pad120[0x21C];
    u8 *attached;
} HeroDDA8;
extern HeroDDA8 g_hero_state;
extern u8 g_hero_position[];
extern s32 D_L12_001B29C8;
extern s32 D_L12_001B29C8_gp SDATA(D_L12_001B29C8);
extern f32 D_L12_001B1DE8 SDATA(D_L12_001B1DE8);
extern f32 D_L12_001B1DF8 SDATA(D_L12_001B1DF8);
extern f32 D_L12_001B1DE0 SDATA(D_L12_001B1DE0);
extern s32 D_L12_001B1DE4 SDATA(D_L12_001B1DE4);
extern s32 D_L12_001B1DF0 SDATA(D_L12_001B1DF0);
extern s32 D_L12_001B1DF4;
/* Integer and FP argument order is preserved independently by the EE ABI. */
extern void pushable_moby_update(void *, void *, f32, f32, f32, s32);
extern void moby_update_empty_alt(void *);
extern s32 IsPointInCuboid(void *, s32);
extern void moby_set_state(void *, s32, s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern f32 vec_distance_xy(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern f32 FastVecDot(void *, void *);
extern f32 math_fabs(f32);
extern void math_approach_target_with_braking(void *, f32, f32, f32, f32);
extern void vec_scale_to_length(void *, void *, f32);
extern f32 fast_vec_dist(void *, void *);
extern s32 math_fast_float_d(void *);
extern f32 IntToFloat(s32);
extern s32 PulseColor(s32, s32, f32);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Moves between the two node-relative endpoints and pauses before reversing. */
void UpdateTodanoShuttlePlatform(u8 *self)
{
    u8 *vars = *(u8 **)(self + 0x68);
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 oldRot[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    VecDDA8 motion;
    VecDDA8 temp;
    f32 work[4] __attribute__((aligned(16)));
    f32 speed, oldSpeed, angle;
    s32 *node_ids, i;

    *(u32 *)(vars + 0x70)|=2;
    qcopy(oldPos, self + 0x10);
    qcopy(oldRot, self + 0xF0);
    switch (self[0x20]) {
    case 0:
        *(u16 *)(self + 0x34)|=0x1000;
        *(u32 *)(vars + 0xDC)|=1;
        self[0x20]=1;
        *(f32 *)(vars + 0x140)=*(f32 *)(vars + 0x13C)=D_L12_001B1DF8;
        break;
    case 1:
        {
            s32 delay;

            /* The compiler retains this short delay and pads its loop. */
            for (delay = 0; delay < 2; delay++) {}
        }
        pushable_moby_update(self, vars + 0x50, 1.5f, 1.5f, 0.1f, *(s32 *)(vars + 0xEC));
        node_ids=(s32 *)(vars + 0xE0);
        for (i = 0; i < 2; i++, node_ids++) {
            if (*node_ids != -1)
                moby_update_empty_alt(D_L12_001B2E9C_gp + (*node_ids << 8));
        }
        if (*(s32 *)(vars + 0xE8)!=-1 && IsPointInCuboid(self + 0x10, *(s32 *)(vars + 0xE8))) {
            *(s32 *)(vars + 0x138)=60;
            moby_set_state(self, 3,-1);
            *(u16 *)(self + 0x34)&=0xEFFF;
            *(f32 *)(vars + 0x130)=1.0f;
        }
        break;
    case 2:
        temp.q = 0;
        temp.f[0]=*(f32 *)(vars + 0x130);
        motion.q=temp.q;
        matrix_mul_vec3(&motion, &motion, &D_L12_001B2F8C[*(s32 *)(vars + 0xE8)]);
        FastVecAdd(&motion, &motion,(u8 *)&D_L12_001B2F8C[*(s32 *)(vars + 0xE8)]+0x30);
        speed=vec_distance_xy(self + 0x10, &motion);
        if (g_hero_state.attached!=self && D_L12_001B29C8%30==0) {
            FastVecSub(&temp, self + 0x10, &motion);
            angle=FastVecDot(&temp, g_hero_state.direction);
            if (math_fabs(angle)<*(f32 *)(vars + 0x134)*0.9f) {
                if (*(f32 *)(vars + 0x13C)>3.0f) *(f32 *)(vars + 0x13C)-=0.5f;
                if (*(f32 *)(vars + 0x140)<9.0f) *(f32 *)(vars + 0x140)+=0.5f;
            } else {
                if (*(f32 *)(vars + 0x13C)<9.0f) *(f32 *)(vars + 0x13C)+=0.5f;
                if (*(f32 *)(vars + 0x140)>3.0f) *(f32 *)(vars + 0x140)-=0.5f;
            }
        }
        oldSpeed=*(f32 *)(vars + 0x134);
        math_approach_target_with_braking(vars + 0x134, speed, *(f32 *)(vars + 0x13C)*0.00027777778f, *(f32 *)(vars + 0x140)*0.00027777778f, D_L12_001B1DE8*0.016666668f);
        FastVecSub(delta, &motion, self + 0x10);
        delta[2]=0;
        vec_scale_to_length(delta, delta, *(f32 *)(vars + 0x134));
        qcopy(&temp, g_hero_position);
        if (math_fabs(temp.f[2]-D_L12_001B2F8C[*(s32 *)(vars + 0xE8)].z)<2.5f)
            temp.f[2]=D_L12_001B2F8C_gp[*(s32 *)(vars + 0xE8)].z;
        if (IsPointInCuboid(&temp, *(s32 *)(vars + 0xE8))) {
            FastVecSub(work, &temp, self + 0x10);
            {
                s32 positive;

                if (FastVecDot(work, delta) >= 0.0f)
                    positive = 1;
                else
                    positive = 0;
                if (positive == D_L12_001B1DE4 &&
                    fast_vec_dist(&temp, self + 0x10) < D_L12_001B1DE0) {
                    *(f32 *)(vars + 0x134) = oldSpeed;
                    break;
                }
            }
        }
        FastVecAdd(self + 0x10, self + 0x10, delta);
        if (speed<0.01f) {
            *(s32 *)(vars + 0x138)=60;
            *(f32 *)(vars + 0x130)=-*(f32 *)(vars + 0x130);
            moby_set_state(self, 3,-1);
        }
        break;
    case 3:
        if (math_fast_float_d(vars + 0x138)) moby_set_state(self, 2,-1);
        break;
    }
    if (self[0x31]) {
        angle=IntToFloat(D_L12_001B29C8_gp%60);
        {
            f32 denominator = IntToFloat(60);

            angle *= 6.2831855f;
            {
                s32 first = D_L12_001B1DF0;
                s32 second = D_L12_001B1DF4;

                angle /= denominator;
                *(s32 *)(self + 0x78) = PulseColor(first, second, angle - 3.1415927f);
            }
        }
    }
    FastVecSub(delta, self + 0x10, oldPos);
    mat_combine_and_store(vars + 0xA0, delta, oldRot, self + 0xF0);
}
