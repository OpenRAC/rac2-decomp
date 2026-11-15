#include "common.h"

/* func_L23_003BF9B0 is a unit of its own: it reads $gp (hence -g8), and it is built with -g,
   whose line labels make the assembler pad its two divisions with two nops each, as retail
   has them (the same effect as func_002B5EF8). Each division stays on a line of its own.
   The structs are partial layouts measured from this function. The accesses must be struct
   members: this cc1 lets a scalar global's load pass a store to a struct member at a
   varying address, and with pointer casts instead the global loads stay behind the stores. */

typedef struct MobyClass_003BF9B0 {
    u8 pad000[0x24];
    f32 scale; /* 0x024 */
} MobyClass_003BF9B0;

typedef struct Moby_003BF9B0 {
    u8 pad000[0x10];
    f32 pos[4]; /* 0x010 */
    u8 state; /* 0x020 */
    u8 pad021[0x3];
    MobyClass_003BF9B0 *pClass; /* 0x024 */
    u8 pad028[0x4];
    f32 scale; /* 0x02C */
    u8 f30; /* 0x030 */
    u8 f31; /* 0x031 */
    u16 f32; /* 0x032 */
    u16 flags; /* 0x034 */
    u8 pad036[0x2];
    u64 f38; /* 0x038 */
    u8 pad040[0x28];
    struct State_003BF9B0 *pVars; /* 0x068 */
    u8 pad06C[0x3];
    u8 f6F; /* 0x06F */
    u8 pad070[0x8];
    s32 f78; /* 0x078 */
    u8 pad07C[0x44];
    u8 fC0[0x10]; /* 0x0C0 */
} Moby_003BF9B0;

typedef struct State_003BF9B0 {
    u8 pad000[0x20];
    f32 f20; /* 0x020 */
    s16 f24; /* 0x024 */
    s16 f26; /* 0x026 */
    s8 f28; /* 0x028 */
    u8 pad029[0x1F];
    s8 f48; /* 0x048 */
    u8 pad049[0x1];
    s8 f4A; /* 0x04A */
    u8 pad04B[0x5];
    f32 f50; /* 0x050 */
    f32 f54; /* 0x054 */
    f32 f58; /* 0x058 */
    f32 f5C; /* 0x05C */
    f32 f60; /* 0x060 */
    u8 pad064[0xC];
    f32 f70; /* 0x070 */
    f32 f74; /* 0x074 */
    f32 f78; /* 0x078 */
    u8 pad07C[0x4];
    f32 f80; /* 0x080 */
    f32 f84; /* 0x084 */
    u32 f88; /* 0x088 */
    u8 pad08C[0xAC];
    s8 f138; /* 0x138 */
    s8 f139; /* 0x139 */
    u8 pad13A[0x6];
    u8 f140[0x10]; /* 0x140 */
    s8 f150; /* 0x150 */
    s8 f151; /* 0x151 */
    s8 f152; /* 0x152 */
    u8 pad153[0x3];
    s8 f156; /* 0x156 */
    s8 f157; /* 0x157 */
    u8 pad158[0x4];
    f32 f15C; /* 0x15C */
    f32 f160; /* 0x160 */
    f32 f164; /* 0x164 */
    f32 f168; /* 0x168 */
    f32 f16C; /* 0x16C */
    f32 f170; /* 0x170 */
    f32 f174; /* 0x174 */
    s16 f178; /* 0x178 */
    u8 pad17A[0x2];
    f32 f17C; /* 0x17C */
    u8 pad180[0x8];
    s32 f188; /* 0x188 */
    u8 pad18C[0xC];
    f32 f198; /* 0x198 */
    f32 f19C; /* 0x19C */
    u8 pad1A0[0xC];
    s8 f1AC; /* 0x1AC */
    s8 f1AD; /* 0x1AD */
    s8 f1AE; /* 0x1AE */
    s8 f1AF; /* 0x1AF */
    u8 pad1B0[0x2];
    s8 f1B2; /* 0x1B2 */
    s8 f1B3; /* 0x1B3 */
    u8 pad1B4[0x3];
    s8 f1B7; /* 0x1B7 */
    u8 pad1B8[0xA0];
    s32 f258; /* 0x258 */
    u8 pad25C[0x10];
    s16 f26C; /* 0x26C */
    s16 f26E; /* 0x26E */
    u8 pad270[0x10];
    u8 f280[0x20]; /* 0x280 */
    struct Moby_003BF9B0 *child; /* 0x2A0 */
    u8 pad2A4[0x2];
    s16 f2A6; /* 0x2A6 */
    f32 f2A8; /* 0x2A8 */
    u8 pad2AC[0x7C];
    s32 f328; /* 0x328 */
    s32 f32C; /* 0x32C */
    u8 pad330[0x84];
    s32 f3B4; /* 0x3B4 */
    u8 pad3B8[0x6];
    s16 f3BE; /* 0x3BE */
} State_003BF9B0;

typedef struct {
    u8 pad000[0xAA];
    s16 fAA; /* 0x0AA */
} Info_003BF9B0;

typedef struct {
    u8 pad000[0x20];
    Info_003BF9B0 *info; /* 0x020 */
} Found_003BF9B0;

extern f32 D_L23_001AFA58 __attribute__((sda));

extern s32 D_L23_001B1424 __attribute__((sda));

extern s32 ref_L23_003BF9B0_00;

extern s32 D_L23_001B1650 __attribute__((sda));

