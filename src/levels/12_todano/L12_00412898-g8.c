#include "common.h"

extern s32 flag_is_third_pending_set(void);
extern void snd_stop_voice(s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void moby_mark_spawned(void *);
extern void set_moby_color(void *, s32, s32, s32);
extern void coll_push_out_of_rectangle(void *, void *);
extern s32 FloatToInt(f32);
extern void gfx_free_point_light(s32);
extern void offset_moby_class_point_pairs(void *, s32, s32);

extern char g_moby_nibble_table[];
extern u8 g_sound_state[];
extern u8 g_level_event_flag_b[];

typedef struct {
    u8 pad[0x464];
    u8 flags[0];
} TodanoObjectFlags;

extern TodanoObjectFlags g_object_flags;
extern s32 g_current_map_index MACRO_ADDR;
extern u8 *g_moby_list_start __attribute__((sda));
extern f32 g_guard_state_decrement __attribute__((sda));
extern s32 g_guard_alarm_bit_shift __attribute__((sda));
extern s32 g_frame_l12_counter MACRO_ADDR;

/* Each object has a three-bit counter in one half of a packed byte. */
#define OBJECT_COUNTERS(o) \
    ((u8 *)D_0019B4A8)[((s16)*(u16 *)((o) + 0xB2) >> 1) + (D_001A79F0 << 10)]
#define INCREMENT_OBJECT_COUNTER(o) { \
    if (*(u16 *)((o) + 0xB2) & 1) { \
        if (((OBJECT_COUNTERS(o) >> 4) & 7) != 7) OBJECT_COUNTERS(o) += 16; \
    } else { \
        if ((OBJECT_COUNTERS(o) & 7) != 7) OBJECT_COUNTERS(o)++; \
    } \
}

/* Shows a looping effect until the object it is linked to has been used up, then fades itself
   out and removes itself. */
void UpdateLinkedMobyFade(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    s32 delta;
    u16 index;
    s32 bits;
    TodanoObjectFlags *record;

    if (flag_is_third_pending_set()) goto kill;
    index = *(u16 *)(object + 0xB2);
    record = &g_object_flags;
    if (record->flags[(s16)index]) goto kill;
    bits = (u8)g_moby_nibble_table[((s16)index >> 1) + (g_current_map_index << 10)];
    if (index & 1) {
        if ((bits >> 4) & 7) goto kill;
    } else if (bits & 7) {
        goto kill;
    }
    goto dispatch;

kill: {
        s32 id;
        u8 *effect;

        g_level_event_flag_b[0] = 1;
        INCREMENT_OBJECT_COUNTER(object);
        id = *(s32 *)(state + 0x10);
        if (id != -1) {
            effect = g_sound_state + id * 0x70;
            if (*(u8 **)(effect + 0x88) == object && effect[0x74])
                snd_stop_voice(id);
        }
        *(s32 *)(state + 0x10) = -1;
        moby_mark_spawned(object);
        return;
    }

dispatch:
    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        object[0x23] = 20;
        *(u16 *)(object + 0x34) |= 0xA08;
        *(s16 *)(state + 0xE) = -1;
        *(f32 *)(state + 4) = 1.0f;
        set_moby_color(object, 0x80, 0x80, 0x80);
        break;
    case 1: {
        u8 *effect;
        u16 index;
        s32 bits;

        effect = g_sound_state + *(s32 *)(state + 0x10) * 0x70;
        if (*(u8 **)(effect + 0x88) != object || !effect[0x74])
            *(s32 *)(state + 0x10) = PlayMobySound(0, 4, object);
        {
            s32 id = *(s32 *)state;
            u8 *linked;

            if (id != -1) {
                linked = g_moby_list_start + (id << 8);
                if (!linked || linked[0x20] == 0xFE || linked[0x20] == 0xFD)
                    goto activate;
                index = *(u16 *)(linked + 0xB2);
                bits = (u8)g_moby_nibble_table[((s16)index >> 1) + (g_current_map_index << 10)];
                if (index & 1) {
                    if ((bits >> 4) & 7) goto activate;
                    else goto update;
                } else if (!(bits & 7)) {
                    goto update;
                }
activate: {
                    *(f32 *)(state + 4) = 1.0f;
                    object[0x20] = 2;
                    INCREMENT_OBJECT_COUNTER(object);
                }
            }
        }
update:
        coll_push_out_of_rectangle(object, state);
        break;
    }
    case 2:
        *(f32 *)(state + 4) -= g_guard_state_decrement;
        if (*(f32 *)(state + 4) < 0.0f)
            object[0x20] = 3;
        else
            object[0x23] = FloatToInt(*(f32 *)(state + 4) * 20.0f);
        break;
    case 3: {
        s32 id;
        u8 *effect;

        id = *(s32 *)(state + 0x10);
        if (id != -1) {
            effect = g_sound_state + id * 0x70;
            if (*(u8 **)(effect + 0x88) == object && effect[0x74])
                snd_stop_voice(id);
        }
        *(s32 *)(state + 0x10) = -1;
        if (*(s16 *)(state + 0xE) != -1) {
            gfx_free_point_light(*(s16 *)(state + 0xE));
            *(s16 *)(state + 0xE) = -1;
        }
        moby_mark_spawned(object);
        return;
    }
    }
    delta = 0xC0;
    *(s16 *)(state + 0xC) += 0xC0;
    if (*(s16 *)(state + 0xC) > 0x1000) {
        *(s16 *)(state + 0xC) -= 0x1000;
        delta = -0xF40;
    } else if (*(s16 *)(state + 0xC) < 0) {
        *(s16 *)(state + 0xC) += 0x1000;
        delta = 0x10C0;
    }
    if (!(g_frame_l12_counter << g_guard_alarm_bit_shift))
        offset_moby_class_point_pairs(*(void **)(object + 0x24), delta, 0);
}
