#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void mat_get_euler_angles(void *, void *);
extern void func_PAL_002A7650(void *, int, int);
extern void PlayMobySound(int, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern char g_hero_position[];
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_and_set_height(void *, void *, void *, int, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_below(int);
extern void func_PAL_002B15D8(void *, int, void *, int, float, float, float, float);
extern void moby_mark_spawned(void *);
typedef int s32;
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001A8FF0 __attribute__((sda));

void func_PAL_L12_0042D378(char *obj) {
    char pos[16];
    union { TI128 q; float f[4]; } offset;
    char dir[16];
    int color;
    if (*(short *)(*(char **)(obj + 0x68) + 0x358))
        mat_get_euler_angles(obj + 0xC0, obj + 0xF0);
    func_PAL_002A7650(obj, 0, 3);
    PlayMobySound(1, 0, obj);
    offset.q = 0;
    offset.f[2] = 0.75f;
    matrix_mul_vec3(pos, &offset, obj + 0xC0);
    FastVecAdd(pos, pos, obj + 0x10);
    func_PAL_002AD288(obj, pos, -1, 0.3330000042915344f, 0.0f);
    FastVecSub(dir, obj + 0x10, g_hero_position);
    vec_transform_and_set_height(obj, dir, dir, 0, 0.0f);
    vec_scale_to_length(dir, dir, 0.120000005f);
    color = D_L12_001A8FF0 ? math_random_int_below(0xFF) : 0xFF;
    func_PAL_002B15D8(obj, color & 0x1F, dir, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(obj);
}


