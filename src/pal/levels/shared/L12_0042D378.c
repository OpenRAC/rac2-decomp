#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_002AB6D8(void *, void *);
extern void func_PAL_002A7650(void *, int, int);
extern void func_002E5CF8(int, int, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern char D_00189EA0[];
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFEB8(void *, void *, void *, int, float);
extern void func_00282F20(void *, void *, float);
extern int func_002A77E0(int);
extern void func_PAL_002B15D8(void *, int, void *, int, float, float, float, float);
extern void func_0029F338(void *);
typedef int s32;
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001A8FF0 __attribute__((sda));

void func_PAL_L12_0042D378(char *obj) {
    char pos[16];
    union { TI128 q; float f[4]; } offset;
    char dir[16];
    int color;
    if (*(short *)(*(char **)(obj + 0x68) + 0x358))
        func_002AB6D8(obj + 0xC0, obj + 0xF0);
    func_PAL_002A7650(obj, 0, 3);
    func_002E5CF8(1, 0, obj);
    offset.q = 0;
    offset.f[2] = 0.75f;
    func_00283098(pos, &offset, obj + 0xC0);
    func_00282CC0(pos, pos, obj + 0x10);
    func_PAL_002AD288(obj, pos, -1, 0.3330000042915344f, 0.0f);
    func_00282CF0(dir, obj + 0x10, D_00189EA0);
    func_002AFEB8(obj, dir, dir, 0, 0.0f);
    func_00282F20(dir, dir, 0.120000005f);
    color = D_L12_001A8FF0 ? func_002A77E0(0xFF) : 0xFF;
    func_PAL_002B15D8(obj, color & 0x1F, dir, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    func_0029F338(obj);
}


