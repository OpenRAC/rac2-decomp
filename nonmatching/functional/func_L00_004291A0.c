/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol high effort; retained reconstruction, not linked or counted.
 * USA v1.01: 964/964 bytes, 0/11 places; first difference +0xC.
 * Profile: -O2 -G0 -ffunction-sections -fno-strength-reduce, in its own unit.
 * Typed partial global records restore retail's full base materializations.
 * Separate loop indices/path pointers, byte offsets retained across distance
 * calls, and a captured node weight recover the 0x90 frame and second-loop operation order.
 * Remaining: first-loop offset/cursor allocation (s3/s4/s5), index/count
 * spill slots and increment scheduling, and initial -1/7 materialization order.
 * Moving the first offset among block/function scope, spelling its first load
 * with a separate i*16, and a guarded do-loop did not close these differences.
 * A typed path-node array worsened size to 980. Early count initialization
 * was 956. Reopen with independent first-loop offset/count lifetime evidence.
 * Declarations required by the draft are included below. No full build run.
 */

#include "common.h"
typedef int InitQuad __attribute__((mode(TI)));
extern u8 *D_L00_001B1844 __attribute__((section(".sdata")));
typedef struct { u8 pad[0xB0]; float scale; } PathView;
extern PathView D_L00_001BD2C0;
extern u8 *D_L00_001FDA80[];
typedef struct { u8 pad[0x194]; InitQuad *transform; } PathCamera;
extern PathCamera D_L00_001B8C80;
extern float func_00283248(float x, float y);
extern float func_00282E48(float *a, float *b);
extern float func_00283CE0(int x);
extern void func_00282C88(InitQuad *v);
extern int func_L00_002C42E0(int event, int value);

/* Partial records follow only the fields used by the two path walks.
 * Retail reserves eight weight/index slots and assumes at most eight accepted
 * entries; it does not add a bounds check to the path scan. */
typedef struct {
    u8 unknown00[0x20];
    int pathIndex;
    int secondPathIndex;
    u8 unknown28[0x10];
    u8 active;
    u8 unknown39;
    short duration;
    float speed;
    u8 unknown40[0xC];
    int eventGate;
    int initialized;
    u8 unknown54[0xC];
    float weights[8];
    int indices[8];
} PathConfig;
typedef struct {
    int first;
    int second;
    float distance;
    float secondDistance;
    int current;
    short node;
    short duration;
} MotionPrefix;

void func_L00_004291A0(u8 *object)
{
    PathConfig *data = *(PathConfig **)(D_L00_001B1844 + *(short *)(object + 0x84) * 32 + 0x1c);
    MotionPrefix *motion;
    u8 *pathState;
    float *weightBase = data->weights;
    int *indices = data->indices;
    int accepted;
    int *reset;
    float distance;
    InitQuad *transform;
    data->active = 1;
    motion = (MotionPrefix *)(*(u8 **)(object + 0x70) + 0x40);
    motion->first = 0;
    motion->second = 0;
    motion->distance = 0;
    motion->secondDistance = 0;
    motion->current = 0;
    motion->node = 0;
    motion->duration = data->duration;
    pathState = *(u8 **)(object + 0x70) + 0x58;
    reset = data->indices;
    { int i;
    for (i = 7; i >= 0; i--) {
        *(float *)((u8 *)reset - 0x20) = 0.0f;
        *reset++ = -1;
    }
    }
    accepted = 0;
    *(float *)(pathState + 0x30) = func_00283248(1.0f, D_L00_001BD2C0.scale) * 2.0f;
    if (data->initialized == 0 && data->pathIndex >= 0) {
        int i;
        float *weightCursor = weightBase;
        u8 *path = D_L00_001FDA80[data->pathIndex];
        for (i = 0; i < *(int *)path; i++) {
            int byteOffset = i * 16;
            float weight = *(float *)(path + byteOffset + 0x1C);
            if (weight > 0.0f) {
                *weightCursor = weight;
                if (weight > 180.0f)
                    *weightCursor = *(float *)(pathState + 0x30) * 57.2957763671875f;
                weightCursor++;
                indices[accepted] = i;
                accepted++;
            }
            distance = func_00282E48((char *)(path + (byteOffset + 0x10)), (float *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
            *(float *)(path + byteOffset + 0x1C) = distance;
            if (i < *(int *)path - 1)
                motion->distance += distance;
        }
    }
    if (data->duration > 0)
        data->speed = (motion->distance / func_00283CE0(data->duration)) * 60.0f;
    if (data->secondPathIndex >= 0) {
        int i;
        u8 *path = D_L00_001FDA80[data->secondPathIndex];
        for (i = 0; i < *(int *)path; i++) {
            int byteOffset = i * 16;
            distance = func_00282E48((char *)(path + (byteOffset + 0x10)), (float *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
            *(float *)(path + byteOffset + 0x1C) = distance;
            if (i < *(int *)path - 1)
                motion->secondDistance += distance;
        }
    }
    { u8 *saved = *(u8 **)(object + 0x70);
    *(float *)saved = 0.03f;
    *(float *)(saved + 4) = 0.2f;
    func_00282C88((InitQuad *)(saved + 0x10));
    }
    { u8 *saved = *(u8 **)(object + 0x70);
    *(float *)(saved + 0x20) = 0.03f;
    *(float *)(saved + 0x24) = 0.2f;
    func_00282C88((InitQuad *)(saved + 0x30));
    }
    transform = D_L00_001B8C80.transform;
    qcopy(object + 0x30, transform + 3);
    qcopy(object, transform);
    qcopy(object + 0x10, transform + 1);
    qcopy(object + 0x20, transform + 2);
    if (data->eventGate == 0)
        func_L00_002C42E0(0x6f, 1);
    data->initialized = 1;
}
