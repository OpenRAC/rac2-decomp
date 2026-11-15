#include "include_asm.h"
#include "common.h"

extern void AttachManipulator(unsigned char *, int, unsigned char *);
extern void moby_set_record_callback(int, void *);
#define GF(offset) (((GornState *)state)->f[(offset) / 4])
#define GI(offset) (((GornState *)state)->i[(offset) / 4])

/* Measured prefixes with integer/float views of the same game records. */
typedef union { float f[0x660 / 4]; int i[0x660 / 4]; } GornState;
typedef union { float f[0x80 / 4]; unsigned short h[0x80 / 2]; unsigned char b[0x80]; } GornOwnerFields;

typedef int GornQuad __attribute__((mode(TI)));
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

extern void matrix_mul_vec3(void *, void *, void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_angle_helper(float);
extern float math_fast_sin_or_cos_a(float);
extern char D_L15_001B97C0[];

extern void DrawPath(char *, int, int, int, float, int);
extern int follower_has_reached_target(char *);
extern void follower_set_push_vector(char *, char *);
extern void follower_set_state(char *, int);
extern void moby_update_movement_state(char *);
extern int moby_process_collision_hit(char *, int, int, int);
typedef struct GornPathPoint {
    float position[3];
    float action;
} GornPathPoint;

typedef struct GornPath {
    int count;
    int pad[3];
    GornPathPoint points[1];
} GornPath;
extern char *D_L15_001FE480[];
extern void gorn_path_mover_init(char *);
extern void path_start_following(void);

/* ---- shared declarations ---- */

extern char *moby_get_motion_data(unsigned char *owner);
extern void moby_init_spawned_sub_object(char *object, int flag);
extern void level_set_object_state_field(int arg0, int value);
extern void gfx_add_draw_callback_second(void *, void *);
extern void gfx_add_draw_callback_first(void *a0, void *a1);
extern void gfx_add_draw_callback_third(void *, int);
extern void gfx_draw_scrolling_grid_if_enabled(void);
extern void backdrop_update_effects(void);
extern void backdrop_draw_fade_layers(void);

extern void VU1_addGSregister(int, int);
extern void gfx_draw_colored_rectangle(int, int, int, int, long);
extern int math_fast_float_d(void *);
extern void DrawGornRibbon(void *, int, int, float, float, float, int, int, int);
extern short g_screen_adjust_offsets[];
extern char D_L15_00269FE0[];

/* Sets the level's four effect blocks up: the screen context first, then, when
   the level's own record says the object is idle, the four blocks of the
   effect data, each with its own size and colour. */
void gorn_draw_ribbon_effects(void *moby) {
    char *vars = *(char **)(moby + 0x68);

    VU1_addGSregister(0x42, 0x48);
    gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], 0x40404040);
    if (math_fast_float_d(vars + 0x50) == 0) {
        char *ribbon_data = D_L15_00269FE0;

        DrawGornRibbon(ribbon_data, 0x46, 0x46, 3.2f, 6.35f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1010);
        DrawGornRibbon(ribbon_data + 0xA0, 0x20, 0x20, 3.1f, 6.19f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1040);
        DrawGornRibbon(ribbon_data + 0x140, 0x20, 0x20, 3.1f, 6.19f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1040);
        DrawGornRibbon(ribbon_data + 0x1E0, 0x20, 0x20, 3.1f, 6.19f, 0.2f, 0x0A, 0x007F7F7F, 0x00FF1040);
    }
}

/* func_L15_00432A60 is in L15_00432A60-ribbon.c. */

extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void *state_get_stored_pointer_value(void);
extern void level_append_object(void *, void *, int, int);
extern void moby_reset_action_state(void *);
extern void gorn_ship_init(char *);
extern void gorn_ship_update_flight(void *, int);
extern void ResetGroupToPathStart(void);
extern void gorn_ship_spawn_damage_effects(void *);
extern char *part_spawn_shockwave_burst(void *, int, int, int, int, int, int, int, float, int, int, int);
extern int math_random_int_below(int);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);
/* Per-frame update of the Gorn enemy ship moby (class 4625): arms it, runs its route, fades it in and out, and drops it when it falls out of the level. */
void gorn_ship_update(unsigned char *moby) {
    float point[4] __attribute__((aligned(16)));
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float ratio;
    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (!state_get_stored_pointer_value()) return;
        gorn_ship_init((char *)moby);
        if (*(int *)(vars + 0x264))
            level_append_object(moby, ResetGroupToPathStart, 0, 0);
        qcopy(vars + 0x430, moby + 0x10);
        break;
    case 1:
        gorn_ship_update_flight(moby, 0);
        break;
    case 2:
        gorn_ship_update_flight(moby, 1);
        if (math_fast_float_d(vars + 0x274)) {
            moby[0x20] = 3;
            *(int *)(vars + 0x274) = 180;
        }
        break;
    case 3:
        gorn_ship_update_flight(moby, 1);
        ratio = IntToFloat(*(int *)(vars + 0x274)) / IntToFloat(180);
        moby[0x23] = FloatToInt((1.0f - ratio) * 95.0f) + 32;
        if (math_fast_float_d(vars + 0x274)) {
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            moby[0x20] = 4;
            *(int *)(vars + 0x274) = 600;
            moby[0x23] = 128;
            *(unsigned short *)(moby + 0x34) &= 0xFFF7;
        }
        break;
    case 4:
        gorn_ship_update_flight(moby, 0);
        if (math_fast_float_d(vars + 0x274)) {
            *(int *)(moby + 0x98) = 0;
            moby[0x20] = 5;
            *(int *)(vars + 0x274) = 180;
            *(unsigned short *)(moby + 0x34) |= 8;
        }
        break;
    case 5:
        gorn_ship_update_flight(moby, 1);
        ratio = IntToFloat(*(int *)(vars + 0x274)) / IntToFloat(180);
        moby[0x23] = FloatToInt(ratio * 95.0f) + 32;
        if (math_fast_float_d(vars + 0x274)) {
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
            moby[0x20] = 2;
            *(int *)(vars + 0x274) = 480;
            moby[0x23] = 32;
        }
        break;
    case 6:
        point[0] = *(float *)(moby + 0x10) + math_random_float_range(-3.0f, 3.0f);
        point[1] = *(float *)(moby + 0x14) + math_random_float_range(-3.0f, 3.0f);
        point[2] = *(float *)(moby + 0x18) + math_random_float_range(-3.0f, 3.0f);
        if (*(int *)(vars + 0x278) == 0) {
            part_spawn_shockwave_burst(point, 1, 24, 24, 24, 24, 24, 0, 3.0f, 1, 1, 1);
            *(int *)(vars + 0x278) = 1;
        }
        if (math_random_int_below(12) == 0 && *(float *)(moby + 0x18) > 350.0f)
            part_spawn_shockwave_burst(point, 0, 4, 4, 4, 4, 4, 0, 1.5f, 0, 0, 0);
        *(float *)(moby + 0x18) -= *(float *)(vars + 0x27C);
        *(float *)(vars + 0x27C) += 0.0005555555690079927f;
        *(float *)(vars + 0x404) = FastAddRotations(*(float *)(vars + 0x404), 0.0014544413425028324f);
        euler_rotation_basis(moby + 0xC0, vars + 0x400);
        gorn_ship_spawn_damage_effects(moby);
        if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
            *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
            *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f)
            moby_reset_action_state(moby);
        break;
    case 7:
        FastVecAdd(moby + 0x10, vars + 0x410, moby + 0x10);
        *(float *)(vars + 0x418) -= 0.003055555745959282f;
        *(float *)(vars + 0x404) = FastAddRotations(*(float *)(vars + 0x404), 0.02617994323372841f);
        euler_rotation_basis(moby + 0xC0, vars + 0x400);
        if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f ||
            *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f ||
            *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f) {
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    math_fast_float_d(vars + 0x450);
}

extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern u8 D_L15_00188660[];
extern s32 PlayMobySound(s32 a, s32 b, void *c);
extern s32 math_random_int_below(s32 a);
extern f32 math_random_float_range(f32 a, f32 b);
extern void moby_transform_joint_to_world(void *obj, s32 a, void *out);
extern void *CreateEnergyStrip(void *a, void *b, s32 c, s32 d, f32 e, f32 f, f32 g, f32 h, s32 i, s32 j, s32 k, s32 l);
extern s32 FloatToInt(f32 a);
extern void gorn_part_spawn_puff(char *object, int a1, int joint, float radius);
/* The particle helper has a different catalogue body in PAL. */
extern void ref_L15_00434D28_00(char *object, int joint, int unused, float radius);

