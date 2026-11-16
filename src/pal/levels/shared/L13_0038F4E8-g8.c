#include "include_asm.h"
#include "names.h"
extern double g_fade_in_param_c __attribute__((sda));
extern double g_fade_in_param_b __attribute__((sda));
extern double g_fade_in_param_a __attribute__((sda));
extern void func_3248E0(unsigned char *, int, int);
extern int func_326C70(unsigned char *, int, int);
extern void func_31A718(unsigned char *);
extern void func_333240(void *, void *, void *, void *, int, int, int, int, int, int, int);

void fade_in_update_pal(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        func_3248E0(a0, 1, -1);
        break;
    case 1:
        if (func_326C70(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0)
            func_3248E0(a0, 2, -1);
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_333240(a0, &g_fade_in_param_a, &g_fade_in_param_b, &g_fade_in_param_c, 0xFFFF, 0, -1, 0,
                    0xFFFF, 0xFF, 0);
        func_31A718(a0);
        break;
    }
}
