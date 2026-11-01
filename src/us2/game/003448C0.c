#include "include_asm.h"

extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);

char *func_US2_003448C0(char *p)
{
    F449e2f67_FUN_003361A8(p);
    F449e2f67_FUN_003361A8(p + 76);
    F449e2f67_FUN_003361A8(p + 152);
    F449e2f67_FUN_003361A8(p + 228);
    F449e2f67_FUN_003361A8(p + 304);
    F449e2f67_FUN_003361A8(p + 380);
    F449e2f67_FUN_00336968(p + 456);
    F449e2f67_FUN_00336968(p + 544);
    F449e2f67_FUN_003366D0(p + 632);
    F449e2f67_FUN_00336968(p + 696);
    F449e2f67_FUN_00336968(p + 784);
    F449e2f67_FUN_00336968(p + 872);
    F449e2f67_FUN_00336968(p + 960);
    F449e2f67_FUN_00336968(p + 1048);
    return p;
}


extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_003361E0(void *, void *, void *);
extern void func_US2_003377B0(void *, void *, void *);
extern int *func_00335E20(void *);
extern void func_00336A30(void *, int);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00336390(void *, void *, int);
extern void func_00336710(void *, void *, void *);
extern int func_00288FB8(int);
extern void func_00336A38(void *, int);
extern int func_US2_003453D0();
extern char D_001ADC10[], D_001ADC18[], D_001ADC20[], D_001ADC28[], D_001ADFC0[], D_001ADFC8[];
extern char D_001ADF10[], D_001ADF18[], D_001ADF20[], D_001ADD60[], D_001AE250[];
extern char D_001ADD58[], D_001AE030[], D_001ADFD8[];
extern char *D_001A8CFC[] __attribute__((sda));

void func_US2_00344950(char *self, void *arg)
{
    int *buf;
    float zero;

    *(void **)(self + 0x4A4) = arg;
    if (arg) {
        buf = func_00336DA8(16, func_00336E40(arg));
        *(int **)(self + 0x4A0) = buf;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;
        buf[0] = 0;
    }
    zero = 0.0f;
    *(int *)(self + 0x4A8) = 1;
    (*(float **)(self + 0x4A0))[0] = 250.0f;
    (*(float **)(self + 0x4A0))[1] = 207.0f;
    func_003361E0(self, D_001ADC10, arg);
    func_003361E0(self + 0x4C, D_001ADC18, arg);
    func_003361E0(self + 0x98, D_001ADC20, arg);
    func_003361E0(self + 0xE4, D_001ADC28, arg);
    func_003361E0(self + 0x130, D_001ADFC0, arg);
    func_003361E0(self + 0x17C, D_001ADFC8, arg);
    func_US2_003377B0(self + 0x368, D_001ADF10, arg);
    func_US2_003377B0(self + 0x3C0, D_001ADF18, arg);
    func_US2_003377B0(self + 0x418, D_001ADF20, arg);
    func_US2_003377B0(self + 0x2B8, D_001ADD60, arg);
    func_US2_003377B0(self + 0x310, D_001AE250, arg);
    func_US2_003377B0(self + 0x1C8, D_001ADD58, arg);
    func_US2_003377B0(self + 0x220, D_001AE030, arg);
    *func_00335E20(self) = 0x60442D00;
    *func_00335E20(self + 0x4C) = 0x60241700;
    *func_00335E20(self + 0x98) = 0x55F0C070;
    *func_00335E20(self + 0xE4) = 0x55F0C070;
    *func_00335E20(self + 0x17C) = 0x70FFFEED;
    *func_00335E20(self + 0x130) = 0x55F0C070;
    *func_00335E20(self + 0x2B8) = 0x80F0F0F0;
    *func_00335E20(self + 0x310) = 0x80F0F0F0;
    *func_00335E20(self + 0x1C8) = 0x80F0F0F0;
    *func_00335E20(self + 0x220) = 0x80F0F0F0;
    *func_00335E20(self + 0x368) = 0x80F0F0F0;
    *func_00335E20(self + 0x3C0) = 0x80F0F0F0;
    *func_00335E20(self + 0x418) = 0x80F0F0F0;
    func_00336A30(self + 0x2B8, 0);
    func_00336A30(self + 0x310, 1);
    func_00335F88(self + 0x310, 0.9f, 0.9f, zero, zero);
    func_00336390(self, D_001A8CFC[0] + 0x8710, 0x9E);
    func_00336390(self + 0x4C, D_001A8CFC[0] + 0x8710, 0x9F);
    func_00336390(self + 0x98, D_001A8CFC[0] + 0x8710, 0xA0);
    func_00336390(self + 0xE4, D_001A8CFC[0] + 0x8710, 0xA1);
    func_00336390(self + 0x130, D_001A8CFC[0] + 0x8710, 0x5D);
    func_00336390(self + 0x17C, D_001A8CFC[0] + 0x8710, 0x5E);
    *(int *)(self + 0x4AC) = 0;
    *(int *)(self + 0x4B0) = 0;
    *(int *)(self + 0x4B8) = 3;
    func_00336710(self + 0x278, D_001ADFD8, arg);
    *func_00335E20(self + 0x278) = 0x60F0F0B0;
    func_00335F88(self + 0x278, 32.0f, 32.0f, zero, zero);
    *func_00335E20(self + 0x1C8) = 0x80F0F0F0;
    *func_00335E20(self + 0x220) = 0x80F0F0F0;
    func_00336A38(self + 0x1C8, func_00288FB8(0x2BEA));
    func_00336A38(self + 0x220, func_00288FB8(0x2BEF));
    func_00336A38(self + 0x368, (int)(self + 0x470));
    func_00336A38(self + 0x3C0, (int)(self + 0x480));
    func_00336A38(self + 0x418, (int)(self + 0x490));
    func_00336A30(self + 0x368, 0);
    func_00336A30(self + 0x3C0, 0);
    func_00336A30(self + 0x418, 0);
    *(int *)(self + 0x4B4) = 0;
    func_00336A38(self + 0x2B8, func_00288FB8(0x2BE5));
    func_US2_003453D0(self, 0);
}


