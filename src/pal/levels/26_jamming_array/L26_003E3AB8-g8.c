#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern void moby_set_state(unsigned char *, int, int);
extern float math_random_float_range(float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void DrawDoubleLayerQuadMesh(void);
extern int g_hero_tether_enabled;
extern float g_flicker_rate __attribute__((sda));
typedef struct { float f[2]; float g[2]; } Counters;

/* Flickers a pair of quads: in state 1 it advances two counters at the flicker rate and draws the double layer quad mesh (PAL: 50 Hz timing). */
void quad_flicker_update_pal(char *moby_arg) {
    char *moby = moby_arg;
    char *vars = *(char **)(moby + 0x68);
    int i;
    int j;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u8 *)(moby + 0x30) = 0xFF;
        moby_set_state((unsigned char *)moby, 1, -1);
        *(int *)vars = 0;
        *(float *)(vars + 4) = 0.5f;
        break;
    case 1:
        if (g_hero_tether_enabled != 0) {
            for (i = 0; i < 2; i = j) {
                float phase;

                j = i + 1;
                phase = ((Counters *)vars)->f[i] + g_flicker_rate * 0.020000001f;
                ((Counters *)vars)->f[i] = phase;
                if (1.0f < phase) {
                    phase = phase - 1.0f;
                    ((Counters *)vars)->f[i] = phase;
                    phase = ((Counters *)vars)->g[j & 1] + math_random_float_range(0.333f, 0.666f);
                    ((Counters *)vars)->g[i] = phase;
                    if (1.0f < phase) {
                        phase = phase - 1.0f;
                        ((Counters *)vars)->g[i] = phase;
                    }
                }
            }
            gfx_add_draw_callback_first((void *)DrawDoubleLayerQuadMesh, moby);
        }
        break;
    }
}
