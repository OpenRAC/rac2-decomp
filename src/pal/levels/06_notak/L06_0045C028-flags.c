#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } TriggerVector;
extern u8 g_sound_state[];
extern void moby_set_state(u8 *, u8, s32);
extern s32 PlayMobySound(s32, s32, char *);
extern float FastAddRotations(float, float);
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern void snd_stop_voice(s32);
extern s32 moby_count_group_not_in_state(s32, s32);
extern void part_spawn_scaled_bolts_pal(void *, s32, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_spawn_masked_debris_pal(char *, s32, void *, u8, float, float, float, float);
extern void moby_mark_spawned(void *);

/* Keep the trigger slot alive until touched, then release it and emit the final burst. */
void trigger_slot_burst_update_pal(u8 *object)
{
    TriggerVector offset;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *record;
    s32 slot;

    switch (object[0x20]) {
    case 0:
        moby_set_state(object, 1, -1);
        break;
    case 1:
        {
            u8 *active = g_sound_state + *(s32 *)(state + 0xC) * 0x70;
            if (*(u8 **)(active + 0x88) != object || !active[0x74])
                *(s32 *)(state + 0xC) = PlayMobySound(1, 4, (char *)object);
        }
        *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), *(float *)(state + 4) * 0.0003490659f);
        if (part_find_owned_effect_slot(object, 0x4010000, 0) && *(s32 *)state == 0) {
            PlayMobySound(0, 0, (char *)object);
            moby_set_state(object, 2, -1);
            slot = *(s32 *)(state + 0xC);
            if (slot != -1) {
                record = g_sound_state + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74])
                    snd_stop_voice(slot);
            }
            *(s32 *)(state + 0xC) = -1;
        }
        object[0xA8] = 0xFF;
        break;
    case 2:
        if (moby_count_group_not_in_state(*(s32 *)(state + 8), -1) == 1)
            part_spawn_scaled_bolts_pal(object, 15, 0.0f);
        offset.quad = 0;
        offset.f[0] = -0.14000002f;
        matrix_mul_vec3(&offset, &offset, object + 0xC0);
        part_spawn_masked_debris_pal((char *)object, 31, &offset, 255, 3.0f, 6.0f, 3.0f, 6.0f);
        moby_mark_spawned(object);
        break;
    }
}
