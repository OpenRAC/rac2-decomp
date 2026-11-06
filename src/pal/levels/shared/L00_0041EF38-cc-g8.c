/* func_PAL_L00_0041EF38, the PAL copy of func_L00_00419C98: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_0032D758 becomes func_PAL_0032F0B8; rename func_L00_002C42E0 becomes func_PAL_L00_002C4480; rename func_L00_0041A5C0 becomes func_PAL_L00_0041F868; rename func_L00_0041BAE8 becomes func_PAL_L00_00420D90; lit 10.0f becomes 12.0f. */
#include "common.h"

/* The three effect tables are small-data pointers; this unit requires -G8. */
typedef int EffectVectorBits __attribute__((mode(TI)));
typedef union { int i[0x980]; float f[0x980]; unsigned char b[0x2600]; char *p[0x980]; } EffectHeroState;
typedef struct { char pad[0x70]; float value; char rest[0x6c]; } EffectClassEntry;
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; char *owner; } EffectSoundSlot;
typedef struct { char pad[0x30]; int active; char rest[12]; } EffectParticleSlot;
typedef struct { char pad[0x514]; int active; char rest[24]; } EffectLargeSlot;
typedef struct { char pad[0x38]; int handle; int rest; } EffectHandleSlot;
extern EffectHeroState D_00189E20;
extern int D_00138180[];
extern unsigned char D_00139568[];
extern EffectClassEntry D_L00_00262570[];
extern EffectSoundSlot D_00188660[];
extern char *D_L00_001B1448 __attribute__((sda));
extern char *D_L00_001B144C __attribute__((sda));
extern char *D_L00_001B1450 __attribute__((sda));
extern char *D_L00_001C3280[];
extern int D_L00_001A8FF0;
extern int D_L00_001A8F00;
extern char ref_L00_00419C98_00[];
extern void func_002FEE50(int);
extern int func_L00_00329E90(char *, int, int *);
extern char *func_L00_0032A088(int, int);
extern int func_L00_0041A490(int);
extern void func_002E59F8(int);
extern void func_0029FCC0(char *, int, char *);
extern void func_002A75E0(char *, int, int, int, int);
extern int func_00282948(int *);
extern int func_L00_002D4040(int);
extern void func_002AA3A8(float *, float *, float, float, float, float);
extern void func_L00_002D3F30(int, int);
extern int func_002E59B0(char *, int);
extern int func_002E5CF8(int, int, char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern int func_00277F48(float, char *, int, char *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, char *, int, void *, float);
extern void func_002A8E20(char *, void *);
extern void func_PAL_0032F0B8(char *, int, char *);
extern void func_PAL_L00_002C4480(int, int);
extern void func_00282C88(void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_0032A1A8(char *, char *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L00_0041ABB8(char *, char *, void *, int);
extern void func_PAL_L00_0041F868(char *);
extern void func_L00_0041A500(char *);
extern void func_PAL_L00_00420D90(char *);
extern void ref_L00_00419C98_01(void *, char *);

/* Initializes the effect tables on first update, processes nearby targets while active,
   and advances the emission vector and scrolling phases. */
void func_PAL_L00_0041EF38(char *object)
{
    float vector[4];
    union { EffectVectorBits word; float v[4]; } direction;
    struct { union { EffectVectorBits word; float position[4]; } u; char pad[8]; unsigned char a,b; short id; int pad3c; int flags; } packet;
    int unused, i = 0, count, enabled;
    char *state = *(char **)(object+0x68);
    char **target;
    if (D_00189E20.i[0x1244/4]==3 && D_L00_001B144C) {
        for (;i<35;i++) { char *p=D_L00_001B144C+i*64; if (*(int *)(p+0x38)>=0) { func_002FEE50(*(int *)(p+0x38)); *(int *)(p+0x38)=-1; } }
    }
    if (!((unsigned char *)object)[0x20]) {
        *(int *)(state+0x34)=func_L00_00329E90(object,0,&unused);
        D_L00_001B1450=func_L00_0032A088(*(short *)(object+0xaa),*(int *)(state+0x34));
        D_L00_001B1448=(char *)func_L00_0041A490((int)D_L00_001B1450+0x33e0);
        D_L00_001B144C=(char *)func_L00_0041A490((int)D_L00_001B1448+0x1f40);
        for (i=124;i>=0;i--) ((EffectParticleSlot *)D_L00_001B1448)[i].active=1;
        for (i=9;i>=0;i--) ((EffectLargeSlot *)D_L00_001B1450)[i].active=0;
        { int invalid=-1; for (i=34;i>=0;i--) ((EffectHandleSlot *)D_L00_001B144C)[i].handle=invalid; }
        *(int *)(state+0x3c)=0; *(int *)(state+0x48)=0; *(int *)(state+0x40)=0; *(int *)(state+0x44)=0;
        *(int *)(state+0x54)=0; *(int *)(state+0x50)=0; *(int *)(state+0x58)=0; *(int *)(state+0x5c)=0;
        *(int *)(state+0x60)=0; *(int *)(state+0x64)=0; ((unsigned char *)object)[0x20]=1; *(int *)(state+0x38)=-1;
    }
    if (D_00189E20.i[0x1244/4]==3) {
        { int handle=*(int *)(state+0x38);
        if (handle!=-1 && ((EffectSoundSlot *)((char *)D_00188660+handle*0x70))->owner==object && ((EffectSoundSlot *)((char *)D_00188660+handle*0x70))->active) func_002E59F8(handle); }
        *(int *)(state+0x38)=-1;
        return;
    }
    func_0029FCC0(object,0,state);
    if (((unsigned char *)object)[0x42]==((unsigned char *)object)[0x43] && (((unsigned char *)object)[0x60]&2)) func_002A75E0(object,1,0,2,0);
    enabled=1;
    if (D_00189E20.i[0x2294/4]==29) { if (!func_00282948(&D_00189E20.i[0x2534/4])) enabled=0; }
    else D_00189E20.i[0x2534/4]=33;
    if ((D_00138180[0x1a0/4]&D_00189E20.i[0x1230/4]) && enabled && func_L00_002D4040(-1) && !D_00189E20.b[0x22bc]) {
        func_002AA3A8((float *)(state+0x50),(float *)(state+0x54),10.0f,0.009000001f,0.0024f,12.0f);
        { int divisor=10; if (*(int *)(state+0x60)%divisor==0) func_L00_002D3F30(-1,1); }
        ++*(int *)(state+0x60);
        if (!func_002E59B0(object,*(int *)(state+0x38))) *(int *)(state+0x38)=func_002E5CF8(0,4,object);
        if (((unsigned char *)object)[0x43]!=2) func_PAL_002A7E68(object,2,0,0);
        count=func_00277F48(0.5f,state,16,object,0);
        if (count>0) { int remaining; target=D_L00_001C3280; remaining=count; do {
            if (*target!=D_00189E20.p[0x2290/4]) {
            func_00282CF0(&direction,*target+0x10,object+0x10);
            func_00282F20(&direction,&direction,1.0f);
            func_00282F20(&packet,&packet,1.0f);
            func_002A8C00(&packet,object,0x910000,&direction,((EffectClassEntry *)((unsigned int)D_L00_00262570+D_00139568[29]*0xe0))->value);
            packet.u.word=direction.word; packet.u.position[3]=5627.925f;
            packet.flags=1; packet.a=9; packet.b=1; packet.id=*(short *)(*target+0xaa);
            func_002A8E20(*target,&packet);
            func_PAL_0032F0B8(*target,29,object); func_002E5CF8(1,0,object);
            }
            target++;
        } while (--remaining); }
    } else {
        { int handle=*(int *)(state+0x38);
        if (handle!=-1 && ((EffectSoundSlot *)((char *)D_00188660+handle*0x70))->owner==object && ((EffectSoundSlot *)((char *)D_00188660+handle*0x70))->active) func_002E59F8(handle); }
        *(int *)(state+0x38)=-1;
        if ((D_00138180[0x1a4/4]&D_00189E20.i[0x1230/4]) && !func_L00_002D4040(-1) && !D_00189E20.b[0x22bc]) func_002E5CF8(2,0,object);
        func_002AA3A8((float *)(state+0x50),(float *)(state+0x54),0,0.072000004f,0.012f,0.15f);
        *(int *)(state+0x60)=0;
    }
    if (D_00189E20.i[0x2294/4]==1) func_PAL_L00_002C4480(29,1);
    func_0029FCC0(object,0,state);
    func_00282C88(vector); vector[1]=-1;
    func_00283098(vector,vector,object+0xc0);
    vector[2]+=0.02f;
    func_00282F20(vector,vector,*(float *)(state+0x50)*0.05f);
    if (D_00189E20.p[0x1450/4]) {
        D_00189E20.p[0xbf8/4]=D_00189E20.p[0x1450/4];
        func_L00_0032A1A8(D_00189E20.p[0x1450/4],state,vector,*(float *)(state+0x50)*0.05f);
        if (D_L00_001A8FF0) { func_00282D30(&direction,object+0xe0,0.02f); func_00282CC0(vector,vector,&direction); }
        else vector[2]+=0.02f;
    }
    qcopy(state+0x10,state);
    if (D_00189E20.i[0x2294/4]) func_002ACEC0(vector,vector,D_00189E20.p[0x2290/4]+0xd0,-0.09817477f);
    if (*(float *)(state+0x50)!=0) func_L00_0041ABB8(object,state,vector,33);
    *(float *)(state+0x58)-=0.1f; if (*(float *)(state+0x58)<=-8) *(float *)(state+0x58)+=8;
    *(float *)(state+0x5c)-=0.025f; if (*(float *)(state+0x5c)<=-8) *(float *)(state+0x5c)+=8;
    if (*(float *)(state+0x50)!=0) { func_PAL_L00_0041F868(object); func_L00_0041A500(object); }
    else { *(int *)(state+0x44)=0; *(int *)(state+0x3c)=0; *(int *)(state+0x48)=0; *(int *)(state+0x40)=0; }
    func_PAL_L00_00420D90(object);
    if (D_L00_001A8F00!=2 && ((unsigned char *)object)[0x31]) ref_L00_00419C98_01(ref_L00_00419C98_00,object);
}
