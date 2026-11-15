#include "common.h"
typedef int ContactQuad __attribute__((mode(TI)));
typedef union { ContactQuad q; float f[4]; } ContactVector;
typedef struct { char pad[0x2290]; void *collision; char gap[0x24CC-0x2294]; int contact; } ContactHero;
extern ContactHero D_00189E20;
extern char D_L08_001BFF60[], D_L08_001A8F20[] MACRO_ADDR;
typedef struct { char pad[0x10]; ContactQuad position; char tail[0xE0]; } ContactEntry;
extern ContactEntry *D_L08_001B29DC __attribute__((sda));
extern float D_L08_001AFFF4 __attribute__((sda)), D_L08_001AFFF0 __attribute__((sda));
extern float D_L08_001AFFEC __attribute__((sda));
extern float D_L08_001B0118 __attribute__((sda)), D_L08_001B0120 __attribute__((sda));
extern float D_L08_001B3410 MACRO_ADDR, D_L08_001B3414 MACRO_ADDR;
extern float D_L08_001B2094 MACRO_ADDR, D_L08_001B2098 MACRO_ADDR;
extern int D_001A79F0;
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern int func_00277258(void *,int,float,void *);
extern void func_0029FCC0(void *,int,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_00282E48(void *,void *);
extern void func_00282CF0(void *,void *,void *),func_00283028(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern int func_002E5DA0(int,int,void *,int),func_00278E78(void);
extern int func_L08_002D2ED8(int,int);
extern void func_002A7470(void *,int,int,int),func_002A7750(void *,int,int);
extern void func_L08_003CDB38(void *),func_L00_002D2168(int,int,float);

/* Checks whether the object has hit a wall or floor this frame. On a hit it bounces the object,
   plays a sound and sparks, and may send the hero back to a saved spot. */
/* Resolve the movement probes and update the D_L08_001BFF60 response. */
int func_L08_003CDB78(char *object, void *prevPos)
{
    ContactVector tempVec, hitPoint;
    char *vars=*(char **)(object+0x68);
    int hit,checkpointIndex,result;
    float fullDist,partDist,fallSpeed;
    ContactHero *hero=&gHeroState;

    vec_scale_to_length(&tempVec,object+0xC0,D_L08_001AFFF4);
    FastVecAdd(&hitPoint,&tempVec,object+0x10);
    vec_scale_to_length(&tempVec,object+0xE0,D_L08_001AFFF0);
    FastVecAdd(&hitPoint,&hitPoint,&tempVec);
    hit=TestPointAgainstCollision(&hitPoint,0,D_L08_001AFFEC,hero->collision);
    if (!hit) {
        TransformMobyJointToWorld(object,1,&tempVec);
        hit=CollLine(&hitPoint,&tempVec,0x10,hero->collision,0);
        if (!hit) {
            TransformMobyJointToWorld(object,4,&tempVec);
            hit=CollLine(&hitPoint,&tempVec,0x10,hero->collision,0);
            if (!hit) {
                qcopy(&hitPoint,prevPos);
                qcopy(&tempVec,vars);
                hit=CollLine(prevPos,vars,0x10,hero->collision,0);
            }
        }
        if (hit) {
            fullDist=fast_vec_dist(&hitPoint,&tempVec);
            partDist=fast_vec_dist(&hitPoint,D_L08_001BFF60);
            FastVecSub(D_L08_001BFF60+0x10,&hitPoint,&tempVec);
            vec_scale_to_length(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,fullDist-partDist);
            FastVecAdd(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&hitPoint);
        }
    }
    if (hit) {
        SpawnExplosionEffects(object,D_L08_001A8F20,D_L08_001BFF60,0.0f,0.0f,3,3,3,0.0f,0.0f,9.0f,0.8f,-1,0.0f,0,3,-1,7,0x810001);
        if (!*(int *)(vars+0xB0)) {
            PlaySoundFromClassBank(4,0,object,0x988);
            *(int *)(vars+0xB0)=15;
        }
        FastVecSub(&hitPoint,vars,&hitPoint);
        FastVecAdd(D_L08_001BFF60+0x10,D_L08_001BFF60+0x10,&hitPoint);
        if (gCurrentMapIndex!=9 && (result=GetCollHitMaterial())==1) {
            D_L08_001B2094=D_L08_001B3410;
            D_L08_001B2098=D_L08_001B3414;
            *(int *)(vars+0x50)=0;
            EnterHeroState_L08(0,1);
            if (*(unsigned char *)(object+0x43)) StartAnimationBlended(object,0,0,10);
            checkpointIndex=*(int *)(vars+0x6C);
            if (checkpointIndex>0) {
                qcopy(vars,&D_L08_001B29DC[checkpointIndex].position);
                PlaceObjectAtStoredTransform(object);
            }
            SetMobyState(object,1,-1);
            gHeroState.contact=result;
        } else {
            qcopy(vars,D_L08_001BFF60+0x10);
            FastVectorNormalize(vars+0x20,vars+0x20,D_L08_001BFF60+0x20);
            FastVecScale(vars+0x20,vars+0x20,D_L08_001B0118);
            fallSpeed=D_L08_001B0120*0.00027777778450399637f;
            *(float *)(vars+0x28)-=fallSpeed;
            if (*(unsigned char *)(object+0x20)!=9) {
                if (*(float *)(vars+0x28)>0.0f) *(float *)(vars+0x28)=-fallSpeed;
                set_hero_animation(0x80,0,15.0f);
                SetMobyState(object,9,-1);
            }
            FastVecAdd(object+0x10,object+0x10,vars+0x20);
        }
    }
    return hit;
}
