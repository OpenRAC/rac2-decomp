/* func_PAL_L03_002B8C28, the PAL copy of func_L03_002B8D10: the same C, where lit 0.024f becomes 0.0288f. */
#include "common.h"

typedef union { int quad __attribute__((mode(TI))); struct { float x, y, z, w; } f; } HopVector;
/* Player (Ratchet) state block in the level's data, reached through D_L03_00189E20. */
typedef struct {
    HopVector field_0;
    unsigned char pad_10[0x10];
    HopVector field_20;
    unsigned char pad_30[0x68];
    float rot_z;
    unsigned char pad_9C[0x54];
    float vel_x;
    float vel_y;
    unsigned char pad_F8[0x68];
    HopVector field_160;
    unsigned char pad_170[0x4];
    float field_174;
    unsigned char pad_178[0x18];
    HopVector field_190;
    float facing_angle;
    float field_1A4;
    float field_1A8;
    unsigned char pad_1AC[0x4];
    float field_1B0;
    float field_1B4;
    int state_time;
    unsigned char pad_1BC[0x18c];
    short field_348;
    short field_34A;
    unsigned char pad_34C[0x108];
    float field_454;
    unsigned char pad_458[0x18];
    HopVector field_470;
    HopVector field_480;
    unsigned char pad_490[0x4];
    float field_494;
    unsigned char pad_498[0x6];
    unsigned char field_49E;
    unsigned char pad_49F[0xf];
    short field_4AE;
    unsigned char pad_4B0[0xc];
    float field_4BC;
    float field_4C0;
    float field_4C4;
    unsigned char pad_4C8[0xc];
    int field_4D4;
    float field_4D8;
    float field_4DC;
    unsigned char pad_4E0[0x10];
    HopVector field_4F0;
    unsigned char pad_500[0x20];
    float field_520;
    short field_524;
    unsigned char pad_526[0x7];
    unsigned char field_52D;
    unsigned char pad_52E[0x532];
    HopVector field_A60;
    unsigned char pad_A70[0x14];
    float field_A84;
    unsigned char pad_A88[0x1b0];
    float anim_time;
    unsigned char pad_C3C[0x804];
    HopVector field_1440;
    unsigned char pad_1450[0x4];
    short field_1454;
    unsigned char pad_1456[0x2];
    float field_1458;
    unsigned char pad_145C[0xe38];
    int state;
    unsigned char pad_2298[0x4];
    int field_229C;
    unsigned char pad_22A0[0x23];
    unsigned char field_22C3;
    unsigned char pad_22C4[0x1f4];
    float field_24B8;
} HopPlayer;
#define HOP_PLAYER (*(HopPlayer *)D_L03_00189E20)
typedef struct {
    unsigned char pad_0[0x158];
    float angle;
    unsigned char pad_15C[0x214];
    HopVector basis;
} HopSavedState;
extern unsigned char D_L03_001B9840[];
#define HOP_SAVED (*(HopSavedState *)D_L03_001B9840)
/* Object (moby) header: its state pointer and class id. */
/* Particle record returned by func_002BDCE8; its payload follows at 0x20. */
typedef struct {
    unsigned char pad_0[4];
    int mode;
    unsigned char pad_8[2];
    unsigned char alpha;
    unsigned char alpha_copy;
} ParticlePayload;

typedef struct {
    unsigned char pad_0[8];
    unsigned char variation;
    unsigned char pad_9;
    union {
        short duration;
        unsigned char duration_lo;
    } life;
    unsigned char pad_C[0x14];
    ParticlePayload payload;
} Particle;

/* Particle emitter inputs; the two register banks retain their EE argument order. */
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern Particle *func_002BDCE8(void *, float, float, float, int, void *, float, unsigned int, int);

#define MACRO_ADDR __attribute__((section(".sdata")))

typedef int TI128 __attribute__((mode(TI)));

extern unsigned char D_L03_00189E20[];

extern int r1_D_L02_0015F04C MACRO_ADDR;

extern TI128 D_001A8F20;

/* func_L03_002ADC00 is in its dedicated zero-vector profile unit. */

extern float func_002AA2E8(float *, float, float);
extern void func_002AA3A8(float *, float *, float, float, float, float);
extern float func_00282E80(void *, void *);

