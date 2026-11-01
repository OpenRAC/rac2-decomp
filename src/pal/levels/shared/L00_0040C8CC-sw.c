#include "include_asm.h"

#include "common.h"
extern struct { char pad[0x80]; float pos[4]; char gap[0x2200]; int surface; } D_00189E20;
extern int D_001AD7EC;
extern int D_001A8CA0, D_001A8CA4;
extern struct { char pad[0x18]; int surface; int gap; float point[4]; } D_001BAF80;
extern void func_00283658(void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_002AD0E0(void *, int, void *, void *, void *, void *);
extern void func_002833F0(void *, void *);
extern int func_002A9640(void *, int, int);
extern void func_PAL_00334CB0(void *);
extern float func_00283248(float, float);
extern void func_002A9288(void *, float);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern float func_002A7878(float, float);
extern void *func_002AF460(void *, float, float, float, float);
extern float func_00282E80(void *, void *);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002A7CA0(float, void *, void *, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7EA0(void *, void *, void *, float, float, float, float, int);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern void func_L00_003252A8(void *, void *, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern float func_002A89A8(void *, int, float);
typedef int AI_Quad __attribute__((mode(TI)));
#define AI_F(p,n) (*(float *)((char *)(p)+(n)))
#define AI_I(p,n) (*(int *)((char *)(p)+(n)))
#define AI_P(p,n) (*(char **)((char *)(p)+(n)))
#define AI_B(p,n) (*(unsigned char *)((char *)(p)+(n)))

void func_PAL_L00_0040C8CC(char *object)
{
    float end[4], offset[4], scratch[4], front[4], back[4], matrix[4];
    char *state = AI_P(object, 0x68);
    char *target;
    char *position;
    float angle, choice;
    int hit;
    if (AI_B(object,0x20) && D_001AD7EC) {
        func_00283658(scratch,object+0xC0);
        func_002AB6D8(scratch,end);
        func_002AD0E0(object,D_001AD7EC,object+0x10,end,object+0x10,offset);
        func_002833F0(object+0xC0,offset);
        qcopy(object+0xF0,offset);
    }
    if (func_002A9640(object,0x4010000,0)) func_PAL_00334CB0(object);
    AI_I(state,0x78)++;
    angle=func_00283248(AI_F(object,0x10)-D_00189E20.pos[0],AI_F(object,0x14)-D_00189E20.pos[1]);
    func_002A9288(object,0.5f);
    switch (AI_B(object,0x20)) {
    case 0:
        func_002A7750(object,1,-1);
        break;
    case 1:
        if (AI_B(object,0x60)&2) {
            choice=func_002A7878(0.0f,100.0f);
            if (choice>=0.0f && choice<25.0f) func_PAL_002A7E68(object,0,0,8);
            if (choice>=25.0f && choice<50.0f) func_PAL_002A7E68(object,4,0,8);
            if (choice>=50.0f && choice<75.0f) func_PAL_002A7E68(object,1,0,8);
            if (choice>=75.0f && choice<100.0f && !D_001A8CA4 && !D_001A8CA0) {
                *(AI_Quad *)scratch=*(AI_Quad *)(object+0x10);
                AI_P(state,0x7C)=func_002AF460(scratch,1.5707964897155762f,999.0f,-1.0f,-1.0f);
                if (AI_P(state,0x7C)) {
                    func_002A7750(object,8,-1);
                    func_PAL_002A7E68(object,5,0,1);
                    AI_F(object,0x48)=1.7f;
                }
            }
        }
        if (func_00282E80(object+0x10,D_00189E20.pos)<2.0f && !D_001A8CA4 && !D_001A8CA0) {
            func_002A7750(object,2,-1);
            func_PAL_002A7E68(object,5,0,1);
            AI_F(object,0x48)=1.7f;
        }
        if (func_00282948(state+0x70)) {
            if (D_001A8CA4) return;
            if (!D_001A8CA0) {
                if (func_002A77E0(2)) {
                    func_002A7750(object,5,-1);
                    AI_I(state,0x70)=((s32)(func_002A7820(400,600)) * 5 + 2) / 6;
                    func_PAL_002A7E68(object,2,0,8);
                } else {
                    func_002A7750(object,6,-1);
                    AI_I(state,0x70)=((s32)(func_002A7820(180,360)) * 5 + 2) / 6;
                    func_PAL_002A7E68(object,3,0,8);
                }
            }
        }
        break;
    case 8:
        target=AI_P(state,0x7C);
        choice=func_00283248(AI_F(target,0x10)-AI_F(object,0x10),AI_F(target,0x14)-AI_F(object,0x14));
        func_002A7CA0(choice,object,state+0x58,0.00031415932f,0.00062831864f,0.020943955f);
        func_00282F20(offset,object+0xC0,0.050000004f);
        func_00282CC0(end,object+0x10,offset);
        if (!func_002A7EA0(object,object+0x10,end,0.5f,0.6f,0.25f,0.52359885f,0)) func_PAL_00334CB0(object);
        break;
    case 6:
        if (AI_B(object,0x60)&2) func_PAL_002A7E68(object,3,0,8);
        if (func_00282948(state+0x70)) {
            func_002A7750(object,1,-1);
            AI_I(state,0x70)=((s32)(func_002A7820(120,600)) * 5 + 2) / 6;
            func_PAL_002A7E68(object,func_002A77E0(2),0,8);
        }
        break;
    case 5:
        if (AI_B(object,0x60)&2) func_PAL_002A7E68(object,2,0,2);
        if (func_00282E80(object+0x10,D_00189E20.pos)<2.0f) {
            func_002A7750(object,2,-1);
            func_PAL_002A7E68(object,5,0,1);
        }
        if (func_00282948(state+0x70)) {
            func_002A7750(object,1,-1);
            AI_I(state,0x70)=((s32)(func_002A7820(400,600)) * 5 + 2) / 6;
        }
        func_002A7CA0(func_00283B98(AI_F(object,0xF8),func_002A7878(-30.0f,30.0f)*0.01745329424738884f),object,state+0x58,0.00020943955f,0.00062831864f,0.015707966f);
        func_00282F20(offset,object+0xC0,0.0050000004f);
        func_00282CC0(end,object+0x10,offset);
        if (!func_002A7EA0(object,object+0x10,end,0.1f,0.5f,0.25f,0.52359885f,0)) {
            func_002A7CA0(func_00283B98(AI_F(object,0xF8),func_002A7878(20.0f,135.0f)*0.01745329424738884f),object,state+0x58,6.9813184e-05f,0.00062831864f,0.015707966f);
        }
        break;
    case 2:
        position=object+0x10;
        *(AI_Quad *)scratch=*(AI_Quad *)(object+0x10);
        AI_P(state,0x7C)=func_002AF460(scratch,1.5707964897155762f,999.0f,-1.0f,-1.0f);
        target=AI_P(state,0x7C);
        if (target) {
            choice=func_00283248(AI_F(target,0x10)-AI_F(object,0x10),AI_F(target,0x14)-AI_F(object,0x14));
            func_002A7CA0(choice,object,state+0x58,0.00031415932f,0.00062831864f,0.020943955f);
            func_00282F20(offset,object+0xC0,0.050000004f);
            func_00282CC0(end,position,offset);
        }
        if (!func_002A7EA0(object,position,end,0.5f,0.6f,0.25f,0.52359885f,0)) {
            func_PAL_00334CB0(object);
        } else if (func_00283C80(angle,AI_F(object,0xF8))>0.52359885f) {
            func_002A7CA0(angle,object,state+0x58,0.0005585055f,0.00062831864f,0.015707966f);
        }
        break;
    case 4:
        func_L00_003252A8(object,scratch,0);
        func_00282F20(scratch,scratch,4.0f);
        func_00282CC0(front,object+0x10,scratch);
        func_00282F20(scratch,scratch,-1.0f);
        func_00282CC0(back,object+0x10,scratch);
        if (func_002761F8(back,front,0,object,0)) {
            if (D_001BAF80.surface!=D_00189E20.surface) qcopy(object+0x10,D_001BAF80.point);
        }
        hit=func_00278E78();
        if (hit>0 && hit!=10 && !D_001A8CA4) {func_PAL_00334CB0(object);return;}
        func_002A7750(object,1,-1);
        break;
    }
    if (!D_001A8CA4 && !D_001A8CA0) {
        qcopy(scratch,object+0x10);
        scratch[2]+=0.5f;
        AI_F(object,0x18)=func_002A89A8(scratch,0,0.5f);
    }
}
