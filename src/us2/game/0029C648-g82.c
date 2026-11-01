#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001A9A54 __attribute__((sda));
extern char D_001A9A60 __attribute__((sda));
extern char D_001A9AB8 __attribute__((sda));
extern char D_00256418[];
extern int func_0026F7D8(void), func_0026F7D8(void);
extern void func_US2_0029CA88(void), func_US2_0029C700(void);
extern void func_00349490(void *, int);
extern void func_US2_0033BA48(void *,void *,void *);
extern void func_US2_0033BA10(void *,float);
extern void func_US2_0033BA28(void *,int);
extern int func_0026F7D0(void), func_0026F7D0(void);

extern int ref_US2_0029C818_00(void), ref_US2_0029C818_00(void);
extern int ref_US2_0029C818_01(void), ref_US2_0029C818_01(void);

void func_US2_0029C818(void) {
 int enabled;
 if (D_001A8CFC[0] != 0) {
  enabled=0;
  if(ref_US2_0029C818_00()) enabled=ref_US2_0029C818_01()!=0;
  if(D_001A9A54 != enabled) {
   func_US2_0029CA88();
   D_001A9A54=enabled;
   if(enabled==1) {
    func_00349490(D_001A8CFC[0]+0x3CD48,(int)&D_001A9A60);
    func_US2_0033BA48(D_001A8CFC[0]+0x3F7B0,&D_001A9AB8,D_00256418);
    func_US2_0033BA10(D_001A8CFC[0]+0x3F7B0,36.0f);
    func_US2_0033BA28(D_001A8CFC[0]+0x3F7B0,-1);
    func_US2_0029C700();
   }
  }
 }
}

extern int ref_L00_0030CDB0_00[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern void func_US2_0029C8F0(void);
extern unsigned int func_00285840(void);
extern void func_US2_0029C648(void);
typedef int (*Fn)(void);
typedef struct { void *cb; int pad; } Slot;
typedef struct {
    char pad0[0x79D8];
    void *cb1;
    char pad1[0x7368 - 0x7354];
    void *cb2;
    char pad2[0x7370 - 0x736C];
    Slot slot[4];
    Slot slot2[2];
} Sub;

void func_US2_0029CA98(void)
{
    int i;
    int result;
    Sub *sub;
    Fn fn;
    char *g;

    if (ref_L00_0030CDB0_00[0] != 0)
        return;

    if (D_001A8CFC[0] == 0)
        goto states;
    func_US2_0029C8F0();
    fn = (Fn)((Sub *)(D_001A8CFC[0] + 0x38000))->cb2;
    if (fn != 0) {
        if (fn() != 0)
            return;
    }
    result = 0;
    for (i = 0; i < 4; i++) {
        sub = (Sub *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Fn *)(D_001A8CFC[0] + 0x3F9F8))[i * 2]();
    }
    if (result != 0)
        return;
    for (i = 0; i < 2; i++) {
        sub = (Sub *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Fn *)(D_001A8CFC[0] + 0x3FA18))[i * 2]();
    }
    if (result != 0)
        return;
states:
    if (D_001A8BB0[0] != 0 && D_001A8BB0[0] != 5) {
        if (D_001A8BB0[0] == 4) {
            if (func_00285840() != 7)
                return;
        }
    }
    g = D_001A8CFC[0];
    if (g != 0) {
        char *b = g + 0x38000;
        g = (char *)((Sub *)b)->cb1;
        ((Fn)g)();
        func_US2_0029C648();
    }
}
