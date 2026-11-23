#include "common.h"

typedef struct {
    char pad00[0x10];
    float position[4];
    char pad20[0x48];
    char *state;
    char pad6c[0x3E];
    unsigned short type;
    char padac[0x14];
    float forward[4];
    char padd0[0x10];
    float up[4];
    char padf0[0x10];
} Moby;

typedef struct {
    char pad[0x18];
    char *object;
    int flags;
    float hit[4];
    float position[4];
    float normal[4];
} Collision;

typedef struct {
    float normal[3];
    float value;
    void *object;
    int flags;
    unsigned char a, b;
    unsigned short type;
    float amount;
    int enabled;
    float extra;
} ImpactRequest;

extern char *g_path_l05_entry_table;
extern Moby *g_feltzin_target_mobys;
extern int g_current_map_index MACRO_ADDR;
extern Collision g_collision_l05_result;
extern char g_ship_l05_rumble_waves[];
extern int g_feltzin_mission_index;
extern float g_ship_hit_value __attribute__((sda));
extern float g_ship_hit_event_amount __attribute__((sda));
extern float g_ship_hit_damage __attribute__((sda));
extern float g_ship_beam_step_distance __attribute__((sda));
extern float g_ship_up_offset __attribute__((sda));
extern int g_ship_record_word __attribute__((sda));

