#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct {
    float vertex[4][4];
    unsigned int color[4];
    float uv[4][2];
    char tail[32];
} __attribute__((aligned(16))) DrawBatch;
extern int D_0018C0B4[];
extern float D_L00_001AF750 __attribute__((sda));
extern int D_L00_001AF74C __attribute__((sda));
extern int D_L00_001AF748 __attribute__((sda));
extern float D_L00_001AF720 __attribute__((sda));
extern float g_camera_l00_position[];
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern float D_L00_001A8F20[] MACRO_ADDR;
extern short D_L00_001AF6D8[][4][2] SDATA(D_L00_001AF6D8);
extern short D_L00_001AF6DA[][4][2] MACRO_ADDR;
extern float D_L00_00294A80[][4];
extern float D_L00_00294B10[][2];
extern char *level_get_slot_body(int, int);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern int FloatToInt(float);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void draw_world_quad(void *, void *, int);

/* Builds and submits the two quads for each active effect record. */
void DrawEffectRecordQuads(char *object)
{
    DrawBatch first, second __attribute__((aligned(16)));
    Vector forward, right, up;
    Vector position, normal;
    Vector scaled, local, rotated;
    int corner;
    char *base;
    float alphaScale = 128.0f;
    int stride = 112;
    *(Quadword *)normal = 0;
    normal[2] = 1.0f;
    normal[3] = 1.0f;
    base = level_get_slot_body(MOBY_CLASS_PULSE_RIFLE, *(short *)(*(char **)(object + 104) + 26));
    gfx_init_quad_packet_state(&first, 54, 0, 128);
    gfx_init_quad_packet_state(&second, 54, 1, 128);
    if (D_0018C0B4[0] == 29)
        alphaScale = 32.0f;
    {
        int index, texture;
        char *record = 0;
        unsigned int color = 0;
        float age, radius, distance, sine, cosine, width;
        float *weight = 0;
        short (*shapeRow)[2];
        short (*uvRow)[2];
        float scale, angle, wave, blend, growth;
        int side, i;
        for (i = 0; i < 80; ++i) {
            record = base + i * stride;
            if (*(short *)(record + 18)) {
                age = (float)*(short *)(record + 16) * *(float *)(record + 32);
                scale = alphaScale * age;
                color = (unsigned int)FloatToInt(scale) << 24;
                angle = age * 3.1415927f * D_L00_001AF750;
                wave = math_fast_sin_or_cos_b(math_wrap_angle_to_pi(angle));
                blend = math_fabs(wave);
                color |= FastTweenColor(D_L00_001AF74C, D_L00_001AF748, blend);
                first.color[3] = color;
                first.color[2] = color;
                first.color[1] = color;
                first.color[0] = color;
                second.color[3] = color;
                second.color[2] = color;
                second.color[1] = color;
                second.color[0] = color;
                distance = *(float *)(record + 28);
                growth = D_L00_001AF720 - distance;
                radius = distance + growth * age;
                qcopy(position, record);
                FastVecSub(forward, g_camera_l00_position, position);
                vec_scale_to_length(forward, forward, 1.0f);
                if (D_L00_001A8FF0[0])
                    cam_compute_view_direction(position, normal, 1);
                FastVecCross(right, forward, normal);
                vec_scale_to_length(right, right, 1.0f);
                FastVecCross(up, right, forward);
                forward[3] = right[3] = up[3] = 0.0f;
                position[3] = 1.0f;
                sine = math_fast_sin_or_cos_a(*(float *)(record + 20));
                cosine = math_fast_sin_or_cos_b(*(float *)(record + 20));
                {
                    float *weights = (float *)(record + 40);
                    for (side = 0; side < 4; ++side) {
                        shapeRow = D_L00_001AF6D8[side];
                        uvRow = D_L00_001AF6DA[side];
                        for (corner = 0; corner < 4; ++corner) {
                            index = shapeRow[corner][0];
                            texture = uvRow[corner][0];
                            weight = weights + index;
                            if (*weight != 0.0f)
                                vec_scale_to_length(scaled, D_L00_00294A80[index], *weight);
                            else
                                qcopy(scaled, D_L00_001A8F20);
                            FastVecAdd(local, D_L00_00294A80[index], scaled);
                            rotated[0] = local[0];
                            rotated[3] = 1.0f;
                            rotated[1] = local[1] * sine - local[2] * cosine;
                            rotated[2] = local[1] * cosine + local[2] * sine;
                            FastVecScale(first.vertex[corner], rotated, radius);
                            first.uv[corner][0] = D_L00_00294B10[texture][0];
                            first.uv[corner][1] = D_L00_00294B10[texture][1];
                            width = (1.0f - age) * 0.075f;
                            FastVecScale(scaled, right, width);
                            FastVecAdd(second.vertex[corner], first.vertex[corner], scaled);
                            FastVecScale(scaled, up, width);
                            FastVecAdd(second.vertex[corner], first.vertex[corner], scaled);
                            second.uv[corner][0] = D_L00_00294B10[texture][0];
                            second.uv[corner][1] = D_L00_00294B10[texture][1];
                        }
                        draw_world_quad(&first, forward, 0);
                        draw_world_quad(&second, forward, 0);
                    }
                }
            }
        }
    }
}
