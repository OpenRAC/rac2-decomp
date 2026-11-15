#include "common.h"

typedef struct { float x, y, z, w; } MmiPoint;
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void func_002A3110(void *, int, int);
extern void scale_vector(void *, void *, float);
extern void divide_vector_xyz(void *, void *, float);
extern void func_00129148(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float square_root(float);
extern void matrix_mul_vec3(void *, void *, void *);

/* Choose collision shapes by volume and scatter points inside them.
 * Source structure follows RAC1's func_L00_0025BCF8_r in
 * overlays/shared/moby_ground_collision.c (GPL-3.0).
 * The float argument precedes the integer arguments in source, as in RAC1;
 * each register bank retains its own argument order in the EE ABI.
 */
int coll_scatter_points_in_shapes(float density, char *object, int limit, MmiPoint *output, int mask)
{
    float volumes[20];
    char *shapes[20];
    MmiPoint center, random, delta, point, jitter;
    char *shape;
    float total;
    int count, index, last, n, i, kind;
    float value;
    {
        char *shape = *(char **)(*(char **)(object + 0x24) + 0x10);
        if (shape == 0) return 0;
        if (*(short *)(shape + 2))
            func_002A3110(object, *(short *)(shape + 2), 0);
        if (*(int *)(shape + 4) <= 0) return 0;
        shape += 16;
        total = 0.0f;
        count = 0;
        index = 0;
        {
            char *data = shape + 4;
            do {
                int kind;
                unsigned flags = *(unsigned *)(data - 4);
                unsigned active;
                last = flags >> 31;
                kind = flags & 255;
                active = flags & 0x20000;
                if (!(((mask >> index) ^ 1) & 1) && active) {
                    shapes[count] = shape;
                    switch (kind) {
                    case 0: case 1: case 2: {
                        float radius;
                        if (kind < 2) {
                            qcopy_nc(&center, shape + 16);
                            scale_vector(&center, &center, *(float *)(object + 0x2C) * (1.0f / 1024.0f));
                            radius = center.w;
                        } else {
                            qcopy_nc(&center, (void *)(0x70000000 + (*(int *)(data) << 4)));
                            qcopy_nc(&random, shape + 16);
                            FastVecAdd(&center, &center, &random);
                            FastVecScale(&center, &center, *(float *)(object + 0x2C) * (1.0f / 1024.0f));
                            radius = *(float *)(object + 0x2C);
                            radius = *(float *)(data + 8) * radius * (1.0f / 1024.0f);
                        }
                        volumes[count] = radius * (radius * 4.188790321350098f) * radius;
                        break;
                    }
                    case 3: {
                        float radius, height, scaled_height;
                        qcopy_nc(&center, shape + 16);
                        FastVecScale(&center, &center, *(float *)(object + 0x2C));
                        radius = center.w * *(float *)(object + 0x2C);
                        radius *= 1.0f / 1024.0f;
                        height = *(float *)(data);
                        scaled_height = height * (1.0f / 1024.0f);
                        height = scaled_height * *(float *)(object + 0x2C);
                        volumes[count] = radius * (radius * 4.187743186950684f) * radius + radius * (radius * 1.5707963705062866f) * height;
                        break;
                    }
                    case 4: {
                        float radius, height;
                        func_00129148(&center, (void *)(0x70000000 + (*(short *)(data) << 4)), *(float *)(object + 0x2C) * (1.0f / 1024.0f));
                        func_00129148(&random, (void *)(0x70000000 + (*(short *)(data + 2) << 4)), *(float *)(object + 0x2C) * (1.0f / 1024.0f));
                        FastVecSub(&delta, &center, &random);
                        radius = FastVecLength(&delta);
                        height = *(float *)(data + 8) * *(float *)(object + 0x2C) * (1.0f / 1024.0f);
                        volumes[count] = height * (height * 1.5707963705062866f) * radius;
                        break;
                    }
                    }
                    total += volumes[count++];
                }
                index++;
                shape += 32;
                data += 32;
            } while (!last);
        }
    }
    n = (int)(density * total + 0.5f);
    if (limit < n) n = limit;
    for (i = 0; i < n; i++) {
        value = math_random_float_range(0.0f, total);
        {
            int selected;
            for (selected = 0; selected < count; selected++) {
                if (value < volumes[selected]) break;
                value -= volumes[selected];
            }
            shape = shapes[selected];
        }
        kind = (unsigned char)*shape;
        switch (kind) {
        case 0: case 1: case 2: {
            float radius, negative;
            if (kind < 2) {
                qcopy_nc(&center, shape + 16);
                FastVecScale(&center, &center, *(float *)(object + 0x2C));
                radius = center.w * *(float *)(object + 0x2C);
            } else {
                qcopy_nc(&center, (void *)(0x70000000 + (*(int *)(shape + 4) << 4)));
                qcopy_nc(&random, shape + 16);
                FastVecAdd(&center, &center, &random);
                FastVecScale(&center, &center, *(float *)(object + 0x2C));
                radius = *(float *)(shape + 12) * *(float *)(object + 0x2C);
            }
            radius = radius * (1.0f / 1024.0f);
            divide_vector_xyz(&center, &center, 1024.0f);
            negative = -radius;
            for (;;) {
                random.x = math_random_float_range(negative, radius);
                random.y = math_random_float_range(negative, radius);
                random.z = math_random_float_range(negative, radius);
                if (FastVecLength(&random) <= radius) {
                    FastVecAdd(&random, &random, &center);
                    matrix_mul_vec3(&random, &random, object + 0xC0);
                    FastVecAdd(&output[i], &random, object + 0x10);
                    break;
                }
            }
            break;
        }
        case 3: {
            float radius, height, a, b, angle;
            qcopy_nc(&center, shape + 16);
            FastVecScale(&center, &center, *(float *)(object + 0x2C));
            radius = center.w * *(float *)(object + 0x2C);
            height = *(float *)(shape + 4) * *(float *)(object + 0x2C);
            divide_vector_xyz(&center, &center, 1024.0f);
            radius *= 1.0f / 1024.0f;
            height *= 1.0f / 1024.0f;
            a = square_root(math_random_float_range(0.0f, radius * radius));
            b = math_random_float_range(0.0f, height);
            angle = math_random_angle();
            random.x = math_fast_sin_or_cos_a(angle) * a;
            random.y = math_fast_sin_or_cos_b(angle) * a;
            random.z = b;
            FastVecAdd(&random, &random, object + 0x10);
            FastVecAdd(&output[i], &center, &random);
            break;
        }
        case 4: {
            float radius, negative;
            char *data = shape + 4;
            func_00129148(&center, (void *)(0x70000000 + (*(short *)(data) << 4)), *(float *)(object + 0x2C));
            func_00129148(&random, (void *)(0x70000000 + (*(short *)(data + 2) << 4)), *(float *)(object + 0x2C));
            FastVecSub(&delta, &random, &center);
            value = math_random_float_range(0.0f, 1.0f);
            FastVecScale(&delta, &delta, value);
            FastVecAdd(&point, &delta, &center);
            divide_vector_xyz(&point, &point, 1024.0f);
            radius = *(float *)(shape + 12) * *(float *)(object + 0x2C);
            radius *= 1.0f / 1024.0f;
            negative = -radius;
            do {
                jitter.x = math_random_float_range(negative, radius);
                jitter.y = math_random_float_range(negative, radius);
                jitter.z = math_random_float_range(negative, radius);
            } while (!(FastVecLength(&jitter) <= radius));
            FastVecAdd(&jitter, &jitter, &point);
            matrix_mul_vec3(&jitter, &jitter, object + 0xC0);
            FastVecAdd(&output[i], &jitter, object + 0x10);
            break;
        }
        }
    }
    return n;
}
