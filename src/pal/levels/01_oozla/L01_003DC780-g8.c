/*
 * func_PAL_L01_003DC780, the PAL copy of func_L01_003D8358 (oozla, -G8
 * profile): the same C, where the frame step 1/60 becomes 1/50, the two turn
 * rates grow by 6/5 and the spring gains are scaled by 1.44 and 1.2.
 *
 * Case 0 waits for a positive height from func_PAL_L01_003BEB40, then either
 * picks two random angles and moves to case 1 (linked object at s+0x8C) or calls func_0026FEB8 and
 * moves to case 2. Case 1 falls to case 2 once the linked object is gone or
 * in state 0xFE/0xFD. In case 2, when hero mode (0x34E) is 0 and hero+0x33C
 * points at this object, two func_002AA898 springs are driven by dot
 * products of the hero offset and the hero is moved by the resulting change;
 * otherwise the height eases towards s+0x84, the springs relax and a
 * one-shot func_002E5CF8 fires when the threshold is crossed.
 *
 * Shape notes: height stays distinct from the first dot product. The scale
 * constant is its own variable (k), read once for -k*y and k*x; reusing one
 * variable for the constant and the product made sched2 issue the zero
 * direction argument before k*x. speed*step is added to the height as one
 * product so the multiply keeps retail's operand order.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
typedef struct { u8 pad[0x34E]; s16 mode; } Hero;
extern Hero D_00189E20 NOT_SDA;
#define HERO ((u8 *)&D_00189E20)
extern u8 *D_L01_001B255C;
extern u8 D_L01_002A4E20[];
extern f32 D_L01_001B0768 __attribute__((sda));
extern f32 D_L01_001B076C __attribute__((sda));
extern f32 D_L01_001B0774 __attribute__((sda));
extern f32 D_L01_001B077C __attribute__((sda));
extern f32 D_L01_001B0780 __attribute__((sda));
extern f32 D_L01_001B0784 __attribute__((sda));
extern f32 D_L01_001B0788 __attribute__((sda));
extern f32 D_L01_001B078C __attribute__((sda));
extern f32 D_L01_001B0790 __attribute__((sda));
extern void func_00282D30(void *,void *,f32);
extern f32 func_PAL_L01_003BEB40(void);
extern f32 func_002A7878(f32,f32);
extern void func_0026FEB8(void *,s32,s32);
extern void func_00282CF0(void *,void *,void *);
extern f32 func_00282DB0(void *,void *);
extern f32 func_002AA898(void *,f32,void *,f32,f32,f32,s32);
extern void func_L01_00316C48(void *,void *,void *,void *,void *);
extern s32 func_002E5CF8(s32,s32,void *);
extern void func_002AEF28(void *,void *,void *,f32,f32,f32);
extern f32 func_00283B98(f32,f32);
extern void func_00282CC0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);
void func_PAL_L01_003DC780(u8 *m)
{
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[4] __attribute__((aligned(16)));
    f32 relative[4] __attribute__((aligned(16)));
    f32 oldAngle[4] __attribute__((aligned(16)));
    f32 oldPos[4] __attribute__((aligned(16)));
    f32 move[4] __attribute__((aligned(16)));
    u8 *s = *(u8 **)(m+0x68);
    f32 k, height, previous, x, y, pitch, scale, speed, step;
    u8 *other;
    func_00282D30(delta,m+0x10,-1.0f);
    qcopy(rotation,m+0xF0);
    previous=F(m,0x18);
    height=func_PAL_L01_003BEB40();
    F(s,0x84)=height+0.2f;
    switch(m[0x20]) {
    case 0:
        if(height>0.0f) {
            I(s,0x80)=1;
            qcopy(s+0x60,m+0xF0);
            qzero_nc(s+0x70);
            if(I(s,0x8C)!=-1) {
                F(m,0x18)=F(s,0x84)-5.0f;
                F(m,0xF0)=func_002A7878(-1.57079637f,1.57079637f);
                F(m,0xF4)=func_002A7878(-1.57079637f,1.57079637f);
                m[0x20]=1;
            } else {
                func_0026FEB8(D_L01_002A4E20,H(m,0xB2),H(m,0xAA));
                m[0x20]=2;
            }
        }
        break;
    case 1:
        other=D_L01_001B255C+(I(s,0x8C)<<8);
        if(!other || other[0x20]==0xFE || other[0x20]==0xFD) m[0x20]=2;
        break;
    case 2:
        if(D_00189E20.mode==0 && *(u8 **)(HERO+0x33C)==m) {
            func_00282CF0(relative,HERO+0x80,m+0x10);
            x=func_00282DB0(relative,m+0xC0);
            y=func_00282DB0(relative,m+0xD0);
            k=D_L01_001B076C;
            pitch=-k*y;
            *(Quad *)oldAngle=*(Quad *)(s+0x60);
            *(Quad *)oldPos=*(Quad *)(m+0x10);
            scale=k*x;
            func_002AA898(s+0x60,pitch,s+0x70,D_L01_001B077C*1.44f,D_L01_001B0780*1.44f,D_L01_001B0784*1.2f,0);
            func_002AA898(s+0x64,scale,s+0x74,D_L01_001B077C*1.44f,D_L01_001B0780*1.44f,D_L01_001B0784*1.2f,0);
            func_L01_00316C48(HERO+0x80,move,m+0x10,oldAngle,s+0x60);
            func_00282CF0(HERO+0x100,move,HERO+0x80);
            F(HERO,0x108)+=F(m,0x18)-oldPos[2];
        } else {
            speed=D_L01_001B0774;
            step=(F(s,0x84)-F(m,0x18))*0.020000001f;
            F(m,0x18)=F(m,0x18)+speed*step;
            if(F(m,0x18)<F(s,0x84)-2.0f) F(m,0x18)+=speed*0.020000001f;
            else {
                func_002AA898(s+0x60,0.0f,s+0x70,D_L01_001B0788*1.44f,D_L01_001B078C*1.44f,D_L01_001B0790*1.2f,0);
                func_002AA898(s+0x64,0.0f,s+0x74,D_L01_001B0788*1.44f,D_L01_001B078C*1.44f,D_L01_001B0790*1.2f,0);
            }
            if(F(m,0x18)>F(s,0x84)) F(m,0x18)=F(s,0x84);
            if(previous<height-D_L01_001B0768 && F(m,0x18)>=height-D_L01_001B0768 && !I(s,0xA0)) {
                func_002E5CF8(0,0,m);
                I(s,0xA0)=1;
            }
        }
        func_002AEF28(m,s+0x90,s+0x94,0.0200712885708f,0.008726647f,0.010821043f);
        F(m,0xF0)=func_00283B98(F(s,0x60),F(m,0xF0));
        F(m,0xF4)=func_00283B98(F(s,0x64),F(m,0xF4));
        func_00282CC0(delta,delta,m+0x10);
        func_002AD6F0(s+0x20,delta,rotation,m+0xF0);
        break;
    }
}
