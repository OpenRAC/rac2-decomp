#include "common.h"

extern char D_00189E20[], D_L22_001C00E0[];
extern float D_L22_001AF380;
extern float D_L22_001AF308;
extern float D_L22_001AF308_gp SDATA(D_L22_001AF308);
extern float D_L22_001B0D44 __attribute__((sda));
extern float D_L22_001B0D48 __attribute__((sda));
extern float D_L22_001B0D58 __attribute__((sda));
extern int D_L22_001B0D54 __attribute__((sda));
extern char *ref_L22_003FD2D8_00 __attribute__((sda));
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_00325600(void *, void *, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283360(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L22_003A2988(void *, float);
extern void func_0029F338(void *);
extern void func_L00_0035F5A0(int, int, int);
extern int func_002B3868(void *);
extern int func_002A77E0(int);
extern int func_002761F8(void *, void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_L22_003FD958(void *, void *, int, int);

void func_L22_003FD2D8(char *o) {
    float rot[4] __attribute__((aligned(16)));
    /* The matrix and scale workspace is reused for the late collision vectors. */
    union {
        struct { float matrix[12], a[4], b[4], scale[12]; } early;
        struct { float trace[4], random[4], a[4], b[4]; } late;
    } scratch __attribute__((aligned(16)));

    char *ctl = *(char **)(o + 0x68);
    float step;
    unsigned int count;
    if (func_002B3868(o) && *(u8 *)(o + 0x20) == 16)
        func_L00_0035F5A0(18, 0, 0);
    if (*(u8 *)(o + 0x31)) {
        float d = fast_vec_dist(D_00189E20 + 0x80, o + 0x10);
        float threshold = D_L22_001AF380;
        *(float *)(ctl + 0x44) = d;
        if (d >= threshold)
            *(u8 *)(o + 0x23) = 127;
    }
    else *(float *)(ctl + 0x44) = 2000.0f;
    if (*(u8 *)(o + 0x20) == 0) {
        qzero(rot);
        rot[2] = 0.018907736986875534f;
        euler_rotation_basis(scratch.early.matrix, rot);
        multiply_matrix3x3(o + 0xc0, o + 0xc0, scratch.early.matrix);
        func_002AFFD8(o + 0x10, ctl + 0x10, 0);
        func_L00_00325600(o + 0xc0, ctl + 0x10, 0);
    }
    else {
        qzero(rot);
        rot[2] = ((45.0f - (float)*(u16 *)(o + 0x96)) * 22.0f + 155.0f)
                 * 0.0002908882452175021f;
        euler_rotation_basis(scratch.early.matrix, rot);
        if (func_002B3868(o)) *(u8 *)(o + 0x23) = 127;
        if (*(u8 *)(o + 0x23) >= 3) --*(u8 *)(o + 0x23);
        if (*(u8 *)(o + 0x23) >= 11 && *(u8 *)(o + 0x20) == 16) {
            switch (*(u16 *)(o + 0x96) & 3) {
            case 0:
                FastVecScale(scratch.early.a, o + 0xc0, -D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xd0, -D_L22_001B0D48);
                break;
            case 1:
                FastVecScale(scratch.early.a, o + 0xc0, D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xd0, D_L22_001B0D48);
                break;
            case 2:
                FastVecScale(scratch.early.a, o + 0xd0, D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xc0, D_L22_001B0D48);
                break;
            case 3:
                FastVecScale(scratch.early.a, o + 0xd0, -D_L22_001B0D58);
                FastVecAdd(scratch.early.a, scratch.early.a, o + 0x10);
                FastVecScale(scratch.early.b, o + 0xc0, -D_L22_001B0D48);
                break;
            }
            func_L22_003FD958(scratch.early.a, scratch.early.b, D_L22_001B0D54, 0);
        }
        step = 0.02222222276031971f;
        set_identity_rotation_rows(scratch.early.scale);
        scratch.early.scale[0] = scratch.early.scale[5] = scratch.early.scale[10] =
            (45.0f - (float)*(u16 *)(o + 0x96) * step) * (D_L22_001B0D44 * step);
        multiply_matrix3x3(scratch.early.matrix, scratch.early.scale, scratch.early.matrix);
        multiply_matrix3x3(o + 0xc0, o + 0xc0, scratch.early.matrix);
        if (*(u16 *)(o + 0x96) >= 46) {
            func_0029F338(o);
            return;
        }
        if (*(u8 *)(o + 0x20) == 16) {
            qcopy(o + 0x10, D_00189E20 + 0x80);
            func_002AFFD8(o + 0x10, ctl + 0x10, 0);
            func_L00_00325600(o + 0xc0, ctl + 0x10, 0);
            vec_scale_to_length(scratch.early.a, ctl + 0x10, -((float)*(u16 *)(o + 0x96) * step) * 7.5f);
            FastVecAdd(o + 0x10, o + 0x10, scratch.early.a);
        }
        else {
            qcopy(o + 0x10, ref_L22_003FD2D8_00 + 0x10);
            func_002AFFD8(o + 0x10, ctl + 0x10, 0);
            func_L00_00325600(o + 0xc0, ctl + 0x10, 0);
            vec_scale_to_length(scratch.early.a, ctl + 0x10, -((float)*(u16 *)(o + 0x96) * step) * 7.5f);
            FastVecAdd(o + 0x10, o + 0x10, scratch.early.a);
        }
    }
    count = *(u16 *)(o + 0x96);
    if (count <= 65534) *(u16 *)(o + 0x96) = count + 1;
    else *(u16 *)(o + 0x96) = 0;
    if (*(short *)(ctl + 0x2a) != 0 && (*(u16 *)(o + 0x96) & 31) == 0) {
        FastVecScale(rot, ctl + 0x10, 6.0f);
        FastVecScale(scratch.late.trace, ctl + 0x10, -3.0f);
        FastVecAdd(rot, rot, o + 0x10);
        FastVecAdd(scratch.late.trace, scratch.late.trace, o + 0x10);
        if (CollLine(scratch.late.trace, rot, 18, 0, 0)) return;
        func_L22_003A2988(o + 0x10, 0.0f);
        {
            float *random = scratch.late.random;
            char *dir = o + 0xc0 + func_002A77E0(2) * 16;
            float f;
            if (func_002A77E0(2)) f = D_L22_001AF308_gp;
            else f = -D_L22_001AF308;
            FastVecScale(random, dir, f);
            FastVecAdd(o + 0x10, o + 0x10, scratch.late.random);
        }
        func_L22_003A2988(o + 0x10, 0.0f);
        FastVecScale(scratch.late.a, ctl + 0x10, 3.0f);
        FastVecScale(scratch.late.b, ctl + 0x10, -3.0f);
        FastVecAdd(scratch.late.a, scratch.late.a, o + 0x10);
        FastVecAdd(scratch.late.b, scratch.late.b, o + 0x10);
        if (CollLine(scratch.late.b, scratch.late.a, 18, 0, 0))
            qcopy(o + 0x10, D_L22_001C00E0);
        *(short *)(ctl + 0x2a) = 0;
    }
}
