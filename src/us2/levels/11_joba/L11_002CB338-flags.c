#include "include_asm.h"

#include "common.h"
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
typedef struct {
    u8 prefix[0x10];
    Vector direction;
    u8 *object;
    unsigned int flags;
    u8 kind, pad29[3];
    float strength;
    unsigned int directionFlags;
    u8 pad34[4];
    u8 *owner;
    u8 pad3c[4];
} ContactEntry;
extern PlayerInputView D_00189E20;
extern ContactEntry D_L11_001C4F80[];
extern int D_L11_001A8F00 __attribute__((sda));
extern u8 D_001A7B0B __attribute__((sda));
extern u8 D_001A7A32 __attribute__((sda));
extern u8 D_001A7A33 __attribute__((sda));
extern int func_US2_L11_002D9208(int, int);
extern float func_L00_0037E668(void);
extern float func_L00_0037E5F0(float);
extern void func_L00_002A6708(void);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_002D36E0(float *, int, float, float, float);
extern void *func_002A9640(void *, unsigned int, int);
extern int func_00283CF0(float);
extern void func_US2_L00_002A4EF8(long);
extern int func_L00_002B9B88(int, int);
extern void func_L00_002B2C58(int, int, float, float);
extern void func_L00_002D3C68(char *, char *, float);

int func_US2_L11_002CB338(long apply)
{
    Vector direction;
    ContactEntry *entry;
    u8 *object, *contact;
    int special;
    if (D_00189E20.movement == 20 || D_00189E20.movement == 7) return 0;
    if (D_00189E20.state == 0x31) return 0;
    if (D_00189E20.timer) return 0;
    if (D_L11_001A8F00) return 0;
    D_00189E20.contact = 0;
    object = D_00189E20.object;
    if (object[0xa8] == 0xff) return 0;
    entry = &D_L11_001C4F80[object[0xa8]];
    if (entry->owner != object) return 0;
    if (!(entry->flags & 9)) return 0;
    if (entry->strength != 0.0f) {
        D_001A7A33 = 0; D_001A7A32 = 1;
    }
    if (func_L00_0037E668() != 0.0f && !D_00189E20.mode) {
        entry->strength = func_L00_0037E5F0(entry->strength);
        if (entry->strength == 0.0f) return 0;
    }
    D_00189E20.contact = entry->object;
    if (!apply) return 1;
    special = 0;
    func_L00_002A6708();
    if (entry->directionFlags & 1) {
        direction.word = entry->direction.word;
        if (entry->direction.f[3] == 5627.9248046875f) special = 1;
    } else if (entry->object) {
        func_00282CF0(&direction, &D_00189E20.position, entry->object+0x10);
    } else func_L00_002D36E0((float *)&direction, 0, -1.0f, 0.0f, 0.0f);
    switch (D_00189E20.mode) {
    case 0:
        contact = D_00189E20.contact;
        if (contact && (*(short *)(contact+0xaa) == 0x4eb || *(short *)(contact+0xaa) == 0x558)) {
            func_US2_L11_002D9208(0x7d, 1); return 1;
        }
        if ((D_00189E20.state == 1 || D_00189E20.state == 0x1d || D_00189E20.interrupted) && !(entry->flags & 8)) {
            u8 *hit = func_002A9640(D_00189E20.object, 1, 0);
            if (hit) func_US2_L00_002A4EF8(func_00283CF0(*(float *)(hit+0x2c)));
            if (!D_00189E20.health) func_US2_L11_002D9208(0x16, 1);
            D_00189E20.timer = 0x4d;
            if (!D_00189E20.soundTimer) D_00189E20.soundTimer = 0x12;
            func_L00_002B9B88(0x14, 0); return 0;
        }
        if (entry->flags & 8) func_US2_L11_002D9208(0x8c, 1);
        else func_US2_L11_002D9208(0x16, 1);
        if (D_00189E20.state == 0x8c) qzero(&direction);
        else {
            func_L00_002B2C58((int)&direction, special, D_00189E20.jumpPressed ? 0.0f : 0.055000003f, 0.028333336f);
            if (special && entry->kind == 4) func_L00_002D3C68((char *)&direction, (char *)&direction, 2.0f);
        }
        break;
    case 1:
        func_US2_L11_002D9208(0x42, 1);
        func_L00_002B2C58((int)&direction, special, 0.083333336f, 0.050000004f);
        break;
    }
    func_00282CC0(&D_00189E20.velocity, &D_00189E20.velocity, &direction);
    func_00282CC0(&D_00189E20.motion, &D_00189E20.motion, &direction);
    return 1;
}
