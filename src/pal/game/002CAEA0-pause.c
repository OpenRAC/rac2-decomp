/* func_PAL_002CAEA0 (1,388 bytes), the PAL copy of func_002CA070 (src/game/002CA070-pause.c):
 * the same C, plus a 0x30-byte copy of D_001B5340 + 0x230 into the pause state (+0x200).
 * func_002CA070 notes: the pause and cinema state machine. Prototype symbols (pause.cpp,
 * loaders.cpp) identify D_001F2840 as the pause state and D_00210A40 as the cinema controller.
 * Own unit: -O2 -G16 -Wa,-G16 -ffunction-sections -frac2-la-funcref-weight (config/cflags.txt).
 * - qzero_nc at the two camera clears (the fresh lui for D_001C2AD0 + 0x10).
 * - The screen size and frame-buffer reads are sym+offset reads of sda pairs, D_001A7340[1] and
 *   D_001A72D8[1]: a (const (plus sym off)) address has length 2, so reorg leaves the bnez slot
 *   empty and gas expands the macro to lui/lw, as retail.
 * - The last loop: D_001A7398 as an sda incomplete array is one `la` insn, so the src giv has
 *   no %hi pseudo and dst takes $v1, the counter $a0, src $a1, as retail.
 * - Case 8 is written in its natural order (page, next, a, b, c, upd, init, init(0)). Its five
 *   block-local values (page, c, 0x18 and the two callbacks) get retail's registers with
 *   -frac2-la-funcref-weight, which counts one more reference in local-alloc for a quantity
 *   set from a function's address (docs/build/compiler-notes.md). The switch is a per-unit
 *   model, not retail's global rule: forced on for every USA v1.01 unit it changes 13 functions.
 *   Allowed by owner ruling, 12 November 2026.
 */
#include "common.h"

typedef struct {
    u8 pad0[0x8];
    int state;          /* 0x08 */
    u8 pad1[0x8];
    int *page;          /* 0x14 */
    int *next;          /* 0x18 */
    u8 pad2[0x4];
    int unk20;          /* 0x20 */
    u8 pad3[0x4];
    int unk28;          /* 0x28 */
    u8 pad4[0x4];
    int unk30[4];       /* 0x30 */
    int unk40[4];       /* 0x40 */
    u8 v50[0x10];       /* 0x50 */
    u8 v60[0x10];       /* 0x60 */
    u8 pad5[0x60];
    int unkD0;          /* 0xD0 */
    u8 pad6[0xC];
    int unkE0;          /* 0xE0 */
    u8 pad7[0x10];
    int unkF4;          /* 0xF4 */
    float unkF8;        /* 0xF8 */
    u8 pad8[0x4];
    int *queued;        /* 0x100 */
    int hasQueued;      /* 0x104 */
    u8 pad9[0x4];
    int unk10C;         /* 0x10C */
    int unk110;         /* 0x110 */
    int unk114;         /* 0x114 */
    int unk118;         /* 0x118 */
    int unk11C;         /* 0x11C */
    u8 padA[0x14];
    int unk134;         /* 0x134 */
    u8 padB[0x8];
    int unk140;         /* 0x140 */
    u8 padC[0x200 - 0x144];
    u8 v200[0x30];      /* 0x200 */
} Menu;

typedef struct {
    u8 pad0[0xB0];
    float fB0;
    u8 pad1[0x218 - 0xB4];
    int i218;
    float f21C;
    u8 pad2[0x228 - 0x220];
    float f228;
    int i22C;
} View;

typedef struct {
    u8 pad0[0xC];
    int fC;
    int f10;
} Buffers;

typedef struct {
    u8 pad0[0x24C];
    int unk24C;
    int unk250;
    int bufs[4];
} Snd;

typedef struct {
    int a;
    int b;
    int *c;
    u8 pad[0x8C - 0xC];
    void (*init)(int);
    void (*upd)(void);
} Cutscene;

