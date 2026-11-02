/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* 260/268; us/us2/pal 0/3 each.
 * Profile: -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * The compiler reuses the point-table base to form the previous point, while retail rematerializes its base minus 16. The row stride is honestly 40 quadwords; no artificial containing header or alias was introduced. Reopen with genuine containing data-layout evidence.
 */
typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));
extern int D_L11_001B25A0 __attribute__((sda));
extern int D_L11_001B25A4 __attribute__((sda));
extern float D_L11_001B25A8 __attribute__((sda));
extern unsigned int D_L11_001B25C0 __attribute__((sda));
extern unsigned int D_L11_001B25C8 __attribute__((sda));
extern unsigned int D_L11_001B25DC __attribute__((sda));
extern TI128 D_L11_00264760[][40];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_L11_0046BC08(u8 *object) {
    float delta[4], step[4];
    u8 *data = *(u8 **)(object + 0x68);
    int i;
    if (D_L11_001B25A4) {
        D_L11_001B25A4 = 0;
        func_00282CF0(delta, data + 0x10, data);
        func_00282F20(step, delta, D_L11_001B25A8 / (float)D_L11_001B25A0);
        D_L11_00264760[*(int *)(data + 0x38)][0] = *(TI128 *)data;
        for (i = 1; i < D_L11_001B25A0; i++)
            func_00282CC0(&D_L11_00264760[*(int *)(data + 0x38)][i], &D_L11_00264760[*(int *)(data + 0x38)][i - 1], step);
        D_L11_001B25C0 = 0;
        D_L11_001B25C8 = 0;
        D_L11_001B25DC = 0;
    }
}
