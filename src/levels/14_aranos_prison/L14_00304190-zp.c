#include "names.h"
/* func_L14_00304190 and func_L14_00390EC0 need -frac2-zero-ti-por: each clears a stack
 * vector with a por and an sq.
 * In func_L14_00304190 the three sda globals are reached with -G0 macro instructions as in
 * retail: the count pointer is reloaded each iteration instead of keeping its address in a
 * saved register. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

typedef struct { int x, y; float z; } Record;
extern Record *g_level_record_table_ptr __attribute__((sda));
extern char *g_level_record_header __attribute__((sda));
extern char g_level_init_matrix[] __attribute__((sda));
extern float g_level_init_axis_vec[];
extern Record g_level_record_source[];
extern Record g_level_record_dest[];
extern float FastVecDot(void *, void *);
extern void set_identity_matrix(void *);
extern void cam_update_view_rotation(int);
extern void gfx_process_view_entry(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void transform_vector(void *, void *, void *);

/* The rotation rows are a 64-byte .lit table, read-only data. */
typedef struct { TI128 row[4]; } Matrix64 __attribute__((aligned(16)));
extern const Matrix64 g_base_transform_matrix;

/* Sets up the level's table of ten records from a template and refreshes each active entry. */
void level_init_record_table(void) {
    Vector axis;
    Record *dst = g_level_record_dest;
    float scale;
    int i;
    axis.q = 0;
    axis.f[0] = 1.0f;
    g_level_record_table_ptr = dst;
    scale = FastVecDot(g_level_init_axis_vec, &axis);
    {
        Record *src = g_level_record_source;
        int copyIndex;
        for (copyIndex = 0; copyIndex < 10; copyIndex++)
            dst[copyIndex].z = src[copyIndex].z * -scale;
    }
    for (i = 0; i < *(short *)(g_level_record_header + 6); i++) {
        if (i >= 10)
            set_identity_matrix(g_level_init_matrix);
        else
            cam_update_view_rotation(i);
        gfx_process_view_entry(i);
    }
}

/* Builds four scaled and rotated rows and moves them by the given transform. */
void gfx_build_transformed_rows(Vector *output, char *transform, float yScale, float zScale, float angle) {
    Vector axis;
    Matrix64 rows;
    int i;
    axis.q = 0;
    axis.f[0] = 1.0f;
    axis.f[3] = 1.0f;
    rows.row[0] = g_base_transform_matrix.row[0];
    rows.row[1] = g_base_transform_matrix.row[1];
    rows.row[2] = g_base_transform_matrix.row[2];
    rows.row[3] = g_base_transform_matrix.row[3];
    for (i = 0; i < 4; i++) {
        qcopy(&output[i], &rows.row[i]);
        output[i].f[1] *= yScale;
        output[i].f[2] *= zScale;
        if (angle != 0.0f) {
            math_apply_axis_rotation_to_quat(&output[i], &output[i], &axis, angle);
            output[i].f[3] = 1.0f;
        }
        transform_vector(&output[i], &output[i], transform);
    }
}
