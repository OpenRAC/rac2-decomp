/* func_PAL_L00_0040E248, the PAL copy of func_L00_004096B0: the same C, where rename func_0032D758 becomes func_PAL_0032F0B8; rename func_0032C700 becomes func_PAL_L00_003FB330; wrap (D_L00_001B0FA0 - 1.0f) (({e}) * 1.2f). */
#include "common.h"

typedef int CollisionQuad __attribute__((mode(TI)));
typedef union { CollisionQuad q; float f[4]; } CollisionVector;
typedef struct { int ignored[3]; } CollisionShape;
/* The swept sphere func_002FE9D0 takes; src/game/002FC8D0.c names its fields. */
typedef struct {
    CollisionVector previous, position, velocity;
    char *moby;
    CollisionShape *ignored;
    int ignoredCount;
    float radius, bounce, minFacing;
    int pad48, collisionFlags, slideOnCreatures, surface, useOffset;
} CollisionQuery;
typedef struct {
    CollisionVector force;
    char *owner;
    int flags;
    unsigned char kind, enabled;
    short object_class;
    float strength;
    int count;
} CollisionImpact;
typedef union {
    struct { CollisionVector point, work, delta, difference, projection, perpendicular; } math;
    CollisionImpact impact;
} CollisionWorkspace;

extern CollisionShape g_sweep_collision_shape;
extern float g_sweep_bounce_factor __attribute__((sda));
extern float g_sweep_radius_a __attribute__((sda));
extern float g_sweep_radius_b __attribute__((sda));
extern float g_sweep_fade_a __attribute__((sda));
extern float g_sweep_fade_b __attribute__((sda));
extern int g_active_tether_object __attribute__((sda));
extern int g_hero_locked_flag, g_hero_action_blocked_flag;
extern char *g_hero_moby NOT_SDA;
extern char *g_area_hit_targets[];
extern unsigned char g_item_slot_to_record[];
typedef struct {
    char pad00[0x74];
    float strength;
    char pad78[0x68];
} CollisionWeaponInfo;
extern CollisionWeaponInfo g_weapon_l00_table[];

