/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 904/920 bytes; frame 0x80 retained, init loop nop schedule and path-loop allocation differ.
 * Reopen with camera-route record types or measured counted pointer-loop lowering.
 * ABI/bounds: Route begins after a 16-byte header. Rotation buffer is a full quad. Segment-count modulo and path writes retained; eight signed-short indices and eight weights use actual backing runtime fields.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"

typedef float CameraVector[4] __attribute__((aligned(16)));
extern unsigned char *D_L01_001B1F04;
extern unsigned char *D_L01_001FE180[];
extern unsigned char D_L01_001BD9C0[];
extern unsigned char D_L01_001B9380[];
extern unsigned char *D_L01_001B264C __attribute__((sda));
extern float func_00283248(float, float);
extern float func_00282E48(void *, void *);
extern float func_00283CE0(int);
extern void func_00282C88(void *);
extern void func_L01_002BEB90(int, int);
extern void func_L00_002B9D60(void *, void *, int, int);

/* Initializes a camera route and both dampers, caching the measured lengths of
 * each path segment. The route records begin after their 16-byte header. */
void func_L01_0042C540(unsigned char *camera)
{
    CameraVector rotation;
    unsigned char *config = *(unsigned char **)(D_L01_001B1F04 + *(short *)(camera + 0x84) * 32 + 0x1c);
    unsigned char *vars, *motion, *path, *pose;
    short *indices;
    float *weights, *clear_weights, length;
    short *clear_indices;
    int i, count;
    config[0x38] = 3;
    vars = *(unsigned char **)(camera + 0x70);
    motion = vars + 0x40;
    *(int *)(motion + 0) = 0; *(int *)(motion + 4) = 0; *(int *)(motion + 8) = 0;
    *(int *)(motion + 12) = 0; *(int *)(motion + 16) = 0;
    *(short *)(motion + 20) = 0;
    *(short *)(motion + 22) = *(u16 *)(config + 0x3a);
    vars = *(unsigned char **)(camera + 0x70);
    indices = (short *)(vars + 0x58); weights = (float *)(vars + 0x68);
    clear_weights = weights; clear_indices = indices;
    for (i = 7; i >= 0; --i) { *clear_weights++ = 0; *clear_indices++ = -1; }
    *(float *)(vars + 0x88) = func_00283248(1.0f, *(float *)(D_L01_001BD9C0 + 0xb0)) * 2.0f;
    if (*(int *)(config + 0x20) >= 0) {
        path = D_L01_001FE180[*(int *)(config + 0x20)];
        count = 0;
        for (i = 0; i < *(int *)path; ++i) {
            if (*(float *)(path + 0x1c + i * 16) > 0) {
                *weights++ = *(float *)(path + 0x1c + i * 16);
                *indices++ = i;
            }
            length = func_00282E48(path + 0x10 + i * 16,
                path + 0x10 + ((i + 1) % *(int *)path) * 16);
            *(float *)(path + 0x1c + i * 16) = length;
            if (i < *(int *)path - 1) *(float *)(motion + 8) += length;
        }
    }
    if (*(short *)(config + 0x3a) > 0)
        *(float *)(config + 0x3c) = *(float *)(motion + 8) / func_00283CE0(*(short *)(config + 0x3a)) * 60.0f;
    if (*(int *)(config + 0x24) >= 0) {
        path = D_L01_001FE180[*(int *)(config + 0x24)];
        for (i = 0; i < *(int *)path; ++i) {
            length = func_00282E48(path + 0x10 + i * 16,
                path + 0x10 + ((i + 1) % *(int *)path) * 16);
            *(float *)(path + 0x1c + i * 16) = length;
            if (i < *(int *)path - 1) *(float *)(motion + 12) += length;
        }
    }
    vars = *(unsigned char **)(camera + 0x70);
    *(float *)(vars + 0) = 0.03f; *(float *)(vars + 4) = 0.2f;
    func_00282C88(vars + 0x10);
    vars = *(unsigned char **)(camera + 0x70);
    *(float *)(vars + 0x20) = 0.03f; *(float *)(vars + 0x24) = 0.2f;
    func_00282C88(vars + 0x30);
    pose = *(unsigned char **)(D_L01_001B9380 + 0x194);
    qcopy(camera + 0x30, pose + 0x30);
    qcopy(camera, pose);
    qcopy(camera + 0x10, pose + 0x10);
    qcopy(camera + 0x20, pose + 0x20);
    if (*(int *)(config + 0x54) < 0) func_L01_002BEB90(0x6f, 1);
    else {
        qzero(rotation); rotation[3] = 1.0f;
        func_L00_002B9D60(D_L01_001B264C + *(int *)(config + 0x54) * 128 + 0x30, rotation, 0x6f, 0);
    }
}
