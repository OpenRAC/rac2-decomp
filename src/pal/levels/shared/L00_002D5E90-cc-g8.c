/* func_PAL_L00_002D5E90, the PAL copy of func_L00_002D5940: the same C. */
#include "common.h"

/* func_PAL_L00_002D5E90 is here rather than in L00_002D3798.c because its tuning floats are read
   through $gp (-G8). */

typedef int Quad5940 __attribute__((mode(TI)));

typedef struct {
    float bounds[4];            /* 0x00; [3] is the radius */
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x10];
    unsigned char drawn;        /* 0x31 */
    char pad32[0x2];
    unsigned short modeBits;    /* 0x34 */
    char pad36[0x2E];
    void (*update)(void *);     /* 0x64 */
    char pad68[0x42];
    short oClass;               /* 0xAA */
    char padAC[0x14];
    float rotMatrix[3][4];      /* 0xC0 */
    float rotation[4];          /* 0xF0 */
} Moby5940;

typedef struct {
    char pad0000[0x80];
    float position[4];          /* 0x0080 */
    char pad0090[0xC0];
    float velocity[4];          /* 0x0150 */
    char pad0160[0x14];
    float speed;                /* 0x0174 */
    char pad0178[0x5B8];
    float transform[12];        /* 0x0730 */
    Quad5940 vector760;         /* 0x0760 */
    Quad5940 vector770;         /* 0x0770 */
    char pad0780[0xAA0];
    Moby5940 *object;           /* 0x1220 */
    char pad1224[0xC];
    int flags;                  /* 0x1230 */
    char pad1234[0x8];
    unsigned char visible;      /* 0x123C */
    char pad123D[0xB];
    int weapon;                 /* 0x1248 */
    char pad124C[0x254];
    float transitionPos[4];     /* 0x14A0 */
    float transitionRot[4];     /* 0x14B0 */
    float rotation[4];          /* 0x14C0 */
    char pad14D0[0x28];
    float blend;                /* 0x14F8 */
    float blendVelocity;        /* 0x14FC */
    char pad1500[0x4];
    float offsetVelocity;       /* 0x1504 */
    float offset;               /* 0x1508 */
    float offsetTarget;         /* 0x150C */
    float angle;                /* 0x1510 */
    float angleVelocity;        /* 0x1514 */
    char pad1518[0xD78];
    int owner;                  /* 0x2290 */
} Hero5940;

extern Hero5940 g_hero_state;
extern char g_cam_follow_matrix[], g_camera_l00_position[], g_hero_l00_position[];
extern Quad5940 g_hero_saved_vector;
/* Incomplete sda arrays are read with the assembler's lui/load macro, as in retail. */
extern unsigned char g_cheat_flags[] __attribute__((sda));
extern int g_frame_l00_counter[] __attribute__((sda));
extern float g_turn_rate_table[] __attribute__((sda));
extern const float g_turn_rate_scale __attribute__((sda));
extern float g_hero_item_time_scale __attribute__((sda)), g_hero_item_step_scale __attribute__((sda));

