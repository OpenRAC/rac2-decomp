/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 09_dobbo: 1268 bytes, expected 1240; us2: 09_dobbo: 1268 bytes, expected 1240; pal: ABSENT.
 * Complete moving-impact reconstruction. Three complete temporary vectors share a union with the
 * verified 0x28-byte impact request. func_002A8C00 initializes attacker/flags/damage/enabled and
 * its full direction; the final word remains prior vector storage. Real pointer/particle
 * returns, all effect arguments and stack arguments are retained. Frame, saved registers and
 * effect scheduling differ.
 * Reopen: Independent source-lifetime/union scheduling witness; preserve the complete impact
 * extent.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct {
    float direction[4]; void *attacker; int flags;
    u8 kind,mode; u16 object_class; float damage; int enabled; float field24;
} Impact;
typedef char ImpactExtent[sizeof(Impact)==0x28 ? 1 : -1];
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
extern float D_L09_001B238C NOT_SDA,D_L09_001B2390 NOT_SDA;
extern int D_L09_001B2388_gp SDATA(D_L09_001B2388);
extern u8 *D_L09_001BFE58 NOT_SDA;
extern float D_L09_001A8F20[];
extern float func_00283B98(float,float),func_00282DF0(void *),func_002A7878(float,float),func_002A7940(void);
extern int func_001163B0(void),func_00282948(void *);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *),func_00283098(void *,void *,void *);
extern void func_00282F20(void *,void *,float),func_00282D30(void *,void *,float),func_002ACEC0(void *,void *,void *,float);
extern void *func_002C16C0(void *,void *,int,int,int,int,float,float,float,float,float);
extern void *func_002BD8B0(void *,void *,int,int,int,int,float);
extern void func_002A8C00(void *,int,int,float,void *);
extern int func_002761F8(void *,void *,int,void *,Impact *);
extern int func_00277258(void *,int,void *,float),func_00277F48(void *,int,void *,Impact *,float);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_0029F338(void *);

/* Updates a moving impact effect. The three temporary effect vectors share
 * storage with the later complete 0x28-byte impact request, as their lifetimes
 * do not overlap. The request's final word retains the prior vector storage.
 */
void func_L09_003A01D8(u8 *object)
{
    struct {
        float predicted[4];
        union {
            struct {Vector point,velocity,axis;} effects;
            Impact impact;
        } payload;
    } f;
    u8 *state = P(object,0x68),*hit;
    float length;
    int collision;
    if (object[0x20]) return;
    F(object,0xF0)=func_00283B98(F(object,0xF0),0.10471977293491364f);
    func_00282CC0(f.predicted,object+0x10,state);
    if (!((D_L09_001B238C>0.9f || D_L09_001B2390>0.9f) && (D_L09_001B2388_gp&1))) {
        length=func_00282DF0(state);
        f.payload.effects.axis.q=0;
        f.payload.effects.axis.f[0]=func_002A7878(-1.0f,1.0f);
        f.payload.effects.axis.f[1]=func_002A7878(-1.0f,1.0f);
        f.payload.effects.axis.f[2]=func_002A7878(-1.0f,1.0f);
        f.payload.effects.velocity.q=f.payload.effects.axis.q;
        func_00282F20(f.payload.effects.velocity.f,f.payload.effects.velocity.f,
                     func_002A7878(0.04f,0.08f)*0.016666668f);
        func_00282D30(f.payload.effects.point.f,state,func_002A7878(0.2f,0.99f));
        func_00282CC0(f.payload.effects.velocity.f,f.payload.effects.velocity.f,f.payload.effects.point.f);
        func_00282F20(f.payload.effects.point.f,state,func_002A7878(0.0f,1.0f)*length);
        func_00282CC0(f.payload.effects.point.f,f.payload.effects.point.f,object+0x10);
        func_002C16C0(object+0x10,f.payload.effects.velocity.f,7,127,0xB0B0B0,3,
                     40000.0f,1000.0f,1.0f,-0.00039999998989515007f,0.0f);
        f.payload.effects.axis.q=0;
        f.payload.effects.axis.f[2]=0.01f;
        func_00283098(f.payload.effects.axis.f,f.payload.effects.axis.f,object+0xC0);
        func_002ACEC0(f.payload.effects.axis.f,f.payload.effects.axis.f,object+0xC0,func_002A7940());
        if (func_001163B0()&1)
            func_002BD8B0(f.payload.effects.point.f,f.payload.effects.axis.f,
                         0x4F007FFF,0x1FFFFFFF,13,1,25000.0f);
    }
    func_002A8C00(&f.payload.impact,I(state,0x3C),0x10001,F(state,0x40),state);
    f.payload.impact.object_class=*(u16 *)(object+0xAA);
    func_00282CF0(f.payload.impact.direction,object+0x10,P(state,0x3C)+0x10);
    f.payload.impact.direction[2]=0.0f;
    func_00282F20(f.payload.impact.direction,f.payload.impact.direction,1.6666667461395264f);
    f.payload.impact.enabled|=1;
    f.payload.impact.kind=4;
    f.payload.impact.direction[3]=5627.9248046875f;
    collision=func_002761F8(object+0x10,f.predicted,0,object,&f.payload.impact);
    if (collision || func_00277258(object+0x10,1,object,0.3f) || func_00282948(state+0x38)) {
        hit=D_L09_001BFE58;
        if (hit && hit==P(state,0x3C)) {
            qcopy(object+0x10,f.predicted);
            return;
        }
        if (hit) {
            if (*(short *)(hit+0xAA)!=0x4E)
                func_00277F48(object+0x10,0,P(state,0x3C),&f.payload.impact,0.5f);
            func_002ABBB8(object,D_L09_001A8F20,0,0.0f,0.0f,0,2,10,
                         0.0f,0.0f,9.0f,0.666f,-1,0.0f,0,1,-1,0,0x810001);
        } else {
            func_002ABBB8(object,D_L09_001A8F20,0,0.0f,0.0f,0,2,8,
                         0.0f,0.0f,9.0f,0.5f,-1,0.0f,0,1,-1,0,0x810001);
        }
        func_002E5CF8(0,0,object);
        func_0029F338(object);
    } else qcopy(object+0x10,f.predicted);
}
