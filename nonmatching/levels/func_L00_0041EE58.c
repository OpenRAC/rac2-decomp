/* Closer B, 2026-11-01: fresh draft from retail, replaces the screened stub. Profile -O2 -G8 -ffunction-sections -g.
 * 1804/1812 bytes, 40 aligned lines, register choice only. Left: 1) retail keeps the first frame address in a
 * call-clobbered temp (addiu v0, sp, 0x20; a0 = v0; s6 = v0 in the delay slot) and every later use is s6; ours
 * uses one pseudo across the calls (108 in the gcse dump). Its twin func_L00_003E2510 has the same shape.
 * 2) the 0xFF divisor is s1 and the angle s0, swapped here, with mfhi v1; daddu s0, v1 where ours is mfhi s1.
 * Settled, keep: no pointer local for moby + 0x10 (gcse's reaching copy gives s0/s4), Hit struct at
 * D_L00_001BF200 (a0 - 0x20 is cse's related value), a switch for the state, D_L00_001A8F20 sda, the separate
 * first-target tests (0xFE alone, then 0xFD), D_L00_001B19C8 MACRO_ADDR. A wide inline around the first three
 * calls reaches 1812 bytes but moves other registers.
 */
#include "common.h"
typedef struct {
    char pad0[0x70];
    float rate;
    char pad74[224 - 0x74];
} ShotKind;
typedef struct {
    unsigned int slot;
    int pad04[3];
    int frame;
    int ownerIndex;
    int ownerKind;
    char *target;
    float velocity[3];
    float speed;
    int pad30;
    int handle;
    int count;
    float step;
    float fade;
} ShotState;
typedef struct {
    float dir[4];
    char *self;
    int flags;
    char a, b;
    u16 kind;
    float rate;
    int one;
    int pad[3];
} Query;
extern int func_002761F8(void *, void *, int, int, void *);
extern int func_00282948(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_0029F338(void *);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_002AB1F0(char *);
extern void func_002AFFD8(void *, void *, int);
extern int func_002B4038(int, int);
extern char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002FEE50(int);
extern void func_002FEE70(int, void *, int);
extern void func_00300190(void *, void *);
extern void func_00334160(void *, int, int);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L00_0041F570(void *);
extern void func_L00_0041FC20(void *, int, int);
extern void func_L00_004200F0(void *);
extern int func_L00_00420310(void *);
extern u8 D_00139570[];
extern int D_0018C0B0[];
extern char D_L00_001A8F20[] __attribute__((sda));
extern int D_L00_001B19C8 MACRO_ADDR;
typedef struct { char pad[0x18]; char *who; char pad1C[4]; float pos[4]; } Hit;
extern Hit D_L00_001BF200;
extern u8 *D_L00_001FE9F4[];
extern u8 *D_L00_001FEA14[];
extern ShotKind D_L00_00262570[];
void func_L00_0041EE58(char *moby)
{
    float start[4], normal[4], a[4], b[4];
    Query query;
    float jit[4];
    ShotState *s = *(ShotState **)(moby + 0x68);
    char *part;
    int alpha, a2, shade, i;
    float d, sp, size;
    if (func_002B4038(s->ownerKind, s->ownerIndex) == 0) {
        func_0029F338(moby);
        func_002FEE50(s->handle);
        return;
    }
    func_00300190(moby + 0x10, moby + 0x10);
    qcopy(start, moby + 0x10);
    func_002AFFD8(moby + 0x10, normal, 1);
    if (s->target) {
        int k = ((u8 *)s->target)[0x20];
        if (k == 0xFE)
            s->target = 0;
        else if (k != 0xFD && func_L00_00420310(s->target) == 0) {
            char *c;
            func_00282CF0(a, s->target + 0x10, moby + 0x10);
            c = func_002AB1F0(s->target);
            if (c) {
                func_00282D30(b, s->target + 0xE0, *(float *)(c + 0x10));
                func_00282CC0(a, a, b);
            }
            d = func_00282DF0(a);
            if (d != 0.0f) {
                sp = s->speed;
                func_00282D30(s->velocity, a, sp / d);
                s->speed = sp;
            } else
                s->target = 0;
        } else
            s->target = 0;
    }
    switch (((u8 *)moby)[0x20]) {
    case 0:
        func_002FEE70(s->handle, s->velocity, 0);
        func_00282CC0(moby + 0x10, moby + 0x10, s->velocity);
        query.self = moby;
        query.flags = 0x10000;
        query.one = 1;
        query.rate = (D_L00_00262570 + D_00139570[0x16])->rate;
        qcopy(&query, s->velocity);
        func_00282F20(&query, &query, 1.0f);
        query.dir[3] = 5627.925f;
        query.kind = *(u16 *)(moby + 0xAA);
        query.a = 1;
        query.b = 1;
        if (func_002761F8(start, moby + 0x10, 0, D_0018C0B0[0], &query) != 0) {
            qcopy(moby + 0x10, D_L00_001BF200.pos);
            if (D_L00_001BF200.who == 0)
                func_L00_0041FC20(D_L00_001BF200.pos, 0xF, 0);
            else if (*(int *)(D_L00_001BF200.who + 0x98)) {
                func_L00_0041FC20(D_L00_001BF200.pos, 0xA, 1);
                func_00334160(D_L00_001BF200.who, 0x3C, *(int *)(moby + 0xB8));
            }
            func_002E5CF8(0, 0, moby);
            moby[0x20] = 1;
            s->target = 0;
            *(u16 *)(moby + 0x34) |= 0x41;
            s->count = 6;
        } else if (func_00282948(&s->count)) {
            func_L00_004200F0(moby + 0x10);
            moby[0x20] = 1;
            s->target = 0;
            *(u16 *)(moby + 0x34) |= 0x41;
            s->count = 6;
        }
        alpha = func_002A77E0(0xFF);
        part = func_002C65A0(moby + 0x10, D_L00_001A8F20, 2, 0x205080, alpha, 0x40, 0x10, 420000.0f, 420000.0f, 0.0f, 1);
        if (part)
            part[2] = *D_L00_001FEA14[0];
        a2 = (alpha + 0x80) % 0xFF;
        part = func_002C65A0(moby + 0x10, D_L00_001A8F20, 2, 0x205080, a2, 0x40, 0x10, 420000.0f, 420000.0f, 0.0f, 1);
        if (part)
            part[2] = *D_L00_001FEA14[0];
        part = func_002C65A0(moby + 0x10, D_L00_001A8F20, 2, 0xFFFFFF, (a2 + 0x40) % 0xFF, 0x30, 0x10, 252000.02f, 252000.02f, 0.0f, 1);
        if (part)
            part[2] = *D_L00_001FEA14[0];
        func_00282CF0(a, moby + 0x10, start);
        func_00282D30(a, a, 0.4f);
        qcopy(b, start);
        for (i = 0; i < 5; i++) {
            shade = func_002A77E0(0xFF);
            size = func_002A7878(0.2f, 0.6f);
            jit[0] = b[0] + func_002A78D8(0.0f, 0.1f);
            jit[1] = b[1] + func_002A78D8(0.0f, 0.1f);
            jit[2] = b[2] + func_002A78D8(0.0f, 0.1f);
            func_002C65A0(jit, D_L00_001A8F20, 0xF, 0x808080, shade, 0x20, 0, size * 210000.0f, size * 42000.0f, 0.0f, 1);
            func_00282CC0(b, b, a);
        }
        if (D_L00_001B19C8 % 10 == 0) {
            part = func_002C65A0(moby + 0x10, D_L00_001A8F20, 0x1E, 0x202080, 0, 0x20, 0, 2100.0f, 420000.0f, 0.0f, 1);
            if (part)
                part[2] = *D_L00_001FE9F4[0];
        }
        func_L00_002E6EF8(func_L00_0041F570, moby);
        break;
    case 1:
        if (func_00282948(&s->count)) {
            func_002FEE50(s->handle);
            func_0029F338(moby);
            return;
        }
        func_L00_002E6EF8(func_L00_0041F570, moby);
        break;
    }
    if (*(float *)(moby + 0x10) < 2.0f || *(float *)(moby + 0x10) > 1021.0f
        || *(float *)(moby + 0x14) < 2.0f || *(float *)(moby + 0x14) > 1021.0f
        || *(float *)(moby + 0x18) < 2.0f || *(float *)(moby + 0x18) > 1021.0f) {
        func_002FEE50(s->handle);
        func_0029F338(moby);
    }
}
