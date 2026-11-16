#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    unsigned char pad[0x100];
    float f100;
    float f104;
} Pad003EE938;
extern void moby_mark_spawned(char *);
extern void path_init_bounds(char *);
extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern int path_is_hero_near_point(char *);
extern float path_update_progress(char *);
extern void path_update_hero_heading_pal(char *);
extern float ApproachValue(float *, float, float);
extern int g_frame_l02_counter __attribute__((sda));
extern Pad003EE938 g_pad_state;

/* The actor's state machine (byte at +0x20): 0 prepares it, 1 waits for the target to come within
   range on its own frame of eight, 2 follows the pad until the state asks to restart. */
void path_l02_follower_update_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    int alpha;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (*(int *)state == -1) {
            moby_mark_spawned(moby);
            return;
        }
        path_init_bounds(moby);
        *(TI128 *)(moby + 0x10) = *(TI128 *)(state + 0x20);
        alpha = FloatToInt(*(float *)(state + 0x2C) * 1.5f);
        if (alpha >= 256)
            alpha = 255;
        *(unsigned char *)(moby + 0x30) = alpha;
        moby_set_state(moby, 1, -1);
        return;
    case 1:
        if ((g_frame_l02_counter & 7) == (((int)moby >> 8) & 7)) {
            if (path_is_hero_near_point(moby)) {
                moby_set_state(moby, 2, -1);
                *(int *)(state + 0x34) = 0;
            }
        }
        return;
    case 2:
        *(float *)(state + 0x44) = path_update_progress(moby);
        path_update_hero_heading_pal(moby);
        if (0.2f < g_pad_state.f100 + g_pad_state.f104)
            ApproachValue((float *)(state + 0x34), 0.0f, 0.40000004f);
        if (*(float *)(state + 4) + 1.0f < *(float *)(state + 0x44))
            moby_set_state(moby, 1, -1);
        return;
    }
}
