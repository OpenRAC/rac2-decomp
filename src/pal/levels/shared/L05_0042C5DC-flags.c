#include "include_asm.h"
#include "names.h"

typedef int Quad __attribute__((mode(TI)));
extern Quad g_projectile_pos_scratch;
extern unsigned char g_particle_params_table[];
extern void FastVecAdd(char *, char *, char *);
extern int math_fast_float_d(int *);
extern int GetCollHitMaterial(void);
extern int coll_test_point(char *, int, float, char *);
extern int CollLine(void *, void *, int, void *, void *);
extern void moby_explode_damage_nearby_pal(char *);
extern void moby_mark_spawned(void *);
extern void FastVecSub(char *, char *, char *);
extern void FastVecScale(char *, char *, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(float *, float, float, float);
extern char *part_spawn_trailing_spark(char *, char *, unsigned int, unsigned int, int, int, float);

/* Move a directed effect, resolve contact and leave paired trail particles. */
void projectile_l05_update_red_pal(char *object) {
    struct { Quad previous, point, step, velocity; } local;
    char *state = *(char **)(object + 0x68);
    char *particle;
    unsigned char *textures;
    float size, limit, first, second;
    int i, contact;
    local.previous = *(Quad *)(object + 16);
    FastVecAdd(object + 16, object + 16, state);
    size = *(float *)(object + 0x2C) + 0.07f;
    *(float *)(object + 0x2C) = size;
    limit = *(float *)(*(char **)(object + 0x24) + 0x24);
    if (limit < size) *(float *)(object + 0x2C) = limit;
    if (!math_fast_float_d((int *)(state + 0x18)) &&
        !(*(float *)(object + 16) < 2.0f) && !(1021.0f < *(float *)(object + 16)) &&
        !(*(float *)(object + 20) < 2.0f) && !(1021.0f < *(float *)(object + 20)) &&
        !(*(float *)(object + 24) < 2.0f) && !(1021.0f < *(float *)(object + 24))) {
        if (!math_fast_float_d((int *)(state + 0x28))) {
            if (GetCollHitMaterial() == 6) goto trail;
            contact = 0;
            if (coll_test_point(object + 16, 16, 1.0f, *(char **)(state + 0x20))) {
                contact = 1;
                *(Quad *)(object + 16) = g_projectile_pos_scratch;
            }
            if (!contact && !CollLine(&local.previous, object + 16, 16, *(char **)(state + 0x20), 0)) goto trail;

        }
        moby_explode_damage_nearby_pal(object);
    }
    moby_mark_spawned(object);
    return;
trail:
    local.point = local.previous;
    FastVecSub((char *)&local.step, object + 16, (char *)&local.previous);
    FastVecScale((char *)&local.step, (char *)&local.step, 0.333f);
    textures = g_particle_params_table;
    i = 3;
    do {
        FastVecAdd((char *)&local.point, (char *)&local.point, (char *)&local.step);
        first = math_random_angle();
        second = math_random_angle();
        vec_build_spherical_offset((float *)&local.velocity, 0.015000001f, first, second);
        particle = part_spawn_trailing_spark((char *)&local.point, (char *)&local.velocity, 0x4FFF0000, 0x1FFF0000, 8, 1, 80000.0f);
        if (particle) particle[2] = (*(unsigned char **)(textures + 0x184))[7];
        particle = part_spawn_trailing_spark((char *)&local.point, (char *)&local.velocity, 0x4FFF1010, 0x1FFF1010, 8, 1, 60000.0f);
        if (particle) particle[2] = (*(unsigned char **)(textures + 0x184))[7];
        i--;
    } while (i >= 0);
}
