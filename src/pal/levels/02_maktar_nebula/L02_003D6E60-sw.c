#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { u8 prefix[0x2C0]; float waypoint[4]; float previousPosition[4]; } WaypointView;
typedef struct {
    u8 reserved_00[0x18]; u8 enabled, count, kind; u8 reserved_1b[0x65]; u8 payload[1];
} DispatchContext;
typedef unsigned long DispatchFlags;
typedef struct { u8 prefix[0x160]; float amount; int reserved164; int kind; int detail; } EffectTuning;
extern EffectTuning D_L02_001BA3C0;
#define EFFECT (&D_L02_001BA3C0)
extern float D_L02_001B3F58 __attribute__((sda));
extern float D_L02_001B01B0[4];
extern float arenaPosition[4] SDATA(D_L02_001B01B0);
extern float D_L02_001B01C0[4] __attribute__((sda));
extern float D_L02_001B01D0[4] __attribute__((sda));
extern int D_L02_001B01E0 __attribute__((sda));
extern int D_L02_001A903C;
extern unsigned char D_001A7A60[] MACRO_ADDR;
typedef struct { u8 prefix[0x80]; float position[4]; u8 reserved90[0x240C]; char *lockTarget; } HeroPositionView;
extern HeroPositionView D_00189E20;
extern void func_PAL_L02_003D8388(char *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283248(float, float);
extern float func_0029F530(char *);
extern int func_002B3890(u8 *);
extern int func_002B3868(u8 *);
extern void func_002B60B0(u8 *, float, float, float, float);
extern void func_L02_003D5B90(char *);
extern int func_L00_0042AB40(char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void func_002A7750(u8 *, s32, s32);
extern void func_PAL_L02_003D8F90(char *);
extern void func_PAL_L02_003D9090(char *, Quadword *, float, float);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void func_L02_003D4A48(char *);
extern void func_L02_003DB880(char *);
extern void func_L02_003FC020(char *, char *);
extern int func_PAL_002B5E10(char *);
extern void func_PAL_L02_003D8B70(char *, int);
extern float func_L02_002F21C0(void *, void *);
extern int func_PAL_L01_00323068(char *, char *);
extern float func_00283C80(float, float);
extern void func_L02_003D69F0(char *);
extern void func_L02_003D5118(char *, int);
extern void func_PAL_L02_003DA778(char *, int);
extern int func_PAL_L02_003D8D80(char *);
extern int func_L02_003D4A60(char *);
extern DispatchFlags func_002B1C20(void *, DispatchContext *);
extern void func_PAL_L02_004009A0(void *, int, int);
extern int func_002E5E58(int, int, void *);
extern void func_PAL_002B1588(int, int);
extern void func_L01_003E9CF8(char *, int, void (*)(char *));
extern void func_L02_003D4900(char *);
extern void func_PAL_002B5E30(u8 *, float);
extern void func_L02_003D4E00(char *);
extern int func_00282978(short *);
extern int func_PAL_L02_003D8E08(char *);
extern int func_PAL_L02_003D9368(char *);
extern void func_00282C88(Quadword *);
extern void func_L02_003D5660(char *, int);
extern int func_PAL_L02_003D9808(char *, int);
extern void func_PAL_L02_003D8738(char *);
#define B(o) (*(u8 *)(state+(o)))
#define H(o) (*(short *)(state+(o)))
#define W(o) (*(int *)(state+(o)))
#define F(o) (*(float *)(state+(o)))
#define P(o) (*(char **)(state+(o)))
#define SET_MODE(m,r) func_002A7750((u8 *)self,(m),(r))

/* Drive the large Maktar sentry's locomotion and paired throw sequences. */
void func_PAL_L02_003D6E60(char *self)
{
    char *state=*(char **)(self+0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float distance, yaw, frame, value, scale;
    int result;
    DispatchFlags events, animFlags;
    unsigned char flags;

    D_L02_001B3F58=0.7853981633974483f;
    func_PAL_L02_003D8388(self);
    qcopy(target, P(0x30C)+0x10);
    distance=func_00282E80(self+0x10,target);
    yaw=func_00283248(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14));
    frame=func_0029F530(self);
    flags=*(u8 *)(self+0x95);
    switch (flags) {
    case 1:
        if (func_002B3890((u8 *)self)) {
            B(0xD6)=0; B(0x70)=8; W(0xA8)=3; W(0x148)&=~4; F(0x30)=3.0f;
            func_002B60B0((u8 *)self,0.0064000003f,0.16000001f,0.012147494f,0.25132746f);
            func_L02_003D5B90(self); W(0x14C)=func_L00_0042AB40(*(char **)(self+0xB8));
        }
    break;
    case 2:
        if (func_002B3890((u8 *)self)) {
            B(0x70)=18; W(0xA8)=4; B(0xD6)=1; W(0x148)|=4;
            F(0x30)=5.0f; W(0x14C)=-1;
        }
        if (*(float *)(self+0x18)<D_L02_001B01B0[2]-1.0f)
            *(float *)(self+0x18)=D_L02_001B01B0[2]-1.0f;
    break;
    case 3:
    case 4:
        if (func_002B3890((u8 *)self)) func_L02_003D5B90(self);
    }
    switch (*(u8 *)(self+0x20)) {
    case 1: return;
    case 2:
        if (func_002B3868((u8 *)self)) {
            D_L02_001B01E0=1; *(unsigned short *)(self+0x96)=0;
            if (*(u8 *)(self+0x43)) func_PAL_002A7E68(self,0,0,8);
        }
        if (*(unsigned short *)(self+0x96)>120) {
            if (*(u8 *)(self+0x42)!=9) {
                if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
                *(u8 *)(self+0x95)=2; qcopy(state+0x2D0, self+0x10);
                qcopy(((WaypointView *)state)->waypoint, D_L02_001B01D0);
            } else {
                func_PAL_L02_003D8F90(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
                func_PAL_L02_003D9090(self,(Quadword *)position,
                    func_00283248(target[0]-*(float *)(self+0x10),target[1]-*(float *)(self+0x14)),0.0f);
            }
        }
        if (func_00282E80(self+0x10,arenaPosition)<18.0f) { H(0x32E)=0; SET_MODE(20,2); }
        break;
    case 3:
        if (func_002B3868((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
            qcopy(state+0x2D0, self+0x10);
            value=func_002A7878(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (func_002A77E0(2)) value=-value;
            F(0x308)=value; qcopy(((WaypointView *)state)->waypoint, D_L02_001B01C0);
            func_L02_003D4A48(self); func_L02_003DB880(P(0x310));
            func_L02_003FC020(*(char **)(self+0xB8),P(0x310));
        }
        func_PAL_L02_003D8F90(self); *(Quadword *)position=*(Quadword *)(state+0x2D0);
        func_PAL_L02_003D9090(self,(Quadword *)position,
            func_00283248(D_00189E20.position[0]-*(float *)(self+0x10),D_00189E20.position[1]-*(float *)(self+0x14)),0.0f);
        if (func_00282E48(self+0x10,((WaypointView *)state)->waypoint)<0.5f) SET_MODE(4,1);
        break;
    case 4:
        if (func_002B3868((u8 *)self) && *(u8 *)(self+0x43)) func_PAL_002A7E68(self,0,0,12);
        func_PAL_002B5E10(self);
        if (H(0x318)) SET_MODE(2,1);
        break;
    case 6:
        if (func_002B3868((u8 *)self) && *(u8 *)(self+0x43)!=1) func_PAL_002A7E68(self,1,0,8);
        if (!func_002A77E0(400)) func_PAL_L02_003D8B70(self,-1);
        if (func_L02_002F21C0(target,arenaPosition)<529.0f)
            func_PAL_L01_00323068(self,(char *)target);
        else func_PAL_L02_003D8B70(self,1);
        if ((*(u8 *)(self+0x42)==1 && frame>1.0f && frame<3.0f) || (frame>16.0f && frame<18.0f)) {
            EFFECT->amount=0.05f; EFFECT->kind=21; EFFECT->detail=0;
        }
        if (distance<9.0f && func_00283C80(yaw,*(float *)(self+0xF8))<0.087266475f
                && frame>3.0f && frame<15.0f) SET_MODE(7,1);
        break;
    case 7:
        if (func_002B3868((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=2) func_PAL_002A7E68(self,2,0,8);
            func_L02_003D69F0(self); *(u8 *)(self+0xBC)=0;
        }
        if (*(u8 *)(self+0x42)==2 && frame>19.0f && frame<23.0f) {
            func_L02_003D5118(self,0); func_PAL_L02_003DA778(self,0);
        } else if (*(u8 *)(self+0xBC)==0 && *(u8 *)(self+0x42)==2 && frame>23.0f) {
            func_L02_003D69F0(self); *(u8 *)(self+0xBC)=1;
        } else if (*(u8 *)(self+0x42)==2 && frame>32.0f && frame<36.0f) {
            func_L02_003D5118(self,1); func_PAL_L02_003DA778(self,1);
        } else if (*(u8 *)(self+0xBC)==1 && *(u8 *)(self+0x42)==2 && frame>36.0f) {
            func_L02_003D69F0(self); *(u8 *)(self+0xBC)=2;
        }
        if (*(u8 *)(self+0x60)&2) {
            if (func_PAL_L02_003D8D80(self) || func_L02_003D4A60(self)) SET_MODE(19,1); else SET_MODE(6,1);
            if (!func_002A77E0(3) || D_00189E20.lockTarget==self)
                func_PAL_L02_003D8B70(self,D_00189E20.lockTarget==self ? 0 : -1);
        }
        break;
    case 8:
        qcopy(position,self+0x10);
        if (F(0x20)>0.0f) {
            events=func_002B1C20(self,(void *)(state+0x60));
            if ((events&2)==2) if (func_PAL_L02_003D8D80(self) || func_L02_003D4A60(self)) SET_MODE(19,1); else SET_MODE(6,1);
        } else if (frame>95.0f && frame<97.0f) {
            EFFECT->amount=0.4f; EFFECT->kind=21; EFFECT->detail=0;
        } else if (frame>110.0f) SET_MODE(9,-1);
        if (func_00282E80(self+0x10,arenaPosition)>18.0f)
            qcopy(self+0x10, position);
        break;
    case 9:
        if (func_002B3868((u8 *)self)) {
            *(int *)(self+0x48)=0; *(short *)(self+0x96)=0;
            func_PAL_L02_004009A0(self,0,-1); *(int *)(self+0x98)=*(int *)(*(char **)(self+0x24)+0x10);
        }
        if (*(unsigned short *)(self+0x96)>50) {
            int storyActive = D_L02_001B01E0;
            *(float *)(self+0x48)=1.0f;
            if (storyActive && !D_001A7A60[1]) {
                D_001A7A60[1]=1; func_002E5E58(1,0,0); func_PAL_002B1588(0x1233,-1); D_L02_001A903C=1;
            }
            func_L01_003E9CF8(self,0,func_L02_003D4900);
            if (P(0x310) && (u8)P(0x310)[0x20]!=254 && (u8)P(0x310)[0x20]!=253 && (u8)P(0x310)[0x20]>2) {
                func_L02_003DB880(P(0x310)); func_L02_003FC020(*(char **)(self+0xB8),P(0x310));
            }
        }
        break;
    case 10:
        if (*(u8 *)(self+0x95)==2) {
            *(Quadword *)position=*(Quadword *)((WaypointView *)state)->waypoint;
            func_PAL_L02_003D9090(self,(Quadword *)position,yaw,0.0f);
        } else func_PAL_002B5E30((u8 *)self,*(float *)(self+0xF8));
        if (*(u8 *)(self+0x60)&2) { SET_MODE(H(0x324),H(0x326)); *(int *)(self+0x48)=0; }
        break;
    case 11:
        if (func_002B3868((u8 *)self)) {
            if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
            H(0x31C)=0; qcopy(state+0x2D0, self+0x10);
            value=func_002A7878(20.0f,40.0f);
            scale=0.017453294f;
            value*=scale;
            if (func_002A77E0(2)) value=-value;
            F(0x308)=value;
        }
        func_L02_003D4E00(self); func_PAL_L02_003D8F90(self);
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        func_PAL_L02_003D9090(self,(Quadword *)position,yaw,0.0f);
        if (!func_002A77E0(400)) func_PAL_L02_003D8B70(self,0);
        if (distance<40.0f && distance>5.0f && func_00282978((short *)(state+0x31C))) {
            if (func_002A77E0(2)) {
                SET_MODE(12,2);
                if (!func_002A77E0(6)) func_PAL_L02_003D8B70(self,0);
            } else {
                SET_MODE(15,2);
                if (!func_002A77E0(6)) func_PAL_L02_003D8B70(self,0);
            }
        }
        if (func_PAL_L02_003D8E08(self)) SET_MODE(20,2);
        if (func_L02_003D4A60(self)) SET_MODE(3,2);
        break;
    case 12:
        if (func_002B3868((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=func_PAL_L02_003D9368(self);
            switch (result) {
            case 0: func_L02_003D5B90(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=10 && *(u8 *)(self+0x43)!=10) func_PAL_002A7E68(self,10,0,6);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            func_PAL_L02_003D9090(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==10 && frame>19.0f) {
            func_00282C88((Quadword *)(state+0x1B0)); func_L02_003D5660(self,0); H(0x328)=1;
        }
        if (H(0x328)) {
            result=func_PAL_L02_003D9808(self,0);
            switch (result) {
            case 1: SET_MODE(14,2); break;
            case 2: func_L02_003D5B90(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==10 && frame>27.0f) SET_MODE(13,2);
        break;
    case 13:
        if (func_002B3868((u8 *)self) && *(u8 *)(self+0x43)!=11) func_PAL_002A7E68(self,11,0,6);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        func_PAL_L02_003D9090(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && func_PAL_L02_003D9808(self,0)==2) {
            SET_MODE(14,2); func_L02_003D5B90(self); H(0x328)=0;
        }
        break;
    case 14:
        if (func_002B3868((u8 *)self) && *(u8 *)(self+0x43)!=12) func_PAL_002A7E68(self,12,0,6);
        if (H(0x328) && func_PAL_L02_003D9808(self,0)==2) { func_L02_003D5B90(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        func_PAL_L02_003D9090(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==12 && frame>6.0f) { func_L02_003D5B90(self); SET_MODE(11,2); }
        break;
    case 15:
        if (func_002B3868((u8 *)self)) H(0x328)=0;
        if (!H(0x328)) {
            result=func_PAL_L02_003D9368(self);
            switch (result) {
            case 0: func_L02_003D5B90(self); SET_MODE(11,-1); break;
            case 2:
                if (*(u8 *)(self+0x42)!=13 && *(u8 *)(self+0x43)!=13) func_PAL_002A7E68(self,13,0,6);
                break;
            }
        } else {
            *(Quadword *)position=*(Quadword *)(self+0x10);
            func_PAL_L02_003D9090(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        }
        if (!H(0x328) && *(u8 *)(self+0x42)==13 && frame>19.0f) {
            func_00282C88((Quadword *)(state+0x1B0)); func_L02_003D5660(self,1); H(0x328)=1;
        }
        if (H(0x328)) {
            result=func_PAL_L02_003D9808(self,1);
            switch (result) {
            case 1: SET_MODE(17,2); break;
            case 2: func_L02_003D5B90(self); H(0x328)=0; break;
            }
        }
        if (H(0x328)==1 && *(u8 *)(self+0x42)==13 && frame>27.0f) SET_MODE(16,2);
        break;
    case 16:
        if (func_002B3868((u8 *)self) && *(u8 *)(self+0x43)!=14) func_PAL_002A7E68(self,14,0,6);
        *(Quadword *)position=*(Quadword *)(self+0x10);
        func_PAL_L02_003D9090(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (H(0x328) && func_PAL_L02_003D9808(self,1)==2) { SET_MODE(17,2); func_L02_003D5B90(self); H(0x328)=0; }
        break;
    case 17:
        if (func_002B3868((u8 *)self) && *(u8 *)(self+0x43)!=15) func_PAL_002A7E68(self,15,0,6);
        if (H(0x328) && func_PAL_L02_003D9808(self,1)==2) { func_L02_003D5B90(self); H(0x328)=0; }
        *(Quadword *)position=*(Quadword *)(self+0x10);
        func_PAL_L02_003D9090(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        if (!H(0x328) && *(u8 *)(self+0x42)==15 && frame>6.0f) { func_L02_003D5B90(self); SET_MODE(11,2); }
        break;
    case 18:
        *(Quadword *)position=*(Quadword *)(state+0x2D0);
        func_PAL_L02_003D9090(self,(Quadword *)position,*(float *)(self+0xF8),0.0f);
        events=func_002B1C20(self,(void *)(state+0x60));
        if ((events&1)==1) { SET_MODE(20,2); H(0x32C)=1; break; }
        animFlags=events&2;
        goto modeEleven;
    case 19:
        if (func_002B3868((u8 *)self) && *(u8 *)(self+0x43)!=17) func_PAL_002A7E68(self,17,0,8);
        { float animationFrame=func_0029F530(self);
        if (*(u8 *)(self+0x42)==17 && animationFrame>9.0f) { *(u8 *)(self+0x95)=2; *(u8 *)(self+0xBE)&=~2; }
        animFlags=*(u8 *)(self+0x60)&2;
        }
    modeEleven:
        if (animFlags) SET_MODE(11,2);
        break;
    case 20:
        if (func_002B3868((u8 *)self)) {
            W(0x148)&=~4;
            if (*(u8 *)(self+0x43)!=9) func_PAL_002A7E68(self,9,0,8);
            func_L02_003D5B90(self);
        }
        if (*(float *)(self+0x18)<D_L02_001B01B0[2]+1.0f && *(float *)(self+0x18)>D_L02_001B01B0[2]) {
            if (*(u8 *)(self+0x42)!=18 && *(u8 *)(self+0x43)!=18) func_PAL_002A7E68(self,18,0,8);
            func_PAL_002B5E30((u8 *)self,yaw);
        } else {
            qcopy_nc(position,self+0x10); position[2]=D_L02_001B01B0[2];
            func_PAL_L02_003D9090(self,(Quadword *)position,yaw,0.0f);
        }
        if (*(u8 *)(self+0x42)==18 && (H(0x1D0)!=0 || *(float *)(self+0x18)<D_L02_001B01B0[2]+0.2f)) {
            if (H(0x32C)) { func_PAL_002A7E68(self,4,0,2); B(0x7A)=0; SET_MODE(8,3); }
            else SET_MODE(6,1);
            if (*(u8 *)(self+0x42)==18 && frame>8.0f && frame<10.0f) {
                EFFECT->amount=0.2f; EFFECT->kind=21; EFFECT->detail=0;
            }
        }
        break;
    }
    func_PAL_L02_003D8738(self);
}
