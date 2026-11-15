/* func_PAL_L01_003D8528, the PAL copy of func_L01_003D4270: the same C, where rename func_L00_002D70A0 becomes func_PAL_L00_002D7850. */
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
extern Pool *func_PAL_L00_002D7850(int);
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

void func_PAL_L01_003D8528(char *m)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4];
    int clear = 1;
    TriggerData *d = *(TriggerData **)(m + 0x68);
    int active = IsPointInCuboid(g_hero_position, d->volume);
    Pool *p;

    if (d->conditions[0] == -1 && d->conditions[1] == -1 &&
        d->conditions[2] == -1 && d->conditions[3] == -1)
        clear = 0;
    if (d->conditions[0] != -1 && moby_count_group_not_in_state(d->conditions[0], -1))
        clear = 0;
    if (d->conditions[1] != -1 && moby_count_group_not_in_state(d->conditions[1], -1))
        clear = 0;
    if (d->conditions[2] != -1 && moby_count_group_not_in_state(d->conditions[2], -1))
        clear = 0;
    if (d->conditions[3] != -1 && moby_count_group_not_in_state(d->conditions[3], -1))
        clear = 0;

    if (B(m, 0x20)) {
        if (d->pool && (!active || clear)) {
            cam_end_override(d->pool);
            d->pool = 0;
        } else if (!d->pool && active && !clear && d->target == -1) {
            Pool *created;

            created = func_PAL_L00_002D7850(d->b33);
            d->pool = created;
            if (!created)
                return;
            created->f0 = d->f18;
            created->fc = d->f1c == -1.0f ? d->f1c : d->f1c * 0.01745329424738884f;
            created->f4 = d->f20;
            created->f8 = d->f24;
            if (!d->b45)
                created->f14 = d->f28;
            else
                created->f14 = -1.0f;
            created->f10 = d->f2c == -1.0f ? d->f2c : d->f2c * 0.01745329424738884f;
            created->s1a = d->b30;
            created->b1e = d->b31;
            created->b1f = d->b32;
            created->b18 = d->b46;
            if (d->f40 != -1)
                created->f34 = d->f40;
            if (d->anchor != -1) {
                if (d->b49)
                    created->pos = ref_L01_003D4270_00[d->anchor].q0;
                else {
                    FastVecSub(pos, &D_L01_001B264C[0][d->anchor].centre, g_hero_position);
                    created->pos = *(Quad *)(pos);
                }
            }
        } else if (active && !d->state && d->target != -1) {
            char *camera = D_L01_001FE180[d->target];

            *(Quad *)(pos) = *(Quad *)(g_hero_position);
            pos[2] += 1.25f;
            rot[2] = mat_fast_helper_a(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -mat_fast_helper_a(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            SetCamera5Pose(D_L01_001B94C0, D_L01_001B94C0 + 0x10, 3, 100, 0);
            object_copy_vector_to_selected(camera + 0x10);
            cam_set_state_rotation(rot);
            d->state = 1;
        } else if (active && d->state) {
            char *camera;

            if (d->state == 1 && (ship_get_docking_state() & 1)) {
                d->state = 2;
                SetCamera5Mode(1, 0);
            }
            camera = D_L01_001FE180[d->target];
            *(Quad *)(pos) = *(Quad *)(g_hero_position);
            pos[2] += 1.25f;
            rot[2] = mat_fast_helper_a(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -mat_fast_helper_a(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            object_copy_vector_to_selected(camera + 0x10);
            cam_set_state_rotation(rot);
        } else if (!active && d->state) {
            cam_set_mode_state(1);
            d->state = 0;
        } else if (d->pool && d->anchor != -1) {
            p = d->pool;
            if (d->b49)
                p->pos = ref_L01_003D4270_00[d->anchor].q0;
            else {
                FastVecSub(pos, &D_L01_001B264C[0][d->anchor].centre, g_hero_position);
                p->pos = *(Quad *)(pos);
            }
        }

        if (d->pool) {
            p = d->pool;
            if (!d->b47 && d->anchor != -1) {
                qcopy(pos, &ref_L01_003D4270_00[d->anchor].centre);
                pos[3] = 1;
                if (math_fast_helper_a(pos, 255.0f) != -1) {
                    d->b47 = 1;
                    if (d->b45)
                        d->pool->f14 = d->f28;
                    if (d->b44) {
                        d->pool->b1f = 0;
                        d->pool->b1e = 0;
                    }
                    if (d->b48)
                        d->pool->b18 = 1;
                }
            }
            p->f10 = d->f2c * 0.01745329424738884f;
        }
    } else {
        d->pool = 0;
        d->state = 0;
        d->b47 = 0;
        B(m, 0x20) = 1;
        B(m, 0x30) = 255;
    }
}
