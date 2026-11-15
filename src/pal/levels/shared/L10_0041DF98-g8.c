#include "include_asm.h"

#include "common.h"
extern char *moby_get_motion_data(void *);
extern int math_random_int_below(int);
extern int PlayMobySound(int, int, char *);
extern void SpawnSpaceProjectile(float, float, float, void *, int, int, int, float, int, int, int);

/* Kills the object: the type at 0x20 picks the effect, and the hit state at 0x268
   ends up at 0x19. */
void func_PAL_L10_0041DF98(void *a0)
{
    void *s0 = a0;
    void *s1 = *(void **)((char *)s0 + 0x68);
    void *v0 = moby_get_motion_data(s0);

    if (v0 == 0)
        return;
    if (*(int *)((char *)v0 + 0x120) == 0)
        return;
    if (*(int *)((char *)s1 + 0x268) != 0)
        return;
    if (*(unsigned char *)((char *)s0 + 0x20) == 2) {
        SpawnSpaceProjectile(0.9f, 13.0f, 4.5f, s0, 0x60000080, 0, 1, 1.0f, 0, -1, 0);
    } else if (*(unsigned char *)((char *)s0 + 0x20) == 1) {
        if (math_random_int_below(2) != 0)
            SpawnSpaceProjectile(0.6f, 5.0f, 1.0f, s0, 0x60800000, 1, 0, 1.0f, 0, -1, 0);
        else
            SpawnSpaceProjectile(0.6f, 5.0f, 1.0f, s0, 0x60800080, 1, 0, 1.0f, 0, -1, 0);
    }
    if (math_random_int_below(3) == 0)
        PlayMobySound(0, 0, s0);
    *(int *)((char *)s1 + 0x268) = 0x15;
}
