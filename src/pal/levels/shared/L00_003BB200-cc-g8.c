/* func_PAL_L00_003BB200, the PAL copy of func_L00_003B7680: the same C, where expr 0.016666668f becomes 0.020000001f; scale func_002A7820(D_L00_001AFB0C[1], D_L00_001AFB0C[2]). */
#include "common.h"

typedef struct OBJ2 {
    char pad0[0x28];
    int f28;
    char pad1[0x68 - 0x2C];
    struct OBJ2 *f68;
} OBJ2;

extern OBJ2 *D_L00_001AFBC0 __attribute__((sda));

typedef struct OBJ3 {
    char pad0[0x98];
    int f98;
} OBJ3;

extern OBJ3 *D_L00_0023DBA0[];

extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void *func_002C3150(void *, void *, int, int, float, int, int);
extern int D_L00_001AFB68 __attribute__((sda));
extern float D_L00_001AFAE8 __attribute__((sda));
extern float D_L00_001AFAEC;
extern int D_L00_001AFB0C[] __attribute__((sda));
extern float D_L00_001AFAFC;
extern int D_L00_001AFB70[2] __attribute__((sda));

void func_PAL_L00_003BB200(char *object, float *position)
{
    float point[4], velocity[4];
    int i;
    for (i = 0; i < D_L00_001AFB68; i++) {
        unsigned char kind, random;
        int *color;
        func_002A7A00(point, 0.0f, 0.333f);
        func_00282CC0(point, point, position);
        func_002A7A00(velocity, D_L00_001AFAE8 * (0.020000001f), D_L00_001AFAEC * (0.020000001f));
        kind = (((int)(func_002A7820(D_L00_001AFB0C[1], D_L00_001AFB0C[2])) * 5 + 2) / 6);
        color = &D_L00_001AFB70[(unsigned char)object[0xbc]];
        random = func_002A77E0(255);
        func_002C3150(point, velocity, *color, kind, D_L00_001AFAFC, random, 0);
    }
}

