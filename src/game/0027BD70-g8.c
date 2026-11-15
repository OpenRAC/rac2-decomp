#include "common.h"

/* Incomplete-array views: the macro form (lui plus low half in ordinary flow, one $gp
   instruction in a delay slot), which is how retail reaches these resident words. */
extern int D_001B1594[] MACRO_ADDR;
extern int D_001B169C[] MACRO_ADDR;
extern int D_001A8BB0[] MACRO_ADDR;
extern float D_001B15A0[] MACRO_ADDR;
extern float D_001B15A4[] MACRO_ADDR;

extern char *ref_0027BD70_00[] MACRO_ADDR;
extern int D_001B1608[] MACRO_ADDR, D_001B160C[] MACRO_ADDR, D_001B1610[] MACRO_ADDR;
extern int D_001B1614[] MACRO_ADDR, D_001B1638[] MACRO_ADDR;
extern int D_001A8770[] SDATA(D_001A8770);
extern char D_0010FFC0[];
extern unsigned short D_0010FFB0 NOT_SDA;
extern int ref_0027BD70_01 NOT_SDA;
extern unsigned long ref_0027BD70_02 NOT_SDA;
extern float D_00189E20[];
extern float ref_0027BD70_03[];
extern char ref_0027BD70_04[], ref_0027BD70_05[];
extern int D_001A7344[] MACRO_ADDR;
extern int ref_0027BD70_06 NOT_SDA;
extern unsigned char D_001AD580[] MACRO_ADDR, D_001AD581[] MACRO_ADDR;
extern unsigned char D_001AD582[] MACRO_ADDR, D_001AD583[] MACRO_ADDR;
extern int D_001A86F4 __attribute__((sda)), D_001A8758 __attribute__((sda));
extern char D_00100AE0[];
extern int D_001A7B90[] MACRO_ADDR;
extern float D_001B1690[] MACRO_ADDR;
extern char ref_0027BD70_07[], ref_0027BD70_08[];
extern int D_001B170C[] MACRO_ADDR;

extern void func_00284F40(int);
extern void func_0027C540(int);
extern void func_002FCF90(int);
extern void func_002FC560(int, unsigned long);
extern void func_0027DCE8(void *);
extern void func_002FC410(void *, int);
extern void func_0011AEA0(int);
extern int func_002B49C8(int);
extern double func_001234F0(float);
extern int func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(int, int, long, char *, int);
extern void func_0027DDC0(int, int, int, int);
extern int func_00283CF0(float);
extern void func_002FC070(void *);
extern float func_00283CE0(int);
extern void func_002FC3C0(int);
extern void func_002F0468(void *);
extern void func_002E2C38(void *);
extern void func_00279D18(void);
extern void func_0029FB20(void);
extern void func_0027A9A0(void);
extern void func_0027B858(void);
extern void func_00291268(void);
extern void func_002EF3B0(void);
extern void func_002F0EF8(void);
extern void func_002FC808(void);
extern void func_0027CEE0(void);
extern void func_0027C660(void);
extern void func_002FC7A8(void);
extern void func_002E11C0(void);
extern void func_0027CF58(void);
extern void func_0027BA68(void);
extern void func_002A03C0(void);
extern void func_0027CE18(void);
extern void func_002725E0(void);
extern void func_0027D160(void);
extern void func_002B9420(void);
extern void func_0027D020(void);
extern void func_002824B8(void);
extern void func_0027D0E8(void);
extern void func_00273418(void);
extern void func_002852D8(void);
extern void func_0027D900(void);
extern void func_0029BF08(void);
extern void func_0028E458(void);
extern void func_00289AA8(void);
extern void func_0027D5C0(void);
extern void func_0027DB68(void);
extern void func_002EF310(void);
extern void func_002F3E78(void);
extern void func_002F0E38(void);
extern void func_002E10B8(void);
extern void func_0029FEE0(void);
extern void func_00279FF0(void);