/* Adds damage effects to the Gorn ship: crackling sparks and puffs of smoke that grow as it loses parts. */
void gorn_ship_spawn_damage_effects(void *object)
{
    u8 *obj = (u8 *)object;
    u8 *vars = *(u8 **)(obj + 0x68);
    u8 *sound_slot = D_L15_00188660 + *(s32 *)(vars + 0x458) * 0x70;
    f32 from_point[4] __attribute__((aligned(16)));
    f32 to_point[4] __attribute__((aligned(16)));
    s32 burst_count;
    s32 remaining;
    s32 *joint_list;

    if (*(u8 **)(sound_slot + 0x88) != obj || sound_slot[0x74] == 0) {
        *(s32 *)(vars + 0x458) = PlayMobySound(3, 4, obj);
    }
    if (math_random_int_below(0xF) == 0 && D_L15_001AEE20[0] < 4) {
        moby_transform_joint_to_world(obj, D_L15_001B1780[math_random_int_below(0xB)], from_point);
        moby_transform_joint_to_world(obj, D_L15_001B1780[math_random_int_below(0xB)], to_point);
        D_L15_001AEE20[0] = D_L15_001AEE20[0] + 1;
        CreateEnergyStrip(from_point, to_point, 0x19, 0, 0.5f, 0.2f, 0.4020000100135803f, 1.122249960899353f, 0x7F7F7F, 0xFF1010, 0x46, 0x46);
    }
    if (*(s32 *)(vars + 0x26C) < 7) {
        burst_count = FloatToInt(8.0f - (f32)*(s32 *)(vars + 0x26C));
        if (burst_count > 0) {
            remaining = burst_count;
            joint_list = D_L15_001B17B0;
            while (1) {
                if (math_random_int_below(2) != 0) {
                    gorn_part_spawn_puff((char *)obj, *joint_list, 0, math_random_float_range(2.0f, 3.0f));
                    ref_L15_00434D28_00((char *)obj, *joint_list, 0, math_random_float_range(0.5f, 1.5f));
                }
                remaining--;
                joint_list++;
                if (remaining == 0) break;
            }
        }
    }
    if (math_random_int_below(2) != 0 && *(s32 *)(vars + 0x26C) < 2) {
        gorn_part_spawn_puff((char *)obj, 0x14, 1, 7.0f);
        ref_L15_00434D28_00((char *)obj, 0x14, 0, math_random_float_range(3.0f, 4.5f));
    }
}



typedef struct GornEffectCamera {
    char pad00[0x140];
    float position[4];
} GornEffectCamera;
extern GornEffectCamera D_L15_001B9680;
extern unsigned char *D_L15_001FF4AC;
extern void moby_transform_joint_to_world(void *, int, void *);
extern float mat_fast_helper_a(float, float);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern unsigned char *SpawnSpinningSparkParticle(float, float, float, float,
                                   void *, int, void *, int, int);
extern int math_random_int_range(int, int);
extern int FloatToInt(float);
extern float IntToFloat(int);



/* Spawns one drifting smoke particle near a joint of the object. */
void gorn_part_spawn_smoke(char *object, int joint, int unused, float radius) {
    float initial[4], point[4], velocity[4];
    float heading, speed, tilt, yaw;
    unsigned char *particle;
    unsigned char *data;

    moby_transform_joint_to_world(object, joint, initial);
    heading = mat_fast_helper_a(D_L15_001B9680.position[0] - *(float *)(object + 0x10),
                            D_L15_001B9680.position[1] - *(float *)(object + 0x14));
    point[0] = initial[0] + math_random_signed_float_range(0, radius);
    point[1] = initial[1] + math_random_signed_float_range(0, radius);
    point[2] = initial[2] + math_random_signed_float_range(0, radius);
    speed = math_random_float_range(radius * 0.008333333767950535f,
                          radius * 0.01666666753590107f);
    tilt = math_random_signed_float_range(0, 1.396263599395752f);
    yaw = FastAddRotations(heading, math_random_signed_float_range(0, 1.5707964897155762f));
    vec_build_spherical_offset(velocity, speed, yaw, tilt);
    particle = SpawnSpinningSparkParticle(0, 1.0f, 1.01f, radius * 210000.0f,
                            point, -1, velocity, 0x307F7F7F, 0);
    if (particle != 0) {
        particle[3] = 0x48;
        *(short *)(particle + 0xA) = math_random_int_range(40, 70);
        particle[9] = FloatToInt(4.0f) + 0x60;
        data = particle + 0x20;
        *(float *)(data + 0x1C) = IntToFloat(math_random_int_range(1, 10));
        *(int *)(data + 4) = 3;
        data[0xA] = 0x7F;
        data[0xB] = particle[0xA];
        particle[2] = *D_L15_001FF4AC;
    }
}

