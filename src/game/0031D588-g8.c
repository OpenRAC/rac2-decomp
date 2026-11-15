#include "common.h"

typedef struct __attribute__((packed, aligned(4))) { long long a; int b; } QueryParams;
typedef struct { char *target; int zero; } QueryExclude;
typedef struct { char *item; } Candidate;
typedef struct { unsigned char pad[28]; unsigned char entry; } DamageClasses;
typedef struct { char pad[112]; float value; char tail[108]; } DamageClass;
typedef struct { char pad[0x2290]; char *player; } PlayerRef;
typedef struct { char pad[132]; int value; } SoundRecord;

extern char D_001BF000[];
extern const QueryParams D_001AFE00;
extern char g_item_slot_to_record[];
extern char D_001BAFA0[];
extern char g_sound_state[];
extern char g_hero_state[];
extern char g_weapon_table[];
extern int D_001AFDF4 SDATA(D_001AFDF4);

extern void vec_transform_or_copy(void *, void *);
extern void part_steer_effect_direction(int, void *, int);
extern void FastVecAdd(void *, void *, void *);
extern s32 snd_set_voice_pitch_bend(int, int);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_clear_128(void *);
extern void gravity_get_dir_at_object(void *, void *, int);
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
extern void gfx_register_overlay_draw_callback(void *, void *);
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

