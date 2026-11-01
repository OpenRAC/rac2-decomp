#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct Moby_003BF9B0 Moby_003BF9B0;
typedef struct {
    u8 reserved_00[0x18]; u8 enabled,count,kind;
    u8 reserved_1b[0x65]; u8 payload[1];
} Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext;
typedef struct {
    u8 pad_000[0x26];
    short f26;
    u8 pad_028[0x10];
    char * f38;
    u8 pad_03C[0xD4];
    short f110;
    u8 pad_112[0x62];
    float f174;
    unsigned short f178;
    u8 pad_17A[0xD6];
    int f250;
    u8 pad_254[0x1C];
    float f270;
    u8 pad_274[0x8];
    float f27C;
    u8 pad_280[0x20];
    char * f2A0;
    short f2A4;
    short f2A6;
    float f2A8;
    u8 pad_2AC[0x74];
    char * f320;
    short f324;
    short f326;
    char * f328;
    char * f32C;
    u8 pad_330[0x84];
    int f3B4;
    float f3B8;
    short f3BC;
    short f3BE;
} DispatchState;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
extern int D_L23_001B1424,D_L23_001B36F0;
extern u8 *D_L23_001B36B0;
typedef struct { u8 pad00[0x80]; float position[4] __attribute__((aligned(16))); u8 pad90[0x2200]; u8 *object; } DispatchHero;
extern DispatchHero D_00189E20;
extern u8 *D_0018C0B0 __attribute__((nosda));
extern float D_L23_001B36A4,D_L23_001B36F4,D_L23_001B36F8;
extern float D_L23_001B36D0[4] __attribute__((aligned(16))) MACRO_ADDR;
extern float D_L23_001C0AA0[] __attribute__((aligned(16)));
extern u8 D_00189F00[];
extern float D_L23_001B3708;
extern float D_L23_001AFA14 __attribute__((sda));
extern int D_L23_001AFA38 __attribute__((sda));
extern float D_L23_001AFA4C __attribute__((sda));
extern float D_L23_001AFA58 __attribute__((sda));
extern float D_L23_001AFA5C __attribute__((sda));
extern float D_L23_001AFA60 __attribute__((sda));
extern float D_L23_001AFA6C __attribute__((sda));
extern float D_L23_001AFA78 __attribute__((sda));
extern float D_L23_001AFA80 __attribute__((sda));
extern float D_L23_001AFA88 __attribute__((sda));
extern float D_L23_001AFA8C __attribute__((sda));
extern float D_L23_001AFA90 __attribute__((sda));
extern int D_L23_001AFA94 __attribute__((sda));
extern int D_L23_001AFA98 __attribute__((sda));
extern int D_L23_001AFA9C __attribute__((sda));
extern void func_L23_003BF9B0(Moby_003BF9B0 *);
extern int func_L23_0041E548(void),func_L23_0041E418(void);
extern int func_002A90C8(int,int,int,int,float);
extern void func_002A8F70(int,int,int,int,int,float);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern u8 *func_0032C700(void *,int,int,int,int,int,int,int,float,float,int,int,int,void *);
extern void func_L23_003C1960(char *),func_L23_003C1988(char *);
extern void func_L23_003C0028(char *),func_L23_003C00D0(char *);
extern void func_L23_003C1B58(char *),func_L23_003C1AE8(char *);
extern void func_L23_003C16D8(char *),func_L23_003BFE38(char *);
extern void func_L23_003C1E88(void *);
extern void func_L23_003C01F8(char *,int);
extern void func_L23_003C02C8(u8 *);
extern float func_002B0360(char *);
extern void func_00282CF0(void *,void *,void *);
extern float func_L02_00329C48(char *,Quad *,char *);
extern float func_00282E48(void *,void *),func_00282DF0(void *);
extern int func_L23_003C0A60(void *,void *,void *);
extern void func_L23_00418650(char *,float);
extern unsigned long func_002B1C20(void *,Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *);
extern void func_002E59F8(int);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float),func_00282D30(void *,void *,float);
extern int func_002E5DA0(int,int,char *,int);
extern void func_L22_003A3C70(int,int);
extern int func_002B3868(u8 *),func_002B3890(u8 *);
extern int func_L00_0035F5A0(int,int,int);
extern void func_L23_003BFFC0(char *,int,int,int,int,float);
extern void func_L23_003BFE90(char *,float,int,int);
extern void func_002A7750(u8 *,s32,int);
extern void func_L00_002E6CF0(void (*)(void *),void *);
extern int func_L11_003404E0(char *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_0029F530(char *),func_002A7878(float,float);
extern int func_US2_002AF9C8(char *,float);
extern void *func_L23_004256F0(u8 *,u8 *,u8 *,u8,u8,float,float,float,float,short,short,int,int,int,int,int);
extern void func_0029FCC0(char *,int,char *);
extern int func_L00_002D6900(unsigned int);

void func_US2_L23_003BFE40(u8 *object)
{
    float difference[4] __attribute__((aligned(16))),point[4] __attribute__((aligned(16))),local[4] __attribute__((aligned(16)));
    char *state=*(char **)(object+0x68);
    int facing,selected,index,mask;
    unsigned long flags;
    float distance,range;
    func_L23_003BF9B0((Moby_003BF9B0 *)object);
    if (D_L23_001B1424>200) return;
    if (func_L23_0041E548())
        func_002A90C8((int)object,(int)object,0x10000,(int)(object+0x10),(float)D_L23_001B36F0);
    selected=D_L23_001B36B0==object;
    facing=0;
    ((DispatchState *)state)->f326=0;
    if (selected && (unsigned int)(object[0x20]-9)>2)
        func_L23_003C1960((char *)object);
    if (object[0x20]!=13) {
        ((DispatchState *)state)->f270=func_002B0360((char *)object+0x10);
        func_00282CF0(difference,D_00189E20.position,object+0x10);
        if (func_L02_00329C48((char *)object,(Quad *)difference,0)<=0.7853982f) facing=1;
        distance=func_00282E48(D_00189E20.position,object+0x10);
        range=D_L23_001AFA6C;
        ((DispatchState *)state)->f27C=distance;
        ((DispatchState *)state)->f324=0;
        if (distance<range)
            ((DispatchState *)state)->f324=func_L23_003C0A60(object,object+0x10,D_00189E20.position);
        qcopy((state+0x300), (object+0x10));
        func_L23_00418650(state+0x300,0.0f);
    }
    if (object[0x95]==3) {
        flags=func_002B1C20(object,(Rac2Native_bf55aa2a4d0dd351_SDataCallDispatchContext *)(state+0x140));
        if (((DispatchState *)state)->f3B4!=-1) {
            func_002E59F8(((DispatchState *)state)->f3B4); ((DispatchState *)state)->f3B4=-1;
        }
        if (object[0x43]==8 && func_00282DF0(state+0x1C0)>0.0f) {
            if (((DispatchState *)state)->f270<D_L23_001B36A4) func_L23_00418650((char *)object+0x10,0.0f);
            *(Quad *)local=0; local[2]=((DispatchState *)state)->f174;
            *(Quad *)point=*(Quad *)local;
            func_00283098(point,point,object+0xC0);
            func_00282CC0(point,point,object+0x10);
            func_00282F20(difference,state+0x1C0,4.0f);
            func_00282CC0(point,point,difference);
            func_002A8C28(object,point,0x90000,0,1,0,5.0f,100.0f,0.0f);
        }
        if ((((DispatchState *)state)->f178&1) && ((DispatchState *)state)->f2A4==0) {
            func_002E5DA0(5,0,(char *)object,0x7E5);
            func_0032C700(((DispatchState *)state)->f2A0+0x10,1,35,20,20,20,45,1,2.5f,20.0f,1,0,0,0);
            ((DispatchState *)state)->f2A4=1;
            if (((DispatchState *)state)->f38==(char *)D_00189E20.object) {
                qcopy(difference, (object+0x10));
                func_L23_00418650((char *)difference,0.0f);
                index=func_L23_0041E418();
                if (index!=-1) func_L22_003A3C70((int)D_00189E20.position,index);
            }
            qcopy((object+0x10), D_00189E20.position);
            func_L23_00418650((char *)object+0x10,(-D_L23_001B36A4)*2.0f);
        }
        if ((flags & 1UL) == 1UL) func_L23_003C0028((char *)object);
        else if (func_002B3868(object) && object[0x43]==8) {
            func_L00_0035F5A0(31,0,0);
            func_L23_003BFFC0((char *)object,8,0,4,2,1.0f);
            ((DispatchState *)state)->f26=25; ((DispatchState *)state)->f2A6=0;
            func_0032C700(((DispatchState *)state)->f2A0+0x10,0,10,15,15,15,15,0,1.0f,20.0f,0,0,0,0);
        } else if ((flags & 2UL) == 2UL) func_002A7750(object,5,0);
    }
    switch (object[0x20]) {
    case 5:
        if (func_002B3890(object)) {
            func_L23_003BFFC0((char *)object,3,0,4,3,1.0f);
            if (((DispatchState *)state)->f3B4!=-1) { func_002E59F8(((DispatchState *)state)->f3B4); ((DispatchState *)state)->f3B4=-1; }
        }
        if (U(object,0x96)>8) func_002A7750(object,7,1);
        else if (U(object,0x96)>=11) {
            mask=0;
            if (object[0x43]!=3) mask|=1;
            if (((u8 *)((DispatchState *)state)->f2A0)[0x43]!=3) mask|=2;
            if (mask) func_L23_003BFFC0((char *)object,3,0,20,mask,1.0f);
            func_L11_003404E0((char *)object);
        }
        break;
    case 1:
        if (func_002B3890(object)) func_L23_003C00D0((char *)object);
        else if (U(object,0x96)>=6) func_002A7750(object,3,0);
        break;
    case 2:
        I(object,0x98)=0;
        if (func_002B3890(object)) {
            func_L23_003C00D0((char *)object);
            func_L23_003BFFC0((char *)object,9,0,0,1,1.0f);
            func_L23_003BFFC0((char *)object,1,0,0,2,1.0f);
            func_L23_003C01F8((char *)object,1);
            ((DispatchState *)state)->f3BC=1; ((DispatchState *)state)->f3B8=(float)D_L23_001AFA38;
        }
        func_L00_002E6CF0(func_L23_003C1E88,object);
        break;
    case 6:
        func_L23_003C1B58((char *)object); break;
    case 3:
        if (func_002B3890(object) && object[0x43]!=1)
            func_L23_003BFFC0((char *)object,1,0,4,3,1.0f);
        func_L11_003404E0((char *)object);
        if (((DispatchState *)state)->f110) {
            func_002A7750(object,5,0);
            func_L23_003BFFC0((char *)object,3,0,10,3,1.0f);
        } else {
            func_00282D30(point,object+0xE0,-3.0f);
            func_00282CC0(point,point,object+0x10);
            func_00282D30(difference,object+0xE0,0.2f);
            func_00282CC0(difference,difference,object+0x10);
            if (func_002761F8(difference,point,18,0,0) && func_00282E48(D_L23_001C0AA0,object+0x10)<4.0f)
                func_002A7750(object,4,0);
        }
        break;
    case 4:
        if (func_002B3890(object) && object[0x43]!=2)
            func_L23_003BFFC0((char *)object,2,0,6,3,1.0f);
        else if ((object[0x60]&2) || func_0029F530((char *)object)>12.0f) {
            func_002A7750(object,5,0);
            func_L23_003BFFC0((char *)object,3,0,20,3,1.0f);
        }
        func_L11_003404E0((char *)object);
        break;
    case 7:
        if (func_002B3890(object)) {
            ((DispatchState *)state)->f250=200;
            ((DispatchState *)state)->f2A8=D_L23_001AFA58+func_002A7878(0.0f,D_L23_001AFA58*0.5f);
            ((DispatchState *)state)->f320=(char *)D_00189E20.position;
        }
        if (!object[0x31]) ((DispatchState *)state)->f2A8=D_L23_001AFA60;
        else if (((DispatchState *)state)->f2A8==D_L23_001AFA60)
            ((DispatchState *)state)->f2A8=D_L23_001AFA58+func_002A7878(0.0f,D_L23_001AFA58*0.5f);
        if (((DispatchState *)state)->f250==0) func_002A7750(object,5,0);
        else if (((DispatchState *)state)->f324 && facing && ((DispatchState *)state)->f27C<D_L23_001AFA78)
            func_002A7750(object,8,2);
        else func_L23_003C02C8(object);
        break;
    case 8:
        if (func_002B3868(object)) ((DispatchState *)state)->f2A8=D_L23_001AFA58+func_002A7878(0.0f,D_L23_001AFA58*0.5f);
        if (((u8 *)((DispatchState *)state)->f2A0)[0x43]!=4) {
            func_L23_003BFFC0((char *)object,4,0,10,2,1.0f);
            F(((DispatchState *)state)->f2A0,0x48)=D_L23_001B3708;
        }
        if (!((DispatchState *)state)->f324 || ((DispatchState *)state)->f27C>D_L23_001AFA80) {
            func_002A7750(object,5,0); ((DispatchState *)state)->f250=0;
        } else if (((DispatchState *)state)->f27C>D_L23_001AFA88 ||
                   ((unsigned int)(object[0x43]-5)<2 && ((DispatchState *)state)->f27C>D_L23_001AFA88-2.0f)) {
            ((DispatchState *)state)->f320=(char *)D_00189E20.position; func_L23_003C02C8(object);
        } else {
            func_L23_003BFFC0((char *)object,3,0,10,1,1.0f); func_L11_003404E0((char *)object);
        }
        if (func_US2_002AF9C8(((DispatchState *)state)->f2A0,28.0f)) func_L23_003BFE90((char *)object,D_L23_001B36F4+D_L23_001B36F4,(int)D_00189F00,0);
        else if (func_US2_002AF9C8(((DispatchState *)state)->f2A0,14.0f)) func_L23_003BFE90((char *)object,D_L23_001B36F4+D_L23_001B36F4,(int)D_00189F00,1);
        break;
    case 9:
        if (func_002B3868(object)) {
            func_L23_003BFFC0((char *)object,6,0,12,1,D_L23_001AFA14);
            func_L23_003BFFC0((char *)object,8,0,12,2,4.0f);
            func_L23_003C1988((char *)object);
            ((DispatchState *)state)->f328=func_L23_004256F0((u8 *)state+0x330,object,(u8 *)state+0x340,50,70,0.7f,0.85f,0.5f,1.2f,30,5,0x7F7F7F,0x7F7F7F,0,-1,0);
            ((DispatchState *)state)->f32C=func_L23_004256F0((u8 *)state+0x330,object,(u8 *)state+0x340,50,70,1.9f,2.05f,0.5f,1.2f,10,2,0x3F00000,0x3F0000,0,-1,0);
            ((DispatchState *)state)->f2A8=D_L23_001AFA5C;
            ((DispatchState *)state)->f3B4=func_002E5DA0(4,4,(char *)object,0x7E5);
        }
        if (!((DispatchState *)state)->f324 || ((DispatchState *)state)->f27C>D_L23_001AFA80) {
            func_002A7750(object,5,0); ((DispatchState *)state)->f250=0; break;
        }
        func_0029FCC0(((DispatchState *)state)->f2A0,1,state+0x330);
        func_0029FCC0(((DispatchState *)state)->f2A0,0,state+0x340);
        if ((int)U(object,0x96)>D_L23_001AFA94) {
            ((DispatchState *)state)->f320=(char *)D_00189E20.position;
            if (((DispatchState *)state)->f27C<D_L23_001AFA8C) func_002A7750(object,10,2);
            func_L23_003C02C8(object);
        }
        break;
    case 10:
        if (!((DispatchState *)state)->f324 || ((DispatchState *)state)->f27C>D_L23_001AFA90) { func_002A7750(object,5,0); break; }
        func_0029FCC0(((DispatchState *)state)->f2A0,1,state+0x330);
        func_0029FCC0(((DispatchState *)state)->f2A0,0,state+0x340);
        if (func_002B3868(object)) {
            func_L23_003C1988((char *)object);
            ((DispatchState *)state)->f328=func_L23_004256F0((u8 *)state+0x330,object,(u8 *)D_L23_001B36D0,95,80,4.0f,4.25f,0.7f,1.3f,35,5,0x5F0000,0x5F2020,0,-1,0);
            ((DispatchState *)state)->f32C=func_L23_004256F0((u8 *)state+0x340,object,(u8 *)D_L23_001B36D0,95,80,4.0f,4.25f,0.7f,1.3f,35,5,0x5F0000,0x5F2020,0,-1,0);
            break;
        }
        if ((int)U(object,0x96)<=D_L23_001AFA98) break;
        func_00282CC0(difference,state+0x330,state+0x340);
        func_00282D30(difference,difference,0.5f);
        if (func_00282E48(difference,D_L23_001B36D0)<D_L23_001AFA4C) {
            func_00282F20(point,((DispatchState *)state)->f2A0+0xE0,0.25f);
            func_00282CC0(point,point,((DispatchState *)state)->f2A0+0xC0);
            func_00282D30(point,point,15.0f); point[3]=5627.9248f;
            func_002A8F70((int)D_0018C0B0,(int)object,0x10007,(int)(object+0x10),(int)point,D_L23_001B36F8);
            func_L00_002D6900(43);
            func_0032C700(D_L23_001B36D0,1,10,10,10,10,45,0,1.2f,20.0f,0,1,0,0);
            ((DispatchState *)state)->f3BE=1;
        }
        func_002A7750(object,11,2);
        break;
    case 11:
        if (func_002B3868(object)) {
            if (((DispatchState *)state)->f3B4!=-1) { func_002E59F8(((DispatchState *)state)->f3B4); ((DispatchState *)state)->f3B4=-1; }
        } else if ((int)U(object,0x96)>D_L23_001AFA9C) { func_L23_003C1960((char *)object); func_002A7750(object,5,0); } else {
            if ((int)U(object,0x96)>=D_L23_001AFA9C-5 && ((DispatchState *)state)->f3BE) {
                func_L00_0035F5A0(29,0,0); ((DispatchState *)state)->f3BE=0; func_L00_002D6900(43);
            }
        }
        break;
    case 12:
    case 13:
        break;
    }
    func_L23_003BFE38((char *)object);
    if (object[0x20]!=13) { func_L23_003C16D8((char *)object); func_L23_003C1AE8((char *)object); }
}
