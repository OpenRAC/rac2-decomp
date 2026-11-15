#include "include_asm.h"

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
extern char *D_L05_001B1EC4;
extern Moby *D_L05_001B251C;
extern int g_current_map_index MACRO_ADDR;
extern Collision D_L05_001BFB00;
extern char D_L05_002B8770[];
extern int D_L05_001B2048;
extern float D_L05_001B1C10 __attribute__((sda));
extern float D_L05_001B1C14 __attribute__((sda));
extern float D_L05_001B1C18 __attribute__((sda));
extern float D_L05_001B1C1C __attribute__((sda));
extern float D_L05_001B1C20 __attribute__((sda));
extern int D_L05_001B1AE4 __attribute__((sda));
extern int math_fast_float_d(void *);
extern int coll_test_point(void *, int, void *, float);
extern void func_PAL_L05_0037D3D0(float);
extern void func_PAL_L05_004485A0(void *);
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
extern int slot_copy_records_to_free(void *);
extern void euler_rotation_basis(void *, void *);
extern void QueueMobyImpact(void *, void *);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void part_spawn_impact_trail(void *);

/* Sweeps the linked moby's movement in short steps, resolving contacts and
 * producing impact damage, recoil and a deferred collision trail. */
void func_PAL_L05_0044B738(char *obj, void *target)
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
    char *record = *(char **)(D_L05_001B1EC4 + *(short *)(obj + 0x84) * 32 + 0x1C);
    Moby *moby = &D_L05_001B251C[*(int *)(record + 0x20)];
    float distance, divisor;
    int count, i;

    math_fast_float_d(record + 0x58);
    if (g_current_map_index == 10 && coll_test_point(moby->position, 16, moby, 0.5f) &&
        D_L05_001BFB00.object &&
        *(short *)(D_L05_001BFB00.object + 0xAA) == 0xF86) {
        func_PAL_L05_0037D3D0(1000);
        func_PAL_L05_004485A0(obj);
        return;
    }
    FastVecSub(delta, moby->position, target);
    distance = FastVecLength(delta);
    if (distance <= D_L05_001B1C1C) {
        count = 2;
        divisor = 2;
    } else {
        if (distance > 30)
            return;
        count = FloatToInt(distance / D_L05_001B1C1C) + 2;
        divisor = IntToFloat(count);
    }
    FastVecScale(step, delta, 1.0f / divisor);
    FastVecScale(offset, moby->up, D_L05_001B1C20);
    FastVecAdd(pos, target, offset);
    for (i = 0; i < count; i++) {
        float *direction;

        FastVecAdd(pos, pos, step);
        if (!coll_test_point(pos, 16, moby, D_L05_001B1C1C) || GetCollHitMaterial() == 6)
            continue;

        if (D_L05_001BFB00.object && !level_has_pending_inner_flag(D_L05_001BFB00.object)) {
            if (D_L05_001BFB00.object) {
                char *link = *(char **)(D_L05_001BFB00.object + 0x24);

                if (link && *(short *)(link + 0x46) == 11) {
                    FastVecSub(dir, moby->position, D_L05_001BFB00.object + 0x10);
                    vec_scale_to_length(dir, dir, 1);
                    qcopy(hit, D_L05_001BFB00.object + 0x10);
                    direction = dir;
                    goto impact;
                }
            }
            if (D_L05_001BFB00.object && g_current_map_index == 10 &&
                *(short *)(D_L05_001BFB00.object + 0xAA) == 0x1315)
                return;
            {
                int kind = *(short *)(D_L05_001BFB00.object + 0xAA);

                if (kind == 0x1327)
                    return;
                if (kind == 0x1328)
                    return;
            }
            FastVecSub(move, D_L05_001BFB00.position, pos);
            FastVecAdd(moby->position, moby->position, move);
            FastVecAdd(obj + 0x30, obj + 0x30, move);
            qcopy(pos, D_L05_001BFB00.position);
            {
                float facing;

                if (*(unsigned short *)(D_L05_001BFB00.object + 0x34) & 0x100) {
                    facing = FastVecDot(D_L05_001BFB00.object + 0xC0, moby->forward);
                } else {
                    euler_rotation_basis(event.rotation, D_L05_001BFB00.object + 0xF0);
                    facing = FastVecDot(event.rotation, moby->forward);
                }
                if (facing > 0)
                    continue;
            }
            if (!*(int *)(record + 0x58)) {
                event.message.flags = 0x10000;
                event.message.amount = D_L05_001B1C14;
                event.message.enabled = 1;
                event.message.object = moby;
                FastVecSub(&event.message, D_L05_001BFB00.object + 0x10, moby->position);
                vec_scale_to_length(&event.message, &event.message, 1);
                event.message.value = 5627.925f;
                event.message.a = 1;
                event.message.b = 1;
                event.message.type = moby->type;
                QueueMobyImpact(D_L05_001BFB00.object, &event.message);
                func_PAL_L05_0037D3D0(D_L05_001B1C18);
                *(int *)(record + 0x58) = ((s32)(D_L05_001B1AE4) * 5 + 2) / 6;
            }
            slot_copy_records_to_free(D_L05_002B8770);
            qcopy(moby->state + 0x90, D_L05_001BFB00.hit);
            gfx_add_draw_callback_third(part_spawn_impact_trail, moby);
            continue;
        }
        FastVecScale(dir, D_L05_001BFB00.normal, 0.0009765625f);
        vec_scale_to_length(dir, dir, 1);
        qcopy(hit, D_L05_001BFB00.hit);
        direction = dir;
impact:
        if (math_fabs(FastVecDot(direction, moby->forward)) > 0.75f) {
            func_PAL_L05_004485A0(obj);
            continue;
        }
        FastVecScale(D_L05_001BFB00.position, direction, D_L05_001B1C1C);
        FastVecAdd(D_L05_001BFB00.position, D_L05_001BFB00.hit, D_L05_001BFB00.position);
        FastVecSub(move, D_L05_001BFB00.position, pos);
        FastVecAdd(moby->position, moby->position, move);
        FastVecAdd(obj + 0x30, obj + 0x30, move);
        qcopy(pos, D_L05_001BFB00.position);
        slot_copy_records_to_free(D_L05_002B8770);
        if (!(D_L05_001B2048 & 3)) {
            float value = D_L05_001B1C10;

            if (hero_is_state_flag_set())
                value += value;
            func_PAL_L05_0037D3D0(value);
        }
        {
            char *state = moby->state;

            FastVecScale(move, direction, D_L05_001B1C1C * 0.8f);
            FastVecAdd(state + 0x90, move, D_L05_001BFB00.hit);
        }
        gfx_add_draw_callback_third(part_spawn_impact_trail, moby);
        if (fast_vec_dist(target, moby->position) < 0.1f)
            func_PAL_L05_004485A0(obj);
    }
}
