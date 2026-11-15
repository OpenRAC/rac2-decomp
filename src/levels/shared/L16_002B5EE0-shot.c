#include "common.h"
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } ShotProbe;
typedef struct {
    char pad00[0x30];
    float velocity[4];
    void *owner;
    int pad44;
    int timer;
    int pad4C;
    float size;
    float radius;
    char pad58[8];
    float speed;
    int mode;
    int enabled;
} ShotState;
typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[0x47];
    ShotState *vars;
    char pad6C[0x3E];
    unsigned short kind;
} ShotMoby;
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, float, void *);
extern int PlayMobySound(void *, int, void *);
extern int FloatToInt(float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern int coll_process_hit(void *, int, void *, void *, float);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern void projectile_update_orientation(void *);

/* Moves a shot, tests it against the level and its targets, and explodes it on contact or timeout. */
/* This is the update of the shot moby of class 1502. */
void shot_l16_update(ShotMoby *m)
{
    float start[4], scratch[4], old[4];
    ShotProbe probe;
    ShotState *v = m->vars;
    qcopy(start, m->position);
    cam_compute_view_direction(m->position, scratch, 1);
    qcopy(old, m->position);
    if (m->state == 0) {
        FastVecAdd(m->position, m->position, v->velocity);
        probe.owner = m;
        probe.flags = 0x10001;
        probe.radius = v->radius;
        probe.active = 1;
        qcopy(probe.v, v->velocity);
        vec_scale_to_length(&probe, &probe, v->speed);
        probe.v[3] = 5627.9248046875f;
        probe.mode = v->mode;
        probe.enabled = v->enabled;
        probe.kind = m->kind;
        if (CollLine(old, m->position, 0, v->owner, &probe) ||
            coll_test_point(m->position, 0, 0.2f, v->owner)) {
            PlayMobySound(0, 0, m);
            SpawnExplosionEffects(m, v->velocity, 0, 0.0f, 0.0f, FloatToInt(v->size * 5.0f),
                         FloatToInt(v->size * 4.0f), FloatToInt(v->size * 10.0f),
                         0.0f, 0.0f, 9.0f, v->size, -1, 0.0f, 0, 1, -1, 0, 0x810001);
            coll_process_hit(m->position, 0x10, v->owner, &probe, 1.0f);
            moby_mark_spawned(m);
            return;
        }
    }
    if (math_fast_float_d(&v->timer)) {
        SpawnExplosionEffects(m, v->velocity, 0, 2.0f, v->radius, FloatToInt(v->size * 5.0f),
                     FloatToInt(v->size * 4.0f), FloatToInt(v->size * 10.0f),
                     0.0f, 0.0f, 9.0f, v->size, -1, 0.0f, 0, 1, -1, 0, 0x810001);
        moby_mark_spawned(m);
        return;
    }
    if (m->position[0] < 2.0f || m->position[0] > 1021.0f ||
        m->position[1] < 2.0f || m->position[1] > 1021.0f ||
        m->position[2] < 2.0f || m->position[2] > 1021.0f) {
        moby_mark_spawned(m);
        return;
    }
    projectile_update_orientation(m);
}
