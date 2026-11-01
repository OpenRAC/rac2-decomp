#include "include_asm.h"

#include "common.h"
extern int D_001A79F0[] __attribute__((sda));
typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap38[0x44-0x38];
    short count;
    char gap46[0x50-0x46];
    char *output;
    char gap54[0x18C-0x54];
    char *parts[4];
} Hero;
extern Hero D_L26_001BC880;
extern char D_L26_0027E310[];
extern float D_L26_001A93E0[4][4] __attribute__((sda));
extern void func_00283AF0(void *, void *);
extern void func_00283958(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_PAL_L26_002FE4A8(void) {
    float matrix[12];
    float rotation[12];
    char *child;
    int index;

    float *out;
    float *vertex;
    float scale;
    int count;
    if (D_001A79F0[0] != 26) return;
    child = 0;
    index = -1;
    switch (D_L26_001BC880.mode) {
    case 0:
        child = D_L26_001BC880.parts[2];
        index = 1;
        break;
    case 1:
        index = 1;
        child = D_L26_001BC880.parts[2];
        break;
    }
    if (index != -1 && child != 0 && D_L26_001BC880.parts[index] != 0) {
        D_L26_001BC880.output = D_L26_0027E310;
        out = (float *)(D_L26_0027E310 + 0x20);
        vertex = D_L26_001A93E0[0];
        func_00283AF0(*(char **)(child + 0x58) + 0x10, rotation);
        func_00283958(rotation, matrix);
        scale = *(float *)(child + 0x2C) / *(float *)(*(char **)(child + 0x24) + 0x24);
        count = 3;
        do {
            func_00283098(out, vertex, matrix);
            vertex += 4;
            func_00282D30(out, out, scale);
            func_00282CC0(out, out, child + 0x10);
            out += 4;
        } while (--count >= 0);
        *(char **)(D_L26_001BC880.output + 0x68) = D_L26_001BC880.parts[index];
    }
    if (D_L26_001BC880.timer >= 0x4A9) D_L26_001BC880.output = 0;
}
