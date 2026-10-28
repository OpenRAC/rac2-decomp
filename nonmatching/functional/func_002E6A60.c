/* functional: medium. Same calls with the same arguments, the same nine negated floats stored to the same addresses, the 16-byte copy done as four word copies, returns the byte at record+0xC; only FPU register use and store order differ. */
extern int D_001B8840[];
extern float D_001B90F0;
extern int D_001B5340[];
extern float D_001B5200[];

extern void func_0027AB40(void);
extern void func_00129178(void *);
extern void func_001292C0(void *, void *, float);
extern void func_00129368(void *, void *, float);
extern void func_00129218(void *, void *, float);

int func_002E6A60(void)
{
    char *rec = (char *)D_001B8840[0x68 / 4] + (D_001B8840[0x38 / 4] << 5);
    unsigned char b = *(unsigned char *)(rec + 0xC);
    float m[16];
    float *out = D_001B5200;

    D_001B90F0 = *(float *)(rec + 0x1C);
    func_0027AB40();
    D_001B5340[0] = *(int *)(rec + 0);
    D_001B5340[1] = *(int *)(rec + 4);
    D_001B5340[2] = *(int *)(rec + 8);
    D_001B5340[3] = *(int *)(rec + 12);
    func_00129178(m);
    func_001292C0(m, m, *(float *)(rec + 0x10));
    func_00129368(m, m, *(float *)(rec + 0x14));
    func_00129218(m, m, *(float *)(rec + 0x18));
    out[0xDC] = -m[8];
    out[0xDD] = -m[9];
    out[0xDE] = -m[10];
    out[0xE0] = -m[0];
    out[0xE1] = -m[1];
    out[0xE2] = -m[2];
    out[0xE4] = m[4];
    out[0xE5] = m[5];
    out[0xE6] = m[6];
    return b;
}
