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
extern float D_L00_001B8DC0[];
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern float D_L00_001A8F20[] MACRO_ADDR;
extern short D_L00_001AF6D8[][4][2] SDATA(D_L00_001AF6D8);
extern short D_L00_001AF6DA[][4][2] MACRO_ADDR;
extern float D_L00_00294A80[][4];
extern float D_L00_00294B10[][2];
extern char *func_L00_0032A088(int, int);
extern void func_00281DE8(void *, int, int, int);
extern int func_00283CF0(float);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern float func_00283180(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00280B90(void *, void *, int);

/* Builds and submits the two quads for each active effect record. */
void func_L00_003A8940(char *object)
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
    base = func_L00_0032A088(1483, *(short *)(*(char **)(object + 104) + 26));
    func_00281DE8(&first, 54, 0, 128);
    func_00281DE8(&second, 54, 1, 128);
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
                color = (unsigned int)func_00283CF0(scale) << 24;
                angle = age * 3.1415927f * D_L00_001AF750;
                wave = func_00283198(func_002ABB18(angle));
                blend = func_00282C48(wave);
                color |= func_00283D38(D_L00_001AF74C, D_L00_001AF748, blend);
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
                func_00282CF0(forward, D_L00_001B8DC0, position);
                func_00282F20(forward, forward, 1.0f);
                if (D_L00_001A8FF0[0])
                    func_002AFFD8(position, normal, 1);
                func_00282DD8(right, forward, normal);
                func_00282F20(right, right, 1.0f);
                func_00282DD8(up, right, forward);
                forward[3] = right[3] = up[3] = 0.0f;
                position[3] = 1.0f;
                sine = func_00283180(*(float *)(record + 20));
                cosine = func_00283198(*(float *)(record + 20));
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
                                func_00282F20(scaled, D_L00_00294A80[index], *weight);
                            else
                                qcopy(scaled, D_L00_001A8F20);
                            func_00282CC0(local, D_L00_00294A80[index], scaled);
                            rotated[0] = local[0];
                            rotated[3] = 1.0f;
                            rotated[1] = local[1] * sine - local[2] * cosine;
                            rotated[2] = local[1] * cosine + local[2] * sine;
                            func_00282D30(first.vertex[corner], rotated, radius);
                            first.uv[corner][0] = D_L00_00294B10[texture][0];
                            first.uv[corner][1] = D_L00_00294B10[texture][1];
                            width = (1.0f - age) * 0.075f;
                            func_00282D30(scaled, right, width);
                            func_00282CC0(second.vertex[corner], first.vertex[corner], scaled);
                            func_00282D30(scaled, up, width);
                            func_00282CC0(second.vertex[corner], first.vertex[corner], scaled);
                            second.uv[corner][0] = D_L00_00294B10[texture][0];
                            second.uv[corner][1] = D_L00_00294B10[texture][1];
                        }
                        func_00280B90(&first, forward, 0);
                        func_00280B90(&second, forward, 0);
                    }
                }
            }
        }
    }
}
