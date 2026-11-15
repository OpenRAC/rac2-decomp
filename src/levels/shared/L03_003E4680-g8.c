#include "common.h"
typedef struct MuseumPlayer {
    char pad00[0x40];
    float matrix40[16];
    float position[4];
    char pad90[8];
    float rotation[4];
    char padA8[0x58];
    float velocity[4];
    char pad110[0x112];
    short mode;
    char pad224[0x118];
    char *focus;
    char pad340[0x8E8];
    int flags;
    char padC2C[0x61C];
    int saved;
    char pad124C[0x1044];
    char *animation;
    int animationId;
    char pad2298[0x30];
    int action;
} MuseumPlayer;
extern MuseumPlayer D_00189E20;
typedef struct MuseumInput {
    char pad[0x1A0];
    union { unsigned long long mask; struct { unsigned low, high; } words; } buttons;
} MuseumInput;
extern MuseumInput D_00138180;
typedef struct MuseumGameState { char pad[0x33]; unsigned char mode; } MuseumGameState;
extern MuseumGameState D_00139568;
extern unsigned char D_0019B4A8[];
extern int D_001A79F0 MACRO_ADDR;
extern unsigned char D_001A7B2B;
typedef struct MuseumCompletion { char pad[0x464]; unsigned char complete[0]; } MuseumCompletion;
extern char D_L03_0021EA30[];
typedef struct MuseumSound { char pad[0x14]; int handle; char rest[0xC8]; } MuseumSound;
extern char D_L03_00266DA0[];
extern int D_L03_001B2940;
extern char *D_L03_001B2A1C;
extern char D_L03_001B0C70_gp[] SDATA(D_L03_001B0C70), D_L03_001B0C80_gp[] SDATA(D_L03_001B0C80), D_L03_001B0C90_gp[] SDATA(D_L03_001B0C90);
extern char D_L03_001B9980[], D_L03_001B9BB0[];
extern float D_L03_001B9C14 NOT_SDA, D_L03_001B2464 MACRO_ADDR;
extern int D_L03_001A8F00;
extern int D_L03_001B0B50 MACRO_ADDR, D_L03_001B0B58 MACRO_ADDR, D_L03_001B0B5C MACRO_ADDR, D_L03_001B0B60 MACRO_ADDR;
extern int D_L03_0029BCD0[][4];
extern void func_002A7750(char *,int,int), func_L00_003294F0(char *,int);
extern int func_002B3868(char *);
extern void func_L03_003E5070(char *),func_L03_003E50E0(char *),func_L03_003E5170(char *);
extern int func_002B0CE0(int,int,int);
extern int func_00294630(int);
extern void func_00294420(int),func_L00_002C8BA8(int);
extern int func_L03_002C6F08(int,int);
extern void func_00283098(void *,void *,void *),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern float func_00283B98(float,float),func_00283248(float,float),func_00282E80(void *,void *);
extern void func_L00_002D40A0(void *,int,float);
extern int func_L00_002D40F0(void);
extern void func_L00_002D2168(int,int,float),func_0026FF08(int,int,float,float,float,float);
extern void func_00335438(void *,void *,int,int,int),func_00335370(void *),func_003353C8(void *);
extern void func_002AC9F8(void *,float),func_002AA800(void *,int,float,float);
extern float func_002AA2E8(float *,float,float);
extern int func_002B49E0(int,int,char *,int,int);
extern void func_00283360(void *),func_00282C88(void *),func_002833F0(void *,void *),func_L00_0042A500(int);
extern int func_002E5CF8(int,int,char *);
extern void func_L01_00323310(int,int);
extern void func_00335370(void *),func_003353C8(void *),func_00335438(void *,void *,int,int,int);
typedef struct { char pad[0x3C]; short a; char p3e[10]; short b; } MenuState;
extern MenuState D_001A63A8;
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
static __inline__ unsigned int AdvanceMuseumTimer(char *obj) {
    unsigned int value = U(obj,0x96);
    unsigned int old = value++;
    U(obj,0x96) = value;
    return old;
}
typedef struct MuseumDisplayVars { char pad[0x6C]; unsigned short settings; } MuseumDisplayVars;
typedef struct MuseumDisplay { char pad[0x68]; MuseumDisplayVars *vars; } MuseumDisplay;
typedef struct MuseumExhibit {
    int childIds[2];
    int cleanupId;
    int trackIds[14];
    unsigned short settings;
    char pad46[2];
    int duration, limit;
    int music, volume;
    MuseumDisplay *display;
    char *pad5C;
    int completed, saved;
    int pad68;
    float fade;
    int resume;
} MuseumExhibit;
/* Runs the Infiltrator lock (moby class 2857): waits for the player to press the button, plays the camera move, starts the puzzle and marks the lock as opened when it is solved. */
void func_L03_003E4680(char *obj) {
    MuseumExhibit *lockVars = (MuseumExhibit *)P(obj,0x68);
    float vec[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    switch (B(obj,0x20)) {
    case 0: {
        int j, state;
        unsigned short id = U(obj,0xB2);
        char *displayMoby;
        if (((MuseumCompletion *)D_L03_0021EA30)->complete[(short)id]
            || (state = D_0019B4A8[((short)id>>1)+(gCurrentMapIndex<<10)], (id & 1) ? (state>>4)&7 : state&7)) {
            SetMobyState(obj,8,-1);
            SetObjectFlagBit(obj,1);
            for (j=0;j<2;j++) if (lockVars->childIds[j]!=-1) SetObjectFlagBit(D_L03_001B2A1C+(lockVars->childIds[j]<<8),1);
        } else {
            SetMobyState(obj,1,-1);
            SpawnInfiltratorBallForMoby(obj);
            displayMoby=(char *)lockVars->display;
            qcopy(displayMoby+0x10,obj+0x10);
            F(displayMoby,0x18)+=1.0f;
            U(lockVars->display,0x34)|=1;
            B(lockVars->display,0x31)=0;
        }
        break;
    }
    case 1:
        if (gHeroState.focus!=obj || D_L03_001B2940<16 || !D_001A7B2B) break;
        ForceClaimNotice(12,0x27F0,1);
        if (!IsClassCached(((MuseumSound *)D_L03_00266DA0)[gItemSlotToRecord.mode].handle)) {
            LoadClassIntoFreeCacheSlot(((MuseumSound *)D_L03_00266DA0)[gItemSlotToRecord.mode].handle);
            break;
        }
        if (gPadState.buttons.words.high&0x10) {
            lockVars->saved=gHeroState.saved;
            gHeroState.action=0x33;
            SetMobyState(obj,2,-1);
        }
        break;
    case 2: {
        unsigned int cameraState;
        if (SetFirstPendingFlag(obj)) {
            matrix_mul_vec3(vec,D_L03_001B0C70_gp,obj+0xC0);
            FastVecAdd(vec,vec,obj+0x10);
            StartHeroTargetState(vec,0,FastAddRotations(F(obj,0xF8),3.1415927f));
        }
        cameraState=GetHeroTargetStateKind();
        if (cameraState==2) SetMobyState(obj,3,-1);
        else if ((AdvanceMuseumTimer(obj)>=301)) {ResetGadgetState(obj);StartHeroLoaderState(0);SetMobyState(obj,1,-1);}
        else if (!cameraState) {ResetGadgetState(obj);SetMobyState(obj,1,-1);}
        break;
    }
    case 3:
        if (SetFirstPendingFlag(obj)) {
            PlayMobySound(0,0,obj);
            EnterHeroState_L03(0x6F,0);set_hero_animation(0x54,0,20.0f);
            FastVecSub(vec,D_L03_001B9980,gHeroState.position);
            matrix_mul_vec3(vec,vec,gHeroState.matrix40);
            SetCamera5Pose(D_L03_001B9980,D_L03_001B9980,3,120,0);
            lockVars->fade=0;
        }
        matrix_mul_vec3(vec,D_L03_001B0C70_gp,obj+0xC0);
        FastVecAdd(vec,vec,obj+0x10);
        FastVecSub(gHeroState.velocity,vec,gHeroState.position);
        gHeroState.velocity[2]=0;
        ClampVectorLength(gHeroState.velocity,0.012500001f);
        StepAngleTowardTarget(gHeroState.rotation,0,FastAddRotations(F(obj,0xF8),3.1415927f),0.017453296f);
        gHeroState.mode=3;
        if ((gHeroState.flags&2) && B(gHeroState.animation,0x43)==0x54) set_hero_animation(0x55,0,7.0f);
        if (gHeroState.animationId!=0x6F) {ResetGadgetState(obj);SetMobyState(obj,1,-1);}
        matrix_mul_vec3(pos,D_L03_001B0C80_gp,&gHeroState);
        FastVecAdd(pos,pos,gHeroState.position);
        qzero_nc(rot);
        matrix_mul_vec3(target,D_L03_001B0C90_gp,&gHeroState);
        FastVecAdd(target,target,gHeroState.position);
        rot[2]=FastMatrixHelperA(target[0]-pos[0],target[1]-pos[1]);
        rot[1]=-FastMatrixHelperA(vec_distance_xy(pos,target),target[2]-pos[2]);
        CopyVectorToSelectedObject(pos);SetCameraStateRotation(rot);
        if ((AdvanceMuseumTimer(obj)>=61)) {
            SetMobyState(obj,4,-1);
            lockVars->resume=gMusicState.a==-1?gMusicState.b:gMusicState.a;
            QueueKeyedRequest(lockVars->music,lockVars->volume);
        }
        break;
    case 4: {
        unsigned int elapsed;
        if (SetFirstPendingFlag(obj)) {
            PlayMobySound(0,0,obj);
            D_L03_001B9C14=0.017453294f;
            SetCameraValueTarget(30,1,0.017453294f,0.005f,0.2f,0.0f);
        }
        gHeroState.mode=3;
        if (gHeroState.animationId!=0x6F) {ResetGadgetState(obj);SetMobyState(obj,1,-1);break;}
        if ((AdvanceMuseumTimer(obj)<21)) break;
        ApproachValue(&lockVars->fade,1.0f,0.116666675f);
        elapsed=U(obj,0x96);
        D_L03_001B2464=lockVars->fade;
        if (elapsed<31) break;
        D_L03_001B9C14=1.1243411f;
        SetCameraValueTarget(1,0,1.1243411f,0.005f,0.2f,0.0f);
        if (!BeginSlotRequest(7,1,obj,0,0)) SetMobyState(obj,5,-1);
        break;
    }
    case 5:
        if (D_L03_001A8F00==7) {
            int i;
            qzero_nc(D_L03_001B9980);
            SpawnInfiltratorBallForMoby(obj);
            D_L03_001B0B50=0;
            /* Pointer arithmetic, not trackIds[i]: an array field of a BLKmode struct would form lockVars+0xC in its own
             * register ahead of the loop's duplicated exit test. The scalar globals leave the loop through load_mems. */
            for (i=0;i<14&&*(lockVars->trackIds+i)>=0;i++) {
                D_L03_0029BCD0[i][0]=*(lockVars->trackIds+i);
                D_L03_001B0B50++;
                D_L03_001B0B5C=lockVars->duration;
                D_L03_001B0B58=lockVars->duration+120;
                D_L03_001B0B60=lockVars->limit;
                lockVars->display->vars->settings=lockVars->settings;
            }
            U(lockVars->display,0x34)&=~1;
            B(lockVars->display,0x31)=1;
            U(lockVars->display,0x34)&=~0x80;
            set_identity_rotation_rows(D_L03_001B9BB0);
            ClearVector128((char *)lockVars->display+0xF0);
            F(lockVars->display,0xF4)=-1.5707964f;
            euler_rotation_basis((char *)lockVars->display+0xC0,(char *)lockVars->display+0xF0);
            SetMobyState(obj,6,-1);
        } else if ((AdvanceMuseumTimer(obj)>=6)) {
            ResetGadgetState(obj);
            QueueKeyedRequest(lockVars->resume,lockVars->volume);
            SetMobyState(obj,1,-1);
        }
        break;
    case 6:
        if (D_L03_001A8F00==7) {set_identity_rotation_rows(D_L03_001B9BB0);UpdateAttachedChild(obj);break;}
        ResetGadgetState(obj);
        QueueKeyedRequest(lockVars->resume,lockVars->volume);
        if (lockVars->cleanupId!=-1) ResetCameraEntry(lockVars->cleanupId);
        if (lockVars->completed) {
            SetMobyState(obj,7,-1);
            if (B(obj,0xB0)!=255) {
                unsigned short id;
                unsigned char *savedByte;
                id=U(obj,0xB2);
                if (id&1) {savedByte=D_0019B4A8+(((short)id>>1)+(gCurrentMapIndex<<10));if (((*savedByte>>4)&7)!=7) *savedByte+=16;}
                else {savedByte=D_0019B4A8+(((short)id>>1)+(gCurrentMapIndex<<10));if ((*savedByte&7)!=7) ++*savedByte;}
            }
            if (gCurrentMapIndex==19) {
                int j;
                for (j=0;j<2;j++) if (lockVars->childIds[j]!=-1) SetObjectFlagBit(D_L03_001B2A1C+(lockVars->childIds[j]<<8),1);
            }
        } else {StartHeroLoaderState(0);SetMobyState(obj,1,-1);}
        break;
    case 7: {
        int j;
        SetObjectFlagBit(obj,1);
        for (j=0;j<2;j++) if (lockVars->childIds[j]!=-1) SetObjectFlagBit(D_L03_001B2A1C+(lockVars->childIds[j]<<8),1);
        StartHeroLoaderState(0);SetMobyState(obj,8,-1);
        break;
    }
    }
}
