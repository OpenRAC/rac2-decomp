#include "ps2_hw.h"
#include "names.h"
extern char D_L00_001BD2C0[];
extern int D_L00_001A8FB4;
extern char *D_L00_001A904C;
extern int D_L00_001AEA7C __attribute__((sda));
extern int D_L00_001AEA80 __attribute__((sda));
extern void func_0027AB40(void);
extern unsigned int func_0034CA68(void *);
extern void func_0034E2E0(void *, int, int, int);
extern void func_0034E218(void *);
extern void func_0034DB98(void *);
extern void func_00338F58(void *);
extern void func_0029CB80(void);
/* Draws the item and bolt HUD once, using a temporary setting that is put back afterwards. */
void func_0034E4F8(char *object)
{
    float saved;
    char *camera;
    char *state = D_L00_001BD2C0;
    saved = *(float *)(state + 0xB0);
    *(float *)(state + 0xB0) = 0.62f;
    UpdateViewContext();
    if (D_L00_001A8FB4 == 0)
        LayoutRadialMenuItems(object, D_L00_001AEA7C, D_L00_001AEA80, GetLabelColorAlpha(object + 0x7A0) >> 24);
    NopHook(object);
    DrawBoltCounterPanel(object + 0x7A0);
    camera = D_L00_001A904C + 0x38000;
    *(int *)(camera + 0x7354) = 0;
    *(int *)(camera + 0x7358) = 0;
    DrawTextPanelScaled(object + 0x1FBC);
    func_0029CB80();
    *(float *)(state + 0xB0) = saved;
    UpdateViewContext();
}

extern char *D_001B23CC[] __attribute__((sda));
extern int ref_L00_0034F690_00 __attribute__((sda));
typedef int (*CleanupCallback)(void);
extern int func_001339B0(void);
extern void func_00124B88(int);
extern void func_003505A8(void *);
extern void func_00351E40(void *);
extern void func_0011AA70(int);
extern void func_0011AA30(int);
extern void func_0011B658(int);
extern void func_0011A950(int, int);
extern CleanupCallback func_00126DC0(CleanupCallback);
extern int func_00351890(void *);
extern int func_0034F898(void *);
extern int func_003506A8(void *);

/* Shuts down the movie player: stops the decoder, removes its handlers and turns the DMA channel off. */
void func_0034F690(void)
{
    WaitSCommandDone(0);
    NopReadBufferHook(gMoviePlayerState[0]);
    NoOp_00351E40(gMoviePlayerState[0] + 0xd9168);
    TerminateThread(ref_L00_0034F690_00);
    DeleteThread(ref_L00_0034F690_00);
    ProcessKernelQueueEntryC(2);
    RemoveDmacHandler(2, *(int *)(gMoviePlayerState[0] + 0xd8000 + 0x10f8));
    func_00126DC0(UpdateVsyncTimerCounters);
    VideoDecShutdown(gMoviePlayerState[0] + 0xd9048);
    ResetMovieAudioDma(gMoviePlayerState[0] + 0xd9100);
    ReturnTrue(gMoviePlayerState[0] + 0xd9040);
    WaitSCommandDone(0);
    D_CTRL &= ~2u;
}

extern char *ref_L00_0034EF58_01[] __attribute__((sda));
extern char ref_L00_0034EF58_00[];
extern void func_0026FEB8(void *, ...);
extern void func_00284088(int, int);
extern int func_0011AB10(void);
extern void func_0011AAB0(int, int);
extern int func_0034F408(void *, void *, int);
extern int func_0034F048(void *, void *, void *);

/* Plays a full-motion video: sets up the player, plays the stream until it ends or is skipped, then cleans up. Returns 1 if the player skipped it. */
int func_0034EF58(void *streamSource, void *sourceMode, char *pool, char *state, int mode, int volume)
{
    int result = 0;
    ref_L00_0034EF58_01[0] = pool;
    gMoviePlayerState[0] = state;
    STUB_printf(ref_L00_0034EF58_00, 0x38cac0);
    BuildAspectBlitStrips(volume, volume);
    ChangeThreadPriority(GetThreadId(), 1);
    if (StartMoviePlayer(streamSource, sourceMode, mode)) {
        result = read_mpeg(gMoviePlayerState[0] + 0xd9048, gMoviePlayerState[0], gMoviePlayerState[0] + 0xd9040);
    }
    ShutdownMoviePlayer();
    ref_L00_0034EF58_01[0] = 0;
    gMoviePlayerState[0] = 0;
    return result;
}

typedef unsigned long long u64;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned char u8;

extern int D_001A72DC;
extern int D_001B23C8;
extern void func_002B6480(void *, int);

/* FMV GS packet builder: one 0x40-byte header record, then a 0x60-byte record per
   (row, column), then the closing A_B word pair at the end of the run. */
