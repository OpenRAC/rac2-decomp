#include "include_asm.h"

#include "common.h"
extern float g_pair_game_centre_pull __attribute__((sda));

/* Pulls a velocity towards the centre of the playfield, more strongly the closer the position is to
 * it. */
void pair_game_apply_centre_pull_pal(float pos_y, float pos_z, float unused_step, float *vel_y, float *vel_z)
{
    float pull = -(g_pair_game_centre_pull * 0.00040000002f) / (pos_y * pos_y + pos_z * pos_z);

    *vel_y = *vel_y + pos_y * pull;
    *vel_z = *vel_z + pos_z * pull;
}
