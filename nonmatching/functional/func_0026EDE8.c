/* functional: high. Unchecked: the title/front-end loop does not return within the gate's budget (it waits on the disc, plays the attract movie and runs menu frames until D_001A8B84 is set). Read against all 585 retail instructions (0x26EDE8-0x26F708) and the 8-entry state jump table at 0x26C4F0 (-1/0 title, 1 load screen, 3, 4, 6; 2, 5 and others -> func_00282A28): every callee, argument, data address (lui/addiu or $gp), constant (0x400000, 475, 119/61, 0xFFFF0FFF, 1800, 178, 512x416, 1/9600 and 1/11520), loop count (30/45/25 frame waits, six tables) and delay-slot store (D_001A8C88, D_001B1684, D_001B1598, D_001A7478, the movie's sequence pointer, D_001B168C) agree. From the near-miss draft nonmatching/game/func_0026EDE8.c (2340/2340 bytes, register roles differ): its accessor inlines (matching contrivance) are written as plain reads of D_001393E0, and func_0029D4D0 and func_002FCB00 are declared as the port's host routines define them (int game addresses). */
/* func_0026EDE8 (2340 bytes): the executable's own loop (the port's TITLE_LOOP): starts the disc read of the boot archive, waits for the loader (D_001393E0) while drawing the loading screens, unpacks the archive (tables, bank, screens), then runs front-end frames by state D_001A8BB0 until D_001A8B84; finally restores the sound settings. */
#include "common.h"
#define WORD(p,o) (*(int *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
#define PTR(p,o) (*(char **)((char *)(p)+(o)))
typedef struct { char *data; int words[3]; } LoaderResource;
typedef struct { int code, count, data, size; } LoaderBank;
typedef struct { int offsets[0x64/4]; } LoaderArchive;
typedef struct { char pad[0x18]; LoaderArchive *archive; } LoaderMemory;
typedef struct { char pad[0x32C]; int base; char pad330[0x20]; int offset, count; } LoaderDisc;
typedef struct {
    char pad[8]; int state, frames, unused10, active;
    short result; char pad1a[0x142]; int status, unused160, request, progress;
} LoaderState;
typedef struct { char pad[0x1A0]; unsigned int pressed; } LoaderPad;
extern LoaderMemory D_001BAEC0;
extern LoaderDisc D_0014B540;
extern char D_001393E0[];
#define LS ((LoaderState *)D_001393E0)
extern LoaderPad D_00138180;
typedef struct { char pad[0x2C]; int count; } LoaderTables;
typedef struct { char pad[0x24CC]; int enabled; } LoaderGame;
typedef struct { char pad[7]; char flag; } LoaderSound;
typedef struct { int active; short *sequence; } LoaderMovie;
typedef struct { char pad[10]; unsigned char index; } LoaderSelection;
typedef struct { char pad[4]; unsigned char mode; char rest[219]; } LoaderOption;
typedef struct { char pad[0x18]; int format; char pad1c[0x14]; int audio; } LoaderSettings;
extern LoaderTables D_00254E78;
extern LoaderGame D_00189E20;
extern LoaderSound D_001A63A8;
extern LoaderMovie D_001BAD40;
extern LoaderSelection D_00139568;
extern LoaderOption D_00239BA0[];
extern LoaderSettings D_00152C00;
extern char *D_001B1604 __attribute__((sda));
extern char D_00238C80[], D_01806380[], D_0180DA80[];
extern int D_001A8C88[] __attribute__((sda));
extern LoaderResource *D_001B1840[] __attribute__((sda));
extern LoaderArchive *D_001A7288[] __attribute__((sda));
extern int D_001A7478 MACRO_ADDR;
extern int D_001B16A8[] __attribute__((sda)), D_001B16AC[] __attribute__((sda)), D_001A8BB8[] __attribute__((sda)), D_001A8BBC[] __attribute__((sda)), D_001A8BB0[] __attribute__((sda)), D_001A8BB4[] __attribute__((sda)), D_001A8B84[] __attribute__((sda)), D_001B1684[] __attribute__((sda)), D_001B1598[] __attribute__((sda));
extern int D_00138320[];
extern unsigned char D_001A7BB4[] __attribute__((sda));
extern short D_001A7A18[] __attribute__((sda));
extern int D_001A7290[] __attribute__((sda)), D_001A72C0[] __attribute__((sda)), D_001A7AF0[] __attribute__((sda)), D_001A7B90[] __attribute__((sda)), D_001A72DC[] __attribute__((sda));
extern unsigned short D_001A7AF2[] __attribute__((sda));
extern unsigned long long D_001A7200[] __attribute__((sda));
extern float D_001B168C MACRO_ADDR;
extern int func_001261F0(int);
extern void func_00290C60(void),func_00298F00(void),func_00298178(void),func_002B9000(void),func_00290758(void);
extern int func_002B7B18(void *,int,int);
/* The port's host routines (host/wad.c, host/picture.c) take game addresses as int. */
extern int func_0029D4D0(int,int);
extern long long func_002FCB00(int,int,int,int);
extern void func_0026EAC8(int),func_0027D330(int),func_002B7CE0(int),func_0011AEA0(int),func_002EED08(void),func_0026EA00(void *),func_00292888(void),func_002B67E0(void *,int),func_00291DE0(void *,int);
extern void func_00294F10(void),func_0028AB70(void),func_0029CD48(void),func_002C9C20(void),func_00284E80(void),func_00133220(void),func_00288AA0(void *,int),func_00288BE8(void *),func_002B4C18(void);
extern void func_00280710(void),func_002FC280(void),func_002FC220(void),func_00284FC0(void),func_00285338(void),func_00284EA8(void),func_00132028(void);
extern void func_0026EC58(unsigned short *),func_002B49E0(int,int,int,int,int),func_002F5FB8(void),func_002CA8A8(void),func_0027C520(void),func_002B4B70(int,int),func_00286738(void),func_0027C4A8(void),func_002E9268(void),func_002EA8E8(void),func_00282A28(void),func_002FC3C0(int),func_0027B948(void),func_00292078(int),func_00292408(int),func_002926B8(int),func_002925F0(int),func_002EC408(void);
extern float func_00283CE0(int);
void func_0026EDE8(void)
{
    LoaderResource *tables[8];
    int counts[8];
    short sequence[32];
    int frames=0, loaded=0, state;
    LoaderArchive *archive;
    char *image,*extra;
    float time;
    D_001A8C88[0]=1;
    func_00290C60();
    { LoaderMemory *memory = &D_001BAEC0;
      LoaderDisc *disc = &D_0014B540;
      func_002B7B18((char *)memory->archive+0x400000, disc->offset+disc->base, disc->count);
    }
    while (LS->status==2 && LS->request<0) {
        func_00298F00();func_00298178();func_001261F0(0);
    }
    while (LS->status!=2 || LS->request>=0) {
        func_00298F00();func_00298178();func_001261F0(0);
    }
    {
    int st;
    st = LS->state;
    for (;;) {
        if (!(st!=2 || (LS->active!=0 && LS->result<-1 && LS->frames<475))) break;
        loaded=1;
        if (LS->status<3 && LS->request<0) {
            if (LS->state!=2) func_0026EAC8((int)D_01806380);
            else if (LS->result!=-4) func_0026EAC8((int)D_0180DA80);
            if (LS->request<0) {
                LS->progress=0;
                LS->request=7;
            }
        }
        func_002B9000();func_00298F00();func_00298178();
        if(frames<=119) frames++;
        func_001261F0(0);
        if(frames>=61 && (D_00138180.pressed&0xFFFF0FFF)) break;
        st = LS->state;
    }
    }
    func_00290758();
    if(loaded) {func_0027D330(5);{int i; for(i=29;i>=0;i--)func_001261F0(0);}}
    { LoaderMemory *memory = &D_001BAEC0;
    func_002B7CE0(1);func_0011AEA0(0);
    func_0029D4D0((int)memory->archive+0x400000,(int)memory->archive);
    func_0011AEA0(0);func_002EED08();
    archive=memory->archive;
    func_0026EA00((char *)(archive->offsets[0x50/4]+(int)archive));
    D_001A7288[0]=memory->archive;
    func_00292888();func_002B67E0((char *)(WORD(archive,8)+(int)archive),0);
    { LoaderBank *bank=(LoaderBank *)(archive->offsets[0]+(int)archive);
      D_001B1604=(char *)bank+bank->code+bank->size;
      func_00291DE0((char *)bank+bank->data,bank->count);
    }
    }
    {int i,j; for(i=0;i<6;i++) {
        int *table=(int *)(archive->offsets[0x48/4]+(int)archive);
        int *part=(int *)(table[i]+(int)table);
        int count=part[0];
        tables[i]=(LoaderResource *)(part+2);counts[i]=count;
        for(j=0;j<counts[i];j++) tables[i][j].data+=(int)tables[i]-8;
    }
    }
    D_00254E78.count=counts[D_001A7BB4[0]];D_001B1840[0]=tables[D_001A7BB4[0]];
    image=(char *)(WORD(archive,0x10)+(int)archive);extra=(char *)(WORD(archive,0x60)+(int)archive);
    {int i; for(i=44;i>=0;i--)func_001261F0(0);}
    func_0027D330(30);{int i; for(i=29;i>=0;i--)func_001261F0(0);}
    func_0026EA00((char *)(WORD(archive,0x58)+(int)archive));
    D_00189E20.enabled=1;D_001B16A8[0]=20;D_001B16AC[0]=(int)D_00238C80;
    D_001A63A8.flag=0;D_001A8BB8[0]=-2;D_001A8BBC[0]=20;D_001A8BB0[0]=0;D_001A8BB4[0]=0;D_001B1684[0]=0;
    func_00294F10();func_0028AB70();func_0029CD48();func_002C9C20();
    {int i; for(i=24;i>=0;i--)func_001261F0(0);}
    func_0027D330(30);frames=1800;D_001B1598[0]=0;func_001261F0(0);
    func_00284E80();func_00133220();D_001A7478=3;
    func_00288AA0(&D_001BAD40,0xB2);func_00288BE8(&D_001BAD40);func_002B4C18();
    while(!D_001A8B84[0]) {
        D_001B1840[0]=tables[D_001A7BB4[0]];D_00254E78.count=counts[D_001A7BB4[0]];
        D_001A7200[0]+=*(volatile unsigned int *)0x10000800;
        *(volatile unsigned int *)0x10000800=0;
        func_00280710();func_002FC280();func_002FC220();func_00284FC0();func_00285338();func_00284EA8();func_00132028();
        state=D_001A8BB0[0];
        switch(state) {
        case -1: case 0:
            if(D_001A8BB4[0]==3 || frames>=1800) {
                frames=0;func_0026EC58((unsigned short *)sequence);D_001BAD40.active=1;D_001A7478=2;
                D_001BAD40.sequence=sequence;func_00288AA0(&D_001BAD40,sequence[1]);func_00288BE8(&D_001BAD40);
            } else {
                func_002FCB00((int)(image+0x10),D_001A72DC[0],512,416);func_002B49E0(3,1,6,0,0);
            }
            break;
        case 1:
            func_002F5FB8();
            if(extra) {func_0026EA00(extra);{int i; for(i=29;i>=0;i--)func_001261F0(0);}func_0027D330(30);extra=0;}
            break;
        case 3:
            frames++;func_002B9000();if(D_00138320[0])frames=0;func_002CA8A8();func_0027C520();
            if(frames>=1800) {frames=0;func_002B4B70(0,0);}break;
        case 4:func_002B9000();func_00286738();func_0027C4A8();break;
        case 6:func_002B9000();func_002E9268();func_002EA8E8();break;
        default:func_00282A28();break;
        }
        if(D_001A8BB0[0]!=state)D_001B1684[0]=0;else D_001B1684[0]++;
        func_00298F00();func_00298178();func_002FC3C0(1);
        time=func_00283CE0(*(volatile unsigned int *)0x10000800);
        D_001B168C=time*(D_001A7B90[0]?0.0000868055578f:0.000104166669f);
        func_0027B948();func_002B4C18();D_001B1598[0]++;func_001261F0(0);
    }
    if(D_001A7290[0]!=D_001A7A18[0])func_00292078(D_001A7A18[0]);
    {int i; i=D_00239BA0[D_00139568.index].mode;
    if(D_001A72C0[0]!=i)func_00292408(i);
    i=D_001A7AF2[0]&31;
    if(D_00152C00.audio!=i)func_002926B8(i);
    if(D_00152C00.format!=(D_001A7AF0[0]&3))func_002925F0(D_001A7AF0[0]&3);
    }
    func_002EC408();
}
