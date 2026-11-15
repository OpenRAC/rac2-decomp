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
/* Updates a swaying effect moby (class 4535): it sways along an arc, then shrinks away and is removed. */
void func_L06_004638F0(unsigned char *moby) {
    char *vars = *(char **)(moby+0x68);
    float tmp[4];
    float phase, wave, bend, height;
    if ((unsigned char)moby[0x20]) AddDrawCallbackToList1(DrawDoubleLayerQuad,moby);
    switch ((unsigned char)moby[0x20]) {
    case 0:
        *(u16 *)(moby+0x34) |= 0x800;
        F38(moby,0xf8)=FastMatrixHelperA(F38(vars,0x20),F38(vars,0x24));
        F38(moby,0xf4)=3.1415927f;
        SetMobyState(moby,1,-1);
        break;
    case 1:
        if(SetFirstPendingFlag(moby)) I38(vars,0x30)=RandomIntRange(20,40);
        add_vectors(tmp,moby+0x10,vars+0x20);
        scale_vector_xyz_in_place(tmp,vars+0x20,0.92f);
        if(FastFloatHelperD((int *)(vars+0x30))) {
            FastVecScale(tmp,vars+0x10,-F38(vars,0x38));
            FastVecAdd(vars,tmp,moby+0x10);
            F38(vars,8)-=F38(vars,0x38)*0.5f;
            F38(vars,0x3c)=3.1415927f/(F38(vars,0x34)+F38(vars,0x34));
            F38(vars,0x40)=1.5707965f;
            SetMobyState(moby,2,-1);
        }
        break;
    case 2:
        if(SetFirstPendingFlag(moby)) {
            I38(vars,0x30)=900;
            F38(vars,0x48)=ProbeGroundHeightBelow(moby+0x10,0,0.5f)+0.1f;
        }
        F38(vars,8)-=F38(vars,0x44);
        phase=WrapAngleToPi(F38(vars,0x3c)*F38(vars,0x34));
        wave=FastSinOrCosB(phase);
        height=F38(vars,0x38);
        {
            float offset;
            bend=wave*3.0f;
            bend=height*(wave>=0.0f ? square_root(wave)+bend : bend-square_root(-wave))*0.25f;
            offset=F38(vars,0x38)*wave*wave*0.6366197f*F38(vars,0x40)*0.5f;
            F38(moby,0xf4)=-(F38(vars,0x40)*wave+1.5707965f);
            FastVecScale(tmp,D_L06_001A8F50,offset);
        }
        FastVecAdd(moby+0x10,tmp,vars);
        FastVecScale(tmp,vars+0x10,bend);
        FastVecAdd(moby+0x10,tmp,moby+0x10);
        if(FloatAbs(phase)<0.1f) F38(vars,0x40)=RandomFloatRange(30.0f,60.0f)*0.017453294f;
        if(F38(moby,0x18)<F38(vars,0x48) || FastFloatHelperD((int *)(vars+0x30))) SetMobyState(moby,3,-1);
        break;
    case 3:
        if(SetFirstPendingFlag(moby)) I38(vars,0x30)=60;
        F38(moby,0xf4)=(F38(moby,0xf4)+1.5707964f)*0.95f-1.5707964f;
        moby[0x23]=(int)((float)I38(vars,0x30)*1.3333334f);
        if(FastFloatHelperD((int *)(vars+0x30))) {MarkMobySpawned(moby);return;}
        break;
    }
    F38(vars,0x3c)+=1.0f;
}


