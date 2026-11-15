#include "common.h"
typedef unsigned int CameraQuad __attribute__((mode(TI)));
typedef union { CameraQuad q; float f[4]; } CameraVector;
extern unsigned char g_hero_state[];
extern void FastVecScale(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float vec_length_xy(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
/* Places the follow camera behind the hero and builds its direction axes. */
void cam_update_follow_placement(unsigned char *camera)
{
    CameraVector matrix[4];
    CameraVector position;
    CameraVector up;
    unsigned char *direction;
    unsigned char *state;
    FastVecScale(matrix, g_hero_state, -1.0f);
    FastVecScale(matrix + 1, g_hero_state + 0x10, -1.0f);
    qcopy(matrix + 2, g_hero_state + 0x20);
    qcopy(matrix + 3, g_hero_state + 0x80);
    direction = *(unsigned char **)(camera + 0x70) + 0x70;
    transform_vector(camera + 0x30, direction, matrix);
    FastVecSub(direction, camera + 0x30, g_hero_state + 0x80);
    *(float *)(direction + 0x10) = vec_length_xy(direction);
    state = *(unsigned char **)(camera + 0x70);
    qcopy(&position, g_hero_state + 0x80);
    position.f[2] += *(float *)(state + 0x90);
    up.q = 0;
    up.f[2] = 1.0f;
    up.f[3] = 1.0f;
    FastVecSub(camera, &position, camera + 0x30);
    vec_scale_to_length(camera, camera, 1.0f);
    FastVecCross(camera + 0x10, camera, &up);
    vec_scale_to_length(camera + 0x10, camera + 0x10, 1.0f);
    FastVecCross(camera + 0x20, camera + 0x10, camera);
}
