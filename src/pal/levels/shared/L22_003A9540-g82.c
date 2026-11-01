#include "include_asm.h"

#include "common.h"
typedef struct { u8 pad[0x1874]; int clock; u8 pad2[0x229c-0x1878]; int mode; } Resident;
extern Resident D_00189E20;
typedef struct { u8 pad[0x6c]; short time; u8 pad2[4]; short mode; } Animation;
extern Animation D_001A63A8_4;
extern int ref_L22_003A6230_00 __attribute__((sda));
extern int D_L22_001B1C48;
extern void func_PAL_L22_003A9880(void *,int,int), func_PAL_L22_003A9808(void *,int);
extern int func_00282948(void *),func_002A77E0(int);
extern float func_00282EB0(void *,void *);
extern void func_002B6D28(void);

void func_PAL_L22_003A95C8(u8 *obj) {
    u8 *ctl = *(u8 **)(obj + 0x68);
    float ratio = *(float *)(ctl + 0x20) / *(short *)(ctl + 0x24);
    float time = D_00189E20.clock * 0.00083333335f;
    if (ref_L22_003A6230_00) return;
    if (D_L22_001B1C48 && !(*(int *)(ctl + 0x4E0) & 0x1000000)) {
        *(int *)(ctl + 0x4E0) |= 0x1000000;
        func_PAL_L22_003A9880(obj,0,2);
    }
    if (*(int *)(ctl + 0x344) && !(*(int *)(ctl + 0x4E0) & 0x800000))
        func_PAL_L22_003A9808(obj,23);
    if (D_00189E20.clock == 0)
        func_PAL_L22_003A9880(obj,20,22);
    if (ratio < 0.25f && !(*(int *)(ctl + 0x4E0) & 0x80))
        func_PAL_L22_003A9808(obj,7);
    if (ratio > 0.02f && time > 0.04f) {
        if (func_00282948(ctl + 0x4E4) && obj[0x31] &&
            func_00282EB0(obj + 0x10, (u8 *)&D_00189E20 + 0x80) < 1600.0f)
            func_PAL_L22_003A9880(obj,3,6);
        if (D_00189E20.mode == 7 &&
            !*(int *)((u8 *)&D_00189E20 + 0x1B8) && func_002A77E0(2) == 0)
            func_PAL_L22_003A9880(obj,8,12);
    }
    if (D_001A63A8_4.mode == 3 && D_001A63A8_4.time < 6000)
        func_002B6D28();
}
