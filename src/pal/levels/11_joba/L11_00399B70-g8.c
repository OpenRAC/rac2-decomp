#include "include_asm.h"

#include "common.h"
extern void FastVecAdd(f32 *a0, f32 *a1, f32 *a2);
extern f32 FastAddRotations(f32 a0, f32 a1);
extern f32 math_fabs(f32 a0);
extern s32 math_fast_float_d(void *a0);
extern s32 vec_fast_helper_a(void *a0);
extern void moby_mark_spawned(void *a0);
extern f32 g_debris_velocity_scale __attribute__((sda));
extern s32 math_random_int_range(s32 low, s32 high);
extern f32 math_random_float_range(f32 low, f32 high);
extern s32 g_ribbon_l11_point_count __attribute__((sda));
extern f32 g_ribbon_jitter __attribute__((sda));
extern f32 g_ribbon_direction_min __attribute__((sda));
extern f32 g_ribbon_direction_max __attribute__((sda));
extern f32 g_ribbon_width_min __attribute__((sda));
extern f32 g_ribbon_width_max __attribute__((sda));
extern f32 g_ribbon_height_min __attribute__((sda));
extern f32 g_ribbon_height_max __attribute__((sda));
extern f32 g_ribbon_offset_scale __attribute__((sda));
extern f32 math_random_signed_float_range(f32 low, f32 high);
extern f32 math_random_angle(void);
extern s32 func_001163B0(void);
extern s32 FloatToInt(f32 value);
extern s32 g_debris_lifetime_base __attribute__((sda));
extern f32 g_debris_l11_scale_factor __attribute__((sda));
extern u8 g_sheepinator_weapon_index[];
extern u8 g_item_l11_record_table[];

/* Scales the state's vector by the level's factor, clamps its timer to the state's
   limit, and runs the two animation angles through the engine's wrap function. */
void debris_l11_piece_update_pal(u8 *object) {
    u8 *moby = object;
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 vel_x, vel_y, fall, min_fall;

    FastVecAdd((f32 *)(moby + 0x10), (f32 *)(moby + 0x10), (f32 *)vars);
    fall = *(f32 *)(vars + 0x8) - 0.006f;
    vel_x = *(f32 *)(vars + 0x0) * g_debris_velocity_scale;
    vel_y = *(f32 *)(vars + 0x4) * g_debris_velocity_scale;
    min_fall = *(f32 *)(vars + 0x20);
    *(f32 *)(vars + 0x8) = fall;
    *(f32 *)(vars + 0x0) = vel_x;
    *(f32 *)(vars + 0x4) = vel_y;
    if (fall < min_fall)
        *(f32 *)(vars + 0x8) = min_fall;
    *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8), *(f32 *)(vars + 0x28));
    *(f32 *)(moby + 0xF0) = FastAddRotations(*(f32 *)(moby + 0xF0), *(f32 *)(vars + 0x2C) * (f32)*(s32 *)(vars + 0x24));
    vel_x = math_fabs(*(f32 *)(moby + 0xF0));
    if (vel_x > 0.78539824f)
        *(s32 *)(vars + 0x24) = -*(s32 *)(vars + 0x24);
    if (math_fast_float_d(vars + 0x1C) != 0) {
        moby_mark_spawned(moby);
    } else if (moby[0x31] == 0) {
        moby_mark_spawned(moby);
    } else if (*(s32 *)(vars + 0x1C) < 0x19) {
        if (vec_fast_helper_a(moby + 0x23) != 0)
            moby_mark_spawned(moby);
    }
}

extern void *CreateMoby(s32 classId);
extern void func_002A0F48(void *moby);
extern void hero_copy_field_to_moby(void *moby);
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xDB];
} JobaChoice_00396DC8;
typedef struct {
    f32 velocity[4];
    f32 random10;
    f32 random14;
    s32 pad18;
    s32 lifetime;
    f32 minFall;
    s32 swingDir;
    f32 spinRate;
    f32 swingRate;
} Piece_00396DC8;
typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 state;
    u8 pad21[0x2C - 0x21];
    f32 scale;
    u8 updateDist;
    u8 drawn;
    u16 drawDist;
    u16 modeBits;
    u8 pad36[0x68 - 0x36];
    Piece_00396DC8 *vars;
    u8 pad6C[0xBC - 0x6C];
    u8 byteBC;
    u8 padBD[0xF0 - 0xBD];
    f32 rot[3];
} PieceMoby_00396DC8;
extern u8 g_joba_choice_table[];

/* Spawns a moby at POSITION pushed three frames along MOTION, with random swing and spin
   rates, a random lifetime around D_L11_001AEC3C frames and the level's scale (doubled
   when the current selection record is enabled). */
PieceMoby_00396DC8 *debris_l11_spawn_piece_pal(void *unused, f32 *position, f32 *motion) {
    PieceMoby_00396DC8 *obj = CreateMoby(0x1AC);

    if (obj != 0) {
        Piece_00396DC8 *vars;
        s32 low;

        obj->modeBits |= 0x1000;
        obj->updateDist = 0x40;
        obj->drawDist = 0x20;
        obj->drawn = 1;
        vars = obj->vars;
        obj->state = 0;
        obj->byteBC = 0;
        qcopy(obj->pos, position);
        obj->pos[2] += math_random_float_range(0.2f, 0.7f);
        obj->pos[0] += motion[0] * 3.0f;
        obj->pos[1] += motion[1] * 3.0f;
        qcopy(vars, motion);
        obj->rot[1] = math_random_signed_float_range(0.17453295f, 0.523598849773407f);
        obj->rot[0] = math_random_float_range(0.17453295f, 0.7853982448577881f);
        vars->swingRate = math_random_float_range(200.0f, 370.0f) * 0.0003490659f;
        vars->swingDir = -1;
        if (func_001163B0() & 1) {
            vars->swingDir = 1;
            obj->rot[1] = -obj->rot[1];
        }
        obj->rot[2] = math_random_angle();
        vars->spinRate = -(math_random_float_range(200.0f, 550.0f) * 0.0003490659f);
        vars->random10 = math_random_angle();
        vars->random14 = math_random_angle();
        low = FloatToInt((f32)g_debris_lifetime_base * 0.7f);
        vars->lifetime = ((s32)(math_random_int_range(low, FloatToInt((f32)g_debris_lifetime_base * 1.2f))) * 5 + 2) / 6;
        obj->scale *= g_debris_l11_scale_factor;
        if (((JobaChoice_00396DC8 *)(g_joba_choice_table + g_sheepinator_weapon_index[0] * 0xE0))->enabled)
            obj->scale += obj->scale;
        vars->minFall = math_random_float_range(-1.2f, -0.4f) * 0.020000001f;
        func_002A0F48(obj);
        hero_copy_field_to_moby(obj);
    }
    return obj;
}
