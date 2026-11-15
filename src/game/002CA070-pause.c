/* func_002CA070 (1,372 bytes): the pause and cinema state machine. Prototype symbols (pause.cpp,
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

/* Sets up the pause or cutscene screen: picks the menu page for the current state, resets the camera and screen buffers, and lays out the memory areas used while paused. */
void func_002CA070(void)
{
    int queued = 0;
    int s, j, k, n, gsBase, gsAfterBackground;
    int *bufferPtr;
    void (*upd)(void);

    gCollisionHit[4] |= 0x80000000;
    gPauseMenuState.unk134 = 0;
    gPauseMenuState.unkE0 = 0;
    switch (gPauseMenuState.state) {
    case 0:
    case 7:
    case 9:
        break;
    case 2:
        queued = 1;
        gPauseMenuState.page = D_0025A190;
        gPauseMenuState.next = D_0025A190;
        break;
    case 3:
        gPauseMenuState.page = 0;
        gPauseMenuState.next = 0;
        break;
    case 4:
        gPauseMenuState.page = D_0025E488;
        gPauseMenuState.next = D_0025E488;
        queued = 1;
        SetPauseScaleInverse(6.0f);
        break;
    case 11:
        gPauseMenuState.next = gPauseMenuState.page = D_00261238;
        D_001A8C8C[0] = gPauseMenuState.unk134 = 1;
        gPauseMenuState.state = 5;
        StartMenuAction(D_001AA4B0);
        break;
    case 5:
        gPauseMenuState.page = D_00261238;
        gPauseMenuState.next = D_00261238;
        gPauseMenuState.unk134 = 1;
        D_001A8C8C[0] = 1;
        break;
    case 6:
        gPauseMenuState.page = D_00259458;
        gPauseMenuState.next = D_00259458;
        break;
    case 1:
        gPauseMenuState.page = D_00259328;
        gPauseMenuState.next = D_00259328;
        break;
    case 10:
        gPauseMenuState.page = D_0025A738;
        gPauseMenuState.next = D_0025A738;
        break;
    case 8:
        gPauseMenuState.page = D_00259018;
        gPauseMenuState.next = D_00259018;
        D_00210A40.a = 0x18;
        D_00210A40.b = 0x18;
        D_00210A40.c = D_00258D70;
        D_00210A40.upd = DrawLevelSelectList;
        D_00210A40.init = RebuildLevelSelectAvailability;
        D_00210A40.init(0);
        StepRingListForward(&D_00210A40);
        break;
    }

    if (gPauseMenuState.hasQueued != 0) {
        D_001A7478[0] = gPauseMenuState.unk140;
        gPauseMenuState.page = gPauseMenuState.queued;
        gPauseMenuState.next = gPauseMenuState.queued;
        if (gPauseMenuState.state == 2 || gPauseMenuState.state == 4) {
            SetCurrentMapAndRefresh(gPauseMenuState.unkF4);
            queued = 1;
            UpdateEntryStates();
        }
        gPauseMenuState.queued = 0;
        gPauseMenuState.hasQueued = 0;
    }

    {
        u8 *camera = D_001C2AD0;
        FastVecScale(camera, D_001AA490, 1.0f);
        qcopy(camera - 0x10, D_001AA4A0);
        camera += 0x20;
        qzero_nc(camera);
    }
    qzero_nc(D_001C2AD0 + 0x10);
    qcopy(gPauseMenuState.v50, gCameraState_001B5340);
    qcopy(gPauseMenuState.v60, gCameraState_001B5340 + 0x10);
    {
        float zfar = 524288.0f;
        float fog = 255.0f;
        float scale = 0.62f;
        gPauseMenuState.unkF8 = D_001B9040.fB0;
        D_001B9040.fB0 = scale;
        D_001B9040.f21C = zfar;
        D_001B9040.f228 = fog;
        D_001B9040.i22C = 0;
        D_001B9040.i218 = 0;
    }
    UpdateViewContext();
    ResetActiveCameraPosition();
    BuildViewMatrices();
    WaitForDmaStatusBits(1);
    GetGsCurrentField(0);
    D_001B1598_sda = D_001B1598[0] + 1;

    if (queued) {
        int areaA, areaB, areaC, areaD;
        areaA = D_001BAEC0.fC + 0x30000;
        areaB = D_001BAEC0.f10 + 0x30000;
        areaC = areaA + 0x3C000;
        areaD = areaB + 0xE0000;
        gPauseMenuState.unk10C = areaC + 0x11800;
        D_001B22B0[0] = 0x30000;
        gPauseMenuState.unk114 = areaA;
        gPauseMenuState.unk20 = areaB;
        gPauseMenuState.unk118 = areaC;
        gPauseMenuState.unk11C = areaD;
        gPauseMenuState.unk110 = areaD;
        InitStreamChunkTable(0);
    } else {
        int areaA, areaB, areaC, areaD, areaE, areaF;
        areaA = D_001BAEC0.fC + 0x60000;
        areaB = D_001BAEC0.f10 + 0x60000;
        areaB = areaB + 0xC000;
        areaA = areaA + 0xC000;
        areaC = areaA + 0x30000;
        areaD = areaB + 0xE0000;
        areaE = areaC + 0xC1000;
        areaF = areaD + 0x60800;
        gPauseMenuState.unk10C = areaE;
        D_001B22B0[0] = 0x60000;
        gPauseMenuState.unk114 = areaA;
        gPauseMenuState.unk20 = areaB;
        gPauseMenuState.unk118 = areaC;
        gPauseMenuState.unk11C = areaD;
        gPauseMenuState.unk110 = areaF;
        InitStreamChunkTable(1);
    }
    D_001A8BC0 = 0x2000;
    ResetPacketBuffer();
    if (queued) {
        ResetMapCacheAndReload();
    }
    UnlinkHudBankGroup(0);
    if (queued) {
        LoadStashedHudBanks(1);
    } else {
        LoadStashedHudBanks(0);
    }
    if (gPauseMenuState.unkD0 == 0) {
        CopyImageToGsBlocks(gPauseMenuState.unk20, D_001A72D8[1], gScreenWidth[1] << 11);
    } else {
        UploadPauseBackgroundToGs();
    }
    gsBase = D_001A72D4[0];
    gPauseMenuState.unk28 = gsBase;
    if (queued) {
        gMapOverlayState.unk24C = gsBase;
        gsAfterBackground = gsBase + 0x40000;
        gMapOverlayState.unk250 = gsAfterBackground;
        D_001A72D4[0] = gsAfterBackground + 0x400;
        for (j = 0; j < 4; j++) {
            int bufferAddr = D_001A72D4[0];
            gMapOverlayState.bufs[j] = bufferAddr;
            D_001A72D4[0] = bufferAddr + 0x4000;
        }
    } else {
        int bufferIndex;
        gMapOverlayState.unk24C = 0;
        gMapOverlayState.unk250 = 0;
        bufferPtr = &gMapOverlayState.bufs[3];
        for (bufferIndex = 0; bufferIndex < 4; bufferIndex++) {
            *bufferPtr = 0;
            bufferPtr--;
        }
    }
    select_moby_context(1);
    for (k = 0; k < 4; k++) {
        gPauseMenuState.unk40[k] = D_001A7398[k];
        gPauseMenuState.unk30[k] = D_001A7398[k];
    }
}
