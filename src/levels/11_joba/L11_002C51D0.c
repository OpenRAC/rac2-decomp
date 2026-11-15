#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword word; float f[4]; } Vector;
/* Partial resident view. Field offsets and widths follow the retail accesses. */
typedef struct {
    u8 prefix[0x80];
    Vector position;
    u8 pad90[0xf0 - 0x90];
    Vector velocity, pad100, motion;
    u8 pad120[0x1dc - 0x120];
    short timer, inputLock;
    u8 pad1e0[0x21c - 0x1e0];
    short soundTimer;
    u8 pad21e[0x31c - 0x21e];
    float elapsed;
    u8 pad320[0x334 - 0x320];
    float jumpTime;
    u8 pad338[8];
    int busy;
    u8 pad344[4];
    short pendingJump;
    u8 pad34a[2];
    short jumpCount;
    u8 pad34e[0x49e - 0x34e];
    u8 animationDone;
    u8 pad49f[0x1490 - 0x49f];
    short command;
    u8 pad1492[3];
    u8 attack, jump, jumpPressed, pad1498[2], hover, cancel, pad149c, saved;
    u8 pad149e[0x1500 - 0x149e];
    int interrupted;
    u8 pad1504[0x2290 - 0x1504];
    u8 *object;
    int state, phase, movement;
    u8 pad22a0[0x22b4 - 0x22a0];
    u8 mode;
    u8 pad22b5[0x22b9 - 0x22b5];
    u8 request;
    u8 pad22ba[3];
    u8 disabled;
    u8 pad22be[0x249c - 0x22be];
    u8 *contact;
    u8 pad24a0[0x24cc - 0x24a0];
    int health;
} PlayerInputView;

extern PlayerInputView D_00189E20;
extern int D_001A79F0 __attribute__((sda));
extern int D_L11_001A9010 __attribute__((sda));
extern u8 D_001A7B0B __attribute__((sda));
extern void func_00282A88(void *, int);
extern float func_00282C48(float);
extern int func_L11_002D8EF8(int, int);

/* Reads the newest button command and sets the hero's attack, jump, cancel and hover flags. It then starts the matching hero state, such as a swing, a jump or a glide. */
void func_L11_002C51D0(void)
{
    short command = gHeroState.command;
    u8 saved = gHeroState.saved;
    int active;

    FastMemoryHelperB(&gHeroState.command, 16);
    gHeroState.command = command;
    gHeroState.saved = saved;
    gHeroState.request = 0;
    gHeroState.pendingJump = 0;
    if (gHeroState.disabled) return;
    active = 0;
    if (gHeroState.busy || (gHeroState.state == 0x7b && gHeroState.elapsed < 0.4f)) active = 1;
    if (command == -1) return;
    if (command == 2 && !gHeroState.inputLock &&
        (!gHeroState.jumpCount || gHeroState.elapsed < 2.5f)) {
        gHeroState.jumpPressed = 1;
        if (!gHeroState.mode && D_001A7B0B) gHeroState.pendingJump = 1;
    }
    if (command == 3) gHeroState.jump = 1;
    if (command == 11) gHeroState.cancel = 1;
    if (command == 1) gHeroState.attack = 1;
    if (command == 8) gHeroState.hover = 1;
    if (command == 12) gHeroState.hover = 1;
    if (gHeroState.attack) {
        if (active && gHeroState.mode == 1 && gHeroState.state != 0x7a) {
            EnterHeroState_L11(0x7a,1); return;
        }
        if (gHeroState.attack && active &&
            (gHeroState.state != 0x38 || gHeroState.animationDone)) {
            if (gHeroState.health) { EnterHeroState_L11(0x38,1); return; }
            if (gCurrentMapIndex == 2 && D_L11_001A9010) { EnterHeroState_L11(0x7d,1); return; }
            if (*(int *)(*(u8 **)(gHeroState.object + 0x24) + 0x1f0)) { EnterHeroState_L11(0x79,1); return; }
            EnterHeroState_L11(0x39,1); return;
        }
    }
    if (gHeroState.jump && gHeroState.state != 0x65 && gHeroState.state != 0x78 &&
        FloatAbs(gHeroState.jumpTime-(gHeroState.position.f[2]+0.25f)) < 1.0f &&
        gHeroState.jumpTime-gHeroState.position.f[2] > 0.0f &&
        (gHeroState.state != 0x66 || gHeroState.animationDone) &&
        (gHeroState.motion.f[2] < 0.0f || gHeroState.state == 0x7b)) {
        if (!gHeroState.health) { EnterHeroState_L11(0x78,1); return; }
        EnterHeroState_L11(0x65,1); return;
    }
    if (!gHeroState.cancel || gHeroState.state == 0x78 || gHeroState.state == 0x74) return;
    if (!(FloatAbs(gHeroState.jumpTime-(gHeroState.position.f[2]+0.25f)) < 1.0f)) return;
    if (!(gHeroState.jumpTime-gHeroState.position.f[2] > 0.0f)) return;
    if (!(gHeroState.motion.f[2] < 0.0f) && gHeroState.state != 0x7b) return;
    if (gCurrentMapIndex == 13) {
        EnterHeroState_L11(0x74, 1);
        return;
    }
    EnterHeroState_L11(0x78, 1);
}


