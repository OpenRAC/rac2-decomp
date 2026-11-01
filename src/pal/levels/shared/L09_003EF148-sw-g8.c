#include "include_asm.h"

#include "common.h"
#define FIELD(p,t,o) (*(t *)((char *)(p)+(o)))
extern int D_L09_001B0C4C __attribute__((sda));
extern float D_L09_001B0C00 __attribute__((sda)), D_L09_001B0C04 __attribute__((sda)), D_L09_001B0C08 __attribute__((sda)), D_L09_001B0C0C __attribute__((sda));
extern float D_L09_001B0C10 __attribute__((sda)), D_L09_001B0C14 __attribute__((sda)), D_L09_001B0C18 __attribute__((sda)), D_L09_001B0C1C __attribute__((sda));
extern char D_L09_001B0C50[];
extern int func_002ACD38(void *);
extern void func_L09_003EAA18(void *);
extern void func_0026FEB8(void *,int,int);
extern int func_002B38B8(void *);
extern void func_002A7750(void *,int,int);
extern void func_002B60B0(void *,float,float,float,float);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int func_L09_003EA058(void *,int);
extern int func_L09_003EA2D0(void *,int,int);
extern int func_L09_0033E658(int);
extern void func_L09_003EA108(void *,int);
extern int func_002B1C20(void *,void *);
extern void func_PAL_L09_003EF588(void *);
extern void func_PAL_L09_003EDEE8(void *);
extern void func_PAL_L09_003EE908(void *);
extern void func_PAL_L09_003EDFA8(void *);
extern void func_L09_003EA9D0(void *);

void func_PAL_L09_003EF148(char *object)
{
    char *state;
    char *position;
    int ready;
    if (D_L09_001B0C4C) return;
    position=object+0x10;
    if (!func_002ACD38(position)) return;
    state=FIELD(object,char *,0x68);
    func_L09_003EAA18(object);
    qcopy(position,state+0x330);
    switch (FIELD(object,unsigned char,0x95)) {
    case 0: func_0026FEB8(D_L09_001B0C50,FIELD(object,short,0xB2),FIELD(object,short,0xAA)); break;
    case 1:
        if (FIELD(state,int,0x154)==1 || func_002B38B8(object)) {
            FIELD(state,int,0x354)=FIELD(state,int,0x378);
            func_002A7750(object,2,2);
        }
        break;
    case 3:
        if (FIELD(state,int,0x154)==1) {
            func_002B60B0(object,D_L09_001B0C10*0.00040000002f,D_L09_001B0C14*0.020000001f,D_L09_001B0C18*6.981318e-06f,D_L09_001B0C1C*0.0003490659f);
            func_002A7750(object,4,4);
        }
        break;
    case 2: case 5: break;
    case 4:
        if (FIELD(state,int,0x154)!=1 && !FIELD(state,unsigned char,0x369)) {
            if (FIELD(object,unsigned char,0x43)) func_PAL_002A7E68(object,0,0,0);
            func_002B60B0(object,D_L09_001B0C00*0.00040000002f,D_L09_001B0C04*0.020000001f,D_L09_001B0C08*6.981318e-06f,D_L09_001B0C0C*0.0003490659f);
            func_002A7750(object,3,3);
        }
        break;
    }
    switch (FIELD(object,unsigned char,0x20)) {
    case 0: func_0026FEB8(D_L09_001B0C50,FIELD(object,short,0xB2),FIELD(object,short,0xAA)); break;
    case 1: break;
    case 2:
        ready = 1;
        if (FIELD(state,int,0x36C)!=-1) ready = func_L09_003EA058(object,FIELD(state,int,0x36C)) != 0;
        if (ready) {
            func_002B60B0(object,D_L09_001B0C00*0.00040000002f,D_L09_001B0C04*0.020000001f,D_L09_001B0C08*6.981318e-06f,D_L09_001B0C0C*0.0003490659f);
            func_L09_003EA2D0(object,FIELD(state,int,0x350),-1);
            FIELD(state,int,0x380)=1;
            func_002A7750(object,3,3);
        } break;
    case 3:
        ready = 1;
        if (FIELD(state,int,0x350)!=-1) ready = func_L09_003EA058(object,FIELD(state,int,0x350)) != 0;
        if (ready) {
            if(FIELD(state,short,0x11A)) FIELD(state,short,0x11A)=0;
            else FIELD(state,short,0x11A)=func_L09_0033E658(FIELD(state,int,0x350));
        } break;
    case 4:
        if(FIELD(state,int,0x350)!=-1) func_L09_003EA108(object,FIELD(state,int,0x350));
        break;
    case 5:
        if(func_002B1C20(object,state+0x180)&2) {
            if(FIELD(state,float,0x20)<=0) func_002A7750(object,6,-1);
            else {
                FIELD(state,int,0x37C)=0;
                if(FIELD(state,int,0x380)) {
                    FIELD(state,unsigned char,0x369)=0;
                    FIELD(state,int,0x354)=FIELD(state,int,0x378);
                    func_002A7750(object,4,4);
                } else {
                    if(FIELD(object,unsigned char,0x43)) func_PAL_002A7E68(object,0,0,0);
                    FIELD(state,int,0x354)=FIELD(state,int,0x378);
                    func_002A7750(object,2,2);
                }
            }
        } break;
    case 6: func_PAL_L09_003EF588(object); break;
    }
    func_PAL_L09_003EDEE8(object);
    FIELD(object,int,0xF0)=0;
    func_PAL_L09_003EE908(object);
    func_PAL_L09_003EDFA8(object);
    func_L09_003EA9D0(object);
}
