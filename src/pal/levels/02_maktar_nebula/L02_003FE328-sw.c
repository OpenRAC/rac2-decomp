#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));
extern int func_00115DA8(char *, const char *, ...);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_L00_002C8BA8(int);
extern void func_L00_002D40A0(char *, int, float);
extern void func_L00_002E6CF0(void (*)(char *), char *);
extern void func_00282A60(void *, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283CE0(int);
extern int func_00288D58(void);
extern char * func_00288FB8(int);
extern void func_PAL_L00_00305110(int, int);
extern void func_PAL_L00_0030FBC0(char *, int);
extern void func_002A7750(char *, int, int);
extern int func_002A77E0(int);
extern int func_002ACBC8(char *, int);
extern int func_L00_003206B8(char *, int);
extern void func_002AD860(int);
extern void func_002B0C28(int, int, int);
extern int func_002B3868(char *);
extern void func_L00_003294F0(char *, int);
extern void func_L01_00323310(int, int);
extern void func_002DF3F8(void *, void *);
extern void func_L00_003672F8(void);
extern void func_L02_003D4900(char *);
extern void func_L02_003D4980(char *, char *);
extern void func_L02_003D4990(char *);
extern int func_L02_003D77B8(char *);
extern void func_L02_003DB870(char *, char *);
extern void func_PAL_L00_003E38E8(int, int);
extern int func_L02_003F9AF0(int);
extern int func_L02_003F9B70(int);
extern void func_L00_003E4948(char *);
extern void func_PAL_L02_003FF640(char *);
extern void func_L02_003FAF90(char *);
extern void func_PAL_L02_003FF718(char *);
extern void func_PAL_L02_003FF858(char *);
extern int func_L02_003FB4D8(char *, int);
extern char * func_L02_003FB5A0(char *, int, int);
extern void func_L02_003FB7E0(char *);
extern void func_L02_003FBA58(char *);
extern void func_L02_003FBAD0(char *);
extern void func_PAL_L02_004002E8(char *);
extern void func_L02_003FBCF8(char *);
extern char * func_L02_003FC098(char *);
extern void func_L02_003FC268(char *, int);
extern void func_L02_003FC518(char *, int);
extern void func_PAL_L02_00400F20(char *);
extern void func_PAL_L02_00401118(char *);
extern int func_L02_003FCBF0(char *);
extern void func_PAL_L02_004013F8(char *, int);
extern void func_L02_003FD070(char *);
extern void func_PAL_L02_00401980(char *);
extern void func_PAL_L02_00401EC8(char *);
extern void func_L02_003FD7C8(char *);
extern void func_PAL_L02_00402030(char *);
extern void func_L02_003FE8B8(char *);
extern void func_PAL_L02_00403FA0(char *);
extern void func_PAL_L02_004042C0(char *);
extern void func_PAL_L02_004046D0(char *);
extern void func_L02_004002E0(char *);
extern int func_L02_00400650(char *, int);
extern void func_L02_00400948(char *);
extern void func_PAL_L02_00405450(void);
extern void func_L01_003E9CF8(char *, int, void (*)(char *));
extern void func_PAL_L00_004071F0(int, int);
extern void func_00335438(void *, void *, int, int, int);
extern void func_003355A8(int);
extern unsigned char D_00139586 __attribute__((section(".data")));
extern unsigned char D_00139592 __attribute__((section(".data")));
extern unsigned char D_001395B8[] __attribute__((section(".data")));
extern int D_00139700 __attribute__((section(".data")));
extern int D_00139730 __attribute__((section(".data")));
extern char D_00189E20[] __attribute__((section(".data")));
extern char D_00189EA0[] __attribute__((section(".data")));
extern int D_0018B068 __attribute__((section(".data")));
extern int D_0018B6F4 __attribute__((section(".data")));
extern unsigned char D_0018C0D7 __attribute__((section(".data")));
extern int D_0018C2EC __attribute__((section(".data")));
extern char D_001A63A8[] __attribute__((section(".data")));
extern unsigned short D_001A65D2 __attribute__((section(".data")));
extern int D_001A7390[] __attribute__((sda));
extern int D_001A7904[] __attribute__((sda));
extern int D_001A7BC0[] __attribute__((sda));
extern int D_L02_001A8F00[] __attribute__((sda));
extern float D_L02_001A8F20[4] __attribute__((section(".sdata")));
extern int D_L02_001A9010 __attribute__((sda));
extern int D_L02_001AA1B0[] __attribute__((sda));
extern char *D_L02_001B1190[14] __attribute__((sda));
extern unsigned char D_L02_001B11C8[4] __attribute__((sda));
extern int D_L02_001B1224 __attribute__((sda));
extern char D_L02_001B1228[] __attribute__((section(".data")));
extern float D_L02_001B2FE0 __attribute__((sda));
extern char * D_L02_001B359C[] __attribute__((sda));
extern char * D_L02_001B35A8[] __attribute__((sda));
extern int D_L02_001B3680[] __attribute__((sda));
extern char * D_L02_001B368C[] __attribute__((sda));
extern char * D_L02_001B3770[] __attribute__((sda));
extern char D_L02_001BA3C0[] __attribute__((section(".data")));
extern int D_L02_001CAA80 __attribute__((section(".data")));
extern char D_L02_001FF6B8[] __attribute__((section(".data")));
typedef struct MaktarState {
    u8 pad000[0x50];
    s32 loadout[4];       
    s32 lost;             
    u8 pad064[0xC];
    s32 trigger1;         
    s32 trigger2;         
    u8 pad078[4];
    s32 zone;             
    u8 pad080[0xC];
    s32 camera;           
    s32 counts[6];        
    char *slots[10];      
    char *owner;          
    s32 frames;           
    s32 slot;             
    u8 pad0DC[0x108 - 0xDC];
    s32 gate1;            
    s32 gate2;            
    u8 pad110[8];
    s16 result;           
    u8 pad11A[6];
    s16 cls;              
    s16 wave;             
    s16 fade;             
    u8 pad126[0x1D0 - 0x126];
    s16 marks[40];        
    s32 music;            
    u8 pad224[4];
    s32 volume;           
    u8 pad22C[4];
    s32 track;            
    s32 trackVolume;      
} MaktarState;
typedef struct MaktarObj {
    u8 pad00[0x20];
    u8 state;             
    u8 pad21[0x68 - 0x21];
    MaktarState *st;      
    u8 pad6C[0x96 - 0x6C];
    u16 timer;            
    u8 pad98[0xBC - 0x98];
    u8 phase;             
    u8 padBD;
    u8 flags;             
} MaktarObj;
typedef struct { u8 pad0[0x284]; char *owner; s32 timer; } MaktarFlags;
extern int D_001A79F0[] __attribute__((sda));
typedef struct {
    u8 pad0[4];
    u8 enabled;           
    u8 pad5[0xE0 - 5];
} MaktarChoice;
extern MaktarChoice D_L02_00264A70[] __attribute__((section(".data")));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; void *ptr[0x980]; } Hero;
#define HERO ((Hero *)D_00189E20)
#define W(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
#define OBJ ((MaktarObj *)actor)

