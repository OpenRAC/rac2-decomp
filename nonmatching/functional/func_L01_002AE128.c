/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol, high effort; task v1314, USA v1.01.
 * Best check.py: 2040/2040 bytes, 0 of 8 places match; first nonrelocated
 * instruction difference at +0x184. Default -O2 -G0 -ffunction-sections.
 * Required declarations are included below. No linked match is claimed.
 *
 * Corrections to the earlier 2032-byte draft:
 * - Construct v10, v20 and v30 before the first loop. Each iteration only
 *   advances both endpoints by v30, then tests the resulting segment.
 * - The wall-facing test is wallDot < cos(1.1344641f), not greater than.
 *   The literal reproduces retail's 0x3F91361F, rather than 0x3F91361E.
 * - Keep the height-test distance separate from the later wall dot product;
 *   otherwise their shared pseudo forces the former into f20 instead of f2.
 * - Name step/limit before copying v120 to preload the final-loop constants.
 *
 * The hit-moby field is declared volatile throughout, based on retail's
 * repeated loads at L01 002AE43C and 002AE44C without an intervening call.
 * Snapshot its initial read for both the null test and func_003148A0; retail
 * does not reread between those operations. This preserves the measured
 * reads and recovers the moby spill at sp+0x140 and retail's 0x1C0 frame.
 * No selected-access volatile casts or volatile locals are used.
 *
 * Remaining differences: slope initialization moves before the first vector
 * add, first-loop termination/delay scheduling differs, and the owner sda
 * view emits a tied absolute field load rather than retail's separate hero
 * base construction. Material-validation setup and later scheduling differ.
 * Without sda on the partial owner view, the corrected candidate is 2048
 * bytes: cc1 instead hoists the hero base into s1 across the first loop.
 * The whole-object hero view pools that base with earlier vector arguments.
 *
 * Measured 20 check.py candidates, plus one allocation diagnostic. The old
 * draft requalified at 2032 bytes. Corrected ordinary scalar forms reached
 * 2016 bytes but retained moby in a GPR and used a 0x1B0 frame. Explicit
 * point/delta pointers gave 2024 bytes before the volatile field; a one-field
 * candidate aggregate tied its scalar form. Qcopy profiles tied default;
 * -fno-gcse did not recover the first-loop addresses; -G8 and unsplit GCSE
 * tied the corrected 2048-byte candidate. Inline slope and bank-preserving
 * FP-first scale calls also tied; an explicit break changed only scheduling.
 * Next useful evidence: original first-loop hero-base representation and
 * the scope/lifetime that keeps slope materialization after the vector add.
 * Do not repeat the old loop reconstruction or reversed wall comparison.
 * Related public RAC1 source: src/overlays/shared/hero_update_ground_material.c,
 * update_hero_ledge_probe and test_hero_ledge_ahead (different gravity model).
 */
#include "common.h"
typedef struct {
 float forward[4];
 char pad10[16];
 float axis[4];
 char pad30[192];
 float velocity[4];
 char pad100[208];
 short cooldown;
 char pad1d2[146];
 float radius;
 char pad268[88];
 float up[4];
 char pad2d0[76];
 float ground;
 char pad320[382];
 u8 apex;
 char pad49f[177];
 char probe[0x40];
 char pad590[1704];
 float frame;
 char padc3c[5716];
 int moby;
 int state;
 char pad2298[4];
 int control;
 char pad22a0[20];
 u8 vehicle;
} LedgeHero;
extern LedgeHero ledgeHero __asm__("D_00189E20");
typedef struct { char pad[0x2290]; int moby; } LedgeOwner;
extern LedgeOwner ledgeOwner __asm__("D_00189E20") __attribute__((sda));
typedef struct { char pad[0x18]; volatile int moby; char pad1C[4]; float point[4],pos[4],normal[4]; } LedgeHit;
extern LedgeHit D_L01_001BF900;
extern float func_002C9280(void *);
extern void func_002E3738(void *, void *, float);
extern void func_002E3470(void *, void *, void *);
extern void func_002E34A0(void *, void *, void *);
extern void func_002E3918(void *, void *, void *);
extern void func_002C92D8(void *, void *, float);
extern int func_002D3C80(void *, void *, int, int, int);
extern int func_002D77E8(void);
extern float func_002C9628(void *);
extern char *func_003148A0(int);
extern char *func_00316D00(int);
extern int func_002D4CE0(float, void *, int, int);
extern float func_002E3560(void *, void *);
extern float func_002E3A48(float);
extern float func_002E3B10(float, float);
typedef int ProbeQuad __attribute__((mode(TI)));
typedef union { ProbeQuad q; float f[4]; } ProbeVec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define B(p,o) (*(u8 *)((char *)(p)+(o)))


