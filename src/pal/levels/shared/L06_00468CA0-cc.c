/* func_PAL_L06_00468CA0, the PAL copy of func_L06_004638F0: the same C, where scale func_002A7820(20,40). */
#include "common.h"
extern void func_L00_002E6CF0(void *,void *);
extern void func_002A7750(void *,int,int);
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern float func_00282C48(float);
extern float func_00283248(float,float);
extern int func_002B3868(void *);
extern int func_002A7820(int,int);
extern void func_00282CD8(void *,void *,void *);
extern void func_00282D48(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A89A8(void *,int,float);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00282C10(float);
extern float func_002A7878(float,float);
extern void func_L06_00463FC0(char *);
extern float D_L06_001A8F50[4] __attribute__((sda));
#define F38(p,o) (*(float *)((char *)(p)+(o)))
#define I38(p,o) (*(int *)((char *)(p)+(o)))
void func_PAL_L06_00468CA0(unsigned char *m) {
    char *v = *(char **)(m+0x68);
    float tmp[4];
    float phase, wave, bend, height;
    if ((unsigned char)m[0x20]) func_L00_002E6CF0(func_L06_00463FC0,m);
    switch ((unsigned char)m[0x20]) {
    case 0:
        *(u16 *)(m+0x34) |= 0x800;
        F38(m,0xf8)=func_00283248(F38(v,0x20),F38(v,0x24));
        F38(m,0xf4)=3.1415927f;
        func_002A7750(m,1,-1);
        break;
    case 1:
        if(func_002B3868(m)) I38(v,0x30)=(((int)(func_002A7820(20,40)) * 5 + 2) / 6);
        func_00282CD8(tmp,m+0x10,v+0x20);
        func_00282D48(tmp,v+0x20,0.90400004f);
        if(func_00282948((int *)(v+0x30))) {
            func_00282D30(tmp,v+0x10,-F38(v,0x38));
            func_00282CC0(v,tmp,m+0x10);
            F38(v,8)-=F38(v,0x38)*0.5f;
            F38(v,0x3c)=3.1415927f/(F38(v,0x34)+F38(v,0x34));
            F38(v,0x40)=1.5707965f;
            func_002A7750(m,2,-1);
        }
        break;
    case 2:
        if(func_002B3868(m)) {
            I38(v,0x30)=750;
            F38(v,0x48)=func_002A89A8(m+0x10,0,0.5f)+0.1f;
        }
        F38(v,8)-=F38(v,0x44);
        phase=func_002ABB18(F38(v,0x3c)*F38(v,0x34));
        wave=func_00283198(phase);
        height=F38(v,0x38);
        {
            float offset;
            bend=wave*3.0f;
            bend=height*(wave>=0.0f ? func_00282C10(wave)+bend : bend-func_00282C10(-wave))*0.25f;
            offset=F38(v,0x38)*wave*wave*0.6366197f*F38(v,0x40)*0.5f;
            F38(m,0xf4)=-(F38(v,0x40)*wave+1.5707965f);
            func_00282D30(tmp,D_L06_001A8F50,offset);
        }
        func_00282CC0(m+0x10,tmp,v);
        func_00282D30(tmp,v+0x10,bend);
        func_00282CC0(m+0x10,tmp,m+0x10);
        if(func_00282C48(phase)<0.1f) F38(v,0x40)=func_002A7878(30.0f,60.0f)*0.017453294f;
        if(F38(m,0x18)<F38(v,0x48) || func_00282948((int *)(v+0x30))) func_002A7750(m,3,-1);
        break;
    case 3:
        if(func_002B3868(m)) I38(v,0x30)=50;
        F38(m,0xf4)=(F38(m,0xf4)+1.5707964f)*0.94f-1.5707964f;
        m[0x23]=(int)((float)I38(v,0x30)*1.5999999f);
        if(func_00282948((int *)(v+0x30))) {func_0029F338(m);return;}
        break;
    }
    F38(v,0x3c)+=1.0f;
}

