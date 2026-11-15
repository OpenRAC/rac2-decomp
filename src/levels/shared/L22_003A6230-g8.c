#include "common.h"
typedef struct { u8 pad[0x1874]; int clock; u8 pad2[0x229c-0x1878]; int mode; } Resident;
extern Resident D_00189E20;
typedef struct { u8 pad[0x6c]; short time; u8 pad2[4]; short mode; } Animation;
extern Animation D_001A63A8_4;
extern int ref_L22_003A6230_00 __attribute__((sda));
extern int D_L22_001B1C48;
extern void func_L22_003A64E8(void *,int,int), func_L22_003A6470(void *,int);
extern int func_00282948(void *),func_002A77E0(int);
extern float func_00282EB0(void *,void *);
extern void func_002B6D28(void);
/* Chooses which animation the object should play next, based on its health, the player's state and a few level flags. */
void func_L22_003A6230(u8 *obj) {
    u8 *ctl = *(u8 **)(obj + 0x68);
    float healthRatio = *(float *)(ctl + 0x20) / *(short *)(ctl + 0x24);
    float seconds = gHeroState.clock * 0.00083333335f;
    if (ref_L22_003A6230_00) return;
    if (D_L22_001B1C48 && !(*(int *)(ctl + 0x4E0) & 0x1000000)) {
        *(int *)(ctl + 0x4E0) |= 0x1000000;
        StartFreeAnimationInRange(obj,0,2);
    }
    if (*(int *)(ctl + 0x344) && !(*(int *)(ctl + 0x4E0) & 0x800000))
        StartAnimationSlot(obj,23);
    if (gHeroState.clock == 0)
        StartFreeAnimationInRange(obj,20,22);
    if (healthRatio < 0.25f && !(*(int *)(ctl + 0x4E0) & 0x80))
        StartAnimationSlot(obj,7);
    if (healthRatio > 0.02f && seconds > 0.04f) {
        if (FastFloatHelperD(ctl + 0x4E4) && obj[0x31] &&
            FastVectorHelperC(obj + 0x10, (u8 *)&gHeroState + 0x80) < 1600.0f)
            StartFreeAnimationInRange(obj,3,6);
        if (gHeroState.mode == 7 &&
            !*(int *)((u8 *)&gHeroState + 0x1B8) && RandomIntBelow(2) == 0)
            StartFreeAnimationInRange(obj,8,12);
    }
    if (D_001A63A8_4.mode == 3 && D_001A63A8_4.time < 6000)
        ResumeMusicStream();
}