/* Sets up the Gorn ship the first time: its health, joint positions and the table of part positions. */
void gorn_ship_init(char *object)
{
    GornOwnerFields *fields = (GornOwnerFields *)object;
    char *state = *(char **)(object + 0x68);
    char *record;
    char *a = state + 0x2B0;
    char *b = state + 0x2F0;
    char *c = state + 0x330;
    char *d = state + 0x370;
    char *e = state + 0x3B0;
    char *f = state + 0x3F0;
    char *position = object + 0x10;
    record = (char *)moby_get_motion_data((unsigned char *)object);
    *(int *)(record + 0x148) = FloatToInt(150.0f);
    moby_init_spawned_sub_object(object, 1);
    GF(0x180) = 150.0f;
    object[0x20] = 1;
    *(unsigned char *)(object + 0x30) = 255;
    *(unsigned short *)(object + 0x32) = 0x1FF;
    *(float *)(object + 0x2C) = 0.675f;
    *(unsigned short *)(object + 0x34) |= 0x100;
    *(unsigned short *)(object + 0x7C) = 63;
    GI(0x458) = -1;
    GI(0x268) = 1;
    GI(0x270) = 0;
    GI(0x27C) = 0;
    GI(0x45C) = 0;
    GI(0x278) = 0;
    moby_transform_joint_point(object, 14, state + 0x280);
    moby_transform_joint_point(object, 16, state + 0x2C0);
    moby_transform_joint_point(object, 18, state + 0x300);
    moby_transform_joint_point(object, 15, state + 0x340);
    moby_transform_joint_point(object, 17, state + 0x380);
    moby_transform_joint_point(object, 19, state + 0x3C0);
    FastVecSub(a, a, position);
    FastVecSub(d, d, position);
    FastVecSub(d, d, a);
    FastVecScale(a, a, 1.0f / fields->f[0x2C / 4]);
    FastVecScale(d, d, 1.0f / fields->f[0x2C / 4]);
    FastVecSub(b, b, position);
    FastVecSub(e, e, position);
    FastVecSub(e, e, b);
    FastVecScale(b, b, 1.0f / fields->f[0x2C / 4]);
    FastVecScale(e, e, 1.0f / fields->f[0x2C / 4]);
    FastVecSub(c, c, position);
    FastVecSub(f, f, position);
    FastVecSub(f, f, c);
    FastVecScale(c, c, 1.0f / fields->f[0x2C / 4]);
    FastVecScale(f, f, 1.0f / fields->f[0x2C / 4]);
    AttachManipulator((unsigned char *)object, 12, (unsigned char *)(state + 0x460));
    AttachManipulator((unsigned char *)object, 13, (unsigned char *)(state + 0x4A0));
    AttachManipulator((unsigned char *)object, 14, (unsigned char *)(state + 0x4E0));
    AttachManipulator((unsigned char *)object, 15, (unsigned char *)(state + 0x520));
    AttachManipulator((unsigned char *)object, 16, (unsigned char *)(state + 0x560));
    AttachManipulator((unsigned char *)object, 17, (unsigned char *)(state + 0x5A0));
    AttachManipulator((unsigned char *)object, 18, (unsigned char *)(state + 0x5E0));
    AttachManipulator((unsigned char *)object, 19, (unsigned char *)(state + 0x620));
    GF(0x510) = GF(0x2B0) * 1024.0f;
    GF(0x514) = GF(0x2B4) * 1024.0f;
    GF(0x518) = GF(0x2B8) * 1024.0f;
    GF(0x550) = GF(0x370) * 1024.0f;
    GF(0x554) = GF(0x374) * 1024.0f;
    GF(0x558) = GF(0x378) * 1024.0f;
    GF(0x590) = GF(0x2F0) * 1024.0f;
    GF(0x594) = GF(0x2F4) * 1024.0f;
    GF(0x598) = GF(0x2F8) * 1024.0f;
    GF(0x5D0) = GF(0x3B0) * 1024.0f;
    GF(0x5D4) = GF(0x3B4) * 1024.0f;
    *(unsigned char *)(state + 0x4E3) = 1;
    *(unsigned char *)(state + 0x523) = 1;
    *(unsigned char *)(state + 0x563) = 1;
    *(unsigned char *)(state + 0x5A3) = 1;
    GF(0x4EC) = 1.0f;
    GF(0x51C) = 1.0f;
    GF(0x52C) = 1.0f;
    GF(0x55C) = 1.0f;
    GF(0x56C) = 1.0f;
    GF(0x59C) = 1.0f;
    GF(0x5AC) = 1.0f;
    GF(0x5D8) = GF(0x3B8) * 1024.0f;
    GF(0x5DC) = 1.0f;
    *(unsigned char *)(state + 0x5E3) = 1;
    GF(0x610) = GF(0x330) * 1024.0f;
    GF(0x614) = GF(0x334) * 1024.0f;
    GF(0x618) = GF(0x338) * 1024.0f;
    GF(0x650) = GF(0x3F0) * 1024.0f;
    GF(0x654) = GF(0x3F4) * 1024.0f;
    GF(0x658) = GF(0x3F8) * 1024.0f;
    *(unsigned char *)(state + 0x623) = 1;
    GF(0x5EC) = 1.0f;
    GF(0x61C) = 1.0f;
    GF(0x62C) = 1.0f;
    GF(0x65C) = 1.0f;
    GI(0x444) = 300;
    GI(0x440) = 0;
    level_set_object_state_field((int)object, 0xFFFF);
    moby_set_record_callback((int)object, (void *)1);
}