extern s32 D_L23_001B36AC;

extern s32 D_L23_001B36F0;

extern u8 g_camera_l23_position[];

extern Moby_003BF9B0 *CreateMoby(s32);

extern void set_identity_rotation_rows(void *);

extern void moby_reset_idle_clear_links(Moby_003BF9B0 *);

extern s32 FloatToInt(f32);

extern void enemy_relocate_near_hero(Moby_003BF9B0 *);

extern void moby_set_controller_speed_limits(Moby_003BF9B0 *, f32, f32, f32, f32);

extern f32 fast_vec_dist(void *, void *);

extern void moby_update_ground_check(Moby_003BF9B0 *);

extern Found_003BF9B0 *part_find_owned_effect_slot(Moby_003BF9B0 *, s32, s32);

extern void moby_apply_damage_to_object(Moby_003BF9B0 *, void *, s32);

extern void cam_compute_view_direction(void *, void *, s32);

extern void vec_negate_and_forward(void *, void *, s32);

/* Sets up this flying enemy on its first frame (stats, speeds, a helper object), then each frame scales it, keeps its helper object in step and checks if it should die near the boss spot. */
void flying_enemy_init_and_update(Moby_003BF9B0 *moby)
{
    State_003BF9B0 *vars = moby->pVars;
    f32 sizeFactor;

    if (moby->state == 0) {
        f32 fps;

        vars->f2A8 = D_L23_001AFA58;
        vars->f3B4 = -1;
        vars->f3BE = 0;
        vars->f26C = 0;
        vars->f26E = 0;
        vars->f32C = 0;
        vars->f328 = 0;
        vars->f2A6 = 0;
        moby->flags |= 0x100;
        vars->f1B7 = 1;
        vars->f150 = 12;
        vars->f151 = 8;
        vars->f152 = 8;
        vars->f156 = 8;
        vars->f157 = 8;
        vars->f1AC = -1;
        vars->f1AD = -1;
        vars->f1AE = -1;
        vars->f1AF = -1;
        vars->f1B2 = -1;
        vars->f1B3 = -1;
        fps = D_L23_001B36F0;
        vars->f15C = 0.5833334f;
        vars->f188 = 3;
        vars->f174 = 4.0f;
        vars->f160 = 0.06666667f;
        vars->f164 = 0.041666668f;
        vars->f168 = 0.083333336f;
        vars->f16C = 0.016666668f;
        vars->f170 = 3.0f;
        vars->f17C = 0.4f;
        vars->f19C = 150.0f / fps;
        vars->f138 = 5;
        vars->f139 = 6;
        vars->f198 = 40.0f / fps;
        vars->f84 = 4.0f;
        vars->f70 = 0.0044444446f;
        vars->f74 = 0.0044444446f;
        vars->f78 = 0.20000002f;
        vars->f50 = 2.5f;
        vars->f54 = 0.75f;
        vars->f60 = 2.0f;
        vars->f58 = 2.75f;
        vars->f5C = 2.75f;
        vars->f80 = 0.78539824f;
        vars->f20 = D_L23_001B36F0;
        vars->f24 = D_L23_001B36F0;
        vars->f28 = 3;
        vars->f26 = 60;
        vars->f88 |= 0x81;
        moby->f32 = 0xFF;
        moby->f30 = 0xFF;
        vars->child = CreateMoby(0x7E6 /* moby class 2022 */);
        set_identity_rotation_rows(vars->child->fC0);
        vars->f258 = 0;
        moby_reset_idle_clear_links(moby);
        vars->f48 = FloatToInt(12.0f);
        vars->f4A = FloatToInt(14.4f);
    } else if (ref_L23_003BF9B0_00 != 0 && D_L23_001B1424 == 0) {
        if (D_L23_001B36AC < 10)
            enemy_relocate_near_hero(moby);
        else
            D_L23_001B1650 = 0;
    }
    if (moby->state == 13)
        return;
    moby_set_controller_speed_limits(moby, 0.0044444446f, 0.13333334f, 0.0017453295f, 0.20943955f);
    sizeFactor = 1.4f;
    if (moby->state == 2)
        sizeFactor = 0.7f;
    moby->scale = moby->pClass->scale * sizeFactor;
    if (vars->child != 0) {
        vars->child->f32 = moby->f32;
        vars->child->f30 = moby->f30;
        vars->child->f38 = moby->f38;
        vars->child->f78 = moby->f78;
        vars->child->f31 = 1;
        vars->child->scale = vars->child->pClass->scale * sizeFactor;
        if (vars->child->f31 != 0 && fast_vec_dist(vars->child->pos, g_camera_l23_position) < 24.0f) {
            moby_update_ground_check(vars->child);
            vars->child->f6F = 22;
        }
    }
    if (moby->f31 != 0 && fast_vec_dist(moby->pos, g_camera_l23_position) < 24.0f) {
        moby_update_ground_check(moby);
        moby->f6F = 22;
    }
    {
        Found_003BF9B0 *found = part_find_owned_effect_slot(moby, 0x30000, 1);

        if (found != 0 && found->info != 0 && found->info->fAA == 0x1190 /* moby class 4496 */)
            vars->f20 = 0;
    }
    if (moby->state == 2)
        vars->f178 = 0;
    moby_apply_damage_to_object(moby, vars->f140, 0);
    cam_compute_view_direction(moby->pos, vars->f280, 0);
    vec_negate_and_forward(moby->fC0, vars->f280, 0);
}
