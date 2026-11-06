/* func_PAL_L11_00439ADC, the PAL copy of func_L11_00434580: the same C, where the spin step 1
 * becomes 1.2f (also the distance test), 0.06666667f becomes 0.080000006f, 1.66666675f becomes
 * 2.0000002f and the particle counts 15, 10, 20 become 12, 8, 17 (the 50 Hz scale of each).
 */
#include "common.h"

typedef int QuadPAL439ADC __attribute__((mode(TI)));
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282E80(void *,void *);
extern void func_002A8C00(void *,void *,int,void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern int func_002B38B8(void *);
extern void func_PAL_L11_0043A4C8(float *,int);
extern void func_L00_003294F0(void *,int);
extern void func_0029F338(void *);
extern float func_002A7878(float,float);
extern int func_002A7820(int,int);
extern void *func_002C2210(void *,int,float,float,unsigned int,int,int,void *,float,int);
extern void func_L00_002E6EF8(void *,void *);
extern char D_L11_001C0D20[];
extern char D_L11_001A8F20[16] MACRO_ADDR;
extern unsigned int D_L11_001B11E0 __attribute__((sda));
extern unsigned int D_L11_001B11E8 __attribute__((sda));
extern unsigned int D_L11_001B11F0 __attribute__((sda));
extern unsigned int D_L11_001B11F8 __attribute__((sda));
extern void func_L11_00434AA8(char *);
void func_PAL_L11_00439ADC(char *obj) {
    float vel[4]; char collision[48]; float pos[4],pos2[4];
    char *st=*(char **)(obj+0x68);
    float scale=*(float *)(st+0x3C);
    float *impact;
    *(float *)(st+0x38)+=1;
    if (*(float *)(st+0x38)<25) {
        float size; int sign;
        *(float *)(st+0x34)+=1.2f;
        func_00282F20(st+0x10,st+0x20,*(float *)(st+0x34));
        func_00282F20(vel,st+0x20,0.080000006f);
        func_002A8C00(collision,obj,0x10001,vel,scale);
        *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
        func_00282CC0(st+0x10,st,st+0x10);
        if(func_002761F8(st,st+0x10,0,obj,collision)) {
            impact=(float *)D_L11_001C0D20;
            *(QuadPAL439ADC *)(st+0x10)=*(QuadPAL439ADC *)impact;
            if(!func_002B38B8(obj)) {
                func_PAL_L11_0043A4C8(impact,6);
                func_L00_003294F0(obj,1);
            }
            func_0029F338(obj); return;
        }
        size=func_002A7878(1,4);
        sign=func_002A7820(25,35); if(!sign) sign--;
        qcopy(pos,st+0x10); pos[2]-=0.1f;
        func_002C2210(pos,12,size*0.3f,size,D_L11_001B11E0,0,sign,D_L11_001A8F20,0.0f,0);
        sign = -sign;
        func_002C2210(st,8,size*0.3f,size,D_L11_001B11E8,0,sign,D_L11_001A8F20,0.0f,0);
        func_002C2210(st,8,size*0.04f,size*0.4f,D_L11_001B11F0,1,-sign,D_L11_001A8F20,0.0f,0);
        func_L00_002E6EF8(func_L11_00434AA8,obj);
        return;
    } else if (*(float *)(st+0x38)>=25 && *(float *)(st+0x38)<34) {
        if(func_00282E80(st,st+0x10)>1.2f) {
            float size; int sign;
            *(float *)(st+0x34)+=1.2f;
            func_00282F20(st+0x10,st+0x20,*(float *)(st+0x34));
            func_00282F20(vel,st+0x20,0.080000006f);
            func_002A8C00(collision,obj,0x10001,vel,scale);
            *(unsigned short *)(collision+0x1A)=*(unsigned short *)(obj+0xAA);
            func_00282CC0(st+0x10,st,st+0x10);
            if(func_002761F8(st,st+0x10,0,obj,collision)) {
                impact=(float *)D_L11_001C0D20;
            *(QuadPAL439ADC *)(st+0x10)=*(QuadPAL439ADC *)impact;
                if(!func_002B38B8(obj)) {
                    func_PAL_L11_0043A4C8(impact,3);
                    func_L00_003294F0(obj,1);
                }
                func_0029F338(obj); return;
            }
            func_00282F20(pos,st+0x20,2.0000002f);
            func_00282CC0(st,st,pos);
            size=func_002A7878(1,4);
            sign=func_002A7820(25,35); if(!sign) sign--;
            qcopy(pos2,st+0x10); pos2[2]-=0.1f;
            func_002C2210(pos2,12,size*0.3f,size,D_L11_001B11E0,0,sign,D_L11_001A8F20,0.0f,0);
            func_002C2210(pos2,17,size*0.4f,size*0.2f,D_L11_001B11F8,1,-sign,D_L11_001A8F20,0.0f,0);
            func_L00_002E6EF8(func_L11_00434AA8,obj);
            return;

        }
        return;
    }
    func_0029F338(obj);
}
