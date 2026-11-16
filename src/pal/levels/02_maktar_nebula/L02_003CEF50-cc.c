#include "names.h"
/* func_PAL_L02_003CEF50, the PAL copy of func_L02_003CB090: the same C, where scale func_0031E7B0(D_L02_gp10B0, D_001B00A4); rename func_002F1BE0 becomes func_00282978; rename func_0031E7B0 becomes func_002A7820; rename func_00366B30 becomes func_002E5CF8. */

typedef unsigned int u32;
typedef short s16;

extern int D_L02_gp10B0 __attribute__((sda));
extern unsigned int g_path_enemy_refresh_range __attribute__((nosda));

extern int FastDecTimer(void *);
extern s16 math_random_int_range(int, unsigned int);
extern int PlayMobySound(int, int, void *);

void func_PAL_L02_003CEF50(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);

    if (FastDecTimer(s0 + 0x3B4) != 0) {
        *(s16 *)(s0 + 0x3B4) = (((int)(math_random_int_range(D_L02_gp10B0, g_path_enemy_refresh_range)) * 5 + 2) / 6);
        PlayMobySound(1, 0, a0);
    }
}
