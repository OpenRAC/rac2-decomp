#include "common.h"

/* func_0032F598 is a unit of its own (-O2 -G8 -ffast-math). The aim vectors live in
   pts[4]: pts[2] is the hit point and pts[3] the origin; pts[0] and pts[1] are never
   touched and only reproduce retail's 0x1A0 frame (oversized local array, allowed by
   owner ruling, 8 November 2026). The effect's 0x3C store is written last so the
   scheduler emits retail's store order. */
typedef union { int q __attribute__((mode(TI))); float f[4]; } V598;
typedef struct __attribute__((packed, aligned(4))) { u64 a; u32 b; } P598;
extern P598 D_001B0988;
typedef struct { char pad[0x1A0]; union { unsigned long long held; unsigned int flags[2]; } buttons; int pressed; } Input598;
extern Input598 D_00138180;
extern char D_00188660[];
extern char D_001A8BD0[] MACRO_ADDR;
extern int D_001B095C __attribute__((sda));
extern float D_001B0994 __attribute__((sda)),D_001B0998 __attribute__((sda));
extern void func_0029FCC0(void *,int,void *),func_0029FC20(void *,int,void *);
extern char *func_002AF580(void *,void *,float,float,void *,int,int,int,float,float,float,int,void *);
extern char *func_002AB1F0(void *),*func_002FEC50(int);
extern void func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *),func_00282F20(void *,void *,float),func_002836E8(void *,void *),func_00283098(void *,void *,void *),func_00282C88(void *),func_00282DD8(void *,void *,void *),func_002AB6D8(void *,void *),func_002AF000(void *,float,float,float),func_002ACF68(void *,void *,void *,int,float),func_002AB600(void *,void *);
extern int func_001163B0(void),func_002E5CF8(int,int,void *),func_002FE5A0(void *,void *,void *,void *,void *,int,int,float);
extern float func_002A78D8(float,float),func_00283B98(float,float),func_002A7878(float,float),func_00283180(float),func_002A7790(float);
extern void func_00331238(void *,void *),func_00331580(void *,void *,float),func_002E59F8(int),func_003313E0(void *,void *);
extern void *func_00332440(void *,void *,void *), *func_00332590(void *,void *,void *,void *);
extern void func_002FDF40(void *,void *,void *,float,float,float,float,void *);
#define F598(p,o) (*(float *)((p)+(o)))
#define I598(p,o) (*(int *)((p)+(o)))
#define B598(p,o) (*(unsigned char *)((p)+(o)))
void func_0032F598(char *obj)
{
    V598 pts[4]; /* [2] hit point, [3] origin; [0], [1] unused frame space */
    P598 params;
    V598 angles, matrix[3], work[8];
    int output;
    char *rec=*(char **)(obj+0x68);
    char *target,*effect,*other;
    float a,b,old1,old2;
    func_0029FCC0(obj,0,&pts[3]);
    params=D_001B0988;
    target=func_002AF580(&pts[3],obj+0xC0,6.2831855f,6.2831855f,&output,0,0,0,10.0f,0.0f,0.0f,0,&params);
    if (!(D_00138180.buttons.flags[0]&0x40)) {
        if (target) {
            qcopy(&pts[2],target+0x10);
            other=func_002AB1F0(target);
            if (other) {
                func_00282D30(&angles,target+0xE0,F598(other,0x10));
                func_00282CC0(&pts[2],&angles,target+0x10);
            }
            func_00282CF0(rec+0x20,&pts[2],&pts[3]);
            func_00282F20(rec+0x20,rec+0x20,1.0f);
            func_002836E8(matrix,obj+0xC0);
            func_00283098(rec+0x20,rec+0x20,matrix);
        } else if (D_00138180.buttons.flags[0]&0x80) {
            func_00282C88(rec+0x20); F598(rec,0x20)=1.0f;
        } else if (func_001163B0()%111==0 && !(D_00138180.buttons.flags[0]&0x80)) {
            float randomAngle, elevation;
            matrix[0].q=0; matrix[0].f[2]=1.0f;
            qcopy(&work[0],rec+0x10);
            func_00282DD8(&work[1],&work[0],matrix);
            func_00282F20(&work[1],&work[1],1.0f);
            func_00282DD8(&work[2],&work[1],&work[0]);
            work[3].f[0]=0.0f;work[3].f[1]=0.0f;work[3].f[2]=0.0f;work[3].f[3]=1.0f;
            func_002AB6D8(&work[0],&angles);
            randomAngle=func_00283B98(angles.f[2],func_002A78D8(0.78539824f,1.5707965f));
            elevation = func_002A7878(0.0f,0.4f);
            func_002AF000(rec+0x20,1.0f,randomAngle,elevation);
        }
    }
    if (D_00138180.buttons.held&0xC0)
        func_002ACF68(rec+0x10,rec+0x10,rec+0x20,0,0.25f);
    else func_002ACF68(rec+0x10,rec+0x10,rec+0x20,0,0.125f);
    angles.q=0;angles.f[2]=1.0f;
    qcopy(matrix,rec+0x10);
    func_00282DD8(&matrix[1],matrix,&angles);
    func_00282F20(&matrix[1],&matrix[1],1.0f);
    func_00282DD8(&matrix[2],&matrix[1],matrix);
    effect=func_002FEC50(I598(rec,0x6C));
    func_002AB600(effect+0x10,matrix);
    B598(effect,3)=1;
    F598(effect,0x30)=-7.83249f;
    F598(effect,0x34)=1.9025599238414737e-12f;
    F598(effect,0x38)=10014.4f;
    F598(effect,0xC)=1.0f;
    F598(effect,0x20)=1.0f; F598(effect,0x24)=1.0f; F598(effect,0x28)=1.0f; I598(effect,0x2C)=0;
    F598(effect,0x3C)=1.0f;
    if (D_00138180.buttons.flags[0]&0x80) {
        a=1.0f-func_002A7790((func_00283180(D_001B0994)+1.0f)*0.5f)*0.5f;
        b=1.0f-func_002A7790((func_00283180(D_001B0998)+1.0f)*0.5f)*0.5f;
        effect=func_002FEC50(I598(rec,0x70));
        other=func_002FEC50(I598(rec,0x74));
        old1=D_001B0994; old2=D_001B0998;
        F598(effect,0x20)=a; F598(other,0x20)=b;
        D_001B0994=func_00283B98(old1,0.36651918292045593f);
        D_001B0998=func_00283B98(D_001B0998,0.36651918292045593f);
        if (old1<0.0f && D_001B0994>=0.0f) {
            func_0029FCC0(obj,2,&work[0]);
            func_0029FC20(obj,2,&work[4]);
            if (target) {
                func_00282CF0(&work[1],&pts[2],&work[0]);
                func_00282F20(&work[1],&work[1],0.25f);
            } else func_00282F20(&work[1],&work[4],0.25f);
            func_002E5CF8(6,0,obj);
            func_00331238(&work[0],&work[1]);
            func_00332440(obj,&work[0],&work[1]);
        } else if (old2<0.0f && D_001B0998>=0.0f) {
            func_0029FCC0(obj,1,&work[0]);
            func_0029FC20(obj,1,&work[1]);
            if (target) {
                func_00282CF0(&work[5],&pts[2],&work[0]);
                func_00282F20(&work[5],&work[5],0.25f);
            } else func_00282F20(&work[5],&work[1],0.25f);
            func_002E5CF8(6,0,obj);
            func_00331238(&work[0],&work[5]);
            func_00332440(obj,&work[0],&work[5]);
        }
    } else if (D_00138180.buttons.flags[0]&0x40) {
        float charge;
        char *slot;
        func_0029FCC0(obj,2,&work[0]);
        func_0029FCC0(obj,1,&work[1]);
        func_00282CC0(&work[2],&work[0],&work[1]);
        func_00282D30(&work[2],&work[2],0.5f);
        func_002FDF40(rec,&work[2],0,1.75f,F598(rec,0x7C),0.10000001f,0.00083333335f,obj);
        I598(rec,0x78)=func_002FE5A0(&work[2],rec,rec+0x30,rec+0x40,obj,0,0,0.00083333335f);
        charge=F598(rec,0x7C)+0.065f;
        charge = charge < 6.0f ? charge : 6.0f;
        F598(rec,0x7C)=charge;
        func_00331580(&work[2],D_001A8BD0,charge);
        slot=D_00188660+D_001B095C*0x70;
        if (I598(slot,0x88)!=(int)obj || !B598(slot,0x74)) D_001B095C=func_002E5CF8(4,4,obj);
        func_00282F20(rec+0x20,rec,1.0f);
        func_002836E8(&work[3],obj+0xC0);
        func_00283098(rec+0x20,rec+0x20,&work[3]);
    }

    if (D_00138180.pressed&0x40) {
        if (D_001B095C!=-1) {
            char *slot=D_00188660+D_001B095C*0x70;
            if (I598(slot,0x88)==(int)obj && B598(slot,0x74)) func_002E59F8(D_001B095C);
        }
        D_001B095C=-1;
        func_002E5CF8(8,0,obj);
        func_0029FCC0(obj,2,&work[0]);
        func_0029FCC0(obj,1,&work[1]);
        func_00282CC0(&work[2],&work[0],&work[1]);
        func_00282D30(&work[2],&work[2],0.5f);
        I598(rec,0x78)=0;F598(rec,0x7C)=1.75f;
        func_003313E0(&work[2],rec);
        func_00332590(obj,&work[0],&work[1],rec);
    }
}
