#include "common.h"

/* gfx_draw_spinning_layered_quads: the RAC1 counterpart is draw_blarg_heavy_interceptor_spinning_beam
   (rac1-decomp, src/overlays/l14_oltanis/heavy_interceptor_and_turrets.c). Its corner table is a
   complete four-vector, 64-byte object read through $gp, hence this unit's -G64 -Wa,-G64. */

typedef struct {
    float m[4][4];
    u32 col[4];
    float uv[8];
    u64 a, b, c, d;
} DobboBeamQuad;

extern float D_L09_001B1200[4][4] __attribute__((sda)); /* quad corners */
extern char D_L09_001B9A00[];                            /* camera position */

extern u64 GetEffectTextureDescriptor(int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float), vec_length_xy(void *), FastAddRotations(float, float);
extern void FastVecSub(void *, void *, void *), euler_rotation_basis(void *, void *);
extern void FastVecScale(void *, void *, float), transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *), draw_world_quad(void *, void *, int);
extern void VU1_addGSregister(int, u64);

/* Draws sixteen pairs of camera-facing quads offset along the object's spin direction, each pair
   larger and more transparent than the last, then advances the spin angle. */
void gfx_draw_spinning_layered_quads(char *moby) {
    char *d = *(char **)(moby + 0x68);
    float src[4][4];    /* as in RAC1, only rows 0 and 3 are used: the frame keeps rows 1 and 2 */
    DobboBeamQuad pk;
    float mat[4][4];
    float t[4];
    float dir[4];
    float v[4];
    float rot[4];
    float rm[3][4];
    float angle;
    float size;
    float step;
    int r, g, b, a;
    u32 col;
    int i, j;

    moby_transform_joint_to_world(moby, 8, src[3]);
    src[3][3] = 1.0f;
    angle = *(float *)(d + 0x380);
    src[0][0] = math_fast_sin_or_cos_a(angle);
    src[0][1] = math_fast_sin_or_cos_b(angle);
    src[0][2] = 0.0f;
    pk.b = GetEffectTex(0xB);
    pk.c = 0x0000FF9000000260ULL;
    pk.d = 0x8000000048ULL;
    pk.a = 0;
    qcopy(dir, src[0]);
    qcopy(mat[3], src[3]);
    mat[3][3] = 1.0f;
    FastVecSub(v, D_L09_001B9A00, mat[3]);
    rot[2] = mat_fast_helper_a(v[0], v[1]);
    rot[1] = -mat_fast_helper_a(vec_length_xy(v), v[2]);
    rot[0] = 0.0f;
    euler_rotation_basis(rm, rot);
    qcopy(mat[0], rm[0]);
    qcopy(mat[1], rm[1]);
    qcopy(mat[2], rm[2]);
    pk.uv[0] = 1.0f;
    pk.uv[1] = 1.0f;
    pk.uv[3] = 1.0f;
    pk.uv[4] = 1.0f;
    pk.uv[2] = 0.0f;
    pk.uv[5] = 0.0f;
    pk.uv[6] = 0.0f;
    pk.uv[7] = 0.0f;
    r = 127;
    g = 100;
    b = 70;
    a = 90;
    VU1_addGSregister(0x47, 0x51001);
    size = 0.1f;
    step = 0.025f;
    for (i = 0; i < 16; i++) {
        /* red is or-ed in last, after the other three (RAC1 writes one expression) */
        col = (a << 24) | (b << 16) | (g << 8);
        col |= r;
        pk.col[3] = col;
        pk.col[2] = col;
        pk.col[1] = col;
        pk.col[0] = col;
        FastVecScale(t, dir, step);
        for (j = 0; j < 4; j++) {
            FastVecScale(pk.m[j], D_L09_001B1200[j], size);
            transform_vector(pk.m[j], pk.m[j], mat);
            FastVecAdd(pk.m[j], pk.m[j], t);
        }
        draw_world_quad(&pk, 0, 0);
        FastVecScale(t, dir, step * -2.0f);
        for (j = 0; j < 4; j++)
            FastVecAdd(pk.m[j], pk.m[j], t);
        draw_world_quad(&pk, 0, 0);
        g -= 16;
        b -= 16;
        a -= 8;
        size += 0.2f;
        step += 0.25f;
        if (r < 0)
            r = 0;
        if (g < 0)
            g = 0;
        if (b < 0)
            b = 0;
        if (a < 0)
            a = 0;
    }
    *(float *)(d + 0x380) = FastAddRotations(*(float *)(d + 0x380), -0.06981318f);
}

/* Per-moby state of the beam emitter, reached through the moby's +0x68 pointer. */
typedef struct {
    char pad000[0x340];
    float glow_dir[4];
    char pad350[0x20];
    float glow_pos[4];
    float spin_angle;
    char pad384[0x422 - 0x384];
    short damaged;
} DobboBeamState;

/* Draws the camera-facing glow quad at the beam's tip, tinted red while the emitter is damaged
   (the RAC1 counterpart is draw_blarg_heavy_interceptor_camera_facing_glow). */
void beam_draw_tip_glow(char *moby)
{
    float mat[3][4];
    float pos[4];
    float offset[4];
    DobboBeamQuad quad;
    float to_camera[4];
    float rot[4];
    DobboBeamState *state = *(DobboBeamState **)(moby + 0x68);
    int i;

    qcopy(pos, state->glow_pos);
    pos[3] = 1.0f;
    FastVecScale(offset, state->glow_dir, 0.5f);
    FastVecAdd(pos, pos, offset);
    quad.b = GetEffectTextureDescriptor(11);
    quad.c = 0x0000FF9000000260ULL;
    quad.d = 0x8000000048ULL;
    quad.a = 0;
    VU1_addGSregister(0x47, 0x51001);
    FastVecSub(to_camera, D_L09_001B9A00, pos);
    rot[2] = mat_fast_helper_a(to_camera[0], to_camera[1]);
    rot[1] = -mat_fast_helper_a(vec_length_xy(to_camera), to_camera[2]);
    rot[0] = 0.0f;
    euler_rotation_basis(mat, rot);
    quad.uv[0] = 1.0f;
    quad.uv[1] = 1.0f;
    quad.uv[2] = 0.0f;
    quad.uv[3] = 1.0f;
    quad.uv[5] = 0.0f;
    quad.uv[6] = 0.0f;
    quad.uv[7] = 0.0f;
    quad.uv[4] = 1.0f;
    if (state->damaged != 0) {
        quad.col[3] = 0x7F40407F;
        quad.col[2] = 0x7F40407F;
        quad.col[1] = 0x7F40407F;
        quad.col[0] = 0x7F40407F;
    } else {
        quad.col[3] = 0x7F7F7F7F;
        quad.col[2] = 0x7F7F7F7F;
        quad.col[1] = 0x7F7F7F7F;
        quad.col[0] = 0x7F7F7F7F;
    }
    for (i = 0; i < 4; i++) {
        FastVecScale(quad.m[i], D_L09_001B1200[i], 0.75f);
        transform_vector(quad.m[i], quad.m[i], mat);
    }
    draw_world_quad(&quad, 0, 0);
}
