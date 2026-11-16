#include "include_asm.h"


#include "common.h"
typedef struct {
    char pad[0xc28];
    int flags;
    char pad2[0x2290 - 0xc2c];
    char *current;
} ResidentState;
extern ResidentState g_hero_state;
extern void set_hero_animation_pal(int, int, float);

/* Switches the player between the push animation states depending on the object's value (PAL). */
void hero_switch_push_anim_state_pal(char *object)
{
    char *vars = *(char **)(object + 0x68);
    if ((g_hero_state.flags & 2) && *(unsigned char *)(g_hero_state.current + 0x43) == 0x44)
        set_hero_animation_pal(0x3f, 0, 6.0f);
    else if (*(unsigned char *)(g_hero_state.current + 0x43) == 0x3f && *(float *)(vars + 0x30) != 0.0f)
        set_hero_animation_pal(0x40, 0, 8.0f);
    else if (*(unsigned char *)(g_hero_state.current + 0x43) == 0x40) {
        if (*(float *)(vars + 0x30) > 0.060000002f)
            set_hero_animation_pal(0x41, 0, 8.0f);
        else if (*(float *)(vars + 0x30) == 0.0f)
            set_hero_animation_pal(0x3f, 0, 8.0f);
        else
            goto final_test;
    } else {
final_test:
        /* This path tests the current vars again after the float checks. */
        if (*(unsigned char *)(g_hero_state.current + 0x43) == 0x41 && *(float *)(vars + 0x30) < 0.060000002f)
            set_hero_animation_pal(0x40, 0, 8.0f);
    }
}



