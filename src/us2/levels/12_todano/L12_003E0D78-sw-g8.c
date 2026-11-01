#include "include_asm.h"

#include "common.h"
typedef struct PathWaypoint { u8 transform[0x30]; f32 position[4]; u8 tail[0x40]; } PathWaypoint;
typedef struct PathTarget { u8 prefix[0x10]; f32 position[4]; u8 mid[0x14]; u16 flags; u8 tail[0xCA]; } PathTarget;
typedef struct WaypointPath { s32 points[10]; } WaypointPath;
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
extern void func_L12_003E04B8(void *);
extern void func_L12_003E07B0(void *);
extern s32 func_002B1C20(void *,void *);
extern void func_US2_00289840(s32,s32);
extern void func_002A7750(void *,s32,s32);
extern void func_002A7470(void *,s32,s32,s32);
extern void func_002AC728(void *,void *,s32,f32,f32);
extern void func_US2_002A7AA8(void *,s32,s32);
extern void func_00282CF0(void *,void *,void *);
extern f32 func_00282DF0(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_L02_0032E998(void *,void *,void *,void *,s32,f32,f32,void *,void *);
extern s32 func_L12_003E1B28(s32,void *);
extern s32 func_00282948(void *);
extern f32 func_00283B98(f32,f32);
extern f32 func_002A78D8(f32,f32);
extern s32 func_L02_00331440(void *,void *,s32,f32,f32,f32);
extern s32 func_002A7820(s32,s32);
extern s32 func_002ACBC8(void *,s32);
extern int func_002E5E58(int,int,void *);
extern void func_US2_002B1880(s32,s32);
extern void func_L12_00419D68(void *,void *,void *);
extern f32 func_002A7878(f32,f32);
extern s32 func_002A77E0(s32);
extern f32 func_002A7940(void);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_00283248(f32,f32);
extern f32 func_00282E20(void *);
extern void func_002B5278(void *,f32);
extern void func_00282F20(void *,void *,f32);
extern s32 D_L12_001B09F0 __attribute__((sda));
extern s32 D_L12_001B09F4 __attribute__((sda));
extern PathWaypoint *D_L12_001B2F8C MACRO_ADDR;
extern s32 D_L12_001B2E9C MACRO_ADDR;
extern u8 D_001A7A60[] MACRO_ADDR;
extern s32 D_L12_001A903C;
#define ANIM(o,n,t) { if ((o)[0x43]!=(n)) func_002A7470(o,n,0,t); }
#define REST(o) { I(o,0x98)=0; U(o,0x34)=(U(o,0x34)|0x41)&0xEFFF; }

/* Waypoint-following state machine for a level 12 object: walks a path of 0x80-byte
 * waypoints, looks at targets, and counts hits in D_L12_001B09F0 (50/100/150/200). */
void func_US2_L12_003E0D78(u8 *o) {
    u8 *s=*(u8 **)(o+0x68);
    f32 v[4] __attribute__((aligned(16)));
    f32 angle,angle2,speed,yaw,pitch;
    PathTarget *target;
    s32 hit;
    func_L12_003E04B8(o);
    if (o[0x95]==1) goto states;
    if (o[0x95]==3) {
        hit=func_002B1C20(o,s+0x60);
        if (hit&1) {
            D_L12_001B09F0++;
            if (D_L12_001B09F0==50) func_US2_00289840(0xA2D,0x84);
            else if (D_L12_001B09F0==100) func_US2_00289840(0xA2E,0x85);
            else if (D_L12_001B09F0==150) func_US2_00289840(0xA2F,0x86);
            else if (D_L12_001B09F0==200) func_US2_00289840(0xA30,0x87);
            func_002A7750(o,1,0);
            ANIM(o,4,20);
            D_L12_001B09F4++;
            func_002AC728(o,o+0x10,-1,1.0f,0.0f);
            func_US2_002A7AA8(o,0,3);
            H(s,0x98)=0;
            F(s,0x20)=H(s,0x24);
            REST(o);
        } else if (hit&2) func_002A7750(o,4,1);
    }
states:
    switch(o[0x20]) {
    case 2:
        D_L12_001B09F4=0;
        I(s,0x7B8)=0;
        func_00282CF0(v,s+0x740,o+0x10);
        speed=0.10000000894069672f;
        if (func_00282DF0(v)>speed) { func_00282F20(v,v,speed); goto add; }
        func_002A7750(o,3,-1);
        ANIM(o,4,20);
        goto add;
    case 3: {
        WaypointPath *path=(WaypointPath *)(s+0x518);
        func_00283098(v,s+0x770,&D_L12_001B2F8C[path->points[I(s,0x794)]]);
        func_00282CC0(v,v,D_L12_001B2F8C[path->points[I(s,0x794)]].position);
        func_L02_0032E998(o+0x10,v,&angle,s+0x110,I(s,0x790),0.0f,F(s,0x7A4),s+0x79C,s+0x7A0);
        if (I(s,0x540) && I(s,0x540)==I(s,0x794)-1) {
            speed=0.05000000447034836f;
            if (!I(s,0x7B8)) {
                I(s,0x7B8)=func_L12_003E1B28(I(s,0x544),o);
                if (I(s,0x7B8)) { func_002A7750(o,7,2); ANIM(o,5,10); }
            }
        } else speed=F(s,0x7AC);
        if (!func_00282948(s+0x7B0)) angle=func_00283B98(angle,F(s,0x7B4));
        if (!I(s,0x7B0) && I(s,0x5D0)>60) {
            I(s,0x7B0)=60;
            F(s,0x7B4)=func_002A78D8(90.0f,135.0f)*0.01745329424738884f;
        }
        if (func_L02_00331440(o,v,1,angle,speed,-1.0f)&0x80) {
            func_002A7750(o,4,-1);
            ANIM(o,1,20);
            if (I(s,0x540) && I(s,0x540)==I(s,0x794)) I(s,0x7A8)=func_002A7820(80,180);
            else I(s,0x7A8)=func_002A7820(10,160);
        }
        if (F(o,0x18)<50.0f) func_002A7750(o,1,0);
        if (I(s,0x5D0)>200) {
            func_002A7750(o,1,0);
            ANIM(o,4,20);
            func_002AC728(o,o+0x10,-1,1.0f,0.0f);
            func_US2_002A7AA8(o,0,3);
            F(s,0x20)=H(s,0x24);
            REST(o);
        } else if (F(s,0x7A4)>=0.5f && F(s,0x61C)<4.0f) F(s,0x7A4)=0.4f;
        if (I(s,0x794)!=I(s,0x798) && I(s,0x7A8)>20) I(s,0x7A8)=20;
        break;
    }
    case 5:
        func_L02_0032E998(o+0x10,s+0x740,&angle2,s+0x110,I(s,0x790),0.0f,F(s,0x7A4),s+0x79C,s+0x7A0);
        if (!func_00282948(s+0x7B0)) angle2=func_00283B98(angle2,F(s,0x7B4));
        func_L02_00331440(o,s+0x740,1,angle2,F(s,0x7AC),-1.0f);
        if (F(o,0x18)<50.0f) func_002A7750(o,1,0);
        if (!I(s,0x7B0) && I(s,0x5D0)>60) {
            I(s,0x7B0)=60;
            F(s,0x7B4)=func_002A78D8(90.0f,135.0f)*0.01745329424738884f;
        }
        if (func_002ACBC8(o+0x10,I(s,0x54C))) { func_002A7750(o,6,-1); ANIM(o,3,20); }
        break;
    case 4: {
        if (I(s,0x794)!=I(s,0x798) && func_00282948(s+0x7A8)) {
            if (I(s,0x798)>=6) {
                if (!D_L12_001B09F4 && !D_001A7A60[10]) {
                    D_001A7A60[10]=1;
                    func_002E5E58(1,0,0);
                    func_US2_002B1880(0x1233,-1);
                    D_L12_001A903C=1;
                }
                func_L12_00419D68((PathTarget *)(D_L12_001B2E9C+(I(s,0x514)<<8)),s+0x740,s+0x750);
                func_002A7750(o,5,-1);
                ANIM(o,4,20);
            } else {
                I(s,0x794)=I(s,0x798);
                func_002A7750(o,3,-1);
                ANIM(o,4,20);
                F(s,0x7A4)=func_002A7878(0.5f,0.7f);
            }
            break;
        }
        if (U(o,0x96)<2 || func_00282948(s+0x7BC)) {
            if ((u32)(I(s,0x794)-1)<4 && (U(o,0x96)<2 || func_002A77E0(2))) {
                qcopy(s+0x780,D_L12_001B2F8C[I(s+((u32)(I(s,0x794)-1)<<2),0x530)].position);
            } else {
                target=(PathTarget *)((I(s,0x548)<<8)+D_L12_001B2E9C);
                if ((target->flags^1)&1) { qcopy(s+0x780,target->position); F(s,0x788)+=0.5f; }
                else {
                    f32 randomYaw=func_002A7940();
                    F(s,0x780)=func_00283180(randomYaw);
                    F(s,0x784)=func_00283198(randomYaw);
                    I(s,0x788)=0;
                    F(s,0x788)+=func_002A7878(F(s,0x788),0.5f);
                    func_00282CC0(s+0x780,s+0x780,o+0x10);
                }
            }
            I(s,0x7BC)=func_002A7820(60,120);
        }
        func_00282CF0(v,s+0x780,o+0x10);
        yaw=func_00283248(v[0],v[1]);
        pitch=-func_00283248(func_00282E20(v),v[2]);
        func_002B5278(o,yaw);
        F(s,0x6A4)=F(s,0x724)=pitch*0.5f;
        break;
    }
    case 8:
        if (U(o,0x96)>=5) {
            REST(o);
            func_002AC728(o,o+0x10,-1,1.0f,0.0f);
            func_002A7750(o,1,0);
        }
    case 6:
        func_00282CF0(v,s+0x750,o+0x10);
        speed=0.10000000894069672f;
        if (func_00282DF0(v)>speed) {
            func_00282F20(v,v,speed);
        } else {
            func_002A7750(o,1,0);
            ANIM(o,4,20);
            U(o,0x7C)=1<<func_002A77E0(6);
            REST(o);
        }
add:
        func_00282CC0(o+0x10,o+0x10,v);
        break;
    case 7:
        if (o[0x60]&2) { func_002A7750(o,3,1); ANIM(o,7,10); }
        break;
    case 1:
        REST(o);
        break;
    }
    func_L12_003E07B0(o);
}
