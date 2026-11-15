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
extern void func_PAL_L02_003F3358(char *);
extern void ApproachValue(float *, float, float);
extern int g_frame_l02_counter __attribute__((sda));
extern Pad003EE938 g_pad_state;

/* The actor's state machine (byte at +0x20): 0 prepares it, 1 waits for the target to come within
   range on its own frame of eight, 2 follows the pad until the state asks to restart. */
void func_PAL_L02_003F2EC0(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int v;

    switch (*(unsigned char *)(arg0 + 0x20)) {
    case 0:
        if (*(int *)state == -1) {
            moby_mark_spawned(arg0);
            return;
        }
        path_init_bounds(arg0);
        *(TI128 *)(arg0 + 0x10) = *(TI128 *)(state + 0x20);
        v = FloatToInt(*(float *)(state + 0x2C) * 1.5f);
        if (v >= 256)
            v = 255;
        *(unsigned char *)(arg0 + 0x30) = v;
        moby_set_state(arg0, 1, -1);
        return;
    case 1:
        if ((g_frame_l02_counter & 7) == (((int)arg0 >> 8) & 7)) {
            if (path_is_hero_near_point(arg0)) {
                moby_set_state(arg0, 2, -1);
                *(int *)(state + 0x34) = 0;
            }
        }
        return;
    case 2:
        *(float *)(state + 0x44) = path_update_progress(arg0);
        func_PAL_L02_003F3358(arg0);
        if (0.2f < g_pad_state.f100 + g_pad_state.f104)
            ApproachValue((float *)(state + 0x34), 0.0f, 0.40000004f);
        if (*(float *)(state + 4) + 1.0f < *(float *)(state + 0x44))
            moby_set_state(arg0, 1, -1);
        return;
    }
}
