/* func_L22_003A4CA8 (576 bytes, levels 22 and 23): the dobbo-orbit twin of
 * func_L23_003C16D8, without the leading child-transform call and keyed on the
 * controller's mode byte (1..3). Same unit flags and the same qzero_nc spelling as
 * the twin: retail rebuilds the stack addresses after each quadword clear.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L22_001AF34C __attribute__((sda));
extern char D_00189EA0[];

extern void func_0029FC20(void *, int, void *);
extern void func_00283098(void *, void *, void *);
extern float func_002B04E0(void *, void *, int);
extern float func_002AAA00(void *, float, float, float, float, void *, int);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void func_00282D30(void *, void *, float);
extern void func_002B0408(void *, void *, void *);
extern int func_00282978(short *);
extern void func_00282CF0(void *, void *, void *);

void func_L22_003A4CA8(char *obj) {
    TI128 v0[1], v1[3], t[1], u[1], r3[3], r4[1];
    float fz0, fz1;
    char *state = *(char **)(obj + 0x68);
    float r;
    float a1;
    float b1;
    float c1;

    if ((unsigned)(*(unsigned char *)(*(char **)(state + 0x440) + 0x43) - 1) < 3) {
        if (*(short *)(state + 0x460) == 0)
            *(int *)(state + 0x458) = 0;
        FastVecSub(v0, D_00189EA0, *(char **)(state + 0x440) + 0x10);
        r = func_002B04E0(*(char **)(state + 0x440), v0, 0);
        b1 = *(float *)(state + 0x128) + *(float *)(state + 0x128);
        a1 = *(float *)(state + 0x124);
        c1 = *(float *)(state + 0x12C);
        fz0 = 0;
        func_002AAA00(&fz0, r, a1, b1, c1, state + 0x458, 0);
        qzero_nc(t);
        ((float *)t)[2] = *(float *)(state + 0x458);
        euler_rotation_basis(v1, t);
        multiply_matrix3x3(*(char **)(state + 0x440) + 0xC0, *(char **)(state + 0x440) + 0xC0, v1);
        func_002A05A8(*(char **)(state + 0x440));
        *(unsigned short *)(*(char **)(state + 0x440) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(state + 0x440));
        FastVecScale(u, state + 0x200, -1.0f);
        func_002B0408(*(char **)(state + 0x440) + 0xC0, u, 0);
        *(short *)(state + 0x460) = D_L22_001AF34C;
        return;
    }
    {
        short v = *(short *)(state + 0x460);

        if (v != 0) {
            if (v == D_L22_001AF34C)
                *(int *)(state + 0x458) = 0;
            *v0 = 0;
            ((float *)v0)[0] = 1.0f;
            ((float *)v0)[3] = 1.0f;
            func_0029FC20(obj, 1, v1);
            qzero_nc(t);
            matrix_mul_vec3(v0, v0, v1);
            r = func_002B04E0(*(char **)(state + 0x440), v0, 0);
            a1 = *(float *)(state + 0x124) + *(float *)(state + 0x124);
            c1 = *(float *)(state + 0x12C);
            b1 = *(float *)(state + 0x128) * 4.0f;
            fz1 = 0;
            func_002AAA00(&fz1, r, a1, b1, c1, state + 0x458, 0);
            qzero_nc(u);
            ((float *)u)[2] = *(float *)(state + 0x458);
            euler_rotation_basis(r3, u);
            multiply_matrix3x3(*(char **)(state + 0x440) + 0xC0, *(char **)(state + 0x440) + 0xC0, r3);
            func_002A05A8(*(char **)(state + 0x440));
            *(unsigned short *)(*(char **)(state + 0x440) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(state + 0x440));
            FastVecScale(r4, state + 0x200, -1.0f);
            func_002B0408(*(char **)(state + 0x440) + 0xC0, r4, 0);
            FastDecTimer((short *)(state + 0x460));
        }
    }
}
