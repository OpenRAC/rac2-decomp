#include "include_asm.h"

#include "common.h"
typedef int ProjectileQuad __attribute__((mode(TI)));
typedef union { ProjectileQuad quad; struct { float x, y, z, w; } v; } ProjectileVector;
typedef struct { float x, y, z; } ProjectileOffset;
typedef struct {
    ProjectileVector previous, position, velocity;
    unsigned char *hitObject;
    int *excluded;
    int mode;
    float radius, response, friction;
    int flags0, flags1, enabled, surface, active;
    float tolerance;
} ProjectileQuery;
extern int D_L03_001AEFCC __attribute__((sda));
extern float D_L03_001AEFB0 __attribute__((sda));
extern float D_L03_001AEFB8 __attribute__((sda));
extern void *D_L03_001B31B0 __attribute__((sda));
extern int D_L03_001B31B8[] __attribute__((sda));
extern unsigned char *D_L03_001ADAAC[] __attribute__((sda));
typedef struct { int row0[64]; int row1[64]; int row2[8]; int count; int flag; int limit; } ProjectilePool;
extern ProjectilePool D_L03_0023B300 __attribute__((nosda));
extern unsigned char *D_L03_0023B530[] __attribute__((nosda));
extern ProjectileOffset D_L03_0023B6C0[] __attribute__((nosda));
extern unsigned char D_L03_00189E20[] __attribute__((nosda));
extern void moby_get_facing_direction(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_add_object_direction_scaled(float, void *, void *);
extern void vec_transform_or_copy(void *, void *);
extern int CollideSweptSphere(ProjectileQuery *);
extern int weapon_get_group(int);
extern void RippleDisturb(void *, int, int, float, float, float, float);
extern unsigned char *moby_spawn_scaled_effect(float, void *);
extern signed char slot_list_add(void *, void *);
extern void state_l00_apply_shared_reset_words(void);
extern int PlayMobySound(int, int, void *);
extern void anim_start_blended_with_flags(void *, int, int, int, int);
extern void table_clear_entry_flag(int);
extern void FastVecSub(void *, void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern float moby_get_anim_value(void *);
extern void projectile_launch_at_target(void *);
extern void miniturret_aim_at_target(void *);
extern void func_PAL_003062B8(void *);
extern signed char part_alloc_effect_slot(float, float, float, void *, int);
extern int slot_alloc_for_object(void *, int);
extern void func_PAL_L00_0038A370(void *);
extern void func_PAL_L00_0038A408(void *);
extern void func_PAL_002AD288(float, float, void *, void *, int);
extern void slot_free(int);
extern void slot_list_remove(void *, int);
extern void moby_mark_spawned(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void moby_l00_advance_child_blend(void *);
extern int vec_fast_helper_b(void *);
extern int math_fast_float_d(void *);
extern void UpdateOwnedParticleTrails(void *);
extern void projectile_check_hit_break(void *);
extern void moby_l00_follow_source_position(void *);
typedef void (*ProjectileDrawCallback)(void *);
extern void gfx_add_draw_callback_third(ProjectileDrawCallback, void *);
extern void projectile_draw_effects(void *);
#define PI(p,o) (*(int *)((p)+(o)))
#define PF(p,o) (*(float *)((p)+(o)))
#define PP(p,o) (*(unsigned char **)((p)+(o)))

void func_PAL_L03_0038EE08(unsigned char *object) {
    unsigned char *state = PP(object, 0x68);
    unsigned char *attached, *created;
    ProjectileVector oldPosition;
    int excluded[2];
    ProjectileVector normal, forward, quaternion, cross;
    float matrix[12];
    ProjectileQuery query;
    ProjectileVector relative;
    float inverse[16];
    float halfAngle;
    int collision, response, index;
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        { int counter = D_L03_001AEFCC;
        PI(state, 0x6C) = counter;
        D_L03_001AEFCC = (counter + 1) % 100; }
        PI(object, 0x98) = 0;
    case 1:
        moby_get_facing_direction(object + 0x10, &normal);
        vec_scale_to_length(&forward, object + 0xE0, 1.0f);
        FastVecCross(&cross, &forward, &normal);
        halfAngle = FastVecDot(&forward, &normal) * 0.5f;
        FastVecScale(&quaternion, &cross, math_fast_sin_or_cos_b(halfAngle));
        quaternion.v.w = math_fast_sin_or_cos_a(halfAngle);
        quaternion_to_rotation_basis(&quaternion, matrix);
        multiply_matrix3x3(object + 0xC0, matrix, object + 0xC0);
        qcopy(&oldPosition, object + 0x10);
        FastVecAdd(object + 0x10, object + 0x10, state);
        part_steer_effect_direction((signed char)state[0x4F], state, 0);
        vec_add_object_direction_scaled(D_L03_001AEFB0 * 0.00040000002f, object + 0x10, state);
        vec_transform_or_copy(object + 0x10, object + 0x10);
        excluded[0] = 0;
        excluded[1] = 0xC5A;
        qcopy(&query.previous, &oldPosition);
        qcopy(&query.position, object + 0x10);
        qcopy(&query.velocity, state);
        query.hitObject = object;
        query.excluded = excluded;
        query.mode = 2;
        query.radius = 0.1f;
        query.response = D_L03_001AEFB8;
        query.friction = 0.5555555820465088f;
        query.flags0 = 0;
        query.flags1 = 0;
        query.tolerance = 0.07400000095367432f;
        query.active = 1;
        query.enabled = 1;
        collision = CollideSweptSphere(&query);
        qcopy(object + 0x10, &query.position);
        qcopy(state, &query.velocity);
        if (collision == 2) {
            unsigned char *hit = query.hitObject;
            if (!hit || (*(short *)(hit + 0xAA) != 0xCB &&
                *(short *)(hit + 0xAA) != 0x1366 && *(short *)(hit + 0xAA) != 0x1367)) {
                qzero_nc(state);
                PP(state, 0x70) = hit;
                if (hit) {
                    PF(state, 0x74) = PF(hit, 0x10);
                    PF(state, 0x78) = PF(hit, 0x14);
                    PF(state, 0x7C) = PF(hit, 0x18);
                }
                response = weapon_get_group(query.surface);
                if (response == 2) {
                    PF(state, 8) = -0.030000001f;
                    object[0x20] = 7;
                    if (!query.surface) {
                        RippleDisturb(D_L03_001B31B0, D_L03_001B31B8[0], 1, PF(object, 0x10), PF(object, 0x14), 0.5f, -0.35f);
                        created = moby_spawn_scaled_effect(2.0f, object + 0x10);
                        if (created)
                            created[0x23] = 0x70;
                    }
                } else if (response == 1) {
                    object[0x20] = 8;
                } else {
                    state[0x4E] = slot_list_add(&D_L03_0023B300, object);
                    state_l00_apply_shared_reset_words();
                    if (D_L03_0023B300.row1[(signed char)state[0x4E]]) {
                        object[0x20] = 2;
                        PlayMobySound(1, 0, object);
                        anim_start_blended_with_flags(object, 1, 0, 0, 0);
                    } else {
                        object[0x20] = 6;
                    }
                }
                table_clear_entry_flag((signed char)state[0x4F]);
                { unsigned char *owner = D_L03_001ADAAC[0];
                D_L03_0023B530[PI(state, 0x6C)] = owner;
                if (owner) {
                    FastVecSub(&relative, object + 0x10, owner + 0x10);
                    matrix_from_basis_rows(inverse, D_L03_0023B530[PI(state, 0x6C)] + 0xC0);
                    transform_vector(&relative, &relative, inverse);
                    { int entry = PI(state, 0x6C) * 12;
                    entry += (int)D_L03_0023B6C0;
                    ((ProjectileOffset *)entry)->x = relative.v.x;
                    ((ProjectileOffset *)entry)->y = relative.v.y;
                    ((ProjectileOffset *)entry)->z = relative.v.z; }
                } }
                PI(object, 0x98) = PI(PP(object, 0x24), 0x10);
            } else {
                FastVecScale(state, state, 1.1f);
            }
        }
        break;
    case 2:
        if (moby_get_anim_value(object) >= 6.0f) {
            anim_start_blended_with_flags(object, 2, 0, 0, 0);
            object[0x20] = 3;
        }
        break;
    case 3:
        projectile_launch_at_target(object);
        goto checkAttached;
    case 4:
        miniturret_aim_at_target(object);
        func_PAL_003062B8(object);
checkAttached:
        attached = PP(state, 0x70);
        if (attached) {
            if (attached[0x20] != 0xFE) {
                if (attached[0x20] != 0xFD)
                    break;
            }
            PI(object, 0x98) = 0;
            state[0x4F] = part_alloc_effect_slot(1.0f, 1.0f, 1.0f, object, 0);
            object[0x20] = 1;
            PP(state, 0x70) = 0;
        }
        break;
    case 5:
        if (moby_get_anim_value(object) <= 1.0f) {
            anim_start_blended_with_flags(object, 0, 0, 0, 0);
            PF(object, 0x48) = 1.0f;
            object[0x20] = 6;
        }
        break;
    case 6:
        if (D_L03_0023B300.row1[(signed char)state[0x4E]]) {
            object[0x20] = 2;
            PlayMobySound(1, 0, object);
            anim_start_blended_with_flags(object, 1, 0, 0, 0);
            PI(state, 0x48) = slot_alloc_for_object(object, 0);
        }
        break;
    case 7:
        func_PAL_L00_0038A370(object);
        func_PAL_L00_0038A408(object);
        break;
    case 8:
        PlayMobySound(3, 0, object);
        func_PAL_002AD288(0.5f, 13.0f, object, object + 0x10, -1);
        object[0x20] = 9;
        *(unsigned short *)(object + 0x34) |= 0x41;
        break;
    case 9:
        if (!PI(state, 0x64)) {
            if (PI(state, 0x48) != -1)
                slot_free(PI(state, 0x48));
            if ((signed char)state[0x4E] != -1)
                slot_list_remove(&D_L03_0023B300, (signed char)state[0x4E]);
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if (object[0x20] >= 2 && D_L03_0023B530[PI(state, 0x6C)]) {
        index = PI(state, 0x6C);
        { int entry = index * 12;
        entry += (int)D_L03_0023B6C0;
        normal.v.x = ((ProjectileOffset *)entry)->x;
        normal.v.y = ((ProjectileOffset *)entry)->y;
        normal.v.z = ((ProjectileOffset *)entry)->z; }
        normal.v.w = 0;
        matrix_mul_vec3(&normal, &normal, D_L03_0023B530[PI(state, 0x6C)] + 0xC0);
        FastVecAdd(object + 0x10, D_L03_0023B530[PI(state, 0x6C)] + 0x10, &normal);
    }
    if ((unsigned int)(object[0x20] - 3) < 2)
        moby_l00_advance_child_blend(object);
    vec_fast_helper_b(state + 0x5C);
    if ((math_fast_float_d(state + 0x40) || PI(D_L03_00189E20, 0x2294) == 0x6F) && object[0x20] != 9)
        object[0x20] = 8;
    UpdateOwnedParticleTrails(object);
    if ((unsigned int)(object[0x20] - 3) < 2) {
        projectile_check_hit_break(object);
        if (!D_L03_0023B300.row1[(signed char)state[0x4E]]) {
            anim_start_blended_with_flags(object, 1, 9, 0, 0);
            object[0x20] = 5;
            PF(object, 0x48) = -1.0f;
            slot_free(PI(state, 0x48));
            PI(state, 0x48) = -1;
            *(short *)(state + 0x4C) = 1;
            PI(state, 0x50) = 0;
            PI(state, 0x44) = 0;
            PI(state, 0x68) = 0;
            qcopy(state + 0x30, state + 0x10);
            qcopy(state + 0x20, state + 0x10);
        }
    }
    if (object[0x20] < 8 && PP(state, 0x70))
        moby_l00_follow_source_position(object);
    gfx_add_draw_callback_third(projectile_draw_effects, object);
}
