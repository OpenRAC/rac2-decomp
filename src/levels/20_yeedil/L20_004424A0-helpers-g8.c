#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L20_001B212C __attribute__((sda));
extern float D_L20_001B2130 __attribute__((sda));
extern float D_L20_001B2138 __attribute__((sda));
extern float D_L20_001B2128 __attribute__((sda));


extern void moby_set_controller_speed_limits(unsigned char *, float, float, float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern float square_root(float);

/* Gets the enemy ready to jump. It picks the turn speed, remembers the ground height and works out how fast to go up. */
void yeedil_boss_start_jump(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    moby_set_controller_speed_limits((unsigned char *)actor, 0.0f, 0.0f,
                 D_L20_001B212C * 4.84813745e-06f,
                 D_L20_001B2130 * 0.000290888245f);
    *(float *)(state + 0x7C) = D_L20_001B2138 * 0.000277777785f;
    *(float *)(state + 0xE0) = coll_probe_ground_height_below(actor + 0x10, 0, 0.5f);
    qzero(state + 0xF0);
    *(float *)(state + 0xF8) = square_root(*(float *)(state + 0x7C) * 2.0f * D_L20_001B2128);
}
