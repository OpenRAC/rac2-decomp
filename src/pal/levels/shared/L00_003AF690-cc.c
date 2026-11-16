#include "names.h"
/* func_PAL_L00_003AF690, the PAL copy of func_L00_003ABEC0: the same C, where rename func_L00_003ACA60 becomes func_PAL_L00_003B0230; rename func_0032D758 becomes func_PAL_0032F0B8; rename func_0032DA58 becomes func_PAL_0032F3B8; rename func_L00_003AC8E8 becomes func_PAL_L00_003B00B8. */
/* func_PAL_L00_003AF690 (retail begins at 0x003ABEC8 in level 00; the catalogue keeps the old name).
   Own unit, `-O2 -G0 -ffunction-sections -g`: -g gives the nop pair before each div.s, and
   D_L00_001B1FB0 uses the `.sdata` macro form so its `la` stays out of the bounds checks' slots.
   The out-of-arena test carries its own copy of the explosion code; jump2's cross-jumping
   later points those branches at the copy after the bounce block, so at sched2 the bounce
   join and the explosion are one block (retail's mov.s-first join and beqz slot). */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { char pad[0x18]; char *hit; int count; Vector point; char gap[0x10]; Vector normal; } Collision;
/* What the shot hands the collision test and its target: direction, owner and damage. */
typedef struct {
    Vector direction;
    char *owner;
    int flags;
    unsigned char kind;
    unsigned char one;
    unsigned short id;
    float damage;
    int count;
    int pad[3];
} ShotInfo;
typedef struct { char pad[4]; unsigned char piercing; char pad5[0x6B]; float damage; char tail[0x6C]; } Material;

