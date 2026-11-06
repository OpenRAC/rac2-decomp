/* func_US2_L08_003F7AB0, the USA v2.00 copy of func_L08_003F6610: the same C, where the frame test becomes a threshold call
   (ref_US2_L08_003F7AB0_00: func_US2_L08_003326F0 in level 8, func_US2_002AF9C8 in level 17). */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 D_00189EA0[];
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
#define E_I(p,o) (*(int *)((u8 *)(p)+(o)))
#define E_F(p,o) (*(float *)((u8 *)(p)+(o)))
extern void func_L08_003F6348(void *,void *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern int D_L08_001B2508;
extern u8 D_L08_001B9B00[];
extern u8 *D_L08_001FE7C0[];
extern u8 *D_L08_001B2ACC __attribute__((sda));
extern float D_L08_001B0B5C __attribute__((sda));
extern u8 D_L08_001AC5E0[] MACRO_ADDR;
extern void func_0029F338(void *);
extern int func_002A8600(void **,int,int,int);
extern int func_00282978(void *);
extern int func_002A77E0(int);
extern void func_L04_003429F8(void *,void *,void *,int,void *,int,float);
extern int func_L08_003F6568(void *,void *);
extern void func_002A7470(void *,int,int,int);
extern int ref_US2_L08_003F7AB0_00(void *,float);
extern float func_00282DF0(void *);
extern void func_00282FB8(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern int func_002A7820(int,int);
extern void func_L02_0031E9E8(void *,float);
extern float func_002A7878(float,float);
extern float func_002A89A8(void *,int,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_002ACB48(void *,float);
extern float func_L00_0031CDD0(void *,void *,int,float,float);
extern u8 *func_L08_003F6018(void *,void *,void *);
extern int func_L06_0035EA68(void *,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
typedef struct { u8 pad[0x120]; float speed; int path,object; u16 delay, timer; u8 limit,count,nearest,pad2; int children[2]; int pad3; int targets[4]; } FVars;
void func_US2_L08_003F7AB0(u8 *m)
{
    void *found;
    struct { TI128 target, direction, velocity, step; } frame;
    u8 *p=*(u8 **)(m+0x68);
    int index;

    void *a2,*t0;
    int a3,t1;
    func_L08_003F6348(m,p);
    if(m[0x31] && func_00282E48(m+0x10,D_L08_001B9B00)<24.0f) {
        func_002A93B0(m);m[0x6f]=0x16;
    }
    switch(m[0x20]) {
    case 0:
        if(D_L08_001B2508) {
            int i;
            found=0;
            for(i=0;i<2;i++) {
                while(!func_002A8600(&found,((FVars *)p)->children[i],0,0)) func_0029F338(found);
            }
            m[0x20]=1;
        }
        p[0x29]=1;
        break;
    case 1:
        if(!func_00282978(p+0x12e)) break;
        if(!func_002A77E0(7)) {
            a2=0;a3=0;t0=0;t1=0;
            if(E_I(p,0x124)!=-1) {a2=p+0x124;a3=1;}
            if(E_I(p,0x128)!=-1) {u8 *obj=D_L08_001FE7C0[E_I(p,0x128)];t1=E_I(obj,0);t0=obj+0x10;}
            func_L04_003429F8(m,p+0xc0,a2,a3,t0,t1,E_F(p,0x120));
        } else {
            u8 *obj=*(u8 **)(p+0x100);
            if(obj && obj[0x20]!=0xfe && obj[0x20]!=0xfd) qcopy(p+0xc0,obj+0x10);
            else {E_I(p,0x100)=0;E_I(p,0x104)=2;}
        }
        if(E_I(p,0x104)==2) break;
        index=func_L08_003F6568(m,p);
        if(p[0x130]>p[0x131] && index!=-1) {
            m[0x20]=2;
            if(m[0x43]!=1) func_002A7470(m,1,0,10);
        }
        break;
    case 2: {
        u8 *chosen;
        float f;
        if(m[0x60]&2) {
            m[0x20]=1;
            if(m[0x43]) func_002A7470(m,0,0,10);
            break;
        }
        if(!ref_US2_L08_003F7AB0_00(m,12.0f)) break;
        chosen=0;
        if(p[0x132]) {
            int i;
            float best, d;
            best=100000.0f;
            for(i=0;i<4;i++) {
                if(((FVars *)p)->targets[i]!=-1) {
                    u8 *obj=D_L08_001B2ACC+((FVars *)p)->targets[i]*128;
                    d=func_00282E48(D_00189EA0,obj+0x30);
                    if(d<best) {chosen=obj;best=d;}
                }
            }
            if(!chosen) {
                func_00282CF0(&frame.target,p+0xc0,(m+0x10));
                func_00282D30(&frame.target,&frame.target,0.5f);
                if(E_F(p,0x120)>3.0f) func_00282FB8(&frame.target,&frame.target,3.0f);
                if(func_00282DF0(&frame.target)<3.0f) func_00282F20(&frame.target,&frame.target,3.0f);
                func_00282CC0(&frame.target,&frame.target,(m+0x10));
            } else qcopy(&frame.target,chosen+0x30);
        } else {
            int k=func_002A7820(0,3);
            int i;
            for(i=0;i<4;i++) {
                int slot=(i+k)%4;
                if(((FVars *)p)->targets[slot]!=-1) {
                    chosen=D_L08_001B2ACC+((FVars *)p)->targets[slot]*128;
                    break;
                }
            }
            if(!chosen) {
                float radius=E_F(p,0x120);if(radius<3.0f) radius=3.0f;
                func_L02_0031E9E8(&frame.target,radius);
                func_00282CC0(&frame.target,&frame.target,(m+0x10));
            } else qcopy(&frame.target,chosen+0x30);
        }
        if(chosen) {
            func_00282D30(&frame.direction,chosen,func_002A7878(-1.0f,1.0f));
            func_00282CC0(&frame.target,&frame.target,&frame.direction);
            func_00282D30(&frame.direction,chosen+0x10,func_002A7878(-1.0f,1.0f));
            func_00282CC0(&frame.target,&frame.target,&frame.direction);
        }
        {float height=func_002A89A8(&frame.target,0,0.5f);
        if(height!=0.0f) E_F(&frame.target,8)=height;}
        func_00282CF0(&frame.direction,&frame.target,(m+0x10));
        f=func_00282DF0(&frame.direction)/D_L08_001B0B5C<0.08000000566f ? func_00282DF0(&frame.direction)/D_L08_001B0B5C : 0.08000000566f;
        func_00282F20(&frame.direction,&frame.direction,f);
        func_0029FCC0(m,0,&frame.velocity);
        func_00282F20(&frame.step,&frame.direction,0.05f);
        func_002ACB48(&frame.step,0.025f);
        func_00282CC0(&frame.velocity,&frame.velocity,&frame.step);
        E_F(&frame.direction,8)=func_L00_0031CDD0(&frame.velocity,&frame.target,0,f,-0.002722222358f);
        func_L08_003F6018(m,&frame.velocity,&frame.direction);
        ((FVars *)p)->timer=((FVars *)p)->delay;
        ((FVars *)p)->count++;
        break;
    }
    case 3:
        func_L06_0035EA68(m,p+0x60);
        if(m[0x60]&2) {
            m[0x20]=1;
            if(m[0x43]) func_002A7470(m,0,0,20);
        }
        break;
    case 4:
        if(func_L06_0035EA68(m,p+0x60)&0x40) {
            func_00282F20(&frame.target,D_L08_001AC5E0,0.1666666716f);
            func_002ABBB8(m,&frame.target,0,0.0f,0.0f,30,8,20,8.0f,4.0f,18.0f,1.0f,1,15.0f,1,1,-1,0,0x810001);
            func_0029F338(m);
        }
        break;
    }
}
