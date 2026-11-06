#include "common.h"


extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283CF0(float);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);



extern int func_00278E78(void);
extern int D_L08_001B1ADC SDATA(D_L08_001B1ADC);
extern int D_L08_001B1AE0 SDATA(D_L08_001B1AE0);
extern int D_L08_001B1B74 SDATA(D_L08_001B1B74);
extern int D_L08_001B1B78 SDATA(D_L08_001B1B78);
extern float D_L08_001B1B14 SDATA(D_L08_001B1B14);
extern float D_L08_001B1B18 SDATA(D_L08_001B1B18);
extern float D_L08_001B1B68 SDATA(D_L08_001B1B68);
extern float D_L08_001B1B6C SDATA(D_L08_001B1B6C);
extern float D_L08_001B1AE4 SDATA(D_L08_001B1AE4);
extern float D_L08_001B1AE8 SDATA(D_L08_001B1AE8);
extern float D_L08_001B1AEC SDATA(D_L08_001B1AEC);
extern float D_L08_001B1AF0 SDATA(D_L08_001B1AF0);
extern float D_L08_001B1AF4 SDATA(D_L08_001B1AF4);
extern float D_L08_001B1AF8 SDATA(D_L08_001B1AF8);

void func_L08_0041E790(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4], boost[4];
    char *state = *(char **)(m + 0x68);
    int col1 = D_L08_001B1ADC;
    int col2 = D_L08_001B1AE0;
    if (!func_00278E78()) {
        col1 = D_L08_001B1B74;
        col2 = D_L08_001B1B78;
    }
    { int i;
    for (i = 0; i < count; i++) {
        int a,b,c;
        char *particle;
        float x,y,range;
        x = func_00283180(func_002A7878(-3.1415927410125732f,3.1415927410125732f));
        offset[0] = x * func_002A7878(minRadius,maxRadius);
        y = func_00283198(func_002A7878(-3.1415927410125732f,3.1415927410125732f));
        y *= func_002A7878(minRadius,maxRadius);
        offset[1] = y;
        offset[2] = 0;
        func_00283098(offset,offset,m+0xC0);
        range = (speed * ((maxRadius-func_00282DF0(offset))*0.01666666753590107f))/maxRadius;
        func_00282F20(velocity,offset,func_002A7878(range / D_L08_001B1B14,range));
        qcopy(boost,state);
        boost[2] *= D_L08_001B1B68;
        func_00282CC0(velocity,velocity,boost);
        {
            velocity[2] += func_002A7878(rise / D_L08_001B1B18,rise)*0.01666666753590107f;
        }
        qzero_nc(accel);
        func_00282CC0(offset,offset,position);
        offset[2] += D_L08_001B1B6C;
        velocity[3] = size;
        accel[3] = endSize;
        a = func_00283CF0(func_002A7878(D_L08_001B1AE4,D_L08_001B1AE8));
        b = func_00283CF0(func_002A7878(D_L08_001B1AEC,D_L08_001B1AF0));
        c = func_00283CF0(func_002A7878(D_L08_001B1AF4,D_L08_001B1AF8));
        particle = func_002BAA28(offset,velocity,accel,col1,col2,a,b,c,-1);
        if (particle && (func_001163B0() & 1)) particle[3] = 0x48;
    }
    }
}
