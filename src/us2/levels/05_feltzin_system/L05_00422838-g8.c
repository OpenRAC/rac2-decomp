#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern int D_L05_001B1364 __attribute__((sda));
extern int D_L05_001B13F4 __attribute__((sda));
extern int D_L05_001B13D8 __attribute__((sda));
extern int D_L05_00221D10[];
extern int D_L05_001B2048;
extern char *D_L05_001B251C;
extern char D_L05_001B1380[] SDATA(D_L05_001B1380);
extern char D_L05_001B1370[] SDATA(D_L05_001B1370);
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern char **level_get_object_list(void);
extern int level_get_saved_value(void);
extern void entry_spawn_list_objects_with_flag(char *, int);
extern void func_L05_0037CEE0(char *, void *, float);
extern void func_L05_0037D608(char *, void *, float);
extern int math_fast_float_d(void *);
extern void ship_start_transition(void *, void *, int);
extern void ship_point_camera_at_target(void *, void *);
extern void moby_set_flag_bit(char *, int);
extern void hero_set_state_value_c(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void func_US2_L05_00422530(char *, int);

/* func_US2_L05_00422838, the v2.00 copy of func_L05_00420A88: the same C, where the timer arm calls
   func_002AD7B8(6) first, not last, and no longer runs func_L05_004222D8 and func_0029B3E0 under
   the D_L05_001B1350 count. */
void func_US2_L05_00422838(char *actor)
{
    Vector a;
    Vector b;
    Vector c;
    char *state = *(char **)(actor + 0x68);
    char **item;
    int count;
    int count2;

    if (D_L05_001B1364 == 0) {
        D_L05_00221D10[11] = 0;
        D_L05_001B1364 = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        item = level_get_object_list();
        count = level_get_saved_value();
        a.q = 0;
        a.f[0] = 487.0f;
        a.f[1] = 526.0f;
        a.f[2] = 531.0f;
        if (count > 0) {
            int n = count;
            do {
                switch (*(short *)(*item + 0xAA)) {
                case 0x957:
                case 0x97C:
                case 0xF76:
                    entry_spawn_list_objects_with_flag(*item, 1);
                    func_L05_0037CEE0(*item, &a, 64.0f);
                    func_L05_0037D608(*item, &a, 64.0f);
                    break;
                }
                item++;
            } while (--n != 0);
        }
    }
    if (D_L05_00221D10[4] != 0 || D_L05_001B2048 < 6)
        return;
    if (D_L05_00221D10[5] <= 0) {
        if (math_fast_float_d(state + 0x58) == 0)
            return;
        *(int *)(state + 0x58) = 120;
        ship_start_transition(D_L05_001B1380, D_L05_001B1370, 200);
        a.q = 0;
        b.q = 0;
        c.q = 0;
        actor[0x20] = 3;
        a.f[0] = 593.5f;
        a.f[1] = 599.0f;
        a.f[2] = 566.0f;
        b.f[0] = 512.5f;
        b.f[1] = 530.0f;
        b.f[2] = 540.0f;
        c.f[0] = 438.0f;
        c.f[1] = 487.0f;
        c.f[2] = 535.0f;
        ship_point_camera_at_target(&a, &c);
        item = level_get_object_list();
        count2 = level_get_saved_value();
        if (count2 > 0) {
            int n = count2;
            do {
                switch (*(short *)(*item + 0xAA)) {
                case 0x957:
                case 0x97C:
                case 0xF76:
                    entry_spawn_list_objects_with_flag(*item, 1);
                    func_L05_0037CEE0(*item, &a, 10.0f);
                    func_L05_0037D608(*item, &b, 20.0f);
                    break;
                }
                item++;
            } while (--n != 0);
        }
    } else if (D_L05_001B13F4 != 0) {
        if (math_fast_float_d(state + 0x58) != 0) {
            *(int *)(state + 0x58) = 25;
            moby_mark_flag_and_append_to_list(6);
            moby_set_flag_bit(D_L05_001B251C + (*(int *)(state + 0x2C) << 8), 1);
            D_L05_001B13D8 = 0;
            D_L05_001B13F4 = 0;
            hero_set_state_value_c(1);
        }
    } else if (math_fast_float_d(state + 0x58) != 0) {
        func_US2_L05_00422530(actor, 0);
    }
}
