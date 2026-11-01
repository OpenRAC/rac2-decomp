/* PAL copy of func_L00_003FEEA0: 1744/1744 bytes, all opcodes and registers right. The only
 * difference is the 0xF0/0xF4 spill-slot pair, swapped. This is the gcse bucket rotation: with
 * dcc1 the plain build has 191 buckets, and RAC_S=183, 193 or 199 gives an exact function, so
 * the body wants 3 to 6 more (or about 16 fewer) insns at gcse with the same final code.
 */
#include "common.h"

extern void func_00300190(void *, void *);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
typedef struct EffectParticle {
    unsigned char prefix[10];
    short life;
    unsigned char gap[20];
} EffectParticle;
typedef struct EffectParticleExtension {
    int color, mode;
    short spin;
    unsigned char alpha, life;
} EffectParticleExtension;
extern EffectParticle *func_002BDCE8(void *, float, float, float, int, void *, float, unsigned, int);
extern float D_L00_001A8F20[4] MACRO_ADDR;


extern void func_002AFFD8(void *, void *, int);
extern void func_L00_003252A8(void *, void *, int);
extern void func_002FEE70(int, void *, void *);
extern void func_002FE880(void *, void *, float);
extern void func_L00_0031D670(void *, void *, void *, float);
extern int func_002FE9D0(void *);
extern int func_00300540(int);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_0032D758(void *, int, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_003FF530(void *);
extern void func_002A9288(void *, float);
extern float func_00282DB0(void *, void *);
extern unsigned char D_0013958D[];
typedef struct EffectPlayer {
    unsigned char prefix[0x70];
    float scale;
    unsigned char suffix[0x6C];
} EffectPlayer;
extern EffectPlayer D_L00_00262570[];
extern void *D_0018C0B0[];
extern void *D_L00_001C3280[];
extern int D_L00_001A8FF0[] MACRO_ADDR, D_L00_001A8FF4[] MACRO_ADDR;
extern float D_L00_001B0C20 __attribute__((sda));
extern float D_L00_001B0C28 __attribute__((sda));
extern float D_L00_001B0C30 __attribute__((sda));
extern float D_L00_001B0C34 __attribute__((sda));
extern float D_L00_001B0C3C __attribute__((sda));
extern float D_L00_001B0C40 __attribute__((sda));
extern int D_L00_001B0C44 __attribute__((sda));
extern char D_L00_001BF230[];
extern unsigned char D_L00_001B0C48[8] NOT_SDA;

typedef int EffectQuad __attribute__((mode(TI)));
typedef union EffectVector { EffectQuad quad; float f[4]; } EffectVector;
typedef struct EffectState {
    EffectVector velocity, axis;
    int timer, bounces, trail, charged, rotation;
} EffectState;
typedef struct SweepQuery {
    EffectVector start, end, delta;
    void *owner;
    int *params;
    int mode;
    float radius, scale, extra;
    int field48, field4c, field50, hit, field58;
    float tolerance;
} SweepQuery;
typedef struct HitQuery {
    float pos[3], radius;
    void *owner;
    unsigned flags;
    unsigned char type, active;
    unsigned short classId;
    float scale;
    int enabled;
} HitQuery;

typedef struct EffectWorkspace {
    EffectVector normal, old;
    union { EffectVector point; int excluded[2]; } params;
    EffectVector tmp;
    SweepQuery query;
    HitQuery hit;
    EffectVector offset, step;
} EffectWorkspace;

void func_PAL_L00_00403780(char *self)
{
    EffectState *p = *(EffectState **)(self + 0x68);
    EffectWorkspace work;
    int i, result, kind, swept;
    float radius, extra, speed, scale;
    float fadeRadius;
    int remaining;
    void **targets;
    func_002AFFD8(self + 0x10, work.normal.f, 1);
    func_00300190(self + 0x10, self + 0x10);
    switch ((unsigned char)self[0x20]) {
    case 0:
        qcopy(work.old.f, self + 0x10);
        func_00282CC0(self + 0x10, self + 0x10, p);
        func_002FEE70(p->rotation, p, 0);
        func_002FE880(self + 0x10, p, 0.005840000230818987f);
        func_00282948(&p->trail);
        if (p->trail) {
            for (i = 0; i < 3; i++) {
                int id;
                EffectParticle *r;
                float x;
                float f;
                float third = 0.33329999446868896f;
                float one = 1.0f;
                *(EffectQuad *)work.tmp.f = *(EffectQuad *)(self + 0x10);
                func_L00_0031D670(work.params.point.f, work.old.f, work.tmp.f, func_00283CE0(i) * third);
                id = func_002A77E0(6);
                if (func_002A77E0(2)) {
                    id = -id;
                }
                x = (float)p->trail / func_00283CE0(42) * 65000.0f + 10000.0f;
                r = func_002BDCE8(work.params.point.f, 0.025f, one, one, id, D_L00_001A8F20, x, 0x80808080, 1);
                if (r) {
                    short life = 42;
                    EffectParticleExtension *extension = (EffectParticleExtension *)(r + 1);
                    r->life = life;
                    extension->mode = 2;
                    extension->alpha = 127;
                    { int l = r->life & 0xFF; extension->life = l; }
                }
            }
        }
        __builtin_memcpy(work.params.excluded, D_L00_001B0C48, 8);
        extra = 1.5f;
        if ((float)p->bounces == 3.0f) {
            extra = 0.0f;
        }
        radius = D_L00_001B0C30;
        if (p->charged) {
            radius = D_L00_001B0C3C;
        }
        qcopy(work.query.start.f, work.old.f);
        qcopy(work.query.end.f, self + 0x10);
        qcopy(work.query.delta.f, p);
        work.query.params = work.params.excluded;
        work.query.owner = self;
        work.query.mode = 2;
        work.query.radius = radius;
        work.query.scale = (D_L00_001B0C20 - 1.0f) * 1.2f + 1.0f;
        work.query.extra = extra;
        work.query.field48 = 0;
        work.query.field4c = 0;
        work.query.field58 = 0;
        swept = func_002FE9D0(&work.query);
        kind = func_00300540(work.query.hit);
        if (swept > 0 && (unsigned)(kind - 1) < 2) {
            func_L00_003FF530(self);
            func_0029F338(self);
            return;
        }
        qcopy(self + 0x10, work.query.end.f);
        qcopy(p, work.query.delta.f);
        func_002ACDE8(self + 0xC0, self + 0xC0, p->axis.f);
        func_002ACDE8(self + 0xD0, self + 0xD0, p->axis.f);
        func_002ACDE8(self + 0xE0, self + 0xE0, p->axis.f);
        work.hit.owner = self;
        work.hit.flags = 0x830000;
        { EffectPlayer *pl = &D_L00_00262570[D_0013958D[0]]; work.hit.scale = pl->scale; }
        work.hit.enabled = 1;
        qcopy(work.hit.pos, p);
        func_00282F20(work.hit.pos, work.hit.pos, 1.0f);
        work.hit.type = 3;
        work.hit.radius = 5627.9248046875f;
        work.hit.classId = *(unsigned short *)(self + 0xAA);
        work.hit.active = 1;
        result = func_00277F48(self + 0x10, 1, D_0018C0B0[0], &work.hit, radius + 0.1f);
        if (result) {
            if (p->charged) {
                if (result > 0) {
                    targets = D_L00_001C3280;
                    remaining = result;
                    do {
                        func_0032D758(*targets, 0x4C, *(void **)(self + 0xB8));
                        targets++;
                    } while (--remaining);
                }
            } else {
                if (result > 0) {
                    targets = D_L00_001C3280;
                    remaining = result;
                    do {
                        func_0032D758(*targets, 0x25, *(void **)(self + 0xB8));
                        targets++;
                    } while (--remaining);
                }
            }
            func_L00_003FF530(self);
            func_0029F338(self);
            return;
        }
        if (swept > 0) {
            qcopy(work.tmp.f, p);
            work.tmp.f[2] = 0;
            func_00282DD8(work.tmp.f, work.tmp.f, work.normal.f);
            func_00282F20(work.tmp.f, work.tmp.f, 1.0f);
            func_002AB668(p->axis.f, work.tmp.f, func_002A7878(0.06283186376094818f, 0.10482405126094818f));
            func_002E5CF8(1, 0, self);
            p->bounces += 1;
            if (p->bounces >= 4) {
                qcopy(self + 0x10, D_L00_001BF230);
                self[0x20] = 1;
                p->timer = (D_L00_001B0C44 * 5 + 2) / 6;
                speed = D_L00_001B0C28 * 0.06283186376094818f;
                if (p->charged) {
                    speed *= D_L00_001B0C34;
                }
                func_L00_003252A8(self, work.offset.f, 1);
                scale = func_00282DB0(work.offset.f, p);
                func_00282D30(work.step.f, work.offset.f, scale);
                func_00282CF0(p, p, work.step.f);
                func_00282F20(p, p, speed);
                qcopy(p->axis.f, work.tmp.f);
                p->axis.f[3] = 0.06283186376094818f;
            }
        }
        break;
    case 1:
        func_00282CC0(self + 0x10, self + 0x10, p);
        func_002AB668(work.old.f, p->axis.f, p->axis.f[3]);
        func_002ACDE8(self + 0xC0, self + 0xC0, work.old.f);
        func_002ACDE8(self + 0xD0, self + 0xD0, work.old.f);
        func_002ACDE8(self + 0xE0, self + 0xE0, work.old.f);
        scale = (D_L00_001B0C40 - 1.0f) * 1.2f + 1.0f;
        p->axis.f[3] *= scale;
        func_00282D30(p, p, scale);
        if (func_00282948(&p->timer)) {
            func_L00_003FF530(self);
            func_0029F338(self);
            return;
        }
        break;
    }
    fadeRadius = D_L00_001B0C28;
    if (p->charged) {
        fadeRadius *= D_L00_001B0C34;
    }
    if (D_L00_001A8FF0[0] == 0 && D_L00_001A8FF4[0] == 0) {
        func_002A9288(self, fadeRadius);
    }
}
