#include "include_asm.h"

#include "common.h"
typedef int BounceWord128 __attribute__((mode(TI)));
typedef union { BounceWord128 word; float f[4]; } BounceVector;
typedef struct {
    BounceVector previous, position, velocity;
    unsigned char *hit;
    int *excluded;
    int mode;
    float radius, response, friction;
    int flags0, flags1, enabled, surface, active;
    float tolerance;
} BounceQuery;
extern void FastVecAdd(void *, void *, void *);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(int, int);
extern void part_steer_effect_direction(int, void *, int);
extern void vec_add_object_direction_scaled(void *, float *, float);
extern int CollideSweptSphere(BounceQuery *);
extern char *moby_get_private_value_0(unsigned char *);
extern void moby_get_facing_direction(void *, float *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int PlayMobySound(int, int, char *);
extern char *ref_L00_003E7270_00(BounceWord128 *, BounceWord128 *);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
extern float FastAddRotations(float, float);
extern void part_queue_ground_shadow(void *, float);
extern float D_L00_001AFEC8;
extern float D_L00_001B0640 __attribute__((sda));
extern float D_L00_001B0644 __attribute__((sda));
extern unsigned char D_L00_001BF220[] __attribute__((nosda));
#define BF(p,o) (*(float *)((p)+(o)))
#define BI(p,o) (*(int *)((p)+(o)))
typedef struct {
    BounceVector previous;
    int excluded[2];
    BounceQuery query;
    BounceVector point, normal, offset;
} BounceWorkspace;

void func_PAL_L00_003EB510(unsigned char *object) {
    char *state = *(char **)(object + 0x68);
    BounceWorkspace work;
    int collision;
    char *info, *spawn;
    short category;
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
    case 1:
        qcopy(&work.previous, object + 0x10);
        FastVecAdd(object + 0x10, object + 0x10, state);
        vec_transform_or_copy(object + 0x10, object + 0x10);
        shop_trigger_current_state_effect((int)state, (int)state);
        part_steer_effect_direction(BI(state, 0x34), state, 0);
        vec_add_object_direction_scaled(object + 0x10, (float *)state, D_L00_001AFEC8 * 0.00040000002f);
        work.excluded[0] = 0;
        work.excluded[1] = 0xA5A;
        qcopy(&work.query.previous, &work.previous);
        qcopy(&work.query.position, object + 0x10);
        qcopy(&work.query.velocity, state);
        work.query.hit = object;
        work.query.excluded = work.excluded;
        work.query.mode = 2;
        work.query.radius = 0.25f;
        work.query.response = D_L00_001B0640;
        work.query.friction = D_L00_001B0644;
        work.query.flags0 = 0;
        work.query.flags1 = 0;
        work.query.active = 0;
        collision = CollideSweptSphere(&work.query);
        qcopy(object + 0x10, &work.query.position);
        qcopy(state, &work.query.velocity);
        qcopy(state + 0x20, &work.query.previous);
        if (collision == 2)
            object[0x20] = 2;
        if (work.query.hit) {
            category = *(short *)(*(char **)(work.query.hit + 0x24) + 0x46);
            if (category == 5 || category == 9 || (*(unsigned short *)(work.query.hit + 0x34) & 0x4000)) {
                info = (char *)moby_get_private_value_0(work.query.hit);
                moby_get_facing_direction(work.query.hit + 0x10, work.normal.f);
                qcopy(&work.point, object + 0x10);
                if (info) {
                    FastVecScale(&work.offset, &work.normal, BF(info, 0x10));
                    FastVecAdd(&work.point, &work.point, &work.offset);
                }
                FastVecScale(&work.normal, &work.normal, -3.0f);
                FastVecAdd(&work.normal, &work.normal, &work.point);
                object[0x20] = 2;
                qcopy(object + 0x10, D_L00_001BF220);
                qcopy(state + 0x20, D_L00_001BF220 + 0x20);
                vec_scale_to_length(state + 0x20, state + 0x20, 1.0f);
                if (CollLine(&work.point, &work.normal, 2, work.query.hit, 0)) {
                    qcopy(object + 0x10, D_L00_001BF220);
                    qcopy(state + 0x20, D_L00_001BF220 + 0x20);
                    vec_scale_to_length(state + 0x20, state + 0x20, 1.0f);
                }
            }
        }
        break;
    case 2:
        PlayMobySound(0, 0, (char *)object);
        spawn = ref_L00_003E7270_00((BounceWord128 *)(object + 0x10), (BounceWord128 *)(state + 0x20));
        BI(spawn, 0xB8) = BI(state, 0x30);
        table_clear_entry_flag(BI(state, 0x34));
        moby_mark_spawned(object);
        return;
    }
    BF(object, 0xF0) = FastAddRotations(BF(object, 0xF0), BF(state, 0x10));
    BF(object, 0xF4) = FastAddRotations(BF(object, 0xF4), BF(state, 0x14));
    part_queue_ground_shadow(object, 0.2f);
    if (BF(object, 0x10) < 2.0f || BF(object, 0x10) > 1021.0f ||
        BF(object, 0x14) < 2.0f || BF(object, 0x14) > 1021.0f ||
        BF(object, 0x18) < 2.0f || BF(object, 0x18) > 1021.0f) {
        table_clear_entry_flag(BI(state, 0x34));
        moby_mark_spawned(object);
    }
}
