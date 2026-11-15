#include "common.h"

typedef unsigned int CarrierQuad __attribute__((mode(TI)));
typedef union { CarrierQuad q; float f[4]; } CarrierVector;
typedef struct {
    float bobPhase, bobOffset, swayPhase, tiltPhase;
    int platform, passenger, destination, timer, path, flags;
    float riseTime, fallTime, rise;
    int motionState, motionTimer;
    float baseZ, minRise, maxRise, minWait, maxWait, spin;
    int sound, source, stopped, idleSound;
} CarrierVars;
typedef struct { int count; int pad[3]; CarrierVector points[1]; } CarrierPath;
typedef struct CarrierMoby {
    char pad0[0x10]; CarrierVector position;
    unsigned char state; char pad21[0x47]; CarrierVars *vars;
    char pad6c[0xC]; int color; char pad7c[0x2E];
    short classId; char padac[6]; short uid; char padb4[8];
    unsigned char hit; char padbd[3]; char matrix[0x30]; float rotation[4];
} CarrierMoby;
typedef struct { char bytes[0x70]; } CarrierSoundRecord;
typedef struct { char pad0[0x74]; unsigned char active; char pad75[0x13]; CarrierMoby *owner; } CarrierVoice;
extern CarrierSoundRecord D_00188660[];
extern CarrierMoby *D_L17_001B2C1C MACRO_ADDR;
extern int D_L17_001B2748[] __attribute__((sda));
extern CarrierPath *D_L17_001FE880[];
extern char D_L17_001B02A0[] NOT_SDA, D_L17_001B02C0[] NOT_SDA;
/* A fixed scalar: storing it does not alias the struct loads scheduled after it. */
extern int D_L17_001B3670 MACRO_ADDR;
extern int D_L17_001B3674 __attribute__((sda));
extern float D_L17_001B0260 __attribute__((sda));
extern float D_L17_001B0264 __attribute__((sda));
extern float D_L17_001B0268 __attribute__((sda));
extern float D_L17_001B026C __attribute__((sda));
extern float D_L17_001B0270 __attribute__((sda));
extern float D_L17_001B0274 __attribute__((sda));
extern float D_L17_001B0278 __attribute__((sda));
extern float D_L17_001B027C __attribute__((sda));
extern float D_L17_001B0280 __attribute__((sda));
extern float D_L17_001B0284 __attribute__((sda));
extern float D_L17_001B0288 __attribute__((sda));
extern float D_L17_001B028C __attribute__((sda));
extern float D_L17_001B0290 __attribute__((sda));
extern float D_L17_001B0294 __attribute__((sda));
extern float D_L17_001B0298 __attribute__((sda));
extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float), func_00283CE0(int), func_00283180(float), func_00283198(float);
extern int func_002A77E0(int), func_002A7820(int, int), func_00283CF0(float), func_00282948(int *);
extern void func_0029F338(void *), func_002AEE70(void *,void *,void *,float,float,float);
extern void func_002AEF28(void *,void *,void *,float,float,float);
extern float func_00283B98(float,float), func_00282E48(void *,void *), func_00282E80(void *,void *), func_00283248(float,float);
extern void func_00283098(void *,void *,void *), func_00282CC0(void *,void *,void *), func_00282CD8(void *,void *,void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int,int,void *), func_002B3868(void *), func_L17_003C7C58(void *);
extern void func_002E5DA0(int,int,void *,int), func_L17_003C5200(void *);
extern void func_L00_002E6CF0(void *,void *), func_0026FEB8(void *), func_002AF000(void *,float,float,float);

/* -ffast-math: combine folds K - (-x) to K + x with K first, retail's add.s order. It would also
   re-associate a literal 0.5f factor, so that value is held in a local. */
