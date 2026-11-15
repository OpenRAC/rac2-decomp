#include "common.h"

extern char *moby_get_motion_data(u8 *);
extern int coll_test_point(void *, int, void *, float);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
typedef struct {
    u8 prefix[0x18];
    int flags;
    int count;
    u8 gap[0x10];
    float position[4];
    float normal[4];
} CollisionResultView;
extern CollisionResultView D_L05_001BFB00;
extern int (*D_L05_00221D64)(u8 *, void *);

/* Checks if the object hit the world, remembers where and which way it hit, then runs the optional extra hit callback. */
int moby_process_collision_hit(u8 *object, void *context, int keepPosition, int skipCollision)
{
    char *vars = (char *)moby_get_motion_data(object);
    char *position;
    if (!skipCollision && coll_test_point(position = (char *)object + 0x10, 0, object, *(float *)(object + 0xC) * 0.0009765599970705807f)) {
        if (D_L05_001BFB00.flags == 0 || !keepPosition)
            qcopy(position, D_L05_001BFB00.position);
        if (D_L05_001BFB00.count > 0) {
            char *normal = vars + 0xD0;
            ++*(int *)(vars + 0x15C);
            FastVecScale(normal, D_L05_001BFB00.normal, 0.0009765599970705807f);
            vec_scale_to_length(normal, normal, 1.0f);
        }
    } else {
        *(int *)(vars + 0x15C) = 0;
    }
    if (D_L05_00221D64 != 0)
        return D_L05_00221D64(object, context);
    return 0;
}
