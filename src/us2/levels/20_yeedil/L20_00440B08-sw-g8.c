#include "include_asm.h"

#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union {
    Q q;
    float f[4];
} Vector;
extern int D_L20_001A8F00, D_L20_001B2AC8;
extern int D_L20_001BDCF0[];
typedef struct {
    char pad[0x80];
    float pos[4];
} Hero;
extern Hero D_00189E20;
extern char D_00189EA0[];
extern float D_L20_001B1FE0 __attribute__((sda));
extern float D_L20_001B1FE4 __attribute__((sda));
extern float D_L20_001B1FE8 __attribute__((sda));
extern float D_L20_001B1FF0 __attribute__((sda));
extern float D_L20_001B1FF8 __attribute__((sda));
extern float D_L20_001B1FFC __attribute__((sda));
extern float D_L20_001B2000 __attribute__((sda));
extern float D_L20_001B2004 __attribute__((sda));
extern float D_L20_001B1FF4;
extern Vector D_L20_001B2010 SDATA(D_L20_001B2010);
extern void func_US2_L20_00441208(char *), func_0029F338(char *);
extern int func_002B3890(char *), func_002A77E0(int), func_002B1C20(char *, void *);
extern void func_US2_002A7AA8(char *, int, int), func_L01_003E9CF8(char *, int, void (*)(char *));
extern void func_L20_00440460(char *), func_002A7750(char *, int, int);
extern int func_002B3868(char *);
extern void func_002A7470(char *, int, int, int);
extern float func_00282E80(void *, void *);
extern void func_002B4FF0(char *, void *, float);
extern int func_L20_0043FFF0(char *);
extern float func_0029F530(char *);
extern void func_L01_00321178(char *, void *);
extern float func_00283248(float, float);
extern void func_L01_00322288(char *, float);
extern int func_US2_002AF9C8(char *, float);
extern void func_00283098(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_002A8C28(void *, void *, int, int, float, float, float, int, int);
extern void func_00273B70(char *), func_002833F0(void *, void *);
extern float func_00282E20(void *);
extern void func_002AA2E8(void *, float, float), func_00282F70(void *, void *, float);
extern float func_002A89A8(void *, int, float);
extern void func_L20_00440150(char *);

void func_US2_L20_00440B08(char *obj) {
    Vector v;
    Q matrix[3];
    float length;
    char *st = *(char **)(obj + 0x68);
    int hit;

    func_US2_L20_00441208(obj);
    if (D_L20_001A8F00 == 2) {
        if (D_L20_001BDCF0[0] >= 5) func_0029F338(obj);
        return;
    }
    switch (*(u8 *)(obj + 0x95)) {
    case 0:
        break;
    case 1:
        if (func_002B3890(obj)) *(int *)(st + 0x284) = func_002A77E0(2);
        break;
    case 2:
        hit = func_002B1C20(obj, st + 0x140);
        if (hit & 1) {
            *(int *)(st + 0x280) = 0;
            func_US2_002A7AA8(obj, 0, 3);
            func_L01_003E9CF8(obj, 0, func_L20_00440460);
        } else if (hit & 2) func_002A7750(obj, 3, 1);
        break;
    }
    switch (*(u8 *)(obj + 0x20)) {
    case 2: {
        float distance;
        if (func_002B3868(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) func_002A7470(obj, 2, 0, 20);
            *(float *)(st + 0x78) = D_L20_001B1FE0 * 0.0166666675f;
            *(float *)(st + 0x288) = 1.0471977f;
        }
        distance = func_00282E80(obj + 0x10, D_00189EA0);
        if (distance < D_L20_001B1FF0) *(float *)(st + 0x288) = 2.0943954f;
        else if (D_L20_001B1FF4 < distance) *(float *)(st + 0x288) = 1.0471977f;
        if (*(int *)(st + 0xD0) == 60) {
            *(int *)(st + 0xD0) = 0;
            *(int *)(st + 0x284) = (*(int *)(st + 0x284) + 1) & 1;
        }
        func_002B4FF0(obj, D_00189EA0, *(int *)(st + 0x284) ? *(float *)(st + 0x288) : - *(float *)(st + 0x288));
        if ((D_L20_001B2AC8 & 15) == (((int)obj >> 8) & 15) && func_L20_0043FFF0(obj)) {
            *(int *)(st + 0x280) = 1;
            func_002A7750(obj, 3, -1);
        }
        break;
    }
    case 3:
        if (func_002B3868(obj)) {
            if (*(u8 *)(obj + 0x43) != 2) func_002A7470(obj, 2, 0, 10);
            *(float *)(st + 0x78) = D_L20_001B1FE4 * 0.0166666675f;
        }
        func_002B4FF0(obj, D_00189EA0, 0.0f);
        if (*(float *)(st + 0x11C) < D_L20_001B1FF8) func_002A7750(obj, 4, -1);
        break;
    case 4: {
        float distance;
        if (func_002B3868(obj)) {
            if (*(u8 *)(obj + 0x43) != 4) func_002A7470(obj, 4, (int)D_L20_001B1FFC, 10);
        }
        distance = func_0029F530(obj);
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && distance >= 9.0f && distance <= 17.0f) {
            float accel = D_L20_001B2004 * 0.00027777778f;
            float speed = D_L20_001B2000 * 0.0166666675f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            func_L01_00321178(obj, D_00189EA0);
        } else {
            func_L01_00322288(obj, func_00283248(
                D_00189E20.pos[0] - *(float *)(obj + 0x10),
                D_00189E20.pos[1] - *(float *)(obj + 0x14)));
        }
        {
            float accel = D_L20_001B1FE8 * 0.00027777778f;
            float speed = D_L20_001B1FE4 * 0.0166666675f;
            *(float *)(st + 0x74) = accel;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
        }
        if (*(u8 *)(obj + 0x42) == *(u8 *)(obj + 0x43) && func_US2_002AF9C8(obj, 14.0f)) {
            func_00283098(&v, &D_L20_001B2010, obj + 0xC0);
            func_00282CC0(&v, &v, obj + 0x10);
            func_002A8C28(obj, &v, 0x04000001, 0, 0.333f, 2.0f, 1.0f, 1, 0);
        }
        if ((*(u8 *)(obj + 0x60) & 2) && func_00282E80(obj + 0x10, D_00189EA0) > D_L20_001B1FF8) func_002A7750(obj, 3, -1);
        break;
    }
    case 7:
        *(char **)(obj + 0x68) = st + 0x210;
        func_00273B70(obj);
        *(char **)(obj + 0x68) = st;
        func_002A8C28(obj, obj + 0x10, 0x04000000, 0, 0.5f, 5.0f, 1.0f, 1, 0);
        qzero_nc(&v);
        v.f[2] = *(float *)(st + 0x288) * 0.0166666675f;
        func_002833F0(matrix, &v);
        func_00283098(st + 0x210, st + 0x210, matrix);
        length = func_00282E20(st + 0x210);
        if (length < 0.0500000045f) {
            func_002AA2E8(&length, 0.0f, 0.0027777778f);
            if (length <= 0.0f) func_002A7750(obj, 1, 1);
            else func_00282F70(st + 0x210, st + 0x210, length);
        }
        if (*(float *)(obj + 0x18) < *(float *)(st + 0x180)) {
            *(int *)(obj + 0x98) = 0;
            *(u16 *)(obj + 0x34) = (*(u16 *)(obj + 0x34) | 0x41) & 0xEFFF;
            func_002A7750(obj, 6, -1);
        }
        break;
    case 1:
        if (func_002B3868(obj)) {
            char *data = *(char **)(obj + 0x24);
            int flags = *(int *)(data + 0x10);
            *(int *)(obj + 0x9C) = 2;
            *(int *)(obj + 0x98) = flags;
            *(u16 *)(obj + 0x34) = *(u16 *)(data + 0x44) | 0x1000;
            func_00283098(&v, st + 0x230, obj + 0xC0);
            func_00282CC0(obj + 0x10, &v, obj + 0x10);
            *(float *)(obj + 0x18) = func_002A89A8(obj + 0x10, 0, 0.5f);
            qzero(obj + 0xF0);
            *(float *)(obj + 0xF8) = func_00283248(
                D_00189E20.pos[0] - *(float *)(obj + 0x10),
                D_00189E20.pos[1] - *(float *)(obj + 0x14));
            if (*(u8 *)(obj + 0x43) != 3) func_002A7470(obj, 3, 0, 5);
        }
        if (*(u8 *)(obj + 0x60) & 2) func_002A7750(obj, 2, 1);
        break;
    case 5:
    case 6:
        break;
    }
    func_L20_00440150(obj);
}
