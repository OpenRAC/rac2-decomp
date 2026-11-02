/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* sol-high, task v1240; USA v1.01, -O2 -G0 -ffunction-sections -g.
 * Best retained draft: 1700 bytes versus 1724 retail; 0 of 27 places match.
 * All required declarations are below. Tested in a dedicated source unit.
 *
 * Separate invalid-target branches and a shared clear_target label recover the
 * two 254/253 comparisons and the separate target-clear tail. The measured
 * small-data address view of the global velocity vector prevents an extra fp
 * save and restores its repeated lui/addiu address construction. A typed
 * collision result with a local pointer recovers retail's saved full base.
 * Splitting the speed load/call/store over source lines with -g retains the
 * pre-div.s nop. The frame and complete prologue now match retail.
 *
 * Remaining: the first collision arm shares the target/flags/lifetime stores
 * with the timeout arm, unlike retail's duplicated stores. Homing delta and
 * old-position addresses allocate to s1/s6 rather than s6/s7; particle-loop
 * angle/count/address registers and constant scheduling also differ. Effect
 * scale array base/index allocation differs. No linked build was run.
 *
 * New measurements: -fno-gcse with the split target branches is 1680 bytes
 * with a wrong 0xf0 frame; it still hoists the velocity address. Native TI
 * copies plus -frac2-qcopy gave 1720 bytes, but reintroduced fp and changed
 * copy scheduling; -frac2-qcopy-barrier returns to 1700 bytes. Concrete object
 * and state fields, canonical particle integer/FP argument interleaving,
 * keep-block-order, and an explicit collision-to-particles goto did not fix
 * the remaining store merge. Stop tied source permutations; investigate the
 * independently justified branch-tail and address-lifetime shape next.
 */