void func_PAL_L03_002B8C28(void) {
    switch (D_L03_00189E20[0x22B4]) {
    case 0:
        *(float *)(D_L03_00189E20 + 0x258) = 0.8f;
        *(float *)(D_L03_00189E20 + 0x25C) = 0.7f;
        *(float *)(D_L03_00189E20 + 0x260) = 0.449999988079071f;
        break;
    case 1:
        *(float *)(D_L03_00189E20 + 0x258) = 0.599999964237213f;
        *(float *)(D_L03_00189E20 + 0x25C) = 0.450000017881394f;
        *(float *)(D_L03_00189E20 + 0x260) = 0.3f;
        break;
    }
    {
        unsigned char *g = D_L03_00189E20;
        if (*(int *)(g + 0x229C) == 4) {
            if (*(short *)(g + 0x4AC) < *(int *)(g + 0x1B8) && !g[0x49E])
                *(float *)(g + 0x25C) = *(float *)(g + 0x4B8);
        } else if (*(int *)(g + 0x2294) == 6) {
            *(float *)(g + 0x25C) = 0.5f;
        } else if (*(int *)(g + 0x2294) == 4) {
            *(float *)(g + 0x258) = 0.350000023841858f;
        } else if (*(int *)(g + 0x2294) == 0x7C) {
            *(float *)(g + 0x260) = 0.8f;
        }
    }
    if (!D_L03_00189E20[0x287] || *(int *)(D_L03_00189E20 + 0x22A4) == 0x12 ||
        *(int *)(D_L03_00189E20 + 0x22B0) == 0x12 ||
        (!D_L03_00189E20[0x22B4] && *(float *)(D_L03_00189E20 + 0x254) < 0.53f) ||
        *(int *)(D_L03_00189E20 + 0x229C) == 0x11 || D_L03_00189E20[0x1494] ||
        func_00282E80(D_L03_00189E20 + 0x240, D_L03_00189E20 + 0x80) > *(float *)(D_L03_00189E20 + 0x264) * 0.5f) {
        float *p = (float *)(D_L03_00189E20 + 0x250);
        unsigned char *g = D_L03_00189E20;
        func_002AA2E8(p, *(float *)(g + 0x258), 0.024f);
        func_002AA2E8(p + 1, *(float *)(g + 0x25C), 0.024f);
        func_002AA3A8(p + 5, p + 6, *(float *)(g + 0x260), 0.028800001f, 0.43200004f, 0.080000006f);
    }
}

/* Per-state airborne steering of the player: velocity, facing and speed targets. */
#undef HOP_PLAYER
#undef HOP_SAVED

/* rac1-decomp src/overlays/shared/camera_001FC308.c: func_L02_001FC308 */
/* Adapted from Lombyte (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay/camera/001fc008.c, FUN_L02_001fc008. */
/* Emits two particle groups scaled by the object's transformed basis length. */
/* func_L03_00329EF0 is defined in L03_002AB5C8-region.c. */

/* func_L03_00339128 is defined in L03_00339128-qcopy.c. */

/* func_L03_0038AB30 is defined in L03_002AB5C8-ribbon.c (its own loop-pass flags). */

/* func_L03_0038B238 is defined in L03_002AB5C8-g8.c (this unit has no $gp access for it). */

extern void func_00282CC0(void *, void *, void *);
extern float (*D_L03_001FE700[])[4];

/* Effect state hung off an object: four vertex-table indices, a vertex count and an offset. */
/* Adjusts each vertex of the object's groups relative to a computed centre, then offsets it by the state vector. */
float func_L03_003C5AB8(unsigned char *);

/* func_L03_003C4240 is defined in L03_002AB5C8-g8.c (it reads two $gp constants). */

/* func_L03_003C4368 is defined in L03_003C4368-g8.c. */

/* func_L03_003C4468 is defined in L03_003C4468-flags.c. */

/* func_L03_003C4578 is defined in L03_002AB5C8-g8.c (it reads $gp data). */

/* func_L03_003C4A10 is defined in L03_002AB5C8-g8.c (it reads $gp data). */

extern int func_002A77E0(int);

/* The level's own copy of the object's tilt routine (func_L03_003C4A10), at another address
   in every level that has it. */
/* The position the tilt is measured from: a four-float vector in the boot's resident data. */
/* The level's entity table base, the group count and the table of group id lists (in the
   resident image: the list of group g ends after its first entry with bit 15 set). */
/* The part of the object's private state (at +0x68) that these walks read: eight group ids at
   +0x200 and the id of an entity at +0x220. */
extern float func_00282E80(void *, void *);

/* Returns the entity nearest to the object, within 15.0, among its eight groups, that has bit 12
   of its flags at 0x34 set, a value of 5 at 0x46 of the record at 0x24, a height (at 0x18)
   within 1.5 of the object's and that func_L03_00419BD8 accepts, or 0. */
/* Returns the entity of class 0xEF9 nearest to the object, within 15.0, among its eight groups
   (func_L03_004197A8 and func_L03_00419BD8 must both accept it), or 0. */
/* Returns the first entity of class 0x97A, in the object's eight groups, that
   func_L03_003CAAC8 finds near the object or near the player, or 0. The group table is reached
   through a local pointer: with its address computed once outside the loops, the walk's other
   constants (0x97A, 0xFF, the player's address) all fit loop.c's budget for moving invariants
   out of the walk, as in retail. */
/* Returns the entity of class 0xE87 or 0xE88 in state 1 nearest to the object, within 14.0,
   among its eight groups, or 0. */
/* Returns the entity of class 0xB10, or of class 0xF4D that func_L03_003CA280 accepts (state 1),
   nearest to the object, within 10.0, among its eight groups (entities in state 0xFE or 0xFD are
   skipped), or 0. The group table goes through a local pointer, as in func_L03_003C5128: that is
   what leaves 0xFE out of loop.c's budget for hoisting the walk's constants, as in retail. */
/* func_L03_003C58F0 is defined in L03_002AB5C8-g8.c (it reads the group count through $gp). */

float func_L03_003C5AB8(unsigned char *a0);
