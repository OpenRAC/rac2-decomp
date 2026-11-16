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

void quad_flicker_update_pal(char *a0) {
    char *s3 = a0;
    char *s4 = *(char **)(s3 + 0x68);
    int i;
    int j;

    switch (*(u8 *)(s3 + 0x20)) {
    case 0:
        *(u8 *)(s3 + 0x30) = 0xFF;
        moby_set_state((unsigned char *)s3, 1, -1);
        *(int *)s4 = 0;
        *(float *)(s4 + 4) = 0.5f;
        break;
    case 1:
        if (g_hero_tether_enabled != 0) {
            for (i = 0; i < 2; i = j) {
                float v;

                j = i + 1;
                v = ((Counters *)s4)->f[i] + g_flicker_rate * 0.020000001f;
                ((Counters *)s4)->f[i] = v;
                if (1.0f < v) {
                    v = v - 1.0f;
                    ((Counters *)s4)->f[i] = v;
                    v = ((Counters *)s4)->g[j & 1] + math_random_float_range(0.333f, 0.666f);
                    ((Counters *)s4)->g[i] = v;
                    if (1.0f < v) {
                        v = v - 1.0f;
                        ((Counters *)s4)->g[i] = v;
                    }
                }
            }
            gfx_add_draw_callback_first((void *)DrawDoubleLayerQuadMesh, s3);
        }
        break;
    }
}
