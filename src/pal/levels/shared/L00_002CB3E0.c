#include "include_asm.h"
#include "names.h"
/* func_PAL_L00_002CB3E0, the PAL copy of func_L00_002CB038. */
extern char D_00189E20_36[];

extern unsigned char g_movie_seen_flags[] __attribute__((sda));
extern unsigned int g_pad_pressed_flags;
extern unsigned char g_pad_state[];
extern unsigned int g_frame_counter __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern unsigned char g_scalar_transition_state[];

typedef struct {
    unsigned short count;
    unsigned short reserved;
    unsigned int best;
    unsigned int levels;
} Statistics;
extern Statistics g_progress_statistics[];

extern float fast_vec_dist(void *, void *);
/* Typed call shape: the EE assigns the GPR and FP banks independently of this order. */
extern char *SelectBestEligibleTarget(void *, float, float, float, float, int, int);

/* keeps the hero's held target (0x1450) while both low pad bits are set: clears it on an ineligible screen, beyond 30 units or on release, records a statistic when the target stops being eligible; with no target and both bits set plus either in the next pad word, picks one from the camera's view and then from the hero's */
void func_PAL_L00_002CB3E0(void)
{
    char *hero = D_00189E20_36;
    int screen = *(int *)(hero + 0x1248);
    char *object;

    if (screen < 0 || !(g_movie_seen_flags[screen] & 0x20) || *(int *)(hero + 0x2294) == 0x31) {
        *(int *)(hero + 0x1450) = 0;
        return;
    }
    object = *(char **)(hero + 0x1450);
    if (object) {
        if (30.0f < fast_vec_dist(hero + 0x80, object + 0x10))
            *(int *)(hero + 0x1450) = 0;
        if ((g_pad_pressed_flags & 3) != 3)
            *(int *)(hero + 0x1450) = 0;
        if (!*(char **)(hero + 0x1450) || (*(unsigned short *)(*(char **)(hero + 0x1450) + 0x34) & 0x1000))
            return;
        *(int *)(hero + 0x1450) = 0;
        if (g_progress_statistics[36].count < 0xFFFF)
            g_progress_statistics[36].count++;
        if ((((int)(g_frame_counter) * 5 + 2) / 6) > g_progress_statistics[36].best)
            g_progress_statistics[36].best = ((int)(g_frame_counter) * 5 + 2) / 6;
        g_progress_statistics[36].levels = (g_progress_statistics[36].levels | (1u << g_current_map_index)) | 0x80000000u;
        return;
    }
    {
        unsigned char *pad = g_pad_state;
        if ((*(unsigned int *)(pad + 0x1A0) & 3) == 3 && (*(unsigned int *)(pad + 0x1A4) & 3) != 0) {
            float radius = 25.0f;
            unsigned char *camera = g_scalar_transition_state;
            float nearAngle = 0.6108652949333191f;
            float farAngle = 1.2217305898666382f;
            char *found = SelectBestEligibleTarget(camera + 0x370, radius, *(float *)(camera + 0x158), nearAngle, farAngle, 5, 1);
            *(char **)(hero + 0x1450) = found;
            if (!found)
                *(char **)(hero + 0x1450) = SelectBestEligibleTarget(hero, radius, *(float *)(hero + 0x98), nearAngle, farAngle, 5, 1);
        }
    }
}
