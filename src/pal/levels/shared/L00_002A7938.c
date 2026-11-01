#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[0x21C];
    short f21C;                        
    unsigned char pad21E[0x186C - 0x21E];
    float f186C;                       
    unsigned char pad1870[0x1FE0 - 0x1870];
    float glow[3][4];                  
    float v2010[4];                    
    float v2020[4];                    
    unsigned char pad2030[0x2080 - 0x2030];
    float queue[8][4];                 
    unsigned int queueColor[8];        
    float queueSize[8];                
    float queueFade[8];                
    short queueCount;                  
    unsigned char pad2162[0x22B4 - 0x2162];
    unsigned char mode;                
    unsigned char pad22B5[0x24FC - 0x22B5];
    short f24FC;                       
    short pad24FE;
    short f2500;                       
    unsigned char pad2502[0x2508 - 0x2502];
    unsigned int f2508;                
    unsigned char pad250C[0x2520 - 0x250C];
    short f2520;                       
    short pad2522;
    unsigned int f2524;                
} Hero_L00_002A7A50;
extern Hero_L00_002A7A50 D_00189E20;
extern int D_L00_001A8F00 MACRO_ADDR;
extern unsigned char D_001A7A40[] __attribute__((sda));
extern void func_L00_00325AE8(void *, unsigned int, float, float);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern void func_0027DDC0(int, int, int, int);
extern void func_002FC560(unsigned int, unsigned long long);
extern int func_L00_002ADEA0(int);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_002AA2E8(float *, float, float);

void func_PAL_L00_002A7938(void)
{
    int index, alpha;
    float value, divisor, size, step, peak;
    unsigned int color;

    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        for (index = 0; index < D_00189E20.queueCount; index++)
            func_L00_00325AE8(D_00189E20.queue[index], D_00189E20.queueColor[index],
                              D_00189E20.queueSize[index], D_00189E20.queueFade[index]);
        return;
    }
    if (D_00189E20.f21C) {
        value = func_00283CE0(D_00189E20.f21C);
        divisor = func_00283CE0(15);
        value = value * 3.1415927f;
        value = func_00283198(value / divisor);
        alpha = func_00283CF0((value * 0.5f + 0.5f) * 80.0f);
        func_0027DDC0(0xAA, 0, 0, alpha);
        func_002FC560(0x47, 0x5360B);
    }
    if (D_00189E20.mode == 3) {
        unsigned int tint = D_00189E20.f2508;
        float (*glow)[4] = D_00189E20.glow;
        int remaining = 2;
        while (remaining >= 0) {
            func_L00_00325AE8(*glow, tint, 0.2f, 0.08f);
            glow++;
            remaining--;
        }
    } else if (D_00189E20.mode == 0) {
        if ((func_L00_002ADEA0(3) == 3 || func_L00_002ADEA0(3) == 2) && !D_00189E20.f24FC) {
            if (D_00189E20.f2500) {
                peak = 1.0f;
                if (peak < D_00189E20.v2020[0]) peak = D_00189E20.v2020[0];
                if (peak < D_00189E20.v2020[1]) peak = D_00189E20.v2020[1];
                if (peak < D_00189E20.v2020[2]) peak = D_00189E20.v2020[2];
                func_00283D38(0xC0000028U, 0x28, peak);
            }
            func_L00_00325AE8(D_00189E20.v2010, 0xC0000028U, 0.05700000002980232f, 0.08f);
        }
        for (index = 0; index < D_00189E20.queueCount; index++)
            func_L00_00325AE8(D_00189E20.queue[index], D_00189E20.queueColor[index],
                              D_00189E20.queueSize[index], D_00189E20.queueFade[index]);
    } else if (D_00189E20.mode == 2) {
        func_L00_00325AE8(D_00189E20.v2010, 0x300000C0U, 0.25f, 0.08f);
    } else if (D_00189E20.mode == 1) {
        size = D_00189E20.f2520 ? 0.101500004529953f : 0.07f;
        if (D_001A7A40[3]) {
            D_00189E20.v2010[2] -= 0.01f;
            size *= 1.7f;
        } else {
            D_00189E20.v2010[2] -= 0.02f;
        }
        func_002AA2E8(&D_00189E20.f186C, size, 0.0036000002f);
        func_L00_00325AE8(D_00189E20.v2010, D_00189E20.f2524, D_00189E20.f186C, 0.08f);
    }
}

