#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_3B3158;
typedef struct {
    char pad00[0x14];
    float life;
    float fade;
    char pad1C[0x26 - 0x1C];
    s16 timer;
    char pad28[0x34 - 0x28];
    s32 stuck;
} Shard_3B3158;
extern char g_hero_state[];
extern char g_hero_l00_position[];
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void shot_damage_around(void *, void *, void *);
extern int FastDecTimer(void *);
extern void moby_mark_spawned(void *);
extern void part_queue_ground_shadow(void *, float);

/* Moves a shard projectile; it explodes on hitting something, leaving the arena or when its timer runs out. */
void shard_projectile_update_pal(char *obj)
{
    Shard_3B3158 *st;
    V4_3B3158 from, dir, at;
    char *game;

    st = *(Shard_3B3158 **)(obj + 0x68);
    dir.q = 0;
    dir.f[2] = 0.16000001f;
    qcopy(&from, obj + 0x10);
    vec_build_spherical_offset(st, st->fade, *(float *)(obj + 0xF8), -*(float *)(obj + 0xF4));
    FastVecAdd(obj + 0x10, obj + 0x10, st);
    game = g_hero_state;
    if (CollLine(&from, obj + 0x10, 0, *(void **)(game + 0x2290), 0)
        || coll_test_point(obj + 0x10, 1, *(void **)(game + 0x2290), 0.3f)) {
        qcopy(&at, g_hero_l00_position);
        vec_fast_normalize(&dir, st, g_hero_l00_position + 0x20);
        vec_scale_to_length(&dir, &dir, 0.040000003f);
        SpawnExplosionEffects_pal(obj, &dir, &at, 0.0f, 0.0f, 0, 0, 4, 0.0f, 0.0f, 9.0f, 0.4f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        shot_damage_around(obj, st, &at);
        moby_mark_spawned(obj);
        return;
    }
    if (*(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f
        || *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f
        || *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
        moby_mark_spawned(obj);
        return;
    }
    if (st->stuck == 0 && (FastDecTimer(&st->timer) || st->life < 0.0f)) {
        SpawnExplosionEffects_pal(obj, &dir, 0, 0.0f, 0.0f, 0, 0, 4, 0.0f, 0.0f, 9.0f, 0.4f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        moby_mark_spawned(obj);
        return;
    }
    {
        float fade = st->fade;
        st->life -= fade;
    }
    part_queue_ground_shadow(obj, 0.2f);
}
