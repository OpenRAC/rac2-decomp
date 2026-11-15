#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern void func_002AB8C0(void *,void *);
extern char *func_002A9640(void *,int,int);
extern int func_00282978(void *);
extern float func_002A96A0(void *,void *);
extern void func_002B3380(void *,void *,void *);
extern char *D_001B1B5C;
typedef struct { int frame; } DamageClock;
extern DamageClock D_001B1688;
extern int D_001B1688_1;
extern u8 D_00139568[];
typedef struct { char pad[0x54]; float scale; char tail[0x88]; } DamageClass;
extern DamageClass D_00239BA0[];
extern int func_00282C30(int);
extern float func_002AFF08(void *,void *,int);
extern void func_00282CF0(void *,void *,void *);
extern char D_00189EA0[];
extern void func_002AFE58(void *,void *,void *,int,float);
extern void func_00282D30(void *,void *,float);
extern int func_002B1350(void *,void *,void *,int);
extern void func_002A7750(void *,int,int);

/* Applies a hit to an object: takes health, decides how strong the reaction is, and starts it. */
int func_002B0ED8(char *object,char *state,int special)
{
    float vector[4] __attribute__((aligned(16)));
    char *health,*callback,*hit;
    float original,damage;
    int result=0,timeout;
    int kind;
    if (!(*(u16 *)(object+0x34)&0x20)) return 0;
    health=P(P(object,0x68),0);
    callback=P(P(object,0x68),0x1c);
    if (!state || !health) return 0;
    UpdateColorFade(object,state);
    original=0.0f;
    hit=FindOwnedEffectSlot(object,0x10000,0);
    if (!FastDecTimer(health+6)) hit=0;
    if (hit) {
        original=F(hit,0x2c);
        if (F(state,0xa8)!=0.0f && P(hit,0x20) && H(object,0xaa)==H(P(hit,0x20),0xaa))
            F(hit,0x2c)=original*F(state,0xa8);
        if (special) F(hit,0x2c)*=F(state,0xac);
    }
    damage=UpdateAimTargetStrength(object,hit);
    U(object,0xa8)=255;
    F(health,0)-=damage;
    if (callback) SpawnDamageDebrisOnHealthLoss(object,callback,health);
    if (damage==0.0f) return 0;
    H(state,0x70)=-1;
    if (hit && P(hit,0x20)) H(state,0x70)=(P(hit,0x20)-D_001B1B5C)>>8;
    kind=U(health,0x17);
    if (damage*((DamageClass *)(gItemSlotToRecord[kind]*224+(char *)gWeaponTable_00239BA0))->scale>=H(health,4)*F(state,0x58)) timeout=90;
    else timeout=300;
    if (!U(state,0x77) && subtract_integer_with_clamp(gGameTime.frame-I(state,0x44))>timeout) {
        if (damage<H(health,4)*F(state,0x58)) damage=H(health,4)*F(state,0x58);
    }
    if (F(health,0)<=0.0f) result=4;
    else if (damage>=H(health,4)*F(state,0x5c)) result=3;
    else if (damage>=H(health,4)*F(state,0x58)) result=2;
    else if (damage!=0.0f && !U(state,0x77) && hit && P(hit,0x20) && H(P(hit,0x20),0xaa)==0x47 /* moby class 71 */) result=2;
    else if (original!=0.0f) result=1;
    if (special && (unsigned)(result-1)<=2) result=6;
    if (result>=2 && hit && U(health,0x17)==10) {
        damage=GetHorizontalOffsetLength(object,hit+0x10,0);
        FastVecSub(hit+0x10,object+0x10,gHeroPosition);
        TransformAndScaleVector(object,hit+0x10,hit+0x10,0,damage);
    }
    if (!result || (*(u16 *)(state+0x38)&3)) return 0;
    if (U(object,0x95)==I(state,0x48) && result<4) {
        if (U(state,0x75)) return 0;
        if (U(state,0x1a)<2) return 0;
    }
    if (hit && (I(hit,0x30)&1)) qcopy(vector,hit+0x10);
    else {
        FastVecScale(vector,object+0xc0,-1.0f);
        vector[2]=1.0f;
        vector[3]=5627.925f;
    }
    if (ApplyObjectReaction(object,state,vector,result)) {
        I(state,0x44)=D_001B1688_1;
        if (I(state,0x48)!=-1) SetMobyState(object,U(state,0x10),I(state,0x48));
        else SetMobyState(object,U(state,0x10),-1);
        U(state,0x1a)=0;
    }
    return result;
}
