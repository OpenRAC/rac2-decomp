#include "common.h"
/* Adapted from RAC1 walloper_and_beam_effects.c (OpenRAC, GPL-3.0). */
extern int GetEffectTextureDescriptor(int);
extern void FastVecSub(void*,void*,void*), FastVecCross(void*,void*,void*), FastVecAdd(void*,void*,void*);
extern float FastVecLength(void*);
extern void FastVecScale(void*,void*,float), draw_world_quad(void*,void*,int), VU1_addGSregister(int,long);
extern float g_camera_eye_state[];
extern int D_001AEE98 __attribute__((sda));
extern int D_001AEE54 __attribute__((sda));
extern int D_001AEE9C __attribute__((sda));
extern int D_001AEE58 __attribute__((sda));
extern float D_001AEE4C __attribute__((sda));
extern int D_001AEE5C __attribute__((sda));
typedef float RW_2BBDE8[4] __attribute__((aligned(16)));
typedef struct { float v[4]; } P_2BBDE8;
typedef struct {
    int c[4];
    float f[8];
    long z4, q0, q1, q2;
} RT_2BBDE8;

/* The EE ABI independently orders integer and floating-point arguments.
 * This interleaving preserves a0-a3 and f12-f14. */
// Draws a ribbon of quads along a polyline, in two passes with edge colouring and a scrolled texture (colours from globals).
void DrawBeamAndArcTwoPassQuads(void *points, int alphaA, int alphaB, float sx, float width, int count, float extend) {
    RW_2BBDE8 coreQuad[4];
    RT_2BBDE8 corePacket;
    RW_2BBDE8 q2[4];
    RT_2BBDE8 haloPacket;
    RW_2BBDE8 normal, haloOffset, eyeRay, tangent, firstPoint, lastPoint, firstRay, lastRay, toEye, extension;
    int i, coreColor, haloColor;
    float length, initialLength, haloLength, firstLength, lastLength;
    corePacket.q0 = GetEffectTextureDescriptor(*(int *)&D_001AEE98);
    coreColor = *(int *)&D_001AEE54 | (alphaA << 24);
    corePacket.q2 = 0x8000000048L;
    corePacket.q1 = 0xFF9000000260L;
    corePacket.z4 = 0;
    corePacket.c[3] = coreColor;
    corePacket.c[2] = coreColor;
    corePacket.c[1] = coreColor;
    corePacket.c[0] = coreColor;
    haloPacket.q0 = GetEffectTextureDescriptor(*(int *)&D_001AEE9C);
    haloColor = *(int *)&D_001AEE58 | (alphaB << 24);
    haloPacket.q2 = corePacket.q2;
    haloPacket.q1 = corePacket.q1;
    haloPacket.z4 = corePacket.z4;
    haloPacket.c[3] = haloColor;
    haloPacket.c[2] = haloColor;
    haloPacket.c[1] = haloColor;
    haloPacket.c[0] = haloColor;
    haloPacket.f[0] = 0; haloPacket.f[1] = 0; haloPacket.f[2] = 0; haloPacket.f[3] = 1.0f; haloPacket.f[4] = 1.0f; haloPacket.f[5] = 0; haloPacket.f[6] = 1.0f; haloPacket.f[7] = 1.0f;
    corePacket.f[0] = D_001AEE4C;
    corePacket.f[1] = 0;
    corePacket.f[2] = D_001AEE4C;
    corePacket.f[3] = 1.0f;
    corePacket.f[4] = 1.0f + D_001AEE4C;
    corePacket.f[5] = 0;
    corePacket.f[6] = 1.0f + D_001AEE4C;
    corePacket.f[7] = 1.0f;
    FastVecSub(eyeRay, points, g_camera_eye_state);
    FastVecSub(tangent, &((P_2BBDE8 *)points)[1], points);
    FastVecCross(normal, tangent, eyeRay);
    initialLength = FastVecLength(normal);
    if (initialLength != 0) initialLength = 1.0f / initialLength;
    FastVecScale(normal, normal, *(float *)&D_001AEE5C * initialLength);
    FastVecAdd(coreQuad[0], points, normal);
    FastVecSub(coreQuad[1], points, normal);
    for (i = 1; i < count - 1; i++) {
        FastVecSub(eyeRay, &((P_2BBDE8 *)points)[i], g_camera_eye_state);
        FastVecSub(tangent, &((P_2BBDE8 *)points)[i + 1], &((P_2BBDE8 *)points)[i]);
        FastVecCross(normal, tangent, eyeRay);
        length = FastVecLength(normal);
        if (length != 0) length = 1.0f / length;
        FastVecScale(normal, normal, *(float *)&D_001AEE5C * length);
        FastVecAdd(coreQuad[2], &((P_2BBDE8 *)points)[i], normal);
        FastVecSub(coreQuad[3], &((P_2BBDE8 *)points)[i], normal);
        if (i == 1) {
            corePacket.c[1] = *(int *)&D_001AEE54;
            corePacket.c[0] = *(int *)&D_001AEE54;
        } else if (i == count - 2) {
            corePacket.c[3] = *(int *)&D_001AEE54;
            corePacket.c[2] = *(int *)&D_001AEE54;
        } else if (i == 2) {
            corePacket.c[1] = coreColor;
            corePacket.c[0] = coreColor;
        }
        draw_world_quad(coreQuad, 0, 0);
        qcopy(coreQuad[0], coreQuad[2]);
        qcopy(coreQuad[1], coreQuad[3]);
    }
    for (i = 0; i < count - 1; i++) {
        FastVecSub(firstRay, &((P_2BBDE8 *)points)[i], g_camera_eye_state);
        FastVecSub(lastRay, &((P_2BBDE8 *)points)[i + 1], g_camera_eye_state);
        firstLength = FastVecLength(firstRay);
        lastLength = FastVecLength(lastRay);
        if (lastLength < firstLength) {
            if (lastLength == 0) qcopy(lastRay, firstRay);
            else FastVecScale(lastRay, lastRay, firstLength / lastLength);
        } else {
            if (firstLength == 0) qcopy(firstRay, lastRay);
            else FastVecScale(firstRay, firstRay, lastLength / firstLength);
        }
        FastVecAdd(firstPoint, g_camera_eye_state, firstRay);
        FastVecAdd(lastPoint, g_camera_eye_state, lastRay);
        FastVecSub(tangent, lastPoint, firstPoint);
        FastVecScale(extension, tangent, extend);
        FastVecSub(firstPoint, firstPoint, extension);
        FastVecAdd(lastPoint, lastPoint, extension);
        FastVecSub(toEye, g_camera_eye_state, firstPoint);
        FastVecCross(normal, toEye, tangent);
        haloLength = FastVecLength(normal);
        if (haloLength != 0) haloLength = 1.0f / haloLength;
        FastVecScale(haloOffset, normal, width * haloLength);
        FastVecAdd(q2[0], firstPoint, haloOffset);
        FastVecSub(q2[1], firstPoint, haloOffset);
        FastVecAdd(q2[2], lastPoint, haloOffset);
        FastVecSub(q2[3], lastPoint, haloOffset);
        if (i == 0) {
            haloPacket.c[1] = *(int *)&D_001AEE58;
            haloPacket.c[0] = *(int *)&D_001AEE58;
        } else if (i == count - 2) {
            haloPacket.c[3] = *(int *)&D_001AEE58;
            haloPacket.c[2] = *(int *)&D_001AEE58;
        } else if (i == 1) {
            haloPacket.c[1] = haloColor;
            haloPacket.c[0] = haloColor;
        }
        draw_world_quad(q2, 0, 0);
    }
    VU1_addGSregister(0x47, 0x5360B);
}
