#include "common.h"

extern unsigned int g_moby_l04_pool;

extern int math_fast_float_d(void *a0);

extern void glow_ring_init_variant(unsigned char *a0);

extern void glow_ring_update_variant(unsigned char *a0);

/* Update for the hoverbike race item box: waits for its owner slot to be active, then shows or hides itself. */
void hoverbike_race_item_box_update(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    int owner_index = *(int *)(vars + 8);
    unsigned char *owner_entry;

    if (owner_index != -1) {
        owner_entry = (unsigned char *)((owner_index << 8) + g_moby_l04_pool);
        if ((unsigned int)(owner_entry[0x20] - 2) >= 2) {
            return;
        }
    }
    if (moby[0x20] == 0) {
        *(int *)vars = 0;
        moby[0x30] = 0xFF;
        *(unsigned short *)(moby + 0x32) = 0x7F;
        moby[0x20] = 1;
        glow_ring_init_variant(moby);
    }
    if (math_fast_float_d(vars) != 0) {
        glow_ring_update_variant(moby);
        *(unsigned short *)(moby + 0x34) &= 0xFFBE;
    } else {
        *(unsigned short *)(moby + 0x34) |= 0x41;
    }
}

typedef int L04_FBD80Quad __attribute__((mode(TI)));

/* The spawned object's state: a jitter table, a scale and a link back to the entity. */
typedef struct {
    float jitter[28];
    float scale;
    unsigned char *owner;
    int timer;
    float age;
} L04_FBD80Vars;

extern unsigned char *ref_L04_003FBD80_00(int kind);
extern int ref_L04_003FBD80_01(int a0, int a1, void *owner);
extern float ref_L04_003FBD80_02(float low, float high);
extern void moby_damage_in_firing_cone(unsigned char *object, L04_FBD80Vars *vars);
extern int g_shield_dome_sound_handle __attribute__((sda));

/* Spawns a kind-0xABE object for an entity of kind 0xBBC: it takes the entity's 8-byte
   word at +0x38, the given position raised by 0.2 and the entity's quadword at +0xF0 (with
   +0xF4 replaced by the entity state's +0x284 when its +0x274 is set), and its state
   points back at the entity with a 0.5 scale and a jitter table of 28 random floats in
   [-10, 10] / 75, the first and last zero. Returns the object, or 0. */
/* Creates a shield dome effect around the given object at the given position. */
unsigned char *shield_dome_spawn(unsigned char *owner, L04_FBD80Quad *pos_in)
{
    float spawn_pos[4] __attribute__((aligned(16)));
    unsigned char *dome;
    unsigned char *owner_vars;
    L04_FBD80Vars *dome_vars;
    int handle;
    long owner_word;
    int i;

    *(L04_FBD80Quad *)spawn_pos = *pos_in;
    if (owner == 0 || *(short *)(owner + 0xAA) != 0xBBC /* moby class 3004 */)
        return 0;
    dome = ref_L04_003FBD80_00(0xABE /* moby class 2750 */);
    if (dome != 0) {
        owner_vars = *(unsigned char **)(owner + 0x68);
        dome[0x30] = 0x7F;
        *(short *)(dome + 0x32) = 0x7F;
        dome[0x31] = 1;
        dome_vars = *(L04_FBD80Vars **)(dome + 0x68);
        handle = ref_L04_003FBD80_01(9, 0, owner);
        owner_word = *(long *)(owner + 0x38);
        g_shield_dome_sound_handle = handle;
        *(long *)(dome + 0x38) = owner_word;
        *(L04_FBD80Quad *)(dome + 0x10) = *(L04_FBD80Quad *)spawn_pos;
        *(float *)(dome + 0x18) += 0.2f;
        *(L04_FBD80Quad *)(dome + 0xF0) = *(L04_FBD80Quad *)(owner + 0xF0);
        if (*(short *)(owner_vars + 0x274) != 0)
            *(float *)(dome + 0xF4) = *(float *)(owner_vars + 0x284);
        dome_vars->owner = owner;
        dome_vars->scale = 0.5f;
        dome_vars->timer = 0;
        dome_vars->age = 0;
        for (i = 0; i < 28; i++) {
            dome_vars->jitter[i] = ref_L04_003FBD80_02(-10.0f, 10.0f) * 0.013333335f;
            if (i == 0 || i == 27)
                dome_vars->jitter[i] = 0;
        }
        moby_damage_in_firing_cone(dome, dome_vars);
    }
    return dome;
}

