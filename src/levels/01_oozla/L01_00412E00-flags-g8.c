#include "include_asm.h"
#include "names.h"


extern double g_flash_burst_param_c __attribute__((sda));
extern double g_flash_burst_param_b __attribute__((sda));
extern double g_flash_burst_param_a __attribute__((sda));
extern void func_3248E0(unsigned char *, int, int);
extern int func_326C70(unsigned char *, int, int);
extern void func_333240(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_00364DF8(int, int, void *);
extern void func_00329F80(void *, int, int);
extern void func_314008(void *);

/* Hand-adapted from func_L12_00388090. */
extern int g_level_unused_word __attribute__((sda));
extern int g_oozla_intro_timer;
extern int ref_L01_00412E00_00 __attribute__((sda));
/* Counts itself, waits for the player to trigger it and then flashes an effect. */
void triggered_flash_update(unsigned char *moby) {
    unsigned char *vars = *(unsigned char **)(moby + 0x68);

    switch (moby[0x20]) {
    case 0:
        ref_L01_00412E00_00 = ref_L01_00412E00_00 + 1;
        func_3248E0(moby, 1, -1);
        break;
    case 1:
        if (func_326C70(moby, 0x04010000, 0) != 0 && *(int *)vars == 0) {
            ref_L01_00412E00_00 = g_oozla_intro_timer - 1;
            func_3248E0(moby, 2, -1);
        }
        moby[0xA8] = 0xFF;
        break;
    case 2:
        func_333240(moby, &g_flash_burst_param_a, &g_flash_burst_param_b, &g_flash_burst_param_c, 0xFFFF, 0, -1, 0,
                    0xFFFF, 0xFF, 0);
        func_314008(moby);
        break;
    }
}
