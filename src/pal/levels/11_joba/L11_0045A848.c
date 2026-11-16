#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *a0, int a1, int a2);
extern void set_moby_color(void *a0, int a1, int a2, int a3);
extern float math_random_float_range(float a, float b);
extern void anim_start_blended(void *a0, int a1, int a2, int a3);
extern void vec_clear_128(void *);
extern int moby_spawn_linked(char *, int, float, float);

/* Aims the object's stage, re-arms its effect and stores the new heading. */
void drone_init_state_pal(char *moby, int delay, int is_arena_mode)
{
    char *vars = *(char **)(moby + 0x68);
    char *definition;
    unsigned short flags;
    int anim_flags;
    float value;

    value = (float)*(short *)(vars + 0x24);
    *(short *)(vars + 0x1FC) = is_arena_mode;
    *(short *)(vars + 0x1EC) = 0;
    *(unsigned char *)(vars + 0x2E) = 1;
    *(float *)(vars + 0x20) = value;
    if (*(unsigned char *)(moby + 0x43) != 0)
        anim_start_blended(moby, 0, 0, 8);
    flags = *(unsigned short *)(moby + 0x34);
    *(unsigned char *)(moby + 0x7F) = 0;
    *(unsigned short *)(moby + 0x34) = (flags | 0x1000) & 0xFFB9;
    definition = *(char **)(moby + 0x24);
    anim_flags = *(int *)(definition + 0x10);
    *(int *)(moby + 0x98) = anim_flags;
    if (*(short *)(vars + 0x1FC) != 0) {
        moby_set_state(moby, 7, 3);
        *(unsigned short *)(moby + 0x34) |= 0x100;
        moby_spawn_linked(moby, 0, 2.0f, 2.0f);
    } else {
        moby_set_state(moby, 3, 1);
        *(unsigned char *)(moby + 0x31) = 1;
        *(unsigned short *)(moby + 0x34) &= 0xFEFE;
    }
    vec_clear_128(vars + 0x1B0);
    value = math_random_float_range(20.0f, 30.0f) * 0.017453294f;
    *(short *)(vars + 0x1EE) = delay;
    *(float *)(vars + 0x1CC) = value;
    if (*(short *)(vars + 0x50) != 0) {
        *(short *)(vars + 0x50) = 0;
        set_moby_color(moby, *(int *)(vars + 0x1F0), *(int *)(vars + 0x1F4), *(int *)(vars + 0x1F8));
        *(short *)(vars + 0x52) = 1;
    }
}

extern void func_002A05A8(void *a0);
extern void arena_add_waiting_fighter(char *p, int id);
extern void snd_stop_voice(int index);
extern int snd_play_from_class_bank(int index, int value, char *object, int kind);
extern char *SpawnExplosion(char *, int, int, int, int, int, int, int, float, float, int,
                         int, int, int);
extern char g_sound_state[];

/* Releases the object's slot in the shared table and drops it to the idle flag block. */
void drone_reset_to_idle_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int voice_index = *(int *)(vars + 0x1DC);
    char *voice;

    if (voice_index != -1) {
        voice = g_sound_state + voice_index * 0x70;
        if (*(char **)(voice + 0x88) == moby && *(unsigned char *)(voice + 0x74) != 0)
            snd_stop_voice(voice_index);
    }
    *(int *)(vars + 0x1DC) = -1;
    if (*(short *)(vars + 0x1EC) == 1) {
        *(short *)(vars + 0x1EC) = 0;
        arena_add_waiting_fighter(*(char **)(moby + 0xB8), *(short *)(moby + 0xAA));
    }
    if (*(unsigned char *)(moby + 0x31) != 0) {
        SpawnExplosion(moby + 0x10, 0, 10, 30, 0, 10, 45, 1, 0.3f, 0.0f, 0, 0, 0, 0);
        snd_play_from_class_bank(0, 0, moby, 0xDF7);
    }
    anim_start_blended(moby, 0, 0, 3);
    func_002A05A8(moby);
    moby_set_state(moby, 1, 0);
    *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & 0xEFFF) | 0x47;
    *(int *)(moby + 0x98) = 0;
    *(unsigned char *)(moby + 0x31) = 0;
    *(short *)(vars + 0x1EC) = 0;
    *(int *)(vars + 0x1C4) = 0;
}


typedef struct {
    u8 pad00[0x10];
    float position[4];
    u8 stage;
    u8 pad21[0x10];
    u8 active;
    u8 pad32[0x68 - 0x32];
    void *state;
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0xAA - 0x70];
    s16 id;
} JobaObject;
typedef struct {
    u8 pad00[0x20];
    JobaObject *object;
    u8 pad24[8];
    s32 f2C;
} HitRecord;
typedef struct {
    u8 pad00[0x28];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 pad34[0x48 - 0x34];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    char contact[0x10];
    u8 f60;
    u8 pad61[0x80 - 0x61];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xE0 - 0x9C];
    s32 fE0;
    float fE4;
    u8 padE8[0x100 - 0xE8];
    float f100;
    float f104;
    float f108;
    float f10C;
    float f110;
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x256 - 0x138];
    s16 f256;
} JobaActorState;
extern JobaObject *g_damage_target_list[];
extern int FloatToInt(float);
extern HitRecord *part_find_owned_effect_slot(void *, int, int);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern char g_hero_l11_position[];
extern void fighter_reset_to_idle(char *);
extern void fighter_update_lock_on(char *);

/* func_L11_00454F18 lives in L11_00454F18-g8.c. */

/* Sets up the actor's tuning on its first stage, handles contacts while active, and runs the
   attack-state update. */
void fighter_update_contacts_pal(JobaObject *obj)
{
    JobaActorState *state = obj->state;
    HitRecord *hit;
    JobaObject *other;

    if (obj->stage == 0) {
        state->f48 = FloatToInt(15.0f);
        state->f4A = FloatToInt(12.0f);
        state->f80 = 0.5f;
        state->f84 = 0.5f;
        state->f108 = 0.5f;
        state->f256 = 0;
        state->f60 = 13;
        state->f98 = 4;
        state->f8C = 0.4f;
        state->f100 = 1.0f;
        state->f104 = 0.25f;
        state->f10C = 0.5f;
        state->f110 = 1.57079649f;
        state->f130 = 0.52359885f;
        state->f134 = 0.01f;
        state->f12C = 0.008f;
        state->f28 = 3;
        state->f30 = 0.75f;
        state->f29 = 1;
        fighter_reset_to_idle((char *)obj);
    }

    if (obj->active) {
        if (obj->stage >= 3) {
            hit = part_find_owned_effect_slot(obj, 0x10000, 1);
            if (hit && (other = hit->object) && !obj->active) {
                if (other->id == 0xDF9 || other->id == 0xB89)
                    hit->f2C = 0;
            }
            if (moby_apply_damage_to_object_pal(obj, state->contact, 0) == 5) {
                state->fE0 = 0;
                state->fE4 = 1.0053098f;
            }
        }
        if (obj->active && fast_vec_dist(obj->position, g_hero_l11_position) < 24.0f) {
            moby_update_ground_check(obj);
            obj->f6F = 22;
        }
    }

    if (obj->stage >= 2 && state->f2E == 2)
        fighter_reset_to_idle((char *)obj);
    fighter_update_lock_on((char *)obj);
}

