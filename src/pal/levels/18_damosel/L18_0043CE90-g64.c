#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_L18_001B1B40[16] __attribute__((sda));
extern int D_L18_001B1B30 __attribute__((sda));
extern float D_L18_001B1B08[2] __attribute__((sda));
extern float D_L18_001B1B00[2] __attribute__((sda));
extern float D_L18_001B1B10[4] __attribute__((sda));
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void vec_local_to_world(void *, void *, float, float, float);
extern void *part_spawn_object_following_effect(void *, void *, int, int, int, int, int, int, float, float);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void moby_mark_spawned(void *);

void func_PAL_L18_00441B80(u8 *obj) {
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68), *p;
    int i, x, y;
    float *q, *ap, *bp;

    switch (obj[0x20]) {
    case 0:
        i = 0;
        bp = b;
        ap = a;
        y = 20;
        x = 4;
        q = D_L18_001B1B40;
        for (; i < 4; i++, y -= 8, x -= 8, q += 4) {
            FastVecScale(v, q, *(float *)(obj + 0x2C));
            part_spawn_object_following_effect(v, obj, 0x28808080, -1, 0, -1, 0, 0x60,
                             *(float *)(obj + 0x2C) * 1050000.f, .15f);
            vec_local_offset_to_world(obj, ap, q[0], q[1], q[2]);
            qcopy(bp, ap);
            if (i < 2) {
                vec_local_to_world(obj, bp, (float)x, 0, -4.f);
            } else {
                vec_local_to_world(obj, bp, 0, (float)y, -4.f);
            }
            a[3] = .2f;
            b[3] = 1.f;
        }
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        p = part_find_owned_effect_slot(obj, 0x4010000, 0);
        if (p && !*(int *)state) {
            *(TI128 *)b = 0;
            b[0] = 3.f;
            b[1] = 3.f;
            *(float *)(p + 0x18) = .75f;
            FastVecScale(v, p + 0x10, math_random_float_range(6.f, 8.f));
            qcopy(a, v);
            FastVecSub(v, v, b);
            FastVecAdd(a, a, b);
            func_PAL_L00_0032C328(obj, v, D_L18_001B1B08, D_L18_001B1B00,
                             0xFFFF, -1, D_L18_001B1B30, 9, -128, 255, 0);
            moby_set_state(obj, 2, -1);
        }
        obj[0xA8] = 255;
        break;
    case 2:
        func_PAL_L00_0032C328(obj, D_L18_001B1B10, D_L18_001B1B08, D_L18_001B1B00,
                         0xFFFF, 0, D_L18_001B1B30, 6, 0xFA7F, 255, 0);
        vec_local_offset_to_world(obj, v, 0, 0, 20.f);
        func_PAL_L00_003FB330(v, 0, 5, 5, 5, 5, 5, 0, 1, 0, 1, 0,
                      *(float *)(obj + 0x2C) * 2.f, 20.f);
        moby_mark_spawned(obj);
        break;
    }
}