/* Turns the ship's eight parts toward the camera by building a rotation for each joint pair. */
void gorn_ship_aim_parts(char *object) {
    float forward[4], up[4], side[4], axis1[4], axis2[4];
    float matrix1[16], matrix2[16], delta[4], temp[4];
    float angle, dot;
    char *state = *(char **)(object + 0x68);
    char *owner = (char *)moby_get_motion_data((unsigned char *)object);
    *(GornQuad *)forward = 0; *(GornQuad *)up = 0; *(GornQuad *)side = 0;
    *(GornQuad *)axis1 = 0; *(GornQuad *)axis2 = 0;
    forward[0] = 1.0f; up[2] = 1.0f; side[1] = 1.0f;
    axis1[2] = 1.0f; axis2[1] = 1.0f;
    if (*(int *)(owner + 0x120) == 0) return;
    matrix_mul_vec3(forward, forward, object + 0xC0);
    matrix_mul_vec3(up, up, object + 0xC0);
    matrix_mul_vec3(side, side, object + 0xC0);
    moby_transform_joint_point(object, 14, matrix1);
    moby_transform_joint_point(object, 15, matrix2);
    FastVecSub(delta, D_L15_001B97C0, matrix1 + 12);
    dot = FastVecDot(delta, up);
    FastVecScale(temp, up, dot);
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, delta, 1.0f);
    angle = (1.5707963705062866f - math_fast_angle_helper(FastVecDot(forward, delta))) * 0.5f;
    if (FastVecDot(delta, side) > 0.0f) angle = -angle;
    FastVecScale(state + 0x4F0, axis1, math_fast_sin_or_cos_b(angle));
    *(float *)(state + 0x4FC) = math_fast_sin_or_cos_a(angle);
    FastVecSub(delta, D_L15_001B97C0, matrix2 + 12);
    FastVecScale(temp, up, FastVecDot(delta, up));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, forward, FastVecLength(delta));
    FastVecAdd(delta, temp, delta);
    vec_scale_to_length(delta, delta, 1.0f);
    dot = FastVecDot(delta, up);
    if (dot <= 0.3142099976539612f) dot = 0.3142099976539612f;
    angle = (1.5707963705062866f - math_fast_angle_helper(dot)) * 0.5f;
    FastVecScale(state + 0x530, axis2, -math_fast_sin_or_cos_b(angle));
    *(float *)(state + 0x53C) = math_fast_sin_or_cos_a(angle);
    moby_transform_joint_point(object, 16, matrix1);
    moby_transform_joint_point(object, 17, matrix2);
    FastVecSub(delta, D_L15_001B97C0, matrix1 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, delta, 1.0f);
    angle = (1.5707963705062866f - math_fast_angle_helper(FastVecDot(forward, delta))) * 0.5f;
    if (FastVecDot(delta, up) > 0.0f) angle = -angle;
    FastVecScale(state + 0x570, axis2, -math_fast_sin_or_cos_b(angle));
    *(float *)(state + 0x57C) = math_fast_sin_or_cos_a(angle);
    FastVecSub(delta, D_L15_001B97C0, matrix2 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, forward, FastVecLength(delta));
    FastVecAdd(delta, temp, delta);
    vec_scale_to_length(delta, delta, 1.0f);
    dot = FastVecDot(delta, side);
    if (dot <= 0.3142099976539612f) dot = 0.3142099976539612f;
    angle = (1.5707963705062866f - math_fast_angle_helper(dot)) * 0.5f;
    FastVecScale(state + 0x5B0, axis1, math_fast_sin_or_cos_b(angle));
    *(float *)(state + 0x5BC) = math_fast_sin_or_cos_a(angle);
    moby_transform_joint_point(object, 18, matrix1);
    moby_transform_joint_point(object, 19, matrix2);
    FastVecScale(side, side, -1.0f);
    FastVecSub(delta, D_L15_001B97C0, matrix1 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, delta, 1.0f);
    angle = (1.5707963705062866f - math_fast_angle_helper(FastVecDot(forward, delta))) * 0.5f;
    if (FastVecDot(delta, up) > 0.0f) angle = -angle;
    FastVecScale(state + 0x5F0, axis2, -math_fast_sin_or_cos_b(angle));
    *(float *)(state + 0x5FC) = math_fast_sin_or_cos_a(angle);
    FastVecSub(delta, D_L15_001B97C0, matrix2 + 12);
    FastVecScale(temp, side, FastVecDot(delta, side));
    FastVecSub(delta, delta, temp);
    vec_scale_to_length(delta, forward, FastVecLength(delta));
    FastVecAdd(delta, temp, delta);
    vec_scale_to_length(delta, delta, 1.0f);
    dot = FastVecDot(delta, side);
    if (dot <= 0.3142099976539612f) dot = 0.3142099976539612f;
    angle = (1.5707963705062866f - math_fast_angle_helper(dot)) * 0.5f;
    FastVecScale(state + 0x630, axis1, -math_fast_sin_or_cos_b(angle));
    *(float *)(state + 0x63C) = math_fast_sin_or_cos_a(angle);
}


