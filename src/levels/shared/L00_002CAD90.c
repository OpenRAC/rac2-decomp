#include "include_asm.h"
#include "names.h"

extern int func_L00_002D1DA0_1(int, void *, void *);

extern void anim_start_blended(void *, int, int, int);

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
/* Handles the lock-on target for the hero: keeps it while the buttons are held and it is close, drops it otherwise, and looks for a new one. */
void UpdateHeroHeldTarget(void)
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
        if (g_frame_counter > g_progress_statistics[36].best)
            g_progress_statistics[36].best = g_frame_counter;
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



/* func_L00_002CB3A8 is in the sibling file L00_002CB3A8-decider.c (its own profile). */

/* loads two object pointers from fixed data, bails out when either is null or when the first object's byte 67 differs from 1, fills two stack ints through a helper, then applies a four-argument operation to each object with those ints */
/* Switches the hero's two linked objects to the animation chosen for the current move. */
void hero_set_linked_objects_anim(void)
{
    char *hero = D_00189E20_36;
    void *firstObj;
    void *secondObj;
    int animIds[2];

    firstObj = *(void **)(hero + 4880);
    secondObj = *(void **)(hero + 4884);

    if (firstObj == 0)
        return;
    if (secondObj == 0)
        return;

    if (*(unsigned char *)((char *)firstObj + 67) != 1)
        return;

    if (func_L00_002D1DA0_1(0, animIds, animIds + 1) == 0)
        return;

    anim_start_blended(firstObj, animIds[0], 0, 7);
    anim_start_blended(secondObj, animIds[1], 0, 7);
}

/* func_L00_002D1B70 is in the sibling file L00_002CAD90-g8.c (-G8). */



