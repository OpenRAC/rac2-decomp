#include "common.h"
extern char g_sound_state[];
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern void snd_stop_voice(int);
extern void moby_set_state(char *,int,int);
extern void gfx_add_draw_callback_third(void *,void *);
extern float math_wrap_angle_full_turn(float);
extern void prison_animated_quads_draw_pal(char *);
extern float math_random_float_range(float, float);
extern int flag_is_third_pending_set(void *);
extern int flag_set_first_pending(void *);
extern float math_fast_sin_or_cos_b(float);
extern int g_frame_tick_counter;
extern int D_L14_001B20C8_1 __attribute__((sda));
extern float g_spark_quad_angles[32], g_spark_quad_progress[32];
typedef struct {
    float w00;
    int w04;
    float w08;
    unsigned int w0c;
    int w10;
    float w14;
    float w18;
    int w1c;
    float w20;
    float w24;
    float w28;
    float w2c;
    unsigned int w30;
    unsigned int w34;
    unsigned int w38;
    unsigned int w3c;
    unsigned int w40;
    unsigned int w44;
    unsigned int w48;
    unsigned int w4c;
    int range[2];
    int w58;
    int w5c;
    float w60;
    float w64;
    float w68;
    float w6c;
    float w70;
    float w74;
    float w78;
    float w7c;
    float current_scale;
    float base_scale;
    float pulse_scale;
    int w8c;
    int pulse_frames;
    int w94;
    int w98;
    float w9c;
    float wa0;
    float wa4;
    int wa8;
    float wac;
    int wb0;
    float wb4;
    int wb8;
    float wbc;
    unsigned int wc0;
    int sound;
} PrisonEffectState;
/* func_PAL_L14_00435D28, the PAL copy of func_L14_00430410: the same C, with pulse_frames rescaled
 * to 50 Hz on init and func_PAL_L14_004364B0 as the draw callback. */
/* Initializes the pulse effect, maintains its sound and draw callback, and fades its scale. */
void prison_pulse_effect_update_pal(char *moby)
{
    PrisonEffectState *vars = *(PrisonEffectState **)(moby+0x68);
    int i;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        vars->pulse_frames=((s32)(vars->pulse_frames) * 5 + 2) / 6;
        vars->w00=0;
        vars->w04=69; vars->w08=1.2f; vars->w0c=0x50000080;
        vars->w20=2.0f; vars->w24=4.2f; vars->w28=3.1f; vars->w2c=3.7f;
        vars->w30=0x80000080; vars->w34=0x80000080;
        vars->w38=0x80200060; vars->w3c=0x80808080; vars->w40=0x80200060;
        vars->w44=0x80300050; vars->w48=0x80202880; vars->w4c=0x80606020;
        for (i=1;i>=0;i--) vars->range[i]=i*50;
        vars->w10=300;
        vars->w60=-0.125f; vars->w64=0.133f;
        vars->w68=0.241f; vars->w6c=-0.221f;
        vars->w18=1.2f; vars->w70=0.6f;
        vars->w74=0.5f; vars->w78=0.4f;
        vars->w7c=0.7f;
        vars->w1c=54;
        vars->w94=0x28280080; vars->w98=0x0a800000;
        vars->wa0=0.9f; vars->wa4=0.1f;
        vars->wa8=20; vars->wac=vars->w14=0.8f;
        vars->wb0=70; vars->wb4=vars->w9c=2.0f;
        for(i=0;i<32;i++) {
            g_spark_quad_angles[i]=math_random_float_range(-3.1415927f,3.1415927f);
            g_spark_quad_progress[i]=(float)i*0.03125f;
        }
        vars->wb8=71; vars->wbc=1.0f;
        vars->wc0=0x80800000;
        moby[0x31]=0; *(unsigned short *)(moby+0x34)|=1;
        vars->sound=-1;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if (((PrisonSoundAnchor *)(g_sound_state+vars->sound*112))->owner!=moby ||
            !((PrisonSoundAnchor *)(g_sound_state+vars->sound*112))->active)
            vars->sound=prisonStartSound(0,4,moby);
        gfx_add_draw_callback_third(prison_animated_quads_draw_pal,moby);
        if(flag_is_third_pending_set(moby)) {
            if(D_L14_001B20C8_1<50) vars->base_scale=0;
            moby_set_state(moby,2,-1);
        }
        break;
    case 2: {
        int sound=vars->sound;
        if(sound!=-1 && ((PrisonSoundAnchor *)(g_sound_state+sound*112))->owner==moby &&
            ((PrisonSoundAnchor *)(g_sound_state+sound*112))->active) snd_stop_voice(sound);
        vars->sound=-1;
        if(flag_set_first_pending(moby)) *(int *)(moby+0x98)=0;
        if(vars->base_scale>0.5f) {
            gfx_add_draw_callback_third(prison_animated_quads_draw_pal,moby);
            vars->base_scale-=0.05f;
        }
        break;
    }
    }
    vars->current_scale=vars->base_scale+vars->pulse_scale*
        math_fast_sin_or_cos_b(math_wrap_angle_full_turn((float)g_frame_tick_counter*6.2831855f/(float)vars->pulse_frames));
}

