#include "names.h"
/* func_PAL_L20_00449B08, the PAL copy of func_L20_00444088: the same C, where the 1/60 step
 * becomes 0.02, the integer argument takes the 50 Hz scale and the created child is returned. */
#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_yeedil_shot_speed __attribute__((sda));

extern int g_yeedil_shot_homing_param __attribute__((sda));

extern void yeedil_boss_compute_shot_launch_pal(char *, char *, char *, float *);

extern char *homing_l20_shot_spawn_pal(char *, char *, char *, char *, int, float, int);

extern void vec_scale_to_length(char *, char *, float);

/* Launches a damaging shot from the enemy muzzle, scaled by its speed and damage settings. (PAL: 50 Hz timings) */
char *yeedil_boss_launch_damage_shot_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    TI128 position;
    TI128 velocity;
    float aim_angle;

    aim_angle = 0.78539824f;
    yeedil_boss_compute_shot_launch_pal(moby, (char *)&position, (char *)&velocity, (float *)&aim_angle);
    vec_scale_to_length((char *)&velocity, (char *)&velocity, g_yeedil_shot_speed * 0.020000001f);
    return homing_l20_shot_spawn_pal(moby, (char *)&position, (char *)&velocity, state + 0x1F0, (g_yeedil_shot_homing_param * 5 + 2) / 6,
                                 (float)*(unsigned char *)(state + 0x35), *(int *)(state + 0x210));
}
