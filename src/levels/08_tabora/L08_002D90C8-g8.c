#include "common.h"

extern char *D_L08_001B29DC __attribute__((sda));

typedef int TI128 __attribute__((mode(TI)));

/* Tuning words read by func_L08_003D3EF8. */
extern float D_L08_001B0338 __attribute__((sda));
extern float D_L08_001B033C __attribute__((sda));
extern float D_L08_001B0340 __attribute__((sda));
extern float D_L08_001B0344 __attribute__((sda));
extern unsigned char D_L08_001B0348 __attribute__((sda));
extern int D_L08_001B034C __attribute__((sda));
extern int D_L08_001B0350 __attribute__((sda));
extern float D_L08_001B0354 __attribute__((sda));
extern float D_L08_001B0358 __attribute__((sda));
extern int D_L08_001B035C __attribute__((sda));
extern int D_L08_001B0360 __attribute__((sda));
extern int D_L08_001B0368 __attribute__((sda));
extern int D_L08_001B036C __attribute__((sda));
/* The frame counter: absolute loads, $gp in a delay slot. */
extern int D_L08_001B2508 MACRO_ADDR;
extern char D_L08_001B9B00[];

extern void func_0029FCC0(void *, int, void *);
extern int func_002A77E0(int);
extern void func_002A7A00(void *, float, float);
extern void func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);
extern unsigned char *func_002C2FD8(void *, int, unsigned char, int, int, int, int, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);

/* Returns the height of the object with the given index, or 0 when there is none. */
float func_L08_003CCD58(int mobyIndex) {
    if (mobyIndex != -1)
        return *(float *)(D_L08_001B29DC + ((unsigned int)mobyIndex << 8) + 0x18);
    return 0.0f;
}

/* Tells whether the linked object is switched on. */
int func_L08_003CCD28(int mobyIndex) {
    if (mobyIndex != -1) {
        if (*(unsigned char *)(*(unsigned char **)(D_L08_001B29DC
                                                  + ((unsigned int)mobyIndex << 8) + 0x68)
                              + 0x14) != 0)
            return 1;
    }
    return 0;
}

/* The parameter block of the shared spawn routines (func_L04_003A1A78 and its siblings). */
typedef struct {
    int kind;
    int count;
    void *table0;
    void *table1;
    void *small0;
    void *counts;
    void *table2;
    void *table3;
    void *small1;
    void *small2;
    void *owner;
    void *callback;
    void *callback2;
} L08SpawnBlock;

extern char D_00189E20[];
extern char D_L08_002A0D00[];
extern char D_L08_0023EC80[];
extern char D_L08_0023ECF0[];
extern char D_L08_002A87F0[];
extern int D_L08_001B01B8[2] __attribute__((sda));
/* Kind 7 consumes seven halfwords; the full owner extent remains unknown. */
extern u16 D_L08_001B01C8[] SDATA(D_L08_001B01C8);
extern int D_L08_001B01D8 __attribute__((sda));
extern int D_L08_001B01DC __attribute__((sda));
extern void func_L08_003CFFE8(void);
extern void func_L00_002E6CF0(void);
extern void func_L04_003A1A78(L08SpawnBlock *);
extern void func_L04_003A5C08(void *, float);
extern void func_L04_003A1C98(L08SpawnBlock *);
extern void func_L04_003A1FA0(L08SpawnBlock *);
extern void func_L04_003A1FE0(L08SpawnBlock *);

/* Runs the shared spawn routines for the object, unless the level's player (the entity at
   D_00189E20+0x1830, kind 0x45) is alive while the mode word at +0x2294 is 0x31. The count
   is the state's +0x10 plus an entry of D_L08_001B01B8 picked by +0x18 (1 when -1); state
   0 sets the object up first and then shares state 1's step, state 2 has its own. */