/* Updates a flying shot. It moves, damages what it touches, bursts into sparks, sets off a blast around it and then goes away. */
void shot_moby_update(char *self)
{
    char old[16] __attribute__((aligned(16)));
    union { char v[16]; QueryParams params; } temp __attribute__((aligned(16)));
    union {
        char raw[32];
        struct { char *targets[4]; QueryExclude exclude; } query;
    } event __attribute__((aligned(16)));
    int count, i, j, n;
    char *state = *(char **)(self + 0x68), *obj, *data;

    vec_transform_or_copy(self + 0x10, self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        *(unsigned char *)(self + 0x20) = 1;
        *(int *)(state + 0x20) = -1;
        *(int *)(state + 0x24) = -1;
    case 1:
        qcopy(old, self + 0x10);
        part_steer_effect_direction(*(int *)(state + 0x44), state, 0);
        FastVecAdd(self + 0x10, self + 0x10, state);
        snd_set_voice_pitch_bend(*(int *)(state + 0x20), *(int *)(state + 0x24) + math_random_int_range(-200, 200));
        n = coll_process_hit(self + 0x10, 0, self, 0, 0.45f);
        for (i = 0; i < n; i++) {
            obj = ((Candidate *)D_001BF000)[i].item;
            data = moby_get_private_value_0(obj);
            if (*(short *)(obj + 0xAA) == MOBY_CLASS_PLASMA_COIL || obj == ((PlayerRef *)g_hero_state)->player
                || !(*(short *)(obj + 0x34) & 0x1000))
                continue;
            if (data) {
                qcopy(self + 0x10, obj + 0x10);
                gravity_get_dir_at_object(obj, temp.v, 1);
                FastVecScale(temp.v, temp.v, *(float *)(data + 0x10));
                FastVecAdd(self + 0x10, self + 0x10, temp.v);
            }
            *(char **)(state + 0x38) = obj;
            *(int *)(state + 0x10) = 15;
            *(unsigned char *)(self + 0x20) = 2;
            qcopy(temp.v, state);
            vec_clear_128(state);
            vec_scale_to_length(temp.v, temp.v, 0.033333335f);
            make_hit_descriptor(event.raw, self, 0x210000, temp.v,
                          ((DamageClass *)g_weapon_table)[((DamageClasses *)g_item_slot_to_record)->entry].value);
            *(unsigned char *)(event.raw + 24) = 1;
            *(unsigned char *)(event.raw + 25) = 3;
            *(short *)(event.raw + 26) = *(short *)(self + 0xAA);
            QueueMobyImpact(obj, event.raw);
            part_spawn_hit_sparks(self + 0x10, 10, 1);
            StartAttachedEffect(obj, 28, *(int *)(self + 0xB8));
            break;
        }
        if (!*(char **)(state + 0x38)) {
            int hit;
            if (CollLine(old, self + 0x10, 2, self, 0))
                hit = 1;
            else
                hit = coll_test_point(self + 0x10, 2, self, 0.1f) != 0;
            if (hit == 1) {
                qcopy(self + 0x10, D_001BAFA0);
                FastVecScale(temp.v, D_001BAFA0 + 0x20, 0.0009765625f);
                vec_scale_to_length(temp.v, temp.v, 0.1f);
                FastVecAdd(self + 0x10, temp.v, self + 0x10);
                *(int *)(state + 0x10) = 15;
                *(unsigned char *)(self + 0x20) = 2;
                part_spawn_hit_sparks(self + 0x10, 15, 0);
            }
        }
        if (math_fast_float_d(state + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            *(int *)(state + 0x10) = 161;
        }
        break;
    case 2: {
        char *info;
        if (*(char **)(state + 0x38)) {
            info = moby_get_private_value_0(*(char **)(state + 0x38));
            if (info) {
                gravity_get_dir_at_object(*(char **)(state + 0x38), temp.v, 1);
                FastVecScale(temp.v, temp.v, *(float *)(info + 0x10));
                FastVecAdd(self + 0x10, temp.v, *(char **)(state + 0x38) + 0x10);
            }
        }
        if (math_fast_float_d(state + 0x10)) {
            *(unsigned char *)(self + 0x20) = 4;
            temp.params = D_001AFE00;
            event.query.exclude = (QueryExclude){*(char **)(state + 0x38), 0};
            SelectBestTargetInCone(self + 0x10, self + 0xC0, 6.2831855f, 6.2831855f, &count,
                          event.query.targets, 3, &event.query.exclude,
                          10.0f, 0.0f, 0.0f, 0, &temp.params);
            for (i = 0; i < count; i++) {
                for (j = 4; j >= 0; j--)
                    spark_spawn_targeted(self, event.query.targets[i], 10);
                PlayMobySound(1, 0, self);
            }
        }
        break;
    }
    case 3:
        break;
    case 4: {
        char *info;
        if (*(char **)(state + 0x38)) {
            if (!D_001AFDF4) {
                D_001AFDF4 = 1;
                PlayMobySound(3, 0, self);
            }
            info = moby_get_private_value_0(*(char **)(state + 0x38));
            if (info) {
                gravity_get_dir_at_object(*(char **)(state + 0x38), temp.v, 1);
                FastVecScale(temp.v, temp.v, *(float *)(info + 0x10));
                FastVecAdd(self + 0x10, temp.v, *(char **)(state + 0x38) + 0x10);
            }
        }
        if (!*(int *)(state + 0x1C)) {
            spark_destroy_moby_free_slot(self);
            if (!*(char **)(state + 0x38)) {
                part_spawn_hit_sparks(self + 0x10, 10, 1);
                PlayMobySound(2, 0, self);
            }
        }
    }
    }
    if (*(unsigned char *)(self + 0x20) != 4) {
        if (!snd_is_voice_playing_for_owner(self, *(int *)(state + 0x20)))
            *(int *)(state + 0x20) = PlayMobySound(0, 4, self);
        if (*(int *)(state + 0x24) == -1) {
            char *rec = g_sound_state + *(int *)(state + 0x20) * 112;
            *(int *)(state + 0x24) = ((SoundRecord *)rec)->value;
        }
    } else if (*(int *)(state + 0x20) != -1) {
        char *rec = g_sound_state + *(int *)(state + 0x20) * 112;
        if (*(char **)(rec + 0x88) == self && *(unsigned char *)(rec + 0x74))
            snd_stop_voice(*(int *)(state + 0x20));
        *(int *)(state + 0x20) = -1;
    }
    spark_update_targeted(self);
    glow_ring_update_entries(self);
    if (!save_is_record_value(*(int *)(state + 0x40), *(int *)(state + 0x3C))) {
        table_clear_entry_flag(*(int *)(state + 0x44));
        moby_mark_spawned(self);
    } else {
        gfx_register_overlay_draw_callback((void *)part_spawn_spark_burst, self);
    }
}
