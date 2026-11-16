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

extern ShipPad g_pad_state;
extern int g_current_map_index;
extern unsigned char g_cheat_flags;
extern float g_ship_stick_deadzone __attribute__((sda));
extern float g_ship_roll_vec_x __attribute__((sda));
extern float g_ship_roll_vec_y __attribute__((sda));
extern float g_ship_roll_vec_z __attribute__((sda));
extern float g_ship_horizontal_input_ramp __attribute__((sda));
extern float g_ship_vertical_input_ramp __attribute__((sda));
extern float g_ship_input_ramp_step __attribute__((sda));
extern int g_ship_roll_timer_value __attribute__((sda));
extern int g_ship_roll_delay_offset __attribute__((sda));
extern int g_ship_roll_duration __attribute__((sda));
extern int g_ship_combo_delay __attribute__((sda));
extern int g_ship_state __attribute__((sda));
extern int g_ship_combo_enabled __attribute__((nosda));
extern void cam_load_parameter_set(char *);
extern float math_fabs(float);
extern int hero_get_state_value_b(void);
extern int path_is_touching_linked_point(char *);
extern float FastVecDot(void *, char *);
extern int func_PAL_L05_00449258(char *);
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
extern int FastDecTimer(short *);
extern float IntToFloat(int);

void func_PAL_L05_00448CA8(char *obj, float *yawRate, float *pitchRate)
{
    float axis[4] __attribute__((aligned(16)));
    InputMode *state = (InputMode *)(*(char **)(obj + 0x70) + 0x50);
    float vertical, horizontal;
    RollState *roll;

    cam_load_parameter_set(obj);
    horizontal = -g_pad_state.stickX;
    vertical = g_pad_state.stickY;
    if (math_fabs(vertical) < g_ship_stick_deadzone) {
        if (vertical == 0.0f) {
            if (g_pad_state.input.words.held & 0x1000) {
                vertical = -g_ship_vertical_input_ramp;
                g_ship_vertical_input_ramp += g_ship_input_ramp_step;
                if (g_ship_vertical_input_ramp > 1.0f) g_ship_vertical_input_ramp = 1.0f;
            } else if (g_pad_state.input.words.held & 0x4000) {
                vertical = g_ship_vertical_input_ramp;
                g_ship_vertical_input_ramp += g_ship_input_ramp_step;
                if (g_ship_vertical_input_ramp > 1.0f) g_ship_vertical_input_ramp = 1.0f;
            } else {
                g_ship_vertical_input_ramp = 0.0f;
            }
        } else {
            vertical = 0.0f;
            g_ship_vertical_input_ramp = vertical;
        }
    } else {
        g_ship_vertical_input_ramp = 0.0f;
        if (vertical > 0.0f)
            vertical = (vertical - g_ship_stick_deadzone) / (1.0f - g_ship_stick_deadzone);
        else
            vertical = (vertical + g_ship_stick_deadzone) / (1.0f - g_ship_stick_deadzone);
    }
    if (horizontal == 0.0f) {
        if (g_pad_state.input.words.held & 0x8000) {
            horizontal = g_ship_horizontal_input_ramp;
            g_ship_horizontal_input_ramp += g_ship_input_ramp_step;
            if (g_ship_horizontal_input_ramp > 1.0f) g_ship_horizontal_input_ramp = 1.0f;
        } else if (g_pad_state.input.words.held & 0x2000) {
            horizontal = -g_ship_horizontal_input_ramp;
            g_ship_horizontal_input_ramp += g_ship_input_ramp_step;
            if (g_ship_horizontal_input_ramp > 1.0f) g_ship_horizontal_input_ramp = 1.0f;
        } else {
            g_ship_horizontal_input_ramp = 0.0f;
        }
    } else {
        g_ship_horizontal_input_ramp = 0.0f;
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
    if (func_PAL_L05_00449258(obj)) {
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
                                      g_ship_roll_vec_x, g_ship_roll_vec_y, g_ship_roll_vec_z);
    }
    *pitchRate = state->pitch;
    *yawRate = state->yaw;
    roll = (RollState *)(*(char **)(obj + 0x70) + 0xD4);
    if (roll->rollTimer && FastDecTimer(&roll->rollTimer))
        roll->rollDirection = 0;
    if (roll->rollDelay == 0) {
        if (g_pad_state.input.buttons & 0xC) {
            roll->rollTimer = ((s32)(g_ship_roll_timer_value) * 5 + 2) / 6;
            roll->rollInverse = 1.0f / IntToFloat(roll->rollTimer);
            roll->rollDelay = roll->rollTimer + ((s32)(g_ship_roll_delay_offset) * 5 + 2) / 6;
            if (g_pad_state.input.words.held & 4) roll->rollDirection = -1;
            else roll->rollDirection = 1;
            if (g_cheat_flags) roll->rollDirection = roll->rollDirection == -1 ? 1 : -1;
        }
    } else {
        FastDecTimer(&roll->rollDelay);
    }
    if (FastDecTimer(&roll->comboDelay) && g_ship_combo_enabled && g_current_map_index != 20) {
        if ((g_pad_state.input.words.held & 3) == 3 || (g_pad_state.input.words.held & 0xC) == 0xC) {
            roll->comboDelay = ((s32)(g_ship_combo_delay) * 5 + 2) / 6;
            g_ship_state = 7;
            roll->comboTimer = ((s32)(g_ship_roll_duration) * 5 + 2) / 6;
            roll->comboInverse = 1.0f / IntToFloat(roll->comboTimer);
        }
    }
}
