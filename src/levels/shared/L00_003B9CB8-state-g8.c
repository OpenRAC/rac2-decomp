#include "common.h"

/* Measured prefixes of the hit packet, material entry and selector. */
typedef struct {
    char prefix[24];
    unsigned char field_18, field_19;
    unsigned short id;
    char tail[20];
} EffectHitPacket;

typedef struct {
    char prefix[0x70];
    float scale;
    char tail[0x6C];
} EffectMaterialEntry;

typedef struct { int x, y, z; } EffectAngles;

/* The effect object and the state block it points to; only the fields used here. */
typedef struct {
    char pad00[0x34];
    int timer;
    char pad38[0x4C - 0x38];
    float intensity;
    int f50;
    int f54;
    int f58;
    int light_index;
} EffectState;

typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char phase;
    char pad21[0x68 - 0x21];
    EffectState *state;
    char pad6C[0xAA - 0x6C];
    unsigned short id;
    char padAC[0xB8 - 0xAC];
    int f_B8;
    char padBC[0xC0 - 0xBC];
    float f_C0[4];
} EffectObject;
typedef struct {
    unsigned char prefix[0x1C];
    unsigned char index;
} EffectMaterialSelector;

extern EffectAngles D_L00_001AFDA8;
extern EffectMaterialSelector g_item_slot_to_record;
extern EffectMaterialEntry g_weapon_l00_table[];
extern int D_L00_001AFDA0 __attribute__((sda));
extern char *spark_move_projectile(EffectObject *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);

extern void QueueMobyImpact(void *, void *);
extern int StartAttachedEffect(void *, int, int);
/* The integer and FP register banks retain their own argument order. */
extern char *SelectBestTargetInCone(void *, float, void *, float, float, float, void *,
                          void *, int, int, float, int, void *);
extern int pair_is_owner_key_free(void *, void *);
extern void KeyOwnerTableInsert(void *, void *, int);
extern void spark_spawn_orbiting_record(void *, void *, int);
extern int PlayMobySound(int, int, void *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern void vec_clear_128(void *);
extern void *part_spawn_ground_effect(void *, float, float, int, unsigned int, int, int,
                          void *, float, int);
extern void moby_get_facing_direction(void *, void *);
extern void part_l00_spawn_spark_burst_2(void *, void *, int, int);
extern void table_clear_entry_flag(int);
extern void pair_clear_owner_key_entries(void *);
extern void gfx_free_point_light(int);
extern void moby_mark_spawned(void *);
extern void effect_update_spark_slots(void *);
extern void spark_update_orbit(void *);
extern void ref_L00_003BAC30_00(void *, EffectObject *);
extern void spark_draw_projectile(void *);

/* Updates motion and hits, then shrinks, emits particles and releases resources. */
/* Per-frame update of the moby class 2473 effect: it hurts and pushes nearby things, fades out,
   then removes itself. */
void UpdateMovingEffectState(EffectObject *self)
{
    EffectAngles angles;
    char *hits[16];
    char vector[16];
    EffectHitPacket packet;
    int hit_count;
    EffectState *state = self->state;
    char *hit_target;
    int i;
    int light_handle;
    int class_index;
    EffectMaterialEntry *class_entry;
    float scale;
    float ratio;

    angles = D_L00_001AFDA8;
    switch (self->phase) {
    case 0:
    case 1:
        state->intensity += (0.6f - state->intensity) * 0.125f;
        hit_target = spark_move_projectile(self);
        if (hit_target) {
            qcopy(vector, state);
            vec_scale_to_length(vector, vector, 0.033333335f);
            class_index = g_item_slot_to_record.index;
            class_entry = g_weapon_l00_table + class_index;
            scale = class_entry->scale;
            make_hit_descriptor(&packet, self, 0x210000, scale, vector);
            packet.field_18 = 1;
            packet.field_19 = 3;
            packet.id = self->id;
            QueueMobyImpact(hit_target, &packet);
            StartAttachedEffect(hit_target, 0x3E, self->f_B8);
        }
        SelectBestTargetInCone(self->position, 6.2831855f, self->f_C0, 6.2831855f, 15.0f, 0.0f,
                      &hit_count, hits, 15, 0, 0.0f, 0, &angles);
        for (i = 0; i < hit_count; i++) {
            if (state->f54 < 15 && pair_is_owner_key_free(self, hits[i])) {
                KeyOwnerTableInsert(self, hits[i], 120);
                spark_spawn_orbiting_record(self, hits[i], 10);
                PlayMobySound(0, 0, self);
            }
        }
        if (math_fast_float_d(&state->timer)) {
            self->phase = 2;
            state->timer = 40;
        }
        break;
    case 2:
        spark_move_projectile(self);
        ratio = IntToFloat(state->timer) / IntToFloat(40);
        state->intensity = ratio * 0.5900000333786011f + 0.01f;
        self->position[0] += math_random_float_range(-0.1f, 0.1f);
        self->position[1] += math_random_float_range(-0.1f, 0.1f);
        self->position[2] += math_random_float_range(-0.1f, 0.1f);
        vec_clear_128(vector);
        part_spawn_ground_effect(self->position, 0.15f, 1.5f, 60, 0x4FFF0000, 0, 2, vector, 0.0013888889225199819f, 1);
        part_spawn_ground_effect(self->position, 0.125f, 1.25f, 60, 0x7FFFFFFF, 0, 2, vector, 0.0013888889225199819f, 1);
        if (math_fast_float_d(&state->timer))
            self->phase = 3;
        break;
    case 3:
        if (state->f54 == 0 && state->f58 == 0) {
            moby_get_facing_direction(self->position, &packet);
            part_l00_spawn_spark_burst_2(self->position, &packet, 6, 0x72FF);
            part_l00_spawn_spark_burst_2(self->position, &packet, 6, 0xFF0000);
            table_clear_entry_flag(state->f50);
            pair_clear_owner_key_entries(self);
            light_handle = state->light_index;
            D_L00_001AFDA0--;
            if (light_handle != -1)
                gfx_free_point_light(light_handle);
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    effect_update_spark_slots(self);
    spark_update_orbit(self);
    ref_L00_003BAC30_00(spark_draw_projectile, self);
}
