#include "include_asm.h"

#include "common.h"
extern char *D_L00_001B1450 __attribute__((sda));
extern void func_00300190(void *, void *);
extern float func_002AA3A8(float *, float, float *, float, float, float);
extern int func_00282948(int *);

/* Walks the ten 0x530-byte records: spins the two direction vectors, then steps the fade state. */
void func_PAL_L00_00420D90(void)
{
    int index, axis;
    char *record;
    float *position, *velocity, value;

    for (index = 0; index < 10; index++) {
        record = (char *)(index * 0x530 + (int)D_L00_001B1450);
        if (*(int *)(record + 0x514) != 1)
            continue;
        velocity = (float *)(record + 0x4f0);
        position = (float *)(record + 0x500);
        for (axis = 0; axis < 2; axis++) {
            func_00300190(record + 0x20 + axis * 16, record + 0x20 + axis * 16);
            value = position[axis] + velocity[axis];
            position[axis] = value;
            if (value <= -8.0f)
                position[axis] = value + 8.0f;
        }
        if (*(int *)(record + 0x518) == 0) {
            func_002AA3A8((float *)(record + 0x510), 0.5f, (float *)(record + 0x51C), 0.0024f, 0.00024000001f, 0.024f);
            if (*(float *)(record + 0x510) == 0.5f) {
                *(int *)(record + 0x518) = 2;
                *(int *)(record + 0x520) = 50;
            }
        } else if (*(int *)(record + 0x518) == 1) {
            func_002AA3A8((float *)(record + 0x510), 0.0f, (float *)(record + 0x51C), 0.0024f, 0.00024000001f, 0.024f);
            if (*(float *)(record + 0x510) == 0.0f)
                *(int *)(record + 0x514) = 0;
        } else if (func_00282948((int *)(record + 0x520))) {
            *(int *)(record + 0x518) = 1;
        }
    }
}