void func_PAL_L02_003FE328(char *actor) {
    MaktarState *st = OBJ->st;
    float f;
    float pos[4];
    char text[112];
    func_L00_003E4948(actor);
    D_L02_001A9010 = 1;
    D_001395B8[2] = D_001395B8[func_L02_003F9B70(0)] != 0;
    switch (OBJ->state) {
    case 0:
        func_L02_003FAF90(actor);
        func_L02_003FD070(actor);
        if (D_001A7904[0] == 2) {
            D_001A7904[0] = 0;
            func_002A7750(actor,2,-1);
            func_L00_003672F8();
            st->fade = D_001A65D2;
            func_L00_002E6CF0(func_L02_004002E0,actor);
            OBJ->timer = 26;
        }
        break;
    case 1:
        if (func_L00_003206B8(D_00189EA0,st->zone)) func_002A7750(actor,4,-1);
        else if (func_002ACBC8(D_00189EA0,st->trigger1)) {
            func_002B0C28(4,0xE61,1);
            func_PAL_L02_00403FA0(actor);
        } else if (D_001395B8[func_L02_003F9B70(0)] && func_L00_003206B8(D_00189EA0,st->trigger2)) {
            func_002B0C28(4,0xE61,1);
            func_PAL_L02_00403FA0(actor);
        }
        if (D_001A7904[0] == 2) {
            D_001A7904[0] = 0;
            func_002A7750(actor,2,-1);
            func_L00_003672F8();
            st->fade = D_001A65D2;
            func_L00_002E6CF0(func_L02_004002E0,actor);
            OBJ->timer = 26;
        }
        D_L02_001A9010 = 0;
        break;
    case 2: {
        char *a;
        if (func_002B3868(actor)) {
            func_L02_003FC268(actor,0); func_L02_003FC518(actor,0); OBJ->phase=0;
            break;
        }
        if (OBJ->phase==0) {
            if (OBJ->timer<26) {
                f=func_00283CE0(OBJ->timer)*0.05882353f;
                if (f<1.0f) f=func_00283CE0(OBJ->timer)*0.05882353f;
                else f=1.0f;
                D_L02_001B2FE0=f;
                break;
            }
            st->fade=D_001A65D2;
            func_L00_002E6CF0(func_L02_004002E0,actor);
            if (D_L02_001CAA80!=1) func_PAL_L00_00305110(1,st->music);
            a=D_L02_001B368C[0]+st->camera*128;
            func_PAL_L00_002B9CD8(a+0x30,a+0x70,0x6f,1);
            func_002DF3F8(D_00189EA0,D_00189EA0+0x10);
            func_L01_00323310(st->music,st->volume);
            *(TI128 *)pos=*(TI128 *)(D_L02_001B368C[0]+st->camera*128+0x30);
            pos[2]+=2.0f;
            func_00335438(pos,D_L02_001B368C[0]+st->camera*128+0x70,1,0,0);
            OBJ->phase=2;
        } else if (OBJ->phase==2) {
            func_L00_002E6CF0(func_L02_004002E0,actor);
            D_L02_001B2FE0=0;
            if (st->fade>0) break;
            if (!D_001395B8[5]) {
                D_001395B8[5]=1; OBJ->phase=1;
                func_L00_003294F0(D_L02_001B359C[0]+st->gate1*256,1);
                OBJ->timer=0;
                break;
            }
            goto beginApproach;
        } else if (OBJ->phase==1 && OBJ->timer>=51 && D_L02_001A8F00[0]!=2) {
        beginApproach:
            OBJ->phase=3;
            func_L00_002C8BA8(0);
            func_L00_002D40A0(func_L02_003FC098(actor),0,0.0f);
        } else if (OBJ->phase==3) {
            if (D_001395B8[func_L02_003F9B70(0)]) {
                if (func_00282E80(D_00189EA0,func_L02_003FC098(actor))<10.0f) func_002A7750(actor,4,-1);
                else if (OBJ->timer>=51) func_003355A8(2);
            } else {
                st->cls=0; st->wave=0;
                D_001395B8[0x3c]=st->result;
                func_002A7750(actor,8,-1);
                func_003355A8(2); func_L00_002C8BA8(0);
            }
        }
        break;
    }
    case 5:
        if (OBJ->timer<150) {
            func_L02_003FC268(actor,0); func_L02_003FC518(actor,0);
            HERO->f[0x24A4/4]=200.0f;
            func_PAL_L02_00400F20(actor); func_L00_002E6CF0(func_PAL_L02_004046D0,actor);
            break;
        }
    case 4:
        if (func_002B3868(actor)) {
            if (OBJ->state==5) func_PAL_L02_004013F8(actor,st->cls);
            func_L02_003FD070(actor); func_PAL_L02_004002E8(actor);
            func_L02_003FC268(actor,0); func_L02_003FC518(actor,0);
            func_PAL_L00_002B9CD8(func_L02_003FC098(actor),D_L02_001A8F20,0x6f,1);
            func_002DF3F8(D_00189EA0,D_00189EA0+0x10);
            func_PAL_L02_00401EC8(actor);
        }
        func_L02_003FD7C8(actor); HERO->f[0x24A4/4]=200.0f;
        break;
    case 10:
        if (OBJ->timer<300) {
            func_L02_003FC268(actor,0); func_L02_003FC518(actor,0);
            if (OBJ->timer>150) HERO->f[0x24A4/4]=200.0f;
            func_PAL_L02_00400F20(actor); func_L00_002E6CF0(func_PAL_L02_004046D0,actor);
            break;
        }
        func_002A7750(actor,4,-1);
        break;
    case 11:
        if (func_002B3868(actor)) { func_L02_003FC268(actor,0); func_L02_003FC518(actor,0); OBJ->phase=0; }
        if (!OBJ->phase) {
            if (OBJ->timer<150) {
                HERO->f[0x24A4/4]=200.0f;
                func_PAL_L02_00400F20(actor); func_L00_002E6CF0(func_PAL_L02_004046D0,actor);
            } else { func_L00_003294F0(D_L02_001B359C[0]+st->gate2*256,1); OBJ->phase=1; }
        } else if (D_0018C2EC>0 && D_L02_001A8F00[0]!=2 && OBJ->timer>=201) {
            OBJ->state=5; OBJ->flags&=0xfe;
        }
        break;
    case 6:
        if (func_002B3868(actor) && !D_001395B8[func_L02_003F9B70(st->cls)]) {
            switch(st->cls) {
            case 0: func_L02_00400650(actor,10); break;
            case 3: func_L02_00400650(actor,13); break;
            case 1: case 2: case 4: case 5: case 6: case 10: func_L02_00400650(actor,func_002A77E0(2)+11); break;
            }
        }
        func_PAL_L02_004042C0(actor);
        break;
    case 7: {
        int choice;
        if (func_002B3868(actor)) {
            choice=D_001395B8[0x3c];
            if (choice && (!D_001395B8[func_L02_003F9B70(W(D_L02_001B1190[choice],8))] ||
                           (choice>=12 && !func_00288D58()) ||
                           (choice==7 && !D_00139586[D_L02_00264A70].enabled) ||
                           (choice==8 && !D_00139592[D_L02_00264A70].enabled))) choice=0;
            st->result=choice;
            func_L02_00400650(actor,func_002A77E0(2));
        }
        func_PAL_L02_00402030(actor);
        break;
    }
    case 8: {
        char *row, *e;
        int n, spawned, allowed;
        func_L02_003F9B70(0);
        if (func_002B3868(actor)) {
            int i, k;
            char *row;
            st->wave=0;
            for(k=0;k<6;k++) st->counts[k]=0;
            st->frames=0; st->lost=0;
            func_L02_003FD070(actor); func_PAL_L02_003FF718(actor); func_PAL_L02_00401980(actor);
            row=P(D_L02_001B1190[st->cls],4);
            row+=st->wave*20;
            func_L02_003FC268(actor,H(row,10)); func_L02_003FC518(actor,H(row,8));
            for(i=39;i>=0;i--) st->marks[i]=0;
            for(i=0;i<4;i++) st->loadout[i]=D_L02_001B11C8[i];
            if (st->cls==7) { char *g=D_00189E20; D_00139700=300; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            else if(st->cls==8) { char *g=D_00189E20; D_00139730=8; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            if(st->cls==13) { char *g=D_00189E20; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            { char *g=D_00189E20; W(g,0x24cc)=D_001A79F0[4]; }
            func_PAL_L02_00405450();
        }
        func_PAL_L02_003FF858(actor);
        if (func_L02_003FCBF0(actor)) {
            int i, cls1;
            unsigned int cls3;
            char *row;
            st->wave++;
            for(i=5;i>=0;i--) st->counts[i]=0;
            st->lost=0;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
            cls1=st->cls;
            cls3=(u16)st->cls;
            st->owner=0;
            if(st->wave>=H(D_L02_001B1190[cls1],0)) {
                if(cls3-7U<2 || cls1==13) D_0018B6F4=D_L02_001B1224;
                func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                if(!st->cls && !D_001395B8[func_L02_003F9B70(0)]) func_002A7750(actor,11,-1);
                else func_002A7750(actor,5,-1);
                st->result=st->cls;
                return;
            }
            if(cls1>=14) st->cls=13;
            func_PAL_L02_00401980(actor);
            row=P(D_L02_001B1190[st->cls],4);
            row+=st->wave*20;
            func_L02_003FC268(actor,H(row,10)); func_L02_003FC518(actor,H(row,8));
        }
        n=++st->frames;
        if((st->cls==3 && n>=1501) || (st->cls==5 && n>=3001)) {
            char *format, *buffer, *a, *b;
            int sum=0, j, count;
            buffer=text;
            for(j=0;j<6;j++) sum+=st->counts[j];
            format=D_L02_001B1228;
            a=func_00288FB8(0x1B37);
            count=st->wave*15+sum-st->lost;
            b=func_00288FB8(0xE86);
            func_00115DA8(buffer,format,a,count,b);
            func_PAL_L00_0030FBC0(buffer,-1);
            func_002A7750(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
            return;
        }
        if(st->cls==7 && D_0018B068==30 && D_00139700<=0) {
            allowed=1;
            for(e=D_L02_001B35A8[0];e;e=P(e,0x28)) {
                if(B(e,0x20)==0xfe) continue;
                if(B(e,0x20)==0xfd) continue;
                if(H(e,0xaa)==0xc89 || H(e,0xaa)==0xbfe) allowed=0;
            }
            if(allowed) {
                func_PAL_L00_0030FBC0(func_00288FB8(0x1B39),-1);
                func_002A7750(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
        } else if(st->cls==8 && D_0018B068==42 && D_00139730<=0) {
            allowed=1;
            for(e=D_L02_001B35A8[0];e;e=P(e,0x28)) {
                if(B(e,0x20)==0xfe) continue;
                if(B(e,0x20)==0xfd) continue;
                if((unsigned short)(U(e,0xaa)-0xc06)<=1) allowed=0;
            }
            if(allowed) {
                func_PAL_L00_0030FBC0(func_00288FB8(0x1B3A),-1);
                func_002A7750(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
        } else if(st->cls==12) {
            if(D_0018C2EC<D_001A79F0[4]) {
                { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                func_PAL_L00_0030FBC0(func_00288FB8(0x1B38),-1);
                func_002A7750(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
            if(st->frames>=6001) {
                func_L01_003E9CF8(st->owner,0,func_L02_003D4900);
                { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                func_002A7750(actor,5,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
        } else if(st->cls==13 && D_0018C2EC<D_001A79F0[4]) {
            func_PAL_L00_0030FBC0(func_00288FB8(0x1B38),-1);
            func_002A7750(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
            return;
        }
        func_L00_002E6CF0(func_L02_003FE8B8,actor);
        row=P(D_L02_001B1190[st->cls],4)+st->wave*20;
        if(OBJ->timer<51 && !U(row,16)) goto spawn;
        func_L02_003FBAD0(actor); spawned=0; func_L02_003FB7E0(actor);
        if(st->slots[st->slot] && func_L02_003D77B8(st->slots[st->slot])) {
            int i;
            for(i=st->counts[3];i<H(row,6);i++) spawned|=func_L02_003FB4D8(actor,0xc3e);
            for(i=st->counts[1];i<H(row,2);i++) spawned|=func_L02_003FB4D8(actor,0xb22);
            for(i=st->counts[2];i<H(row,4);i++) spawned|=func_L02_003FB4D8(actor,0xc3b);
            for(i=st->counts[0];i<H(row,0);i++) spawned|=func_L02_003FB4D8(actor,0x9ca);
        }
        if(!st->counts[4] && B(row,16) && !st->counts[5] && B(row,17)) {
            char *a, *b;
            a=func_L02_003FB5A0(actor,0x9f8,0); b=func_L02_003FB5A0(actor,0xa44,1);
            func_L02_003D4980(a,b); func_L02_003DB870(b,a); func_L02_003D4990(a); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            if(!D_L02_001B3770[0]) { D_L02_001B3770[0]=a; func_00282A60(D_L02_001FF6B8,0,224); }
            if(!D_L02_001B3770[1]) { char *buf=D_L02_001FF6B8; D_L02_001B3770[1]=b; func_00282A60(buf+224,0,224); }
            func_L02_00400650(actor,15); func_L01_00323310(st->track,st->trackVolume);
        } else if(!st->counts[4] && B(row,16)) {
            char *a;
            a=func_L02_003FB5A0(actor,0x9f8,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!D_L02_001B3770[0]) { D_L02_001B3770[0]=snd; func_00282A60(D_L02_001FF6B8,0,224); } }
            func_L02_00400650(actor,14); func_L01_00323310(st->track,st->trackVolume);
        } else if(!st->counts[5] && B(row,17)) {
            char *a;
            a=func_L02_003FB5A0(actor,0xa44,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!D_L02_001B3770[1]) { char *buf=D_L02_001FF6B8; D_L02_001B3770[1]=snd; func_00282A60(buf+224,0,224); } }
            func_L02_00400650(actor,20); func_L01_00323310(st->track,st->trackVolume);
        }
        if(!U(row,16)) { char *g=D_001A63A8; if(B(g,0x48)!=st->music && B(g,0x3c)!=st->music) func_L01_00323310(st->music,st->volume); }
        if(spawned) func_L02_003FBA58(actor);
    spawn:
        if(st->cls==7) func_002AD860(30);
        else if(st->cls==8) func_002AD860(42);
        else if(st->cls==13) { func_002AD860(10); D_0018C0D7=1; }
        func_PAL_L02_00401118(actor); func_L02_00400948(actor);
        if(!(D_001A7BC0[0]&3)) func_L02_003FBCF8(actor);
        func_PAL_L02_00400F20(actor); func_L00_002E6CF0(func_PAL_L02_004046D0,actor);
        if(func_L02_003F9AF0(st->cls)!=-1) {
            D_L02_001AA1B0[0]=func_L02_003F9AF0(st->cls); D_L02_001B3680[0]=D_001A7390[0];
        }
        break;
    }
    }
    func_PAL_L02_003FF640(actor);
}
