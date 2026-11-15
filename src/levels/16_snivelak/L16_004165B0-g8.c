#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;

extern char *D_L16_001B2B1C __attribute__((sda));
extern char *D_L16_001B2B1C_2;
extern char D_00189EA0[];
extern s32 func_00319BE8(char *, s32);

/* runs the object's start-up state once and marks the four sub-objects it carries as alive */
void func_L16_00418D28(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *entry;
    u8 entryState;

    if (*(u8 *)(moby + 0x20) == 0)
        *(u8 *)(moby + 0x20) = 1;
    if (*(u8 *)(moby + 0x20) != 1)
        return;

    entry = (*(s32 *)vars << 8) + D_L16_001B2B1C_2;
    if (entry != 0) {
        entryState = *(u8 *)(entry + 0x20);
        if (entryState != 0xFE) {
            if (entryState != 0xFD)
                return;
        }
    }
    if (func_00319BE8(gHeroPosition, *(s32 *)(vars + 4)) == 0)
        return;
    if (*(s32 *)(vars + 0x10) != -1)
        *(u8 *)(D_L16_001B2B1C + (*(s32 *)(vars + 0x10) << 8) + 0xBC) = 1;
    if (*(s32 *)(vars + 0x14) != -1)
        *(u8 *)(D_L16_001B2B1C + (*(s32 *)(vars + 0x14) << 8) + 0xBC) = 1;
    if (*(s32 *)(vars + 0x18) != -1)
        *(u8 *)(D_L16_001B2B1C + (*(s32 *)(vars + 0x18) << 8) + 0xBC) = 1;
    if (*(s32 *)(vars + 0x1C) != -1)
        *(u8 *)(D_L16_001B2B1C + (*(s32 *)(vars + 0x1C) << 8) + 0xBC) = 1;
    *(u8 *)(moby + 0x20) = 2;
}

extern s32 D_L16_001B1FCC __attribute__((sda));
extern s32 D_L16_001B1FC4 __attribute__((sda));
extern s32 D_L16_001B1FC8 __attribute__((sda));
extern s32 D_L16_001B1FD0 __attribute__((sda));
extern s32 D_001B3AAC __attribute__((nosda));
extern f32 D_L16_001B3AAC __attribute__((sda));
extern s32 func_003219A0(char *);
extern void func_00313DD0(char *, s32, s32);
extern f32 func_002E73F8(f32);
extern void func_0041ECF8(char *, f32);

extern f32 D_L16_001B1C60 __attribute__((sda));
extern f32 D_001B1C64 __attribute__((nosda));
extern f32 D_001B1C68 __attribute__((nosda));
extern f32 D_001B1C6C __attribute__((nosda));
extern f32 D_L16_001B1C70 __attribute__((sda));
extern f32 D_001B1C74 __attribute__((nosda));
extern s32 D_L16_001B1C78 __attribute__((sda));
extern s32 D_001B1C7C __attribute__((nosda));
extern s32 D_L16_001B1C80 __attribute__((sda));
extern s32 D_001B1C84 __attribute__((nosda));
extern s32 D_001B1C88 __attribute__((nosda));
extern s32 D_001B1C8C __attribute__((nosda));
extern s32 D_L16_001B1C90 __attribute__((sda));
extern void func_003140C0(char *, f32, f32);
extern s32 func_00313EE0(s32, s32);
extern s32 func_00313EA0(s32);
extern s32 func_003320E0(char *, char *, u32, u32, f32, u32, u32);
extern f32 func_00313F38(f32, f32);
extern void func_002E7450(char *);
extern void func_002E7488(char *, char *, char *);

extern s32 D_0018B650 __attribute__((nosda));
extern s32 D_L16_001B16C0 __attribute__((sda));
extern void func_002C4368(s32);
extern void func_00433698(s32);

/* clears the level state word and reseeds the two engine subsystems */
void func_L16_00416E88(void) {
    D_0018B650 = 0;
    D_L16_001B16C0 = 0;
    func_002C4368(0);
    func_00433698(3);
}

extern f32 D_L16_001B1E90 __attribute__((sda));
extern f32 D_L16_001B1E94 __attribute__((sda));
extern void func_0031C698(char *, char *, char *, f32, f32, f32);

/* submits the sub-object at 0x68 with the level's angle scale */
void func_L16_0041C948(char *moby) {
    char *self = moby;
    char *st = *(char **)(self + 0x68);

    func_0031C698(self, st + 4, st, D_L16_001B1E90, D_L16_001B1E94 * 0.000290888245f, -1.0f);
}

extern char D_00189EA0[];
extern s32 D_L16_001B1A80 __attribute__((sda));
extern void func_002E7968(char *, s32 *, char *);
extern void func_002E7488(char *, char *, char *);

/* installs the two level matrices on the shared render object */
void func_L16_00416E30(char *moby) {
    char *obj = gHeroPosition;

    func_002E7968(obj, &D_L16_001B1A80, moby + 0xC0);
    func_002E7488(obj, obj, moby + 0x10);
    *(f32 *)(obj + 0x18) = *(f32 *)(moby + 0xF8);
}

extern f32 D_L16_001B1C28 __attribute__((sda));
extern f32 D_L16_001B1C2C __attribute__((sda));
extern f32 D_L16_001B1C30 __attribute__((sda));
extern f32 D_L16_001B1C34 __attribute__((sda));

