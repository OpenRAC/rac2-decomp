#include "common.h"
typedef struct {
    char pad0[0x80];
    float pos[4];
    char pad90[0x60];
    float vel[4];
    char pad100[0x10];
    float v110[4], v120[4], v130[4];
    char pad140[0xB0];
    short control;
    char pad1F2[0x12A];
    float f31C;
    char pad320[0x1C];
    char *obj;
    int active;
    char pad344[0x1F4C];
    int query;
    int action;
    char pad2298[0x1D];
    char flag;
    char pad22B6[0x216];
    int f24CC;
} L01_003BBF68_HERO;
extern L01_003BBF68_HERO D_00189E20;
extern float D_L01_001AFE2C __attribute__((sda));
extern float D_L01_001AFE28 __attribute__((sda));
extern float func_0029F530(void *);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_00283CF0(float);
extern int func_L00_002D6900(int);
extern void func_L00_002D6B70(int);
extern int func_00282948(void *);
extern void func_002E5CF8(int, int, void *);
extern int func_002A77E0(int);
extern void func_L00_002B30E8(void);
extern void func_002A8BD0(void *, void *, int, float);
extern void func_002A8E20(int, void *);
extern void func_L01_002C1988(int);
extern void func_L01_002BEB90(int, int);
extern void func_L00_002D2168(int, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AC9F8(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);

void func_L01_003BBF68(char *obj)
{
    union {
        char query[0x24];
        struct { float pos[4], delta[4]; } vec;
    } scratch;
    char *s = *(char **)(obj + 0x68);
    float frame = func_0029F530(obj);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        func_002A7750(obj, 1, -1);
        if (*(unsigned char *)(obj + 0x43) != 0) func_002A7470(obj, 0, 0, 2);
        *(int *)(obj + 0x9C) = 3;
        *(unsigned short *)(obj + 0x34) &= 0xEFFF;
        *(int *)(s + 0x78) = -1;
        break;
    case 1:
        if (D_00189E20.obj == obj && D_00189E20.active) {
            func_002A7750(obj, 2, -1);
            *(int *)(s + 0x60) = FloatToInt(*(float *)(s + 0x50) * 60.0f);
            *(int *)(s + 0x78) = func_L00_002D6900(7);
            if (*(unsigned char *)(obj + 0x43) != 1) func_002A7470(obj, 1, 0, 10);
        }
        break;
    case 2:
        if (D_00189E20.obj == obj && D_00189E20.active) {
            *(int *)(s + 0x78) = func_L00_002D6900(4);
        } else if (*(int *)(s + 0x78) != -1) {
            func_L00_002D6B70(*(int *)(s + 0x78));
            *(int *)(s + 0x78) = -1;
        }
        if (func_00282948(s + 0x70) && func_00282948(s + 0x60)) {
            if (*(int *)(s + 0x78) != -1) {
                func_L00_002D6B70(*(int *)(s + 0x78));
                *(int *)(s + 0x78) = -1;
            }
            func_002A7750(obj, 3, -1);
            PlayMobySound(0, 0, obj);
            if (*(unsigned char *)(obj + 0x43) != 2) func_002A7470(obj, 2, 0, 6);
            if (D_00189E20.obj == obj && D_00189E20.active)
                *(int *)(s + 0x78) = func_L00_002D6900(5);
            *(float *)(obj + 0x48) = D_L01_001AFE2C;
        }
        break;
    case 3:
        if (*(float *)(s + 0x74) < 4.0f && frame > 4.0f) {
            *(unsigned short *)(obj + 0x34) |= 0x1000;
            *(int *)(s + 0x64) = 600;
            if (D_00189E20.obj == obj && D_00189E20.f31C < 0.5f) {
                *(int *)(s + 0x78) = func_L00_002D6900(5);
                *(int *)(s + 0x68) = 1;
                *(int *)(obj + 0x9C) = -1;
            } else {
                if (*(int *)(s + 0x78) != -1) {
                    func_L00_002D6B70(*(int *)(s + 0x78));
                    *(int *)(s + 0x78) = -1;
                }
                *(int *)(obj + 0x9C) = 0x80000000;
            }
            func_002A7750(obj, 4, -1);
        }
        break;
    case 4:
        if (*(int *)(s + 0x68) && !func_002A77E0(11)) *(int *)(s + 0x78) = func_L00_002D6900(5);
        if (*(float *)(s + 0x74) < 46.0f && frame > 46.0f) {
            if (*(int *)(s + 0x68)) {
                if (D_00189E20.f24CC < 2) func_L00_002B30E8();
                else {
                    func_002A8BD0(scratch.query, obj, 1, (float)*(unsigned char *)(s + 0x34));
                    QueueMobyImpact(D_00189E20.query, scratch.query);
                }
                D_00189E20.flag = 0;
                func_L01_002C1988(0);
                *(int *)(s + 0x68) = 0;
                *(int *)(s + 0x70) = 120;
            }
            *(int *)(obj + 0x9C) = 3;
            *(unsigned short *)(obj + 0x34) &= 0xEFFF;
        }
        if (*(unsigned char *)(obj + 0x60) & 2) {
            if (*(int *)(s + 0x78) != -1) {
                func_L00_002D6B70(*(int *)(s + 0x78));
                *(int *)(s + 0x78) = -1;
            }
            func_002A7750(obj, 1, -1);
            if (*(unsigned char *)(obj + 0x43) != 0) func_002A7470(obj, 0, 0, 10);
        } else if (*(int *)(s + 0x68)) {
            if (D_00189E20.action != 111) {
                SetHeroMoveState(111, 1);
                set_hero_animation(10, 0, 10.0f);
            }
            D_00189E20.control = 2;
            qcopy(scratch.vec.pos, obj + 0x10);
            scratch.vec.pos[2] += 2.0f;
            FastVecSub(scratch.vec.delta, scratch.vec.pos, D_00189E20.pos);
            func_002AC9F8(scratch.vec.delta, 0.06666667f);
            FastVecAdd(D_00189E20.pos, D_00189E20.pos, scratch.vec.delta);
            func_00282C88(D_00189E20.vel);
            func_00282C88(D_00189E20.v110);
            func_00282C88(D_00189E20.v120);
            func_00282C88(D_00189E20.v130);
            if (*(int *)(s + 0x64) > 60) *(int *)(s + 0x64) = 60;
        }
        break;
    }
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * D_L01_001AFE28;
    *(unsigned char *)(obj + 0xA8) = 255;
    *(float *)(s + 0x74) = frame;
}
