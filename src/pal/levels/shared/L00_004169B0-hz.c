/* func_PAL_L00_004169B0, the PAL copy of func_L00_00411B30: the same C, where 0.033333335f becomes
   0.040000003f; func_L00_00412928 becomes func_PAL_L00_004177A8. */
#include "common.h"

typedef int Vector128 __attribute__((mode(TI)));

extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
typedef struct SpawnObject {
    char pad00[0x10];
    float position[4];
    char status;
    char pad21[0xf];
    unsigned char alpha;
    char pad31;
    short color;
    char pad34[0x34];
    SpawnState *state;
    char pad6c[0x54];
    float forward[4], right[4], up[4];
} SpawnObject;

#include "include_asm.h"

#ifndef RAC2_T_NODE16_F23626AD8
typedef struct Node16_F23626ad8 Node16_F23626ad8;
#endif

#ifndef RAC2_T_NODE104_F23626AD8
typedef struct Node104_F23626ad8 Node104_F23626ad8;
#endif

#ifndef RAC2_T_NODE24_F23626AD8
typedef struct Node24_F23626ad8 Node24_F23626ad8;
#endif

struct Node16_F23626ad8 {
    short h0;
    unsigned char pad2[2];
    unsigned char b4;
    unsigned char b5;
    unsigned char b6;
};

struct Node104_F23626ad8 {
    unsigned char pad0[16];
    Node16_F23626ad8 *p16;
};

struct Node24_F23626ad8 {
    unsigned char pad0[52];
    unsigned short h52;
    unsigned char pad54[50];
    Node104_F23626ad8 *p104;
};

#ifndef RAC2_T_OBJ_F23626AD8
typedef struct Obj_F23626ad8 {
    unsigned char pad0[4];
    union {
        int f4;
        struct {
            unsigned char b4;
            unsigned char b5;
            short h6;
        } b;
    } u;
    unsigned char pad8[16];
    Node24_F23626ad8 *f24;
} Obj_F23626ad8;
#endif

extern void func_002AFFD8(char *a0, void *a1, int a2);

extern void func_00282D30(void *a0, void *a1, float f12);

extern char D_L00_00256BC0[];
extern char *func_002AB1F0(char *);
extern float func_00283B98(float, float);
extern float func_00283180(float), func_00283198(float), func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00282948(void *);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_PAL_L00_004177A8(void *, int, int);
void func_PAL_L00_004169B0(char *object)
{
    Vector128 temp[1];
    char event[48];
    char *p, *q, *node, *first, *second;
    int i;
    float fraction, amount;
    for (i = 0; i < 48; i++) {
        p = D_L00_00256BC0 + i * 0xd0;
        if (*(char **)(p + 0xac) != object) continue;
        first = p + 0x20;
        qcopy(first, p + 0x40);
        if (*(char **)(p + 0xb4)) {
            node = func_002AB1F0(*(char **)(p + 0xb4));
            if (node) {
                func_002AFFD8(*(char **)(p + 0xb4) + 0x10, temp, 1);
                func_00282D30(temp, temp, *(float *)(node + 0x10));
                func_00282CC0(temp, temp, *(char **)(p + 0xb4) + 0x10);
                func_00282CC0(first, temp, first);
            } else qcopy(first, *(char **)(p + 0xb4) + 0x10);
        }
        if (*(int *)(p + 0xb8)) {
            *(float *)(p + 96) = func_00283B98(*(float *)(p + 96), *(float *)(p + 108) * 100.0f);
            *(float *)(p + 100) = func_00283B98(*(float *)(p + 100), *(float *)(p + 112) * 100.0f);
            *(float *)(p + 104) = func_00283B98(*(float *)(p + 104), *(float *)(p + 116) * 100.0f);
            *(float *)(p + 132) = func_00283B98(*(float *)(p + 132), *(float *)(p + 144) * 100.0f);
            *(float *)(p + 136) = func_00283B98(*(float *)(p + 136), *(float *)(p + 148) * 100.0f);
            *(float *)(p + 140) = func_00283B98(*(float *)(p + 140), *(float *)(p + 152) * 100.0f);
        } else {
            *(float *)(p + 96) = func_00283B98(*(float *)(p + 96), *(float *)(p + 108));
            *(float *)(p + 100) = func_00283B98(*(float *)(p + 100), *(float *)(p + 112));
            *(float *)(p + 104) = func_00283B98(*(float *)(p + 104), *(float *)(p + 116));
            *(float *)(p + 132) = func_00283B98(*(float *)(p + 132), *(float *)(p + 144));
            *(float *)(p + 136) = func_00283B98(*(float *)(p + 136), *(float *)(p + 148));
            *(float *)(p + 140) = func_00283B98(*(float *)(p + 140), *(float *)(p + 152));
        }
        *(float *)(p + 0) = func_00283180(*(float *)(p + 96)) * *(float *)(p + 120);
        *(float *)(p + 4) = func_00283198(*(float *)(p + 100)) * *(float *)(p + 124);
        *(float *)(p + 8) = -func_00283198(*(float *)(p + 104)) * *(float *)(p + 128);
        *(float *)(p + 16) = func_00283180(*(float *)(p + 132)) * *(float *)(p + 156);
        *(float *)(p + 20) = func_00283198(*(float *)(p + 136)) * *(float *)(p + 160);
        *(float *)(p + 24) = -func_00283198(*(float *)(p + 140)) * *(float *)(p + 164);
        qcopy(p + 0x30, p + 0x50);
        if (*(char **)(p + 0xb0)) {
            node = func_002AB1F0(*(char **)(p + 0xb0));
            if (node) {
                func_002AFFD8(*(char **)(p + 0xb0) + 0x10, temp, 1);
                func_00282D30(temp, temp, *(float *)(node + 0x10));
                func_00282CC0(temp, temp, *(char **)(p + 0xb0) + 0x10);
                func_00282CC0(p + 0x30, temp, p + 0x30);
            } else qcopy(p + 0x30, *(char **)(p + 0xb0) + 0x10);
        }
        first = p + 0x30;
        q = p;
        fraction = func_00283CE0(*(int *)(q + 0xb8));
        fraction /= func_00283CE0(*(int *)(q + 0xbc));
        second = q + 0x20;
        func_00282D08(first, second, first, 1.0f - fraction);
        if (!func_00282948(q + 0xb8)) continue;
        if (*(int *)(*(char **)(q + 0xb0) + 0x98) && !*(int *)(q + 0xc0) && *(int *)(q + 0xc4)) {
            func_00282CF0(temp, first, second);
            func_00282F20(temp, temp, 0.040000003f);
            amount = *(float *)(q + 0xc8);
            *(int *)(object + 0xb8) = *(int *)(*(char **)(q + 0xcc) + 0x20);
            func_002A8C00(event, object, 0x210000, temp, amount);
            event[0x18] = 5;
            event[0x19] = 3;
            *(short *)(event + 0x1a) = *(short *)(object + 0xaa);
            func_002A8E20(*(char **)(q + 0xb0), event);
            *(int *)(q + 0xc0) = 1;
            func_PAL_L00_004177A8(first, 10, 1);
        }
        if (func_00282948(q + 0xa8)) *(int *)(q + 0xac) = 0;
    }
}
