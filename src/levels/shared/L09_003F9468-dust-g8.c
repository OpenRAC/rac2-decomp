#include "common.h"

/* The spawn ranges of the dust puffs, read through $gp. */
extern int D_L09_001B17A8 __attribute__((sda));
extern int D_L09_001B17AC __attribute__((sda));
extern float D_L09_001B17B0 __attribute__((sda));
extern float D_L09_001B17B4 __attribute__((sda));
extern float D_L09_001B17B8 __attribute__((sda));
extern float D_L09_001B17BC __attribute__((sda));
extern float D_L09_001B17C0 __attribute__((sda));
extern float D_L09_001B17C4 __attribute__((sda));
extern float D_L09_001B17C8 __attribute__((sda));
extern float D_L09_001B17CC __attribute__((sda));
extern float D_L09_001B17D0 __attribute__((sda));
extern float D_L09_001B17D4 __attribute__((sda));
extern int D_L09_001B17D8 __attribute__((sda));
extern int D_L09_001B17DC __attribute__((sda));
extern int D_L09_001B17E0 __attribute__((sda));
extern int D_L09_001B17E4 __attribute__((sda));
extern float D_L09_001B17E8 __attribute__((sda));
extern int D_L00_001A8FB4 __attribute__((sda));
extern int g_current_map_index __attribute__((section(".sdata")));
/* Volatile: retail keeps its store out of the branch delay slot. */
extern volatile int D_L09_001B25A8 __attribute__((section(".sdata")));
extern int D_00138324 __attribute__((nosda));
extern char g_sound_state[];
typedef struct {
    char pad0[0x33C];
    u8 *standing;
    char pad340[0x34E - 0x340];
    short busy;
    char pad350[0x22B4 - 0x350];
    u8 help;
} Player10200;

extern Player10200 g_hero_state;
extern u8 D_001395B8[];
extern char D_L09_001BFC00[];

extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void add_vectors(void *, void *, void *);
extern int math_random_int_range(int, int);
extern int FastTweenColor(int, int, float);
extern int func_001163B0(void);
extern void part_spawn_ground_effect(void *, int, float, float, int, int, int, void *, int, float);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern void TryClaimNotice(int, int, int);
extern int req_push_queue(void *, int);
extern void req_launch_queued(void *);
extern void data_set_small_value_and_refresh(int, int);
extern int game_is_either_mode_two(void);

/* Throws one dust puff at a random point around the object, then runs its state: 0 arms it,
   1 keeps its sound slot and, while the player stands on it, shows a message on levels 9 and
   18 and moves on when bit 0x10 of D_00138324 is set and D_L00_001A8FB4 is 4; 2 waits for
   func_00288AA0 on D_L09_001BFC00; 3 and 4 finish it. The frame counter at +0x96 saturates.
   The vector clear is qzero_nc: retail clears through a register address. */
/* Update for the Giant Clank Pad (moby class 3712). It throws dust puffs while it waits and works as a pad you step on. */
void giant_clank_pad_update(u8 *obj)
{
    float pos[4];
    float vel[4];
    float tmp[4];
    int *vars = *(int **)(obj + 0x68);
    float r;
    float spin;
    float size;
    int life;
    int tex;
    int n;
    int dir;
    char *sound_slot;

    r = math_random_float_range(D_L09_001B17B0, D_L09_001B17B4);
    pos[0] = math_fast_sin_or_cos_a(math_random_angle()) * r;
    pos[1] = math_fast_sin_or_cos_b(math_random_angle()) * r;
    pos[2] = 0.0f;
    add_vectors(tmp, pos, obj + 0x10);
    pos[2] -= D_L09_001B17E8;
    qzero_nc(vel);
    vel[2] = math_random_float_range(D_L09_001B17B8, D_L09_001B17BC) * (1.0f / 60.0f);
    life = math_random_int_range(D_L09_001B17A8, D_L09_001B17AC);
    spin = math_random_float_range(D_L09_001B17C8, D_L09_001B17CC);
    size = math_random_float_range(D_L09_001B17D0, D_L09_001B17D4);
    tex = FastTweenColor(D_L09_001B17D8, D_L09_001B17DC, math_random_float_range(0.0f, 1.0f));
    n = math_random_int_range(D_L09_001B17E0, D_L09_001B17E4);
    dir = (func_001163B0() & 1) ? -n : n;
    part_spawn_ground_effect(pos, life, spin, size, tex, 2, dir, vel, 0,
                  -(math_random_float_range(D_L09_001B17C0, D_L09_001B17C4) * (1.0f / 3600.0f)));

    switch (obj[0x20]) {
    case 0:
        moby_set_state(obj, 1, -1);
        vars[2] = -1;
        break;
    case 1:
        sound_slot = g_sound_state + vars[2] * 0x70;
        if (*(u8 **)(sound_slot + 0x88) != obj || *(u8 *)(sound_slot + 0x74) == 0)
            vars[2] = PlayMobySound(0, 4, obj);
        if (g_hero_state.standing != obj || g_hero_state.busy != 0)
            break;
        if (g_hero_state.help == 0) {
            if (g_current_map_index == 9)
                TryClaimNotice(4, 0x27C6, 1);
            else if (g_current_map_index == 18)
                TryClaimNotice(4, 0x27ED, 1);
        } else if (g_hero_state.help == 2) {
            TryClaimNotice(4, 0x27B4, 1);
        }
        if (!(D_00138324 & 0x10) || D_L00_001A8FB4 != 4)
            break;
        if (g_current_map_index == 9 || g_current_map_index == 18)
            moby_set_state(obj, 2, -1);
        else
            moby_set_state(obj, 4, -1);
        break;
    case 2:
        if (g_current_map_index == 9) {
            if (req_push_queue(D_L09_001BFC00, 100)) {
                req_launch_queued(D_L09_001BFC00);
                moby_set_state(obj, 3, -1);
            }
        } else if (g_current_map_index == 18) {
            if (req_push_queue(D_L09_001BFC00, 0x92)) {
                req_launch_queued(D_L09_001BFC00);
                moby_set_state(obj, 3, -1);
            }
        }
        break;
    case 3:
        if (game_is_either_mode_two()) {
            D_L09_001B25A8 = 1;
            break;
        }
    case 4: {
        int lvl;

        D_L09_001B25A8 = 0;
        obj[0x31] = 1;
        lvl = g_current_map_index;
        *(u16 *)(obj + 0x34) &= ~1;
        if (lvl == 9) {
            D_001395B8[0x1D] = 1;
            D_001395B8[0x2D] = 1;
        } else if (lvl == 18) {
            D_001395B8[0x87] = 1;
            D_001395B8[0x9F] = 1;
        }
        data_set_small_value_and_refresh(vars[0], 1);
        break;
    }
    case 5:
    case 6:
        break;
    }
    if (*(u16 *)(obj + 0x96) < 0xFFFF)
        *(u16 *)(obj + 0x96) += 1;
}
