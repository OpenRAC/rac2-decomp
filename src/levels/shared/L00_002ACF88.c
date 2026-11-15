#include "common.h"
typedef int V4_Fbfdc087a __attribute__((mode(TI)));

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
extern LedgeProbeResident D_00189E20;
/* Related ledge-probe flow: OpenRAC/rac1-decomp hero_idle_and_animation.c,
 * check_ledge_grab (GPL-3.0); this version uses oriented vector helpers. */
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00283180(float);
extern float func_00283248(float, float);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern float func_L00_002D3EA8(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern char *func_002AB1F0(void *);
extern char *func_002AD0B0(void *);
extern int func_00277258(void *, int, void *, float);
typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    unsigned char pad1c[4];
    float position[4];
    unsigned char pad30[16];
    float normal[4];
} LedgeProbeHit;
extern LedgeProbeHit D_L00_001BF200;
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
int func_L00_002ACF88(void *position, void *unused, char *out)
{
    float v0[4], v1[4], v2[4], v3[4], v4[4], v5[4], v6[4], v7[4], v8[4], v9[4], v10[4], v11[4], v12[4], v13[4], v14[4], v15[4], v16[4], v17[4], v18[4], v19[4];
    char *a, *b;
    void *object;
    int go, found, i, kind, ok;
    int edge, j;
    float height;
    float step, max;
    float down, fwd, up, top, drop, rise, back, d, length;
    if (out) IN(out,0x28)=0;
    if (D_00189E20.cooldown) return 0;
    go=0;
    if (D_00189E20.vehicle==0) {
        if ((D_00189E20.control==4 && (D_00189E20.pastApex || func_L00_002D3B00((char *)&D_00189E20+0xf0)<0.05833333730697632f)) || D_00189E20.control==2 || D_00189E20.state==8 || D_00189E20.state==25 || D_00189E20.state==26) go=1;
        if (D_00189E20.state==14 && D_00189E20.frame<37.0f) go=0;
    }
    if (D_00189E20.vehicle==1) {
        if ((D_00189E20.control==4 && D_00189E20.pastApex) || D_00189E20.control==2 || D_00189E20.state==75 || D_00189E20.state==73 || D_00189E20.state==74) go=1;
    }
    if (out != (char *)&D_00189E20+0x550) go=1;
    if (!go) return 0;
    down=-0.7f; fwd=0.3f; up=1.5f; top=1.15f; drop=-1.43f; rise=1.8f; back=0.5f;
    found=0;
    if (D_00189E20.vehicle==1) { down=-0.4f; fwd=0.25f; up=0.725f; top=0.7f; drop=-0.71f; rise=0.7f; back=0.32f; }
    qcopy(v0,position);
    vec_scale_to_length(v4,(char *)&D_00189E20,D_00189E20.radius);
    FastVecAdd(v0,v0,v4);
    vec_scale_to_length(v4,(char *)&D_00189E20+0x20,up+0.15f);
    FastVecAdd(v1,v0,v4);
    vec_scale_to_length(v4,(char *)&D_00189E20+0x20,-top);
    FastVecAdd(v2,v0,v4);
    vec_scale_to_length(v3,(char *)&D_00189E20,fwd*0.25f);
    for(i=0; i<4; i++) {
        FastVecAdd(v1,v1,v3);
        FastVecAdd(v2,v2,v3);
        if(CollLine(v1,v2,4,D_00189E20.moby,0)) {
            kind=GetCollHitMaterial();
            if(kind!=9 && kind!=12 && kind!=0 && func_L00_002D3EA8(D_L00_001BF200.normal)<0.349065899848938f) found=1;
        }
        if(found) break;
    }
    object=0;
    if(!found) goto fail;
    if(D_L00_001BF200.moby) {
        ok=0;
        a=func_002AB1F0(D_L00_001BF200.moby);
        b=func_002AD0B0(D_L00_001BF200.moby);
        if(a && (*(unsigned short *)(a+0x1e)&1)) ok=1;
        else if(b) ok=IN(b,0x3c)&1;
        if(!ok) return 0;
        object=D_L00_001BF200.moby;
    }
    if(out) *(void **)(out+0x38)=D_L00_001BF200.moby;
    qcopy(v6,D_L00_001BF200.position);
    FastVecSub(v5,v6,position);
    if(up<func_L00_002D3B00(v5)) return 0;
    vec_scale_to_length(v7,(char *)&D_00189E20+0x20,0.005f);
    FastVecAdd(v7,v7,v6);
    vec_scale_to_length(v8,(char *)&D_00189E20,-1.0f);
    FastVecAdd(v8,v8,v7);
    if(CollLine(v8,v7,2,D_00189E20.moby,0)) {
        if(!D_L00_001BF200.moby || D_L00_001BF200.moby!=object) return 0;
    }
    if(out) {
        vec_scale_to_length(v9,(char *)&D_00189E20+0x20,0.6f);
        FastVecAdd(v9,v9,v6);
        if(func_00277258(v9,4,D_00189E20.moby,0.45f)) IN(out,0x34)|=1;
        else IN(out,0x34)&=~1;
    }
    height=func_L00_002D3B00(v5);
    if(height+D_00189E20.groundHeight<rise || height<0.5f) return 0;
    *(V4_Fbfdc087a *)v11=0; FL(v11,0)=1.0f; FL(v11,8)=down;
    matrix_mul_vec3(v11,v11,(char *)&D_00189E20);
    edge=0;
    FastVecAdd(v11,v11,v6);
    FastVecSub(v9,position,v11);
    func_L00_002D3B58(v9,v9,0.0f);
    FastVecAdd(v9,v9,v11);
    vec_scale_to_length(v10,(char *)&D_00189E20+0x20,-down*0.2f);
    for(j=0;j<5;j++) {
        if(CollLine(v9,v11,2,0,0)) {
            vec_scale_to_length(v12,D_L00_001BF200.normal,1.0f);
            edge=1;
            func_L00_002D3B58(v12,v12,0.0f);
            break;
        }
        FastVecAdd(v9,v9,v10);
        FastVecAdd(v11,v11,v10);
    }
    if(!edge) return 0;
    length=FastVecDot((char *)&D_00189E20,v12);
    if(!(length<func_00283180(1.134464144706726f))) return 0;
    step=0.03f;
    max=2.4f;
    qcopy(v18,v6);
    vec_scale_to_length(v17,(char *)&D_00189E20+0x2c0,-0.05f);
    vec_scale_to_length(v16,v12,step);
    FastVecAdd(v15,v16,v17);
    FastVecSub(v16,v16,v17);
    FastVecAdd(v13,v18,v16);
    FastVecAdd(v14,v18,v15);
    for(d=0.0f;d<max;d+=step) {
        if(!CollLine(v14,v13,4,D_00189E20.moby,0)) {
            if(out) {
                qcopy(out+0x10,v18);
                vec_scale_to_length(v19,v12,back);
                vec_scale_to_length(out,(char *)&D_00189E20+0x2c0,-drop);
                FastVecAdd(out,v19,out);
                FastVecAdd(out,out+0x10,out);
                FL(out,0x24)=func_00283248(FL(v12,0),FL(v12,4));
                IN(out,0x28)=1;
            }
            return 1;
        }
        qcopy(v18,D_L00_001BF200.position);
        FastVecAdd(v14,v18,v15);
        FastVecAdd(v13,v18,v16);
    }
fail:
    return 0;
}
#undef FL
#undef IN
