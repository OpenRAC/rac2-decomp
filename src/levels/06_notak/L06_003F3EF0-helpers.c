#include "names.h"
/* Allocate a flock member and initialize its complete vectors and orientation. */
#include "common.h"

extern char *CreateMoby(int);
extern float math_random_float_range(float, float);
extern void func_002A0F48(char *);

typedef int TI128 __attribute__((mode(TI)));

char *flock_create_member(char *owner, TI128 *position, TI128 *motion, int field1a, int field1c)
{
    char *vars;
    char *member;
    float angle;
    u8 byte1c = (u8)field1c;
    u8 byte1a = (u8)field1a;

    member = (char *)CreateMoby(0x75E /* moby class 1886 */);
    if (member != 0) {
        vars = *(char **)(member + 0x68);
        *(char **)(vars + 0x10) = owner;
        qcopy(member + 0x10, position);
        qcopy(vars, motion);
        {
            angle = math_random_float_range(-3.1415927f, 3.1415927f);
            *(float *)(member + 0xF0) = angle;
            angle = math_random_float_range(-3.1415927f, 3.1415927f);
            *(float *)(member + 0xF4) = angle;
        }
        *(unsigned short *)(vars + 0x18) = 0x1F4;
        *(int *)(vars + 0x14) = 0;
        *(unsigned char *)(member + 0x30) = 0xFF;
        *(unsigned short *)(member + 0x32) = 0x40;
        *(unsigned char *)(member + 0x31) = 1;
        *(unsigned char *)(member + 0x20) = 0;
        angle = *(float *)(*(int *)(member + 0x24) + 0x24) * 0.3f;
        *(float *)(member + 0x2C) = angle;
        *(unsigned char *)(vars + 0x1C) = byte1c;
        *(unsigned char *)(vars + 0x1A) = byte1a;
        *(unsigned char *)(vars + 0x1B) = 0;
        func_002A0F48(member);
    }
    return member;
}
