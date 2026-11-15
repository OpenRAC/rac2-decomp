#include "common.h"

/* The instance data of the bobbing object. */
typedef struct {
    float bobPhase;             /* 0x00 */
    float bobOffset;            /* 0x04 */
    float swayPhase;            /* 0x08 */
    float tiltPhase;            /* 0x0C */
    float rise;                 /* 0x10: height of the upper rest above the lower one */
    int state;                  /* 0x14 */
    int timer;                  /* 0x18 */
    float baseZ;                /* 0x1C */
    float minRise;              /* 0x20 */
    float maxRise;              /* 0x24 */
    float minWait;              /* 0x28: seconds */
    float maxWait;              /* 0x2C */
    float riseTime;             /* 0x30 */
    float fallTime;             /* 0x34 */
    float spinSpeed;            /* 0x38: radians per frame */
    int sound;                  /* 0x3C */
    int stopped;                /* 0x40 */
} BobberVars;

typedef struct {
    u8 pad0[0x10];
    float position[4];          /* 0x10 */
    u8 pad20[0x68 - 0x20];
    BobberVars *vars;           /* 0x68 */
    u8 pad6C[0x78 - 0x6C];
    int color;                  /* 0x78 */
    u8 pad7C[0xA8 - 0x7C];
    u8 impactSlot;              /* 0xA8 */
    u8 padA9[0xB2 - 0xA9];
    s16 uid;                    /* 0xB2 */
    u8 padB4[0xF0 - 0xB4];
    float rotation[4];          /* 0xF0 */
} Moby;

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

/* The frame counter is an incomplete array: it keeps its absolute address
   load, while the complete tuning scalars use GP addressing. The -g profile
   keeps retail's div.s hazards. */
extern int D_L17_001B2748[] __attribute__((sda));
extern float D_L17_001B0248 __attribute__((sda));
extern float D_L17_001B024C __attribute__((sda));
extern float D_L17_001B0250 __attribute__((sda));
extern float D_L17_001B0254 __attribute__((sda));
extern float D_L17_001B0258 __attribute__((sda));
extern char g_hero_position[];          /* the hero's position */
extern SoundRecord g_sound_state[];
extern char D_L17_001A8F20[] MACRO_ADDR;

extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float FastAddRotations(float, float);
extern float vec_distance_xy(void *, void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern int FloatToInt(float);
extern int math_fast_float_d(int *);
extern int PlayMobySound(int, int, void *);
extern int part_find_owned_effect_slot(void *, int, int);
extern float IntToFloat(int);
extern void math_update_wrapped_angle_offset(void *, float *, float *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, float *, float *, float, float, float);
extern void snd_stop_voice(int);
extern void SpawnExplosion(void *, int, int, int, int, int, int, int, int,
                          int, int, int, float, float);
extern void part_spawn_masked_debris(void *, int, void *, int, float, float, float, float);
extern void part_spawn_scaled_bolts(void *, int, float);
extern void moby_mark_spawned(void *);

/* Rests at a low and a high height in turn, easing each move along a cosine,
   while bobbing, swaying and spinning; plays its sound while the hero is near
   and is destroyed when hit. */
void UpdateBobbingSpinningObject(Moby *moby)
{
    BobberVars *vars = moby->vars;
    float spin;
    float ratio;
    int color;
    int flash;

    /* Flash bright for 15 frames of every 60, phased by the instance id. */
    flash = (D_L17_001B2748[0] + moby->uid) % 60 < 15;
    color = flash ? 0x80FFFFFF : 0x80404040;
    moby->color = color;
    if (vars->stopped == 1)
        return;

    switch (vars->state) {
    case 0:
        /* First update: pick the rise, the spin and a random point in the cycle. */
        vars->baseZ = moby->position[2];
        vars->rise = math_random_float_range(vars->minRise, vars->maxRise);
        spin = math_random_float_range(0.004363324f, 0.013089972f);
        if (math_random_int_below(2))
            spin = -spin;
        vars->spinSpeed = spin;
        vars->sound = -1;
        if (math_random_int_below(2)) {
            moby->position[2] += vars->rise;
            vars->state = 3;
        } else {
            vars->state = 1;
        }
        vars->timer = math_random_int_range(FloatToInt(vars->minWait * 60.0f),
                                    FloatToInt(vars->maxWait * 60.0f));
        vars->timer = math_random_int_range(0, vars->timer);
        break;

    case 1:
        /* Resting low. */
        if (math_fast_float_d(&vars->timer)) {
            vars->timer = FloatToInt(vars->riseTime * 60.0f);
            vars->state = 2;
        }
        moby->position[2] = vars->baseZ;
        break;

    case 2:
        /* Rising. */
        if (math_fast_float_d(&vars->timer)) {
            moby->position[2] = vars->baseZ + vars->rise;
            vars->state = 3;
            vars->timer = math_random_int_range(FloatToInt(vars->minWait * 60.0f),
                                        FloatToInt(vars->maxWait * 60.0f));
        } else {
            ratio = IntToFloat(vars->timer) / (vars->riseTime * 60.0f);
            moby->position[2] = vars->baseZ +
                vars->rise * (math_fast_sin_or_cos_a(ratio * 3.141593f) * 0.5f) +
                vars->rise * 0.5f;
        }
        break;

    case 3:
        /* Resting high. */
        if (math_fast_float_d(&vars->timer)) {
            vars->timer = FloatToInt(vars->fallTime * 60.0f);
            vars->state = 4;
        }
        moby->position[2] = vars->baseZ + vars->rise;
        break;

    case 4:
        /* Falling. */
        if (math_fast_float_d(&vars->timer)) {
            moby->position[2] = vars->baseZ;
            vars->state = 1;
            vars->timer = math_random_int_range(FloatToInt(vars->minWait * 60.0f),
                                        FloatToInt(vars->maxWait * 60.0f));
        } else {
            ratio = IntToFloat(vars->timer) / (vars->fallTime * 60.0f);
            moby->position[2] = vars->baseZ +
                vars->rise * (math_fast_sin_or_cos_a((1.0f - ratio) * 3.141593f) * 0.5f) +
                vars->rise * 0.5f;
        }
        break;
    }

    /* The periods are in seconds: 0.00029088825 is one degree per second, in radians per frame. */
    math_update_wrapped_angle_offset(moby, &vars->bobPhase, &vars->bobOffset, D_L17_001B024C,
                  360.0f / D_L17_001B0248 * 0.00029088825f, moby->position[2]);
    moby_scale_owner_words_by_angles(moby, &vars->swayPhase, &vars->tiltPhase, D_L17_001B0250,
                  360.0f / D_L17_001B0254 * 0.00029088825f,
                  360.0f / D_L17_001B0258 * 0.00029088825f);
    moby->rotation[2] = FastAddRotations(moby->rotation[2], vars->spinSpeed);

    if (vec_distance_xy(moby->position, g_hero_position) < 80.0f) {
        SoundVoice *voice = (SoundVoice *)&g_sound_state[vars->sound];
        if (voice->owner != moby || !voice->active)
            vars->sound = PlayMobySound(0, 4, moby);
    } else {
        int sound = vars->sound;
        if (sound != -1) {
            SoundVoice *voice = (SoundVoice *)&g_sound_state[sound];
            if (voice->owner == moby && voice->active)
                snd_stop_voice(sound);
        }
        vars->sound = -1;
    }

    if (part_find_owned_effect_slot(moby, 0x4010000, 0)) {
        SpawnExplosion(moby->position, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, 0, 10.0f, 20.0f);
        part_spawn_masked_debris(moby, 127, D_L17_001A8F20, 255, 3.0f, 6.0f, 3.0f, 6.0f);
        part_spawn_scaled_bolts(moby, 9, 0);
        moby_mark_spawned(moby);
    } else {
        moby->impactSlot = 255;
    }
}
