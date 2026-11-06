/* func_PAL_L20_00444E38, the PAL copy of func_L20_0043F460: the same C, where rename func_002BDBC0 becomes func_PAL_002BE880; scale func_002A7820(0x14, 0x50). */

/* func_L20_00444088 is defined in L20_00444088-g8.c (it needs its own flags). */

extern float D_L20_001B1FD0 __attribute__((sda));

extern float D_L20_001B1FD4;

extern int D_L20_001B1FC0 __attribute__((sda));

extern int D_L20_001B1FC4 __attribute__((nosda));

extern int D_001B1FC4 __attribute__((nosda));

extern int D_L20_001B1FC8 __attribute__((nosda));

extern int D_L20_001B1FCC __attribute__((nosda));

extern char D_L20_001A8F20[];

extern float func_002A7878(float, float);

extern int func_002A7820(int, int);

extern void func_PAL_002BE880(char *, char *, int, int, int, float);

void func_PAL_L20_00444E38(char *arg0) {
    char *s0 = arg0;
    float f20;
    int r;
    int v[2];

    f20 = func_002A7878(D_L20_001B1FD0, D_L20_001B1FD4) * 210000.0f;
    r = (((int)(func_002A7820(0x14, 0x50)) * 5 + 2) / 6);
    if (*(short *)(s0 + 0xAA) == 0xB5A) {
        v[0] = D_L20_001B1FC0;
        v[1] = D_001B1FC4;
    } else {
        v[0] = D_L20_001B1FC8;
        v[1] = D_L20_001B1FCC;
    }
    func_PAL_002BE880(s0 + 0x10, D_L20_001A8F20, D_L20_001B1FC0, D_L20_001B1FC4, r, f20);
}
