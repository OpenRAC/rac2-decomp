#include "include_asm.h"
#include "common.h"

/* func_PAL_L01_003D6A78, the PAL copy of func_L01_003D2890: the same C, with the launcher timers scaled to 50 Hz. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float value[4]; } LaunchVector;
typedef struct {
    float f0, f4, f8, f12, f16, f20;
    unsigned char f24, f25; short f26;
    unsigned char f28, f29, f30, f31;
    unsigned char pad32[16];
    short f48, f50; int f52, f56, f60;
} PoolRecord64;
extern void STUB_printf(const char *, ...);
extern void moby_set_state(unsigned char *, int, int);
extern void moby_set_byte_on_group(int, int);
extern int IsPointInCuboid(void *, int);
extern int math_fast_float_d(int *);
extern PoolRecord64 *cam_alloc_override_slot(int);
extern void cam_end_override(unsigned char *);
extern unsigned char *moby_l01_spawn_child(unsigned char *, LaunchVector *, LaunchVector *, int, int);
extern unsigned char *g_moby_l01_table __attribute__((sda));
extern unsigned char *D_L01_001B264C __attribute__((sda));
extern char D_L01_001B0548[], D_L01_001B0580[];
extern int D_L01_00297BF0[];
extern unsigned char g_hero_position[];
typedef struct { int delay, startId, endId, unused; int first[2], second[2]; int p20, p24, timer, duration; short selection, mode; PoolRecord64 *pool; int event, command; } LaunchState;
#define FIELD(o) (*(int *)(data + (o)))
#define HALF(o) (*(short *)(data + (o)))
#define POOL (*(PoolRecord64 **)(data + 0x34))
void func_PAL_L01_003D6A78(unsigned char *self)
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
                STUB_printf(D_L01_001B0548, *(short *)(self + 0xaa), *(short *)(self + 0xb2), i);
                moby_set_state(self, 4, -1);
            }
            if (state->second[i] == -1) {
                STUB_printf(D_L01_001B0580, *(short *)(self + 0xaa), *(short *)(self + 0xb2), i);
                moby_set_state(self, 4, -1);
            }
        }
        if (self[0x20] == 0) moby_set_state(self, 1, -1);
        break;
    case 1:
        if (self[0xbc]) {
            g_moby_l01_table[FIELD(4) * 256 + 0xbc] = 1;
            FIELD(0x28) = 0;
            self[0xbc] = 0;
            FIELD(0x3c) = 0;
            FIELD(0x2c) = (FIELD(0x24) * 5 + 2) / 6;
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        if (math_fast_float_d((int *)(data + 0x28))) {
            command = D_L01_00297BF0[FIELD(0x3c)];
            switch (command) {
            case 0: HALF(0x30) = 0; HALF(0x32) = 0; break;
            case 1: HALF(0x30) = 1; HALF(0x32) = 1; break;
            case 2: HALF(0x32) = 1; HALF(0x30) = 0; break;
            }
            {
                unsigned char *base = D_L01_001B264C;
                int index;
                int selection = HALF(0x30);
                FIELD(0x3c)++;
                index = state->second[selection];
                qcopy_nc(&point, base + index * 128 + 0x30);
                qcopy_nc(&target, base + index * 128 + 0x70);
                moby_l01_spawn_child(self, &point, &target, HALF(0x32) + 0xa9e, HALF(0x30));
            }
            {
                int duration = (FIELD(0) * 5 + 2) / 6;
                int triggerIndex = FIELD(8);
                state->timer = duration;
                g_moby_l01_table[triggerIndex * 256 + 0xbc] = 1;
            }
        }
        if (FIELD(0x28) < (FIELD(0) * 5 + 2) / 6 - 33)
            g_moby_l01_table[FIELD(8) * 256 + 0xbc] = 0;
        if (math_fast_float_d((int *)(data + 0x2c))) moby_set_state(self, 3, -1);
        break;
    case 3:
        g_moby_l01_table[FIELD(4) * 256 + 0xbc] = 0;
        moby_set_byte_on_group(self[0x21], 0);
        moby_set_state(self, 1, -1);
        break;
    }
    if (self[0x20] == 2 && FIELD(0x38) != -1 && IsPointInCuboid(g_hero_position, FIELD(0x38))) {
        if (POOL == 0) {
            POOL = cam_alloc_override_slot(5);
            qzero((unsigned char *)POOL + 0x20);
            *(float *)((unsigned char *)POOL + 0x20) = -1.0f;
            POOL->f24 = 1;
            POOL->f4 = 6.0f;
            POOL->f26 = 1;
            POOL->f30 = 1;
        }
    } else if (POOL) {
        cam_end_override((unsigned char *)POOL);
        POOL = 0;
    }
}
