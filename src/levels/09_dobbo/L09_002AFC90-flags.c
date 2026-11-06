#include "include_asm.h"


typedef unsigned char u8;
extern int D_001A79F0 __attribute__((sda));
extern int D_L09_001A9010 __attribute__((sda));
extern u8 D_001A7B0B __attribute__((sda));
extern void func_00282A88(void *, int);
extern float func_00282C48(float);
extern int func_L09_002C3580(int, int);
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword word; float f[4]; } Vector;
typedef struct {
    u8 prefix[0x80];
    Vector position;
    u8 pad90[0xf0 - 0x90];
    Vector velocity, pad100, motion;
    u8 pad120[0x1dc - 0x120];
    short timer, inputLock;
    u8 pad1e0[0x21c - 0x1e0];
    short soundTimer;
    u8 pad21e[0x318 - 0x21e];
    float t318, elapsed;
    u8 pad320[0x330 - 0x320];
    float t330;
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
    u8 pad1492[2], flag1494;
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
    u8 pad24a0[0x24c4 - 0x24a0];
    float t24c4;
    u8 pad24c8[4];
    int health;
} PlayerInputView;
extern PlayerInputView D_00189E20;

/* Hand-adapted from func_L11_002C51D0. */
void func_L09_002AFC90(void)
{
    short command = D_00189E20.command;
    u8 saved = D_00189E20.saved;
    int active;

    func_00282A88(&D_00189E20.command, 16);
    D_00189E20.command = command;
    D_00189E20.saved = saved;
    D_00189E20.request = 0;
    D_00189E20.pendingJump = 0;
    if (D_00189E20.disabled) return;
    active = 0;
    if (D_00189E20.busy || (D_00189E20.state == 0x7b && D_00189E20.elapsed < 0.4f)) active = 1;
    if (command == -1) return;
    if (command == 2 && !D_00189E20.inputLock &&
        (!D_00189E20.jumpCount || D_00189E20.elapsed < 2.5f)) {
        D_00189E20.jumpPressed = 1;
        if (!D_00189E20.mode && D_001A7B0B) D_00189E20.pendingJump = 1;
    }
    if (command == 14) {
        D_00189E20.flag1494 = 1;
        D_00189E20.t24c4 = 0.2f;
        D_00189E20.t330 = D_00189E20.t318 + 0.2f;
    }
    if (command == 0) {
        float d = D_00189E20.t330 - D_00189E20.t318;

        D_00189E20.t24c4 = d;
        if (d < 0.85f && 0.25f < d) D_00189E20.request = 1;
        D_00189E20.flag1494 = 1;
    }
    if (command == 3) D_00189E20.jump = 1;
    if (command == 11) D_00189E20.cancel = 1;
    if (command == 1) D_00189E20.attack = 1;
    if (command == 8) D_00189E20.hover = 1;
    if (command == 12) D_00189E20.hover = 1;
    if (D_00189E20.attack) {
        if (D_00189E20.attack && active &&
            (D_00189E20.state != 0x38 || D_00189E20.animationDone)) {
            if (D_00189E20.health) { func_L09_002C3580(0x38,1); return; }
            if (D_001A79F0 == 2 && D_L09_001A9010) { func_L09_002C3580(0x7d,1); return; }
            if (*(int *)(*(u8 **)(D_00189E20.object + 0x24) + 0x1f0)) { func_L09_002C3580(0x79,1); return; }
            func_L09_002C3580(0x39,1); return;
        }
    }
    if (D_00189E20.jump && D_00189E20.state != 0x65 && D_00189E20.state != 0x78 &&
        func_00282C48(D_00189E20.jumpTime-(D_00189E20.position.f[2]+0.25f)) < 1.0f &&
        D_00189E20.jumpTime-D_00189E20.position.f[2] > 0.0f &&
        (D_00189E20.state != 0x66 || D_00189E20.animationDone) &&
        (D_00189E20.motion.f[2] < 0.0f || D_00189E20.state == 0x7b)) {
        if (!D_00189E20.health) { func_L09_002C3580(0x78,1); return; }
        func_L09_002C3580(0x65,1); return;
    }
    if (!D_00189E20.cancel || D_00189E20.state == 0x78 || D_00189E20.state == 0x74) return;
    if (!(func_00282C48(D_00189E20.jumpTime-(D_00189E20.position.f[2]+0.25f)) < 1.0f)) return;
    if (!(D_00189E20.jumpTime-D_00189E20.position.f[2] > 0.0f)) return;
    if (!(D_00189E20.motion.f[2] < 0.0f) && D_00189E20.state != 0x7b) return;
    if (D_001A79F0 == 13) {
        func_L09_002C3580(0x74, 1);
        return;
    }
    func_L09_002C3580(0x78, 1);
}
