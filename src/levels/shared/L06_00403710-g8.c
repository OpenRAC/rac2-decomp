#include "common.h"

#define I(p, o) (*(s32 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define H(p, o) (*(u16 *)((char *)(p) + (o)))
extern char *D_L06_001FE500[];
typedef struct {
    char pad[0x1F0];
    u16 moveFlags;
    char pad1F2[0x13E];
    float height;
    char pad334[0x1F60];
    s32 mode;
    s32 pad2298;
    s32 action;
    char pad22A0[0x15];
    u8 flag;
} HeroState;
extern HeroState D_00189E20;
extern s32 D_001A79F0;
extern float D_L06_001B0090 __attribute__((sda));
extern float D_L06_001B9858 NOT_SDA;
extern s32 func_00283CF0(float);
extern void func_0029F338(void *);
extern s32 func_002A77E0(s32);
extern void func_002A7470(void *, s32, s32, s32);
extern float func_00283248(float, float);
extern float func_002AAA00(float *, float, float, float, float, float *, s32);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern s32 func_00282948(s32 *);
extern float func_00282C48(float);
extern s32 func_002ACBC8(void *, s32);
extern float func_00283B98(float,float);
extern void func_002833F0(void *,void *);
extern s32 func_002E5CF8(s32,s32,void *);
extern void func_L06_00403DA8(void *,void *);
extern void func_L00_002B9D60(void *,void *,s32,s32);
extern s32 func_002A8AF0(void *,void *,s32);
extern s32 func_002B3868(void *);
extern void func_L00_002B30E8(void);
typedef struct {
    char p0[0x48];
    u8 timerA;
    u8 p49;
    u8 timerB;
    char p4B[5];
    s32 path;
    s32 active;
    s32 point;
    s32 timeout;
    float turn;
    float homeZ;
    float speed;
    s32 wait;
    float pathZ;
    s32 p74;
    s32 range;
    s32 outsideWait;
    s32 insideWait;
} LaunchData;

void func_L06_00403710(char *obj)
{
    float pos[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    LaunchData *data = *(LaunchData **)(obj + 0x68);
    s32 state = B(obj,0x20);
    switch (state) {
    case 0:
        if (data->active) {
            data->timerA = FloatToInt(15.0f);
            data->timerB = FloatToInt(12.0f);
            B(obj,0x20) = 2;
            {
                float height = F(obj,0x18);
                B(obj,0x30) = 255;
                H(obj,0x34) |= 1;
                data->homeZ = height;
                data->wait = 30;
            }
        } else {
            if (data->path == -1) {
                func_0029F338(obj);
                return;
            }
            data->point = func_002A77E0(I(D_L06_001FE500[data->path],0));
            data->timeout = 600;
            if (B(obj,0x43) != 1) func_002A7470(obj,1,0,10);
            F(obj,0x18) = F(D_L06_001FE500[data->path],0x18) - D_L06_001B0090;
            data->pathZ = F(obj,0x18);
            B(obj,0x20) = 1;
        }
        break;
    case 1:
        qcopy(pos,D_L06_001FE500[data->path] + 0x10 + data->point*16);
        func_002AAA00((float *)(obj+0xF8),func_00283248(pos[0]-F(obj,0x10),pos[1]-F(obj,0x14)),0.0008726647356525064f,0.0008726647356525064f,0.05235988646745682f,&data->turn,0);
        vec_scale_to_length(step,obj+0xC0,0.05000000447034836f);
        FastVecAdd(obj+0x10,obj+0x10,step);
        if (fast_vec_dist(obj+0x10,pos)<3.0f || func_00282948(&data->timeout)) {
            data->point = (data->point+func_002A77E0(I(D_L06_001FE500[data->path],0))) % I(D_L06_001FE500[data->path],0);
            data->timeout = 600;
        }
        break;
    case 2:
        func_00282948(&data->wait);
        if (func_00282C48(D_00189E20.height-data->homeZ)<0.8f && D_00189E20.action==18 && !IsPointInCuboid((char *)&D_00189E20+0x80,data->range)) {
            if (data->wait == 0) {
                F(obj,0xF4) = -1.5533431768417358f;
                F(obj,0xF8) = FastAddRotations(D_L06_001B9858,1.5707964897155762f);
                euler_rotation_basis(obj+0xC0,obj+0xF0);
                qcopy(obj+0x10,(char *)&D_00189E20+0x80);
                vec_scale_to_length(pos,obj+0xE0,D_L06_001B0090);
                FastVecSub(obj+0x10,obj+0x10,pos);
                data->speed = 0.13333334028720856f;
                H(obj,0x34) &= 0xFFFE;
                PlayMobySound(1,0,obj);
                if (B(obj,0x43) != 2) func_002A7470(obj,2,10,5);
                B(obj,0x20) = 3;
                qcopy(step,(char *)&D_00189E20+0x80);
                step[2] = D_00189E20.height;
                func_L06_00403DA8(obj,step);
                func_L00_002B9D60((char *)&D_00189E20+0x80,(char *)&D_00189E20+0x90,111,0);
                D_00189E20.flag = 1;
            }
        } else if (D_00189E20.mode!=18) {
            if (point_in_path_xy((char *)&D_00189E20+0x80,D_L06_001FE500[data->path]+0x10,I(D_L06_001FE500[data->path],0))) data->wait=data->insideWait;
            else data->wait=data->outsideWait;
        }
        break;
    case 3:
        if (func_002B3868(obj)) PlayMobySound(1,0,obj);
        qzero_nc((char *)&D_00189E20+0xF0);
        qzero_nc((char *)&D_00189E20+0x110);
        qzero_nc((char *)&D_00189E20+0x120);
        qzero_nc((char *)&D_00189E20+0x130);
        D_00189E20.moveFlags = 3;
        D_00189E20.flag = 1;
        {
            s32 level = D_001A79F0;
            F(obj,0x18) += data->speed;
            if (level != 9)
                data->speed -= 0.0027777778450399637f;
            else
                data->speed -= 0.0055555556900799274f;
        }
        if (data->speed<0.03333333507180214f) {
            vec_scale_to_length(pos,obj+0xE0,D_L06_001B0090);
            func_002AAA00((float *)(obj+0xF4),1.5533431768417358f,0.0034906589426100254f,0.0034906589426100254f,0.41887909173965454f,&data->turn,0);
            euler_rotation_basis(obj+0xC0,obj+0xF0);
            vec_scale_to_length(step,obj+0xE0,D_L06_001B0090);
            FastVecSub(delta,step,pos);
            FastVecSub(obj+0x10,obj+0x10,delta);
        }
        if (data->speed<0.0f && F(obj,0x18)<D_00189E20.height) {
            qcopy_nc(pos,(char *)&D_00189E20+0x80);
            pos[2]=D_00189E20.height;
            func_L06_00403DA8(obj,pos);
        }
        if (data->speed<0.0f && F(obj,0x18)<data->homeZ) func_L00_002B30E8();
        if ((B(obj,0x60)&2) && B(obj,0x43)!=1) func_002A7470(obj,1,0,10);
        break;
    }
}
