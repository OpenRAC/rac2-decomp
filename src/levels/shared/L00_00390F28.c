#include "include_asm.h"
#include "names.h"
typedef struct {
    char pad0[0x30];
    float f30;
    float f34;
    float f38;
    float f3C;
    unsigned char b40;
    unsigned char b41;
    unsigned char b42;
} State_390F28;

typedef struct {
    char pad0[0x23C];
    int a;
    int b;
    int c;
} Cfg_390F28;

extern int D_L00_001A8A44 __attribute__((section(".sdata")));
extern float D_L00_001B1984 __attribute__((section(".sdata")));
extern float D_L00_001B1988 __attribute__((section(".sdata")));
extern float D_L00_001B198C __attribute__((section(".sdata")));
extern float D_L00_001B1990 __attribute__((section(".sdata")));
extern unsigned char D_L00_001B1980 __attribute__((section(".sdata")));
extern unsigned char D_L00_001B1981 __attribute__((section(".sdata")));
extern unsigned char D_L00_001B1982 __attribute__((section(".sdata")));
extern float D_L00_001B2500 __attribute__((section(".sdata")));
extern float D_L00_001B2408 __attribute__((section(".sdata")));
extern int D_L00_001B1EB4 __attribute__((section(".sdata")));
extern int D_L00_001B20C0 __attribute__((section(".sdata")));
extern int D_L00_001B255C __attribute__((section(".sdata")));
extern Cfg_390F28 D_L00_001BD2C0;
extern void func_00284E18(int, int, int);

/* Restores the lighting and fog settings saved by func_L00_00390E10; when full is set it also resets the view range. */
void func_L00_00390F28(char *object, int full)
{
    State_390F28 *st = *(State_390F28 **)(object + 0x68);

    D_L00_001A8A44 = 0;
    D_L00_001B1984 = st->f30;
    D_L00_001B1988 = st->f34;
    D_L00_001B198C = st->f38;
    D_L00_001B1990 = st->f3C;
    D_L00_001B1980 = st->b40;
    D_L00_001B1981 = st->b41;
    D_L00_001B1982 = st->b42;
    if (full) {
        D_L00_001B2500 = 983040.0f;
        D_L00_001B2408 = 500.0f;
        D_L00_001B255C = 0x3C0;
        D_L00_001B1EB4 = 0x3C0;
        D_L00_001B20C0 = 0x1F4000;
    }
    SetBackgroundColor(D_L00_001BD2C0.a, D_L00_001BD2C0.b, D_L00_001BD2C0.c);
}
