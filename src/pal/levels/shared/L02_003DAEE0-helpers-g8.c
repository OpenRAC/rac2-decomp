#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(u8 *, s32, s32);

extern void euler_rotation_basis(void *, void *);

extern void moby_find_nearby_record(char *);

extern void moby_update_attached_transforms(void *, void *);

/* The level's own rate, read $gp-relative. */
extern float D_L02_001B0380 __attribute__((sda));

/* Integer duration counter, in PAL read and written $gp-relative. */
extern int D_L02_001B3FD8 __attribute__((sda));

/* func_PAL_L02_003DAEE0, the PAL copy of func_L02_003D6DF8: the same C, where the rate constant becomes
   0.0003490659f and the duration gets the 50 Hz scale. */
void func_PAL_L02_003DAEE0(char *a0) {
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    TI128 v[2];
    float f;

    if (*(unsigned char *)(s0 + 0x20) != 0)
        return;
    *(unsigned char *)(s1 + 0x9) = 0;
    *(unsigned char *)(s1 + 0x8) = 3;
    *(int *)(s1 + 0x10) = 0;
    *(unsigned short *)(s0 + 0x34) &= 0xEFFF;
    moby_set_state((u8 *)s0, 2, -1);
    v[1] = 0;
    *(float *)&v[1] = D_L02_001B0380 * 0.0003490659f;
    v[0] = v[1];
    euler_rotation_basis((char *)(s1 + 0x80), (char *)&v[0]);
    f = 180.0f / D_L02_001B0380;
    *(unsigned short *)(s0 + 0x34) |= 0x100;
    D_L02_001B3FD8 = ((int)(f * 60.0f) * 5 + 2) / 6;
    moby_find_nearby_record(s0);
    moby_update_attached_transforms(s0, s1 + 0x30);
    *(int *)(s1 + 0xBC) = 0;
    *(short *)(s1 + 0xC0) = -1;
}
