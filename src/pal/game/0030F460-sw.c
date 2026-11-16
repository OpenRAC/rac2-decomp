#include "include_asm.h"
/* func_PAL_0030F460, the PAL copy of func_0030E030: the same C, where 0.0030555557f becomes 0.0044f,
 * both func_002ACB48 0.5f become 0.6f, 0.02f becomes 0.024f and the func_002A7470 blend 10 becomes 8. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct {
    Vector previous, position, velocity;
    char *owner;
    int *ignore;
    int ignore_count;
    float radius, friction, bounce;
    int flags, mask, response, surface, gravity;
    float max_turn;
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
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern float math_random_float_range(float, float);
extern void moby_spring_away_from_player_game_pal(char *), moby_apply_hit_damage_game_pal(char *), table_clear_entry_flag(int), RemoveMobyFromIndexList(int, u16 *), moby_mark_spawned(void *);
extern void copy_matrix_rotation(void *, void *), mat_get_euler_angles(float *, float *), euler_rotation_basis(void *, void *);
/* Retail returns a boolean, despite a legacy caller declaring this helper void. */
extern int moby_transform_point_and_rotation_by_parent(int, int, void *, void *, void *, void *);
/* Steers a moving projectile, resolves its collision, then follows a struck moby. */
void projectile_update_pal(char *moby) {
    /* The 96-byte collision query and following attachment transform have
     * disjoint lifetimes and occupy the same measured stack workspace. */
    struct {
        Vector old_position, desired, forward, quaternion, axis;
        Vector rotation[3];
        int ignore[2];
        union {
            CollisionQuery query;
            struct { Vector transform[4], angles, adjusted; } attachment;
        } phase;
        Vector scatter;
    } scratch;
    char *state = *(char **)(moby + 0x68);
    ++*(int *)(state + 0x3C);
    switch (((u8 *)moby)[0x20]) {
    case 0:
        moby[0x20] = 1;
        if (((u8 *)moby)[0x43]) anim_start_blended(moby, 0, 0, 0);
        *(int *)(moby + 0x98) = 0;
        /* fall through */
    case 1: {
        int collision;
        char *hit;
        float half_angle;
        short type;
        moby_get_facing_direction(moby + 0x10, scratch.desired.f);
        vec_scale_to_length(&scratch.forward, moby + 0xE0, 1.0f);
        FastVecCross(&scratch.axis, &scratch.forward, &scratch.desired);
        half_angle = FastVecDot(&scratch.forward, &scratch.desired) * 0.5f;
        FastVecScale(&scratch.quaternion, &scratch.axis, math_fast_sin_or_cos_b(half_angle));
        scratch.quaternion.f[3] = math_fast_sin_or_cos_a(half_angle);
        quaternion_to_rotation_basis(&scratch.quaternion, scratch.rotation);
        multiply_matrix3x3(moby + 0xC0, scratch.rotation, moby + 0xC0);
        qcopy(&scratch.old_position, (moby + 0x10));
        FastVecAdd(moby + 0x10, moby + 0x10, state + 0x10);
        part_steer_effect_direction(*(int *)(state + 0x20), state + 0x10, 0);
        vec_add_object_direction_scaled(moby + 0x10, (float *)(state + 0x10), 0.0044f);
        vec_transform_or_copy(moby + 0x10, moby + 0x10);
        shop_trigger_current_state_effect((int)(state + 0x10), (int)(state + 0x10));
        scratch.ignore[0] = 0; scratch.ignore[1] = 0x232;
        qcopy(&scratch.phase.query.previous, &scratch.old_position);
        qcopy(&scratch.phase.query.position, (moby + 0x10));
        qcopy(&scratch.phase.query.velocity, (state + 0x10));
        scratch.phase.query.owner = moby; scratch.phase.query.ignore = scratch.ignore; scratch.phase.query.ignore_count = 2;
        scratch.phase.query.radius = 0.2f; scratch.phase.query.friction = 0.45f; scratch.phase.query.bounce = 0.5555556f;
        scratch.phase.query.flags = 0; scratch.phase.query.mask = 0; scratch.phase.query.gravity = 1; scratch.phase.query.response = 1; scratch.phase.query.max_turn = 0.174f;
        collision = CollideSweptSphere(&scratch.phase.query);
        qcopy((moby + 0x10), &scratch.phase.query.position);
        qcopy((state + 0x10), &scratch.phase.query.velocity);
        if (g_hero_effect_inhibit && *(float *)(moby + 0x18) < 462.43f) {
            vec_add_random_offset(scratch.scatter.f, 0.6f);
            SpawnExplosionEffects_pal(moby, &scratch.scatter, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            moby[0x20] = 6;
        }
        if (collision != 2) break;
        hit = scratch.phase.query.owner;
        if (hit) {
            type = *(short *)(hit + 0xAA);
            if (type == 0xCB || type == 0x1366 || type == 0x1367) goto accelerate;
            *(char **)(state + 0x38) = hit;
        }
        {
            FastVecScale(&scratch.desired, &g_coll_hit_normal, 0.0009765625f);
            vec_scale_to_length(&scratch.desired, &scratch.desired, 1);
            vec_scale_to_length(&scratch.forward, moby + 0xE0, 1);
            FastVecCross(&scratch.axis, &scratch.forward, &scratch.desired);
            half_angle = FastVecDot(&scratch.forward, &scratch.desired) * 0.5f;
            FastVecScale(&scratch.quaternion, &scratch.axis, math_fast_sin_or_cos_b(half_angle));
            scratch.quaternion.f[3] = math_fast_sin_or_cos_a(half_angle);
            quaternion_to_rotation_basis(&scratch.quaternion, scratch.rotation);
            multiply_matrix3x3(moby + 0xC0, scratch.rotation, moby + 0xC0);
            moby[0x20] = collision;
            if (((u8 *)moby)[0x43] != 1) anim_start_blended(moby, 1, 0, 8);
            *(int *)(moby + 0x98) = *(int *)(*(char **)(moby + 0x24) + 0x10);
        }
        goto response_done;
accelerate:
        FastVecScale(state + 0x10, state + 0x10, 1.1f);
response_done:
        if (weapon_get_group(scratch.phase.query.surface)) {
            vec_add_random_offset(scratch.scatter.f, 0.6f);
            SpawnExplosionEffects_pal(moby, &scratch.scatter, 0, 0.0f, 0.0f, 0, 0, 0,
                         4.0f, 3.0f, 9.0f, 1.0f, 2, 12.0f, 1, 1, -1, 0, 0x810001);
            moby[0x20] = 6;
        }
        break;
    }
    case 2: moby[0x20] = 3; break;
    case 3:
        if (((u8 *)moby)[0x60] & 2) {
            if (((u8 *)moby)[0x43] != 2) anim_start_blended(moby, 2, 0, 8);
            *(float *)(moby + 0x48) = math_random_float_range(0.7f, 1.05f);
        }
        moby_spring_away_from_player_game_pal(moby); moby_apply_hit_damage_game_pal(moby);
        break;
    case 5: moby[0x20] = 4; break;
    case 4:
        *(float *)(moby + 0x2C) -= *(float *)(moby + 0x2C) * 0.024f;
        if (*(float *)(moby + 0x2C) < *(float *)(*(char **)(moby + 0x24) + 0x24) * 0.1f) moby[0x20] = 6;
        break;
    case 6:
        table_clear_entry_flag(*(int *)(state + 0x20));
        if (!*(int *)(state + 0x40)) RemoveMobyFromIndexList((int)moby, g_projectile_moby_index_list);
        moby_mark_spawned(moby);
        return;
    }
    if ((u32)(((u8 *)moby)[0x20] - 2) < 3 && *(char **)(state + 0x38)) {
        copy_matrix_rotation(scratch.phase.attachment.transform, moby + 0xC0);
        mat_get_euler_angles((float *)scratch.phase.attachment.transform, scratch.phase.attachment.angles.f);
        if (moby_transform_point_and_rotation_by_parent((int)moby, *(int *)(state + 0x38), moby + 0x10, &scratch.phase.attachment.angles, moby + 0x10, &scratch.phase.attachment.adjusted))
            euler_rotation_basis(moby + 0xC0, &scratch.phase.attachment.adjusted);
    }
}