/* func_L15_00435E80 is in L15_00435E80.c. */

/* Puts the object into its falling state with a long timer and full health value. */
void gorn_ship_start_falling(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    *(int *)(vars + 0x270) = 1;
    *(int *)(vars + 0x274) = 0x1E0;
    *(char *)(moby + 0x23) = 0x20;
    *(char *)(moby + 0x20) = 2;
    *(unsigned short *)(moby + 0x34) |= 8;
    *(float *)(vars + 0x180) = 450.0f;
    *(int *)(moby + 0x98) = 0;
}

/* func_L15_004360D8 is in L15_004360D8.c. */

extern int PlayMobySound(int, int, void *);
extern void SpawnSpaceProjectile(void *, int, int, float, int, float, float, float,
                              int, int, int);

/* The mover's own state decides whether the shot happens: the level's record
   must exist and be ready, and the mover's own counter must be idle.  The two
   shots take the slots after the counter, and the counter wraps at three. */
void gorn_path_mover_fire_shots(char *moby) {
    char *mover = moby;
    char *vars;
    char *owner;
    int shot_index;

    vars = *(char **)(mover + 0x68);
    owner = (char *)moby_get_motion_data(moby);
    if (owner == 0) {
        return;
    }
    if (*(int *)(owner + 0x120) == 0) {
        return;
    }
    if (*(int *)(vars + 0x450) != 0) {
        return;
    }
    PlayMobySound(2, 0, mover);
    SpawnSpaceProjectile(mover, 0x600000CF, 1, 1.0f, 0, 2.0f, 1.5f, 1.5f, 0x1E,
                     *(int *)(vars + 0x454) * 2 + 4, 0);
    SpawnSpaceProjectile(mover, 0x600000CF, 1, 1.0f, 0, 2.0f, 1.5f, 1.5f, 0x1E,
                     *(int *)(vars + 0x454) * 2 + 5, 0);
    *(int *)(vars + 0x450) = math_random_int_range(0x14, 0x3C);
    shot_index = *(int *)(vars + 0x454) + 1;
    *(int *)(vars + 0x454) = shot_index;
    if (shot_index >= 3) {
        *(int *)(vars + 0x454) = 0;
    }
}

/* func_L15_004363C8 is in L15_004363C8-g8.c. */

/* Advance through the path points, pausing when an odd encoded action supplies
   a duration in seconds. The path has a 16-byte header and 16-byte points. */
