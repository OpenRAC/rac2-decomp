#include "common.h"

typedef unsigned int DrawQuad __attribute__((mode(TI)));
typedef union { DrawQuad q; float f[4]; } DrawVec;
typedef struct { DrawVec v[9]; } DrawPacket;

extern DrawVec D_L30_001B09B0[4] __attribute__((sda));
extern DrawVec D_L30_001B9DC0;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00280B90(void *, int, int);

void func_L30_003D9CA8(DrawVec *position, DrawPacket *source, float scale, float offset) {
    struct { DrawPacket packet; DrawVec up, side, forward, normal, point, temp; } f;
    int i;
    f.packet = *source;
    source = &f.packet;
    f.up.q = 0; f.up.f[2] = 1; f.up.f[3] = 1;
    qcopy(&f.point, position);
    func_00282CF0(&f.side, &D_L30_001B9DC0, &f.point);
    func_00282F20(&f.side, &f.side, 1.0f);
    func_00282DD8(&f.forward, &f.side, &f.up);
    func_00282F20(&f.forward, &f.forward, 1.0f);
    func_00282DD8(&f.normal, &f.forward, &f.side);
    func_00282D30(&f.temp, &f.side, offset);
    func_00282CC0(&f.point, &f.point, &f.temp);
    for (i = 0; i < 4; i++) {
        func_00282D30(&f.packet.v[i], &D_L30_001B09B0[i], scale);
        func_002830C0(&f.packet.v[i], &f.packet.v[i], &f.side);
    }
    func_00280B90(source, 0, 0);
}
