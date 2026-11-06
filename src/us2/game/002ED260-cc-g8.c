/* func_US2_002ED260, the USA v2.00 copy of func_002EC408: the same C, where rename func_00298F00 becomes func_US2_00299CF0; rename func_002E9268 becomes func_US2_002EA0C0; rename func_002EA8E8 becomes func_US2_002EB740; rename func_00133710 becomes func_00133700; rename func_00132828 becomes func_00132818; rename func_001336D0 becomes func_001336C0. */
#include "common.h"
extern unsigned char D_001A7BE8[] __attribute__((sda));
extern char D_00188660[], D_001A63A8_3[], D_00152C00[], D_001393E0[], D_001B9040[], D_001BAF80[], D_001BADC0[], D_001AC1E0[], D_001C5540[], D_00240450[], D_001B8840_raw[] __asm__("D_001B8840");
extern int D_00214920[];
extern int D_001ABEB0 __attribute__((sda)), D_001ABF0C __attribute__((sda));
extern void func_00282A60(void *, int, int), func_0011AEA0(int), func_002B7CE0(int);
extern void *func_001336C0(void (*)(s32));
extern int func_00132028(void), func_00133580(int), func_001261F0(int), func_0029EFD0(int), func_US2_002EA0C0(void), func_00293A60(void);
extern void func_0029FAE0(),
    func_00133700(),
    func_00133230(),
    func_002E5FE0(),
    func_002B7170(),
    func_00132858(),
    func_00132818(),
    func_0026FEB8(),
    func_00284E18(),
    func_US2_00299CF0(),
    func_00298178(),
    func_002939D0(),
    func_002FCDA8(),
    func_0027D330(),
    func_00133AA0(),
    func_002E6178(),
    func_002ED260(),
    func_002FC280(),
    func_002FC220(),
    func_00284FC0(),
    func_00285338(),
    func_00284EA8(),
    func_002B9000(),
    func_002FC3C0(),
    func_002EAB18(),
    func_US2_002EB740();
