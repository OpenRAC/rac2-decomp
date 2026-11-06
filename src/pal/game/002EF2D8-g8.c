/* func_PAL_002EF2D8, the PAL copy of func_002EE3B0: the same C, with the 60 Hz values scaled by 6/5
 * for 50 Hz and both rates multiplied by 1.2f at the end. */
#include "common.h"

extern char *func_002ED688(unsigned char *);
extern int func_002EE6A8(unsigned char *);
extern float D_001AC248 __attribute__((sda));
extern float D_001AC240 __attribute__((sda));
extern float D_001AC244 __attribute__((sda));

void func_PAL_002EF2D8(unsigned char *owner)
{
    char *object = func_002ED688(owner);
    int state;

    if (!object)
        return;
    if (*(unsigned char **)(object + 0x10))
        state = func_002EE6A8(*(unsigned char **)(object + 0x10));
    else
        state = func_002EE6A8(owner);
    if (state == 3) {
        D_001AC248 = 0.50000006f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 1) {
        D_001AC248 = 0.48000002f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 13) {
        D_001AC248 = 0.48000002f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 2) {
        D_001AC248 = 0.16000001f;
        D_001AC240 = 0.005f;
        D_001AC244 = 0.025f;
    } else if (state == 5) {
        D_001AC248 = 0.50000006f;
        D_001AC240 = 0.04f;
        D_001AC244 = 0.2f;
    } else if (state == 6) {
        D_001AC248 = 0.44000003f;
        D_001AC240 = 0.03f;
        D_001AC244 = 0.15f;
    } else if (state == 4) {
        D_001AC248 = 0.6f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 8) {
        D_001AC248 = 0.50000006f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 7) {
        D_001AC248 = 0.20000002f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 11) {
        D_001AC248 = 0.6f;
        D_001AC240 = 0.02f;
        D_001AC244 = 0.1f;
    } else if (state == 12) {
        float *duration = *(float **)(object + 0x154);
        D_001AC248 = duration ? *duration * 0.020000001f : 0.20000002f;
        D_001AC240 = 0.005f;
        D_001AC244 = 0.025f;
    }
    if (*(int *)(object + 0x108) && state != 11 && state != 2 && state != 12) {
        D_001AC240 *= 0.7f;
        D_001AC244 *= 0.7f;
    }
    D_001AC240 *= 1.2f;
    D_001AC244 *= 1.2f;
}
