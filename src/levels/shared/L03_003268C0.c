/* func_L03_003268C0: spawn the level's effect bursts over the configured range. */
#include "common.h"

typedef struct { float x, y, z, w; } L03EffectVector;
typedef struct { float x, y; } L03EffectRange;
extern L03EffectRange D_L03_001AA2E8;
extern unsigned char D_L03_001A8F20[] MACRO_ADDR;
extern void vec_random_direction(L03EffectVector *, float, float);
extern float math_random_angle(void);
extern void vec_clear_128(L03EffectVector *);
extern void FastVecAdd(void *, void *, void *);
extern float math_fabs(float);
extern int math_random_int_below(int);
extern int coll_scatter_points_in_shapes(void *, int, void *, int, float);
extern char *part_spawn_flying_fragment(void *, int, void *, void *, int, int, void *, void *, void *, float);

/* Launches a burst of small effect objects from an object, some at set places and some at random nearby points. */
void part_spawn_effect_burst(unsigned char *object, int first, int count, int randomFirst,
                        int randomCount, int limit, int alternate, void *offset) {
    L03EffectVector velocity;
    L03EffectRange range = D_L03_001AA2E8;
    L03EffectVector points[16];
    L03EffectVector rotation;
    int flags = alternate ? 2 : 0;
    int i, found;
    if (first > 0 && count > 0) {
        for (i = 0; i < count; i++) {
            vec_random_direction(&velocity, range.x, range.y);
            velocity.z = math_fabs(velocity.z) * 1.5f;
            FastVecAdd(&velocity, &velocity, offset);
            part_spawn_flying_fragment(object, first + i, object + 0x10, object + 0xF0,
                            0, flags, &velocity, D_L03_001A8F20, D_L03_001A8F20, 0.0f);
        }
    }
    if (randomFirst > 0 && randomCount > 0) {
        found = coll_scatter_points_in_shapes(object, limit, points, 0xFFFF, 1000.0f);
        if (found) {
            for (i = 0; i < limit && i < found; i++) {
                vec_random_direction(&velocity, range.x, range.y);
                velocity.z = math_fabs(velocity.z) * 1.5f;
                FastVecAdd(&velocity, &velocity, offset);
                vec_clear_128(&rotation);
                rotation.x = math_random_angle();
                rotation.y = math_random_angle();
                rotation.z = math_random_angle();
                part_spawn_flying_fragment(object, randomFirst + math_random_int_below(randomCount),
                                &points[i], &rotation, 0, flags, &velocity,
                                D_L03_001A8F20, D_L03_001A8F20, 0.0f);
            }
        }
    }
}
