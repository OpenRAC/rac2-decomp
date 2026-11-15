#include "include_asm.h"

/* Level reset: frees the two sound handles, restores the camera pose from the 16-byte
   default (a quadword copy of the small-data vector, so this unit is built with -G16). */
#include "common.h"
typedef struct { char pad[0x28]; char *obj; char pad2[0x60 - 0x2C]; int f60; char pad3[0x78 - 0x64]; int soundHandle1; int soundHandle2; char pad4[0x8C - 0x80]; int f8C; } Reset2F8768;
typedef struct { float v[4]; } Vec4_2F8768 __attribute__((aligned(16)));
typedef struct { char pad[0x72]; unsigned short mode; } Mode2F8768;
extern Reset2F8768 D_0021F240;
extern Mode2F8768 D_001A63A8;
extern char D_00189E20[];
extern int D_001A8BB0 __attribute__((sda));
extern Vec4_2F8768 D_001AD200 __attribute__((sda));
extern void func_0028B6C8(int, int);
extern void func_0028E440(void);
extern unsigned int func_0026F748(int, int);
extern void func_0026F728(void);
extern void func_0026F778(char *, void *, int, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern void func_003355A8(int);
extern void func_002FB170(void);
extern void func_0029F338(void *);
extern void func_00132B28(int);
extern void func_002B7320(void);
extern void func_00132028(void);

void func_002F8768(void)
{
    Vec4_2F8768 out;
    float dir[4];
    Vec4_2F8768 in;

    if (gVendorMenuState.soundHandle2 != -1)
        set_animation_parameter(gVendorMenuState.soundHandle2, 0);
    if (gVendorMenuState.soundHandle1 != -1)
        set_animation_parameter(gVendorMenuState.soundHandle1, 0);
    gVendorMenuState.soundHandle2 = -1;
    gVendorMenuState.soundHandle1 = -1;
    TickCountdown();
    gCurrentGameMode = 0;
    EmptyStubF748(0, 1);
    gHeroState[0x22B5] = 0;
    EmptyStubF728();
    if (gVendorMenuState.f60 == 0) {
        qcopy(&in, &D_001AD200);
        matrix_mul_vec3(&out, &in, gVendorMenuState.obj + 0xC0);
        FastVecAdd(&out, &out, gVendorMenuState.obj + 0x10);
        dir[0] = 0;
        dir[1] = 0;
        dir[2] = FastAddRotations(*(float *)(gVendorMenuState.obj + 0xF8), 3.1415927f);
        EmptyStubF778((char *)&out, dir, 0, 0);
        SetCameraModeState(2);
    }
    gVendorMenuState.obj[0x20] = 1;
    if ((unsigned short)(gMusicState.mode - 6) >= 2)
        gMusicState.mode = 5;
    if (gVendorMenuState.f8C != 0)
        ClearShopPreview();
    if (gVendorMenuState.f60 != 0)
        MarkMobySpawned(gVendorMenuState.obj);
    SendSoundCommand23(0x5D);
    music_Unpause();
    snd_Pump();
}
