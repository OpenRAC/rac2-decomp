#include "include_asm.h"
#include "common.h"
extern int g_current_map_index;
typedef struct {
    double x;
    double y;
} Vec2;
typedef struct {
    u8 pad00[0x30];
    s32 type;
    s32 timer;
    u8 pad38[0x18];
    void *f50;
    u8 pad54[0x138];
    s32 slot[4];
    void *obj;
} L07Base;
extern L07Base g_followed_points_state;
typedef struct {
    u8 pad00[0x20];
    Vec2 m[4];
    u8 pad60[0x08];
    s32 f68;
} L07Mat;
extern L07Mat g_followed_points_matrix;
extern int g_followed_point_vec __attribute__((sda));
typedef struct {
    u8 pad00[0x24];
    void *f24;
    u8 pad28[0x04];
    f32 f2C;
    u8 pad30[0x28];
    void *f58;
} L07Obj;
extern void vec_fast_to_int_helper(void *src, Vec2 *dst);
extern void quaternion_to_rotation_basis(Vec2 *src, Vec2 *dst);
extern void matrix_mul_vec3(Vec2 *out, Vec2 *in, Vec2 *rotation);
extern void FastVecScale(Vec2 *out, Vec2 *in, f32 scale);
extern void FastVecAdd(Vec2 *out, Vec2 *in, Vec2 *add);

/* Places four marker points around the level object, scaled and turned to match the object it follows. */
void moby_build_followed_points_pal(void) {
    Vec2 rotation[3];
    Vec2 quat[3];
    void *followed_obj;
    int slot_index;
    f32 scale;
    L07Mat *points_matrix;
    Vec2 *point;
    Vec2 *base_point;
    int i;

    if (g_current_map_index != 7)
        return;

    followed_obj = 0;
    slot_index = -1;
    switch (g_followed_points_state.type) {
    case 2:
        followed_obj = g_followed_points_state.obj;
        slot_index = 2;
        break;
    case 3:
        followed_obj = g_followed_points_state.obj;
        slot_index = 2;
        break;
    }
    if (slot_index == -1)
        goto end;
    if (followed_obj == 0)
        goto end;
    if (g_followed_points_state.slot[slot_index] == 0)
        goto end;

    points_matrix = &g_followed_points_matrix;
    g_followed_points_state.f50 = points_matrix;
    point = &points_matrix->m[0];
    base_point = (Vec2 *)&g_followed_point_vec;

    vec_fast_to_int_helper((u8 *)((L07Obj *)followed_obj)->f58 + 0x10, quat);
    quaternion_to_rotation_basis(quat, rotation);
    scale = ((L07Obj *)followed_obj)->f2C / *(f32 *)((u8 *)((L07Obj *)followed_obj)->f24 + 0x24);

    for (i = 0; i < 4; i++) {
        matrix_mul_vec3(point, base_point, rotation);
        FastVecScale(point, point, scale);
        FastVecAdd(point, point, (Vec2 *)((u8 *)followed_obj + 0x10));
        point++;
        base_point++;
    }

    ((L07Mat *)g_followed_points_state.f50)->f68 = g_followed_points_state.slot[slot_index];

end:
    if (g_followed_points_state.type == 2) {
        if (g_followed_points_state.timer >= 0x526)
            g_followed_points_state.f50 = 0;
    }
    if (g_followed_points_state.type == 3) {
        if (g_followed_points_state.timer < 0x43)
            g_followed_points_state.f50 = 0;
    }
}
