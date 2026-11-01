#include "include_asm.h"

#include "common.h"
extern void func_00274208(void *);
extern int func_002746C8(void *);
extern void func_00282F20(float, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_PAL_00274928(void *, void *, void *);
extern void func_002AFFD8(void *, void *, int);
extern float func_00282DB0(void *, void *);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_002AA2E8(float *, float, float);
extern void func_002ACE78(void *, void *, float);
extern void func_00283810(void *, void *, void *, float);
extern int func_002E5CF8(int, int, void *);
extern int func_002E5E58(int, int, void *);
extern int func_002E5F00(int, char *);
extern void func_00283028(void *, void *, void *);
extern float D_001BAFC0[];

int func_PAL_00273D38(char *object)
{
    float delta[4];
    float direction[4];
    float scaled[4];
    float correction[4];
    float length;
    char *state = *(char **)(object + 0x68);
    char *orientation;
    float distance, step, factor;
    int sound;

    func_00274208(object);
    if (func_002746C8(object)) {
        orientation = state + 0x10;
        func_00282F20(1.0f, D_001BAFC0, D_001BAFC0);
        func_00282DD8(delta, D_001BAFC0, state);
        func_PAL_00274928(object, orientation, delta);
        func_002AFFD8(object + 0x10, direction, 1);
        if (func_00282DB0(direction, D_001BAFC0) > 0.7f) {
            distance = func_00282DB0(state, D_001BAFC0);
            step = distance * 0.5f;
            if (func_00282C48(step) < 0.040000003f)
                step = 0.0f;
            func_00282F20(distance + step, scaled, D_001BAFC0);
            func_00282CF0(state, state, scaled);
            if (step == 0.0f) {
                length = func_00282DF0(state);
                func_002AA2E8(&length, 0.040000003f, 0.0028000001f);
                func_00282F20(length, state, state);
                func_00282DD8(correction, state, D_001BAFC0);
                factor = func_00282DF0(correction) * -0.5f;
                factor /= *(float *)(state + 0x2C);
                func_002ACE78(correction, correction, factor);
                func_00283810(orientation, orientation, correction, 0.1f);
            }
            if (func_00282C48(distance) >= 0.040000003f) {
                if (*(u8 *)(state + 0x5E) != 0xFF)
                    sound = func_002E5CF8(*(u8 *)(state + 0x5E), 0, object);
                else
                    sound = func_002E5E58(8, 0, object);
                if (sound != -1)
                    func_002E5F00(sound, state + 0x20);
            }
        } else {
            func_00283028(state, state, D_001BAFC0);
        }
    }
    return 0;
}
