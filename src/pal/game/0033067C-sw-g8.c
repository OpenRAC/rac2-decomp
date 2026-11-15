#include "include_asm.h"

#include "common.h"
typedef struct {
    float x, y, z, w;
} UpdateVec;
typedef struct {
    UpdateVec start, end, velocity;
    void *object;
    void *ignore;
    int ignoreCount;
    float radius, friction, bounce;
    int flags, mask, response, surface, gravity;
    float maxTurn;
} UpdateQuery;
typedef union {
    UpdateQuery query;
    struct {
        UpdateVec angles, adjusted, transform[4];
    } attachment;
} UpdateWorkspace;
typedef struct {
    char pad[0x18];
    char *hit;
    int count;
    UpdateVec point, extra, normal;
} UpdateCollision;
extern char D_L00_001B2C00[] MACRO_ADDR;
extern UpdateCollision g_collision_result;
extern char D_L00_001BF240[];
extern char g_hero_state[];
extern char *g_follow_camera_object __attribute__((nosda));
extern int D_L00_001A904C[] MACRO_ADDR;
extern int D_0018C0B4 __attribute__((nosda));
extern int D_00138324 __attribute__((nosda));
extern int D_L00_001A8F00 __attribute__((sda));
extern float D_L00_001B0C98 __attribute__((sda));
extern char *D_L00_001B0CA0 __attribute__((sda));
extern int D_L00_001B0CA4 __attribute__((sda));
extern float D_L00_001B0CAC __attribute__((sda));
extern float D_L00_001B0CB0 __attribute__((sda));
extern int D_L00_001B2C10[] MACRO_ADDR;
extern int update_timer SDATA(D_L00_001B2C10);
extern int D_L00_001B2C14[] MACRO_ADDR;
extern int update_collision SDATA(D_L00_001B2C14);
extern int D_L00_001B2C18[] MACRO_ADDR;
extern int update_water SDATA(D_L00_001B2C18);
extern int D_L00_001B2C28[] MACRO_ADDR;
extern int update_handle SDATA(D_L00_001B2C28);
extern char *D_L00_001ADB2C[] MACRO_ADDR;
extern float D_L00_00254650[][2];
extern void gravity_get_dir_at_object(void *, void *, int);
extern void moby_get_facing_direction(void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern void vec_scale_to_length(void *, void *, float);
extern void ForceClaimNotice(int, int, int);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern void func_PAL_0029C0F0(int, void (*)(void *));
extern void hud_draw_timer_b(void *);
extern void ref_L00_003FFBA0_00(void);
extern void object_set_root_data_active(void);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void func_PAL_0026F5B8(int, int);
extern void part_setup_object_effect_entry(void *, void *, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int PlayMobySound(int, int, void *);
extern void func_PAL_00331948(void *), moby_steer_heading_to_aim(void *), func_PAL_00331A48(void *);
extern void func_PAL_00332720(void *), snd_play_on_threshold_crossing(void);
extern int math_fast_float_d(void *);
extern int CollideSweptSphere(UpdateQuery *);
extern int weapon_get_group(int);
extern void vec_clear_128(void *);
extern float FastVecLength(void *);
extern char *func_PAL_0032F3B8(void *, void *, void *, float);
extern void QueueRadialMobyImpacts(void *);
extern void table_clear_entry_flag(int), slot_free(int), moby_mark_spawned(void *);
extern void copy_matrix_rotation(void *, void *), mat_get_euler_angles(void *, void *);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void euler_rotation_basis(void *, void *), func_PAL_00331118(void *);
extern void gfx_register_final_draw_callback(void (*)(void *), void *);
extern void func_PAL_003329A8(void *);
extern void part_queue_ground_shadow(void *, float);
#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define P(p, n) (*(char **)((char *)(p) + (n)))
#define STATE(p) (*(unsigned char *)((p) + 0x20))

/* Advances launch, grounded movement, falling and teardown states of a timed actor. */
void func_PAL_0033067C(char *obj)
{
    /* The query and attachment transform use the same workspace in separate phases. */
    struct {
        UpdateVec previous, ahead, behind;
        UpdateWorkspace workspace;
        UpdateVec rotation;
    } scratch;
    char *vars = P(obj, 0x68);
    int i, hit, action;
    float (*particles)[2];
    char *hero;

    if (STATE(obj) >= 2)
    gravity_get_dir_at_object(obj, D_L00_001B2C00, 1);
    else
    moby_get_facing_direction(obj + 0x10, D_L00_001B2C00);
    FastVecScale(D_L00_001B2C00, D_L00_001B2C00, -1.0f);
    FastVecScale(&scratch.ahead, obj + 0xE0, D_L00_001B0CAC);
    FastVecAdd(&scratch.ahead, obj + 0x10, &scratch.ahead);
    FastVecScale(&scratch.behind, obj + 0xE0, -1.0f);
    FastVecAdd(&scratch.behind, obj + 0x10, &scratch.behind);
    if (CollLine(&scratch.ahead, &scratch.behind, 2, obj, 0)) {
        if (GetCollHitMaterial() == 2) {
            FastVecScale(D_L00_001B2C00, D_L00_001BF240, 0.0009765625f);
            vec_scale_to_length(D_L00_001B2C00, D_L00_001B2C00, -1.0f);
            D_L00_001B2C14[0] = 1;
        } else {
            update_collision = 0;
        }
        if (GetCollHitMaterial() == 6)
        update_water = 1;
        else
        update_water = 0;
    } else {
        update_collision = 0;
        D_L00_001B2C18[0] = 0;
    }
    ForceClaimNotice(6, 0, 1);
    switch (STATE(obj)) {
    case 0:
        STATE(obj) = 1;
        I(vars, 0x58) = 0;
        F(obj, 0x2C) = 0.00025f;
        I(obj, 0x98) = 0;
        particles = D_L00_00254650;
        for (i = 97; i >= 0; i--) {
            (*particles)[0] = math_random_angle();
            (*particles)[1] = math_random_signed_float_range(720.0f, 2160.0f) * 0.0003490659f;
            particles++;
        }
        update_timer = 1500;
        if (D_L00_001A904C[0])
            func_PAL_0029C0F0(0, hud_draw_timer_b);
        /* fall through */
    case 1:
        hero = g_hero_state;
        action = I(hero, 0x2294);
        if (action == 98 || D_L00_001A8F00 == 2 || action == 111 || action == 100 ||
            action == 99 || action == 23 || action == 24 || action == 129 || action == 39) {
            ref_L00_003FFBA0_00();
            STATE(obj) = 7;
            object_set_root_data_active();
            I(vars, 0x60) = 0;
            break;
        }
        F(obj, 0x2C) += 0.01f;
        if (F(obj, 0x2C) > 0.023f)
            F(obj, 0x2C) = 0.023f;
        qcopy(&scratch.previous, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        part_steer_effect_direction(D_L00_001B2C28[0], vars, 0);
        vec_transform_or_copy(obj + 0x10, obj + 0x10);
        shop_trigger_current_state_effect(vars, vars);
        vec_add_object_direction_scaled(obj + 0x10, vars, 0.0044f);
        if (CollLine(&scratch.previous, obj + 0x10, 0, obj, 0)) {
            UpdateCollision *collision = &g_collision_result;
            char *other = collision->hit;
            if (other && (other == P(hero, 0x2290) || *(short *)(other + 0xAA) == 0x907))
                break;
            qcopy(obj + 0x10, &collision->point);
            ForceClaimNotice(6, 0, 1);
            func_PAL_0026F5B8(28, 1);
            part_setup_object_effect_entry(obj + 0x10, obj + 0xF0, obj);
            STATE(obj) = 2;
            func_PAL_002A7E68(obj, 1, 0, 10);
            I(obj, 0x48) = 0;
        }
        break;
    case 2:
        STATE(obj) = 3;
        PlayMobySound(2, 0, obj);
        if (D_0018C0B4 != 28 || D_L00_001A8F00 == 2) {
            ref_L00_003FFBA0_00();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 3:
        func_PAL_00331948(obj);
        moby_steer_heading_to_aim(obj);
        func_PAL_00331A48(obj);
        func_PAL_00332720(obj);
        snd_play_on_threshold_crossing();
        if (math_fast_float_d(D_L00_001B2C10)) {
            STATE(obj) = 9;
            I(vars, 0x60) = 8;
        }
        if (D_00138324 & 32) {
            STATE(obj) = 9;
            I(vars, 0x60) = 8;
        }
        if (D_0018C0B4 != 28 || D_L00_001A8F00 == 2) {
            ref_L00_003FFBA0_00();
            STATE(obj) = 9;
            I(vars, 0x60) = 0;
        }
        break;
    case 4:
        qcopy(&scratch.previous, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        vec_add_object_direction_scaled(obj + 0x10, vars, 0.0088f);
        vec_transform_or_copy(obj + 0x10, obj + 0x10);
        shop_trigger_current_state_effect(vars, vars);
        qcopy(&scratch.workspace.query.start, &scratch.previous);
        qcopy(&scratch.workspace.query.end, obj + 0x10);
        qcopy(&scratch.workspace.query.velocity, vars);
        scratch.workspace.query.radius = 0.2f;
        scratch.workspace.query.friction = 0.85f;
        scratch.workspace.query.bounce = 0.75f;
        scratch.workspace.query.response = 1;
        scratch.workspace.query.object = obj;
        scratch.workspace.query.ignore = 0;
        scratch.workspace.query.ignoreCount = 0;
        scratch.workspace.query.flags = 0;
        scratch.workspace.query.mask = 0;
        scratch.workspace.query.gravity = 0;
        hit = CollideSweptSphere(&scratch.workspace.query);
        qcopy(obj + 0x10, &scratch.workspace.query.end);
        qcopy(vars, &scratch.workspace.query.velocity);
        if (hit == 2) {
            if (weapon_get_group(scratch.workspace.query.surface) || scratch.workspace.query.surface == 12) {
                STATE(obj) = 9;
                I(vars, 0x60) = 8;
            } else {
                STATE(obj) = 2;
                vec_clear_128(vars);
            }
        } else if (FastVecLength(vars) > 0.4f) {
            STATE(obj) = 9;
            I(vars, 0x60) = 8;
        }
        break;
    case 9:
        STATE(obj) = 5;
        object_set_root_data_active();
        /* fall through */
    case 5:
        if (math_fast_float_d(vars + 0x60)) {
            PlayMobySound(1, 0, obj);
            vec_scale_to_length(&scratch.rotation, obj + 0xC0, 1.0f);
            func_PAL_0032F3B8(obj, obj + 0x10, &scratch.rotation, F(obj, 0x18));
            STATE(obj) = 6;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            if (D_0018C0B4 != 28 || D_L00_001A8F00 == 2) {
                ref_L00_003FFBA0_00();
                I(vars, 0x60) = 0;
            } else
                I(vars, 0x60) = ((s32)D_L00_001B0CA4 * 5 + 2) / 6;
            I(vars, 0x64) = 0;
        }
        break;
    case 6:
        QueueRadialMobyImpacts(obj);
        F(vars, 0x64) += D_L00_001B0C98 * 0.020000001f;
        if (math_fast_float_d(vars + 0x60) && !I(vars, 0x68))
            STATE(obj) = 8;
        break;
    case 7:
        if (math_fast_float_d(vars + 0x60))
            STATE(obj) = 8;
        break;
    case 8:
        if (D_0018C0B4 == 28)
            func_PAL_0026F5B8(0, 1);
        if (*(short *)(g_follow_camera_object + 0x86) == 27)
            ref_L00_003FFBA0_00();
        table_clear_entry_flag(update_handle);
        slot_free(I(vars, 0x6C));
        slot_free(I(vars, 0x70));
        slot_free(I(vars, 0x74));
        D_L00_001B0CA0 = 0;
        func_PAL_0029C0F0(0, 0);
        moby_mark_spawned(obj);
        return;
    }
    if (STATE(obj) >= 2 && D_L00_001ADB2C[0]) {
        copy_matrix_rotation(scratch.workspace.attachment.transform, obj + 0xC0);
        mat_get_euler_angles(scratch.workspace.attachment.transform, &scratch.workspace.attachment.angles);
        moby_transform_point_and_rotation_by_parent(obj, D_L00_001ADB2C[0], obj + 0x10,
                     &scratch.workspace.attachment.angles, obj + 0x10,
                     &scratch.workspace.attachment.adjusted);
        euler_rotation_basis(obj + 0xC0, &scratch.workspace.attachment.adjusted);
    }
    if ((unsigned int)(STATE(obj) - 2) < 2)
        func_PAL_00331118(obj);
    gfx_register_final_draw_callback(func_PAL_003329A8, obj);
    part_queue_ground_shadow(obj, D_L00_001B0CB0);
}
