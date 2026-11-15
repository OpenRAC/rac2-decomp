#include "common.h"

/* func_L23_004278D8 is a unit of its own: it reads $gp (hence -g8), and it is built with -g,
   whose line label in front of the division makes the assembler pad it with retail's two nops
   (the effect func_L23_004160B0 uses). The division stays in a statement of its own.
   Measured on this body:
   - D_L23_001B36FC is a plain extern: it comes out absolute (`lui $at` + `lwc1`) outside a delay
     slot, as retail; marked sda it would be one $gp-relative load;
   - the particle emitter is func_L23_004160B0's, with its constants in the same order (90.0f,
     1/60, pi/180 as locals of the loop body) and `vec[2]` stored twice. */

extern u8 *g_mothership_boss_moby __attribute__((sda));

extern s32 D_L23_001B1694 __attribute__((sda));

extern s32 g_hero_moby __attribute__((nosda));

extern float D_L23_001B36FC;

extern char D_L23_001BA500[];

extern u8 *part_find_owned_effect_slot(u8 *, s32, s32);

extern int FastDecTimer(u8 *);

extern s32 mothership_is_attack_state(void);

extern s32 mothership_is_held(void);

extern void boss_start_fight_once(void);

extern void gfx_start_color_fade(u8 *, u8 *);

extern void gfx_update_color_fade(u8 *, u8 *);

extern void part_l23_spawn_hit_sparks(u8 *);

extern float math_random_signed_float_range(float, float);

extern float FastAddRotations(float, float);

extern float math_random_float_range(float, float);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern u8 *cam_moby_create(u8 *, s32, s32, s32, u8 *, u8 *, float *, float, float, s32);

extern void moby_fade_out_update(void);

/* Hit handler of the object: takes the damage of the object that hit it (unless the shield state
   or the hit filter rejects the hit), then spawns one particle per set bit of the mask word, at
   most ten, fewer the more of the timer is left. */
/* Handles hits on the boss part. It takes damage, ignores some hits, and throws out small
   pieces as it loses health. */
void boss_part_handle_hit(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *hit;
    s32 piece_count;
    s32 i;
    float vec[3];

    hit = part_find_owned_effect_slot(moby, 0x30000, 1);
    moby[0xA8] = 0xFF;
    FastDecTimer(vars + 0x26);
    if (hit != 0) {
        if (mothership_is_attack_state() == 0 || *(s16 *)(vars + 0x26) != 0 ||
            (g_mothership_boss_moby != 0 && mothership_is_held() != 0) ||
            (*(s32 *)(hit + 0x20) == g_hero_moby && D_L23_001B1694 < 0)) {
            if (mothership_is_held() != 0)
                boss_start_fight_once();
            hit = 0;
        }
    }
    if (hit != 0) {
        *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - *(float *)(hit + 0x2C);
        if (*(float *)(vars + 0x20) > 0.0f) {
            vars[0x147] = 0xFF;
            gfx_start_color_fade(moby, vars + 0x140);
            part_l23_spawn_hit_sparks(*(u8 **)(hit + 0x20));
            if (*(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) != 0x118F)
                *(s16 *)(vars + 0x26) = 0x14;
            if (*(u16 *)(moby + 0x7C) != 0) {
                float health_ratio;

                health_ratio = *(float *)(vars + 0x20) / D_L23_001B36FC;
                piece_count = 10 - (s32)(health_ratio * 10.0f);
                for (i = 0; i < piece_count; i++) {
                    s32 mask = *(u16 *)(moby + 0x7C);

                    if ((mask >> i) & 1) {
                        float angle, speed;
                        u8 *piece;
                        u8 *base = (u8 *)D_L23_001BA500;
                        float spread = 90.0f;
                        float per_tick = 0.016666668f;
                        float to_rad = 0.017453294f;

                        *(u16 *)(moby + 0x7C) = mask & ~(1 << i);
                        angle = FastAddRotations(math_random_signed_float_range(spread, 120.0f) * to_rad,
                                              *(float *)(base + 0x158));
                        speed = math_random_float_range(2.0f, 4.0f) * per_tick;
                        vec[0] = math_fast_sin_or_cos_a(angle) * speed;
                        vec[1] = math_fast_sin_or_cos_b(angle) * speed;
                        vec[2] = 0.0f;
                        vec[2] = math_random_float_range(5.0f, 8.0f) * per_tick;
                        piece = cam_moby_create(moby, 1, *(s16 *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                                          vec, spread, 15.0f, 0xFF);
                        if (piece != 0)
                            *(void (**)(void))(piece + 0x64) = moby_fade_out_update;
                    }
                }
            }
        }
    }
    gfx_update_color_fade(moby, vars + 0x140);
}
