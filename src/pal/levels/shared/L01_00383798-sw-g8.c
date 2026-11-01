#include "include_asm.h"

#include "common.h"
#define BI(p, o) (*(int *)((p) + (o)))
#define BS(p, o) (*(short *)((p) + (o)))
#define BU(p, o) (*(unsigned short *)((p) + (o)))
#define BF(p, o) (*(float *)((p) + (o)))
#define BP(p, o) (*(unsigned char **)((p) + (o)))
typedef struct {
    unsigned char pad[0x80];
    float x, y, z, w;
    float rest[2];
    float angle;
    unsigned char pad2[0x2294 - 0x9C];
    int state;
    int unknown;
    int mode;
    unsigned char pad3[0x22B4 - 0x22A0];
    unsigned char locked;
} PlayerInteractionView;
extern unsigned char D_00189E20[];
#define PLAYER ((PlayerInteractionView *)D_00189E20)
extern int D_001B2088;
extern int D_001A79F0 __attribute__((section(".sdata")));
extern unsigned char D_00138324[];
extern float D_L01_001AEF30 __attribute__((sda));
extern float D_L01_001AEF28 __attribute__((sda));
extern float D_L01_001AEF2C __attribute__((sda));
extern float func_00283198(float);
extern float func_00282C48(float);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00283B98(float, float);
extern void func_0029F338(void *);
extern void func_0029F978(void *, int, void *);
extern void func_002A0F48(void *);
extern int func_00288D58(void);
extern unsigned char *func_0029EFD0(int);
extern void func_L01_00367F78(void);
extern void func_L01_00371228(int, int);
extern void ref_L01_003808C0_00(void *, void *);
extern void func_00283898(void *, int, float);
extern void func_L01_003801B8(void);
extern int func_002B0C28(int, int, int);
extern int func_002B49E0(int, int, void *, int, char *);

