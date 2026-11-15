#include "include_asm.h"
#include "names.h"


extern int func_419B10(void *, void *, int, void *, void *, void *, float, float);
extern void func_32D0F0(void *, int, float);
float bot_compute_speed_from_turn(unsigned char *);

int func_PAL_L03_003C81C8(unsigned char *a0, int a1, int a2) {
    unsigned char *s0 = *(unsigned char **)(a0 + 0x68);
    float f = 0.0f;
    float out;
    int r;

    if (a2 != 0)
        f = bot_compute_speed_from_turn(a0);
    r = func_419B10(*(void **)(s0 + 0x220), a0 + 0x10, a1, &out, s0 + 0x368, s0 + 0x36C, f,
                    *(float *)(s0 + 0x110));
    func_32D0F0(a0, a1, out);
    return r;
}




