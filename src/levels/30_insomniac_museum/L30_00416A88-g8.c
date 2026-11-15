#include "common.h"
extern float D_L30_001B1F04 __attribute__((sda));
extern char *D_L30_001C0218 NOT_SDA;
extern int func_002A8C28(void *, float, void *, float, int, float, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(void *, void *, int, float, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00277258(void *, int, void *, float);
extern void func_00282D30(void *, void *, float);
extern int func_00277F48(void *, float, int, void *, void *);
extern void func_00282C88(void *);
extern void func_L16_00406080(void *, int, int, int, int, int, int, int, int, float, int);
extern void func_0029F338(void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_L08_002F2D10(void *, void *);
extern void func_L30_00416FB0(void);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
void func_L30_00416A88(char *obj) {
    float pos[4];
    struct Packet { Vec v; void *owner; int mode; unsigned char kind, active; unsigned short id; float distance; int enabled; } packet;
    Vec velocity;
    struct Packet query;
    char *st = *(char **)(obj + 0x68);
    if (!*(unsigned char *)(obj + 0xBC)) {
        if (++*(int *)(st + 0x24) > 240) {
            if (!*(unsigned char *)(obj + 0xBC)) {
                func_002A8C28(obj, 0.6f, obj + 0x10, *(float *)(st + 0x14), 0x10003, 0.0f, 0, 1, 0);
                func_002A7750(obj, 1, -1);
            }
        }
        switch (*(unsigned char *)(obj + 0x20)) {
        case 0: {
            FastVecAdd(pos, obj + 0x10, st);
            make_hit_descriptor(&packet, obj, 3, *(float *)(st + 0x14), st);
            packet.id = *(unsigned short *)(obj + 0xAA);
            if (CollLine(obj + 0x10, pos, 0, obj, &packet) || func_00277258(obj + 0x10, 0, obj, 0.3f)) {
                /* Two full copies of the response: cross-jumping merges their tails after reload,
                   and each copy's velocity pointer stays local to its block, in $s0. */
                if (D_L30_001C0218) {
                    if (D_L30_001C0218 == *(char **)(st + 0x10)) goto move; /* An owner hit continues normal movement. */
                    qcopy(&velocity, st);
                    FastVecScale(&velocity, &velocity, 1.5f);
                    velocity.f[2] = 1.0f;
                    velocity.f[3] = 5627.9248046875f;
                    make_hit_descriptor(&query, obj, 0x10003, *(float *)(st + 0x14), &velocity);
                    query.active = 1;
                    query.id = *(unsigned short *)(obj + 0xAA);
                    query.kind = 0;
                    func_00277F48(obj + 0x10, 0.6f, 0, obj, &query);
                    if (!*(unsigned char *)(obj + 0xBC)) func_002A7750(obj, 1, -1);
                    return;
                }
                qcopy(&velocity, st);
                FastVecScale(&velocity, &velocity, 3.0f);
                velocity.f[2] = 1.0f;
                velocity.f[3] = 5627.9248046875f;
                make_hit_descriptor(&query, obj, 0x10003, *(float *)(st + 0x14), &velocity);
                query.active = 1;
                query.id = *(unsigned short *)(obj + 0xAA);
                query.kind = 0;
                func_00277F48(obj + 0x10, 0.6f, 0, obj, &query);
                if (!*(unsigned char *)(obj + 0xBC)) func_002A7750(obj, 1, -1);
                return;
            }
move:
            if (!*(unsigned char *)(obj + 0xBC)) qcopy(obj + 0x10, pos);
            FastVecScale(&velocity, st, -0.5f);
            func_00282C88(&query);
            break;
        }
        case 1:
            func_L16_00406080(obj + 0x10, 0, 25, 20, 20, 20, 0, 0, 1, 0.25f, 0);
            func_0029F338(obj);
            return;
        }
    }
    func_002ACEC0(obj + 0xE0, obj + 0xE0, obj + 0xD0, D_L30_001B1F04 * 0.01745329424738884f);
    func_002ACEC0(obj + 0xC0, obj + 0xC0, obj + 0xD0, D_L30_001B1F04 * 0.01745329424738884f);
    func_L08_002F2D10(func_L30_00416FB0, obj);
}
