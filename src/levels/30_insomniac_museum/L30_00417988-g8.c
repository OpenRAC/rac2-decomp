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
extern char D_L30_0021EDB0[];
typedef struct MuseumSound { char pad[0x14]; int handle; char rest[0xC8]; } MuseumSound;
extern char D_L30_002693F0[];
extern int D_L30_001B2C40;
extern char *D_L30_001B2D1C;
extern char D_L30_001B1FC0_gp[] SDATA(D_L30_001B1FC0), D_L30_001B1FD0_gp[] SDATA(D_L30_001B1FD0), D_L30_001B1FE0_gp[] SDATA(D_L30_001B1FE0);
extern char D_L30_001B9DC0[], D_L30_001B9FF0[];
extern float D_L30_001BA054 NOT_SDA, D_L30_001B2764 MACRO_ADDR;
extern int D_L30_001A8F00;
extern int D_L30_001B06E8 MACRO_ADDR, D_L30_001B06F0 MACRO_ADDR, D_L30_001B06F4 MACRO_ADDR, D_L30_001B06F8 MACRO_ADDR;
extern int D_L30_0029D0E0[][4];
extern char D_L30_001B1FF0[],D_L30_001B2000[],D_L30_001B2010[],D_L30_001B2020[],D_L30_001B2030[],D_L30_001B2040[],D_L30_001B2050[],D_L30_001B2060[],D_L30_001B2070[],D_L30_001B2080[],D_L30_001B2090[],D_L30_001B20A0[],D_L30_001B20B0[],D_L30_001B20C0[],D_L30_001B20D0[],D_L30_001B20E0[],D_L30_001B20F0[];
extern void func_002A7750(char *,int,int), func_L00_003294F0(char *,int);
extern int func_002B3868(char *);
extern void func_L30_00418570(char *),func_L30_004185E0(char *),func_L30_00418670(char *);
extern int func_002B0CE0(int,int,int);
extern int func_00294630(int);
extern void func_00294420(int),func_L00_002C8BA8(int),func_L00_002C42E0(int,int);
extern void func_00283098(void *,void *,void *),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern float func_00283B98(float,float),func_00283248(float,float),func_00282E80(void *,void *);
extern void func_L00_002D40A0(void *,int,float);
extern int func_L00_002D40F0(void);
extern void func_L00_002D2168(int,int,float),func_0026FF08(int,int,float,float,float,float);
extern void func_L30_0042BEB8(void *,void *,int,int,int),func_L30_0042BDF0(void *),func_L30_0042BE48(void *);
extern void func_002AC9F8(void *,float),func_002AA800(void *,int,float,float);
extern float func_002AA2E8(float *,float,float);
extern int func_002B49E0(int,int,char *,int,int);
extern void func_00283360(void *),func_00282C88(void *),func_002833F0(void *,void *),func_L30_0042E658(int);
extern char *func_L30_00413490(char *);
extern void func_L30_00413528(char *,void *,void *,int,int,int);
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
    MuseumDisplay *display;
    char *menu;
    int completed, saved;
    int pad60;
    float fade;
} MuseumExhibit;
void func_L30_00417988(char *obj) {
    MuseumExhibit *st = (MuseumExhibit *)P(obj,0x68);
    float vec[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float target[4] __attribute__((aligned(16)));
    switch (B(obj,0x20)) {
    case 0: {
        int j, state;
        unsigned short id = U(obj,0xB2);
        char *o;
        if (((MuseumCompletion *)D_L30_0021EDB0)->complete[(short)id]
            || (state = D_0019B4A8[((short)id>>1)+(gCurrentMapIndex<<10)], (id & 1) ? (state>>4)&7 : state&7)) {
            SetMobyState(obj,8,-1);
            SetObjectFlagBit(obj,1);
            for (j=0;j<2;j++) if (st->childIds[j]!=-1) SetObjectFlagBit(D_L30_001B2D1C+(st->childIds[j]<<8),1);
        } else {
            SetMobyState(obj,1,-1);
            SpawnMuseumEffectObject(obj);
            o=(char *)st->display;
            qcopy(o+0x10,obj+0x10);
            F(o,0x18)+=1.0f;
            U(st->display,0x34)|=1;
            B(st->display,0x31)=0;
        }
        break;
    }
    case 1:
        if (gHeroState.focus!=obj || D_L30_001B2C40<16 || !D_001A7B2B) break;
        ForceClaimNotice(12,0x2803,1);
        if (!IsClassCached(((MuseumSound *)D_L30_002693F0)[gItemSlotToRecord.mode].handle)) {
            LoadClassIntoFreeCacheSlot(((MuseumSound *)D_L30_002693F0)[gItemSlotToRecord.mode].handle);
            break;
        }
        if (gPadState.buttons.words.high&0x10) {
            st->saved=gHeroState.saved;
            gHeroState.action=0x33;
            SetMobyState(obj,2,-1);
        } else if ((gCurrentMapIndex==21 || gCurrentMapIndex==30) && ((gPadState.buttons.mask&3)==3)) SetMobyState(obj,9,-1);
        break;
    case 2: {
        unsigned int cameraState;
        if (SetFirstPendingFlag(obj)) {
            matrix_mul_vec3(vec,D_L30_001B1FC0_gp,obj+0xC0);
            FastVecAdd(vec,vec,obj+0x10);
            StartHeroTargetState(vec,0,FastAddRotations(F(obj,0xF8),3.1415927f));
        }
        cameraState=GetHeroTargetStateKind();
        if (cameraState==2) SetMobyState(obj,3,-1);
        else if ((AdvanceMuseumTimer(obj)>=301)) {StartHeroLoaderState(0);SetMobyState(obj,1,-1);}
        else if (!cameraState) SetMobyState(obj,1,-1);
        break;
    }
    case 3:
        if (SetFirstPendingFlag(obj)) {
            SetHeroAction_L00(0x6F,0);set_hero_animation(0x54,0,20.0f);
            FastVecSub(vec,D_L30_001B9DC0,gHeroState.position);
            matrix_mul_vec3(vec,vec,gHeroState.matrix40);
            func_L30_0042BEB8(D_L30_001B9DC0,D_L30_001B9DC0,3,120,0);
            st->fade=0;
        }
        matrix_mul_vec3(vec,D_L30_001B1FC0_gp,obj+0xC0);
        FastVecAdd(vec,vec,obj+0x10);
        FastVecSub(gHeroState.velocity,vec,gHeroState.position);
        gHeroState.velocity[2]=0;
        ClampVectorLength(gHeroState.velocity,0.012500001f);
        StepAngleTowardTarget(gHeroState.rotation,0,FastAddRotations(F(obj,0xF8),3.1415927f),0.017453296f);
        gHeroState.mode=3;
        if ((gHeroState.flags&2) && B(gHeroState.animation,0x43)==0x54) set_hero_animation(0x55,0,7.0f);
        if (gHeroState.animationId!=0x6F) SetMobyState(obj,1,-1);
        matrix_mul_vec3(pos,D_L30_001B1FD0_gp,&gHeroState);
        FastVecAdd(pos,pos,gHeroState.position);
        qzero_nc(rot);
        matrix_mul_vec3(target,D_L30_001B1FE0_gp,&gHeroState);
        FastVecAdd(target,target,gHeroState.position);
        rot[2]=FastMatrixHelperA(target[0]-pos[0],target[1]-pos[1]);
        rot[1]=-FastMatrixHelperA(vec_distance_xy(pos,target),target[2]-pos[2]);
        func_L30_0042BDF0(pos);func_L30_0042BE48(rot);
        if ((AdvanceMuseumTimer(obj)>=61)) SetMobyState(obj,4,-1);
        break;
    case 4: {
        unsigned int elapsed;
        if (SetFirstPendingFlag(obj)) {
            D_L30_001BA054=0.017453294f;
            SetCameraValueTarget(30,1,0.017453294f,0.005f,0.2f,0.0f);
        }
        gHeroState.mode=3;
        if ((AdvanceMuseumTimer(obj)<21)) break;
        ApproachValue(&st->fade,1.0f,0.116666675f);
        elapsed=U(obj,0x96);
        D_L30_001B2764=st->fade;
        if (elapsed<31) break;
        D_L30_001BA054=1.1243411f;
        SetCameraValueTarget(1,0,1.1243411f,0.005f,0.2f,0.0f);
        if (!BeginSlotRequest(7,1,obj,0,0)) SetMobyState(obj,5,-1);
        break;
    }
    case 5:
        if (D_L30_001A8F00==7) {
            int i;
            SpawnMuseumEffectObject(obj);
            D_L30_001B06E8=0;
            /* Pointer arithmetic, not trackIds[i]: an array field of a BLKmode struct would form st+0xC in its own
             * register ahead of the loop's duplicated exit test. The scalar globals leave the loop through load_mems. */
            for (i=0;i<14&&*(st->trackIds+i)>=0;i++) {
                D_L30_0029D0E0[i][0]=*(st->trackIds+i);
                D_L30_001B06E8++;
                D_L30_001B06F4=st->duration;
                D_L30_001B06F0=st->duration+120;
                D_L30_001B06F8=st->limit;
                st->display->vars->settings=st->settings;
            }
            U(st->display,0x34)&=~1;
            B(st->display,0x31)=1;
            U(st->display,0x34)&=~0x80;
            set_identity_rotation_rows(D_L30_001B9FF0);
            ClearVector128((char *)st->display+0xF0);
            F(st->display,0xF4)=-1.5707964f;
            euler_rotation_basis((char *)st->display+0xC0,(char *)st->display+0xF0);
            SetMobyState(obj,6,-1);
        } else if ((AdvanceMuseumTimer(obj)>=6)) SetMobyState(obj,1,-1);
        break;
    case 6:
        if (D_L30_001A8F00==7) {set_identity_rotation_rows(D_L30_001B9FF0);UpdateMuseumEffectHolder(obj);break;}
        ReleaseMuseumEffectObject(obj);
        if (st->cleanupId!=-1) func_L30_0042E658(st->cleanupId);
        if (st->completed) {
            unsigned short id;
            unsigned char *p;
            SetMobyState(obj,7,-1);
            if (B(obj,0xB0)==255) break;
            id=U(obj,0xB2);
            if (id&1) {p=D_0019B4A8+(((short)id>>1)+(gCurrentMapIndex<<10));if (((*p>>4)&7)!=7) *p+=16;}
            else {p=D_0019B4A8+(((short)id>>1)+(gCurrentMapIndex<<10));if ((*p&7)!=7) ++*p;}
        } else {StartHeroLoaderState(0);SetMobyState(obj,1,-1);}
        break;
    case 7: {
        int j;
        SetObjectFlagBit(obj,1);
        for (j=0;j<2;j++) if (st->childIds[j]!=-1) SetObjectFlagBit(D_L30_001B2D1C+(st->childIds[j]<<8),1);
        StartHeroLoaderState(0);SetMobyState(obj,8,-1);
        break;
    }
    case 8:
        if ((gPadState.buttons.mask&15)==15) SetMobyState(obj,9,-1);
        break;
    case 9:
        if (SetFirstPendingFlag(obj)) {
            st->menu=SpawnMuseumTweakMenu(obj);
            MuseumTweakMenuAddItem(st->menu,&st->settings,D_L30_001B1FF0,0,0,10000);
            MuseumTweakMenuAddItem(st->menu,&st->duration,D_L30_001B2000,0,30,1000);
            MuseumTweakMenuAddItem(st->menu,&st->limit,D_L30_001B2010,0,15,1000);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[0],D_L30_001B2020,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[1],D_L30_001B2030,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[2],D_L30_001B2040,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[3],D_L30_001B2050,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[4],D_L30_001B2060,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[5],D_L30_001B2070,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[6],D_L30_001B2080,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[7],D_L30_001B2090,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[8],D_L30_001B20A0,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[9],D_L30_001B20B0,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[10],D_L30_001B20C0,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[11],D_L30_001B20D0,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[12],D_L30_001B20E0,0,-1,3);
            MuseumTweakMenuAddItem(st->menu,&st->trackIds[13],D_L30_001B20F0,0,-1,3);
            st->completed=0;
        }
        ForceClaimNotice(1,0,1);
        if (!st->menu || H(st->menu,0xAA)!=0x118A || B(st->menu,0x20)==254 || B(st->menu,0x20)==253) SetMobyState(obj,1,-1);
        break;
    }
}
