#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
extern void func_L03_003F71E0(u8 *, int);
extern int func_31B9F0(int);
extern float func_31BA88(float, float);
extern void func_31B640(int, int, int, int);
extern void func_32ECF8(void);
extern void func_2EEBF0(void *);
typedef struct { u8 pad[0x1B8]; int busy; u8 pad2[0x62]; short timer; u8 pad3[0x2074]; int action; int unknown; int weapon; } Player;
extern Player D_00189E20;
typedef struct { u8 pad[0x6C]; short id; u8 pad2[4]; short mode; } Voice;
extern Voice D_001A63A8;
extern float D_L03_001B3760 __attribute__((sda));
/* Picks boss voice lines to play based on its health, its state and what the hero is doing. */
void func_L03_003F6E88(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    float ratio = *(float *)(state + 0x20) / (float)*(short *)(state + 0x24);
    if (entity[0x20] == 2 && !state[0x41D]) StartBossVoiceLine(entity, 13);
    if (entity[0x20] == 6 && !*(unsigned short *)(state + 0x410)) {
        if (func_31BA88(0, 1) > 0.3f) StartBossVoiceLine(entity, 1);
        else StartBossVoiceLine(entity, 0);
    }
    if (entity[0x20] >= 6) {
        if (entity[0x20] == 15 && !state[0x413]) StartBossVoiceLine(entity, 3);
        if (gHeroState.action == 0x39 && !gHeroState.busy) {
            int choice = func_31B9F0(3);
            if (choice == 0) StartBossVoiceLine(entity, 8);
            else if (choice == 1) {
                StartBossVoiceLine(entity, 9);
                gHeroState.timer = 0xF0;
            }
        }
        if (gHeroState.weapon == 7 && !gHeroState.busy) {
            if (func_31B9F0(5) == 0 && !state[0x41A]) StartBossVoiceLine(entity, 10);
        }
        if (ratio < 0.8f && D_L03_001B3760 >= 0.8f && !func_31B9F0(2)) {
            StartBossVoiceLine(entity, 2);
        } else if (ratio < 0.6f && D_L03_001B3760 >= 0.6f && !func_31B9F0(2)) {
            StartBossVoiceLine(entity, 5);
        } else if (ratio < 0.4f && D_L03_001B3760 >= 0.4f && !func_31B9F0(2)) {
            StartBossVoiceLine(entity, 6);
        } else if (ratio < 0.2f && D_L03_001B3760 >= 0.2f && !func_31B9F0(2)) {
            StartBossVoiceLine(entity, 4);
        }
        D_L03_001B3760 = ratio;
    }
    if (gMusicState.mode == 3 && gMusicState.id < 6000) {
        func_31B640(*(int *)(state + 0x2C4), 1, 0, 10);
        func_32ECF8();
    }
    func_2EEBF0(state + 0x408);
}
