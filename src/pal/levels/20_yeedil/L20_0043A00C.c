#include "include_asm.h"

#include "common.h"
extern f32 func_00303270(f32, f32);
extern s32 path_check_entry_for_moby(char *, s32);
extern f32 vec_distance_xy(void *, void *);
extern char *D_L20_001FEC80[];

s32 func_PAL_L20_0043A610(char *arg0, s32 arg1) {
    char *s1 = arg0;
    s32 s0 = arg1;
    char *s3;
    s32 s2;
    f32 f0;

    s3 = *(char **)(s1 + 0x68);
    s2 = path_check_entry_for_moby(s1, s0);
    if (s2 == 0) {
        if (s0 != -1) {
            f0 = vec_distance_xy(s1 + 0x10,
                               D_L20_001FEC80[s0] + ((*(s16 *)(s3 + 0x1CA) << 4) + 0x10));
            if (!(*(f32 *)(s3 + 0x134) > f0)) {
            } else {
                s2 = 1;
            }
        }
    }
    return s2;
}


