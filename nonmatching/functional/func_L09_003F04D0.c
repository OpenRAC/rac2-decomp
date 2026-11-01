/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Retained complete C reconstruction, 30 October 2026. NOT MATCHING.
 * Profile: -O2 -G0 -ffunction-sections.
 * us: 09_dobbo: 1332 bytes, expected 1348; us2: 09_dobbo: 1332 bytes, expected 1348; pal: ABSENT.
 * Both actual jump tables were decoded: five mode destinations and seven state destinations.
 * Three paired link spawns retain the real pointer-return constructor, full vector buffers,
 * animation/sound calls and the full 12-GPR/7-FP effect call with four stack arguments. Switch
 * layout, reloads and register allocation differ.
 * Reopen: Independent switch/control-flow and constructor argument-lifetime witness.
 * Local placement checks only; no strict linked or native-runtime claim.
 */
#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define S(p,o) (*(short *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
extern u8 D_L09_001C9F80[];
extern void func_L09_003F0378(void *),func_L09_003F0330(void *);
extern void func_002A7750(void *,int,int),func_002A7470(void *,int,int,int);
extern void func_0029FCC0(void *,int,void *),func_00282F20(void *,void *,float);
extern void func_00282CF0(void *,void *,void *),func_002A6C58(void *,int,int),func_0029F338(void *);
extern int func_002E5CF8(int,int,void *),func_L09_003FB650(void *,void *,int,int);
extern u8 *func_L09_003F6820(void *,void *,void *,void *,int,float,float,float);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,
                         float,float,float,float,int,float,int,int,int,int,int);

/* Three paired beam links per firing cycle, bounded by the two measured
 * script modes and a seven-state animation switch.
 */
void func_L09_003F04D0(u8 *object)
{
    u8 *state = P(object,0x68),*first,*second;
    float point[4],direction[4];
    int mode = I(D_L09_001C9F80,0xC),side,i,half;
    if (mode) {
        side = I(D_L09_001C9F80,0);
        if (F(object,0x18) < F(D_L09_001C9F80,0x28) && side == 1) return;
        if (F(D_L09_001C9F80,0x28) < F(object,0x18) && side == 0) return;
        if (mode == 2) {
            if (F(D_L09_001C9F80,0x38) < F(object,0x18) && side == 1) return;
            if (F(object,0x18) < F(D_L09_001C9F80,0x38) && side == 2) return;
        }
    }
    func_L09_003F0378(object);
    switch (object[0x95]) {
    case 1:
        if (I(state,0x64) == 1) {
            I(state,0x8C) = I(state,0xA4);
            func_002A7750(object,1,2);
        }
        break;
    case 2:
        if (I(state,0x64) != 1 && object[0x20] == 1) {
            I(state,0x8C) = I(state,0xA8);
            if (object[0x43]) func_002A7470(object,0,0,3);
            func_002A7750(object,0,1);
        }
        break;
    }
    switch (object[0x20]) {
    case 0: func_L09_003F0330(object); break;
    case 1:
        if (!S(state,0x92)) {
            if (object[0x43] != 1) func_002A7470(object,1,0,3);
            func_002A7750(object,2,-1);
        }
        break;
    case 2:
        if (object[0x60]&2) {
            H(state,0x92) = H(state,0x9C);
            if (object[0x43] != 2) func_002A7470(object,2,0,3);
            func_002E5CF8(2,0,object);
            for (i=0;i<6;i+=2) {
                func_00282F20(direction,object+0xC0,F(state,0x98)*0.016666668f);
                func_0029FCC0(object,i,point);
                half = i/2;
                first = func_L09_003F6820(point,direction,object,0,
                    S(state,0xA0)*half+S(state,0xA2),F(state,0x94),(float)state[0x34],F(state,0x80));
                if (first && S(first,0xAA)==0xD09 && first[0x20]!=0xFE && first[0x20]!=0xFD) {
                    func_0029FCC0(object,i+1,point);
                    second = func_L09_003F6820(point,direction,object,first,
                        S(state,0xA0)*half+S(state,0xA2),F(state,0x94),(float)state[0x34],F(state,0x80));
                    P(P(first,0x68),0x24)=second;
                    if (second && S(second,0xAA)==0xD09 && second[0x20]!=0xFE && second[0x20]!=0xFD)
                        func_L09_003FB650(first,second,1,0);
                    else func_0029F338(first);
                }
            }
            func_002A7750(object,3,-1);
        }
        break;
    case 3:
        if (!S(state,0x92)) {
            H(state,0x92)=H(state,0x9E);
            if (object[0x43]!=3) func_002A7470(object,3,0,3);
            func_002A7750(object,4,-1);
        }
        break;
    case 4:
        if (object[0x60]&2) {
            if (object[0x43]) func_002A7470(object,0,0,3);
            func_002A7750(object,1,-1);
        }
        break;
    case 5:
        if (object[0x60]&2) {
            I(state,0x8C)=I(state,0xA4); H(state,0x92)=H(state,0x9E);
            if (object[0x43]!=3) func_002A7470(object,3,0,1);
            func_002A7750(object,4,-1);
        }
        break;
    case 6:
        func_002A6C58(object,0,3);
        func_0029FCC0(object,6,direction);
        func_00282CF0(point,direction,object+0x10);
        func_002ABBB8(object,point,direction,0.0f,0.0f,10,3,16,
            4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,1,-1,0,0x810001);
        func_002E5CF8(3,0,object);
        func_0029F338(object);
        break;
    }
}
