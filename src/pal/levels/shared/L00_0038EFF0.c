#include "include_asm.h"
#include "names.h"



extern void projectile_l00_bouncing_update_pal(char *object);
extern void projectile_l00_falling_update_pal(char *object);
extern float FastAddRotations(float value, float step);
extern void moby_fade_colour_by_countdown_pal(char *object);
extern void vec_transform_or_copy(char *target, char *source);
extern void shop_trigger_current_state_effect(char *target, char *source);
extern void weapon_update_hit_sweep_pal(char *object);

/* Dispatches on a byte mode at object+32: mode 0 updates two float angles from a linked node and runs a follow-up call; mode 1 refreshes a 16-byte block and a node copy then calls a final update. */
void turning_fading_moby_update_pal(char *object)
{
    char *moby = object;
    unsigned char mode = *(unsigned char *)(moby + 32);
    char *vars = *(char **)(moby + 104);
    float result;

    switch (mode) {
    case 0:
        if (*(int *)(vars + 20) != 0) {
            projectile_l00_bouncing_update_pal(moby);
        } else {
            projectile_l00_falling_update_pal(moby);
        }
        result = FastAddRotations(*(float *)(moby + 240), 0.04188791f);
        *(float *)(moby + 240) = result;
        result = FastAddRotations(*(float *)(moby + 244), 0.15707967f);
        *(float *)(moby + 244) = result;
        moby_fade_colour_by_countdown_pal(moby);
        break;
    case 1:
        vec_transform_or_copy((char *)(moby + 16), (char *)(moby + 16));
        shop_trigger_current_state_effect(vars, vars);
        weapon_update_hit_sweep_pal(moby);
        break;
    }
}



