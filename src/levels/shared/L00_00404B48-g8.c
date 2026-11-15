#include "common.h"
extern float func_00283B98(float,float),func_002A7940(void);
extern int func_002A7820(int,int);
extern void func_00281EB8(void *,int,unsigned int,int,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern int D_L00_001B0E00 __attribute__((sda));
extern int D_L00_001B0E04 __attribute__((sda));
extern int D_L00_001B0E08 __attribute__((sda));
extern int D_L00_001B0E0C __attribute__((sda));
extern int D_L00_001B0E10 __attribute__((sda));
extern int D_L00_001B0E14 __attribute__((sda));
extern float D_L00_001B0E18 __attribute__((sda));
extern float D_L00_001B0E1C __attribute__((sda));
extern float D_L00_001B0E20 __attribute__((sda));

/* Draws the sparkling glow and sparks around a flying shot. */
void func_L00_00404B48(char *obj)
{
    float tmp[4];
    char *ctx=*(char **)(obj+104);
    char *pos=obj+16;
    unsigned int color;
    *(float *)(ctx+28)=FastAddRotations(*(float *)(ctx+28),D_L00_001B0E18*0.017453294f);
    color=RandomIntRange(D_L00_001B0E0C,D_L00_001B0E10);
    color=(color<<24)|D_L00_001B0E08;
    DrawBillboardQuad_00281EB8(pos,D_L00_001B0E00,color,1,D_L00_001B0E1C,0.08f,-*(float *)(ctx+28));
    DrawBillboardQuad_00281EB8(pos,D_L00_001B0E00,color,1,D_L00_001B0E1C,0.08f,*(float *)(ctx+28));
    DrawBillboardQuad_00281EB8(pos,D_L00_001B0E00,color,1,D_L00_001B0E1C,0.08f,FastAddRotations(*(float *)(ctx+28)*2.0f,0.0f));
    DrawBillboardQuad_00281EB8(pos,D_L00_001B0E04,D_L00_001B0E14,1,D_L00_001B0E20,0.08f,FastAddRotations(-*(float *)(ctx+28)*1.5f,0.0f));
    DrawBillboardQuad_00281EB8(pos,D_L00_001B0E04,D_L00_001B0E14,1,D_L00_001B0E20,0.08f,*(float *)(ctx+28)*0.5f);
    DrawBillboardQuad_00281EB8(pos,D_L00_001B0E04,D_L00_001B0E14,1,D_L00_001B0E20,0.08f,FastAddRotations(*(float *)(ctx+28)*2.5f,0.0f));
    DrawBillboardQuad_00281EB8(pos,49,0x10007fff,1,0.35f,0.08f,*(float *)(ctx+28)*0.5f);
    DrawBillboardQuad_00281EB8(pos,49,0x10007fff,1,0.35f,0.08f,*(float *)(ctx+28)*-0.5f);
    DrawBillboardQuad_00281EB8(pos,47,0x507f7f7f,1,0.1f,0.08f,RandomAngle());
    FastVecAdd(tmp,pos,ctx+32);
    DrawBillboardQuad_00281EB8(tmp,47,0x507f7f7f,1,0.09f,0.08f,RandomAngle());
}