extern int hero_is_slot_item_wrench(int);
extern void func_002A0F48(void *);
extern char *level_get_table_entry_address(int);
extern int hero_is_action_allowed(void);
extern void copy_matrix_rotation(void *, void *);
extern f32 ApproachValue(float *, float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern float FastAddRotations(float, float), math_fast_sin_or_cos_b(float);
extern void transform_vector(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void euler_to_matrix(void *, void *), multiply_matrix3x3(void *, void *, void *);
extern void mat_get_euler_angles(void *, void *), mat_build_rotation_from_angles(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *), lerp_vector(void *, void *, void *, float);
extern void vec_fast_normalize3(void *, void *, void *, float), quaternion_to_rotation_basis(void *, void *);
extern void FastVecScale(void *, void *, float), vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void copy_matrix3x4(void *, void *);

/* Places the hero's held object (D_00189E20.object): from the weapon's mount offset and
   rotation, a turning bob angle, the blend from the transition pose while blend < 1, and a
   ground probe that limits the vertical offset to [-1.5, 0]. */
void UpdateHeroHeldObject_pal(void) {
    Moby5940 *obj = g_hero_state.object;
    char *mount;
    float m[16], rot[16], offset[4], temp[4], a[4], b[4];
    float turn, height, scale, target;
    int state;

    if (!obj)
        return;
    if (obj->oClass == 0x47) {
        if (!g_hero_state.visible && !obj->state) {
            obj->drawn = 0;
            obj->modeBits |= 1;
        } else {
            obj->drawn = 1;
            obj->modeBits &= ~1;
        }
        return;
    }
    if (hero_is_slot_item_wrench(0)) {
        obj->modeBits |= 1;
        obj->drawn = 0;
        if (obj->update)
            obj->update(obj);
        func_002A0F48(obj);
        return;
    }

    mount = level_get_table_entry_address(g_hero_state.weapon);
    copy_matrix_rotation(m, g_cam_follow_matrix);
    qcopy_nc(&m[12], g_cam_follow_matrix - 0x230);
    m[15] = 1.0f;
    qcopy_nc(offset, mount);
    offset[0] += g_hero_state.offset;
    if (g_cheat_flags[0] && !hero_is_action_allowed())
        offset[1] = -offset[1];

    /* Turn rate in degrees per second (FE4 while moving, FE0 otherwise) to radians per frame. */
    if (g_hero_state.speed > 0.02f)
        turn = g_turn_rate_table[0] * 0.0003490659f;
    else
        turn = g_turn_rate_scale * 0.0003490659f;
    ApproachValue(&g_hero_state.angleVelocity, turn, 0.010053098f);
    g_hero_state.angle = FastAddRotations(g_hero_state.angle, g_hero_state.angleVelocity);
    offset[2] += math_fast_sin_or_cos_b(g_hero_state.angle) * 0.02f;

    transform_vector(obj->position, offset, m);
    if (!hero_is_action_allowed())
        FastVecAdd(obj->position, obj->position, g_hero_state.velocity);
    euler_to_matrix(rot, mount + 0x10);
    multiply_matrix3x3(obj->rotMatrix, m, rot);
    mat_get_euler_angles(obj->rotMatrix, obj->rotation);
    mat_build_rotation_from_angles(g_hero_state.rotation, obj->rotation);

    if (g_hero_state.blend < 1.0f) {
        math_step_value_toward_target(&g_hero_state.blend, &g_hero_state.blendVelocity, 1.0f,
                      g_hero_item_time_scale * 0.020000001f, g_hero_item_step_scale * 0.00040000002f,
                      g_hero_item_time_scale * 0.020000001f);
        matrix_mul_vec3(temp, g_hero_state.transitionPos, &g_hero_state);
        FastVecAdd(temp, temp, g_hero_state.position);
        lerp_vector(obj->position, temp, obj->position, g_hero_state.blend);
        mat_build_rotation_from_angles(a, obj->rotation);
        vec_fast_normalize3(b, g_hero_state.transitionRot, a, g_hero_state.blend);
        quaternion_to_rotation_basis(b, obj->rotMatrix);
    }

    obj->drawn = 1;
    obj->modeBits &= ~1;
    func_002A0F48(obj);

    if ((g_frame_l00_counter[0] ^ 1) & 1) {
        scale = 0.0009765625f;
        height = obj->bounds[3] * scale;
        FastVecScale(temp, obj->bounds, scale);
        vec_scale_to_length(a, obj->rotMatrix[1], height * -1.2f);
        FastVecAdd(a, a, temp);
        if (CollLine(g_camera_l00_position, a, 0, g_hero_state.owner, 0)) {
            target = (g_hero_state.offset - height) + fast_vec_dist(g_hero_l00_position, temp);
            g_hero_state.offsetTarget = target;
            if (target > 0.0f)
                g_hero_state.offsetTarget = 0.0f;
            else if (target < -1.5f)
                g_hero_state.offsetTarget = -1.5f;
        } else {
            g_hero_state.offsetTarget = 0;
        }
    }

    math_step_value_toward_target(&g_hero_state.offset, &g_hero_state.offsetVelocity, g_hero_state.offsetTarget,
                  0.006f, 0.006f, 0.10000001f);
    copy_matrix3x4(g_hero_state.transform, m);
    qcopy_nc(&g_hero_state.vector760, m);
    qcopy_nc(&g_hero_state.vector770, &g_hero_saved_vector);

    state = hero_is_action_allowed();
    if (state)
        g_hero_state.flags |= 5;
    if (obj->update)
        obj->update(obj);
    if (state)
        g_hero_state.flags &= ~5;
}
