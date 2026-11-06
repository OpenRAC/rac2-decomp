/* func_PAL_L02_003CEF50, the PAL copy of func_L02_003CB090: the same C, where scale func_0031E7B0(D_L02_gp10B0, D_001B00A4); rename func_002F1BE0 becomes func_00282978; rename func_0031E7B0 becomes func_002A7820; rename func_00366B30 becomes func_002E5CF8. */

typedef unsigned int u32;
typedef short s16;

extern int D_L02_gp10B0 __attribute__((sda));
extern unsigned int D_001B00A4 __attribute__((nosda));

extern int func_00282978(void *);
extern s16 func_002A7820(int, unsigned int);
extern void func_002E5CF8(int, int, void *);

void func_PAL_L02_003CEF50(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);

    if (func_00282978(s0 + 0x3B4) != 0) {
        *(s16 *)(s0 + 0x3B4) = (((int)(func_002A7820(D_L02_gp10B0, D_001B00A4)) * 5 + 2) / 6);
        func_002E5CF8(1, 0, a0);
    }
}
