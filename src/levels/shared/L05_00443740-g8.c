#include "common.h"

extern char *D_L05_001B1EC4, *D_L05_001B251C;
typedef struct {
    char pad[0x7C];
    int timer, flag;
} DriverState;
extern DriverState D_L05_00221D10;
extern char D_L05_002B8770[];
extern float D_L05_001B1A84 __attribute__((sda));
extern float D_L05_001B1A7C __attribute__((sda));
extern float D_L05_001B1A80 __attribute__((sda));
extern float D_L05_001B1BF8 __attribute__((sda));
extern float D_L05_001B1BFC __attribute__((sda));
extern float D_L05_001B1A98 __attribute__((sda));
/* The direction has an unknown complete extent; only its GP address is needed. */
extern float direction[] SDATA(D_L05_001B1C00);

extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_002702C8(float, float, float, float, float, void *);
extern float func_00283CE0(int);
extern float func_002A7C00(float, float, float);
extern float func_002ABB18(float);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern int func_00282948(void *);
extern void func_L00_002D6998(void *);
extern void func_L05_00445338(void *, void *);
extern void func_L05_00443C18(void *, void *);
extern void func_L05_00418508(void *);
extern void func_L05_00443D08(void *, void *);
extern void func_L05_004445E8(void *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L05_00444B20(void);
extern void func_L05_00445D60(void);

#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))

/* Updates the driven moby position and rebuilds its basis, including bank and roll. */
void func_L05_00443740(char *obj)
{
    char old[16] __attribute__((aligned(16)));
    char a[16] __attribute__((aligned(16)));
    char b[16] __attribute__((aligned(16)));
    char c[16] __attribute__((aligned(16)));
    char d[16] __attribute__((aligned(16)));
    char e[16] __attribute__((aligned(16)));
    char rotation[16] __attribute__((aligned(16)));
    char *input = P(obj, 0x70) + 0x50;
    char *moby = D_L05_001B251C +
        (I(P(D_L05_001B1EC4 + H(obj, 0x84) * 32, 0x1C), 0x20) << 8);
    char *state = P(moby, 0x68);
    float t, angle;
    float forward;

    qcopy(old, moby + 0x10);
    forward = D_L05_001B1A7C;
    F(moby, 0x2C) = F(P(moby, 0x24), 0x24) * D_L05_001B1A84;
    FastVecScale(a, obj, forward);
    FastVecAdd(moby + 0x10, obj + 0x30, a);
    FastVecScale(b, obj + 0x20, D_L05_001B1A80);
    FastVecAdd(moby + 0x10, moby + 0x10, b);
    t = -F(input, 0x68) / (F(input, 0x78) * 0.017453294f);
    if (t > 1.0f) t = 1.0f;
    else if (t < -1.0f) t = -1.0f;
    FastVecScale(c, obj + 0x10, F(state, 0x250) * t);
    FastVecAdd(moby + 0x10, moby + 0x10, c);
    t = F(input, 0x64) / (F(input, 0x74) * 0.017453294f);
    if (t < 0.0f) {
        t *= F(state, 0x24C);
        if (t < -1.0f) t = -1.0f;
    } else if (t > 1.0f) {
        t = 1.0f;
    }
    F(state, 0xC) = func_002702C8(F(state, 0xC), t, D_L05_001B1BF8,
                                  D_L05_001B1BFC, 0.0f, state + 0x10);
    FastVecScale(b, obj + 0x20, F(state, 0x254) * F(state, 0xC));
    FastVecAdd(moby + 0x10, moby + 0x10, b);
    if (D_L05_00221D10.flag) {
        if (!func_00282948(&D_L05_00221D10.timer)) {
            func_L00_002D6998(D_L05_002B8770);
        } else {
            D_L05_00221D10.flag = 0;
            D_L05_00221D10.timer = 7;
        }
    }
    ResolveLinkedMobyMovementCollisions(obj, old);
    func_L05_00443C18(obj, moby);
    FastVecSub(d, state + 0x20, obj + 0x30);
    vec_scale_to_length(d, d, D_L05_001B1A98);
    FastVecAdd(e, obj + 0x30, d);
    FastVecSub(moby + 0xC0, e, moby + 0x10);
    vec_scale_to_length(moby + 0xC0, moby + 0xC0, 1.0f);
    FastVecCross(moby + 0xD0, moby + 0xC0, obj + 0x20);
    vec_scale_to_length(moby + 0xD0, moby + 0xD0, 1.0f);
    FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
    I(moby, 0xCC) = 0;
    I(moby, 0xDC) = 0;
    I(moby, 0xEC) = 0;
    angle = (-F(input, 0x68) / (F(input, 0x78) * 0.017453294f)) *
            0.017453294f * F(state, 0x258);
    {
        char *turn = P(obj, 0x70) + 0xD4;
        if (H(turn, 4)) {
            float wave = IntToFloat(H(turn, 6));
            wave = func_002A7C00(1.0f, 0.0f, wave * F(turn, 8));
            wave = func_002ABB18(wave * 12.566371f);
            if (H(turn, 4) == -1) wave = -wave;
            angle = FastAddRotations(angle, wave);
        }
    }
    if (func_00282C48(angle) > 0.00001f) {
        func_002AB668(rotation, moby + 0xC0, angle);
        func_002ACDE8(moby + 0xD0, moby + 0xD0, rotation);
        func_002ACDE8(moby + 0xE0, moby + 0xE0, rotation);
    }
    FastVecScale(rotation, direction, 0.05f);
    matrix_mul_vec3(rotation, rotation, moby + 0xC0);
    FastVecAdd(moby + 0x10, moby + 0x10, rotation);
    func_L05_00418508(moby);
    UpdateShipWeapons(moby, obj);
    func_L05_004445E8(moby);
    func_L00_002E6CF0(func_L05_00444B20, moby);
    func_L00_002E6EF8(func_L05_00445D60, moby);
}
