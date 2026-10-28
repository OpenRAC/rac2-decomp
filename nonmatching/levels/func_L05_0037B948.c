/* Complete C near miss; NOT linked and no exact-C credit.
 * Measured source unit: src/levels/shared/L05_0037B948.c
 * Game profile: -O2 -G0 -ffunction-sections
 * Compiled/retail bytes: 476/480. US: 0/4; US2: 0/4; PAL: 0/4.
 * Residual and reopening condition: Two target-pointer temporaries and the last branch delay slot/restore sharing differ. A cone constant genuinely live across the calls recovers both FPR saves. Separate pointer lifetimes and an early return tied; G8 regressed. Reopen with independent lifetime or twin evidence.
 * Field views describe only measured prefixes, not complete game-object extents.
 */

#include "common.h"
extern int func_002ED688(void *object);
extern float func_00282E48(void *a, void *b);
extern int func_002761F8(void *a, void *b, int flags, void *owner, void *ignore);
extern void func_00283658(void *out, void *in);
extern void func_002AB6D8(float *matrix, float *angles);
extern float func_00283248(float a, float b);
extern float func_00283C80(float a, float b);
extern float func_00282E80(void *a, void *b);
extern int func_00283DB8(void *point, float radius);
extern int D_L05_00221D3C;
extern char *D_L05_001BFB18;

void func_L05_0037B948(char *object, int checkView, float limit)
{
    float angles[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    char *state = (char *)func_002ED688(object);
    float horizontal;
    float vertical;
    float cone;
    char *target;
    char *horizontalTarget;
    char *verticalTarget;
    if (state == 0)
        return;
    target = *(char **)(state + 0x120);
    if (target == 0)
        return;
    *(int *)(state + 0x104) = 0;
    *(int *)(state + 0x108) = 0;
    cone = 0.7068582773208618f;
    if (D_L05_00221D3C == 1)
        return;
    if (limit < func_00282E48(target + 0x10, object + 0x10))
        return;
    if (func_002761F8(object + 0x10, *(char **)(state + 0x120) + 0x10, 0, object, 0)) {
        if (D_L05_001BFB18 == 0)
            return;
        if (*(short *)(D_L05_001BFB18 + 0xAA) != *(short *)(*(char **)(state + 0x120) + 0xAA))
            return;
    }
    func_00283658(matrix, object + 0xC0);
    func_002AB6D8(matrix, angles);
    horizontalTarget = *(char **)(state + 0x120);
    horizontal = func_00283C80(func_00283248(*(float *)(horizontalTarget + 0x10) - *(float *)(object + 0x10), *(float *)(horizontalTarget + 0x14) - *(float *)(object + 0x14)), angles[2]);
    vertical = func_00282E80(*(char **)(state + 0x120) + 0x10, object + 0x10);
    verticalTarget = *(char **)(state + 0x120);
    vertical = func_00283C80(func_00283248(vertical, *(float *)(verticalTarget + 0x18) - *(float *)(object + 0x18)), 0.0f);
    if (horizontal <= cone && vertical <= cone)
        *(int *)(state + 0x104) = 1;
    if (checkView) {
        qcopy(point, object + 0x10);
        point[3] = 0.1f;
        if (func_00283DB8(point, 256.0f) == -1)
            return;
        *(int *)(state + 0x108) = 1;
    }
}