extern Collision g_collision_result;
extern Vector g_projectile_offset_points[][4];
extern Material g_weapon_l00_table[];
extern unsigned short g_homing_moby_index_list[] MACRO_ADDR;
extern char g_camera_l00_position[];
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby;
extern char g_hero_position[];
extern int CollLine(void *, void *, int, void *, void *);
/* func_L00_002E6EF8 in most levels; the callee differs in levels 08, 09, 19 and 30. */
extern void ref_L00_003ABEC0_00(void *, void *);
extern int FastDecTimer(void *);
extern float math_fabs(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_angle_helper(float);
extern void moby_mark_spawned(void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void QueueMobyImpact(void *, void *);
extern char *moby_get_private_value_0(char *);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void RemoveMobyFromIndexList(void *, unsigned short *);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern int PlayMobySound(int, int, void *);
extern void table_clear_entry_flag(int);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void homing_shot_spawn_explosion_pal(char *, void *, char *);
extern void part_emit_shot_trail_pal(char *, void *);
extern void moby_transform_offset_to_world(char *, void *);
extern void shot_save_trail_transform(void);
extern int StartAttachedEffect_pal(void *, int, int);
extern char *part_spawn_blast_effect_moby_pal(char *, char *, void *, float);

/* A homing shot: follows its target (turning at most as far as its speed allows), records
   its path, tests the step for a hit and explodes on contact, out of the arena or too far
   from the hero. */
void homing_l00_shot_update_pal(char *object)
{
    Vector start;
    Vector forward;
    Vector aim;
    Vector step;
    Vector delta;
    Vector lead;
    Vector offset;
    union {
        struct { Vector axis; Vector side; Vector turn; } t;
        ShotInfo shot;
    } u;
    Vector up;
    Vector normal;
    char *state;
    char *target;
    char *info;
    char *owner;
    int locked;
    float distance, length, angle;
    unsigned char kind;
    Collision *hit;
    int bounce;

    owner = 0;
    state = *(char **)(object + 0x68);
    target = *(char **)(state + 0x10);
    qcopy(start, object + 0x10);
    cam_compute_view_direction(object + 0x10, forward, 1);
    if (target != 0) {
        info = moby_get_private_value_0(target);
        kind = *(unsigned char *)(target + 0x20);
        if (kind == 0xFE || (kind == 0xFD || (info != 0 && *(float *)info <= 0.0f))) {
            *(char **)(state + 0x10) = 0;
            target = 0;
        } else {
            qcopy(aim, target + 0x10);
            if (info != 0) {
                FastVecScale(step, target + 0xE0, *(float *)(info + 0x10));
                FastVecAdd(aim, aim, step);
            }
        }
    }
    locked = 0;
    if (target != 0 && *(short *)(state + 0x24) < 0x128 && *(signed char *)(target + 0x20) >= 0
        && *(unsigned char *)(state + 0x26) != 0) {
        step[0] = *(float *)(state + 0x0);
        step[1] = *(float *)(state + 0x4);
        step[2] = *(float *)(state + 0x8);
        step[3] = 0.0f;
        FastVecSub(delta, aim, step);
        distance = FastVecLength(delta);
        FastVecAdd(lead, aim, state + 0x40);
        FastVecSub(offset, object + 0x10, lead);
        length = FastVecLength(offset);
        if (length != 0.0f && distance != 0.0f) {
            angle = FastVecDot(offset, delta);
            angle = 1.5707964f - math_fast_angle_helper(angle / (length * distance));
            FastVecCross(u.t.axis, delta, offset);
            FastVecCross(u.t.side, delta, u.t.axis);
            if (FastVecDot(offset, u.t.side) < 0.0f) {
                angle = -angle;
            }
            length = distance / *(float *)(state + 0x18);
            angle = length * math_fast_sin_or_cos_b(angle);
            if (math_fabs(angle) > 100.0f) {
                angle = 0.0f;
            }
            while (angle > 1.0f) {
                angle -= 1.0f;
            }
            while (angle < -1.0f) {
                angle += 1.0f;
            }
            angle = math_fast_angle_helper(angle);
            FastVecScale(offset, offset, -1.0f);
            vec_scale_to_length(offset, offset, 1.0f);
            if (math_fabs(angle) > 1e-05f) {
                vec_scale_to_length(u.t.turn, u.t.axis, 1.0f);
                math_build_axis_angle_quat(u.t.turn, u.t.turn, angle);
                vec_rotate_by_quaternion(object + 0xC0, offset, u.t.turn);
                FastVecCross(object + 0xD0, object + 0xC0, forward);
                vec_scale_to_length(object + 0xD0, object + 0xD0, 1.0f);
                FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
                qcopy(state + 0x30, object + 0xC0);
            }
            if (fast_vec_dist(aim, object + 0x10) <= *(float *)(state + 0x18)
                && CollLine(object + 0x10, aim, 0x12, g_hero_moby, 0) == 0) {
                locked = 1;
                qcopy(g_collision_result.point, aim);
                g_collision_result.count = -1;
                g_collision_result.hit = target;
            }
        }
    } else {
        part_steer_effect_direction(*(int *)(state + 0x50), state + 0x30, 0);
        qcopy(object + 0xC0, state + 0x30);
        FastVecCross(object + 0xD0, object + 0xC0, forward);
        vec_scale_to_length(object + 0xD0, object + 0xD0, 1.0f);
        FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
    }

    if (target != 0) {
        *(float *)(state + 0x0) = aim[0];
        *(float *)(state + 0x4) = aim[1];
        *(float *)(state + 0x8) = aim[2];
    }
    *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
    FastVecScale(step, object + 0xC0, *(float *)(state + 0x18));
    FastVecAdd(object + 0x10, object + 0x10, step);
    vec_transform_or_copy(object + 0x10, object + 0x10);
    if (target != 0 && *(short *)(target + 0xAA) == 0xCEA) {
        FastVecSub(delta, aim, object + 0x10);
        if (FastVecDot(delta, object + 0xC0) < 0.0f) {
            *(char **)(state + 0x10) = 0;
            target = 0;
            locked = 0;
        }
    }
    if (*(float *)(object + 0x10) < 2.0f || *(float *)(object + 0x10) > 1021.0f
        || *(float *)(object + 0x14) < 2.0f || *(float *)(object + 0x14) > 1021.0f
        || *(float *)(object + 0x18) < 2.0f || *(float *)(object + 0x18) > 1021.0f) {
        RemoveMobyFromIndexList(object, g_homing_moby_index_list);
        table_clear_entry_flag(*(int *)(state + 0x50));
        moby_mark_spawned(object);
        return;
    }
    moby_transform_offset_to_world(object, delta);
    {
        Vector *trail = g_projectile_offset_points[*(int *)(state + 0x2C)];
        int k;

        for (k = 3; k > 0; k--) {
            qcopy(trail[k], trail[k - 1]);
        }
        qcopy(trail[0], delta);
    }
    if (++*(unsigned char *)(state + 0x27) >= 4) {
        ref_L00_003ABEC0_00(shot_save_trail_transform, object);
    }
    part_emit_shot_trail_pal(object, start);
    qcopy(lead, object + 0x10);
    FastVecScale(offset, forward, -0.25f);
    FastVecAdd(offset, object + 0x10, offset);
    if (CollLine(lead, offset, 2, 0, 0) != 0) {
        FastVecScale(lead, forward, 0.25f);
        FastVecAdd(object + 0x10, g_collision_result.point, lead);
    }
    u.shot.owner = object;
    u.shot.count = 1;
    u.shot.flags = 0x830000;
    {
        Material *material = &g_weapon_l00_table[g_item_slot_to_record[0x1B]];

        u.shot.damage = material->damage;
    }
    qcopy_nc(u.shot.direction, step);
    vec_scale_to_length(u.shot.direction, u.shot.direction, 1.5f);
    u.shot.direction[3] = 5627.9248f;
    u.shot.kind = 3;
    u.shot.one = 1;
    u.shot.id = *(unsigned short *)(object + 0xAA);
    if (locked == 0) {
        if (CollLine(start, object + 0x10, 0, g_hero_moby, &u.shot) == 0) {
            goto checked;
        }
    } else if (target != 0) {
        QueueMobyImpact(target, &u.shot);
    }
    hit = &g_collision_result;
    if (hit->hit != 0) {
        if (hit->hit != g_hero_moby) {
            if (hit->hit != *(char **)(state + 0xC)) {
                *(unsigned char *)(object + 0xBC) = 2;
                qcopy(object + 0x10, hit->point);
                owner = object;
                if (g_weapon_l00_table[g_item_slot_to_record[0x1B]].piercing != 0) {
                    StartAttachedEffect_pal(hit->hit, 0x45, *(int *)(object + 0xB8));
                } else {
                    StartAttachedEffect_pal(hit->hit, 0x1B, *(int *)(object + 0xB8));
                }
            }
        }
    } else if (hit->count > 0) {
        *(unsigned char *)(object + 0xBC) = 1;
        qcopy(object + 0x10, hit->point);
    }
checked:
    if (*(unsigned char *)(object + 0xBC) == 0) {
        goto far;
    }
    {
        float spin;

        PlayMobySound(0, 0, object);
        bounce = 1;
        cam_compute_view_direction(object + 0x10, up, 1);
        if (g_collision_result.hit != 0 && g_collision_result.count <= 0) {
            FastVecSub(normal, g_camera_l00_position, object + 0x10);
            vec_scale_to_length(normal, normal, 1.0f);
        } else {
            vec_scale_to_length(normal, g_collision_result.normal, 1.0f);
            if (math_fabs(FastVecDot(normal, up)) >= 0.1f) {
                bounce = 0;
            }
        }
        spin = 0.0f;
        if (bounce) {
            spin = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        }
        part_spawn_blast_effect_moby_pal(object, object + 0x10, normal, spin);
        homing_shot_spawn_explosion_pal(object, up, owner);
    }
    RemoveMobyFromIndexList(object, g_homing_moby_index_list);
    table_clear_entry_flag(*(int *)(state + 0x50));
    moby_mark_spawned(object);
    return;
far:
    if (FastDecTimer(state + 0x24) != 0 || vec_distance_xy(object + 0x10, g_hero_position) > 75.0f) {
        RemoveMobyFromIndexList(object, g_homing_moby_index_list);
        table_clear_entry_flag(*(int *)(state + 0x50));
        moby_mark_spawned(object);
    }
}
