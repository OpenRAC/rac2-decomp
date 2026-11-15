#include "common.h"
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_0019B2E8[];
extern float D_L12_001B0A20 __attribute__((sda));
extern float D_L12_001B0A24 __attribute__((sda));
extern float D_L12_001B0A30[4] __attribute__((sda));
typedef struct TodanoPlayerView { u8 pad[0x80]; float position[4]; } TodanoPlayerView;
extern TodanoPlayerView D_00189E20;
extern u8 *D_0018C0B0 NOT_SDA;
extern void func_L12_003E1638(u8 *);
extern void func_L12_003E19F0(u8 *);
extern int func_002B3890(u8 *);
extern void func_002A7750(u8 *,int,int);
extern void func_002A7470(u8 *,int,int,int);
extern void func_002B60B0(u8 *,float,float,float,float);
extern int func_002A7820(int,int);
extern int func_002B1C20(u8 *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002A8F70(u8 *,u8 *,int,void *,void *,float);
extern void func_002A6C58(u8 *,int,int);
extern void func_L01_003E9CF8(u8 *,int,int);
extern void func_0029F338(u8 *);
extern float func_002A7940(void);
extern float func_002A7878(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern int func_L01_00321178(u8 *,void *);
extern int func_002A77E0(int);
extern float func_00283248(float,float);
extern void func_002B50E0(u8 *,void *,float);
extern void func_L12_003E1AA8(u8 *);
extern void func_002AA800(void *,int,float,float);
extern float func_0029F530(u8 *);
extern void func_002A8D70(u8 *,int,int,int,int,int,float,float,float);
extern void func_002B5258(u8 *);
extern void func_00283098(void *,void *,void *);
extern void func_L12_003E0A38(void *,void *,void *,int);
/* Moby update: Mutant Test-Squirrel (class 4020, PS3 name). */
void func_L12_003E0BF0(u8 *o) {
    u8 *d=*(u8 **)(o+0x68);
    float temp[4] __attribute__((aligned(16)));
    float angle, speed;
    func_L12_003E1638(o);
    switch(o[0x95]) {
    case 5: {

        if(func_002B3890(o)) {
            *(u16 *)(o+0x34)|=1;
            *(int *)(o+0x98)=0;
            o[0x31]=0;

        }
        if(D_0019B2E8[o[0xB0]+(D_001A79F0<<4)]&0x80) {
            if(*(int *)(d+0x13C)==-1) {
                func_002A7750(o,1,0);
                if(o[0x43]) func_002A7470(o,0,0,0);
            } else {
                func_002A7750(o,9,4);
                if(o[0x43]!=14) func_002A7470(o,14,0,0);
                *(float *)(o+0x18)+=4.0f;
                *(int *)(o+0x98)=0;
                *(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|0x41)&0xEFFF;
            }
            *(int *)(o+0x98)=*(int *)(*(u8 **)(o+0x24)+0x10);
            o[0x31]=1;
            *(u16 *)(o+0x34)&=0xFFFE;
        }
        break; }
    case 0:
        if(func_002B3890(o)) func_002B60B0(o,0.001111111138f,D_L12_001B0A20*0.0166666675359f,0.0008726647356525064f,0.104719772935f);
        if(*(short *)(d+0x364)==1) {
            func_002A7750(o,5,2);
            if(o[0x43]!=2) func_002A7470(o,2,0,10);
        } else if(*(short *)(d+0x366)) {
            func_002A7750(o,3,1);
            if(o[0x43]!=3) func_002A7470(o,3,0,20);
            *(short *)(d+0x366)=0;
            if(*(short *)(d+0x360)<300) *(short *)(d+0x360)=func_002A7820(480,600);
        }
        break;
    case 1:
        if(func_002B3890(o)) func_002B60B0(o,0.003333333414f,D_L12_001B0A24*0.0166666675359f,0.0017453294713050127f,0.20943954587f);
        if(*(short *)(d+0x364)==1) {
            func_002A7750(o,6,2);
            if(o[0x43]!=7) func_002A7470(o,7,0,10);
        } else if(!*(short *)(d+0x360)) {
            func_002A7750(o,1,0);
            if(o[0x43]) func_002A7470(o,0,0,20);
        }
        break;
    case 2:
        if(func_002B3890(o)) func_002B60B0(o,0.003333333414f,D_L12_001B0A24*0.0166666675359f,0.0017453294713050127f,0.20943954587f);
        if(*(short *)(d+0x364)!=1) {
            func_002A7750(o,3,1);
            if(o[0x43]!=3) func_002A7470(o,3,0,20);
            *(short *)(d+0x360)=func_002A7820(580,600);
        }
        break;
    case 3: {
        int hit; u8 *target;
        hit=func_002B1C20(o,d+0x60);
        target=*(u8 **)(d+0x38);
        if(target && *(short *)(target+0xAA)==0xFAB) {
            FastVecSub(temp,o+0x10,target+0x10);
            vec_scale_to_length(temp,temp,1.0f);
            func_002A8F70(o,D_0018C0B0,0x10000,*(u8 **)(d+0x38)+0x10,temp,50.0f);
        }
        if(hit&1) {
            SetDeathBits(o,0,3);
            qcopy(temp,o+0x10);
            temp[2]+=0.25f;
            func_L01_003E9CF8(o,0,0);
            func_0029F338(o);
            return;
        }
        if(hit&2) {
            if(*(short *)(d+0x364)==1) {
                func_002A7750(o,6,2);
                if(o[0x43]!=7) func_002A7470(o,7,0,20);
            } else {
                func_002A7750(o,3,1);
                if(o[0x43]!=3) func_002A7470(o,3,0,20);
                *(short *)(d+0x360)=func_002A7820(580,600);
            }
        }
        break; }
    case 4:
        if(func_002B3890(o)) func_002B60B0(o,0.004444444552f,D_L12_001B0A24*0.0166666675359f,0.0034906589426100254f,0.20943954587f);
        break;
    }
    switch(o[0x20]) {
    case 1:
        if(!*(short *)(d+0x362)) {
            func_002A7750(o,2,-1);
            angle=func_002A7940();
            speed=func_002A7878(3.0f,5.0f);
            *(float *)(d+0x350)=func_00283180(angle)*speed;
            *(float *)(d+0x354)=func_00283198(angle)*speed;
            *(int *)(d+0x358)=0;
            FastVecAdd(d+0x350,d+0x350,d+0x340);
            if(o[0x43]!=15) func_002A7470(o,15,0,10);
        }
        func_002B5258(o);
        break;
    case 2: {
        int hit;
        hit=func_L01_00321178(o,d+0x350);
        if((*(u16 *)(o+0x96)>=31 && (hit&0x80)) || *(u16 *)(o+0x96)>=601) {
            func_002A7750(o,1,-1);
            *(short *)(d+0x362)=func_002A7820(300,500);
            if(o[0x43]!=func_002A77E0(2)) func_002A7470(o,func_002A77E0(2),0,20);
        }
        break; }
    case 3: func_002B5258(o); break;
    case 5: {
        u8 *position=o+0x10;
        u8 *target=*(u8 **)(d+0x368);
        int v;
        angle=func_00283248(D_00189E20.position[0]-*(float *)(target+0x10),D_00189E20.position[1]-*(float *)(target+0x14));
        func_002B50E0(o,position,angle);
        v=o[0x60];
        v&=2;
        if(v) {
            func_002A7750(o,6,-1);
            if(o[0x43]!=7) func_002A7470(o,7,0,20);
        } else {
            v=*(u16 *)(o+0x96);
            if(v==20) func_L12_003E1AA8(o);
        }
        break; }
    case 6:
        if(func_L01_00321178(o,*(u8 **)(d+0x368)+0x10)&0x80) {
            func_002A7750(o,7,-1);
            if(o[0x43]!=8) func_002A7470(o,8,0,20);
        }
        break;
    case 7:
        if(o[0x60]&2) {
            func_002A7750(o,6,-1);
            if(o[0x43]!=7) func_002A7470(o,7,0,10);
        } else {
            float time;
            u8 *yaw=o+0xF8;
            u8 *target=*(u8 **)(d+0x368);
            angle=func_00283248(*(float *)(target+0x10)-*(float *)(o+0x10),*(float *)(target+0x14)-*(float *)(o+0x14));
            StepAngleTowardTarget(yaw,0,angle,0.058177649974823f);
            time=func_0029F530(o);
            if(12.0f<=time && time<=14.0f) func_002A8D70(o,2,1,0,1,0,0.25f,d[0x34],1.0f);
            func_002B5258(o);
        }
        break;
    case 10: {
        u8 *position=o+0x10;
        u8 *target=*(u8 **)(d+0x374);
        angle=func_00283248(*(float *)(target+0x10)-*(float *)(o+0x10),*(float *)(target+0x14)-*(float *)(o+0x14));
        func_002B50E0(o,position,angle);
        if(o[0x43]==5 && *(float *)(o+0x18)<*(float *)(d+0x348)+*(float *)(d+0x1F8)*10.0f) func_002A7470(o,6,0,10);
        if(o[0x43]==6 && (o[0x60]&2)) {
            func_002A7750(o,11,-1);
            if(o[0x43]!=7) func_002A7470(o,7,0,20);
        }
        break; }
    case 11:
        func_L01_00321178(o,*(u8 **)(d+0x374)+0x10);
        if(*(float *)(d+0x21C)<2.0f) {
            func_002A7750(o,12,-1);
            if(o[0x43]!=8) func_002A7470(o,8,0,20);
        }
        break;
    case 12: {
        float time;
        if(*(u8 **)(d+0x374)) {
            func_L01_00321178(o,*(u8 **)(d+0x374)+0x10);
            time=func_0029F530(o);
            if(11.0f<=time) {
                int release=1;
                matrix_mul_vec3(temp,D_L12_001B0A30,o+0xC0);
                FastVecAdd(temp,temp,o+0x10);
                if(!(14.0f<=time)) release=0;
                func_L12_003E0A38(*(u8 **)(d+0x374),temp,o+0xF0,release);
                if(release) *(int *)(d+0x374)=0;
            }
        }
        if(o[0x60]&2) {
            func_002A7750(o,13,-1);
            if(o[0x43]!=9) func_002A7470(o,9,0,10);
        }
        break; }
    case 13:
        if(o[0x60]&2) {
            func_002A7750(o,1,0);
            if(o[0x43]) func_002A7470(o,0,0,10);
        }
        break;
    }
    func_L12_003E19F0(o);
}
