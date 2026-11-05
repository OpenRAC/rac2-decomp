/* 5 November 2026: preserve this native-oriented variant rather than replacing it with the matching draft. Only the independently checked interfaces/widths are repaired; no new native runtime validation is claimed. */
/* functional: high. Unchecked: every captured call waits past the gate's 40M-instruction budget (NOTHING COMPARED). Read 0x2CA070-0x2CA5C8 in full, with all 12 jump-table words at 0x26CC50 (0, 7, 9 go to the default): same reads, writes and calls in retail's order. Differs only in form: the 16-byte lq/sq copies and clears are four word copies (same bytes), case 8 calls func_002CB510 directly where retail jalr's the constant it just stored, function addresses are stored as 32-bit game addresses, and func_002FC8D0 is declared as the port's host function (gaddr = unsigned int). */

/* Enters a menu/scene state (D_001F2840): picks the menu page for its state (cases 1-6, 8, 10, 11; case 8 also
 * sets up the cutscene player D_00210A40), takes a queued page if one is pending, resets the camera block at
 * D_001C2AD0 and the view at D_001B9040, lays out the frame/texture buffer addresses from D_001BAEC0 for the
 * full or the reduced (queued) set, the sound buffers in D_001C4FA0, and copies the four D_001A7398 words to
 * +0x30 and +0x40. */

typedef struct {
    char pad0[0x8];
    int state;          /* 0x08 */
    char pad1[0x8];
    int *page;          /* 0x14 */
    int *next;          /* 0x18 */
    char pad2[0x4];
    int unk20;          /* 0x20 */
    char pad3[0x4];
    int unk28;          /* 0x28 */
    char pad4[0x4];
    int unk30[4];       /* 0x30 */
    int unk40[4];       /* 0x40 */
    int v50[4];         /* 0x50 */
    int v60[4];         /* 0x60 */
    char pad5[0x60];
    int unkD0;          /* 0xD0 */
    char pad6[0xC];
    int unkE0;          /* 0xE0 */
    char pad7[0x10];
    int unkF4;          /* 0xF4 */
    float unkF8;        /* 0xF8 */
    char pad8[0x4];
    int *queued;        /* 0x100 */
    int hasQueued;      /* 0x104 */
    char pad9[0x4];
    int unk10C;         /* 0x10C */
    int unk110;         /* 0x110 */
    int unk114;         /* 0x114 */
    int unk118;         /* 0x118 */
    int unk11C;         /* 0x11C */
    char padA[0x14];
    int unk134;         /* 0x134 */
    char padB[0x8];
    int unk140;         /* 0x140 */
} SceneMenu;

typedef struct {
    char pad0[0xB0];
    float fB0;
    char pad1[0x218 - 0xB4];
    int i218;
    float f21C;
    char pad2[0x228 - 0x220];
    float f228;
    int i22C;
} SceneView;

typedef struct {
    char pad0[0xC];
    int fC;
    int f10;
} SceneBuffers;

typedef struct {
    char pad0[0x24C];
    int unk24C;
    int unk250;
    int bufs[4];
} SceneSound;

typedef struct {
    int a;              /* 0x00 */
    int b;              /* 0x04 */
    int *c;             /* 0x08 */
    char pad[0x8C - 0xC];
    int init;           /* 0x8C: a function's game address */
    int upd;            /* 0x90: a function's game address */
} SceneCutscene;

extern int D_001BAF80[];
extern SceneMenu D_001F2840;
extern SceneView D_001B9040;
extern SceneBuffers D_001BAEC0;
extern SceneSound D_001C4FA0;
extern SceneCutscene D_00210A40;
extern int D_0025A190[], D_0025E488[], D_00261238[], D_00259458[], D_00259328[], D_0025A738[], D_00259018[], D_00258D70[];
extern int D_001A8C8C;
extern int D_001A7478;
extern int D_001B22B0;
extern int D_001A8BC0;
extern int D_001B1598;
extern int D_001A72D4;
extern int D_001A72DC;      /* the second frame buffer */
extern int D_001A7344;      /* the screen height */
extern int D_001A7398[];
extern int D_001AA4B0[];
extern int D_001AA490[];
extern int D_001AA4A0[];
extern int D_001C2AC0[], D_001C2AD0[], D_001C2AE0[], D_001C2AF0[];
extern int D_001B5340[];

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
extern void func_002FC8D0(unsigned int, int, int);
extern void func_002C9F68(void);
extern void func_0028B338(int);

