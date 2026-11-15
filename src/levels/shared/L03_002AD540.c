#include "include_asm.h"
/* Per-frame level update (the L01 body's layout): the resident block through a pointer, the
   tail through fresh pointers, the mode word as a macro load; program-specific calls by ref_. */

#include "common.h"

extern char D_00189E20[];
extern int D_L03_001A8F00 MACRO_ADDR;
extern char D_00189EA0[];

extern void ref_L03_002AD540_00(void);
extern void func_L00_002D24E8(void);
extern void ref_L03_002AD540_01(void);
extern void ref_L03_002AD540_02(void);
extern void ref_L03_002AD540_03(char *a0, char *a1, char *a2);
extern void ref_L03_002AD540_04(void);
extern void ref_L03_002AD540_05(void);
extern void func_L00_002D2E68(void);
extern void func_L00_002D3068(void);
extern void func_L00_002AE0C8(void);
extern void func_L00_002B9CA8(void);
extern void func_L00_002AC1A0(void);
extern void func_L00_002AB1D8(void);
extern void func_L00_002AB420(void);
extern void func_L00_002ABBA0(void);
extern void func_L00_002AB948(void);
extern void func_L00_002A5518(void);
extern void func_L00_002A5840(void);
extern void func_L00_002B7718(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9460(void);
extern void func_L00_002AA178(int a0);
extern void func_L00_002B2120(void);
extern void func_L00_002B2318(void);
extern void func_L00_002B2200(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_L00_002A67F8(void);
extern void func_L00_002D5EB8(void);
extern void func_L00_002A6420(void);
extern void func_L00_002D5158(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *a0);
extern void func_002A677C(int a0);
extern void ref_L03_002AD540_06(void);
extern void func_L00_002A9760(void);

void func_L03_002AD540(void) {
    char *p;

    p = D_00189E20;
    *(short *)(p + 0x2162) = 0;
    *(short *)(p + 0x2160) = 0;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        ref_L03_002AD540_00();
        return;
    }
    AdvanceHeroAnimation();
    ref_L03_002AD540_01();
    ref_L03_002AD540_02();
    ref_L03_002AD540_03(p + 0x80, p + 0x90, p + 0x550);
    ref_L03_002AD540_04();
    ref_L03_002AD540_05();
    if (D_L03_001A8F00 == 2 || D_L03_001A8F00 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            func_L00_002D2E68();
        else
            func_L00_002D3068();
        return;
    }
    RebuildRegionObjectMembership();
    if (*(unsigned char *)(p + 0x22B4) != 0)
        return;
    UpdateDelayedSounds();
    UpdateHeroEasingTargetsAndPointEffects();
    func_L00_002AB1D8();
    UpdateHeroPitchAndYawEasingTargets();
    UpdateHeroAutoAimAngles();
    UpdateHeroIdleRandomRotationTargets();
    ClampHeroControlAndUpdateEffects();
    UpdateHeroGlowAndExtraManipulators();
    UpdateHeroTiltPoseTargets();
    func_L00_002A5368();
    update_hero_moby();
    func_L00_002AA178(0);
    func_L00_002B2120();
    func_L00_002B2318();
    func_L00_002B2200();
    func_L00_002AFBC0();
    if (*(unsigned char *)(p + 0x22B5) != 0 || func_L00_002D6418() != 0)
        func_L00_002D2E68();
    else
        func_L00_002D3068();
    func_L00_002A7958();
    ApplyHeroAxisScales();
    func_L00_002A67F8();
    func_L00_002D5EB8();
    func_L00_002A6420();
    UpdateHeroAimAndTransitions();
    {
        char *q = D_00189E20;
        if ((*(int *)(q + 0x229C) != 0x16 && *(int *)(q + 0x229C) != 0x1F
             && *(int *)(q + 0x2294) != 0x31) || func_L00_002A7000() != 0)
            func_L00_003080D0(D_00189EA0);
    }
    {
        char *q = D_00189E20;
        func_002A677C(*(int *)(q + 0x2290));
    }
    ref_L03_002AD540_06();
    UpdateHeroMobyProbedHeightBounds();
}
