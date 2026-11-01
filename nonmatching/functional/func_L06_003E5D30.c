/* functional: medium. Written from the assembly: the local 20 by 10 vector grid is a float array on the stack as in retail; the data words at the gp-relative addresses are read as plain floats. */

extern int D_001A79F0;
extern unsigned char D_0018C0D4;
extern int D_L06_001B31B0;
extern int D_L06_001B31B4;
extern float D_L06_001AF710;
extern float D_L06_001AF714;
extern float D_L06_001AF718;

extern void func_0029F338(void *);
extern int func_00282948(void *);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002A7A00(void *, float, float);

/* Moby `m` with a big variables block (`vars`, +104): state 0 gives up (removes itself) while
   the global at D_001A79F0 is 10 and D_0018C0D4 is 1; otherwise it sets D_L06_001B31B0/B4 to 45
   and 22, fills three tables of ten ints at vars+0x12C00 (i*45/10 plus 0, 11, 23 and 34) and goes
   to state 1. State 1 advances a phase at vars+0x12DE0 by D_L06_001AF718/60 (wrapping past 1),
   then for each of four sheets and ten columns: when the column's timer (vars+0x12C00 + i*120 +
   j*4) has run out, rebuilds the sheet's 20 rows (one vector per row, its y spread by
   D_L06_001AF714, a local 20 by 10 grid via func_002A7A00), sums three neighbouring rows into
   the second half of the sheet scaled by 1/3 and restarts the timer at D_L06_001B31B0; otherwise
   adds the second half onto the first. */
void func_L06_003E5D30(char *m)
{
    char *vars = *(char **)(m + 104);
    float grid[20 * 10 * 4];
    int i, j, r, k;

    if (m[32] == 0) {
        int *base;

        if (D_001A79F0 == 10 && D_0018C0D4 == 1) {
            func_0029F338(m);
            return;
        }
        D_L06_001B31B0 = 45;
        D_L06_001B31B4 = 22;
        base = (int *)(vars + 0x12D68);
        for (i = 0; i < 10; i++) {
            int q = (i * 45) / 10;

            base[i - 90] = q;
            base[i - 60] = q + 11;
            base[i - 30] = q + 23;
            base[i] = q + 34;
        }
        m[32] = 1;
        return;
    }
    if (m[32] != 1) {
        return;
    }

    {
        float phase = *(float *)(vars + 0x12DE0) + D_L06_001AF718 * 0.016666668f;

        *(float *)(vars + 0x12DE0) = phase;
        if (phase > 1.0f) {
            *(float *)(vars + 0x12DE0) = phase - 1.0f;
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 10; j++) {
            char *first = vars + i * 9600 + j * 16;
            char *second = vars + i * 9600 + 0x9600 + j * 16;
            int *timer = (int *)(vars + 0x12C00 + i * 120 + j * 4);

            if (func_00282948(timer) != 0) {
                for (r = 0; r < 20; r++) {
                    char *vec = first + r * 320;

                    func_00282C88(vec);
                    *(float *)(vec + 12) = 1.0f;
                    *(float *)(vec + 4) = (float)r * 0.05f * D_L06_001AF714 - D_L06_001AF714 * 0.5f;
                    func_002A7A00(grid + (r * 10 + j) * 4, 0.0f, D_L06_001AF710 * 0.016666668f);
                }
                for (k = 0; k < 18; k++) {
                    char *out = second + 320 + k * 320;

                    func_00282CC0(out, grid + (k * 10 + j) * 4, grid + ((k + 1) * 10 + j) * 4);
                    func_00282CC0(out, out, grid + ((k + 2) * 10 + j) * 4);
                    func_00282D30(out, out, 0.333f);
                }
                *timer = D_L06_001B31B0;
            } else {
                for (k = 0; k < 18; k++) {
                    func_00282CC0(first + 320 + k * 320, first + 320 + k * 320, second + 320 + k * 320);
                }
            }
        }
    }
}
