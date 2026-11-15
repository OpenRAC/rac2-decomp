#include "include_asm.h"
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; struct { float x, y, z, w; } f; } Vector;
typedef struct { Vector vertices[4]; unsigned int colors[4]; float uv[8]; long zero, texture, state, flags; } Packet;
typedef struct {
    Vector position;
    short age, active;
    float rate, angle, unused1C, widthEnd, widthStart, heightEnd, heightStart;
    float phase, step, widthModulation, heightModulation;
} Particle;
extern int D_L00_001B09F0 __attribute__((sda));
extern float D_L00_001B09E4 __attribute__((sda));
extern int D_L00_001B09E8 __attribute__((sda));
extern int D_L00_001B09EC __attribute__((sda));
extern int D_L00_001A8FF0;
extern int D_0018C0B4 NOT_SDA;
extern Vector D_L00_001B8DC0;
extern Vector D_L00_001AA310[4];
extern char *func_L00_0032A088(int, int);
extern char *func_L00_0032A0B8(int, int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);
extern float func_00283B98(float, float);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002AFFD8(char *, char *, int);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, void *, int);

void func_L00_003F6B10(char *object)
{
    Packet packet;
    Vector up, matrix[4], point, rotated;
    char *context = *(char **)(object + 0x68);
    char *base, *table;
    Particle *particle;
    float alpha, sizeX, t, width, height, pulseX, pulseY, phaseCos, phaseSin, rotationCos, rotationSin, blend;
    int alphaByte, offset, i, j;
    unsigned int color;
    float zero;

    table = func_L00_0032A088(0xC04, *(short *)(context + 0x1A));
    base = table + *(int *)(func_L00_0032A0B8(0xC04, *(short *)(context + 0x1A)) + 4);
    up.q = 0;
    up.f.z = 1.0f;
    up.f.w = 1.0f;
    alpha = IntToFloat(D_L00_001B09F0);
    if (D_0018C0B4 == 29)
        alpha *= 0.5f;
    func_00281DE8(&packet, 0x36, 0, 0x80);
    packet.uv[0] = 0.0f;
    packet.uv[1] = 0.0f;
    packet.uv[2] = 0.0f;
    packet.uv[3] = 1.0f;
    packet.uv[4] = 1.0f;
    packet.uv[5] = 0.0f;
    packet.uv[6] = 1.0f;
    packet.uv[7] = 1.0f;
    zero = packet.uv[0];
    for (i = 0; i < 120; i++) {
        particle = (Particle *)(i * 0x40 + (int)base);
        if (particle->active != 0) {
            t = (float)particle->age * particle->rate;
            alphaByte = FloatToInt(alpha * t) << 24;
            blend = func_002ABB18(t * 3.1415927f * D_L00_001B09E4);
            blend = func_00282C48(func_00283198(blend));
            color = alphaByte | FastTweenColor(D_L00_001B09EC, D_L00_001B09E8, blend);
            packet.colors[3] = color;
            packet.colors[2] = color;
            packet.colors[1] = color;
            packet.colors[0] = color;
            width = particle->widthStart + (particle->widthEnd - particle->widthStart) * t;
            height = particle->heightStart + (particle->heightEnd - particle->heightStart) * t;
            particle->phase = FastAddRotations(particle->phase, particle->step);
            phaseCos = func_00283180(particle->phase);
            pulseX = particle->widthModulation * width * phaseCos;
            phaseSin = func_00283198(particle->phase);
            pulseY = particle->heightModulation * height * phaseSin;
            matrix[3].q = particle->position.q;
            FastVecSub(&matrix[0], &D_L00_001B8DC0, &matrix[3]);
            vec_scale_to_length(&matrix[0], &matrix[0], 1.0f);
            if (D_L00_001A8FF0 != 0)
                func_002AFFD8((char *)&matrix[3], (char *)&up, 1);
            sizeX = width + pulseX;
            height = height + pulseY;
            FastVecCross(&matrix[1], &matrix[0], &up);
            vec_scale_to_length(&matrix[1], &matrix[1], 1.0f);
            FastVecCross(&matrix[2], &matrix[1], &matrix[0]);
            matrix[3].f.w = 1.0f;
            matrix[2].f.w = zero;
            matrix[1].f.w = zero;
            matrix[0].f.w = zero;
            rotationCos = func_00283180(particle->angle);
            rotationSin = func_00283198(particle->angle);
            for (j = 0; j < 4; j++) {
                point.f.y = D_L00_001AA310[j].f.y * sizeX;
                point.f.x = D_L00_001AA310[j].f.x;
                point.f.z = D_L00_001AA310[j].f.z * height;
                rotated.f.y = point.f.y * rotationCos - point.f.z * rotationSin;
                rotated.f.z = point.f.y * rotationSin + point.f.z * rotationCos;
                rotated.f.x = point.f.x;
                rotated.f.w = 1.0f;
                transform_vector(&packet.vertices[j], &rotated, matrix);
            }
            draw_world_quad(&packet, 0, 0);
        }
    }
}
