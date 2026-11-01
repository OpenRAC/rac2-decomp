#include "include_asm.h"

#include "common.h"
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Vec;
typedef struct {
    char pad[0x80];
    float pos[4];
    char pad2[0x2200];
    char *hero;
    int mode;
} Globals;
extern Globals D_00189E20;
extern char D_L20_001A8F20[] __attribute__((sda));
extern float D_L20_001B2124 SDATA(D_L20_001B2124);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);
extern float func_00282E80(void *, void *);
extern float func_002A89A8(void *, int, float);
extern void func_L01_00322288(void *, float);
extern int func_PAL_L02_00333638(void *, void *, int, float, float, float);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C28(void *, void *, int, float, float, float, int, int,
                          int);
extern void func_PAL_L00_0038C620(void *);
extern void func_L02_003948D0(void *);
extern void func_002C9218(void *, void *, void *, float);

void func_PAL_L20_00447BE0(char *obj) {
    char *state = *(char **)(obj + 0x68);
    char *basis;
    char *hero;
    char *other;
    Vec pos;
    float angle;
    float rate;

    angle = func_00283248(D_00189E20.pos[0] - *(float *)(obj + 0x10),
                          D_00189E20.pos[1] - *(float *)(obj + 0x14));
    if (func_00283C80(*(float *)(obj + 0xF8), angle) < 1.57079637f) {
        angle = func_00283248(D_00189E20.pos[0] - *(float *)(obj + 0x10),
                              D_00189E20.pos[1] - *(float *)(obj + 0x14));
        func_L01_00322288(obj, angle);
    }
    *(int *)(D_00189E20.hero + 0x98) = 0;
    basis = state + 0xF0;
    func_PAL_L02_00333638(obj, D_L20_001A8F20, 0x10, *(float *)(obj + 0xF8), -1.0f, -1.0f);
    hero = D_00189E20.hero;
    *(int *)(hero + 0x98) = *(int *)(*(char **)(hero + 0x24) + 0x10);
    func_002AFDD8(obj, basis, basis, 0);
    *(int *)(state + 0xF4) = 0;
    func_00283098(basis, basis, obj + 0xC0);
    rate = (*(float *)(state + 0x100) + *(float *)(state + 0x100)) / *(float *)(state + 0x78);
    if (rate < 0.5f) {
        rate = 0.5f;
    }
    *(float *)(state + 0x1804) =
        func_00283B98(*(float *)(state + 0x1804), D_L20_001B2124 * (rate * 0.0003490659f));
    func_00282CC0(&pos, obj + 0xC0, obj + 0x10);
    func_002A8C28(obj, &pos, 0x10008, 3.0f, (float)*(u8 *)(state + 0x34), 2.0f, 0, 1, 0);
    qcopy(&pos, obj + 0x10);
    pos.f[2] += 5.0f;
    func_002A8C28(obj, &pos, 0x10000, 5.5f, 50.0f, 2.0f, 0, 1, 0);
    other = *(char **)(state + 0xD4);
    if (other) {
        if (*(short *)(other + 0xAA) == 0x1366) {
            func_PAL_L00_0038C620(other);
        } else if (*(short *)(other + 0xAA) == 0x1367) {
            func_L02_003948D0(other);
        }
    }
    if (D_00189E20.mode == 0x8C) {
        if (func_00282E80(D_00189E20.pos, obj + 0x10) <= 4.0f) {
            D_00189E20.pos[2] += 5.0f;
            D_00189E20.pos[2] = func_002A89A8(D_00189E20.pos, 0, 0.5f);
            *(short *)((char *)&D_00189E20 + 0x1E0) = 5;
            *(short *)((char *)&D_00189E20 + 0x1F0) = 5;
        }
    }
    func_002C9218(*(void **)(state + 0x210), obj + 0x10, obj + 0x10, *(float *)(state + 0x50));
}
