/* Historical unsafe draft, preserved for comparison. The measured rate is
   1/60, not 1/120. func_00282F70 takes one float; the negative acceleration
   belongs to func_L00_0031CDD0, which takes an optional output pointer and two
   floats. Use func_L07_003F43E0-ballistic.c for the corrected contracts. */
/* Mid worker 7: near miss, flags -O2 -G8 -ffunction-sections -frac2-qcopy (own file, 408 B, frame 0xA0 with the
   float[16] local). Calls, arguments, frame and every store match; 15 instructions differ only in float
   load / multiply scheduling: retail loads the $gp scalar 0x1E48 first (f1), then 0x24(obj) -> f0, 0x1E44 (f20),
   0x1E40 (f21) and reuses f1 for the 1/3600 constant; ours loads the scalars after the pointer chain and keeps
   a fourth float register. All 360 valid orderings of the six statements, with and without -g, give 15-18 diffs. */
typedef int TI128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int id);
extern void func_002B37E8(char *obj, char *arg);
extern float func_002A7940(void);
extern void func_002833F0(char *dst, char *src);
extern void func_00282CF0(char *dst, char *a, char *b);
extern void func_00282F70(char *dst, char *src, float a, float b);
extern float func_L00_0031CDD0(char *a, char *b, int c, float d);
extern void func_00283698(char *dst, char *src);
extern void func_00283098(char *dst, char *src, char *m);
extern float D_L07_001B0E30 __attribute__((sda));
extern float D_L07_001B0E34 __attribute__((sda));
extern float D_L07_001B0E38 __attribute__((sda));

char *func_L07_003F43E0(char *a0, char *a1, char *a2, char *a3, float a4)
{
    char *obj = func_0029EFD0(0xE1D);

    if (obj != 0) {
        char *st;
        float f20;
        float f21;
        float buf[16];

        func_002B37E8(obj, a0);
        *(TI128 *)(obj + 0x10) = *(TI128 *)a2;
        *(float *)(obj + 0xF8) = func_002A7940();
        *(float *)(obj + 0xF0) = func_002A7940();
        func_002833F0(obj + 0xC0, obj + 0xF0);
        *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
        st = *(char **)(obj + 0x68);
        *(char **)(st + 0x20) = a1;
        f20 = D_L07_001B0E34 * (1.0f / 120.0f);
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * D_L07_001B0E38;
        f21 = D_L07_001B0E30 * (1.0f / 3600.0f);
        func_00282CF0(st + 0x10, a3, obj + 0x10);
        func_00282F70(st + 0x10, st + 0x10, f20, -f21);
        *(float *)(st + 0x18) = func_L00_0031CDD0(obj + 0x10, a3, 0, f20);
        *(float *)(st + 0x1C) = f21;
        *(float *)(st + 0x34) = a4;
        if (a1 != 0) {
            func_00283698((char *)buf, a1 + 0xC0);
            func_00283098(st + 0x10, st + 0x10, (char *)buf);
            func_00282CF0(st, obj + 0x10, a1 + 0x10);
            func_00283098(st, st, (char *)buf);
        }
    }
    return obj;
}
