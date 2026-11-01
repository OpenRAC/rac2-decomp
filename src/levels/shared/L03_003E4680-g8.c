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
extern void func_00294420(int),func_L00_002C8BA8(int),func_L03_002C6F08(int,int);
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
extern void func_002E5CF8(int,int,char *);
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
void func_L03_003E4680(char *obj) {
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
        if (((MuseumCompletion *)D_L03_0021EA30)->complete[(short)id]
            || (state = D_0019B4A8[((short)id>>1)+(D_001A79F0<<10)], (id & 1) ? (state>>4)&7 : state&7)) {
            func_002A7750(obj,8,-1);
            func_L00_003294F0(obj,1);
            for (j=0;j<2;j++) if (st->childIds[j]!=-1) func_L00_003294F0(D_L03_001B2A1C+(st->childIds[j]<<8),1);
        } else {
            func_002A7750(obj,1,-1);
            func_L03_003E5070(obj);
            o=(char *)st->display;
            qcopy(o+0x10,obj+0x10);
            F(o,0x18)+=1.0f;
            U(st->display,0x34)|=1;
            B(st->display,0x31)=0;
        }
        break;
    }
    case 1:
        if (D_00189E20.focus!=obj || D_L03_001B2940<16 || !D_001A7B2B) break;
        func_002B0CE0(12,0x27F0,1);
        if (!func_00294630(((MuseumSound *)D_L03_00266DA0)[D_00139568.mode].handle)) {
            func_00294420(((MuseumSound *)D_L03_00266DA0)[D_00139568.mode].handle);
            break;
        }
        if (D_00138180.buttons.words.high&0x10) {
            st->saved=D_00189E20.saved;
            D_00189E20.action=0x33;
            func_002A7750(obj,2,-1);
        }
        break;
    case 2: {
        unsigned int cameraState;
        if (func_002B3868(obj)) {
            func_00283098(vec,D_L03_001B0C70_gp,obj+0xC0);
            func_00282CC0(vec,vec,obj+0x10);
            func_L00_002D40A0(vec,0,func_00283B98(F(obj,0xF8),3.1415927f));
        }
        cameraState=func_L00_002D40F0();
        if (cameraState==2) func_002A7750(obj,3,-1);
        else if ((AdvanceMuseumTimer(obj)>=301)) {func_L03_003E5170(obj);func_L00_002C8BA8(0);func_002A7750(obj,1,-1);}
        else if (!cameraState) {func_L03_003E5170(obj);func_002A7750(obj,1,-1);}
        break;
    }
    case 3:
        if (func_002B3868(obj)) {
            func_002E5CF8(0,0,obj);
            func_L03_002C6F08(0x6F,0);func_L00_002D2168(0x54,0,20.0f);
            func_00282CF0(vec,D_L03_001B9980,D_00189E20.position);
            func_00283098(vec,vec,D_00189E20.matrix40);
            func_00335438(D_L03_001B9980,D_L03_001B9980,3,120,0);
            st->fade=0;
        }
        func_00283098(vec,D_L03_001B0C70_gp,obj+0xC0);
        func_00282CC0(vec,vec,obj+0x10);
        func_00282CF0(D_00189E20.velocity,vec,D_00189E20.position);
        D_00189E20.velocity[2]=0;
        func_002AC9F8(D_00189E20.velocity,0.012500001f);
        func_002AA800(D_00189E20.rotation,0,func_00283B98(F(obj,0xF8),3.1415927f),0.017453296f);
        D_00189E20.mode=3;
        if ((D_00189E20.flags&2) && B(D_00189E20.animation,0x43)==0x54) func_L00_002D2168(0x55,0,7.0f);
        if (D_00189E20.animationId!=0x6F) {func_L03_003E5170(obj);func_002A7750(obj,1,-1);}
        func_00283098(pos,D_L03_001B0C80_gp,&D_00189E20);
        func_00282CC0(pos,pos,D_00189E20.position);
        qzero_nc(rot);
        func_00283098(target,D_L03_001B0C90_gp,&D_00189E20);
        func_00282CC0(target,target,D_00189E20.position);
        rot[2]=func_00283248(target[0]-pos[0],target[1]-pos[1]);
        rot[1]=-func_00283248(func_00282E80(pos,target),target[2]-pos[2]);
        func_00335370(pos);func_003353C8(rot);
        if ((AdvanceMuseumTimer(obj)>=61)) {
            func_002A7750(obj,4,-1);
            st->resume=D_001A63A8.a==-1?D_001A63A8.b:D_001A63A8.a;
            func_L01_00323310(st->music,st->volume);
        }
        break;
    case 4: {
        unsigned int elapsed;
        if (func_002B3868(obj)) {
            func_002E5CF8(0,0,obj);
            D_L03_001B9C14=0.017453294f;
            func_0026FF08(30,1,0.017453294f,0.005f,0.2f,0.0f);
        }
        D_00189E20.mode=3;
        if (D_00189E20.animationId!=0x6F) {func_L03_003E5170(obj);func_002A7750(obj,1,-1);break;}
        if ((AdvanceMuseumTimer(obj)<21)) break;
        func_002AA2E8(&st->fade,1.0f,0.116666675f);
        elapsed=U(obj,0x96);
        D_L03_001B2464=st->fade;
        if (elapsed<31) break;
        D_L03_001B9C14=1.1243411f;
        func_0026FF08(1,0,1.1243411f,0.005f,0.2f,0.0f);
        if (!func_002B49E0(7,1,obj,0,0)) func_002A7750(obj,5,-1);
        break;
    }
    case 5:
        if (D_L03_001A8F00==7) {
            int i;
            qzero_nc(D_L03_001B9980);
            func_L03_003E5070(obj);
            D_L03_001B0B50=0;
            /* Pointer arithmetic, not trackIds[i]: an array field of a BLKmode struct would form st+0xC in its own
             * register ahead of the loop's duplicated exit test. The scalar globals leave the loop through load_mems. */
            for (i=0;i<14&&*(st->trackIds+i)>=0;i++) {
                D_L03_0029BCD0[i][0]=*(st->trackIds+i);
                D_L03_001B0B50++;
                D_L03_001B0B5C=st->duration;
                D_L03_001B0B58=st->duration+120;
                D_L03_001B0B60=st->limit;
                st->display->vars->settings=st->settings;
            }
            U(st->display,0x34)&=~1;
            B(st->display,0x31)=1;
            U(st->display,0x34)&=~0x80;
            func_00283360(D_L03_001B9BB0);
            func_00282C88((char *)st->display+0xF0);
            F(st->display,0xF4)=-1.5707964f;
            func_002833F0((char *)st->display+0xC0,(char *)st->display+0xF0);
            func_002A7750(obj,6,-1);
        } else if ((AdvanceMuseumTimer(obj)>=6)) {
            func_L03_003E5170(obj);
            func_L01_00323310(st->resume,st->volume);
            func_002A7750(obj,1,-1);
        }
        break;
    case 6:
        if (D_L03_001A8F00==7) {func_00283360(D_L03_001B9BB0);func_L03_003E50E0(obj);break;}
        func_L03_003E5170(obj);
        func_L01_00323310(st->resume,st->volume);
        if (st->cleanupId!=-1) func_L00_0042A500(st->cleanupId);
        if (st->completed) {
            func_002A7750(obj,7,-1);
            if (B(obj,0xB0)!=255) {
                unsigned short id;
                unsigned char *p;
                id=U(obj,0xB2);
                if (id&1) {p=D_0019B4A8+(((short)id>>1)+(D_001A79F0<<10));if (((*p>>4)&7)!=7) *p+=16;}
                else {p=D_0019B4A8+(((short)id>>1)+(D_001A79F0<<10));if ((*p&7)!=7) ++*p;}
            }
            if (D_001A79F0==19) {
                int j;
                for (j=0;j<2;j++) if (st->childIds[j]!=-1) func_L00_003294F0(D_L03_001B2A1C+(st->childIds[j]<<8),1);
            }
        } else {func_L00_002C8BA8(0);func_002A7750(obj,1,-1);}
        break;
    case 7: {
        int j;
        func_L00_003294F0(obj,1);
        for (j=0;j<2;j++) if (st->childIds[j]!=-1) func_L00_003294F0(D_L03_001B2A1C+(st->childIds[j]<<8),1);
        func_L00_002C8BA8(0);func_002A7750(obj,8,-1);
        break;
    }
    }
}
