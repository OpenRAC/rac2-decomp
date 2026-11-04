#include "common.h"
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
typedef struct { int first,second,third; } AllocationOffsets;
typedef struct { void *data; int first,second; float cooldown; int timer; void *target,*previous; short acquire,release; } WeaponContext;
typedef struct HeroView {
char pad0[1180];
unsigned char field49c;
char pad49d[1935];
int fieldc2c;
char padc30[1536];
int field1230;
char pad1234[12];
int field1240;
char pad1244[700];
int field1500;
char pad1504[3468];
unsigned char * field2290;
int field2294;
char pad2298[4];
int field229c;
char pad22a0[528];
int field24b0;
char pad24b4[128];
int field2534;
} HeroView;
extern HeroView D_00189E20;
extern unsigned int D_00138320;
extern unsigned char D_0013957E;
typedef struct { char pad[0x54]; float rate; char rest[0x88]; } WeaponEntry;
extern WeaponEntry D_L00_00262570[];
extern void func_L00_003B6158(void *), func_L00_003B60E8(void);
extern int func_L00_002D4040(int);
extern void func_00273318(void *,float,unsigned int,void *,int,float,int,float,int);
extern void *func_L00_00329E90(void *,void (*)(void),int *);
extern char *func_L00_0032A088(int,void *),*func_L00_00329FF0(void *);
extern AllocationOffsets *func_L00_0032A0B8(int,void *);
extern void func_00282A88(void *,int);
extern int func_00282948(int *),func_002829D8(float *);
extern int func_L00_002B3998(float);
extern void func_L00_002AF568(void),func_L00_00311080(void *,void *,int,int,int,int);
extern void func_L00_002D3F30(int,int),func_002E5CF8(int,int,void *);
extern char *func_L00_0041C2D0(void *,void *,int,void *,int,int);
void func_L00_003B5BF8(unsigned char *object)
{
    int existing;
    WeaponContext *state=*(WeaponContext **)(object+0x68);
    char *ctx=(char *)state;
    char *cursor,*base,*other,*result;
    int offset;
    void **table;
    int triggered,secondary,finished,allowed;
    func_L00_003B6158(object);
    if(D_00189E20.field1500 || D_00189E20.field2294==29 || D_00189E20.field2294==1) {
        unsigned int color;
        if(F(ctx,0xC)>0.0f && func_L00_002D4040(-1)) color=0x600000FF;
        else color=0x600FFF0F;
        func_00273318(object,1.0f,color,0,38,0.0f,-1,90.0f,4);
    }
    switch(object[0x20]) {
    case 0: {
        other=func_L00_00329E90(object,func_L00_003B60E8,&existing);
        state->data=other;
        if(!existing) {
            cursor=func_L00_0032A088(H(object,0xAA),other);
            base=cursor;
            cursor=func_L00_00329FF0(cursor+0x64);
            { int i; for(i=0;i<25;i++) {((void **)base)[i]=cursor;cursor+=0x280;} }
            cursor=func_L00_00329FF0(cursor);
            I(ctx,4)=cursor-base;
            func_00282A88(cursor,0x20D0);
            cursor=func_L00_00329FF0(cursor+0x20D0);
            I(ctx,8)=cursor-base;
            { int j; for(j=24;j>=0;j--) ((int *)cursor)[j]=0; }
            cursor=func_L00_00329FF0(cursor+0x64);
            offset=cursor-base;
            table=(void **)cursor;
            cursor=func_L00_00329FF0(cursor+0x64);
            { int k; for(k=0;k<25;k++) {table[k]=cursor;cursor+=0x280;} }
            { AllocationOffsets *offsets=func_L00_0032A0B8(H(object,0xAA),*(void **)ctx);
            offsets->first=I(ctx,4);offsets->second=I(ctx,8);offsets->third=offset; }
        }
        object[0x20]=1;H(ctx,0x1C)=4;
        state->cooldown=0;state->target=0;state->previous=0;state->release=0;
        return;
    }
    case 1: case 2:
        triggered=0;secondary=0;finished=0;allowed=1;
        if(D_00189E20.field1500 || D_00189E20.field2294==29) {
            if(!func_00282948(&D_00189E20.field2534)) allowed=0;
        } else D_00189E20.field2534=40;
        if(object[0x20]==1) {
            if(func_002829D8((float *)(ctx+0xC)) && allowed &&
               (D_00138320 & D_00189E20.field1230) && D_00189E20.field1240>=23 &&
               (D_00189E20.field1500 || D_00189E20.field2294==1 || D_00189E20.field2294==29) && func_L00_002D4040(22)) {
                { WeaponEntry *w=&D_L00_00262570[D_0013957E];
                F(ctx,0xC)=1.0f/w->rate; }
                triggered=1;
            }
            secondary=0;
            if(D_00189E20.field2294==0x83 && !D_00189E20.fieldc2c && func_L00_002B3998(33.0f)) secondary=func_L00_002D4040(22)!=0;
            if(D_00189E20.field229c==4 && allowed && !D_00189E20.field49c &&
               F(ctx,0xC)==0.0f && (D_00138320&0x20) && D_00189E20.field1240>=23 && func_L00_002D4040(22)) {
                func_L00_002AF568();
                other=*(char **)((char *)&D_00189E20+0xE98);
                if(other) {
                    F(other,8)=0.0f;
                    func_L00_00311080(D_00189E20.field2290,other,D_00189E20.field24b0,1,1,1);
                }
                object[0x20]=2;
                { WeaponEntry *w=&D_L00_00262570[D_0013957E];
                F(ctx,0xC)=1.0f/w->rate; }
                I(ctx,0x10)=8;
            }
        } else if(func_00282948((int *)(ctx+0x10))) {finished=1;object[0x20]=1;}
        if(triggered || secondary || finished) {
            func_L00_002D3F30(-1,1);func_002E5CF8(2,0,object);
            result=func_L00_0041C2D0(object,object+0x10,triggered,*(void **)ctx,I(ctx,0x14),1);
            if(result) *(void **)(result+0xB8)=object;
        }
        return;
    }
}
