#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern f32 func_002A78D8(f32 low, f32 high);
extern f32 D_001A8BD0[] __attribute__((sda));
typedef struct {
    TI128 position;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
} State_332440;
extern int func_002FED90(void *obj, f32 x, f32 y, f32 z, void *src);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_002AFFD8(void *, void *, int);
extern char *func_0029EFD0(int);
extern void func_00282F20(void *, void *, float);
typedef int L_34730TI __attribute__((mode(TI)));
extern L_34730TI func_00334710(int, L_34730TI *);
typedef int TI __attribute__((mode(TI)));
extern TI func_00334710(int, TI *);

char *func_PAL_00334028(void *a0, void *a1, void *a2)
{
    TI128 localA;
    TI128 localB;
    char *object;
    State_332440 *state;
    int result;

    func_002AFFD8(a1, &localA, 1);
    object = func_0029EFD0(0xEAA);
    if (object != 0) {
        state = *(State_332440 **)(object + 0x68);
        state->f10 = 0x43;
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x20) = 0;
        qcopy(object + 0x10, a1);
        qcopy(state, a2);
        state->f18 = 0;
        state->f14 = 0;
        func_00282F20(&localB, a2, 1.0f);
        qcopy(object + 0xC0, &localB);
        func_00282DD8(object + 0xD0, object + 0xC0, &localA);
        func_00282F20(object + 0xD0, object + 0xD0, 1.0f);
        func_00282DD8(object + 0xE0, object + 0xD0, object + 0xC0);
        *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
        result = func_002FED90(object, 1.0f, 1.0f, 1.0f, 0);
        state->f1C = result;
        state->f20 = (int)a0;
    }
    return object;
}

