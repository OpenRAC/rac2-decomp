#include "common.h"

extern int FastDecTimer(void *);
extern void part_kill(void *);
extern void moby_transform_joint_point(void *, int, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern char g_camera_l00_position[];

/* Particle update for a particle attached to an owner moby: kills it when its timer ends or the
   owner is gone, places it on an owner joint (bone matrix) or at an offset from the owner, can
   fade it by the facing angle, then moves it towards the point at D_L00_001B8DC0. */
void UpdateOwnerAttachedDriftParticle(char *p)
{
    union {
        struct { float matrix[16]; float transformed[4]; } m;
        float v[3][4];
    } w __attribute__((aligned(16)));
    char *q = p + 0x20;
    char *owner;
    char *pos;
    char *ownerpos;
    float dot;

    if (*(short *)(p + 0xA) >= 0 && FastDecTimer(p + 0xA)) {
        part_kill(p);
        return;
    }
    owner = *(char **)q;
    if (owner) {
        if (*(signed char *)(owner + 0x20) < 0) {
            part_kill(p);
            return;
        }
        ownerpos = owner + 0x10;
        if (*(int *)(q + 4) >= 0) {
            char *initial = p + 0x10;
            moby_transform_joint_point(owner, *(int *)(q + 4), w.m.matrix);
            w.m.matrix[15] = 0;
            transform_vector(w.m.transformed, q + 0x10, w.m.matrix);
            FastVecAdd(initial, &w.m.matrix[12], w.m.transformed);
            pos = initial;
            goto drift;
        } else {
            char *initial = p + 0x10;
            qcopy(initial, ownerpos);
            matrix_mul_vec3(w.v[0], q + 0x10, owner + 0xC0);
            FastVecAdd(initial, initial, w.v[0]);
            pos = initial;
        }
        if (*(short *)(q + 0xE)) {
            FastVecSub(w.v[1], pos, g_camera_l00_position);
            p[8] = FloatToInt(FastVecDot(w.v[1], g_camera_l00_position + 0x230) * 6.0f);
        }
        if (*(short *)(q + 0xC)) {
            FastVecSub(w.v[2], pos, ownerpos);
            vec_scale_to_length(w.v[1], w.v[1], 1.0f);
            vec_scale_to_length(w.v[2], w.v[2], 1.0f);
            dot = -FastVecDot(w.v[1], w.v[2]);
            if (dot < 0.0f)
                *(unsigned int *)(p + 4) &= 0x05FFFFFF;
            else
                *(unsigned int *)(p + 4) = (*(unsigned int *)(p + 4) & 0xFFFFFF) |
                    (FloatToInt(IntToFloat(*(unsigned char *)(p + 7)) * dot) << 24);
        }
    } else {
        char *initial = p + 0x10;
        qcopy(initial, q + 0x10);
        pos = initial;
    }
drift:
    FastVecSub(w.v[0], g_camera_l00_position, pos);
    vec_scale_to_length(w.v[0], w.v[0], *(float *)(q + 8));
    FastVecAdd(pos, pos, w.v[0]);
}
