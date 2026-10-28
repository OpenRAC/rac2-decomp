/* func_L00_00325AE8 - 468 bytes, 27 places.  Matches at every place in us,
   pal and us2 in src/levels/shared/L00_00325AE8-g8.c with
   `-O2 -G8 -ffunction-sections -frac2-zero-ti-por` (marker removed from its
   original unit).

   Not landed: retail reaches the 64-byte table D_001AA310 (four vectors)
   through $gp (`addiu $s5,$gp,-0x4CE0`), and only a declaration of
   `float D_001AA310[2] __attribute__((sda))` gives that.  COMPILER-NOTES
   ("Symbols, addresses and small data") forbids understating an object's
   extent, so this needs another way to get the GP form for a 64-byte object. */

#include "common.h"

typedef int V4_325AE8 __attribute__((mode(TI)));

extern int func_002E67A0(int);
extern void func_002EE138(char *, char *, char *);
extern void func_002EE3D0(float, char *, char *);
extern void func_002EE220(char *, char *, char *);
extern void func_002EE178(char *, char *, float);
extern void func_002EE108(char *, char *, char *);
extern void func_002EE5D8(char *, char *, char *);
extern void func_002EAC30(char *, char *, int);
extern char D_001B8DC0[];
/* 64-byte table of four vectors; the two-element declaration is what gives the $gp addressing at -G8 (docs/COMPILER-NOTES.md) */
extern float D_001AA310[2] __attribute__((sda));

void func_L00_00325AE8(char *source, int color, float alpha, float distance)
{
    char work[0x90];
    float up[4];
    char basis[0x30];
    char position[16];
    char scaled[16];
    char *table;
    char *p;
    int i;

    *(V4_325AE8 *)up = 0;
    up[2] = 1.0f;
    up[3] = 1.0f;
    *(long long *)(work + 0x78) = func_002E67A0(0xB);
    *(long long *)(work + 0x88) = 0x0000008000000048LL;
    *(long long *)(work + 0x80) = 0x0000FF9000000260LL;
    *(long long *)(work + 0x70) = 5;
    *(int *)(work + 0x50) = 0;
    *(int *)(work + 0x54) = 0;
    *(int *)(work + 0x58) = 0;
    *(float *)(work + 0x5C) = 1.0f;
    *(float *)(work + 0x60) = 1.0f;
    *(int *)(work + 0x64) = 0;
    *(float *)(work + 0x68) = 1.0f;
    *(float *)(work + 0x6C) = 1.0f;
    qcopy(position, source);
    func_002EE138(basis, D_001B8DC0, position);
    func_002EE3D0(1.0f, basis, basis);
    func_002EE220(basis + 0x10, basis, (char *)up);
    func_002EE3D0(1.0f, basis + 0x10, basis + 0x10);
    func_002EE220(basis + 0x20, basis + 0x10, basis);
    func_002EE178(scaled, basis, distance);
    func_002EE108(position, position, scaled);
    *(int *)(work + 0x4C) = color;
    *(int *)(work + 0x48) = color;
    *(int *)(work + 0x44) = color;
    *(int *)(work + 0x40) = color;
    table = (char *)D_001AA310;
    p = work;
    for (i = 3; i >= 0; i--) {
        func_002EE178(p, table, alpha);
        table += 0x10;
        func_002EE5D8(p, p, basis);
        p += 0x10;
    }
    func_002EAC30(work, 0, 0);
}
