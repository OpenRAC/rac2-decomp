#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_L03_001B01BC __attribute__((sda)),D_L03_001B01A4 __attribute__((sda)),D_L03_001B01B4 __attribute__((sda)),D_L03_001B01AC __attribute__((sda));
extern float D_L03_001B01A8 __attribute__((sda)),D_L03_001B01B8 __attribute__((sda)),D_L03_001B01B0 __attribute__((sda));
extern u8 D_L03_001B01D4 __attribute__((sda));
extern float D_L03_001B9998 NOT_SDA, D_L03_001BFDE8 NOT_SDA;
typedef struct { float vec[4]; char pad[0x2d4]; int mode; } PlayerState;
extern PlayerState D_0018BDD0;
typedef struct { char pad[0x74]; u8 active; char pad75[0x13]; char *owner; } L03ControlEntry;
extern u8 D_00188660[];
extern float func_00283B98(float,float);
extern void func_002833F0(void *,void *);
extern float func_00282DF0(void *);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern void func_00283098(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282C88(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AC9F8(void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002C9218(int,void *,void *,float);
extern void func_0029FCC0(void *,int,void *);
extern int func_002761F8(void *,void *,int,void *,int);
extern void func_002A93B0(void *);
/* Moves the held platform for one frame: reads the player input, pushes the platform around and checks the ground below it. */
void func_L03_003C7AC0(char *moby)
{
    float a[4],b[4],c[4];
    union { float m[12]; struct { float pad[4], d[4]; } v; } scratch;
    char *vars=*(char **)(moby+0x68);
    char *heldMoby;
    int slot;
    if(*(u8 *)(moby+0x20)==2) {
        *(TI128 *)c=0;
        c[2]=FastAddRotations(D_L03_001B9998,D_L03_001B01BC*0.017453294f);
        *(TI128 *)(b)=*(TI128 *)(c);
        euler_rotation_basis(scratch.m,b);
        qcopy(a,D_0018BDD0.vec);
        if(FastVecLength(a)>0.0f && D_0018BDD0.mode==0x31) {
            L03ControlEntry *controlEntry=(L03ControlEntry *)(gSoundState+*(int *)(vars+0x108)*0x70);
            if(controlEntry->owner!=moby || !controlEntry->active)
                *(int *)(vars+0x108)=PlayMobySound(0,4,moby);
        } else {
            slot=*(int *)(vars+0x108);
            if(slot!=-1) {
                L03ControlEntry *controlEntry=(L03ControlEntry *)(gSoundState+slot*0x70);
                if(controlEntry->owner==moby && controlEntry->active) StopSoundVoice(slot);
            }
            *(int *)(vars+0x108)=-1;
        }
        a[0]=-a[0];
        matrix_mul_vec3(a,a,scratch.m);
        heldMoby=*(char **)(vars+0xf0);
        if(heldMoby) {
            if(*(short *)(heldMoby+0xaa)==0xb85 /* moby class 2949 */) FastVecScale(a,a,D_L03_001B01AC*(1.0f/60.0f));
            else FastVecScale(a,a,D_L03_001B01B4*(1.0f/60.0f));
        } else FastVecScale(a,a,D_L03_001B01A4*(1.0f/60.0f));
    } else {
        slot=*(int *)(vars+0x108);
        if(slot!=-1) {
            L03ControlEntry *controlEntry=(L03ControlEntry *)(gSoundState+slot*0x70);
            if(controlEntry->owner==moby && controlEntry->active) StopSoundVoice(slot);
        }
        *(int *)(vars+0x108)=-1;
        ClearVector128(a);
    }
    FastVecSub(b,a,vars+0xe0);
    b[2]=0;
    heldMoby=*(char **)(vars+0xf0);
    if(heldMoby) {
        if(*(short *)(heldMoby+0xaa)==0xb85 /* moby class 2949 */) ClampVectorLength(b,D_L03_001B01B0*0.000277777785f);
        else ClampVectorLength(b,D_L03_001B01B8*0.000277777785f);
    } else {
        ClampVectorLength(b,D_L03_001B01A8*0.000277777785f);
    }
    FastVecAdd(vars+0xe0,vars+0xe0,b);
    FastVecAdd(moby+0x10,moby+0x10,vars+0xe0);
    PushPointAwayFromPath(*(int *)vars,moby+0x10,moby+0x10,1.25f);
    TransformMobyJointToWorld(moby,2,c);
    qcopy(scratch.m,c);
    scratch.m[2]+=20.0f;
    qcopy(scratch.v.d,c);
    scratch.v.d[2]+=0.5f;
    if(CollLine(scratch.v.d,scratch.m,2,moby,0)) *(float *)(vars+0xf4)=D_L03_001BFDE8;
    UpdateMobyGroundCheck(moby);
    *(u8 *)(moby+0xbd)=D_L03_001B01D4;
}
