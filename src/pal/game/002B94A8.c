#include "include_asm.h"

#include "common.h"
extern float IntToFloat(int);
struct PadState {
    u8 pad_0[0x100] __attribute__((aligned(16)));
    f32 analog[16];                      
    f32 analog_prev[16];                 
    u8 profile[4];                       
    u8 act[4];                           
    u8 unk188;                           
    u8 unk189;                           
    u8 pad_18A[0x2];
    s16 unk18C;                          
    s16 hist_idx;                        
    s32 hist_count;                      
    s32 socket;                          
    s32 profile_state;                   
    s32 device_state;                    
    s32 held;                            
    s32 pressed;                         
    s32 released;                        
    s32 prev_held;                       
    s32 raw_held;                        
    s32 raw_pressed;                     
    s32 raw_released;                    
    s32 prev_raw_held;                   
    u32 held_unmasked;                   
    u32 pressed_unmasked;                
    u32 released_unmasked;               
    s32 mode;                            
    s32 no_buttons;                      
    s32 no_direction;                    
    s32 stick_moved;                     
    s32 unk1DC;                          
    s32 hist_btn[30];                    
    f32 hist_ang[30];                    
    f32 hist_mag[30];                    
    s32 unk348;                          
    u8 pad_34C;
    u8 rep_delay;                        
    u8 rep_rate;                         
    u8 rep_timer;                        
};
typedef struct PadState PadState;
extern struct { s32 word; u8 mirror; u8 rest[7]; } g_unlocked_item_flags MACRO_ADDR;
extern float vec_length_xy(float *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);

