/* func_PAL_L30_0041AC18, the PAL copy of func_L30_004158B0: the same C, where 1/60 becomes 0.02,
 * 1/30 becomes 0.04, 2/15 becomes 0.16, 0.0040555559 becomes 0.00584, the ring count 16 becomes 13
 * and particle lifetimes are scaled by 5/6. Each loop has its own counter and the two pairs count up. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct {
    short life, initialLife, duration, pad;
    float inner, outer, strength, scale;
    int sound, flash, count0, count1, count2, count3, count4, count5, color;
} ExplosionState;
extern float D_L30_001B1EF8 __attribute__((sda));
extern float D_L30_001B1EFC __attribute__((sda));
extern int D_L30_001B1F00 __attribute__((sda));
extern char D_L30_001A8F20[] __attribute__((sda)) NOT_SDA;
extern unsigned char *D_L30_001FF940[];
extern unsigned char *D_L30_001FFAB0[];
extern struct { char pad[0x140]; float position[4]; } D_L30_001B9C80;
extern char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern char *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern void func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern char *func_002C6DD8(void *, void *, int, float);
extern void func_00308408(void *, void *, void *, int, float, int, int, int, int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AF000(void *, float, float, float);
extern char *func_002BDCE8(void *, float, float, float, int, void *, float, int, int);

void func_PAL_L30_0041AC18(char *obj) {
    float p[4] __attribute__((aligned(16)));
    float v[4] __attribute__((aligned(16)));
    float t[4] __attribute__((aligned(16)));
    ExplosionState *st = *(ExplosionState **)(obj + 0x68);
    float a;
    int i, sign;
    {
        float burstSize, burstSpeed;
        int i;
        char *particle;
        burstSize = D_L30_001B1EF8 * st->scale * 210000.0f;
        burstSpeed = D_L30_001B1EFC * st->scale * 210000.0f;
        particle = func_002C65A0(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color | 0x7F000000, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = D_L30_001FFAB0[0][0];
        particle = func_002C65A0(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color, 0, 100, 0, burstSize, burstSpeed, 0.0f, 0);
        if (particle) particle[2] = D_L30_001FFAB0[0][0];
        for (i = 0; i < 2; i++) {
            particle = func_002C65A0(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color | 0x7F000000, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
            if (particle) particle[2] = D_L30_001FF940[0x170/4][5];
        }
        for (i = 0; i < 2; i++) {
            particle = func_002C65A0(obj + 0x10, D_L30_001A8F20, (D_L30_001B1F00 * 5 + 2) / 6, st->color | 0x7F000000, 0, 127, 0, burstSize, burstSpeed, 0.0f, 0);
            if (particle) particle[2] = D_L30_001FF940[0x170/4][6];
        }
    }
    {
        int i;
        for (i = 0; i < st->count0; i++) {
            float a, direction, size, speed;
            int n, life;
            char *particle;
            a = func_00283248(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
            n = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            life = func_002A7820(30, 50);
            p[0] = *(float *)(obj+0x10) + func_002A78D8(0.0f, 0.1f)*st->scale;
            p[1] = *(float *)(obj+0x14) + func_002A78D8(0.0f, 0.1f)*st->scale;
            p[2] = *(float *)(obj+0x18) + func_002A78D8(0.0f, 0.1f)*st->scale;
            size = func_002A7878(0.6f, 1.0f)*st->scale;
            speed = func_002A7878(9.0f, 12.0f)*st->scale;
            direction = func_00283B98(a, func_002A78D8(0.0f, 1.396263599395752f));
            v[0] = func_00283180(direction)*0.020000001f*speed;
            v[1] = func_00283198(direction)*0.020000001f*speed;
            v[2] = 0.0f;
            speed = func_002A7878(0.0f, 12.0f)*st->scale;
            v[2] = speed*0.020000001f;
            func_002C7970(p,v,(life * 5 + 2) / 6,st->color,n,127,127,size*210000.0f,st->scale*2100.0f,0.00584f,1);
            n *= 2;
            particle = func_002C7970(p,v,(life * 5 + 2) / 6,st->color&0xFFFFFF,-n,48,48,size*1260000.0f,st->scale*4200.0f,0.00584f,0);
            if (particle) particle[2] = D_L30_001FF940[0xD4/4][0];
        }
    }
    {
        int i;
        for (i = 0; i < st->count1; i++) {
            float a, direction, size, speed;
            int n, life;
            char *particle;
            a = func_00283248(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
            n = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            life = func_002A7820(30, 50);
            p[0] = *(float *)(obj+0x10) + func_002A78D8(0.0f, 0.1f)*st->scale;
            p[1] = *(float *)(obj+0x14) + func_002A78D8(0.0f, 0.1f)*st->scale;
            p[2] = *(float *)(obj+0x18) + func_002A78D8(0.0f, 0.1f)*st->scale;
            size = func_002A7878(0.75f, 1.5f)*st->scale;
            speed = func_002A7878(9.0f, 12.0f)*st->scale;
            direction = func_00283B98(a, func_002A78D8(0.0f, 1.396263599395752f));
            v[0] = func_00283180(direction)*0.020000001f*speed;
            v[1] = func_00283198(direction)*0.020000001f*speed;
            v[2] = 0.0f;
            speed = func_002A7878(0.0f, 12.0f)*st->scale;
            v[2] = speed*0.020000001f;
            func_002C7970(p,v,(life * 5 + 2) / 6,st->color&0xFFFFFF,n,127,127,size*210000.0f,st->scale*2100.0f,0.00584f,5);
        }
    }
    {
        int i;
        for (i = 0; i < st->count2; i++) {
            float a, direction, size, speed;
            int n, life;
            char *particle;
            a = func_00283248(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
            n = func_00283CF0(func_002A78D8(2.0f, 5.0f));
            life = func_002A7820(30, 50);
            p[0] = *(float *)(obj+0x10) + func_002A78D8(0.0f, 0.1f)*st->scale;
            p[1] = *(float *)(obj+0x14) + func_002A78D8(0.0f, 0.1f)*st->scale;
            p[2] = *(float *)(obj+0x18) + func_002A78D8(0.0f, 0.1f)*st->scale;
            size = func_002A7878(0.6f, 1.0f)*st->scale;
            speed = func_002A7878(9.0f, 12.0f)*st->scale;
            direction = func_00283B98(a, func_002A78D8(0.0f, 1.396263599395752f));
            v[0] = func_00283180(direction)*0.020000001f*speed;
            v[1] = func_00283198(direction)*0.020000001f*speed;
            v[2] = 0.0f;
            speed = func_002A7878(0.0f, 12.0f)*st->scale;
            v[2] = speed*0.020000001f;
            func_002C7970(p,v,(life * 5 + 2) / 6,st->color&0xFFFFFF,n,127,127,size*210000.0f,st->scale*2100.0f,0.00584f,3);
        }
    }
    {
        int i;
        for (i = 0; i < st->count4; i++) {
            float x, y;
            char *particle;
            func_00282D30(p,obj+0xC0,func_002A7878(15.0f,20.0f)*st->scale*0.020000001f);
            x = func_002A78D8(0.2617994248867035f,1.396263599395752f);
            y = func_002A78D8(0.2617994248867035f,1.396263599395752f);
            func_002AB668(t,obj+0xD0,x);
            func_002ACDE8(v,p,t);
            func_002AB668(t,obj+0xC0,y);
            func_002ACDE8(v,v,t);
            particle = func_002C6DD8(obj+0x10,v,(func_002A7820(20,35) * 5 + 2) / 6,0.00584f);
            if (particle) {
                int alpha = 0x7F000000;
                *(int *)(particle+12) = *(int *)(particle+4) = st->color|alpha;
            }
        }
    }
    if (st->count5) {
        *(Quadword *)v = 0;
        v[2] = st->scale*0.16000001f;
        *(Quadword *)p = *(Quadword *)v;
        func_00308408(obj,obj+0x10,p,13,st->scale*3.5f,(unsigned char)st->color,(unsigned char)(st->color>>8),(unsigned char)(st->color>>16),45);
    }
    func_002ABBB8(obj,D_L30_001A8F20,obj+0x10,0.0f,0.0f,0,0,0,0.0f,0.0f,9.0f,0.0f,-1,st->scale*20.0f,0,0,-1,0,0x810001);
    sign = 1;
    a = func_00283248(D_L30_001B9C80.position[0] - *(float *)(obj+0x10), D_L30_001B9C80.position[1] - *(float *)(obj+0x14));
    for (i = 0; i < st->count3; i++) {
        float size, x, y;
        char *particle;
        p[0] = *(float *)(obj+0x10) + func_002A78D8(0.0f,1.0f)*st->scale;
        sign = -sign;
        p[1] = *(float *)(obj+0x14) + func_002A78D8(0.0f,1.0f)*st->scale;
        p[2] = *(float *)(obj+0x18) + func_002A78D8(0.0f,1.0f)*st->scale;
        size = func_002A7878(0.020000001f,0.040000003f)*st->scale;
        x = func_002A78D8(0.0f,1.396263599395752f);
        y = func_002A78D8(0.0f,1.5707964897155762f);
        func_002AF000(v,size,func_00283B98(a,y),x);
        particle = func_002BDCE8(p,0.0f,1.0f,1.01f,sign,v,st->scale*315000.0f,st->color|0x7F0000,0);
        if (particle) {
            char *sub = particle + 0x20;
            *(short *)(particle+10) = (func_002A7820(40,70) * 5 + 2) / 6;
            particle[9] = func_00283CF0(4.0f)+64;
            *(int *)(sub+4) = 3;
            *(float *)(sub+0x1C) = func_00283CE0((func_002A7820(1,10) * 5 + 2) / 6);
            sub[0xA] = 64;
            sub[0xB] = particle[10];
        }
    }
}
