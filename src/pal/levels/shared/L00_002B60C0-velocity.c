#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct {
    u8 pad0[0xF0];
    float velocity[4];               
    u8 pad100[0x140 - 0x100];
    float lastVelocity[4];           
    u8 pad150[0x174 - 0x150];
    float f174;
    float f178;
    u8 pad17C[0x190 - 0x17C];
    float targetDir[4];              
    float inputAngle;                
    u8 pad1A4[0x1B0 - 0x1A4];
    float inputSpeed;                
    float f1B4;
    u8 pad1B8[0x287 - 0x1B8];
    u8 f287;
    u8 pad288[0x34A - 0x288];
    s16 f34A;
    u8 pad34C[0x524 - 0x34C];
    s16 f524;
    u8 pad526[0xA60 - 0x526];
    float vecA60[4];
    u8 padA70[0x1454 - 0xA70];
    s16 f1454;
    u8 pad1456[0x2294 - 0x1456];
    s32 f2294;
    u8 pad2298[4];
    s32 f229C;
    u8 pad22A0[0x22C3 - 0x22A0];
    u8 moveMode;                     
} HeroVelocity;
extern HeroVelocity D_00189E20;
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282E20(void *);
extern float func_L00_002D3A58(void *);
extern float func_00282DB0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F70(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D3BD8(void *, void *, float);
extern float func_L00_002B5590(void *);

/* Moves the hero's velocity toward the requested one, accelerating harder when reversing. */
void func_PAL_L00_002B60C0(float rate)
{
    float v[4] __attribute__((aligned(16)));
    float t[4] __attribute__((aligned(16)));
    float u[4] __attribute__((aligned(16)));
    float angle, speed, dot, len, velLen;

    switch (D_00189E20.moveMode) {
    case 0:
        angle = D_00189E20.inputAngle;
        speed = D_00189E20.inputSpeed;
        if (D_00189E20.f229C == 4 && D_00189E20.f524 && D_00189E20.f287)
            speed = 0.10000001f;
        if (D_00189E20.f34A && D_00189E20.f2294 == 14 && speed > 0.020000001f)
            speed = 0.020000001f;
        v[0] = func_00283180(angle) * speed;
        v[1] = func_00283198(angle) * speed;
        v[2] = D_00189E20.velocity[2];
        dot = -(D_00189E20.velocity[0] * v[0] + D_00189E20.velocity[1] * v[1]);
        len = func_00282E20(v);
        velLen = func_00282E20(D_00189E20.velocity);
        if (len == 0.0f || velLen == 0.0f) {
            dot = 0.0f;
        } else {
            dot /= len;
            dot /= velLen;
        }
        dot += 1.0f;
        dot *= 1.5f;
        if (dot > 3.0f)
            dot = 3.0f;
        if (dot < 1.0f)
            dot = 1.0f;
        rate *= dot;
        func_00282CF0(v, v, D_00189E20.velocity);
        if (func_00282E20(v) > rate)
            func_00282F70(v, v, rate);
        func_00282CC0(D_00189E20.velocity, D_00189E20.velocity, v);
        qcopy(D_00189E20.lastVelocity, D_00189E20.velocity);
        *(Quad *)t = *(Quad *)D_00189E20.vecA60;
        D_00189E20.f1B4 = D_00189E20.f178 - func_L00_002B5590(t);
        if (D_00189E20.f1454)
            D_00189E20.f1B4 = D_00189E20.f174;
        break;
    case 1:
    case 2:
        *(Quad *)t = *(Quad *)D_00189E20.targetDir;
        speed = D_00189E20.inputSpeed;
        func_L00_002D3B58(v, t, 0.0f);
        func_00282F20(v, v, speed);
        func_L00_002D3B58(u, D_00189E20.velocity, 0.0f);
        dot = -func_00282DB0(u, v);
        len = func_L00_002D3A58(v);
        velLen = func_L00_002D3A58(D_00189E20.velocity);
        if (len == 0.0f || velLen == 0.0f) {
            dot = 0.0f;
        } else {
            dot /= len;
            dot /= velLen;
        }
        dot += 1.0f;
        dot *= 1.5f;
        if (dot > 3.0f)
            dot = 3.0f;
        if (dot < 1.0f)
            dot = 1.0f;
        rate *= dot;
        func_00282CF0(v, v, D_00189E20.velocity);
        func_L00_002D3B58(v, v, 0.0f);
        if (func_L00_002D3A58(v) > rate)
            func_L00_002D3BD8(v, v, rate);
        func_00282CC0(D_00189E20.velocity, D_00189E20.velocity, v);
        D_00189E20.f1B4 = D_00189E20.f178;
        if (D_00189E20.f1454)
            D_00189E20.f1B4 = D_00189E20.f174;
        break;
    }
}