extern void cam_compute_view_direction(char *, char *, int);
extern void vec_transform_or_copy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_add_object_direction_scaled(void *, float *, float);
extern int CollideSweptSphere(CollisionQuery *);
extern int weapon_get_group(int);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern int coll_process_hit(void *, float, int, void *, int);
extern int moby_is_in_special_class_range(char *);
extern char *moby_get_private_value_0(void *);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float math_fabs(float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern int PlayMobySound(int, int, char *);
extern int FastDecTimer(void *);
extern void QueueMobyImpact(void *, CollisionImpact *);
extern int StartAttachedEffect_pal(void *, int, void *);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
extern void part_queue_ground_shadow(void *, float);

/* Resolve motion and contacts, select a nearby target, and apply the object's
 * impact response. The query and impact layouts reflect their measured fields. */
void func_PAL_L00_0040E248(char *object)
{
    CollisionVector direction, previous;
    CollisionShape shape[1];
    CollisionQuery query;
    CollisionWorkspace workspace;
    char *state = *(char **)(object + 0x68);
    char *position = object + 0x10;
    int contacts, contact_kind, triggered;
    float range, fade;

    cam_compute_view_direction(position, (char *)&direction, 1);
    vec_transform_or_copy(position, position);
    if (*(unsigned char *)(object + 0x20) == 0) {
        float sweep_radius, min_facing;

        qcopy(&previous, position);
        FastVecAdd(position, position, state);
        part_steer_effect_direction(*(int *)(state + 0x28), state, 0);
        vec_add_object_direction_scaled(position, (float *)state, 0.00584f);
        /* Set here rather than at its use: sched1 issues this constant right after the call, which
           leaves the %hi of the copy below in $v1 and the list pointer in $a1. */
        min_facing = 1.5f;
        shape[0] = g_sweep_collision_shape;
        sweep_radius = g_sweep_radius_a;
        if (*(int *)(state + 0x24) != 0)
            sweep_radius = g_sweep_radius_b;
        qcopy(&query.previous, &previous);
        qcopy(&query.position, position);
        qcopy(&query.velocity, state);
        query.radius = sweep_radius;
        query.ignored = shape;
        query.ignoredCount = 3;
        query.minFacing = min_facing;
        query.bounce = (((g_sweep_bounce_factor - 1.0f)) * 1.2f) + 1.0f;
        query.moby = object;
        query.pad48 = 0;
        query.collisionFlags = 0;
        query.useOffset = 0;
        contacts = CollideSweptSphere(&query);
        contact_kind = weapon_get_group(query.surface);
        qcopy(position, &query.position);
        qcopy(state, &query.velocity);
        vec_rotate_by_quaternion(object + 0xC0, object + 0xC0, state + 0x10);
        vec_rotate_by_quaternion(object + 0xD0, object + 0xD0, state + 0x10);
        vec_rotate_by_quaternion(object + 0xE0, object + 0xE0, state + 0x10);
        if (contacts > 0) {
            int count, i, best;
            count = coll_process_hit(position, 7.0f, 1, g_hero_moby, 0);
            if (count != 0) {
                float closest = 10000.0f;
                best = -1;
                for (i = 0; i < count; i++) {
                    char *target = g_area_hit_targets[i];
                    char *description;
                    if (*(unsigned char *)(target + 0x31) == 0 || moby_is_in_special_class_range(target) != 0)
                        continue;
                    description = moby_get_private_value_0(target);
                    if (description != 0 && !(*(float *)description <= 0.0f) && target != 0 &&
                        *(char **)(target + 0x24) != 0 &&
                        *(short *)(*(char **)(target + 0x24) + 0x46) == 5) {
                        float distance = fast_vec_dist(target + 0x10, object + 0x10);
                        if (distance < closest) {
                            closest = distance;
                            best = i;
                        }
                    }
                }
                if (best >= 0) {
                    char *target = g_area_hit_targets[best];
                    char *description = moby_get_private_value_0(target);
                    float length, projection;
                    qcopy(&workspace.math.point, target + 0x10);
                    if (g_hero_locked_flag != 0) {
                        FastVecScale(&workspace.math.work, target + 0xE0,
                                      *(float *)(description + 0x10));
                        FastVecAdd(&workspace.math.point, &workspace.math.point, &workspace.math.work);
                    } else
                        workspace.math.point.f[2] += *(float *)(description + 0x10);
                    projection = FastVecDot(&direction, state);
                    FastVecScale(&workspace.math.work, &direction, projection);
                    FastVecSub(&workspace.math.delta, state, &workspace.math.work);
                    length = FastVecLength(&workspace.math.delta);
                    if (length != 0.0f) {
                        FastVecSub(&workspace.math.difference, &workspace.math.point, object + 0x10);
                        projection = FastVecDot(&workspace.math.difference, &direction);
                        FastVecScale(&workspace.math.projection, &direction, projection);
                        FastVecSub(&workspace.math.perpendicular, &workspace.math.difference, &workspace.math.projection);
                        if (length < 0.080000006f)
                            length = 0.080000006f;
                        vec_scale_to_length(&workspace.math.perpendicular, &workspace.math.perpendicular, length);
                        FastVecAdd(state, &workspace.math.perpendicular, &workspace.math.work);
                    }
                }
            }
            qcopy(&workspace.math.point, state);
            workspace.math.point.f[2] = 0.0f;
            FastVecCross(&workspace.math.point, &workspace.math.point, &direction);
            vec_scale_to_length(&workspace.math.point, &workspace.math.point, 1.0f);
            range = math_random_signed_float_range(0.0f, 0.52359885f);
            if (math_fabs(range) < 0.00001f) {
                math_build_axis_angle_quat(&workspace.math.work, &direction, range);
                vec_rotate_by_quaternion(&workspace.math.point, &workspace.math.point, &workspace.math.work);
            }
            range = math_random_float_range(0.062831864f, 0.12566373f);
            math_build_axis_angle_quat(state + 0x10, &workspace.math.point, range);
            PlayMobySound(0, 0, object);
        }
        workspace.impact.owner = object;
        workspace.impact.flags = 0x830000;
        workspace.impact.strength = (g_item_slot_to_record[0x25] + g_weapon_l00_table)->strength;
        workspace.impact.count = 1;
        qcopy(&workspace.impact.force, state);
        triggered = 0;
        vec_scale_to_length(&workspace.impact.force, &workspace.impact.force, 1.0f);
        workspace.impact.kind = 3;
        workspace.impact.force.f[3] = 5627.9248046875f;
        workspace.impact.enabled = 1;
        workspace.impact.object_class = *(short *)(object + 0xAA);
        range = *(int *)(state + 0x24) != 0 ? 8.0f : 2.0f;
        if (FastDecTimer(state + 0x20) != 0 ||
            (contacts > 0 && (unsigned int)(contact_kind - 1) <= 1)) {
            triggered = 1;
        } else {
            if (*(short *)(state + 0x22) == 0) {
                int count, i;
                count = coll_process_hit(object + 0x10, range, 1, g_hero_moby, 0);
                for (i = 0; i < count; i++) {
                    char *target = g_area_hit_targets[i];
                    char *description = moby_get_private_value_0(target);
                    int special = moby_is_in_special_class_range(target);
                    if (special != 0 || (description != 0 && *(float *)description > 0.0f &&
                                         *(short *)(description + 6) == 0)) {
                        QueueMobyImpact(target, &workspace.impact);
                        triggered = 1;
                        if (special == 0) {
                            if (*(int *)(state + 0x24) != 0)
                                StartAttachedEffect_pal(target, 0x4C, *(void **)(object + 0xB8));
                            else
                                StartAttachedEffect_pal(target, 0x25, *(void **)(object + 0xB8));
                        }
                        break;
                    }
                }
            } else {
                (*(short *)(state + 0x22))--;
                if (*(short *)(state + 0x22) < 0)
                    *(short *)(state + 0x22) = 0;
            }
        }
        if (triggered) {
            float blast_range;
            PlayMobySound(1, 0, object);
            blast_range = 0.6f;
            if (*(int *)(state + 0x24) != 0)
                blast_range = 2.4f;
            SpawnExplosion_pal(object + 0x10, 0, 6, 5, 6, 8, 10, 0, 0, 0, 0, g_active_tether_object,
                          blast_range, 20.0f);
            table_clear_entry_flag(*(int *)(state + 0x28));
            moby_mark_spawned(object);
            return;
        }
    }
    fade = g_sweep_fade_a;
    if (*(int *)(state + 0x24) != 0)
        fade = g_sweep_fade_b;
    if (g_hero_locked_flag == 0 && g_hero_action_blocked_flag == 0)
        part_queue_ground_shadow(object, fade);
}
