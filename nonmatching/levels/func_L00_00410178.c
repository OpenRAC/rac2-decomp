/* Complete C near miss; not linked and no matching credit.
 * -O2 -G0 -ffunction-sections -g: 692/692 bytes; USA and USA2 0/27 each,
 * first mismatch +0x74. PAL has no catalogue row. Default without -g is 680
 * bytes: the measured pre-div.s nop floor is missing. Eight bounded trials.
 * Explicit conversion/inversion and in-place blue attenuation recover the
 * retail operation sequence; two reciprocal numerator registers and four
 * independent light-field stores still differ. G8, fine force-mem/speculation
 * controls tie; disabling first scheduling changes the prologue and is rejected.
 * Existing allocator diagnostics reproduce byte-identical objects and record
 * the remaining constant temporaries. No invented references or register pins.
 * Four complete aligned vectors cover every VU/transfer read. The real light
 * record is 32 bytes, and the qualified caller supplies a full nozzle vector.
 * Hero and private-state types are measured field-prefix views, never claimed
 * owner-allocation bounds. Every dependent transfer uses default qcopy.
 * Reopen with grounded reciprocal or field-store lifetime evidence.
 */
#include "common.h"

typedef struct { float v[4]; } __attribute__((aligned(16))) LightVector;
/* Only the known light/timer prefix of the larger BlasterVars allocation. */
typedef struct {
    u8 prefix00[0xC];
    s16 light, flash;
} MuzzleState;
typedef struct {
    u8 prefix00[0x760];
    LightVector forward;
    u8 gap770[0xAD4];
    int mode;
    u8 gap1248[0x1048];
    u8 *weapon;
    u8 gap2294[0x258];
    s16 vehicle;
} HeroPrefix;
typedef struct {
    float red, green, blue, reserved;
    LightVector position;
} MuzzleLight;
extern HeroPrefix D_00189E20;
extern MuzzleLight D_L00_001C6F40[];
extern float func_00283CE0(int);
extern void func_00282D30(void *, const void *, float);
extern void func_00282CC0(void *, const void *, const void *);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern int func_00282978(s16 *);
extern void func_00291450(int);

void func_L00_00410178(u8 *actor, const void *nozzle)
{
    LightVector origin, direction, offset, shift;
    MuzzleState *state = *(MuzzleState **)(actor + 0x68);
    int paused = D_00189E20.mode == 3;
    float red, green, blue, reciprocal;
    LightVector *forward;

    if (!paused && state->flash > 0) {
        if (state->flash >= 13) {
            float sample;
            reciprocal = func_00283CE0(3);
            reciprocal = 1.0f / reciprocal;
            red = func_00283CE0(15 - state->flash) * reciprocal;
            green = func_00283CE0(15 - state->flash) * (reciprocal * 0.8f);
            sample = func_00283CE0(15 - state->flash);
            reciprocal *= 0.5f;
            blue = sample * reciprocal;
        } else {
            float sample;
            reciprocal = func_00283CE0(12);
            reciprocal = 1.0f / reciprocal;
            red = func_00283CE0(state->flash) * reciprocal;
            green = func_00283CE0(state->flash) * (reciprocal * 0.8f);
            sample = func_00283CE0(state->flash);
            reciprocal *= 0.5f;
            blue = sample * reciprocal;
        }
        if (D_00189E20.vehicle != 0) {
            func_00282D30(&direction, actor + 0xD0, -1.0f);
            qcopy(&origin, nozzle);
            forward = &direction;
        } else {
            qcopy(&direction, &D_00189E20.forward);
            qcopy(&origin, nozzle);
            forward = &direction;
        }
        func_00282D30(&offset, D_00189E20.weapon + 0xE0, 0.3f);
        func_00282CC0(&origin, &origin, &offset);
        func_00282D30(&shift, forward, 1.75f);
        func_00282CC0(&origin, &origin, &shift);
        if (state->light == -1) {
            state->light = func_L00_002FCF18(&origin, 14.0f, 0.0f, red, green, blue);
        } else {
            MuzzleLight *light = &D_L00_001C6F40[state->light];
            qcopy(&light->position, &origin);
            light->blue = blue;
            light->position.v[3] = 14.0f;
            light->red = red;
            light->green = green;
        }
        func_00282978(&state->flash);
    } else if (state->light != -1) {
        func_00291450(state->light);
        state->light = -1;
        state->flash = 0;
    }
    if (paused) {
        if (state->light != -1) {
            func_00291450(state->light);
            state->light = -1;
        }
        state->flash = 0;
    }
}
