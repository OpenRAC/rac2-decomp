/* Collect transformed group points and blended colors for the shared draw emitter.
 * The local snapshots remain complete 16-byte vectors in the stack workspace.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* Partial global view with the complete vector consumed by the math helper. */
typedef struct {
    char reserved_000[0x140];
    float x_140;
    float y_144;
    float z_148;
    float w_14C;
} Aimvec_F0b10;

extern Aimvec_F0b10 D_L00_001B8C80;

extern int func_00283DB8(char *local, float value);
extern void func_00283098(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282CF0(char *off, char *v, char *pos);
extern void func_00282F20(char *dst, char *src, float angle);
extern float func_00282DB0(char *, char *);
extern int func_L00_0031C998(int, int, float);
extern void func_L00_003F34D8(char *, int *, char *, int *, int *);
extern void func_L00_00325CC0(int, void *, void *, float, float);

extern unsigned short **D_L00_001A9014 __attribute__((sda));
extern unsigned char *D_L00_001B2514 __attribute__((sda));
extern unsigned char *D_L00_001B251C __attribute__((sda));

void func_L00_003F3518(char *obj)
{
    unsigned char *st = *(unsigned char **)(obj + 0x68);
    char buf0[0x460] __attribute__((aligned(16)));
    char buf1[0x120] __attribute__((aligned(16)));
    char pos[16] __attribute__((aligned(16)));
    char b[16] __attribute__((aligned(16)));
    char d[16] __attribute__((aligned(16)));
    char c[16] __attribute__((aligned(16)));
    char f[16] __attribute__((aligned(16)));
    char e4[16] __attribute__((aligned(16)));
    int idx;
    int count;
    int color;
    unsigned short *q;
    unsigned char *e;
    float dot;

    idx = *(int *)st;
    count = 0;
    q = D_L00_001A9014[idx];
    for (; q != 0 && ((short)q[-1] >= 0 || q == D_L00_001A9014[*(int *)st]) &&
           (e = D_L00_001B251C + ((*q & 0x7FFF) << 6)) != 0;
         q++) {
        qcopy(pos, D_L00_001B2514 + ((*q & 0x7FFF) << 5));
        *(float *)(pos + 12) += *(float *)(st + 0x4C);
        if (func_00283DB8(pos, *(float *)(st + 0x60)) < 0)
            continue;
        qcopy(b, e + 0x30);
        *(TI128 *)c = 0;
        *(float *)(c + 0) = *(float *)(st + 0x50);
        *(float *)(c + 4) = *(float *)(st + 0x54);
        *(float *)(c + 8) = *(float *)(st + 0x58);
        *(TI128 *)d = *(TI128 *)c;
        matrix_mul_vec3(d, d, (char *)e);
        FastVecAdd(b, b, d);
        if (*(int *)(st + 0x6C) != 0) {
            func_L00_003F34D8(b, (int *)(st + 0x30), buf0, (int *)buf1, &count);
            continue;
        }
        FastVecSub(c, (char *)&D_L00_001B8C80.x_140, b);
        vec_scale_to_length(c, c, 1.0f);
        *(TI128 *)e4 = 0;
        *(float *)(e4 + 0) = *(float *)(st + 0x40);
        *(float *)(e4 + 4) = *(float *)(st + 0x44);
        *(float *)(e4 + 8) = *(float *)(st + 0x48);
        *(TI128 *)f = *(TI128 *)e4;
        matrix_mul_vec3(f, f, (char *)e);
        vec_scale_to_length(f, f, 1.0f);
        dot = FastVecDot(c, f);
        if (*(float *)(st + 0x3C) < dot) {
            dot = dot * 0.5f + 0.5f;
            if (*(int *)(st + 0x38) != 0)
                dot = dot * dot;
            color = func_L00_0031C998(*(int *)(st + 0x34), *(int *)(st + 0x30), dot);
            func_L00_003F34D8(b, &color, buf0, (int *)buf1, &count);
        }
    }
    DrawOffsetBillboardBatch(count, buf0, buf1, *(float *)(st + 0x4C), *(float *)(st + 0x5C));
}
