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

void cam_swingshot_update_node_switch_pal(char *o)
{
    int *t = (int *)(*(char **)(o + 0x70) + 0xB8);
    int st = g_hero_state.state;
    char *pos;
    int x, y;

    if (st == 0x2B) {
        x = t[2];
        pos = o + 0x30;
        y = g_hero_state.fAD4;
    } else {
        pos = o + 0x30;
        if ((unsigned int)(st - 0x23) >= 3)
            goto done;
        x = t[2];
        y = g_hero_state.fAA4;
    }
    if (x != y) {
        char *p = g_scalar_transition_state.dst;
        *(Q128 *)(p + 0x30) = *(Q128 *)pos;
        *(Q128 *)p = *(Q128 *)o;
        *(Q128 *)(p + 0x10) = *(Q128 *)(o + 0x10);
        *(Q128 *)(p + 0x20) = *(Q128 *)(o + 0x20);
        cam_swingshot_init_pal(o);
        g_scalar_transition_state.f314 = 0x25;
    }
done:
    ref_L00_00428F00_00(o);
    ResolveCameraMovementCollisions(pos, 0.5f);
    *(int *)(*(char **)(o + 0x70) + 0x80) = 0;
}
