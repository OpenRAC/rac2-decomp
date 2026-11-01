#include "common.h"

extern int func_00282978(void *);
extern void func_002B9180(void *);
extern void func_0029FC20(void *, int, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern char D_001B5340[];

/* Particle update for a particle attached to an owner moby: kills it when its timer ends or the
   owner is gone, places it on an owner joint (bone matrix) or at an offset from the owner, can
   fade it by the facing angle, then moves it towards the point at D_001B5340. */
void func_002C6B68(char *p)
{
    union {
        struct { float matrix[16]; float transformed[4]; } m;
        float v[3][4];
    } w __attribute__((aligned(16)));
    char *q = p + 0x20;
    char *owner;
    char *pos;
    char *ownerpos;
    float dot;

    if (*(short *)(p + 0xA) >= 0 && func_00282978(p + 0xA)) {
        func_002B9180(p);
        return;
    }
    owner = *(char **)q;
    if (owner) {
        if (*(signed char *)(owner + 0x20) < 0) {
            func_002B9180(p);
            return;
        }
        ownerpos = owner + 0x10;
        if (*(int *)(q + 4) >= 0) {
            char *initial = p + 0x10;
            func_0029FC20(owner, *(int *)(q + 4), w.m.matrix);
            w.m.matrix[15] = 0;
            func_002830C0(w.m.transformed, q + 0x10, w.m.matrix);
            func_00282CC0(initial, &w.m.matrix[12], w.m.transformed);
            pos = initial;
            goto drift;
        } else {
            char *initial = p + 0x10;
            qcopy(initial, ownerpos);
            func_00283098(w.v[0], q + 0x10, owner + 0xC0);
            func_00282CC0(initial, initial, w.v[0]);
            pos = initial;
        }
        if (*(short *)(q + 0xE)) {
            func_00282CF0(w.v[1], pos, D_001B5340);
            p[8] = func_00283CF0(func_00282DB0(w.v[1], D_001B5340 + 0x230) * 6.0f);
        }
        if (*(short *)(q + 0xC)) {
            func_00282CF0(w.v[2], pos, ownerpos);
            func_00282F20(w.v[1], w.v[1], 1.0f);
            func_00282F20(w.v[2], w.v[2], 1.0f);
            dot = -func_00282DB0(w.v[1], w.v[2]);
            if (dot < 0.0f)
                *(unsigned int *)(p + 4) &= 0x05FFFFFF;
            else
                *(unsigned int *)(p + 4) = (*(unsigned int *)(p + 4) & 0xFFFFFF) |
                    (func_00283CF0(func_00283CE0(*(unsigned char *)(p + 7)) * dot) << 24);
        }
    } else {
        char *initial = p + 0x10;
        qcopy(initial, q + 0x10);
        pos = initial;
    }
drift:
    func_00282CF0(w.v[0], D_001B5340, pos);
    func_00282F20(w.v[0], w.v[0], *(float *)(q + 8));
    func_00282CC0(pos, pos, w.v[0]);
}
