#include "common.h"

typedef int Vec128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x46];
    short kind;
} Type2318;
typedef struct {
    char pad0[0x10];
    float pos[4];
    unsigned char state;
    char pad1[3];
    Type2318 *type;
    char pad2[0x34 - 0x28];
    unsigned short flags;
    char pad3[0x78 - 0x36];
    int colour;
    char pad4[0xc0 - 0x7c];
    float mat[16];
} Obj2318;

extern unsigned char D_001A7B00[] __attribute__((sda));
extern int func_00282948(void *);
extern Obj2318 *D_L00_001FACE0[];
extern int func_002AB1F0(void *);
extern float func_00282E20(void *);
typedef struct {
    char pad[9];
    unsigned char index;
} ItemSelector2318;
extern ItemSelector2318 D_00139568;
extern unsigned char D_00139571;
typedef struct {
    char pad0[4];
    unsigned char flag;
    char pad1[0x58 - 5];
    int count;
    char pad2[224 - 0x5c];
} Record2318;
extern Record2318 D_L00_00262570[];
extern void func_L00_0040B838(void *, int, void *, int);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
typedef struct {
    char pad[0x64];
    unsigned char *owner;
} Owner2318;
extern Owner2318 D_L00_001FE940;
extern char D_L00_001A8F20[] MACRO_ADDR;
extern char *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);

extern int func_L00_002ADEA0(int);
extern void func_00282CF0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, int, int);
typedef struct {
    char pad0[0x80]; float position[4];
    char pad1[0x98-0x90]; float heading;
    char pad2[0x1314-0x9c]; Obj2318 *weapon;
    char pad3[0x18d0-0x1318]; Obj2318 *target; int active, timer;
    char pad4[0x2010-0x18dc]; float point[4] __attribute__((aligned(16)));
    char pad5[0x2290-0x2020]; int owner;
    char pad6[0x22b4-0x2294]; unsigned char mode;
    char pad7[0x24fc-0x22b5]; short blocked;
} Hero2318;
extern Hero2318 D_00189E20;

