/* func_L00_004003F0 - 444 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_L00_004003F0 448B vs 444B. Callee names are the boot copies
   (func_00336D50, func_00300A00, func_002ED578, func_0027F5B8, func_00115DA8)
   with real prototypes taken from matched callers. Reads of
   D_L00_001A904C/001B2704/001B2C10 are incomplete sda arrays (tied lui/lw
   form) and match. Left: (1) retail saves f20-f24 (five consts: 380.0, 0.5,
   -0.5, 1.0, 0.0) and reloads 454.0f (lui/mtc1 f12) before each func_00300A00
   call; mine also keeps 454.0f in a saved reg (f25). (2) retail saves $s0 and
   never uses it (s0,s1,ra saved, only s1=0x8710 used): frame 0xA0 vs mine
   0x90. Not reachable with the C I tried. */

/* in place of the marker in src/levels/shared/L00_003FFA70.c */
extern int D_L00_001B0CA0 __attribute__((sda));
extern char *D_L00_001A904C[] __attribute__((sda));
extern float D_L00_001B2704[] __attribute__((sda));
extern int *D_L00_001B2C10[] __attribute__((sda));
extern char D_L00_001B0CB8[];
extern int func_00336D50(int, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern void func_002ED578(int, int *, int *, int *);
extern int func_00115DA8(char *, char *, ...);
extern int func_002EF250(float);
extern void func_0027F5B8(int, int, long, int, int);

int func_L00_004003F0(void)
{
    char text[64] __attribute__((aligned(16)));
    int a;
    int b;
    int c;
    int obj;

    if (D_L00_001B0CA0 != 0) {
        obj = func_00336D50((int)(D_L00_001A904C[0] + 0x8710), 0xC1);
        func_00300A00(obj, 0x60442D00, 454.0f, (int)(D_L00_001B2704[0] * 380.0f + 0.5f), -0.5f, 1.0f, 0.0f);
        obj = func_00336D50((int)(D_L00_001A904C[0] + 0x8710), 0xC2);
        func_00300A00(obj, 0x55F0C070, 454.0f, (int)(D_L00_001B2704[0] * 380.0f + 0.5f), -0.5f, 1.0f, 0.0f);
        func_002ED578((int)D_L00_001B2C10[0], &a, &b, &c);
        func_00115DA8(text, D_L00_001B0CB8, a, b, c);
        func_0027F5B8(func_002EF250(405.0f), (int)(D_L00_001B2704[0] * 372.0f + 0.5f), 0x80808080, (int)text, 0x80);
    }
    return 1;
}
