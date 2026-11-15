#include "common.h"

/* func_L00_004118A8: own unit for -frac2-qcopy -frac2-qcopy-barrier.
 * The tail store order follows sched1 register weight: the stk store is the last use of slot,
 * so it carries the pointer death and goes first; the two t2 stores and the zero store keep
 * source order otherwise, which leaves the 0xC0 zero store for the break jump delay slot. */

/* A -frac2-qcopy unit: the two 16-byte vectors copied into the record are lq/sq pairs. */

typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));

extern float func_002A7878_2(float low, float high);
extern float func_002A78D8_1(float low, float high);
extern void func_00282C88_1(void *p);
extern char D_L00_00256BC0[];

/* Claims the first free record of the forty-eight 0xD0-byte records at D_L00_00256BC0, keeps
   the owner and the caller's words in it, and fills it with eighteen drawn values. */
void func_L00_004118A8(char *owner, int target, int other, char *pos, char *vel, int flag, int timeA, int timeB, int effectSlot, float scale)
{
    char *records = D_L00_00256BC0;
    char *record;
    char *posOut;
    int i;

    for (i = 0; i < 48; i++) {
        record = records + i * 0xD0;
        if (*(int *)(record + 0xAC) != 0)
            continue;
        *(char **)(record + 0xAC) = owner;
        posOut = record + 0x40;
        *(Q16_B0e5d8f83 *)posOut = *(Q16_B0e5d8f83 *)pos;
        *(Q16_B0e5d8f83 *)(record + 0x50) = *(Q16_B0e5d8f83 *)vel;
        *(float *)(record + 0x60) = func_002A7878_2(-3.14159274f, 3.14159274f);
        *(float *)(record + 0x64) = func_002A7878_2(-3.14159274f, 3.14159274f);
        *(float *)(record + 0x68) = func_002A7878_2(-3.14159274f, 3.14159274f);
        *(float *)(record + 0x84) = func_002A7878_2(-3.14159274f, 3.14159274f);
        *(float *)(record + 0x88) = func_002A7878_2(-3.14159274f, 3.14159274f);
        *(float *)(record + 0x8C) = func_002A7878_2(-3.14159274f, 3.14159274f);
        *(float *)(record + 0x6C) = func_002A78D8_1(0.001f, 0.005f);
        *(float *)(record + 0x70) = func_002A78D8_1(0.001f, 0.005f);
        *(float *)(record + 0x74) = func_002A78D8_1(0.001f, 0.005f);
        *(float *)(record + 0x90) = func_002A78D8_1(0.001f, 0.005f);
        *(float *)(record + 0x94) = func_002A78D8_1(0.001f, 0.005f);
        *(float *)(record + 0x98) = func_002A78D8_1(0.001f, 0.005f);
        *(float *)(record + 0x78) = func_002A7878_2(3.25f, 4.75f);
        *(float *)(record + 0x7C) = func_002A7878_2(3.25f, 4.75f);
        *(float *)(record + 0x80) = func_002A7878_2(3.25f, 4.75f);
        *(float *)(record + 0x9C) = func_002A7878_2(3.25f, 4.75f);
        *(float *)(record + 0xA0) = func_002A7878_2(3.25f, 4.75f);
        *(float *)(record + 0xA4) = func_002A7878_2(3.25f, 4.75f);
        func_00282C88_1(record);
        func_00282C88_1(record + 0x10);
        *(int *)(record + 0xB0) = other;
        *(int *)(record + 0xB4) = target;
        *(int *)(record + 0xC4) = flag;
        *(float *)(record + 0xC8) = scale;
        *(int *)(record + 0xBC) = timeA;
        *(int *)(record + 0xB8) = timeA;
        *(int *)(record + 0xA8) = timeB;
        *(int *)(record + 0xC0) = 0;
        *(int *)(record + 0xCC) = effectSlot;
        break;
    }
}
