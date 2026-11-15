#include "include_asm.h"

#include "common.h"
typedef unsigned int quadword __attribute__((mode(TI)));
extern void moby_set_state(u8 *, int, int);
extern void moby_set_flag_bit(u8 *, int);
extern u8 *D_L03_001B2A20[3] __attribute__((sda));
extern unsigned short D_L03_001B0300 __attribute__((sda));
extern unsigned short D_L03_001B0304 __attribute__((sda));
extern int g_frame_l03_counter[3] __attribute__((sda));
extern int D_L03_001B02F8 __attribute__((sda));
extern int D_L03_001B02FC[3] __attribute__((sda));
extern int D_L03_001B0308;
extern float D_L03_001B030C __attribute__((sda));
extern float D_L03_001B0310 __attribute__((sda));
extern float D_L03_001B0314 __attribute__((sda));
extern float D_L03_001B0318 __attribute__((sda));
extern u8 D_L03_001A8F20[16] __attribute__((sda));
extern void DrawGadgebotSpawnContainer(void);
extern void gfx_add_draw_callback_first(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_L00_00328480(void *, void *, float, float, float, float, int, int, void *, int, int);
extern void func_PAL_002B15D8(void *, int, void *, int, float, float, float, float);
extern int PlayMobySound(int, int, void *);

void func_PAL_L03_003CE358(u8 *m) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    switch (m[0x20]) {
    case 0:
        if ((int)m < (int)D_L03_001B2A20[0]) {
            *(int *)(m+0x9c) = 15;
            moby_set_state(m, 3, -1);
        } else {
            *(unsigned short *)(m+0x7c) = D_L03_001B0300;
            moby_set_state(m, 1, -1);
        }
        break;
    case 1:
        if (m[0x31]) {
            gfx_add_draw_callback_first(DrawGadgebotSpawnContainer, m);
            *(int *)(m+0x78) = FastTweenColor(D_L03_001B02F8, D_L03_001B02FC[0],
                (math_fast_sin_or_cos_b((g_frame_l03_counter[0] % 150) * 0.04188786819577217f - 3.14159f) + 1.0f) * 0.5f);
        }
        if (part_find_owned_effect_slot(m, 0x10000, 0)) {
            *(quadword *)a = 0; *(quadword *)b = 0;
            b[2] = 0.060000002f;
            a[2] = 0.5f;
            FastVecAdd(a, a, m+0x10);
            func_PAL_L00_00328480(m,a,0.333000004f,3.0f,0.5f,1.0f,5,1,b,0x504040c0,0);
            func_PAL_002B15D8(m,D_L03_001B0308,D_L03_001A8F20,255,D_L03_001B030C,D_L03_001B0310,D_L03_001B0314,D_L03_001B0318);
            PlayMobySound(0,0,m);
            *(unsigned short *)(m+0x7c) = D_L03_001B0304;
            moby_set_flag_bit(m,1);
            *(int *)(m+0x9c) = 15;
            *(unsigned short *)(m+0x34) |= 2;
            moby_set_state(m,2,-1);
        }
        break;
    }
}
