/* Related hero layout and prediction flow adapted from OpenRAC/rac1-decomp
 * src/overlays/shared/hero_idle_and_animation.c (GPL-3.0). */

#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { float x; float y; float z; } ContactVector3;
typedef struct {
    unsigned char pad0[0x1d4];
    int f1D4;
    unsigned char pad1d8[0x38];
    short f210;
    unsigned char pad212[0x52];
    float f264;
    unsigned char pad268[0x1c];
    unsigned char f284;
    unsigned char f285;
    unsigned char pad286[0xe];
    unsigned char *f294;
    unsigned char pad298[0x84];
    float f31C;
    unsigned char pad320[0x1cc];
    float f4EC;
    unsigned char pad4f0[0xc];
    float f4FC;
    unsigned char pad500[0x20];
    float f520;
    unsigned char pad524[0x54];
    int f578;
    unsigned char pad57c[0x1d18];
    int f2294;
    unsigned char pad2298[0x4];
    int f229C;
    unsigned char pad22a0[0x4];
    int f22A4;
    unsigned char pad22a8[0x8];
    int f22B0;
    unsigned char pad22b4[0xf];
    unsigned char f22C3;
    unsigned char pad22c4[0x214];
    short f24D8;
    unsigned char f24DA;
    unsigned char f24DB;
} WallContactHero;
extern WallContactHero D_00189E20;
typedef struct {
    unsigned char pad0[0x18];
    unsigned char *object;
    unsigned char pad1c[4];
    Vector point;
    unsigned char pad30[0x10];
    Vector normal;
} WallContactHit;
extern WallContactHit D_L00_001BF200;
extern float func_L00_002D3B00(char *);
extern void func_L00_002D3B58(Quadword *, Quadword *, float);
extern void func_L00_002D3BD8(char *, int, float);
extern void func_L00_002D3778(ContactVector3 *, ContactVector3 *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_L00_002ACF88(void *, void *, void *);
extern int func_L00_002AB108(float *, float, float);
extern int func_002AD0B0(unsigned char *);
/* EE argument banks: a0 = output, a1 = flag, f12/f13/f14 = scale/angle/height.
 * The floating arguments retain their order independently of the integer bank. */
extern void func_L00_002D3638(float *output, float scale, float angle, float height, int flag);
extern int func_002761F8(void *, void *, unsigned int, void *, void *);
extern int func_00278E78(void);
extern float func_L00_002D3EA8(void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E80(void *, void *);
/* Predict the next ledge contact, then validate the two obstruction probes. */
void func_L00_002AC578(void)
{
    Vector predicted, probeEnd, localNormal;
    unsigned char *state;
    int contact;
    int ticks;
    float steps;
    float height, distance, angle, limit;

    if (D_00189E20.f31C < 0.4f) return;
    if (func_L00_002D3B00((char *)&D_00189E20 + 0xF0) < -0.3333333432674408f || D_00189E20.f22C3) return;
    if (D_00189E20.f578) {
        D_00189E20.f1D4 = 0;
        return;
    }
    qcopy(&predicted, (unsigned char *)&D_00189E20 + 0x80);
    ticks = 20;
    qcopy(&probeEnd, (unsigned char *)&D_00189E20 + 0x110);
    steps = (float)ticks;
    func_L00_002D3B58(&probeEnd.q, &probeEnd.q, 0.0f);
    func_L00_002D3BD8((char *)&probeEnd, (int)&probeEnd, steps);
    FastVecAdd(&predicted, &predicted, &probeEnd);
    distance = func_L00_002D3B00((char *)&D_00189E20 + 0xF0);
    distance = distance * steps - D_00189E20.f520 * steps * steps * 0.5f;
    func_L00_002D3778((ContactVector3 *)&predicted,
                     (ContactVector3 *)&predicted, distance);
    if (func_L00_002ACF88(&predicted, (unsigned char *)&D_00189E20 + 0x90, 0)) {
        D_00189E20.f1D4 = 0;
        D_00189E20.f210 = 0x16;
        return;
    }
    if (!func_L00_002AB108(0, 0.3f, 1.0f)) return;
    state = 0;
    if (D_L00_001BF200.object) state = (unsigned char *)func_002AD0B0(D_L00_001BF200.object);
    height = 1.7f;
    if (state && (*(unsigned int *)(state + 0x3C) & 0x20)) height = 0.5f;
    else if (D_00189E20.f2294 != 0x11 && (!D_00189E20.f285 || D_00189E20.f284)) height = 3.0f;
    func_L00_002D3638(predicted.f, 0.0f, 0.0f, height, 1);
    func_L00_002D3638(probeEnd.f, D_00189E20.f264 + 1.4f, 0.0f, height, 1);
    if (!CollLine(&predicted, &probeEnd, 2, 0, 0)) return;
    contact = GetCollHitMaterial();
    if (contact == 10 || contact == 12) return;
    D_00189E20.f294 = D_L00_001BF200.object;
    angle = func_L00_002D3EA8(&D_L00_001BF200.normal);
    if (angle < 1.3089970350265503f) return;
    transform_vector(&localNormal, &D_L00_001BF200.normal, (unsigned char *)&D_00189E20 + 0x40);
    angle = func_00283248(localNormal.f[0], localNormal.f[1]);
    angle = FastDiffRots(angle, 3.1415927410125732f);
    if (0.8726646900177002f < angle) return;
    limit = D_00189E20.f2294 == 0x11 ? 0.95f : 0.72f;
    func_L00_002D3638(predicted.f, 0.0f, 0.0f, 0.2f, 1);
    func_L00_002D3638(probeEnd.f, D_00189E20.f264 + 1.4f, 0.0f, 0.2f, 1);
    if (!CollLine(&predicted, &probeEnd, 2, 0, 0)) return;
    distance = vec_distance_xy(&D_L00_001BF200.point, &predicted);
    if (limit < distance) return;
    *(Quadword *)((unsigned char *)&D_00189E20 + 0x4E0) = D_L00_001BF200.normal.q;
    D_00189E20.f4EC = func_00283248(D_L00_001BF200.normal.f[0], D_L00_001BF200.normal.f[1]);
    if (D_00189E20.f229C != 4 && D_00189E20.f22A4 != 4 && D_00189E20.f22B0 != 4) return;
    if (D_00189E20.f24D8 && FastDiffRots(D_00189E20.f4FC, D_00189E20.f4EC) < 2.967060089111328f) return;
    D_00189E20.f24DA = 0;
    if (contact == 15) D_00189E20.f24DA = 1;
    else if (D_00189E20.f24DB) return;
    if (D_00189E20.f2294 == 0x11)
        D_00189E20.f1D4 = 7;
    else
        D_00189E20.f1D4 = 6;
}
