/* func_PAL_L18_0043C3F4, the PAL copy of func_L18_00437190: the same C at 50 Hz. The particle lifetime
   120 becomes 100, written in its arm; the tuning counts go through ((x) * 5 + 2) / 6; the speed step
   D_L18_001B1918 is scaled by 1.2f; 0.016666668f becomes 0.020000001f and the spin clamp follows.
   func_002BDCE8 becomes func_PAL_002BE9A8, func_L18_00437BA8 becomes func_PAL_L18_0043CE90 and
   func_002ABBB8 becomes func_PAL_002AC718. */
#include "common.h"
#define H(p,o) (*(short *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern int func_002B3868(void *);
extern int func_002E5CF8(int,int,void *);
extern void func_00282CC0(char *,char *,char *);
extern void func_002A7750(void *,int,int);
extern int func_00282978(void *);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern float func_002A7878(float,float);
extern void func_L00_0031D670(void *,void *,void *,float);
typedef struct { int pad0; int flags; u8 pad8[2]; u8 alpha; u8 lifetime; } ParticleRender;
typedef struct { u8 pad0[0xa]; s16 lifetime; u8 padc[0x14]; ParticleRender render; } Particle;
extern Particle *func_PAL_002BE9A8(void *,float,float,float,float,int,void *,int,int);
extern int func_002761F8(void *,void *,int,void *,int);
extern int func_00277258(void *,int,void *,float);
extern void func_00282F20(char *,char *,float);
extern void func_00283028(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282E20(void *);
extern void func_00282F70(void *,void *,float);
extern int func_00283CF0(float);
extern int func_00282948(void *);
extern void func_PAL_L18_0043CE90(void *,int);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_0029F338(void *);
extern int func_00277F48(void *,int,void *,int,float);
extern void func_002A8F70(void *,void *,int,void *,void *,float);
extern float func_00283B98(float,float);
typedef int TI128 __attribute__((mode(TI)));
extern TI128 D_001A8F20 MACRO_ADDR;
extern u8 D_L18_001BFC00[];
extern u8 D_00189E20[];
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; u8 *p[0x980]; TI128 q[0x260]; } HeroView;
typedef union { u8 b[0x100]; s16 h[0x80]; u16 u[0x80]; s32 i[0x40]; float f[0x40]; u8 *p[0x40]; TI128 q[0x10]; } ObjectView;
#define OBJ ((ObjectView *)obj)
#define STATE ((ObjectView *)st)
typedef union { u8 b[0x60]; float f[0x18]; u8 *p[0x18]; TI128 q[6]; } CollisionView;
#define HERO ((HeroView *)D_00189E20)
#define COLL ((CollisionView *)D_L18_001BFC00)
extern u8 *D_L18_001C3C80[];
extern float D_L18_001B1940[3];
extern float D_L18_001B18F8 __attribute__((sda));
extern int D_L18_001B18FC __attribute__((sda));
extern int D_L18_001B1900 __attribute__((sda));
extern int D_L18_001B1904 __attribute__((sda));
extern float D_L18_001B1908 __attribute__((sda));
extern float D_L18_001B190C __attribute__((sda));
extern float D_L18_001B1910 __attribute__((sda));
extern float D_L18_001B1914 __attribute__((sda));
extern float D_L18_001B1918 __attribute__((sda));
extern float D_L18_001B1924 __attribute__((sda));
extern float D_L18_001B1928 __attribute__((sda));
extern int D_L18_001B192C __attribute__((sda));
extern int D_L18_001B1930 __attribute__((sda));
extern float D_L18_001B1934 __attribute__((sda));
extern int D_L18_001B1938 __attribute__((sda));
static inline int same_group(u8 *st) {
    int valid=0;
    if(COLL->p[6] && STATE->p[0x9]) valid=H(COLL->p[6],0xaa)==H(STATE->p[0x9],0xaa);
    return valid;
}
static inline float clamp_speed(float speed, float low, float high) {
    if(speed<low) speed=low;
    if(speed>high) speed=high;
    return speed;
}
void func_PAL_L18_0043C3F4(u8 *obj) {
    float delta[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    u8 *st=OBJ->p[0x1a], *p, *other;
    u8 **targets;
    int i, n, mode=obj[0x20], amount, r,g,b;
    float t, x, minimum;
    switch(mode) {
    case 0: case 1:
        if(func_002B3868(obj)) func_002E5CF8(1,0,obj);
        func_00282CC0((char *)delta,(char *)obj+0x10,(char *)st+0x10);
        STATE->f[0x6]-=STATE->f[0x7];
        if(obj[0x20]==1 && STATE->f[0x6]<0) func_002A7750(obj,0,-1);
        func_00282978(st+0x28);
        {s16 life=STATE->h[0x14];
        if(life) {
            for(i=0;i<D_L18_001B1900;i++) {
                float ratio, denominator, random, fraction;
                Particle *spark;
                *(TI128 *)temp=*(TI128 *)(obj+0x10);
                fraction=(float)i; fraction*=0.3333f;
                func_L00_0031D670(pos,temp,delta,fraction);
                amount=func_002A77E0(6);
                if(func_002A77E0(2)) amount=-amount;
                denominator=func_00283CE0((D_L18_001B18FC*5+2)/6);
                ratio=(float)STATE->h[0x14]; ratio/=denominator;
                random=func_002A7878(0.9f,1.0f);
                spark=func_PAL_002BE9A8(pos,D_L18_001B1910,1,1,random*(D_L18_001B1908+(D_L18_001B190C-D_L18_001B1908)*ratio),amount,&D_001A8F20,D_L18_001B1904,0);
                if(spark) { ParticleRender *particle; spark->lifetime=100; particle=&spark->render; particle->flags=2; particle->alpha=127; particle->lifetime=*(u8 *)&spark->lifetime; }
            }
        }
        }
        if(func_002761F8(obj+0x10,delta,0,obj,0) && !same_group(st)) qcopy(obj+0x10,&COLL->q[2]);
        else qcopy(obj+0x10,delta);
        if(func_00277258(obj+0x10,0,obj,D_L18_001B18F8) && (obj[0x20]==0 || OBJ->f[0x6]-COLL->f[10]<0)) {
            if(!same_group(st)) {
                func_00282F20((char *)pos,(char *)(u8 *)&COLL->q[4],D_L18_001B18F8);
                func_00282CC0((char *)obj+0x10,(char *)(u8 *)&COLL->q[2],(char *)pos);
                func_00283028(st+0x10,st+0x10,(u8 *)&COLL->q[4]);
                func_002E5CF8(1,0,obj);
                if(obj[0x20]!=0) goto bounce_done;
                func_002A7750(obj,1,-1);
                if(++STATE->h[0x15]==1) {
                    func_00282F70(st+0x10,st+0x10,D_L18_001B1928*0.020000001f);
                    STATE->f[0x6]*=D_L18_001B1924;
                } else {
                    func_00282D30(temp,st+0x10,D_L18_001B1924);
                    if(func_00282E20(temp)<D_L18_001B1914*0.020000001f) {
                        func_00282F70(st+0x10,st+0x10,D_L18_001B1914*0.020000001f);
                        STATE->f[0x6]*=D_L18_001B1924;
                    } else qcopy(st+0x10,temp);
                }
bounce_done:
                if(STATE->h[0x15]>=4) {
                    func_002A7750(obj,2,-1); STATE->f[0x6]=0;
                    STATE->f[0x7]=func_00282E20(st+0x10);
                    STATE->f[0x7]*=D_L18_001B1924;
                    minimum=D_L18_001B1914*0.020000001f;
                    if(STATE->f[0x7]<minimum) STATE->f[0x7]=minimum;
                    func_00282F20((char *)st+0x10,(char *)st+0x10,STATE->f[0x7]);
                    STATE->f[0xb]=1.0f/func_00283CE0(STATE->i[0x8]);
                }
            }
        }
        break;
    case 2:
        { typedef struct { float a,b,c; } Triple; *(Triple *)delta=*(Triple *)D_L18_001B1940; }
        t=(float)STATE->i[0x8]*STATE->f[0xb];
        r=func_00283CF0((delta[0]-255.0f)*t+255.0f);
        g=func_00283CF0(delta[1]*t); b=func_00283CF0(delta[2]*t);
        {u32 color=(u32)b<<16; color|=0xff000000; color|=g<<8; color|=r; OBJ->i[0x1e]=color;}
        {float speed=STATE->f[0x7]*((D_L18_001B1918-1.0f)*1.2f+1.0f);
        minimum=D_L18_001B1914*0.020000001f;
        STATE->f[0x7]=speed;
        if(speed<minimum) STATE->f[0x7]=minimum;}
        func_00282F20((char *)st+0x10,(char *)st+0x10,STATE->f[0x7]);
        func_00282CC0((char *)obj+0x10,(char *)obj+0x10,(char *)st+0x10);
        if(func_00282948(st+0x20)) func_002A7750(obj,3,-1);
        break;
    case 3:
        if(func_002B3868(obj)) {
            func_PAL_L18_0043CE90(obj+0x10,D_L18_001B1938);
            func_PAL_002AC718(obj,st+0x10,obj+0x10,0,0,3,3,5,1,0.2f,9,1,-1,0,1,1,-1,0,0x810001);
            func_002E5CF8(0,0,obj);
        }
        else {
        if(((D_L18_001B192C+D_L18_001B1930)*5+2)/6<OBJ->u[0x4b]) {func_0029F338(obj);return;}
        x=D_L18_001B1934;
        if(OBJ->u[0x4b]<(D_L18_001B192C*5+2)/6) x=x*(float)OBJ->u[0x4b]/(float)((D_L18_001B192C*5+2)/6);
        n=func_00277F48(obj+0x10,0,obj,0,x);
        if(!n) break;
        if(n>0) {
        int remaining;
        targets=D_L18_001C3C80;
        remaining=n;
        do {
            u8 *other=*targets;
            int valid=0;
            if(other==HERO->p[0x2290/4]) {qcopy(delta,&HERO->q[8]); if(HERO->i[0x340/4]) valid=1;}
            else {qcopy(delta,other+0x10); if(U(other,0x34)&0x20) {u8 *owner=P(P(other,0x68),0x18);if(owner) {if(H(owner,0xc0)) valid=1;}}}
            if(valid) func_002A8F70(other,obj,0x10001,other+0x10,&D_001A8F20,STATE->f[0xc]);
            targets++;
        } while(--remaining);
        }
        }
        break;
    }
    if(OBJ->u[0x4b]<65535) OBJ->u[0x4b]++;
    {
        float speed, angle;
        if(obj[0x20]<2) speed=func_00282E20(st+0x10);
        else if(obj[0x20]==2) speed=STATE->f[0x7];
        else return;
        speed=clamp_speed(speed,0.004f,0.120000005f);
        speed-=0.004f;
        angle=0.116000004f;
        angle=speed/angle;
        angle*=7.0f;
        angle+=1.0f;
        angle*=0.017453294f;
        OBJ->f[0x3d]=func_00283B98(angle,OBJ->f[0x3d]);
    }
    if(OBJ->f[0x4]<2 || OBJ->f[0x4]>1021 || OBJ->f[0x5]<2 || OBJ->f[0x5]>1021 || OBJ->f[0x6]<2 || OBJ->f[0x6]>1021)func_0029F338(obj);
}
