#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L05_003D5D90);


#include "common.h"
extern float func_002A7878(float a, float b);
extern float D_L05_0023F920[][4][137][4];
extern float D_L05_0024A460[][4][137];
extern float D_L05_0024D020[][4][4];
extern int D_L05_0024CFD0[][4], D_L05_0024CF30[][4], D_L05_0024CF80[][4];
extern float D_L05_001B2F58[] __attribute__((sda)), D_L05_001B2F88[] __attribute__((sda));
extern float D_L05_001B2FB8[] __attribute__((sda)), D_L05_001B2FD0[] __attribute__((sda));
extern int D_L05_001B2F70[] __attribute__((sda)), D_L05_001B2FE8[] __attribute__((sda));
extern int D_L05_001B2FA0[] __attribute__((sda));
extern int func_001163B0(void);
extern void func_00282C88(void *);

/* Clears the four emitters' 137 vectors of the object's slot, gives each a random speed, and
   starts the emitters around the object's position with random fades and lifetimes. */
void func_PAL_L05_003D7130(char *obj)
{
    int *st = *(int **)(obj + 0x68);
    char *position = obj + 0x10;
    int i, j;
    float *v;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 137; j++) {
            float speed = func_002A7878(0.5f, 4.0f);

            func_00282C88(D_L05_0023F920[*st][i][j]);
            D_L05_0024A460[*st][i][j] = speed;
        }
        /* This slot and the actor position do not contain the private index. */
        qcopy_nc(D_L05_0024D020[*st][i], position);
        D_L05_0024CFD0[*st][i] = 5;
        D_L05_0024CF30[*st][i] = func_001163B0() % 128 + 128;
        D_L05_0024CF80[*st][i] = func_001163B0() % 2 + 6;
        {
            float jitter = func_002A7878(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[0] += jitter;
        }
        {
            float jitter = func_002A7878(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[1] += jitter;
        }
        {
            float jitter = func_002A7878(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)D_L05_0024D020 + offset);
            v[2] += jitter;
        }
    }
    D_L05_001B2F58[*st] = 0.01f;
    D_L05_001B2F70[*st] = 128;
    D_L05_001B2F88[*st] = 0.1f;
    D_L05_001B2FE8[*st] = 5;
    D_L05_001B2FA0[*st] = 128;
    D_L05_001B2FB8[*st] = 0.0f;
    D_L05_001B2FD0[*st] = 0.0f;
}

