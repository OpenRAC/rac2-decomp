#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union {TI128 q;float v[4];} Vector;

/* Measured camera prefix: its position precedes the three-row basis. */
typedef struct {
    float position[4];
    u8 reserved10[0x220];
    float basis[3][4];
} CameraBasisPrefix;
typedef struct NODE NODE;
typedef void (*DrawCallback_r002E6CF0)(void *);
extern unsigned int D_00138324[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern int mode_gp SDATA(D_L00_001A8F00);
extern int D_L00_001B1BE8 MACRO_ADDR;
extern float D_L00_001B18E0;
extern CameraBasisPrefix D_L00_001B8DC0;
extern float D_L00_001AFA44 __attribute__((sda));
extern int D_L00_001AFA4C __attribute__((sda));
extern void func_002A7750(unsigned char *,unsigned char,int),func_0029F338(void *);
extern int func_002B49E0(int,int,int,int,unsigned char *),func_002B4B70(int,int);
extern int func_L00_003B6858(void *);
extern void func_L00_003B69D8(void *),func_L00_003B75C8(void *),func_L00_003B72B0(void *),func_L00_003B77A8(void *);
extern void func_L00_003B7908(void *),func_L00_002E6CF0(DrawCallback_r002E6CF0,void *),func_L00_003B6A90(NODE *);
extern float func_002AA2E8(float *,float,float);
extern void func_002833F0(float *,float *),func_00283698(void *,void *),func_00282CF0(void *,void *,void *),func_00283098(void *,void *,void *);
extern void func_L00_003B7190(float *,float *),func_L00_003B7260(float,float,float,float *,float *),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float);
extern void func_L00_003B74A8(unsigned char *,void *);
extern int func_002A8C28(void *,float *,float,int,float,float,int,int,int);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
/* Runs the two-ship minigame object and its shots. It starts the game, updates the scene, and moves each shot until it hits the middle or times out. */
void func_L00_003B63D8(unsigned char *object)
{
    Vector point;
    /* 00283698 reads three source rows and writes all four destination rows. */
    float inverse[4][4];
    Vector velocity,spawn,offset;
    char *context=*(char **)(object+0x68);
    int mode;
    switch(object[0x20]) { case 0: {
        if(!D_L00_001A8F00) {BeginSlotRequest(7,1,(int)object,2,0);return;}
        if(D_L00_001A8F00==7 && InitializePairedObjects(object)) {
            point.q=0;point.v[1]=1.5707964f;
            euler_rotation_basis(gCameraPosition_L00.basis,point.v);
            SetMobyState(object,1,-1);return;
        }
        { unsigned timer=U(object,0x96),old=timer++;
          U(object,0x96)=timer; if(old<6)return; }
        MarkMobySpawned(object);return;
    break; } case 1: {
        D_L00_001B1BE8=1;
        UpdatePairedObjects(object);
        UpdateSameClassMobies(object);
        SpawnCameraSparkles(object);
        SpawnPairGameBackgroundParticles(object);
        AddDrawCallbackToList1(DrawPairGameScores,object);
        if(I(context,0x60) && I(context,0x64)++>=91) {
            ApproachValue(&D_L00_001B18E0,1.0f,0.06666667f);
            mode=mode_gp;
            if(D_L00_001B18E0>=1.0f) {
                DestroyPairGameObjects((NODE *)object);
                InitializePairedObjects(object);
                I(context,0x64)=0; I(context,0x60)=0;
                mode=D_L00_001A8F00;
            }
        } else {
            ApproachValue(&D_L00_001B18E0,0.0f,0.06666667f);
            mode=D_L00_001A8F00;
        }
        if(mode!=7) {
            DestroyPairGameObjects((NODE *)object);
            MarkMobySpawned(object);return;
        } else {
            if(!(D_00138324[0]&0x10))return;
            EndSlotRequest(1,0);return;
        }
    break; } case 2: {
        matrix_from_basis_rows(inverse,gCameraPosition_L00.basis);
        FastVecSub(&point,object+0x10,gCameraPosition_L00.position);
        matrix_mul_vec3(&point,&point,inverse);
        matrix_mul_vec3(&velocity,context,inverse);
        WrapPlayAreaCoordinates(point.v+1,point.v+2);
        ApplyCentrePullToVelocity(point.v[1],point.v[2],D_L00_001AFA44*0.00027777778f,velocity.v+1,velocity.v+2);
        velocity.v[0]=0.0f;
        FastVecAdd(&point,&point,&velocity);
        matrix_mul_vec3(object+0x10,&point,gCameraPosition_L00.basis);
        FastVecAdd(object+0x10,object+0x10,gCameraPosition_L00.position);
        matrix_mul_vec3(context,&velocity,gCameraPosition_L00.basis);
        if(point.v[1]*point.v[1]+point.v[2]*point.v[2]<0.09f) {MarkMobySpawned(object);return;} else {
            SpawnTwoColoredSparkles(object,object+0x10);
            vec_scale_to_length(&offset,gCameraPosition_L00.basis,-0.1f);
            FastVecAdd(&spawn,object+0x10,&offset);
            SweepCollisionFromObject(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            FastVecSub(&spawn,object+0x10,&offset);
            SweepCollisionFromObject(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            FastVecSub(&spawn,object+0x10,&offset);
            SweepCollisionFromObject(*(void **)(object+0xB8),spawn.v,0.1f,0x10000,1.0f,1.0f,0,1,0);
            if(D_L00_001A8F00==7) {int limit=D_L00_001AFA4C; unsigned timer=U(object,0x96),old=timer++;
              U(object,0x96)=timer; if((int)old<=limit)return;}
        }
    }
    break; default: return; }
    MarkMobySpawned(object);
}
