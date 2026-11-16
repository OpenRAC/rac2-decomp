#include "include_asm.h"
#include "names.h"


extern double g_hit_trigger_param_a __attribute__((sda));
extern double g_hit_trigger_param_b __attribute__((sda));
extern double g_hit_trigger_param_c __attribute__((sda));
extern void func_3248E0(unsigned char *, int, int);
extern int func_326C70(unsigned char *, int, int);
extern void func_31A718(unsigned char *);
extern void func_333240(void *, void *, void *, void *, int, int, int, int, int, int, int);

/* Hand-adapted from func_L13_0038C718. */
extern int g_hit_trigger_value __attribute__((sda));
extern void func_00364DF8(int, int, void *);
extern void func_00329F80(void *, int, int);
extern void func_314008(void *);
/* Moby class 4871 update. Waits for a hit, then plays its effect and sound. */
void hit_trigger_update(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        func_3248E0(a0, 1, -1);
        break;
    case 1:
        if (func_326C70(a0, 0x04010000, 0) != 0 && *(int *)s1 == 0) {
            func_3248E0(a0, 2, -1);
            func_00364DF8(0, 0, a0);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        func_333240(a0, &g_hit_trigger_param_c, &g_hit_trigger_param_b, &g_hit_trigger_param_a, 0xFFFF, 0, g_hit_trigger_value, 0,
                    0xFFFF, 0xFF, 0);
        func_00329F80(a0, 0x1308, 0);
        func_314008(a0);
        break;
    }
}
