#include "common.h"

typedef struct {
    u8 pad0[0x20];
    u8 state;
    u8 pad21[0xAA - 0x21];
    short oClass;
    u8 padAC[0x100 - 0xAC];
} GrelbinMoby;

extern int D_US2_L19_001B1F5C __attribute__((sda));
extern int D_US2_L19_001B1F60 __attribute__((sda));
extern GrelbinMoby *D_L19_001B2A1C MACRO_ADDR;
extern GrelbinMoby *D_L19_001B2A20 MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern int D_L19_001A903C[] MACRO_ADDR;
extern int func_002E5E58(int, int, void *);
extern void func_US2_002B1880(int, int);

/* USA v2.00's own function, no v1.01 twin: walks the moby list 40 entries per call, counting live
   mobies of classes 0x11C7, 0x1266 and 0xF57. A full pass that finds none sets the flag at
   D_001A7A60[6] and runs the same award sequence as func_L19_00423548, then returns 1. */
int func_US2_L19_0042BBF8(void)
{
    int i;
    GrelbinMoby *moby;

    if (D_001A7A60[6] == 0) {
        for (i = 0; i < 40; i++) {
            moby = D_L19_001B2A1C + D_US2_L19_001B1F5C;
            if (moby->oClass == 0x11C7 || moby->oClass == 0x1266 || moby->oClass == 0xF57) {
                if (moby != 0 && moby->state != 0xFE && moby->state != 0xFD)
                    D_US2_L19_001B1F60++;
            }
            D_US2_L19_001B1F5C++;
            if (D_L19_001B2A1C + D_US2_L19_001B1F5C >= D_L19_001B2A20) {
                if (D_US2_L19_001B1F60 == 0) {
                    if (D_001A7A60[6] == 0) {
                        D_001A7A60[6] = 1;
                        func_002E5E58(1, 0, 0);
                        func_US2_002B1880(0x1233, -1);
                        D_L19_001A903C[0] = 1;
                    }
                    return 1;
                }
                D_US2_L19_001B1F5C = 0;
                D_US2_L19_001B1F60 = 0;
            }
        }
    }
    return 0;
}
