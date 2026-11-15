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
extern char g_camera_eye_state[];

/* Particle update for a particle attached to an owner moby: kills it when its timer ends or the
   owner is gone, places it on an owner joint (bone matrix) or at an offset from the owner, can
   fade it by the facing angle, then moves it towards the point at D_001B5340. */
/* Updates a particle that is attached to another object. */
void part_update_moby_attached(char *particle)
{
    union {
        struct { float matrix[16]; float transformed[4]; } m;
        float v[3][4];
    } work __attribute__((aligned(16)));
    char *attach = particle + 0x20;
    char *owner;
    char *pos;
    char *ownerpos;
    float dot;

    if (*(short *)(particle + 0xA) >= 0 && FastDecTimer(particle + 0xA)) {
        part_kill(particle);
        return;
    }
    owner = *(char **)attach;
    if (owner) {
        if (*(signed char *)(owner + 0x20) < 0) {
            part_kill(particle);
            return;
        }
        ownerpos = owner + 0x10;
        if (*(int *)(attach + 4) >= 0) {
            char *initial = particle + 0x10;
            moby_transform_joint_point(owner, *(int *)(attach + 4), work.m.matrix);
            work.m.matrix[15] = 0;
            transform_vector(work.m.transformed, attach + 0x10, work.m.matrix);
            FastVecAdd(initial, &work.m.matrix[12], work.m.transformed);
            pos = initial;
            goto drift;
        } else {
            char *initial = particle + 0x10;
            qcopy(initial, ownerpos);
            matrix_mul_vec3(work.v[0], attach + 0x10, owner + 0xC0);
            FastVecAdd(initial, initial, work.v[0]);
            pos = initial;
        }
        if (*(short *)(attach + 0xE)) {
            FastVecSub(work.v[1], pos, g_camera_eye_state);
            particle[8] = FloatToInt(FastVecDot(work.v[1], g_camera_eye_state + 0x230) * 6.0f);
        }
        if (*(short *)(attach + 0xC)) {
            FastVecSub(work.v[2], pos, ownerpos);
            vec_scale_to_length(work.v[1], work.v[1], 1.0f);
            vec_scale_to_length(work.v[2], work.v[2], 1.0f);
            dot = -FastVecDot(work.v[1], work.v[2]);
            if (dot < 0.0f)
                *(unsigned int *)(particle + 4) &= 0x05FFFFFF;
            else
                *(unsigned int *)(particle + 4) = (*(unsigned int *)(particle + 4) & 0xFFFFFF) |
                    (FloatToInt(IntToFloat(*(unsigned char *)(particle + 7)) * dot) << 24);
        }
    } else {
        char *initial = particle + 0x10;
        qcopy(initial, attach + 0x10);
        pos = initial;
    }
drift:
    FastVecSub(work.v[0], g_camera_eye_state, pos);
    vec_scale_to_length(work.v[0], work.v[0], *(float *)(attach + 8));
    FastVecAdd(pos, pos, work.v[0]);
}
