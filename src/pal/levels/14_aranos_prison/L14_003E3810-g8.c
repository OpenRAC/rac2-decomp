#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
extern char *D_L14_001B268C __attribute__((sda));
extern char D_00188660[];
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_002AD6F0(void *, void *, void *, void *);
extern float func_00282C48(float);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);

void func_PAL_L14_003E3810(char *self) {
    struct { Vector argument, rotation; } work;
    char *state = *(char **)(self + 0x68);
    float target;
    int index;
    if (*(int *)(state + 0x7C))
        target = *(float *)(((char (*)[0x80])D_L14_001B268C)[*(int *)(state + 0x60)] + 0x38);
    else
        target = *(float *)(state + 0x70);
    func_002AA548(self + 0x18, state + 0x74, target,
                 0.0016000001f, 0.0032000002f, 1.0f);
    work.rotation.q = 0;
    work.rotation.f[2] = *(float *)(state + 0x74);
    work.argument.q = work.rotation.q;
    func_002AD6F0(state + 0x20, &work.argument, self + 0xF0, self + 0xF0);
    if (0.01f < func_00282C48(*(float *)(state + 0x74))) {
        char *entry = D_00188660 + *(int *)(state + 0x78) * 0x70;
        if (*(char **)(entry + 0x88) != self || *(unsigned char *)(entry + 0x74) == 0)
            *(int *)(state + 0x78) = func_002E5CF8(0, 4, self);
    } else {
        index = *(int *)(state + 0x78);
        if (index != -1) {
            char *entry = D_00188660 + index * 0x70;
            if (*(char **)(entry + 0x88) == self && *(unsigned char *)(entry + 0x74) != 0)
                func_002E59F8(index);
        }
        *(int *)(state + 0x78) = -1;
    }
}
