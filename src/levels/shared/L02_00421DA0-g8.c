#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { u8 reserved[0x140]; float position[4]; } FlareTargetView;
extern FlareTargetView D_L02_001BA3C0 __attribute__((nosda));
extern float D_L02_001B1FA8 __attribute__((sda)),D_L02_001B1FAC __attribute__((sda));
extern float D_L02_001B1FB0 __attribute__((sda)),D_L02_001B1FB4 __attribute__((sda));
extern float D_L02_001B1FB8 __attribute__((sda));
extern float D_L02_001B1FBC __attribute__((sda)),D_L02_001B1FC0 __attribute__((sda));
extern u32 D_L02_001B1FC8 __attribute__((sda)),D_L02_001B1FCC __attribute__((sda));
extern void func_00282CF0(void *,void *,void *);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern float func_002A78D8(float,float);
extern int func_001163B0(void);
extern void func_00282D30(void *,void *,float);
extern u8 *func_002C2210(void *,int,u32,float,float,int,int,void *,int,float);
extern int func_00283CF0(float);
extern void func_00282CC0(void *,void *,void *);

/* Emit paired particles, choosing an outward or target-directed trajectory. */
void func_L02_00421DA0(void *origin,int count,int inner)
{
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float base[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float toward[4] __attribute__((aligned(16)));
    int i,sign;
    float size,angle,speed;
    u8 *particle;
    func_00282CF0(base,D_L02_001BA3C0.position,origin);
    base[2]=0;
    axis[0]=0;axis[1]=0;axis[2]=1;axis[3]=1;
    for(i=0;i<count;i++) {
        size=func_002A7878(D_L02_001B1FBC,D_L02_001B1FC0);
        sign=func_002A77E0(2);
        if (!sign) sign--;
        angle=func_002A7878(-1.0471977f,1.0471977f);
        func_002ACEC0(velocity,base,axis,angle);
        speed=func_002A7878(D_L02_001B1FA8,D_L02_001B1FAC)*0.016666668f;
        func_00282F20(velocity,velocity,speed);
        velocity[2]=func_002A7878(D_L02_001B1FB0,D_L02_001B1FB4)*0.016666668f;
        qcopy(position,origin);
        position[0]+=func_002A78D8(0,0.15f);
        position[1]+=func_002A78D8(0,0.15f);
        position[2]+=func_002A78D8(0,0.15f);
        if(!inner) {
            if(!(func_001163B0()&1)) {
                func_00282D30(velocity,velocity,1.5f);
                particle=func_002C2210(position,60,D_L02_001B1FC8,size*0.35f,size,0,sign,velocity,0,D_L02_001B1FB8);
                if(particle) particle[9]=(u8)(func_00283CF0(4.0f)+0x70);
                particle=func_002C2210(position,60,D_L02_001B1FCC,size*0.245f,size*0.7f,1,-sign,velocity,0,D_L02_001B1FB8);
            } else {
                func_00282CF0(toward,D_L02_001BA3C0.position,position);
                func_00282F20(toward,toward,speed);
                func_00282CC0(velocity,velocity,toward);
                particle=func_002C2210(position,40,D_L02_001B1FC8,size*2.05f,size,0,sign,velocity,0,D_L02_001B1FB8);
                if(particle) particle[9]=(u8)(func_00283CF0(4.0f)+0x70);
                particle=func_002C2210(position,40,D_L02_001B1FCC,size*1.4350001f,size*0.7f,1,-sign,velocity,0,D_L02_001B1FB8);
            }
        } else {
            if(!(func_001163B0()&1)) {
                func_00282D30(velocity,velocity,1.5f);
                particle=func_002C2210(position,60,D_L02_001B1FC8,size*0.3f,size,0,sign,velocity,0,D_L02_001B1FB8);
                if(particle) particle[9]=(u8)(func_00283CF0(4.0f)+0x70);
                particle=func_002C2210(position,60,D_L02_001B1FCC,size*0.21000001f,size*0.7f,1,-sign,velocity,0,D_L02_001B1FB8);
            } else {
                func_00282CF0(toward,D_L02_001BA3C0.position,position);
                func_00282F20(toward,toward,speed);
                func_00282CC0(velocity,velocity,toward);
                particle=func_002C2210(position,40,D_L02_001B1FC8,size*0.25f,size,0,sign,velocity,0,D_L02_001B1FB8);
                if(particle) particle[9]=(u8)(func_00283CF0(4.0f)+0x70);
                particle=func_002C2210(position,40,D_L02_001B1FCC,size*0.175f,size*0.7f,1,-sign,velocity,0,D_L02_001B1FB8);
            }
        }
        if(particle) particle[9]=(u8)(func_00283CF0(4.0f)+0x70);
    }
}
