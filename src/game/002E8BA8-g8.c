#include "common.h"

extern char D_001AC180[];
typedef struct { char pad[0xB0]; float value; } Camera;
extern Camera D_001B9040;
typedef struct { char pad[0x64]; int variant; } SceneMenu;
extern SceneMenu D_00152C00;
typedef struct { char pad[0x34]; int frame; char pad38[0x154]; char *first; } Scene;
extern Scene D_001B8840;
typedef struct { char pad[0x15C]; int mode; int pad160; int next; } Control;
extern Control D_001393E0;
extern char *D_001B2148 MACRO_ADDR;
extern int D_001B1598 MACRO_ADDR, D_001B1490 MACRO_ADDR;
extern int D_001B169C __attribute__((sda));
extern float D_001B15A0 MACRO_ADDR;
extern int D_001A7344;
extern void func_00284F40(int);
extern void func_00279D18(void);
extern void func_0029FB20(void);
extern void func_0027B858(void);
extern void func_0027AB40(void);
extern void func_002E35E0(void);
extern void func_0027C540(int);
extern void func_002E8190(void);
extern void func_0027C660(void);
extern void func_002A03C0(void);
extern void func_002FCF90(int);
extern void func_002E82C8(int);
extern void func_002E7B48(void *);
extern void func_002ECB70(void *);
extern void func_002ED4B8(void);
extern void func_0026FEB8(void *,int,int);
extern void func_002E7BC8(void *);
extern void func_002FC560(unsigned int,unsigned long long);
extern void func_002FC3C0(unsigned long long);
extern void func_0029FEE0(void);
extern void func_0027DDC0(int,int,int,int);
extern unsigned long long func_0027C878(int);
extern int func_00283CF0(float);
extern void func_0027E018(int,int,int,int,int,int,int,int,unsigned long long,unsigned long long);
extern void func_0028F410(float,float,float,float,float,int,int,unsigned long long);
#define H(p,o) (*(short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))

/* Renders the transition scene, its loading indicator and the final fade. */
void func_002E8BA8(void) {
    float saved;
    char *object;
    int alpha;
    AppendDrawListBufferTag(0);
    BuildViewMatrices();
    UpdateWatchedObjects();
    WriteClearColorPackets();
    saved = D_001B9040.value;
    D_001B169C = -1;
    if (saved<0.62f) D_001B9040.value = 0.62f;
    UpdateViewContext();
    BuildViewMatrices();
    BuildViewTransformsAndSubmit();
    D_001B9040.value = saved;
    UpdateViewContext();
    BuildViewMatrices();
    if (gHeroMoby_00152C00.variant==4) {
        SetupGifPaging(1);
        DrawScreenOverlayQuads();
        DoGifPaging();
    }
    UploadMainTextures();
    append_dma_tag(0x2080000);
    SetupGifPaging(1);
    if (gHeroMoby_00152C00.variant==4 && gScenePlaybackState.frame>60) {
        alpha = (gScenePlaybackState.frame-60)*2;
        if (alpha>128) alpha = 128;
        DrawFadeOverlayStrip(alpha);
    }
    if (!D_001B2148 || H(D_001B2148, 0xAA)==0xD54 /* moby class 3412 */) {
        object = gScenePlaybackState.first;
        if (B(object, 0x95)>16) {
            DrawShipEngineFlames(object);
            render_environment_mapped_object(object);
            DrawEffectRecords();
        }
        else STUB_printf(D_001AC180, B(object, 0x95), D_001B1598);

    } else if (B(gScenePlaybackState.first, 0x95)>16) DrawEffectRecords();
    if (D_001B2148 && ((unsigned short)(H(D_001B2148, 0xAA)-0x128C /* moby class 4748 */)<2 || H(D_001B2148, 0xAA)==0x1342 /* moby class 4930 */)) SpawnShipThrusterParticles(D_001B2148);
    if ((unsigned int)(gMemcardState.mode-15)<2 || gMemcardState.next==15 || D_001B1490) {
        float y, angle;
        VU1_addGSregister(0x47, 0x3004B);
        DrawTexturedQuad(0x2C, gScreenHeight-0x60, 64, 64, 0, 0, 64, 64, 0x80808080ULL, GetEffectTextureDescriptor(3));
        y = (float)((gScreenHeight-0x40)<<4);
        angle = (D_001B1598%55)*-0.11423972994f;
        DrawRotatedSprite(1216.0f, y, 272.0f, 272.0f, angle, 64, 64, GetEffectTextureDescriptor(4));
        if ((unsigned int)(gMemcardState.mode-15)<2 || gMemcardState.next==15) D_001B1490 = 30;
        else D_001B1490 = D_001B1490-1;
    }
    DoGifPaging();
    if (gScreenFade>0.0f) {
        if (gScreenFade>1.0f) gScreenFade = 1.0f;
        SetClearColorPacket(0, 0, 0, FloatToInt(gScreenFade*128.0f));
    }
    WaitForDmaStatusBits(16);
    PatchMobyGifs();
}
