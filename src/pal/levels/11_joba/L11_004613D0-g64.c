#include "include_asm.h"

#include "common.h"
typedef int L11RenderQuad __attribute__((mode(TI)));
typedef struct {
    float vertex[4][4];
    int color[4];
    float uv[4][2];
    u64 reserved, texture, setup, state;
} L11Packet;
extern int D_L11_001B30C8[] __attribute__((sda));
extern int D_L11_001B2060 __attribute__((sda));
extern int D_L11_001B2090 __attribute__((sda));
extern int D_L11_001B2064[] __attribute__((sda));
extern int D_L11_001B2098[] __attribute__((sda));
extern float D_L11_001B2070[4][2] __attribute__((sda));
extern L11RenderQuad D_L11_001B20A0[4] __attribute__((sda));
extern L11RenderQuad D_L11_001B20E0[4] __attribute__((sda));
extern float func_00283CE0(int);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern void func_00283788(void *, void *, void *);
extern void func_L02_002EF968(void *, int, int, void *, void *, int);
extern void func_00282C88(void *);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00280B90(void *, void *, int);

/* Rotate alternating packet edges and submit the pair sixteen times. */
void func_PAL_L11_004613D0(char *p)
{
    float matrix[16], rotation[16], spin[12];
    float vector[4];
    L11Packet packets[2];
    float angles[4], temp[4], transform[12];
    char *q = *(char **)(p + 0x68);
    int i, j, k, side;

    *(L11RenderQuad *)vector = 0;
    vector[0] = 30.0f;
    vector[3] = 1.0f;
    *(L11RenderQuad *)temp = 0;
    temp[0] = func_00283CE0(D_L11_001B30C8[0] % 500) *
        (1.0f / 600.0f) * 2.0f * 3.14159274f - 3.14159274f;
    *(L11RenderQuad *)angles = *(L11RenderQuad *)temp;
    func_00283410(rotation, angles);
    func_00283410(matrix, p + 0xF0);
    qcopy(matrix + 12, p + 0x10);
    matrix[15] = 1.0f;
    func_002830C0(temp, vector, matrix);
    temp[3] = 30.0f;
    if (func_00283DB8(temp, 512.0f) != -1)
        func_00283788(matrix, matrix, rotation);
    func_L02_002EF968(&packets[0], D_L11_001B2060, D_L11_001B2090,
                      D_L11_001B2070, D_L11_001B20A0, 1);
    func_L02_002EF968(&packets[1], D_L11_001B2064[0], D_L11_001B2098[0],
                      D_L11_001B2070, D_L11_001B20E0, 1);
    for (i = 0; i < 4; i++) {
        packets[0].color[i] += *(int *)q;
        packets[1].color[i] += *(int *)q;
    }
    func_00282C88(angles);
    angles[0] = 0.52359879f;
    func_002833F0(spin, angles);
    func_00283738(transform, spin, spin);
    for (k = 0; k < 16; k++) {
        side = (k & 1) ? 2 : 0;
        for (j = 0; j < 2; j++) {
            func_00283098(packets[j].vertex[side], packets[j].vertex[side], transform);
            func_00283098(packets[j].vertex[side + 1], packets[j].vertex[side + 1], transform);
            func_00280B90(&packets[j], matrix, 1);
        }
    }
}
