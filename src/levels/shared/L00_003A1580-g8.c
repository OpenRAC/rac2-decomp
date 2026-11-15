#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
extern float D_L00_0023B510[4][32];
extern float D_L00_002947B0[5][4];
extern float D_L00_001B2850[4] MACRO_ADDR;
extern float D_L00_001AF5F0 __attribute__((sda));
extern float D_L00_001AF5F4 __attribute__((sda));
extern float D_L00_001AF5D8 __attribute__((sda));
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_L00_003A2138(int, float *, int);
extern void func_002A3F10(void *, int, int *, void *);
extern float func_00283198(float), func_00283180(float), func_00283B98(float, float);
extern void func_002830C0(void *, void *, void *);
extern void func_L00_003A2BB8(char *, int, char *, char *);
extern void func_L00_003A25D8(int, int, int, int, float);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern void func_L00_003A2258(void *, void *, void *, void *);
extern void func_L00_003A2408(char *, void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_001163B0(void);
extern void func_L00_003A2C60(void *, int, float);
extern void func_0029FCC0(char *, int, char *);

/* Transform the weapon's animated attachment points and draw its beam network. */
void func_L00_003A1580(void *object)
{
    float points[5][4], attachments[5][4], matrix[4][4];
    float normal[4], side[4], endpoint[4], muzzle[4];
    char *moby = object;
    char *state = 0;
    int lookup, i;
    int attachment_count = 5, inner = 0x40, outer = 0x78, channel = 0x47, spark_count = 1;
    VU1_addGSregister(channel, 0x53001ULL);
    state = *(char **)(moby + 0x68);
    UpdateWobblingBeamPoints((int)moby, D_L00_0023B510[0], 4);
    lookup = 0;
    get_moby_joint_matrices(moby, 1, &lookup, matrix);
    matrix[3][0] = 0.0f;
    matrix[3][1] = 0.0f;
    matrix[3][2] = 0.0f;
    matrix[3][3] = 1.0f;
    D_L00_002947B0[1][0] = FastSinOrCosB(D_L00_001AF5F0) * 0.015f + 0.4f;
    D_L00_002947B0[1][2] = FastSinOrCosA(D_L00_001AF5F0) * 0.0149f;
    D_L00_002947B0[1][1] = -FastSinOrCosA(D_L00_001AF5F4) * 0.0151f;
    D_L00_001AF5F0 = FastAddRotations(D_L00_001AF5F0, 0.4188790917f);
    D_L00_001AF5F4 = FastAddRotations(D_L00_001AF5F4, 0.4130613208f);
    for (i = 0; i < attachment_count; i++)
        transform_vector(attachments[i], D_L00_002947B0[i], matrix);
    GetAttachmentPointWorldPos(moby, 0, (char *)points[0], (char *)attachments[0]);
    SpawnBeamFlare((int)moby, (int)points[0], 0x7F7F2020, inner, 0.11f);
    SpawnBeamFlare((int)moby, (int)points[0], 0x7FFF4040, outer, 0.05f);
    GetAttachmentPointWorldPos(moby, 0, (char *)points[1], (char *)attachments[1]);
    if (D_L00_001B2850[3] == -1.0f) {
        qcopy(D_L00_001B2850, points[1]);
        D_L00_001B2850[3] = 0.0f;
    } else {
        int changed = 0;
        SpringVectorToTarget(D_L00_001B2850, points[1], &changed, 0.25f, 0.2000000179f, 0.5f);
    }
    SpawnBeamFlare((int)moby, (int)D_L00_001B2850, 0x7F00397F, inner, *(float *)(state + 0xC) * 0.1856249869f);
    SpawnBeamFlare((int)moby, (int)D_L00_001B2850, 0x7F0072FF, outer, *(float *)(state + 0xC) * 0.08437500149f);
    GetAttachmentPointWorldPos(moby, 1, (char *)points[2], (char *)attachments[2]);
    SpawnBeamFlare((int)moby, (int)points[2], 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)points[2], 0x7FFF4040, outer, 0.025f);
    GetAttachmentPointWorldPos(moby, 2, (char *)points[3], (char *)attachments[3]);
    SpawnBeamFlare((int)moby, (int)points[3], 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)points[3], 0x7FFF4040, outer, 0.025f);
    GetAttachmentPointWorldPos(moby, 3, (char *)points[4], (char *)attachments[4]);
    SpawnBeamFlare((int)moby, (int)points[4], 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)points[4], 0x7FFF4040, outer, 0.025f);
    DrawJitteredBeamCurve(moby, points[0], D_L00_001B2850, D_L00_0023B510[0]);
    ComputeRingOutwardNormal(moby, D_L00_001B2850, normal, *(float *)(state + 0xC) * 0.35f);
    FastVecSub(side, D_L00_001B2850, points[2]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, D_L00_001B2850);
    DrawJitteredBeamCurve(moby, points[2], endpoint, D_L00_0023B510[1]);
    SpawnBeamFlare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (Rand() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        SpawnSparkSpray_L00(endpoint, spark_count, 0.0f);
    FastVecSub(side, D_L00_001B2850, points[3]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, D_L00_001B2850);
    DrawJitteredBeamCurve(moby, points[3], endpoint, D_L00_0023B510[2]);
    SpawnBeamFlare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (Rand() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        SpawnSparkSpray_L00(endpoint, spark_count, 0.0f);
    FastVecSub(side, D_L00_001B2850, points[4]);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, 1.0f);
    FastVecCross(side, side, normal);
    vec_scale_to_length(side, side, *(float *)(state + 0xC) * 0.45f);
    FastVecAdd(endpoint, side, D_L00_001B2850);
    DrawJitteredBeamCurve(moby, points[4], endpoint, D_L00_0023B510[3]);
    SpawnBeamFlare((int)moby, (int)endpoint, 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)endpoint, 0x7FFF4040, outer, 0.025f);
    if (Rand() % 11 == 0 && *(float *)(state + 0xC) > D_L00_001AF5D8)
        SpawnSparkSpray_L00(endpoint, spark_count, 0.0f);
    TransformMobyJointToWorld(moby, 1, (char *)muzzle);
    DrawJitteredBeamCurve(moby, muzzle, points[2], D_L00_0023B510[3]);
    SpawnBeamFlare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    TransformMobyJointToWorld(moby, 2, (char *)muzzle);
    DrawJitteredBeamCurve(moby, muzzle, points[3], D_L00_0023B510[2]);
    SpawnBeamFlare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    TransformMobyJointToWorld(moby, 3, (char *)muzzle);
    DrawJitteredBeamCurve(moby, muzzle, points[4], D_L00_0023B510[1]);
    SpawnBeamFlare((int)moby, (int)muzzle, 0x7F7F2020, inner, 0.055f);
    SpawnBeamFlare((int)moby, (int)muzzle, 0x7FFF4040, outer, 0.025f);
    if (Rand() % 11 == 0) {
        int selected = Rand();
        selected %= 4;
        SpawnSparkSpray_L00(points[selected + 1], spark_count, 0.001f);
    }
    VU1_addGSregister(channel, 0x5360BULL);
}
