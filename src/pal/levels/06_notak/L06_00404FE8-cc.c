/* func_PAL_L06_00404FE8, the PAL copy of func_L06_004012B0: the same C, where rename func_0032DA58 becomes func_PAL_0032F3B8; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_002C16C0 becomes func_PAL_002C23B8; scale func_002A7820(20,10); scale func_002A7820(0,10). */
/*
 * func_PAL_L06_00404FE8: four-state update of an effect object. State 3 leaves the switch and emits its
 * two particles after it; every other path returns. Built with -frac2-keep-block-order, which keeps
 * the default block between the two: the store there is dead and costs no word, but the block lives
 * until jump2, so the end of case 3 stays a block boundary through local-alloc and both sched passes.
 * It has a unit of its own for that flag and for its prototypes, which differ from L06_0033BDC0.c's.
 */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern char *func_002A9640(char *, int, int);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern int func_00282948(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00283B98(float, float);
extern int func_002E5CF8(int, int, char *);
extern char *func_PAL_0032F3B8(char *, void *, void *, float);
extern int func_002A8C28(char *, float, void *, int, float, float, int, int, int);
extern void func_PAL_002B15D8(char *, int, float, void *, float, float, float, unsigned char);
extern void func_0029F338(char *);
extern float func_002AA548(void *, float, void *, float, float, float);
extern char *func_PAL_002C23B8(void *, void *, int, int, int, int, float, float, float, float, float);
typedef struct { char pad[0x140]; Vec position; char gap[0x10]; float scale; int unused; int duration, timer; char gap2[0x10]; float speed; int unused2, limit; } Effect;
extern Effect D_L06_001B9700;

extern unsigned char *D_L06_001FF41C;
typedef struct { int timer; float speed, height; int handle; Vec velocity; } UpdateState;
void func_PAL_L06_00404FE8(char *obj) {
    struct { Vec pos, direction, random; } frame;
    UpdateState *ctx = *(UpdateState **)(obj+0x68);
    char *hit, *particle;
    float speed;
    char *position;
    Vec *velocity;

    switch ((unsigned char)obj[0x20]) {
    case 0:
        qcopy(&frame.pos,obj+0x10);
        frame.pos.f[2] += 10.0f;
        func_00282CC0(&ctx->velocity,obj+0x10,&frame.pos);
        ctx->handle=-1;
        obj[0x20]=1;
        return;
    case 1:
        hit=func_002A9640(obj,0x10000,0);
        if (hit) {
          if (*(short *)(*(char **)(hit+0x20)+0xAA)!=0x8B8) {
            if (func_002A77E0(3)==1) {
                ctx->timer=(((int)(func_002A7820(20,10)) * 5 + 2) / 6);
                ctx->height=*(float *)(obj+0x18)+20.0f;
                obj[0x20]=3;
            } else {
                ctx->timer=(((int)(func_002A7820(0,10)) * 5 + 2) / 6);
                obj[0x20]=2;
            }

          }
        }
        *(unsigned char *)(obj+0xA8)=255;
        return;
    case 2:
        if (func_00282948(ctx)) {
            float unit = 1.0f;
            func_002E5CF8(0,0,obj);
            frame.random.q=0;
            frame.random.f[2]=0.060000002f;
            func_00282CF0(&frame.direction,&D_L06_001B9700.position,&frame.pos);
            func_00282F20(&frame.direction,&frame.direction,unit);
            func_PAL_0032F3B8(obj,obj+0x10,&frame.direction,5.0f);
            D_L06_001B9700.speed=0.1f;
            D_L06_001B9700.limit=75;
            D_L06_001B9700.scale=0.2f;
            D_L06_001B9700.duration=50;
            D_L06_001B9700.timer=0;
            func_002A8C28(obj,3.0f,obj+0x10,0x10000,3.0f,1.0f,0,1,0);
            func_PAL_002B15D8(obj,0xEF,3.0f,&frame.random,6.0f,3.0f,6.0f,255);
            func_0029F338(obj);
        }
        return;
    case 3:
        if (func_00282948(ctx)) {obj[0x20]=2; return;}
        func_002AA548(obj+0x18,ctx->height,&ctx->speed,0.040000003f,0.040000003f,0.40000004f);
        *(float *)(obj+0xF0)=func_00283B98(*(float *)(obj+0xF0),func_002A7820(-10,10)*0.017453294f);
        *(float *)(obj+0xF4)=func_00283B98(*(float *)(obj+0xF4),func_002A7820(-10,10)*0.017453294f);
        *(float *)(obj+0xF8)=func_00283B98(*(float *)(obj+0xF8),func_002A7820(-5,25)*0.017453294f);
        velocity=&ctx->velocity;
        func_00282F20(velocity,velocity,ctx->speed);
        break;
    default:
        speed = 0.0f;
        return;
    }
    speed=ctx->speed;
    frame.random.q=0;
    position=obj+0x10;
    frame.random.f[0]=func_002A7878(-1.0f,1.0f);
    frame.random.f[1]=func_002A7878(-1.0f,1.0f);
    frame.random.f[2]=func_002A7878(-1.0f,1.0f);
    frame.direction.q=frame.random.q;
    func_00282F20(&frame.direction,&frame.direction,func_002A7878(0.1f,0.2f)*0.020000001f);
    func_00282F20(&frame.pos,velocity,-func_002A7878(0.002f,0.020000001f));
    func_00282CC0(&frame.direction,&frame.direction,&frame.pos);
    func_00282F20(&frame.pos,velocity,func_002A7878(0.0f,1.0f)*speed);
    func_00282CC0(&frame.pos,&frame.pos,position);
    particle=func_PAL_002C23B8(&frame.pos,&frame.direction,17,60,0x606060,3,80000.0f,40000.0f,1.0f,-0.0002f,0.0f);
    if (particle) {
        particle[2]=*D_L06_001FF41C;
        particle[3]=0x44;
        if (func_002A7820(0,1)) {
            particle[3]=0x48;
            *(int *)(particle+4)=0x70707F;
            {char *payload=particle+0x20;
            payload[0x11]=0x70;
            payload[0x12]=0x70;
            payload[0x13]=0x70;
            *(short *)(payload+0x1E)=0x7F;}
        }
    }
    obj+=0x10;
    func_PAL_002C23B8(obj,&frame.direction,6,127,0xB0B0B0,3,80000.0f,40000.0f,1.0f,-0.0004f,0.0f);
}
