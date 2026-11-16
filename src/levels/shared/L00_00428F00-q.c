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
extern void cam_swingshot_init(char *);
extern void ref_L00_00428F00_00(char *); /* func_L00_00428EB0 in most levels */
extern void ResolveCameraMovementCollisions(char *, float);

/* Updates the swingshot camera. If the hero grabs a different node, it saves the old view and restarts the camera setup. */
void cam_swingshot_update_node_switch(char *camera)
{
    int *tracking = (int *)(*(char **)(camera + 0x70) + 0xB8);
    int heroState = g_hero_state.state;
    char *pos;
    int trackedId, heroTargetId;

    if (heroState == 0x2B) {
        trackedId = tracking[2];
        pos = camera + 0x30;
        heroTargetId = g_hero_state.fAD4;
    } else {
        pos = camera + 0x30;
        if ((unsigned int)(heroState - 0x23) >= 3)
            goto done;
        trackedId = tracking[2];
        heroTargetId = g_hero_state.fAA4;
    }
    if (trackedId != heroTargetId) {
        char *cameraDst = g_scalar_transition_state.dst;
        *(Q128 *)(cameraDst + 0x30) = *(Q128 *)pos;
        *(Q128 *)cameraDst = *(Q128 *)camera;
        *(Q128 *)(cameraDst + 0x10) = *(Q128 *)(camera + 0x10);
        *(Q128 *)(cameraDst + 0x20) = *(Q128 *)(camera + 0x20);
        cam_swingshot_init(camera);
        g_scalar_transition_state.f314 = 0x2D;
    }
done:
    ref_L00_00428F00_00(camera);
    ResolveCameraMovementCollisions(pos, 0.5f);
    *(int *)(*(char **)(camera + 0x70) + 0x80) = 0;
}