/* Draws one whole frame: all the game layers, the overlays, the subtitles and the fade effects, in order. */
void func_0027BD70(void)
{
    char text[64];
    float ticks;

    if (!ref_0027BD70_00[0] || *(short *)(ref_0027BD70_00[0] + 4) ||
        ((D_001B1594[0] ^ 1) & 1))
        AppendDrawListBufferTag(0);
    BuildViewMatrices();
    UpdateWatchedObjects();
    UpdateVisibilityByMode();
    WriteClearColorPackets();
    D_001B169C[0] = -1;
    if (ref_0027BD70_00[0] && (D_001B1594[0] & 1))
        InitLevelRendering();
    if (D_001B1594[0] & 2)
        BeginRenderFrame();
    append_dma_tag(0x02010000);
    if (D_001B1594[0] & 4)
        DrawLevelRenderPasses();
    append_dma_tag(0x02020000);
    if (D_001B1610[0]) {
        AppendVu1DmaChainTable3();
        SetupGifPaging(1);
        RunEarlyDrawCallbacks();
        DoGifPaging();
        AppendVu1DmaChainTable2();
    }
    if (D_001B1594[0] & 8)
        BeginRenderBufferSetup();
    append_dma_tag(0x02040000);
    if (D_001A8770[0])
        DrawScreenTintStep(D_001A8770);
    if (D_001B1614[0]) {
        AppendVu1DmaChainTable3();
        SetupGifPaging(1);
        RunLateDrawCallbacks();
        DoGifPaging();
        AppendVu1DmaChainTable2();
    }
    if (D_001B1594[0] & 0x10) {
        if (gCurrentGameMode[0] == 2)
            RenderObjectPreviewToTexture();
        else
            UploadMainTextures();
    }
    append_dma_tag(0x02080000);
    SetupGifPaging(0);
    if ((D_001B1594[0] & 0x20) && D_001B169C[0] != 6) {
        VU1_addDataRef(D_0010FFC0, D_0010FFB0);
        D_001B169C[0] = 6;
    }
    if (D_001B1594[0] & 0x20) {
        AppendVu1DmaChainTable3();
        if (D_001B1608[0])
            RunWorldDrawCallbacks();
        VU1_addGSregister(0x42, 0x8000000048UL);
        DrawLensFlare();
        AppendVu1DmaChainTable3();
        DrawLightQuads();
        VU1_addGSregister(8, 5);
        AppendVu1DmaChainTable3();
        FlushCache(0);
        DrawParticles();
        D_001B169C[0] = 9;
        if (D_001B160C[0]) {
            AppendVu1DmaChainTable3();
            RunOverlayDrawCallbacks();
        }
        DrawGlowSprites();
        if (D_001B1638[0]) {
            AppendVu1DmaChainTable3();
            RunFinalDrawCallbacks();
        }
        VU1_addGSregister(0x42, 0x8000000044UL);
        DrawReticleAndMarkers();
    }
    QueueFirstStripPacket();
    AppendVu1DmaChainTable3();
    if ((D_001B1594[0] & 0x180) && !IsCurrentRequestSlot(3)) {
        VU1_addGSregister(0x47, 0x33001);
        DrawLetterboxBars();
        if (D_001B1594[0] & 0x80) {
            RunLevelCallbacksAndDraw();
            UpdateHudRecordHandlers();
            DrawSubtitleBox();
        }
    }
    if (gCurrentGameMode[0] == 2)
        DrawSubtitles();
    if (ref_0027BD70_01 && (ref_0027BD70_02 & 5) == 5) {
        Sprintf(text, ref_0027BD70_04,
            FloatToDouble(gHeroState[32]),
            FloatToDouble(gHeroState[33]),
            FloatToDouble(gHeroState[34]));
        DrawTextMediumFont(24, gScreenHeight[0] - 54, 0x80F0F0F0L, text, -1);
        Sprintf(text, ref_0027BD70_05,
            FloatToDouble(ref_0027BD70_03[80]),
            FloatToDouble(ref_0027BD70_03[81]),
            FloatToDouble(ref_0027BD70_03[82]));
        DrawTextMediumFont(24, gScreenHeight[0] - 40, 0x80F0F0F0L, text, -1);
    }
    DoGifPaging();
    if (D_001B1594[0] & 0x40) {
        VU1_addGSregister(0x42, 0x8000000044UL);
        if (ref_0027BD70_06)
            SetClearColorPacket(D_001AD580[0], D_001AD581[0], D_001AD582[0], D_001AD583[0]);
        if (gScreenFade[0] > 0.0f) {
            if (gScreenFade[0] > 1.0f)
                gScreenFade[0] = 1.0f;
            SetClearColorPacket(0, 0, 0, FloatToInt(gScreenFade[0] * 128.0f));
        }
        if (D_001B15A4[0] > 0.0f) {
            if (D_001B15A4[0] > 1.0f)
                D_001B15A4[0] = 1.0f;
            SetClearColorPacket(255, 255, 255, FloatToInt(D_001B15A4[0] * 128.0f));
        }
        if (D_001A86F4 && D_001A8758)
            DrawScreenStripeEffect();
    }
    StartDmaChannel0AndWait(D_00100AE0);
    FlushCache(0);
    ticks = IntToFloat(((int)T1_COUNT));
    D_001B1690[0] = ticks * (gIsPalVideo[0] ? (1.0f / 11520.0f) : (1.0f / 9600.0f));
    WaitForDmaStatusBits(2);
    if (D_001B1594[0] & 2) {
        func_002F0468(ref_0027BD70_07);
        PatchTfragGifs();
    }
    WaitForDmaStatusBits(4);
    if (D_001B1594[0] & 4) {
        func_002F3E78();
        ApplyObjectRowOverrides();
    }
    WaitForDmaStatusBits(8);
    if (D_001B1594[0] & 8) {
        ProcessShrubRenderData(ref_0027BD70_08);
        patch_shrub_gifs();
    }
    WaitForDmaStatusBits(16);
    if (D_001B1594[0] & 16)
        PatchMobyGifs();
    ApplyDisplayConfiguration();
    D_001B170C[0] = 0;
}
