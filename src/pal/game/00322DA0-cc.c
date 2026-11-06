/* func_PAL_00322DA0, the PAL copy of func_003216E8: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_002B0ED8 becomes func_PAL_002B1A50; rename func_002AC728 becomes func_PAL_002AD288; rename func_002A6C58 becomes func_PAL_002A7650; expr 0.004166667f becomes 0.006f; expr 0.06666667f becomes 0.080000006f; expr 0.008333334f becomes 0.012f; expr 0.13333334f becomes 0.16000001f. */
#include "common.h"

/* Camera position used by the facing-vector helpers. */
/* func_0031F210 is in 0031F210-ribbon.c. */

/* func_0031FC28 is in 0031F210-pickup-g8.c. */

/* func_003202E8 is in 0031F210-g8.c. */

extern void func_002A7750(unsigned char *, unsigned char, int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern void func_00321F60(char *);
extern void func_00321E28(char *);
extern void func_00282C88(void *);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_002B60B0(char *, float, float, float, float);
extern void func_0029FCC0(char *, int, void *);
extern int func_002761F8(void *, void *, int, char *, int);
extern float func_002A89A8(void *, int, float);
extern void func_PAL_002A7E68(char *, int, int, int);
extern int func_002A8508(int, int);
extern int func_002B3BA8(char *, int, float, float, int, int);
extern void func_PAL_002AD288(char *, void *, int, float, float);
extern void func_PAL_002A7650(char *, int, int);
extern void func_002A93B0(char *);
extern void func_0029FC20(char *, int, float *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(float *, float *, float *);
extern int func_PAL_002B1A50(char *, void *, int);
extern float func_00282E48(void *, void *);
extern float D_001BAFA0[];
extern char *D_001B1C4C MACRO_ADDR;
extern char D_001B5340[];
extern int D_001B1B78 MACRO_ADDR;
extern short *D_001EE5A0[];
extern char *D_001B1B5C MACRO_ADDR;
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define U(p,o) (*(unsigned char *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
int func_PAL_00322DA0(char *object)
{
    float matrix[16];
    char *data = *(char **)(object + 0x68);
    int status, special;
    char *child;
    short *list;
    char *other;
    if (!U(object,0x20)) {
        F(object,0x2c) *= 1.1f;
        U(object,0x7e) |= 1;
        *(char **)(data+0x18)=data+0x110;
        F(data,0x284) *= 0.017453294f;
        U(data,0x48)=func_00283CF0(20.0f);
        U(data,0x4a)=func_00283CF0(16.0f);
        if(func_002A77E0(2)==1) H(object,0x34)|=0x8000;
        F(data,0x90)=0.5f;
        F(data,0x94)=0.5f;
        F(data,0x114)=0.5f;
        U(data,0x70)=15;
        I(data,0xa8)=5;
        U(data,0x71)=19;
        U(data,0x72)=21;
        U(data,0x76)=23;
        U(data,0x77)=24;
        F(data,0x7c)=0.120000005f;
        F(data,0x80)=0.080000006f;
        F(data,0x84)=0.006f;
        F(data,0x88)=0.012f;
        F(data,0x8c)=0.006f;
        F(data,0x9c)=0.4f;
        *(char *)(data+0xcc)=-1;*(char *)(data+0xcd)=-1;*(char *)(data+0xce)=-1;*(char *)(data+0xcf)=-1;*(char *)(data+0xd2)=-1;*(char *)(data+0xd3)=-1;
        I(data,0x2c0)=-1;
        F(data,0x110)=0.8f;
        F(data,0x118)=0.4f;
        F(data,0x11c)=0.4f;
        F(data,0x120)=1.134464144706726f;
        F(data,0x140)=0.52359885f;
        F(data,0x13c)=0.008f;
        *(char **)(data+0x158)=data+0x3d0;
        *(char **)(data+0x15c)=data+0x450;
        func_002B60B0(object,0.0064000003f,0.16000001f,0.0016755164f,0.12566373f);
        qcopy(data+0x200,object+0x10);
        U(data,0x2e)=1;
        I(data,0x280)=0;
        F(data,0x210)=1.0f;
        F(data,0x21c)=5.0f;
        F(data,0x220)=10.0f;
        F(data,0x298)=(float)U(data,0x34);
        U(data,0x28)=3;
        func_0029FCC0(object,0,data+0x380);
        F(data,0x388)+=20.0f;
        func_0029FCC0(object,0,data+0x390);
        if(func_002761F8(data+0x390,data+0x380,0,object,0)) qcopy(data+0x380,D_001BAFA0);
        if(!I(data,0x27c) && I(data,0x288)==-1) {
            F(object,0x18)=func_002A89A8(object+0x10,0,0.5f);
            func_002A7750((unsigned char *)object,1,0);
            if(U(object,0x43)) func_PAL_002A7E68(object,0,0,0);
        } else {
            func_002A7750((unsigned char *)object,3,2);
            if(U(object,0x43)!=11) func_PAL_002A7E68(object,11,0,0);
            I(object,0x98)=0;F(data,0x30)=2.5f;
            child=func_0029EFD0(0xab7);
            *(char **)(data+0x2ac)=child;
            if(!child) return 1;
            U(child,0x30)=U(object,0x30);
            H(*(char **)(data+0x2ac),0x32)=H(object,0x32);
            U(*(char **)(data+0x2ac),0x31)=1;
            *(long long *)(*(char **)(data+0x2ac)+0x38)=*(long long *)(object+0x38);
            H(*(char **)(data+0x2ac),0x34)|=0x41;
            qcopy_nc(*(char **)(data+0x2ac)+0x10,object+0x10);
            func_002A0F48(*(char **)(data+0x2ac));
        }
        if(I(data,0x288)!=-1) {
            func_002A7750((unsigned char *)object,2,0);
            qcopy(data+0x380,D_001B1C4C+(I(data,0x288)<<7)+0x30);
            U(object,0x30)=0x80;
        }
    }
    if(U(object,0x31) && func_00282E48(object+0x10,D_001B5340)<24.0f) {
        func_002A93B0(object);U(object,0x6f)=22;
    }
    func_0029FCC0(object,0,data+0x390);
    func_0029FCC0(object,1,data+0x3a0);
    func_0029FCC0(object,2,data+0x3b0);
    func_0029FC20(object,3,matrix);
    func_00282C88(data+0x3c0);
    I(data,0x3c8)=0;F(data,0x3c0)=0.25f;
    func_002830C0(data+0x3c0,data+0x3c0,matrix);
    func_00282CC0((float *)(data+0x3c0),(float *)(data+0x3c0),matrix+12);
    special=0;
    if(U(data,0x2e)==2) special=1;
    status=func_PAL_002B1A50(object,data+0x60,0);
    if(status || special) {
        F(data,0x30)=0.5f;
        if(status==5) {I(data,0xf0)=0;F(data,0xf4)=1.0053098f;}
        func_00321F60(object);
        if((status==4 || status==5 || special) && D_001B1B78>=U(object,0x21) && func_002A8508(U(object,0x21),-1)>=2) {
            list=D_001EE5A0[U(object,0x21)];
            for (;;) {
                other=(char *)(D_001B1B5C+((*list & 0x7fff)<<8));
                if (*(short *)(other+0xaa)==0xb0a) {
                    char *d=*(char **)(other+0x68);
                    if (!I(d,0x294)) {I(d,0x294)=1;break;}
                } else if (*(short *)(other+0xaa)==0xb0b) {
                    char *d=*(char **)(other+0x68);
                    if (!I(d,0x294)) {
                        I(d,0x294)=1;
                        if (!I(data,0x29c)) break;
                    }
                }
                if (*list++ < 0) break;
            }
        }
    }
    I(data,0x258)=func_002B3BA8(object,I(data,0x250),F(data,0x268),10.0f,0,0);
        I(data,0x25c)=func_002B3BA8(object,I(data,0x254),F(data,0x26c),10.0f,0,0);
        if(F(object,0x18)<90.0f) {
            func_PAL_002AD288(object,object+0x10,-1,0.5f,13.0f);
            func_PAL_002A7650(object,0,3);return 1;
        }
    if(special) {func_00321E28(object);return 1;}
    return 0;
}

extern void func_00321F60(char *);

void func_00321E28(char *object);

/* func_00321FE0 is in the -G8 sibling. */

/* func_00322138 is in 0031F210-q.c. */

extern void func_0029FC20(char *, int, float *);
extern void func_00282CC0(float *, float *, float *);
/* Integer and FP arguments keep their order in the separate EE banks. */
/* Effect at an object's joint: func_002A8C28 at the joint and at two points along its axis,
   three grey func_002C65A0 particles at the joint and one func_002C16C0 particle at the near
   point, which at random takes flags 0x48 and the 0x707070 tint. */
extern void func_002A7750(unsigned char *, unsigned char, int);
/* func_003248A8 is in 0031F210-init.c. */

/* func_00325158 is in 0031F210-turn-g8.c. */

/* func_00325320 is in the -G8 sibling. */

/* func_00325A88 (cursor bookkeeping and a 16-byte copy) is a near miss:
   nonmatching/game/func_00325A88.c */
/* func_00325B28 is in the -G8 sibling. */

extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);

/* func_00325D30 and func_00325DA0 are in 0031F210-group-g8.c. */

/* func_00325EC0 is in 0031F210-effects-g8.c. */

/* func_00326198 is in 0031F210-state-g8.c. */

/* negates two floats read from a fixed global table, clamps each to [-1,1] into an object reached through the parameter's +104 pointer, packs the pair into a two-float stack buffer, passes it to two callees and stores the second callee's float return value at object+48 */
/* func_00326EC0 is in 0031F210-basis-g8.c. */
