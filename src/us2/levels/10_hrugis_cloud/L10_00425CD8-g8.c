#include "names.h"
/* func_US2_L10_00425CD8 and func_US2_L10_00425F48, the v2.00 copies of func_L10_00424028 and
 * func_L10_00424290: the same C, plus destroying the two path markers func_US2_L10_00426260 may
 * have left behind (as func_US2_L10_00426130 does). func_US2_L10_00425CD8 also drops the
 * D_L10_001B1390 / func_L10_00425888 / func_0029B3E0 block and calls func_002AD7B8 first.
 * Their own unit for -G8. */
#include "common.h"

extern int D_L10_00221CFC __attribute__((section(".data")));
extern int g_mission_initialized __attribute__((sda));
extern void music_Unpause(void);
extern void entry_init_all_registered(void);
extern void hero_set_state_value_a(int);
extern void *level_get_object_list(void);
extern int level_get_saved_value(void);
extern void cloud_destroy_leftover_objects(void);
extern void cloud_spawn_objects(int, int);
extern void hero_set_state_value_c(int);
extern int D_L10_001B13F8 __attribute__((sda));
extern int D_L10_001B13FC __attribute__((sda));
extern int D_L10_001B1444 __attribute__((sda));
extern int D_L10_001B1424 __attribute__((sda));
extern char *D_L10_001B251C;
extern void CreateEnergyStrip(void *, void *, int, int, int, int, int, int, float, float, float, float);
extern int math_fast_float_d(void *);
extern void moby_set_flag_bit(void *, int);
extern void moby_mark_flag_and_append_to_list(int);

typedef struct { int idx; u8 pad[0x28]; int f2C; } G221CD0;
extern G221CD0 D_L10_00221CD0;
extern u8 *D_001B2614;
extern void entry_spawn_list_objects_with_flag(void *, int);
extern void func_L05_0037CEE0(void *, void *, f32);
extern void func_L05_0037D608(void *, void *, f32);
extern void hrugis_set_group_states(void *);
extern void *level_find_object_by_class_id(int);
extern int group_count_alive(void *);
extern void func_US2_L10_00425A78(void *, int);
extern int list_count_ready_objects(void *);
extern void FadeToBlack(int);
extern void hrugis_reset_mission_state(void *);
extern void *D_L10_001B1400 __attribute__((sda)), *D_L10_001B1404 __attribute__((sda));
extern void moby_mark_spawned(void *);

void func_US2_L10_00425CD8(char *object)
{
    char **all;
    int result;
    char *st = *(char **)(object + 0x68);
    char *p;
    int i;
    if (!g_mission_initialized) {
        typedef int Quad __attribute__((mode(TI)));
        union { Quad q; float f[4]; } av, bv;
        D_L10_00221CFC = 0;
        g_mission_initialized = 1;
        D_L10_001B13F8 = 0;
        D_L10_001B13FC = 0;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        all = level_get_object_list();
        result = level_get_saved_value();
        for (i = 0; i < result; i++) {
            if (*(short *)(all[i] + 0xAA) == 0xF85) entry_spawn_list_objects_with_flag(all[i], 1);
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(75,16);
        av.q = 0; bv.q = 0;
        av.f[0] = 469.63f; av.f[1] = 407.93f; av.f[2] = 502.79f;
        bv.f[0] = 476.13f; bv.f[1] = 415.41f; bv.f[2] = 502.79f;
        CreateEnergyStrip(&av,&bv,1,2000000,0x7F7F7F,0xFF1010,70,70,0.5f,0.2f,0.402f,1.12225f);
        if (D_L10_001B1400) {
            moby_mark_spawned(D_L10_001B1400);
            D_L10_001B1400 = 0;
        }
        if (D_L10_001B1404) {
            moby_mark_spawned(D_L10_001B1404);
            D_L10_001B1404 = 0;
        }
    }
    p = level_find_object_by_class_id(0xF85);
    result = p ? group_count_alive(p) : 0;
    if (!result) {
        entry_init_all_registered();
        if (D_L10_001B1444) {
            if (math_fast_float_d(st + 0x58)) {
                *(int *)(st + 0x58) = 10;
                moby_mark_flag_and_append_to_list(12);
                moby_set_flag_bit(D_L10_001B251C + *(int *)(st + 0x2C) * 256,1);
                D_L10_001B1424 = 0;
                D_L10_001B1444 = 0;
                hero_set_state_value_c(1);
            }
        } else if (math_fast_float_d(st + 0x58)) {
            func_US2_L10_00425A78(object,0);
            D_L10_001B13F8 = 0;
            D_L10_001B13FC = 0;
        }
    }
}

void func_US2_L10_00425F48(u8 *a0) {
    u8 **p;
    int n;
    int i;
    u8 *o;
    void *v;
    int r;

    if (g_mission_initialized == 0) {
        g_mission_initialized = 1;
        D_L10_00221CD0.f2C = 0;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        p = level_get_object_list();
        n = level_get_saved_value();
        for (i = 0; i < n; i++) {
            o = p[i];
            switch (*(short *)(o + 0xAA)) {
            case 0xCBE:
                entry_spawn_list_objects_with_flag(o, 1);
                break;
            case 0xF93:
                entry_spawn_list_objects_with_flag(o, 1);
                func_L05_0037CEE0(p[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                func_L05_0037D608(p[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                hrugis_set_group_states(p[i]);
                break;
            }
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(0x2D, 12);
        if (D_L10_001B1400) {
            moby_mark_spawned(D_L10_001B1400);
            D_L10_001B1400 = 0;
        }
        if (D_L10_001B1404) {
            moby_mark_spawned(D_L10_001B1404);
            D_L10_001B1404 = 0;
        }
    }
    v = level_find_object_by_class_id(0xF93);
    r = v ? group_count_alive(v) : 0;
    if (r == 0) {
        func_US2_L10_00425A78(a0, 1);
    }
    if (list_count_ready_objects(level_find_object_by_class_id(0xCBE)) == 0) {
        FadeToBlack(0x1E);
        hero_set_state_value_c(0);
        hrugis_reset_mission_state(a0);
    }
}
