/* func_PAL_L08_003DD458, the PAL copy of func_L08_003D92D8: the same C, where 240 becomes 200;
   0.0017453294713050127f becomes 0.0025132746f; 0.10471977293491364f becomes 0.12566373f; 0.02f
   becomes 0.028800001f; 0.4f becomes 0.57600003f. */
#include "common.h"

extern u8 D_L08_001B9B00[];
extern f32 func_00282E48(void *, void *);

extern void func_0029FCC0(void *, int, void *);

typedef struct {
    u8 pad00[0x20];
    u8 f20;
    u8 f21;
    u8 pad22[0x24 - 0x22];
    void *f24;
    u8 pad28[0x2C - 0x28];
    f32 f2C;
    u8 pad30[0x68 - 0x30];
    void *f68;
    u8 pad6C[0x95 - 0x6C];
    u8 f95;
    u16 f96;
    u8 pad98[0xBC - 0x98];
    u8 fBC;
    u8 padBD[0x100 - 0xBD];
} Ent;

typedef int V4 __attribute__((mode(TI)));

extern s32 func_3357E8(Ent *, void *, s32);
extern void func_2FA0B8(void *, void *, f32);

extern float func_00282E80(void *, void *);

typedef struct {
    int mode;
    char pad4[8];
    int active;
    char pad10[0x18];
    float lower;
    char pad2C[12];
    float upper;
} HeightGate;
typedef struct {
    u8 pad0[0x80];
    V4 position;
    u8 pad90[0x40];
    V4 other;
    u8 padE0[0x21B0];
    int handle;
} HeroTarget;
extern HeroTarget D_00189E20;
extern HeightGate D_L08_001CA080;
extern char D_L08_001BFF80[];
extern int func_00278E78(void);
extern void func_002A93B0(void *);
extern void func_L08_003D82F0(void *);
extern void func_00283410(void *, void *);
extern void func_00283698(void *, void *);
extern float func_002A89A8(void *, int, float);
extern float func_00283248(float, float);
extern float func_002AAA00(void *, void *, float, float, float, float, int);
extern float func_00283BE0(float, float);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_00283098(void *, void *, void *);

extern void func_L08_003D8A28(Ent *a0);
void func_PAL_L08_003DD458(u8 *object)
{
    float point[4], angles[4], matrix[16], inverse[16], other[16];
    char *state = *(char **)(object + 0x68);
    float yaw, pitch, target;
    float pointX, pointY;
    float *pitchAngle, *rollAngle;
    int hit;

    if (D_L08_001CA080.active) {
        if (*(float *)(object + 0x18) < D_L08_001CA080.lower && D_L08_001CA080.mode == 1) return;
        if (D_L08_001CA080.lower < *(float *)(object + 0x18) && D_L08_001CA080.mode == 0) return;
        if (D_L08_001CA080.active == 2) {
            if (D_L08_001CA080.upper < *(float *)(object + 0x18) && D_L08_001CA080.mode == 1) return;
            if (*(float *)(object + 0x18) < D_L08_001CA080.upper && D_L08_001CA080.mode == 2) return;
        }
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L08_001B9B00) < 24.0f) {
        func_002A93B0(object);
        object[0x6F] = 22;
    }
    func_L08_003D82F0(object);
    if (*(float *)(object + 0x18) < *(float *)(state + 0x434) + 0.12f) {
        if (func_00278E78() == 1 || func_00278E78() == 11) {
            *(int *)(state + 0x20) = 0;
            object[0x20] = 11;
            return;
        }
    }
    *(float *)(object + 0x2C) +=
        (*(float *)(*(char **)(object + 0x24) + 0x24) * 1.7f - *(float *)(object + 0x2C)) * 0.05f;
    hit = func_3357E8((Ent *)object, state + 0x50, 0);
    if (hit) {
        if (hit == 5) *(int *)(state + 0xE0) = 0;
        *(int *)(state + 0x48C) = 200;
        func_L08_003D8A28((Ent *)object);
    }
    if (object[0x20] < 9 && object[0x20] != 4) {
        pitchAngle = (float *)(object + 0xF4);
        rollAngle = (float *)(object + 0xF0);
        *(V4 *)angles = 0;
        angles[2] = *(float *)(object + 0xF8);
        *(V4 *)point = *(V4 *)angles;
        func_00283410(matrix, point);
        func_00283698(inverse, matrix);
        func_00283698(other, object + 0xC0);
        func_002A89A8(object + 0x10, 0, 0.5f);
        func_2FA0B8(angles, D_L08_001BFF80, 1.0f);
        func_00283098(angles, angles, inverse);
        target = func_00283248(angles[2], angles[0]);
        func_002AAA00(pitchAngle, state + 0x460, target, 0.0025132746f,
                      0.0025132746f, 0.12566373f, 0);
        target = -func_00283248(angles[2], angles[1]);
        func_002AAA00(rollAngle, state + 0x464, target, 0.0025132746f,
                      0.0025132746f, 0.12566373f, 0);
    }
    if (object[0x20] == 8 && !object[0x95]) {
        func_0029FCC0(object, 1, point);
        if (*(int *)(state + 0x250) == D_00189E20.handle) {
            qcopy(state + 0x210, &D_00189E20.position);
            qcopy(state + 0x230, &D_00189E20.other);
        }
        pointY = point[1];
        pointX = point[0];
        yaw = func_00283248(*(float *)(state + 0x230) - pointX, *(float *)(state + 0x234) - pointY);
        pitch = func_00283248(func_00282E80(point, state + 0x230), *(float *)(state + 0x238) - point[2]);
        yaw = func_00283BE0(yaw, *(float *)(object + 0xF8)) * 0.5f;
        pitch = func_00283BE0(-pitch, *(float *)(object + 0xF4)) * 0.3333333432674408f;
        {
            int i;
            for (i = 0; i < 3; i++) {
                *(float *)(state + 0x2C8 + i * 0x80) = yaw;
                if (yaw > 0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = 0.523598849773407f;
                else if (yaw < -0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = -0.523598849773407f;
                *(float *)(state + 0x2C4 + i * 0x80) = pitch;
            }
        }
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            *(float *)(state + 0x2C0 + i * 0x80) = 0;
            *(float *)(state + 0x2C4 + i * 0x80) = 0;
        }
    }
    {
        int i;
        for (i = 0; i < 3; i++) func_002AEC48(object, state + 0x260 + i * 0x80, 3, 0.028800001f, 0.57600003f);
    }
}
