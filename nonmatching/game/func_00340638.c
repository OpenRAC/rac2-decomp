/* func_00340638 - 448 bytes.  Worker attempt, 27 October 2026 (draft below).

   432 B vs 448. Natural: six 8-byte local copies (struct of 2 floats) from
   D_001AE098/A0/98/A8/90/B0 compile to the same ldl/ldr/sdl/sdr at
   sp+0,0x10..0x50 as retail; 23-word descriptor f[] like func_00344F98. Store
   order after the func_00336390 call decoded from retail.
   Diff: retail keeps the default store f[21]=1 as sw t6,0x54(s6) with s6=&f
   (=sp+0x60) held across the call (daddu a0,s6) while the later f[21]=(x==1)
   store is sp-relative; mine drops the first store (dead) and uses addiu
   a0,sp,0x60. Needs a way for cse to not see them as the same address
   (pointer base). Also f[20]=0 before the call is kept in both. */

/* in src/game/0033F030.c replacing the INCLUDE_ASM */
typedef struct { float x, y; } Pair340638;

extern Pair340638 D_001AE098;
extern Pair340638 D_001AE0A0;
extern Pair340638 D_001AE0A8;
extern Pair340638 D_001AE090;
extern Pair340638 D_001AE0B0;
extern char D_00259CE0[];
extern char *D_001A8CFC;
extern void func_00336390(char *, char *, int);
extern void func_00337210(int *);

void func_00340638(char *o)
{
    Pair340638 p0 = D_001AE098;
    Pair340638 p1 = D_001AE0A0;
    Pair340638 p2 = D_001AE098;
    Pair340638 p3 = D_001AE0A8;
    Pair340638 p4 = D_001AE090;
    Pair340638 p5 = D_001AE0B0;
    int f[23];

    f[20] = 0;
    f[21] = 1;
    f[21] = *(int *)(o + 0x81C) == 1;
    f[16] = (int)(o + 0xA18);
    f[19] = *(int *)(o + 0x820);
    f[3] = *(int *)(o + 0x814);
    f[4] = *(int *)(o + 0x818);
    f[9] = (int)&p4;
    f[14] = 1;
    f[0] = (int)D_00259CE0;
    f[1] = 3;
    f[2] = 2;
    f[17] = (int)(o + 0x870);
    f[13] = 0;
    func_00336390(o + 0x17C, D_001A8CFC + 0x8710, 0x5D);
    f[10] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x7D0);
    f[8] = (int)&p3;
    f[7] = (int)&p2;
    f[6] = (int)&p1;
    f[20] = (int)&p5;
    f[12] = (int)(o + 0x214);
    f[18] = *(int *)(o + 0x80C);
    f[11] = 0;
    f[5] = (int)&p0;
    f[22] = 0;
    func_00337210(f);
}
