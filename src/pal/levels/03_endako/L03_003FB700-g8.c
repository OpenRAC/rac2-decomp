#include "include_asm.h"

typedef unsigned char u8;
extern void func_PAL_L03_003FBA58(u8 *, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_PAL_002A7E68(int, int, int, int);
extern void func_002B6D28(void);
extern void func_00282948(void *);
typedef struct { u8 pad[0x1B8]; int busy; u8 pad2[0x62]; short timer; u8 pad3[0x2074]; int action; int unknown; int weapon; } Player;
extern Player D_00189E20;
typedef struct { u8 pad[0x6C]; short id; u8 pad2[4]; short mode; } Voice;
extern Voice D_001A63A8;
extern float D_L03_001B3760 __attribute__((sda));

void func_PAL_L03_003FB700(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    float ratio = *(float *)(state + 0x20) / (float)*(short *)(state + 0x24);
    if (entity[0x20] == 2 && !state[0x41D]) func_PAL_L03_003FBA58(entity, 13);
    if (entity[0x20] == 6 && !*(unsigned short *)(state + 0x410)) {
        if (func_002A7878(0, 1) > 0.3f) func_PAL_L03_003FBA58(entity, 1);
        else func_PAL_L03_003FBA58(entity, 0);
    }
    if (entity[0x20] >= 6) {
        if (entity[0x20] == 15 && !state[0x413]) func_PAL_L03_003FBA58(entity, 3);
        if (D_00189E20.action == 0x39 && !D_00189E20.busy) {
            int choice = func_002A77E0(3);
            if (choice == 0) func_PAL_L03_003FBA58(entity, 8);
            else if (choice == 1) {
                func_PAL_L03_003FBA58(entity, 9);
                D_00189E20.timer = 0xC8;
            }
        }
        if (D_00189E20.weapon == 7 && !D_00189E20.busy) {
            if (func_002A77E0(5) == 0 && !state[0x41A]) func_PAL_L03_003FBA58(entity, 10);
        }
        if (ratio < 0.8f && D_L03_001B3760 >= 0.8f && !func_002A77E0(2)) {
            func_PAL_L03_003FBA58(entity, 2);
        } else if (ratio < 0.6f && D_L03_001B3760 >= 0.6f && !func_002A77E0(2)) {
            func_PAL_L03_003FBA58(entity, 5);
        } else if (ratio < 0.4f && D_L03_001B3760 >= 0.4f && !func_002A77E0(2)) {
            func_PAL_L03_003FBA58(entity, 6);
        } else if (ratio < 0.2f && D_L03_001B3760 >= 0.2f && !func_002A77E0(2)) {
            func_PAL_L03_003FBA58(entity, 4);
        }
        D_L03_001B3760 = ratio;
    }
    if (D_001A63A8.mode == 3 && D_001A63A8.id < 6000) {
        func_PAL_002A7E68(*(int *)(state + 0x2C4), 1, 0, 8);
        func_002B6D28();
    }
    func_00282948(state + 0x408);
}
