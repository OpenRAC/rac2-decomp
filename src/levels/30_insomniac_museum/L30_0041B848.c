#include "include_asm.h"
#include "common.h"

/* func_L00_003F8280: a 16-byte vector with a quadword view, the 4-row basis the vertex
   transform reads (three axes and a position) and the 144-byte packet with a quad's vertices,
   colours and UVs. */
typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct { Vector row[3]; Vector position; } Frame;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern Vector D_0018A0E0;
extern Vector ref_L30_0041B848_01[4];
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void gfx_world_to_screen_unit(int, float *, float *);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);

extern Vector ref_L30_0041B848_02;
extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecCross(char *, char *, char *);
extern void draw_world_quad(char *, float *, int);
/* Draws a camera-facing textured quad of the given size at a position, optionally rolled and
   moved along the camera direction, then redraws it with texture -1 and UVs projected to the
   screen (from points pulled 20% towards the quad's centre when mode is set), jittered and
   clamped to [0, 1]. */
void gfx_draw_screen_quad(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    gfx_init_quad_packet_state(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    FastVecSub((char *)&frame.row[0], (char *)&ref_L30_0041B848_02, (char *)&frame.position);
    vec_scale_to_length((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    FastVecCross((char *)&frame.row[1], (char *)&frame.row[0], (char *)&D_0018A0E0);
    vec_scale_to_length((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    FastVecCross((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        euler_rotation_basis(scratch.u.rotation, &scratch.angles);
        multiply_matrix3x3(frame.row, frame.row, scratch.u.rotation);
    }
    FastVecScale(&scratch.angles, &frame.row[0], offset);
    FastVecAdd(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = ref_L30_0041B848_01;
        count = 3;
        do {
            FastVecScale(vertex, corner, size);
            ++corner;
            --count;
            transform_vector(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    VU1_addGSregister(0x47, 0x31001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                FastVecAdd(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        FastVecScale(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            FastVecSub((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            FastVecScale(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            FastVecAdd(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            gfx_world_to_screen_unit((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            gfx_world_to_screen_unit((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    gfx_init_quad_packet_state(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x33001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360bULL);
}
