#include "common.h"

typedef unsigned int TaboraTI __attribute__((mode(TI)));
typedef float TaboraVec[4] __attribute__((aligned(16)));
typedef struct {
    TaboraVec pos[4];
    u32 color[4];
    float uv[8];
    u64 primitive, texture, mode, flags;
} TaboraQuad;

extern u64 func_0027C878(int);
extern void func_00280B90(void *, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283CE0(int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7AA8(float, float, float, float, float);
extern int func_001163B0(void);
extern int func_L02_002F1658(void);
extern char *func_L08_0034A078(void *, void *, int, void *);
extern float D_L08_001B3A20[] MACRO_ADDR;
extern char *D_L08_001B3A30[] MACRO_ADDR;

extern TaboraVec D_L08_001B3A40[] MACRO_ADDR;
extern TaboraVec D_L08_002603E0[][4];
extern TaboraVec D_L08_001B9B00;
extern TaboraVec D_0018A0E0;
extern char D_L08_001FF680[];

/* Draws a pair of ribbon strips between the supplied endpoints, with occasional
   particles at the requested segment. The two strips have independent textures.
   The named constants and argument copies are read inside the loop: gcse folds them, and
   they bring the RTL count to the 500 insns (251 hash buckets) of retail's spill slots. */
void func_L08_0042A0B0(int texture0, int texture1, TaboraVec *points,
                      int alpha0, int alpha1, int slot, int particleSegment)
{
    TaboraQuad q, glow;
    TaboraVec offsets[2], frame[4], basis[4], tangent, endpoints[2], particle;
    float width, segments, u, randomRadius, randomAngle, t;
    u32 color0, color1, saved0, saved1;
    int i, corner, corner2;
    char *p, *settings, *settings2, *visual, *base;
    char **owner;
    int entry = slot, row = slot;
    float w0;
    int mode = 0, flags = 0;
    TaboraVec *path = points;
    int segment = particleSegment;
    int flashCount = 0x7F;
    int sparkCount = 0x40;
    int mask = 3;
    int total = 20;
    int last = 19;

    q.texture = func_0027C878(texture0);
    color0 = (alpha0 << 24) | 0x7F407F;
    q.flags = 0x8000000048ULL;
    q.mode = 0xFF9000000260ULL;
    q.primitive = 0;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = color0;
    glow.texture = func_0027C878(texture1);
    width = 0.6f;
    u = D_L08_001B3A20[slot];
    color1 = (alpha1 << 24) | 0xFF10FF;
    glow.color[0] = glow.color[1] = glow.color[2] = glow.color[3] = color1;
    glow.flags = q.flags;
    glow.mode = q.mode;
    glow.primitive = q.primitive;
    glow.uv[0] = 1; glow.uv[1] = 0; glow.uv[2] = 1; glow.uv[3] = 1;
    glow.uv[4] = 0; glow.uv[5] = 0; glow.uv[6] = 0; glow.uv[7] = 1;
    q.uv[0] = u; q.uv[1] = 0; q.uv[2] = u; q.uv[3] = 1;
    q.uv[4] = u + 1; q.uv[5] = 0; q.uv[6] = u + 1; q.uv[7] = 1;
    if (*(s16 *)(((char **)D_L08_001B3A30)[slot] + 0xAA) == 0x1C) width = 0.3f;
    w0 = width;
    *(TaboraTI *)offsets[0] = 0;
    *(TaboraTI *)offsets[1] = 0;
    offsets[0][3] = 1; offsets[0][2] = width;
    offsets[1][2] = width + width; offsets[1][3] = 1;
    qcopy(frame[0], D_L08_002603E0[slot][1]);
    func_00282CF0(frame[1], D_L08_001B9B00, D_L08_002603E0[slot][3]);
    func_00282D30(frame[1], frame[1], 1);
    func_00282DD8(frame[2], frame[1], frame[0]);
    func_00282F20(frame[2], frame[2], 1);
    func_00282DD8(frame[0], frame[2], frame[1]);
    qcopy(frame[3], D_L08_002603E0[slot][3]);
    qcopy(basis[3], D_L08_002603E0[slot][3]);
    func_00282CF0(tangent, D_L08_001B3A40[slot], basis[3]);
    func_00282F20(basis[0], tangent, 1);
    func_00282DD8(basis[1], basis[0], D_0018A0E0);
    func_00282F20(basis[1], basis[1], -1);
    func_00282DD8(basis[2], basis[1], basis[0]);
    qcopy(q.pos[0], offsets[0]);
    func_00282D30(q.pos[1], q.pos[0], -1);
    qcopy(glow.pos[0], offsets[1]);
    func_00282D30(glow.pos[1], glow.pos[0], -1);
    func_002830C0(endpoints[0], points[0], basis);
    func_002830C0(endpoints[1], points[1], basis);
    func_00282CF0(frame[0], endpoints[1], endpoints[0]);
    func_00282F20(frame[0], frame[0], 1);
    func_00282CF0(frame[1], D_L08_001B9B00, endpoints[0]);
    func_00282DD8(frame[2], frame[1], frame[0]);
    func_00282F20(frame[2], frame[2], 1);
    func_00282DD8(frame[1], frame[0], frame[2]);
    qcopy(frame[3], endpoints[0]);
    func_002830C0(q.pos[0], q.pos[0], frame);
    func_002830C0(q.pos[1], q.pos[1], frame);
    func_002830C0(glow.pos[0], glow.pos[0], frame);
    func_002830C0(glow.pos[1], glow.pos[1], frame);
    for (i = 1; i < last; i++) {
        qcopy(q.pos[2], offsets[0]);
        func_00282D30(q.pos[3], q.pos[2], -1);
        qcopy(glow.pos[2], offsets[1]);
        func_00282D30(glow.pos[3], glow.pos[2], -1);
        func_002830C0(endpoints[0], path[i], basis);
        func_002830C0(endpoints[1], path[i + 1], basis);
        func_00282CF0(frame[0], endpoints[1], endpoints[0]);
        func_00282F20(frame[0], frame[0], 1);
        func_00282CF0(frame[1], D_L08_001B9B00, endpoints[0]);
        func_00282DD8(frame[2], frame[1], frame[0]);
        func_00282F20(frame[2], frame[2], 1);
        func_00282DD8(frame[1], frame[0], frame[2]);
        qcopy(frame[3], endpoints[0]);
        func_002830C0(q.pos[2], q.pos[2], frame);
        func_002830C0(q.pos[3], q.pos[3], frame);
        func_002830C0(glow.pos[2], glow.pos[2], frame);
        func_002830C0(glow.pos[3], glow.pos[3], frame);
        if (i == 1) {
            saved0 = q.color[0]; saved1 = glow.color[0];
            q.color[0] = q.color[1] = 0xFFFFFF;
            glow.color[0] = glow.color[1] = 0xFF10FF;
            func_00280B90(&q, 0, 0);
            func_00280B90(&glow, 0, 0);
            q.color[0] = q.color[1] = q.color[2] = q.color[3] = saved0;
            glow.color[0] = glow.color[1] = glow.color[2] = glow.color[3] = saved1;
        } else {
            func_00280B90(&q, mode, flags);
            func_00280B90(&glow, mode, flags);
        }
        qcopy(q.pos[0], q.pos[2]); qcopy(q.pos[1], q.pos[3]);
        qcopy(glow.pos[0], glow.pos[2]); qcopy(glow.pos[1], glow.pos[3]);
        if (i == segment && func_L02_002F1658()) {
            owner = &((char **)D_L08_001B3A30)[entry];
            randomRadius = func_002A7878(0.03f, 0.15f);
            randomAngle = func_002A78D8(0.3490659f, 0.6981318f);
            *(TaboraTI *)particle = 0;
            particle[3] = particle[0] = 1;
            particle[0] = randomRadius * func_00283180(randomAngle);
            particle[1] = randomRadius * func_00283198(randomAngle);
            func_00283098(particle, particle, D_L08_002603E0[row]);
            corner = func_001163B0() & mask;
            p = func_L08_0034A078(q.pos[corner], particle, sparkCount, *owner);
            if (p) {
                base = D_L08_001FF680;
                visual = p + 0x20;
                settings = *(char **)(base + 0xD4);
                p[2] = settings[0];
                *(float *)(visual + 0x10) = 1 / func_00283CE0(*(s16 *)(p + 0xA));
                *(u32 *)(visual + 0x18) = 0x7F207F;
                *(float *)(p + 0xC) = 150000;
                corner2 = func_001163B0() & mask;
                p = func_L08_0034A078(q.pos[corner2], particle, flashCount, *owner);
                if (p) {
                    visual = p + 0x20;
                    settings2 = *(char **)(base + 0xD4);
                    p[2] = settings2[0];
                    *(float *)(visual + 0x10) = 1 / func_00283CE0(*(s16 *)(p + 0xA));
                    *(u32 *)(visual + 0x18) = 0xFFFFFF;
                    *(float *)(p + 0xC) = 30000;
                }
            }
        }
        t = func_00283CE0(i);
        segments = func_00283CE0(total);
        t = func_002A7AA8(-1, 0, 1, 0, t / segments);
        {
            float u2 = D_L08_001B3A20[slot];
            q.uv[0] = u2; q.uv[1] = 0; q.uv[2] = u2; q.uv[3] = 1;
            q.uv[4] = u2 + 1; q.uv[5] = 0; q.uv[6] = u2 + 1; q.uv[7] = 1;
        }
        offsets[0][2] = w0 + (0.05f - w0) * t;
        offsets[1][2] = offsets[0][2] + offsets[0][2];
    }
}
