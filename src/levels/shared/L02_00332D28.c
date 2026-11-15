/* func_L02_00332D28 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CC0(void *, void *, void *);
extern int func_L02_00333218(void *, void *);
extern void func_00282CF0(void *, void *, void *);
/* Canonical pointer inputs and float return are explicit. */
extern float func_002AFF08(char *, char *, char *);
extern void func_002AFE58(char *, char *, char *, float, char *);
extern float func_002B0360(char *);
extern void func_002AFD88(char *, char *, float, float, float);
extern void func_002AFEB8(char *, char *, char *, float, char *);
extern int func_00282948(void *);

/* Moves an object by its velocity and pushes it out of any walls it touched, trying up to 8 times. It slows the object, keeps it above the ground and counts how long it has been touching. */
void func_L02_00332D28(char *object, char *data, void *originalPosition, void *scratch, char *transform) {
    TI128 before;
    int hit, i;
    float speed, height;
    FastVecAdd(object + 0x10, object + 0x10, data + 0xA0);
    qcopy(&before, object + 0x10);
    *(int *)(data + 0x84) = 0;
    qzero(data + 0x60);
    {
        int changed = 0;
        for (i = 0; i < 8; i++) {
            hit = CheckObjectSphereHit(object, data);
            changed |= hit;
            if (!hit)
                break;
        }
        if (changed) {
            FastVecSub(data + 0xA0, object + 0x10, originalPosition);
            speed = GetHorizontalOffsetLength(object, data + 0xA0, transform);
            if (*(float *)(data + 0xB0) < speed)
                TransformAndScaleVector(object, data + 0xA0, data + 0xA0, *(float *)(data + 0xB0), transform);
            else
                *(float *)(data + 0xB0) = speed;
            height = GetDistanceFromGravityCenter(object + 0x10);
            if (height <= *(float *)(data + 0x90)) {
                float zero = 0.0f;
                AddTransformedPointToVector(object, object + 0x10, zero, zero, *(float *)(data + 0x90) - height);
                TransformAndSetHeight(object, data + 0xA0, data + 0xA0, zero, transform);
            }
            if (*(float *)(data + 0xB0) < *(float *)(data + 0x28) * 0.5f)
                *(int *)(data + 0x80) += 1;
            else
                FastFloatHelperD(data + 0x80);
        } else {
            FastFloatHelperD(data + 0x80);
        }
        FastVecSub(data + 0x70, object + 0x10, &before);
    }
}
