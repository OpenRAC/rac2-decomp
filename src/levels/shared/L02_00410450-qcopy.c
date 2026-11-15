#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef int Quad __attribute__((mode(TI)));
typedef struct { u8 *child; float x, y; } CaptureState;
extern void func_002A7750(u8 *, u8, int);
extern void func_L02_003A6FE8(char *);

/* Bind a captured child and initialize the capture trajectory. */
void func_L02_00416720(u8 *object, u8 *child, float x, float y)
{
    CaptureState *state=*(CaptureState **)(object+0x68);
    if (child) {
        u8 *data;
        SetMobyState(object,2,-1);
        *(Quad *)(child+0x10)=*(Quad *)(object+0x10);
        *(float *)(child+0x18)-=2.0f;
        state->x=x;
        state->y=y;
        state->child=child;
        InitNanotechCrateMoby((char *)child);
        *(u16 *)(child+0x36)=0x7F80;
        *(u16 *)(state->child+0x34)&=0xFFFE;
        *(u16 *)(state->child+0x34)&=0xFF7F;
        data=*(u8 **)(state->child+0x68);
        *(int *)(data+0xAC)=2;
        *(float *)(data+0xB0)=1.0f;
    }
}