typedef int UpdateQuad __attribute__((mode(TI)));
typedef float L04_EE090Vec[4] __attribute__((aligned(16)));
extern int g_game_tick_counter MACRO_ADDR;
extern L04_EE090Vec g_tether_zero_vec, g_hero_position;
extern unsigned char g_effect_default_params[] MACRO_ADDR;
/* Table of 0x80-byte target records; targets[] below holds indices into it. */
extern unsigned char *g_linked_record_table __attribute__((sda));
extern unsigned char *g_route_path_table[];
extern void moby_start_timed_effect(unsigned char *, unsigned char *);
extern int moby_count_slot_objects_find_free(unsigned char *, unsigned char *);
extern void moby_mark_spawned(void *);
extern int GetFirstMobyInGroup(unsigned char **, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void anim_start_blended(void *, int, int, int);
extern int FastDecTimer(short *);
extern int math_random_int_below(int);
extern int FindHeroOrMobyTarget(void *, void *, void *, int, void *, int, float);
extern int math_random_int_range(int, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_fast_divide_helper(void *, void *, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_random_planar_offset(void *, float);
extern float math_random_float_range(float, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_add_random_offset(void *, float);
extern float weapon_compute_shot_launch_speed(void *, void *, int, float, float);
extern unsigned char *SpawnChildMoby(void *, void *);
extern void vec_random_direction(void *, float, float);
extern void *level_build_spawn_record(void *, void *, void *, void *, void *, void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void SetDeathBits(void *, int, int);

typedef struct {
    char pad0[0x20];
    float speed;
    char pad24[5];
    unsigned char active;
    char pad2a[0x46];
    float range;
    int idList;
    int pathIndex;
    short delay;
    short timer;
    unsigned char limit;
    unsigned char fired;
    unsigned char nearest;
    char pad83;
    int group;
    char pad88[8];
    int targets[4]; /* indices into D_L04_001B25CC, -1 for an empty slot */
    char padA0[0x50];
    UpdateQuad goal;
    char pad100[0x30];
    unsigned char *link;
    int linkState;
    char pad138[8];
    int shots;
} L04_EE090Vars;

/* Launcher: pick a target point near a record (nearest to the player, or a
 * random one), fire a child towards it, and retire after enough shots. */
/* Update for a launcher: picks a target point near a record or the player and fires a shot at it, until it runs out of shots. */
void LaunchSpawnerMobyUpdate(unsigned char *moby)
{
    float target[4], delta[4], rotation[4], axis[4], position[4], velocity[4];
    L04_EE090Vars *vars = *(L04_EE090Vars **)(moby + 0x68);
    unsigned char *cursor_moby, *chosen_target, *shot;
    int found_count, slot;
    float speed_scale, ground_z;

    moby_start_timed_effect(moby, (unsigned char *)vars);
    if (moby[0x31] && fast_vec_dist(moby + 0x10, g_tether_zero_vec) < 24.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 22;
    }
    switch (moby[0x20]) {
    case 0:
        vars->active = 1;
        vars->speed = 1.0f;
        vars->shots = 0;
        if (g_game_tick_counter) {
            cursor_moby = 0;
            found_count = 0;
            while (!GetFirstMobyInGroup(&cursor_moby, vars->group, 0, 0)) {
                moby_mark_spawned(cursor_moby);
                found_count++;
            }
            if (found_count < vars->limit)
                vars->limit = found_count;
            moby[0x20] = 1;
        }
        break;
    case 1: {
        float best, distance;

        moby_start_timed_effect(moby, (unsigned char *)vars);
        if (moby[0x43] == 1 && (moby[0x60] & 2))
            anim_start_blended(moby, 0, 0, 5);
        if (!FastDecTimer(&vars->timer))
            break;
        if (!math_random_int_below(7)) {
            void *ids, *path;
            int n, pathCount;
            ids = 0;
            n = 0;
            path = 0;
            pathCount = 0;
            if (vars->idList != -1) {
                ids = &vars->idList;
                n = 1;
            }
            if (vars->pathIndex != -1) {
                unsigned char *d = g_route_path_table[vars->pathIndex];
                path = d + 0x10;
                pathCount = *(int *)d;
            }
            FindHeroOrMobyTarget(moby, &vars->goal, ids, n, path, pathCount, vars->range);
        } else {
            unsigned char *q = vars->link;
            if (q && q[0x20] != 0xFE && q[0x20] != 0xFD) {
                qcopy_nc(&vars->goal, q + 0x10);
            } else {
                vars->link = 0;
                vars->linkState = 2;
            }
        }
        if (vars->linkState == 2)
            break;
        slot = moby_count_slot_objects_find_free(moby, (unsigned char *)vars);
        if (vars->fired >= vars->limit || slot == -1)
            break;
        chosen_target = 0;
        if (vars->nearest) {
            int i;
            best = 100000.0f;
            /* Read through an int-pointer view, as in func_L06_003F3800;
             * vars->targets[i] here gives different registers and stack slots. */
            for (i = 0; i < 4; i++) {
                int id = ((int *)((unsigned char *)vars + 0x90))[i];
                if (id != -1) {
                    unsigned char *q = g_linked_record_table + id * 128;
                    distance = fast_vec_dist(g_hero_position, q + 0x30);
                    if (distance < best) {
                        chosen_target = q;
                        best = distance;
                    }
                }
            }
            if (!chosen_target) {
                FastVecSub(target, &vars->goal, moby + 0x10);
                FastVecScale(target, target, 0.5f);
                if (vars->range > 1.0f)
                    vec_fast_divide_helper(target, target, 1.0f);
                if (FastVecLength(target) < 1.0f)
                    vec_scale_to_length(target, target, 1.0f);
                FastVecAdd(target, target, moby + 0x10);
            } else {
                qcopy_nc(target, chosen_target + 0x30);
            }
        } else {
            int i;
            int start = math_random_int_range(0, 3);
            /* targets[k] is read twice (cse merges the loads), keeping the
             * exit test short enough that jump1 does not peel an iteration. */
            for (i = 0; i < 4; i++) {
                int k = (i + start) % 4;
                if (vars->targets[k] != -1) {
                    chosen_target = g_linked_record_table + vars->targets[k] * 128;
                    break;
                }
            }
            if (!chosen_target) {
                float radius = vars->range;
                if (radius < 1.0f)
                    radius = 1.0f;
                math_random_planar_offset(target, radius);
                FastVecAdd(target, target, moby + 0x10);
            } else {
                qcopy_nc(target, chosen_target + 0x30);
            }
        }
        if (chosen_target) {
            FastVecScale(delta, chosen_target, math_random_float_range(-0.5f, 0.5f));
            FastVecAdd(target, target, delta);
            FastVecScale(delta, chosen_target + 0x10, math_random_float_range(-0.5f, 0.5f));
            FastVecAdd(target, target, delta);
        }
        ground_z = coll_probe_ground_height_below(target, 0, 3.0f);
        if (ground_z != 0)
            target[2] = ground_z;
        FastVecSub(delta, target, moby + 0x10);
        speed_scale = FastVecLength(delta) * 0.0100000007f;
        vec_scale_to_length(delta, delta, speed_scale);
        moby_transform_joint_to_world(moby, 0, rotation);
        vec_scale_to_length(axis, delta, 0.05f);
        vec_add_random_offset(axis, 0.025f);
        delta[2] = weapon_compute_shot_launch_speed(rotation, target, 0, speed_scale, -0.00272222236f);
        *(UpdateQuad *)position = *(UpdateQuad *)(moby + 0x10);
        shot = SpawnChildMoby(moby, position);
        *(float *)(shot + 0x2C) = *(float *)(*(unsigned char **)(shot + 0x24) + 0x24);
        vec_random_direction(position, 2.0f, 3.0f);
        position[2] = 0;
        FastVecAdd(position, position, target);
        rotation[2] += 1.0f;
        *(UpdateQuad *)velocity = 0;
        velocity[2] = 3.0f;
        level_build_spawn_record(shot, rotation, velocity, position, velocity, g_effect_default_params, 60, 0, 0);
        vars->fired++;
        vars->timer = vars->delay;
        if (++vars->shots >= 19)
            moby_set_state(moby, 2, -1);
        PlayMobySound(0, 0, moby);
        if (moby[0x43] != 1)
            anim_start_blended(moby, 1, 0, 5);
        break;
    }
    case 2:
        SpawnExplosion(moby + 0x10, 0, 25, 20, 20, 20, 20, 0, 1, 0, 0, 0, 0.75f, 20.0f);
        vars->speed = 0;
        PlayMobySound(1, 0, moby);
        SetDeathBits(moby, 0, 3);
        moby_mark_spawned(moby);
        break;
    }
}
