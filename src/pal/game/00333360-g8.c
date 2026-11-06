/* func_PAL_00333360, the PAL copy of func_00331800: the same C at 50 Hz, where
 * the func_002A7820 timers take the scale, func_PAL_002A7E68's last argument
 * 10 becomes 8 and the speeds and turn rates change.
 * It has its own unit for its jump table and -frac2-hazard-labels,
 * without which it does not match.
 *
 * func_002A7CA0 is void (see 0032EB28-ai-g8.c). With a float declaration the
 * call sets F0, which ends the F12 copy's dependence on the later calls, and
 * sched2 issues that copy after F14/F15, A0 and A1.
 * The arguments interleave by bank; each bank keeps its order. */
#include "common.h"

extern struct { char pad[0x80]; float pos[4]; char gap[0x2200]; int surface; } D_00189E20;
extern struct { char pad[0x18]; int surface; int gap; float point[4]; } D_001BAF80;
extern int D_001AD7EC;
extern int D_001A8CA0, D_001A8CA4;
extern void func_00283658(void *,void *);
extern void func_002AB6D8(void *,void *);
extern void func_002AD0E0(void *,int,void *,void *,void *,void *);
extern void func_002833F0(void *,void *);
extern int func_002A9640(void *,int,int);
extern void func_PAL_00333CD8(void *);
extern float func_00283248(float,float);
extern void func_002A9288(void *,float);
extern void func_002A7750(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern float func_002A7878(float,float);
extern float func_00282E80(void *,void *);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern float func_00283B98(float,float);
extern void func_002A7CA0(float,void *,void *,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002A7EA0(void *,void *,void *,float,float,float,float,int);
extern int func_00277258(void *,int,void *,float);
extern void func_002B00B0(void *,void *,int);
extern int func_002761F8(void *,void *,int,void *,int);
extern int func_00278E78(void);
extern float func_002A89A8(void *,int,float);

#define AI_F(p,n) (*(float *)((char *)(p)+(n)))
#define AI_I(p,n) (*(int *)((char *)(p)+(n)))
#define AI_B(p,n) (*(unsigned char *)((char *)(p)+(n)))

void func_PAL_00333360(char *object)
{
    float dest[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    union { float matrix[16]; struct { float vector[4]; float far[4]; float near[4]; } v; } work __attribute__((aligned(16)));
    char *state = *(char **)(object+0x68);
    float r;
    float angle;
    char *position;
    float *saved;
    int hit;

    if (AI_B(object,0x20) && D_001AD7EC) {
        func_00283658(work.matrix,object+0xc0);
        func_002AB6D8(work.matrix,dest);
        func_002AD0E0(object,D_001AD7EC,object+0x10,dest,object+0x10,temp);
        func_002833F0(object+0xc0,temp);
        qcopy(object+0xf0,temp);
    }
    if (func_002A9640(object,0x4010000,0)) func_PAL_00333CD8(object);
    func_00283248(AI_F(object,0x10)-D_00189E20.pos[0],AI_F(object,0x14)-D_00189E20.pos[1]);
    func_002A9288(object,0.5f);
    switch (AI_B(object,0x20)) {
    case 0:
        func_002A7750(object,1,-1);
        break;
    case 1:
        if (AI_B(object,0x60)&2) {
            r=func_002A7878(0,100);
            if (r>=0 && r<20) func_PAL_002A7E68(object,0,0,8);
            if (r>=20 && r<50) func_PAL_002A7E68(object,4,0,8);
            if (r>=50 && r<100) func_PAL_002A7E68(object,1,0,8);
        }
        if (func_00282E80(object+0x10,D_00189E20.pos)<2 && !D_001A8CA4 && !D_001A8CA0) {
            func_002A7750(object,2,-1);
            func_PAL_002A7E68(object,2,0,8);
            AI_F(object,0x48)=0.75f;
        }
        if (func_00282948(state+0x70)) {
            if (D_001A8CA4) return;
            if (!D_001A8CA0) {
                if (func_002A77E0(2)) {
                    func_002A7750(object,5,-1);
                    AI_I(state,0x70)=(func_002A7820(400,600)*5+2)/6;
                    func_PAL_002A7E68(object,2,0,8);
                    AI_F(object,0x48)=0.75f;
                } else {
                    func_002A7750(object,6,-1);
                    AI_I(state,0x70)=(func_002A7820(180,360)*5+2)/6;
                    func_PAL_002A7E68(object,3,0,8);
                }
            }
        }
        break;
    case 6:
        if (AI_B(object,0x60)&2) func_PAL_002A7E68(object,3,0,8);
        if (func_00282948(state+0x70)) {
            func_002A7750(object,1,-1);
            AI_I(state,0x70)=(func_002A7820(120,600)*5+2)/6;
            func_PAL_002A7E68(object,func_002A77E0(2),0,8);
        }
        break;
    case 5:
        if (AI_B(object,0x60)&2) {
            func_PAL_002A7E68(object,2,0,8);
            AI_F(object,0x48)=0.75f;
        }
        position=object+0x10;
        if (func_00282E80(position,D_00189E20.pos)<2) {
            func_002A7750(object,2,-1);
            AI_F(object,0x48)=0.1f;
            func_PAL_002A7E68(object,2,0,8);
        }
        if (func_00282948(state+0x70)) {
            func_002A7750(object,1,-1);
            AI_I(state,0x70)=(func_002A7820(400,600)*5+2)/6;
        }
        angle=func_00283B98(AI_F(object,0xf8),func_002A7878(-30,30)*0.017453294f);
        func_002A7CA0(angle,object,state+0x58,0.00020943955f,0.00062831864f,0.015707966f);
        func_00282F20(temp,object+0xc0,0.0050000004f);
        func_00282CC0(dest,position,temp);
        saved=work.matrix;
        qcopy_nc(saved,position);
        if (func_002A7EA0(object,position,dest,0.1f,0.7f,0.25f,0.52359885f,2)) {
            if (func_00277258(position,1,object,0.5f) && D_001BAF80.surface) qcopy(position,saved);
        } else {
            angle=func_00283B98(AI_F(object,0xf8),func_002A7878(20,135)*0.017453294f);
            func_002A7CA0(angle,object,state+0x58,6.9813184e-05f,0.00062831864f,0.015707966f);
        }
        break;
    case 2:
        position=object+0x10;
        if (func_00282E80(position,D_00189E20.pos)<2) {
            angle=func_00283B98(AI_F(object,0xf8),func_002A7878(-30,30)*0.017453294f);
            func_002A7CA0(angle,object,state+0x58,0.00020943955f,0.00062831864f,0.015707966f);
            func_00282F20(temp,object+0xc0,0.0050000004f);
            func_00282CC0(dest,position,temp);
            saved=work.matrix;
            qcopy_nc(saved,position);
            if (func_002A7EA0(object,position,dest,0.5f,0.7f,0.25f,0.52359885f,2)) {
                if (func_00277258(position,1,object,0.5f) && D_001BAF80.surface) qcopy(position,saved);
            } else {
                angle=func_00283B98(AI_F(object,0xf8),func_002A7878(-90,-10)*0.017453294f);
                func_002A7CA0(angle,object,state+0x58,8.377582e-05f,0.00062831864f,0.015707966f);
            }
        } else {
            AI_F(object,0x48)=1;
            func_002A7750(object,1,-1);
        }
        break;
    case 4:
        func_002B00B0(object,work.matrix,0);
        func_00282F20(work.matrix,work.matrix,4);
        func_00282CC0(work.v.far,object+0x10,work.matrix);
        func_00282F20(work.matrix,work.matrix,-1);
        func_00282CC0(work.v.near,object+0x10,work.matrix);
        if (func_002761F8(work.v.near,work.v.far,0,object,0)) {
            if (D_001BAF80.surface!=D_00189E20.surface) qcopy(object+0x10,D_001BAF80.point);
        }
        hit=func_00278E78();
        if (hit>0 && hit!=10 && !D_001A8CA4) {func_PAL_00333CD8(object);return;}
        func_002A7750(object,0,-1);
        break;
    case 3:
        break;
    }
    if (!D_001A8CA4 && !D_001A8CA0) {
        qcopy(work.matrix,object+0x10);
        work.matrix[2]+=0.5f;
        AI_F(object,0x18)=func_002A89A8(work.matrix,0,0.5f);
    }
}
