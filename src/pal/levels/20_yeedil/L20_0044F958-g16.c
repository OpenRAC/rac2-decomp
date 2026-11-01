#include "include_asm.h"

#include "common.h"
typedef int ProjectileQuadword __attribute__((mode(TI)));
typedef struct {
    u8 reserved00[0x18];
    u8 *object;
    int polygon;
    float correction[4], point[4], normal[4];
} CollisionView;
extern int D_L20_001A8F00;
extern CollisionView D_L20_001C0400;
extern u8 *D_0018C0B0 __attribute__((nosda));
extern float D_L20_001B23F8 __attribute__((sda));
extern float D_L20_001B23FC __attribute__((sda));
extern float D_L20_001B2400 __attribute__((sda));
extern float D_L20_001B2400_4[] MACRO_ADDR;
extern float D_L20_001B2408 __attribute__((sda));
extern void func_0029F338(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *), func_00282E20(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282F70(float, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_PAL_L20_0044FD80(char *, char *);
extern float func_002A7878(float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002A9288(char *, float);
extern void func_00282C98(void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_002ACE78(float *, float *, float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern int func_00282948(int *);

void func_PAL_L20_0044F958(u8 *moby)
{
    float rate;
    float previous[4] __attribute__((aligned(16)));
    float angles[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float basis[12] __attribute__((aligned(16)));
    float quaternion[4] __attribute__((aligned(16)));
    float spin[12] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    int collided;
    if (D_L20_001A8F00 == 2) { func_0029F338(moby); return; }
    if (moby[0x20] != 1) return;
    qcopy(previous, (float *)(moby + 0x10));
    collided = 0;
    func_00282CC0((float *)(moby + 0x10), (float *)(moby + 0x10), state);
    if (func_00282DF0(state) > D_L20_001B23F8 * 0.1f && func_002761F8(previous, (float *)(moby + 0x10), 2, moby, 0)) {
        collided = 1;
        func_00282F20((float *)(moby + 0x10), D_L20_001C0400.normal, 0.01f);
        func_00282CC0((float *)(moby + 0x10), (float *)(moby + 0x10), D_L20_001C0400.correction);
    }
    if (func_00277258((float *)(moby + 0x10), 0, moby, D_L20_001B23F8 * 0.1f)) {
        collided = 1;
        if (D_L20_001C0400.polygon < 0 &&
            (D_L20_001C0400.object != *(u8 **)(moby + 0xb8) || !*(int *)(state + 0x20)) &&
            *(short *)(D_L20_001C0400.object + 0xaa) != *(short *)(moby + 0xaa)) {
            func_PAL_L20_0044FD80((char *)moby, (char *)(D_L20_001C0400.object == D_0018C0B0 ? 0x10001 : 0x10000));
            return;
        }
        qcopy((float *)(moby + 0x10), D_L20_001C0400.point);
    }
    if (collided) *(float *)(state + 8) = func_002A7878(D_L20_001B2400, D_L20_001B2400_4[1]) * 0.020000001f;
    else *(float *)(state + 8) -= *(float *)(state + 0x10);
    rate = func_00282E20(state);
    func_002AA2E8(&rate, D_L20_001B23FC * 0.020000001f, 0.002f);
    func_00282F70(rate, state, state);
    *(ProjectileQuadword *)rotation = 0;
    rotation[2] = *(float *)(state + 0x14);
    *(ProjectileQuadword *)angles = *(ProjectileQuadword *)rotation;
    func_002833F0(basis, angles);
    func_00283098(state, state, basis);
    if (moby[0x31]) {
        func_002A9288((char *)moby, D_L20_001B2408);
        func_00282C98(rotation);
        func_00282DD8(quaternion, rotation, state);
        func_002ACE78(quaternion, quaternion, 0.031415932f);
        func_00283958(quaternion, spin);
        func_00283738(moby + 0xc0, spin, moby + 0xc0);
    }
    func_00282948((int *)(state + 0x20));
    if (func_00282948((int *)(state + 0x18))) func_PAL_L20_0044FD80((char *)moby, 0);
}
