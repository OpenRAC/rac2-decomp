#include "include_asm.h"

#include "common.h"
typedef int LiftQuad __attribute__((mode(TI)));
extern u8 *D_L12_001B2F8C MACRO_ADDR;
typedef struct {
    u8 pad[0x80]; f32 position[4];
    u8 pad90[0x33c - 0x90]; u8 *standing; s32 flags;
} LiftPlayer;
extern LiftPlayer D_00189E20;
extern int D_00138324 NOT_SDA;
typedef struct { u8 pad[0x74]; u8 active; u8 pad75[0x13]; u8 *owner; } LiftSound;
extern u8 D_00188660[];
extern void func_002A7750(u8 *object, int animation, int frame);
extern int func_002B38B8(u8 *object);
extern float func_00282C48(float x);
extern int func_002B0C28(int channel, int message, int mode);
extern float func_00282E80(void *a, void *b);
extern int func_002ACBC8(void *point, int index);
extern float func_002AA548(float *value, float *velocity, float target, float minimum, float acceleration, float maximum);
extern void func_002E59F8(int index);
extern int func_002E5CF8(int index, int kind, char *object);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_002AD6F0(void *matrix, void *offset, void *a, void *b);

void func_US2_L12_0041FE80(u8 *object)
{
    LiftQuad oldPosition;
    LiftQuad displacement;
    u8 *data = *(u8 **)(object + 0x68);

    float target;
    float rate;
    float reference;
    int index;
    qcopy(&oldPosition, object + 0x10);
    switch (object[0x20]) {
    case 0:
        qcopy(data + 0x70, object + 0x10);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (!func_002B38B8(object)) break;
        if (*(int *)(data + 0x68))
            target = *(float *)(D_L12_001B2F8C + *(int *)(data + 0x60) * 128 + 0x38);
        else
            target = *(float *)(data + 0x78);
        if (func_00282C48(target - *(float *)(object + 0x18)) < 2.0f) {
            reference = *(float *)(D_L12_001B2F8C + *(int *)(data + 0x60) * 128 + 0x38);
            if (D_00189E20.standing == object && D_00189E20.flags) {
                func_002B0C28(8, 0x12EC, 1);
                if (D_00138324 & 0x10)
                    *(int *)(data + 0x68) = (*(int *)(data + 0x68) + 1) & 1;
            } else if (*(int *)(data + 0x68)) {
                if (func_00282C48(D_00189E20.position[2] - *(float *)(data + 0x78)) < 4.0f &&
                    func_00282E80(D_00189E20.position, object + 0x10) < 24.0f)
                    *(int *)(data + 0x68) = 0;
            } else {
                if (func_00282C48(D_00189E20.position[2] - reference) < 4.0f &&
                    func_00282E80(D_00189E20.position, object + 0x10) < 24.0f)
                    *(int *)(data + 0x68) = 1;
            }
        }
        rate = 0.003888888983055949f;
        if (*(int *)(data + 0x68)) {
            if (D_00189E20.position[2] < *(float *)(object + 0x18) - 1.0f &&
                func_002ACBC8(D_00189E20.position, *(int *)(data + 0x60))) {
                target += 3.0f;
                rate = 0.007777777966111898f;
            } else {
                target += 0.5f;
            }
        }
        func_002AA548((float *)(object + 0x18), (float *)(data + 0x6c), target, 0.0019444444915279746f, rate, 0.5f);
        if (func_00282C48(target - *(float *)(object + 0x18)) < 0.8f) {
            index = *(int *)(data + 0x80);
            if (index != -1) {
                LiftSound *sound = (LiftSound *)(index * 112 + (s32)D_00188660);
                if (sound->owner == object && sound->active)
                    func_002E59F8(index);
            }
            *(int *)(data + 0x80) = -1;
        } else {
            LiftSound *sound = (LiftSound *)(*(int *)(data + 0x80) * 112 + (s32)D_00188660);
            if (sound->owner != object || sound->active == 0)
                *(int *)(data + 0x80) = func_002E5CF8(0, 4, (char *)object);
        }
    }
    func_00282CF0(&displacement, object + 0x10, &oldPosition);
    func_002AD6F0(data + 0x20, &displacement, object + 0xf0, object + 0xf0);
}
