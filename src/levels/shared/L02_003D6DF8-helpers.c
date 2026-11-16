#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(u8 *, s32, s32);

extern void euler_rotation_basis(void *, void *);

extern void moby_find_nearby_record(char *);

extern void moby_update_attached_transforms(void *, void *);

/* The level's own rate, read $gp-relative. */
extern float g_platform_rotation_speed_degrees __attribute__((sda));

/* Integer duration counter: readers use integer loads; this store is absolute. */
extern int g_snd_emitter_cooldown NOT_SDA;

/* Sets up a moving platform when it first appears: sets its turn speed, its timer and its starting state. */
void platform_init(char *moby_arg) {
    char *moby = moby_arg;
    char *vars = *(char **)(moby + 0x68);
    TI128 rotation[2];
    float seconds;

    if (*(unsigned char *)(moby + 0x20) != 0)
        return;
    *(unsigned char *)(vars + 0x9) = 0;
    *(unsigned char *)(vars + 0x8) = 3;
    *(int *)(vars + 0x10) = 0;
    *(unsigned short *)(moby + 0x34) &= 0xEFFF;
    moby_set_state((u8 *)moby, 2, -1);
    rotation[1] = 0;
    *(float *)&rotation[1] = g_platform_rotation_speed_degrees * 0.0002908882452175021f;
    rotation[0] = rotation[1];
    euler_rotation_basis((char *)(vars + 0x80), (char *)&rotation[0]);
    seconds = 180.0f / g_platform_rotation_speed_degrees;
    *(unsigned short *)(moby + 0x34) |= 0x100;
    g_snd_emitter_cooldown = (int)(seconds * 60.0f);
    moby_find_nearby_record(moby);
    moby_update_attached_transforms(moby, vars + 0x30);
    *(int *)(vars + 0xBC) = 0;
    *(short *)(vars + 0xC0) = -1;
}