extern int D_001BAF80[];
extern Menu D_001F2840;
extern View D_001B9040;
extern Buffers D_001BAEC0;
extern Snd D_001C4FA0;
extern Cutscene D_00210A40;
extern int D_0025A190[], D_0025E488[], D_00261238[], D_00259458[], D_00259328[], D_0025A738[], D_00259018[], D_00258D70[];
extern int D_001A8C8C[] __attribute__((sda));
extern int D_001A7478[] __attribute__((sda));
extern int D_001B22B0[] __attribute__((sda));
extern int D_001A8BC0 __attribute__((sda));
extern int D_001B1598[] __attribute__((sda));
extern int D_001B1598_sda __attribute__((sda));
extern int D_001A72D4[] __attribute__((sda));
extern int D_001A72D8[] __attribute__((sda));   /* the two frame buffers */
extern int D_001A7340[] __attribute__((sda));   /* the screen size pair: [0] width, [1] height */
extern int D_001A7398[] __attribute__((sda));
extern u8 D_001AA4B0[16] __attribute__((sda));
extern u8 D_001AA490[16] __attribute__((sda));
extern u8 D_001AA4A0[16] __attribute__((sda));
extern u8 D_001C2AD0[];
extern u8 D_001B5340[];

extern void func_002C9C60(float);
extern void func_002D5E98(void *);
extern void func_002CB648(void);
extern int func_002CB510(int);
extern void func_002C9AD8(void *);
extern void func_00295C50(int);
extern int func_0029D830(void);
extern void func_00282D30(void *, void *, float);
extern void func_0027AB40(void);
extern void func_002C9C90(void);
extern void func_00279D18(void);
extern void func_002FC3C0(int);
extern int func_001261F0(int);
extern void func_002DE3A0(int);
extern void func_002FC1D8(void);
extern void func_002954C0(void);
extern void func_0028AFE8(int);
extern void func_0028ACB0(int);
extern void func_002FC8D0(int, int, int);
extern void func_002C9F68(void);
extern void func_0028B338(int);
extern void func_00282AB0(void *, void *, int);

