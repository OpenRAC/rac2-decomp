#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
typedef struct {
    char pad0[0x1B8]; int field1b8;
    char pad1bc[0x160]; float field31c;
    char pad320[0xF00]; int field1220;
    char pad1224[0x16]; u8 field123a;
    char pad123b[0xD]; int field1248;
    char pad124c[0x1048]; int field2294;
    char pad2298[0x1C]; u8 field22b4;
} MotionResident;
extern MotionResident D_00189E20;
#define R ((char *)&D_00189E20)

typedef struct { char pad[0x168]; u16 sentinel; } HudResident;
extern HudResident D_0018C958;


extern int D_001A79F0 __attribute__((sda));
extern u8 D_L16_0027F078[];
extern int D_L16_001A8FF0;
extern u8 *D_L16_001B2B1C;
extern float D_L16_001AF430 __attribute__((sda));
extern float D_L16_001AF434 __attribute__((sda));
extern float D_L16_001AF438 __attribute__((sda));
extern void func_002AFFD8(char *,char *,int);
extern void func_L00_00325600(void *,void *,void *);
extern void func_002AB6D8(float *,float *);
extern void func_002A7750(u8 *,s32,s32);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00282948(int *);
extern float func_00282E48(void *,void *);
extern int func_00288E18(int,int);
extern int func_L00_0032EF10(int,int,int);
extern int func_L16_003960F8(char *);
extern void func_002AFDD8(char *,char *,char *,char *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern void func_L16_002C0BC8(int,int);
extern void func_L16_00395D30(char *);
extern float func_00282C48(float);
extern void func_003355A8(int);
extern void func_L16_00395858(char *);
extern void func_L16_003959B8(char *);
extern void func_L16_00395C00(char *);
extern void func_L16_00395ED0(char *);
extern s32 func_002B3868(u8 *);
void func_L16_00395250(u8 *object)
{
    struct { float position[4],direction[4],forward[4]; } vectors;
#define position vectors.position
#define direction vectors.direction
#define forward vectors.forward
    u8 *state=*(u8 **)(object+0x68);
    u8 *target;
    float value,velocity,zero,ground;
    u8 mode;
    switch (object[0x20]) {
    case 0:
        if (!D_L16_001A8FF0) return;
        F(object,0x2C)=F(*(u8 **)(object+0x24),0x24);
        func_002AFFD8((char *)object+0x10,(char *)position,0);
        *(u16 *)(object+0x34)|=0x100;
        func_L00_00325600(object+0xC0,position,0);
        func_L00_00325600(object+0xC0,position,0);
        qcopy(state+0x10,object+0x10);
        func_002AB6D8((float *)(object+0xC0),(float *)(state+0x20));
        target=D_L16_001B2B1C+(I(state,4)<<8);
        I(state,0x58)=0;
        if (!target || target[0x20]==254 || target[0x20]==253) { F(state,0x34)=1.0f; func_002A7750(object,4,-1); }
        else { F(state,0x34)=0.0f; goto mode1; }
        return;
    case 1:
        func_00282F20(position,object+0xE0,D_L16_001AF430);
        func_00282CC0(object+0x10,position,state+0x10);
        if (func_00282948((int *)(state+0x3C)) && func_00282E48(object+0x10,R+0x80)<1.75f) {
            if (D_00189E20.field123a || D_00189E20.field22b4) goto decay;
            if (D_0018C958.sentinel<65535 && I(D_L16_0027F078,0)==0 && I(D_L16_0027F078,0x24)==-1) {
                func_00288E18(0x9C7,30);
                D_0018C958.sentinel=-1;
            }
            if (D_00189E20.field1248!=10) goto decay;
            if (D_00189E20.field1220) {
                if (!func_L00_0032EF10(0x80,7,0) || !(D_00189E20.field31c<0.2f) || !func_L16_003960F8((char *)object)) goto decay;
                if (F(state,0x34)<1.0f) {
                    func_002AFDD8((char *)object,(char *)forward,R,0);
                    func_00282CF0(direction,R+0x80,object+0x10);
                    func_002AFDD8((char *)object,(char *)direction,(char *)direction,0);
                    zero=0.0f;
                    forward[2]=zero;
                    direction[2]=zero;
                    func_00282F20(direction,direction,1.0f);
                    func_00282F20(forward,forward,1.0f);
                    if (func_00282DB0(direction,forward)<0.2f) { func_L16_002C0BC8(0x37,1); func_L16_00395D30((char *)object); }
                    func_002A7750(object,2,-1);
                }
            }
        }
decay:
    if (F(state,0x34)==0.0f) return;
    F(state,0x40)-=0.0027777778f;
    F(state,0x34)+=F(state,0x40);
    value=F(state,0x34);
    if (!(value<=0.0f)) return;
    F(state,0x34)=0.0f;
    if (func_00282C48(F(state,0x40))>0.0016666668f) { F(state,0x40)*=-0.333f; F(state,0x34)=F(state,0x40); }
    else F(state,0x40)=0.0f;
        return;
    case 2:
        if (func_L00_0032EF10(0x80,7,0) && D_00189E20.field1b8>=21) goto leaveActive;
        if (F(state,0x34)>=1.0f) goto leaveActive;
        if (D_00189E20.field2294==0x37) goto active;
leaveActive:
        if (D_00189E20.field2294==0x37) func_L16_002C0BC8(0,1);
        func_003355A8(1);
        I(state,0x3C)=20;
        I(state,0x58)++;
        if (I(state,0x58)==3 || I(state,0x58)==6) func_00288E18(0x9C7,30);
        if (F(state,0x34)>=1.0f) {
            if (D_001A79F0==26) D_0018C958.sentinel=-1;
            F(state,0x34)=1.0f;
            func_002A7750(object,4,-1);
        } else {
mode1:
            func_002A7750(object,1,-1);
        }
        return;
active:
            func_00282F20(position,object+0xE0,D_L16_001AF434);
            func_00282CC0(object+0x10,position,state+0x10);
            func_L16_00395858((char *)object);
            func_L16_003959B8((char *)object);
            func_L16_00395C00((char *)object);
            func_L16_00395ED0((char *)object);
        return;
    case 4:
        if (func_002B3868(object)) F(state,0x44)=D_L16_001AF430;
        velocity=F(state,0x48)-0.0027777778f;
        value=F(state,0x44)+velocity;
        ground=D_L16_001AF438;
        F(state,0x48)=velocity;
        F(state,0x44)=value;
        if (value<=ground) {
            F(state,0x44)=ground;
            if (func_00282C48(F(state,0x48))>0.0016666668f) F(state,0x48)*=-0.333f;
            else *(u16 *)(object+0x34)|=2;
        }
        func_00282F20(position,object+0xE0,F(state,0x44));
        func_00282CC0(object+0x10,position,state+0x10);
        return;
    default:
        return;
    }
}