int func_L01_002AE128(void *input, int unused, char *out) {
    ProbeVec v0,v10,v20,v30,v40,v50,v60,v70,v80,v90,vA0,vB0,vC0,vD0,vE0,vF0,v100,v110,v120,v130;
    int moby,go,found,i,type,ok,edge,j;
    char *a,*b;
    float distance,wallDot,travel,top,down,drop,slope,step,limit;
    if(out) I(out,0x28)=0;
    if(ledgeHero.cooldown) return 0;
    go=0;
    if(!ledgeHero.vehicle) {
        if ((ledgeHero.control==4 && (ledgeHero.apex || func_002C9280(ledgeHero.velocity)<0.0583333373f)) || ledgeHero.control==2 || ledgeHero.state==8 || ledgeHero.state==0x19 || ledgeHero.state==0x1A) go=1;
        if(ledgeHero.state==14 && ledgeHero.frame<37.0f) go=0;
    }
    if(out != ledgeHero.probe) go=1;
    if(!go) return 0;
    {
    LedgeHero *hero = &ledgeHero;
    top=1.15f; down=-0.7f; drop=-1.43f;
    found=0;
    qcopy(&v0,input);
    func_002E3738(&v40,hero,hero->radius);
    func_002E3470(&v0,&v0,&v40);
    {
        func_002E3738(&v40,hero->axis,1.65f);
        func_002E3470(&v10,&v0,&v40);
        func_002E3738(&v40,hero->axis,-top);
        func_002E3470(&v20,&v0,&v40);
        func_002E3738(&v30,hero,0.075f);
    }
    }
    slope=0.3490659f;
    for(i=0; !found && i<4; i++) {
        func_002E3470(&v10,&v10,&v30);
        func_002E3470(&v20,&v20,&v30);
        if(func_002D3C80(&v10,&v20,4,ledgeOwner.moby,0)) {
            type=func_002D77E8();
            if(type!=9 && type!=12 && type!=0 && func_002C9628(D_L01_001BF900.normal)<slope) found=1;
        }
    }
    moby=0;
    if(!found) return 0;
    {
    int firstMoby = D_L01_001BF900.moby;
    if(firstMoby) {
        ok=0;
        a=func_003148A0(firstMoby);
        b=func_00316D00(D_L01_001BF900.moby);
        if(a && (*(u16 *)(a+0x1E)&1)) ok=1;
        else if(b) ok=I(b,0x3C)&1;
        if(!ok) return 0;
        moby=D_L01_001BF900.moby;
        if(out) I(out,0x38)=D_L01_001BF900.moby;
    }
    }
    qcopy(&v60,D_L01_001BF900.point);
    func_002E34A0(&v50,&v60,input);
    if(func_002C9280(&v50)>1.5f) return 0;
    func_002E3738(&v70,ledgeHero.axis,0.005f);
    func_002E3470(&v70,&v70,&v60);
    func_002E3738(&v80,&ledgeHero,-1.0f);
    func_002E3470(&v80,&v80,&v70);
    if(func_002D3C80(&v80,&v70,2,ledgeHero.moby,0)) {
        int m=D_L01_001BF900.moby;
        if(!m || m!=moby) return 0;
    }
    if(out) {
        func_002E3738(&v90,ledgeHero.axis,0.6f);
        func_002E3470(&v90,&v90,&v60);
        if(func_002D4CE0(0.45f,&v90,4,ledgeHero.moby)) I(out,0x34)|=1;
        else I(out,0x34)&=~1;
    }
    distance=func_002C9280(&v50);
    if(distance+ledgeHero.ground<1.8f || distance<0.5f) return 0;
    vB0.q=0; vB0.f[0]=1.0f; vB0.f[2]=down;
    func_002E3918(&vB0,&vB0,&ledgeHero);
    edge=0; j=0;
    func_002E3470(&vB0,&vB0,&v60);
    func_002E34A0(&v90,input,&vB0);
    func_002C92D8(&v90,&v90,0.0f);
    func_002E3470(&v90,&v90,&vB0);
    func_002E3738(&vA0,ledgeHero.axis,-down*0.2f);
    while(j<5) {
        if(func_002D3C80(&v90,&vB0,2,0,0)) {
            func_002E3738(&vC0,D_L01_001BF900.normal,1.0f);
            edge=1;
            func_002C92D8(&vC0,&vC0,0.0f);
            break;
        }
        func_002E3470(&v90,&v90,&vA0); j++;
        func_002E3470(&vB0,&vB0,&vA0);
    }
    if(!edge) return 0;
    wallDot=func_002E3560(&ledgeHero,&vC0);
    if(!(wallDot<func_002E3A48(1.1344641f))) return 0;
    step=0.03f; limit=2.4f;
    qcopy(&v120,&v60);
    func_002E3738(&v110,ledgeHero.up,-0.05f);
    func_002E3738(&v100,&vC0,step);
    travel=0.0f;
    func_002E3470(&vF0,&v100,&v110);
    func_002E34A0(&v100,&v100,&v110);
    func_002E3470(&vD0,&v120,&v100);
    func_002E3470(&vE0,&v120,&vF0);
    do {
        if(!func_002D3C80(&vE0,&vD0,4,ledgeHero.moby,0)) {
            if(out) {
                qcopy(out+0x10,&v120);
                func_002E3738(&v130,&vC0,0.5f);
                func_002E3738(out,ledgeHero.up,-drop);
                func_002E3470(out,&v130,out);
                func_002E3470(out,out+0x10,out);
                F(out,0x24)=func_002E3B10(vC0.f[0],vC0.f[1]);
                I(out,0x28)=1;
            }
            return 1;
        }
        qcopy(&v120,D_L01_001BF900.point);
        travel+=step;
        func_002E3470(&vE0,&v120,&vF0);
        func_002E3470(&vD0,&v120,&v100);
    } while(travel<limit);
    return 0;
}

