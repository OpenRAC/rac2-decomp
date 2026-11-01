#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
extern float D_L16_001B0C78 __attribute__((sda));
extern int D_L16_001B0CA8 __attribute__((sda));
extern int D_L16_001B0CAC __attribute__((sda));
extern char *D_L16_001BFF58[];
extern char D_L16_001A8F20[] __attribute__((sda));
extern void func_002A8C28(float, float, float, void *, void *, int, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282C88(void *);
extern float func_002A7878(float, float);
extern void *func_002C2210(void *, int, int, int, int, void *, float, float, float, int);
extern void func_0029F338(void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L16_003E70E0(void *);

/* Updates the moving object, handles impact/timeout, and emits its death particles. */
void func_PAL_L16_003EB0B0(char *object)
{
    float position[4];
    char collision[48];
    float velocity[4];
    float direction[4];
    char *state = *(char **)(object + 104);
    float size;
    if (++*(int *)(state + 36) > 240) {
        func_002A8C28(0.6f, *(float *)(state + 20), 0.0f, object, object + 16, 0x10001, 0, 1, 0);
        func_002A7750(object, 1, -1);
    }
    switch (*(unsigned char *)(object + 32)) {
    case 0:
        func_00282CC0(position, object + 16, state);
        func_002A8C00(collision, object, 1, state, *(float *)(state + 20));
        *(unsigned short *)(collision + 26) = *(unsigned short *)(object + 170);
        if ((func_002761F8(object + 16, position, 0, object, collision) ||
             func_00277258(object + 16, 0, object, 0.3f)) &&
             (D_L16_001BFF58[0] == 0 || D_L16_001BFF58[0] != *(char **)(state + 16))) {
            func_002A8C28(0.6f, *(float *)(state + 20), 0.0f, object, object + 16, 0x10001, 0, 1, 0);
            func_002A7750(object, 1, -1);
            return;
        }
        *(Quadword *)(object + 16) = *(Quadword *)position;
        func_00282D30(velocity, state, -0.5f);
        func_00282C88(direction);
        break;
    case 1:
        size = func_002A7878(8.0f, 10.0f);
        func_002C2210(object + 16, 12, D_L16_001B0CA8, 0, 10, D_L16_001A8F20, size * 0.3f, size, 0.0f, 0);
        func_002C2210(object + 16, 12, D_L16_001B0CAC, 1, -10, D_L16_001A8F20, size * 0.04f, size * 0.4f, 0.0f, 0);
        func_0029F338(object);
        return;
    }
    func_002ACEC0(object + 224, object + 224, object + 208, D_L16_001B0C78 * 0.017453294f);
    func_002ACEC0(object + 192, object + 192, object + 208, D_L16_001B0C78 * 0.017453294f);
    func_L00_002E6EF8(func_L16_003E70E0, object);
}