void func_PAL_002CAEA0(void)
{
    int queued = 0;
    int s, j, k, n, t, u;
    int *p;
    void (*upd)(void);

    D_001BAF80[4] |= 0x80000000;
    D_001F2840.unk134 = 0;
    D_001F2840.unkE0 = 0;
    switch (D_001F2840.state) {
    case 0:
    case 7:
    case 9:
        break;
    case 2:
        queued = 1;
        D_001F2840.page = D_0025A190;
        D_001F2840.next = D_0025A190;
        break;
    case 3:
        D_001F2840.page = 0;
        D_001F2840.next = 0;
        break;
    case 4:
        D_001F2840.page = D_0025E488;
        D_001F2840.next = D_0025E488;
        queued = 1;
        func_002C9C60(6.0f);
        break;
    case 11:
        D_001F2840.next = D_001F2840.page = D_00261238;
        D_001A8C8C[0] = D_001F2840.unk134 = 1;
        D_001F2840.state = 5;
        func_002D5E98(D_001AA4B0);
        break;
    case 5:
        D_001F2840.page = D_00261238;
        D_001F2840.next = D_00261238;
        D_001F2840.unk134 = 1;
        D_001A8C8C[0] = 1;
        break;
    case 6:
        D_001F2840.page = D_00259458;
        D_001F2840.next = D_00259458;
        break;
    case 1:
        D_001F2840.page = D_00259328;
        D_001F2840.next = D_00259328;
        break;
    case 10:
        D_001F2840.page = D_0025A738;
        D_001F2840.next = D_0025A738;
        break;
    case 8:
        D_001F2840.page = D_00259018;
        D_001F2840.next = D_00259018;
        D_00210A40.a = 0x18;
        D_00210A40.b = 0x18;
        D_00210A40.c = D_00258D70;
        D_00210A40.upd = func_002CB648;
        D_00210A40.init = func_002CB510;
        D_00210A40.init(0);
        func_002C9AD8(&D_00210A40);
        break;
    }

    if (D_001F2840.hasQueued != 0) {
        D_001A7478[0] = D_001F2840.unk140;
        D_001F2840.page = D_001F2840.queued;
        D_001F2840.next = D_001F2840.queued;
        if (D_001F2840.state == 2 || D_001F2840.state == 4) {
            func_00295C50(D_001F2840.unkF4);
            queued = 1;
            func_0029D830();
        }
        D_001F2840.queued = 0;
        D_001F2840.hasQueued = 0;
    }

    {
        u8 *r = D_001C2AD0;
        func_00282D30(r, D_001AA490, 1.0f);
        qcopy(r - 0x10, D_001AA4A0);
        r += 0x20;
        qzero_nc(r);
    }
    qzero_nc(D_001C2AD0 + 0x10);
    qcopy(D_001F2840.v50, D_001B5340);
    qcopy(D_001F2840.v60, D_001B5340 + 0x10);
    func_00282AB0(D_001F2840.v200, D_001B5340 + 0x230, 0x30);
    {
        float zfar = 524288.0f;
        float fog = 255.0f;
        float scale = 0.62f;
        D_001F2840.unkF8 = D_001B9040.fB0;
        D_001B9040.fB0 = scale;
        D_001B9040.f21C = zfar;
        D_001B9040.f228 = fog;
        D_001B9040.i22C = 0;
        D_001B9040.i218 = 0;
    }
    func_0027AB40();
    func_002C9C90();
    func_00279D18();
    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598_sda = D_001B1598[0] + 1;

    if (queued) {
        int a, b, c, d;
        a = D_001BAEC0.fC + 0x30000;
        b = D_001BAEC0.f10 + 0x30000;
        c = a + 0x3C000;
        d = b + 0xE0000;
        D_001F2840.unk10C = c + 0x11800;
        D_001B22B0[0] = 0x30000;
        D_001F2840.unk114 = a;
        D_001F2840.unk20 = b;
        D_001F2840.unk118 = c;
        D_001F2840.unk11C = d;
        D_001F2840.unk110 = d;
        func_002DE3A0(0);
    } else {
        int a, b, c, d, e, f;
        a = D_001BAEC0.fC + 0x60000;
        b = D_001BAEC0.f10 + 0x60000;
        b = b + 0xC000;
        a = a + 0xC000;
        c = a + 0x30000;
        d = b + 0xE0000;
        e = c + 0xC1000;
        f = d + 0x60800;
        D_001F2840.unk10C = e;
        D_001B22B0[0] = 0x60000;
        D_001F2840.unk114 = a;
        D_001F2840.unk20 = b;
        D_001F2840.unk118 = c;
        D_001F2840.unk11C = d;
        D_001F2840.unk110 = f;
        func_002DE3A0(1);
    }
    D_001A8BC0 = 0x2000;
    func_002FC1D8();
    if (queued) {
        func_002954C0();
    }
    func_0028AFE8(0);
    if (queued) {
        func_0028ACB0(1);
    } else {
        func_0028ACB0(0);
    }
    if (D_001F2840.unkD0 == 0) {
        func_002FC8D0(D_001F2840.unk20, D_001A72D8[1], D_001A7340[1] << 11);
    } else {
        func_002C9F68();
    }
    t = D_001A72D4[0];
    D_001F2840.unk28 = t;
    if (queued) {
        D_001C4FA0.unk24C = t;
        u = t + 0x40000;
        D_001C4FA0.unk250 = u;
        D_001A72D4[0] = u + 0x400;
        for (j = 0; j < 4; j++) {
            int v = D_001A72D4[0];
            D_001C4FA0.bufs[j] = v;
            D_001A72D4[0] = v + 0x4000;
        }
    } else {
        int z;
        D_001C4FA0.unk24C = 0;
        D_001C4FA0.unk250 = 0;
        p = &D_001C4FA0.bufs[3];
        for (z = 0; z < 4; z++) {
            *p = 0;
            p--;
        }
    }
    func_0028B338(1);
    for (k = 0; k < 4; k++) {
        D_001F2840.unk40[k] = D_001A7398[k];
        D_001F2840.unk30[k] = D_001A7398[k];
    }
}
