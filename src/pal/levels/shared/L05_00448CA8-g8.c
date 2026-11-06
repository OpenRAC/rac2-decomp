/* func_PAL_L05_00448CA8, the PAL copy of func_L05_00442A58: the same C, where the roll and combo
   timers scale to 50 Hz (the tunables are read as ints) and rollInverse is stored before rollDelay. */
#include "include_asm.h"
#include "common.h"

/* The steering input reader. The controller block's analog stick and button words are read
   through the plain symbol (lui/addiu), its small tunables through $gp, so the unit is -G8.
   -frac2-zero-ti-por gives the quadword zero of the axis vector (por + sq) and
   -frac2-hazard-labels keeps the deadzone division's join label on its mtc1 hazard nop. */

typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct {
    char pad0[0x108];
    float stickX, stickY;
    char pad110[0x90];
    union {
        long buttons;
        struct { int held, pressed; } words;
    } input;
} ShipPad;

/* At the camera state's +0x50. */
typedef struct {
    float yawParams[3], pitchParams[3];
    char pad18[6];
    unsigned char mode, changed;
    char pad20[0x34];
    float pitchVelocity, yawVelocity;
    char pad5c[8];
    float pitch, yaw;
    char pad6c[8];
    float pitchLimit, yawLimit;
} InputMode;

typedef struct {
    char pad0[0x40];
    float value, velocity;
} SteeringRecord;

/* At the camera state's +0xD4. */
typedef struct {
    char pad0[4];
    s16 rollDirection, rollTimer;
    float rollInverse;
    s16 rollDelay, comboTimer, comboDelay;
    char pad12[2];
    float comboInverse;
} RollState;

extern ShipPad D_00138180;
extern int D_001A79F0;
extern unsigned char D_001A7A44;
extern float D_L05_001B1A68 __attribute__((sda));
extern float D_L05_001B1A40 __attribute__((sda));
extern float D_L05_001B1A44 __attribute__((sda));
extern float D_L05_001B1A48 __attribute__((sda));
extern float D_L05_001B1B74 __attribute__((sda));
extern float D_L05_001B1B78 __attribute__((sda));
extern float D_L05_001B1B7C __attribute__((sda));
extern int D_L05_001B1AE8 __attribute__((sda));
extern int D_L05_001B1AEC __attribute__((sda));
extern int D_L05_001B1AF0 __attribute__((sda));
extern int D_L05_001B1AF4 __attribute__((sda));
extern int D_L05_001B1B20 __attribute__((sda));
extern int D_L05_002A18E0 __attribute__((nosda));
extern void func_L05_00442880(char *);
extern float func_00282C48(float);
extern int func_L05_00379F38(void);
extern int func_L05_004459B0(char *);
extern float func_00282DB0(void *, char *);
extern int func_PAL_L05_00449258(char *);
extern float func_002702C8(float *, float, float, float, float, float);
extern int func_00282978(short *);
extern float func_00283CE0(int);

