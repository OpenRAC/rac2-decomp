#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    int count;                   
    u8 pad04[0x10 - 0x04];
    Vec points[1];               
} LiftPath;
typedef struct {
    u8 pad00[0x50];
    u8 motion[0x40];             
    u8 pad90[0x98 - 0x90];
    float vertical_speed;         
    u8 pad9C[0xA4 - 0x9C];
    int path;                    
    u8 padA8[0xAC - 0xA8];
    s16 at_last;                  
    u8 padAE[0xB4 - 0xAE];
    int sound;                   
    u8 padB8[0xC8 - 0xB8];
    int point;                   
    int needs_trigger;            
    int f0D0;                    
    int has_record;               
    float *record;               
    u8 padDC[0xE0 - 0xDC];
    Vec velocity;                
} LiftVars;
typedef struct {
    u8 pad00[0x10];
    Vec position;                
    u8 state;                    
    u8 pad21[0x68 - 0x21];
    LiftVars *vars;              
    u8 pad6C[0xF0 - 0x6C];
    Vec rotation;                
} Moby;
typedef struct {
    u8 pad0000[0x212];
    s16 f212;                    
    s16 f214;                    
    u8 pad0216[0x33C - 0x216];
    Moby *ground_moby;            
    int grounded_frames;          
    u8 pad0344[0x2290 - 0x344];
    Moby *moby;                  
} Hero;
typedef struct {
    u8 bytes[0x70];
} SoundRecord;
typedef struct {
    u8 pad0[0x74];
    u8 active;                   
    u8 pad75[0x88 - 0x75];
    Moby *owner;                 
} SoundVoice;
extern Hero g_hero_state;
extern SoundRecord g_sound_state[];
extern LiftPath *g_path_l17_table[];
extern int g_pad_held_flags[];
extern float g_lift_speed __attribute__((sda));
extern float g_lift_record_value_a __attribute__((sda));
extern float g_lift_record_value_b __attribute__((sda));
extern float g_lift_record_value_c __attribute__((sda));
extern int flag_is_third_pending_set(void *);
extern int flag_set_first_pending(void *);
extern int hero_get_target_state_kind(void);
extern int hero_is_on_moby(void *);
extern int TryClaimNotice(int, int, int);
extern void moby_set_state(void *, int, int);
extern void hero_start_target_state(void *, int, float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void platform_attach_path_to_lift(void *);
extern float *cam_alloc_override_slot(int);
extern void cam_end_override(void *);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern float math_fabs(float);
extern int FastDecTimer(s16 *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Moves a lift between the first and the last point of its path: triangle
   starts it while the hero stands on it, it eases to the other end with its
   travel sound, and while idle it jumps to the hero's end when the hero is more
   than 10 units above or below it. Riders follow its movement. */
void UpdateSmolgPathLift_us2(Moby *moby)
{
    Quad old;
    Quad delta;
    LiftVars *vars = moby->vars;
    LiftPath *path;
    int sound;
    int point;
    Vec *velocity;

    qcopy(&old, &moby->position);
    path = g_path_l17_table[vars->path];
    switch (moby->state) {
    case 0:
        /* Waiting at one end. */
        vars->sound = -1;
        if (g_hero_state.ground_moby == moby && g_hero_state.grounded_frames) {
            if (vars->needs_trigger && !flag_is_third_pending_set(moby))
                goto finish;
            TryClaimNotice(8, 0x12EC, 1);
            if (g_pad_held_flags[0] & 0x10) {
                if (!vars->at_last) {
                    moby_set_state(moby, 4, -1);
                    velocity = &vars->velocity;
                    vars->point = 1;
                    FastVecSub(velocity, &path->points[1], &path->points[0]);
                    vec_scale_to_length(velocity, velocity, g_lift_speed * 0.016666668f);
                } else {
                    moby_set_state(moby, 5, -1);
                    velocity = &vars->velocity;
                    point = path->count - 2;
                    vars->point = point;
                    FastVecSub(velocity, &path->points[point], &path->points[point + 1]);
                    vec_scale_to_length(velocity, velocity, g_lift_speed * 0.016666668f);
                }
                break;
            }
        }
        if (moby->position.f[2] + 10.0f < g_hero_state.moby->position.f[2] && vars->at_last) {
            qcopy(&moby->position, &path->points[0]);
            vars->at_last = 0;
        } else if (g_hero_state.moby->position.f[2] < moby->position.f[2] - 10.0f && !vars->at_last) {
            qcopy(&moby->position, &path->points[path->count - 1]);
            vars->at_last = 1;
            moby->position.f[2] += 0.2f;
        }
        break;

    case 4:
        /* Leaving the first point. */
        if (flag_set_first_pending(moby))
            hero_start_target_state(&moby->position, 0, moby->rotation.f[2]);
        if (hero_get_target_state_kind() == 1)
            goto finish;
        moby_set_state(moby, 1, -1);
        break;

    case 5:
        /* Leaving the last point. */
        if (flag_set_first_pending(moby))
            hero_start_target_state(&moby->position, 0, moby->rotation.f[2]);
        if (hero_get_target_state_kind() == 1)
            goto finish;
        moby_set_state(moby, 3, -1);
        break;

    case 1:
        /* Travelling to the last point. */
        if (flag_set_first_pending(moby))
            vars->vertical_speed = 0.0f;
        {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[vars->sound];

            if (voice->owner != moby || !voice->active)
                vars->sound = PlayMobySound(0, 4, moby);
        }
        if (hero_is_on_moby(moby)) {
            g_hero_state.f212 = 4;
            g_hero_state.f214 = 4;
            platform_attach_path_to_lift(moby);
            if (!vars->has_record) {
                float *record = cam_alloc_override_slot(5);
                float value;

                vars->record = record;
                if (record) {
                    vars->has_record = 1;
                    record[0] = g_lift_record_value_a;
                    value = g_lift_record_value_b;
                    vars->record[1] = value;
                    vars->record[3] = g_lift_record_value_c;
                }
            }
        }
        math_step_value_toward_target(&moby->position.f[2], &vars->vertical_speed,
                      path->points[path->count - 1].f[2], 0.0019444445f, 0.003888889f, 0.5f);
        if (math_fabs(moby->position.f[2] - path->points[path->count - 1].f[2]) < 0.2f) {
            moby_set_state(moby, 0, -1);
            sound = vars->sound;
            if (sound != -1) {
                SoundVoice *voice = (SoundVoice *)&g_sound_state[sound];

                if (voice->owner == moby && voice->active)
                    snd_stop_voice(sound);
            }
            vars->sound = -1;
            if (vars->has_record) {
                cam_end_override(vars->record);
                vars->has_record = 0;
            }
            vars->at_last = !vars->at_last;
        }
        break;

    case 2:
        /* Stopped: when the count runs out, head back to the first point. */
        sound = vars->sound;
        if (sound != -1) {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[sound];

            if (voice->owner == moby && voice->active)
                snd_stop_voice(sound);
        }
        vars->sound = -1;
        if (FastDecTimer(&vars->at_last)) {
            moby_set_state(moby, 5, -1);
            velocity = &vars->velocity;
            point = vars->point - 1;
            vars->point = point;
            FastVecSub(velocity, &path->points[point], &path->points[point + 1]);
            vec_scale_to_length(velocity, velocity, g_lift_speed * 0.016666668f);
        }
        break;

    case 3:
        /* Travelling to the first point. */
        if (flag_set_first_pending(moby))
            vars->vertical_speed = 0.0f;
        {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[vars->sound];

            if (voice->owner != moby || !voice->active)
                vars->sound = PlayMobySound(0, 4, moby);
        }
        if (hero_is_on_moby(moby)) {
            g_hero_state.f212 = 4;
            g_hero_state.f214 = 4;
            platform_attach_path_to_lift(moby);
            if (!vars->has_record) {
                float *record = cam_alloc_override_slot(5);
                float value;

                vars->record = record;
                if (record) {
                    vars->has_record = 1;
                    record[0] = g_lift_record_value_a;
                    value = g_lift_record_value_b;
                    vars->record[1] = value;
                    vars->record[3] = g_lift_record_value_c;
                }
            }
        }
        math_step_value_toward_target(&moby->position.f[2], &vars->vertical_speed,
                      path->points[0].f[2], 0.0019444445f, 0.003888889f, 0.5f);
        if (math_fabs(moby->position.f[2] - path->points[0].f[2]) < 0.2f) {
            vars->at_last = 0;
            moby_set_state(moby, 0, -1);
            if (vars->has_record) {
                cam_end_override(vars->record);
                vars->has_record = 0;
            }
            sound = vars->sound;
            if (sound != -1) {
                SoundVoice *voice = (SoundVoice *)&g_sound_state[sound];

                if (voice->owner == moby && voice->active)
                    snd_stop_voice(sound);
            }
            vars->sound = -1;
        }
        break;
    }

finish:
    if (!hero_is_on_moby(moby) && vars->has_record) {
        cam_end_override(vars->record);
        vars->has_record = 0;
    }
    FastVecSub(&delta, &moby->position, &old);
    mat_combine_and_store(vars->motion, &delta, &moby->rotation, &moby->rotation);
}
