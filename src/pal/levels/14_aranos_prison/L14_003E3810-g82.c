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
extern float g_flying_away_speed __attribute__((sda));
extern float g_flying_away_rate __attribute__((sda));
extern float g_flying_away_scale __attribute__((sda));

/* Moves and spins an object that flies off and is removed once it has gone far enough. (PAL) */
void flying_away_update_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_set_state(moby, 1, -1);
        if (*(int *)(vars + 0x0) != -1) {
            moby_forward_transform_to_handler(moby, 0);
        }
        break;
    case 1:
        if (flag_is_third_pending_set(moby) != 0) {
            if (*(int *)(vars + 0x0) != -1) {
                moby_forward_transform_to_handler(moby, 1);
            }
            moby_set_state(moby, 2, -1);
            {
                float s = g_flying_away_speed * 0.020000001f;

                *(float *)(vars + 0xC) = s;
                if (*(int *)(vars + 0x8) != 0) {
                    *(float *)(vars + 0xC) = -s;
                }
            }
            *(int *)(vars + 0x10) = 0;
        }
        break;
    case 2:
        {
            float a[4];
            float b[4];

            if (flag_set_first_pending(moby) != 0) {
                PlayMobySound(0, 0, moby);
            }
            vec_copy_helper_a(b);
            FastVecCross(a, moby + 0xC0, b);
            vec_scale_to_length(a, a, *(float *)(vars + 0xC));
            FastVecAdd(moby + 0x10, moby + 0x10, a);
            {
                float old = *(float *)(vars + 0xC);
                float m;

                *(float *)(vars + 0x10) = *(float *)(vars + 0x10) + old;
                if (*(int *)(vars + 0x8) != 0) {
                    m = old - g_flying_away_rate * 0.00040000002f;
                } else {
                    m = old + g_flying_away_rate * 0.00040000002f;
                }
                {
                    float x = m * g_flying_away_scale;

                    *(float *)(vars + 0xC) = m;
                    *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), x);
                }
            }
            if (math_fabs(*(float *)(vars + 0x10)) > 4.0f) {
                moby_mark_spawned(moby);
                return;
            }
        }
        break;
    }
    if (*(unsigned char *)(moby + 0x31) != 0 && *(int *)(vars + 0x4) != -1) {
        gfx_add_draw_callback_first(gfx_draw_flipbook_billboard, moby);
    }
}