extern int math_fast_float_d(void *);
extern int coll_test_point(void *, int, void *, float);
extern void hero_apply_damage(float);
extern void ship_start_crash_recovery(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecLength(void *);
extern float IntToFloat(int);
extern float FastVecDot(void *, void *);
extern float math_fabs(float);
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);
extern int GetCollHitMaterial(void);
extern int level_has_pending_inner_flag(void *);
extern int hero_is_state_flag_set(void);
extern int actuator_play_waves(void *);
extern void euler_rotation_basis(void *, void *);
extern void QueueMobyImpact(void *, void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void part_spawn_impact_trail(void *);

/* Sweeps the linked moby's movement in short steps, resolving contacts and
 * producing impact damage, recoil and a deferred collision trail. */
/* Moves the driven object in small steps and bounces it off walls. Hitting an enemy hurts it, and impacts leave a spray of sparks. */
void ResolveLinkedMobyMovementCollisions(char *obj, void *target)
{
    float delta[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float hit[4] __attribute__((aligned(16)));
    float move[4] __attribute__((aligned(16)));
    /* The facing matrix and the later impact request share the retail scratch. */
    union {
        ImpactRequest message;
        float rotation[3][4];
    } event;
    char *record = *(char **)(g_path_l05_entry_table + *(short *)(obj + 0x84) * 32 + 0x1C);
    Moby *moby = &g_feltzin_target_mobys[*(int *)(record + 0x20)];
    float distance, divisor;
    int count, i;

    math_fast_float_d(record + 0x58);
    if (g_current_map_index == 10 && coll_test_point(moby->position, 16, moby, 0.5f) &&
        g_collision_l05_result.object &&
        *(short *)(g_collision_l05_result.object + 0xAA) == 0xF86 /* moby class 3974 */) {
        hero_apply_damage(1000);
        ship_start_crash_recovery(obj);
        return;
    }
    FastVecSub(delta, moby->position, target);
    distance = FastVecLength(delta);
    if (distance <= g_ship_beam_step_distance) {
        count = 2;
        divisor = 2;
    } else {
        if (distance > 30)
            return;
        count = FloatToInt(distance / g_ship_beam_step_distance) + 2;
        divisor = IntToFloat(count);
    }
    FastVecScale(step, delta, 1.0f / divisor);
    FastVecScale(offset, moby->up, g_ship_up_offset);
    FastVecAdd(pos, target, offset);
    for (i = 0; i < count; i++) {
        float *direction;

        FastVecAdd(pos, pos, step);
        if (!coll_test_point(pos, 16, moby, g_ship_beam_step_distance) || GetCollHitMaterial() == 6)
            continue;

        if (g_collision_l05_result.object && !level_has_pending_inner_flag(g_collision_l05_result.object)) {
            if (g_collision_l05_result.object) {
                char *link = *(char **)(g_collision_l05_result.object + 0x24);

                if (link && *(short *)(link + 0x46) == 11) {
                    FastVecSub(dir, moby->position, g_collision_l05_result.object + 0x10);
                    vec_scale_to_length(dir, dir, 1);
                    qcopy(hit, g_collision_l05_result.object + 0x10);
                    direction = dir;
                    goto impact;
                }
            }
            if (g_collision_l05_result.object && g_current_map_index == 10 &&
                *(short *)(g_collision_l05_result.object + 0xAA) == 0x1315 /* moby class 4885 */)
                return;
            {
                int kind = *(short *)(g_collision_l05_result.object + 0xAA);

                if (kind == 0x1327 /* moby class 4903 */)
                    return;
                if (kind == 0x1328 /* moby class 4904 */)
                    return;
            }
            FastVecSub(move, g_collision_l05_result.position, pos);
            FastVecAdd(moby->position, moby->position, move);
            FastVecAdd(obj + 0x30, obj + 0x30, move);
            qcopy(pos, g_collision_l05_result.position);
            {
                float facing;

                if (*(unsigned short *)(g_collision_l05_result.object + 0x34) & 0x100) {
                    facing = FastVecDot(g_collision_l05_result.object + 0xC0, moby->forward);
                } else {
                    euler_rotation_basis(event.rotation, g_collision_l05_result.object + 0xF0);
                    facing = FastVecDot(event.rotation, moby->forward);
                }
                if (facing > 0)
                    continue;
            }
            if (!*(int *)(record + 0x58)) {
                event.message.flags = 0x10000;
                event.message.amount = g_ship_hit_event_amount;
                event.message.enabled = 1;
                event.message.object = moby;
                FastVecSub(&event.message, g_collision_l05_result.object + 0x10, moby->position);
                vec_scale_to_length(&event.message, &event.message, 1);
                event.message.value = 5627.925f;
                event.message.a = 1;
                event.message.b = 1;
                event.message.type = moby->type;
                QueueMobyImpact(g_collision_l05_result.object, &event.message);
                hero_apply_damage(g_ship_hit_damage);
                *(int *)(record + 0x58) = g_ship_record_word;
            }
            actuator_play_waves(g_ship_l05_rumble_waves);
            qcopy(moby->state + 0x90, g_collision_l05_result.hit);
            gfx_add_draw_callback_third(part_spawn_impact_trail, moby);
            continue;
        }
        FastVecScale(dir, g_collision_l05_result.normal, 0.0009765625f);
        vec_scale_to_length(dir, dir, 1);
        qcopy(hit, g_collision_l05_result.hit);
        direction = dir;
impact:
        if (math_fabs(FastVecDot(direction, moby->forward)) > 0.75f) {
            ship_start_crash_recovery(obj);
            continue;
        }
        FastVecScale(g_collision_l05_result.position, direction, g_ship_beam_step_distance);
        FastVecAdd(g_collision_l05_result.position, g_collision_l05_result.hit, g_collision_l05_result.position);
        FastVecSub(move, g_collision_l05_result.position, pos);
        FastVecAdd(moby->position, moby->position, move);
        FastVecAdd(obj + 0x30, obj + 0x30, move);
        qcopy(pos, g_collision_l05_result.position);
        actuator_play_waves(g_ship_l05_rumble_waves);
        if (!(g_feltzin_mission_index & 3)) {
            float value = g_ship_hit_value;

            if (hero_is_state_flag_set())
                value += value;
            hero_apply_damage(value);
        }
        {
            char *state = moby->state;

            FastVecScale(move, direction, g_ship_beam_step_distance * 0.8f);
            FastVecAdd(state + 0x90, move, g_collision_l05_result.hit);
        }
        gfx_add_draw_callback_third(part_spawn_impact_trail, moby);
        if (fast_vec_dist(target, moby->position) < 0.1f)
            ship_start_crash_recovery(obj);
    }
}
