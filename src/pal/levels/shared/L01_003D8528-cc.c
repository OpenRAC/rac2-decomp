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
extern Row *g_swamp_patrol_positions[] __attribute__((sda));
extern Row *ref_L01_003D4270_00 __attribute__((sda));
extern char *g_path_l01_table[];
extern char g_level_origin_vec[];

extern int IsPointInCuboid(void *, int);
extern int moby_count_group_not_in_state(int, int);
extern void cam_end_override(void *);
extern Pool *cam_alloc_override_slot_pal(int);
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

/* Camera trigger area: while the hero is inside it and its conditions are clear, it overrides the camera (or points it at a target), and gives the camera back when the hero leaves. */
void trigger_area_effect_update_pal(char *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4];
    int clear = 1;
    TriggerData *vars = *(TriggerData **)(moby + 0x68);
    int active = IsPointInCuboid(g_hero_position, vars->volume);
    Pool *slot;

    if (vars->conditions[0] == -1 && vars->conditions[1] == -1 &&
        vars->conditions[2] == -1 && vars->conditions[3] == -1)
        clear = 0;
    if (vars->conditions[0] != -1 && moby_count_group_not_in_state(vars->conditions[0], -1))
        clear = 0;
    if (vars->conditions[1] != -1 && moby_count_group_not_in_state(vars->conditions[1], -1))
        clear = 0;
    if (vars->conditions[2] != -1 && moby_count_group_not_in_state(vars->conditions[2], -1))
        clear = 0;
    if (vars->conditions[3] != -1 && moby_count_group_not_in_state(vars->conditions[3], -1))
        clear = 0;

    if (B(moby, 0x20)) {
        if (vars->pool && (!active || clear)) {
            cam_end_override(vars->pool);
            vars->pool = 0;
        } else if (!vars->pool && active && !clear && vars->target == -1) {
            Pool *created;

            created = cam_alloc_override_slot_pal(vars->b33);
            vars->pool = created;
            if (!created)
                return;
            created->f0 = vars->f18;
            created->fc = vars->f1c == -1.0f ? vars->f1c : vars->f1c * 0.01745329424738884f;
            created->f4 = vars->f20;
            created->f8 = vars->f24;
            if (!vars->b45)
                created->f14 = vars->f28;
            else
                created->f14 = -1.0f;
            created->f10 = vars->f2c == -1.0f ? vars->f2c : vars->f2c * 0.01745329424738884f;
            created->s1a = vars->b30;
            created->b1e = vars->b31;
            created->b1f = vars->b32;
            created->b18 = vars->b46;
            if (vars->f40 != -1)
                created->f34 = vars->f40;
            if (vars->anchor != -1) {
                if (vars->b49)
                    created->pos = ref_L01_003D4270_00[vars->anchor].q0;
                else {
                    FastVecSub(pos, &g_swamp_patrol_positions[0][vars->anchor].centre, g_hero_position);
                    created->pos = *(Quad *)(pos);
                }
            }
        } else if (active && !vars->state && vars->target != -1) {
            char *camera = g_path_l01_table[vars->target];

            *(Quad *)(pos) = *(Quad *)(g_hero_position);
            pos[2] += 1.25f;
            rot[2] = mat_fast_helper_a(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -mat_fast_helper_a(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            SetCamera5Pose(g_level_origin_vec, g_level_origin_vec + 0x10, 3, 100, 0);
            object_copy_vector_to_selected(camera + 0x10);
            cam_set_state_rotation(rot);
            vars->state = 1;
        } else if (active && vars->state) {
            char *camera;

            if (vars->state == 1 && (ship_get_docking_state() & 1)) {
                vars->state = 2;
                SetCamera5Mode(1, 0);
            }
            camera = g_path_l01_table[vars->target];
            *(Quad *)(pos) = *(Quad *)(g_hero_position);
            pos[2] += 1.25f;
            rot[2] = mat_fast_helper_a(pos[0] - F(camera, 0x10), pos[1] - F(camera, 0x14));
            rot[1] = -mat_fast_helper_a(vec_distance_xy(camera + 0x10, pos), pos[2] - F(camera, 0x18));
            rot[0] = 0;
            object_copy_vector_to_selected(camera + 0x10);
            cam_set_state_rotation(rot);
        } else if (!active && vars->state) {
            cam_set_mode_state(1);
            vars->state = 0;
        } else if (vars->pool && vars->anchor != -1) {
            slot = vars->pool;
            if (vars->b49)
                slot->pos = ref_L01_003D4270_00[vars->anchor].q0;
            else {
                FastVecSub(pos, &g_swamp_patrol_positions[0][vars->anchor].centre, g_hero_position);
                slot->pos = *(Quad *)(pos);
            }
        }

        if (vars->pool) {
            slot = vars->pool;
            if (!vars->b47 && vars->anchor != -1) {
                qcopy(pos, &ref_L01_003D4270_00[vars->anchor].centre);
                pos[3] = 1;
                if (math_fast_helper_a(pos, 255.0f) != -1) {
                    vars->b47 = 1;
                    if (vars->b45)
                        vars->pool->f14 = vars->f28;
                    if (vars->b44) {
                        vars->pool->b1f = 0;
                        vars->pool->b1e = 0;
                    }
                    if (vars->b48)
                        vars->pool->b18 = 1;
                }
            }
            slot->f10 = vars->f2c * 0.01745329424738884f;
        }
    } else {
        vars->pool = 0;
        vars->state = 0;
        vars->b47 = 0;
        B(moby, 0x20) = 1;
        B(moby, 0x30) = 255;
    }
}
