#include "common.h"

/* func_PAL_L00_0042E68C, the PAL copy of func_L00_004291A0: the same C, with the duration scaled
 * for 50 Hz at both uses and object + 0x30 named early, so it takes its stack slot ahead of gcse's
 * reaching registers. */

typedef int InitQuad __attribute__((mode(TI)));
typedef struct { u8 pad[0xB0]; float scale; } PathView;
extern PathView D_L00_001BD2C0;
extern u8 *D_L00_001FDA80[];
typedef struct { u8 pad[0x194]; InitQuad *transform; } PathCamera;
extern PathCamera D_L00_001B8C80;
extern float func_00283248(float x, float y);
extern void func_00282C88(InitQuad *v);
extern int func_L00_002C42E0(int event, int value);
extern float func_00282E48(char *a, char *b);
extern float func_00283CE0(int);
#define SDA_OBJ __attribute__((section(".sdata")))
extern char *D_L00_001B1844 SDA_OBJ;

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

void func_PAL_L00_0042E68C(u8 *object)
{
    PathConfig *data = *(PathConfig **)(D_L00_001B1844 + *(short *)(object + 0x84) * 32 + 0x1c);
    MotionPrefix *motion;
    u8 *pathState;
    float *weights = data->weights;
    int accepted;
    float distance;
    InitQuad *transform;
    u8 *position;
    data->active = 1;
    motion = (MotionPrefix *)(*(u8 **)(object + 0x70) + 0x40);
    motion->first = 0;
    motion->second = 0;
    motion->distance = 0;
    motion->secondDistance = 0;
    motion->current = 0;
    motion->node = 0;
    motion->duration = ((s32)data->duration * 5 + 2) / 6;
    pathState = *(u8 **)(object + 0x70) + 0x58;
    {
        int i;
        for (i = 0; i < 8; i++) {
            data->weights[i] = 0.0f;
            data->indices[i] = -1;
        }
    }
    accepted = 0;
    position = object + 0x30;
    *(float *)(pathState + 0x30) = func_00283248(1.0f, D_L00_001BD2C0.scale) * 2.0f;
    if (data->initialized == 0 && data->pathIndex >= 0) {
        int i;
        u8 *path = D_L00_001FDA80[data->pathIndex];
        for (i = 0; i < *(int *)path; i++) {
            float weight = *(float *)(path + (i << 4) + 0x1C);
            if (weight > 0.0f) {
                weights[accepted] = weight;
                if (weight > 180.0f)
                    weights[accepted] = *(float *)(pathState + 0x30) * 57.2957763671875f;
                data->indices[accepted] = i;
                accepted++;
            }
            distance = func_00282E48((char *)(path + (i * 16 + 0x10)), (char *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
            *(float *)(path + (i << 4) + 0x1C) = distance;
            if (i < *(int *)path - 1)
                motion->distance += distance;
        }
    }
    if (data->duration > 0)
        data->speed = (motion->distance / func_00283CE0(((s32)data->duration * 5 + 2) / 6)) * 60.0f;
    if (data->secondPathIndex >= 0) {
        int i;
        u8 *path = D_L00_001FDA80[data->secondPathIndex];
        for (i = 0; i < *(int *)path; i++) {
            int byteOffset = i * 16;
            distance = func_00282E48((char *)(path + (byteOffset + 0x10)), (char *)(path + 0x10 + ((i + 1) % *(int *)path) * 16));
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
    qcopy(position, transform + 3);
    qcopy(object, transform);
    qcopy(object + 0x10, transform + 1);
    qcopy(object + 0x20, transform + 2);
    if (data->eventGate == 0)
        func_L00_002C42E0(0x6f, 1);
    data->initialized = 1;
}
