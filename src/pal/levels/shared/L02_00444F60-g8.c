#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern int D_L02_001AEC78 MACRO_ADDR;
extern float ref_L02_0043F4C8_1[] __attribute__((sda));
extern float ref_L02_0043F4C8_2[] __attribute__((sda));
extern float ref_L02_0043F4C8_3 __attribute__((sda));
extern float ref_L02_0043F4C8_4 __attribute__((sda));
extern float ref_L02_0043F4C8_5 __attribute__((sda));
extern u8 D_00189E20[];
extern u8 D_L02_001A8F20[] MACRO_ADDR;
extern float func_002A7940(void);
extern float func_002A78D8(float,float);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern void func_002A7750(void *,int,int);
extern float func_00283B98(float,float);
extern float func_00283198(float);
extern void func_002833F0(void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_L00_003206B8(void *,int);
extern u8 *func_002A9640(void *,u32,int);
extern int func_002A7820(int,int);
extern void func_00282F20(void *,void *,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00283698(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern float func_00282C68(float,float,float);
extern int func_002761F8(void *,void *,int,void *,int);
extern int func_002B3868(void *);
extern int func_002E5CF8(int,int,char *);
extern void func_PAL_L01_002E2968(void *,void *,int,int,int,float,float,float);
extern int func_00282978(short *);
extern void func_00282C88(void *);
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_PAL_002B15D8(char *,int,float *,u8,float,float,float,float);
extern void func_PAL_L00_003281C0(void *,int,float);
extern void func_0029F338(void *);
extern void func_PAL_L02_00445550(void *);

/* Advance the hovering object's idle, launch and impact states. */
void func_PAL_L02_00444F60(u8 *object)
{
    Vector delta;
    /* The tilt input dies after 833F0. The later inverse has four rows. */
    union {
        struct { Vector angles; Vector rotation[3]; } tilt;
        Vector inverse[4];
    } workspace;
    Vector destination;
    u8 *effect=*(u8 **)(object+0x68);
    u8 *hit;
    int mode;
    switch(object[0x20]) {
    case 0:
        if(*(int *)(effect+0x40)) D_L02_001AEC78=D_L02_001AEC78-1;
        qcopy(effect,object+0x10);
        *(float *)(effect+0x10)=func_002A7940();
        *(float *)(effect+0x14)=func_002A7940();
        *(float *)(effect+0x18)=func_002A78D8(ref_L02_0043F4C8_1[0],ref_L02_0043F4C8_1[1])*0.0003490659f;
        *(float *)(effect+0x1C)=func_002A78D8(ref_L02_0043F4C8_2[0],ref_L02_0043F4C8_2[1])*0.0003490659f;
        *(int *)(effect+0x40)=0;
        *(float *)(effect+0x4C)=0.12566373f;
        object[0x40]=func_002A77E0((*(u8 **)(*(u8 **)(object+0x24)+0x48))[0x10]);
        *(short *)(effect+0x48)=180;
        mode=func_002A77E0(2)+1;
        if(object[0x43]!=mode) func_PAL_002A7E68(object,mode,0,5);
        func_002A7750(object,1,-1);
        break;
    case 1: {
        if(object[0x31]) {
            u8 *position=object+0x10;
            *(float *)(effect+0x10)=func_00283B98(*(float *)(effect+0x10),*(float *)(effect+0x18));
            *(float *)(effect+0x14)=func_00283B98(*(float *)(effect+0x14),*(float *)(effect+0x1C));
            *(float *)(object+0xF0)=ref_L02_0043F4C8_3*func_00283198(*(float *)(effect+0x10));
            *(float *)(object+0xF4)=ref_L02_0043F4C8_4*func_00283198(*(float *)(effect+0x14));
            workspace.tilt.angles.q=0;
            workspace.tilt.angles.f[0]=*(float *)(effect+0x10);
            workspace.tilt.angles.f[2]=*(float *)(effect+0x14);
            delta.q=workspace.tilt.angles.q;
            func_002833F0(workspace.tilt.rotation,&delta);
            func_00282D30(position,&workspace.tilt.rotation[1],ref_L02_0043F4C8_5);
            func_00282CC0(position,position,effect);
        }
        if(*(short *)(effect+0x3E)) {
            u8 *player=D_00189E20; if(*(u8 **)(player+0x33C)==object && *(int *)(player+0x340)) *(short *)(effect+0x3E)=2;
            if(*(short *)(effect+0x3E)==2) {
                *(float *)(effect+8)-=0.080000006f;
                if(*(int *)(effect+0x50) && func_L00_003206B8(object+0x10,*(int *)(effect+0x50))) func_002A7750(object,3,-1);
            }
        }
        if(*(int *)(effect+0x40)) break;
        hit=func_002A9640(object,0x4210000,0);
        if(!hit) break;
        {
        D_L02_001AEC78--;
        *(short *)(effect+0x4A)=((s32)(func_002A7820(30,60)) * 5 + 2) / 6;
        qcopy(effect+0x20,hit+0x10);
        func_00282F20(effect+0x20,effect+0x20,0.3f);
        func_00282CF0(&delta,hit,object+0x10);
        func_00283698(workspace.inverse,object+0xC0);
        func_002830C0(&delta,&delta,workspace.inverse);
        *(float *)(effect+0x30)=-(func_00282C68(delta.f[2],-1.0f,1.0f)*0.08377582f);
        *(float *)(effect+0x34)=func_00282C68(delta.f[1],-1.0f,1.0f)*0.062831864f;
        func_00282D30(&destination,effect+0x20,(float)*(short *)(effect+0x4A));
        func_00282CC0(&destination,object+0x10,&destination);
        if(func_002761F8(object+0x10,&destination,2,0,0)) *(short *)(effect+0x3C)=1;
        if(*(short *)(effect+0x3C)) func_002A7750(object,3,-1);
        else func_002A7750(object,2,-1);
        }
        break;
    }
    case 2:
        if(func_002B3868(object)) func_002E5CF8(0,0,object);
        delta.q=0; workspace.tilt.angles.q=0;
        delta.f[2]=0.080000006f;
        workspace.tilt.angles.f[2]=-0.5f;
        func_00282CC0(&workspace.tilt.angles,&workspace.tilt.angles,object+0x10);
        if(!func_002A77E0(2)) func_PAL_L01_002E2968(&workspace.tilt.angles,&delta,1,0x40F0F0F0,1,0.008f,0.9f,1.04f);
        *(float *)(object+0xF4)=func_00283B98(*(float *)(object+0xF4),*(float *)(effect+0x30));
        *(float *)(object+0xF8)=func_00283B98(*(float *)(object+0xF8),*(float *)(effect+0x34));
        func_00282CC0(object+0x10,object+0x10,effect+0x20);
        if(func_00282978((short *)(effect+0x4A))) func_002A7750(object,3,-1);
        break;
    case 3:
        if(*(short *)(effect+0x3C)) func_00282C88(effect+0x20);
        func_PAL_002AC718(object,D_L02_001A8F20,object+0x10,0.0f,0.0f,10,5,15,0.0f,0.0f,9.0f,*(float *)(object+0x2C)*10.0f,-1,0.0f,0,0,-1,0,0x810001);
        func_PAL_002B15D8((char *)object,0x3FFF,(float *)(effect+0x20),255,3.0f,6.0f,3.0f,6.0f);
        func_PAL_L00_003281C0(object,3,0.0f);
        func_002E5CF8(1,0,object);
        func_0029F338(object);
        return;
    }
    if(object[0x20]) func_PAL_L02_00445550(object);
}
