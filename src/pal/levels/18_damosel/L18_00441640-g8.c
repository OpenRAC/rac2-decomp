#include "common.h"

extern void *part_find_owned_effect_slot(void *, int, int);
extern float func_PAL_002AA108(void *, void *);
extern void func_PAL_002AC290(void *, void *), func_PAL_002AC3C0(void *, void *);
extern void moby_set_state(void *, int, int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float), FastAddRotations(float, float);
extern int IsPointInCuboid(void *, int), flag_set_first_pending(void *);
extern void moby_mark_spawned(void *);
extern int math_fast_float_d(void *);
extern int PlayMobySound(int, int, void *);
extern char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_PAL_002B15D8(void *, int, void *, float, float, float, float, int);
extern void vec_scale_to_length(void *, void *, float), matrix_mul_vec3(void *, void *, void *), vec_add_random_offset(void *, float), FastVecAdd(void *, void *, void *);
extern u8 g_hero_position[];
extern u8 D_L18_001A8F20[] __attribute__((sda));
extern float D_L18_001B1AB0 __attribute__((sda));
extern float D_L18_001B1AB4 __attribute__((sda));
extern float D_L18_001B1AB8 __attribute__((sda));
extern float D_L18_001B1ABC __attribute__((sda));
extern float D_L18_001B1AC0 __attribute__((sda));
extern float D_L18_001B1AC4 __attribute__((sda));
extern float D_L18_001B1ACC __attribute__((sda));
extern int D_L18_001B1AD0 __attribute__((sda));
extern int D_L18_001B1AD4 __attribute__((sda));
extern u8 D_L18_001B1AE0[] SDATA(D_L18_001B1AE0);
extern u8 D_L18_001B1AF0[] SDATA(D_L18_001B1AF0);
extern u8 *protopet_count_group(int, int *);
extern void protopet_launch_shot(void *, void *, void *);

typedef struct {
    u8 pad00[0x20];
    float health;
    s16 initialized;
    u8 pad26[0xa];
    float scale;
    u8 pad34[0x1c];
    float transform[4];
    float turnX, turnY;
    u8 pad68[8];
    s32 startRegion, fireRegion, childId;
    float baseZ, velocityZ;
    s32 fireTimer;
} LauncherState;

typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 mode;
    u8 pad21[0x47];
    LauncherState *state;
    u8 pad6c[0x2a];
    u16 timer;
    u8 pad98[0x10];
    u8 opacity;
    u8 pada9[0x17];
    float matrix[12];
    float rotation[4];
} LauncherObject;

/* func_PAL_L18_00441640, the PAL copy of func_L18_0043C258: the same C, where the per-frame rates scale to
 * 50 Hz and the fire delay goes through ((s32)(x) * 5 + 2) / 6. */
void func_PAL_L18_00441640(LauncherObject *obj) {
    LauncherState *s = obj->state;
    u8 *child;
    float damage, z;
    float v[4] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    int zero;
    int low;

    damage = func_PAL_002AA108(obj, part_find_owned_effect_slot(obj, 0x10000, 0));
    s->health -= damage;
    if (damage > 0.0f) {
        func_PAL_002AC290(obj, s->transform);
        if (s->health <= 0.0f) {
            func_PAL_L00_003FB330(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
            func_PAL_002B15D8(obj, 0x3a, D_L18_001A8F20, 3, 6, 3, 6, 255);
            PlayMobySound(1, 0, obj);
            moby_mark_spawned(obj);
            return;
        }
    }
    obj->opacity = 255;
    func_PAL_002AC3C0(obj, s->transform);
    switch (obj->mode) {
    case 0:
        s->baseZ = obj->position[2];
        if (!s->initialized) {
            s->initialized = 1;
            s->health = 1;
        }
        s->fireTimer = -1;
        s->scale = 1;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (s->startRegion != -1 && IsPointInCuboid(g_hero_position, s->startRegion))
            moby_set_state(obj, 2, -1);
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            obj->rotation[0] = 0;
            obj->rotation[1] = 0;
            z = obj->rotation[0];
            obj->position[2] = s->baseZ;
            s->velocityZ += math_random_float_range(z, D_L18_001B1AB0 * 0.020000001f);
            s->turnX = math_random_float_range(z, D_L18_001B1AB4 * 0.0003490659f);
            s->turnY = math_random_float_range(z, D_L18_001B1AB8 * 0.0003490659f);
            obj->position[2] = s->baseZ;
            PlayMobySound(0, 0, obj);
        }
        if (obj->position[2] >= s->baseZ) {
            obj->position[2] += s->velocityZ;
            s->velocityZ -= D_L18_001B1ACC * 0.00040000002f;
            if (s->velocityZ > 0) {
                obj->rotation[0] = FastAddRotations(s->turnX, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(s->turnY, obj->rotation[1]);
            } else {
                obj->rotation[0] = FastAddRotations(-s->turnX, obj->rotation[0]);
                obj->rotation[1] = FastAddRotations(-s->turnY, obj->rotation[1]);
            }
        } else {
            moby_set_state(obj, 2, -1);
        }
        if (s->fireTimer == 0) {
            zero = 0;
            child = protopet_count_group(s->childId, &zero);
            if (child) {
                vec_scale_to_length(v, D_L18_001B1AF0, D_L18_001B1AC0 * 0.020000001f);
                matrix_mul_vec3(v, v, obj->matrix);
                vec_add_random_offset(v, D_L18_001B1ABC * 0.020000001f);
                matrix_mul_vec3(p, D_L18_001B1AE0, obj->matrix);
                FastVecAdd(p, p, obj->position);
                protopet_launch_shot(child, p, v);
                low = D_L18_001B1AD0;
                *(s32 *)(child + 0xB8) = (s32)obj;
                s->fireTimer = ((s32)math_random_int_range(low, D_L18_001B1AD4) * 5 + 2) / 6;
            }
        } else if (s->fireTimer == -1) {
            if (s->fireRegion != -1 && IsPointInCuboid(g_hero_position, s->fireRegion)) {
                s->fireTimer++;
                func_PAL_L00_003FB330(obj->position, 1, 25, 20, 20, 20, 45, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                PlayMobySound(1, 0, obj);
                vec_scale_to_length(v, D_L18_001B1AF0, D_L18_001B1AC4 * 0.020000001f);
                matrix_mul_vec3(v, v, obj->matrix);
                vec_add_random_offset(p, D_L18_001B1ABC * 0.020000001f);
                FastVecAdd(v, v, p);
                func_PAL_002B15D8(obj, 5, v, 3, 6, 3, 6, 255);
            }
        } else {
            math_fast_float_d(&s->fireTimer);
        }
        break;
    }
    if (obj->timer < 65535)
        (obj->timer)++;
}
