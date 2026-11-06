typedef struct GornConfig { int words[10]; } GornConfig;
extern char D_L10_00221CD0[];
extern GornConfig D_L10_002A3C70[];
extern int D_L10_001B13A4 __attribute__((sda));
extern char *D_L10_001B13F0 __attribute__((sda));
extern int D_L10_001B1440 __attribute__((sda));
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern int func_002ED8A0(int);
extern void func_L05_00379F28(int);
extern int func_L05_00442860(void);
extern void func_L05_0037D6E8(void);
extern void func_L05_00379F68(void);
extern void func_L05_00445A98(void);

/* func_US2_L10_00425104, the v2.00 copy of func_L10_004235A0: the same C, without removing the two
   temporary objects. */
void func_US2_L10_00425104(void) {
    char *state;
    int i;
    func_L05_0037B210();
    func_L05_00379F18(1);
    state = D_L10_00221CD0;
    *(int *)(state + 0x28) = 100;
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0xC) = 0;
    D_L10_001B13A4 = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x2C) = 1;
    i = func_002ED8A0(6);
    D_L10_001B1440 = 0;
    *(float *)(state + 0x30) = 8.0f;
    D_L10_002A3C70[i].words[5] = D_L10_002A3C70[i].words[4];
    func_L05_00379F28(0);
    if (func_L05_00442860()) {
        *(int *)(state + 0x2C) = 0;
        D_L10_001B13F0[0x20] = 1;
    }
    func_L05_0037D6E8();
    func_L05_00379F68();
    func_L05_00445A98();
}
