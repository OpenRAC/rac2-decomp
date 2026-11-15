#include "common.h"
typedef union { unsigned int q __attribute__((mode(TI))); struct { float x,y,z,w; } f; } V413;
typedef struct {
    V413 velocity;
    int charge, age;
    char pad18[0x14];
    short light, triggered;
    V413 orientation;
    short kind, pad42;
    int override;
    char pad48[8];
    V413 direction;
} State413;
typedef struct { float inner, outer; char pad[8]; V413 position; } Light413;
typedef struct { char pad[0x98]; float angle; char gap[0x21F4]; int owner; char gap2[0x20]; unsigned char mode; } Player413;
extern Player413 D_00189E20;
extern int D_L22_001B1564 __attribute__((sda)), D_L22_001B1568 __attribute__((sda));
extern int D_L22_001B155C __attribute__((sda)), D_L22_001B1560 __attribute__((sda));
extern float D_L22_001B1544 __attribute__((sda)), D_L22_001B1548 __attribute__((sda));
extern int D_L22_001A8FF0 MACRO_ADDR;
typedef struct { int enabled; unsigned int color; unsigned long long counter; } ChargeFx413;
extern ChargeFx413 D_L22_001A8AC0[] __attribute__((sda));
extern int D_L22_001A8AB0;
extern int D_L22_001B1C48;
extern float D_L22_001A93E4;
extern char D_L22_001C4140[];
/* sda: one la macro per use, so its address is not kept across the loop. */
extern char D_L22_001A8F20[] __attribute__((sda));
/* Unsized view: read through a separate lui rather than the small-data lw macro. */
extern unsigned char *D_L22_001FF82C[];
extern Light413 D_L22_001C7E00[];
extern float func_00283CE0(int), func_002A7878(float,float), func_00283180(float), func_00283198(float);
extern int func_00283CF0(float), func_002A7820(int,int), func_002A77E0(int);
extern void func_00282F20(void*,void*,float), func_00282CD8(void*,void*,void*);
extern void func_L22_003398B8(int,void*,void*);
extern void func_L22_00334F78(void*,int,int,int,int,float,float);
extern short func_00291308(void*,int,float,float);
extern int func_L00_0035F5A0(int,int,int);
extern void func_002E59F8(int), func_00291450(int), func_0029F338(int);
extern void func_00282D30(void*,void*,float),func_002AFFD8(void*,void*,int),func_L00_00325600(void*,void*,int);
extern void func_00282DD8(void*,void*,void*),func_00283958(void*,void*),func_00283738(void*,void*,void*);
extern float func_00282DF0(void*),func_00282C10(float);
extern int func_00277F48(void*,int,void*,int,float);
extern void func_002A9850(void*,void*,void*,int,int,int,int,int,float,float,float);
extern void func_0032C700(void*,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void func_L04_00358868(void*,int,int,int,float),func_002A7988(void*,float,float);
extern void func_002BCB00(void*,void*,int,int,int,int,int,int,int,float);
extern char *func_L08_0034A078(void*,void*,int,void*);

/* Updates the charge-up shot: while charged it gathers sparks and a glow, then fires and flies forward, hitting things and spawning light and sparkles until it expires. */
void func_L22_00413B70(unsigned char *obj)
{
    struct { V413 velocity, random, position, scaled, matrix[3], rotation, normalized, temp; } frame;
    State413 *state;
    int *handle = &D_L22_001B1568;
    int i, j, hit, color;
    float radius, spread, fade, factor;
    char *particle, *sub;
    if (*(int *)(obj+0xB8) == gHeroState.owner) handle=&D_L22_001B1564;
    state = *(State413 **)(obj+0x68);
    switch (obj[0x20]) {
    case 0: {
        float charge;
        if (state->triggered && (gHeroState.mode==2 || !state->kind)) {
            if (!state->charge && handle==&D_L22_001B1568) {
                D_L22_001A8AC0[0].enabled=1;
                D_L22_001A8AC0[0].color=0xFFFF00;
            }
            charge=IntToFloat(++state->charge)*0.033333335f;
            if (charge>1.0f) charge=1.0f;
            charge *= charge * (state->kind ? 10.0f : 5.0f);
            for (j=0;j<FloatToInt(charge);j++) {
                int loop_r,loop_g,loop_b;
                frame.random.q=0;
                frame.random.f.x=RandomFloatRange(-1.0f,1.0f);
                frame.random.f.y=RandomFloatRange(-1.0f,1.0f);
                frame.random.f.z=RandomFloatRange(-1.0f,1.0f);
                frame.velocity.q=frame.random.q;
                if (state->kind) { loop_r=0x4F;loop_g=0xAF;loop_b=0xFF; }
                else { loop_r=0x6F;loop_g=0x1F;loop_b=0xF; }
                loop_g=RandomIntRange(loop_r,loop_g);
                loop_b=RandomIntRange(loop_r,loop_b);
                if (loop_b>255) loop_b=255;
                if (loop_g>255) loop_g=255;
                vec_scale_to_length(&frame.velocity,&frame.velocity,RandomFloatRange(15.0f,30.0f));
                add_vectors(&frame.random,&frame.velocity,obj+0x10);
                {
                    int high=(loop_g<<8)|0x7F000000;
                    SpawnHomingTrailEffect((loop_b<<16)|high|loop_r,&frame.velocity,obj);
                }
            }
            if (state->charge<50) {
                int alpha=D_L22_001A8AC0[0].color>>24;
                if (!D_L22_001A8AC0[0].counter && alpha==255) alpha=37;
                if (alpha<36) alpha++; else alpha=37;
                D_L22_001A8AC0[0].counter=0x1F00000042ULL;
                D_L22_001A8AC0[0].color=(D_L22_001A8AC0[0].color&0xFFFF00)|(alpha<<24);
            } else D_L22_001A8AC0[0].color |= 0xFF000000;
            if (state->light != -1) {
                float light_charge;
                float inner, outer;
                D_L22_001C7E00[state->light].position.f.x=*(float *)(obj+0x10);
                D_L22_001C7E00[state->light].position.f.y=*(float *)(obj+0x14);
                D_L22_001C7E00[state->light].position.f.z=*(float *)(obj+0x18);
                { int n=state->charge;
                if (n>50) n=50;
                if (n<0) n=0;
                D_L22_001C7E00[state->light].position.f.w=IntToFloat(n)*0.14f; }
                light_charge=IntToFloat(state->charge)*0.033333335f;
                if (light_charge>1) light_charge=1;
                SpawnGlowEffectRecord(&D_L22_001C7E00[state->light].position,
                    RandomIntRange(15,47)&255,RandomIntRange(47,63)&255,RandomIntRange(63,127)&255,20,light_charge*840000.0f,0.0f);
                D_L22_001C7E00[state->light].inner=RandomFloatRange(D_L22_001C7E00[state->light].inner*0.8f,
                    (D_L22_001C7E00[state->light].position.f.w+D_L22_001C7E00[state->light].position.f.w)*0.14285715f);
                outer=D_L22_001C7E00[state->light].outer*0.8f;
                inner=D_L22_001C7E00[state->light].inner;
                D_L22_001C7E00[state->light].outer=RandomFloatRange(inner < outer ? inner : outer,inner);
            } else if (!(D_L22_001B1C48&3)) {
                state->light=AddPointLight(obj+0x10,0,0.0f,0.0f);
            }
        } else {
            D_L22_001A8AB0=0;
            D_L22_001A8AC0[0].enabled=0;
            state->charge=0;
            StartEffectInSlot(22,0,0);
            if (state->kind) {
                if (D_L22_001B155C != -1) {
                    StopSoundVoice(D_L22_001B155C);
                    D_L22_001B155C=StartEffectInSlot(21,0,0);
                }
            } else if (D_L22_001B1560 != -1) {
                StopSoundVoice(D_L22_001B1560);
                D_L22_001B1560=StartEffectInSlot(21,0,0);
            }
            if (!D_L22_001A8FF0) {
                state->velocity.f.x=FastSinOrCosA(gHeroState.angle)*0.6666667f;
                state->velocity.f.y=FastSinOrCosB(gHeroState.angle)*0.6666667f;
                state->velocity.f.z=0;
                obj[0x20]=1;
                state->age=0;
            } else {
                FastVecScale(state,obj+0xC0,2.0f);
                obj[0x20]=1;
                state->age=0;
            }
        }
    break;
    }
    case 1: {
        float extra = 3.5f;
        radius=IntToFloat(state->age)*0.33333334f+1.3f;
        ++state->age;
        ComputeViewDirection(obj+0x10,&frame.position,1);
        spread=radius+extra;
        if (state->kind) vec_scale_to_length(&frame.scaled,obj+0xC0,2.0f);
        else vec_scale_to_length(&frame.scaled,obj+0xC0,extra);
        vec_scale_to_length(&frame.normalized,&frame.position,1.0f);
        FastVecCross(&frame.rotation,obj+0xE0,&frame.normalized);
        if (state->kind) factor=D_L22_001B1548; else factor=D_L22_001B1544;
        FastVecScale(&frame.rotation,&frame.rotation,factor);
        fade=FastVecLength(&frame.rotation);
        frame.rotation.f.w=-square_root(1.0f-fade*fade);
        quaternion_to_rotation_basis(&frame.rotation,frame.matrix);
        multiply_matrix3x3(obj+0xC0,frame.matrix,obj+0xC0);
        if (state->override) {
            if (state->kind) FastVecScale(&frame.scaled,&state->direction,0.6666667f);
            else FastVecScale(&frame.scaled,&state->direction,1.0f);
            vec_scale_to_length(&frame.temp,&frame.scaled,1.0f);
            qcopy(obj+0xC0, &frame.temp);
        }
        state->velocity.q=frame.scaled.q;
        if (state->light!=-1) {
            Light413 *lights = D_L22_001C7E00;
            lights[state->light].position.f.w *= 0.39999998f;
            if (lights[state->light].position.f.w<0.0001f) {
                FreePointLight(state->light);
                state->light=-1;
            }
        }
        if (state->age>=51 || gHeroState.mode!=2) {
            if (*(int *)(obj+0xB8)==gHeroState.owner) {
                if(D_L22_001B155C!=-1) {StopSoundVoice(D_L22_001B155C);D_L22_001B155C=-1;}
            } else if(D_L22_001B1560!=-1) {StopSoundVoice(D_L22_001B1560);D_L22_001B1560=-1;}
            MarkMobySpawned(*handle);
            *handle=0;
            return;
        } else {
            add_vectors(&frame.position,obj+0x10,state);
            if (*(float *)(obj+0x10)<2 || *(float *)(obj+0x10)>1021 ||
                *(float *)(obj+0x14)<2 || *(float *)(obj+0x14)>1021 ||
                *(float *)(obj+0x18)<2 || *(float *)(obj+0x18)>1021) {
                if (*(int *)(obj+0xB8)==gHeroState.owner) {
                    if(D_L22_001B155C!=-1) {StopSoundVoice(D_L22_001B155C);D_L22_001B155C=-1;}
                } else if(D_L22_001B1560!=-1) {StopSoundVoice(D_L22_001B1560);D_L22_001B1560=-1;}
                MarkMobySpawned(*handle);
                *handle=0;
                return;
            } else if (state->kind) {
                hit=ProcessCollisionHit(obj+0x10,16,obj,0,radius);
                frame.position.q=((V413 *)(obj+0x10))->q;
                QueueKnockbackForNodes(obj,&frame.position,D_L22_001C4140,hit,0,0x8B0000,2,1,D_L22_001A93E4,1.0f,1.0f);
                if (hit) SpawnExplosion(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1.0f,20.0f);
                {
                /* Block scopes keep these local to one basic block, as retail allocates them. */
                float effect=spread*105000.0f, diameter;
                int count=50-state->age;
                if(count>5) count=5;
                diameter=spread+spread;
                {
                int b=RandomIntRange(63,127);
                int g=RandomIntRange(47,63);
                int r=RandomIntRange(15,47);
                int high=(g<<8)|0x4F000000;
                SpawnJointFollowParticle(obj,(b<<16)|high|r,count,-1,effect);
                }
                SpawnRandomDirectionEffect(&frame.velocity,spread*0.016666668f,diameter*0.016666668f);
                {
                int b=RandomIntRange(63,127);
                int g=RandomIntRange(47,63);
                int r=RandomIntRange(15,47);
                int high=(g<<8)|0x7F000000;
                SpawnSparkParticle_002BCB00(obj+0x10,&frame.velocity,(b<<16)|high|r,0x4F7F4F2F,45,1,*D_L22_001FF82C[0],-1,0,210000.0f);
                }
                }
                i=5;
                do {
                    SpawnRandomDirectionEffect(&frame.velocity,spread*0.016666668f,(spread+spread)*0.016666668f);
                    SpawnRandomDirectionEffect(&frame.random,0.0f,spread*0.5f);
                    add_vectors(&frame.position,&frame.random,obj+0x10);
                    particle=SpawnShortLivedParticle(&frame.random,&frame.velocity,127,obj);
                    /* reorg merges the two decrements into the test's delay slot. */
                    if(particle) {
                        *(float *)(particle+12)=RandomFloatRange(6000,32000)*spread*0.4f;
                        --i;
                    } else --i;
                } while(i>=0);
                for(i=0;i<8;i++) {
                    particle=SpawnShortLivedParticle(obj+0x10,D_L22_001A8F20,127,obj);
                    if(particle) {
                        sub=particle+0x20;
                        if(i==2 && !RandomIntBelow(8)) *(float *)(particle+12)=180000;
                        else *(float *)(particle+12)=RandomFloatRange(80000,120000);
                        *(short *)(particle+10)=2;
                        *(float *)(particle+12)*=spread;
                        fade=IntToFloat(2);
                        color=0x7F7F7F;
                        *(short *)(sub+0x16)=3;
                        *(int *)(sub+0x18)=color;
                        *(float *)(sub+0x10)=1.0f/fade;
                    }
                }
            } else {
                hit=ProcessCollisionHit(obj+0x10,16,*(void **)(obj+0xB8),0,radius);
                frame.position.q=((V413 *)(obj+0x10))->q;
                QueueKnockbackForNodes(obj,&frame.position,D_L22_001C4140,hit,0,0x8B0007,2,1,D_L22_001A93E4,1,1);
                if(hit) SpawnExplosion(obj+0x10,0,25,20,20,20,45,1,1,0,0,0,1,20);
                {
                float effect=spread*105000.0f;
                int count=50-state->age;
                if(count>5)count=5;
                {
                int r=RandomIntRange(15,47);
                int g=RandomIntRange(47,63);
                int b=RandomIntRange(63,127);
                int high=(g<<8)|0x4F000000;
                SpawnJointFollowParticle(obj,(r<<16)|high|b,count,-1,effect);
                }
                }
                SpawnRandomDirectionEffect(&frame.velocity,spread*0.016666668f,(spread+spread)*0.016666668f);
                {
                int r=RandomIntRange(15,47);
                int g=RandomIntRange(31,47);
                int b=RandomIntRange(63,127);
                int high=(g<<8)|0x7F000000;
                SpawnSparkParticle_002BCB00(obj+0x10,&frame.velocity,(r<<16)|high|b,0x4F1F1F7F,45,1,*D_L22_001FF82C[0],-1,0,210000);
                }
            }
        }
    }
    }
    if(D_L22_001A8FF0) {
        ComputeViewDirection(obj+0x10,&state->orientation,0);
        NegateAndForwardVector(obj+0xC0,&state->orientation,0);
    }
    state->triggered=0;
}
