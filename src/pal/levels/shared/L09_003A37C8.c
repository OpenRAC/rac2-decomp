#include "include_asm.h"


#include "common.h"
extern void *CreateMoby(int id);
extern float mat_fast_helper_a(float x, float y);
extern float vec_length_xy(char *a);
extern void func_002A0F48(char *a);
extern char *part_spawn_sized(char *object, int direction, u32 position, int a3, float speed, float f13);

/* Creates a small moving effect object at a position, aims it along a direction and returns it. */
char *moby_spawn_aimed_effect_pal(char *object, char *direction, char *position, float speed)
{
    char *spawned = CreateMoby(0x3A6 /* moby class 934 */);
    char *vars;
    float length;

    if (spawned != 0) {
        *(u8 *)(spawned + 0x30) = 0xFF;
        *(u16 *)(spawned + 0x32) = 0xFF;
        *(u8 *)(spawned + 0x31) = 1;
        *(u8 *)(spawned + 0x20) = 0;
        *(u64 *)(spawned + 0x38) = *(u64 *)(object + 0x38);
        qcopy(spawned + 0x10, position);
        vars = *(char **)(spawned + 0x68);
        qcopy(vars, direction);
        *(char **)(vars + 0x3C) = object;
        *(u32 *)(vars + 0x38) = 0xC8;
        *(float *)(vars + 0x40) = speed;
        *(float *)(spawned + 0xF8) = mat_fast_helper_a(*(float *)direction, *(float *)(direction + 4));
        length = vec_length_xy(direction);
        *(float *)(spawned + 0xF4) =
            -mat_fast_helper_a(length, *(float *)(direction + 8));
        *(char **)(vars + 0x48) =
            part_spawn_sized(spawned, -1, 0xF0208080, 0x60, 0.1f, 0.01f);
        func_002A0F48(spawned);
        *(u8 *)(spawned + 0x31) = 0;
        *(u16 *)(spawned + 0x34) |= 1;
    }
    return spawned;
}



extern void cam_compute_view_direction(void *pos, void *out, int mode);
extern void FastVecAdd(void *dst, void *a, void *b);
extern void vec_scale_to_length(void *dst, void *src, float scale);
extern int CollLine(void *from, void *to, int mode, int filter, void *hit);
extern int coll_test_point(float radius, void *pos, int mode, int filter);
extern int PlayMobySound(int a, int b, void *object);
extern int FloatToInt(float x);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                          int, float, int, int, int, int, int);
extern int coll_process_hit(void *pos, int kind, int filter, void *hit, float amount);
extern int math_fast_float_d(void *timer);
extern void moby_mark_spawned(void *object);
extern void projectile_update_orientation_pal(void *object);
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
void projectile_l09_update_pal(char *object)
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
            SpawnExplosionEffects_pal(object, data + 0x30, 0, 0.0f, 0.0f, r, g, b, 0.0f, 0.0f, 9.0f, F(data, 0x50),
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
        SpawnExplosionEffects_pal(object, data + 0x30, 0, 2.0f, F(data, 0x54), r, g, b, 0.0f, 0.0f, 9.0f, F(data, 0x50),
                      -1, 0.0f, 0, 1, -1, 0, 0x810001);
        moby_mark_spawned(object);
        return;
    }
    if (F(object, 0x10) < 2.0f || F(object, 0x10) > 1021.0f || F(object, 0x14) < 2.0f
        || F(object, 0x14) > 1021.0f || F(object, 0x18) < 2.0f || F(object, 0x18) > 1021.0f) {
        moby_mark_spawned(object);
        return;
    }
    projectile_update_orientation_pal(object);
}

