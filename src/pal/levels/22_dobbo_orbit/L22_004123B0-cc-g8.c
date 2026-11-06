/* func_PAL_L22_004123B0, the PAL copy of func_L22_0040D638: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; scale D_L22_001B119C. */
#include "common.h"
typedef union { unsigned int q __attribute__((mode(TI))); float f[4]; } Vec;
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002A77E0(int);
extern void func_002AFFD8(void *,void *,int);
#define U8(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define U16(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define S16(p,o) (*(short *)((char *)(p)+(o)))
#define I32(p,o) (*(int *)((char *)(p)+(o)))
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define PTR(p,o) (*(char **)((char *)(p)+(o)))
extern void func_002B60B0(void *,float,float,float,float);
extern void func_002A7750(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int func_00277258(void *,int,int,float);
extern void func_L22_003A3550(void *,int,float);
extern void func_L22_003A2988(void *,float);
extern float func_00282E48(void *,void *);
extern void func_PAL_002B1A50(void *,void *,int);
extern void func_L00_00325600(void *,void *,int);
extern char *D_L22_001AF314;
extern short D_L22_001B2A88;
extern int D_L22_001B2A8C, D_L22_001B2A90;
extern char D_L22_00189EA0[], D_L22_00189ED0[];
extern float D_L22_001AF308;
extern int D_L22_001B119C __attribute__((sda));
extern char *D_L22_001C00D8 __attribute__((section(".data")));
void func_PAL_L22_004123B0(char *obj) {
    Vec offset;
    int state = U8(obj,0x20);
    char *ctx = PTR(obj,0x68);
    if (state == 0) {
        U16(obj,0x32)=80; U8(obj,0x30)=255; U16(obj,0x34)|=0x100;
        U8(ctx,0x150)=5; I32(ctx,0x188)=3;
        FL(ctx,0x17c)=0.15f; FL(ctx,0x170)=0.5f; FL(ctx,0x174)=0.5f;
        if (S16(ctx,0x24)==0) { S16(ctx,0x24)=1; FL(ctx,0x20)=1.0f; }
        I32(ctx,0x88)|=5;
        FL(ctx,0x84)=0.5f; FL(ctx,0x54)=-7.0f; FL(ctx,0x50)=7.0f;
        FL(ctx,0x58)=0.4f; FL(ctx,0x5c)=0.4f;
        FL(ctx,0x60)=1.5707964897155762f;
        FL(ctx,0x80)=1.5533431768417358f;
        func_002B60B0(obj,0.0096f,0.24000001f,0.0025132746f,0.25132746f);
        I32(ctx,0x288)=0; I32(ctx,0x28c)=1; I32(obj,0x98)=0;
        U16(obj,0x34)=(U16(obj,0x34)|0x41)&0xefff;
        func_002A7750(obj,1,4);
    } else if (state == 1) {
        if (!D_L22_001AF314) goto finish;
        func_002A7750(obj,6,4);
        if (func_002A77E0(2)) {
            S16(ctx,0x178)=0;
            U16(obj,0x34)=(U16(obj,0x34)&0xffbe)|0x1000;
            I32(obj,0x98)=I32(PTR(obj,0x24),0x10);
            func_L22_003A3550(obj+0x10,1,7.2f);
            if (func_00277258(obj+0x10,1,0,3.0f) && S16(D_L22_001C00D8,0xaa)==0xedd && U8(D_L22_001C00D8,0x20)!=6) {
                char *axis=obj+0xc0+16*func_002A77E0(2);
                float scale;
                if (func_002A77E0(2)) scale=D_L22_001AF308;
                else scale=-D_L22_001AF308;
                func_00282D30(&offset,axis,scale);
                func_00282CC0(obj+0x10,obj+0x10,&offset);
                func_L22_003A2988(obj+0x10,7.2f);
            }
            qcopy(ctx+0x2a0,obj+0x10);
            I32(ctx,0x284)=0;
            func_002A7750(obj,2,0);
            if (U8(obj,0x43)!=1) func_PAL_002A7E68(obj,1,0,0);
        } else I32(ctx,0x284)=state;
    } else if (D_L22_001B2A88==2) {
        if ((U16(D_L22_001AF314,0x34)^1)&1) {
            float distance;
            if (state == 6) goto respawn;
            {
                distance=func_00282E48(D_L22_00189EA0,obj+0x10);
                if (U8(obj,0x20)!=6 && distance<55.0f) I32(ctx,0x288)=D_L22_001B2A88;
            }
            if (U8(obj,0x20)==6 || distance>55.0f) {
respawn:
                if (D_L22_001B2A8C<16 && !D_L22_001B2A90) {
                    D_L22_001B2A8C++;
                    S16(ctx,0x178)=0;
                    U16(obj,0x34)=(U16(obj,0x34)&0xffbe)|0x1000;
                    I32(obj,0x98)=I32(PTR(obj,0x24),0x10);
                    qcopy(obj+0x10,D_L22_00189ED0);
                    func_002A7750(obj,8,5);
                    D_L22_001B2A90=(((int)(D_L22_001B119C) * 5 + 2) / 6);
                    I32(ctx,0x288)=D_L22_001B2A88;
                }
            }
        }
    }
finish:
    if (U8(obj,0x20)!=6) {
        FL(obj,0x2c)=FL(PTR(obj,0x24),0x24)*0.4f;
        func_PAL_002B1A50(obj,ctx+0x140,0);
        func_002AFFD8(obj+0x10,ctx+0x290,0);
        func_L00_00325600(obj+0xc0,ctx+0x290,0);
    }
}