void UpdateGornPathMover(char *object) {
    char *mover = object;
    char *state = *(char **)(mover + 0x68);

    switch (*(unsigned char *)(mover + 0x20)) {
    case 0:
        *(unsigned char *)(mover + 0x30) = 0xFF;
        if (state_get_stored_pointer_value() == 0) {
            return;
        }
        gorn_path_mover_init(mover);
        if (*(int *)(state + 0x264) != 0) {
            level_append_object(mover, (void *)path_start_following, 0, 0);
        }
        DrawPath(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        break;
    case 1: {
        GornPath *path;
        char *owner;
        int index;

        DrawPath(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        owner = (char *)moby_get_motion_data(mover);
        path = (GornPath *)D_L15_001FE480[*(int *)(state + 0x268)];
        if (follower_has_reached_target(mover) != 0) {
            index = *(int *)(state + 0x26C);
            *(int *)(state + 0x26C) = index + 1;
            if (index + 1 == path->count - 1) {
                *(unsigned char *)(mover + 0x20) = 3;
            } else {
                float action = path->points[index].action;

                if (action != -1.0f) {
                    if ((FloatToInt(action) & 1) != 0) {
                        *(int *)(state + 0x274) = (FloatToInt(action) >> 1) * 0x3C;
                        *(unsigned char *)(mover + 0x20) = 2;
                    }
                }
                follower_set_push_vector(mover, (char *)&path->points[*(int *)(state + 0x26C)]);
                *(int *)(owner + 0x130) = 0x1E8480;
            }
        }
        follower_set_state(mover, 0xC);
        moby_update_movement_state(mover);
        moby_process_collision_hit(mover, 0, 1, 1);
        break;
    }
    case 2:
        if (math_fast_float_d((int *)(state + 0x274)) != 0) {
            *(unsigned char *)(mover + 0x20) = 1;
        }
        break;
    }
}


/* Sets up the Gorn path mover the first time: health, size and starting path counters. */
void gorn_path_mover_init(char *moby) {
    char *mover = moby;
    char *vars = *(char **)(mover + 0x68);
    char *owner = (char *)moby_get_motion_data((unsigned char *)moby);

    *(int *)(owner + 0x148) = 100;
    moby_init_spawned_sub_object(mover, 1);
    *(float *)(vars + 0x180) = 100.0f;
    *(unsigned char *)(mover + 0x20) = 1;
    *(unsigned char *)(mover + 0x30) = 0xFF;
    *(unsigned short *)(mover + 0x32) = 0x1FF;
    *(unsigned short *)(mover + 0x34) |= 0x100;
    *(float *)(mover + 0x2C) = 0.20000000298023224f;
    *(float *)(vars + 0x278) = 10.0f;
    *(int *)(vars + 0x26C) = 0;
    *(int *)(vars + 0x270) = 0;
    *(int *)(vars + 0x274) = 0;
    *(int *)(owner + 0x154) = (int)(vars + 0x278);
    level_set_object_state_field((int)mover, 0xFFFF);
}


/* Registers the three scrolling grid draw callbacks for the object. */
void gorn_register_grid_draw_callbacks(void *moby) {
    gfx_add_draw_callback_second((void *)gfx_draw_scrolling_grid_if_enabled, moby);
    gfx_add_draw_callback_first((void *)backdrop_update_effects, moby);
    gfx_add_draw_callback_third((void *)backdrop_draw_fade_layers, moby);
}

/* func_L15_00437B68 is in L15_00437B68-g8.c. */

/* func_L15_00438260 is in L15_00438260-g8.c. */

/* func_L15_00438518 is in L15_00438518-g8.c. */

extern int D_L15_001A8FF0[] __attribute__((sda));
extern char D_00189ED0[];
extern int math_random_int_below(int);
extern int func_001163B0(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern unsigned char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
/* Spawns a burst of spinning spark particles at a position. */
void gorn_part_spawn_spark_burst(char *pos, int count, int mode) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    FastVecSub(direction, D_L15_001B97C0, (float *)pos);
    if (D_L15_001A8FF0[0] == 0) {
        direction[2] = 0.0f;
        axis[0] = 0.0f; axis[1] = 0.0f; axis[2] = 1.0f; axis[3] = 1.0f;
    } else {
        FastVecSub(extra, pos, D_00189ED0);
        vec_scale_to_length(axis, extra, 1.0f);
        FastVecScale(extra, axis, FastVecDot(axis, direction));
        FastVecSub(direction, direction, extra);
    }
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.75f, 2.0f);
        sign = math_random_int_below(2);
        if (sign == 0)
            sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        speed = math_random_float_range(0.05f, 3.0f) * (1.0f / 60.0f);
        vec_scale_to_length((char *)velocity, (char *)velocity, speed);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += math_random_signed_float_range(0.0f, 0.15f);
        point[1] += math_random_signed_float_range(0.0f, 0.15f);
        point[2] += math_random_signed_float_range(0.0f, 0.15f);
        if (mode == 0) {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            } else {
                FastVecSub(extra, D_L15_001B97C0, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            }
        } else {
            if (!(func_001163B0() & 1)) {
                FastVecScale(velocity, velocity, 1.5f);
                particle = part_spawn_ground_effect(point, 60, size * 0.3f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 60, size * 0.21000000834465027f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            } else {
                FastVecSub(extra, D_L15_001B97C0, point);
                vec_scale_to_length((char *)extra, (char *)extra, speed);
                FastVecAdd((char *)velocity, (char *)velocity, (char *)extra);
                particle = part_spawn_ground_effect(point, 40, size * 0.25f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
                if (particle)
                    particle[9] = FloatToInt(4.0f) + 0x70;
                particle = part_spawn_ground_effect(point, 40, size * 0.175f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
            }
        }
        if (particle)
            particle[9] = FloatToInt(4.0f) + 0x70;
    }
}


/* The level's id lists: the number of groups, the table of the groups' lists (a pointer, read
   through $gp in a branch delay slot and as a bare lui/lw elsewhere: `sda` arrays of unknown size
   give that), the base of the 64-byte records of the first walk, the base of the 32-byte records
   of the second, and the table that maps a record's byte at +0x1D to a class. */
extern int D_L15_001A9018[] __attribute__((sda));
extern unsigned short **D_L15_001A9014[] __attribute__((sda));
extern unsigned char *D_L15_001B2C9C[] __attribute__((sda));
extern unsigned char *D_L15_001B2C94[] __attribute__((sda));
extern short D_L15_00227500[];

extern float vec_distance_xy(void *, void *);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_b(float);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void BuildObjectAttachmentTransforms(void *, void *, int, int, int, int, int, int);
extern void level_set_record_payload_by_key(void *, int, int, void *);
extern void moby_update_attached_transforms(void *, void *);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);

/* State 0 looks for the group of the level's id lists that holds the 64-byte record closest to
   the object (first walk, distances below 9999.0; the group index goes to the state's first word
   and the function ends when there is none), sets the object's aim from two random values
   (func_002A7878, func_002A7940) and the record list at state + 0x40, removes the object when the
   state's byte at +0x8A is zero, and otherwise walks the chosen group's 32-byte records
   (second walk): records of class 0xD34 and 0xD33 get their id written into the record list with
   the payload at state + 0x680 and state + 0x6A0 (func_L00_00323E48).  It then picks two random
   angular speeds (the second gets the sign opposite to the first) and goes to state 1, which
   keeps aiming and turns the two angles at +0x688 and +0x6A8.  Both walks keep the second
   `p != 0` guard before the `p[-1]` read and the second walk has a pointer variable of its own
   (one shared variable swaps two callee-saved registers).  Measured: a0 + 0xC0 and a0 + 0xF0
   formed in locals ahead of the second walk make loop.c hoist the two class constants out of it
   (two more saved registers); written at their use after the walk, as below, they stay in the
   loop.  The sign test is a store followed by a conditional store, which gives retail's
   `bc1f` with the first store in its slot and lets the constant 1 be shared by both stores. */
/* Per-frame update of a Gorn moby (class 4729): finds the nearest group, aims at it and spins its parts. */
void gorn_group_aim_update(unsigned char *moby)
{
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    unsigned short *p;
    unsigned short *q;
    unsigned char *record;
    int i;
    int best_group;
    short cls;
    float best_distance;
    float distance;
    float turn_b;

    switch (moby[0x20]) {
    case 0:
        best_group = -1;
        best_distance = 9999.0f;
        for (i = 0; i < D_L15_001A9018[0]; i++) {
            for (p = D_L15_001A9014[0][i];
                 p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L15_001A9014[0][i]);
                 p++) {
                record = D_L15_001B2C9C[0] + ((*p & 0x7FFF) << 6);
                if (record == 0)
                    break;
                distance = vec_distance_xy(record + 0x30, moby + 0x10);
                if (distance < best_distance) {
                    best_distance = distance;
                    best_group = i;
                }
            }
        }
        *(int *)vars = best_group;
        if (best_group == -1)
            return;
        *(float *)(vars + 0x28) = 12.0f;
        *(float *)(vars + 0x2C) = math_random_float_range(30.0f, 37.0f);
        *(float *)(vars + 0x1C) = math_random_angle();
        *(float *)(vars + 0xC) = math_fast_sin_or_cos_b(*(float *)(vars + 0x1C)) * *(float *)(vars + 0x28);
        math_update_wrapped_angle_offset(moby, vars + 0x1C, vars + 0xC, *(float *)(vars + 0x28),
                      *(float *)(vars + 0x2C) * 0.000290888245f, -1.0f);
        moby[0x30] = 0xFF;
        BuildObjectAttachmentTransforms(moby, vars + 0x40, 20, *(int *)(vars + 4), *(int *)vars,
                          *(int *)(vars + 8), 7, 0);
        if (vars[0x8A] == 0) {
            moby_mark_spawned(moby);
            return;
        }
        for (q = D_L15_001A9014[0][*(int *)vars];
             q != 0 && ((q != 0 && (short)q[-1] >= 0) || q == D_L15_001A9014[0][*(int *)vars]);
             q++) {
            record = D_L15_001B2C94[0] + ((*q & 0x7FFF) << 5);
            if (record == 0)
                break;
            cls = D_L15_00227500[record[0x1D]];
            if (cls == 0xD34 /* moby class 3380 */)
                level_set_record_payload_by_key(vars + 0x40, 1, (short)*q, vars + 0x680);
            if (cls == 0xD33 /* moby class 3379 */)
                level_set_record_payload_by_key(vars + 0x40, 1, (short)*q, vars + 0x6A0);
        }
        vars[0x8D] = 1;
        *(unsigned short *)(moby + 0x34) |= 0x104;
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        *(float *)(vars + 0x38) = math_random_signed_float_range(27.0f, 52.0f) * 0.000290888245f;
        turn_b = math_random_signed_float_range(25.0f, 37.0f) * 0.000290888245f;
        *(float *)(vars + 0x3C) = turn_b;
        if (0.0f <= *(float *)(vars + 0x38) * turn_b)
            *(float *)(vars + 0x3C) = -turn_b;
        moby[0x20] = 1;
        break;
    case 1:
        math_update_wrapped_angle_offset(moby, vars + 0x1C, vars + 0xC, *(float *)(vars + 0x28),
                      *(float *)(vars + 0x2C) * 0.000290888245f, -1.0f);
        *(float *)(vars + 0x688) = FastAddRotations(*(float *)(vars + 0x688), *(float *)(vars + 0x38));
        *(float *)(vars + 0x6A8) = FastAddRotations(*(float *)(vars + 0x6A8), *(float *)(vars + 0x3C));
        moby_update_attached_transforms(moby, vars + 0x40);
        break;
    }
}
