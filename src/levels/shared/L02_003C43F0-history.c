#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(void *, int, int);
extern float func_00283248(float, float);
extern float func_00282E20(char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_L00_002E6EF8(void *, void *);
extern unsigned char D_00188660[];
extern int func_001163B0(void);
extern void func_002833F0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern int func_002761F8(void *, void *, int, int, int);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002A8E20(void *, void *);
extern char *func_002AB1F0(void *);
extern void func_L00_003252A8(void *, void *, int);
extern void func_L02_004012A0(char *);
extern void func_L02_004013C0(void *);
extern void func_L02_00401480(void *);
extern char *D_L02_001C0958;

void func_L02_00400D08(unsigned char *obj)
{
    float old[4] __attribute__((aligned(16)));
    union {
        TI128 q;
        float f[4];
    } point;
    float step[4] __attribute__((aligned(16)));
    char packet[48] __attribute__((aligned(16)));
    float impact[4] __attribute__((aligned(16)));
    unsigned char *d = *(unsigned char **)(obj + 0x68);
    char *hit, *info;
    int i;

    point.q = 0;
    point.f[0] = -0.3f;
    point.f[3] = 1.0f;
    switch ((unsigned char)obj[0x20]) {
    case 0: {
        int random;
        func_002A7750(obj, 1, -1);
        random = func_001163B0();
        *(int *)(d + 0x60) = 0;
        *(int *)(d + 0x7c) = -1;
        d[0x74] = random & 1;
        *(float *)(obj + 0xf8) = func_00283248(*(float *)d, *(float *)(d + 4));
        *(float *)(obj + 0xf4) = -func_00283248(vec_length_xy(d), *(float *)(d + 8));
        euler_rotation_basis(obj + 0xc0, obj + 0xf0);
        matrix_mul_vec3(&point, &point, obj + 0xc0);
        FastVecAdd(&point, &point, obj + 0x10);
        vec_scale_to_length((char *)&step, (char *)&point, 0.01f);
        qcopy(d + 0x20, &point);
        for (i = 0; i < 3; i++) {
            FastVecAdd(d + 0x30 + i * 16, d + 0x20 + i * 16, &step);
        }
        d[0x79] = 2;
    }
    /* Fall through to the first movement update. */
    case 1: {
        unsigned char *p;
        int id;
        *(float *)(obj + 0xf8) = func_00283248(*(float *)d, *(float *)(d + 4));
        *(float *)(obj + 0xf4) = -func_00283248(vec_length_xy(d), *(float *)(d + 8));
        *(float *)(d + 0x60) -= 0.1f;
        if (*(float *)(d + 0x60) <= -8.0f) {
            *(float *)(d + 0x60) += 8.0f;
        }
        matrix_mul_vec3(&point, &point, obj + 0xc0);
        FastVecAdd(&point, &point, obj + 0x10);
        qcopy(&old, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, d);
        id = *(int *)(d + 0x7c);
        p = D_00188660 + id * 0x70;
        if (*(char **)(p + 0x88) != obj || !p[0x74]) {
            *(int *)(d + 0x7c) = PlayMobySound(0, 4, obj);
        }
        if (CollLine(&old, obj + 0x10, 0, *(int *)(obj + 0xb8), 0)) {
            hit = D_L02_001C0958;
            if (hit) {
                make_hit_descriptor(packet, obj, 0x10001, d, *(float *)(d + 0x6c));
                packet[0x18] = 5;
                packet[0x19] = 3;
                *(unsigned short *)(packet + 0x1a) = *(unsigned short *)(obj + 0xaa);
                QueueMobyImpact(hit, packet);
                PlayMobySound(1, 0, obj);
                info = func_002AB1F0(hit);
                if (info) {
                    func_L00_003252A8(hit, &step, 1);
                    FastVecScale(&impact, &step, *(float *)(info + 0x10));
                    FastVecAdd(&impact, &impact, hit + 0x10);
                }
            } else {
                PlayMobySound(1, 0, obj);
            }
            func_L02_004012A0(obj);
            obj[0x20] = 2;
            *(unsigned short *)(obj + 0x34) |= 0x41;
        }
        if (func_00282948(d + 0x70) ||
            *(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
            *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
            *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
            obj[0x20] = 2;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            qcopy(obj + 0x10, &old);
            break;
        }
        if (!d[0x7a]) {
            FastVecSub((float *)&step, (float *)(d + 0x10), (float *)d);
            if (*(float *)(d + 0x64) < FastVecLength(&step)) {
                vec_scale_to_length((char *)&step, (char *)&step, *(float *)(d + 0x64));
            } else {
                d[0x7a] = 1;
            }
            FastVecAdd(d, d, &step);
        }
        if (!(unsigned char)d[0x77]) {
            SpawnActorPuff(obj);
            d[0x77] = d[0x78];
        } else {
            d[0x77]--;
        }
        if (!(unsigned char)d[0x79]) {
            for (i = 3; i > 0; i--) {
                qcopy(d + 0x20 + i * 16, d + 0x10 + i * 16);
            }
            qcopy(d + 0x20, &point);
            d[0x79] = 2;
        } else {
            d[0x79]--;
        }
        break;
    }
    case 2: {
        unsigned char *p;
        int id;
        id = *(int *)(d + 0x7c);
        if (id != -1) {
            p = D_00188660 + id * 0x70;
            if (*(char **)(p + 0x88) == obj && p[0x74]) {
                func_002E59F8(id);
            }
        }
        *(int *)(d + 0x7c) = -1;
        func_0029F338(obj);
        return;
    }
    }
    if (obj[0x20] == 1) {
        func_L00_002E6EF8(func_L02_00401480, obj);
    }
}