/* Water object: runs the shared spawn routines that make the water splash and ripple effects. */
void func_L08_003CFE68(char *owner)
{
    L08SpawnBlock spawnBlock;
    char *world = gHeroState;
    char *hero = *(char **)(world + 0x1830);
    char *vars;
    int spawnCount;

    if (hero != 0 && *(short *)(hero + 0xAA) == 0x45 &&
        *(unsigned char *)(hero + 0x20) != 0xFE && *(unsigned char *)(hero + 0x20) != 0xFD &&
        *(int *)(world + 0x2294) == 0x31)
        return;
    vars = *(char **)(owner + 0x68);
    if (vars == 0)
        return;
    spawnCount = 1;
    if (*(int *)(vars + 0x18) != -1)
        spawnCount = D_L08_001B01B8[*(int *)(vars + 0x18)];
    spawnCount += *(int *)(vars + 0x10);
    spawnBlock.kind = 7;
    spawnBlock.count = spawnCount;
    spawnBlock.small1 = &D_L08_001B01D8;
    spawnBlock.small2 = &D_L08_001B01DC;
    spawnBlock.table0 = D_L08_002A0D00;
    spawnBlock.table1 = D_L08_0023EC80;
    spawnBlock.small0 = D_L08_001B01C8;
    spawnBlock.counts = D_L08_001B01B8;
    spawnBlock.table2 = D_L08_0023ECF0;
    spawnBlock.table3 = D_L08_002A87F0;
    spawnBlock.owner = owner;
    spawnBlock.callback = StartSharedWaterEffect;
    spawnBlock.callback2 = AddDrawCallbackToList1;
    switch (*(unsigned char *)(owner + 0x20)) {
    case 0:
        InitWaterObject(&spawnBlock);
        AddWaterSplashEntry(owner, *(float *)(vars + 0x28));
    case 1:
        UpdateWaterController(&spawnBlock);
        break;
    case 2:
        AdvanceWaterControllerState(&spawnBlock);
        break;
    }
    UpdateWaterRipplePatches_L04(&spawnBlock);
}

/* Tells whether the linked object is switched on. */
int func_L08_003D0098(int mobyIndex) {
    if (mobyIndex != -1) {
        if (*(unsigned char *)(*(unsigned char **)(D_L08_001B29DC
                                                  + ((unsigned int)mobyIndex << 8) + 0x68)
                              + 0x14) != 0)
            return 1;
    }
    return 0;
}

/* After a one-in-four roll, spawns four particles from joint 0 whose velocity grows by a
   random step each time; then draws four rings between the moby and the point at
   D_L08_001B9B00, laid out as RAC1's update_gold_bolt_glow_rings lays out its rings: each
   ring's colour follows the frame counter, and its byte argument (the ring angle in RAC1)
   is the counter's low byte, doubled and/or inverted by the ring index. */
/* Spawns sparks and draws four glowing rings around the object that pulse with the frame counter. */
void func_L08_003D3EF8(char *moby)
{
    TI128 jointPos, sparkVelocity, velocityStep, ringPos, ringStep;
    int sparkIndex;
    int ringIndex;
    int angleByte;
    float phase;
    float reciprocal, half, size;
    int ringColor;

    TransformMobyJointToWorld(moby, 0, &jointPos);
    if (RandomIntBelow(4) == 0) {
        RandomDirectionVector(&sparkVelocity, D_L08_001B0338 * 0.016666668f, D_L08_001B033C * 0.016666668f);
        angleByte = D_L08_001B0348;
        SpawnHeroRelativeParticle(&jointPos, &sparkVelocity, D_L08_001B034C, angleByte, RandomIntBelow(255), 0, D_L08_001B0354);
        for (sparkIndex = 2; sparkIndex >= 0; sparkIndex--) {
            RandomDirectionVector(&velocityStep, D_L08_001B0340 * 0.016666668f, D_L08_001B0344 * 0.016666668f);
            FastVecAdd(&sparkVelocity, &sparkVelocity, &velocityStep);
            angleByte = D_L08_001B0348;
            SpawnHeroRelativeParticle(&jointPos, &sparkVelocity, D_L08_001B0350, angleByte, RandomIntBelow(255), 0, D_L08_001B0358);
        }
    }
    FastVecSub(&ringPos, D_L08_001B9B00, &jointPos);
    vec_scale_to_length(&ringPos, &ringPos, -0.3f);
    vec_scale_to_length(&ringStep, &ringPos, 0.1f);
    FastVecAdd(&ringPos, &ringPos, &jointPos);
    reciprocal = 0.003921569f;
    half = 0.5f;
    size = 3.0f;
    for (ringIndex = 0; ringIndex < 4; ringIndex++) {
        phase = IntToFloat(0xFF - ((D_L08_001B2508 + ringIndex * 20) & 0xFF));
        ringColor = FastTweenColor(D_L08_001B035C, D_L08_001B0360, FloatAbs(half - phase * reciprocal));
        angleByte = D_L08_001B2508 & 0xFF;
        if (ringIndex & 2)
            angleByte = angleByte * 2;
        if (ringIndex & 1)
            angleByte = 0xFF - angleByte;
        SpawnFadingParticle_002C2FD8(&ringPos, ringColor, angleByte, D_L08_001B036C, D_L08_001B0368, 2, 0,
                      (IntToFloat(ringIndex) + size)
                          * (*(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24)));
        FastVecAdd(&ringPos, &ringPos, &ringStep);
    }
}
