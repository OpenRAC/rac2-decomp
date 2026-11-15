#include "include_asm.h"

/* func_PAL_L14_0042E5F8, the PAL copy of func_L14_00428E68: the same C, with the timers at 50 Hz. */
#include "common.h"

#define W(p, o) (*(int *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))

typedef struct {
    char pad[0x80];
    float position[4];
} Hero;

extern int func_PAL_L14_0042ED80(void *);
extern int flag_set_second_pending(void *);
extern int moby_dispatch_action_by_kind(void *, void *);
extern int flag_set_first_pending(void *);
extern int func_PAL_L01_00323068(void *, void *);
extern int coll_point_inside_region(void *, int);
extern int moby_start_effect_from_entry(void *, float);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
/* Integer and FP arguments retain their respective EE register-bank order. */
extern int coll_sweep_from_object(void *, void *, float, float, int, float, int, int, int);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float moby_get_anim_value(void *);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void func_PAL_L14_0042F200(void *);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_PAL_002B5E10(void *);
extern void moby_l14_set_state_value(void *, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void func_PAL_L14_0042F0D8(void *);

extern float D_L14_001B1924 __attribute__((sda));
extern float D_L14_001B1928 __attribute__((sda));
extern float D_L14_001B192C __attribute__((sda));
extern float D_L14_001B1930 __attribute__((sda));
extern int D_L14_001B20C8;
extern u8 g_hero_state[];
extern u8 *g_moby_l14_pool;
extern int D_L14_001B1938[4];
extern char *D_L14_001C39C0[];


void func_PAL_L14_0042E5F8(char *self)
{
    char *s = *(char **)(self + 0x68);
    int r, i;
    float angle, t;
    union {
        int choices[4];
        float pos[4];
    } scratch;

    if (func_PAL_L14_0042ED80(self)) {
        moby_mark_spawned(self);
        return;
    }
    {
        switch (B(self, 0x95)) {
        case 0:
            if (W(s, 0x2F0) == 1 && B(self, 0x20) == 1)
                moby_set_state(self, 5, 1);
            break;
        case 1:
            if (flag_set_second_pending(self))
                moby_set_controller_speed_limits(self,
                    D_L14_001B1924 * 0.00040000002f,
                    D_L14_001B1928 * 0.020000001f,
                    D_L14_001B192C * 6.981318e-06f,
                    D_L14_001B1930 * 0.0003490659f);
            if (W(s, 0x2F0) != 1) {
                moby_set_state(self, 1, 0);
                W(s, 0x30C) = (math_random_int_range(580, 600) * 5 + 2) / 6;
            }
            break;
        case 2:
            r = moby_dispatch_action_by_kind(self, s + 0x140);
            if (r & 1) {
                func_PAL_L14_0042F200(self);
                moby_mark_spawned(self);
                return;
            }
            if (r & 2) {
                if (W(s, 0x2F0) == 1)
                    moby_set_state(self, 5, 1);
                else {
                    moby_set_state(self, 1, 0);
                    W(s, 0x30C) = (math_random_int_range(580, 600) * 5 + 2) / 6;
                }
            }
            break;
        }
    }

    switch (B(self, 0x20)) {
    case 1:
        if (flag_set_first_pending(self) && B(self, 0x43) != 6)
            func_PAL_002A7E68(self, 6, 0, 17);
        if (B(self, 0x60) & 2) {
            __builtin_memcpy(scratch.choices, D_L14_001B1938, 16);
            if (B(self, 0x43) != scratch.choices[math_random_int_below(4)])
                func_PAL_002A7E68(self, scratch.choices[math_random_int_below(4)], 0, 17);
        }
        if (W(s, 0x2B8) != -1)
            func_PAL_002B5E10(self);
        if ((D_L14_001B20C8 & 15) == (((int)self >> 8) & 15)) {
            if (W(s, 0x2B8) == -1)
                break;
            if (W(s, 0x31C) && ((Hero *)g_hero_state)->position[2] + 2.0f < F(self, 0x18) &&
                vec_distance_xy(self + 0x10, (((Hero *)g_hero_state)->position)) < 16.0f) {
                moby_set_state(self, 2, -1);
                break;
            }
            if (!W(s, 0x31C) && F(self, 0x18) < ((Hero *)g_hero_state)->position[2] - 2.0f &&
                vec_distance_xy(self + 0x10, (((Hero *)g_hero_state)->position)) < 8.0f)
                moby_set_state(self, 3, -1);
        } else {
            angle = mat_fast_helper_a(((Hero *)g_hero_state)->position[0] - F(self, 0x10),
                                 ((Hero *)g_hero_state)->position[1] - F(self, 0x14));
            if (FastDiffRots(F(self, 0xF8), angle) > 0.7853982449f)
                moby_set_state(self, 4, -1);
        }
        break;
    case 4:
        if (flag_set_first_pending(self) && B(self, 0x43) != 8)
            func_PAL_002A7E68(self, 8, 0, 17);
        angle = mat_fast_helper_a(((Hero *)g_hero_state)->position[0] - F(self, 0x10),
                             ((Hero *)g_hero_state)->position[1] - F(self, 0x14));
        moby_start_effect_from_entry(self, angle);
        if (FastDiffRots(F(self, 0xF8), angle) < 0.05235988274f)
            moby_set_state(self, 1, -1);
        break;
    case 2:
        if (flag_set_first_pending(self)) {
            if (B(self, 0x43) != 8)
                func_PAL_002A7E68(self, 8, 0, 17);
            moby_l14_set_state_value(g_moby_l14_pool + W(s, 0x2B8) * 256, 0);
        }
        if (func_PAL_L01_00323068(self, g_moby_l14_pool + W(s, 0x2B8) * 256 + 0x10) & 128) {
            moby_l14_set_state_value(g_moby_l14_pool + W(s, 0x2B8) * 256, 1);
            W(s, 0x31C) = 0;
            moby_set_state(self, 1, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) {
            if (B(self, 0x43) != 8)
                func_PAL_002A7E68(self, 8, 0, 17);
            moby_l14_set_state_value(g_moby_l14_pool + W(s, 0x2B8) * 256, 0);
        }
        if (func_PAL_L01_00323068(self, s + 0x2E0) & 128) {
            W(s, 0x31C) = 1;
            moby_set_state(self, 1, -1);
        }
        break;
    case 5:
        if (flag_set_first_pending(self) && B(self, 0x43) != 16)
            func_PAL_002A7E68(self, 16, 7, 6);
        t = moby_get_anim_value(self);
        if (t < 19.0f) {
            angle = mat_fast_helper_a(F(s, 0x210) - F(self, 0x10),
                                 F(s, 0x214) - F(self, 0x14));
            moby_start_effect_from_entry(self, angle);
            W(s, 0x320) = 1;
        } else if (t <= 22.0f && W(s, 0x320)) {
            coll_sweep_from_object(self, *(char **)(s + 0x300) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            coll_sweep_from_object(self, *(char **)(s + 0x304) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            moby_transform_joint_to_world(self, 6, scratch.pos);
            r = coll_sweep_from_object(self, scratch.pos, 0.57f, 2.0f, 1, 2.0f, 0, 1, 0);
            for (i = 0; i < r; i++)
                if (*(short *)(D_L14_001C39C0[i] + 0xAA) == 2404)
                    W(s, 0x320) = 0;
        }
        break;
    case 7:
        if (coll_point_inside_region((((Hero *)g_hero_state)->position), W(s, 0x2BC)))
            moby_set_state(self, 8, -1);
        break;
    case 8:
        if (flag_set_first_pending(self) && B(self, 0x43) != 1)
            func_PAL_002A7E68(self, 1, 0, 2);
        if (B(self, 0x60) & 2)
            moby_set_state(self, 1, 0);
        break;
    }
    func_PAL_L14_0042F0D8(self);
}
