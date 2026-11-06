/* func_PAL_L15_00437CD0, the PAL copy of func_L15_004320B0: the same C, where scale func_00283CF0(func_002A7878(6.0f, 10.0f)). */
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
extern char *func_0029EFD0(int);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern short D_L15_001B36A8[] __attribute__((sda));
extern short D_L15_001B36B8[] __attribute__((sda));

char *func_PAL_L15_00437CD0(char *a0, char *a1) {
    char *o = func_0029EFD0(0x11AA);
    int i;

    if (o != 0) {
        char *st = *(char **)(o + 0x68);
        int r;

        *(u8 *)(o + 0x30) = 0xFF;
        *(short *)(o + 0x32) = 0xFF;
        *(u8 *)(o + 0x31) = 1;
        *(u8 *)(o + 0x20) = 1;
        *(TI128 *)(st + 0x10) = *(TI128 *)a1;
        *(TI128 *)st = *(TI128 *)a0;
        *(TI128 *)(o + 0x10) = *(TI128 *)a0;
        r = (((int)(func_00283CF0(func_002A7878(6.0f, 10.0f))) * 5 + 2) / 6);
        *(int *)(st + 0x50) = r;
        *(int *)(st + 0x54) = r * 2;
        for (i = 0; i < 3; i++) {
            D_L15_001B36A8[i] = -1;
            D_L15_001B36B8[i] = 10;
        }
    }
    return o;
}
