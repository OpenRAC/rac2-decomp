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
extern int g_miniturret_counter __attribute__((sda));
extern float g_miniturret_move_speed __attribute__((sda));
extern float g_miniturret_query_response __attribute__((sda));
extern void *g_ripple_param_a __attribute__((sda));
extern int g_ripple_param_b[] __attribute__((sda));
extern unsigned char *g_miniturret_l03_owner_table[] __attribute__((sda));
typedef struct { int row0[64]; int row1[64]; int row2[8]; int count; int flag; int limit; } ProjectilePool;
extern ProjectilePool g_miniturret_projectile_pool __attribute__((nosda));
extern unsigned char *g_miniturret_l03_owner_table_2[] __attribute__((nosda));
extern ProjectileOffset g_miniturret_projectile_offsets[] __attribute__((nosda));
extern unsigned char g_hero_l03_state_block[] __attribute__((nosda));
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
extern void projectile_cleanup_table(void);
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
extern void func_PAL_00305D30(void *);
extern void func_PAL_00305DC8(void *);
extern void part_spawn_explosion_with_sparks_pal(float, float, void *, void *, int);
extern void slot_free(int);
extern void slot_list_remove(void *, int);
extern void moby_mark_spawned(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_advance_grow_effect(void *);
extern int vec_fast_helper_b(void *);
extern int math_fast_float_d(void *);
extern void UpdateOwnedParticleTrails(void *);
extern void projectile_check_hit_break(void *);
extern void moby_follow_attached_motion(void *);
typedef void (*ProjectileDrawCallback)(void *);
extern void gfx_register_overlay_draw_callback(ProjectileDrawCallback, void *);
extern void projectile_draw_effects(void *);
#define PI(p,o) (*(int *)((p)+(o)))
#define PF(p,o) (*(float *)((p)+(o)))
#define PP(p,o) (*(unsigned char **)((p)+(o)))

void func_PAL_00305470(unsigned char *object) {
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
        { int counter = g_miniturret_counter;
        PI(state, 0x6C) = counter;
        g_miniturret_counter = (counter + 1) % 100; }
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
        vec_add_object_direction_scaled(g_miniturret_move_speed * 0.00040000002f, object + 0x10, state);
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
        query.response = g_miniturret_query_response;
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
                        RippleDisturb(g_ripple_param_a, g_ripple_param_b[0], 1, PF(object, 0x10), PF(object, 0x14), 0.5f, -0.35f);
                        created = moby_spawn_scaled_effect(2.0f, object + 0x10);
                        if (created)
                            created[0x23] = 0x70;
                    }
                } else if (response == 1) {
                    object[0x20] = 8;
                } else {
                    state[0x4E] = slot_list_add(&g_miniturret_projectile_pool, object);
                    projectile_cleanup_table();
                    if (g_miniturret_projectile_pool.row1[(signed char)state[0x4E]]) {
                        object[0x20] = 2;
                        PlayMobySound(1, 0, object);
                        anim_start_blended_with_flags(object, 1, 0, 0, 0);
                    } else {
                        object[0x20] = 6;
                    }
                }
                table_clear_entry_flag((signed char)state[0x4F]);
                { unsigned char *owner = g_miniturret_l03_owner_table[0];
                g_miniturret_l03_owner_table_2[PI(state, 0x6C)] = owner;
                if (owner) {
                    FastVecSub(&relative, object + 0x10, owner + 0x10);
                    matrix_from_basis_rows(inverse, g_miniturret_l03_owner_table_2[PI(state, 0x6C)] + 0xC0);
                    transform_vector(&relative, &relative, inverse);
                    { int entry = PI(state, 0x6C) * 12;
                    entry += (int)g_miniturret_projectile_offsets;
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
        if (g_miniturret_projectile_pool.row1[(signed char)state[0x4E]]) {
            object[0x20] = 2;
            PlayMobySound(1, 0, object);
            anim_start_blended_with_flags(object, 1, 0, 0, 0);
            PI(state, 0x48) = slot_alloc_for_object(object, 0);
        }
        break;
    case 7:
        func_PAL_00305D30(object);
        func_PAL_00305DC8(object);
        break;
    case 8:
        PlayMobySound(3, 0, object);
        part_spawn_explosion_with_sparks_pal(0.5f, 13.0f, object, object + 0x10, -1);
        object[0x20] = 9;
        *(unsigned short *)(object + 0x34) |= 0x41;
        break;
    case 9:
        if (!PI(state, 0x64)) {
            if (PI(state, 0x48) != -1)
                slot_free(PI(state, 0x48));
            if ((signed char)state[0x4E] != -1)
                slot_list_remove(&g_miniturret_projectile_pool, (signed char)state[0x4E]);
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if (object[0x20] >= 2 && g_miniturret_l03_owner_table_2[PI(state, 0x6C)]) {
        index = PI(state, 0x6C);
        { int entry = index * 12;
        entry += (int)g_miniturret_projectile_offsets;
        normal.v.x = ((ProjectileOffset *)entry)->x;
        normal.v.y = ((ProjectileOffset *)entry)->y;
        normal.v.z = ((ProjectileOffset *)entry)->z; }
        normal.v.w = 0;
        matrix_mul_vec3(&normal, &normal, g_miniturret_l03_owner_table_2[PI(state, 0x6C)] + 0xC0);
        FastVecAdd(object + 0x10, g_miniturret_l03_owner_table_2[PI(state, 0x6C)] + 0x10, &normal);
    }
    if ((unsigned int)(object[0x20] - 3) < 2)
        part_advance_grow_effect(object);
    vec_fast_helper_b(state + 0x5C);
    if ((math_fast_float_d(state + 0x40) || PI(g_hero_l03_state_block, 0x2294) == 0x6F) && object[0x20] != 9)
        object[0x20] = 8;
    UpdateOwnedParticleTrails(object);
    if ((unsigned int)(object[0x20] - 3) < 2) {
        projectile_check_hit_break(object);
        if (!g_miniturret_projectile_pool.row1[(signed char)state[0x4E]]) {
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
        moby_follow_attached_motion(object);
    gfx_register_overlay_draw_callback(projectile_draw_effects, object);
}
