#include "include_asm.h"
/* func_0030E030: per-frame update of the actor (boot copy of func_L00_00398150) and its state block. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector previous, position, velocity;
    char *owner;
    int *ignore;
    int ignoreCount;
    float radius, friction, bounce;
    int flags, mask, response, surface, gravity;
    float maxTurn;
} CollisionQuery;
extern int g_hero_effect_inhibit MACRO_ADDR;
extern Vector g_coll_hit_normal;
extern u16 g_projectile_moby_index_list[] MACRO_ADDR;
extern void anim_start_blended(char *, int, int, int), moby_get_facing_direction(void *, float *);
extern void vec_scale_to_length(void *, void *, float), FastVecCross(void *, void *, void *);
extern float FastVecDot(void *, void *), math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *, void *, float), quaternion_to_rotation_basis(void *, void *), multiply_matrix3x3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *), part_steer_effect_direction(int, void *, void *), vec_add_object_direction_scaled(void *, float *, float);
extern void vec_transform_or_copy(void *, void *), shop_trigger_current_state_effect(int, int);
extern int CollideSweptSphere(CollisionQuery *), weapon_get_group(int);
extern void vec_add_random_offset(float *, float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern float math_random_float_range(float, float);
extern void moby_spring_away_from_player(char *), moby_apply_hit_damage(char *), table_clear_entry_flag(int), RemoveMobyFromIndexList(int, u16 *), moby_mark_spawned(void *);
extern void copy_matrix_rotation(void *, void *), mat_get_euler_angles(float *, float *), euler_rotation_basis(void *, void *);
/* Retail returns a boolean, despite a legacy caller declaring this helper void. */
extern int moby_transform_point_and_rotation_by_parent(int, int, void *, void *, void *, void *);
/* Steers a moving projectile, resolves its collision, then follows a struck actor. */
void projectile_update(char *actor) {
    /* The 96-byte collision query and following attachment transform have
     * disjoint lifetimes and occupy the same measured stack workspace. */
    struct {
        Vector oldPosition, desired, forward, quaternion, axis;
        Vector rotation[3];
        int ignore[2];
        union {
            CollisionQuery query;
            struct { Vector transform[4], angles, adjusted; } attachment;
        } phase;
        Vector scatter;
    } scratch;
    char *vars = *(char **)(actor + 0x68);
    ++*(int *)(vars + 0x3C);
    switch (((u8 *)actor)[0x20]) {
    case 0:
        actor[0x20] = 1;
        if (((u8 *)actor)[0x43]) anim_start_blended(actor, 0, 0, 0);
        *(int *)(actor + 0x98) = 0;
        /* fall through */
    case 1: {
        int collision;
        char *hit;
        float halfAngle;
        short hit_class;
        moby_get_facing_direction(actor + 0x10, scratch.desired.f);
        vec_scale_to_length(&scratch.forward, actor + 0xE0, 1.0f);
        FastVecCross(&scratch.axis, &scratch.forward, &scratch.desired);
        halfAngle = FastVecDot(&scratch.forward, &scratch.desired) * 0.5f;
        FastVecScale(&scratch.quaternion, &scratch.axis, math_fast_sin_or_cos_b(halfAngle));
        scratch.quaternion.f[3] = math_fast_sin_or_cos_a(halfAngle);
        quaternion_to_rotation_basis(&scratch.quaternion, scratch.rotation);
        multiply_matrix3x3(actor + 0xC0, scratch.rotation, actor + 0xC0);
        qcopy(&scratch.oldPosition, (actor + 0x10));
        FastVecAdd(actor + 0x10, actor + 0x10, vars + 0x10);
        part_steer_effect_direction(*(int *)(vars + 0x20), vars + 0x10, 0);
        vec_add_object_direction_scaled(actor + 0x10, (float *)(vars + 0x10), 0.0030555557f);
        vec_transform_or_copy(actor + 0x10, actor + 0x10);
        shop_trigger_current_state_effect((int)(vars + 0x10), (int)(vars + 0x10));
        scratch.ignore[0] = 0; scratch.ignore[1] = 0x232;
        qcopy(&scratch.phase.query.previous, &scratch.oldPosition);
        qcopy(&scratch.phase.query.position, (actor + 0x10));
        qcopy(&scratch.phase.query.velocity, (vars + 0x10));
        scratch.phase.query.owner = actor; scratch.phase.query.ignore = scratch.ignore; scratch.phase.query.ignoreCount = 2;
        scratch.phase.query.radius = 0.2f; scratch.phase.query.friction = 0.45f; scratch.phase.query.bounce = 0.5555556f;
        scratch.phase.query.flags = 0; scratch.phase.query.mask = 0; scratch.phase.query.gravity = 1; scratch.phase.query.response = 1; scratch.phase.query.maxTurn = 0.174f;
        collision = CollideSweptSphere(&scratch.phase.query);
        qcopy((actor + 0x10), &scratch.phase.query.position);
        qcopy((vars + 0x10), &scratch.phase.query.velocity);
        if (g_hero_effect_inhibit && *(float *)(actor + 0x18) < 462.43f) {
            vec_add_random_offset(scratch.scatter.f, 0.5f);
            SpawnExplosionEffects(actor, &scratch.scatter, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            actor[0x20] = 6;
        }
        if (collision != 2) break;
        hit = scratch.phase.query.owner;
        if (hit) {
            hit_class = *(short *)(hit + 0xAA);
            if (hit_class == MOBY_CLASS_DECOY || hit_class == MOBY_CLASS_MINITURRET || hit_class == MOBY_CLASS_MEGATURRET) goto accelerate;
            *(char **)(vars + 0x38) = hit;
        }
        {
            FastVecScale(&scratch.desired, &g_coll_hit_normal, 0.0009765625f);
            vec_scale_to_length(&scratch.desired, &scratch.desired, 1);
            vec_scale_to_length(&scratch.forward, actor + 0xE0, 1);
            FastVecCross(&scratch.axis, &scratch.forward, &scratch.desired);
            halfAngle = FastVecDot(&scratch.forward, &scratch.desired) * 0.5f;
            FastVecScale(&scratch.quaternion, &scratch.axis, math_fast_sin_or_cos_b(halfAngle));
            scratch.quaternion.f[3] = math_fast_sin_or_cos_a(halfAngle);
            quaternion_to_rotation_basis(&scratch.quaternion, scratch.rotation);
            multiply_matrix3x3(actor + 0xC0, scratch.rotation, actor + 0xC0);
            actor[0x20] = collision;
            if (((u8 *)actor)[0x43] != 1) anim_start_blended(actor, 1, 0, 10);
            *(int *)(actor + 0x98) = *(int *)(*(char **)(actor + 0x24) + 0x10);
        }
        goto response_done;
accelerate:
        FastVecScale(vars + 0x10, vars + 0x10, 1.1f);
response_done:
        if (weapon_get_group(scratch.phase.query.surface)) {
            vec_add_random_offset(scratch.scatter.f, 0.5f);
            SpawnExplosionEffects(actor, &scratch.scatter, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            actor[0x20] = 6;
        }
        break;
    }
    case 2: actor[0x20] = 3; break;
    case 3:
        if (((u8 *)actor)[0x60] & 2) {
            if (((u8 *)actor)[0x43] != 2) anim_start_blended(actor, 2, 0, 10);
            *(float *)(actor + 0x48) = math_random_float_range(0.7f, 1.05f);
        }
        moby_spring_away_from_player(actor); moby_apply_hit_damage(actor);
        break;
    case 5: actor[0x20] = 4; break;
    case 4:
        *(float *)(actor + 0x2C) -= *(float *)(actor + 0x2C) * 0.02f;
        if (*(float *)(actor + 0x2C) < *(float *)(*(char **)(actor + 0x24) + 0x24) * 0.1f) actor[0x20] = 6;
        break;
    case 6:
        table_clear_entry_flag(*(int *)(vars + 0x20));
        if (!*(int *)(vars + 0x40)) RemoveMobyFromIndexList((int)actor, g_projectile_moby_index_list);
        moby_mark_spawned(actor);
        return;
    }
    if ((u32)(((u8 *)actor)[0x20] - 2) < 3 && *(char **)(vars + 0x38)) {
        copy_matrix_rotation(scratch.phase.attachment.transform, actor + 0xC0);
        mat_get_euler_angles((float *)scratch.phase.attachment.transform, scratch.phase.attachment.angles.f);
        if (moby_transform_point_and_rotation_by_parent((int)actor, *(int *)(vars + 0x38), actor + 0x10, &scratch.phase.attachment.angles, actor + 0x10, &scratch.phase.attachment.adjusted))
            euler_rotation_basis(actor + 0xC0, &scratch.phase.attachment.adjusted);
    }
}
