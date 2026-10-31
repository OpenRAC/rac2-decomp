/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1420/1440 bytes; frame 0xC0 retained, weighted path-search and pointer reload scheduling differ.
 * Reopen with measured camera runtime/control record layouts and path-loop lifetimes.
 * ABI/bounds: Four complete vector buffers. Route-step outputs use separate real int segment and float distance objects, not an undersized packet. All five GPR and one FP route-step arguments retained.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"
typedef float RouteVector[4] __attribute__((aligned(16)));
extern unsigned char *D_L01_001B1F04;
extern unsigned char *D_L01_001FE180[];
extern unsigned char *D_L01_001B255C;
extern unsigned char D_L01_001B96F0[];
extern unsigned char D_0018A0E0[];
extern int D_L01_001B1FA8;
extern int D_L01_001B1FA8_gp SDATA(D_L01_001B1FA8);
extern int func_L00_00341820(void *, void *, void *, void *, int, float);
extern int func_00282978(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_0026FF08(int, int, float, float, float, float);
extern void func_00272198(float);
extern float func_002A7C00(float, float, float);
extern void func_L01_002BEB90(int, int);

void func_L01_0042C8D8(unsigned char *camera)
{
    RouteVector old, up, direction, target;
    unsigned char *v = *(unsigned char **)(camera + 0x70);
    unsigned char *c = *(unsigned char **)(D_L01_001B1F04 + *(short *)(camera + 0x84) * 32 + 0x1c);
    unsigned char *motion = v + 0x40;
    unsigned char *path, *look;
    short *indices = (short *)(v + 0x58);
    int done, i, j, segment, next, local_segment;
    float along, total, local_distance;
    if (!*(short *)(motion + 0x14)) {
        path = D_L01_001FE180[*(int *)(c + 0x20)];
        look = D_L01_001FE180[*(int *)(c + 0x24)];
        if (*(int *)(c + 0x58)) D_L01_001B1FA8 = 1;
        *(short *)(motion + 0x14) = 1;
        qcopy(camera + 0x30, path + 0x10);
        if (*(int *)(c + 0x28) >= 0) {
            up[0] = *(float *)(c + 0x2c); up[1] = *(float *)(c + 0x30); up[2] = *(float *)(c + 0x34);
            *(int *)&up[3] = 0;
            func_00283098(up, up, D_L01_001B96F0);
            func_00282CC0(direction, D_L01_001B255C + *(int *)(c + 0x28) * 256 + 0x10, up);
            func_00282CF0(old, direction, camera + 0x30);
        } else func_00282CF0(old, look + 0x10, camera + 0x30);
        func_00282D30(up, D_0018A0E0, -1.0f);
        func_00282F20(camera, old, 1.0f);
        func_00282DD8(camera + 0x10, camera, up);
        func_00282F20(camera + 0x10, camera + 0x10, 1.0f);
        func_00282DD8(camera + 0x20, camera + 0x10, camera);
        return;
    }
    path = D_L01_001FE180[*(int *)(c + 0x20)];
    qcopy(old, camera + 0x30);
    done = func_L00_00341820(path, camera + 0x30, motion, v + 0x44, 0, *(float *)(c + 0x3c) * 0.016666668f);
    if (*(short *)(motion + 0x16) && func_00282978(v + 0x56)) done = 1;
    if (c[0x39]) done = 1;
    if (done) {
        c[0x39] = 1;
        func_0026FF08(0, 3, *(float *)(v + 0x88), 0.005f, 0.2f, 0.0f);
        func_00272198(4.0f);
        *(short *)(camera + 0x7e) = 4;
        if (*(int *)(c + 0x58)) D_L01_001B1FA8_gp = 0;
        func_L01_002BEB90(0, 1);
        return;
    }
    for (i = 0; i < 7 && indices[i] >= 0 && indices[i + 1] >= 0; ++i) {
        segment = *(int *)motion;
        next = i + 1;
        if (segment < indices[i] || segment >= indices[next]) continue;
        along = 0;
        for (j = indices[i]; j < segment; ++j) along += *(float *)(path + j * 16 + 0x1c);
        total = along;
        along += *(float *)(motion + 4);
        for (j = segment; j < indices[next]; ++j) total += *(float *)(path + j * 16 + 0x1c);
        func_0026FF08(0, 3, func_002A7C00(*(float *)(v + 0x68 + i * 4),
            *(float *)(v + 0x68 + next * 4), along / total) * 0.017453294f, 0.005f, 0.2f, 0);
    }
    *(float *)(motion + 0x10) += func_00282E48(old, camera + 0x30);
    if (*(int *)(c + 0x28) >= 0) {
        direction[0] = *(float *)(c + 0x2c); direction[1] = *(float *)(c + 0x30); direction[2] = *(float *)(c + 0x34);
        *(int *)&direction[3] = 0;
        func_00283098(direction, direction, D_L01_001B96F0);
        func_00282CC0(target, D_L01_001B255C + *(int *)(c + 0x28) * 256 + 0x10, direction);
        func_00282CF0(up, target, camera + 0x30);
    } else {
        local_segment = 0; local_distance = 0;
        func_L00_00341820(D_L01_001FE180[*(int *)(c + 0x24)], direction,
            &local_segment, &local_distance, 0, *(float *)(motion + 0x10) / *(float *)(motion + 8) * *(float *)(motion + 12));
        func_00282CF0(up, direction, camera + 0x30);
    }
    func_00282D30(direction, D_0018A0E0, -1.0f);
    func_00282F20(camera, up, 1.0f);
    func_00282DD8(camera + 0x10, camera, direction);
    func_00282F20(camera + 0x10, camera + 0x10, 1.0f);
    func_00282DD8(camera + 0x20, camera + 0x10, camera);
}
