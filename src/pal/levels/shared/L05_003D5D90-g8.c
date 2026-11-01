#include "include_asm.h"

#include "common.h"
typedef struct { float v[4][4]; int color[4]; float uv[4][2]; unsigned long gs[4]; } QuadD2618;
typedef struct { int index; float scale; int mode; } StateD2618;
extern unsigned long func_0027C878(int);
extern void func_002FC560(u32, u64);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern int func_00282948(int *);
extern void func_00283410(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00280B90(void *, void *, int);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00282C48(float);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_0029F338(void *);
extern int D_L05_001AFCAC __attribute__((sda));
extern int D_L05_001AFCA0 __attribute__((sda));
extern int D_L05_001AFCA4 __attribute__((sda));
extern int D_L05_001AFC98 __attribute__((sda));
extern int D_L05_001AFC9C __attribute__((sda));
extern float D_L05_001AFCB4 __attribute__((sda));
extern float D_L05_001AFCB8 __attribute__((sda));
extern int D_L05_001AFCB0 __attribute__((sda));
extern struct { char pad[0x140]; float pos[4]; } D_L05_001B9580;
extern int D_L05_0024CFD0[][4], D_L05_0024CF30[][4], D_L05_0024CF80[][4];
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) VectorD2618;
extern VectorD2618 D_L05_0024D020[][4];
extern float D_L05_0024A460[][4][137];
extern float D_L05_0023F920[][4][137][4];
extern float D_L05_002ADDF0[][4];
extern short D_L05_002ACD30[][4][3];
extern float D_L05_002AC4A0[][4];
extern float D_L05_002AD930[][2];
extern float D_L05_001B2F58[] MACRO_ADDR;
extern float D_L05_001B2F88[] MACRO_ADDR;
extern float D_L05_001B2FB8[] MACRO_ADDR;
extern float D_L05_001B2FD0[] MACRO_ADDR;
extern int D_L05_001B2F70[] MACRO_ADDR;
extern int D_L05_001B2FA0[] MACRO_ADDR;
extern int D_L05_001B2FE8[] MACRO_ADDR;
extern char *D_L05_001B3018[] MACRO_ADDR;
/* Selects the quad's texture and resets its GS tags. */
static inline void InitQuadD2618(QuadD2618 *q, int texture)
{
    q->gs[1] = func_0027C878(texture);
    q->gs[2] = 0xFF9000000260UL;
    q->gs[0] = 0;
}
/* One axis of the object's rotation. */
static inline float RotationAxisD2618(char *object, int axis)
{
    return ((float *)(object + 0xF0))[axis];
}
/* One axis of the object's position, which follows four words after the object's start. */
static inline float PositionAxisD2618(char *object, int axis)
{
    return ((float *)object)[4 + axis];
}
/* Turns rotation to face the camera from the object's position. */
static inline void FaceCameraD2618(float *rotation, char *object)
{
    float x, y;
    x = D_L05_001B9580.pos[0] - *(float *)(object + 0x10);
    y = D_L05_001B9580.pos[1] - PositionAxisD2618(object, 1);
    rotation[0] = RotationAxisD2618(object, 0);
    rotation[1] = RotationAxisD2618(object, 1);
    rotation[2] = RotationAxisD2618(object, 2);
    rotation[3] = 0;
    rotation[2] = func_00283248(x, y);
    x = func_00282E80(object + 0x10, D_L05_001B9580.pos);
    rotation[1] = -func_00283248(x, D_L05_001B9580.pos[2] - PositionAxisD2618(object, 2));
}

/* Faces the camera, then draws four layers of a 128-quad mesh, a growing flash quad and, in mode 0,
   two spinning glow quads. Once func_00282948 reports on D_L05_001B2FE8 and the alpha at
   D_L05_001B2FA0 falls below zero, calls func_0029F338 and returns; otherwise calls func_002FC560. */
