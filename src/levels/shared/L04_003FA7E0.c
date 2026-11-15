#include "common.h"
/* Projectile steering, collision response and impact effects shared by Barlow and Joba.
 * The aligned 0x50-byte template uses the compiler's normal quadword block move.
 * Keep the real helper returns even when ignored: they affect call scheduling. */
typedef int HomingUpdateQuad __attribute__((mode(TI), aligned(16)));
typedef union { float v[4]; HomingUpdateQuad q; } HomingUpdateVector;
typedef struct { HomingUpdateVector v[5]; } __attribute__((aligned(16))) HomingUpdateTemplate;
typedef struct { unsigned int v[6]; } HomingUpdateColors;
typedef union { HomingUpdateColors colors; HomingUpdateVector vectors[2]; } HomingUpdateColorScratch;
extern HomingUpdateTemplate D_L04_002CA100;
extern unsigned char *D_L04_001FF25C;
extern float D_L04_001B200C MACRO_ADDR;
extern unsigned char D_L04_001B9540[];
extern unsigned char D_L04_001C3B40[];
extern char D_L04_001B9680[];
extern HomingUpdateColors D_L04_001B0458, D_L04_001B0470;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern float func_00282E20(void *);
extern float func_00282DB0(void *, void *);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00282948(void *);
extern int func_00282978(void *);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002AA898(void *, float, void *, float, float, float, int);
extern void func_002AF000(void *, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282FB8(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void * func_002BD8B0(void *, void *, int, int, int, int, float);
extern unsigned char *func_002C16C0(void *, void *, int, int, int, int, float, float, float, float, float);
extern unsigned char *func_L04_0040EC80(void *, void *, void *, void *, void *, void *, float, float);
extern void func_L04_003FA350(void *, void *, void *);
extern void func_L04_0040ACC8(void);
extern int func_L04_003F9ED0(void *, void *, void *, void *, void *, void *, void *);
extern int func_002E5DA0(int, int, void *, int);
extern int func_00277F48(void *, int, void *, float, int);
extern void func_002A9850(void *, void *, void *, int, int, int, int, int, float, float, float);
extern void func_00283788(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_L03_002EFB60(void *, void *, float);
extern void func_L04_0030FA30(void *, void *, void *);
extern void func_00283388(void *);
extern void func_002830C0(void *, void *, void *);
extern void * func_002BCB00(void *, void *, int, int, int, int, int, int, int, float);
extern void * func_00308600(void *, void *, int, int, int);
extern void * func_002BBCB0(void *, void *, int, int, int, int, float, float, int, int);
extern void func_002BB838(void *, void *, int, int, int, float);
extern void * func_00308408(void *, void *, void *, float, int, unsigned char, unsigned char, unsigned char, unsigned char);
extern void *func_00312B70(void *, void *, int, void *);
extern void * func_0032DA58(void *, void *, void *, float);
extern void func_0029F338(void *);
typedef struct {
    unsigned char pad0[0x140];
    float focus[4];
    unsigned char pad150[0x10];
    float shakeA;
    int pad164;
    int shakeTimeA;
    int shakeClockA;
    unsigned char pad170[0x10];
    float shakeB;
    int pad184;
    int shakeTimeB;
} HomingCamera;
#define BF(p,o) (*(float *)((unsigned char *)(p)+(o)))
#define BI(p,o) (*(int *)((unsigned char *)(p)+(o)))
#define BP(p,o) (*(unsigned char **)((unsigned char *)(p)+(o)))
/* Updates the homing rocket: it steers at its target, leaves a smoke trail, and blows up with sparks and a camera shake when it hits. */
void func_L04_003FA7E0(unsigned char *rocket) {
    HomingUpdateTemplate settings;
    HomingUpdateVector cameraMotion, oldPos, velocity, normal, trailMotion, direction, hitPos, acceleration, motion, steeringTemp, targetPos, temp, random;
    float cross[16], crossSquared[16], matC[16], matB[16], matA[16];
    HomingUpdateColorScratch colorsA;
    HomingUpdateColors colorsB, colorsC;
    float outX, outY, outZ;
    int collision;
    unsigned char *state, *target, *owner, *ownerState, *particle;
    HomingCamera *camera;
    float yaw, pitch, jitter, threshold, camDist, angle, speed, fade;
    int i, j, count, lifeA, lifeB;
    settings=D_L04_002CA100;
    collision=0;
    velocity.q = 0; velocity.v[2] = 0.13333334f;
    normal.q = 0; normal.v[2] = 1.0f;
    acceleration.q = 0;
    state = BP(rocket,0x68);
    BF(state,0x30) += (BF(state,0x44) - BF(state,0x30)) * 0.1f;
    target = BP(state,0x28);
    if (target && *(short *)(target+0xAA) == 0xBBC /* moby class 3004 */) {
        if (target[0xBC] == 6) goto destroy;
        ownerState = BP(target,0x68);
        qcopy(&targetPos,target+0x10);
        FastVecScale(&steeringTemp,target+0xC0,1.75f);
        FastVecAdd(&targetPos,&targetPos,&steeringTemp);
        if (BI(ownerState,0x744)) {
            jitter = RandomFloatRange(-0.25f,0.25f);
            if (!(BI(ownerState,0x744)&1)) jitter += 1.5f;
            else jitter -= 1.5f;
            FastVecScale(&steeringTemp,target+0xD0,jitter);
            FastVecAdd(&targetPos,&targetPos,&steeringTemp);
            FastVecScale(&steeringTemp,target+0xC0,1.0f);
            FastVecAdd(&targetPos,&targetPos,&steeringTemp);
        }
        yaw = FastMatrixHelperA(targetPos.v[0]-BF(rocket,0x10),targetPos.v[1]-BF(rocket,0x14));
        pitch = -FastMatrixHelperA(vec_distance_xy(rocket+0x10,&targetPos),targetPos.v[2]-BF(rocket,0x18));
    } else {
        if (!target) {
            *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(rocket+0x10);
            *(HomingUpdateQuad *)&random = *(HomingUpdateQuad *)(rocket+0xC0);
            target = FindHoverbikeAimTarget(rocket,&temp,&random,&outX,&outY,&outZ,0.3490659f,30.0f);
            if (target) { BP(state,0x28)=target; BF(state,0x2C)=outZ; }
        }
        owner = BP(state,0x20);
        if (owner && *(short *)(owner+0xAA)==0xBBC /* moby class 3004 */) {
            unsigned char *ownerData = BP(owner,0x68);
            FastDecTimer(state+0x4C);
            jitter = IntToFloat(*(short *)(state+0x4C));
            jitter /= IntToFloat(*(short *)(state+0x4E));
            FastVecScale(&acceleration,ownerData+0x290,jitter);
        }
        if (target) {
            FastVecSub(&motion,target+0x10,rocket+0x10);
            jitter = FastVecDot(&motion,&motion);
        } else jitter=200.0f;
        if (jitter>32.0f && (target || BI(state,0x24)>60)) {
            SteerProjectileAroundWalls(rocket,state+0x3C,state+0x40);
            yaw=BF(state,0x3C);
            pitch=BF(state,0x40);
        } else if (target && BI(state,0x24)<300 && (signed char)target[0x20]>=0) {
            qcopy(&targetPos,target+0x10);
            targetPos.v[2]+=BF(state,0x2C);
            FastVecSub(&motion,&targetPos,rocket+0x10);
            yaw=FastMatrixHelperA(motion.v[0],motion.v[1]);
            pitch=-FastMatrixHelperA(vec_length_xy(&motion),motion.v[2]);
        } else if (BI(state,0x24)<300) {
            yaw=BF(state,0x3C); pitch=BF(state,0x40);
        } else { yaw=BF(rocket,0xF8); pitch=BF(rocket,0xF4); }
    }
    if (target) {
        if (*(short *)(target+0xAA)==0xBBC /* moby class 3004 */) {
            ApproachWithVelocity(rocket+0xF8,yaw,state+0x34,0.1f,0.28f,0.20943955f,0);
            ApproachWithVelocity(rocket+0xF4,pitch,state+0x38,0.1f,0.28f,0.20943955f,0);
        } else {
            ApproachWithVelocity(rocket+0xF8,yaw,state+0x34,2.4f,0.18f,0.17453294992446899414f,0);
            ApproachWithVelocity(rocket+0xF4,pitch,state+0x38,2.4f,0.18f,0.17453294992446899414f,0);
        }
    } else {
        ApproachWithVelocity(rocket+0xF8,yaw,state+0x34,4000.0f,0.18f,0.20943955f,0);
        ApproachWithVelocity(rocket+0xF4,pitch,state+0x38,10000.0f,0.18f,0.3141593f,0);
    }
    BuildSphericalOffset(&direction,BF(state,0x30),BF(rocket,0xF8),-BF(rocket,0xF4));
    random.q = 0;
    random.v[0]=RandomFloatRange(-1.0f,1.0f);
    random.v[1]=RandomFloatRange(-1.0f,1.0f);
    random.v[2]=RandomFloatRange(-1.0f,1.0f);
    *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(&random);
    vec_scale_to_length(&temp,&temp,RandomFloatRange(0.1f,0.2f)*0.016666668f);
    vec_scale_to_length(&trailMotion,&direction,-RandomFloatRange(0.00166666682343930006f,0.016666668f));
    FastVecAdd(&temp,&temp,&trailMotion);
    vec_scale_to_length(&trailMotion,&direction,RandomFloatRange(0,1)*BF(state,0x30));
    FastVecAdd(&trailMotion,&trailMotion,rocket+0x10);
    particle=SpawnBurstParticle_002C16C0(&trailMotion,&temp,60,127,0x606060,3,40000,1000,1,-0.0002f,0);
    if(particle) { unsigned char b=*D_L04_001FF25C; particle[3]=0x44; particle[2]=b; }
    SpawnBurstParticle_002C16C0(rocket+0x10,&temp,6,127,0xB0B0B0,3,40000,1000,1,-0.0004f,0);
    random.q = 0; random.v[2]=0.02f;
    matrix_mul_vec3(&random,&random,rocket+0xC0);
    ApplyAxisRotationToQuaternion(&random,&random,rocket+0xC0,RandomAngle());
    SpawnTrailingSparkParticle(&trailMotion,&random,0x4F007FFF,0x1FFFFFFF,5,1,20000);
    qcopy(&oldPos,rocket+0x10);
    add_vectors(&temp,&direction,&acceleration);
    if(target && *(short *)(target+0xAA)==0xBBC /* moby class 3004 */) {
        FastVecAdd(rocket+0x10,rocket+0x10,&direction);
        FastVecSub(&direction,rocket+0x10,&targetPos);
        threshold=0.5f;
        if(BI(BP(target,0x68),0x744)) threshold=1;
        if(FastVecDot(&direction,&direction)<threshold) { UpdateRacerEventStreak(); rocket[0xBC]=2; }
    } else {
        if(BF(rocket,0x10)<0 || BF(rocket,0x14)<0 || BF(rocket,0x18)<0) goto destroy;
        collision=SweepProjectileCollision(rocket,state,rocket+0x10,&direction,&velocity,&normal,&hitPos);
    }
    if(!rocket[0xBC]) goto finish;
    PlaySoundFromClassBank(11,0,rocket,0xBBC /* moby class 3004 */);
    if(target && *(short *)(target+0xAA)!=0xBBC /* moby class 3004 */) {
        lifeA=ProcessCollisionHit(rocket+0x10,16,rocket,2.0f,0);
        *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(rocket+0x10);
        QueueKnockbackForNodes(rocket,&temp,D_L04_001C3B40,lifeA,collision,0x30000,3,1,2,1,1);
    }
    cross[0]=0; cross[4]=-normal.v[2]; cross[8]=normal.v[1]; cross[12]=0;
    cross[1]=normal.v[2]; cross[5]=0; cross[9]=-normal.v[0]; cross[13]=0;
    cross[2]=-normal.v[1]; cross[6]=normal.v[0]; cross[10]=0; cross[14]=0;
    cross[3]=0; cross[7]=0; cross[11]=0; cross[15]=0;
    multiply_matrix(crossSquared,cross,cross);
    for(i=0;i<10;i++) {
        angle=RandomAngle();
        func_L03_002EFB60(matA,crossSquared,1-FastSinOrCosA(angle));
        func_L03_002EFB60(matB,cross,FastSinOrCosB(angle));
        ProcessLevelDrawHelper(matB,matB,matA);
        set_identity_matrix(matA);
        ProcessLevelDrawHelper(matC,matB,matA);
        transform_vector(&temp,&hitPos,matC);
        vec_scale_to_length(&temp,&temp,RandomFloatRange(8.5f,16.5f)*0.016666668f);
        temp.v[2]+=0.083333336f;
        FastVecAdd(&temp,&temp,&velocity);
        SpawnSparkParticle_002BCB00(rocket+0x10,&temp,0x4F007FFF,0x1F00007F,RandomIntRange(60,120),1,-1,-1,0,40000);
    }
    random.q = 0;
    random.v[0]=RandomFloatRange(-1,1); random.v[1]=RandomFloatRange(-1,1); random.v[2]=RandomFloatRange(-1,1);
    *(HomingUpdateQuad *)&temp = *(HomingUpdateQuad *)(&random);
    FastVecSub(&cameraMotion,D_L04_001B9680,rocket+0x10);
    camDist=FastVecLength(&cameraMotion);
    cameraMotion.v[2]+=camDist*0.5f;
    vec_scale_to_length(&temp,&temp,camDist*0.00333333364687860012f);
    vec_scale_to_length(&cameraMotion,&cameraMotion,(camDist+camDist)*0.016666668f);
    FastVecAdd(&temp,&temp,&cameraMotion);
    FastVectorDivideHelper(&temp,&temp,0.16666667f);
    SpawnSpinningDebrisMoby(rocket+0x10,&temp,RandomIntRange(60,90),0,0);
    if(camDist<6) count=FloatToInt(camDist)/2;
    else count=3;
    fade=0;
    if(camDist<7) fade=7-camDist;
    for(j=0;j<count;j++) {
        speed=RandomFloatRange(8,10)*0.016666668f;
        colorsA.colors=D_L04_001B0458; colorsB=D_L04_001B0470;
        speed-=fade*0.016666668f;
        {
            unsigned int *ca=colorsA.colors.v+RandomIntBelow(6), *cb=colorsB.v+RandomIntBelow(6);
            int la=RandomIntRange(15,20), lb=RandomIntRange(25,30);
            SpawnFireworkSparkParticle(rocket+0x10,&velocity,*ca,*cb,la,lb,400000,speed,0,0);
        }
        {
            int la=RandomIntRange(5,10), lb=RandomIntRange(15,20);
            SpawnFireworkSparkParticle(rocket+0x10,&velocity,0x7FFFFFFF,0xFFFFFF,la,lb,400000,speed*0.5f,0,0);
        }
    }
    for(j=0;j<10;j++) {
        colorsA.colors=D_L04_001B0458; colorsC=D_L04_001B0470;
        random.q = 0;
        random.v[0]=RandomFloatRange(-1,1); random.v[1]=RandomFloatRange(-1,1); random.v[2]=RandomFloatRange(-1,1);
        *(HomingUpdateQuad *)&colorsB = *(HomingUpdateQuad *)(&random);
        vec_scale_to_length(&colorsB,&colorsB,RandomFloatRange(0,3)*0.016666668f);
        {
            unsigned int *ca=colorsA.colors.v+RandomIntBelow(6), *cb=colorsC.v+RandomIntBelow(6);
            SpawnColorBlendParticle(rocket+0x10,&colorsB,*ca,*cb,RandomIntRange(20,35),200000);
        }
    }
    if(D_L04_001B200C<0.95f && camDist>9) {
        SpawnShockwaveRing(rocket,rocket+0x10,&velocity,4,15,127,127,127,32);
        SpawnShockwaveRing(rocket,rocket+0x10,&velocity,4,24,127,127,127,32);
    }
    SpawnShockwaveRing(rocket,rocket+0x10,&velocity,4,20,127,127,0,48);
    SpawnShockwaveRing(rocket,rocket+0x10,&velocity,2,19,255,255,255,32);
    direction.v[0]=0;
    rocket[0xBC]=0;
    {
        HomingCamera *shake=(HomingCamera *)D_L04_001B9540;
        if(camDist<20) shake->shakeA=0.4f-camDist*0.0175f;
        else shake->shakeA=0.050000012f;
    }
    camera=(HomingCamera *)D_L04_001B9540;
    camera->shakeTimeA=25; camera->shakeClockA=0;
    SpawnTemplateEffectMoby(&settings,rocket+0x10,0,0);
    FastVecSub(&random,rocket+0x10,camera->focus);
    if(FastVecLength(&random)<64) {
        FastVecSub(&colorsA.vectors[1],camera->focus,&colorsA);
        vec_scale_to_length(&colorsA.vectors[1],&colorsA.vectors[1],1);
        SpawnBlastEffectMoby(rocket,rocket+0x10,&colorsA.vectors[1],5);
        camera->shakeB=0.1f; camera->shakeTimeB=90;
        camera->shakeA=0.2f; camera->shakeTimeA=60; camera->shakeClockA=0;
    }
destroy:
    MarkMobySpawned(rocket);
    return;
finish:
    if(target && *(short *)(target+0xAA)==0xBBC /* moby class 3004 */) return;
    if(FastFloatHelperD(state+0x24) || !BP(state,0x20) || vec_distance_xy(rocket+0x10,BP(state,0x20)+0x10)>260) MarkMobySpawned(rocket);
}
#undef BF
#undef BI
#undef BP
