#include "common.h"

struct family_27f9_object;
extern float moby_turn_toward_position(struct family_27f9_object *, float *, float *, float, float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern void coll_move_resolve_collisions(char *, char *, void *, void *, char *);
extern char *g_path_l09_table[];
extern char g_hero_position[];
extern char g_default_particle_vec[] MACRO_ADDR;

/* Moves the enemy toward its target and along its path, and keeps it from sliding through walls. */
void enemy_move_along_path(char *object)
{
    float endpoint[4] __attribute__((aligned(16)));
    float before[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *data;
    char *path;
    qcopy(before, object + 0x10);
    moby_turn_toward_position((struct family_27f9_object *)object, *(float **)(state + 0x200),
        (float *)(state + 0x4B4), *(float *)(state + 0x114), *(float *)(state + 0x118),
        *(float *)(state + 0x11C));
    if (*(int *)(state + 0x2BC) != 255) {
        path = g_path_l09_table[*(int *)(state + 0x2BC)];
        qcopy(endpoint, path + *(int *)path * 16);
        FastVecSub(endpoint, endpoint, path + 0x10);
        FastVecAdd(endpoint, endpoint, g_hero_position);
        data = *(char **)(*(char **)(object + 0x68) + 0x18);
        vec_spring_to_target(object + 0x10, endpoint, state + 0x4B8, *(float *)(state + 0x120),
            *(float *)(state + 0x124), *(float *)(state + 0x128));
        coll_move_resolve_collisions(object, data, before, g_default_particle_vec, 0);
    }
}