void func_PAL_L05_00448CA8(char *obj, float *yawRate, float *pitchRate)
{
    float axis[4] __attribute__((aligned(16)));
    InputMode *state = (InputMode *)(*(char **)(obj + 0x70) + 0x50);
    float vertical, horizontal;
    RollState *roll;

    func_L05_00442880(obj);
    horizontal = -D_00138180.stickX;
    vertical = D_00138180.stickY;
    if (func_00282C48(vertical) < D_L05_001B1A68) {
        if (vertical == 0.0f) {
            if (D_00138180.input.words.held & 0x1000) {
                vertical = -D_L05_001B1B78;
                D_L05_001B1B78 += D_L05_001B1B7C;
                if (D_L05_001B1B78 > 1.0f) D_L05_001B1B78 = 1.0f;
            } else if (D_00138180.input.words.held & 0x4000) {
                vertical = D_L05_001B1B78;
                D_L05_001B1B78 += D_L05_001B1B7C;
                if (D_L05_001B1B78 > 1.0f) D_L05_001B1B78 = 1.0f;
            } else {
                D_L05_001B1B78 = 0.0f;
            }
        } else {
            vertical = 0.0f;
            D_L05_001B1B78 = vertical;
        }
    } else {
        D_L05_001B1B78 = 0.0f;
        if (vertical > 0.0f)
            vertical = (vertical - D_L05_001B1A68) / (1.0f - D_L05_001B1A68);
        else
            vertical = (vertical + D_L05_001B1A68) / (1.0f - D_L05_001B1A68);
    }
    if (horizontal == 0.0f) {
        if (D_00138180.input.words.held & 0x8000) {
            horizontal = D_L05_001B1B74;
            D_L05_001B1B74 += D_L05_001B1B7C;
            if (D_L05_001B1B74 > 1.0f) D_L05_001B1B74 = 1.0f;
        } else if (D_00138180.input.words.held & 0x2000) {
            horizontal = -D_L05_001B1B74;
            D_L05_001B1B74 += D_L05_001B1B7C;
            if (D_L05_001B1B74 > 1.0f) D_L05_001B1B74 = 1.0f;
        } else {
            D_L05_001B1B74 = 0.0f;
        }
    } else {
        D_L05_001B1B74 = 0.0f;
    }
    if ((D_001A79F0 != 5 && D_001A79F0 != 10) || !func_L05_00379F38()) {
        if (horizontal < 0.0f) horizontal = -(horizontal * horizontal);
        else horizontal = horizontal * horizontal;
        if (vertical < 0.0f) vertical = -(vertical * vertical);
        else vertical = vertical * vertical;
    }
    if (state->mode == 0 && (horizontal != 0.0f || vertical != 0.0f)) {
        state->changed = 0;
        state->mode = 1;
    } else if (state->mode == 1) {
        state->changed = 0;
    }
    *(Quad *)axis = 0;
    axis[3] = axis[2] = 1.0f;
    if (state->mode < 2 && ((D_00138180.input.words.pressed & 3) || func_L05_004459B0(obj))) {
        if (func_00282C48(func_00282DB0(axis, obj)) < 0.7f)
            state->mode = 2;
    }
    if (func_PAL_L05_00449258(obj)) {
        *pitchRate = (*yawRate = 0.0f);
    }
    *pitchRate = (-vertical * 0.017453294f) * state->pitchLimit;
    *yawRate = (horizontal * 0.017453294f) * state->yawLimit;
    state->pitch = func_002702C8(&state->pitchVelocity, state->pitch, *pitchRate,
                                 state->pitchParams[0], state->pitchParams[1], state->pitchParams[2]);
    state->yaw = func_002702C8(&state->yawVelocity, state->yaw, *yawRate,
                               state->yawParams[0], state->yawParams[1], state->yawParams[2]);
    {
        SteeringRecord *record = *(SteeringRecord **)(obj + 0x70);
        record->value = func_002702C8(&record->velocity, record->value, vertical,
                                      D_L05_001B1A40, D_L05_001B1A44, D_L05_001B1A48);
    }
    *pitchRate = state->pitch;
    *yawRate = state->yaw;
    roll = (RollState *)(*(char **)(obj + 0x70) + 0xD4);
    if (roll->rollTimer && func_00282978(&roll->rollTimer))
        roll->rollDirection = 0;
    if (roll->rollDelay == 0) {
        if (D_00138180.input.buttons & 0xC) {
            roll->rollTimer = ((s32)(D_L05_001B1AE8) * 5 + 2) / 6;
            roll->rollInverse = 1.0f / func_00283CE0(roll->rollTimer);
            roll->rollDelay = roll->rollTimer + ((s32)(D_L05_001B1AEC) * 5 + 2) / 6;
            if (D_00138180.input.words.held & 4) roll->rollDirection = -1;
            else roll->rollDirection = 1;
            if (D_001A7A44) roll->rollDirection = roll->rollDirection == -1 ? 1 : -1;
        }
    } else {
        func_00282978(&roll->rollDelay);
    }
    if (func_00282978(&roll->comboDelay) && D_L05_002A18E0 && D_001A79F0 != 20) {
        if ((D_00138180.input.words.held & 3) == 3 || (D_00138180.input.words.held & 0xC) == 0xC) {
            roll->comboDelay = ((s32)(D_L05_001B1AF4) * 5 + 2) / 6;
            D_L05_001B1B20 = 7;
            roll->comboTimer = ((s32)(D_L05_001B1AF0) * 5 + 2) / 6;
            roll->comboInverse = 1.0f / func_00283CE0(roll->comboTimer);
        }
    }
}
