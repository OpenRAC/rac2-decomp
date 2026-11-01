/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/*
 * Tier: opus-1 (Claude Opus 5.5), task v1066, USA v1.01, default game profile:
 * -O2 -G0 -ffunction-sections (own unit; the switches compile to branches, no .rodata).
 * Best check.py: 932/932 bytes, 0 of 1 places; 5 instructions differ, all in the post-spawn
 * trigger block (+0x234..+0x248): retail puts the entity base in a0 and the timer value in v0,
 * ours swaps them (lui/lw base, lw timer, addu, sw timer).
 * Closer than the sol-high draft: array indexing (state->first[i], state->second[i]) now gives
 * retail's two strength-reduced cursors and preheader order; the sda scalar declaration of
 * D_L01_001B264C gives the tied lui/lw $a1 form; reading the entity base into a local before the
 * timer store and indexing it in the store gives retail's addu operand order and 0xBC offset.
 * Remaining: in sched1's order the base and timer quantities tie in local-alloc (2 refs, equal
 * life), so the earlier-born base takes v0. Retail needs the timer allocated first (born
 * first, or its store before the addu in sched1). Four statement orders of the block (index,
 * base, timer, store) give the same bytes: a tie. Reopen with a new allocation hypothesis.
 * All declarations needed to compile this unit follow.
 */
#include "common.h"


typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float value[4]; } LaunchVector;
typedef struct {
    float f0, f4, f8, f12, f16, f20;
    unsigned char f24, f25; short f26;
    unsigned char f28, f29, f30, f31;
    unsigned char pad32[16];
    short f48, f50; int f52, f56, f60;
} PoolRecord64;
extern void func_0026FEB8(const char *, ...);
extern void func_002A7750(unsigned char *, int, int);
extern void func_002A8598(int, int);
extern int func_002ACBC8(void *, int);
extern int func_00282948(int *);
extern PoolRecord64 *func_L00_002D70A0(int);
extern void func_L00_002D7140(unsigned char *);
extern unsigned char *func_L01_003D25B8(unsigned char *, LaunchVector *, LaunchVector *, int, int);
extern unsigned char *D_L01_001B255C __attribute__((sda));
extern unsigned char *D_L01_001B264C __attribute__((sda));
extern char D_L01_001B0548[], D_L01_001B0580[];
extern int D_L01_00297BF0[];
extern unsigned char D_00189EA0[];
typedef struct { int delay, startId, endId, unused; int first[2], second[2]; int p20, p24, timer, duration; short selection, mode; PoolRecord64 *pool; int event, command; } LaunchState;
#define FIELD(o) (*(int *)(data + (o)))
#define HALF(o) (*(short *)(data + (o)))
#define POOL (*(PoolRecord64 **)(data + 0x34))
void func_L01_003D2890(unsigned char *self)
{
    LaunchState *state = *(LaunchState **)(self + 0x68);
    unsigned char *data = (unsigned char *)state;
    LaunchVector point, target;
    int i, command;
    int *firstIDs, *secondIDs;
    switch (self[0x20]) {
    case 0:
        POOL = 0;
        for (i = 0; i < 2; i++) {
            if (state->first[i] == -1) {
                func_0026FEB8(D_L01_001B0548, *(short *)(self + 0xaa), *(short *)(self + 0xb2), i);
                func_002A7750(self, 4, -1);
            }
            if (state->second[i] == -1) {
                func_0026FEB8(D_L01_001B0580, *(short *)(self + 0xaa), *(short *)(self + 0xb2), i);
                func_002A7750(self, 4, -1);
            }
        }
        if (self[0x20] == 0) func_002A7750(self, 1, -1);
        break;
    case 1:
        if (self[0xbc]) {
            D_L01_001B255C[FIELD(4) * 256 + 0xbc] = 1;
            FIELD(0x28) = 0;
            self[0xbc] = 0;
            FIELD(0x3c) = 0;
            FIELD(0x2c) = FIELD(0x24);
            func_002A7750(self, 2, -1);
        }
        break;
    case 2:
        if (func_00282948((int *)(data + 0x28))) {
            command = D_L01_00297BF0[FIELD(0x3c)];
            switch (command) {
            case 0: HALF(0x30) = 0; HALF(0x32) = 0; break;
            case 1: HALF(0x30) = 1; HALF(0x32) = 1; break;
            case 2: HALF(0x32) = 1; HALF(0x30) = 0; break;
            }
            { unsigned char *base = D_L01_001B264C;
            int index;
            int selection=HALF(0x30);
            FIELD(0x3c)++;
            index = state->second[selection];
            qcopy_nc(&point, base + index * 128 + 0x30);
            qcopy_nc(&target, base + index * 128 + 0x70);
            func_L01_003D25B8(self, &point, &target, HALF(0x32) + 0xa9e, HALF(0x30)); }
            { int triggerIndex = FIELD(8);
            unsigned char *entities = D_L01_001B255C;
            int ticks = FIELD(0);
            FIELD(0x28) = ticks;
            entities[triggerIndex * 256 + 0xbc] = 1; }
        }
        if (FIELD(0x28) < FIELD(0) - 40)
            D_L01_001B255C[FIELD(8) * 256 + 0xbc] = 0;
        if (func_00282948((int *)(data + 0x2c))) func_002A7750(self, 3, -1);
        break;
    case 3:
        D_L01_001B255C[FIELD(4) * 256 + 0xbc] = 0;
        func_002A8598(self[0x21], 0);
        func_002A7750(self, 1, -1);
        break;
    }
    if (self[0x20] == 2 && FIELD(0x38) != -1 && func_002ACBC8(D_00189EA0, FIELD(0x38))) {
        if (POOL == 0) {
            POOL = func_L00_002D70A0(5);
            qzero((unsigned char *)POOL + 0x20);
            *(float *)((unsigned char *)POOL + 0x20) = -1.0f;
            POOL->f24 = 1;
            POOL->f4 = 6.0f;
            POOL->f26 = 1;
            POOL->f30 = 1;
        }
    } else if (POOL) {
        func_L00_002D7140((unsigned char *)POOL);
        POOL = 0;
    }
}
