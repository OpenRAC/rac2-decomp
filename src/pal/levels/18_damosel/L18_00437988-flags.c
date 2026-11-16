#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern u8 *part_spawn_gravity_fade(void *, void *, int, unsigned, int, int, int,
                          float, float, float, int);
extern u8 g_explosion_effect_desc[] __attribute__((sda));
extern u8 *g_particle_template_table[];
extern u8 *fireball_spawn(void *, void *, void *, int, float, float);
extern u8 g_beam_target_vec[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern u8 g_moby_group_flags[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern void moby_set_controller_speed_limits(u8 *arg0, float, float, float, float);
extern u8 g_data_block_base[];

void extermibot_set_slow_limits_pal(u8 *a0) {
    moby_set_controller_speed_limits(a0, 0.008f, 0.064f, 0.040212393f, 1.0053098f);
}

void extermibot_set_fast_limits_pal(u8 *a0) {
    moby_set_controller_speed_limits(a0, 0.2f, 0.22000001f, 0.040212393f, 1.0053098f);
}
