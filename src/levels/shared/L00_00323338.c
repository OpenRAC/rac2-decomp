#include "common.h"

extern float fast_vec_dist(void *, void *);

extern void matrix_from_basis_rows(void *, void *);

extern void copy_matrix3x4(void *, void *);

typedef int V4TI_F36d8a248 __attribute__((mode(TI)));

/* Finds the joint record closest to the given point and returns its index, also giving back its inverse matrix and position. */
int coll_find_closest_joint_record(void *attachment, void *records, int count, void *src0, void *src1,
                      void *dst, void *ctx)
{
    struct {
        V4TI_F36d8a248 v0;
        V4TI_F36d8a248 v1;
        V4TI_F36d8a248 matrix[4];
    } local;
    void *lp = &local.v0;
    void *matrix = (char *)lp + 0x20;
    char *record;
    int i;
    int best = 0;
    float bestf = 9999.0f;

    local.v0 = *(V4TI_F36d8a248 *)src0;
    local.v1 = *(V4TI_F36d8a248 *)src1;
    for (i = 0; i < count; i++) {
        float f = fast_vec_dist(lp, (char *)records + i * 0x40 + 0x30);
        if (f < bestf) {
            bestf = f;
            best = i;
        }
    }
    record = (char *)records + (best << 6);
    matrix_from_basis_rows(matrix, record);
    copy_matrix3x4(ctx, matrix);
    qcopy(dst, record + 0x30);
    return best;
}
