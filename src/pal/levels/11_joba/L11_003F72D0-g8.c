#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad0[0x10];
    f32 x;
    f32 y;
    f32 z;
    u8 pad1C[0x8];
    u8 *model;
    u8 pad28[0x9];
    u8 b31;
    u8 pad32[2];
    u16 flags;
    u8 pad36[0x49];
    u8 b7F;
    u8 pad80[0x18];
    u32 w98;
    u8 pad9C[0x1C];
    s32 slot;
    u8 padBC[0x4];
    u8 mtx[0x30];
    s32 rotW;
    f32 rotX;
    f32 rotZ;
} L11Moby;
extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);
extern void func_002A0488(void *, int, int, int);
extern int func_PAL_002B3F18(char *, char *, char *);
extern f32 func_00283180(f32 a0);
extern f32 func_00283198(f32 a0);
extern f32 func_00283B98(f32 a0, f32 a1);
extern void func_002833F0(void *a0, void *a1);
extern f32 *func_L11_004417E8(s32 a0);
extern f32 D_L11_001B0558 __attribute__((sda));
extern f32 D_L11_001B0540 __attribute__((sda));

void func_PAL_L11_003F72D0(u8 *arg0) {
    L11Moby *m = (L11Moby *)arg0;
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    f32 *p;
    f32 f20;
    f32 y;
    u32 w;

    *(f32 *)(s1 + 0x20) = (f32)*(s16 *)(s1 + 0x24);
    w = *(u32 *)(m->model + 0x10);
    m->flags &= 0xFFFE;
    m->b31 = 1;
    m->w98 = w;
    *(u8 *)(s1 + 0x2E) = 1;
    m->b7F = 0;
    m->flags = (m->flags & 0xFFB9) | 0x1000;
    *(s32 *)(s1 + 0x60) = 0;
    func_PAL_002B3F18((char *)m, (char *)(s1 + 0x50), (char *)(s1 + 0x20));
    if (*(s16 *)(s1 + 0x70) != 0) {
        *(s16 *)(s1 + 0x70) = 0;
        func_002A0488(m, *(u32 *)(s1 + 0x280), *(u32 *)(s1 + 0x284),
                      *(u32 *)(s1 + 0x288));
        *(s16 *)(s1 + 0x72) = 1;
    }
    func_002A7750(arg0, 2, 2);
    *(s32 *)(s1 + 0x250) = 0;
    f20 = func_00283180(*(f32 *)(s1 + 0x250));
    p = func_L11_004417E8(m->slot);
    m->x = D_L11_001B0558 * f20 + p[0];
    f20 = func_00283198(*(f32 *)(s1 + 0x250));
    p = func_L11_004417E8(m->slot);
    y = D_L11_001B0558 * f20 + p[1];
    m->z = D_L11_001B0540;
    m->rotX = -1.5707965f;
    m->rotW = 0;
    m->y = y;
    m->rotZ = func_00283B98(3.1415927f, *(f32 *)(s1 + 0x250));
    func_002833F0(m->mtx, &m->rotW);
}
