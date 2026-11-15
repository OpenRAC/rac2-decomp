#include "common.h"
extern char D_00189E20[];
extern void func_0029FC20(void *, int, void *);
extern void func_00283678(void *, void *);
extern void func_002AB6D8(void *, void *);
extern void *func_L00_002A4DB0(void *, int, int, void *);
extern void func_00282AB0(void *, void *, int);
extern void func_002A0F48(void *);
extern char D_L22_001B8EC0[];

typedef struct { char pad[0x48]; char *animations[1]; } AnimationTable_b0847;

void func_L22_002AA480(void) {
    char matrix[64] __attribute__((aligned(16)));
    char *g = D_00189E20;
    char *p = *(char **)(g + 0xC18);
    p[0x6F] = 0;
    if ((*(u16 *)(*(char **)(g + 0x2290) + 0x34) ^ 1) & 1) {
        func_0029FC20(*(void **)(g + 0x2290), 5, matrix);
        qcopy(p + 0x10, matrix + 0x30);
        copy_matrix3x4(p + 0xC0, matrix);
        func_002AB6D8(matrix, p + 0xF0);
        *(u16 *)(p + 0x34) &= 0xFFBE;
        if (*(u8 *)(p + 0x43) != 0x7A) {
            char *buf = D_L22_001B8EC0;
            p[0x40] = 1;
            p[0x42] = 0x7A;
            p[0x43] = 0x7A;
            *(void **)(p + 0x58) = func_L00_002A4DB0(p, 0x7A, 1, buf);
            *(void **)(p + 0x5C) = func_L00_002A4DB0(p, *(u8 *)(p + 0x43), *(u8 *)(p + 0x41), buf + 0x600);
        } else if (*(u8 *)(p + 0x42) == *(u8 *)(p + 0x43)) {
            *(float *)(p + 0x44) += *(float *)(p + 0x48) * *(float *)(p + 0x4C);
        } else {
            *(float *)(p + 0x44) += *(float *)(p + 0x4C);
        }
        if (*(float *)(p + 0x44) >= 1.0f) {
            char *buf = D_L22_001B8EC0;
            p[0x40] = p[0x41];
            *(void **)(p + 0x58) = buf;
            func_00282AB0(buf, buf + 0x600, 0x600);
            ++*(u8 *)(p + 0x41);
            if (*(u8 *)(p + 0x41) >= *(u8 *)((*(AnimationTable_b0847 **)(p + 0x24))->animations[*(u8 *)(p + 0x43)] + 0x10))
                p[0x41] = 0;
            *(void **)(p + 0x5C) = func_L00_002A4DB0(p, *(u8 *)(p + 0x43), *(u8 *)(p + 0x41), buf + 0x600);
            *(float *)(p + 0x44) = (*(float *)(p + 0x44) - 1.0f) / *(float *)(p + 0x4C);
            *(float *)(p + 0x4C) = **(float **)(p + 0x58);
            *(float *)(p + 0x44) *= *(float *)(p + 0x4C);
        }
        func_002A0F48(p);
    } else {
        *(u16 *)(p + 0x34) |= 0x41;
    }
}
