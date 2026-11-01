/* Closer b, 2026-11-01, on item 5: retail keeps three values: the madd for the first .w store, a separate mult, and
 * D + mult from loop.c's giv init (the `daddu v1, v0` is cse2 merging two givs' inits). So `.w`'s giv in retail does not
 * start from the madd. Eleven forms of the store (row[n], [r][n], cast and pointer views, no row local) give 56 lines or
 * worse; forms that name D_L00_00240080 fold 12 into the symbol (2760). Item 1 is one if/else over both arguments. */
/* Tier: opus-1 (v1898), USA v1.01; best 2752/2752 bytes, 0/27 places; 650 of 688 instructions
 * align with retail once relocations are masked. Replaces sol-high's 2708-byte draft.
 * Unit: src/levels/shared/L00_003C3D90-g8.c, profile -O2 -G8 -ffunction-sections -g -frac2-hazard-labels.
 * All declarations it needs are below.
 *
 * What settled the structure (each measured here, keep these):
 * - Tables 2950/2970/2990/00240080 are incomplete `sda` arrays: tied lui/addiu macro, no %hi hoist,
 *   so sched2 can move them across calls (retail's s4, s7, s1 before the calls).
 * - The three short tables are ONE array, D_L00_001B2990[][8]: same base keeps the store order.
 * - Every loop counter is its own scoped variable; sharing i/j wrecks global allocation.
 * - Typed struct views (Particle, HitPacket, Moby) are needed: mem/s stores let the $gp scalar loads
 *   schedule past them, which fixed both spawn blocks with no helper locals.
 * - `weapon` pointer, `spread` and `fade` locals, chained slot store, `object` local in the
 *   acquisition block, and two ternaries on `col1` (the only form whose insn count gives gcse's
 *   hash order, hence retail's spill slots 0x84..0x94).
 * - Reload registers are round-robin (allocate_reload_reg), so an early extra reload shifts every
 *   later v0/v1/a0/a1 choice; do not chase those one by one.
 *
 * What still differs:
 * 1. C4020/C402C: retail `bnel` then `b`; here `bne` then `bnel`. The second test is not threaded.
 *    A gp load does not trap (retail fills non-annulled at C40CC), so a0 looks live on the
 *    fall-through at reorg, perhaps an update_block USE. An if/else gives `bne`/`b` but loses the
 *    spill slot order.
 * 2. C4040: retail `sw v0,8(s3); jal; addiu a0,s3,4`; here the two are swapped. C4058: the 0x10(s3)
 *    address is computed before the call in retail, after it here.
 * 3. C45C8: retail fills the beq slot with `daddu a1,zero`; here `addiu a0,s3,0x20` fills it.
 * 4. C4618: retail `addu v0,s3,v0`; every form tried gives `addu v0,v0,s3`. Natural
 *    ctx->targets[slot] folds (ctx+0x20) into a register instead (expand_assignment alignment test).
 * 5. C4720-C4784, ribbon preheader: retail has `v0 = D + i*160; v1 = v0; s2 = v0+0x1C; s1 = v1+0x10`
 *    with first .w through a separate madd. Here `row` merges with that madd in cse. The inner loop
 *    bottom already matches. The giv must add (reg)+12 without folding 12 into the symbol or being
 *    combined with [n]'s giv. Tried: D[r][n].w, (D[r]+n)->w, ((float *)&D[r][n])[3], in-loop row,
 *    temporary v/w pointers, _1 alias for the first store.
 * 6. C46C4 onward: the a0/v1/a1 swaps look like the round-robin consequence of the above.
 * 54 compiles. Next: items 1 and 5 first; they change insn counts and so the hash order.
 */
