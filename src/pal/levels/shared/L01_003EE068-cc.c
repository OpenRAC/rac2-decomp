/* func_PAL_L01_003EE068, the PAL copy of func_L00_003E7C88: the same C, where rename func_L00_003E7E40 becomes func_PAL_L00_003EC0E0. */
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
extern float D_L00_001B065C __attribute__((sda));
extern int D_L00_001B0648[3] __attribute__((sda));
extern char *D_L00_001B0650[] __attribute__((sda));
extern void ref_L00_003E7C88_00(float *, float, float);
extern void func_PAL_L00_003EC0E0(char *, void *, float);
extern void moby_set_fading_alpha_color(int, char *);
extern void set_moby_color(char *, int, int, int);
extern void moby_mark_spawned(char *);

void func_PAL_L01_003EE068(void) {
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
                ref_L00_003E7C88_00(fade, 0.0f, D_L00_001B065C * 0.020000001f);
                func_PAL_L00_003EC0E0(o, D_L00_001B0648, *fade);
                moby_set_fading_alpha_color(i, D_L00_001B0650[0]);
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