#include "common.h"
extern int func_002B4038(int,int);
extern void func_002AFFD8(void *,void *,int);
extern int func_L00_003E39B8(void *);
extern char *func_002AB1F0(void *);
extern void func_00282CF0_7(void *,void *,void *);
extern void func_00282CC0_7(void *,void *,void *);
extern void func_00282D30_7(void *,void *,float);
extern float func_00282DF0_7(void *);
extern void func_00282F20_7(void *,void *,float);
extern void func_002FEE70(int,void *,int);
extern void func_00300190(void *,void *);
extern float func_00283B98(float,float);
extern void func_L00_003E3890(void *);
extern int func_002761F8(void *,void *,int,int,void *);
extern void func_L00_003E3258(void *,int,int);
extern void func_00334160(void *,int,int);
extern void func_002E5CF8(int,int,void *);
extern int func_00282948(void *);
extern void func_L00_003E3668(void *);
extern int func_002A77E0(int);
extern char *func_002C65A0(void *,void *,int,int,int,int,int,float,float,float,int);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern void func_L00_002E6EF8(void *,void *);
extern void func_002FEE50(int);
extern void func_0029F338(void *);
extern unsigned char D_00139586 NOT_SDA;
typedef struct { char pad[112]; float scale; char rest[108]; } EffectScale;
extern EffectScale D_L00_00262570[];
extern int D_0018C0B0 NOT_SDA;
typedef struct { char pad[0x18]; char *moby; int pad1c; float point[4]; } MissileHit;
extern MissileHit D_L00_001BF200;
extern float D_L00_001A8F20[4] __attribute__((sda));
extern unsigned char *D_L00_001FEA14 NOT_SDA;
extern unsigned char *D_L00_001FE9F4 NOT_SDA;
extern int D_L00_001B19C8 NOT_SDA;
extern void func_L00_003E2BD0(void *);
#define EI(p,o) (*(int *)((p)+(o)))
#define EP(p,o) (*(char **)((p)+(o)))
#define EF(p,o) (*(float *)((p)+(o)))
#define EB(p,o) (*(unsigned char *)((p)+(o)))
#define EH(p,o) (*(unsigned short *)((p)+(o)))
typedef struct {
    char pad[0x14];
    int owner, active;
    char *target;
    float velocity[3], speed;
    int pad30, sound, lifetime;
    char pad3c[8];
    float rotation[3];
} MissileState;
void func_L00_003E2510(char *obj)
{
    float dir[4], old[4], delta[4], tmp[4];
    char hit[48] __attribute__((aligned(16)));
    float spawn[4];
    MissileState *state=*(MissileState **)(obj+0x68);
    char *r, *particle;
    float len,speed,size;
    int angle,i;
    if(!func_002B4038(state->active,state->owner)) return;
    func_002AFFD8(obj+0x10,dir,1);
    qcopy(old,obj+0x10);
    if(state->target) {
        if(EB(state->target,0x20)==254) goto clear_target;
        if(EB(state->target,0x20)==253) goto clear_target;
        if(func_L00_003E39B8(state->target)) goto clear_target;
        {
            func_00282CF0_7(delta,state->target+0x10,obj+0x10);
            r=func_002AB1F0(state->target);
            if(r) {func_00282D30_7(tmp,dir,EF(r,0x10));func_00282CC0_7(delta,delta,tmp);}
            len=func_00282DF0_7(delta);
            if(len!=0) {
                speed=state->speed;
                func_00282D30_7(state->velocity,delta,speed/len);
                state->speed=speed;
            }
            else state->target=0;
        }
        goto target_done;
clear_target:
        state->target=0;
    }
target_done:
    switch(EB(obj,0x20)) {
    case 0:
        func_002FEE70(state->sound,state->velocity,0);
        func_00282CC0_7(obj+0x10,obj+0x10,state->velocity);
        func_00300190(obj+0x10,obj+0x10);
        EF(obj,0xf0)=func_00283B98(EF(obj,0xf0),state->rotation[0]);
        EF(obj,0xf4)=func_00283B98(EF(obj,0xf4),state->rotation[1]);
        EF(obj,0xf8)=func_00283B98(EF(obj,0xf8),state->rotation[2]);
        func_L00_003E3890(obj);
        EI(hit,0x14)=0x10000;EP(hit,0x10)=obj;EI(hit,0x20)=1;
        EF(hit,0x1c)=D_L00_00262570[D_00139586].scale;
        qcopy(hit,state->velocity);func_00282F20_7(hit,hit,1);
        EF(hit,0xc)=5627.925f;EH(hit,0x1a)=EH(obj,0xaa);EB(hit,0x18)=1;EB(hit,0x19)=1;
        if(func_002761F8(old,obj+0x10,0,D_0018C0B0,hit)) {
            MissileHit *collision = &D_L00_001BF200;
            r=collision->moby;
            if(!r) func_L00_003E3258(collision->point,15,0);
            else if(EI(r,0x98)) {func_L00_003E3258(collision->point,10,1);func_00334160(collision->moby,30,EI(obj,0xb8));}
            func_002E5CF8(0,0,obj);
            EB(obj,0x20)=1;state->target=0;EH(obj,0x34)|=0x41;state->lifetime=6;
        } else if(func_00282948(&state->lifetime)) {
            func_L00_003E3668(obj+0x10);EB(obj,0x20)=1;state->target=0;EH(obj,0x34)|=0x41;state->lifetime=6;
        }
        angle=func_002A77E0(255);
        particle=func_002C65A0(obj+0x10,D_L00_001A8F20,2,0x202080,angle,64,16,420000,420000,0,1);
        if(particle) EB(particle,2)=*D_L00_001FEA14;
        particle=func_002C65A0(obj+0x10,D_L00_001A8F20,2,0x202080,(angle+128)%255,64,16,420000,420000,0,1);
        if(particle) EB(particle,2)=*D_L00_001FEA14;
        func_00282CF0_7(delta,obj+0x10,old);func_00282D30_7(delta,delta,.2f);qcopy(tmp,old);
        for(i=4;i>=0;i--) {
            angle=func_002A77E0(255);size=func_002A7878(.1f,.3f);
            spawn[0]=tmp[0]+func_002A78D8(0,.1f);spawn[1]=tmp[1]+func_002A78D8(0,.1f);spawn[2]=tmp[2]+func_002A78D8(0,.1f);
            func_002C65A0(spawn,D_L00_001A8F20,15,0x808080,angle,32,0,size*210000,size*42000,0,1);
            func_00282CC0_7(tmp,tmp,delta);
        }
        if(D_L00_001B19C8%10==0) {
            particle=func_002C65A0(obj+0x10,D_L00_001A8F20,30,0x202080,0,32,0,2100,420000,0,1);
            if(particle) EB(particle,2)=*D_L00_001FE9F4;
        }
        func_L00_002E6EF8(func_L00_003E2BD0,obj);
        break;
    case 1:
        if(func_00282948(&state->lifetime)) {func_002FEE50(state->sound);func_0029F338(obj);return;}
        func_L00_002E6EF8(func_L00_003E2BD0,obj);
        break;
    }
    if(EF(obj,0x10)<2 || EF(obj,0x10)>1021 || EF(obj,0x14)<2 || EF(obj,0x14)>1021 || EF(obj,0x18)<2 || EF(obj,0x18)>1021) {
        func_002FEE50(state->sound);func_0029F338(obj);
    }
}
