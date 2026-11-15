#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

typedef struct {
    u8 pad00[0x30];
    u8 *target;
} Vars31A848;

typedef struct {
    u8 pad00[0x68];
    Vars31A848 *vars;
} Moby31A848;

extern TI D_001A8BD0 MACRO_ADDR;

extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_002831B0(float);
extern void ref_L00_003BFC98_00(void *, void *, int);

/* Checks whether the target is turned away from where the object faces by more than the given number of degrees. Returns 1 if there is no target. */
int func_0031A848(Moby31A848 *self, float limit) {
    float up[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    float fwd[4] __attribute__((aligned(16)));
    float proj[4] __attribute__((aligned(16)));
    Vars31A848 *vars = self->vars;

    if (vars->target == 0) {
        return 1;
    }
    ref_L00_003BFC98_00(self, fwd, 1);
    qcopy(up, &D_001A8BD0);
    up[0] = 1.0f;
    matrix_mul_vec3(up, up, (u8 *)self + 0xC0);
    FastVecSub(dir, vars->target + 0x10, (u8 *)self + 0x10);
    vec_scale_to_length(dir, dir, 1.0f);
    vec_scale_to_length(proj, fwd, FastVecDot(fwd, dir));
    FastVecSub(dir, dir, proj);
    vec_scale_to_length(dir, dir, 1.0f);
    return limit * 0.017453294f < FloatAbs(1.5707964f - FastAngleHelper(FastVecDot(dir, up)));
}
