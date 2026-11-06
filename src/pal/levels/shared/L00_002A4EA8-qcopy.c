/* func_PAL_L00_002A4EA8, the PAL copy of func_L00_002A5048 in its own unit (flags in config/cflags.txt): the same C, where the speed and acceleration arguments of func_002AA898 are scaled by 1.44f (1.2f squared, 60/50 Hz). */
#include "include_asm.h"

typedef unsigned char u8;
typedef int Quad __attribute__((mode(TI)));
extern u8 D_0018C0D4;
extern void *func_L00_002A4FE8(int);
extern float func_00282C48(float);
extern float func_002AA898(float *, float, float *, float, float, float, int);
extern float func_002AA3A8(float *, float *, float, float, float, float);
extern void func_0029F978(u8 *, unsigned int, u8 *);
extern void func_0029F9F0(char *, char *);
extern void func_002A91F0(void *, float *);
extern void func_00282C88(Quad *);

/* Update an active attachment's orientation/position and link or retire its record. */
void func_PAL_L00_002A4EA8(u8 *node)
{
    u8 *owner = func_L00_002A4FE8(*(short *)(node + 0xA2));
    float *angles;
    Quad *position;

    if (owner == 0)
        return;
    if (D_0018C0D4 == 0) {
        int kind = *(short *)(node + 0xA2);
        if (kind == 4 || kind == 2 || kind == 5 || kind == 3)
            return;
    } else if (*(short *)(node + 0xA2) == 0) {
        return;
    }
    if (*(float *)(node + 0x60) == 0.0f &&
        *(float *)(node + 0x64) == 0.0f &&
        *(float *)(node + 0x68) == 0.0f &&
        *(float *)(node + 0x90) == 0.0f &&
        *(float *)(node + 0x94) == 0.0f &&
        *(float *)(node + 0x98) == 0.0f &&
        func_00282C48(*(float *)(node + 0x70)) < 0.003f &&
        func_00282C48(*(float *)(node + 0x74)) < 0.003f &&
        func_00282C48(*(float *)(node + 0x78)) < 0.003f &&
        *(float *)(node + 0xAC) == 1.0f &&
        func_00282C48(*(float *)(node + 0x40)) < 0.005f &&
        func_00282C48(*(float *)(node + 0x44)) < 0.005f &&
        func_00282C48(*(float *)(node + 0x48)) < 0.005f) {
        if (node[1] != 0)
            func_0029F9F0((char *)owner, (char *)node);
    } else {
        angles = (float *)(node + 0x40);
        position = (Quad *)(node + 0x70);
        func_002AA898(angles, *(float *)(node + 0x60), (float *)(node + 0x50),
                     *(float *)(node + 0xA4) * 1.44f, *(float *)(node + 0xA8) * 1.44f, 0.0f, 2);
        func_002AA898((float *)(node + 0x44), *(float *)(node + 0x64), (float *)(node + 0x54),
                     *(float *)(node + 0xA4) * 1.44f, *(float *)(node + 0xA8) * 1.44f, 0.0f, 2);
        func_002AA898((float *)(node + 0x48), *(float *)(node + 0x68), (float *)(node + 0x58),
                     *(float *)(node + 0xA4) * 1.44f, *(float *)(node + 0xA8) * 1.44f, 0.0f, 2);
        func_002AA3A8((float *)position, (float *)(node + 0x80),
                     *(float *)(node + 0x90), *(float *)(node + 0xA4), *(float *)(node + 0xA8), 0.0f);
        func_002AA3A8((float *)(node + 0x74), (float *)(node + 0x84),
                     *(float *)(node + 0x94), *(float *)(node + 0xA4), *(float *)(node + 0xA8), 0.0f);
        func_002AA3A8((float *)(node + 0x78), (float *)(node + 0x88),
                     *(float *)(node + 0x98), *(float *)(node + 0xA4), *(float *)(node + 0xA8), 0.0f);
        if (node[1] == 0)
            func_0029F978(owner, *(short *)(node + 0xA0), node);
        func_002A91F0(node + 0x10, angles);
        *(Quad *)(node + 0x30) = *position;
        *(float *)(node + 0x20) = *(float *)(node + 0xAC);
        *(float *)(node + 0x24) = *(float *)(node + 0xAC);
        *(float *)(node + 0x28) = *(float *)(node + 0xAC);
    }
    func_00282C88((Quad *)(node + 0x90));
    func_00282C88((Quad *)(node + 0x60));
    *(float *)(node + 0xAC) = 1.0f;
}
