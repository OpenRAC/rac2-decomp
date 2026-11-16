/* func_PAL_L00_003EBF24, the PAL copy of func_L00_003E7C88: the same C, where the
 * per-frame step 1/60 becomes 1/50 and the callee at +0x98 is func_PAL_L00_003EC0E0. */
#include "common.h"

typedef struct {
    char *object;
    unsigned char rgb[4];
    int unused;
    float fade;
    void (*callback)(char *);
    int rest[3];
} FadeEntry;

extern FadeEntry g_fading_moby_list[];
extern int g_fading_moby_count[] __attribute__((sda));
extern float g_fade_duration_scale __attribute__((sda));
extern int g_model_trail_params[3] __attribute__((sda));
extern char *g_fade_color_table[] __attribute__((sda));
extern void ref_L00_003E7C88_00(float *, float, float);
extern void func_PAL_L00_003EC0E0(char *, void *, float);
extern void moby_set_fading_alpha_color(int, char *);
extern void set_moby_color(char *, int, int, int);
extern void moby_mark_spawned(char *);

void func_PAL_L00_003EBF24(void) {
    int i;
    i = 0;
    if (i < g_fading_moby_count[0]) {
        FadeEntry *base = g_fading_moby_list;
        FadeEntry *prev = (FadeEntry *)((char *)base - 32);
        float zero = 0.0f;
        do {
            float *fade = (float *)((char *)base + (i * 32 + 12));
            FadeEntry *p = &g_fading_moby_list[i];
            char *o = p->object;
            if (*fade != zero) {
                ref_L00_003E7C88_00(fade, 0.0f, g_fade_duration_scale * 0.020000001f);
                func_PAL_L00_003EC0E0(o, g_model_trail_params, *fade);
                moby_set_fading_alpha_color(i, g_fade_color_table[0]);
            } else {
                int callbacks = (int)&base->callback;
                void (**callback)(char *) = (void (**)(char *))(i * 32 + callbacks);
                if (*callback) {
                    set_moby_color(o, p->rgb[0], p->rgb[1], p->rgb[2]);
                    *(unsigned char *)(o + 35) = 128;
                    *(unsigned short *)(o + 52) &= ~2;
                    (*callback)(o);
                } else moby_mark_spawned(o);
                {
                    FadeEntry *end = (FadeEntry *)(g_fading_moby_count[0] * 32 + (int)prev);
                    g_fading_moby_count[0]--;
                    g_fading_moby_list[i] = *end;
                }
            }
            i++;
        } while (i < g_fading_moby_count[0]);
    }
}
