#include "include_asm.h"

#include "common.h"
extern char *moby_get_motion_data(void *);
extern int math_random_int_below(int);
extern int PlayMobySound(int, int, char *);
extern void SpawnSpaceProjectile(float, float, float, void *, int, int, int, float, int, int, int);

/* Kills the object: the type at 0x20 picks the effect, and the hit state at 0x268
   ends up at 0x19. */
void lightning_object_update_state_pal(void *moby)
{
    void *self = moby;
    void *vars = *(void **)((char *)self + 0x68);
    void *motion = moby_get_motion_data(self);

    if (motion == 0)
        return;
    if (*(int *)((char *)motion + 0x120) == 0)
        return;
    if (*(int *)((char *)vars + 0x268) != 0)
        return;
    if (*(unsigned char *)((char *)self + 0x20) == 2) {
        SpawnSpaceProjectile(0.9f, 13.0f, 4.5f, self, 0x60000080, 0, 1, 1.0f, 0, -1, 0);
    } else if (*(unsigned char *)((char *)self + 0x20) == 1) {
        if (math_random_int_below(2) != 0)
            SpawnSpaceProjectile(0.6f, 5.0f, 1.0f, self, 0x60800000, 1, 0, 1.0f, 0, -1, 0);
        else
            SpawnSpaceProjectile(0.6f, 5.0f, 1.0f, self, 0x60800080, 1, 0, 1.0f, 0, -1, 0);
    }
    if (math_random_int_below(3) == 0)
        PlayMobySound(0, 0, self);
    *(int *)((char *)vars + 0x268) = 0x15;
}
