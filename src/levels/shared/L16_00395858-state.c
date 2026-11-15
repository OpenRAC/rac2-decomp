#include "common.h"
typedef struct {
    char pad[0xc28];
    int flags;
    char pad2[0x2290 - 0xc2c];
    char *current;
} ResidentState;
extern ResidentState g_hero_state;
extern void set_hero_animation(int, int, float);

/* Switches the player between the push animation states depending on the object's value. */
void hero_switch_push_anim_state(char *object)
{
    char *state = *(char **)(object + 0x68);
    if ((g_hero_state.flags & 2) && *(unsigned char *)(g_hero_state.current + 0x43) == 0x44)
        set_hero_animation(0x3f, 0, 7.0f);
    else if (*(unsigned char *)(g_hero_state.current + 0x43) == 0x3f && *(float *)(state + 0x30) != 0.0f)
        set_hero_animation(0x40, 0, 10.0f);
    else if (*(unsigned char *)(g_hero_state.current + 0x43) == 0x40) {
        if (*(float *)(state + 0x30) > 0.05000000447f)
            set_hero_animation(0x41, 0, 10.0f);
        else if (*(float *)(state + 0x30) == 0.0f)
            set_hero_animation(0x3f, 0, 10.0f);
        else
            goto finalTest;
    } else {
finalTest:
        /* This path tests the current state again after the float checks. */
        if (*(unsigned char *)(g_hero_state.current + 0x43) == 0x41 && *(float *)(state + 0x30) < 0.05000000447f)
            set_hero_animation(0x40, 0, 10.0f);
    }
}
