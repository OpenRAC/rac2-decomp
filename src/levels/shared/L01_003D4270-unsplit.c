#include "common.h"

/* Own unit: retail's PRE leaves the `!active && d->state` arm's load in place,
 * which takes gcse on the unsplit flow graph (tools/compiler/README.md). */

typedef int Quad __attribute__((mode(TI)));

typedef struct Row {
    Quad q0;
    char pad[0x20];
    Quad centre;
    char rest[0x40];
} Row;

typedef struct Pool {
    float f0, f4, f8, fc, f10, f14;
    unsigned char b18, b19;
    short s1a;
    unsigned char b1c, b1d, b1e, b1f;
    Quad pos;
    int pad30, f34;
} Pool;

typedef struct TriggerData {
    int conditions[4];
    int volume;
    struct Pool *pool;
    float f18, f1c, f20, f24, f28, f2c;
    unsigned char b30, b31, b32, b33;
    int anchor, target, state, f40;
    unsigned char b44, b45, b46, b47, b48, b49;
} TriggerData;

extern char g_hero_position[];
extern Row *D_L01_001B264C[] __attribute__((sda));
extern Row *ref_L01_003D4270_00 __attribute__((sda));
extern char *D_L01_001FE180[];
extern char D_L01_001B94C0[];

extern int IsPointInCuboid(void *, int);
extern int moby_count_group_not_in_state(int, int);
extern void cam_end_override(void *);
extern Pool *cam_alloc_override_slot(int);
extern void FastVecSub(void *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(void *, void *);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern int ship_get_docking_state(void);
extern void SetCamera5Mode(int, int);
extern void cam_set_mode_state(int);
extern int math_fast_helper_a(void *, float);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define B(p, o) (*(unsigned char *)((char *)(p) + (o)))

/* Watches a trigger area: while the player is inside and its conditions hold, it creates an effect and can take over the camera. */
void trigger_area_effect_update(char *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4];
    int clear = 1;
    TriggerData *trigger = *(TriggerData **)(moby + 0x68);
    int active = IsPointInCuboid(g_hero_position, trigger->volume);
    Pool *pool;

    if (trigger->conditions[0] == -1 && trigger->conditions[1] == -1 &&
        trigger->conditions[2] == -1 && trigger->conditions[3] == -1)
        clear = 0;
    if (trigger->conditions[0] != -1 && moby_count_group_not_in_state(trigger->conditions[0], -1))
        clear = 0;
    if (trigger->conditions[1] != -1 && moby_count_group_not_in_state(trigger->conditions[1], -1))
        clear = 0;
    if (trigger->conditions[2] != -1 && moby_count_group_not_in_state(trigger->conditions[2], -1))
        clear = 0;
    if (trigger->conditions[3] != -1 && moby_count_group_not_in_state(trigger->conditions[3], -1))
        clear = 0;

    if (B(moby, 0x20)) {
        if (trigger->pool && (!active || clear)) {
            cam_end_override(trigger->pool);
            trigger->pool = 0;
        } else if (!trigger->pool && active && !clear && trigger->target == -1) {
            Pool *created;

            created = cam_alloc_override_slot(trigger->b33);
            trigger->pool = created;
            if (!created)
                return;
            created->f0 = trigger->f18;
            created->fc = trigger->f1c == -1.0f ? trigger->f1c : trigger->f1c * 0.01745329424738884f;
            created->f4 = trigger->f20;
            created->f8 = trigger->f24;
            if (!trigger->b45)
                created->f14 = trigger->f28;
            else
                created->f14 = -1.0f;
            created->f10 = trigger->f2c == -1.0f ? trigger->f2c : trigger->f2c * 0.01745329424738884f;
            created->s1a = trigger->b30;
            created->b1e = trigger->b31;
            created->b1f = trigger->b32;
            created->b18 = trigger->b46;
            if (trigger->f40 != -1)
                created->f34 = trigger->f40;
            if (trigger->anchor != -1) {
                if (trigger->b49)
                    created->pos = ref_L01_003D4270_00[trigger->anchor].q0;
                else {
                    FastVecSub(pos, &D_L01_001B264C[0][trigger->anchor].centre, g_hero_position);
                    created->pos = *(Quad *)(pos);
                }
            }
        } else if (active && !trigger->state && trigger->target != -1) {
            char *camera = D_L01_001FE180[trigger->target];

            *(Quad *)(pos) = *(Quad *)(g_hero_position);
            pos[2] += 1.25f;
            rot[2] = mat_fast_helper_a(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -mat_fast_helper_a(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            SetCamera5Pose(D_L01_001B94C0, D_L01_001B94C0 + 0x10, 3, 120, 0);
            object_copy_vector_to_selected(camera + 0x10);
            cam_set_state_rotation(rot);
            trigger->state = 1;
        } else if (active && trigger->state) {
            char *camera;

            if (trigger->state == 1 && (ship_get_docking_state() & 1)) {
                trigger->state = 2;
                SetCamera5Mode(1, 0);
            }
            camera = D_L01_001FE180[trigger->target];
            *(Quad *)(pos) = *(Quad *)(g_hero_position);
            pos[2] += 1.25f;
            rot[2] = mat_fast_helper_a(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -mat_fast_helper_a(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            object_copy_vector_to_selected(camera + 0x10);
            cam_set_state_rotation(rot);
        } else if (!active && trigger->state) {
            cam_set_mode_state(1);
            trigger->state = 0;
        } else if (trigger->pool && trigger->anchor != -1) {
            pool = trigger->pool;
            if (trigger->b49)
                pool->pos = ref_L01_003D4270_00[trigger->anchor].q0;
            else {
                FastVecSub(pos, &D_L01_001B264C[0][trigger->anchor].centre, g_hero_position);
                pool->pos = *(Quad *)(pos);
            }
        }

        if (trigger->pool) {
            pool = trigger->pool;
            if (!trigger->b47 && trigger->anchor != -1) {
                qcopy(pos, &ref_L01_003D4270_00[trigger->anchor].centre);
                pos[3] = 1;
                if (math_fast_helper_a(pos, 255.0f) != -1) {
                    trigger->b47 = 1;
                    if (trigger->b45)
                        trigger->pool->f14 = trigger->f28;
                    if (trigger->b44) {
                        trigger->pool->b1f = 0;
                        trigger->pool->b1e = 0;
                    }
                    if (trigger->b48)
                        trigger->pool->b18 = 1;
                }
            }
            pool->f10 = trigger->f2c * 0.01745329424738884f;
        }
    } else {
        trigger->pool = 0;
        trigger->state = 0;
        trigger->b47 = 0;
        B(moby, 0x20) = 1;
        B(moby, 0x30) = 255;
    }
}
