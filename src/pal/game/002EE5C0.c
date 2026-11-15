#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned char u8;
extern char *moby_get_motion_data(unsigned char *);
typedef struct { float lim; char pad[0x2c]; float v[4]; char pad2[0x40]; } Rec128;
extern Rec128 *D_001B1C54[] __attribute__((sda));
extern int D_00214F90[];
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecLength(void *);
extern void vec_fast_normalize(void *, void *, void *);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void *part_spawn_ground_effect(void *, unsigned int, unsigned int, unsigned int, s32, float *, float, float, float, s32);
extern unsigned int scene_get_state_word(void);
extern int follower_get_state();

void func_PAL_002EE5C0(u8 *a0)
{
    u8 *s2;
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float r;
    float f;
    float lim;
    int i;
    Rec128 *s0;
    float *s3;

    s2 = (u8 *)moby_get_motion_data(a0);
    if (s2 != 0 && !scene_get_state_word() && follower_get_state(a0) != 2) {
        s0 = &D_001B1C54[0][D_00214F90[0]];
        s3 = s0->v;
        FastVecSub(v, a0 + 0x10, s3);
        f = FastVecLength(v);
        r = *(float *)(a0 + 0xC) * 0.00097656f;
        f = f + r;
        lim = s0->lim;
        if (lim < f) {
            vec_scale_to_length(v, v, lim - r);
            FastVecAdd(a0 + 0x10, v, s3);
        }
        if (*(int *)(s2 + 0x15C) >= 7) {
            vec_fast_normalize(s2 + 0x90, s2 + 0x90, s2 + 0xD0);
            *(int *)(s2 + 0x15C) = 0;
            for (i = 0x13; i >= 0; i--) {
                float a = math_random_angle();
                float b = math_random_angle();
                vec_build_spherical_offset(w, 0.20000002f, a, b);
                part_spawn_ground_effect(a0 + 0x10, 0x32, 0x4000FF7F, 0, 2, w, 0.2f, 1.25f, 0.0f, 0);
            }
        }
    }
}

