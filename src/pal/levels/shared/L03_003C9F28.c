#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u32 D_L03_0024A7B0;
extern void func_002A7750(u8 *, u8, s32);
extern u32 func_002B38B8(u8 *);
typedef float f32;
extern f32 D_L04_001B1C88 __attribute__((sda));
extern u8 *D_L03_001B2A1C __attribute__((sda));
/* func_L03_003C5B28 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5CE8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5DC8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
extern void func_L03_003CAB80(u8 *, void *, f32 *);
extern void func_L03_00419A60(u32, u8 *, s32);
extern s32 func_00277258(void *, s32, void *, f32);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_L00_003294F0(u8 *entity, s32 enabled);
extern char D_00189EA0[];
typedef struct {
    u8 pad0[0x110];
    f32 f110;
    f32 f114;
    u8 pad118[0x220 - 0x118];
    u32 f220;
    u8 pad224[0x340 - 0x224];
    f32 f340[4];
    u8 pad350[0x358 - 0x350];
    u8 *f358;
} L03_5EE8Vars;
typedef struct {
    u8 pad0[0x10];
    s32 f10;
} L03_5EE8Class;
typedef struct {
    u8 pad0[0x24];
    L03_5EE8Class *f24;
    u8 pad28[0x43 - 0x28];
    u8 f43;
    u8 pad44[0x68 - 0x44];
    L03_5EE8Vars *f68;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} L03_5EE8Moby;
s32 func_L03_00419BD8(u32 a0, u8 *first, u8 *second);
extern s32 func_L03_00419C58(u32, f32 *);
extern f32 func_00282E80(void *, f32 *);
extern f32 func_002A89A8(f32 *, s32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_002A7878(f32, f32);
extern s32 func_002A77E0(s32);
extern u32 D_0024A7B0;
extern s32 ref_L03_003E3750_00(u8 *, u32);
extern u8 *func_0029EFD0(s32);
extern s32 g_activeGadgetItem;
extern f32 D_001B9C14;
extern f32 D_001B2464 __attribute__((sda));
extern f32 func_00282C48(f32);
extern u32 func_L03_00329EF0(u8 *, u8 *, u8 *, s32);
extern s32 func_L02_0032E998(u8 *, u8 *, void *, u8 *, s32, s32 *, s32 *, float, float);
extern s32 func_L02_0032EDD8(u8 *, u8 *, s32, s32 *);
s32 func_L03_00419C00(u8 *, u8 *, u8 *);
extern s32 func_002A77E0(s32);
extern f32 D_L03_001B9BEC;

void func_PAL_L03_003C9F28(L03_5EE8Moby *m) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 test[4] __attribute__((aligned(16)));
    L03_5EE8Vars *v = m->f68;

    func_L03_00419A60(v->f220, v->f358 + 0x10, 0);
    func_L03_003CAB80(v->f358, D_00189EA0, pos);
    qcopy(test, pos);
    test[2] += v->f110 + v->f114;
    if (func_00277258(test, 0, m, v->f110) == 0) {
        qcopy(v->f340, pos);
        func_L00_003294F0(v->f358, 0);
        v->f358 = 0;
        m->f98 = m->f24->f10;
        func_002A7750((u8 *)m, 0x11, 4);
        if (m->f43 != 0) {
            func_PAL_002A7E68(m, 0, 0, 0x11);
        }
    } else {
        func_L03_00419A60(v->f220, v->f358 + 0x10, 1);
    }
}