/* Lets the hero lock onto a close enemy and fire the current weapon at it, with a burst of sparks. Counts down the weapon ammo and reloads when empty. */
void func_L00_002B2318(void) {
    float scratchVec[4] __attribute__((aligned(16)));
    float sparkA[4] __attribute__((aligned(16)));
    float sparkB[4] __attribute__((aligned(16)));
    float offsetA[4] __attribute__((aligned(16)));
    float offsetB[4] __attribute__((aligned(16)));
    float angle;
    int i;
    int j;
    int objectIndex;
    char *effect;
    Record2318 *record;

    if (gHeroState.active && !gHeroState.mode && (D_001A7B00[1] || D_001A7B00[0x41])) {
        if ((hero_slot_item_id(3) == 3 || hero_slot_item_id(3) == 2) && !gHeroState.blocked) {
            if (FastFloatHelperD(&gHeroState.timer)) {
                Obj2318 *object;
                for (objectIndex = 0; (object = D_L00_001FACE0[objectIndex]) != 0; objectIndex++) {
                    if (object->type && object->type->kind == 5 && object && object->state != 254 && object->state != 253 && GetMobyPrivateValue0(object)) {
                        FastVecSub(scratchVec, object->pos, gHeroState.position);
                        if (!(16.0f < vec_length_xy(scratchVec))) gHeroState.target = object;
                    }
                }
                if (gHeroState.target && gHeroState.target->type->kind == 5 && gHeroState.target->state != 254 && gHeroState.target->state != 253
                    && CollLine(gHeroState.point, gHeroState.target->pos, 0, gHeroState.owner, 0)) {
                    FastVecSub(scratchVec, gHeroState.target->pos, gHeroState.position);
                    if (vec_length_xy(scratchVec) < 16.0f) {
                        record = &gWeaponTable_L00[gItemSlotToRecord.index];
                        if (record->count > 0) {
                            if (record->flag) SpawnClankZapperMoby(gHeroState.point, gHeroState.owner, gHeroState.target, 1);
                            else SpawnClankZapperMoby(gHeroState.point, gHeroState.owner, gHeroState.target, 0);
                            { Record2318 *slotRecord = &gWeaponTable_L00[gItemSlotToRecord.index];
                            gHeroState.timer = 120;
                            slotRecord->count--; }
                        } else {
                            gHeroState.active = 0;
                            gWeaponTable_L00[gItemSlotToRecord.index].count = 30;
                        }
                    }
                }
            } else {
                angle = FastDiffRots(FastMatrixHelperA(gHeroState.target->pos[0] - gHeroState.position[0], gHeroState.target->pos[1] - gHeroState.position[1]), gHeroState.heading);
                if (angle > 1.3962636f && gWeaponTable_L00[gItemSlotToRecord.index].flag) {
                    Obj2318 *weapon = gHeroState.weapon;
                    weapon->colour = 0x800000ff;
                    weapon->flags |= 0x10;
                    qcopy(scratchVec, gHeroState.point);
                    TransformMobyJointToWorld(weapon, 6, sparkA);
                    TransformMobyJointToWorld(weapon, 7, sparkB);
                    *(Vec128 *)offsetA = 0;
                    *(Vec128 *)offsetB = 0;
                    offsetA[0] = -0.025f; offsetA[1] = 0.01f; offsetA[2] = 0.04f;
                    offsetB[0] = -0.025f; offsetB[1] = -0.01f; offsetB[2] = 0.04f;
                    matrix_mul_vec3(offsetA, offsetA, weapon->mat);
                    FastVecAdd(sparkA, sparkA, offsetA);
                    matrix_mul_vec3(offsetB, offsetB, weapon->mat);
                    FastVecAdd(sparkB, sparkB, offsetB);
                    for (i = 0; i < 30; i++) {
                        sparkA[0] += RandomSignedFloatRange(0.0f, 0.004f);
                        sparkA[1] += RandomSignedFloatRange(0.0f, 0.004f);
                        sparkA[2] += RandomSignedFloatRange(0.0f, 0.004f);
                        sparkB[0] += RandomSignedFloatRange(0.0f, 0.004f);
                        sparkB[1] += RandomSignedFloatRange(0.0f, 0.004f);
                        sparkB[2] += RandomSignedFloatRange(0.0f, 0.004f);
                        effect = SpawnBurstParticle_002C16C0(sparkA, D_L00_001A8F20, 2, 127, 0x2020ff, FloatToInt(RandomSignedFloatRange(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *D_L00_001FE940.owner;
                        effect = SpawnBurstParticle_002C16C0(sparkB, D_L00_001A8F20, 2, 127, 0x2020ff, FloatToInt(RandomSignedFloatRange(1.0f, -1.0f)), 25200.0f, 500.0f, 1.0f, 0.0f, 0.0f);
                        if (effect) effect[2] = *D_L00_001FE940.owner;
                    }
                }
                qcopy(scratchVec, gHeroState.point);
                if (angle < 1.3962636f) {
                    for (j = 0; j < 20; j++) {
                        sparkA[0] = scratchVec[0] + RandomSignedFloatRange(0.0f, 0.04f);
                        sparkA[1] = scratchVec[1] + RandomSignedFloatRange(0.0f, 0.04f);
                        sparkA[2] = scratchVec[2] + RandomSignedFloatRange(0.0f, 0.04f);
                        record = &gWeaponTable_L00[gItemSlotToRecord.index];
                        /* Identical arms: retail still reads this flag into $v0 and the next call clobbers it, the
                           dead load jump2's cross-jump leaves. One arm is 36 bytes short of retail. */
                        if (record->flag) {
                            effect = SpawnBurstParticle_002C16C0(sparkA, D_L00_001A8F20, 2, 127, 0x20ff20, FloatToInt(RandomSignedFloatRange(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *D_L00_001FE940.owner;
                        } else {
                            effect = SpawnBurstParticle_002C16C0(sparkA, D_L00_001A8F20, 2, 127, 0x20ff20, FloatToInt(RandomSignedFloatRange(1.0f, -1.0f)), 31500.002f, 500.0f, 1.0f, 0.0f, 0.0f);
                            if (effect) effect[2] = *D_L00_001FE940.owner;
                        }
                    }
                }
            }
        }
    }
}
