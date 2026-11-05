#include "common.h"
extern void func_00282CF0(void *, void *, void *);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
typedef int TI __attribute__((mode(TI)));
typedef float RingVec[4] __attribute__((aligned(16)));
typedef struct {RingVec v[4]; unsigned c[4]; float uv[4][2]; long g[4];} RingQuad;
extern int D_L01_001AF5D8 __attribute__((sda));
extern int D_L01_001AF5DC __attribute__((sda));
extern int D_L01_001AF5E0 __attribute__((sda));
extern int D_L01_001AF5E4 __attribute__((sda));
extern int D_L01_001AF5E8 __attribute__((sda));
extern int D_L01_001AF5F0[] SDATA(D_L01_001AF5F0);
extern float D_L01_001AF5F8[] SDATA(D_L01_001AF5F8);
extern float D_L01_001AF618 __attribute__((sda));
extern float D_L01_001AF620 __attribute__((sda));
extern float D_L01_001AF5FC[] MACRO_ADDR;
extern char D_00189F20[];
extern float D_L01_001B1FA4;
extern void func_00283658(void *,void *);
extern long func_0027C878(int);
extern void func_002AC9F8(void *,float);
extern unsigned func_00283D38(unsigned,unsigned,float);
extern void func_00282C90(void *);
extern void func_002833F0(void *,void *);
extern void func_L01_002E1510(void *,int,void *,int,void *);
/* Draws the moby's fading ring: four quads, one per row, repeated 32 times around it by the
 * batched draw, fading and growing as the radius in its vars shrinks. Row 0 takes the first
 * colour and the others the second. Adapted from RAC1 draw_moby_radius_ring (GPL-3.0). */
void func_L01_00398B50(char *m)
{
    RingQuad q[4];
    float mat[12];
    float pos[4];
    float transform[12];
    float rot[4];
    char *d=*(char **)(m+0x68);
    float alpha,h;
    int j,k;
    func_00283658(mat,m+0xc0);
    qcopy(pos,m+0x10);
    for(j=0;j<4;j++) {
        q[j].g[1]=func_0027C878(D_L01_001AF5E8);
        q[j].g[2]=0xFF9000000260L;
        q[j].g[3]=(long)D_L01_001AF5D8|((long)D_L01_001AF5DC<<2);
        q[j].g[3]|=(long)D_L01_001AF5E0<<4;
        q[j].g[3]|=(long)D_L01_001AF5E4<<6;
        q[j].g[3]|=0x8000L<<24;
        q[j].g[0]=0;
    }
    h=0.1f;
    alpha=(1.95f-F(d,0x34))*2.0f;
    if(alpha>1) alpha=1; else if(alpha<0) alpha=0;
    if(F(d,0x34)<1.15f) {
        float t, shrink;
        char *g;
        func_00282CF0(D_00189F20,m+0x10,D_00189F20-0x80);
        g=D_00189F20-0x100;
        I(g,0x108)=0;
        func_002AC9F8(D_00189F20,0.01666666753590107f);
        shrink=F(d,0x34);
        t=1.15f-shrink; if(t<0)t=0;
        {float fade=(0.2f-shrink)*5; if(fade<0)fade=0; D_L01_001B1FA4=fade;}
        h=t+0.1f;
        if(B(m,0x20)!=7 && B(m,0x20)!=8) {
            if(shrink<0.65f) {
                float v=shrink*1.5384615659713745f;
                *(short *)(g+0x2500)=1;
                F(g,0x2024)=v;F(g,0x2020)=v;F(g,0x2028)=2-v;
            } else *(short *)(g+0x2500)=0;
        }
    }
    {
    float scale=0.8f;
    int i;
    RingQuad *row;
    for(i=0;i<4;i++) {
        for(k=0;k<4;k++) {
            unsigned c;
            q[i].uv[k][0]=D_L01_001AF5F8[k*2];
            q[i].uv[k][1]=D_L01_001AF5FC[k*2];
            c=D_L01_001AF5F0[i!=0];
            q[i].c[k]=c;
            q[i].c[k]=func_00283D38(c&0xffffff,c,alpha);
            func_00282C90(q[i].v[k]);
            row=(RingQuad *)q[0].v[k];
            {float radius=F(d,0x34); if(i)radius+=0.01f; q[i].v[k][0]=radius;}
            if(k&1) {
                switch(i) {
                case 0:row[i].v[0][2]+=D_L01_001AF618+h;break;
                case 1:row[i].v[0][2]+=D_L01_001AF618+D_L01_001AF620;break;
                case 2:row[i].v[0][2]+=(D_L01_001AF618-h*scale)+D_L01_001AF620;break;
                case 3:row[i].v[0][2]+=(D_L01_001AF618+h*scale)+D_L01_001AF620;break;
                }
            } else {
                switch(i) {
                case 0:row[i].v[0][2]+=D_L01_001AF618-h;break;
                case 1:row[i].v[0][2]+=D_L01_001AF618-D_L01_001AF620;break;
                case 2:row[i].v[0][2]+=(D_L01_001AF618-h*scale)-D_L01_001AF620;break;
                case 3:row[i].v[0][2]+=(D_L01_001AF618+h*scale)-D_L01_001AF620;break;
                }
            }
        }
    }
    }
    *(TI *)rot=0;rot[2]=0.19634954631328583f;
    func_002833F0(transform,rot);
    func_L01_002E1510(q,4,transform,32,mat);
}
