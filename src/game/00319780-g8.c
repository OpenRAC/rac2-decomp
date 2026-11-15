#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(u16 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern void func_00319B38(void *),func_002A93B0(void *),func_0029FCC0(void *,int,void *),func_0029FC20(void *,int,void *),func_00282C88(void *),func_002830C0(void *,void *,void *),func_00282CC0(void *,void *,void *),func_002AB6D8(void *,void *),func_002B4090(void *,void *,float,float,float),func_002A6C58(void *,int,int),func_0029F338(void *),func_00319F38(void *),func_002B3BA8(void *,int,int,int,float,float),func_0031A718(void *);
extern float func_00282E48(void *,void *),func_002A89A8(void *,int,float);
extern int func_002B0ED8(void *,void *,int),func_002761F8(void *,void *,int,void *,int),func_002A8508(int,int);
extern int func_00278E78(void);
extern int func_0031A628(void *);
extern char D_001B5340[];
extern char D_001A8BD0[16] MACRO_ADDR;
extern int D_001B1B78 MACRO_ADDR;
extern short *D_001EE5A0[];
extern char *D_001B1B5C MACRO_ADDR;
extern char *D_0018C0B0 NOT_SDA;
/* Handles the enemy's body each frame: ground checks, damage, waking its group mates and picking a target. */
void func_00319780(char *self)
{
    float matrix[16];
    float a[4],b[4];
    char *vars=P(self,0x68);
    float height;
    int result,kind,mode;
    short *list;
    char *moby;
    if(B(self,0x20)==0) InitClass2484Moby(self);
    if(B(self,0x31) && fast_vec_dist(self+0x10,gCameraState_001B5340)<24.0f) {
        UpdateMobyGroundCheck(self);
        B(self,0x6F)=22;
    }
    TransformMobyJointToWorld(self,0,vars+0x300);
    TransformMobyJointToWorld(self,1,vars+0x310);
    TransformMobyJointToWorld(self,2,vars+0x320);
    TransformMobyJointPoint(self,3,matrix);
    ClearVector128(vars+0x330);
    F(vars,0x338)=0.0f;
    F(vars,0x330)=0.25f;
    transform_vector(vars+0x330,vars+0x330,matrix);
    FastVecAdd(vars+0x330,vars+0x330,matrix+12);
    result=ApplyDamageToObject(self,vars+0x80,0);
    height=ProbeGroundHeightBelow(self+0x10,0,0.5f);
    if(height==0.0f || F(self,0x18)-height>20.0f) {
        if(B(vars,0x9A)==1) {
            if(H(self,0x34)&0x100) {
                GetEulerAnglesFromMatrix(self+0xC0,self+0xF0);
                H(self,0x34)&=~0x100;
            }
            qcopy(a,D_001A8BD0);
            a[2]+=0.5f;
            RotateObjectAboutPoint(self,a,0.05f,0.05f,0.0f);
        }
    } else {
        qcopy(a,self+0x10);
        qcopy(b,self+0x10);
        b[2]-=1.0f;
        if(CollLine(a,b,0,self,0)) {
            kind=GetCollHitMaterial();
            if(kind==1 || kind==11) {
                SetDeathBits(self,0,3);
                MarkMobySpawned(self);
                return;
            }
        }
    }
    if(result) {
        if(result==5) {
            I(vars,0x110)=0;
            F(vars,0x114)=0.8377581834793091f;
        }
        AlertGroupClass2484(self);
        PassGroupLeadToken(self);
        if((result==4 || result==5) && D_001B1B78>=B(self,0x21) && CountMobysInGroupNotInState(B(self,0x21),-1)>=2) {
            list=D_001EE5A0[B(self,0x21)];
            do {
                moby=D_001B1B5C+((*list&0x7FFF)<<8);
                if(*(short *)(moby+0xAA)==0x9B4 /* moby class 2484 */ && I(P(moby,0x68),0x2A4)==0) {
                    I(P(moby,0x68),0x2A4)=1;
                    goto done_list;
                }
            } while(*list++>=0);
        }
    }
done_list:
    SelectAimTarget_002B3BA8(self,I(vars,0x400),0,0,0.0f,0.0f);
    mode=B(self,0x20);
    if(mode!=3 && mode!=12 && mode!=13 && mode!=14 && mode!=16 && I(vars,0x350) && P(vars,0x30)==gHeroMoby_0018C0B0)
        PickNearestGroupMemberAsTarget(self);
}
