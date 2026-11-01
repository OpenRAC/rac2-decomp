#include "include_asm.h"


extern void Ffb202470_FUN_0033AB50(char *p);

char *func_PAL_0033DC60(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


INCLUDE_ASM("asm/pal/game", func_PAL_0033DDC0);

INCLUDE_ASM("asm/pal/game", func_PAL_0033DF90);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033E000(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/game", func_PAL_0033E160);


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033E300(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}





/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033E888(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern void Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

int func_PAL_0033E9E8(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    Fc558ca70_FUN_0033AE28(p);
    q = *(float **)(a0 + 732);
    Fc558ca70_FUN_0033B018(p, q[0], q[1]);
    if (a1 & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(a0 + 728)) {
        case 0:
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}



extern void func_PAL_0033CA78(int);

char *func_PAL_0033EC50(char *object)
{
    extern void func_003363D0(void *);
    func_PAL_0033CA78((int)(object + 8));
    func_003363D0(object + 0x2DC);
    func_003363D0(object + 0x324);
    return object;
}




typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair D_L00_001AE1A8;
extern char D_L00_001AE1B0[];
extern void func_00336548(void *);
extern void func_0027FA10(int, int, unsigned long, char *, int);
extern int func_0027FB40(int, int, unsigned long, char *, int);
extern char D_L00_001AE118[];
extern void func_PAL_0033CE70(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern SolTextPair D_L00_001AE110;
extern char D_L00_001AE118[];
extern void func_PAL_0033CE70(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);

/* func_0033D028 uses small data in 0033D028-g8.c. */

void func_PAL_0033F190(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *format, *first, *second;
    char *format2, *middle, *last;
    int color;
    func_PAL_0033CE70(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE1A8;
    format = D_L00_001AE1B0;
    first = func_00288FB8(0xE34);
    func_00115DA8(buffer, format, first);
    func_0027FA10(0x100, 0x91, color, buffer, -1);
    func_00336548(object + 0x2DC);
    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    middle = func_00288FB8(0xE35);
    func_00115DA8(buffer, format, middle);
    func_0027FA10(0x100, 0xBE, color, buffer, -1);
    func_00336548(object + 0x324);
    color = *(int *)(object + 0x2D8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    format2 = D_L00_001AE118;
    last = func_00288FB8(0xE36);
    second = func_00288FB8(pair.ids[*(int *)0x1A7C20 != 0]);
    func_00115DA8(buffer, format2, last, second);
    func_0027FB40(0x100, 0xE1, color, buffer, -1);
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033F310(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



extern void F5979c03f_FUN_0033AE28 (char *object);
extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);
extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

int func_PAL_0033F470 (char *object, int flags)
{
  volatile unsigned char *g = (volatile unsigned char *) 0x1A7C1E;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}


extern void func_0027FAA8(int, int, unsigned long, char *, int);

void func_PAL_0033F508(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    int color;
    func_PAL_0033CE70(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = func_00288FB8(0xBAA);
    second = func_00288FB8(pair.ids[*(unsigned char *)0x1A7C1E != 0]);
    func_00115DA8(buffer, format, first, second);
    func_0027FAA8(0x100, 0xAA, color, buffer, -1);
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033F5D8(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/game", func_PAL_0033F738);




/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033F9A0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/game", func_PAL_0033FB00);


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033FC98(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/game", func_PAL_0033FDF8);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033FED8(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



INCLUDE_ASM("asm/pal/game", func_PAL_00340038);



extern int func_PAL_003402F0(int);

int func_PAL_003402B8(int owner)
{
    int result;
    result = func_PAL_003402F0(owner);
    return *(int *)(owner + 0x3B8) + result * 0x14;
}


INCLUDE_ASM("asm/pal/game", func_PAL_003402F0);


INCLUDE_ASM("asm/pal/game", func_PAL_00340348);





void func_0033AF48(int);

void func_PAL_00340610(int param_1) {
  func_0033AF48(param_1 + 8);
}

extern void func_0033AB50_1(void *);
extern void func_L00_0042BFF8(void *);
extern void func_L00_0042C290(void *);
extern void func_L00_0042BAD0(void *);

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
char *func_PAL_00340630(char *object)
{
    func_0033AB50_1(object + 8);
    func_L00_0042BFF8(object + 732);
    func_L00_0042C290(object + 792);
    func_L00_0042C290(object + 880);
    func_L00_0042C290(object + 968);
    func_L00_0042BAD0(object + 1056);
    func_L00_0042C290(object + 1136);
    func_L00_0042C290(object + 1224);
    func_L00_0042C290(object + 1312);
    func_L00_0042C290(object + 1400);
    func_L00_0042C290(object + 1488);
    func_L00_0042C290(object + 1576);
    return object;
}






INCLUDE_ASM("asm/pal/game", func_PAL_00341090);

INCLUDE_ASM("asm/pal/game", func_PAL_00341208);
