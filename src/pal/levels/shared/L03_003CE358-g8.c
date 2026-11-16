#include "include_asm.h"

#include "common.h"
typedef unsigned int quadword __attribute__((mode(TI)));
extern void moby_set_state(u8 *, int, int);
extern void moby_set_flag_bit(u8 *, int);
extern u8 *g_moby_record_end[3] __attribute__((sda));
extern unsigned short g_breakable_value_a __attribute__((sda));
extern unsigned short g_breakable_value_b __attribute__((sda));
extern int g_frame_l03_counter[3] __attribute__((sda));
extern int g_breakable_tween_color_start __attribute__((sda));
extern int g_breakable_tween_colors[3] __attribute__((sda));
extern int g_breakable_debris_mask;
extern float g_breakable_debris_param_a __attribute__((sda));
extern float g_breakable_debris_param_b __attribute__((sda));
extern float g_breakable_debris_param_c __attribute__((sda));
extern float g_breakable_debris_param_d __attribute__((sda));
extern u8 g_effect_descriptor_default[16] __attribute__((sda));
extern void DrawGadgebotSpawnContainer(void);
extern void gfx_add_draw_callback_first(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_L00_00328480(void *, void *, float, float, float, float, int, int, void *, int, int);
extern void func_PAL_002B15D8(void *, int, void *, int, float, float, float, float);
extern int PlayMobySound(int, int, void *);

void breakable_moby_update_pal(u8 *m) {
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    switch (m[0x20]) {
    case 0:
        if ((int)m < (int)g_moby_record_end[0]) {
            *(int *)(m+0x9c) = 15;
            moby_set_state(m, 3, -1);
        } else {
            *(unsigned short *)(m+0x7c) = g_breakable_value_a;
            moby_set_state(m, 1, -1);
        }
        break;
    case 1:
        if (m[0x31]) {
            gfx_add_draw_callback_first(DrawGadgebotSpawnContainer, m);
            *(int *)(m+0x78) = FastTweenColor(g_breakable_tween_color_start, g_breakable_tween_colors[0],
                (math_fast_sin_or_cos_b((g_frame_l03_counter[0] % 150) * 0.04188786819577217f - 3.14159f) + 1.0f) * 0.5f);
        }
        if (part_find_owned_effect_slot(m, 0x10000, 0)) {
            *(quadword *)a = 0; *(quadword *)b = 0;
            b[2] = 0.060000002f;
            a[2] = 0.5f;
            FastVecAdd(a, a, m+0x10);
            func_PAL_L00_00328480(m,a,0.333000004f,3.0f,0.5f,1.0f,5,1,b,0x504040c0,0);
            func_PAL_002B15D8(m,g_breakable_debris_mask,g_effect_descriptor_default,255,g_breakable_debris_param_a,g_breakable_debris_param_b,g_breakable_debris_param_c,g_breakable_debris_param_d);
            PlayMobySound(0,0,m);
            *(unsigned short *)(m+0x7c) = g_breakable_value_b;
            moby_set_flag_bit(m,1);
            *(int *)(m+0x9c) = 15;
            *(unsigned short *)(m+0x34) |= 2;
            moby_set_state(m,2,-1);
        }
        break;
    }
}
