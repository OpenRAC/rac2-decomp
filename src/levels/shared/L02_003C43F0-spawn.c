
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

/* Spawns a moby of class 2906 at a position and fills in its private values. Returns the new object, or 0 if none could be made. */
char *part_spawn_trail_effect_moby(TI128 *position, TI128 *dataVec0, TI128 *dataVec10, unsigned char flag75,
                        unsigned char flag76, unsigned char flag77, float value6C, float value68, float value64) {
    char *moby;
    char *vars;
    struct SpawnHeader *header;

    moby = CreateMoby(0xB5A /* moby class 2906 */);
    if (moby == 0)
        goto end;
    qcopy(moby + 0x10, position);
    header = (struct SpawnHeader *)moby;
    header->rate = 0.014999999664723873f;
    header->kind = 0xFF;
    header->flags = 0xFF;
    header->mode = 0;
    vars = *(char **)(moby + 0x68);
    qcopy(vars, dataVec0);
    qcopy(vars + 0x10, dataVec10);
    *(int *)(vars + 0x70) = 0x10E;
    *(unsigned char *)(vars + 0x75) = flag75;
    *(unsigned char *)(vars + 0x76) = flag76;
    *(unsigned char *)(vars + 0x77) = flag77;
    *(float *)(vars + 0x68) = value68;
    *(float *)(vars + 0x6C) = value6C;
    *(float *)(vars + 0x64) = value64;
    func_002A0F48(moby);
end:
    return moby;
}
