/* func_0032F3D0 - 444 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Decoded fully (see draft; D_001B0960 sda gate, two func_00300A00 calls,
   sprintf, func_0027F5B8). Needs -G8 -Wa,-G32 unit. Default flags: 448 vs 444
   B: mine hoists 451.0f into a 6th callee-saved FP reg (retail keeps 380.0,
   0.5, -0.5, 1.0, 0.0 only, reloads 451.0 per call) and retail saves an
   unused s0 (frame 0xA0 vs 0x90). -fno-expensive-optimizations gives only 3
   FP regs (428 B). */

extern void func_00300A00(int, int, float, float, float, float, float);

extern int D_001B0960 __attribute__((sda));
extern int D_001A8CFC;
extern float D_001B23A4;
extern int D_001B2840;
extern char D_001B0978[];
extern int func_00336D50(int, int);
extern int func_00283CF0(float);
extern void func_002ED578(int, int *, int *, int *);
extern void func_00115DA8(char *, char *, ...);
extern void func_0027F5B8(int, int, unsigned long, char *, int);

int func_0032F3D0(void) {
    char text[64];
    int x;
    int y;
    int z;
    int r;
    float zero;

    if (D_001B0960) {
        zero = 0.0f;
        r = func_00336D50(D_001A8CFC + 0x8710, 0xC1);
        func_00300A00(r, 0x60442D00, 451.0f, (float)(int)(D_001B23A4 * 380.0f + 0.5f), -0.5f, 1.0f, zero);
        r = func_00336D50(D_001A8CFC + 0x8710, 0xC2);
        func_00300A00(r, 0x55F0C070, 451.0f, (float)(int)(D_001B23A4 * 380.0f + 0.5f), -0.5f, 1.0f, zero);
        func_002ED578(D_001B2840, &x, &y, &z);
        func_00115DA8(text, D_001B0978, x, y, z);
        func_0027F5B8(func_00283CF0(406.25f), (int)(D_001B23A4 * 372.0f + 0.5f), 0x80808080, text, 0x80);
    }
    return 1;
}
