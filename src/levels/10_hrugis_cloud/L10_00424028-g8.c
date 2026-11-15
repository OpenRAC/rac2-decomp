#include "common.h"

extern int D_L10_001B1648 __attribute__((sda));

extern u8 D_L10_0042BEE0[];

extern int func_003179F0(void *a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern f32 func_00309B38(f32 f12, f32 f13);
extern void func_00301B98(void *a0, void *a1);

extern void func_00307C68(char *a0, int a1, int a2, int a3, f32 f12, f32 f13, f32 f14);

/* Three func_00307C68(p + 0x10, 11, colour, 1, ...) calls, each colour with a random
   alpha byte; the first alpha also sets +0x1C of this level's D_L10_001C7800 record. */
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
extern int g_mission_completion_counts __attribute__((sda));
extern int D_L10_001B1424 __attribute__((sda));
extern char *D_L10_001B251C;
extern void CreateEnergyStrip(void *, void *, int, int, int, int, int, int, float, float, float, float);
extern int math_fast_float_d(void *);
extern void mission_store_completion_counts(void);
extern int MemcardSave(int, int);
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
extern void hrugis_finish_mission_reward(void *, int);
extern int list_count_ready_objects(void *);
extern void FadeToBlack(int);
extern void hrugis_reset_mission_state(void *);

extern int math_random_int_range(int low, int high);
extern f32 math_random_float_range(f32 low, f32 high);
extern f32 math_random_angle(void);
extern void gfx_draw_billboard_quad(void *at, int kind, unsigned int colour, int count, f32 size,
                          f32 rate, f32 spin);
extern f32 IntToFloat(int);
extern u8 D_L10_001C7800[];

/* First call: resets the D_L10_001B13A4 block, marks every class-0xF85 moby, spawns 75
   objects and the effect box. Then, until the 0xF85 moby reports done, each timer expiry
   either closes the D_L10_001B1444 sequence (with D_L10_001B1390 raised around the
   func_0029B3E0 call, which returns an int) or restarts state 0 through func_L10_00423DC8. */
void mission_first_update(char *object)
{
    char **moby_list;
    int result;
    char *vars = *(char **)(object + 0x68);
    char *target_moby;
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
        moby_list = level_get_object_list();
        result = level_get_saved_value();
        for (i = 0; i < result; i++) {
            if (*(short *)(moby_list[i] + 0xAA) == 0xF85 /* moby class 3973 */) entry_spawn_list_objects_with_flag(moby_list[i], 1);
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(75,16);
        av.q = 0; bv.q = 0;
        av.f[0] = 469.63f; av.f[1] = 407.93f; av.f[2] = 502.79f;
        bv.f[0] = 476.13f; bv.f[1] = 415.41f; bv.f[2] = 502.79f;
        CreateEnergyStrip(&av,&bv,1,2000000,0x7F7F7F,0xFF1010,70,70,0.5f,0.2f,0.402f,1.12225f);
    }
    target_moby = level_find_object_by_class_id(0xF85 /* moby class 3973 */);
    result = target_moby ? group_count_alive(target_moby) : 0;
    if (!result) {
        entry_init_all_registered();
        if (D_L10_001B1444) {
            if (math_fast_float_d(vars + 0x58)) {
                *(int *)(vars + 0x58) = 10;
                g_mission_completion_counts++;
                mission_store_completion_counts();
                MemcardSave(0,-1);
                g_mission_completion_counts--;
                moby_set_flag_bit(D_L10_001B251C + *(int *)(vars + 0x2C) * 256,1);
                D_L10_001B1424 = 0;
                D_L10_001B1444 = 0;
                hero_set_state_value_c(1);
                moby_mark_flag_and_append_to_list(12);
            }
        } else if (math_fast_float_d(vars + 0x58)) {
            hrugis_finish_mission_reward(object,0);
            D_L10_001B13F8 = 0;
            D_L10_001B13FC = 0;
        }
    }
}

/* Mission controller for the second challenge: sets it up on the first frame, then ends the
   round when the first target group is gone or the second group is cleared. */
void mission_second_update(u8 *moby) {
    u8 **moby_list;
    int moby_count;
    int i;
    u8 *current;
    void *target_moby;
    int targets_left;

    if (g_mission_initialized == 0) {
        g_mission_initialized = 1;
        D_L10_00221CD0.f2C = 0;
        music_Unpause();
        entry_init_all_registered();
        hero_set_state_value_a(0);
        moby_list = level_get_object_list();
        moby_count = level_get_saved_value();
        for (i = 0; i < moby_count; i++) {
            current = moby_list[i];
            switch (*(short *)(current + 0xAA)) {
            case 0xCBE /* moby class 3262 */:
                entry_spawn_list_objects_with_flag(current, 1);
                break;
            case 0xF93 /* moby class 3987 */:
                entry_spawn_list_objects_with_flag(current, 1);
                func_L05_0037CEE0(moby_list[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                func_L05_0037D608(moby_list[i], D_001B2614 + D_L10_00221CD0.idx * 128 + 0x30, 64.0f);
                hrugis_set_group_states(moby_list[i]);
                break;
            }
        }
        cloud_destroy_leftover_objects();
        cloud_spawn_objects(0x2D, 12);
    }
    target_moby = level_find_object_by_class_id(0xF93 /* moby class 3987 */);
    targets_left = target_moby ? group_count_alive(target_moby) : 0;
    if (targets_left == 0) {
        hrugis_finish_mission_reward(moby, 1);
    }
    if (list_count_ready_objects(level_find_object_by_class_id(0xCBE /* moby class 3262 */)) == 0) {
        FadeToBlack(0x1E);
        hero_set_state_value_c(0);
        hrugis_reset_mission_state(moby);
    }
}

/* Two-state start-up for a cloud puff: state 0 lays the record at +0x10 out (position
   reset, colour limits, the builder call, its handle in the $gp variable), and states 0
   and 1 both fade the +0xF8 value down; anything else goes straight to the update. */
void cloud_puff_startup_update(u8 *moby) {
    u8 *puff = moby;
    u8 state = *(u8 *)(puff + 0x20);
    f32 zero;

    switch (state) {
    case 0:
        *(int *)(puff + 0x1C) = 0;
        *(u8 *)(puff + 0x20) = 1;
        zero = *(f32 *)(puff + 0x1C);
        *(u16 *)(puff + 0x32) = 0x1FF;
        *(u8 *)(puff + 0x30) = 0xFF;
        *(f32 *)(puff + 0x10) = 512.0f;
        *(f32 *)(puff + 0x14) = 512.0f;
        *(f32 *)(puff + 0x18) = 512.0f;
        D_L10_001B1648 = func_003179F0(puff + 0x10, 40.0f, zero, zero, zero, 1.0f);
    case 1:
        *(f32 *)(puff + 0xF8) =
            func_00309B38(*(f32 *)(puff + 0xF8), 0.00981747824699f);
        break;
    default:
        break;
    }
    func_00301B98(D_L10_0042BEE0, puff);
}

/* The cloud puff's burst: three layers of particles at the object's position, coloured
   0x800000, 0x808080 and 0x804040 under random alphas, then the entry of D_L10_001C7800
   named by D_L10_001B1648 takes half of a value for the first alpha at +0x1C. */
void part_spawn_cloud_puff_burst(u8 *object)
{
    int alpha;
    u8 *entry;

    alpha = math_random_int_range(1, 0x80) << 24;
    object += 0x10;
    gfx_draw_billboard_quad(object, 0xB, (math_random_int_range(0x20, 0x80) << 24) | 0x800000, 1,
                  math_random_float_range(8.0f, 15.0f), 0.01f, math_random_angle());
    gfx_draw_billboard_quad(object, 0xB, alpha | 0x808080, 1, math_random_float_range(4.0f, 12.0f), 0.025f,
                  math_random_angle());
    gfx_draw_billboard_quad(object, 0xB, (math_random_int_range(0, 0x80) << 24) | 0x804040, 1,
                  math_random_float_range(8.0f, 17.0f), 0.05f, math_random_angle());
    entry = D_L10_001C7800 + (D_L10_001B1648 << 5);
    *(f32 *)(entry + 0x1C) = IntToFloat(alpha >> 24) * 0.5f;
}
