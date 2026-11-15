#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(void *dst, void *src, void *src2);
extern void moby_set_state();
extern void moby_forward_transform_to_handler();
extern int flag_is_third_pending_set();
extern int flag_set_first_pending();
extern int PlayMobySound();
extern void vec_copy_helper_a();
extern void FastVecAdd(void *dst, void *src, void *src2);
extern void FastVecCross(void *dst, void *src, void *mtx);
extern void vec_scale_to_length(void *dst, void *src, float s);
extern float FastAddRotations(float a, float b);
extern float math_fabs(float a);
extern void moby_mark_spawned();
extern void gfx_add_draw_callback_first();
extern void gfx_draw_flipbook_billboard();
extern float D_L14_001B0388 __attribute__((sda));
extern float D_L14_001B038C __attribute__((sda));
extern float D_L14_001B0390 __attribute__((sda));

void func_PAL_L14_003E3968(char *arg0) {
    char *v = *(char **)(arg0 + 0x68);

    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        moby_set_state(arg0, 1, -1);
        if (*(int *)(v + 0x0) != -1) {
            moby_forward_transform_to_handler(arg0, 0);
        }
        break;
    case 1:
        if (flag_is_third_pending_set(arg0) != 0) {
            if (*(int *)(v + 0x0) != -1) {
                moby_forward_transform_to_handler(arg0, 1);
            }
            moby_set_state(arg0, 2, -1);
            {
                float s = D_L14_001B0388 * 0.020000001f;

                *(float *)(v + 0xC) = s;
                if (*(int *)(v + 0x8) != 0) {
                    *(float *)(v + 0xC) = -s;
                }
            }
            *(int *)(v + 0x10) = 0;
        }
        break;
    case 2:
        {
            float a[4];
            float b[4];

            if (flag_set_first_pending(arg0) != 0) {
                PlayMobySound(0, 0, arg0);
            }
            vec_copy_helper_a(b);
            FastVecCross(a, arg0 + 0xC0, b);
            vec_scale_to_length(a, a, *(float *)(v + 0xC));
            FastVecAdd(arg0 + 0x10, arg0 + 0x10, a);
            {
                float old = *(float *)(v + 0xC);
                float m;

                *(float *)(v + 0x10) = *(float *)(v + 0x10) + old;
                if (*(int *)(v + 0x8) != 0) {
                    m = old - D_L14_001B038C * 0.00040000002f;
                } else {
                    m = old + D_L14_001B038C * 0.00040000002f;
                }
                {
                    float x = m * D_L14_001B0390;

                    *(float *)(v + 0xC) = m;
                    *(float *)(arg0 + 0xF0) = FastAddRotations(*(float *)(arg0 + 0xF0), x);
                }
            }
            if (math_fabs(*(float *)(v + 0x10)) > 4.0f) {
                moby_mark_spawned(arg0);
                return;
            }
        }
        break;
    }
    if (*(unsigned char *)(arg0 + 0x31) != 0 && *(int *)(v + 0x4) != -1) {
        gfx_add_draw_callback_first(gfx_draw_flipbook_billboard, arg0);
    }
}
