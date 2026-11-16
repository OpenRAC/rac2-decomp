#include "common.h"

typedef struct __attribute__((packed, aligned(4))) { long long a; int b; } QueryParams;
typedef struct { char *target; int zero; } QueryExclude;
typedef struct { char *item; } Candidate;
typedef struct { unsigned char pad[28]; unsigned char entry; } DamageClasses;
typedef struct { char pad[112]; float value; char tail[108]; } DamageClass;
typedef struct { char pad[0x2290]; char *player; } PlayerRef;
typedef struct { char pad[132]; int value; } SoundRecord;

extern char g_area_hit_targets[];
extern const QueryParams g_thrown_shot_query_params;
extern char g_item_slot_to_record[];
extern char g_hero_l00_position[];
extern char g_sound_state[];
extern char g_hero_state[];
extern char g_weapon_l00_table[];
extern int g_thrown_shot_initialized SDATA(D_L00_001B0134);

extern void vec_transform_or_copy(void *, void *);
extern void part_steer_effect_direction(int, void *, int);
extern void FastVecAdd(void *, void *, void *);
extern s32 snd_set_voice_pitch_bend(int, int);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_clear_128(void *);
extern void moby_forward_position_call(void *, void *, int);
extern void part_spawn_hit_sparks(void *, int, int);
extern int StartAttachedEffect(void *, int, int);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void spark_spawn_targeted(void *, void *, int);
extern void part_spawn_spark_burst(void *);
extern void spark_destroy_moby_free_slot(void *);
extern void snd_stop_voice(int);
extern void spark_update_targeted(void *);
extern void glow_ring_update_entries(void *);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
extern void ref_L00_003CA730_00(void *, void *);
extern int math_random_int_range(int, int);
extern int coll_process_hit(void *, int, void *, int, float);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_test_point(void *, int, void *, float);
extern int math_fast_float_d(void *);
extern int PlayMobySound(int, int, void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int save_is_record_value(int, int);
extern char *moby_get_private_value_0(void *);
extern char *SelectBestTargetInCone(void *, void *, float, float, int *, void *, int, void *,
                           float, float, float, int, void *);

/* Per-frame update of a thrown shot. It flies forward, sticks to or hits things it touches, explodes to damage nearby enemies, plays its sound and removes itself when its time runs out. */
void thrown_shot_update(char *self)
{
    char prev_pos[16] __attribute__((aligned(16)));
    union { char v[16]; QueryParams params; } scratch __attribute__((aligned(16)));
    union {
        char raw[32];
        struct { char *targets[4]; QueryExclude exclude; } query;
    } message __attribute__((aligned(16)));
    int count, i, j, hit_count;
    char *vars = *(char **)(self + 0x68), *hit_object, *hit_info;

    vec_transform_or_copy(self + 0x10, self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(vars + 0x20) = -1;
        *(int *)(vars + 0x24) = -1;
    case 1:
        qcopy(prev_pos, self + 0x10);
        part_steer_effect_direction(*(int *)(vars + 0x44), vars, 0);
        FastVecAdd(self + 0x10, self + 0x10, vars);
        snd_set_voice_pitch_bend(*(int *)(vars + 0x20), *(int *)(vars + 0x24) + math_random_int_range(-200, 200));
        hit_count = coll_process_hit(self + 0x10, 0, self, 0, 0.45f);
        for (i = 0; i < hit_count; i++) {
            hit_object = ((Candidate *)g_area_hit_targets)[i].item;
            hit_info = moby_get_private_value_0(hit_object);
            if (*(short *)(hit_object + 0xAA) == MOBY_CLASS_PLASMA_COIL || hit_object == ((PlayerRef *)g_hero_state)->player
                || !(*(short *)(hit_object + 0x34) & 0x1000))
                continue;
            if (hit_info) {
                qcopy(self + 0x10, hit_object + 0x10);
                moby_forward_position_call(hit_object, scratch.v, 1);
                FastVecScale(scratch.v, scratch.v, *(float *)(hit_info + 0x10));
                FastVecAdd(self + 0x10, self + 0x10, scratch.v);
            }
            *(char **)(vars + 0x38) = hit_object;
            *(int *)(vars + 0x10) = 15;
            *(unsigned char *)(self + 0x20) = 2;
            qcopy(scratch.v, vars);
            vec_clear_128(vars);
            vec_scale_to_length(scratch.v, scratch.v, 0.033333335f);
            make_hit_descriptor(message.raw, self, 0x210000, scratch.v,
                          ((DamageClass *)g_weapon_l00_table)[((DamageClasses *)g_item_slot_to_record)->entry].value);
            *(unsigned char *)(message.raw + 24) = 1;
            *(unsigned char *)(message.raw + 25) = 3;
            *(short *)(message.raw + 26) = *(short *)(self + 0xAA);
            QueueMobyImpact(hit_object, message.raw);
            part_spawn_hit_sparks(self + 0x10, 10, 1);
            StartAttachedEffect(hit_object, 28, *(int *)(self + 0xB8));
            break;
        }
        if (!*(char **)(vars + 0x38)) {
            int did_hit;
            if (CollLine(prev_pos, self + 0x10, 2, self, 0))
                did_hit = 1;
            else
                did_hit = coll_test_point(self + 0x10, 2, self, 0.1f) != 0;
            if (did_hit == 1) {
                qcopy(self + 0x10, g_hero_l00_position);
                FastVecScale(scratch.v, g_hero_l00_position + 0x20, 0.0009765625f);
                vec_scale_to_length(scratch.v, scratch.v, 0.1f);
                FastVecAdd(self + 0x10, scratch.v, self + 0x10);
                *(int *)(vars + 0x10) = 15;
                *(unsigned char *)(self + 0x20) = 2;
                part_spawn_hit_sparks(self + 0x10, 15, 0);
            }
        }
        if (math_fast_float_d(vars + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(vars + 0x10) = 161;
        }
        break;
    case 2: {
        char *hit_info;
        if (*(char **)(vars + 0x38)) {
            hit_info = moby_get_private_value_0(*(char **)(vars + 0x38));
            if (hit_info) {
                moby_forward_position_call(*(char **)(vars + 0x38), scratch.v, 1);
                FastVecScale(scratch.v, scratch.v, *(float *)(hit_info + 0x10));
                FastVecAdd(self + 0x10, scratch.v, *(char **)(vars + 0x38) + 0x10);
            }
        }
        if (math_fast_float_d(vars + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            scratch.params = g_thrown_shot_query_params;
            message.query.exclude = (QueryExclude){*(char **)(vars + 0x38), 0};
            SelectBestTargetInCone(self + 0x10, self + 0xC0, 6.2831855f, 6.2831855f, &count,
                          message.query.targets, 3, &message.query.exclude,
                          10.0f, 0.0f, 0.0f, 0, &scratch.params);
            for (i = 0; i < count; i++) {
                for (j = 4; j >= 0; j--)
                    spark_spawn_targeted(self, message.query.targets[i], 10);
                PlayMobySound(1, 0, self);
            }
        }
        break;
    }
    case 3:
        break;
    case 4: {
        char *hit_info;
        if (*(char **)(vars + 0x38)) {
            if (!g_thrown_shot_initialized) {
                g_thrown_shot_initialized = 1;
                PlayMobySound(3, 0, self);
            }
            hit_info = moby_get_private_value_0(*(char **)(vars + 0x38));
            if (hit_info) {
                moby_forward_position_call(*(char **)(vars + 0x38), scratch.v, 1);
                FastVecScale(scratch.v, scratch.v, *(float *)(hit_info + 0x10));
                FastVecAdd(self + 0x10, scratch.v, *(char **)(vars + 0x38) + 0x10);
            }
        }
        if (!*(int *)(vars + 0x1C)) {
            spark_destroy_moby_free_slot(self);
            if (!*(char **)(vars + 0x38)) {
                part_spawn_hit_sparks(self + 0x10, 10, 1);
                PlayMobySound(2, 0, self);
            }
        }
    }
    }
    if (*(unsigned char *)(self + 0x20) != 4) {
        if (!snd_is_voice_playing_for_owner(self, *(int *)(vars + 0x20)))
            *(int *)(vars + 0x20) = PlayMobySound(0, 4, self);
        if (*(int *)(vars + 0x24) == -1) {
            char *sound_entry = g_sound_state + *(int *)(vars + 0x20) * 112;
            *(int *)(vars + 0x24) = ((SoundRecord *)sound_entry)->value;
        }
    } else if (*(int *)(vars + 0x20) != -1) {
        char *sound_entry = g_sound_state + *(int *)(vars + 0x20) * 112;
        if (*(char **)(sound_entry + 0x88) == self && *(unsigned char *)(sound_entry + 0x74))
            snd_stop_voice(*(int *)(vars + 0x20));
        *(int *)(vars + 0x20) = -1;
    }
    spark_update_targeted(self);
    glow_ring_update_entries(self);
    if (!save_is_record_value(*(int *)(vars + 0x40), *(int *)(vars + 0x3C))) {
        table_clear_entry_flag(*(int *)(vars + 0x44));
        moby_mark_spawned(self);
    } else {
        ref_L00_003CA730_00((void *)part_spawn_spark_burst, self);
    }
}
