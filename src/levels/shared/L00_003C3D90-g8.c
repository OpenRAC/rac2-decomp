#include "common.h"

/* func_L00_003C3D90: per-frame update of an electric-arc effect moby (both oclass 0xA5C and 0x1192):
   sound upkeep, colour fade, eight particle pairs, area damage, target locking and five ribbon arcs.
   Its own unit for -G8, -g (the nop pair before the ratio's div.s) and -frac2-mult-add-no-flatten (the
   ribbon point givs); flags in config/cflags.txt. */
extern int D_L00_001A8F00;
extern char D_00189EA0[];
extern char D_00188660[];
extern unsigned char D_00139568[];
typedef struct { char pad0[4]; unsigned char active; char pad5[0x6b]; float strength; char pad74[0x6c]; } WeaponEntry;
extern WeaponEntry D_L00_00262570[];
typedef struct { char pad[0xb4]; int changed; } ChangedState;
extern ChangedState D_00139868;
typedef struct { char pad0[0x80]; float position[4]; char pad90[0x11b0]; int upgrades; char pad1244[0x104c]; char *moby; char pad2294[0x28]; unsigned char busy; } HeroState;
extern HeroState D_00189E20_13;
extern char D_L00_001B8DC0[];
typedef struct { float v[4]; } __attribute__((aligned(16))) EffectVector;
extern EffectVector D_L00_00240080[][10];
extern EffectVector D_L00_00240080_1[][10];
extern int D_L00_001B2950[] MACRO_ADDR;
extern int D_L00_001B2970[] MACRO_ADDR;
/* Ribbon state, one short per ribbon in three parallel arrays (as upstream's L25 tether declares
   its D_L25_001B2948/2950/2958): respawn timer, fade and the timer's starting value. */
extern short D_L00_001B2990[] MACRO_ADDR;
extern short D_L00_001B29A0[] MACRO_ADDR;
extern short D_L00_001B29B0[] MACRO_ADDR;

