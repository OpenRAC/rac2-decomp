#include "include_asm.h"




#include "common.h"
extern u8 g_hero_position_vec[];
extern f32 fast_vec_dist(void *, void *);
extern f32 IntToFloat(int);
extern f32 math_fabs(f32);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
typedef struct {
    u8 pad00[0x20];
    u8 unk_20;
    u8 unk_21;
    u8 pad22[0x24 - 0x22];
    void *unk_24;
    u8 pad28[0x2C - 0x28];
    f32 unk_2C;
    u8 pad30[0x68 - 0x30];
    void *unk_68;
    u8 pad6C[0x95 - 0x6C];
    u8 unk_95;
    u16 unk_96;
    u8 pad98[0xBC - 0x98];
    u8 unk_BC;
    u8 padBD[0x100 - 0xBD];
} Ent;
typedef struct {
    u8  pad00[0x20];
    f32 unk_20;
    void *unk_24;
    u8  pad28[0x2C - 0x28];
    f32 unk_2C;
    u8  pad30[0x50 - 0x30];
    u8  unk_50[0x88 - 0x50];
    u16 unk_88;
    u8  pad8A[0xE4 - 0x8A];
    f32 unk_E4;
    u8  padE8[0x144 - 0xE8];
    s32 unk_144;
    u8  pad148[0x150 - 0x148];
    f32 unk_150[4];
    f32 unk_160;
    f32 unk_164;
    f32 unk_168;
    u8  pad16C[0x189 - 0x16C];
    u8  unk_189;
    u8  pad18A[0x18C - 0x18A];
    u8  unk_18C;
    u8  pad18D[0x1B0 - 0x18D];
    f32 unk_1B0;
    f32 unk_1B4;
    u8  unk_1B8[0x1BA - 0x1B8];
    s16 unk_1BA;
    s16 unk_1BC;
    u16 unk_1BE;
    u8  pad1C0[0x1CC - 0x1C0];
    s32 unk_1CC;
    f32 unk_1D0;
    f32 unk_1D4;
    s32 unk_1D8;
    s32 unk_1DC;
    u8  unk_1E0[0x254 - 0x1E0];
    s32 unk_254;
    u8  pad258[0x40E - 0x258];
    u16 unk_40E;
    u8  pad410[0x440 - 0x410];
    u8  unk_440[0x448 - 0x440];
    s32 unk_448;
    u8  unk_44C[0x484 - 0x44C];
    s32 unk_484;
    s32 unk_488;
    u8  unk_48C[8];
} Moby;
typedef struct {
    f32 unk_0;
    f32 unk_4;
    f32 unk_8;
    f32 unk_C;
} Quad;
typedef struct {
    u8  pad00[0x24];
    f32 unk_24;
} Sub24;
extern s32 func_2F9A60();
extern s32 func_327898(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern void value_set_and_smooth_pal(Ent *, void *, s32, s32, f32);
extern s32 moby_apply_damage_to_object_pal(Ent *, void *, s32);
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern f32 g_ground_height_result;
extern f32 g_hero_height_limit;
extern f32 coll_find_ground_height(Quad *, f32, f32, f32, f32);
extern void vehicle_compute_height_limits(Ent *);
extern void sandfly_release_sounds(Ent *);
extern float math_fabs(float);
extern u8 g_inventory_have_flags[] __attribute__((sda));
extern u8 g_request_l08_queue[];
extern s32 g_cutscene_l08_active_flag[] __attribute__((sda));
extern s32 g_glider_flag_table[] __attribute__((sda));
extern u8 *g_collision_box_table[] __attribute__((sda));
extern s32 IsPointInCuboid(void *, s32);
extern s32 req_push_queue(void *, s32);
extern s32 req_launch_queued(void *);
extern s32 game_is_either_mode_two(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern f32 math_random_angle(void);
extern s32 math_random_int_range(s32, s32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);

/* func_L08_00423010 is in its own unit. */

/* func_L08_004233E0 is defined in L08_004233E0-init.c. */

/* func_L08_004237F0 is matched in its own unit, src/levels/08_tabora/L08_004237F0.c (default flags). */

/* the driver is primed, the entry follows its mount and then its own update runs */
/* Checks the sandfly for hits: when it is hurt a timer starts or it begins to die, and its sounds are stopped (PAL version). */
void sandfly_check_hit_pal(Ent *moby)
{
    Moby *vars = moby->unk_68;
    Sub24 *sub;
    f32 half_size;
    s32 hit_result;

    value_set_and_smooth_pal(moby, vars->unk_1E0, 2, 1, 2.5f);
    vehicle_compute_height_limits(moby);
    sub = moby->unk_24;
    half_size = sub->unk_24 * 0.5f;
    moby->unk_2C = half_size;
    hit_result = moby_apply_damage_to_object_pal(moby, vars->unk_50, 0);
    if (hit_result != 0) {
        if (vars->unk_20 <= 0.0f) {
            vars->unk_88 |= 2;
            vars->unk_E4 = 1.0053098f;
        } else {
            vars->unk_1BE = 275;
        }
        snd_stop_queued(moby);
        sandfly_release_sounds(moby);
    }
}


