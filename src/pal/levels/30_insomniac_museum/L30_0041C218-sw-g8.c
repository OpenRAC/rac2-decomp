#include "include_asm.h"

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
extern void func_00294420(int),func_L00_002C8BA8(int),func_PAL_L00_002C4480(int,int);
extern void func_00283098(void *,void *,void *),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern float func_00283B98(float,float),func_00283248(float,float),func_00282E80(void *,void *);
extern void func_L00_002D40A0(void *,int,float);
extern int func_L00_002D40F0(void);
extern void func_PAL_L00_002D2668(int,int,float),func_0026FF08(int,int,float,float,float,float);
extern void func_00335438(void *,void *,int,int,int),func_00335370(void *),func_003353C8(void *);
extern void func_002AC9F8(void *,float),func_002AA800(void *,int,float,float);
extern float func_002AA2E8(float *,float,float);
extern int func_002B49E0(int,int,char *,int,int);
extern void func_00283360(void *),func_00282C88(void *),func_002833F0(void *,void *),func_L00_0042A500(int);
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

void func_PAL_L30_0041CE18(char *obj) {
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
            || (state = D_0019B4A8[((short)id>>1)+(D_001A79F0<<10)], (id & 1) ? (state>>4)&7 : state&7)) {
            func_002A7750(obj,8,-1);
            func_L00_003294F0(obj,1);
            for (j=0;j<2;j++) if (st->childIds[j]!=-1) func_L00_003294F0(D_L30_001B2D1C+(st->childIds[j]<<8),1);
        } else {
            func_002A7750(obj,1,-1);
            func_L30_00418570(obj);
            o=(char *)st->display;
            qcopy(o+0x10,obj+0x10);
            F(o,0x18)+=1.0f;
            U(st->display,0x34)|=1;
            B(st->display,0x31)=0;
        }
        break;
    }
    case 1:
        if (D_00189E20.focus!=obj || D_L30_001B2C40<16 || !D_001A7B2B) break;
        func_002B0CE0(12,0x1BC9,1);
        if (!func_00294630(((MuseumSound *)D_L30_002693F0)[D_00139568.mode].handle)) {
            func_00294420(((MuseumSound *)D_L30_002693F0)[D_00139568.mode].handle);
            break;
        }
        if (D_00138180.buttons.words.high&0x10) {
            st->saved=D_00189E20.saved;
            D_00189E20.action=0x33;
            func_002A7750(obj,2,-1);
        } else if ((D_001A79F0==21 || D_001A79F0==30) && ((D_00138180.buttons.mask&3)==3)) func_002A7750(obj,9,-1);
        break;
    case 2: {
        unsigned int cameraState;
        if (func_002B3868(obj)) {
            func_00283098(vec,D_L30_001B1FC0_gp,obj+0xC0);
            func_00282CC0(vec,vec,obj+0x10);
            func_L00_002D40A0(vec,0,func_00283B98(F(obj,0xF8),3.1415927f));
        }
        cameraState=func_L00_002D40F0();
        if (cameraState==2) func_002A7750(obj,3,-1);
        else if ((AdvanceMuseumTimer(obj)>=251)) {func_L00_002C8BA8(0);func_002A7750(obj,1,-1);}
        else if (!cameraState) func_002A7750(obj,1,-1);
        break;
    }
    case 3:
        if (func_002B3868(obj)) {
            func_PAL_L00_002C4480(0x6F,0);func_PAL_L00_002D2668(0x54,0,17.0f);
            func_00282CF0(vec,D_L30_001B9DC0,D_00189E20.position);
            func_00283098(vec,vec,D_00189E20.matrix40);
            func_00335438(D_L30_001B9DC0,D_L30_001B9DC0,3,100,0);
            st->fade=0;
        }
        func_00283098(vec,D_L30_001B1FC0_gp,obj+0xC0);
        func_00282CC0(vec,vec,obj+0x10);
        func_00282CF0(D_00189E20.velocity,vec,D_00189E20.position);
        D_00189E20.velocity[2]=0;
        func_002AC9F8(D_00189E20.velocity,0.015000001f);
        func_002AA800(D_00189E20.rotation,0,func_00283B98(F(obj,0xF8),3.1415927f),0.020943955f);
        D_00189E20.mode=3;
        if ((D_00189E20.flags&2) && B(D_00189E20.animation,0x43)==0x54) func_PAL_L00_002D2668(0x55,0,6.0f);
        if (D_00189E20.animationId!=0x6F) func_002A7750(obj,1,-1);
        func_00283098(pos,D_L30_001B1FD0_gp,&D_00189E20);
        func_00282CC0(pos,pos,D_00189E20.position);
        qzero_nc(rot);
        func_00283098(target,D_L30_001B1FE0_gp,&D_00189E20);
        func_00282CC0(target,target,D_00189E20.position);
        rot[2]=func_00283248(target[0]-pos[0],target[1]-pos[1]);
        rot[1]=-func_00283248(func_00282E80(pos,target),target[2]-pos[2]);
        func_00335370(pos);func_003353C8(rot);
        if ((AdvanceMuseumTimer(obj)>=51)) func_002A7750(obj,4,-1);
        break;
    case 4: {
        unsigned int elapsed;
        if (func_002B3868(obj)) {
            D_L30_001BA054=0.017453294f;
            func_0026FF08(25,1,0.017453294f,0.005f,0.2f,0.0f);
        }
        D_00189E20.mode=3;
        if ((AdvanceMuseumTimer(obj)<18)) break;
        func_002AA2E8(&st->fade,1.0f,0.14000002f);
        elapsed=U(obj,0x96);
        D_L30_001B2764=st->fade;
        if (elapsed<26) break;
        D_L30_001BA054=1.1243411f;
        func_0026FF08(1,0,1.1243411f,0.005f,0.2f,0.0f);
        if (!func_002B49E0(7,1,obj,0,0)) func_002A7750(obj,5,-1);
        break;
    }
    case 5:
        if (D_L30_001A8F00==7) {
            int i;
            func_L30_00418570(obj);
            D_L30_001B06E8=0;
            /* Pointer arithmetic, not trackIds[i]: an array field of a BLKmode struct would form st+0xC in its own
             * register ahead of the loop's duplicated exit test. The scalar globals leave the loop through load_mems. */
            for (i=0;i<14&&*(st->trackIds+i)>=0;i++) {
                D_L30_0029D0E0[i][0]=*(st->trackIds+i);
                D_L30_001B06E8++;
                D_L30_001B06F4=st->duration;
                D_L30_001B06F0=st->duration+100;
                D_L30_001B06F8=st->limit;
                st->display->vars->settings=st->settings;
            }
            U(st->display,0x34)&=~1;
            B(st->display,0x31)=1;
            U(st->display,0x34)&=~0x80;
            func_00283360(D_L30_001B9FF0);
            func_00282C88((char *)st->display+0xF0);
            F(st->display,0xF4)=-1.5707964f;
            func_002833F0((char *)st->display+0xC0,(char *)st->display+0xF0);
            func_002A7750(obj,6,-1);
        } else if ((AdvanceMuseumTimer(obj)>=5)) func_002A7750(obj,1,-1);
        break;
    case 6:
        if (D_L30_001A8F00==7) {func_00283360(D_L30_001B9FF0);func_L30_004185E0(obj);break;}
        func_L30_00418670(obj);
        if (st->cleanupId!=-1) func_L00_0042A500(st->cleanupId);
        if (st->completed) {
            unsigned short id;
            unsigned char *p;
            func_002A7750(obj,7,-1);
            if (B(obj,0xB0)==255) break;
            id=U(obj,0xB2);
            if (id&1) {p=D_0019B4A8+(((short)id>>1)+(D_001A79F0<<10));if (((*p>>4)&7)!=7) *p+=16;}
            else {p=D_0019B4A8+(((short)id>>1)+(D_001A79F0<<10));if ((*p&7)!=7) ++*p;}
        } else {func_L00_002C8BA8(0);func_002A7750(obj,1,-1);}
        break;
    case 7: {
        int j;
        func_L00_003294F0(obj,1);
        for (j=0;j<2;j++) if (st->childIds[j]!=-1) func_L00_003294F0(D_L30_001B2D1C+(st->childIds[j]<<8),1);
        func_L00_002C8BA8(0);func_002A7750(obj,8,-1);
        break;
    }
    case 8:
        if ((D_00138180.buttons.mask&15)==15) func_002A7750(obj,9,-1);
        break;
    case 9:
        if (func_002B3868(obj)) {
            st->menu=func_L30_00413490(obj);
            func_L30_00413528(st->menu,&st->settings,D_L30_001B1FF0,0,0,10000);
            func_L30_00413528(st->menu,&st->duration,D_L30_001B2000,0,30,1000);
            func_L30_00413528(st->menu,&st->limit,D_L30_001B2010,0,15,1000);
            func_L30_00413528(st->menu,&st->trackIds[0],D_L30_001B2020,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[1],D_L30_001B2030,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[2],D_L30_001B2040,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[3],D_L30_001B2050,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[4],D_L30_001B2060,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[5],D_L30_001B2070,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[6],D_L30_001B2080,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[7],D_L30_001B2090,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[8],D_L30_001B20A0,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[9],D_L30_001B20B0,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[10],D_L30_001B20C0,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[11],D_L30_001B20D0,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[12],D_L30_001B20E0,0,-1,3);
            func_L30_00413528(st->menu,&st->trackIds[13],D_L30_001B20F0,0,-1,3);
            st->completed=0;
        }
        func_002B0CE0(1,0,1);
        if (!st->menu || H(st->menu,0xAA)!=0x118A || B(st->menu,0x20)==254 || B(st->menu,0x20)==253) func_002A7750(obj,1,-1);
        break;
    }
}
