#include "names.h"
/* func_PAL_L02_003DD308, the PAL copy of func_L02_003D91A0: the same C, where rename func_002A96A0 becomes func_PAL_002AA108; rename func_002AB800 becomes func_PAL_002AC290; rename func_L02_003D9728 becomes func_PAL_L02_003DD890; rename func_L02_003D9E68 becomes func_PAL_L02_003DDFD0. */
#include "common.h"

extern int g_moby_l02_pool[] __attribute__((sda));
/* Read-only view: these loads may pass the state stores, as in retail. */
extern const int D_L02_001B359C_1[] __attribute__((sda));
extern int g_boss_damage_totals[];
extern int FloatToInt(float);
extern void get_moby_color(char *, void *, void *, void *);
extern void mem_clear(void *, int, int);
extern void brawler_switch_off_actor(char *);
extern void *part_find_owned_effect_slot(char *, int, int);
extern float moby_update_aim_target_strength_pal(char *, void *);
extern void gfx_start_color_fade_pal(int, char *);
extern void moby_set_state(char *, int, int);
extern void moby_copy_joint_transform_to_object(char *, char *, int, int);
extern int weapon_select_aim_target(char *, int, int, int, float, float);
extern void chainblade_advance_health_phase(char *);
extern void arena_set_current_boss(void *, void *);
extern void walker_boss_update_movement_shake_pal(char *);
extern void twin_muzzle_turret_update_pal(char *);

/* Field-at-use prefix only; the full state allocation is not inferred. */
struct InitPrefix {
    u8 reserved00[0x28]; u8 mode, ready; u8 reserved2A[6];
    float radius; u8 reserved34[0x14]; u8 flag; u8 reserved49; u8 limit;
    u8 reserved4B[5]; int enabled; float gain, weight, scale, turn;
    u8 reserved64[0x18]; float rate, maximum, epsilon; int phase;
    u8 reserved8C[0x98]; float blend; u8 reserved128[0x11]; u8 active;
};

/* Sets up a Maktar walker boss on its first frame, then handles damage taken, its health, and hit reactions every frame. */
void walker_boss_update_damage_pal(char *self) {
    char *state = *(char **)(self + 0x68);
    char *entry;
    char *part;
    char *owner;
    char *attacker;
    char *damage;
    char *source;
    float amount;
    if (*(unsigned char *)(self + 0x20) == 0) {
        struct InitPrefix *initial = (struct InitPrefix *)state;
        initial->flag = FloatToInt(15.0f);
        initial->limit = FloatToInt(24.0f);
        initial->active = 1;
        initial->mode = 3;
        initial->blend = 0.5f;
        initial->gain = 1.0f;
        initial->weight = 1.0f;
        initial->scale = 1.0f;
        initial->phase = 2;
        initial->turn = 1.1344641f;
        initial->maximum = 0.52359885f;
        initial->epsilon = 0.01f;
        initial->rate = 0.020000001f;
        initial->radius = 11.0f;
        initial->ready = 0;
        initial->enabled = 0;
        entry = (char *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + D_L02_001B359C_1[0]);
        *(unsigned short *)(entry + 0x34) |= 6;
        *(short *)(state + 0x286) = 50;
        get_moby_color(self, state + 0x270, state + 0x274, state + 0x278);
        mem_clear(state + 0x170, 0, 0x40);
        mem_clear(state + 0x1B0, 0, 0x40);
        brawler_switch_off_actor(self);
        *(char **)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + g_moby_l02_pool[0] + 0xB8) = self;
        *(int *)(state + 0x250) = 0x40FF00EA;
        *(int *)(state + 0x258) = 0x40FF00EA;
        *(int *)(state + 0x264) = 0;
        *(short *)(state + 0x280) = 0;
        *(int *)(state + 0x254) = 0x40FF00EA;
        *(short *)(state + 0x282) = 0;
        return;
    }
    damage = part_find_owned_effect_slot(self, 0x10000, 0);
    amount = moby_update_aim_target_strength_pal(self, damage);
    if (damage && *(char **)(damage + 0x20)) {
        source = *(char **)(damage + 0x20);
        if (*(short *)(source + 0xAA) == 0xC89 || *(short *)(source + 0xAA) == 0xBFE)
            amount *= 0.35f;
    }
    if (amount > 0.0f) {
        if (*(unsigned char *)(self + 0x20) >= 5 && *(unsigned char *)(self + 0x20) != 10 &&
            *(unsigned char *)(self + 0x20) != 11) {
            *(float *)(state + 0x20) -= amount;
            { int at = *(unsigned char *)(state + 0x37) * 4 + 0xE0; *(int *)((char *)g_boss_damage_totals + at) += (int)(amount * 32.0f); }
            if (*(short *)(state + 0x140) == 0)
                gfx_start_color_fade_pal((int)self, state + 0x140);
            if (amount > 3.0f && *(unsigned char *)(self + 0x20) == 6 && *(unsigned char *)(self + 0x42) == 7) {
                *(short *)(state + 0x28A) = *(unsigned char *)(self + 0x20);
                attacker = (char *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + D_L02_001B359C_1[0]);
                *(short *)(state + 0x28C) =
                    *(unsigned char *)(attacker + 0x43) != 255 ? *(unsigned char *)(attacker + 0x43)
                                                               : *(unsigned char *)(attacker + 0x42);
                *(short *)(state + 0x28E) = *(unsigned char *)(self + 0xBC);
                moby_set_state(self, 9, -1);
                *(float *)(state + 0x24C) = 0.27925274f;
            }
            if (*(float *)(state + 0x20) <= 0.0f) {
                *(float *)(state + 0x24C) = 0.5585055f;
                moby_set_state(self, 10, -1);
            }
        }
    }
    *(unsigned char *)(self + 0xA8) = 255;
    *(unsigned char *)((*(int *)(*(char **)(self + 0x68) + 0x244) << 8) + g_moby_l02_pool[0] + 0xA8) = 255;
    owner = (char *)(g_moby_l02_pool[0] + (*(int *)(*(char **)(self + 0x68) + 0x244) << 8));
    if (owner && *(char **)(*(char **)(self + 0x68) + 0x260))
        moby_copy_joint_transform_to_object(owner, *(char **)(*(char **)(self + 0x68) + 0x260), 4, 0);
    *(short *)(state + 0x284) = weapon_select_aim_target(self, *(int *)(state + 0x268), 0, 0, 100.0f, 100.0f);
    part = *(char **)(state + 0x160);
    *(char **)(state + 0x240) = part;
    if (*(unsigned char *)(self + 0x20) != 3)
        qcopy(state + 0x230, part + 0x10);
    if (*(unsigned char *)(state + 0x2E) == 2) {
        source = *(char **)(state + 0x264);
        if (source && *(unsigned char *)(source + 0x20) != 254 && *(unsigned char *)(source + 0x20) != 253 &&
            *(unsigned char *)(source + 0x20) >= 3) {
            chainblade_advance_health_phase(*(char **)(state + 0x264));
            arena_set_current_boss(*(void **)(self + 0xB8), *(void **)(state + 0x264));
        }
        brawler_switch_off_actor(self);
    }
    walker_boss_update_movement_shake_pal(self);
    twin_muzzle_turret_update_pal(self);
}