typedef struct { char pad[0xf8]; unsigned char *f8; } ParticleDefs;
extern ParticleDefs D_L00_001FE940;
extern int D_L00_001AFF98 __attribute__((sda));
extern int D_L00_001AFF44 __attribute__((sda));
extern int D_L00_001AFF90 __attribute__((sda));
extern int D_L00_001AFF10 __attribute__((sda));
extern int D_L00_001AFF14 __attribute__((sda));
extern int D_L00_001AFF18 __attribute__((sda));
extern int D_L00_001AFF1C __attribute__((sda));
extern int D_L00_001AFF24 __attribute__((sda));
extern float D_L00_001AFF2C __attribute__((sda));
extern float D_L00_001AFF40 __attribute__((sda));
extern float D_L00_001AFF4C __attribute__((sda));
extern int D_L00_001AFF64 __attribute__((sda));
extern int D_L00_001AFF68 __attribute__((sda));
extern float D_L00_001AFF6C __attribute__((sda));
extern int D_L00_001AFF70 __attribute__((sda));
/* Ribbon spread: D_L00_001AFF7C in most levels, 0x001AFF80 in 00_aranos_tutorial. */
extern float ref_L00_003C3D90_00 __attribute__((sda));
extern void func_L00_0037E640(void);
extern int func_002E59B0(void *,int);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern int func_L00_003C3A70(int);
extern float func_L00_0037E668(void);
extern int func_L00_003C5B18(float);
extern void func_L00_0037E698(void);
extern void func_0029F338(void *);
extern float func_00282C48(float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_00283D38(float,int,int);
extern int func_00282978(void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_0029FCC0(void *,int,void *);
extern int func_002A7820(int,int);
extern float func_002A7940(void);
extern void func_002AF000(void *,float,float,float);
extern char *func_002C36D0(void *,int,int,int);
extern int func_00282948(void *);
extern int func_002829D8(void *);
extern int func_00277F48(void *,int,void *,int,float);
extern float *func_002AB1F0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_002A8E20(void *,void *);
extern void func_L00_003C58E8(void *,int);
extern char *func_L00_00412FF8(void *,int);
extern void func_002A7988(void *,float,float);
extern float func_002A7878(float,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_L00_002E6CF0(void *,void *);
extern void func_L00_003C4850(void *);
typedef struct { char pad0[0x46]; short category; } MobyInfo;
typedef struct EffectContext EffectContext;
typedef struct Moby { char pad0[0x10]; float x,y,z,w; unsigned char state; char pad21[3]; MobyInfo *info; char pad28[9]; unsigned char enabled; char pad32[0x68-0x32]; EffectContext *ctx; char pad6c[0xaa-0x6c]; short oclass; char padac[0xe0-0xac]; float forward[4]; } Moby;
typedef struct { char pad0[4]; Moby *moby; char pad8[8]; float dx,dy,dz; } ParticleOwner;
typedef struct { char pad0[2]; unsigned char sprite; char pad3; int colour; char pad8[4]; float size; float x,y,z; char pad1c[4]; ParticleOwner owner; char pad3c[0xb8-0x3c]; Moby *source; } Particle;
typedef struct { float x,y,z; float damage; Moby *source; int flags; unsigned char kind; unsigned char mode; short oclass; float strength; int one; char pad24[0xc]; } HitPacket;
struct EffectContext { float value; short timer; short pad6; int colour; int sound; float cooldown; int lock; short timers[4]; Moby *targets[4]; };
extern Moby *D_L00_001C3280[];
/* A sound slot as src/game/002B6120-sound-g8.c views it: D_00188660 + slot * 0x70. */
typedef struct { char pad0[0x74]; unsigned char active; char pad75[0x13]; Moby *object; } SoundAnchor;
static __inline__ void clearSound(Moby *self,EffectContext *ctx)
{
    int id=ctx->sound;
    if(id!=-1) {
        SoundAnchor *sound=(SoundAnchor *)(gSoundState+id*0x70);
        if(sound->object==self && sound->active)
            StopSoundVoice(id);
    }
    ctx->sound=-1;
}
void func_L00_003C3D90(Moby *self)
{
    float offset[4],origin[4],position[4];
    EffectContext *ctx=self->ctx;
    float value,ratio,sign;
    int i,j,k,slot;
    if(D_L00_001A8F00) return;
    qcopy(&self->x,gHeroPosition);
    TickFadeTimer();
    if(!D_L00_001A8F00) {
        if(!IsVoicePlayingForOwner(self,ctx->sound))
            ctx->sound=PlayMobySound(3,4,self);
    } else if(IsVoicePlayingForOwner(self,ctx->sound)) clearSound(self,ctx);
    if(gWeaponTable_L00[gItemSlotToRecord[0x2d]].active && self->oclass==0xa5c /* Shield Charger */ ) {
        int saved=D_L00_001AFF98;
        D_L00_001AFF98=0;
        if(CreateTrailOwnerMoby(1)) {
            clearSound(self,ctx);
            PlayMobySound(2,0,self);
            D_L00_001AFF98=0;
            MarkMobySpawned(self);
            return;
        }
        D_L00_001AFF98=saved;
    }
    value=GetFadeValue();
    if(!CanUseHeldWeapon(value) || D_L00_001AFF44==40) {
        clearSound(self,ctx);
        D_L00_001AFF44=0;
        ResetFadeLevel();
        PlayMobySound(2,0,self);
        D_L00_001AFF98=0;
        MarkMobySpawned(self);
        return;
    }
    if(value!=ctx->value) {
        D_00139868.changed+=FloatToInt(FloatAbs(ctx->value-value));
        ctx->value=value;
        ctx->timer=D_L00_001AFF90;
    }
    ratio=IntToFloat(ctx->timer)/IntToFloat(D_L00_001AFF90);
    if(self->oclass==0xa5c /* Shield Charger */ ) ctx->colour=FastTweenColor(ratio,D_L00_001AFF10,D_L00_001AFF14);
    else ctx->colour=FastTweenColor(ratio,D_L00_001AFF18,D_L00_001AFF1C);
    FastDecTimer(&ctx->timer);
    FastVecScale(offset,D_00189E20_13.moby+0xe0,0.75f);
    FastVecAdd(&self->x,D_00189E20_13.position,offset);
    TransformMobyJointToWorld(D_00189E20_13.moby,10,origin);
    for(i=0;i<8;i++) {
        if(!D_L00_001B2950[i]) {
            Particle *effect;
            int id=RandomIntRange(D_L00_001AFF64,D_L00_001AFF68);
            value=RandomAngle();
            ratio=RandomAngle();
            BuildSphericalOffset(position,D_L00_001AFF4C,value,ratio);
            FastVecAdd(position,position,origin);
            effect=(Particle *)(D_L00_001B2950[i]=(int)SpawnBluishFadeParticle(position,id,2,1));
            if(effect) {
                ParticleOwner *sub=&effect->owner;
                sub->dx=effect->x-self->x;
                sub->dy=effect->y-self->y;
                sub->dz=effect->z-self->z;
                sub->moby=self;
                effect->colour=D_L00_001AFF70|ctx->colour;
                effect->size=D_L00_001AFF6C*210000.0f;
                effect->sprite=D_L00_001FE940.f8[1];
                D_L00_001B2970[i]=id;
            }
            effect=(Particle *)SpawnBluishFadeParticle(position,id,2,1);
            if(effect) {
                ParticleOwner *sub=&effect->owner;
                sub->dx=effect->x-self->x;
                sub->dy=effect->y-self->y;
                sub->dz=effect->z-self->z;
                sub->moby=self;
                effect->colour=0x307f7f7f;
                effect->size=D_L00_001AFF6C*63000.00390625f;
                effect->sprite=D_L00_001FE940.f8[1];
            }
        } else if(FastFloatHelperD(D_L00_001B2970+i)) D_L00_001B2950[i]=0;
    }
    slot=0;
    FastFloatHelperD(&ctx->lock);
    {
    int t;
    for(t=0;t<4;t++) if(FastDecTimer(&ctx->timers[t])) {
        ctx->targets[t]=0;
        slot=t;
    }
    }
    if(FastVectorHelperB(&ctx->cooldown)) {
        int count=ProcessCollisionHit(&self->x,1,D_00189E20_13.moby,0,D_L00_001AFF2C*0.3f);
        if(count) {
            HitPacket packet;
            float scaled[4],output[4];
            int p;
            WeaponEntry *weapon=&gWeaponTable_L00[gItemSlotToRecord[0x2d]];
            packet.flags=65536;
            packet.one=1;
            packet.damage=5627.9248046875f;
            packet.kind=3;
            packet.strength=weapon->strength;
            packet.mode=2;
            packet.oclass=self->oclass;
            packet.source=self;
            for(p=0;p<count;p++) {
                Moby *object=gAreaHitTargets[p];
                float *health=0;
                if(!object->enabled || !object || object->state==0xfe || object->state==0xfd || !object->info || object->info->category!=5) continue;
                health=GetMobyPrivateValue0(object);
                if(health) {
                    if(health[0]<=0) continue;
                    FastVecScale(scaled,self->forward,health[4]);
                    FastVecAdd(position,&object->x,scaled);
                } else qcopy(position,&object->x);
                FastVecSub(&packet,position,&self->x);
                vec_scale_to_length(&packet,&packet,1.0f);
                QueueMobyImpact(object,&packet);
                FastVecScale(scaled,&packet,D_L00_001AFF2C*0.3f);
                FastVecAdd(output,&self->x,scaled);
                SpawnSparkPairs_L00(output,ctx->colour);
                ctx->cooldown=0.5f;
            }
        }
    }
    if(!D_L00_001A8F00 && slot && self->oclass==0x1192 /* Tesla Barrier */  && !ctx->lock && !D_00189E20_13.busy && D_00189E20_13.upgrades>=23) {
        int hits=ProcessCollisionHit(&self->x,1,D_00189E20_13.moby,0,D_L00_001AFF40);
        if(hits) for(j=0;j<hits;j++) {
            float *health=0;
            int freeSlot;
            if(!gAreaHitTargets[j]->enabled || !gAreaHitTargets[j] || gAreaHitTargets[j]->state==0xfe || gAreaHitTargets[j]->state==0xfd || !gAreaHitTargets[j]->info || gAreaHitTargets[j]->info->category!=5) continue;
            health=GetMobyPrivateValue0(gAreaHitTargets[j]);
            if(health && health[0]<=0) continue;
            freeSlot=-1;
            /* ctx->targets[k] through the byte offset k << 2: retail forms ctx + (k << 2) first. */
            for(k=0;k<4 && gAreaHitTargets[j]!=((Moby **)((char *)ctx+(k<<2)))[8];k++) {
                if(!((Moby **)((char *)ctx+(k<<2)))[8]) freeSlot=k;
            }
            if(k==4) {
                Particle *effect;
                Moby *object;
                if(freeSlot<0) break;
                object=gAreaHitTargets[j];
                ((Moby **)((char *)ctx+(freeSlot<<2)))[8]=object;
                effect=(Particle *)SpawnLightningArcMoby(object,D_L00_001AFF24);
                if(effect) {
                    effect->source=self;
                    D_L00_001AFF44++;
                    PlayMobySound(5,0,self);
                    ctx->timers[slot]=RandomIntRange(20,60);
                }
                break;
            }
        }
    }
    qcopy(position,origin);
    {
    int r;
    for(r=0;r<5;r++) {
        if(FastDecTimer(&D_L00_001B2990[r])) D_L00_001B2990[r]=0;
        if(!D_L00_001B2990[r]) {
            float velocity[4],scaled[4];
            int id=RandomIntRange(3,45);
            D_L00_001B2990[r]=id;
            D_L00_001B29B0[r]=id;
            D_L00_001B29A0[r]=64;
            SpawnRandomDirectionEffect(velocity,ref_L00_003C3D90_00,ref_L00_003C3D90_00);
            qcopy(D_L00_00240080[r],position);
            D_L00_00240080[r]->v[3]=0.04f;
            sign=1.0f;
            {
            int n;
            for(n=1;n<10;n++) {
                float width=0.04f;
                FastVecSub(scaled,D_L00_00240080_1[r][n-1].v,gCameraPosition_L00);
                ApplyAxisRotationToQuaternion(velocity,velocity,scaled,RandomFloatRange(0.0872664749622345f,1.3089970350265503f)*sign);
                sign=-sign;
                FastVecAdd(D_L00_00240080[r][n].v,D_L00_00240080_1[r][n-1].v,velocity);
                D_L00_00240080[r][n].v[3]=width;
            }
            }
        }
    }
    }
    AddDrawCallbackToList1(UpdateTrailEffectDraw,self);
}
