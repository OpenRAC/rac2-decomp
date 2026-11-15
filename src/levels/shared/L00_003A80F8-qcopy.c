#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
extern unsigned char D_0013957F[];
typedef struct { char pad[112]; float scale; char tail[108]; } TableEntry;
extern char g_weapon_l00_table[];
extern void *g_hero_moby;
/* The collision query writes this prefix and additional vector fields after it. */
typedef struct {
    char state[24];
    void *object;
    unsigned int detail;
    float position[4];
} CollisionResultPrefix;
extern CollisionResultPrefix g_collision_result;
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void SpawnConfiguredImpactEffects(char *, void *);
extern void weapon_start_health_drain(void *, int, int);

/* Checks if the beam hits something on its way, and if so shows the impact and returns 1. */
int beam_test_segment_hit(char *object, void *target)
{
    char local[64];
    char *state = *(char **)(object + 104);
    *(char **)(local + 16) = object;
    *(int *)(local + 20) = 0x10000;
    *(int *)(local + 32) = 1;
    *(float *)(local + 28) = ((TableEntry *)(g_weapon_l00_table + D_0013957F[0] * 224))->scale;
    *(TI128 *)local = *(TI128 *)state;
    vec_scale_to_length(local, local, 1.0f);
    *(unsigned short *)(local + 26) = *(unsigned short *)(object + 0xAA);
    *(float *)(local + 12) = 5627.925f;
    *(unsigned char *)(local + 24) = 1;
    *(unsigned char *)(local + 25) = 1;
    if (*(short *)(state + 18) == 1)
        *(TI128 *)(local + 48) = *(TI128 *)(state + 48);
    else
        *(TI128 *)(local + 48) = *(TI128 *)(object + 16);
    if (CollLine(target, local + 48, 0, g_hero_moby, local) != 0) {
        SpawnConfiguredImpactEffects(object, g_collision_result.position);
        if (g_collision_result.object != 0)
            weapon_start_health_drain(g_collision_result.object, 23, *(int *)(object + 184));
        return 1;
    }
    return 0;
}
