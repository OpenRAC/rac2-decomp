#include "include_asm.h"
#include "names.h"
typedef int Q128 __attribute__((mode(TI)));

extern char *func_0029EFD0(int);
extern void func_002AEC18(void *a0, int a1);
extern void func_002A7750(char *, int, int);
extern void func_L00_00383B90(void *);
extern int D_L00_001AEE0C __attribute__((sda));
extern float D_L00_001AEE08 __attribute__((sda));

/* Creates a Hoverbomb Projectile at a position, flying with the given velocity. */
char *func_L00_00384D40(char *owner, void *pos, void *vel)
{
    char *moby = CreateMoby(0x5D8 /* Hoverbomb Projectile */);

    if (moby != 0) {
        char *vars = *(char **)(moby + 0x68);

        SetMobyLightColor(moby, D_L00_001AEE0C);
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(char **)(moby + 0xB8) = owner;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * D_L00_001AEE08;
        *(void (**)(void *))(moby + 0x64) = UpdateTwoPlayerGoalController;
        *(Q128 *)(moby + 0x10) = *(Q128 *)pos;
        *(Q128 *)vars = *(Q128 *)vel;
        SetMobyState(moby, 3, -1);
    }
    return moby;
}
