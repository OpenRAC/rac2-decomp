#include "common.h"

/* The counter pair gives a ratio; the three bytes and four floats are interpolated with it and
   stored in the record. Retail reaches the byte and float tables through the assembler's
   absolute macro form (MACRO_ADDR arrays), also when the load lands in a call's delay slot. */
extern int D_L00_001B0B64 __attribute__((sda));
extern int D_L00_001B0B60 __attribute__((sda));
extern float D_L00_001B0BB0 __attribute__((sda));

extern unsigned char D_L00_001B1980[] MACRO_ADDR;
extern unsigned char D_L00_001B1981[] MACRO_ADDR;
extern unsigned char D_L00_001B1982[] MACRO_ADDR;
extern float D_L00_001B2BE0[] MACRO_ADDR;
extern float D_L00_001B1984[] MACRO_ADDR;
extern float D_L00_001B1988[] MACRO_ADDR;
extern float D_L00_001B198C[] MACRO_ADDR;
extern float D_L00_001B1990[] MACRO_ADDR;

/* Measured fields of the record the fade writes. */
typedef struct {
    char pad_00[0x218];
    float f218, f21C;
    char pad_220[8];
    float f228, f22C;
    int i230, i234, i238;
} L00FadeRecord;
extern L00FadeRecord D_L00_001BD2C0;

extern void func_00282948(void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0027AB40(void);

void func_L00_003FBF78(void)
{
    float ratio;

    if (D_L00_001B0B64 <= 0) {
        return;
    }
    func_00282948(&D_L00_001B0B64);
    ratio = IntToFloat(D_L00_001B0B64) / IntToFloat(D_L00_001B0B60);
    D_L00_001BD2C0.i230 =
        FloatToInt(IntToFloat(D_L00_001B1980[0]) + (255.0f - IntToFloat(D_L00_001B1980[0])) * ratio);
    D_L00_001BD2C0.i234 =
        FloatToInt(IntToFloat(D_L00_001B1981[0]) + (255.0f - IntToFloat(D_L00_001B1981[0])) * ratio);
    D_L00_001BD2C0.i238 =
        FloatToInt(IntToFloat(D_L00_001B1982[0]) + (255.0f - IntToFloat(D_L00_001B1982[0])) * ratio);
    D_L00_001BD2C0.f218 = D_L00_001B1984[0] + -D_L00_001B1984[0] * ratio;
    D_L00_001BD2C0.f21C =
        D_L00_001B1988[0] + (D_L00_001B2BE0[0] * (D_L00_001B0BB0 * 1024.0f) - D_L00_001B1988[0]) * ratio;
    D_L00_001BD2C0.f228 = D_L00_001B198C[0] + (255.0f - D_L00_001B198C[0]) * ratio;
    D_L00_001BD2C0.f22C = D_L00_001B1990[0] + (100.0f - D_L00_001B1990[0]) * ratio;
    UpdateViewContext();
}
