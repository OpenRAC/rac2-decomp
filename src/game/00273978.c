/* Initialize the camera tracking parameters and resolve its initial target. */
#include "common.h"
extern int func_0029F840(void *, void *, int, int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_0029F6A0(void *, int, void *);
void func_00273978(char *obj, int mode, int index, void *a, void *b, unsigned char tag, float angle) {
    char *p;
    float local[4];
    *(int *)(obj+0x98) = 0;
    *(unsigned short *)(obj+0x34)|=0x100;
    p = *(char **)(obj+0x68);
    qcopy(p, a);
    qcopy(p+0x10, b);
    *(float *)(p+0x38) = 0.45f;
    *(float *)(p+0x3c) = 0.033333335f;
    *(float *)(p+0x40) = 0.5f;
    *(float *)(p+0x44) = 0.013089971616864204f;
    *(float *)(p+0x48) = angle*0.00027777778f;
    *(float *)(p+0x4c) = 0.0017453294713050127f;
    *(short *)(p+0x34) = 180;
    p[0x5e] = tag;
    p[0x5d] = mode;
    p[0x58] = 0;
    p[0x5c] = 0;
    *(int *)(p+0x30) = 0;
    switch (mode) {
        case 2:
        *(short *)(p+0x36) = index;
        *(short *)(obj+0x7c) = (1<<index)|0x8000;
        p[0x58] = func_0029F840(obj, p+0x20, *(int *)(p+0x30), index);
        FastVecSub(p+0x20, p+0x20, obj+0x10);
        func_002AFDD8(obj, p+0x20, p+0x20, 0);
        break;
        case 0: case 3:
        FastVecScale(p+0x20, obj, 0.0009765625f);
        *(float *)(p+0x2c) = *(float *)(obj+0xc)*0.0009765625f;
        FastVecSub(p+0x20, p+0x20, obj+0x10);
        func_002AFDD8(obj, p+0x20, p+0x20, 0);
        break;
        case 1:
        *(short *)(p+0x36) = index;
        *(short *)(obj+0x7c) = (mode<<index)|0x8000;
        func_0029F6A0(obj, index, local);
        FastVecSub(p+0x20, local, obj+0x10);
        func_002AFDD8(obj, p+0x20, p+0x20, 0);
        break;
    }
}