void func_0034FE18(void *packet, int textureAddress, int height, int width, int bufferIndex)
{
    u8 *cursor = (u8 *)packet;
    int rows = height >> 4;
    int cols = width >> 4;
    int i, j;
    u64 c00, c10, c18, c28, c38, c40;
    u32 off, addr;

    *(u64 *)(cursor + 0x00) = 0x10000003;
    *(u64 *)(cursor + 0x08) = 0;
    *(u64 *)(cursor + 0x10) = 0x1000000000000002ULL;
    *(u64 *)(cursor + 0x18) = 0xE;
    *(u64 *)(cursor + 0x20) = ((ll)D_001A72DC >> 8) << 32 | 0x8000000000000LL;
    *(u64 *)(cursor + 0x28) = 0x50;
    *(u64 *)(cursor + 0x30) = 0x1000000010ULL;
    *(u64 *)(cursor + 0x38) = 0x52;

    cursor += 0x40;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            c00 = 0x10000004;
            c10 = 0x1000000000000002ULL;
            c18 = 0xE;
            c28 = 0x51;
            c38 = 0x53;
            c40 = 0x0800000000000040ULL;
            *(u64 *)(cursor + 0x00) = c00;
            *(u64 *)(cursor + 0x08) = 0;
            *(u64 *)(cursor + 0x10) = c10;
            *(u64 *)(cursor + 0x18) = c18;
            *(u64 *)(cursor + 0x20) = (((u64)(i << 4)) << 32) | (((u64)(j << 4)) << 48);
            *(u64 *)(cursor + 0x28) = c28;
            *(u64 *)(cursor + 0x30) = 0;
            *(u64 *)(cursor + 0x38) = c38;
            *(u64 *)(cursor + 0x40) = c40;
            *(u64 *)(cursor + 0x48) = 0;
            *(u32 *)(cursor + 0x50) = 0x30000040;
            *(u32 *)(cursor + 0x54) = textureAddress & 0x0FFFFFFF;
            *(u64 *)(cursor + 0x58) = 0;
            textureAddress += 0x400;
            cursor += 0x60;
        }
    }

    *(u32 *)(cursor + 0x00) = 0x20000000;
    off = (bufferIndex << 14) + 0x1C81C0;
    addr = D_001B23C8 + off;
    *(u32 *)(cursor + 0x0C) = 0;
    *(u32 *)(cursor + 0x08) = 0;
    *(u32 *)(cursor + 0x04) = addr;
    BuildFrameDmaChain((void *)(u32)(D_001B23C8 + off), 1);
}

extern char D_001AE830[];
extern void func_00351848(unsigned char *, int *, int *, int *, int *);
extern int func_003518F0(char *, unsigned long long, unsigned long long, int, int);
extern void func_00351868(char *, int);
extern void func_0034F780(int);
extern int func_00350460(u32, int, u32, int, u32, int, int, int);

/* Callback that hands the next piece of movie data to the decoder and reports whether any data was taken. */
int func_00350240(u8 *unused, char *src, char *dst)
{
    int first_address, first_count, second_address, second_count;
    int used = *(int *)(src + 8);
    int remain = *(int *)(src + 0xC);
    int size;
    int second;
    int result;

    size = (int)dst + *(int *)(dst + 0x50008);
    size -= used;
    if (remain < size)
        size = remain;
    second = remain - size;
    VideoDecGetFreeRegions((unsigned char *)(gMoviePlayerState[0] + 0xD9048),
                  &first_address, &first_count, &second_address, &second_count);
    result = CopySplitBuffer((first_address & 0x0FFFFFFF) | 0x20000000, first_count,
                           (second_address & 0x0FFFFFFF) | 0x20000000, second_count,
                           used, size, (int)dst, second);
    if (result > 0) {
        if (VideoDecAddTimestamp(gMoviePlayerState[0] + 0xD9048,
                          *(unsigned long long *)(src + 0x10),
                          *(unsigned long long *)(src + 0x18),
                          first_address, result) == 0)
            SetMovieDebugValue((int)D_001AE830);
    }
    VideoDecAddPendingBytes(gMoviePlayerState[0] + 0xD9048, result);
    return result > 0;
}

extern void func_00336320(void *);
extern void func_00336828(void *);
extern void func_00336A78(void *);
extern float *func_00335E18(void *);
extern float *func_00335E10(void *);
extern unsigned int *func_00335E20(void *);
extern void func_0034AD10(void *);
extern unsigned long func_0027C878(int);
extern void func_0027F640(float, float, unsigned long, char *, int, float, unsigned long, unsigned char *);
extern int func_0027FBD8(int, int, unsigned long, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int D_001A8C64[] __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda)); /* the player's bolts */
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern unsigned char D_001A7A32[] __attribute__((sda)); /* bolt multiplier */
extern char D_001AE6F8[], D_001AE700[], D_001AE708[]; /* "'", ".", "x%d" */
extern int D_001ADAE8 __attribute__((sda));
extern int D_001ADAEC __attribute__((sda));
extern unsigned int D_001ADAF0 __attribute__((sda));

/* A g++ 2.95 vtable entry: this-adjustment, index, function. */
typedef struct HudVEntry {
    short delta;
    short index;
    void (*fn)(void *);
} HudVEntry;

typedef struct HudElem4C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x18];
} HudElem4C;

typedef struct HudElem3C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x8];
} HudElem3C;

