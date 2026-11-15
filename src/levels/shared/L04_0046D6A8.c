#include "include_asm.h"
#include "common.h"

extern char g_hero_position[];
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

/* Rebuilds the camera's three axes so it looks from its position toward the player. */
void cam_look_at_player(char *obj) {
    Quad offset;
    Quad up_vector;
    char *axis_y;
    char *camera_data = *(char **)(obj + 0x70);

    qcopy(&offset, g_hero_position);
    offset.f[2] = offset.f[2] + *(float *)(camera_data + 0x90);
    up_vector.q = 0;
    up_vector.f[2] = 1.0f;
    up_vector.f[3] = 1.0f;
    FastVecSub(obj, &offset, obj + 0x30);
    vec_scale_to_length(obj, obj, 1.0f);
    axis_y = obj + 0x10;
    FastVecCross(axis_y, obj, &up_vector);
    vec_scale_to_length(axis_y, axis_y, 1.0f);
    FastVecCross(obj + 0x20, axis_y, obj);
}
