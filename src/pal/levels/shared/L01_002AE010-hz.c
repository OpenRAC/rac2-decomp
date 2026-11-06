/* func_PAL_L01_002AE010, the PAL copy of func_L01_002AE128: the same C, where 0.05833333730697632f
   becomes 0.07000001f. */
#include "common.h"

extern void func_002E3738(void *, void *, float);

extern void func_002E3470(void *, void *, void *);

extern void func_002E34A0(void *a0, void *a1, void *a2);

extern void func_002E3918(void *a0, void *a1, void *a2);

extern float func_002E3B10(float f12, float f13);

typedef int LedgeQuad __attribute__((mode(TI)));
typedef struct {
unsigned char pad0[464];
short cooldown;
unsigned char pad1d2[146];
float radius;
unsigned char pad268[180];
float groundHeight;
unsigned char pad320[382];
unsigned char pastApex;
unsigned char pad49f[1945];
float frame;
unsigned char padc3c[5716];
void * moby;
int state;
unsigned char pad2298[4];
int control;
unsigned char pad22a0[20];
unsigned char vehicle;
} LedgeProbeResident;
extern LedgeProbeResident ledgeHero __asm__("D_00189E20");
extern float func_002C9280(void *);
extern void func_002C92D8(void *, void *, float);
extern float func_002C9628(void *);
extern float func_002E3560(void *, void *);
extern float func_002E3A48(float);
extern int func_002D3C80(void *, void *, int, void *, int);
extern int func_002D77E8(void);
extern char *func_003148A0(void *);
extern char *func_00316D00(void *);
extern int func_002D4CE0(void *, int, void *, float);
typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    unsigned char pad1c[4];
    float position[4];
    unsigned char pad30[16];
    float normal[4];
} LedgeProbeHit;
extern LedgeProbeHit ledgeHit __asm__("D_L01_001BF900");
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
/* The ledge probe of func_L00_002ACF88 without its vehicle == 1 branch. */
int func_PAL_L01_002AE010(void *position, void *unused, char *out)
{
    float v0[4], v1[4], v2[4], v3[4], v4[4], v5[4], v6[4], v7[4], v8[4], v9[4], v10[4], v11[4], v12[4], v13[4], v14[4], v15[4], v16[4], v17[4], v18[4], v19[4];
    char *a, *b;
    void *object;
    int go, found, i, kind, ok;
    int edge, j;
    float height;
    float step, max;
    float down, top, drop, d, length;
    LedgeProbeResident *hero;
    if (out) IN(out,0x28)=0;
    if (ledgeHero.cooldown) return 0;
    go=0;
    if (ledgeHero.vehicle==0) {
        if ((ledgeHero.control==4 && (ledgeHero.pastApex || func_002C9280((char *)&ledgeHero+0xf0)<0.07000001f)) || ledgeHero.control==2 || ledgeHero.state==8 || ledgeHero.state==25 || ledgeHero.state==26) go=1;
        if (ledgeHero.state==14 && ledgeHero.frame<37.0f) go=0;
    }
    if (out != (char *)&ledgeHero+0x550) go=1;
    if (!go) return 0;
    hero=&ledgeHero;
    down=-0.7f; top=1.15f; drop=-1.43f;
    found=0;
    qcopy(v0,position);
    func_002E3738(v4,hero,hero->radius);
    func_002E3470(v0,v0,v4);
    func_002E3738(v4,(char *)&ledgeHero+0x20,1.65f);
    func_002E3470(v1,v0,v4);
    func_002E3738(v4,(char *)&ledgeHero+0x20,-top);
    func_002E3470(v2,v0,v4);
    func_002E3738(v3,hero,0.075f);
    for(i=0; i<4; i++) {
        func_002E3470(v1,v1,v3);
        func_002E3470(v2,v2,v3);
        if(func_002D3C80(v1,v2,4,ledgeHero.moby,0)) {
            kind=func_002D77E8();
            if(kind!=9 && kind!=12 && kind!=0 && func_002C9628(ledgeHit.normal)<0.349065899848938f) found=1;
        }
        if(found) break;
    }
    object=0;
    if(!found) goto fail;
    if(ledgeHit.moby) {
        ok=0;
        a=func_003148A0(ledgeHit.moby);
        b=func_00316D00(ledgeHit.moby);
        if(a && (*(unsigned short *)(a+0x1e)&1)) ok=1;
        else if(b) ok=IN(b,0x3c)&1;
        if(!ok) return 0;
        object=ledgeHit.moby;
    }
    if(out) *(void **)(out+0x38)=ledgeHit.moby;
    qcopy(v6,ledgeHit.position);
    func_002E34A0(v5,v6,position);
    if(1.5f<func_002C9280(v5)) return 0;
    func_002E3738(v7,(char *)&ledgeHero+0x20,0.005f);
    func_002E3470(v7,v7,v6);
    func_002E3738(v8,(char *)&ledgeHero,-1.0f);
    func_002E3470(v8,v8,v7);
    if(func_002D3C80(v8,v7,2,ledgeHero.moby,0)) {
        if(!ledgeHit.moby || ledgeHit.moby!=object) return 0;
    }
    if(out) {
        func_002E3738(v9,(char *)&ledgeHero+0x20,0.6f);
        func_002E3470(v9,v9,v6);
        if(func_002D4CE0(v9,4,ledgeHero.moby,0.45f)) IN(out,0x34)|=1;
        else IN(out,0x34)&=~1;
    }
    height=func_002C9280(v5);
    if(height+ledgeHero.groundHeight<1.8f || height<0.5f) return 0;
    *(LedgeQuad *)v11=0; FL(v11,0)=1.0f; FL(v11,8)=down;
    func_002E3918(v11,v11,(char *)&ledgeHero);
    edge=0;
    func_002E3470(v11,v11,v6);
    func_002E34A0(v9,position,v11);
    func_002C92D8(v9,v9,0.0f);
    func_002E3470(v9,v9,v11);
    func_002E3738(v10,(char *)&ledgeHero+0x20,-down*0.2f);
    for(j=0;j<5;j++) {
        if(func_002D3C80(v9,v11,2,0,0)) {
            func_002E3738(v12,ledgeHit.normal,1.0f);
            edge=1;
            func_002C92D8(v12,v12,0.0f);
            break;
        }
        func_002E3470(v9,v9,v10);
        func_002E3470(v11,v11,v10);
    }
    if(!edge) return 0;
    length=func_002E3560((char *)&ledgeHero,v12);
    if(!(length<func_002E3A48(1.134464144706726f))) return 0;
    step=0.03f;
    max=2.4f;
    qcopy(v18,v6);
    func_002E3738(v17,(char *)&ledgeHero+0x2c0,-0.05f);
    func_002E3738(v16,v12,step);
    func_002E3470(v15,v16,v17);
    func_002E34A0(v16,v16,v17);
    func_002E3470(v13,v18,v16);
    func_002E3470(v14,v18,v15);
    for(d=0.0f;d<max;d+=step) {
        if(!func_002D3C80(v14,v13,4,ledgeHero.moby,0)) {
            if(out) {
                qcopy(out+0x10,v18);
                func_002E3738(v19,v12,0.5f);
                func_002E3738(out,(char *)&ledgeHero+0x2c0,-drop);
                func_002E3470(out,v19,out);
                func_002E3470(out,out+0x10,out);
                FL(out,0x24)=func_002E3B10(FL(v12,0),FL(v12,4));
                IN(out,0x28)=1;
            }
            return 1;
        }
        qcopy(v18,ledgeHit.position);
        func_002E3470(v14,v18,v15);
        func_002E3470(v13,v18,v16);
    }
fail:
    return 0;
}
