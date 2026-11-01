#include "include_asm.h"

#include "common.h"
extern int D_L30_001AF930 __attribute__((sda));
extern int D_L30_001AF934 __attribute__((sda));
extern int D_L30_001AF938 __attribute__((sda));
extern int D_L30_001AF92C __attribute__((sda));
extern float D_L30_001AF93C __attribute__((sda));
extern float D_L30_001AF940 __attribute__((sda));
extern float D_L30_001AF944 __attribute__((sda));
extern float D_L30_001AF948 __attribute__((sda));
extern float D_L30_001AF94C __attribute__((sda));
extern float D_L30_001AF8C8 __attribute__((sda));
extern int D_001A7344;
extern u64 func_0027C878(int);
extern int func_00283CF0(float);
extern float func_00282DF0(void *),func_00282C48(float),func_00283B98(float,float);
extern void func_0027E018(int,int,int,int,int,int,int,int,s64,u64);
extern void func_0027E4A8(float,float,float,float,float,int,int,u64,unsigned,unsigned,int,int,float,float);

void func_PAL_L30_003B74B0(char *obj) {
    char *st=*(char **)(obj+0x68);
    u64 texture=func_0027C878(D_L30_001AF930+0x12);
    func_0027E018(func_00283CF0(D_L30_001AF94C),D_001A7344-128,128,128,0,0,128,128,D_L30_001AF92C,texture);
    texture=func_0027C878(D_L30_001AF934+0x12);
    func_0027E018(func_00283CF0(D_L30_001AF94C)+128,D_001A7344-128,128,128,0,0,128,128,D_L30_001AF92C,texture);
    texture=func_0027C878(D_L30_001AF938+0x12);
    {
        float angle;
        angle=func_00282DF0(st)*0.017453294f;
        { float numerator=D_L30_001AF93C*angle;
        angle=numerator/(D_L30_001AF8C8*0.020000001f); }
        angle=func_00283B98(angle,D_L30_001AF940*0.017453294f);
        func_0027E4A8(D_L30_001AF94C+64,(float)(D_001A7344-64),64,64,angle,64,64,texture,0x00FFFFF3,0x60808080,0,0,0.5f,0.35f);
    }
    {
        float angle;
        angle=func_00282C48(*(float *)(st+0x4C))*0.017453294f;
        { float scaled=D_L30_001AF944*angle;
        angle=func_00283B98(D_L30_001AF948*0.017453294f,scaled); }
        func_0027E4A8(D_L30_001AF94C+128+64,(float)(D_001A7344-64),64,64,angle,64,64,texture,0x00FFFFF3,0x60808080,0,0,0.5f,0.35f);
    }
}