void func_L17_003C45A0(CarrierMoby *moby)
{
    CarrierVector offset, target, rotation, result;
    CarrierVector *rotationPtr;
    CarrierVars *vars = moby->vars;
    CarrierMoby *platform, *destination, *passenger;
    CarrierVars *destinationVars;
    float bob, ratio, wave, half, distance, blend, angle, pitch;
    float heightDelta, randomSpin, travelDistance;
    int color, lo, hi, ready, flash;
    if (vars->platform == -1) bob = D_L17_001B0268;
    else bob = D_L17_001B0264;
    flash = (D_L17_001B2748[0] + moby->uid) % 60 < 15;
    color = flash ? 0x80FFFFFF : 0x80404040;
    moby->color = color;
    if (moby->state == 0) {
        vars->idleSound = -1;
        if (vars->source != -1) {
            qcopy_nc(&moby->position,&D_L17_001B2C1C[vars->source].position);
            moby->position.f[2] += D_L17_001B0294;
            qcopy_nc(&D_L17_001B2C1C[vars->platform].position,&D_L17_001B2C1C[vars->source].position);
            D_L17_001B2C1C[vars->platform].position.f[2] += D_L17_001B0298;
            func_002A7750(moby,1,-1);
            return;
        }
        if (vars->destination != -1 && vars->path != -1) {
            CarrierPath *path = D_L17_001FE880[vars->path];
            moby->position.f[2] = path->points[path->count-1].f[2] + D_L17_001B0284 + D_L17_001B028C + 10.0f;
        }
        if (vars->platform != -1)
            D_L17_001B2C1C[vars->platform].position.f[2] = moby->position.f[2] - D_L17_001B0290 - D_L17_001B0284;
        vars->baseZ = moby->position.f[2];
        randomSpin = func_002A7878(0.004363324f,0.013089972f);
        if (func_002A77E0(2)) randomSpin = -randomSpin;
        vars->spin = randomSpin;
        func_002A7750(moby,1,-1);
    }
    if (vars->source != -1) {
        func_L00_002E6CF0(DrawIndexedRibbonSegments,moby);
        qcopy_nc(&moby->position,&D_L17_001B2C1C[vars->source].position);
        moby->position.f[2] += D_L17_001B0294;
        qcopy_nc(&D_L17_001B2C1C[vars->platform].position,&D_L17_001B2C1C[vars->source].position);
        D_L17_001B2C1C[vars->platform].position.f[2] += D_L17_001B0298;
        return;
    }
    if (vars->platform == -1) {
        switch (vars->motionState) {
        case 0:
            vars->baseZ = moby->position.f[2];
            vars->rise = func_002A7878(vars->minRise,vars->maxRise);
            if (func_002A77E0(2)) { moby->position.f[2] += vars->rise; vars->motionState=3; }
            else vars->motionState=1;
            lo=FloatToInt(vars->minWait*60.0f); hi=FloatToInt(vars->maxWait*60.0f);
            vars->motionTimer=func_002A7820(lo,hi);
            vars->motionTimer=func_002A7820(0,vars->motionTimer);
            break;
        case 1:
            if (func_00282948(&vars->motionTimer)) { vars->motionTimer=FloatToInt(vars->riseTime*60.0f); vars->motionState=2; }
            moby->position.f[2]=vars->baseZ; break;
        case 2:
            if (func_00282948(&vars->motionTimer)) {
                moby->position.f[2]=vars->baseZ+vars->rise; vars->motionState=3;
                lo=FloatToInt(vars->minWait*60.0f); hi=FloatToInt(vars->maxWait*60.0f);
                vars->motionTimer=func_002A7820(lo,hi);
            } else {
                ratio=IntToFloat(vars->motionTimer)/(vars->riseTime*60.0f);
                wave=func_00283180(ratio*3.141593f);
                half=0.5f;
                moby->position.f[2]=vars->baseZ+vars->rise*(wave*half)+vars->rise*half;
            } break;
        case 3:
            if (func_00282948(&vars->motionTimer)) { vars->motionTimer=FloatToInt(vars->fallTime*60.0f); vars->motionState=4; }
            moby->position.f[2]=vars->baseZ+vars->rise; break;
        case 4:
            if (func_00282948(&vars->motionTimer)) {
                moby->position.f[2]=vars->baseZ; vars->motionState=1;
                lo=FloatToInt(vars->minWait*60.0f); hi=FloatToInt(vars->maxWait*60.0f);
                vars->motionTimer=func_002A7820(lo,hi);
            } else {
                ratio=IntToFloat(vars->motionTimer)/(vars->fallTime*60.0f);
                wave=func_00283180((1.0f-ratio)*3.141593f);
                half=0.5f;
                moby->position.f[2]=vars->baseZ+vars->rise*(wave*half)+vars->rise*half;
            } break;
        }
    } else moby->position.f[2]=vars->baseZ;
    func_002AEE70(moby,&vars->bobPhase,&vars->bobOffset,bob,360.0f/D_L17_001B0260*0.00029088825f,moby->position.f[2]);
    func_002AEF28(moby,&vars->swayPhase,&vars->tiltPhase,D_L17_001B026C,360.0f/D_L17_001B0270*0.00029088825f,360.0f/D_L17_001B0274*0.00029088825f);
    moby->rotation[2]=FastAddRotations(moby->rotation[2],vars->spin);
    qzero(&offset); offset.f[2]=D_L17_001B0290;
    matrix_mul_vec3(&offset,&offset,moby->matrix);
    add_vectors(&target,&offset,&moby->position);
    if (((CarrierVoice *)&D_00188660[vars->idleSound])->owner != moby || !((CarrierVoice *)&D_00188660[vars->idleSound])->active)
        vars->idleSound=PlayMobySound(2,4,moby);
    if (vars->platform == -1 || D_L17_001B2C1C[vars->platform].classId != 0x93B) return;
    func_L00_002E6CF0(DrawIndexedRibbonSegments,moby);
    if (vars->passenger == -1 || vars->path == -1 || vars->destination == -1) return;
    destination=&D_L17_001B2C1C[vars->destination]; destinationVars=destination->vars;
    platform=&D_L17_001B2C1C[vars->platform]; passenger=&D_L17_001B2C1C[vars->passenger];
    target.q=destination->position.q;
    target.f[2]+=D_L17_001B028C;
    bob=offset.f[2]-D_L17_001B0284;
    heightDelta=bob-target.f[2];
    platform->position.q=offset.q; platform->position.f[2]=bob;
    switch (moby->state) {
    case 1:
        if (vars->sound != -1 && ((CarrierVoice *)&D_00188660[vars->sound])->owner==moby && ((CarrierVoice *)&D_00188660[vars->sound])->active) func_002E59F8(vars->sound);
        vars->sound=-1;
        if (passenger->hit) { func_002A7750(moby,2,-1); vars->timer=FloatToInt(D_L17_001B0278*60.0f); }
        platform->position.f[2]=bob; vars->stopped=0; break;
    case 2:
        ratio=IntToFloat(vars->timer)/(D_L17_001B0278*60.0f);
        platform->position.f[2]=bob-heightDelta*func_00283198((1.0f-ratio)*1.5707965f);
        if (((CarrierVoice *)&D_00188660[vars->sound])->owner!=moby || !((CarrierVoice *)&D_00188660[vars->sound])->active) vars->sound=PlayMobySound(0,4,moby);
        STUB_printf(D_L17_001B02A0); vars->stopped=0;
        if (func_00282948(&vars->timer)) { func_002A7750(moby,3,-1); vars->timer=FloatToInt(D_L17_001B027C*60.0f); }
        break;
    case 3:
        if (func_002B3868(moby)) PlayMobySound(0,0,platform);
        platform->position.f[2]=bob-heightDelta; ready=0;
        if (func_L17_003C7C58(destination)) {
            if (vars->sound != -1 && ((CarrierVoice *)&D_00188660[vars->sound])->owner==moby && ((CarrierVoice *)&D_00188660[vars->sound])->active) func_002E59F8(vars->sound);
            vars->sound=-1;
        } else if (((CarrierVoice *)&D_00188660[vars->sound])->owner!=moby || !((CarrierVoice *)&D_00188660[vars->sound])->active) vars->sound=PlayMobySound(1,4,moby);
        if (vars->destination && destination->classId==0x935 && destinationVars) {
            if ((*(int *)((char *)destinationVars+0xAC)==2 || *(int *)((char *)destinationVars+0xA0)==-1) && *(int *)((char *)destinationVars+0xBC)!=3) {
                ready=1; platform->position.q=target.q; vars->timer=0;
            } else if (*(int *)((char *)destinationVars+0xAC)==1 && fast_vec_dist(&platform->position,&target)<1.0f) { vars->timer=0; ready=1; }
        }
        if (!ready && func_00282948(&vars->timer)) {
            if (vars->sound != -1 && ((CarrierVoice *)&D_00188660[vars->sound])->owner==moby && ((CarrierVoice *)&D_00188660[vars->sound])->active) func_002E59F8(vars->sound);
            vars->sound=-1; func_002A7750(moby,4,-1); func_002E5DA0(1,0,moby,0x93B); vars->timer=FloatToInt(D_L17_001B0280*60.0f);
        } break;
    case 4:
        ratio=IntToFloat(vars->timer)/(D_L17_001B0280*60.0f);
        platform->position.f[2]=bob-heightDelta*func_00283198(ratio*1.5707965f);
        passenger->hit=0;
        if (((CarrierVoice *)&D_00188660[vars->sound])->owner!=moby || !((CarrierVoice *)&D_00188660[vars->sound])->active) vars->sound=PlayMobySound(1,4,moby);
        STUB_printf(D_L17_001B02C0);
        if (func_00282948(&vars->timer)) func_002A7750(moby,1,-1);
        break;
    }
    distance=fast_vec_dist(&target,&platform->position);
    if (distance<D_L17_001B0288 && distance>0.01f) {
        blend=1.0f-distance/D_L17_001B0288;
        travelDistance=offset.f[2]-platform->position.f[2];
        angle=vec_distance_xy(&offset,&target);
        pitch=-func_00283248(angle,target.f[2]-offset.f[2]);
        pitch=1.5707965f-(1.5707965f-pitch)*blend;
        rotationPtr=&rotation;
        angle=func_00283248(target.f[0]-offset.f[0],target.f[1]-offset.f[1]);
        pitch=-pitch;
        func_002AF000(rotationPtr,travelDistance,angle,pitch);
        FastVecAdd(&result,&offset,rotationPtr);
        platform->position.q=result.q;
        platform->rotation[1]=FastAddRotations(pitch,1.5707965f);
        moby->rotation[1]=FastAddRotations(moby->rotation[1],platform->rotation[1]);
        D_L17_001B3670=moby->state; D_L17_001B3674=platform->state;
        if (vars->sound != -1 && ((CarrierVoice *)&D_00188660[vars->sound])->owner==moby && ((CarrierVoice *)&D_00188660[vars->sound])->active) func_002E59F8(vars->sound);
        vars->sound=-1;
    }
}
