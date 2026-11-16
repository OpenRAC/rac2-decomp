#include "include_asm.h"
#include "names.h"

typedef int Q128 __attribute__((mode(TI)));
typedef struct {
    char pad0[0xAA4];
    int fAA4;
    char padAA8[0xAD4 - 0xAA8];
    int fAD4;
    char padAD8[0x2294 - 0xAD8];
    int state;
} Hero_428F00;
typedef struct {
    char pad0[0x194];
    char *dst;
    char pad198[0x314 - 0x198];
    int f314;
} Ctl_428F00;
extern Hero_428F00 g_hero_state;
extern Ctl_428F00 g_scalar_transition_state;
extern void cam_swingshot_init_pal(char *);
extern void ref_L00_00428F00_00(char *);
extern void ResolveCameraMovementCollisions(char *, float);

/* Restarts the swing shot camera when the hero moves on to a new swing node, then resolves collisions. */
void cam_swingshot_update_node_switch_pal(char *moby)
{
    int *tracking = (int *)(*(char **)(moby + 0x70) + 0xB8);
    int state = g_hero_state.state;
    char *pos;
    int cur_node, hero_node;

    if (state == 0x2B) {
        cur_node = tracking[2];
        pos = moby + 0x30;
        hero_node = g_hero_state.fAD4;
    } else {
        pos = moby + 0x30;
        if ((unsigned int)(state - 0x23) >= 3)
            goto done;
        cur_node = tracking[2];
        hero_node = g_hero_state.fAA4;
    }
    if (cur_node != hero_node) {
        char *dst = g_scalar_transition_state.dst;
        *(Q128 *)(dst + 0x30) = *(Q128 *)pos;
        *(Q128 *)dst = *(Q128 *)moby;
        *(Q128 *)(dst + 0x10) = *(Q128 *)(moby + 0x10);
        *(Q128 *)(dst + 0x20) = *(Q128 *)(moby + 0x20);
        cam_swingshot_init_pal(moby);
        g_scalar_transition_state.f314 = 0x25;
    }
done:
    ref_L00_00428F00_00(moby);
    ResolveCameraMovementCollisions(pos, 0.5f);
    *(int *)(*(char **)(moby + 0x70) + 0x80) = 0;
}
