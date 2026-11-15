#include "names.h"
/* func_US2_L05_0042DB38, the USA v2.00 copy of func_L05_0042BDB0: the same C, where rename func_002B0A18 becomes func_US2_002B1880. */
#include "common.h"
extern int g_current_map_index MACRO_ADDR;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern u8 D_0019B278[];
extern float D_L05_001B1738 __attribute__((sda));
extern float D_L05_001B173C __attribute__((sda));
extern float D_L05_001B1740 __attribute__((sda));
extern float D_L05_001B1748 __attribute__((sda));
extern float D_L05_001B174C __attribute__((sda));
extern float D_L05_001B1750 __attribute__((sda));
extern float D_L05_001B1754 __attribute__((sda));
extern int D_L05_001B1778 __attribute__((sda));
extern int D_L05_001B177C __attribute__((sda));
extern u8 *D_L05_001B1780 __attribute__((sda));
extern int D_L05_001B2170 __attribute__((sda));
extern int D_L05_001B1F68 __attribute__((sda));
extern int D_L05_001B2264[] __attribute__((sda));
extern u8 g_hero_position[];
extern u8 g_hero_state[];
extern float math_random_angle(void);
extern void moby_init_randomized_vars(void *);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern void part_draw_bolt_glow_rings(void *);
extern int math_random_int_below(int);
extern void part_spawn_sparkle_drift(void *);
extern float fast_vec_dist(void *, void *);
extern void func_US2_002B1880(int, int);
extern int MemcardSave(int, int);
extern int PlayMobySound(int, int, void *);
extern void moby_mark_spawned(void *);
extern void cam_blend_moby_update(void *);
extern void bobbing_l01_moby_update(void *);
extern void anim_start_blended(void *, int, int, int);
extern void set_hero_animation(int, int, float);
extern int math_fast_float_d(void *);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void cam_set_mode_state(int);

typedef union { float f[0x40]; int i[0x40]; s16 h[0x80]; u16 uh[0x80]; } Fields;

void func_US2_L05_0042DB38(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    int i;
    u8 *hero;
    switch (actor[0x20]) {
    case 0:
        if (((Fields *)state)->i[0] == -1 || D_0019B278[((Fields *)state)->i[0] + (D_001A79F0_gp << 2)] != 0) {
            moby_mark_spawned(actor);
            return;
        }
        qcopy(state + 0x10, actor + 0x10);
        ((Fields *)state)->f[0x1C / 4] = ((Fields *)actor)->f[0xF8 / 4];
        ((Fields *)actor)->f[0xF0 / 4] = math_random_angle();
        ((Fields *)actor)->f[0xF4 / 4] = math_random_angle();
        ((Fields *)actor)->f[0xF8 / 4] = math_random_angle();
        ((Fields *)actor)->f[0xFC / 4] = math_random_angle();
        ((Fields *)state)->f[0x68 / 4] = D_L05_001B1748 * 0.00029088825f;
        ((Fields *)state)->f[0x64 / 4] = D_L05_001B174C * 0.00029088825f;
        ((Fields *)state)->f[0x60 / 4] = D_L05_001B1750 * 0.00029088825f;
        if (((Fields *)actor)->h[0x32 / 2] < 64)
            ((Fields *)actor)->h[0x32 / 2] = 64;
        actor[0x20] = 1;
        moby_init_randomized_vars(actor);
        return;
    case 1:
        ((Fields *)actor)->f[0x2C / 4] = *(float *)(*(char **)(actor + 0x24) + 0x24) * D_L05_001B1738;
        ((Fields *)actor)->f[0x18 / 4] = ((Fields *)state)->f[0x18 / 4] + D_L05_001B173C +
                                  D_L05_001B1740 * math_fast_sin_or_cos_b(((Fields *)actor)->f[0xFC / 4]);
        ((Fields *)actor)->f[0xF0 / 4] = FastAddRotations(((Fields *)actor)->f[0xF0 / 4], D_L05_001B1748 * 0.00029088825f);
        ((Fields *)actor)->f[0xF4 / 4] = FastAddRotations(((Fields *)actor)->f[0xF4 / 4], D_L05_001B174C * 0.00029088825f);
        ((Fields *)actor)->f[0xF8 / 4] = FastAddRotations(((Fields *)actor)->f[0xF8 / 4], D_L05_001B1750 * 0.00029088825f);
        ((Fields *)actor)->f[0xFC / 4] = FastAddRotations(((Fields *)actor)->f[0xFC / 4], D_L05_001B1754 * 0.00029088825f);
        part_draw_bolt_glow_rings(actor);
        if (math_random_int_below(D_L05_001B1778) == 0)
            part_spawn_sparkle_drift(actor);
        if (fast_vec_dist(D_L05_001B1780 + 0x10, actor + 0x10) < 1.5f) {
            D_L05_001B2170 = 180;
            func_US2_002B1880(0x124B, -1);
            D_0019B278[((Fields *)state)->i[0] + (g_current_map_index << 2)] = 1;
            D_L05_001B177C++;
            MemcardSave(0, -1);
            PlayMobySound(1, 0, actor);
            moby_mark_spawned(actor);
        }
        return;
    case 2:
        D_L05_001B2264[1] = 1;
        cam_blend_moby_update(actor);
        qcopy(actor + 0x10, g_hero_position);
        qcopy(actor + 0xF0, g_hero_position + 0x10);
        if (actor[0x42] == 1) {
            bobbing_l01_moby_update(actor);
            if (math_random_int_below(10) == 0)
                part_spawn_sparkle_drift(actor);
            if (actor[0x60] & 2) {
                if (actor[0x43] != 0)
                    anim_start_blended(actor, 0, 0, 0);
                actor[0x31] = 0;
                ((Fields *)actor)->uh[0x34 / 2] |= 1;
                for (i = 3; i >= 0; i--)
                    part_spawn_sparkle_drift(actor);
            }
        }
        hero = g_hero_state;
        if (*(int *)(hero + 0xC28) & 2)
            set_hero_animation(0, 0, 30.0f);
        if (actor[0x42] == 0 && math_fast_float_d(state + 0x6C) != 0) {
            D_L05_001B2170 = 180;
            func_US2_002B1880(0x1234, -1);
            D_0019B278[((Fields *)state)->i[0] + (g_current_map_index << 2)] = 1;
            D_L05_001B177C++;
            D_L05_001B1F68 = 0;
            hero_reset_position_and_direction(hero + 0x80, hero + 0x90, 0, 0);
            cam_set_mode_state(0);
            MemcardSave(0, -1);
            moby_mark_spawned(actor);
        }
        break;
    }
}
