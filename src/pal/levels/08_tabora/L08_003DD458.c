#include "names.h"
/* func_PAL_L08_003DD458, the PAL copy of func_L08_003D92D8: the same C, where 240 becomes 200;
   0.0017453294713050127f becomes 0.0025132746f; 0.10471977293491364f becomes 0.12566373f; 0.02f
   becomes 0.028800001f; 0.4f becomes 0.57600003f. */
#include "common.h"

extern u8 g_hero_position_vec[];
extern f32 fast_vec_dist(void *, void *);

extern void moby_transform_joint_to_world(void *, int, void *);

typedef struct {
    u8 pad00[0x20];
    u8 f20;
    u8 f21;
    u8 pad22[0x24 - 0x22];
    void *f24;
    u8 pad28[0x2C - 0x28];
    f32 f2C;
    u8 pad30[0x68 - 0x30];
    void *f68;
    u8 pad6C[0x95 - 0x6C];
    u8 f95;
    u16 f96;
    u8 pad98[0xBC - 0x98];
    u8 fBC;
    u8 padBD[0x100 - 0xBD];
} Ent;

typedef int V4 __attribute__((mode(TI)));

extern s32 func_3357E8(Ent *, void *, s32);
extern void func_2FA0B8(void *, void *, f32);

extern float vec_distance_xy(void *, void *);

typedef struct {
    int mode;
    char pad4[8];
    int active;
    char pad10[0x18];
    float lower;
    char pad2C[12];
    float upper;
} HeightGate;
typedef struct {
    u8 pad0[0x80];
    V4 position;
    u8 pad90[0x40];
    V4 other;
    u8 padE0[0x21B0];
    int handle;
} HeroTarget;
extern HeroTarget g_hero_state;
extern HeightGate g_init_context;
extern char g_collision_aim_vector[];
extern int GetCollHitMaterial(void);
extern void moby_update_ground_check(void *);
extern void moby_store_ground_height(void *);
extern void euler_to_matrix(void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern float mat_fast_helper_a(float, float);
extern float math_approach_target_with_direction_mode(void *, void *, float, float, float, float, int);
extern float fast_subtract_rotations(float, float);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void matrix_mul_vec3(void *, void *, void *);

extern void crawler_release_sounds(Ent *a0);
void func_PAL_L08_003DD458(u8 *object)
{
    float point[4], angles[4], matrix[16], inverse[16], other[16];
    char *state = *(char **)(object + 0x68);
    float yaw, pitch, target;
    float pointX, pointY;
    float *pitchAngle, *rollAngle;
    int hit;

    if (g_init_context.active) {
        if (*(float *)(object + 0x18) < g_init_context.lower && g_init_context.mode == 1) return;
        if (g_init_context.lower < *(float *)(object + 0x18) && g_init_context.mode == 0) return;
        if (g_init_context.active == 2) {
            if (g_init_context.upper < *(float *)(object + 0x18) && g_init_context.mode == 1) return;
            if (*(float *)(object + 0x18) < g_init_context.upper && g_init_context.mode == 2) return;
        }
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, g_hero_position_vec) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 22;
    }
    moby_store_ground_height(object);
    if (*(float *)(object + 0x18) < *(float *)(state + 0x434) + 0.12f) {
        if (GetCollHitMaterial() == 1 || GetCollHitMaterial() == 11) {
            *(int *)(state + 0x20) = 0;
            object[0x20] = 11;
            return;
        }
    }
    *(float *)(object + 0x2C) +=
        (*(float *)(*(char **)(object + 0x24) + 0x24) * 1.7f - *(float *)(object + 0x2C)) * 0.05f;
    hit = func_3357E8((Ent *)object, state + 0x50, 0);
    if (hit) {
        if (hit == 5) *(int *)(state + 0xE0) = 0;
        *(int *)(state + 0x48C) = 200;
        crawler_release_sounds((Ent *)object);
    }
    if (object[0x20] < 9 && object[0x20] != 4) {
        pitchAngle = (float *)(object + 0xF4);
        rollAngle = (float *)(object + 0xF0);
        *(V4 *)angles = 0;
        angles[2] = *(float *)(object + 0xF8);
        *(V4 *)point = *(V4 *)angles;
        euler_to_matrix(matrix, point);
        matrix_from_basis_rows(inverse, matrix);
        matrix_from_basis_rows(other, object + 0xC0);
        coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        func_2FA0B8(angles, g_collision_aim_vector, 1.0f);
        matrix_mul_vec3(angles, angles, inverse);
        target = mat_fast_helper_a(angles[2], angles[0]);
        math_approach_target_with_direction_mode(pitchAngle, state + 0x460, target, 0.0025132746f,
                      0.0025132746f, 0.12566373f, 0);
        target = -mat_fast_helper_a(angles[2], angles[1]);
        math_approach_target_with_direction_mode(rollAngle, state + 0x464, target, 0.0025132746f,
                      0.0025132746f, 0.12566373f, 0);
    }
    if (object[0x20] == 8 && !object[0x95]) {
        moby_transform_joint_to_world(object, 1, point);
        if (*(int *)(state + 0x250) == g_hero_state.handle) {
            qcopy(state + 0x210, &g_hero_state.position);
            qcopy(state + 0x230, &g_hero_state.other);
        }
        pointY = point[1];
        pointX = point[0];
        yaw = mat_fast_helper_a(*(float *)(state + 0x230) - pointX, *(float *)(state + 0x234) - pointY);
        pitch = mat_fast_helper_a(vec_distance_xy(point, state + 0x230), *(float *)(state + 0x238) - point[2]);
        yaw = fast_subtract_rotations(yaw, *(float *)(object + 0xF8)) * 0.5f;
        pitch = fast_subtract_rotations(-pitch, *(float *)(object + 0xF4)) * 0.3333333432674408f;
        {
            int i;
            for (i = 0; i < 3; i++) {
                *(float *)(state + 0x2C8 + i * 0x80) = yaw;
                if (yaw > 0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = 0.523598849773407f;
                else if (yaw < -0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = -0.523598849773407f;
                *(float *)(state + 0x2C4 + i * 0x80) = pitch;
            }
        }
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            *(float *)(state + 0x2C0 + i * 0x80) = 0;
            *(float *)(state + 0x2C4 + i * 0x80) = 0;
        }
    }
    {
        int i;
        for (i = 0; i < 3; i++) moby_update_eased_node(object, state + 0x260 + i * 0x80, 3, 0.028800001f, 0.57600003f);
    }
}
