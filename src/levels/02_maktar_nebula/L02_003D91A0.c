#include "common.h"

extern int g_moby_l02_pool[] __attribute__((sda));
/* Read-only view: these loads may pass the state stores, as in retail. */
extern const int D_L02_001B359C_1[] __attribute__((sda));
extern int D_L02_001FF6B8[];
extern int FloatToInt(float);
extern void get_moby_color(char *, void *, void *, void *);
extern void mem_clear(void *, int, int);
extern void brawler_switch_off_actor(char *);
extern void *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength(char *, void *);
extern void gfx_start_color_fade(int, char *);
extern void moby_set_state(char *, int, int);
extern void moby_copy_joint_transform_to_object(char *, char *, int, int);
extern int weapon_select_aim_target(char *, int, int, int, float, float);
extern void chainblade_advance_health_phase(char *);
extern void arena_set_current_boss(void *, void *);
extern void walker_boss_update_movement_shake(char *);
extern void twin_muzzle_turret_update(char *);

/* Field-at-use prefix only; the full state allocation is not inferred. */
struct InitPrefix {
    u8 reserved00[0x28]; u8 mode, ready; u8 reserved2A[6];
    float radius; u8 reserved34[0x14]; u8 flag; u8 reserved49; u8 limit;
    u8 reserved4B[5]; int enabled; float gain, weight, scale, turn;
    u8 reserved64[0x18]; float rate, maximum, epsilon; int phase;
    u8 reserved8C[0x98]; float blend; u8 reserved128[0x11]; u8 active;
};

/* Sets up a Maktar walker boss on its first frame, then handles damage taken, its health, and hit reactions every frame. */
void walker_boss_update_damage(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *owner_moby;
    char *body_part;
    char *legs_moby;
    char *legs_moby2;
    char *hit_info;
    char *hit_source;
    float damage_amount;
    if (*(unsigned char *)(moby + 0x20) == 0) {
        struct InitPrefix *init_vars = (struct InitPrefix *)vars;
        init_vars->flag = FloatToInt(15.0f);
        init_vars->limit = FloatToInt(24.0f);
        init_vars->active = 1;
        init_vars->mode = 3;
        init_vars->blend = 0.5f;
        init_vars->gain = 1.0f;
        init_vars->weight = 1.0f;
        init_vars->scale = 1.0f;
        init_vars->phase = 2;
        init_vars->turn = 1.1344641f;
        init_vars->maximum = 0.52359885f;
        init_vars->epsilon = 0.01f;
        init_vars->rate = 0.013888889f;
        init_vars->radius = 11.0f;
        init_vars->ready = 0;
        init_vars->enabled = 0;
        owner_moby = (char *)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + D_L02_001B359C_1[0]);
        *(unsigned short *)(owner_moby + 0x34) |= 6;
        *(short *)(vars + 0x286) = 60;
        get_moby_color(moby, vars + 0x270, vars + 0x274, vars + 0x278);
        mem_clear(vars + 0x170, 0, 0x40);
        mem_clear(vars + 0x1B0, 0, 0x40);
        brawler_switch_off_actor(moby);
        *(char **)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + g_moby_l02_pool[0] + 0xB8) = moby;
        *(int *)(vars + 0x250) = 0x40FF00EA;
        *(int *)(vars + 0x258) = 0x40FF00EA;
        *(int *)(vars + 0x264) = 0;
        *(short *)(vars + 0x280) = 0;
        *(int *)(vars + 0x254) = 0x40FF00EA;
        *(short *)(vars + 0x282) = 0;
        return;
    }
    hit_info = part_find_owned_effect_slot(moby, 0x10000, 0);
    damage_amount = moby_update_aim_target_strength(moby, hit_info);
    if (hit_info && *(char **)(hit_info + 0x20)) {
        hit_source = *(char **)(hit_info + 0x20);
        if (*(short *)(hit_source + 0xAA) == 0xC89 /* moby class 3209 */ || *(short *)(hit_source + 0xAA) == 0xBFE /* moby class 3070 */)
            damage_amount *= 0.35f;
    }
    if (damage_amount > 0.0f) {
        if (*(unsigned char *)(moby + 0x20) >= 5 && *(unsigned char *)(moby + 0x20) != 10 &&
            *(unsigned char *)(moby + 0x20) != 11) {
            *(float *)(vars + 0x20) -= damage_amount;
            { int at = *(unsigned char *)(vars + 0x37) * 4 + 0xE0; *(int *)((char *)D_L02_001FF6B8 + at) += (int)(damage_amount * 32.0f); }
            if (*(short *)(vars + 0x140) == 0)
                gfx_start_color_fade((int)moby, vars + 0x140);
            if (damage_amount > 3.0f && *(unsigned char *)(moby + 0x20) == 6 && *(unsigned char *)(moby + 0x42) == 7) {
                *(short *)(vars + 0x28A) = *(unsigned char *)(moby + 0x20);
                legs_moby2 = (char *)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + D_L02_001B359C_1[0]);
                *(short *)(vars + 0x28C) =
                    *(unsigned char *)(legs_moby2 + 0x43) != 255 ? *(unsigned char *)(legs_moby2 + 0x43)
                                                               : *(unsigned char *)(legs_moby2 + 0x42);
                *(short *)(vars + 0x28E) = *(unsigned char *)(moby + 0xBC);
                moby_set_state(moby, 9, -1);
                *(float *)(vars + 0x24C) = 0.1939255f;
            }
            if (*(float *)(vars + 0x20) <= 0.0f) {
                *(float *)(vars + 0x24C) = 0.387851f;
                moby_set_state(moby, 10, -1);
            }
        }
    }
    *(unsigned char *)(moby + 0xA8) = 255;
    *(unsigned char *)((*(int *)(*(char **)(moby + 0x68) + 0x244) << 8) + g_moby_l02_pool[0] + 0xA8) = 255;
    legs_moby = (char *)(g_moby_l02_pool[0] + (*(int *)(*(char **)(moby + 0x68) + 0x244) << 8));
    if (legs_moby && *(char **)(*(char **)(moby + 0x68) + 0x260))
        moby_copy_joint_transform_to_object(legs_moby, *(char **)(*(char **)(moby + 0x68) + 0x260), 4, 0);
    *(short *)(vars + 0x284) = weapon_select_aim_target(moby, *(int *)(vars + 0x268), 0, 0, 100.0f, 100.0f);
    body_part = *(char **)(vars + 0x160);
    *(char **)(vars + 0x240) = body_part;
    if (*(unsigned char *)(moby + 0x20) != 3)
        qcopy(vars + 0x230, body_part + 0x10);
    if (*(unsigned char *)(vars + 0x2E) == 2) {
        hit_source = *(char **)(vars + 0x264);
        if (hit_source && *(unsigned char *)(hit_source + 0x20) != 254 && *(unsigned char *)(hit_source + 0x20) != 253 &&
            *(unsigned char *)(hit_source + 0x20) >= 3) {
            chainblade_advance_health_phase(*(char **)(vars + 0x264));
            arena_set_current_boss(*(void **)(moby + 0xB8), *(void **)(vars + 0x264));
        }
        brawler_switch_off_actor(moby);
    }
    walker_boss_update_movement_shake(moby);
    twin_muzzle_turret_update(moby);
}