#include "common.h"
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
extern char D_L00_0023F040[];
typedef struct { float v[4]; } EffectVector;
extern EffectVector D_L00_00240080[][10] __attribute__((sda));
extern int D_L00_001B2950[] __attribute__((sda));
extern int D_L00_001B2970[] __attribute__((sda));
extern short D_L00_001B2990[][8] __attribute__((sda));

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
extern float D_L00_001AFF7C __attribute__((sda));
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
#define WORD(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
#define BYTE(p,o) (*(unsigned char *)((char *)(p)+(o)))
typedef struct { char pad0[0x46]; short category; } MobyInfo;
typedef struct EffectContext EffectContext;
typedef struct Moby { char pad0[0x10]; float x,y,z,w; unsigned char state; char pad21[3]; MobyInfo *info; char pad28[9]; unsigned char enabled; char pad32[0x68-0x32]; EffectContext *ctx; char pad6c[0xaa-0x6c]; short oclass; char padac[0xe0-0xac]; float forward[4]; } Moby;
typedef struct { char pad0[4]; Moby *moby; char pad8[8]; float dx,dy,dz; } ParticleOwner;
typedef struct { char pad0[2]; unsigned char sprite; char pad3; int colour; char pad8[4]; float size; float x,y,z; char pad1c[4]; ParticleOwner owner; char pad3c[0xb8-0x3c]; Moby *source; } Particle;
typedef struct { float x,y,z; float damage; Moby *source; int flags; unsigned char kind; unsigned char mode; short oclass; float strength; int one; char pad24[0xc]; } HitPacket;
struct EffectContext { float value; short timer; short pad6; int colour; int sound; float cooldown; int lock; short timers[4]; Moby *targets[4]; };
extern Moby *D_L00_001C3280[];
static __inline__ void clearSound(Moby *self,EffectContext *ctx)
{
    int id=ctx->sound;
    if(id!=-1) {
        char *sound=D_00188660+id*112;
        if(*(Moby **)(sound+0x88)==self && BYTE(sound,0x74))
            func_002E59F8(id);
    }
    ctx->sound=-1;
}
void func_L00_003C3D90(Moby *self)
{
    float offset[4],origin[4],position[4];
    EffectContext *ctx=self->ctx;
    float value,ratio,sign;
    int i,j,k,slot,col1,col2;
    if(D_L00_001A8F00) return;
    qcopy(&self->x,D_00189EA0);
    func_L00_0037E640();
    if(!D_L00_001A8F00) {
        if(!func_002E59B0(self,ctx->sound))
            ctx->sound=func_002E5CF8(3,4,self);
    } else if(func_002E59B0(self,ctx->sound)) clearSound(self,ctx);
    if(D_L00_00262570[D_00139568[0x2d]].active && self->oclass==0xa5c) {
        int saved=D_L00_001AFF98;
        D_L00_001AFF98=0;
        if(func_L00_003C3A70(1)) {
            clearSound(self,ctx);
            func_002E5CF8(2,0,self);
            D_L00_001AFF98=0;
            func_0029F338(self);
            return;
        }
        D_L00_001AFF98=saved;
    }
    value=func_L00_0037E668();
    if(!func_L00_003C5B18(value) || D_L00_001AFF44==40) {
        clearSound(self,ctx);
        D_L00_001AFF44=0;
        func_L00_0037E698();
        func_002E5CF8(2,0,self);
        D_L00_001AFF98=0;
        func_0029F338(self);
        return;
    }
    if(value!=ctx->value) {
        D_00139868.changed+=func_00283CF0(func_00282C48(ctx->value-value));
        ctx->value=value;
        ctx->timer=D_L00_001AFF90;
    }
    ratio=func_00283CE0(ctx->timer)/func_00283CE0(D_L00_001AFF90);
    col1=self->oclass;
    ctx->colour=func_00283D38(ratio,col1==0xa5c?D_L00_001AFF10:D_L00_001AFF18,col1==0xa5c?D_L00_001AFF14:D_L00_001AFF1C);
    func_00282978(&ctx->timer);
    func_00282D30(offset,D_00189E20_13.moby+0xe0,0.75f);
    func_00282CC0(&self->x,D_00189E20_13.position,offset);
    func_0029FCC0(D_00189E20_13.moby,10,origin);
    for(i=0;i<8;i++) {
        if(!D_L00_001B2950[i]) {
            Particle *effect;
            int id=func_002A7820(D_L00_001AFF64,D_L00_001AFF68);
            value=func_002A7940();
            ratio=func_002A7940();
            func_002AF000(position,D_L00_001AFF4C,value,ratio);
            func_00282CC0(position,position,origin);
            effect=(Particle *)(D_L00_001B2950[i]=(int)func_002C36D0(position,id,2,1));
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
            effect=(Particle *)func_002C36D0(position,id,2,1);
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
        } else if(func_00282948(D_L00_001B2970+i)) D_L00_001B2950[i]=0;
    }
    slot=0;
    func_00282948(&ctx->lock);
    {
    int t;
    for(t=0;t<4;t++) if(func_00282978(&ctx->timers[t])) {
        ctx->targets[t]=0;
        slot=t;
    }
    }
    if(func_002829D8(&ctx->cooldown)) {
        int count=func_00277F48(&self->x,1,D_00189E20_13.moby,0,D_L00_001AFF2C*0.3f);
        if(count) {
            HitPacket packet;
            float scaled[4],output[4];
            int p;
            WeaponEntry *weapon=&D_L00_00262570[D_00139568[0x2d]];
            packet.flags=65536;
            packet.one=1;
            packet.damage=5627.9248046875f;
            packet.kind=3;
            packet.strength=weapon->strength;
            packet.mode=2;
            packet.oclass=self->oclass;
            packet.source=self;
            for(p=0;p<count;p++) {
                Moby *object=D_L00_001C3280[p];
                float *health;
                if(!object->enabled || !object || object->state==0xfe || object->state==0xfd || !object->info || object->info->category!=5) continue;
                health=func_002AB1F0(object);
                if(health) {
                    if(health[0]<=0) continue;
                    func_00282D30(scaled,self->forward,health[4]);
                    func_00282CC0(position,&object->x,scaled);
                } else qcopy(position,&object->x);
                func_00282CF0(&packet,position,&self->x);
                func_00282F20(&packet,&packet,1.0f);
                func_002A8E20(object,&packet);
                func_00282D30(scaled,&packet,D_L00_001AFF2C*0.3f);
                func_00282CC0(output,&self->x,scaled);
                func_L00_003C58E8(output,ctx->colour);
                ctx->cooldown=0.5f;
            }
        }
    }
    if(!D_L00_001A8F00 && slot && self->oclass==0x1192 && !ctx->lock && !D_00189E20_13.busy && D_00189E20_13.upgrades>=23) {
        int hits=func_00277F48(&self->x,1,D_00189E20_13.moby,0,D_L00_001AFF40);
        if(hits) for(j=0;j<hits;j++) {
            float *health;
            int freeSlot;
            if(!D_L00_001C3280[j]->enabled || !D_L00_001C3280[j] || D_L00_001C3280[j]->state==0xfe || D_L00_001C3280[j]->state==0xfd || !D_L00_001C3280[j]->info || D_L00_001C3280[j]->info->category!=5) continue;
            health=func_002AB1F0(D_L00_001C3280[j]);
            if(health && health[0]<=0) continue;
            freeSlot=-1;
            for(k=0;k<4;k++) {
                if(D_L00_001C3280[j]==ctx->targets[k]) break;
                if(!ctx->targets[k]) freeSlot=k;
            }
            if(k==4) {
                Particle *effect;
                Moby *object;
                if(freeSlot<0) break;
                object=D_L00_001C3280[j];
                ((Moby **)ctx)[freeSlot+8]=object;
                effect=(Particle *)func_L00_00412FF8(object,D_L00_001AFF24);
                if(effect) {
                    effect->source=self;
                    D_L00_001AFF44++;
                    func_002E5CF8(5,0,self);
                    ctx->timers[slot]=func_002A7820(20,60);
                }
                break;
            }
        }
    }
    qcopy(position,origin);
    {
    int r;
    for(r=0;r<5;r++) {
        if(func_00282978(&D_L00_001B2990[0][r])) D_L00_001B2990[0][r]=0;
        if(!D_L00_001B2990[0][r]) {
            float velocity[4],scaled[4];
            int id=func_002A7820(3,45);
            float spread=D_L00_001AFF7C;
            int fade;
            D_L00_001B2990[2][r]=id;
            fade=64;
            D_L00_001B2990[1][r]=fade;
            D_L00_001B2990[0][r]=id;
            func_002A7988(velocity,spread,spread);
            qcopy(D_L00_00240080[r],position);
            D_L00_00240080[r]->v[3]=0.04f;
            sign=1.0f;
            {
            int n;
            EffectVector *row=D_L00_00240080[r];
            for(n=1;n<10;n++) {
                func_00282CF0(scaled,D_L00_00240080[r][n-1].v,D_L00_001B8DC0);
                func_002ACEC0(velocity,velocity,scaled,func_002A7878(0.0872664749622345f,1.3089970350265503f)*sign);
                sign=-sign;
                func_00282CC0(D_L00_00240080[r][n].v,D_L00_00240080[r][n-1].v,velocity);
                row[n].v[3]=0.04f;
            }
            }
        }
    }
    }
    func_L00_002E6CF0(func_L00_003C4850,self);
}
