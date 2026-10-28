/* Retained nonmatching reconstruction, 27 October 2026.
 * Profile: -O2 -G0 -ffunction-sections -g. Candidate and retail: 488 bytes. USA v1.01, USA v2.00 and PAL each reject all three carrying places. Only five initial flag constant/store words differ: the byte and halfword 255 constants take different registers/order. The later spawn, vector operations, division hazards, stores and return agree. Reordering the stores either changes their order or merges the constants. A separately tested partial object-header view tied. Reopen with a measured allocation explanation; no volatile or artificial dependencies.
 */
#include "common.h"
extern void *func_0029EFD0(int);
extern float func_00283248(float, float);
extern float func_00282E20(void *);
extern char *func_L09_003364E0(char *, int, unsigned int, int, float, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, char *);
extern char D_0018A0E0[];
char *func_L18_0043FFF8(void *position, char *owner, float *direction,
                       int kind, int flags, float x, float y, float z)
{
    char *object = func_0029EFD0(0x1263);
    char *state;
    float angle;
    int lifetime;
    if (object) {
        *(unsigned short *)(object + 0x34) = 0x100;
        ((unsigned char *)object)[0x30] = 255;
        *(unsigned short *)(object + 0x32) = 255;
        state = *(char **)(object + 0x68);
        object[0x20] = 0;
        qcopy(state, direction);
        qcopy(object + 0x10, position);
        *(float *)(object + 0xf8) = func_00283248(direction[0], direction[1]);
        angle = func_00282E20(direction);
        *(float *)(object + 0xf4) = -func_00283248(angle, direction[2]);
        *(char **)(state + 0x30) = func_L09_003364E0(object, -1, 0xf0208080, 0x60, 0.1f, 0.01f);
        *(float *)(state + 0x1c) = y;
        qcopy(object + 0xc0, state);
        func_00282DD8(object + 0xd0, object + 0xc0, D_0018A0E0);
        func_00282F20(object + 0xd0, object + 0xd0, -1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        angle = func_00282DF0(direction);
        angle = *(float *)(state + 0x1c) / angle;
        lifetime = func_00283CF0(angle);
        *(float *)(state + 0x24) = z;
        *(int *)(state + 0x34) = lifetime;
        *(float *)(state + 0x20) = x;
        *(int *)(state + 0x28) = kind;
        *(int *)(state + 0x2c) = flags;
        *(char **)(state + 0x10) = owner;
        if (*(short *)(owner + 0xaa) == 0xee1)
            func_002E5CF8(5, 0, owner);
        object[0x31] = 0;
        *(unsigned short *)(object + 0x34) |= 1;
    }
    return object;
}
