#include "include_asm.h"

typedef struct { float x, y, z, w; } V4_F213135aa;
extern float F213135aa_FUN_002A7878(float a, float b);
extern void F213135aa_FUN_002833F0(char *a, char *b);
extern void F213135aa_FUN_00282F20(char *a, char *b, float f);
extern void F213135aa_FUN_00282CF0(char *a, char *b, char *c);
extern void F213135aa_FUN_00282DD8(char *a, char *b, char *c);
extern void F213135aa_FUN_002AB668(char *a, char *b, float f);
extern V4_F213135aa ref_00302DA0_04[];

int func_PAL_003033A8(char *obj, char *obj2, float x, float y)
{
    V4_F213135aa m0, m1, m2;
    char *s1;
    char *s3;
    float f22;

    s1 = *(char **)(obj + 104);
    if (*(unsigned char *)(obj + 32) == 4)
        return 0;
    f22 = 0.0f;
    if (x == 0.0f)
        x = F213135aa_FUN_002A7878(-30.0f, 30.0f) * 1.7453294247388839721680e-02f;
    if (y == 0.0f)
        y = F213135aa_FUN_002A7878(f22, 30.0f) * 1.7453294247388839721680e-02f;
    s3 = s1 + 32;
    if (*(unsigned char *)(obj + 32) == 3) {
        F213135aa_FUN_002833F0((char *)&m0, s1 + 16);
        F213135aa_FUN_00282F20(s3, (char *)&m2, 0.16000001f);
    }
    *(float *)(s1 + 100) = f22;
    *(float *)(s1 + 76) = x;
    *(float *)(s1 + 72) = y;
    *(char **)(s1 + 96) = obj2;
    F213135aa_FUN_00282CF0((char *)&m1, obj2 + 16, obj + 16);
    s1 = s1 + 48;
    F213135aa_FUN_00282DD8((char *)&m0, s3, (char *)&m1);
    F213135aa_FUN_00282F20(s1, (char *)&m0, 1.0f);
    F213135aa_FUN_002AB668(s1, s1, 0.25132746f);
    *(unsigned char *)(obj + 32) = 4;
    return 1;
}


INCLUDE_ASM("asm/pal/game", func_PAL_00303548);

INCLUDE_ASM("asm/pal/game", func_PAL_00303578);

INCLUDE_ASM("asm/pal/game", func_PAL_00303950);
