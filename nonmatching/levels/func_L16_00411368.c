/*
 * func_L16_00411368: check.py passed (func_L16_00411368: 1 of 1 places match (src/levels/16_snivelak/L16_00403900.c)), but it calls func_L16_00411368_period, defined in the same unit and not placed everywhere func_L16_00411368 is: the strict build would reject it ('needs .text.<callee> at its place, which is not C'). Needs an arrangement where those calls are external.
 */
void func_L16_00411368(u8 *arg)
{
    u8 *s0;
    u8 *s1;
    float f20;
    float period = 120.0f;

    s0 = arg;
    s1 = *(u8 **)(arg + 0x68);
    f20 = 10.0f;
    if (s0[0x20] == 0xD || s0[0x20] == 0xF || s0[0x20] == 0xE || s0[0x20] == 0x11)
        f20 = 25.0f;
    f20 = f20 + func_00283198((float)(D_L16_001B2648 % func_L16_00411368_period(120.0f)) / period * 6.2831855f - 3.1415927f);
    func_002AA548(s0 + 0x18, s1 + 0x268, *(float *)(s1 + 0x264) + f20,
                  0.0083333338f, 0.0027777778f, 0.16666667f);
    func_L16_00412F48(s0);
}