/* Decodes a raw pad reading into held, pressed and released buttons and analog stick values, with mirroring, flick detection and auto-repeat (PAL). */
void pad_decode_reading_pal(PadState *pad_state, u8 *reading, s32 length) {
    float stick[2];
    s32 i, j, k;
    s32 held_now;
    float magnitude, angle;

    pad_state->raw_held = pad_state->held = ((reading[0] << 8) | reading[1]) ^ 0xFFFF;
    for (i = 0; i < 16; i++) {
        pad_state->analog[i] = 0;
    }
    if (length >= 6) {
        for (i = 0; i < 4; i++) {
            s32 deflection = reading[i + 2] - 0x7F;
            if (deflection < 0)
                deflection = -deflection;
            if (deflection >= 0x30) {
                float ratio = IntToFloat(deflection - 0x30) / IntToFloat(0x4C);
                pad_state->analog[i] = ratio;
                if (ratio > 1.0f) {
                    pad_state->analog[i] = 1.0f;
                }
                if (reading[i + 2] < 0x7F) {
                    pad_state->analog[i] = -pad_state->analog[i];
                }
            }
        }
    }
    if (length >= 0x12) {
        for (i = 4; i < 16; i++) {
            pad_state->analog[i] = IntToFloat(reading[i + 2]) * 0.003921569f;
        }
    }
    if (g_unlocked_item_flags.mirror) {
        pad_state->analog[2] = -pad_state->analog[2];
        pad_state->analog[0] = -pad_state->analog[0];
        if (pad_state->held & 0x8000) {
            pad_state->held = (pad_state->held & ~0x8000) | 0x2000;
        } else if (pad_state->held & 0x2000) {
            pad_state->held = (pad_state->held & ~0x2000) | 0x8000;
        }
        pad_state->raw_held = pad_state->held;
    }
    for (i = 0; i < 16; i++) {
        pad_state->analog_prev[i] = pad_state->analog[i];
    }
    if (pad_state->analog[2] != 0.0f || pad_state->analog[3] != 0.0f) {
        pad_state->stick_moved = 1;
    } else {
        pad_state->stick_moved = 0;
    }
    if (pad_state->analog[2] < 0.0f)
        pad_state->held |= 0x8000;
    if (pad_state->analog[2] > 0.0f)
        pad_state->held |= 0x2000;
    if (pad_state->analog[3] < 0.0f)
        pad_state->held |= 0x1000;
    if (pad_state->analog[3] > 0.0f)
        pad_state->held |= 0x4000;
    pad_state->pressed = ~pad_state->prev_held & pad_state->held;
    pad_state->released = ~pad_state->held & pad_state->prev_held;
    pad_state->no_buttons = pad_state->held == 0;
    pad_state->no_direction = (pad_state->held & 0xF000) == 0;
    pad_state->raw_pressed = ~pad_state->prev_held & pad_state->raw_held;
    pad_state->raw_released = ~pad_state->held & pad_state->prev_raw_held;
    pad_state->pressed_unmasked = pad_state->pressed;
    pad_state->released_unmasked = pad_state->released;
    pad_state->held_unmasked = pad_state->held;
    pad_state->unk348 = pad_state->held;
    if (g_unlocked_item_flags.mirror) {
        pad_state->analog_prev[2] = -pad_state->analog_prev[2];
        pad_state->analog_prev[0] = -pad_state->analog_prev[0];
        if (((s32)pad_state->held_unmasked) & 0x8000) {
            pad_state->held_unmasked = (((s32)pad_state->held_unmasked) & ~0x8000) | 0x2000;
        } else if (((s32)pad_state->held_unmasked) & 0x2000) {
            pad_state->held_unmasked = (((s32)pad_state->held_unmasked) & ~0x2000) | 0x8000;
        }
        if (((s32)pad_state->pressed_unmasked) & 0x8000) {
            pad_state->pressed_unmasked = (((s32)pad_state->pressed_unmasked) & ~0x8000) | 0x2000;
        } else if (((s32)pad_state->pressed_unmasked) & 0x2000) {
            pad_state->pressed_unmasked = (((s32)pad_state->pressed_unmasked) & ~0x2000) | 0x8000;
        }
        if (((s32)pad_state->released_unmasked) & 0x8000) {
            pad_state->released_unmasked = (((s32)pad_state->released_unmasked) & ~0x8000) | 0x2000;

        } else if (((s32)pad_state->released_unmasked) & 0x2000) {
            pad_state->released_unmasked = (((s32)pad_state->released_unmasked) & ~0x2000) | 0x8000;
        }
    }
    if (pad_state->mode == 1) {
        pad_state->held &= ~0x5030;
        pad_state->pressed &= ~0x5030;
        pad_state->released &= ~0x5030;
        pad_state->analog[0] = 0.0f;
        pad_state->analog[1] = 0.0f;
        pad_state->mode = 0;
    }
    if (pad_state->mode == 2) {
        pad_state->held &= 0x900;
        pad_state->pressed &= 0x900;
        pad_state->released &= 0x900;
        pad_state->raw_held &= 0x900;
        pad_state->no_direction = 1;
        pad_state->analog[2] = 0.0f;
        pad_state->analog[3] = 0.0f;
        pad_state->mode = 0;
    }
    stick[0] = pad_state->analog[2];
    stick[1] = pad_state->analog[3];
    magnitude = vec_length_xy(stick);
    angle = mat_fast_helper_a(stick[0], stick[1]);
    pad_state->hist_mag[pad_state->hist_idx] = magnitude;
    pad_state->hist_ang[pad_state->hist_idx] = angle;
    if (magnitude > 0.9f) {
        s32 hist_pos;
        for (j = 1; j < 3 && !(pad_state->hist_mag[hist_pos = (pad_state->hist_idx - j + 30) % 30] > 0.9f); j++) {
            float prev_mag = pad_state->hist_mag[hist_pos];
            if (prev_mag < 0.25f) { pad_state->pressed |= 0x10000; break; }
        }
        if (!(pad_state->pressed & 0x10000)) {
            for (k = 1; k < 4; k++) {
                if (FastDiffRots(pad_state->hist_ang[(pad_state->hist_idx - k + 30) % 30], angle) >
                    0.959931194782257080078125f) {
                    pad_state->pressed |= 0x10000;
                    break;
                }
            }
        }
    }
    pad_state->hist_btn[pad_state->hist_idx] = pad_state->pressed;
    pad_state->hist_idx = (pad_state->hist_idx + 1) % 30;
    if (++pad_state->hist_count > 30) {
        pad_state->hist_count = 30;
    }
    if (pad_state->rep_rate) {
        held_now = pad_state->held;
        if (held_now != 0 && held_now == pad_state->prev_held) {
            u8 timer = --pad_state->rep_timer;
            if (0 == timer || timer == 0xFF) {
                pad_state->rep_timer = pad_state->rep_rate;
                pad_state->pressed = held_now;
            }
        } else {
            pad_state->rep_timer = pad_state->rep_delay;
        }
    }
}


typedef struct {
    char reserved[0x18E];
    short active;
    int value;
} State_2B8518;
extern State_2B8518 g_pad_state;

/* Polls both pad devices (PAL). */
void pad_poll_ports_pal(void) {
    extern void poll_pad_device_state(void *);
    extern State_2B8518 g_pad_device_state;
    poll_pad_device_state(&g_pad_state);
    poll_pad_device_state(&g_pad_device_state);
}

