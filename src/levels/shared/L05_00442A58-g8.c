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

extern ShipPad g_pad_state;
extern int g_current_map_index;
extern unsigned char D_001A7A44;
extern float D_L05_001B1A68 __attribute__((sda));
extern float D_L05_001B1A40 __attribute__((sda));
extern float D_L05_001B1A44 __attribute__((sda));
extern float D_L05_001B1A48 __attribute__((sda));
extern float D_L05_001B1B74 __attribute__((sda));
extern float D_L05_001B1B78 __attribute__((sda));
extern float D_L05_001B1B7C __attribute__((sda));
extern short D_L05_001B1AE8 __attribute__((sda));
extern short D_L05_001B1AEC __attribute__((sda));
extern short D_L05_001B1AF0 __attribute__((sda));
extern short D_L05_001B1AF4 __attribute__((sda));
extern int g_ship_state __attribute__((sda));
extern int D_L05_002A18E0 __attribute__((nosda));
extern void cam_load_parameter_set(char *);
extern float math_fabs(float);
extern int hero_get_state_value_b(void);
extern int path_is_touching_linked_point(char *);
extern float FastVecDot(void *, char *);
extern int ship_update_turn_animation(char *);
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
extern int FastDecTimer(short *);
extern float IntToFloat(int);

/* Reads the controller and turns the stick and buttons into ship turning, tilting and barrel rolls. */
void UpdateSteeringInput(char *obj, float *yawRate, float *pitchRate)
{
    float axis[4] __attribute__((aligned(16)));
    InputMode *state = (InputMode *)(*(char **)(obj + 0x70) + 0x50);
    float vertical, horizontal;
    RollState *roll;

    cam_load_parameter_set(obj);
    horizontal = -g_pad_state.stickX;
    vertical = g_pad_state.stickY;
    if (math_fabs(vertical) < D_L05_001B1A68) {
        if (vertical == 0.0f) {
            if (g_pad_state.input.words.held & 0x1000) {
                vertical = -D_L05_001B1B78;
                D_L05_001B1B78 += D_L05_001B1B7C;
                if (D_L05_001B1B78 > 1.0f) D_L05_001B1B78 = 1.0f;
            } else if (g_pad_state.input.words.held & 0x4000) {
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
        if (g_pad_state.input.words.held & 0x8000) {
            horizontal = D_L05_001B1B74;
            D_L05_001B1B74 += D_L05_001B1B7C;
            if (D_L05_001B1B74 > 1.0f) D_L05_001B1B74 = 1.0f;
        } else if (g_pad_state.input.words.held & 0x2000) {
            horizontal = -D_L05_001B1B74;
            D_L05_001B1B74 += D_L05_001B1B7C;
            if (D_L05_001B1B74 > 1.0f) D_L05_001B1B74 = 1.0f;
        } else {
            D_L05_001B1B74 = 0.0f;
        }
    } else {
        D_L05_001B1B74 = 0.0f;
    }
    if ((g_current_map_index != 5 && g_current_map_index != 10) || !hero_get_state_value_b()) {
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
    if (state->mode < 2 && ((g_pad_state.input.words.pressed & 3) || path_is_touching_linked_point(obj))) {
        if (math_fabs(FastVecDot(axis, obj)) < 0.7f)
            state->mode = 2;
    }
    if (ship_update_turn_animation(obj)) {
        *pitchRate = (*yawRate = 0.0f);
    }
    *pitchRate = (-vertical * 0.017453294f) * state->pitchLimit;
    *yawRate = (horizontal * 0.017453294f) * state->yawLimit;
    state->pitch = math_step_spring_damper_clamped(&state->pitchVelocity, state->pitch, *pitchRate,
                                 state->pitchParams[0], state->pitchParams[1], state->pitchParams[2]);
    state->yaw = math_step_spring_damper_clamped(&state->yawVelocity, state->yaw, *yawRate,
                               state->yawParams[0], state->yawParams[1], state->yawParams[2]);
    {
        SteeringRecord *record = *(SteeringRecord **)(obj + 0x70);
        record->value = math_step_spring_damper_clamped(&record->velocity, record->value, vertical,
                                      D_L05_001B1A40, D_L05_001B1A44, D_L05_001B1A48);
    }
    *pitchRate = state->pitch;
    *yawRate = state->yaw;
    roll = (RollState *)(*(char **)(obj + 0x70) + 0xD4);
    if (roll->rollTimer && FastDecTimer(&roll->rollTimer))
        roll->rollDirection = 0;
    if (roll->rollDelay == 0) {
        if (g_pad_state.input.buttons & 0xC) {
            roll->rollTimer = D_L05_001B1AE8;
            {
                float inverse = 1.0f / IntToFloat(roll->rollTimer);
                roll->rollDelay = roll->rollTimer + D_L05_001B1AEC;
                roll->rollInverse = inverse;
            }
            if (g_pad_state.input.words.held & 4) roll->rollDirection = -1;
            else roll->rollDirection = 1;
            if (D_001A7A44) roll->rollDirection = roll->rollDirection == -1 ? 1 : -1;
        }
    } else {
        FastDecTimer(&roll->rollDelay);
    }
    if (FastDecTimer(&roll->comboDelay) && D_L05_002A18E0 && g_current_map_index != 20) {
        if ((g_pad_state.input.words.held & 3) == 3 || (g_pad_state.input.words.held & 0xC) == 0xC) {
            unsigned short duration = D_L05_001B1AF0;
            roll->comboDelay = D_L05_001B1AF4;
            g_ship_state = 7;
            roll->comboTimer = duration;
            roll->comboInverse = 1.0f / IntToFloat((short)duration);
        }
    }
}
