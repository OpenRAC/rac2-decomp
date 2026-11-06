/* func_PAL_L22_003BCCAC, the PAL copy of func_L22_003B9450: the same C, where (all 50 Hz values)
   the charge divisor 0.033333335f becomes 0.039473683f, the light argument 20 becomes 17,
   0.33333334f becomes 0.40000004f, the launch 0.6666667f becomes 0.8000001f, ctx+0x50's 1.0f becomes 1.2f,
   the >=6 test becomes >=5, 0.39999998f becomes 0.27999997f, the 50 limit and countdown become 42,
   the >5 clamp becomes >4, 0.016666668f becomes 0.020000001f and the 45 argument becomes 37. */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
/* Retail state update, reconstructed from USA v1.01 level 22. */
#define F32(p,o) (*(float *)((char *)(p)+(o)))
#define I32(p,o) (*(int *)((char *)(p)+(o)))
#define S16(p,o) (*(short *)((char *)(p)+(o)))
#define U8(p,o) (*(unsigned char *)((char *)(p)+(o)))
typedef struct {
    char prefix[0x80]; Vec position;
    char gap90[8]; float angle;
    char gap9c[0x2290-0x9c]; int object;
    char gap2294[0x20]; unsigned char state;
} Hero;
extern Hero D_00189E20;
extern char *D_L22_001AFA08 __attribute__((sda)), *D_L22_001AFA0C __attribute__((sda));
extern int D_L22_001AFA00 __attribute__((sda)), D_L22_001AFA04 __attribute__((sda));
extern float D_L22_001AF9DC __attribute__((sda)), D_L22_001AF9E0 __attribute__((sda));
extern float D_L22_001AF9EC __attribute__((sda)), D_L22_001AF9F0 __attribute__((sda));
extern float D_L22_001AF9F4 __attribute__((sda)), D_L22_001AF9F8 __attribute__((sda)), D_L22_001AF9FC __attribute__((sda));
extern int D_L22_001A8FF0 MACRO_ADDR, D_L22_001A8AB0 MACRO_ADDR;
typedef struct { int enabled; unsigned int color; unsigned long long command; } ScreenEffect;
extern ScreenEffect D_L22_001A8AC0 MACRO_ADDR;
extern int D_L22_001B1C48 MACRO_ADDR;
typedef struct { float size, secondary, unknown[2]; float position[3], radius; } Effect;
extern Effect D_L22_001C7E00[];
extern char D_L22_001C4140[], D_L22_001A8F20[] MACRO_ADDR;
extern float D_L22_001B2AA4 MACRO_ADDR, D_L22_001B2A9C MACRO_ADDR;
extern unsigned char *D_L22_001FF82C __attribute__((nosda));
extern float func_00283CE0(int);
extern int func_00283CF0(float), func_002A7820(int,int), func_002A77E0(int);
extern float func_002A7878(float,float), func_00283180(float), func_00283198(float), func_00282C10(float);
extern void func_00282F20(void *,void *,float), func_00282D30(void *,void *,float);
extern void func_00282CD8(void *,void *,void *), func_00282CC0(void *,void *,void *), func_00282CF0(void *,void *,void *);
extern void func_PAL_L22_0033BBB0(int,void *,void *), func_L22_00334F78(void *,int,int,int,int,float,float);
extern int func_00291308(void *,float,float,int);
extern void func_002E59F8(int), func_0029F338(char *), func_00291450(int);
extern int func_L00_0035F5A0(int,int,int);
extern void func_002AFFD8(void *,void *,int), func_L00_00325600(void *,void *,int);
extern void func_00283958(void *,void *), func_00283738(void *,void *,void *);
extern float func_00282DF0(void *),func_00282DB0(void *,void *),func_00282E48(void *,void *),func_002B0360(void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_L00_00320B70(void *,void *,void *,void *,float,float,float,void *,float,void *);
extern void func_L22_003A2988(void *,float);
extern int func_00277F48(void *,int,void *,int,float);
extern void func_002A9850(void *,void *,void *,int,int,int,int,int,float,float,float);
extern char *func_PAL_L00_003FB330(void *,int,int,int,float,float,int,int,int,int,int,int,int,void *);
extern void func_L04_00358868(void *,int,int,int,float);
extern void func_002A7988(void *,float,float);
/* Same registers as its definition: integers a0-t3 then one stack word, the float in $f12. */
extern void *func_PAL_002BD790(void *,void *,int,int,float,int,int,int,int,int);
extern char *func_PAL_L08_0034C4A8(void *,void *,int,void *);
typedef struct { char prefix[0x10]; float inverse; char gap[2]; short kind; int color; } ParticleTail;
void func_PAL_L22_003BCCAC(char *obj) {
    struct { Vec point, velocity, ground, motion, matrix[3], rotation, direction, scratch, intercept, result, predicted; } frame;
    char *ctx = *(char **)(obj+0x68);
    char **slot = &D_L22_001AFA0C;
    int hit;
    float radius, scale, length, turn;
    if (I32(obj,0xB8)==D_00189E20.object) slot=&D_L22_001AFA08;
    switch (U8(obj,0x20)) {
    case 0: {
        float charge, intensity, size;
        int r, g, b, count;
        if (S16(ctx,0x2E) && (D_00189E20.state==2 || !S16(ctx,0x40))) {
            if (!I32(ctx,0x10) && slot==&D_L22_001AFA0C) { D_L22_001A8AC0.enabled=1; D_L22_001A8AC0.color=0xFFFF00; }
            charge=func_00283CE0(++I32(ctx,0x10))*0.039473683f;
            if(charge>1.0f) charge=1.0f;
            if(S16(ctx,0x40)) charge *= charge*10.0f;
            else charge *= charge*5.0f;
            { int i; for(i=0;i<func_00283CF0(charge);i++) {
                int r, g, b;
                u32 color;
                frame.velocity.q=0;
                frame.velocity.f[0]=func_002A7878(-1.0f,1.0f);
                frame.velocity.f[1]=func_002A7878(-1.0f,1.0f);
                frame.velocity.f[2]=func_002A7878(-1.0f,1.0f);
                frame.point.q=frame.velocity.q;
                if(S16(ctx,0x40)) {r=79;g=175;b=255;} else {r=111;g=31;b=15;}
                g=func_002A7820(r,g); b=func_002A7820(r,b);
                if(b>255)b=255; if(g>255)g=255;
                func_00282F20(&frame.point,&frame.point,func_002A7878(15.0f,30.0f));
                func_00282CD8(&frame.velocity,&frame.point,obj+0x10);
                color=((u32)g<<8)|0x7F000000;
                func_PAL_L22_0033BBB0(((u32)b<<16|color)|r,&frame.point,obj);
            } }
            if(I32(ctx,0x10)<50) {
                int alpha=D_L22_001A8AC0.color>>24;
                if(!D_L22_001A8AC0.command && alpha==255) alpha=37;
                D_L22_001A8AC0.command=0x1F00000042ULL;
                { int previous=alpha; alpha++; if (previous>=36) alpha=37; }
                D_L22_001A8AC0.color=(D_L22_001A8AC0.color&0xFFFF00)|(alpha<<24);
            } else D_L22_001A8AC0.color |= 0xFF000000;
            if(S16(ctx,0x2C)!=-1) {
                Effect *effects=D_L22_001C7E00; char *lights,*light;
                effects[S16(ctx,0x2C)].position[0]=F32(obj,0x10);
                effects[S16(ctx,0x2C)].position[1]=F32(obj,0x14);
                effects[S16(ctx,0x2C)].position[2]=F32(obj,0x18);
                count=I32(ctx,0x10); if(count>50)count=50; if(count<0)count=0;
                effects[S16(ctx,0x2C)].radius=func_00283CE0(count)*0.14f;
                intensity=func_00283CE0(I32(ctx,0x10))*0.039473683f; if(intensity>1.0f)intensity=1.0f;
                lights=(char *)effects->position; light=lights+S16(ctx,0x2C)*32;
                r=func_002A7820(15,47)&255;g=func_002A7820(47,63)&255;b=func_002A7820(63,127)&255;
                func_L22_00334F78(light,r,g,b,17,intensity*840000.0f,0.0f);
                effects[S16(ctx,0x2C)].size=func_002A7878(effects[S16(ctx,0x2C)].size*0.8f,effects[S16(ctx,0x2C)].radius*2.0f*0.14285715f);
                size=effects[S16(ctx,0x2C)].size;
                {
                    float secondary=effects[S16(ctx,0x2C)].secondary*0.8f;
                    effects[S16(ctx,0x2C)].secondary=func_002A7878(secondary>size?size:secondary,size);
                }
            } else if(!(D_L22_001B1C48&3)) S16(ctx,0x2C)=func_00291308(obj+0x10,0.0f,0.0f,0);
        } else {
            D_L22_001A8AB0=0; D_L22_001A8AC0.enabled=0;I32(ctx,0x10)=0;
            func_L00_0035F5A0(22,0,0);
            if(S16(ctx,0x40)) { if(D_L22_001AFA00!=-1) {func_002E59F8(D_L22_001AFA00);D_L22_001AFA00=func_L00_0035F5A0(21,0,0);} }
            else if(D_L22_001AFA04!=-1) {func_002E59F8(D_L22_001AFA04);D_L22_001AFA04=func_L00_0035F5A0(21,0,0);}
            if(!D_L22_001A8FF0) {
                F32(ctx,0)=func_00283180(D_00189E20.angle)*0.8000001f;
                F32(ctx,4)=func_00283198(D_00189E20.angle)*0.8000001f;F32(ctx,8)=0.0f;U8(obj,0x20)=1;
            } else {func_00282D30(ctx,obj+0xC0,2.0f);U8(obj,0x20)=1;}
            I32(ctx,0x14)=0;
        }
    } break;
    case 1: {
        radius=func_00283CE0(I32(ctx,0x14))*0.40000004f+1.3f;
        I32(ctx,0x14)++;scale=radius+3.5f;radius*=0.5f;
        func_002AFFD8(obj+0x10,&frame.ground,1);
        if (S16(ctx,0x40)) func_00282F20(&frame.motion,obj+0xC0,2.0f);
        else func_00282F20(&frame.motion,obj+0xC0,D_L22_001AF9F8);
        func_00282F20(&frame.direction,&frame.ground,1.0f);
        func_00282DD8(&frame.rotation,obj+0xE0,&frame.direction);
        turn=S16(ctx,0x40)?D_L22_001AF9E0:D_L22_001AF9DC;
        func_00282D30(&frame.rotation,&frame.rotation,turn);
        length=func_00282DF0(&frame.rotation);
        frame.rotation.f[3]=-func_00282C10(1.0f-length*length);
        func_00283958(&frame.rotation,frame.matrix);
        func_00283738(obj+0xC0,frame.matrix,obj+0xC0);
        if(S16(ctx,0x40)) {
            if(func_00282E48(&D_00189E20.position,obj+0x10)<D_L22_001AF9FC) { I32(ctx,0x44)=0;S16(ctx,0x42)=0; }
        } else {func_00282D30(&frame.motion,ctx+0x50,1.2f);func_00282F20(&frame.scratch,&frame.motion,1.0f);qcopy(obj+0xC0,&frame.scratch);}
        if(I32(ctx,0x44) && S16(ctx,0x40) && S16(ctx,0x42) && I32(ctx,0x14)>=5) {
            func_00282CF0(&frame.scratch,obj+0x10,*(char **)(ctx+0x44)+0x10);
            if(func_00282DB0(&frame.scratch,&frame.motion)<0.0f) {
                func_00282D30(&frame.predicted,*(char **)(ctx+0x44)+0xE0,D_L22_001AF9EC);
                func_00282CC0(&frame.result,*(char **)(ctx+0x44)+0x10,&frame.predicted);
                func_L00_00320B70(obj+0x10,obj+0xC0,&frame.result,ctx+0x48,D_L22_001AF9F0,D_L22_001AF9F4,0.0f,&frame.ground,0.0f,&frame.intercept);
                func_00282F20(obj+0xC0,obj+0xC0,1.0f);func_00282D30(&frame.motion,obj+0xC0,2.0f);
            }
        }
        *(Quad *)ctx=frame.motion.q;
        if(S16(ctx,0x2C)!=-1) {
            Effect *effects=D_L22_001C7E00;
            effects[S16(ctx,0x2C)].radius*=0.27999997f;
            if(effects[S16(ctx,0x2C)].radius<0.0001f) {func_00291450(S16(ctx,0x2C));S16(ctx,0x2C)=-1;}
        }
        if(I32(ctx,0x14)>42 || D_00189E20.state!=2) {
            if(I32(obj,0xB8)==D_00189E20.object) {if(D_L22_001AFA00!=-1){func_002E59F8(D_L22_001AFA00);D_L22_001AFA00=-1;}}
            else if(D_L22_001AFA04!=-1){func_002E59F8(D_L22_001AFA04);D_L22_001AFA04=-1;}
            func_0029F338(*slot);*slot=0;return;
        }
        func_00282CD8(&frame.ground,obj+0x10,ctx);
        if(!S16(ctx,0x40) && func_002B0360(obj+0x10)-D_L22_001B2AA4<1.3f) func_L22_003A2988(obj+0x10,1.3f);
        if(F32(obj,0x10)<2.0f || F32(obj,0x10)>1021.0f || F32(obj,0x14)<2.0f || F32(obj,0x14)>1021.0f || F32(obj,0x18)<2.0f || F32(obj,0x18)>1021.0f) {
            if(I32(obj,0xB8)==D_00189E20.object) {if(D_L22_001AFA00!=-1){func_002E59F8(D_L22_001AFA00);D_L22_001AFA00=-1;}}
            else if(D_L22_001AFA04!=-1){func_002E59F8(D_L22_001AFA04);D_L22_001AFA04=-1;}
            func_0029F338(*slot);*slot=0;return;
        }
        if(S16(ctx,0x40)) {
            int count,i; float emission; char *particle;
            hit=func_00277F48(obj+0x10,16,obj,0,radius);
            frame.ground.q=*(Quad *)(obj+0x10);
            func_002A9850(obj,&frame.ground,D_L22_001C4140,hit,0,0x8B0000,2,1,D_L22_001B2A9C,1.0f,1.0f);
            if(hit)func_PAL_L00_003FB330(obj+0x10,0,25,20,1.0f,20.0f,20,20,45,1,1,0,0,0);
            count=42-I32(ctx,0x14);if(count>4)count=4;
            emission=scale*105000.0f;
            { int r=func_002A7820(63,127),g=func_002A7820(47,63),b=func_002A7820(15,47);
            u32 x=(u32)g<<8|0x4F000000; func_L04_00358868(obj,((u32)r<<16|x)|b,count,-1,emission); }
            func_002A7988(&frame.point,scale*0.020000001f,(scale+scale)*0.020000001f);
            { int r=func_002A7820(63,127),g=func_002A7820(47,63),b=func_002A7820(15,47); u32 x=(u32)g<<8|0x7F000000;
            func_PAL_002BD790(obj+0x10,&frame.point,((u32)r<<16|x)|b,0x4F7F4F2F,210000.0f,37,1,*D_L22_001FF82C,-1,0); }
            for(i=5;i>=0;i--) {
                func_002A7988(&frame.point,scale*0.020000001f,(scale+scale)*0.020000001f);
                func_002A7988(&frame.velocity,0.0f,scale*0.5f);
                func_00282CD8(&frame.ground,&frame.velocity,obj+0x10);
                particle=func_PAL_L08_0034C4A8(&frame.velocity,&frame.point,127,obj);
                if(particle)F32(particle,0xC)=func_002A7878(6000.0f,32000.0f)*scale*0.4f;
            }
            for(i=0;i<8;i++) {
                particle=func_PAL_L08_0034C4A8(obj+0x10,D_L22_001A8F20,127,obj);
                if(particle) {
                    ParticleTail *tail=(ParticleTail *)(particle+0x20);
                    if(i==2 && !func_002A77E0(8))F32(particle,0xC)=180000.0f;
                    else F32(particle,0xC)=func_002A7878(80000.0f,120000.0f);
                    F32(particle,0xC)*=scale;S16(particle,0xA)=2;
                    { int color=0x7F7F7F; float inverse=1.0f/func_00283CE0(2); tail->kind=3;tail->color=color;tail->inverse=inverse; }
                }
            }
        } else {
            int count; float emission;
            hit=func_00277F48(obj+0x10,16,*(void **)(obj+0xB8),0,radius);
            frame.ground.q=*(Quad *)(obj+0x10);
            func_002A9850(obj,&frame.ground,D_L22_001C4140,hit,0,0x8B0007,2,1,D_L22_001B2A9C,1.0f,1.0f);
            if(hit)func_PAL_L00_003FB330(obj+0x10,0,25,20,1.0f,20.0f,20,20,45,1,1,0,0,0);
            count=42-I32(ctx,0x14);if(count>4)count=4;
            emission=scale*105000.0f;
            { int r=func_002A7820(15,47),g=func_002A7820(47,63),b=func_002A7820(63,127);
            u32 x=(u32)g<<8|0x4F000000; func_L04_00358868(obj,((u32)r<<16|x)|b,count,-1,emission); }
            func_002A7988(&frame.point,scale*0.020000001f,(scale+scale)*0.020000001f);
            { int r=func_002A7820(15,47),g=func_002A7820(31,47),b=func_002A7820(63,127); u32 x=(u32)g<<8|0x7F000000;
            func_PAL_002BD790(obj+0x10,&frame.point,((u32)r<<16|x)|b,0x4F1F1F7F,210000.0f,37,1,*D_L22_001FF82C,-1,0); }
        }
    } break;
    default: break;
    }
    if(D_L22_001A8FF0) {func_002AFFD8(obj+0x10,ctx+0x30,0);func_L00_00325600(obj+0xC0,ctx+0x30,0);}
    S16(ctx,0x2E)=0;
}
