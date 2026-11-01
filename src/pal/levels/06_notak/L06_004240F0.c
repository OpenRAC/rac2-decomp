#include "include_asm.h"

#include "common.h"
extern int func_00282948(char *);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_PAL_002AC3C0(char *, char *);
extern int func_002A7820(int, int);
extern char *func_PAL_002BE9A8(char *, float, float, float, int, char *, float, unsigned int, int);

/* func_L06_0041FC58 is matched in its own unit, src/levels/06_notak/L06_0041FC58-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

void func_PAL_L06_004240F0(unsigned char *obj)
{
    char *data = *(char **)(obj + 0x68);
    float velocity[4], position[4];
    int count;
    unsigned char *first, *particle;
    func_PAL_002AC3C0(obj, data + 0x50);
    if (obj[0xBC]) {
        obj[0xBC] = 0;
        if (*(int *)(data + 0x248) < 250)
            *(int *)(data + 0x248) = ((s32)(func_002A7820(480, 600)) * 5 + 2) / 6;
    }
    if (func_00282948(data + 0x24C) && *(int *)(data + 0x204) != 2)
        func_00282948(data + 0x248);
    func_00282948(data + 0x240);
    if (*(unsigned short *)(obj + 0x96) < 65534) ++*(unsigned short *)(obj + 0x96);
    if (func_00282948(data + 0x250)) *(float *)(data + 0x290) = *(float *)(data + 0x298);
    velocity[0] = 0;
    velocity[2] = -0.05f;
    velocity[3] = 1;
    velocity[1] = 0;
    count = func_002A77E0(16);
    if (func_002A77E0(2)) count = -count;
    qcopy(position, obj + 0x10);
    position[2] -= 0.2f;
    first = func_PAL_002BE9A8((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
    if (first) {
        unsigned char *state;
        *(short *)(first + 0xA) = 7;
        state = first + 0x20;
        first[9] = func_00283CF0(4) + 0x70;
        *(int *)(state + 4) = 2;
        state[0xA] = 0xDF;
        state[0xB] = first[0xA];
    }
    {
        unsigned char *second = func_PAL_002BE9A8((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
        if (second) {
            unsigned char *state = second + 0x20;
            /* Retail reuses the first particle header here. */
            *(short *)(first + 0xA) = 7;
            first[9] = func_00283CF0(4) + 0x70;
            *(int *)(state + 4) = 2;
            state[0xA] = 0xDF;
            state[0xB] = first[0xA];
        }
    }
    particle = func_PAL_002BE9A8((char *)position, .05f, 1, .97f, 16, (char *)velocity, 157500, 0x8FFFFFFF, 0);
    if (particle) {
        unsigned char *state;
        state = particle + 0x20;
        particle[9] = func_00283CF0(4) + 0x70;
        *(short *)(particle + 0xA) = 19;
        particle[8] = func_002A77E0(255);
        *(int *)(state + 4) = 2;
        state[0xA] = 0x8F;
        state[0xB] = first[0xA];
    }
}

