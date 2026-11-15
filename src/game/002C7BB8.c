#include "common.h"
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern char *func_002B9030(int);
extern int func_002A7820(int, int);
extern unsigned char *D_001F26C8;
void func_002C7D58(char *);
char *func_002C7BB8(char *pos, char *vel, int life, int color, int speed, int alpha, int endAlpha, float size, float endSize, float gravity, int kind)
{
    char *obj = func_002B9030(0x62);
    char *p;
    if (obj) {
        qcopy(obj + 16, pos);
        *(int *)(obj+4) = (alpha << 24) | color;
        p = obj+32;
        obj[9] = FloatToInt(4.0f)+64;
        obj[1] = 0;
        *(float *)(obj+12) = size;
        obj[3] = 72;
        obj[8] = func_002A7820(0, speed*100)%255;
        obj[2] = D_001F26C8[kind];
        *(short *)(obj+10) = life;
        *(float *)(obj+32) = *(float *)vel;
        *(float *)(p+4) = *(float *)(vel+4);
        *(float *)(p+8) = *(float *)(vel+8);
        *(float *)(p+12) = gravity;
        p[21] = speed;
        *(float *)(p+16) = (endSize-size)/IntToFloat(life);
        { int delta = (endAlpha-alpha)/life;
        p[20] = delta; }
        *(void (**)(char *))(p+28) = func_002C7D58;
        *(int *)(p+24) = 60;
    }
    return obj;
}
