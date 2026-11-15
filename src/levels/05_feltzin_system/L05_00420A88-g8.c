#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern int D_L05_001B1364 __attribute__((sda));
extern int D_L05_001B13F4 __attribute__((sda));
extern int D_L05_001B13D8 __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
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
extern void feltzin_mission_clamp_save_counts(void);
extern int MemcardSave(int, int);
extern void moby_set_flag_bit(char *, int);
extern void hero_set_state_value_c(int);
extern void moby_mark_flag_and_append_to_list(int);
extern void UpdateFeltzinMissionReward(char *, int);

/* Controls the first Feltzin mission: on the first frame it sets up the scene and points the
   nearby objects at a target, later it moves the camera and hands over to the reward code. */
void feltzin_mission_one_update(char *actor)
{
    Vector a;
    Vector b;
    Vector c;
    char *state = *(char **)(actor + 0x68);
    char **objects;
    int count;
    int secondCount;

    if (D_L05_001B1364 == 0) {
        D_L05_00221D10[11] = 0;
        D_L05_001B1364 = 1;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        objects = level_get_object_list();
        count = level_get_saved_value();
        a.q = 0;
        a.f[0] = 487.0f;
        a.f[1] = 526.0f;
        a.f[2] = 531.0f;
        if (count > 0) {
            int remaining = count;
            do {
                switch (*(short *)(*objects + 0xAA)) {
                case 0x957 /* moby class 2391 */:
                case 0x97C /* moby class 2428 */:
                case 0xF76 /* moby class 3958 */:
                    entry_spawn_list_objects_with_flag(*objects, 1);
                    func_L05_0037CEE0(*objects, &a, 64.0f);
                    func_L05_0037D608(*objects, &a, 64.0f);
                    break;
                }
                objects++;
            } while (--remaining != 0);
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
        objects = level_get_object_list();
        secondCount = level_get_saved_value();
        if (secondCount > 0) {
            int remaining = secondCount;
            do {
                switch (*(short *)(*objects + 0xAA)) {
                case 0x957 /* moby class 2391 */:
                case 0x97C /* moby class 2428 */:
                case 0xF76 /* moby class 3958 */:
                    entry_spawn_list_objects_with_flag(*objects, 1);
                    func_L05_0037CEE0(*objects, &a, 10.0f);
                    func_L05_0037D608(*objects, &b, 20.0f);
                    break;
                }
                objects++;
            } while (--remaining != 0);
        }
    } else if (D_L05_001B13F4 != 0) {
        if (math_fast_float_d(state + 0x58) != 0) {
            *(int *)(state + 0x58) = 25;
            D_L05_001B1350++;
            feltzin_mission_clamp_save_counts();
            MemcardSave(0, -1);
            D_L05_001B1350--;
            moby_set_flag_bit(D_L05_001B251C + (*(int *)(state + 0x2C) << 8), 1);
            D_L05_001B13D8 = 0;
            D_L05_001B13F4 = 0;
            hero_set_state_value_c(1);
            moby_mark_flag_and_append_to_list(6);
        }
    } else if (math_fast_float_d(state + 0x58) != 0) {
        UpdateFeltzinMissionReward(actor, 0);
    }
}
