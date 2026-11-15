#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

/* A lift path of D_L17_001FE880. */
typedef struct {
    int count;                  /* 0x00 */
    u8 pad04[0x10 - 0x04];
    Vec points[1];              /* 0x10: count points */
} LiftPath;

/* The instance data of the lift. */
typedef struct {
    u8 pad00[0x50];
    u8 motion[0x40];            /* 0x50: this frame's movement, for what rides on it */
    u8 pad90[0x98 - 0x90];
    float verticalSpeed;        /* 0x98 */
    u8 pad9C[0xA4 - 0x9C];
    int path;                   /* 0xA4: index in D_L17_001FE880 */
    u8 padA8[0xAC - 0xA8];
    s16 atLast;                 /* 0xAC: nonzero at the last point; state 2 counts it down */
    u8 padAE[0xB4 - 0xAE];
    int sound;                  /* 0xB4 */
    u8 padB8[0xC8 - 0xB8];
    int point;                  /* 0xC8: the point it travels towards */
    int needsTrigger;           /* 0xCC: wait for trigger flag 4 before taking the hero */
    int f0D0;                   /* 0xD0: path index of func_L17_003C3250 */
    int hasRecord;              /* 0xD4 */
    float *record;              /* 0xD8: from func_L00_002D70A0(5) while the hero rides */
    u8 padDC[0xE0 - 0xDC];
    Vec velocity;               /* 0xE0: movement per frame along the current segment */
} LiftVars;

typedef struct {
    u8 pad00[0x10];
    Vec position;               /* 0x10 */
    u8 state;                   /* 0x20 */
    u8 pad21[0x68 - 0x21];
    LiftVars *vars;             /* 0x68 */
    u8 pad6C[0xF0 - 0x6C];
    Vec rotation;               /* 0xF0 */
} Moby;

/* The hero (D_00189E20), as far as the lift reads it. */
typedef struct {
    u8 pad0000[0x212];
    s16 f212;                   /* 0x212 */
    s16 f214;                   /* 0x214 */
    u8 pad0216[0x33C - 0x216];
    Moby *groundMoby;           /* 0x33C */
    int groundedFrames;         /* 0x340 */
    u8 pad0344[0x2290 - 0x344];
    Moby *moby;                 /* 0x2290 */
} Hero;

/* The sound voices are 0x70-byte records after the pool's 0x70-byte header.
   SoundVoice views voice n from record n, so its offsets include the header. */
typedef struct {
    u8 bytes[0x70];
} SoundRecord;

typedef struct {
    u8 pad0[0x74];
    u8 active;                  /* 0x74 */
    u8 pad75[0x88 - 0x75];
    Moby *owner;                /* 0x88 */
} SoundVoice;

extern Hero g_hero_state;
extern SoundRecord g_sound_state[];
extern LiftPath *g_path_l17_table[];
extern int D_00138324[];        /* the buttons pressed this frame; 0x10 is triangle */
extern float D_L17_001B0220 __attribute__((sda));
extern float D_L17_001B0228 __attribute__((sda));
extern float D_L17_001B022C __attribute__((sda));
extern float D_L17_001B0234 __attribute__((sda));

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
void UpdateSmolgPathLift(Moby *moby)
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
        if (g_hero_state.groundMoby == moby && g_hero_state.groundedFrames) {
            if (vars->needsTrigger && !flag_is_third_pending_set(moby))
                goto finish;
            TryClaimNotice(8, 0x279A, 1);
            if (D_00138324[0] & 0x10) {
                if (!vars->atLast) {
                    moby_set_state(moby, 4, -1);
                    velocity = &vars->velocity;
                    vars->point = 1;
                    FastVecSub(velocity, &path->points[1], &path->points[0]);
                    vec_scale_to_length(velocity, velocity, D_L17_001B0220 * 0.016666668f);
                } else {
                    moby_set_state(moby, 5, -1);
                    velocity = &vars->velocity;
                    point = path->count - 2;
                    vars->point = point;
                    FastVecSub(velocity, &path->points[point], &path->points[point + 1]);
                    vec_scale_to_length(velocity, velocity, D_L17_001B0220 * 0.016666668f);
                }
                break;
            }
        }
        if (moby->position.f[2] + 10.0f < g_hero_state.moby->position.f[2] && vars->atLast) {
            qcopy(&moby->position, &path->points[0]);
            vars->atLast = 0;
        } else if (g_hero_state.moby->position.f[2] < moby->position.f[2] - 10.0f && !vars->atLast) {
            qcopy(&moby->position, &path->points[path->count - 1]);
            vars->atLast = 1;
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
            vars->verticalSpeed = 0.0f;
        {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[vars->sound];

            if (voice->owner != moby || !voice->active)
                vars->sound = PlayMobySound(0, 4, moby);
        }
        if (hero_is_on_moby(moby)) {
            g_hero_state.f212 = 4;
            g_hero_state.f214 = 4;
            platform_attach_path_to_lift(moby);
            if (!vars->hasRecord) {
                float *record = cam_alloc_override_slot(5);
                float value;

                vars->record = record;
                if (record) {
                    vars->hasRecord = 1;
                    record[0] = D_L17_001B0228;
                    value = D_L17_001B022C;
                    vars->record[1] = value;
                    vars->record[3] = D_L17_001B0234;
                }
            }
        }
        math_step_value_toward_target(&moby->position.f[2], &vars->verticalSpeed,
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
            if (vars->hasRecord) {
                cam_end_override(vars->record);
                vars->hasRecord = 0;
            }
            vars->atLast = !vars->atLast;
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
        if (FastDecTimer(&vars->atLast)) {
            moby_set_state(moby, 5, -1);
            velocity = &vars->velocity;
            point = vars->point - 1;
            vars->point = point;
            FastVecSub(velocity, &path->points[point], &path->points[point + 1]);
            vec_scale_to_length(velocity, velocity, D_L17_001B0220 * 0.016666668f);
        }
        break;

    case 3:
        /* Travelling to the first point. */
        if (flag_set_first_pending(moby))
            vars->verticalSpeed = 0.0f;
        {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[vars->sound];

            if (voice->owner != moby || !voice->active)
                vars->sound = PlayMobySound(0, 4, moby);
        }
        if (hero_is_on_moby(moby)) {
            g_hero_state.f212 = 4;
            g_hero_state.f214 = 4;
            platform_attach_path_to_lift(moby);
            if (!vars->hasRecord) {
                float *record = cam_alloc_override_slot(5);
                float value;

                vars->record = record;
                if (record) {
                    vars->hasRecord = 1;
                    record[0] = D_L17_001B0228;
                    value = D_L17_001B022C;
                    vars->record[1] = value;
                    vars->record[3] = D_L17_001B0234;
                }
            }
        }
        math_step_value_toward_target(&moby->position.f[2], &vars->verticalSpeed,
                      path->points[0].f[2], 0.0019444445f, 0.003888889f, 0.5f);
        if (math_fabs(moby->position.f[2] - path->points[0].f[2]) < 0.2f) {
            vars->atLast = 0;
            moby_set_state(moby, 0, -1);
            if (vars->hasRecord) {
                cam_end_override(vars->record);
                vars->hasRecord = 0;
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
    if (!hero_is_on_moby(moby) && vars->hasRecord) {
        cam_end_override(vars->record);
        vars->hasRecord = 0;
    }
    FastVecSub(&delta, &moby->position, &old);
    mat_combine_and_store(vars->motion, &delta, &moby->rotation, &moby->rotation);
}
