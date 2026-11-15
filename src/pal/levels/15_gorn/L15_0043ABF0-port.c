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
extern void moby_process_collision_hit(char *, int, int, int);
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

extern int moby_get_motion_data(unsigned char *owner);
extern void func_PAL_L05_0037D610(char *object, int flag);
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

/* func_L15_00432A60 is in L15_00432A60-ribbon.c. */

extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern int state_get_stored_pointer_value(void);
extern void level_append_object(void *, void *, int, int);
extern void moby_reset_action_state(void *);
extern void func_PAL_L15_0043B0D8(char *);
extern void gorn_ship_update_flight(void *, int);
extern void ResetGroupToPathStart(void);
extern void gorn_ship_spawn_damage_effects(void *);
extern void part_spawn_shockwave_burst(void *, int, int, int, int, int, int, int, float, int, int, int);
extern int math_random_int_below(int);
extern void moby_mark_spawned(void *);
extern void euler_rotation_basis(void *, void *);

extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern u8 D_L15_00188660[];
extern s32 PlayMobySound(s32 a, s32 b, void *c);
extern s32 math_random_int_below(s32 a);
extern f32 math_random_float_range(f32 a, f32 b);
extern void moby_transform_joint_to_world(void *obj, s32 a, void *out);
extern void CreateEnergyStrip(void *a, void *b, s32 c, s32 d, f32 e, f32 f, f32 g, f32 h, s32 i, s32 j, s32 k, s32 l);
extern s32 FloatToInt(f32 a);
extern void gorn_part_spawn_puff(char *object, int a1, int joint, float radius);
/* The particle helper has a different catalogue body in PAL. */
extern void ref_L15_00434D28_00(char *object, int joint, int unused, float radius);



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

void func_PAL_L15_0043B0D8(char *object)
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
    func_PAL_L05_0037D610(object, 1);
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
    GI(0x444) = 250;
    GI(0x440) = 0;
    level_set_object_state_field((int)object, 0xFFFF);
    moby_set_record_callback((int)object, (void *)1);
}

/* func_L15_004360D8 is in L15_004360D8.c. */

extern int PlayMobySound(int, int, void *);
extern void SpawnSpaceProjectile(void *, int, int, float, int, float, float, float,
                              int, int, int);



/* func_L15_00438260 is in L15_00438260-g8.c. */

/* func_L15_00438518 is in L15_00438518-g8.c. */

extern int D_L15_001A8FF0[] __attribute__((sda));
extern char D_00189ED0[];
extern int math_random_int_below(int);
extern int func_001163B0(void);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern unsigned char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);


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