/* func_PAL_002A9FA0, the PAL copy of func_002A9588: the same C, with span scaled to 50 Hz at each use. */
extern int D_L00_001AA1D4 __attribute__((sda));
extern int D_L00_001AA1D8 __attribute__((sda));
extern int func_00283D38(int, int, float);

int func_PAL_002A9FA0(int first, int second, int span, int mode, int reset)
{
    int *counter = &D_L00_001AA1D8;
    int phase;
    float amount;
    if (mode == 0) counter = &D_L00_001AA1D4;
    ++*counter;
    if (reset)
        *counter = 0;
    phase = *counter % (((span * 2) * 5 + 2) / 6);
    if (phase >= (span * 5 + 2) / 6)
        amount = 1.0f - (float)(phase - (span * 5 + 2) / 6) / (float)((span * 5 + 2) / 6);
    else
        amount = (float)phase / (float)((span * 5 + 2) / 6);
    return func_00283D38(second, first, amount);
}
