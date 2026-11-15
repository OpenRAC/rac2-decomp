#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern u8 *func_002B9030(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern u8 *D_L05_001FF3E4;
extern void func_L00_00340490(char *);
u8 *func_L05_00352B28(float *position,float *velocity,int duration,int color,int kind,int alpha,int endAlpha,float size,float endSize,float drag)
{
    u8 *effect = func_002B9030(0x69);
    u8 *motion;
    float lifetime;
    if (effect) {
        *(Quad *)(effect+0x10) = *(Quad *)position;
        *(int *)(effect+4) = (alpha << 24) | color;
        motion = effect+0x20;
        effect[9] = FloatToInt(4.0f)+64;
        effect[1] = 0;
        *(float *)(effect+0xC) = size;
        effect[3] = 0x48;
        effect[8] = func_002A77E0(255);
        effect[2] = *D_L05_001FF3E4;
        *(short *)(effect+0xA) = duration;
        *(float *)(effect+0x20) = velocity[0];
        *(float *)(motion+4) = velocity[1];
        *(float *)(motion+8) = velocity[2];
        *(float *)(motion+0xC) = drag;
        motion[0x15] = kind;
        lifetime = IntToFloat(duration);
        *(float *)(motion+0x10) = (endSize-size)/lifetime;
        motion[0x14] = (endAlpha-alpha)/duration;
        *(void (**)(char *))(motion+0x1C) = func_L00_00340490;
    }
    return effect;
}