typedef struct HudText {
    char pad0[0x34];
    unsigned char *metrics; /* 0x34 */
    long long style;        /* 0x38 */
} HudText;

typedef struct HudOwner {
    HudElem4C top[3];       /* 0x0 */
    char pad0E4[0x1C];
    char panel100[0x48];    /* 0x100 */
    char panel148[0x3C];    /* 0x148 */
    HudElem4C mid[2];       /* 0x184 */
    char pad21C[0x1C];
    HudText text;           /* 0x238 */
    char pad240[0x280 - 0x238 - sizeof(HudText)];
    char panel280[0x40];    /* 0x280 */
    HudElem4C side[2];      /* 0x2C0 */
    HudElem4C a[8];         /* 0x358 */
    HudElem4C b;            /* 0x5B8 */
    HudElem3C c[8];         /* 0x604 */
    char pad7E4[4];
    char final[4];          /* 0x7E8 */
} HudOwner;

/* Draws the bolt counter panel: thousands separators by language (as RAC1's
 * bolt counter) and the "x%d" multiplier. The vtable pointers are read through
 * &a[i] + 0x30 so that every induction value is object-relative, and each
 * loop keeps its own vtable local, as in RAC2's DRAW idiom (00337210.c). */
void func_0034DB98(void *arg)
{
    HudOwner *object = arg;
    char separator[32];
    char multiplierText[16];
    float *scale;
    float x, y, step;
    unsigned int color;
    int foreground, shadow;
    int i, j, digits, n, apostrophe, yoffset, xoffset;

    DrawScreenElementAtStoredPosition(&object->top[0]);
    DrawScreenElementAtStoredPosition(&object->top[1]);
    DrawScreenElementAtStoredPosition(&object->top[2]);
    DrawColoredQuadWidget(object->panel148);
    DrawAlignedTextLabel(object->panel100);
    if (!gNoticeOwner[0]) {
        HudElem4C *left = &object->side[0];
        HudElem4C *right = &object->side[1];
        DrawScreenElementAtStoredPosition(left);
        DrawScreenElementAtStoredPosition(right);
        { float *value = GetSecondField(left); *value = -*value; }
        { float *value = GetSecondField(right); *value = -*value; }
        DrawScreenElementAtStoredPosition(left);
        DrawScreenElementAtStoredPosition(right);
        { float *value = GetSecondField(left); *value = -*value; }
        { float *value = GetSecondField(right); *value = -*value; }
        for (i = 0; i < 8; i++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->a[i] + 0x30);
            vt[1].fn((char *)&object->a[i] + vt[1].delta);
        }
        for (j = 0; j < 8; j++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->c[j] + 0x30);
            vt[1].fn((char *)&object->c[j] + vt[1].delta);
        }
        DrawScreenElementAtStoredPosition(&object->b);
        *GetFieldC(&object->b) = 0x70FFFEED;
    }
    DrawScreenElementAtStoredPosition(&object->mid[0]);
    DrawScreenElementAtStoredPosition(&object->mid[1]);
    DrawAlignedTextLabel(&object->text);
    DrawColoredQuadWidget(object->panel280);
    x = GetFirstField(&object->text)[0];
    y = GetFirstField(&object->text)[1];
    x += 32.0f;
    y += -10.0f;
    color = *GetFieldC(&object->text);
    digits = 1;
    n = gPlayerBolts[0];
    while (n >= 10) { n /= 10; digits++; }
    apostrophe = D_001A7BB0[4] != 3 && D_001A7BB0[4] != 5;
    Sprintf(separator, apostrophe ? D_001AE6F8 : D_001AE700);
    yoffset = apostrophe ? 21 : 10;
    xoffset = apostrophe ? -34 : -29;
    step = 3.0f;
    if (step < (float)digits) {
        float start = x + (float)xoffset;
        do {
            HudText *t = &object->text;
            float drawX = start - (float)(int)(step * 11.6f);
            long long style;
            unsigned long texture;
            step += 3.0f;
            scale = GetSecondField(t);
            style = t->style;
            texture = GetEffectTextureDescriptor((int)style);
            FontPrintScaled(drawX, y + (float)yoffset, color, separator, -1, *scale, texture, t->metrics);
        } while (step < (float)digits);
    }
    if (gBoltMultiplier[0] >= 2) {
        Sprintf(multiplierText, D_001AE708, gBoltMultiplier[0]);
        foreground = (D_001ADAF0 & 0xFFFFFF) | (color & 0xFF000000);
        shadow = color & 0xFF000000;
        DrawTextCenteredLargeFont(D_001ADAE8, D_001ADAEC + 2, shadow, multiplierText, -1);
        DrawTextCenteredLargeFont(D_001ADAE8 + 2, D_001ADAEC, shadow, multiplierText, -1);
        DrawTextCenteredLargeFont(D_001ADAE8 + 2, D_001ADAEC + 2, shadow, multiplierText, -1);
        DrawTextCenteredLargeFont(D_001ADAE8, D_001ADAEC, foreground, multiplierText, -1);
    }
    DrawSegmentedRingMeter(object->final);
}
