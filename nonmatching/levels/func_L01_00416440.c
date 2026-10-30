/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1520/1552 bytes after truthful helper returns; frame 0xB0 retained, idle rotation loop and scripted pickup branches differ.
 * Reopen with a source witness for the four explicit angle updates and interaction-state lifetimes.
 * ABI/bounds: Four complete local vectors; camera helpers retain all arguments. 002B0A18 returns void, 0029B3E0 returns int. No particle/query packet is fabricated.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"
typedef float PickupVector[4] __attribute__((aligned(16)));
extern unsigned char D_00189E20[];
extern u8 D_001A7B2A[], D_001A7A45[];
extern float D_L01_001B1A58[] __attribute__((sda));
extern int D_L01_001B1A98 __attribute__((sda));
extern float D_L01_001B1A68 __attribute__((sda));
extern int D_L01_001B21B0, D_L01_001B22A8, D_L01_001B1FA8;
extern int D_L01_001B1FA8_gp SDATA(D_L01_001B1FA8);
extern float func_002A7940(void);
extern float func_00283B98(float,float);
extern float func_00283BE0(float,float);
extern float func_00282E80(void *,void *);
extern float func_00282C48(float);
extern float func_00283180(float), func_00283198(float);
extern int func_002A77E0(int);
extern void func_L01_00416B30(void *), func_L01_00416C08(void *);
extern void func_L01_00417090(void *), func_L01_00416E78(void *), func_L01_00416A50(void *);
extern void func_002B0A18(int,int);
extern void func_00288308(int);
extern int func_002E5CF8(int,int,void *);
extern void func_0029F338(void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282C88(void *);
extern void func_0027D330(int);
extern void func_L01_002B35E8(int);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_00335438(void *,void *,int,int,int);
extern void func_00335370(void *), func_003353C8(void *), func_003355A8(int);
extern void func_002A7470(void *,int,int,int);
extern void func_L00_002D2168(int,int,float);
extern int func_00282948(void *);
extern int func_0029B3E0(int,int);
#define PF(o) (*(float *)(p+(o)))

/* Pickup/interaction state: idle rotation, hero approach, scripted camera and
 * animation completion. Vector temporaries are complete aligned quads. */
void func_L01_00416440(unsigned char *m)
{
    PickupVector camera, angles, effect, effect_angles;
    unsigned char *p=*(unsigned char **)(m+0x68), *hero=D_00189E20;
    int i;
    switch(m[0x20]) {
    case 0:
        if(D_001A7B2A[0]) goto remove;
        qcopy(p+0x10,m+0x10); PF(0x1c)=*(float *)(m+0xf8);
        *(float *)(m+0xf0)=func_002A7940(); *(float *)(m+0xf4)=func_002A7940();
        *(float *)(m+0xf8)=func_002A7940(); *(float *)(m+0xfc)=func_002A7940();
        PF(0x68)=D_L01_001B1A68*0.0002908882452175021f;
        PF(0x64)=D_L01_001B1A58[5]*0.0002908882452175021f;
        PF(0x60)=D_L01_001B1A58[6]*0.0002908882452175021f;
        if(*(short *)(m+0x32)<64) *(short *)(m+0x32)=64;
        m[0x20]=1; func_L01_00416B30(m);
        break;
    case 1:
        *(float *)(m+0x2c)=*(float *)(*(unsigned char **)(m+0x24)+0x24)*D_L01_001B1A58[0];
        for(i=0;i<4;++i) *(float *)(m+0xf0+i*4)=func_00283B98(*(float *)(m+0xf0+i*4),D_L01_001B1A58[4+i]*0.0002908882452175021f);
        func_L01_00416C08(m);
        if(!func_002A77E0(D_L01_001B1A98)) func_L01_00417090(m);
        if(!(func_00282E80(m+0x10,hero+0x80)<3.0f)) break;
        if(!(func_00282C48(*(float *)(m+0x18)-*(float *)(hero+0x88))<2.0f)) break;
        if(!*(int *)(hero+0x24cc) || (hero[0x22b4]!=3 && hero[0x22b4]!=0)) break;
        if(*(short *)(p+0xc)) {
            D_L01_001B21B0=180; func_002B0A18(0xaaa,-1); func_00288308(50);
            func_002E5CF8(1,0,m); func_0029F338(m); break;
        }
        camera[0]=func_00283180(PF(0x1c))*2.5f;
        camera[1]=func_00283198(PF(0x1c))*2.5f; *(int *)&camera[2]=0;
        func_00282CC0(camera,camera,p+0x10);
        func_00282C88(angles); angles[2]=func_00283B98(PF(0x1c),3.141593f);
        func_0027D330(10);
        if(hero[0x22b4]==3) func_L01_002B35E8(0);
        func_L00_002B9D60(camera,angles,0x6f,0); func_002E5CF8(0,0,m);
        effect[0]=func_00283180(PF(0x1c))*1.25f;
        effect[1]=func_00283198(PF(0x1c))*1.25f; *(int *)&effect[2]=0;
        effect[0]+=func_00283180(func_00283B98(PF(0x1c),1.5707965f))*4.0f;
        effect[1]+=func_00283198(func_00283B98(PF(0x1c),1.5707965f))*4.0f;
        func_00282CC0(effect,effect,p+0x10); effect[2]+=1.0f;
        func_00282C88(effect_angles); effect_angles[2]=func_00283BE0(PF(0x1c),1.5707965f);
        func_00335438(effect,effect_angles,1,0,0); func_00335370(effect); func_003353C8(effect_angles);
        qcopy(m+0x10,hero+0x80); qcopy(m+0xf0,hero+0x90);
        if(m[0x43]!=1) func_002A7470(m,1,0,0);
        func_L00_002D2168(0x7b,0,0);
        if(D_001A7A45[0]) *(u16 *)(m+0x34)|=0x8000;
        hero[0x22bf]=1; D_L01_001B1FA8=1; m[0x20]=2; *(int *)(p+0x6c)=60;
        break;
    case 2:
        D_L01_001B22A8=1; func_L01_00416E78(m);
        qcopy(m+0x10,hero+0x80); qcopy(m+0xf0,hero+0x90);
        if(m[0x42]==1) {
            func_L01_00416A50(m);
            if(!func_002A77E0(10)) func_L01_00417090(m);
            if(m[0x60]&2) {
                if(m[0x43]) func_002A7470(m,0,0,0);
                m[0x31]=0; *(u16 *)(m+0x34)|=1;
                for(i=3;i>=0;--i) func_L01_00417090(m);
                if(*(int *)(hero+0xc28)&2) func_L00_002D2168(0,0,30.0f);
            }
        }
        if(!m[0x42] && func_00282948(p+0x6c)) {
            D_L01_001B21B0=180; func_002B0A18(0x129a,-1); func_00288308(50);
            D_L01_001B1FA8_gp=0; func_L00_002B9D60(hero+0x80,hero+0x90,0,0);
            func_003355A8(0); func_0029B3E0(0,-1);
remove:
            func_0029F338(m);
        }
        break;
    }
}
