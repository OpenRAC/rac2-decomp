#include "common.h"

extern void func_00282C78(f32 *, f32 *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern f32 D_001B2050[] __attribute__((sda));
extern f32 D_001B2060[] __attribute__((sda));
extern f32 D_001B2070[4] __attribute__((sda));

void func_002DF640(f32 *dir, f32 scale) {
    f32 v[4] __attribute__((aligned(16)));

    qcopy(D_001B2050, dir);
    func_00282C78(v, dir);
    FastVecScale(D_001B2070, D_001B2050, scale);
    if (v[0] < v[1]) {
        if (v[0] < v[2]) {
            D_001B2060[0] = v[0];
            D_001B2060[1] = v[2];
            D_001B2060[2] = v[1];
        } else {
            D_001B2060[0] = v[1];
            D_001B2060[1] = v[0];
            D_001B2060[2] = v[2];
        }
    } else if (v[1] < v[2]) {
        D_001B2060[0] = v[2];
        D_001B2060[1] = v[1];
        D_001B2060[2] = v[0];
    } else {
        D_001B2060[0] = v[1];
        D_001B2060[1] = v[0];
        D_001B2060[2] = v[2];
    }
    FastVecCross(D_001B2060, D_001B2060, D_001B2050);
    vec_scale_to_length(D_001B2060, D_001B2060, 1.0f);
}
