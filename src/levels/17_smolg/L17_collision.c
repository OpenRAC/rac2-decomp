#include "common.h"

extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern int func_00277F48(void *, int, void *, int, float);
extern void *func_001153D4(void *, const void *, unsigned int);
extern int func_002A90C8(void *, void *, int, void *, float);
extern char *D_L17_001C4080[];

void func_L17_0041F180(char *object, char *params) {
    float matrix[12] __attribute__((aligned(16)));
    float center[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    float inverse[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float radius;
    char *position;
    int count, i, n;

    char *candidate;
    if (*(int *)(params + 8) & 0x100)
        return;
    euler_rotation_basis(matrix, object + 0xF0);
    radius = *(float *)params > *(float *)(params + 4) ? *(float *)params : *(float *)(params + 4);
    radius *= 0.5f;
    /* Center is initialized here before it escapes to the vector callees. */
    qzero_nc(center);
    center[2] = radius;
    position = object + 0x10;
    matrix_mul_vec3(center, center, matrix);
    FastVecAdd(center, center, position);
    count = func_00277F48(center, 0x10, object, 0, radius);
    if (!count)
        return;
    {
        char *candidates[count];

        func_001153D4(candidates, D_L17_001C4080, count * 4);
        for (i = 0; i < count; i++) {
            candidate = candidates[i];
            if (!candidate || (u8)candidate[0x20] == 0xFE || (u8)candidate[0x20] == 0xFD)
                continue;
            FastVecSub(delta, candidate + 0x10, object + 0x10);
            matrix_from_basis_rows(inverse, matrix);
            transform_vector(local, delta, inverse);
            qcopy(point, local);
            if (point[0] < -(*(float *)params * 0.5f + *(float *)(params + 0x48)))
                point[0] = -*(float *)params * 0.5f;
            else if (point[0] > *(float *)params * 0.5f + *(float *)(params + 0x48))
                point[0] = *(float *)params * 0.5f;
            if (point[2] < -(*(float *)(params + 4) * 0.5f + *(float *)(params + 0x4C)))
                point[2] = -*(float *)(params + 4) * 0.5f;
            else if (point[2] > *(float *)(params + 4) * 0.5f + *(float *)(params + 0x4C))
                point[2] = *(float *)(params + 4) * 0.5f;
            point[1] = 0;
            matrix_mul_vec3(point, point, matrix);
            FastVecAdd(point, point, object + 0x10);
            n = func_00277F48(point, 0x10, object, 0, *(float *)(params + 0x48));
            {
                int j;
                for (j = 0; j < n; j++) {
                    if (D_L17_001C4080[j] == candidate)
                        func_002A90C8(candidate, object, 0x10001, point, *(float *)(params + 0x50));
                }
            }
        }
    }
}

void func_L17_00420758(char *object, char *params) {
    float matrix[12] __attribute__((aligned(16)));
    float center[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    float inverse[16] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float radius;
    char *position;
    int count, i, n;

    char *candidate;
    if (*(int *)(params + 8) & 0x100)
        return;
    euler_rotation_basis(matrix, object + 0xF0);
    radius = *(float *)params > *(float *)(params + 4) ? *(float *)params : *(float *)(params + 4);
    radius *= 0.5f;
    /* Center is initialized here before it escapes to the vector callees. */
    qzero_nc(center);
    center[2] = radius;
    position = object + 0x10;
    matrix_mul_vec3(center, center, matrix);
    FastVecAdd(center, center, position);
    count = func_00277F48(center, 0x10, object, 0, radius);
    if (!count)
        return;
    {
        char *candidates[count];

        func_001153D4(candidates, D_L17_001C4080, count * 4);
        for (i = 0; i < count; i++) {
            candidate = candidates[i];
            if (!candidate || (u8)candidate[0x20] == 0xFE || (u8)candidate[0x20] == 0xFD)
                continue;
            FastVecSub(delta, candidate + 0x10, object + 0x10);
            matrix_from_basis_rows(inverse, matrix);
            transform_vector(local, delta, inverse);
            qcopy(point, local);
            if (point[0] < -(*(float *)params * 0.5f + *(float *)(params + 0x48)))
                point[0] = -*(float *)params * 0.5f;
            else if (point[0] > *(float *)params * 0.5f + *(float *)(params + 0x48))
                point[0] = *(float *)params * 0.5f;
            if (point[2] < -(*(float *)(params + 4) * 0.5f + *(float *)(params + 0x4C)))
                point[2] = -*(float *)(params + 4) * 0.5f;
            else if (point[2] > *(float *)(params + 4) * 0.5f + *(float *)(params + 0x4C))
                point[2] = *(float *)(params + 4) * 0.5f;
            point[1] = 0;
            matrix_mul_vec3(point, point, matrix);
            FastVecAdd(point, point, object + 0x10);
            n = func_00277F48(point, 0x10, object, 0, *(float *)(params + 0x48));
            {
                int j;
                for (j = 0; j < n; j++) {
                    if (D_L17_001C4080[j] == candidate)
                        func_002A90C8(candidate, object, 0x10001, point, *(float *)(params + 0x50));
                }
            }
        }
    }
}
