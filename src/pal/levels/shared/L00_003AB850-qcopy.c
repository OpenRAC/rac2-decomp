#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern unsigned char g_beam_weapon_index[];
typedef struct { char pad[112]; float scale; char tail[108]; } TableEntry;
extern char g_weapon_l00_table[];
extern void *g_hero_moby;
typedef struct {
    char state[24];
    void *object;
    unsigned int detail;
    float position[4];
} CollisionResultPrefix;
extern CollisionResultPrefix g_collision_result;
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern void SpawnConfiguredImpactEffects_pal(char *, void *);
extern int weapon_start_health_drain_pal(void *, int, int);

/* Tests the beam moby's last step for a hit; on a hit spawns the impact effects, damages what was hit and returns 1. */
int beam_test_segment_hit_pal(char *object, void *target)
{
    char local[64];
    char *state = *(char **)(object + 104);
    *(char **)(local + 16) = object;
    *(int *)(local + 20) = 0x10000;
    *(int *)(local + 32) = 1;
    *(float *)(local + 28) = ((TableEntry *)(g_weapon_l00_table + g_beam_weapon_index[0] * 224))->scale;
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
        SpawnConfiguredImpactEffects_pal(object, g_collision_result.position);
        if (g_collision_result.object != 0)
            weapon_start_health_drain_pal(g_collision_result.object, 23, *(int *)(object + 184));
        return 1;
    }
    return 0;
}
