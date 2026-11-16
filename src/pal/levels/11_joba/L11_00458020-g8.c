#include "names.h"
/* func_PAL_L11_00458020, the PAL copy of func_L11_00452450: the same C, where 0.0055555557f
   becomes 0.008f; 0.004444444552063942f becomes 0.0064000003f; 0.13333334028720856f becomes
   0.16000001f; 0.0011635529808700085f becomes 0.0016755164f; 0.10471977293491364f becomes
   0.12566373f; func_L11_00452DF8 becomes func_PAL_L11_004589C8; func_002B0ED8 becomes
   func_PAL_002B1A50; 0.8377582f becomes 1.0053098f. */
#include "common.h"

extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern void FastVecAdd(void *, void *, void *);

typedef struct JobObject JobObject;

typedef struct {
    u8 pad00[0x18];
    float *params;          /* +0x18, points at param_block */
    u8 pad1C[4];
    float health;           /* +0x20 */
    u8 pad24[4];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 f34;
    u8 pad35[0x48 - 0x35];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    u8 hit_info[0x10];       /* +0x50 */
    u8 f60;
    u8 pad61[8];
    u8 f69;
    u8 pad6A[0x80 - 0x6A];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xFC - 0x9C];
    float fFC;
    float param_block[5];    /* +0x100 */
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x1D4 - 0x138];
    float f1D4;
    u8 pad1D8[0x1E6 - 0x1D8];
    u8 f1E6;
    u8 pad1E7;
    u8 f1E8;
    u8 f1E9;
    u8 pad1EA[0x1FC - 0x1EA];
    u16 spawn_timer;         /* +0x1FC */
    u8 pad1FE[0x2F0 - 0x1FE];
    float basis[12];        /* +0x2F0 */
    float anchor[4];        /* +0x320 */
    u8 pad330[0x354 - 0x330];
    JobObject *turret;      /* +0x354 */
    float turn_rate;         /* +0x358 */
    u8 pad35C[0x364 - 0x35C];
    s16 fire_timer;          /* +0x364 */
    u8 pad366[0x36E - 0x366];
    s16 f36E;
} JobState;

struct JobObject {
    u8 pad00[0x10];
    float position[4];      /* +0x10 */
    u8 stage;               /* +0x20 */
    u8 pad21[0x31 - 0x21];
    u8 f31;
    u8 pad32[2];
    u16 flags;              /* +0x34 */
    u8 pad36[0x68 - 0x36];
    JobState *state;        /* +0x68 */
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0x95 - 0x70];
    u8 f95;
    u8 pad96[0xB8 - 0x96];
    s32 fB8;
    u8 padBC[4];
    float rotation[12];     /* +0xC0 */
};

extern s32 FloatToInt(float);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 moby_apply_damage_to_object_pal(void *, void *, s32);
extern void matrix_from_basis_rows(void *, void *);
extern void cam_compute_view_direction(void *, void *, s32);
extern s32 arena_is_point_in_inner_zone(s32, void *);
extern void moby_set_state(void *, s32, s32);
extern char g_hero_l11_position[];
extern s32 g_enemy_ai_frozen;

extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern void flamethrower_robot_deactivate_pal(void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void vec_clear_128(void *);
extern void transform_vector(void *, void *, void *);
extern s32 weapon_select_aim_target(void *, s32, s32, s32, float, float);

/* Per-frame update of an L11 object: on its first frame it seeds its state block (a random-sign
   turn rate of 15 to 40 degrees, the 0.5/0.4 constant set) and runs its setup; then it sets the
   proximity flag, rebuilds the frame at state + 0x290 and, from stage 3 on, runs its hit, death
   and tracking checks. */
void turret_enemy_update_b_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *aim;
    char *hit;
    char *source;
    float matrix[16];
    float turn_rate;
    s16 kind;

    if (*(u8 *)(object + 0x20) == 0) {
        *(char **)(state + 0x18) = state + 0x100;
        turn_rate = math_random_float_range(15.0f, 40.0f) * 0.017453294f;
        if (math_random_int_below(2) != 0)
            turn_rate = -turn_rate;
        *(f32 *)(state + 0x2C8) = turn_rate;
        if (math_random_int_below(2) == 1)
            *(u16 *)(object + 0x34) |= 0x8000;
        *(u8 *)(state + 0x48) = FloatToInt(15.0f);
        *(u8 *)(state + 0x4A) = FloatToInt(12.0f);
        *(u8 *)(state + 0x60) = 0xB;
        *(s32 *)(state + 0x98) = 4;
        *(f32 *)(state + 0x100) = 0.8f;
        *(f32 *)(state + 0x104) = *(f32 *)(state + 0x84) = *(f32 *)(state + 0x80) = 0.5f;
        *(f32 *)(state + 0x10C) = *(f32 *)(state + 0x108) = *(f32 *)(state + 0x8C) = 0.4f;
        *(f32 *)(state + 0x110) = 1.5707965f;
        *(f32 *)(state + 0x130) = 0.52359885f;
        *(f32 *)(state + 0x12C) = 0.008f;
        *(f32 *)(state + 0x134) = 2.8f;
        moby_set_controller_speed_limits(object, 0.0064000003f, 0.16000001f,
                      0.0016755164f, 0.12566373f);
        *(u8 *)(state + 0x28) = 3;
        flamethrower_robot_deactivate_pal(object);
    }
    if (*(s16 *)(state + 0x2D8) == 0 && *(u8 *)(object + 0x20) != 0xC && g_enemy_ai_frozen == 0) {
        *(u16 *)(object + 0x34) |= 0x400;
        if (*(u8 *)(object + 0x31) != 0 && fast_vec_dist(object + 0x10, g_hero_l11_position) < 24.0f) {
            moby_update_ground_check(object);
            *(u8 *)(object + 0x6F) = 0x16;
        }
    } else {
        *(u16 *)(object + 0x34) &= 0xFBFF;
    }
    aim = state + 0x290;
    moby_transform_joint_to_world(object, 1, state + 0x270);
    moby_transform_joint_to_world(object, 2, state + 0x280);
    moby_transform_joint_point(object, 3, matrix);
    vec_clear_128(aim);
    *(s32 *)(state + 0x298) = 0;
    *(f32 *)(state + 0x290) = 0.25f;
    transform_vector(aim, aim, matrix);
    FastVecAdd(aim, aim, matrix + 12);
    if (*(u8 *)(object + 0x20) >= 3) {
        hit = (char *)part_find_owned_effect_slot(object, 0x10000, 1);
        if (hit != 0) {
            source = *(char **)(hit + 0x20);
            if (source != 0 && *(u8 *)(object + 0x31) == 0) {
                kind = *(s16 *)(source + 0xAA);
                if (kind == 0xA03 || kind == 0xB89)
                    *(s32 *)(hit + 0x2C) = 0;
            }
        }
        if (moby_apply_damage_to_object_pal(object, state + 0x50, 0) == 5) {
            *(s32 *)(state + 0xE0) = 0;
            *(f32 *)(state + 0xE4) = 1.0053098f;
        }
        if (*(s16 *)(state + 0x2D8) != 0) {
            char *pos;
            matrix_from_basis_rows(state + 0x230, object + 0xC0);
            pos = object + 0x10;
            cam_compute_view_direction(pos, state + 0x260, 0);
            if (arena_is_point_in_inner_zone(*(s32 *)(object + 0xB8), pos) == 0) {
                *(s32 *)(state + 0x20) = 0;
                moby_set_state(object, 0xC, 4);
            }
        }
        if (*(u8 *)(object + 0x20) >= 2 && *(u8 *)(state + 0x2E) == 2)
            flamethrower_robot_deactivate_pal(object);
        *(s16 *)(state + 0x2D0) = weapon_select_aim_target(object, *(s32 *)(state + 0x2CC), 0, 0, 100.0f, 100.0f);
        *(s32 *)(state + 0x2C4) = *(s32 *)(state + 0x220);
    }
}
