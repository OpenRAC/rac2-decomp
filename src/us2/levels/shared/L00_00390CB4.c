#include "include_asm.h"

/* func_US2_L00_00390CB4, the v2.00 copy of func_L00_0038F8B8: the same C with one test added
 * after the level 111/98 gate, on D_US2_001B1860. */
#include "common.h"
/* Partial resident view: only fields observed by the launch gate are named. */
typedef struct { char pad00[0xA8]; u16 launches; char padAA[2]; u32 bestTime, mask; } LaunchStats;
typedef struct {
    char pad00[0x33C]; char *support; int grounded; char pad344[0x434]; float heading;
    char pad77C[0xAB4]; u32 buttons; char pad1234[0xC]; int resource;
    char pad1244[0x2BC]; int special; char pad1504[0xD90]; int level;
    char pad2298[4]; int state; char pad22A0[0x1C]; u8 busy; char pad22BD[0x22F];
    s16 platform; char pad24EE[0x46]; int cooldown; char pad2538[8];
} TetherLaunchHero;
extern TetherLaunchHero D_00189E20;
extern LaunchStats D_0018C360;
extern int D_L00_001A8F00[] __attribute__((sda)), D_L00_001A8F08[] __attribute__((sda));
typedef struct { char pad00[0x1A4]; u32 buttons; } LaunchInput;
extern LaunchInput D_00138180;
extern u32 D_001A7390 MACRO_ADDR;
extern u32 D_001A79F0[] __attribute__((sda));
extern char *D_L00_001B8E10;
extern float D_US2_001B1860 __attribute__((sda));
extern int func_00282948(int *), func_L00_002D3F30(int, int);
extern float func_00282E20(void *), func_00283248(float, float);
extern void func_002AF000(float *, float, float, float), func_00282CC0(void *, void *, void *);
extern void func_002A7470(void *, int, int, int), func_L00_002F46C8(void);
extern char *func_L00_00390FF8(char *, char *, float, float);
extern int func_002E5CF8(int, int, char *);
/* Starts the tether when the shared input and movement gates permit it. */
void func_US2_L00_00390CB4(char *actor) {
    int *state;
    int ready;
    float point[4];
    float heading, pitch;
    u32 now;
    if (!actor) return;
    state = *(int **)(actor + 0x68);
    ready = 1;
    func_00282948(state);
    if (D_00189E20.level == 29) { if (!func_00282948(&D_00189E20.cooldown)) ready = 0; }
    else D_00189E20.cooldown = 40;
    if (D_L00_001A8F00[0] || D_L00_001A8F08[0] != -2 || !(D_00138180.buttons & D_00189E20.buttons) || state[0] || state[1] || D_00189E20.busy) goto finish;
    if (D_00189E20.state == 7 || D_00189E20.state == 2 || D_00189E20.state == 3 || D_00189E20.state == 4 || D_00189E20.state == 5 || D_00189E20.state == 6 || D_00189E20.state == 16 || D_00189E20.state == 14 || D_00189E20.state == 9 || D_00189E20.state == 10 || D_00189E20.state == 11 || D_00189E20.state >= 13 || D_00189E20.level == 111 || D_00189E20.level == 98) goto finish;
    if (D_US2_001B1860 != 0.0f) goto finish;
    if ((D_L00_001B8E10 && *(short *)(D_L00_001B8E10 + 0x86) == 5) || !D_00189E20.grounded || D_00189E20.resource < 23) goto finish;
    if (D_00189E20.support && (*(short *)(D_00189E20.support + 0xAA) == 0x13E || *(short *)(D_00189E20.support + 0xAA) == 0x46F) && ready) goto finish;
    if (!func_L00_002D3F30(-1, 1)) goto denied;
    pitch = 0.0f;
    heading = D_00189E20.heading;
    if (D_00189E20.platform == 1 || D_00189E20.special) {
        pitch = func_00283248(func_00282E20(actor + 0xD0), *(float *)(actor + 0xD8));
        func_002AF000(point, 0.6f, heading, -pitch);
        func_00282CC0(point, point, actor + 0x10);
    } else {
        func_002AF000(point, 0.6f, heading, -pitch);
        func_00282CC0(point, point, actor + 0x10);
    }
    if (*(u8 *)(actor + 0x43) != 3) func_002A7470(actor, 3, 0, 0);
    func_L00_002F46C8();
    *(char **)(state + 1) = func_L00_00390FF8(actor, (char *)point, heading, pitch);
    if (D_0018C360.launches < 0xFFFF) D_0018C360.launches++;
    now = D_001A7390;
    if (D_0018C360.bestTime < now) D_0018C360.bestTime = now;
    D_0018C360.mask |= 1U << D_001A79F0[0];
    D_0018C360.mask |= 0x80000000;
    state[0] = 60;
    goto finish;
denied:
    if (D_00138180.buttons & D_00189E20.buttons) func_002E5CF8(0, 0, actor);
finish:
    if ((*(u8 *)(actor + 0x60) & 2) && *(u8 *)(actor + 0x43) != 1) func_002A7470(actor, 1, 0, 0);
    *(u16 *)(actor + 0x34) |= 4;
}
