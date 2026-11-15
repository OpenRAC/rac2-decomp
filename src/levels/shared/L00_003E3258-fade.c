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
extern void part_spawn_model_trails(char *, void *, float);
extern void moby_set_fading_alpha_color(int, char *);
extern void set_moby_color(char *, int, int, int);
extern void moby_mark_spawned(char *);

/* Fades each object in the list. When a fade ends, it restores the object and runs its finish function, or deletes it, and drops it from the list. */
void UpdateFadingMobyList(void) {
    int i;
    i = 0;
    if (i < g_fading_moby_count[0]) {
        FadeEntry *base = g_fading_moby_list;
        FadeEntry *prev = (FadeEntry *)((char *)base - 32);
        float zero = 0.0f;
        do {
            float *fade = (float *)((char *)base + (i * 32 + 12));
            FadeEntry *entry = &g_fading_moby_list[i];
            char *fadeObject = entry->object;
            if (*fade != zero) {
                ref_L00_003E7C88_00(fade, 0.0f, D_L00_001B065C * 0.01666666753590107f);
                part_spawn_model_trails(fadeObject, D_L00_001B0648, *fade);
                moby_set_fading_alpha_color(i, D_L00_001B0650[0]);
            } else {
                int callbacks = (int)&base->callback;
                void (**callback)(char *) = (void (**)(char *))(i * 32 + callbacks);
                if (*callback) {
                    set_moby_color(fadeObject, entry->rgb[0], entry->rgb[1], entry->rgb[2]);
                    *(unsigned char *)(fadeObject + 35) = 128;
                    *(unsigned short *)(fadeObject + 52) &= ~2;
                    (*callback)(fadeObject);
                } else moby_mark_spawned(fadeObject);
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
