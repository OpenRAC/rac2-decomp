/* func_PAL_L05_00448CA8, the PAL copy of func_L05_00442A58: the same C, where the roll and combo
   timers scale to 50 Hz (the tunables are read as ints) and roll_inverse is stored before roll_delay. */
#include "include_asm.h"
#include "common.h"

/* The steering input reader. The controller block's analog stick and button words are read
   through the plain symbol (lui/addiu), its small tunables through $gp, so the unit is -G8.
   -frac2-zero-ti-por gives the quadword zero of the axis vector (por + sq) and
   -frac2-hazard-labels keeps the deadzone division's join label on its mtc1 hazard nop. */

typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct {
    char pad0[0x108];
    float stick_x, stick_y;
    char pad110[0x90];
    union {
        long buttons;
        struct { int held, pressed; } words;
    } input;
} ShipPad;

/* At the camera state's +0x50. */
typedef struct {
    float yaw_params[3], pitch_params[3];
    char pad18[6];
    unsigned char mode, changed;
    char pad20[0x34];
    float pitch_velocity, yaw_velocity;
    char pad5c[8];
    float pitch, yaw;
    char pad6c[8];
    float pitch_limit, yaw_limit;
} InputMode;

typedef struct {
    char pad0[0x40];
    float value, velocity;
} SteeringRecord;

/* At the camera state's +0xD4. */
typedef struct {
    char pad0[4];
    s16 roll_direction, roll_timer;
    float roll_inverse;
    s16 roll_delay, combo_timer, combo_delay;
    char pad12[2];
    float combo_inverse;
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
extern int ship_update_turn_animation_pal(char *);
extern float math_step_spring_damper_clamped(float *, float, float, float, float, float);
extern int FastDecTimer(short *);
extern float IntToFloat(int);

/* Reads the stick and buttons into pitch and yaw rates for the ship, and handles the barrel roll and double-tap combo timers (PAL: 50 Hz). */
void UpdateSteeringInput_pal(char *obj, float *yaw_rate, float *pitch_rate)
{
    float axis[4] __attribute__((aligned(16)));
    InputMode *state = (InputMode *)(*(char **)(obj + 0x70) + 0x50);
    float vertical, horizontal;
    RollState *roll;

    cam_load_parameter_set(obj);
    horizontal = -g_pad_state.stick_x;
    vertical = g_pad_state.stick_y;
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
    if (ship_update_turn_animation_pal(obj)) {
        *pitch_rate = (*yaw_rate = 0.0f);
    }
    *pitch_rate = (-vertical * 0.017453294f) * state->pitch_limit;
    *yaw_rate = (horizontal * 0.017453294f) * state->yaw_limit;
    state->pitch = math_step_spring_damper_clamped(&state->pitch_velocity, state->pitch, *pitch_rate,
                                 state->pitch_params[0], state->pitch_params[1], state->pitch_params[2]);
    state->yaw = math_step_spring_damper_clamped(&state->yaw_velocity, state->yaw, *yaw_rate,
                               state->yaw_params[0], state->yaw_params[1], state->yaw_params[2]);
    {
        SteeringRecord *record = *(SteeringRecord **)(obj + 0x70);
        record->value = math_step_spring_damper_clamped(&record->velocity, record->value, vertical,
                                      g_ship_roll_vec_x, g_ship_roll_vec_y, g_ship_roll_vec_z);
    }
    *pitch_rate = state->pitch;
    *yaw_rate = state->yaw;
    roll = (RollState *)(*(char **)(obj + 0x70) + 0xD4);
    if (roll->roll_timer && FastDecTimer(&roll->roll_timer))
        roll->roll_direction = 0;
    if (roll->roll_delay == 0) {
        if (g_pad_state.input.buttons & 0xC) {
            roll->roll_timer = ((s32)(g_ship_roll_timer_value) * 5 + 2) / 6;
            roll->roll_inverse = 1.0f / IntToFloat(roll->roll_timer);
            roll->roll_delay = roll->roll_timer + ((s32)(g_ship_roll_delay_offset) * 5 + 2) / 6;
            if (g_pad_state.input.words.held & 4) roll->roll_direction = -1;
            else roll->roll_direction = 1;
            if (g_cheat_flags) roll->roll_direction = roll->roll_direction == -1 ? 1 : -1;
        }
    } else {
        FastDecTimer(&roll->roll_delay);
    }
    if (FastDecTimer(&roll->combo_delay) && g_ship_combo_enabled && g_current_map_index != 20) {
        if ((g_pad_state.input.words.held & 3) == 3 || (g_pad_state.input.words.held & 0xC) == 0xC) {
            roll->combo_delay = ((s32)(g_ship_combo_delay) * 5 + 2) / 6;
            g_ship_state = 7;
            roll->combo_timer = ((s32)(g_ship_roll_duration) * 5 + 2) / 6;
            roll->combo_inverse = 1.0f / IntToFloat(roll->combo_timer);
        }
    }
}
