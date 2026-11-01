#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;
typedef struct State_L04_00454BF8 {
    s32 group;           
    s32 flags;           
    s32 mode;            
    s32 pad0C;
    f32 band[4];         
    f32 scale;           
    f32 dir_in[3];       
    f32 gain;            
    s32 rgba_a[4];       
    s32 rgba_b[4];       
    f32 off_in[3];       
    f32 radius;          
    f32 fade_start;      
    f32 fade_end;        
    f32 off2_in[3];      
    f32 reach;           
    s32 pad7C;
    s32 trigger;         
    u8 alpha;            
    u8 pad85[0x90 - 0x85];
    f32 dir[4];          
    f32 off[4];          
    f32 off2[4];         
    s32 color_a;         
    s32 color_b;         
    u8 padC8[0xE0 - 0xC8];
    f32 time;            
    f32 period;          
    f32 step;            
} State_L04_00454BF8;
typedef struct Mtx_L04_00454BF8 {
    f32 axis[3][4];      
    f32 pos[4];          
} Mtx_L04_00454BF8;
extern void func_0029F338(void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_L02_002F1FB8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283CC8(float *, float);
extern f32 func_L04_00455418(void *, f32);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00283098(void *, void *, void *);
extern float func_002831B0(float);
extern f32 func_L04_004554F8(f32);
extern void func_L00_0036EF68(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void *func_L04_00363CA0(void *, int, float);
extern int func_00283D38(int, int, float);
extern s32 D_L04_001A9018 __attribute__((sda));
extern u16 **D_L04_001A9014 __attribute__((sda));
extern u8 *D_L04_001B2B54 __attribute__((sda));
extern Mtx_L04_00454BF8 *D_L04_001B2B5C __attribute__((sda));
extern char D_L04_001B9680[];

/* A light controller. State 0 checks its id list (released when the group is out of range or has
   no list), converts its record (bands scaled, colours packed, fade angles to radians, the three
   vectors copied and normalised) and falls into state 1. State 1 advances the clock and, when its
   trigger is -1 or func_002ACBC8 holds for it, walks the group's id list: each matrix of
   D_L04_001B2B5C within 32 units of the camera gets a blend from one of four modes (wave along
   a direction, distance, position phase, or a sweeping axis), the two packed colours are mixed by
   it, the light record of D_L04_001B2B54 is recoloured (flag 1), and a glow facing the camera is
   spawned (flag 2), faded by the angle between its offset and the view.
   It is a -g unit: the line label on the case 1 division is what makes the assembler pad it with
   the retail's nop. The sweep's thresholds are locals set at the head of their case, which is what
   puts them in saved registers before the calls. */
void func_PAL_L04_0045A808(u8 *self)
{
    State_L04_00454BF8 *st = *(State_L04_00454BF8 **)(self + 0x68);
    f32 to_cam[4];
    f32 axis[4];
    f32 probe[4];
    f32 spot[4];
    f32 pull[4];
    f32 whole;
    u16 *p;
    Mtx_L04_00454BF8 *e;
    u8 *light;
    s32 group;
    s32 color;
    s32 alpha;
    f32 blend;
    f32 fade;
    f32 time;
    f32 theta;
    f32 phi;
    f32 sin_theta;
    f32 elev;
    f32 along;
    f32 angle;
    f32 size;
    f32 half;
    f32 quarter;
    f32 rise;
    f32 full;
    f32 fall;
    f32 gone;
    s32 glow;
    s32 red;
    s32 green;
    s32 blue;
    s32 word_a;
    s32 word_b;

    switch (self[0x20]) {
    case 0:
        group = st->group;
        if (group >= D_L04_001A9018 || group == -1 || D_L04_001A9014[group] == 0) {
            func_0029F338(self);
            return;
        }
        st->time = 0.0f;
        st->step = 0.019867549f;
        st->fade_start *= 0.017453294f;
        st->fade_end *= 0.017453294f;
        word_a = st->rgba_a[3] << 24 | st->rgba_a[2] << 16;
        word_a |= st->rgba_a[1] << 8;
        word_a |= st->rgba_a[0];
        st->color_a = word_a;
        word_b = st->rgba_b[3] << 24 | st->rgba_b[2] << 16;
        word_b |= st->rgba_b[1] << 8;
        word_b |= st->rgba_b[0];
        st->color_b = word_b;
        st->band[0] *= st->scale;
        st->band[1] *= st->scale;
        st->band[2] *= st->scale;
        st->band[3] *= st->scale;
        st->scale = 1.0f;
        st->period = st->band[0] + st->band[1] + st->band[2] + st->band[3];
        self[0x30] = st->alpha;
        st->dir[0] = st->dir_in[0];
        st->dir[1] = st->dir_in[1];
        st->dir[2] = st->dir_in[2];
        st->dir[3] = 0.0f;
        if (st->dir[0] == 0.0f && st->dir[1] == 0.0f && st->dir[2] == 0.0f)
            st->mode = 0;
        else
            func_00282F20(st->dir, st->dir, 1.0f);
        st->off[0] = st->off_in[0];
        st->off[1] = st->off_in[1];
        st->off[2] = st->off_in[2];
        st->off[3] = 0.0f;
        func_00282F20(st->off, st->off, 1.0f);
        st->off2[0] = st->off2_in[0];
        st->off2[1] = st->off2_in[1];
        st->off2[2] = st->off2_in[2];
        st->off2[3] = 0.0f;
        func_002A7750(self, 1, -1);
    case 1:
        st->time += st->step;
        if (st->trigger != -1 && func_002ACBC8(D_L04_001B9680, st->trigger) == 0)
            return;
        for (p = D_L04_001A9014[st->group];
             p != 0 && ((s16)p[-1] >= 0 || p == D_L04_001A9014[st->group]); p++) {
            e = &D_L04_001B2B5C[*p & 0x7FFF];
            if (e == 0)
                break;
            func_L02_002F1FB8(to_cam, D_L04_001B9680, e->pos);
            blend = 0.0f;
            light = D_L04_001B2B54 + ((*p & 0x7FFF) << 5);
            if (func_00282DF0(to_cam) > 32.0f)
                continue;
            switch (st->mode) {
            case 1:
                along = func_00282DB0(e->pos, st->dir) * st->gain / func_00282DF0(st->dir);
                blend = func_L04_00455418(st, st->time + along);
                break;
            case 2:
                blend = func_L04_00455418(st, st->time + func_00282E48(self + 0x10, e->pos));
                break;
            case 3:
                blend = func_L04_00455418(st, st->time + st->period *
                                                     func_00283CC8(&whole, e->pos[0] + e->pos[1] + e->pos[2]));
                break;
            case 4:
                half = 0.5f;
                quarter = 1.5707965f;
                rise = 1.3962636f;
                full = 1.48353f;
                fall = 1.6580629f;
                gone = 2.007129f;
                time = st->time;
                theta = time * half * 3.1415927f;
                phi = time * quarter;
                sin_theta = func_00283198(theta);
                axis[0] = sin_theta * func_00283180(phi);
                axis[1] = sin_theta * func_00283198(phi);
                axis[2] = func_00283180(theta);
                func_00283098(axis, axis, self + 0xC0);
                func_L02_002F1FB8(probe, e->pos, self + 0x10);
                func_00282F20(probe, probe, 1.0f);
                elev = 1.5707964f - func_002831B0(func_00282DB0(probe, axis));
                if (elev > rise) {
                    if (elev <= full)
                        blend = func_L04_004554F8((elev - rise) / (full - rise));
                    else if (elev <= fall)
                        blend = 1.0f;
                    else if (elev <= gone)
                        blend = 1.0f - func_L04_004554F8((elev - fall) / (gone - fall));
                }
                break;
            }
            color = func_00283D38(st->color_b, st->color_a, blend);
            if (st->flags & 1) {
                blue = (color >> 16) & 0xFF;
                green = (color >> 8) & 0xFF;
                red = color & 0xFF;
                func_L00_0036EF68(light, red, green, blue);
            }
            if (st->flags & 2) {
                fade = 1.0f;
                func_00282F20(axis, to_cam, 1.0f);
                func_00283098(probe, st->off, e);
                angle = 1.5707964f - func_002831B0(func_00282DB0(probe, axis));
                if (angle >= st->fade_end)
                    fade = 0.0f;
                else if (angle > st->fade_start)
                    fade = func_L04_004554F8((angle - st->fade_end) / (st->fade_start - st->fade_end));
                alpha = (u32)color >> 24;
                if (alpha == 0)
                    continue;
                if (fade == 0.0f)
                    continue;
                if (fade != 1.0f)
                    alpha = (s32)((f32)alpha * fade);
                glow = (color & 0xFFFFFF) | (alpha << 24);
                size = func_00282DF0(e);
                func_00283098(spot, st->off2, e);
                func_00282CC0(spot, spot, e->pos);
                func_00282CF0(pull, D_L04_001B9680, spot);
                func_00282F20(pull, pull, st->reach * size);
                func_00282CC0(spot, spot, pull);
                func_L04_00363CA0(spot, glow, st->radius * size * 210000.0f);
            }
        }
        break;
    }
}
