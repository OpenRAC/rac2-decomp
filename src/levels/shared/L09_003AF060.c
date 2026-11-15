#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x, y, z, w;
} BeamVector __attribute__((aligned(16)));

typedef struct {
    BeamVector vertices[4];
    unsigned int colors[4];
    float uv[8];
    unsigned long long tag, texture, control, blend;
} BeamPacket;

extern long long func_0027C878(int);
extern int func_001163B0(void);
extern float func_002A7878(float, float);
extern void func_L00_003C1D30(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(char *, char *, float);
extern void func_00282DD8(char *, char *, char *);
extern void func_00282D30(char *, char *, float);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(char *, char *, int);
extern char D_L09_001B9A00[];

/* Draws three textured strips between the two stored endpoints, facing the camera. */
void func_L09_003AF060(char *object)
{
    BeamPacket beam, glow, core;
    BeamVector matrix[4];
    BeamVector beamWidth, glowWidth, coreWidth;
    char *state = *(char **)(object + 0x68);

    beam.texture = GetEffectTextureDescriptor(16);
    beam.control = 0x0000FF9000000260ULL;
    beam.tag = 0;
    beam.blend = 0x8000000040ULL | ((unsigned long long)(func_001163B0() % 2 + 1) << 2);
    beam.colors[1] = 0x7F081840;
    beam.colors[0] = 0x7F081840;
    beam.colors[3] = 0x7F081840;
    beam.colors[2] = 0x7F081840;

    glow.texture = GetEffectTextureDescriptor(16);
    glow.control = 0x0000FF9000000260ULL;
    glow.blend = 0x8000000048ULL;
    glow.colors[1] = 0x1F030B1F;
    glow.colors[0] = 0x1F030B1F;
    glow.colors[3] = 0x1F030B1F;
    glow.colors[2] = 0x1F030B1F;
    glow.tag = 0;

    core.texture = GetEffectTextureDescriptor(16);
    core.control = 0x0000FF9000000260ULL;
    core.blend = 0x8000000048ULL;
    core.tag = 0;
    core.colors[1] = 0x7F7F7F7F;
    core.colors[0] = 0x7F7F7F7F;
    core.colors[3] = 0x7F7F7F7F;
    core.colors[2] = 0x7F7F7F7F;

    *(TI128 *)&beamWidth = 0;
    *(TI128 *)&glowWidth = 0;
    *(TI128 *)&coreWidth = 0;
    beamWidth.w = 1.0f;
    glowWidth.w = 1.0f;
    coreWidth.w = 1.0f;
    coreWidth.z = func_002A7878(0.2f, 0.25f);
    beamWidth.z = func_002A7878(0.3f, 0.4f);
    glowWidth.z = beamWidth.z + beamWidth.z;
    coreWidth.z *= *(float *)(state + 0x50);
    glowWidth.z *= *(float *)(state + 0x50);
    beamWidth.z *= *(float *)(state + 0x50);

    func_L00_003C1D30(&beam);
    func_L00_003C1D30(&glow);
    func_L00_003C1D30(&core);
    beam.uv[0] = 0;
    beam.uv[1] = 0;
    beam.uv[2] = 0;
    beam.uv[3] = 1;
    beam.uv[4] = 1;
    beam.uv[5] = 0;
    beam.uv[6] = 1;
    beam.uv[7] = 1;
    glow.uv[0] = 0;
    glow.uv[1] = 0;
    glow.uv[2] = 0;
    glow.uv[3] = 1;
    glow.uv[4] = 1;
    glow.uv[5] = 0;
    glow.uv[6] = 1;
    glow.uv[7] = 1;
    core.uv[0] = 0;
    core.uv[1] = 0;
    core.uv[2] = 0;
    core.uv[3] = 1;
    core.uv[4] = 1;
    core.uv[5] = 0;
    core.uv[6] = 1;
    core.uv[7] = 1;

    FastVecSub(&matrix[0], state + 0x20, state + 0x10);
    vec_scale_to_length((char *)&matrix[0], (char *)&matrix[0], 1.0f);
    FastVecSub(&matrix[1], D_L09_001B9A00, state + 0x10);
    FastVecCross((char *)&matrix[2], (char *)&matrix[1], (char *)&matrix[0]);
    vec_scale_to_length((char *)&matrix[2], (char *)&matrix[2], 1.0f);
    FastVecCross((char *)&matrix[1], (char *)&matrix[0], (char *)&matrix[2]);

    qcopy(&matrix[3], state + 0x10);
    qcopy(&beam.vertices[0], &beamWidth);
    qcopy(&glow.vertices[0], &glowWidth);
    qcopy(&core.vertices[0], &coreWidth);
    FastVecScale((char *)&beam.vertices[1], (char *)&beam.vertices[0], -1.0f);
    FastVecScale((char *)&glow.vertices[1], (char *)&glow.vertices[0], -1.0f);
    FastVecScale((char *)&core.vertices[1], (char *)&core.vertices[0], -1.0f);
    transform_vector(&beam.vertices[0], &beam.vertices[0], matrix);
    transform_vector(&beam.vertices[1], &beam.vertices[1], matrix);
    transform_vector(&glow.vertices[0], &glow.vertices[0], matrix);
    transform_vector(&glow.vertices[1], &glow.vertices[1], matrix);
    transform_vector(&core.vertices[0], &core.vertices[0], matrix);
    transform_vector(&core.vertices[1], &core.vertices[1], matrix);

    qcopy(&matrix[3], state + 0x20);
    qcopy(&beam.vertices[2], &beamWidth);
    qcopy(&glow.vertices[2], &glowWidth);
    qcopy(&core.vertices[2], &coreWidth);
    FastVecScale((char *)&beam.vertices[3], (char *)&beam.vertices[2], -1.0f);
    FastVecScale((char *)&glow.vertices[3], (char *)&glow.vertices[2], -1.0f);
    FastVecScale((char *)&core.vertices[3], (char *)&core.vertices[2], -1.0f);
    transform_vector(&beam.vertices[2], &beam.vertices[2], matrix);
    transform_vector(&beam.vertices[3], &beam.vertices[3], matrix);
    transform_vector(&glow.vertices[2], &glow.vertices[2], matrix);
    transform_vector(&glow.vertices[3], &glow.vertices[3], matrix);
    transform_vector(&core.vertices[2], &core.vertices[2], matrix);
    transform_vector(&core.vertices[3], &core.vertices[3], matrix);

    draw_world_quad((char *)&beam, 0, 0);
    draw_world_quad((char *)&glow, 0, 0);
    draw_world_quad((char *)&core, 0, 0);
}
