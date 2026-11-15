#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { Vector row[3]; } Matrix3;
extern unsigned char g_hero_state[];
extern void set_identity_rotation_rows(Matrix3 *);
extern void vec_scale_to_length(Vector *, Vector *, float);
extern void multiply_matrix3x3(Matrix3 *, Matrix3 *, Matrix3 *);
extern void FastVecSub(Vector *, Vector *, Vector *);
extern void matrix_mul_vec3(Vector *, Vector *, Matrix3 *);
extern void FastVecAdd(Vector *, Vector *, Vector *);

/* Apply the pending axis scales to the player and its attached objects. */
void ApplyHeroAxisScales(void) {
    Matrix3 scale;
    Matrix3 transformed;
    Vector delta;
    unsigned char *player = g_hero_state;
    int row, column;
    if (*(short *)(player + 0x2500) == 0) return;
    set_identity_rotation_rows(&scale);
    vec_scale_to_length(&scale.row[0], &scale.row[0], *(float *)(player + 0x2020));
    vec_scale_to_length(&scale.row[1], &scale.row[1], *(float *)(player + 0x2024));
    vec_scale_to_length(&scale.row[2], &scale.row[2], *(float *)(player + 0x2028));
    multiply_matrix3x3(&transformed, &scale, (Matrix3 *)(player + 0x40));
    multiply_matrix3x3(&transformed, (Matrix3 *)player, &transformed);
    {
        unsigned char *object = *(unsigned char **)(player + 0x2290);
        multiply_matrix3x3((Matrix3 *)(object + 0xC0), (Matrix3 *)(object + 0xC0), &scale);
    }
    if (player[0x22B4] == 0) {
        for (row = 0; row < 7; ++row) {
            for (column = 0; column < 3; ++column) {
                unsigned char *player = g_hero_state;
                unsigned char *object = *(unsigned char **)(player + row * 0x50 + 0x1220);
                if (column == 1) object = *(unsigned char **)(player + row * 0x50 + 0x1224);
                else if (column == 2) object = *(unsigned char **)(player + row * 0x50 + 0x1228);
                if (object) {
                    multiply_matrix3x3((Matrix3 *)(object + 0xC0), &transformed, (Matrix3 *)(object + 0xC0));
                    FastVecSub(&delta, (Vector *)(object + 0x10), (Vector *)(player + 0x80));
                    matrix_mul_vec3(&delta, &delta, &transformed);
                    FastVecAdd((Vector *)(object + 0x10), &delta, (Vector *)(player + 0x80));
                }
            }
        }
    }
    {
        unsigned char *tail = g_hero_state;
        if (*(float *)(g_hero_state + 0x2020) == 1.0f &&
            *(float *)(g_hero_state + 0x2024) == 1.0f &&
            *(float *)(g_hero_state + 0x2028) == 1.0f)
            *(short *)(tail + 0x2500) = 0;
        {
            unsigned char *tail = g_hero_state;
            *(float *)(tail + 0x2020) = 1.0f;
            *(float *)(tail + 0x2024) = 1.0f;
            *(float *)(tail + 0x2028) = 1.0f;
        }
    }
}
