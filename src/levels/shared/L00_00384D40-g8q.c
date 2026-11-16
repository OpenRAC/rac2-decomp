#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"
typedef int Q128 __attribute__((mode(TI)));

extern char *CreateMoby(int);
extern void moby_set_light_color(void *a0, int a1);
extern void moby_set_state(char *, int, int);
extern void goal_controller_update(void *);
extern int g_hoverbomb_light_color __attribute__((sda));
extern float g_hoverbomb_scale __attribute__((sda));

/* Creates a Hoverbomb Projectile at a position, flying with the given velocity. */
char *hoverbomb_create_projectile(char *owner, void *pos, void *vel)
{
    char *moby = CreateMoby(MOBY_CLASS_HOVERBOMB_PROJECTILE);

    if (moby != 0) {
        char *vars = *(char **)(moby + 0x68);

        moby_set_light_color(moby, g_hoverbomb_light_color);
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(char **)(moby + 0xB8) = owner;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * g_hoverbomb_scale;
        *(void (**)(void *))(moby + 0x64) = goal_controller_update;
        *(Q128 *)(moby + 0x10) = *(Q128 *)pos;
        *(Q128 *)vars = *(Q128 *)vel;
        moby_set_state(moby, 3, -1);
    }
    return moby;
}
