/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1396/1332 bytes; frame 0xD0 instead of 0xE0, platform state branches and tilt-lifetime allocation differ.
 * Reopen with platform-state types and the retained old-position/old-tilt lifetime witness.
 * ABI/bounds: Seven complete 16-byte vectors. 002AA898 returns float and preserves all four FP inputs plus pos/velocity/direction GPR inputs. 00316C48 helper output is one complete quad; standing-hero halfword predicate decoded with branch-likely control flow.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"
typedef float LiftVector[4] __attribute__((aligned(16)));
extern unsigned char D_00189E20[];
extern float D_L01_001B1B28[] __attribute__((sda));
extern int func_002ACD38(void *);
extern float func_L01_003BAFB0(void);
extern float func_002A7940(void);
extern void func_002A7750(void *,int,int);
extern float func_002A7798(float);
extern void func_002AEF28(void *,void *,void *,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
extern float func_00283B98(float,float), func_00283198(float);
extern int func_00283D38(int,int,float);
extern float func_00282DB0(void *,void *);
extern float func_002AA898(float *,float,float *,float,float,float,int);
extern void func_L01_00316C48(void *,void *,void *,void *,void *);
#define F(o) (*(float *)(p+(o)))
#define G(i) D_L01_001B1B28[(i)]

/* Moving platform: initializes its vertical range, moves between endpoints,
 * then applies the standing hero's displacement to its damped tilt. */
void func_L01_0041C970(unsigned char *m)
{
    LiftVector old, rotation, delta, offset, old_tilt, old_position, output;
    unsigned char *p, *hero=D_00189E20;
    float ground, ease, speed, dotx, doty;
    int pressing;
    if(!func_002ACD38(m+0x10)) return;
    p=*(unsigned char **)(m+0x68);
    qcopy(old,m+0x10); qcopy(rotation,m+0xf0);
    switch(m[0x20]) {
    case 0:
        ground=func_L01_003BAFB0(); F(0xac)=0;
        if(!(ground>100.0f)) break;
        F(0x78)=func_002A7940(); F(0x7c)=func_002A7940();
        F(0x68)=0;
        F(0x6c)=*(float *)(m+0x18)-ground;
        F(0x60)=F(0x6c); F(0x64)=F(0x6c)-G(0);
        qcopy(p+0x80,m+0xf0); qzero(p+0x90);
        func_002A7750(m,*(int *)(p+0xa0)?1:2,-1);
        break;
    case 1:
        ground=func_L01_003BAFB0();
        pressing=0;
        if(*(int *)(hero+0x229c)==0x19 && F(0x68)<0.0f
            && *(float *)(m+0x18)-0.2f<*(float *)(hero+0x88)
            && *(float *)(m+0x18)<ground+0.1f) pressing=1;
        if((*(void **)(hero+0x33c)==m && !*(short *)(hero+0x34e)) || pressing) {
            if(pressing) *(int *)(m+0x98)=0;
            else *(int *)(m+0x98)=*(int *)(*(unsigned char **)(m+0x24)+0x10);
            ease=func_002A7798((F(0x6c)-F(0x64))/G(0));
            speed=-(G(1)*0.016666668f);
        } else {
            *(int *)(m+0x98)=*(int *)(*(unsigned char **)(m+0x24)+0x10);
            ease=func_002A7798((G(0)-(F(0x6c)-F(0x64)))/G(0));
            speed=G(2)*(ease*0.016666668f);
        }
        F(0x68)=speed; F(0x6c)+=F(0x68); *(float *)(m+0x18)=ground+F(0x6c);
        func_002AEF28(m,p+0x78,p+0x7c,G(5),G(6)*0.0002908882452175021f,G(7)*0.0002908882452175021f);
        func_00282CF0(delta,m+0x10,old); func_002AD6F0(p+0x20,delta,rotation,m+0xf0);
        break;
    case 2:
        if(m[0x31]) {
            F(0xac)=func_00283B98(F(0xac),0.052359887f);
            *(int *)(m+0x78)=func_00283D38(0xffeefc0e,0xf03b4004,func_00283198(F(0xac))*0.5f+0.5f);
        }
        ground=func_L01_003BAFB0();
        if(!*(short *)(hero+0x34e) && *(void **)(hero+0x33c)==m) {
            func_00282CF0(offset,hero+0x80,m+0x10);
            dotx=func_00282DB0(offset,m+0xc0); doty=func_00282DB0(offset,m+0xd0);
            qcopy(old_tilt,p+0x80); qcopy(old_position,m+0x10);
            func_002AA898((float *)(p+0x80),-G(8)*doty,(float *)(p+0x90),G(10),G(11),G(12),0);
            func_002AA898((float *)(p+0x84),G(9)*dotx,(float *)(p+0x94),G(10),G(11),G(12),0);
            func_L01_00316C48(hero+0x80,output,m+0x10,old_tilt,p+0x80);
        } else {
            func_002AA898((float *)(p+0x80),0,(float *)(p+0x90),G(13),G(14),G(15),0);
            func_002AA898((float *)(p+0x84),0,(float *)(p+0x94),G(13),G(14),G(15),0);
        }
        *(float *)(m+0x18)=ground+F(0x6c);
        func_002AEF28(m,p+0x78,p+0x7c,G(5),G(6)*0.0002908882452175021f,G(7)*0.0002908882452175021f);
        *(float *)(m+0xf0)=func_00283B98(F(0x80),*(float *)(m+0xf0));
        *(float *)(m+0xf4)=func_00283B98(F(0x84),*(float *)(m+0xf4));
        func_00282CF0(delta,m+0x10,old); func_002AD6F0(p+0x20,delta,rotation,m+0xf0);
        break;
    }
}
