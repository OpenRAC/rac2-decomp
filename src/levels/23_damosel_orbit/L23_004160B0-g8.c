#include "common.h"

/* func_L23_004160B0 is a unit of its own: it reads $gp (hence -g8), and it is built with -g,
   whose line label in front of the division makes the assembler pad it with retail's two nops
   (the effect func_L23_003BF9B0 and func_L23_004402D8 use). The division stays in a statement of
   its own for that label.
   Measured on this body:
   - the three float constants of the loop are locals set at the top of the `if` block, in the
     order 90.0f, 1/60, pi/180: loop.c hoists invariants in the order it finds them, and retail
     has them in that order ahead of the loop. As literals, the pi/180 factor (used first) comes
     out ahead of the other two; set at the top of the loop body instead, the 90.0f local is
     replaced by its constant in both calls (gcse's constant propagation) and is not hoisted;
   - `0.017453294f` is the spelling of retail's 0x3C8EFA36;
   - `hit = 0` follows `if (f()) g();`, or the call's delay slot takes it;
   - `base` is read inside the loop, which gives the hoisted address pair and the
     `lwc1 $f13,0x158($s6)` in the call's delay slot;
   - func_00273730 is declared with its int 0xFF argument last, for the `addiu $t3` in the delay
     slot of its call;
   - D_L23_001B13CC is read as a variable (retail compares with its value), not written 0.0f. */

extern float g_mothership_hit_damage_scale __attribute__((sda));

extern float g_mothership_hit_damage_floor __attribute__((sda));

extern char *g_mothership_boss_moby __attribute__((sda));

extern char g_hero_l23_state_block[];

extern char *part_find_owned_effect_slot(char *, int, int);

extern int FastDecTimer(char *);

extern int mothership_is_held(void);

extern void boss_start_fight_once(void);

extern void gfx_start_color_fade(char *, char *);

extern void gfx_update_color_fade(char *, char *);

extern void part_l23_spawn_hit_sparks(char *);

extern void mothership_attach_hit_effect(char *);

extern float math_random_signed_float_range(float, float);

extern float FastAddRotations(float, float);

extern float math_random_float_range(float, float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern char *cam_moby_create(char *, int, int, int, char *, char *, float *, float, float, int);

extern void moby_fade_out_update(void);

/* Updates the hit state of the object, and when its mask word still has bits set, spawns one
   particle per set bit (at most ten, fewer the fuller the value at +0x20 is), each launched at
   a random angle and speed, and clears the bit. */
/* Handles hits on this object: loses health, plays hit effects, and throws out sparks as it gets more damaged. */
void enemy_handle_hit_sparks(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *hit;
    int particle_count;
    int i;
    float velocity[3];

    hit = part_find_owned_effect_slot(moby, 0x30000, 1);
    *(unsigned char *)(moby + 0xA8) = 0xFF;
    FastDecTimer(vars + 0x26);
    if (hit != 0) {
        if (*(short *)(vars + 0x26) != 0 || (g_mothership_boss_moby != 0 && mothership_is_held() != 0)) {
            if (mothership_is_held() != 0)
                boss_start_fight_once();
            hit = 0;
        }
    }
    if (hit != 0) {
        *(unsigned char *)(vars + 0x147) = 0xFF;
        gfx_start_color_fade(moby, vars + 0x140);
        part_l23_spawn_hit_sparks(*(char **)(hit + 0x20));
        if (*(float *)(vars + 0x20) <= g_mothership_hit_damage_floor) {
            mothership_attach_hit_effect(hit);
            *(float *)(vars + 0x20) = g_mothership_hit_damage_floor;
        } else {
            *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - *(float *)(hit + 0x2C);
        }
        if (*(float *)(vars + 0x20) <= g_mothership_hit_damage_floor)
            *(float *)(vars + 0x20) = g_mothership_hit_damage_floor;
        if (*(short *)(*(char **)(hit + 0x20) + 0xAA) != 0x118F /* moby class 4495 */)
            *(short *)(vars + 0x26) = 0x14;
        if (*(unsigned short *)(moby + 0x7C) != 0) {
            float damage_ratio;

            damage_ratio = *(float *)(vars + 0x20) / g_mothership_hit_damage_scale;
            particle_count = 10 - (int)(damage_ratio * 10.0f);
            if (*(float *)(vars + 0x20) <= g_mothership_hit_damage_floor)
                particle_count = 10;
            for (i = 0; i < particle_count; i++) {
                int mask = *(unsigned short *)(moby + 0x7C);

                if ((mask >> i) & 1) {
                    float angle, speed;
                    char *particle;
                    char *base = g_hero_l23_state_block;
                    float spread = 90.0f;
                    float per_tick = 0.016666668f;
                    float to_rad = 0.017453294f;

                    *(unsigned short *)(moby + 0x7C) = mask & ~(1 << i);
                    angle = FastAddRotations(math_random_signed_float_range(spread, 120.0f) * to_rad,
                                          *(float *)(base + 0x158));
                    speed = math_random_float_range(2.0f, 4.0f) * per_tick;
                    velocity[0] = math_fast_sin_or_cos_a(angle) * speed;
                    velocity[1] = math_fast_sin_or_cos_b(angle) * speed;
                    velocity[2] = 0.0f;
                    velocity[2] = math_random_float_range(5.0f, 8.0f) * per_tick;
                    particle = cam_moby_create(moby, 1, *(short *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                                      velocity, spread, 15.0f, 0xFF);
                    if (particle != 0)
                        *(void (**)(void))(particle + 0x64) = moby_fade_out_update;
                }
            }
        }
    }
    gfx_update_color_fade(moby, vars + 0x140);
}