void func_PAL_L01_00383798(unsigned char *m) {
    unsigned char *s=BP(m,0x68);
    unsigned char *hero, *nearHero, *child;
    int color,other;
    int i,canUse,show,accepted;
    float distance,height;
    float phase,amplitude;
    D_L01_001AEF30+=0.05f;
    if(D_L01_001AEF30>3.14f) D_L01_001AEF30=-3.14f;
    color=0x20100;other=0x80F0F0B0;
    if(BI(s,0x94)==2) {color=0x101;other=0x8080;}
    BI(m,0x78)=color*((int)(func_00283198(D_L01_001AEF30)*24.0f)+96)|0x80000000;
    if(BP(s,0xC)) BI(BP(s,0xC),0x78)=other|0x80000000;
    if(BI(s,0x94)==3) {
        BU(m,0x34)|=1;m[0x31]=0;BI(m,0x98)=0;
        if(BP(s,0xC)) {BU(BP(s,0xC),0x34)|=1;BP(s,0xC)[0x31]=0;}
    }
    switch(m[0x20]) {
case 0:
        if(BI(s,0x98) && !func_00288D58()) {func_0029F338(m);return;}
        m[0x20]=1;BI(s,0)=0;BI(s,4)=0;
        BP(s,0xC)=func_0029EFD0(0x477);
        BU(BP(s,0xC),0x34)|=2;
        BS(BP(s,0xC),0x32)=0x40;
        BF(BP(s,0xC),0x10)=BF(m,0x10);
        BF(BP(s,0xC),0x14)=BF(m,0x14);
        BF(BP(s,0xC),0x18)=BF(m,0x18)+1.95f;
        if(BI(s,0x94)==3) BF(BP(s,0xC),0x18)-=30.0f;
        BP(s,0xC)[0x63]=0x20;BF(s,0x90)=0;
        for(i=0;i<2;i++) func_0029F978(BP(s,0xC),i,s+0x10+i*0x40);
        func_002A0F48(BP(s,0xC));
        break;
case 1:
        if(BF(s,0x90)>0) BF(s,0x90)-=0.1f;
        if(BF(s,0x90)<=0) BU(BP(s,0xC),0x34)|=1;
        if(!(D_001B2088&7)) {
            hero=(unsigned char *)&PLAYER->x;
            if(func_00282E80(m+0x10,hero)<=16.0f && func_00282C48(BF(m,0x18)-BF(hero,8))<=8.0f) {
                m[0x20]=2;BU(BP(s,0xC),0x34)&=0xFFFE;
                if(BI(s,0x94)==2) func_L01_00367F78();
                func_L01_00371228(D_001A79F0,BI(s,0x94));
            }
        }
        if(BI(s,0x94)==3) break;
        ref_L01_003808C0_00(func_L01_003801B8,m);
        func_00283898(s+0x20,2,D_L01_001AEF28);
        func_00283898(s+0x60,2,D_L01_001AEF2C);
        D_L01_001AEF28=func_00283B98(D_L01_001AEF28,0.01f);
        phase=func_00283B98(D_L01_001AEF2C,-0.02f);
        child=BP(s,0xC);
        amplitude=BF(s,0x90)*BF(BP(child,0x24),0x24)*2.5f;
        D_L01_001AEF2C=phase;
        BF(child,0x2C)=amplitude;
        func_002A0F48(BP(s,0xC));
        break;
case 2:
        if(BF(s,0x90)<1) BF(s,0x90)+=0.1f;
        nearHero=(unsigned char *)&PLAYER->x;
        distance=func_00282E80(m+0x10,nearHero);
        height=func_00282C48(BF(m,0x18)-BF(nearHero,8));
        if(!(D_001B2088&7) && (distance>18.0f || height>10.0f)) {m[0x20]=1;return;}
        if(BI(s,0x94)!=3) {
            ref_L01_003808C0_00(func_L01_003801B8,m);
            func_00283898(s+0x20,2,D_L01_001AEF28);
            func_00283898(s+0x60,2,D_L01_001AEF2C);
            D_L01_001AEF28=func_00283B98(D_L01_001AEF28,0.01f);
            phase=func_00283B98(D_L01_001AEF2C,-0.02f);
            child=BP(s,0xC);
            amplitude=BF(s,0x90)*BF(BP(child,0x24),0x24)*2.5f;
            D_L01_001AEF2C=phase;
            BF(child,0x2C)=amplitude;
            func_002A0F48(BP(s,0xC));
        }
        canUse=1;show=1;
        if(PLAYER->mode!=0 && PLAYER->state!=3 && PLAYER->mode!=1) {canUse=0;show=0;}
        if(PLAYER->state==28 || PLAYER->state==49) {canUse=0;show=0;}
        if(PLAYER->locked) {canUse=0;show=0;}
        if(distance>4.0f || height>2.0f) {canUse=0;show=0;}
        if(func_00283C80(PLAYER->angle,func_00283248(BF(m,0x10)-PLAYER->x,BF(m,0x14)-PLAYER->y))>1.5707964f) {canUse=0;show=0;}
        accepted=0;
        if(show) {
            int text=0x12EB;
            if(BI(s,0x94)==2) text=0x1350;
            else if(BI(s,0x94)==4) text=0x1351;
            accepted=func_002B0C28(1,text,1)!=0;
        }
        if((BI(D_00138324,0)&16) && canUse && accepted) m[0x20]=4;
        break;
case 3:
        break;
case 4:
        if(BF(s,0x90)>0) BF(s,0x90)-=0.1f;
        if(BF(s,0x90)<=0) {
            BU(BP(s,0xC),0x34)|=1;func_002B49E0(5,1,m,0,0);m[0x20]=3;break;
        }
        if(BI(s,0x94)==3) break;
        ref_L01_003808C0_00(func_L01_003801B8,m);
        func_00283898(s+0x20,2,D_L01_001AEF28);
        func_00283898(s+0x60,2,D_L01_001AEF2C);
        D_L01_001AEF28=func_00283B98(D_L01_001AEF28,0.01f);
        phase=func_00283B98(D_L01_001AEF2C,-0.02f);
        child=BP(s,0xC);
        amplitude=BF(s,0x90)*BF(BP(child,0x24),0x24)*2.5f;
        D_L01_001AEF2C=phase;
        BF(child,0x2C)=amplitude;
        func_002A0F48(BP(s,0xC));
        break;
    }
}
