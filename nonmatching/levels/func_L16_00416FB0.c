/* 30 October 2026 recheck, current game compiler, -O2 -G8 -ffunction-sections.
 * USA v1.01 and v2.00: 600/604 bytes, 0/1 placements each. PAL identity absent.
 * The absolute floating macro is still put in the collision call's delay slot,
 * where the assembler selects the GP form. Full aligned vector locals produce
 * 588 bytes with a worse frame; disabling first scheduling produces 560 bytes.
 * Both are rejected. Retain this 600-byte source, without invented accesses or
 * changed argument banks. Reopen with a call/setup scheduling witness.
 */
/* M33 2026-10-26: 600/604 B, one instruction: everything else is retail's once D_L16_001B1AFC is an incomplete MACRO_ADDR float read [0] (retail lui $at; lwc1), the hero pointer is ((Hero *)D_00189E20)->ptr[0x2290/4] (retail keeps %hi in $s5) and the near/far base is one object (D_L16_001B9B00 + 0x230 for 0x1B9D30). Left: cc1 schedules the l.s macro last and reorg puts it in the func_00277F48 jal slot, where gas turns it into the 4-byte $gp form; retail has lui/lwc1 before the jal and a3=0 in the slot. Float-position prototypes, sda-incomplete and -G0 did not move it. In the permuter. */
#include "common.h"
/* Nonmatching reconstruction; game compiler, -O2 -G8 -ffunction-sections.
   Remeasured after correcting the resident byte to canonical D_001A7A0A:
   us: 600 bytes, expected 604; 0 of 1 places match.
   us2: 600 bytes, expected 604; 0 of 1 places match.
   pal: func_L16_00416FB0 is in neither catalogue of pal.
   D_001A7A0A is below the resident cutoff; its identity agrees with the
   existing declarations in L00_002E3B38.c and L00_002F43D0.c.
   Pointer construction and allocation still differ in this new measurement.
   Reopen with a verified shared-base layout for the camera vectors. */
extern u32 D_00138320 __attribute__((nosda));
extern char D_L16_001B1AD0 __attribute__((sda));
extern char D_L16_001B1AF0 __attribute__((sda));
extern f32 D_L16_001B1B00 __attribute__((sda));
extern f32 D_L16_001B1B04 __attribute__((sda));
extern s32 D_L16_001B1B08 __attribute__((sda));
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; char *ptr[0x980]; } Hero;
extern char D_L16_001B9B00[], D_00189E20[];
extern f32 D_L16_001B1AFC[] MACRO_ADDR;
extern char *D_L16_001BFF58 __attribute__((nosda));
extern char D_L16_001BFF60[];
extern u8 D_001A7A0A __attribute__((nosda));
extern s32 func_00282948(char *);
extern void func_00283098(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, f32);
extern s32 func_00277F48(char *, s32, char *, s32, f32);
extern s32 func_002761F8(char *, char *, s32, char *, s32);
extern void func_00282CF0(char *, char *, char *);
extern void func_L13_0040DC20(char *, char *, char *, s32, f32);

/* Aims the alternating muzzle toward the current ray or collision hit. */
void func_L16_00416FB0(char *self) {
    char muzzle[16], aim[16], far[16], near[16], velocity[16];
    char *st = *(char **)(self + 0x68);
    f32 speed;
    if (!func_00282948(st + 0x8C)) return;
    if (!(D_00138320 & 0xA0)) return;
    func_00283098(muzzle, &D_L16_001B1AD0 + (*(s32 *)(st + 0x88) << 4), self + 0xC0);
    func_00282CC0(muzzle, muzzle, self + 0x10);
    func_00283098(aim, &D_L16_001B1AF0, self + 0xC0);
    func_00282CC0(aim, aim, self + 0x10);
    func_00282F20(near, (D_L16_001B9B00 + 0x230), 2.0f);
    func_00282CC0(near, near, D_L16_001B9B00);
    func_00282F20(far, (D_L16_001B9B00 + 0x230), 120.0f);
    func_00282CC0(far, far, D_L16_001B9B00);
    *(s32 *)(self + 0x98) = 0;
    if (func_00277F48(aim, 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], 0, D_L16_001B1AFC[0]) && D_L16_001BFF58)
        func_00282CF0(velocity, D_L16_001BFF58 + 0x10, muzzle);
    else if (func_002761F8(near, far, 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], 0))
        func_00282CF0(velocity, D_L16_001BFF60, muzzle);
    else func_00282CF0(velocity, far, muzzle);
    func_00282F20(velocity, velocity, D_L16_001B1B00 * 0.01666666753590107f);
    *(s32 *)(self + 0x98) = *(s32 *)(*(char **)(self + 0x24) + 0x10);
    speed = D_L16_001B1B04;
    if (D_001A7A0A) speed *= 5.0f;
    func_L13_0040DC20(self, velocity, muzzle, 0, speed);
    *(s32 *)(st + 0x8C) = D_L16_001B1B08;
    *(s32 *)(st + 0x88) = (*(s32 *)(st + 0x88) + 1) & 1;
}
