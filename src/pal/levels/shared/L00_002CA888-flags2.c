#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad0[0x160];
    f32 v160[4];
    u8 pad170[0x1B4 - 0x170];
    f32 f1B4;
    u8 pad1B8[0xE98 - 0x1B8];
    s32 fE98;
    u8 padE9C[0xEA4 - 0xE9C];
    s32 fEA4;
    u8 padEA8[0x22B8 - 0xEA8];
    u8 b22B8;
    u8 pad22B9;
    u8 b22BA;
    u8 pad22BB[0x24B0 - 0x22BB];
    void *f24B0;
    s32 f24B4;
    u8 pad24B8[0x24EC - 0x24B8];
    s16 h24EC;
} Hero_2CAF20;
typedef struct {
    u8 pad0[0x28];
    void *moby;
    u8 pad2C[0xE0 - 0x2C];
} Entry_2CAF20;
extern Hero_2CAF20 D_00189E20;
extern u8 D_00139568[];
extern Entry_2CAF20 D_L00_00262570[];
extern s32 func_L00_002ADEA0(s32);
extern void func_PAL_L00_002AF6C0(void);
extern int func_PAL_L00_002C4480(int a0, int a1);
extern void func_PAL_L00_002D2668(void *, int, f32);
extern void func_002AC9F8(float *, float);

int func_PAL_L00_002CB2C8(void)
{
    Hero_2CAF20 *h = &D_00189E20;
    int idx;
    void *moby;

    if (h->b22B8 != 0 && h->b22BA != 0 && h->h24EC == 0) {
    idx = func_L00_002ADEA0(0);
    if (idx != h->f24B4) {
        func_PAL_L00_002AF6C0();
        return 0;
    }
    moby = (D_L00_00262570 + D_00139568[idx])->moby;
    if (func_PAL_L00_002C4480(0, 0) == 0)
        return 0;
    func_002AC9F8(h->v160, 0.030000001f);
    if (0.030000001f < h->f1B4)
        h->f1B4 = 0.030000001f;
    func_PAL_L00_002D2668(moby, 0, 9.0f);
    if (h->fE98 != 0)
        h->fEA4 = 1;
    h->f24B0 = moby;
    return 1;
    }
    return 0;
}

extern char D_0018C318[];
extern char D_00138180[];
extern int D_L00_001A8FB4 __attribute__((section(".sdata")));
extern s32 func_00282978(s32);
extern void func_L00_002FC008(void);

void func_PAL_L00_002CB5E8(void)
{
    char *b;
    char *o;
    u64 w;

    func_00282978(D_0018C318);
    func_00282978(D_0018C318 + 2);
    b = D_0018C318 - 0x24F8;
    if (0x37 == *(int *)(b + 0x2294))
        return;
    if (*(u8 *)(b + 0x22BC) != 0)
        return;
    if (D_L00_001A8FB4 != 0)
        return;
    o = D_00138180;
    if (*(int *)(o + 0x1A4) & 0x10)
        *(short *)(b + 0x24F8) = 17;
    w = *(u32 *)(b + 0x24F8);
    if (w == 0)
        return;
    if (*(int *)(o + 0x1B8) & 0x10) {
        if (*(short *)(b + 0x24FA) == 0) {
            *(short *)(b + 0x24FA) = 17;
            return;
        }
        *(int *)(b + 0x2538) = 1;
        func_L00_002FC008();
    }
}

extern int func_L00_002D1DA0(int, void *, void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern char D_00189E20_36[];

/* func_L00_002CB3A8 is in the sibling file L00_002CB3A8-decider.c (its own profile). */

/* loads two object pointers from fixed data, bails out when either is null or when the first object's byte 67 differs from 1, fills two stack ints through a helper, then applies a four-argument operation to each object with those ints */
void func_PAL_L00_002D1FE8(void)
{
    char *p = D_00189E20_36;
    void *s0;
    void *s1;
    int buf[2];

    s0 = *(void **)(p + 4880);
    s1 = *(void **)(p + 4884);

    if (s0 == 0)
        return;
    if (s1 == 0)
        return;

    if (*(unsigned char *)((char *)s0 + 67) != 1)
        return;

    if (func_L00_002D1DA0(0, buf, buf + 1) == 0)
        return;

    func_PAL_002A7E68(s0, buf[0], 0, 6);
    func_PAL_002A7E68(s1, buf[1], 0, 6);
}
