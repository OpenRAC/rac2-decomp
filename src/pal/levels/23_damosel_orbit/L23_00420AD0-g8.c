#include "include_asm.h"

#include "common.h"
typedef int TI16 __attribute__((mode(TI)));
extern char *g_mothership_boss_moby __attribute__((sda));
extern int g_charged_l23_blast_timer __attribute__((sda));
extern TI16 g_boss_effect_position;
extern void FastVecAdd(char *, char *, char *);
extern void FastVecScale(char *, char *, float);
extern float math_random_float_range(float, float);
extern void moby_mark_spawned(void *);
extern float g_boss_gun_vec_scale_a __attribute__((sda));
extern float g_boss_gun_vec_scale_b __attribute__((sda));
extern float g_mothership_hit_damage_floor MACRO_ADDR;
extern int g_hero_moby NOT_SDA;
extern int g_boss_fight_timer;
typedef struct {
    char pad[0x158];
    float f158;
} Cam_0041B9F0;
extern Cam_0041B9F0 g_hero_l23_state_block;
typedef struct {
    char pad[0x1870];
    char f1870[0xC];
    int f187C;
    char pad2[0x2290 - 0x1880];
    int f2290;
    int f2294;
} Player_0041B9F0;
extern Player_0041B9F0 g_hero_state;
extern void boss_pick_strongest_generator(void);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern char *part_find_owned_effect_slot(void *, int, int);
extern void boss_start_fight_once_pal(void);
extern void gfx_start_color_fade_pal(void *, void *);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, float, float, unsigned char);
extern void moby_fade_out_update_pal(unsigned char *);
extern void part_l23_spawn_hit_sparks_pal(char *);
extern void moby_set_state(void *, int, int);
extern void cancel_hero_item_animation_pal(void);
extern void release_moby_animation_slot(int, void *);
extern s32 hero_l22_set_action_pal(int, int);
extern void gfx_update_color_fade_pal(void *, void *);
extern int part_spawn_damage_debris_pal(void *, void *, void *);
extern void moby_transform_joint_point(void *, int, void *);

/* the boss shield: while it is down, takes the hits of the shots that reach it; while it is up,
   sums the strength of the live generators into the shield measure */
void UpdateShieldHitsAndStrength_pal(unsigned char *moby) {
    char effect_pos[16];
    float spawn_vel[4];
    float joint_matrix[16];
    unsigned char *boss_state = *(unsigned char **)(g_mothership_boss_moby + 0x68);
    char *shot;
    float total;
    int i;

    boss_pick_strongest_generator();
    math_fast_float_d(&g_boss_fight_timer);
    if (*(int *)(boss_state + 0x60C) == -1 && *(char **)(boss_state + 0x610) == 0) {
        FastVecScale(effect_pos, moby + 0xE0, g_boss_gun_vec_scale_a);
        FastVecAdd(effect_pos, effect_pos, moby + 0x10);
        qcopy(&g_boss_effect_position, effect_pos);
        shot = part_find_owned_effect_slot(moby, 0x30000, 0);
        moby[0xA8] = 0xFF;
        FastDecTimer(boss_state + 0x26);
        if (shot != 0) {
            if (*(short *)(boss_state + 0x26) != 0 || *(int *)(boss_state + 0x604) != 0
                || (*(int *)(shot + 0x20) == g_hero_moby && g_charged_l23_blast_timer < 0)) {
                shot = 0;
                if (*(int *)(boss_state + 0x604) != 0 && *(unsigned short *)(boss_state + 0x26) == 0)
                    boss_start_fight_once_pal();
            }
            if (shot != 0) {
                boss_state[0x147] = 0xFF;
                gfx_start_color_fade_pal(moby, boss_state + 0x140);
                if (*(unsigned short *)(moby + 0x7C) != 0) {
                    for (i = 0; i < 4; i++) {
                        float angle;
                        float speed;
                        char *child;

                        angle = FastAddRotations(math_random_signed_float_range(90.0f, 120.0f) * 0.017453294f,
                                              g_hero_l23_state_block.f158);
                        speed = math_random_float_range(2.0f, 4.0f) * 0.020000001f;
                        spawn_vel[0] = math_fast_sin_or_cos_a(angle) * speed;
                        spawn_vel[1] = math_fast_sin_or_cos_b(angle) * speed;
                        spawn_vel[2] = 0.0f;
                        spawn_vel[2] = math_random_float_range(5.0f, 8.0f) * 0.020000001f;
                        child = cam_moby_create_pal(moby, 1, *(short *)(moby + 0xAA), i, moby + 0x10,
                                              moby + 0xF0, spawn_vel, 90.0f, 15.0f, 0xFF);
                        if (child != 0)
                            *(void **)(child + 0x64) = (void *)moby_fade_out_update_pal;
                    }
                    *(unsigned short *)(moby + 0x7C) = 0;
                }
                part_l23_spawn_hit_sparks_pal(*(char **)(shot + 0x20));
                *(float *)(boss_state + 0x20) -= *(float *)(shot + 0x2C);
                *(short *)(boss_state + 0x26) = 17;
                if (*(float *)(boss_state + 0x20) <= 0.0f) {
                    moby_set_state(moby, 4, 0);
                    g_hero_state.f2294 = 0;
                    cancel_hero_item_animation_pal();
                    release_moby_animation_slot(g_hero_state.f2290, g_hero_state.f1870);
                    g_hero_state.f187C = 0;
                    hero_l22_set_action_pal(0, 1);
                    return;
                }
            }
        }
        gfx_update_color_fade_pal(moby, boss_state + 0x140);
        part_spawn_damage_debris_pal(moby, boss_state + 0x210, boss_state + 0x20);
    } else {
        char *held_part;

        total = *(float *)(boss_state + 0x32C) * (float)*(short *)(boss_state + 0x2F6);
        if (*(int *)(boss_state + 0x60C) != -1) {
            int gen_index;

            moby_transform_joint_point(moby, *(int *)(boss_state + 0x60C) + 1, joint_matrix);
            FastVecScale(effect_pos, (char *)(joint_matrix + 4), g_boss_gun_vec_scale_b);
            FastVecAdd(effect_pos, effect_pos, moby + 0x10);
            qcopy(&g_boss_effect_position, effect_pos);
            for (gen_index = 0; gen_index < 5; gen_index++) {
                char *generator = ((char **)(boss_state + 0x358))[gen_index];

                if (generator != 0) {
                    float generator_hp = *(float *)(*(char **)(generator + 0x68) + 0x20);

                    if (g_mothership_hit_damage_floor < generator_hp)
                        total += generator_hp;
                }
            }
        } else {
            FastVecScale(effect_pos, moby + 0xE0, g_boss_gun_vec_scale_a);
            FastVecAdd(effect_pos, effect_pos, moby + 0x10);
            qcopy(&g_boss_effect_position, effect_pos);
        }
        held_part = *(char **)(boss_state + 0x610);
        if (held_part != 0) {
            float held_hp = *(float *)(*(char **)(held_part + 0x68) + 0x20);

            if (held_hp >= 0.0f) {
                total += held_hp;
            } else {
                moby_mark_spawned(held_part);
                *(char **)(boss_state + 0x610) = 0;
                *(short *)(boss_state + 0x26) = 25;
            }
        }
        if (*(unsigned short *)(moby + 0x7C) != 0)
            total += *(float *)(boss_state + 0x324) * (float)*(short *)(boss_state + 0x2F6);
        *(float *)(boss_state + 0x20) = total;
    }
}
