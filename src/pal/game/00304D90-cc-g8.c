/* func_PAL_00304D90, the PAL copy of func_00303BF8: the same C, where scale D_001B1688; scale D_001B1688; scale D_001B1688. */

extern float D_002222E0[];
extern int D_001B1688;

extern float func_00283CB8(float);
extern float func_00283198(float);
extern float func_00283180(float);

/* Fills three columns of the 64-entry, 32-byte-stride table at D_002222E0 from the state's
   parameters, one column for each flag bit (0x10, 0x40, 0x20) the state's word at +0x4C has
   clear: a sine of the wrapped phase 8 x 8 grid position, a cosine, and a sine again. */
void func_PAL_00304D90(char *object)
{
    char *state = *(char **)(object + 0x68);
    int i;

    if (~*(int *)(state + 0x4C) & 0x10) {
        for (i = 0; i < 64; i++) {
            int col = i % 8;
            int row = i / 8;

            D_002222E0[i * 8] = func_00283198(func_00283CB8(*(float *)(state + 0x38) * (float)col + *(float *)(state + 0x3C) * (float)row + (float)(((int)(D_001B1688) * 5 + 2) / 6) * *(float *)(state + 0x30)) * 6.2831855f);
        }
    }
    if (~*(int *)(state + 0x4C) & 0x40) {
        for (i = 0; i < 64; i++)
            D_002222E0[i * 8 + 1] = func_00283180(func_00283CB8((float)(((int)(D_001B1688) * 5 + 2) / 6) * D_002222E0[i * 8 + 2] / *(float *)(state + 0x24)) * 6.2831855f);
    }
    if (~*(int *)(state + 0x4C) & 0x20) {
        for (i = 0; i < 64; i++)
            D_002222E0[i * 8 + 4] = func_00283198(func_00283CB8((float)(((int)(D_001B1688) * 5 + 2) / 6) * D_002222E0[i * 8 + 3]) * 6.2831855f);
    }
}
