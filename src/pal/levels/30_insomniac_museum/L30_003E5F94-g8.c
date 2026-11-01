#include "include_asm.h"

#include "common.h"
extern char D_L30_001B3AE0[] __attribute__((sda)), D_L30_001B3AF0[] __attribute__((sda)), D_00189EA0[];
extern float D_L30_001B3B20[] __attribute__((sda));
extern float D_L30_001B0B78 __attribute__((sda));
extern float D_L30_001B0B7C __attribute__((sda));
extern float D_L30_001B0B80 __attribute__((sda));
extern float D_L30_001B0BB0 __attribute__((sda));
extern float D_L30_001B0BBC __attribute__((sda));
extern float D_L30_001B0BC0 __attribute__((sda));
extern float D_L30_001B0BC4 __attribute__((sda));
extern int D_L30_001B0BB4 __attribute__((sda));
extern int D_L30_001B0BB8 __attribute__((sda));
extern char D_L30_001B0B90[16] __attribute__((sda)), D_L30_001B0BA0[16] __attribute__((sda));
extern void func_002A7750(void *,int,int);
extern int func_002A9640(void *,int,int), func_PAL_00273A10(void *);
extern void func_00282C88(void *),func_00282C98(void *),func_00282CF0(void *,void *,void *),func_00282DD8(void *,void *,void *),func_00283098(void *,void *,void *),func_00282CC0(void *,void *,void *),func_002833F0(void *,void *);
extern void func_00282F70(void *,void *,float),func_00282F20(void *,void *,float);
extern float func_00283198(float),func_00283180(float);
extern void func_PAL_L00_00328480(void *,void *,float,int,int,void *,unsigned,int,float,float,float);
extern void func_PAL_00273818(void *,int,int,void *,void *,int,float);

void func_PAL_L30_003E5F94(unsigned char *obj) {
    struct { float v[4], axis[4], up[4], pos[4]; } f;
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; func_002A7750(obj,1,-1);
        *(unsigned short *)(obj+0x34)|=0x100;
        qcopy(D_L30_001B3AE0,obj+0x10); qcopy(D_L30_001B3AF0,obj+0xF0);
        func_00282C88(D_L30_001B3B20); D_L30_001B3B20[2]=0.4f;
        break;
    case 1:
        if(func_002A9640(obj,0x10000,0)) {
            float frameTime=0.020000001f;
            float angleScale;
            func_00282CF0(f.v,obj+0x10,D_00189EA0);
            angleScale=0.0003490659f;
            func_00282F70(f.v,f.v,D_L30_001B0B78*frameTime);
            f.v[2]=D_L30_001B0B7C*frameTime;
            func_00282C98(f.up);
            func_00282DD8(f.axis,f.v,f.up);
            func_00282F20(f.axis,f.axis,func_00283198(-D_L30_001B0B80*angleScale));
            f.axis[3]=func_00283180(D_L30_001B0B80*angleScale);
            func_00283098(f.pos,D_L30_001B0B90,obj+0xC0);
            func_00282CC0(f.pos,f.pos,obj+0x10);
            func_PAL_L00_00328480(obj,f.pos,D_L30_001B0BB0,D_L30_001B0BB4,D_L30_001B0BB8,D_L30_001B0BA0,0x50404040,0,D_L30_001B0BBC,D_L30_001B0BC0,D_L30_001B0BC4);
            func_PAL_00273818(obj,0,-1,f.v,f.axis,255,15.0f);
            *(int *)(obj+0x98)=0; func_002A7750(obj,2,-1);
        }
        break;
    case 2: if(func_PAL_00273A10(obj)) func_002A7750(obj,3,-1); break;
    case 3:
        if(obj[0x23]<2) {
            qcopy(obj+0x10,D_L30_001B3AE0); func_002833F0(obj+0xC0,D_L30_001B3AF0);
            obj[0x23]=128; *(int *)(obj+0x98)=*(int *)(*(char **)(obj+0x24)+0x10); func_002A7750(obj,1,-1);
        } else obj[0x23]-=2;
        break;
    }
    obj[0xA8]=255;
}