void func_002CA070(void)
{
    int queued = 0;
    int k, t;

    D_001BAF80[4] |= 0x80000000;
    D_001F2840.unk134 = 0;
    D_001F2840.unkE0 = 0;
    switch ((unsigned int)D_001F2840.state) {
    case 2:
        queued = 1;
        D_001F2840.next = D_0025A190;
        D_001F2840.page = D_0025A190;
        break;
    case 3:
        D_001F2840.next = 0;
        D_001F2840.page = 0;
        break;
    case 4:
        D_001F2840.next = D_0025E488;
        queued = 1;
        D_001F2840.page = D_0025E488;
        func_002C9C60(6.0f);
        break;
    case 11:
        D_001F2840.state = 5;
        D_001F2840.next = D_00261238;
        D_001A8C8C = 1;
        D_001F2840.page = D_00261238;
        D_001F2840.unk134 = 1;
        func_002D5E98(D_001AA4B0);
        break;
    case 5:
        D_001F2840.next = D_00261238;
        D_001F2840.unk134 = 1;
        D_001A8C8C = 1;
        D_001F2840.page = D_00261238;
        break;
    case 6:
        D_001F2840.next = D_00259458;
        D_001F2840.page = D_00259458;
        break;
    case 1:
        D_001F2840.next = D_00259328;
        D_001F2840.page = D_00259328;
        break;
    case 10:
        D_001F2840.next = D_0025A738;
        D_001F2840.page = D_0025A738;
        break;
    case 8:
        D_001F2840.next = D_00259018;
        D_00210A40.a = 0x18;
        D_00210A40.b = 0x18;
        D_00210A40.c = D_00258D70;
        D_00210A40.upd = (int)func_002CB648;
        D_001F2840.page = D_00259018;
        D_00210A40.init = (int)func_002CB510;
        func_002CB510(0);
        func_002C9AD8(&D_00210A40);
        break;
    default:            /* 0, 7, 9 and anything above 11 */
        break;
    }

    if (D_001F2840.hasQueued != 0) {
        int *page = D_001F2840.queued;
        int state = D_001F2840.state;
        D_001A7478 = D_001F2840.unk140;
        D_001F2840.next = page;
        D_001F2840.page = page;
        if (state == 2 || state == 4) {
            func_00295C50(D_001F2840.unkF4);
            queued = 1;
            func_0029D830();
        }
        D_001F2840.hasQueued = 0;
        D_001F2840.queued = 0;
    }

    func_00282D30(D_001C2AD0, D_001AA490, 1.0f);
    for (k = 0; k < 4; k++)
        D_001C2AC0[k] = D_001AA4A0[k];
    for (k = 0; k < 4; k++)
        D_001C2AF0[k] = 0;
    for (k = 0; k < 4; k++)
        D_001C2AE0[k] = 0;
    for (k = 0; k < 4; k++)
        D_001F2840.v50[k] = D_001B5340[k];
    for (k = 0; k < 4; k++)
        D_001F2840.v60[k] = D_001B5340[4 + k];
    D_001F2840.unkF8 = D_001B9040.fB0;
    D_001B9040.fB0 = 0.62f;
    D_001B9040.f21C = 524288.0f;
    D_001B9040.f228 = 255.0f;
    D_001B9040.i218 = 0;
    D_001B9040.i22C = 0;
    func_0027AB40();
    func_002C9C90();
    func_00279D18();
    func_002FC3C0(1);
    func_001261F0(0);
    D_001B1598 = D_001B1598 + 1;

    if (queued) {
        int a = D_001BAEC0.fC + 0x30000;
        int b = D_001BAEC0.f10 + 0x30000;
        int c = a + 0x3C000;
        int d = b + 0xE0000;
        D_001F2840.unk110 = d;
        D_001F2840.unk10C = c + 0x11800;
        D_001B22B0 = 0x30000;
        D_001F2840.unk114 = a;
        D_001F2840.unk20 = b;
        D_001F2840.unk118 = c;
        D_001F2840.unk11C = d;
        func_002DE3A0(0);
    } else {
        int b = D_001BAEC0.f10 + 0x60000 + 0xC000;
        int a = D_001BAEC0.fC + 0x60000 + 0xC000;
        int c = a + 0x30000;
        int d = b + 0xE0000;
        D_001F2840.unk110 = d + 0x60800;
        D_001F2840.unk10C = c + 0xC1000;
        D_001B22B0 = 0x60000;
        D_001F2840.unk114 = a;
        D_001F2840.unk20 = b;
        D_001F2840.unk118 = c;
        D_001F2840.unk11C = d;
        func_002DE3A0(1);
    }
    D_001A8BC0 = 0x2000;
    func_002FC1D8();
    if (queued)
        func_002954C0();
    func_0028AFE8(0);
    if (queued)
        func_0028ACB0(1);
    else
        func_0028ACB0(0);
    if (D_001F2840.unkD0 == 0)
        func_002FC8D0((unsigned int)D_001F2840.unk20, D_001A72DC, D_001A7344 << 11);
    else
        func_002C9F68();
    t = D_001A72D4;
    D_001F2840.unk28 = t;
    if (queued) {
        int u = t + 0x40000;
        D_001C4FA0.unk24C = t;
        D_001A72D4 = u + 0x400;
        D_001C4FA0.unk250 = u;
        for (k = 0; k < 4; k++) {
            int v = D_001A72D4;
            D_001C4FA0.bufs[k] = v;
            D_001A72D4 = v + 0x4000;
        }
    } else {
        D_001C4FA0.unk24C = 0;
        D_001C4FA0.unk250 = 0;
        for (k = 3; k >= 0; k--)
            D_001C4FA0.bufs[k] = 0;
    }
    func_0028B338(1);
    for (k = 0; k < 4; k++) {
        int v = D_001A7398[k];
        D_001F2840.unk30[k] = v;
        D_001F2840.unk40[k] = v;
    }
}
