#include "include_asm.h"

#include "common.h"

extern void func_0032F620(int, int, int);

/* func_L13_0041B670 is in L13_0041B670-g16.c (-G16). */

/* Plays the resident message for the sub-object's state; states 2..4 and the
   out-of-range case repeat the default message in their own block. */

/* func_L13_0041BAE0 is in L13_0041BAE0-ring.c (-G32). */

INCLUDE_ASM("asm/levels", func_L13_0041FBE0);




INCLUDE_ASM("asm/levels", func_L13_00438D88);

typedef struct { float x, y, z, w; } __attribute__((aligned(16))) PathPoint;
typedef struct { int count; int reserved[3]; PathPoint point[0]; } CameraPath;
extern char *D_L13_001B22C4[] __attribute__((sda));
extern char *D_L13_001B9914;
extern CameraPath *D_L13_001FE580[];
extern float D_00189EA0[4];
extern float func_00282E48(void *, void *);
extern int func_L00_00341FA8(void *, void *, void *, int *, float *, int, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_L13_004388C8(char *);

void func_L13_00439820(char *camera) {
    float projected[4] __attribute__((aligned(16)));
    float tangent[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    int segment;
    float fraction;
    char *source;
    char *settings = *(char **)(D_L13_001B22C4[0] + *(short *)(camera + 0x84) * 32 + 0x1C);
    source = D_L13_001B9914;
    qcopy(camera + 0x30, source + 0x30);
    qcopy(camera, source);
    qcopy(camera + 0x10, source + 0x10);
    qcopy(camera + 0x20, source + 0x20);
    qcopy(camera + 0x40, camera);
    if (*(int *)(settings + 0x20) >= 0) {
        CameraPath *path = D_L13_001FE580[*(int *)(settings + 0x20)];
        int i;
        for (i = 0; i < path->count; i++) {
            path->point[i].w = func_00282E48(&path->point[i], &path->point[(i + 1) % path->count]);
        }
    }
    *(short *)(settings + 0x36) = 0;
    if (*(int *)(settings + 0x30) == 3) {
        CameraPath *path = D_L13_001FE580[*(int *)(settings + 0x20)];
        segment = 0;
        fraction = 0.0f;
        if (func_L00_00341FA8(path, D_00189EA0, projected, &segment, &fraction, 0, 20.0f, 1.0f, 0.0f)) {
            int count = path->count;
            int next = segment + 1;
            if (next >= count) next = count - 1;
            func_00282CF0(tangent, &path->point[next], &path->point[segment]);
            if (func_00282DF0(tangent) != 0.0f && next != segment) {
                func_00282F20(tangent, tangent, 1.0f);
                func_00282CF0(difference, camera + 0x30, D_00189EA0);
                if (func_00282DB0(difference, tangent) > 0.0f)
                    *(short *)(settings + 0x36) = 1;
            }
        }
    }
    func_L13_004388C8(camera);
}
