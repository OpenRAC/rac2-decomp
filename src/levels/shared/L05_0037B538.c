#include "common.h"

extern int func_002ED688(u8 *);
extern int func_00277258(void *, int, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
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
int func_L05_0037B538(u8 *object, void *context, int keepPosition, int skipCollision)
{
    char *vars = (char *)GetMobyMotionData(object);
    char *position;
    if (!skipCollision && TestPointAgainstCollision(position = (char *)object + 0x10, 0, object, *(float *)(object + 0xC) * 0.0009765599970705807f)) {
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
