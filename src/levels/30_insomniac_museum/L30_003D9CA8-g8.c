#include "common.h"

typedef unsigned int DrawQuad __attribute__((mode(TI)));
typedef union { DrawQuad q; float f[4]; } DrawVec;
typedef struct { DrawVec v[9]; } DrawPacket;

extern DrawVec g_facing_sprite_corners[4] __attribute__((sda));
extern DrawVec g_camera_l30_position;
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, int, int);

/* Draws a flat four-corner sprite that faces the camera, with a given size and sideways offset. */
void gfx_l30_draw_facing_sprite(DrawVec *position, DrawPacket *source, float scale, float offset) {
    struct { DrawPacket packet; DrawVec up, side, forward, normal, point, temp; } f;
    int i;
    f.packet = *source;
    source = &f.packet;
    f.up.q = 0; f.up.f[2] = 1; f.up.f[3] = 1;
    qcopy(&f.point, position);
    FastVecSub(&f.side, &g_camera_l30_position, &f.point);
    vec_scale_to_length(&f.side, &f.side, 1.0f);
    FastVecCross(&f.forward, &f.side, &f.up);
    vec_scale_to_length(&f.forward, &f.forward, 1.0f);
    FastVecCross(&f.normal, &f.forward, &f.side);
    FastVecScale(&f.temp, &f.side, offset);
    FastVecAdd(&f.point, &f.point, &f.temp);
    for (i = 0; i < 4; i++) {
        FastVecScale(&f.packet.v[i], &g_facing_sprite_corners[i], scale);
        transform_vector(&f.packet.v[i], &f.packet.v[i], &f.side);
    }
    draw_world_quad(source, 0, 0);
}
