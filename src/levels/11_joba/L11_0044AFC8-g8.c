#include "common.h"
extern int D_001A8FF4;
extern char D_00189EA0[];
extern char *D_0018C2BC __attribute__((section(".data")));
typedef int TIAfc8 __attribute__((mode(TI)));
extern void func_L11_0044BD68(char *);
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern int func_002A77E0(int);
extern void func_00282CF0(void *, void *, void *);
extern float func_002B04E0(char *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_002B3890(char *);
extern int func_002B3868(char *);
extern void func_002B60B0(char *, float, float, float, float);
extern char *func_L11_004417E8(int);
extern int func_L11_00441808(int, void *);
extern void func_L11_0044C688(char *, void *);
extern void func_L11_0044C818(char *);
extern void func_L01_00321178(char *, void *);
extern void func_L02_00333438(char *, void *);
extern int func_002B5278(char *, float);
extern int func_002B50E0(char *, void *, float);
extern int func_L11_0044C850(char *);
extern int func_002B4FF0(char *, void *, float);
extern void func_L02_00333480(char *, void *, void *);
extern float func_0029F530(char *);
extern int func_002A8D70(char *, int, float, float, int, float, int, int, int);
extern void func_L00_002E6CF0(void (*)(char *), char *);
extern void func_L11_0044C220(char *);
extern void func_L11_0044C180(char *);
extern void func_L11_00340500(char *, void *);
extern int func_002B1C20(char *, void *);
extern void func_L02_003FC248(char *, int, int);
extern void func_L11_0044C4F0(char *);
extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern void func_L07_00321D68(char *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A3F10(char *, int, void *, void *);
extern void func_002B4090(char *, void *, float, float, float);
extern void func_002833F0(void *, void *);
extern void func_L11_0044C0F0(char *);

void func_L11_0044AFC8(char *object)
{
    float target[4], direction[4], matrix[16];
    int collision_flags;
    char *state = *(char **)(object + 0x68);
    char *position, *waypoint;
    float angle, difference, distance, frame, scale;
    int result, i;
    float *rotation;
    if (*(u8 *)(object + 0x20) == 1) return;
    if (*(short *)(state + 0x4D2) && !D_001A8FF4 &&
        *(u8 *)(object + 0x20) != 11 && *(u8 *)(object + 0x20) != 10) return;
    func_L11_0044BD68(object);
    if (*(u8 *)(object + 0x20) == 1) return;
    if (*(short *)(state + 0x4D2) && !D_001A8FF4) return;
    if (*(short *)(state + 0x4CA) == 0) {
        *(int *)(state + 0x490) = 0;
        if (*(u8 *)(object + 0x95) == 4) {
            func_002A7750(object, 4, 2);
            if (func_002A77E0(2)) {
                if (*(u8 *)(object + 0x43) != 2) func_002A7470(object, 2, 0, 10);
            } else if (*(u8 *)(object + 0x43) != 3) func_002A7470(object, 3, 0, 10);
        }
    }
    if (*(char **)(state + 0x490)) *(TIAfc8 *)target = *(TIAfc8 *)(*(char **)(state + 0x490) + 0x10);
    else *(TIAfc8 *)target = *(TIAfc8 *)D_00189EA0;
    if (*(short *)(state + 0x4D2)) {
        func_00282CF0(direction, target, object + 0x10);
        position = object + 0x10;
        difference = func_002B04E0(object, direction, state + 0x230);
        angle = 0.0f;
    } else {
        position = object + 0x10;
        angle = func_00283248(target[0] - *(float *)(object + 0x10), target[1] - *(float *)(object + 0x14));
        difference = func_00283C80(angle, *(float *)(object + 0xF8));
    }
    distance = func_00282E48(position, target);
    if (*(u8 *)(object + 0x95) == 2) {
        if (func_002B3890(object)) {
            if (*(u8 *)(object + 0x43) != 10) func_002A7470(object, 10, 0, 10);
            *(u8 *)(object + 0xBC) = 0;
            func_002B60B0(object, 0.002222222276031971f, 0.06666667014360428f, 0.0011635529808700085f, 0.10471977293491364f);
            func_L11_0044C688(object, func_L11_004417E8(*(int *)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (*(u8 *)(object + 0xBC) == 1 && *(u16 *)(object + 0x96) > 300) {
            switch (func_002A77E0(5)) {
            case 0: if (*(u8 *)(object + 0x43) != 2) func_002A7470(object,2,0,10); break;
            case 1: if (*(u8 *)(object + 0x43) != 3) func_002A7470(object,3,0,10); break;
            case 2: if (*(u8 *)(object + 0x43) != 4) func_002A7470(object,4,0,10); break;
            case 3: if (*(u8 *)(object + 0x43) != 6) func_002A7470(object,6,0,10); break;
            case 4: if (*(u8 *)(object + 0x43) != 7) func_002A7470(object,7,0,10); break;
            }
            *(u16 *)(object + 0x96) = func_002A77E0(100);
        }
        if (*(short *)(state + 0x4CA)) {
            func_002A7750(object,5,4);
            if (func_002A77E0(2)) {
                if (*(u8 *)(object + 0x43) != 1) func_002A7470(object,1,0,10);
            } else if (*(u8 *)(object + 0x43) != 5) func_002A7470(object,5,0,10);
        }
        if (difference > 2.792527198791504f) func_L11_0044C818(object);
        waypoint = state + 0x470;
        if (*(u8 *)(object + 0xBC) == 0 && func_00282E80(position, waypoint) < 0.5f) *(u8 *)(object + 0xBC) = 1;
        else if (*(short *)(state + 0x4D2)) func_L02_00333438(object,waypoint);
        else func_L01_00321178(object,waypoint);
    }
    switch (*(u8 *)(object + 0x20)) {
    case 3:
        if (func_002B3868(object)) {
            *(u8 *)(object + 0xBC) = 0;
            if (*(u8 *)(object + 0x43) != 2) func_002A7470(object,2,0,0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (*(u8 *)(object + 0xBC) == 0 && *(short *)(state + 0x4D0) < *(u16 *)(object + 0x96)) {
            if (*(u8 *)(object + 0x43) != 10) func_002A7470(object,10,0,10);
            *(u8 *)(object + 0xBC) = 1;
        } else if (*(u8 *)(object + 0xBC) == 1) {
            if (func_L11_00441808(*(int *)(object+0xB8),position)) func_002A7750(object,4,2);
            func_L01_00321178(object,func_L11_004417E8(*(int *)(object+0xB8)));
        }
        break;
    case 5:
        if (*(u8 *)(object + 0x60) & 2) func_002A7750(object,7,-1);
        break;
    case 6:
        if (func_002B3868(object)) {
            if (*(u8 *)(object + 0x43) != 9) func_002A7470(object,9,0,10);
            func_002B60B0(object,0.004444444552063942f,0.13333334028720856f,0.006981317885220051f,0.8377581834793091f);
        }
        func_002B5278(object,angle);
        if (*(u8 *)(object+0x60)&2) func_002A7750(object,*(short *)(state+0x4CC),*(short *)(state+0x4CE));
        break;
    case 7:
        if (func_002B3868(object)) {
            if (*(u8 *)(object+0x43)!=10) func_002A7470(object,10,0,15);
        }
        if (*(u8 *)(object+0x42)==8 && distance>15.0f) {
            if (*(u8 *)(object+0x43)!=10) func_002A7470(object,10,0,4);
            func_002B60B0(object,0.004444444552063942f,0.13333334028720856f,0.0011635529808700085f,0.10471977293491364f);
        } else if (*(u8 *)(object+0x42)==10 && distance<7.0f) {
            if (*(u8 *)(object+0x43)!=8) func_002A7470(object,8,0,4);
            func_002B60B0(object,0.004444444552063942f,0.03333333507180214f,0.0011635529808700085f,0.10471977293491364f);
        }
        if (distance<2.8f && difference<0.3839724659919739f) {
            func_002A7750(object,8,-1);
            if (*(u8 *)(object+0x43)!=11) func_002A7470(object,11,4,3);
            *(int *)(state+0x4B0)=0;
        } else if (distance>2.8f) {
            if (*(short *)(state+0x4D2)) func_L02_00333438(object,target);
            else if (!func_L11_0044C850(object)) func_002B4FF0(object,target,*(float *)(state+0x494));
        } else {
            if (*(short *)(state+0x4D2)) {
                func_00282CF0(direction,target,position);
                func_L02_00333480(object,position,direction);
            } else func_002B50E0(object,position,angle);
        }
        if (difference>2.792527198791504f) func_L11_0044C818(object);
        break;
    case 8:
        if (*(u8 *)(object+0x60)&2) {
            *(float *)(state+0x4AC)=8.0f;
            if (D_0018C2BC==object) {
                func_002A7750(object,9,-1);
                if (*(u8 *)(object+0x43)!=12) func_002A7470(object,12,0,7);
            } else func_002A7750(object,7,-1);
        }
        frame=func_0029F530(object);
        if (*(u8 *)(object+0x42)==11) {
            if (19.0f<=frame && frame<=25.0f) {
                func_002A8D70(object,0,0.35f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
                func_002A8D70(object,1,0.15f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
                func_002A8D70(object,2,0.15f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
            }
        }
        if (*(u8 *)(object+0x42)==11 && 17.0f<=frame && frame<=25.0f) {
            func_L00_002E6CF0(func_L11_0044C220,object);
            func_L11_0044C180(object);
            *(float *)(state+0x4AC)=25.0f;
        }
        if (*(short *)(state+0x4D2)) func_L11_00340500(object,target);
        else func_002B50E0(object,position,angle);
        break;
    case 9:
        if (*(u8 *)(object+0x60)&2) func_002A7750(object,7,-1);
        break;
    case 10:
        result=func_002B1C20(object,state+0x50);
        if (*(u8 *)(object+0x42)==15) {
            if (!func_002A77E0(30) || (result&1)) {
                if (func_0029F530(object)<15.0f && *(short *)(state+0x4D2) && !func_002A77E0(2)) func_002A7750(object,11,-1);
                else {func_L02_003FC248(object,0,-1); func_L11_0044C4F0(object);}
            }
        } else if (result&2) func_002A7750(object,7,4);
        break;
    case 11:
        if (func_002B3868(object)) {
            func_00282CF0(state+0x1A0,func_L11_004417E8(*(int *)(object+0xB8)),position);
            *(int *)(state+0x1A8)=0;
            scale=func_002A7878(3.0f,5.0f);
            func_00282F20(state+0x1A0,state+0x1A0,scale*0.01666666753590107f);
            if (*(u8 *)(object+0x43)!=17) func_002A7470(object,17,0,30);
            *(short *)(state+0x4D2)=0;
            rotation = (float *)(state + 0x480);
            for (i = 0; i < 3; i++) {
                rotation[i] = func_002A7878(240.0f,720.0f)*0.0002908882452175021f;
                qcopy((char *)matrix + i * 16, object + 0xC0 + i * 16);
            }
            func_002AB6D8(matrix,object+0xF0);
            *(u16 *)(object+0x34)&=0xEFFF;
        }
        *(float *)(state+0x1A8)-=*(float *)(state+0x12C);
        func_L07_00321D68(object,state+0x1A0);
        func_00282D30(state+0x480,state+0x480,0.98f);
        scale=*(float *)(object+0x2C)*0.0009765625f;
        collision_flags=6;
        func_002A3F10(object,1,&collision_flags,matrix);
        func_00282D30(direction,matrix+12,scale);
        func_002B4090(object,direction,*(float *)(state+0x480),*(float *)(state+0x484),*(float *)(state+0x488));
        func_002833F0(object+0xC0,object+0xF0);
        if (*(float *)(object+0x18)<*(float *)(func_L11_004417E8(*(int *)(object+0xB8))+8)+5.0f ||
            !func_002A77E0(450) || *(u16 *)(object+0x96)>300) {
            func_L02_003FC248(object,0,-1); func_L11_0044C4F0(object);
        }
        break;
    }
    func_L11_0044C0F0(object);
}
