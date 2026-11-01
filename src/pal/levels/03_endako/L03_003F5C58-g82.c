#include "include_asm.h"

#include "common.h"
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DF0(void *);
extern float func_00282E48(void *,void *);
extern void func_002AAC80(void *,float,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002E5CF8(int,int,void *);
extern void func_002AA2E8(void *,float,float);
extern float func_00283198(float);
extern float func_00283B98(float,float);
extern float func_00282E20(void *);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern void func_002AAA00(void *,void *,float,float,float,float,int);
extern u8 D_L03_00188660[] NOT_SDA;
extern float D_0018A138 NOT_SDA;
extern float D_L03_001B1088 __attribute__((sda)), D_L03_001B1074 __attribute__((sda)), D_L03_001B1078 __attribute__((sda));
extern float D_L03_001B107C __attribute__((sda)), D_L03_001B1080 __attribute__((sda)), D_L03_001B1084 __attribute__((sda)), D_L03_001B108C __attribute__((sda));

void func_PAL_L03_003FA3C0(u8 *entity) {
    u8 *state = *(u8 **)(entity+0x68);
    float delta[4];
    int next;
    float distance, target, tilt, blend, rate, speed, remaining, wave, step;
    if (*(u8 **)(state+0x2CC)) {
        next = *(int *)(state+0x2D8);
        if (*(int *)(state+0x2DC) < next) next--;
        else if (next < *(int *)(state+0x2DC)) next++;
        func_00282CF0(delta, *(u8 **)(state+0x2CC)+(next*16+16), state+0x290);
        distance = func_00282DF0(delta);
        remaining=func_00282E48(state+0x290,*(u8 **)(state+0x2CC)+(*(int *)(state+0x2DC)*16+16));
        func_002AAC80(state+0x2D0,remaining,D_L03_001B1088*0.00040000002f,D_L03_001B1088*0.00040000002f,0.20000002f);
        func_00282F20(delta,delta,*(float *)(state+0x2D0));
        func_00282CC0(state+0x290,state+0x290,delta);
        if (distance <= *(float *)(state+0x2D0)) *(int *)(state+0x2D8)=next;
        {
            u8 *sound=D_L03_00188660+*(int *)(state+0x3CC)*0x70;
            if (*(u8 **)(sound+0x88)!=entity || !sound[0x74]) *(int *)(state+0x3CC)=func_002E5CF8(0,4,entity);
        }
    }
    switch(entity[0x95]) {
    case 3:
        distance=D_0018A138-155.0f;
        if(distance>1.5f) distance=1.5f;
        else if(distance<0) distance=0;
        func_002AA2E8(state+0x300,0.1f,0.010000001f);
        func_002AA2E8(state+0x304,distance,0.030000001f);
        break;
    case 4:
        func_002AA2E8(state+0x300,0.3f,0.010000001f);
        func_002AA2E8(state+0x304,1.5f,0.030000001f);
        break;
    case 1:
        func_002AA2E8(state+0x300,0.1f,0.010000001f);
        func_002AA2E8(state+0x304,1.5f,0.030000001f);
        break;
    default:
        func_002AA2E8(state+0x300,D_L03_001B1074,0.010000001f);
        func_002AA2E8(state+0x304,D_L03_001B1078,0.030000001f);
    }
    qcopy(entity+0x10,state+0x290);
    wave=func_00283198(*(float *)(state+0x2C0));
    step=D_L03_001B107C*0.0003490659f;
    *(float *)(entity+0x18)+=*(float *)(state+0x300)*wave+*(float *)(state+0x304);
    *(float *)(state+0x2C0)=func_00283B98(*(float *)(state+0x2C0),step);
    if(entity[0x95]==0 && func_00282E20(delta)>0.020000001f) {
        tilt=0.17453295f;
        target=func_00283248(delta[0],delta[1]);
    } else {
        target=func_00283248(*(float *)(state+0x50)-*(float *)(entity+0x10),*(float *)(state+0x54)-*(float *)(entity+0x14));
        tilt=0;
        blend=*(float *)(state+0x2D0)*4.9999995f-0.1f;
        if(blend>1) blend=1;
        else if(blend<0) blend=0;
        if(blend!=0) {
            if(entity[0x95]!=4) {
                if(func_00283BE0(func_00283248(delta[0],delta[1]),*(float *)(entity+0xF8))<0)
                    speed=-(D_L03_001B1084*0.017453294f);
                else speed=D_L03_001B1084*0.017453294f;
                target=func_00283B98(target,speed*blend);
            }
            tilt=D_L03_001B1080*(blend*0.017453294f);
        }
    }
    rate=0.0025132746f;
    if(entity[0x95]==3) rate=0;
    func_002AAA00(state+0x2A4,state+0x3C8,tilt,rate,0.0025132746f,0.25132746f,0);
    func_002AAA00(state+0x2A8,state+0x3C4,target,rate,0.0025132746f,0.25132746f,0);
    qcopy(entity+0xF0,state+0x2A0);
}
