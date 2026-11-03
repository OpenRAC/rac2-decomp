#include "include_asm.h"
#include "common.h"

extern s32 D_L10_001B0F44 __attribute__((sda));
extern s32 D_L10_001B0F48 __attribute__((sda));

s32 func_L10_004176A0(void) {
    s32 v = D_L10_001B0F44;
    D_L10_001B0F44 = 0;
    return v;
}

s32 func_L10_004176B0(void) {
    s32 v = D_L10_001B0F48;
    D_L10_001B0F48 = 0;
    return v;
}

extern s32 D_L10_001B0F44 __attribute__((sda));
extern s32 D_L10_001B0F48 __attribute__((sda));
extern u8 D_L10_00265BA0[];
extern u8 *D_L10_001FB1E0[];
extern u8 *D_001B251C;

/* Clears the arena's 128 records of 0x60 bytes and then walks the entry's two-byte
   id list, flagging every live object of one class. */
void func_L10_00417440(u8 *arg0) {
    s32 *p;
    s32 i;
    u8 *q;
    u16 *r;
    u8 *e;

    D_L10_001B0F44 = 0;
    p = (s32 *)D_L10_00265BA0;
    D_L10_001B0F48 = 0;
    p = (s32 *)((u8 *)p + 0x2FE0);
    for (i = 0x7F; i >= 0; i--) {
        *p = 0;
        p -= 0x18;
    }
    q = D_L10_001FB1E0[arg0[0x21]];
    if (q == 0)
        return;
    r = (u16 *)q;
    do {
        e = D_001B251C + ((*r & 0x7FFF) << 8);
        e[0x20] = 1;
        if ((s16)*r < 0)
            break;
        r++;
    } while (1);
}

extern void func_0032BD98(s32 a0, u8 *a1);
extern void func_0032AF78(s32 a0);

/* Releases both timed effects the entry's live objects still hold: the id list walks the
   same arena records as func_L10_00417440, one record per id, and tears down the two
   effect slots at +0x2C4 and +0x2C0 of each record. */
void func_L10_004174C8(u8 *arg0) {
    u16 *r;
    u8 *e;
    u8 *s0;
    u8 *q;
    u32 v;

    q = D_L10_001FB1E0[arg0[0x21]];
    if (q == 0)
        return;
    r = (u16 *)q;
    do {
        e = D_001B251C + ((*r & 0x7FFF) << 8);
        s0 = *(u8 **)(e + 0x68);
        if (*(u8 **)(s0 + 0x2C4) != 0) {
            func_0032BD98((s32)*(u8 **)(s0 + 0x2C4), s0 + 0x370);
            func_0032BD98((s32)*(u8 **)(s0 + 0x2C4), s0 + 0x3B0);
            v = *(u32 *)(*(u8 **)(*(u8 **)(s0 + 0x2C4) + 0x68) + 0x18);
            if (v != 0)
                func_0032AF78(v);
            func_0032AF78((s32)*(u8 **)(s0 + 0x2C4));
            *(u32 *)(s0 + 0x2C4) = 0;
        }
        if (*(u8 **)(s0 + 0x2C0) != 0) {
            func_0032BD98((s32)*(u8 **)(s0 + 0x2C0), s0 + 0x2F0);
            func_0032BD98((s32)*(u8 **)(s0 + 0x2C0), s0 + 0x330);
            v = *(u32 *)(*(u8 **)(*(u8 **)(s0 + 0x2C0) + 0x68) + 0x18);
            if (v != 0)
                func_0032AF78(v);
            func_0032AF78((s32)*(u8 **)(s0 + 0x2C0));
            *(u32 *)(s0 + 0x2C0) = 0;
        }
    } while ((s16)*r++ >= 0);
}

/* The mission state (D_L10_00221CD0), as far as func_L10_00423500 resets it. */
typedef struct {
    u8 pad00[0x10];
    s32 f10;                    /* 0x10 */
    s32 rounds;                 /* 0x14 */
    u8 pad18[0x28 - 0x18];
    s32 f28;                    /* 0x28 */
    s32 waiting;                /* 0x2C */
    f32 f30;                    /* 0x30 */
} MissionState;

/* A 40-byte reward slot of D_L10_002A3C70: available while value has not reached limit. */
typedef struct {
    u8 pad[16];
    s32 limit;                  /* 0x10 */
    s32 value;                  /* 0x14 */
    u8 tail[16];
} RewardSlot;

extern s32 D_L10_001B13A0 __attribute__((sda));  /* the selected kind, -2 for none */
extern s32 D_L10_001B13A4 __attribute__((sda));
extern s32 D_L10_001B1438 __attribute__((sda));  /* set while a kind is being chosen */
extern MissionState D_L10_00221CD0;
extern RewardSlot D_L10_002A3C70[];

extern s32 func_002ED8A0(s32 kind);
extern void func_L05_0037B210(void);
extern void func_L05_00379F28(s32 value);
extern void func_L05_0037D6E8(void);
extern void func_L05_00379F68(void);

/* Resets the mission state and refills the reward slot of kind 6. */
void func_L10_00423500(void *object) {
    s32 slot;

    D_L10_001B13A0 = -2;
    D_L10_001B1438 = 1;
    D_L10_00221CD0.waiting = 1;
    D_L10_00221CD0.f28 = 100;
    D_L10_001B13A4 = 0;
    D_L10_00221CD0.rounds = 0;
    slot = func_002ED8A0(6);
    D_L10_002A3C70[slot].value = D_L10_002A3C70[slot].limit;
    func_L05_0037B210();
    D_L10_00221CD0.f30 = 8.0f;
    D_L10_00221CD0.f10 = 0;
    func_L05_00379F28(0);
    func_L05_0037D6E8();
    func_L05_00379F68();
}
