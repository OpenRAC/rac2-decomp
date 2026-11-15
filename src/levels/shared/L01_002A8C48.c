/* Per-frame level update: the resident block through a pointer, the tail through fresh
   pointers (retail re-derives them from the kept %hi), the mode word as a macro load. */

#include "common.h"

extern char D_00189E20[];
extern int D_L01_001A8F40 MACRO_ADDR;
extern char D_00189EA0[];

extern void func_L01_002A84D8(void);
extern void func_2C7CA8(void);
extern void func_L00_002B36E0(void);
extern void func_L01_002ADDC8(void);
extern void func_L01_002AE128(char *a0, char *a1, char *a2);
extern void func_L01_002C37C8(void);
extern void func_2C8628(void);
extern void func_L00_002D3068(void);
extern void func_2AEB80(void);
extern void func_2B9878(void);
extern void func_L00_002AC1A0(void);
extern void func_L00_002AB1D8(void);
extern void func_L00_002AB420(void);
extern void func_L00_002ABBA0(void);
extern void func_L00_002AB948(void);
extern void func_L00_002A5518(void);
extern void func_L00_002A5840(void);
extern void func_L00_002B7718(void);
extern void func_2A7740(void);
extern void func_2AB028(void);
extern void func_L00_002AA178(int a0);
extern void func_L00_002B2120(void);
extern void func_L00_002B2318(void);
extern void func_L00_002B2200(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_2A9520(void);
extern void func_2A9310(void);
extern void func_L00_002A67F8(void);
extern void func_L00_002D5EB8(void);
extern void func_L00_002A6420(void);
extern void func_L00_002D5158(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *a0);
extern void func_30F444(int a0);
extern void func_L01_002A9298(void);
extern void func_2AB328(void);

void func_L01_002A8C48(void) {
    char *p;

    p = D_00189E20;
    *(short *)(p + 0x2162) = 0;
    *(short *)(p + 0x2160) = 0;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        func_L01_002A84D8();
        return;
    }
    func_2C7CA8();
    UpdateHeroInputAndHistory();
    func_L01_002ADDC8();
    ProbeLedgeGrab(p + 0x80, p + 0x90, p + 0x550);
    func_L01_002C37C8();
    if (D_L01_001A8F40 == 2 || D_L01_001A8F40 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            func_2C8628();
        else
            func_L00_002D3068();
        return;
    }
    func_2AEB80();
    if (*(unsigned char *)(p + 0x22B4) != 0)
        return;
    func_2B9878();
    UpdateHeroEasingTargetsAndPointEffects();
    func_L00_002AB1D8();
    UpdateHeroPitchAndYawEasingTargets();
    UpdateHeroAutoAimAngles();
    UpdateHeroIdleRandomRotationTargets();
    ClampHeroControlAndUpdateEffects();
    UpdateHeroGlowAndExtraManipulators();
    UpdateHeroTiltPoseTargets();
    func_2A7740();
    func_2AB028();
    func_L00_002AA178(0);
    func_L00_002B2120();
    func_L00_002B2318();
    func_L00_002B2200();
    func_L00_002AFBC0();
    if (*(unsigned char *)(p + 0x22B5) != 0 || func_L00_002D6418() != 0)
        func_2C8628();
    else
        func_L00_002D3068();
    func_2A9520();
    func_2A9310();
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
        func_30F444(*(int *)(q + 0x2290));
    }
    func_L01_002A9298();
    func_2AB328();
}
