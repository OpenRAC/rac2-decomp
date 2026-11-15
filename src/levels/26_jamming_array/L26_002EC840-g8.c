#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;

extern u8 *D_L26_001B1C1C __attribute__((sda));

extern u16 *D_L26_001FA6E0[];

/* The walk below reads the group count and one word through $gp; the group table of id lists is
   absolute, and the entity base (D_L26_001B1C1C above, through $gp) is the bare `lui`/`lw` pair
   here, a second name sized over 8 bytes with `sda` in this -G8 unit. */
extern int D_L26_001B1C38 __attribute__((sda));

extern u8 *D_L26_001B1C1C_1[3] __attribute__((sda));

extern char D_L26_002967A0[];

extern int D_L26_001B0478 __attribute__((sda));

extern int D_L26_001B047C;

extern void func_00281A08(void *, int, void *, void *, int, int, int, int, float);

/* For every entity of the object's group, hands six slots of its private state (+0x80 and +0x100,
   the words at +0x190 and +0x194 and the float at +0x198) to the resident effect scheduler,
   together with the level's float template D_L26_002967A0 and the two words D_L26_001B0478 and
   D_L26_001B047C. */
void func_L26_003D4AE8(u8 *object) {
    u16 *groupIds;
    u8 *entity;
    u8 *state;

    for (groupIds = D_L26_001FA6E0[object[0x21]];
         object[0x21] != 0xFF && object[0x21] <= D_L26_001B1C38 && groupIds != 0 &&
         ((groupIds != 0 && (short)groupIds[-1] >= 0) || groupIds == D_L26_001FA6E0[object[0x21]]);
         groupIds++) {
        entity = D_L26_001B1C1C_1[0] + ((*groupIds & 0x7FFF) << 8);
        if (entity == 0)
            break;
        state = *(u8 **)(entity + 0x68);
        DrawTrailRibbon_00281A08(D_L26_002967A0, 6, state + 0x80, state + 0x100, *(int *)(state + 0x194),
                      *(int *)(state + 0x190), D_L26_001B0478, D_L26_001B047C, *(float *)(state + 0x198));
    }
}

/* Walks the record's live list and flags every entry whose id matches. */
/* func_L26_003DC128 is defined in L02_003CE9A8-g8.c. */

/* func_L26_003DBE18: while object[0x20] is 0 it seeds the private state (constants, the
   func_002B0360 sample of the position minus 1.5, and D_L26_001B05D8 degrees as radians with a
   random sign); then, when func_00282E48(position, D_L26_001B8B80) is below 24, it calls
   func_002A93B0 and sets object[0x6F] to 0x16, runs its per-frame helpers and returns 1 once the
   private byte +0x2E is 2. */
extern float D_L26_001B05D8 __attribute__((sda));
extern unsigned short D_L26_001B05E0 __attribute__((sda));
extern unsigned short D_L26_001B05E4;
extern float D_L26_001B8B80[4];
extern float func_002B0360(char *);
extern int func_002A77E0(int);
extern void func_00325B70(char *, char **, int, int);
extern void func_002A7750(unsigned char *, unsigned char, int);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L26_003DC128(void *);
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern void func_00283698(void *, void *);
extern void func_002AFFD8(char *, char *, int);
extern void func_00325D30(char *, char *);

/* Sets up a flying creature on its first frame. Each frame after that it reacts to the hero being
   close, updates its movement and returns 1 once it is finished and should be removed. */
int func_L26_003DBE18(unsigned char *object) {
    char *private = *(char **)(object + 0x68);
    float height;
    float turn;
    if (object[0x20] == 0) {
        *(int *)(private + 0x98) = 3;
        *(float *)(private + 0x80) = 1.0f;
        private[0x60] = 7;
        *(float *)(private + 0x84) = 0.8f;
        *(float *)(private + 0x8C) = 0.15f;
        height = GetDistanceFromGravityCenter((char *)object + 0x10) - 1.5f;
        turn = D_L26_001B05D8;
        *(float *)(private + 0x100) = 1.0f;
        turn *= 0.017453294f;
        *(float *)(private + 0x90) = height;
        *(float *)(private + 0x104) = 0.5f;
        {
            int flip = RandomIntBelow(2);
            float angle = turn;
            if (flip) angle = -angle;
            *(float *)(private + 0x1DC) = angle;
        }
        *(unsigned short *)(private + 0x1E2) = D_L26_001B05E0;
        *(unsigned short *)(private + 0x1E4) = D_L26_001B05E4;
        private[0x2E] = 1;
        *(unsigned short *)(object + 0x34) |= 0x100;
        if (*(float *)(private + 0x20) == 0.0f) {
            *(short *)(private + 0x24) = 3;
            *(float *)(private + 0x20) = 3.0f;
        }
        SpawnEnemyChildParts((char *)object, (char **)(private + 0x270), 0, 2);
        SetMobyState(object, 1, 0);
        if (object[0x43]) StartAnimationBlended(object, 0, 0, 0);
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, D_L26_001B8B80) < 24.0f) {
        UpdateMobyGroundCheck(object);
        object[0x6F] = 0x16;
    }
    if (ApplyDamageToObject(object, private + 0x50, 0)) SetGroupMobyAlertFlagL26(object);
    *(short *)(private + 0x224) = SelectAimTarget_002B3BA8(object, *(int *)(private + 0x210), 0, 0, 16.0f, 0.0f);
    matrix_from_basis_rows(private + 0x230, object + 0xC0);
    ComputeViewDirection((char *)object + 0x10, private + 0x260, 0);
    if ((unsigned char)private[0x2E] == 2) {
        DestroyAttachedParts((char *)object, private + 0x270);
        return 1;
    }
    return 0;
}
