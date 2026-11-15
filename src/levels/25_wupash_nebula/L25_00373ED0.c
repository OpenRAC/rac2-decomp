#include "include_asm.h"
#include "names.h"

/* func_L25_003752D8, func_L25_00376FE0 and func_L25_00377608 live in the sibling
   small-data unit (L25_00373ED0-g8.c): their loop counts are read through $gp. */


/* func_L25_0040CDA0 is in L25_00373ED0-mission-g8.c. */

/* func_L25_0040D208 is in L25_00373ED0-hud-g8.c. */

extern char *part_find_owned_effect_slot(char *a0, int a1, int a2);

extern void gfx_update_color_fade(char *a0, char *a1);

extern void gfx_start_color_fade(char *a0, char *a1);

extern int snd_play_from_class_bank(int index, int value, char *object, int kind);

extern void part_spawn_shockwave_burst(void *a0, void *a1, int a2, int a3, int a4, int a5, int a6, int a7,
                              int a8, int a9, int a10, float f12);

extern void func_L05_00421908(char *a0, int a1, int a2);

extern int moby_is_in_use(char *a0);

extern void moby_release_from_group(char *a0);

extern void moby_reset_action_state(char *a0);

/* The moby's death timer: it ticks the stored time down and, once it reaches zero,
   fires the object's effect and takes the moby down, which it reports. */
int moby_tick_death_timer(char *objectMoby, int flag)
{
    char *effectLink;
    float *timerPtr;
    char *frameInfo;
    char *vars;
    int ret = 0;

    frameInfo = part_find_owned_effect_slot(objectMoby, 0x230000, 0);
    *(unsigned char *)(objectMoby + 0xA8) = 0xFF;
    vars = *(char **)(objectMoby + 0x68);
    effectLink = *(char **)(vars + 0x10);
    timerPtr = *(float **)(vars + 0x0);
    if (effectLink != 0) {
        gfx_update_color_fade(objectMoby, effectLink);
    }
    if (frameInfo != 0) {
        if (effectLink != 0) {
            *(unsigned char *)(effectLink + 7) = 0xFF;
            gfx_start_color_fade(objectMoby, effectLink);
        }
        *timerPtr = *timerPtr - *(float *)(frameInfo + 0x2C);
        if (*(short *)(objectMoby + 0xAA) != 0xB73 /* moby class 2931 */) {
            snd_play_from_class_bank(2, 0, objectMoby, 0x957);
        }
        if (*timerPtr <= 0.0f) {
            *timerPtr = 0.0f;
            part_spawn_shockwave_burst(objectMoby + 0x10, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 0, 0, 0.5f);
            func_L05_00421908(objectMoby, 1, 0x19);
            if (moby_is_in_use(objectMoby)) {
                moby_release_from_group(objectMoby);
            }
            if (flag == 0) {
                moby_reset_action_state(objectMoby);
            }
            ret = 1;
        }
    }
    return ret;
}

/* func_L25_0040DE40 is defined in L25_00373ED0-fade-g8.c. */
