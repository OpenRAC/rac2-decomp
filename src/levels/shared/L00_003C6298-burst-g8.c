/* func_L00_003C94D8: a unit of its own for -fno-sched-interblock (retail has no interblock
 * motion in the first loop).  tailW has a lifetime of more than one insn, so loop.c hoists it
 * on its first pass; the 0.05f and 0.5f stores then fit the second pass's threshold. */
#include "common.h"
typedef int BurstQuad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } BurstVec __attribute__((aligned(16)));
extern char D_0018A550[] NOT_SDA;
typedef struct { char pad[0x110]; BurstVec velocity; char gap[0x220]; int active; } BurstResident;
extern BurstResident D_00189E20 NOT_SDA;
typedef struct { char pad[0x16C]; unsigned char *burstColors; } BurstTables;
extern BurstTables D_L00_001FE940;
extern float D_L00_001B00FC __attribute__((sda));
extern float D_L00_001B0100 __attribute__((sda));
extern int D_L00_001B0104 __attribute__((sda));
extern int D_L00_001B010C __attribute__((sda));
extern float D_L00_001B0110 __attribute__((sda));
extern float D_L00_001B0114 __attribute__((sda));
extern float D_L00_001B0118 __attribute__((sda));
extern float D_L00_001B011C __attribute__((sda));
extern float D_L00_001B0120 __attribute__((sda));
extern float D_L00_001B0124 __attribute__((sda));
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_002ACEC0(void *,void *,void *,float);
extern float func_002A7878(float,float);
extern float func_00283B98(float,float);
extern void func_00282D30(void *,void *,float);
typedef struct { int kind, color, pad08, color2; BurstVec position, previous, velocity; } BurstParticle;
extern BurstParticle *func_L00_00333F90(void *,void *);
extern float func_00282C48(float);
extern void func_002AB668(void *,void *,float);
extern void func_002ACDE8(void *,void *,void *);
extern float func_002A78D8(float,float);
extern int func_00283CF0(float);
extern void func_00282CF0(void *,void *,void *);
extern char *func_002C16C0(void *,void *,int,int,int,int,float,float,float,float,float);
/* Spawns a burst of ten shots and ten sparks in a cone from the muzzle of the weapon. */
void func_L00_003C94D8(char *object)
{
    BurstVec matrix, start, saved, position, velocity, local, temp, offset;
    float angle, speed, life;
    int i, kind, mode;

    *(BurstQuad *)&local = 0;
    *(BurstQuad *)&saved = 0;
    saved.x=0.3f; saved.y=-1.0f; saved.w=1.0f;
    local.x=0.513f; local.y=-1.0f; local.z=0.183f; local.w=1.0f;
    matrix_mul_vec3(&local,&local,object+0xC0);
    FastVecAdd(&position,object+0x10,&local);
    angle=0.0f;
    object[0xBC]=6;
    ApplyAxisRotationToQuaternion(&saved,D_0018A550,D_0018A550+0x10,0.3490659f);
    qcopy(&start,&saved);
    for(i=0;i<10;i++) {
        BurstParticle *p;
        angle=FastAddRotations(angle,RandomFloatRange(0.0f,0.6283186f));
        speed=RandomFloatRange(0.10000001f,0.3f);
        FastVecScale(&velocity,&start,speed);
        p=SpawnStreakEffect_L00(&position,&velocity);
        if(p) {
            BurstVec *tail;
            float tailW;
            FastVecScale(&velocity,&start,0.75f);
            tail = &p->velocity;
            tailW = 2.0f;
            FastVecAdd(&p->position,&position,&velocity);
            qcopy_nc(&p->previous,&position);
            tail->w=tailW;
            p->position.w=0.05f;
            p->previous.w=0.5f;
            p->color=0x307F7F7F;
            p->color2=0x307F7F7F;
        }
        if(FloatAbs(angle)>0.00001f) {
            BuildAxisAngleQuaternion(&matrix,D_0018A550,angle);
            RotateVectorByQuaternion(&start,&saved,&matrix);
        }
    }
    ApplyAxisRotationToQuaternion(&saved,D_0018A550,D_0018A550+0x10,D_L00_001B00FC*0.017453294f);
    angle=0.0f;
    qcopy(&start,&saved);
    qzero_nc(&offset);
    if(gHeroState.active) FastVecScale(&offset,&gHeroState.velocity,1.7f);
    for(i=9;i>=0;i--) {
        char *p;
        angle=FastAddRotations(angle,RandomFloatRange(0.0f,0.6283186f));
        speed=RandomFloatRange(D_L00_001B0114*0.016666668f,D_L00_001B0118*0.016666668f);
        FastVecScale(&velocity,&start,speed);
        FastVecAdd(&velocity,&velocity,&offset);
        kind=D_L00_001B010C;
        mode=FloatToInt(RandomSignedFloatRange(1.0f,2.0f));
        temp.x=position.x+RandomSignedFloatRange(0.0f,D_L00_001B0100);
        temp.y=position.y+RandomSignedFloatRange(0.0f,D_L00_001B0100);
        temp.z=position.z+RandomSignedFloatRange(0.0f,D_L00_001B0100);
        life=RandomFloatRange(D_L00_001B011C,D_L00_001B0120)*210000.0f;
        FastVecSub(&temp,&temp,&velocity);
        p=SpawnBurstParticle_002C16C0(&temp,&velocity,kind,D_L00_001B0104,0x505050,mode,life,D_L00_001B0124,D_L00_001B0110,0.0f,0.0f);
        if(p) p[2]=D_L00_001FE940.burstColors[1];
        if(FloatAbs(angle)>0.00001f) {
            BuildAxisAngleQuaternion(&matrix,D_0018A550,angle);
            RotateVectorByQuaternion(&start,&saved,&matrix);
        }
    }
}
