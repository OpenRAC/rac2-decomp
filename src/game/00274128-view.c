#include "common.h"
/* Adapted from RAC1 gfx_build_view_matrices (GPL-3.0). */
typedef struct { float f[0x50]; } SceneG;
extern char g_camera_basis_vectors[],g_view_state_buffer[],g_view_matrix_buffer[];
extern void multiply_matrix(void *,void *,void *);
extern void scale_vector(void *,void *,float);
extern void FastVecScale(void *,void *,float);
/* Builds the camera view matrices and the clip data from the current camera. */
void gfx_build_view_matrices(void) {
    float m[4][4];
    SceneG *view_matrix;
    char *view_state;
    float *view_floats;
    float off_x;
    float off_y;
    float off_z;

    qcopy(m[0], g_camera_basis_vectors);
    qcopy(m[1], g_camera_basis_vectors + 0x10);
    qcopy(m[2], g_camera_basis_vectors + 0x20);
    view_matrix = (SceneG *)(g_camera_basis_vectors - 0x370);
    view_state = g_view_state_buffer;
    view_floats = (float *)(view_state - 0xC0);
    view_matrix->f[0] = -m[1][0];
    *(int *)&view_matrix->f[0x30 / 4] = 0;
    view_matrix->f[0x10 / 4] = -m[1][1];
    view_matrix->f[0x20 / 4] = -m[1][2];
    view_matrix->f[4 / 4] = -m[2][0];
    view_matrix->f[0x14 / 4] = -m[2][1];
    view_matrix->f[0x24 / 4] = -m[2][2];
    view_matrix->f[8 / 4] = m[0][0];
    view_matrix->f[0x18 / 4] = m[0][1];
    view_matrix->f[0x28 / 4] = m[0][2];
    view_matrix->f[0x3C / 4] = 1.0f;
    *(int *)&view_matrix->f[0x34 / 4] = 0;
    *(int *)&view_matrix->f[0x38 / 4] = 0;
    *(int *)&view_matrix->f[0xC / 4] = 0;
    *(int *)&view_matrix->f[0x1C / 4] = 0;
    *(int *)&view_matrix->f[0x2C / 4] = 0;
    multiply_matrix(&view_matrix->f[0x40 / 4], view_state, view_matrix);
    multiply_matrix(&view_matrix->f[0x80 / 4], view_state + 0x40, view_matrix);
    off_x = view_floats[0x1A0 / 4];
    off_y = view_floats[0x1A4 / 4];
    off_z = view_floats[0x1A8 / 4];
    view_matrix->f[0x80 / 4] += view_matrix->f[0x8C / 4] * off_x;
    view_matrix->f[0x84 / 4] += view_matrix->f[0x8C / 4] * off_y;
    view_matrix->f[0x88 / 4] += view_matrix->f[0x8C / 4] * off_z;
    view_matrix->f[0x90 / 4] += view_matrix->f[0x9C / 4] * off_x;
    view_matrix->f[0x94 / 4] += view_matrix->f[0x9C / 4] * off_y;
    view_matrix->f[0x98 / 4] += view_matrix->f[0x9C / 4] * off_z;
    view_matrix->f[0xA0 / 4] += view_matrix->f[0xAC / 4] * off_x;
    view_matrix->f[0xA4 / 4] += view_matrix->f[0xAC / 4] * off_y;
    view_matrix->f[0xA8 / 4] += view_matrix->f[0xAC / 4] * off_z;
    view_matrix->f[0xB0 / 4] += view_matrix->f[0xBC / 4] * off_x;
    view_matrix->f[0xB4 / 4] += view_matrix->f[0xBC / 4] * off_y;
    view_matrix->f[0xB8 / 4] += view_matrix->f[0xBC / 4] * off_z;
    multiply_matrix(&view_matrix->f[0xC0 / 4], view_state + 0x80, view_matrix);
    scale_vector(&view_matrix->f[0x100 / 4], view_state + 0x80, view_floats[0x1C0 / 4]);
    scale_vector(&view_matrix->f[0x110 / 4], view_state + 0x90, view_floats[0x1C0 / 4]);
    qcopy(&view_matrix->f[0x120 / 4], view_state + 0xA0);
    qcopy(&view_matrix->f[0x130 / 4], view_state + 0xB0);
    multiply_matrix(&view_matrix->f[0x100 / 4], &view_matrix->f[0x100 / 4], view_matrix);
    qcopy(g_view_matrix_buffer, view_matrix);
    qcopy(g_view_matrix_buffer + 0x10, &view_matrix->f[0x10 / 4]);
    qcopy(g_view_matrix_buffer + 0x20, &view_matrix->f[0x20 / 4]);
    FastVecScale(g_view_matrix_buffer + 0x30, &view_matrix->f[0x140 / 4], 1024.0f);
    *(float *)(g_view_matrix_buffer + 0x3C) = 1024.0f;
}
