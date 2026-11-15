#include "include_asm.h"
#include "common.h"

typedef float V4_2EE238[4] __attribute__((aligned(16)));

extern float D_001AC240 __attribute__((sda));
extern float D_001AC244 __attribute__((sda));
extern float D_001AC248 __attribute__((sda));

extern char *func_002ED688(char *);
extern void func_002EE3B0(char *);
extern void func_00282C88(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282C48(float);
extern float func_00282DF0(void *);

/* One step of a follower: it is pulled towards its target and kept at its ride
   height, with the speed clamped, then moved. */
void func_002EE238(char *owner)
{
    char *o = func_002ED688(owner);
    char *vel;
    char *pull;
    char *pos;
    V4_2EE238 t;
    float h, k, len;

    if (o == 0)
        return;
    func_002EE3B0(owner);
    vel = o + 0xC0;
    pull = o + 0x80;
    pos = o + 0x90;
    func_00282C88(vel);
    FastVecSub(pull, o + 0x60, owner + 0x10);
    vec_scale_to_length(t, pull, D_001AC240);
    FastVecAdd(vel, t, vel);
    qcopy(t, pos);
    h = (*(float *)(o + 0x124) - D_001AC248 * 0.5f) / D_001AC248;
    k = func_00282C48(h);
    if (k < D_001AC240)
        k = D_001AC240;
    if (D_001AC244 < k)
        k = D_001AC244;
    if (0.0f < h)
        k = -k;
    vec_scale_to_length(t, t, k);
    FastVecAdd(vel, t, vel);
    len = FastVecLength(vel);
    k = D_001AC240 * D_001AC248;
    if (k < len)
        vec_scale_to_length(vel, vel, k);
    qcopy(o + 0xA0, pos);
    FastVecAdd(pos, vel, pos);
}
