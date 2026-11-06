/* func_PAL_003188D8, the PAL copy of func_003173B0: the same C, with the animation rates,
   the draw scale and the timers changed for 50 Hz. */
#include "common.h"

extern void func_002B60B0(void *, float, float, float, float);
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int), func_PAL_002A7E68(void *, int, int, int);
extern float func_00283B98(float angle, float step);
extern float func_00283198(float angle);
extern int func_00282948(void *timer);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282E80(void *, void *);
extern float func_002A89A8(void *, int, float);
extern int func_PAL_003192E0(char *);
extern int func_002B3890(char *);
extern int func_PAL_002B27B8(char *, char *);
extern void func_002E59F8(int);
extern void *func_PAL_0032DF28(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002A7650(void *, int, int);
extern void func_0029F338(void *);
extern void func_002A677C(void *);
extern int func_PAL_002B5BA8(void *, void *, float);
extern int func_002A8D70(void *, int, float, float, int, float, int, int, int);
extern void func_PAL_00319768(char *);
extern unsigned char D_00188660[];
extern unsigned char D_00189E20[];
typedef struct { char pad[0x249C]; char *target; } Hero3173;
extern char *D_001F1700[];
#define FI(p,o) (*(int *)((p)+(o)))
#define FF(p,o) (*(float *)((p)+(o)))
#define FH(p,o) (*(short *)((p)+(o)))
#define FU(p,o) (*(unsigned short *)((p)+(o)))
#define FB(p,o) (*(unsigned char *)((p)+(o)))
#define FP(p,o) (*(char **)((p)+(o)))
/* Keeps state 6's transition from cross-jumping into state 10's identical call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeMode3173Six(void *, int, int) __asm__("func_002A7750");
void func_PAL_003188D8(char *self)
{
    char *d = FP(self,0x68);
    int flags, n, i;
    char *sound, *path;
    float target[4], delta[4];
    float f, height, savedHeight;
    /* Written out here and at the end of state 3, not shared through a label: cross-jumping
       merges the two after sched1, which has to see func_0029F338 in the same block as the
       explosion's calls for it to set a3..t3 up before a0..a2. */
    if (func_PAL_003192E0(self)) {
        func_0029F338(self);
        return;
    }
    switch (FB(self,0x95)) {
    case 0:
        if (func_002B3890(self))
            func_002B60B0(self,0.0096f,0.080000006f,1.0053098f,1.0053098f);
        if (FI(d,0x258)==1 && func_00282948(d+0x2A4) && FI(d,0x2AC)) {
            if (FI(d,0x294)==-1) {
                func_002A7750(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) func_PAL_002A7E68(self,2,0,4);
            } else func_002A7750(self,4,2);
        } else if (FH(d,0x276)) {
            func_002A7750(self,3,1);
            FH(d,0x276)=0;
            if (FH(d,0x270)<250) FH(d,0x270)=(((int)(func_002A7820(480,600)) * 5 + 2) / 6);
        }
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 1:
        if (func_002B3890(self))
            func_002B60B0(self,0.0096f,0.080000006f,1.0053098f,1.0053098f);
        if ((FI(d,0x258)==1 || FI(d,0x25C)==1) && FI(d,0x2AC)) {
            if (FI(d,0x294)!=-1) func_002A7750(self,4,2);
            else {
                func_002A7750(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) func_PAL_002A7E68(self,2,0,4);
            }
        }
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 2:
        if (func_002B3890(self))
            func_002B60B0(self,0.0096f,0.080000006f,1.0053098f,1.0053098f);
        if (FI(d,0x258)!=1 && FI(d,0x25C)!=1 && FB(self,0x20)!=4) {
            func_002A7750(self,1,1);
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,17);
            FH(d,0x270)=(((int)(func_002A7820(580,600)) * 5 + 2) / 6);
        }
        break;
    case 3:
        flags=func_PAL_002B27B8(self,d+0x60);
        if (flags&1) {
            n=FI(d,0x2A8);
            if (n!=-1) {
                sound=(char *)D_00188660+n*0x70;
                if (FP(sound,0x88)==self && FB(sound,0x74)) func_002E59F8(n);
            }
            FI(d,0x2A8)=-1;
            func_PAL_0032DF28(self+0x10,0,0,0,0,20,45,1,0.3f,20.0f,1,0,0,0);
            func_002E5CF8(0,0,self);
            func_PAL_002A7650(self,0,3);
            func_0029F338(self);
            return;
        }
        if (flags&2) {
            if (FI(d,0x258)==1 || FI(d,0x25C)==1) {
                func_002A7750(self,5,2);
                if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,4);
                if (FI(d,0x294)!=-1) func_002A7750(self,4,2);
            } else {
                func_002A7750(self,3,1);
                FH(d,0x270)=(((int)(func_002A7820(580,600)) * 5 + 2) / 6);
            }
        }
        break;
    }
    switch (FB(self,0x20)) {
    case 1:
        if (FU(self,0x96)>=26) {
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,4);
            func_002A7750(self,2,-1);
            FF(self,0x18)=FF(d,0x28C);
        } else {
            f=func_00283198((float)FU(self,0x96)*0.14842157f)*0.02f;
            if (FF(self,0x18)>FF(d,0x28C)) FF(self,0x18)-=f;
            else FF(self,0x18)+=f;
        }
        break;
    case 4:
        path=D_001F1700[FI(d,0x294)];
        if (FI(d,0x298)>=FI(path,0)) {
            FI(d,0x294)=-1;
            FF(d,0x28C)=func_002A89A8(self+0x10,0,0.5f)+0.5f;
            func_002A7750(self,5,-1);
        } else {
            qcopy(target,path+0x10+FI(d,0x298)*16);
            func_00282CF0(delta,target,self+0x10);
            func_00282F20(delta,delta,FF(d,0x1C0));
            func_00282CC0(self+0x10,self+0x10,delta);
            if (func_00282E80(self+0x10,target)<0.5f) FI(d,0x298)++;
            if (FI(d,0x298)>=FI(path,0)-6 && FF(d,0x1C0)>=0.120000005f)
                FF(d,0x1C0)-=0.0032000002f;
            height=func_002A89A8(self+0x10,0,0.5f)+0.5f;
            if (FF(self,0x18)<height) FF(self,0x18)=height;
            FF(d,0x28C)=FF(self,0x18);
            func_002A677C(self);
        }
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 5:
        savedHeight=FF(self,0x18);
        func_PAL_002B5BA8(self,d+0x230,FF(d,0x290));
        FF(self,0x18)=savedHeight;
        if (func_00282E80(self+0x10,FP(d,0x240)+0x10)<1.3f) func_002A7750(self,7,-1);
        FF(self,0xF8)=func_00283B98(FF(self,0xF8),0.03490659f);
        break;
    case 6:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)!=3) func_PAL_002A7E68(self,3,0,4);
            changeMode3173Six(self,8,-1);
        }
        break;
    case 8:
        height=1.75f;
        FF(self,0x48)=height;
        for (i=0;i<4;i++) func_002A8D70(self,i,0.17f,FF(d,0x2B0),1,1.0f,0,1,0);
        if (((Hero3173 *)D_00189E20)->target==self) func_002A7750(self,9,-1);
        if (func_00282E80(self+0x10,FP(d,0x240)+0x10)>1.3f && (float)FU(self,0x96)>120.0f) {
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,12);
            func_002A7750(self,5,-1);
            FF(self,0x48)=1.0f;
        }
        break;
    case 9:
        if ((float)FU(self,0x96)>20.0f) {
            func_002A7750(self,10,-1);
            if (FB(self,0x43)!=4) func_PAL_002A7E68(self,4,0,4);
            FF(self,0x48)=1.0f;
        }
        break;
    case 10:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)) func_PAL_002A7E68(self,0,0,12);
            func_002A7750(self,5,-1);
        }
        break;
    case 7:
        if (FU(self,0x96)>=30) {
            func_002A7750(self,6,-1);
            if (FB(self,0x43)!=1) func_PAL_002A7E68(self,1,0,2);
            FF(self,0x48)=1.0f;
        }
        break;
    }
    if (FB(self,0x20)!=4 && FB(self,0x95)==2 && FF(self,0x18)<FF(d,0x28C)) FF(self,0x18)=FF(d,0x28C);
    func_PAL_00319768(self);
}
