#include "include_asm.h"

#include "common.h"
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
extern char *func_PAL_L00_003BEE68(EffectObject *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern void QueueMobyImpact(void *, void *);
extern void func_PAL_0032F0B8(void *, int, int);
extern void SelectBestTargetInCone(void *, float, void *, float, float, float, void *,
                          void *, int, int, float, int, void *);
extern int pair_is_owner_key_free(void *, void *);
extern void KeyOwnerTableInsert(void *, void *, int);
extern void func_PAL_L00_003BF548(void *, void *, int);
extern int PlayMobySound(int, int, void *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern void vec_clear_128(void *);
extern void part_spawn_ground_effect(void *, float, float, int, unsigned int, int, int,
                          void *, float, int);
extern void moby_get_facing_direction(void *, void *);
extern void func_PAL_L00_003C11A0(void *, void *, int, int);
extern void table_clear_entry_flag(int);
extern void pair_clear_owner_key_entries(void *);
extern void gfx_free_point_light(int);
extern void moby_mark_spawned(void *);
extern void func_PAL_L00_003BF7F8(void *);
extern void spark_update_orbit(void *);
extern void ref_L00_003BAC30_00(void *, EffectObject *);
extern void func_PAL_L00_003BF2F8(void *);

/* Updates motion and hits, then shrinks, emits particles and releases resources. */
void func_PAL_L01_003BA750(EffectObject *self)
{
    EffectAngles angles;
    char *hits[16];
    char vector[16];
    EffectHitPacket packet;
    int count;
    EffectState *state = self->state;
    char *result;
    int i;
    int handle;
    int material;
    EffectMaterialEntry *entry;
    float scale;
    float ratio;

    angles = D_L00_001AFDA8;
    switch (self->phase) {
    case 0:
    case 1:
        state->intensity += (0.6f - state->intensity) * 0.125f;
        result = func_PAL_L00_003BEE68(self);
        if (result) {
            qcopy(vector, state);
            vec_scale_to_length(vector, vector, 0.040000003f);
            material = g_item_slot_to_record.index;
            entry = g_weapon_l00_table + material;
            scale = entry->scale;
            make_hit_descriptor(&packet, self, 0x210000, scale, vector);
            packet.field_18 = 1;
            packet.field_19 = 3;
            packet.id = self->id;
            QueueMobyImpact(result, &packet);
            func_PAL_0032F0B8(result, 0x3E, self->f_B8);
        }
        SelectBestTargetInCone(self->position, 6.2831855f, self->f_C0, 6.2831855f, 15.0f, 0.0f,
                      &count, hits, 15, 0, 0.0f, 0, &angles);
        for (i = 0; i < count; i++) {
            if (state->f54 < 15 && pair_is_owner_key_free(self, hits[i])) {
                KeyOwnerTableInsert(self, hits[i], 120);
                func_PAL_L00_003BF548(self, hits[i], 10);
                PlayMobySound(0, 0, self);
            }
        }
        if (math_fast_float_d(&state->timer)) {
            self->phase = 2;
            state->timer = 33;
        }
        break;
    case 2:
        func_PAL_L00_003BEE68(self);
        ratio = IntToFloat(state->timer) / IntToFloat(40);
        state->intensity = ratio * 0.5900000333786011f + 0.01f;
        self->position[0] += math_random_float_range(-0.1f, 0.1f);
        self->position[1] += math_random_float_range(-0.1f, 0.1f);
        self->position[2] += math_random_float_range(-0.1f, 0.1f);
        vec_clear_128(vector);
        part_spawn_ground_effect(self->position, 0.15f, 1.5f, 50, 0x4FFF0000, 0, 2, vector, 0.002f, 1);
        part_spawn_ground_effect(self->position, 0.125f, 1.25f, 50, 0x7FFFFFFF, 0, 2, vector, 0.002f, 1);
        if (math_fast_float_d(&state->timer))
            self->phase = 3;
        break;
    case 3:
        if (state->f54 == 0 && state->f58 == 0) {
            moby_get_facing_direction(self->position, &packet);
            func_PAL_L00_003C11A0(self->position, &packet, 6, 0x72FF);
            func_PAL_L00_003C11A0(self->position, &packet, 6, 0xFF0000);
            table_clear_entry_flag(state->f50);
            pair_clear_owner_key_entries(self);
            handle = state->light_index;
            D_L00_001AFDA0--;
            if (handle != -1)
                gfx_free_point_light(handle);
            moby_mark_spawned(self);
            return;
        }
        break;
    }
    func_PAL_L00_003BF7F8(self);
    spark_update_orbit(self);
    ref_L00_003BAC30_00(func_PAL_L00_003BF2F8, self);
}
