extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_L16_00414038(void *, float, int, int, int, float, float, int, void *);
extern float D_001B197C __attribute__((sda));
extern float D_001B1980 __attribute__((sda));
extern int D_001B193C __attribute__((sda));
extern int D_001B1940 __attribute__((sda));
extern int D_001B1974 __attribute__((sda));
extern int D_001B1978 __attribute__((sda));

void func_L30_0040E660(char *a0) {
    func_L16_00414038(a0 + 0x10, D_001B197C * *(float *)(a0 + 0x2C), D_001B193C, func_002A7820(0x5F, 0x6F), D_001B1974, func_002A7940(), 1.0f, 2, a0);
    func_L16_00414038(a0 + 0x10, D_001B197C * *(float *)(a0 + 0x2C) * D_001B1980, D_001B1940, func_002A7820(0x6F, 0x7F), D_001B1978, func_002A7940(), 1.0f, 2, a0);
}
