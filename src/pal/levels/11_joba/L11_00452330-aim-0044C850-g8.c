#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    u8 reserved00[0x10];
    float position[4];
} EntityPositionPrefix;
typedef struct {
    u8 pad00[0x134];
    float f134;
    u8 pad138[0x4C0 - 0x138];
    s32 group;           
} AimState;
typedef struct {
    u8 pad00[0x10];
    float position[4];   
    u8 pad20[0xE0 - 0x20];
    u8 orientation[0x18];    
    float heading;       
} AimObject;
extern u16 *g_group_id_lists[];
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern s32 g_tribe_group_limit __attribute__((sda));
extern float g_enemy_aim_range_b __attribute__((sda));
extern float g_enemy_aim_cone_deg_b __attribute__((sda));
extern float g_enemy_aim_turn_deg_b __attribute__((sda));
extern int math_fast_helper_a(void *v, float r);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_subtract_rotations(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern int moby_get_busy_flag(void *);

/* Same as AimAtGroupEntityInCone_pal, with the second set of range and cone limits. */
s32 enemy_aim_at_group_entity_in_cone_b_pal(AimObject *obj)
{
    AimState *state = *(AimState **)((u8 *)obj + 0x68);
    float copy[4];
    float vec[4];
    u16 *p;
    EntityPositionPrefix *e;
    float saved;
    float a;
    float b;

    *(TI128 *)vec = 0;
    vec[0] = obj->position[0];
    vec[1] = obj->position[1];
    vec[2] = obj->position[2];
    vec[3] = 2.0f;
    *(TI128 *)copy = *(TI128 *)vec;
    if (math_fast_helper_a(copy, 128.0f) <= 0)
        return 0;
    if (state->group == -1)
        return 0;
    for (p = g_group_id_lists[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= g_tribe_group_limit && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == g_group_id_lists[state->group]);
         p++) {
        e = (EntityPositionPrefix *)(g_moby_l11_table[0] + ((*p & 0x7FFF) << 8));
        if (e == 0)
            return 0;
        if (!moby_get_busy_flag(e))
            continue;
        if (!(vec_distance_xy(obj->position, e->position) < g_enemy_aim_range_b))
            continue;
        a = mat_fast_helper_a(e->position[0] - obj->position[0], e->position[1] - obj->position[1]);
        if (!(FastDiffRots(obj->heading, a) < g_enemy_aim_cone_deg_b * 0.017453294f))
            continue;
        if (p == 0)
            return 0;
        FastVecSub(vec, obj->position, e->position);
        b = g_enemy_aim_turn_deg_b * 0.017453294f;
        a = mat_fast_helper_a(e->position[0] - obj->position[0], e->position[1] - obj->position[1]);
        math_apply_axis_rotation_to_quat(vec, vec, obj->orientation,
                      fast_subtract_rotations(obj->heading, a) >= 0.0f ? -b : b);
        FastVecAdd(vec, vec, e->position);
        saved = state->f134;
        state->f134 = 0.0001f;
        moby_l01_turn_toward_target_pal(obj, vec);
        state->f134 = saved;
        return 1;
    }
    return 0;
}
