#include "include_asm.h"
#include "common.h"

/* Matched in its own unit: the timer test needs an int-returning func_00282948, which
   L09_002B7238.c declares void. */
extern void cam_compute_view_direction(void *pos, void *out, int mode);
extern void FastVecAdd(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float scale);
extern int CollLine(void *from, void *to, int mode, int filter, void *hit);
extern int coll_test_point(float radius, void *pos, int mode, int filter);
extern int PlayMobySound(int a, int b, void *object);
extern int FloatToInt(float x);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                          int, float, int, int, int, int, int);
extern int coll_process_hit(void *pos, int kind, int filter, void *hit, float amount);
extern int math_fast_float_d(void *timer);
extern void moby_mark_spawned(void *object);
extern void projectile_update_orientation(void *object);

#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))

typedef struct {
    float v[4];
    void *object;
    int flags;
    u8 a, b;
    u16 id;
    float radius;
    int mode;
} Hit_L09_003AEA88;

/* Moves the projectile, then explodes it on a hit or when its timer runs out, and destroys
   it then or once it leaves the 2..1021 world box; otherwise refreshes its orientation. */
void projectile_l09_update(char *object)
{
    char *data = *(char **)(object + 0x68);
    float old[4] __attribute__((aligned(16)));
    float scratch[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    Hit_L09_003AEA88 hit __attribute__((aligned(16)));

    qcopy(old, object + 0x10);
    cam_compute_view_direction(object + 0x10, scratch, 1);
    qcopy(start, object + 0x10);
    if (B(object, 0x20) == 0) {
        FastVecAdd(object + 0x10, object + 0x10, data + 0x30);
        hit.object = object;
        hit.flags = 0x10001;
        hit.radius = F(data, 0x54);
        hit.mode = 1;
        qcopy(hit.v, data + 0x30);
        vec_scale_to_length(hit.v, hit.v, F(data, 0x60));
        hit.v[3] = 5627.925f;
        hit.a = B(data, 0x64);
        hit.b = B(data, 0x68);
        hit.id = *(u16 *)(object + 0xAA);
        if (CollLine(start, object + 0x10, 0, I(data, 0x40), &hit)
            || coll_test_point(0.2f, object + 0x10, 0, I(data, 0x40))) {
            int r, g, b;

            PlayMobySound(0, 0, object);
            r = FloatToInt(F(data, 0x50) * 5.0f);
            g = FloatToInt(F(data, 0x50) * 4.0f);
            b = FloatToInt(F(data, 0x50) * 10.0f);
            SpawnExplosionEffects(object, data + 0x30, 0, 0.0f, 0.0f, r, g, b, 0.0f, 0.0f, 9.0f, F(data, 0x50),
                          -1, 0.0f, 0, 1, -1, 0, 0x810001);
            coll_process_hit(object + 0x10, 16, I(data, 0x40), &hit, 1.0f);
            moby_mark_spawned(object);
            return;
        }
    }
    if (math_fast_float_d(data + 0x48)) {
        int r, g, b;

        r = FloatToInt(F(data, 0x50) * 5.0f);
        g = FloatToInt(F(data, 0x50) * 4.0f);
        b = FloatToInt(F(data, 0x50) * 10.0f);
        SpawnExplosionEffects(object, data + 0x30, 0, 2.0f, F(data, 0x54), r, g, b, 0.0f, 0.0f, 9.0f, F(data, 0x50),
                      -1, 0.0f, 0, 1, -1, 0, 0x810001);
        moby_mark_spawned(object);
        return;
    }
    if (F(object, 0x10) < 2.0f || F(object, 0x10) > 1021.0f || F(object, 0x14) < 2.0f
        || F(object, 0x14) > 1021.0f || F(object, 0x18) < 2.0f || F(object, 0x18) > 1021.0f) {
        moby_mark_spawned(object);
        return;
    }
    projectile_update_orientation(object);
}