/* initialises the level object's scale/limit table */
void func_L16_00418218(char *table) {
    f32 first = D_L16_001B1C28;
    f32 second = D_L16_001B1C2C;
    f32 third = D_L16_001B1C30;
    f32 fourth = D_L16_001B1C34;

    *(long long *)(table + 112) = 0LL;
    *(int *)(table + 80) = 0;
    *(int *)(table + 84) = 0;
    *(float *)(table + 88) = 1.0f;
    *(int *)(table + 92) = 0;
    *(int *)(table + 96) = 0;
    *(float *)(table + 100) = 1.0f;
    *(float *)(table + 104) = 1.0f;
    *(float *)(table + 108) = 1.0f;
    *(float *)(table + 8) = first;
    *(float *)(table + 24) = second;
    *(long long *)(table + 128) = 0x0000FF9000000260LL;
    *(float *)(table + 40) = first;
    *(float *)(table + 4) = third;
    *(float *)(table + 36) = fourth;
    *(int *)(table + 0) = 0;
    *(int *)(table + 16) = 0;
    *(int *)(table + 32) = 0;
    *(int *)(table + 48) = 0;
    *(float *)(table + 12) = 1.0f;
    *(float *)(table + 28) = 1.0f;
    *(float *)(table + 44) = 1.0f;
    *(float *)(table + 56) = second;
    *(float *)(table + 20) = third;
    *(float *)(table + 52) = fourth;
    *(float *)(table + 60) = 1.0f;
}

/* The id-list walk below reads D_L16_001B2B1C as a bare symbol (a second name for the 4-byte
   `sda` pointer above, declared as a 12-byte array so the assembler keeps its loads absolute),
   while D_L16_001B2B38 is a plain int: its `.extern` comes last in the file, which leaves a load
   in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern unsigned char *D_L16_001B2B1C_base[3] __asm__("D_L16_001B2B1C") __attribute__((sda));
extern s32 D_L16_001B2B38;
extern unsigned short *D_L16_001FB660[];
extern s32 D_L16_001B1FE0 __attribute__((sda));
extern void func_00283098(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CF0(char *, char *, char *);
extern void func_002AFDD8(char *, char *, char *, s32);
extern void func_002833F0(char *, char *);

/* Builds a transform in buf0 from the object's +0xC0 and +0x10 blocks, then, for every entity of
   the object's group (byte 0x21): derives buf1 from buf0 and the entity's position, has
   func_002AFDD8 fill buf2, stores the argument at +0xF4 (negated for class 0x125D) and rewrites
   the entity's +0x10 block from its +0xC0 frame and the two buffers. */
void func_L16_0041ECF8(char *self, f32 spin) {
    char buf0[0x10];
    char buf1[0x10];
    char buf2[0x10];
    char buf3[0x10];
    unsigned short *idList;
    char *entity;
    f32 spinValue;

    matrix_mul_vec3(buf0, (char *)&D_L16_001B1FE0, self + 0xC0);
    FastVecAdd(buf0, buf0, self + 0x10);
    for (idList = D_L16_001FB660[*(u8 *)(self + 0x21)];
         *(u8 *)(self + 0x21) != 0xFF && *(u8 *)(self + 0x21) <= D_L16_001B2B38 && idList != 0 &&
         ((idList != 0 && (short)idList[-1] >= 0) || idList == D_L16_001FB660[*(u8 *)(self + 0x21)]);
         idList++) {
        entity = (char *)D_L16_001B2B1C_base[0] + ((*idList & 0x7FFF) << 8);
        if (entity == 0)
            break;
        FastVecSub(buf1, buf0, entity + 0x10);
        TransformVectorByObjectOrGiven(entity, buf2, buf1, 0);
        spinValue = spin;
        if (*(short *)(entity + 0xAA) == 0x125D)
            spinValue = -spinValue;
        *(f32 *)(entity + 0xF4) = spinValue;
        euler_rotation_basis(entity + 0xC0, entity + 0xF0);
        matrix_mul_vec3(buf2, buf2, entity + 0xC0);
        FastVecSub(buf3, buf2, buf1);
        FastVecSub(entity + 0x10, entity + 0x10, buf3);
    }
}

extern s32 D_001A7A00;
extern void func_002E7788(char *, char *, f32);
extern char D_00189E20[];
extern void func_00315728(char *, char *, s32, char *, f32);
extern void func_00315948(char *, char *);

/* next frame: arms the object once the shared render state names it, then hands its box to the collision pass */
void func_L16_0041C6A0(char *moby) {
    char buf[0x30];
    char extent[0x10];
    char *hero;
    char *lockedTarget;

    if (*(u8 *)(moby + 0x20) == 0) {
        *(u8 *)(moby + 0x20) = 1;
        *(u8 *)(moby + 0x31) = 0;
        *(u16 *)(moby + 0x34) |= 1;
    }
    if (*(u8 *)(moby + 0x20) != 1)
        return;
    hero = gHeroState;
    lockedTarget = *(char **)(hero + 0x33C);
    if (lockedTarget == 0 || lockedTarget != moby)
        return;
    if (*(s32 *)(hero + 0x340) == 0)
        return;
    *(s32 *)(extent + 0) = 0;
    *(f32 *)(extent + 4) = 1.0f;
    *(s32 *)(extent + 8) = 0;
    *(f32 *)(extent + 0xC) = 1.0f;
    func_002E7788(extent, extent, 10.0f);
    func_00315728(buf, moby, 1, extent, (f32)(D_001A7A00 * 200));
    *(u16 *)(buf + 0x1A) = *(u16 *)(moby + 0xAA);
    func_00315948(*(char **)(hero + 0x2290), buf);
}
