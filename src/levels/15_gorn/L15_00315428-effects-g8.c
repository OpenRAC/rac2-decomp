#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union Vec {
    Quad q;
    float f[4];
} Vec;
#define FIELD(t, p, o) (*(t *)((char *)(p) + (o)))

typedef struct Stage {
    char pad[0x30];
    int busy, frame;
    char pad38[12];
    short count;
    char pad46[0x146];
    char *objects[4];
} Stage;

extern Stage D_L15_001BD4C0;
extern int D_001A79F0;
extern float D_L15_00293010[][8];
extern char D_L15_001A9420[16] SDATA(D_L15_001A9420);
extern char D_L15_001A9430[16] SDATA(D_L15_001A9430);
extern char D_L15_001A9440[16] SDATA(D_L15_001A9440);
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
extern void func_00283AF0(void *, void *);
extern void func_00283958(void *, void *);
extern void func_L01_0031A278(void *, void *, float, float, float);
extern void func_L05_00424990(void *, int, int, int, int, int, int, int, int, int, int, float);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L05_00419CC8(void *, void *, void *, int, int, int, int, int, float);
extern void func_0029FC20(void *, int, void *);
extern void func_00283678(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern void func_L00_0033C0D0(void *, void *, void *, void *, int);

/* Updates the stage objects and emits effects at the scripted frame counts. */
void func_L15_00315428(void)
{
    /* The joint transform reuses the earlier effect vectors and writes 64 bytes. */
    union {
        struct { Vec a, b, c; } effect;
        Vec joint[4];
    } scratch;
    Vec matrix[3], offset, velocity, first, second, third, fourth;
    char *obj;
    int i;
    float sign;
    float *row;

    StartStartupAnimations();
    for (i = 0; i < D_L15_001BD4C0.count; i++) {
        char *obj = D_L15_001BD4C0.objects[i];
        if (obj && FIELD(short, obj, 0xAA) == 0xE29) {
            FIELD(unsigned short, obj, 0x34) |= 0x800;
        }
        if (FIELD(short, obj, 0xAA) == 0xD54) {
            UpdateEquipmentPieces(obj);
        }
        if (obj && FIELD(short, obj, 0xAA) == 0xFA0 /* TV Screens */) {
            if (FIELD(char *, obj, 0x68)) {
                StoreAngleUpdateResult(obj, FIELD(char *, obj, 0x68) + 0xC,
                                 0x80AAAAD2, 0x80396464, 0.061086535f);
            }
        }
    }
    if (gCurrentMapIndex != 15 || D_L15_001BD4C0.busy) {
        return;
    }

    obj = D_L15_001BD4C0.objects[2];
    if (D_L15_001BD4C0.frame == 13) {
        FastVectorToIntHelper(FIELD(char *, obj, 0x58) + 0x10, &scratch.effect.b);
        quaternion_to_rotation_basis(&scratch.effect.b, obj + 0xC0);
        ComputeMobyLocalPoint(obj, &scratch.effect.a, 4, 3, 5);
        SpawnShockwaveBurst(&scratch.effect.a, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 1.5f);
    }
    if ((unsigned)(D_L15_001BD4C0.frame - 20) >= 31 && !RandomIntBelow(3)) {
        sign = 1;
        if (RandomIntBelow(2)) {
            sign = -1;
        }
        row = D_L15_00293010[RandomIntBelow(3)];
        ComputeMobyLocalPoint(obj, &scratch.effect.a, row[0], row[1], row[2]);
        ComputeMobyLocalPoint(obj, &scratch.effect.b, row[4], row[5], row[6]);
        scratch.effect.b.f[0] += RandomSignedFloatRange(.5f, 1.5f);
        scratch.effect.b.f[1] += RandomSignedFloatRange(.5f, 1.5f);
        scratch.effect.b.f[2] += RandomSignedFloatRange(.5f, 1.5f);
        FastVecSub(&scratch.effect.c, &scratch.effect.b, &scratch.effect.a);
        vec_scale_to_length(&scratch.effect.c, &scratch.effect.c, 1.1666667f);
        SpawnShotEffectMoby(obj, &scratch.effect.a, &scratch.effect.c, 0xbe4620, 0x783214, 1, 0, 1, sign);
    }
    if (D_L15_001BD4C0.frame < 140) {
        char *obj = D_L15_001BD4C0.objects[3];
        float strength = .4f;
        TransformMobyJointPoint(obj, 0, scratch.joint);
        /* Only the three rotation rows are needed by the following transforms. */
        copy_matrix3x4(matrix, scratch.joint);
        offset.q = 0;
        offset.f[0] = -.3f;
        offset.f[3] = 1;
        velocity.q = 0;
        matrix_mul_vec3(&first, &offset, matrix);
        FastVecAdd(&first, &first, obj + 0x10);
        first.f[3] = 0;
        second.q = first.q;
        third.q = first.q;
        fourth.q = first.q;
        AddRandomOffsetToVector(&first, .3f);
        AddRandomOffsetToVector(&second, .3f);
        AddRandomOffsetToVector(&third, .3f);
        AddRandomOffsetToVector(&fourth, .3f);
        velocity.f[0] = -(RandomFloatRange(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        SpawnObjectRelativeParticle(obj, &first, &velocity, D_L15_001A9420, 1);
        velocity.f[0] = -(RandomFloatRange(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        SpawnObjectRelativeParticle(obj, &second, &velocity, D_L15_001A9420, 1);
        velocity.f[0] = -(RandomFloatRange(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        SpawnObjectRelativeParticle(obj, &third, &velocity, D_L15_001A9430, 1);
        velocity.f[0] = -(RandomFloatRange(30, 40) * 0.016666668f) * strength;
        matrix_mul_vec3(&velocity, &velocity, matrix);
        SpawnObjectRelativeParticle(obj, &fourth, &velocity, D_L15_001A9440, 1);
    }
}