typedef struct {
    unsigned char gap0[0x4AC];
    int column, row, index, mode;
} DobboGridState312;
typedef struct { unsigned char pad[6]; short id; short tail; } SelectionRow;
extern SelectionRow D_001AA810[];
extern SelectionRow ref_L00_00286D68_00[];

void func_US2_00344E08(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        state->row = 1;
        state->mode = 2;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        state->row = 0;
        state->mode = 2;
    } else if (buttons & 0x8000) {
        --state->column;
        func_002E5E58(3, 0, 0);
        if (state->column < 0) {
            state->column = 0;
            state->mode = 1;
        }
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        ++state->column;
        if (state->column >= 2) {
            state->column = 0;
            state->mode = 1;
            state->row = 0;
        }
    }
    state->index = D_001AA810[state->column].id;
}


/* The cursor's up/down/left/right move: the button mask picks the direction, the state keeps
   the column (0x43C), the row (0x440), the chosen index (0x444) and the mode (0x448). */
void func_US2_00344F18(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        if (--state->row < 0) {
            if (state->column < 2) {
                state->row = 0;
                state->mode = 0;
            } else if (state->column == 2) {
                state->row = 1;
            } else {
                state->row = 0;
                state->mode = 1;
                state->column = 0;
            }
        }
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        if (++state->row >= 2) {
            if (state->column < 2) {
                state->row = 0;
                state->mode = 0;
            } else if (state->column == 2) {
                state->row = 0;
            } else {
                state->row = 0;
                state->mode = 3;
                state->column = 0;
            }
        }
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        if (--state->column < 0) {
            state->column = 3;
        }
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        if (++state->column >= 4) {
            state->column = 0;
            state->mode = 3;
            state->row = 0;
        }
    }
    state->index = ref_L00_00286D68_00[state->column + state->row * 4].id;
}


/* prioritized masks1000/4000/8000/2000 update signedcolumns43C/rows440 and mode448 with originalevent3 flags0/entitynull; index444=column+2row */
void func_US2_00345080(DobboGridState312 *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        --state->row;
        if (state->row < 0) {
            if (state->column == 0) {
                state->mode = 2;
                state->row = 1;
                state->column = 3;
            } else if (state->column == 1) {
                state->row = state->column;
            }
        }
    } else if (buttons & 0x4000) {
        int row;
        func_002E5E58(3, 0, 0);
        row = state->row + 1;
        state->row = row > 1 ? 0 : row;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        --state->column;
        if (state->column < 0) {
            state->column = 3;
            state->row = 1;
            state->mode = 2;
        }
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        ++state->column;
        if (state->column >= 2)
            state->column = 0;
    }
    state->index = state->column + state->row * 2;
}


extern int func_002E5E58(int, unsigned int, void *);
extern short D_L00_001AAB76;

void func_US2_003451B8(char *object, unsigned int buttons)
{
    if (buttons & 0x1000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 2;
        *(int *)(object + 0x4B0) = 1;
        *(int *)(object + 0x4AC) = 3;
    } else if (buttons & 0x4000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 2;
        *(int *)(object + 0x4AC) = 3;
        *(int *)(object + 0x4B0) = 0;
    } else if (buttons & 0x8000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B8) = 0;
        *(int *)(object + 0x4AC) = 1;
        *(int *)(object + 0x4B0) = 0;
    } else if (buttons & 0x2000) {
        func_002E5E58(3, 0, 0);
        *(int *)(object + 0x4B0) = 0;
        *(int *)(object + 0x4B8) = 3;
        *(int *)(object + 0x4AC) = 0;
    }
    *(int *)(object + 0x4B4) = D_L00_001AAB76;
}


INCLUDE_ASM("asm/us2/game", func_US2_00345298);
