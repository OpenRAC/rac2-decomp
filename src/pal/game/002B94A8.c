#include "include_asm.h"

#include "common.h"
extern float func_00283CE0(int);
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
extern struct { s32 word; u8 mirror; u8 rest[7]; } D_001A7A40 MACRO_ADDR;
extern float func_00282E20(float *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);

void func_PAL_002B94A8(PadState *p, u8 *buf, s32 len) {
    float v[2];
    s32 i, j, k;
    s32 cur;
    float mag, ang;

    p->raw_held = p->held = ((buf[0] << 8) | buf[1]) ^ 0xFFFF;
    for (i = 0; i < 16; i++) {
        p->analog[i] = 0;
    }
    if (len >= 6) {
        for (i = 0; i < 4; i++) {
            s32 d = buf[i + 2] - 0x7F;
            if (d < 0)
                d = -d;
            if (d >= 0x30) {
                float f = func_00283CE0(d - 0x30) / func_00283CE0(0x4C);
                p->analog[i] = f;
                if (f > 1.0f) {
                    p->analog[i] = 1.0f;
                }
                if (buf[i + 2] < 0x7F) {
                    p->analog[i] = -p->analog[i];
                }
            }
        }
    }
    if (len >= 0x12) {
        for (i = 4; i < 16; i++) {
            p->analog[i] = func_00283CE0(buf[i + 2]) * 0.003921569f;
        }
    }
    if (D_001A7A40.mirror) {
        p->analog[2] = -p->analog[2];
        p->analog[0] = -p->analog[0];
        if (p->held & 0x8000) {
            p->held = (p->held & ~0x8000) | 0x2000;
        } else if (p->held & 0x2000) {
            p->held = (p->held & ~0x2000) | 0x8000;
        }
        p->raw_held = p->held;
    }
    for (i = 0; i < 16; i++) {
        p->analog_prev[i] = p->analog[i];
    }
    if (p->analog[2] != 0.0f || p->analog[3] != 0.0f) {
        p->stick_moved = 1;
    } else {
        p->stick_moved = 0;
    }
    if (p->analog[2] < 0.0f)
        p->held |= 0x8000;
    if (p->analog[2] > 0.0f)
        p->held |= 0x2000;
    if (p->analog[3] < 0.0f)
        p->held |= 0x1000;
    if (p->analog[3] > 0.0f)
        p->held |= 0x4000;
    p->pressed = ~p->prev_held & p->held;
    p->released = ~p->held & p->prev_held;
    p->no_buttons = p->held == 0;
    p->no_direction = (p->held & 0xF000) == 0;
    p->raw_pressed = ~p->prev_held & p->raw_held;
    p->raw_released = ~p->held & p->prev_raw_held;
    p->pressed_unmasked = p->pressed;
    p->released_unmasked = p->released;
    p->held_unmasked = p->held;
    p->unk348 = p->held;
    if (D_001A7A40.mirror) {
        p->analog_prev[2] = -p->analog_prev[2];
        p->analog_prev[0] = -p->analog_prev[0];
        if (((s32)p->held_unmasked) & 0x8000) {
            p->held_unmasked = (((s32)p->held_unmasked) & ~0x8000) | 0x2000;
        } else if (((s32)p->held_unmasked) & 0x2000) {
            p->held_unmasked = (((s32)p->held_unmasked) & ~0x2000) | 0x8000;
        }
        if (((s32)p->pressed_unmasked) & 0x8000) {
            p->pressed_unmasked = (((s32)p->pressed_unmasked) & ~0x8000) | 0x2000;
        } else if (((s32)p->pressed_unmasked) & 0x2000) {
            p->pressed_unmasked = (((s32)p->pressed_unmasked) & ~0x2000) | 0x8000;
        }
        if (((s32)p->released_unmasked) & 0x8000) {
            p->released_unmasked = (((s32)p->released_unmasked) & ~0x8000) | 0x2000;

        } else if (((s32)p->released_unmasked) & 0x2000) {
            p->released_unmasked = (((s32)p->released_unmasked) & ~0x2000) | 0x8000;
        }
    }
    if (p->mode == 1) {
        p->held &= ~0x5030;
        p->pressed &= ~0x5030;
        p->released &= ~0x5030;
        p->analog[0] = 0.0f;
        p->analog[1] = 0.0f;
        p->mode = 0;
    }
    if (p->mode == 2) {
        p->held &= 0x900;
        p->pressed &= 0x900;
        p->released &= 0x900;
        p->raw_held &= 0x900;
        p->no_direction = 1;
        p->analog[2] = 0.0f;
        p->analog[3] = 0.0f;
        p->mode = 0;
    }
    v[0] = p->analog[2];
    v[1] = p->analog[3];
    mag = func_00282E20(v);
    ang = func_00283248(v[0], v[1]);
    p->hist_mag[p->hist_idx] = mag;
    p->hist_ang[p->hist_idx] = ang;
    if (mag > 0.9f) {
        s32 h;
        for (j = 1; j < 3 && !(p->hist_mag[h = (p->hist_idx - j + 30) % 30] > 0.9f); j++) {
            float m = p->hist_mag[h];
            if (m < 0.25f) { p->pressed |= 0x10000; break; }
        }
        if (!(p->pressed & 0x10000)) {
            for (k = 1; k < 4; k++) {
                if (func_00283C80(p->hist_ang[(p->hist_idx - k + 30) % 30], ang) >
                    0.959931194782257080078125f) {
                    p->pressed |= 0x10000;
                    break;
                }
            }
        }
    }
    p->hist_btn[p->hist_idx] = p->pressed;
    p->hist_idx = (p->hist_idx + 1) % 30;
    if (++p->hist_count > 30) {
        p->hist_count = 30;
    }
    if (p->rep_rate) {
        cur = p->held;
        if (cur != 0 && cur == p->prev_held) {
            u8 t = --p->rep_timer;
            if (0 == t || t == 0xFF) {
                p->rep_timer = p->rep_rate;
                p->pressed = cur;
            }
        } else {
            p->rep_timer = p->rep_delay;
        }
    }
}


typedef struct {
    char reserved[0x18E];
    short active;
    int value;
} State_2B8518;
extern State_2B8518 D_00138180;

void func_PAL_002B9BB8(void) {
    extern void func_002B85F8(void *);
    extern State_2B8518 D_00138500;
    func_002B85F8(&D_00138180);
    func_002B85F8(&D_00138500);
}

