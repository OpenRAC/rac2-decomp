#include "common.h"

extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern int coll_process_hit(void *, int, void *, int, float);
extern void *func_001153D4(void *, const void *, unsigned int);
extern void part_start_effect_default_table(void *, void *, int, void *, float);
extern char *D_L17_001C4080[];

/* Finds objects touching its box and hits each one (collision test for the box). */
void coll_hit_mobys_inside_box(char *object, char *params) {
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
    count = coll_process_hit(center, 0x10, object, 0, radius);
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
            n = coll_process_hit(point, 0x10, object, 0, *(float *)(params + 0x48));
            {
                int j;
                for (j = 0; j < n; j++) {
                    if (D_L17_001C4080[j] == candidate)
                        part_start_effect_default_table(candidate, object, 0x10001, point, *(float *)(params + 0x50));
                }
            }
        }
    }
}

/* Finds objects touching its box and hits each one (collision test for the box). */
void coll_hit_mobys_inside_box_copy(char *object, char *params) {
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
    count = coll_process_hit(center, 0x10, object, 0, radius);
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
            n = coll_process_hit(point, 0x10, object, 0, *(float *)(params + 0x48));
            {
                int j;
                for (j = 0; j < n; j++) {
                    if (D_L17_001C4080[j] == candidate)
                        part_start_effect_default_table(candidate, object, 0x10001, point, *(float *)(params + 0x50));
                }
            }
        }
    }
}
