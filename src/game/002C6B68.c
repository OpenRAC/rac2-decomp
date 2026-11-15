#include "common.h"

extern int func_00282978(void *);
extern void func_002B9180(void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern char D_001B5340[];

/* Particle update for a particle attached to an owner moby: kills it when its timer ends or the
   owner is gone, places it on an owner joint (bone matrix) or at an offset from the owner, can
   fade it by the facing angle, then moves it towards the point at D_001B5340. */
/* Updates a particle that is attached to another object. */
void func_002C6B68(char *particle)
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
        KillParticle(particle);
        return;
    }
    owner = *(char **)attach;
    if (owner) {
        if (*(signed char *)(owner + 0x20) < 0) {
            KillParticle(particle);
            return;
        }
        ownerpos = owner + 0x10;
        if (*(int *)(attach + 4) >= 0) {
            char *initial = particle + 0x10;
            TransformMobyJointPoint(owner, *(int *)(attach + 4), work.m.matrix);
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
            FastVecSub(work.v[1], pos, gCameraState_001B5340);
            particle[8] = FloatToInt(FastVecDot(work.v[1], gCameraState_001B5340 + 0x230) * 6.0f);
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
    FastVecSub(work.v[0], gCameraState_001B5340, pos);
    vec_scale_to_length(work.v[0], work.v[0], *(float *)(attach + 8));
    FastVecAdd(pos, pos, work.v[0]);
}
