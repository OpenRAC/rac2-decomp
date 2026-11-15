#include "include_asm.h"
#include "names.h"
extern int g_current_map_index;
extern char *moby_get_motion_data(char *object);
extern void SpawnSpaceProjectile(char *, int, int, int, float, float, float, float, int, int, int);
extern int math_random_int_below(int);
extern int snd_play_from_class_bank(int, int, char *, int);

/* Spawns the object's effect once its guards clear, then runs the timer and marks the run.
 * The two words of the effect's parameters are the same in both calls, so the compiler
 * loads the constant once and copies it into the two argument registers. */
void func_PAL_L05_003D4168(char *obj)
{
    char *s1 = *(char **)(obj + 0x68);
    char *r;

    r = moby_get_motion_data(obj);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x1B8) != 0)
        return;
    if (*(unsigned char *)(obj + 0x20) == 1) {
        if (g_current_map_index == 0xF)
            SpawnSpaceProjectile(obj, 0x60008000, 1, 0, 0.6f, 2.0f, 1.0f, 1.0f, 0, -1, 0);
        else
            SpawnSpaceProjectile(obj, 0x60008000, 1, 0, 1.0f, 2.0f, 1.0f, 1.0f, 0, -1, 0);
    }
    if (math_random_int_below(3) == 0)
        snd_play_from_class_bank(0, 0, obj, 0x957);
    *(int *)(s1 + 0x1B8) = 0x11;
}