void func_PAL_L05_003D6360(char *object)
{
    QuadD2618 q;
    float matrix[16];
    float rotation[4];
    float temporary[4];
    float scratch[4];
    StateD2618 *state = *(StateD2618 **)(object + 0x68);
    int vertex;
    int corner;
    int inactive;
    InitQuadD2618(&q, D_L05_001AFCAC);
    func_002FC560(0x47, 0x53001);
    FaceCameraD2618(rotation, object);
    {
        /* Declared after the setup: its pseudo number orders the spill slots of gcse's temporaries. */
        int group;
        for (group = 0; group < 4; group++) {
            inactive = 0;
            if (func_00282948(&D_L05_0024CFD0[state->index][group]) ||
                !D_L05_0024CFD0[state->index][group]) {
                inactive = 1;
                D_L05_0024CFD0[state->index][group] = 0;
            }
            func_00283410(matrix, rotation);
            matrix[12 + 0] = D_L05_0024D020[state->index][group].x;
            matrix[12 + 1] = D_L05_0024D020[state->index][group].y;
            matrix[12 + 2] = D_L05_0024D020[state->index][group].z;
            matrix[12 + 3] = 1.0f;
            q.color[0] = q.color[1] = q.color[2] = q.color[3] = D_L05_001AFCB0;
            {
                unsigned long blend = (unsigned long)D_L05_001AFC98;
                blend |= (unsigned long)D_L05_001AFC9C << 2;
                blend |= (unsigned long)D_L05_001AFCA0 << 4;
                blend |= (unsigned long)D_L05_001AFCA4 << 6;
                blend |= ((unsigned long)D_L05_0024CF30[state->index][group] << 32);
                q.gs[3] = blend;
            }
            if (inactive == 1) {
                D_L05_0024CF30[state->index][group] -= D_L05_0024CF80[state->index][group];
                if (D_L05_0024CF30[state->index][group] < 0)
                    D_L05_0024CF30[state->index][group] = 0;
            }
            if (inactive == 0) {
                for (vertex = 0; vertex < 137; vertex++) {
                    if (vertex % 5 == 0 && vertex > 5) {
                        func_00282D30(temporary, D_L05_002ADDF0[vertex], D_L05_0024A460[state->index][group][vertex]);
                        func_00282CD8(scratch, D_L05_0023F920[state->index][group][vertex], temporary);
                    }
                }
            } else {
                for (vertex = 0; vertex < 137; vertex++) {
                    if (vertex % 5 == 0 && vertex > 5) {
                        func_00282D30(temporary, D_L05_002ADDF0[vertex], D_L05_0024A460[state->index][group][vertex] * 0.25f);
                        func_00282CD8(scratch, D_L05_0023F920[state->index][group][vertex], temporary);
                    }
                }
            }
            for (vertex = 0; vertex < 128; vertex++) {
                for (corner = 0; corner < 4; corner++) {
                    int vi = D_L05_002ACD30[vertex][corner][0];
                    int ti = D_L05_002ACD30[vertex][corner][1];
                    func_00282CC0(temporary, D_L05_002AC4A0[vi], D_L05_0023F920[state->index][group][vi]);
                    func_00282D30(q.v[corner], temporary, D_L05_001AFCB4 * state->scale);
                    q.uv[corner][0] = D_L05_002AD930[ti][0];
                    q.uv[corner][1] = D_L05_002AD930[ti][1];
                    D_L05_002AD930[ti][0] += 0.0001f;
                    if (D_L05_002AD930[ti][0] > 8.0f)
                        D_L05_002AD930[ti][0] -= 8.0f;
                }
                if (func_00282E48(object + 0x10, D_L05_001B9580.pos) > 10.0f)
                    func_00280B90(&q, matrix, 0);
            }
        }
    }
    InitQuadD2618(&q, 0x43);
    {
        unsigned long blend = (unsigned long)D_L05_001AFC98;
        blend |= (unsigned long)D_L05_001AFC9C << 2;
        blend |= (unsigned long)D_L05_001AFCA0 << 4;
        blend |= (unsigned long)D_L05_001AFCA4 << 6;
        blend |= ((unsigned long)D_L05_001B2F70[state->index] << 32);
        q.gs[3] = blend;
    }
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = 0x7F204080;
    q.uv[0][0] = 0; q.uv[0][1] = 0; q.uv[1][0] = 1; q.uv[1][1] = 0;
    q.uv[2][0] = 0; q.uv[2][1] = 1; q.uv[3][0] = 1; q.uv[3][1] = 1;
    q.v[0][2] = -2; q.v[1][2] = 2; q.v[2][2] = -2; q.v[3][2] = 2;
    q.v[0][1] = -2; q.v[1][1] = -2; q.v[2][1] = 2; q.v[3][1] = 2;
    q.v[0][0] = 0; q.v[1][0] = 0; q.v[2][0] = 0; q.v[3][0] = 0;
    func_00283410(matrix, rotation);
    func_00282D30(q.v[0], q.v[0], D_L05_001B2F58[state->index] * state->scale);
    func_00282D30(q.v[1], q.v[1], D_L05_001B2F58[state->index] * state->scale);
    func_00282D30(q.v[2], q.v[2], D_L05_001B2F58[state->index] * state->scale);
    func_00282D30(q.v[3], q.v[3], D_L05_001B2F58[state->index] * state->scale);
    matrix[12 + 0] = *(float *)(object + 0x10);
    matrix[12 + 1] = *(float *)(object + 0x14);
    matrix[12 + 2] = *(float *)(object + 0x18);
    matrix[12 + 3] = 1;
    func_00280B90(&q, matrix, 0);
    D_L05_001B2F58[state->index] += 0.4f;
    D_L05_001B2F70[state->index] -= 5;
    if (D_L05_001B2F70[state->index] < 0) D_L05_001B2F70[state->index] = 0;
    if (state->mode == 0) {
        float *angle_a, *size, *angle_b;
        int color = 0x7F8080FF;
        q.gs[1] = func_0027C878(0x44);
        angle_a = D_L05_001B2FB8;
        size = D_L05_001B2F88;
        angle_b = D_L05_001B2FD0;
        q.color[0] = q.color[1] = q.color[2] = q.color[3] = color;
        {
            unsigned long blend = (unsigned long)D_L05_001AFC98;
            blend |= (unsigned long)D_L05_001AFC9C << 2;
            blend |= (unsigned long)D_L05_001AFCA0 << 4;
            blend |= (unsigned long)D_L05_001AFCA4 << 6;
            blend |= ((unsigned long)D_L05_001B2FA0[state->index] << 32);
            q.gs[3] = blend;
        }
        q.uv[0][0] = 0; q.uv[0][1] = 0; q.uv[1][0] = 1; q.uv[1][1] = 0;
        q.uv[2][0] = 0; q.uv[2][1] = 1; q.uv[3][0] = 1; q.uv[3][1] = 1;
        q.v[0][2] = -2; q.v[1][2] = 2; q.v[2][2] = -2; q.v[3][2] = 2;
        q.v[0][1] = -2; q.v[1][1] = -2; q.v[2][1] = 2; q.v[3][1] = 2;
        q.v[0][0] = 0; q.v[1][0] = 0; q.v[2][0] = 0; q.v[3][0] = 0;
        rotation[0] = angle_a[state->index];
        func_00283410(matrix, rotation);
        func_00282D30(q.v[0], q.v[0], size[state->index] * state->scale);
        func_00282D30(q.v[1], q.v[1], size[state->index] * state->scale);
        func_00282D30(q.v[2], q.v[2], size[state->index] * state->scale);
        func_00282D30(q.v[3], q.v[3], size[state->index] * state->scale);
        matrix[12 + 2] = func_00283198(-rotation[1]);
        matrix[12 + 0] = func_00283180(-rotation[2]) * (1.0f - func_00282C48(matrix[12 + 2]));
        matrix[12 + 1] = -func_00283198(-rotation[2]) * (1.0f - func_00282C48(matrix[12 + 2]));
        matrix[12 + 2] *= state->scale;
        matrix[12 + 0] *= state->scale;
        matrix[12 + 1] *= state->scale;
        matrix[12 + 2] += *(float *)(object + 0x18);
        matrix[12 + 0] += *(float *)(object + 0x10);
        matrix[12 + 1] += *(float *)(object + 0x14);
        matrix[12 + 3] = 1;
        func_00280B90(&q, matrix, 0);
        q.color[0] = q.color[1] = q.color[2] = q.color[3] = color;
        q.uv[0][0] = 0; q.uv[0][1] = 0; q.uv[1][0] = 1; q.uv[1][1] = 0;
        q.uv[2][0] = 0; q.uv[2][1] = 1; q.uv[3][0] = 1; q.uv[3][1] = 1;
        q.v[0][2] = -2; q.v[1][2] = 2; q.v[2][2] = -2; q.v[3][2] = 2;
        q.v[0][1] = -2; q.v[1][1] = -2; q.v[2][1] = 2; q.v[3][1] = 2;
        q.v[0][0] = 0; q.v[1][0] = 0; q.v[2][0] = 0; q.v[3][0] = 0;
        rotation[0] = angle_b[state->index];
        func_00283410(matrix, rotation);
        func_00282D30(q.v[0], q.v[0], size[state->index] * state->scale);
        func_00282D30(q.v[1], q.v[1], size[state->index] * state->scale);
        func_00282D30(q.v[2], q.v[2], size[state->index] * state->scale);
        func_00282D30(q.v[3], q.v[3], size[state->index] * state->scale);
        matrix[12 + 2] = func_00283198(-rotation[1]);
        matrix[12 + 0] = func_00283180(-rotation[2]) * (1.0f - func_00282C48(matrix[12 + 2]));
        matrix[12 + 1] = -func_00283198(-rotation[2]) * (1.0f - func_00282C48(matrix[12 + 2]));
        matrix[12 + 2] *= state->scale * 2;
        matrix[12 + 0] *= state->scale * 2;
        matrix[12 + 1] *= state->scale * 2;
        matrix[12 + 2] += *(float *)(object + 0x18);
        matrix[12 + 0] += *(float *)(object + 0x10);
        matrix[12 + 1] += *(float *)(object + 0x14);
        matrix[12 + 3] = 1;
        func_00280B90(&q, matrix, 0);
        angle_a[state->index] = func_00283B98(angle_a[state->index], 0.055850547f);
        angle_b[state->index] = func_00283BE0(angle_b[state->index], 0.055850547f);
        size[state->index] += 0.02f;
    }
    if (func_00282948(D_L05_001B2FE8 + state->index)) {
        D_L05_001B2FA0[state->index] -= 2;
        if (D_L05_001B2FA0[state->index] < 0) {
            D_L05_001B2FA0[state->index] = 0;
            D_L05_001B3018[state->index] = 0;
            D_L05_001AFCB8 -= 1.0f;
            func_0029F338(object);
            return;
        }
    }
    func_002FC560(0x47, 0x5360B);
}
