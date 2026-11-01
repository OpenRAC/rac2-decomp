#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern unsigned char *D_L22_001AF314[] __attribute__((sda));
extern unsigned char *D_L22_001C00D8 NOT_SDA;
extern unsigned char D_00189F00[], D_L22_001B9C80[];
extern int D_L22_001AF304[] __attribute__((sda));
extern float D_L22_001AF308 __attribute__((sda));
extern float D_L22_001B2AA0;
extern float D_L22_001B2AA4;
extern float D_L22_001B11A0 __attribute__((sda));
extern float D_L22_001B11A4 __attribute__((sda));
extern float D_L22_001B11A8 __attribute__((sda));
extern float D_L22_001B11AC __attribute__((sda));
extern float D_L22_001B11B0 __attribute__((sda));
extern float D_L22_001B11B4 __attribute__((sda));
extern float D_L22_001B11BC __attribute__((sda));
extern float D_L22_001B11C0 __attribute__((sda));
extern float D_L22_001B11C4 __attribute__((sda));
extern void func_L22_0040D638(void *), func_L22_0040DA80(void *), func_L22_0040DD20(void *);
extern float func_00282E48(void *, void *), func_L02_00329C48(void *, void *, int), func_002B0360(void *);
extern void func_002A7750(void *, int, int), func_002A7470(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *), func_00283098(void *, void *, void *);
extern int func_L22_003A2780(void *, void *, void *), func_002B3890(void *), func_002B1C20(void *, void *);
extern void func_L22_003A2988(void *, float);
extern int func_00277258(void *, int, void *, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_0029F338(void *);
extern int func_002A77E0(int), func_002A7820(int, int);
extern void func_L22_0040DB20(void *, void *, float), func_L22_0040DC40(void *, void *, int, float);
extern void func_L02_00332630(void *, void *);
extern int func_L00_0035F5A0(int, int, int);
extern int func_L22_003A6620(void);
extern void func_L22_003A3C70(void *, int), func_002A7A00(void *, float, float);
extern float func_00282C48(float);
extern unsigned char *func_00273730(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_00310C88(void);
extern void func_00282F20(void *, void *, float), func_00282D30(void *, void *, float);
extern void func_L22_003A2B90(void *, void *, void *, int);
extern int func_US2_002AF9C8(void *, float);
extern float func_002A7878(float, float);
extern void func_002A7988(void *, float, float);
typedef struct { unsigned char pad[0x80]; Vec position; unsigned char gap[0x2200]; unsigned char *moby; } HeroView;
extern HeroView D_00189E20;

void func_US2_L22_0040DD88(unsigned char *obj) {
    Vec delta, temp, push, old, posx, negx, posy, negy, offset, scatter;
    unsigned char *ctx = *(unsigned char **)(obj + 0x68);
    unsigned char *hit, *part;
    int collision, facing, visible, flags, i, choice;
    float distance;
    func_L22_0040D638(obj);
    if (!D_L22_001AF314[0]) return;
    collision = 0; facing = 0; distance = 0.0f; visible = 0;
    if (obj[0x20] != 6 && obj[0x95] != 5) {
        if (func_00282E48(D_L22_001AF314[0] + 0x10, obj + 0x10) < D_L22_001B11A0) {
            collision = 1;
            func_002A7750(obj, 5, 3);
        }
        func_00282CF0(&delta, (&D_00189E20.position), obj + 0x10);
        if (func_L02_00329C48(obj, &delta, 0) <= 0.785398185f) facing = 1;
        if (func_L22_003A2780(D_L22_001AF314[0], (&D_00189E20.position), obj + 0x10)) visible = 1;
        distance = func_00282E48((&D_00189E20.position), obj + 0x10);
        if (func_002B0360(obj + 0x10) - D_L22_001B2AA4 > 9.19999981f) {
            qcopy(&temp, obj + 0x10);
            func_L22_003A2988(&temp, 2.0f);
            if (func_00277258(&temp, 0, obj, 5.0f) && (hit = D_L22_001C00D8) && *(short *)(hit + 0xAA) == 0xDCE) {
                func_0032C700(hit + 0x10, 0, 0x19, 0x14, 0x14, 0xA, 0xF, 1, 1, 0, 0, 0, 1.5f, 20.0f);
                func_0029F338(hit);
            }
        }
    }
    switch (obj[0x95]) {
        case 0:
            if (func_002B3890(obj) && obj[0x43] != 1) func_002A7470(obj, 1, 0, 20);
            if (D_L22_001AF304[0]) break;
            if (visible && distance < 40.0f) {
                func_002A7750(obj, 3, 1);
                if (*(int *)(ctx + 0x258) < 300) *(int *)(ctx + 0x258) = func_002A7820(480, 600);
            } else if (obj[0x31] && distance < 80.0f) {
                func_L22_0040DC40(obj, ctx + 0x2A0, 1, D_L22_001B11AC);
            } else func_L22_0040DD20(obj);
            break;
        case 1:
            if (func_002B3890(obj) && obj[0x43] != 1) func_002A7470(obj, 1, 0, 20);
            if (!*(int *)(ctx + 0x258)) {
                func_002A7750(obj, 2, 0);
            } else if (visible && facing && distance < 30.0f) {
                func_002A7750(obj, 4, 2);
                func_L22_0040DD20(obj);
            } else func_L22_0040DC40(obj, (&D_00189E20.position), 1, D_L22_001B11B4);
            break;
        case 2:
            if (facing || func_002B3890(obj)) {
                if (obj[0x43] != 3) func_002A7470(obj, 3, 0, 10);
                *(float *)(obj + 0x48) = D_L22_001B2AA0;
            } else if ((obj[0x60] & 2) && obj[0x43] == 3) func_002A7470(obj, 1, 0, 10);
            if (!visible || distance > 50.0f) {
                func_002A7750(obj, 2, 0);
                *(int *)(ctx + 0x258) = 0;
            } else if (distance > 20.0f) func_L22_0040DC40(obj, (&D_00189E20.position), 1, D_L22_001B11B4);
            else func_L02_00332630(obj, (&D_00189E20.position));
            break;
        case 3:
            flags = func_002B1C20(obj, ctx + 0x140);
            if ((flags & 1) || collision) {
                Vec *saved_position;
                func_L00_0035F5A0(17, 0, 0);
                if (*(void **)(ctx + 0x38) == D_00189E20.moby && func_L22_003A6620()) func_L22_003A3C70((&D_00189E20.position), 0);
                for (i = 0; i < 5; i++) {
                    func_002A7A00(&delta, D_L22_001B11BC * 0.0166666675f, D_L22_001B11C0 * 0.0166666675f);
                    delta.f[2] = func_00282C48(delta.f[2]) * D_L22_001B11C4;
                    func_00283098(&delta, &delta, obj + 0xC0);
                    part = func_00273730(obj, 1, *(short *)(obj + 0xAA), i, obj + 0x10, obj + 0xF0, &delta, 255, 30.0f, 15.0f);
                    *(void **)(part + 0x64) = func_00310C88;
                }
                func_00282CF0(&temp, D_L22_001B9C80, &delta);
                func_00282F20(&temp, &temp, 1.0f);
                func_0032C700(obj + 0x10, 0, 25, 20, 20, 10, 15, 1, 1, 0, 0, 0, 1.5f, 20.0f);
                *(short *)(ctx + 0x178) = 0;
                *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
                *(float *)(ctx + 0x20) = *(short *)(ctx + 0x24);
                saved_position = &old;
                /* This fresh scratch vector is consumed through calls; no C field
                 * access depends on moving across its copy. */
                qcopy_nc(saved_position, (&D_00189E20.position));
                func_L22_003A2988(saved_position, 0.0f);
                func_00282D30(&push, D_00189E20.moby + 0xE0, -80.0f);
                switch (func_002A77E0(7)) {
                case 0: func_00282D30(&offset, D_00189E20.moby + 0xC0, -50.0f); break;
                case 1: func_00282D30(&offset, D_00189E20.moby + 0xD0, 50.0f); break;
                case 2: func_00282D30(&offset, D_00189E20.moby + 0xD0, -50.0f); break;
                case 3:
                    func_00282D30(&posy, D_00189E20.moby + 0xD0, 50.0f);
                    func_00282D30(&posx, D_00189E20.moby + 0xC0, 50.0f);
                    func_00282CC0(&offset, &posy, &posx); func_00282D30(&offset, &offset, 0.5f); break;
                case 4:
                    func_00282D30(&posx, D_00189E20.moby + 0xC0, 50.0f);
                    func_00282D30(&negy, D_00189E20.moby + 0xD0, -50.0f);
                    func_00282CC0(&offset, &posx, &negy); func_00282D30(&offset, &offset, 0.5f); break;
                case 5:
                    func_00282D30(&negy, D_00189E20.moby + 0xD0, -50.0f);
                    func_00282D30(&negx, D_00189E20.moby + 0xC0, -50.0f);
                    func_00282CC0(&offset, &negy, &negx); func_00282D30(&offset, &offset, 0.5f); break;
                case 6:
                    func_00282D30(&negx, D_00189E20.moby + 0xC0, -50.0f);
                    func_00282D30(&posy, D_00189E20.moby + 0xD0, 50.0f);
                    func_00282CC0(&offset, &negx, &posy); func_00282D30(&offset, &offset, 0.5f); break;
                }
                func_00282CC0(&push, &push, &offset);
                func_00282CC0(&push, &push, saved_position);
                func_L22_003A2B90(D_L22_001AF314[0], obj + 0x10, &push, 1);
                func_L22_003A2988(obj + 0x10, 7.19999981f);
                if (func_00277258(obj + 0x10, 1, 0, 3.0f) && *(short *)(D_L22_001C00D8 + 0xAA) == 0xEDD && D_L22_001C00D8[0x20] != 6) {
                    func_00282D30(&scatter, obj + 0xC0 + func_002A77E0(2) * 16,
                                  2.0f * (func_002A77E0(2) ? D_L22_001AF308 : -D_L22_001AF308));
                    func_00282CC0(obj + 0x10, obj + 0x10, &scatter);
                    func_L22_003A2988(obj + 0x10, 7.19999981f);
                }
                qcopy(ctx + 0x2A0, obj + 0x10);
                func_002A7750(obj, 2, 0);
            } else if (flags & 2) {
                func_002A7750(obj, 3, 1);
                *(int *)(ctx + 0x258) = func_002A7820(580, 600);
            }
            break;
        case 4: case 5: break;
        }
    switch (obj[0x20]) {
    case 2: case 3: case 5: case 6: break;
    case 4:
        if (func_US2_002AF9C8(obj, 1.5f)) func_L22_0040DB20(obj, D_00189F00, 0.0f);
        break;
    case 9:
        qcopy(&delta, obj + 0x10);
        func_L22_003A2988(&delta, 7.19999981f);
        if (*(unsigned short *)(obj + 0x96) >= 61 && !(*(unsigned short *)(obj + 0x96) & 63)) func_L22_0040DB20(obj, ctx + 0x2A0, 50.0f);
        if (func_00282E48(obj + 0x10, &delta) < 0.1f) {
            func_002A7750(obj, 2, 0);
            *(int *)(ctx + 0x88) &= ~0x10;
        } else func_L22_0040DC40(obj, &delta, 0, D_L22_001B11B0);
        break;
    case 7:
        if ((*(unsigned short *)(obj + 0x96) & 7) == 7) {
            qcopy(&delta, *(void **)(ctx + 0x2B0));
            func_00282F20(&delta, &delta, *(float *)(ctx + 0x2B4));
            func_00282CC0(&delta, (&D_00189E20.position), &delta);
            func_L22_003A2988(&delta, 7.19999981f);
            qcopy(ctx + 0x2A0, &delta);
        }
        if (*(unsigned short *)(obj + 0x96) >= 61 && !(*(unsigned short *)(obj + 0x96) & 511)) func_L22_0040DB20(obj, ctx + 0x2A0, 50.0f);
        if (func_00282E48(obj + 0x10, ctx + 0x2A0) < 2.0f || func_00282E48(obj + 0x10, (&D_00189E20.position)) < 20.0f) {
            func_002A7750(obj, 9, 5);
            *(int *)(ctx + 0x280) = 0;
        } else func_L22_0040DC40(obj, ctx + 0x2A0, 0, D_L22_001B11B4);
        break;
    case 8: {
        float min, max;
        *(float *)(ctx + 0x2B4) = func_002A7878(0.0f, 15.0f) + 10.0f;
        choice = func_002A77E0(4);
        switch (choice) {
        case 0: qcopy(&temp, D_00189E20.moby + 0xD0); func_00282D30(&temp, &temp, -1.0f); break;
        case 1: qcopy(&temp, D_00189E20.moby + 0xD0); break;
        case 2: qcopy(&temp, D_00189E20.moby + 0xC0); func_00282D30(&temp, &temp, -1.0f); break;
        case 3: qcopy(&temp, D_00189E20.moby + 0xC0); break;
        }
        min = D_L22_001B11A4; max = D_L22_001B11A8;
        *(void **)(ctx + 0x2B0) = D_00189E20.moby + 0xC0;
        func_00282D30(&delta, &temp, func_002A7878(min, max));
        func_00282CC0(&delta, &delta, (&D_00189E20.position));
        func_002A7988(&push, 0.1f, D_L22_001B11A4 * 0.333333343f);
        func_00282CC0(&delta, &delta, &push);
        qcopy(obj + 0x10, &delta);
        qcopy(&old, *(void **)(ctx + 0x2B0));
        func_00282F20(&old, &old, *(float *)(ctx + 0x2B4));
        func_00282CC0(&old, (&D_00189E20.position), &old);
        func_L22_003A2988(&old, 7.19999981f);
        qcopy(ctx + 0x2A0, &old);
        func_002A7750(obj, 7, 5);
        *(int *)(ctx + 0x28C) = 0;
        *(int *)(ctx + 0x88) |= 0x10;
        break;
    }
    }
    func_L22_0040DA80(obj);
}
