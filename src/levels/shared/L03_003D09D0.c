#include "include_asm.h"
#include "common.h"

extern char *func_003113F0(int);
extern void func_002EF818(char *, char *);

/* Creates an interpolated particle emitter (moby class 2527) with its position, speed and fade time. */
char *part_create_interpolated_emitter(int owner, int attachment, void *position, void *offset, void *velocity, int duration, int timer, int rayMask)
{
    char *moby = func_003113F0(0x9DF /* moby class 2527 */);
    char *vars;

    if (moby != 0) {
        *(int *)(moby + 0xB8) = owner;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        vars = *(char **)(moby + 0x68);
        *(short *)(moby + 0x32) = 0xFF;
        func_002EF818(moby + 0xC0, moby + 0xF0);
        qcopy(moby + 0x10, position);
        qcopy(vars, offset);
        qcopy(vars + 0x10, velocity);
        *(int *)(vars + 0x40) = attachment;
        *(int *)(vars + 0x28) = timer;
        *(float *)(vars + 0x24) = 1.0f / (float)duration;
        *(int *)(vars + 0x38) = rayMask;
        *(int *)(vars + 0x34) = 0;
        *(int *)(vars + 0x20) = 0;
    }
    return moby;
}
