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
extern void func_PAL_L23_00423838(void);
extern void func_PAL_002AC290(void *, void *);
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
extern s32 func_PAL_L22_002C99C8(int, int);
extern void func_PAL_002AC3C0(void *, void *);
extern int part_spawn_damage_debris_pal(void *, void *, void *);
extern void moby_transform_joint_point(void *, int, void *);

/* the boss shield: while it is down, takes the hits of the shots that reach it; while it is up,
   sums the strength of the live generators into the shield measure */
void UpdateShieldHitsAndStrength_pal(unsigned char *moby) {
    char tmp[16];
    float vec[4];
    float mtx[16];
    unsigned char *st = *(unsigned char **)(g_mothership_boss_moby + 0x68);
    char *hit;
    float total;
    int i;

    boss_pick_strongest_generator();
    math_fast_float_d(&g_boss_fight_timer);
    if (*(int *)(st + 0x60C) == -1 && *(char **)(st + 0x610) == 0) {
        FastVecScale(tmp, moby + 0xE0, g_boss_gun_vec_scale_a);
        FastVecAdd(tmp, tmp, moby + 0x10);
        qcopy(&g_boss_effect_position, tmp);
        hit = part_find_owned_effect_slot(moby, 0x30000, 0);
        moby[0xA8] = 0xFF;
        FastDecTimer(st + 0x26);
        if (hit != 0) {
            if (*(short *)(st + 0x26) != 0 || *(int *)(st + 0x604) != 0
                || (*(int *)(hit + 0x20) == g_hero_moby && g_charged_l23_blast_timer < 0)) {
                hit = 0;
                if (*(int *)(st + 0x604) != 0 && *(unsigned short *)(st + 0x26) == 0)
                    func_PAL_L23_00423838();
            }
            if (hit != 0) {
                st[0x147] = 0xFF;
                func_PAL_002AC290(moby, st + 0x140);
                if (*(unsigned short *)(moby + 0x7C) != 0) {
                    for (i = 0; i < 4; i++) {
                        float angle;
                        float speed;
                        char *child;

                        angle = FastAddRotations(math_random_signed_float_range(90.0f, 120.0f) * 0.017453294f,
                                              g_hero_l23_state_block.f158);
                        speed = math_random_float_range(2.0f, 4.0f) * 0.020000001f;
                        vec[0] = math_fast_sin_or_cos_a(angle) * speed;
                        vec[1] = math_fast_sin_or_cos_b(angle) * speed;
                        vec[2] = 0.0f;
                        vec[2] = math_random_float_range(5.0f, 8.0f) * 0.020000001f;
                        child = cam_moby_create_pal(moby, 1, *(short *)(moby + 0xAA), i, moby + 0x10,
                                              moby + 0xF0, vec, 90.0f, 15.0f, 0xFF);
                        if (child != 0)
                            *(void **)(child + 0x64) = (void *)moby_fade_out_update_pal;
                    }
                    *(unsigned short *)(moby + 0x7C) = 0;
                }
                part_l23_spawn_hit_sparks_pal(*(char **)(hit + 0x20));
                *(float *)(st + 0x20) -= *(float *)(hit + 0x2C);
                *(short *)(st + 0x26) = 17;
                if (*(float *)(st + 0x20) <= 0.0f) {
                    moby_set_state(moby, 4, 0);
                    g_hero_state.f2294 = 0;
                    cancel_hero_item_animation_pal();
                    release_moby_animation_slot(g_hero_state.f2290, g_hero_state.f1870);
                    g_hero_state.f187C = 0;
                    func_PAL_L22_002C99C8(0, 1);
                    return;
                }
            }
        }
        func_PAL_002AC3C0(moby, st + 0x140);
        part_spawn_damage_debris_pal(moby, st + 0x210, st + 0x20);
    } else {
        char *held;

        total = *(float *)(st + 0x32C) * (float)*(short *)(st + 0x2F6);
        if (*(int *)(st + 0x60C) != -1) {
            int k;

            moby_transform_joint_point(moby, *(int *)(st + 0x60C) + 1, mtx);
            FastVecScale(tmp, (char *)(mtx + 4), g_boss_gun_vec_scale_b);
            FastVecAdd(tmp, tmp, moby + 0x10);
            qcopy(&g_boss_effect_position, tmp);
            for (k = 0; k < 5; k++) {
                char *gen = ((char **)(st + 0x358))[k];

                if (gen != 0) {
                    float v = *(float *)(*(char **)(gen + 0x68) + 0x20);

                    if (g_mothership_hit_damage_floor < v)
                        total += v;
                }
            }
        } else {
            FastVecScale(tmp, moby + 0xE0, g_boss_gun_vec_scale_a);
            FastVecAdd(tmp, tmp, moby + 0x10);
            qcopy(&g_boss_effect_position, tmp);
        }
        held = *(char **)(st + 0x610);
        if (held != 0) {
            float h = *(float *)(*(char **)(held + 0x68) + 0x20);

            if (h >= 0.0f) {
                total += h;
            } else {
                moby_mark_spawned(held);
                *(char **)(st + 0x610) = 0;
                *(short *)(st + 0x26) = 25;
            }
        }
        if (*(unsigned short *)(moby + 0x7C) != 0)
            total += *(float *)(st + 0x324) * (float)*(short *)(st + 0x2F6);
        *(float *)(st + 0x20) = total;
    }
}
