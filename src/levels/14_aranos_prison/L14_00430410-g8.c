#include "common.h"
extern char g_sound_state[];
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } PrisonSoundAnchor;
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern void snd_stop_voice(int);
extern void moby_set_state(char *,int,int);
extern void gfx_add_draw_callback_third(void *,void *);
extern float math_wrap_angle_full_turn(float);
extern void DrawAnimatedPrisonQuads(char *);
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
    float currentScale;
    float baseScale;
    float pulseScale;
    int w8c;
    int pulseFrames;
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
/* Initializes the pulse effect, maintains its sound and draw callback, and fades its scale. */
void UpdatePrisonPulseEffect(char *self)
{
    PrisonEffectState *s = *(PrisonEffectState **)(self+0x68);
    int i;
    switch ((unsigned char)self[0x20]) {
    case 0:
        s->w00=0;
        s->w04=69; s->w08=1.2f; s->w0c=0x50000080;
        s->w20=2.0f; s->w24=4.2f; s->w28=3.1f; s->w2c=3.7f;
        s->w30=0x80000080; s->w34=0x80000080;
        s->w38=0x80200060; s->w3c=0x80808080; s->w40=0x80200060;
        s->w44=0x80300050; s->w48=0x80202880; s->w4c=0x80606020;
        for (i=1;i>=0;i--) s->range[i]=i*50;
        s->w10=300;
        s->w60=-0.125f; s->w64=0.133f;
        s->w68=0.241f; s->w6c=-0.221f;
        s->w18=1.2f; s->w70=0.6f;
        s->w74=0.5f; s->w78=0.4f;
        s->w7c=0.7f;
        s->w1c=54;
        s->w94=0x28280080; s->w98=0x0a800000;
        s->wa0=0.9f; s->wa4=0.1f;
        s->wa8=20; s->wac=s->w14=0.8f;
        s->wb0=70; s->wb4=s->w9c=2.0f;
        for(i=0;i<32;i++) {
            g_spark_quad_angles[i]=math_random_float_range(-3.1415927f,3.1415927f);
            g_spark_quad_progress[i]=(float)i*0.03125f;
        }
        s->wb8=71; s->wbc=1.0f;
        s->wc0=0x80800000;
        self[0x31]=0; *(unsigned short *)(self+0x34)|=1;
        s->sound=-1;
        moby_set_state(self,1,-1);
        break;
    case 1:
        if (((PrisonSoundAnchor *)(g_sound_state+s->sound*112))->owner!=self ||
            !((PrisonSoundAnchor *)(g_sound_state+s->sound*112))->active)
            s->sound=prisonStartSound(0,4,self);
        gfx_add_draw_callback_third(DrawAnimatedPrisonQuads,self);
        if(flag_is_third_pending_set(self)) {
            if(D_L14_001B20C8_1<50) s->baseScale=0;
            moby_set_state(self,2,-1);
        }
        break;
    case 2: {
        int sound=s->sound;
        if(sound!=-1 && ((PrisonSoundAnchor *)(g_sound_state+sound*112))->owner==self &&
            ((PrisonSoundAnchor *)(g_sound_state+sound*112))->active) snd_stop_voice(sound);
        s->sound=-1;
        if(flag_set_first_pending(self)) *(int *)(self+0x98)=0;
        if(s->baseScale>0.5f) {
            gfx_add_draw_callback_third(DrawAnimatedPrisonQuads,self);
            s->baseScale-=0.05f;
        }
        break;
    }
    }
    s->currentScale=s->baseScale+s->pulseScale*
        math_fast_sin_or_cos_b(math_wrap_angle_full_turn((float)g_frame_tick_counter*6.2831855f/(float)s->pulseFrames));
}

