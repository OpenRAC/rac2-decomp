#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x760];
    int axis[4];
    char pad770[0xad4];
    int mode;
    char pad1248[0x1048];
    char *object;
    char pad2294[0x258];
    short alternate;
} EffectResident;
typedef struct { char pad0[0xc]; short light; short timer; } FlashState;
typedef struct { float color[4]; float position[4]; } LightRecord;
extern EffectResident D_00189E20;
extern LightRecord D_L00_001C6F40[];
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern void func_00291450(int);
extern int func_00282978(void *);

/* Drives a short light flash from a countdown timer: while the timer is 13 or more the
   intensity ramps up as (15 - timer) / 3, below that it fades as timer / 12 (the three
   colour channels take 1, 0.8 and 0.5 of it). The light is placed at the origin plus 0.3
   of the vector at +0xE0 of the resident block's object and 1.75 of an axis (the negated
   +0xD0 vector of the object, or the resident axis); it is created once, then its record
   is updated. When the timer has run out, or the resident mode is 3, the light is
   released. Each branch keeps its own reciprocal, which is what lets 1.0f share the
   reciprocal's register. */
void func_PAL_L00_00414F80(char *object, void *origin)
{
    float position[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float scale[4] __attribute__((aligned(16)));
    FlashState *state;
    float *axis;
    int disabled = D_00189E20.mode == 3;
    float a, b, c;

    state = *(FlashState **)(object + 0x68);
    if (!disabled && state->timer > 0) {
        if (state->timer >= 11) {
            float inverse = 1.0f / func_00283CE0(2);
            a = func_00283CE0(12 - state->timer) * inverse;
            b = func_00283CE0(12 - state->timer) * (inverse * 0.8f);
            c = func_00283CE0(12 - state->timer) * (inverse * 0.5f);
        } else {
            float inverse = 1.0f / func_00283CE0(10);
            a = func_00283CE0(state->timer) * inverse;
            b = func_00283CE0(state->timer) * (inverse * 0.8f);
            c = func_00283CE0(state->timer) * (inverse * 0.5f);
        }
        if (D_00189E20.alternate) {
            func_00282D30(direction, object + 0xd0, -1.0f);
            qcopy(position, origin);
            axis = direction;
        } else {
            qcopy(direction, D_00189E20.axis);
            qcopy(position, origin);
            axis = direction;
        }
        func_00282D30(offset, D_00189E20.object + 0xe0, 0.3f);
        func_00282CC0(position, position, offset);
        func_00282D30(scale, axis, 1.75f);
        func_00282CC0(position, position, scale);
        if (state->light == -1) {
            state->light = func_L00_002FCF18(position, 14.0f, 0.0f, a, b, c);
        } else {
            LightRecord *light = &D_L00_001C6F40[state->light];
            qcopy(light->position, position);
            light->position[3] = 14.0f;
            light->color[0] = a;
            light->color[1] = b;
            light->color[2] = c;
        }
        func_00282978(&state->timer);
    } else if (state->light != -1) {
        func_00291450(state->light);
        state->light = -1;
        state->timer = 0;
    }
    if (disabled) {
        if (state->light != -1) {
            func_00291450(state->light);
            state->light = -1;
        }
        state->timer = 0;
    }
}
