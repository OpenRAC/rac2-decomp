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

float func_L08_003CCD58(int index) {
    if (index != -1)
        return *(float *)(D_L08_001B29DC + ((unsigned int)index << 8) + 0x18);
    return 0.0f;
}

int func_L08_003CCD28(int index) {
    if (index != -1) {
        if (*(unsigned char *)(*(unsigned char **)(D_L08_001B29DC
                                                  + ((unsigned int)index << 8) + 0x68)
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
void func_L08_003CFE68(char *object)
{
    L08SpawnBlock block;
    char *level = D_00189E20;
    char *player = *(char **)(level + 0x1830);
    char *state;
    int count;

    if (player != 0 && *(short *)(player + 0xAA) == 0x45 &&
        *(unsigned char *)(player + 0x20) != 0xFE && *(unsigned char *)(player + 0x20) != 0xFD &&
        *(int *)(level + 0x2294) == 0x31)
        return;
    state = *(char **)(object + 0x68);
    if (state == 0)
        return;
    count = 1;
    if (*(int *)(state + 0x18) != -1)
        count = D_L08_001B01B8[*(int *)(state + 0x18)];
    count += *(int *)(state + 0x10);
    block.kind = 7;
    block.count = count;
    block.small1 = &D_L08_001B01D8;
    block.small2 = &D_L08_001B01DC;
    block.table0 = D_L08_002A0D00;
    block.table1 = D_L08_0023EC80;
    block.small0 = D_L08_001B01C8;
    block.counts = D_L08_001B01B8;
    block.table2 = D_L08_0023ECF0;
    block.table3 = D_L08_002A87F0;
    block.owner = object;
    block.callback = func_L08_003CFFE8;
    block.callback2 = func_L00_002E6CF0;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        func_L04_003A1A78(&block);
        func_L04_003A5C08(object, *(float *)(state + 0x28));
    case 1:
        func_L04_003A1C98(&block);
        break;
    case 2:
        func_L04_003A1FA0(&block);
        break;
    }
    func_L04_003A1FE0(&block);
}

int func_L08_003D0098(int index) {
    if (index != -1) {
        if (*(unsigned char *)(*(unsigned char **)(D_L08_001B29DC
                                                  + ((unsigned int)index << 8) + 0x68)
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
void func_L08_003D3EF8(char *obj)
{
    TI128 joint, velocity, step, ring, ring_step;
    int count;
    int k;
    int b;
    float t;
    float reciprocal, half, size;
    int color;

    func_0029FCC0(obj, 0, &joint);
    if (func_002A77E0(4) == 0) {
        func_002A7A00(&velocity, D_L08_001B0338 * 0.016666668f, D_L08_001B033C * 0.016666668f);
        b = D_L08_001B0348;
        func_002C3150(&joint, &velocity, D_L08_001B034C, b, func_002A77E0(255), 0, D_L08_001B0354);
        for (count = 2; count >= 0; count--) {
            func_002A7A00(&step, D_L08_001B0340 * 0.016666668f, D_L08_001B0344 * 0.016666668f);
            FastVecAdd(&velocity, &velocity, &step);
            b = D_L08_001B0348;
            func_002C3150(&joint, &velocity, D_L08_001B0350, b, func_002A77E0(255), 0, D_L08_001B0358);
        }
    }
    FastVecSub(&ring, D_L08_001B9B00, &joint);
    vec_scale_to_length(&ring, &ring, -0.3f);
    vec_scale_to_length(&ring_step, &ring, 0.1f);
    FastVecAdd(&ring, &ring, &joint);
    reciprocal = 0.003921569f;
    half = 0.5f;
    size = 3.0f;
    for (k = 0; k < 4; k++) {
        t = IntToFloat(0xFF - ((D_L08_001B2508 + k * 20) & 0xFF));
        color = FastTweenColor(D_L08_001B035C, D_L08_001B0360, func_00282C48(half - t * reciprocal));
        b = D_L08_001B2508 & 0xFF;
        if (k & 2)
            b = b * 2;
        if (k & 1)
            b = 0xFF - b;
        func_002C2FD8(&ring, color, b, D_L08_001B036C, D_L08_001B0368, 2, 0,
                      (IntToFloat(k) + size)
                          * (*(float *)(obj + 0x2C) / *(float *)(*(char **)(obj + 0x24) + 0x24)));
        FastVecAdd(&ring, &ring, &ring_step);
    }
}
