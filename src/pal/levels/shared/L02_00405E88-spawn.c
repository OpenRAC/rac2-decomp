/* func_PAL_L02_00405E88, the PAL copy of func_L02_00401530: the same C with the 270-frame count
   becomes 225. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

struct SpawnHeader {
    u8 unknown000[0x20];
    u8 mode;
    u8 unknown021[11];
    f32 rate;
    u8 flags, unknown031;
    u16 kind;
};

extern char *CreateMoby(int);

extern void func_002A0F48(void *);

/* Creates a projectile trail moby with the given position, velocity and settings (PAL: 225 frames). */
char *part_spawn_trail_effect_moby_pal(TI128 *position, TI128 *velocity, TI128 *target, unsigned char count_min,
                        unsigned char count_max, unsigned char interval, float damage, float unk_param, float approach_rate) {
    char *moby;
    char *vars;
    struct SpawnHeader *header;

    moby = CreateMoby(0xB5A);
    if (moby == 0)
        goto end;
    qcopy(moby + 0x10, position);
    header = (struct SpawnHeader *)moby;
    header->rate = 0.014999999664723873f;
    header->kind = 0xFF;
    header->flags = 0xFF;
    header->mode = 0;
    vars = *(char **)(moby + 0x68);
    qcopy(vars, velocity);
    qcopy(vars + 0x10, target);
    *(int *)(vars + 0x70) = 0xE1;
    *(unsigned char *)(vars + 0x75) = count_min;
    *(unsigned char *)(vars + 0x76) = count_max;
    *(unsigned char *)(vars + 0x77) = interval;
    *(float *)(vars + 0x68) = unk_param;
    *(float *)(vars + 0x6C) = damage;
    *(float *)(vars + 0x64) = approach_rate;
    func_002A0F48(moby);
end:
    return moby;
}
