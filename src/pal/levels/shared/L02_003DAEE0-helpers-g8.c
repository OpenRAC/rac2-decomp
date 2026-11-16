#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(u8 *, s32, s32);

extern void euler_rotation_basis(void *, void *);

extern void moby_find_nearby_record(char *);

extern void moby_update_attached_transforms(void *, void *);

/* The level's own rate, read $gp-relative. */
extern float g_platform_rotation_speed_degrees __attribute__((sda));

/* Integer duration counter, in PAL read and written $gp-relative. */
extern int g_snd_emitter_cooldown __attribute__((sda));

/* func_PAL_L02_003DAEE0, the PAL copy of func_L02_003D6DF8: the same C, where the rate constant becomes
   0.0003490659f and the duration gets the 50 Hz scale. */
void platform_init_pal(char *moby) {
    char *moby_ref = moby;
    char *vars = *(char **)(moby_ref + 0x68);
    TI128 euler_vec[2];
    float spin_time;

    if (*(unsigned char *)(moby_ref + 0x20) != 0)
        return;
    *(unsigned char *)(vars + 0x9) = 0;
    *(unsigned char *)(vars + 0x8) = 3;
    *(int *)(vars + 0x10) = 0;
    *(unsigned short *)(moby_ref + 0x34) &= 0xEFFF;
    moby_set_state((u8 *)moby_ref, 2, -1);
    euler_vec[1] = 0;
    *(float *)&euler_vec[1] = g_platform_rotation_speed_degrees * 0.0003490659f;
    euler_vec[0] = euler_vec[1];
    euler_rotation_basis((char *)(vars + 0x80), (char *)&euler_vec[0]);
    spin_time = 180.0f / g_platform_rotation_speed_degrees;
    *(unsigned short *)(moby_ref + 0x34) |= 0x100;
    g_snd_emitter_cooldown = ((int)(spin_time * 60.0f) * 5 + 2) / 6;
    moby_find_nearby_record(moby_ref);
    moby_update_attached_transforms(moby_ref, vars + 0x30);
    *(int *)(vars + 0xBC) = 0;
    *(short *)(vars + 0xC0) = -1;
}
