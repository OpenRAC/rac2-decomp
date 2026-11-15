/* Allocate a flock member and initialize its complete vectors and orientation. */
#include "common.h"

extern char *func_0029EFD0(int);
extern float func_002A7878(float, float);
extern void func_002A0F48(char *);

typedef int TI128 __attribute__((mode(TI)));

char *func_L06_003F3EF0(char *owner, TI128 *position, TI128 *motion, int field1a, int field1c)
{
    char *record;
    char *created;
    float angle;
    u8 byte1c = (u8)field1c;
    u8 byte1a = (u8)field1a;

    created = (char *)CreateMoby(0x75E);
    if (created != 0) {
        record = *(char **)(created + 0x68);
        *(char **)(record + 0x10) = owner;
        qcopy(created + 0x10, position);
        qcopy(record, motion);
        {
            angle = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(created + 0xF0) = angle;
            angle = func_002A7878(-3.1415927f, 3.1415927f);
            *(float *)(created + 0xF4) = angle;
        }
        *(unsigned short *)(record + 0x18) = 0x1F4;
        *(int *)(record + 0x14) = 0;
        *(unsigned char *)(created + 0x30) = 0xFF;
        *(unsigned short *)(created + 0x32) = 0x40;
        *(unsigned char *)(created + 0x31) = 1;
        *(unsigned char *)(created + 0x20) = 0;
        angle = *(float *)(*(int *)(created + 0x24) + 0x24) * 0.3f;
        *(float *)(created + 0x2C) = angle;
        *(unsigned char *)(record + 0x1C) = byte1c;
        *(unsigned char *)(record + 0x1A) = byte1a;
        *(unsigned char *)(record + 0x1B) = 0;
        func_002A0F48(created);
    }
    return created;
}
