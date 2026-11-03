#include "common.h"
typedef float RouteVector[4] __attribute__((aligned(16)));
typedef struct { short idx[8]; float angle[8]; float roll; } PathKeys;
typedef struct { char pad0[0x20]; int path; int look; int target; float offset[3]; char pad38; unsigned char finished; char pad3a[2]; float speed; char pad40[0x18]; int lock; } CameraPath;
typedef struct { int segment; float distance; float length; float scale; float travelled; short started; short stop; } PathMotion;
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
    CameraPath *c = *(CameraPath **)(D_L01_001B1F04 + *(short *)(camera + 0x84) * 32 + 0x1c);
    PathMotion *motion = (PathMotion *)(v + 0x40);
    unsigned char *path;
    PathKeys *keys = (PathKeys *)(v + 0x58);
    int done, i, j, k, target_index, local_segment;
    float along, total, local_distance;
    if (!motion->started) {
        unsigned char *start = D_L01_001FE180[c->path];
        unsigned char *look = D_L01_001FE180[c->look];
        if (c->lock) D_L01_001B1FA8 = 1;
        motion->started = 1;
        qcopy(camera + 0x30, start + 0x10);
        target_index = c->target;
        if (target_index >= 0) {
            float *src = c->offset;
            unsigned char *entity = D_L01_001B255C + target_index * 256;
            up[0] = src[0]; up[1] = src[1]; up[2] = src[2];
            *(int *)&up[3] = 0;
            func_00283098(up, up, D_L01_001B96F0);
            func_00282CC0(direction, entity + 0x10, up);
            func_00282CF0(old, direction, camera + 0x30);
        } else func_00282CF0(old, look + 0x10, camera + 0x30);
        func_00282D30(up, D_0018A0E0, -1.0f);
        func_00282F20(camera, old, 1.0f);
        func_00282DD8(camera + 0x10, camera, up);
        func_00282F20(camera + 0x10, camera + 0x10, 1.0f);
        func_00282DD8(camera + 0x20, camera + 0x10, camera);
        return;
    }
    path = D_L01_001FE180[c->path];
    qcopy(old, camera + 0x30);
    done = func_L00_00341820(path, camera + 0x30, &motion->segment, v + 0x44, 0, c->speed * 0.016666668f);
    if (motion->stop && func_00282978(v + 0x56)) done = 1;
    if (c->finished) done = 1;
    if (done) {
        c->finished = 1;
        func_0026FF08(0, 3, keys->roll, 0.005f, 0.2f, 0.0f);
        func_00272198(4.0f);
        *(short *)(camera + 0x7e) = 4;
        if (c->lock) D_L01_001B1FA8_gp = 0;
        func_L01_002BEB90(0, 1);
        return;
    }
    for (i = 0; i < 7 && keys->idx[i] >= 0 && keys->idx[i + 1] >= 0; ++i) {
        if (motion->segment >= keys->idx[i] && motion->segment < keys->idx[i + 1]) {
            along = 0;
            for (j = keys->idx[i]; j < motion->segment; ++j) along += *(float *)(path + j * 16 + 0x1c);
            total = along;
            along += motion->distance;
            for (k = motion->segment; k < keys->idx[i + 1]; ++k) total += *(float *)(path + k * 16 + 0x1c);
            func_0026FF08(0, 3, func_002A7C00(keys->angle[i],
                keys->angle[i + 1], along / total) * 0.017453294f, 0.005f, 0.2f, 0);
        }
    }
    motion->travelled += func_00282E48(old, camera + 0x30);
    target_index = c->target;
    if (target_index >= 0) {
        float *src = c->offset;
        unsigned char *entity = D_L01_001B255C + target_index * 256;
        direction[0] = src[0]; direction[1] = src[1]; direction[2] = src[2];
        *(int *)&direction[3] = 0;
        func_00283098(direction, direction, D_L01_001B96F0);
        func_00282CC0(target, entity + 0x10, direction);
        func_00282CF0(up, target, camera + 0x30);
    } else {
        float progress = motion->travelled / motion->length * motion->scale;
        local_segment = 0; local_distance = 0;
        func_L00_00341820(D_L01_001FE180[c->look], direction, &local_segment, &local_distance, 0, progress);
        func_00282CF0(up, direction, camera + 0x30);
    }
    func_00282D30(direction, D_0018A0E0, -1.0f);
    func_00282F20(camera, up, 1.0f);
    func_00282DD8(camera + 0x10, camera, direction);
    func_00282F20(camera + 0x10, camera + 0x10, 1.0f);
    func_00282DD8(camera + 0x20, camera + 0x10, camera);
}
