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
extern L07Base D_L07_001BCF00;
typedef struct {
    u8 pad00[0x20];
    Vec2 m[4];
    u8 pad60[0x08];
    s32 f68;
} L07Mat;
extern L07Mat D_L07_0027E8C0;
extern int D_L07_001A93E0 __attribute__((sda));
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

void func_PAL_L07_002F4618(void) {
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
        if (D_L07_001BCF00.timer >= 0x526)
            D_L07_001BCF00.f50 = 0;
    }
    if (D_L07_001BCF00.type == 3) {
        if (D_L07_001BCF00.timer < 0x43)
            D_L07_001BCF00.f50 = 0;
    }
}