extern int D_001B1680[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern int D_00139810 __attribute__((nosda));
extern int D_00139814 __attribute__((nosda));
extern int D_0013977C __attribute__((nosda));
extern int D_00139780 __attribute__((nosda));
extern int D_00139788 __attribute__((nosda));
extern int D_001A7280[] __attribute__((sda));
extern int D_001A7424[] __attribute__((sda));
extern int D_001B16AC[] __attribute__((sda));
extern int D_001B2148[] __attribute__((sda));
extern unsigned char D_001395E3 __attribute__((nosda));
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern int D_001B2130[] MACRO_ADDR __attribute__((sda));
extern int D_001B1598[] __attribute__((sda));

typedef struct { unsigned char a,b,c,pad; float x,y,z,w; } Config;
extern Config D_001B1640 __attribute__((sda));
typedef struct { char pad[0x17a0]; int handles[6]; } TransitionEngine;
typedef struct { char pad[0x2c]; short phase, scene; } TransitionState;
typedef struct { char pad[0x18]; short requested; char pad1[0x142]; int state; int pad2; int request; char pad3[0x14]; int playing; } TransitionAudio;
typedef struct { char pad[0x218]; float near_plane, far_plane, pad2[2], near_intensity, far_intensity; int red, green, blue; } TransitionFog;
typedef struct { char pad[0x10]; unsigned flags; } TransitionArchive;
typedef struct { char pad[0x54]; char *current; } TransitionScene;

void func_US2_002ED260(void)
{
    int i,ready,done,kind,current;
    func_00282A60(D_001BADC0,-1,0x80);
    D_001A8BB0[0]=6;
    ((TransitionState *)D_00152C00)->phase=0;
    ((TransitionState *)D_00152C00)->scene=0;
    if(D_001B1680[0]==22 || D_001A79F0[0]==22) ((TransitionState *)D_00152C00)->scene=1;
    else if(D_001B1680[0]==23 || D_001A79F0[0]==23) ((TransitionState *)D_00152C00)->scene=1;
    else if(D_001B1680[0]==26 || D_001A79F0[0]==26) ((TransitionState *)D_00152C00)->scene=2;
    if(D_001B1680[0]==14 && !D_001395E3) ((TransitionState *)D_00152C00)->scene=3;
    if(D_001A7BE8[0] && D_001B1680[0] && !(D_00139810&0x200)) D_001ABEB0=0xa9;
    else if(D_001A7BE8[1] && D_001B1680[0]!=1 && !(D_0013977C&0x800000))D_001ABEB0=23;
    else if(D_001A7BE8[5] && D_001B1680[0]!=5 && !(D_00139810&0x800))D_001ABEB0=0xab;
    else if(D_001A7BE8[8] && D_001B1680[0]!=8 && !(D_00139814&0x2000))D_001ABEB0=0xad;
    else if((D_001A7BC8[10] || D_001A7BC8[11]) && !(D_00139780&0x4000000))D_001ABEB0=26;
    else if(D_001B1680[0]==13 && !(D_00139780&0x8000000))D_001ABEB0=27;
    else if(D_001A7BE8[16] && D_001B1680[0]!=16 && !(D_00139814&0x8000))D_001ABEB0=0xaf;
    ((TransitionArchive *)D_001BAF80)->flags|=0x80000000;
    func_0029FAE0();
    func_0011AEA0(0);
    func_00133700(2,0,0,0,0);
    func_00133230();
    func_00132028();
    func_002E5FE0();
    func_002B7170();
    D_001A63A8_3[7]=1;
    for (i=0; i<6; i++)if(((TransitionEngine *)D_00188660)->handles[i]){
        func_00132858(((TransitionEngine *)D_00188660)->handles[i]);
        func_00132818();
        func_0026FEB8(D_001AC1E0,((TransitionEngine *)D_00188660)->handles[i]);
        D_001B16AC[0]=0;
        ((TransitionEngine *)D_00188660)->handles[i]=0;
    }
    ((TransitionFog *)D_001B9040)->red=0;
    ((TransitionFog *)D_001B9040)->green=0;
    ((TransitionFog *)D_001B9040)->blue=16;
    ((TransitionFog *)D_001B9040)->near_plane=0;
    ((TransitionFog *)D_001B9040)->far_plane=524288.0f;
    ((TransitionFog *)D_001B9040)->near_intensity=255.0f;
    ((TransitionFog *)D_001B9040)->far_intensity=128.0f;
    D_001B1640.a=*(unsigned char *)&((TransitionFog *)D_001B9040)->red;
    D_001B1640.b=*(unsigned char *)&((TransitionFog *)D_001B9040)->green;
    D_001B1640.c=*(unsigned char *)&((TransitionFog *)D_001B9040)->blue;
    D_001B1640.x=((TransitionFog *)D_001B9040)->near_plane;
    D_001B1640.y=((TransitionFog *)D_001B9040)->far_plane;
    D_001B1640.z=((TransitionFog *)D_001B9040)->near_intensity;
    D_001B1640.w=((TransitionFog *)D_001B9040)->far_intensity;
    func_00284E18(0,0,0);
    if(D_001B1680[0]<0) {
        while(((TransitionAudio *)D_001393E0)->state>=3 || ((TransitionAudio *)D_001393E0)->request>=0){
            func_US2_00299CF0();
            func_00298178();
        }
        if(((TransitionAudio *)D_001393E0)->playing)((TransitionAudio *)D_001393E0)->playing=0;
        if(((TransitionAudio *)D_001393E0)->requested>=0)((TransitionAudio *)D_001393E0)->requested=-1;
        D_001A7424[0]=D_001A7424[0]&~0x200;
        func_001336C0(0);
        D_001A63A8_3[7]=0;
        func_002B7CE0(1);
        while(func_00132028()){
        }
        D_001A63A8_3[7]=1;
        func_0027D330(6);
        D_001A79F0[0]=D_001B1680[0];
        func_002939D0();
        func_00133580(0);
        D_001A63A8_3[7]=0;
        func_002FCDA8();
        return;
    }
    current=D_001A79F0[0];
    if((unsigned)current<19 && (current || (D_00139788&2)) && current<28)D_001A7BE8[current]=2;
    D_001A79F0[0]=D_001B1680[0];
    D_001A7280[0]=0;
    D_001A7280[1]=1;
    ((TransitionArchive *)D_001BAF80)->flags|=0x80000000;
    ready=0;
    func_002EAB18();
    func_00133AA0(D_001A79F0[0],D_001C5540);
    kind=((TransitionState *)D_00152C00)->scene;
    if(kind==3){
        D_001B2148[0]=func_0029EFD0(0x1342);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else if(kind==1){
        D_001B2148[0]=func_0029EFD0(0x128c);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else if(kind==2){
        D_001B2148[0]=func_0029EFD0(0x128d);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else{
        int i;
        for(i=0;D_00214920[i];i++)D_00214920[i]=0;
        func_002E6178(((TransitionScene *)D_001B8840_raw)->current);
    }
    func_002ED260(D_00240450);
    do {
        func_002FC280();
        func_002FC220();
        func_00284FC0();
        func_00285338();
        func_00284EA8();
        func_002B9000();
        done=func_US2_002EA0C0();
        func_US2_002EB740();
        func_US2_00299CF0();
        func_00298178();
        func_002FC3C0(1);
        func_001261F0(0);
        D_001B1598[0]=D_001B1598[0]+1;
        if(!D_001ABEB0 && !ready)ready=func_00293A60();
    }
    while(!done);
    D_001ABF0C=0;
    if(!ready){
        do{
            func_0011AEA0(0);
            func_001261F0(0);
            func_US2_00299CF0();
            func_00298178();
        }
        while(!func_00293A60());
    }
    while(((TransitionAudio *)D_001393E0)->state!=2 || ((TransitionAudio *)D_001393E0)->request>=0){
        func_0011AEA0(0);
        func_001261F0(0);
        func_US2_00299CF0();
        func_00298178();
    }
    if(D_001B2130[2])func_00132858(D_001B2130[2]);
    if(D_001B2130[4])func_00132858(D_001B2130[4]);
    while(func_00132028()){
    }
    func_00132818();
    func_001336C0(0);
    func_00133580(0);
    func_00133580(0);
    D_001A63A8_3[7]=0;
    func_002FCDA8();
}
