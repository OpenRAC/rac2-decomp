#include "include_asm.h"

#include "common.h"

extern char *g_snowfall_moby __attribute__((sda));

extern float func_2E5480(float offset, float a1);

extern void func_338D20(int offset, int a1, char *a2, void *a3, int a4, float f12);

extern void func_2E4B70(char *offset, void *a1);

/* Updates the snow effect object using the given value to set its sound or brightness. */
void snow_emitter_update_effect(float offset) {
    char *vars = *(char **)(g_snowfall_moby + 0x68);
    int pos2;

    func_338D20(*(int *)(vars + 0x14), 1, vars + 0x50, &pos2, 0, func_2E5480(offset + 45.0f, 1000.0f));
    func_2E4B70(vars + 0x20, &pos2);
}

extern int g_current_map_index;

/* The engine's VU0 pair: two doubles, sixteen bytes. */
typedef struct {
    double x;
    double y;
} Vec2;

/* The level object this function drives. */
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

extern L07Base D_L07_001BCF00;

/* The matrix the level object points at. */
typedef struct {
    u8 pad00[0x20];
    Vec2 m[4];
    u8 pad60[0x08];
    s32 f68;
} L07Mat;

extern L07Mat D_L07_0027E8C0;

/* The four records the engine reads through $gp. */
extern int D_L07_001A93E0 __attribute__((sda));

/* The object the level object names. */
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

extern void matrix_mul_vec3(Vec2 *out, Vec2 *in, Vec2 *mat);

extern void FastVecScale(Vec2 *out, Vec2 *in, f32 scale);

extern void FastVecAdd(Vec2 *out, Vec2 *in, Vec2 *add);

/* Places four marker points around the level object, scaled and turned to match the object it follows. */
void moby_build_followed_points(void) {
    Vec2 mat[3];
    Vec2 buf[3];
    void *obj;
    int idx;
    f32 scale;
    L07Mat *g;
    Vec2 *p;
    Vec2 *q;
    int i;

    if (g_current_map_index != 7)
        return;

    obj = 0;
    idx = -1;
    switch (D_L07_001BCF00.type) {
    case 2:
        obj = D_L07_001BCF00.obj;
        idx = 2;
        break;
    case 3:
        obj = D_L07_001BCF00.obj;
        idx = 2;
        break;
    }
    if (idx == -1)
        goto end;
    if (obj == 0)
        goto end;
    if (D_L07_001BCF00.slot[idx] == 0)
        goto end;

    g = &D_L07_0027E8C0;
    D_L07_001BCF00.f50 = g;
    p = &g->m[0];
    q = (Vec2 *)&D_L07_001A93E0;

    vec_fast_to_int_helper((u8 *)((L07Obj *)obj)->f58 + 0x10, buf);
    quaternion_to_rotation_basis(buf, mat);
    scale = ((L07Obj *)obj)->f2C / *(f32 *)((u8 *)((L07Obj *)obj)->f24 + 0x24);

    for (i = 0; i < 4; i++) {
        matrix_mul_vec3(p, q, mat);
        FastVecScale(p, p, scale);
        FastVecAdd(p, p, (Vec2 *)((u8 *)obj + 0x10));
        p++;
        q++;
    }

    ((L07Mat *)D_L07_001BCF00.f50)->f68 = D_L07_001BCF00.slot[idx];

end:
    if (D_L07_001BCF00.type == 2) {
        if (D_L07_001BCF00.timer >= 0x62D)
            D_L07_001BCF00.f50 = 0;
    }
    if (D_L07_001BCF00.type == 3) {
        if (D_L07_001BCF00.timer < 0x50)
            D_L07_001BCF00.f50 = 0;
    }
}
