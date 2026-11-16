#include "include_asm.h"
#include "names.h"

#define MACRO_ADDR __attribute__((section(".sdata")))
typedef unsigned char u8;
typedef int s32;
extern u8 g_sound_state[];
extern u8 g_moby_group_flags[];
extern u8 g_moby_nibble_table[];
extern int g_current_map_index MACRO_ADDR;
extern u8 *g_moby_l19_array __attribute__((sda));
extern u8 g_level_marker_flags[] MACRO_ADDR;
typedef struct { u8 pad[0x464]; u8 slot[1]; } SlotTable;
extern SlotTable g_marker_slot_table;
extern SlotTable g_trigger_active_table;
extern void vec_scale_to_length(void *, void *, float);
extern void set_moby_color(void *, int, int, int);
extern void moby_set_state(u8 *, u8, s32);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(s32);
extern s32 flag_is_third_pending_set(u8 *);
extern s32 FloatToInt(float);
extern void gfx_free_point_light(s32);
extern void moby_mark_spawned(void *);
extern void offset_moby_class_point_pairs(unsigned char *, int, int);

void level_marker_update_fading_pal(u8 *actor)
{
    u8 *state = *(u8 **)(actor + 0x68);
    float scale = 9.77f;
    int flags;
    int step;
    if (*(short *)(actor + 0xaa) == 0x1204)
        scale = 6.2f;
    switch (actor[0x20]) {
    case 0:
        *(int *)(state + 0x14) = -1;
        actor[0x23] = 0x50;
        actor[0x20] = 1;
        *(unsigned short *)(actor + 0x34) |= 0xb0c;
        vec_scale_to_length(actor + 0xc0, actor + 0xc0, *(float *)(state + 0xc) / scale);
        vec_scale_to_length(actor + 0xd0, actor + 0xd0, 0.8f);
        *(float *)(actor + 0xc) *= *(float *)(state + 0xc) / scale;
        *(short *)(state + 0xa) = -1;
        *(float *)(state + 4) = 1.0f;
        set_moby_color(actor, 0x80, 0x80, 0x80);
        if (actor[0xb0] != 0xff && (g_moby_group_flags[actor[0xb0] + g_current_map_index * 16] & 0x80))
            moby_set_state(actor, 3, -1);
        break;
    case 1: {
        u8 *link = g_sound_state + *(int *)(state + 0x14) * 0x70;
        int index;
        if (*(u8 **)(link + 0x88) != actor || link[0x74] == 0)
            *(int *)(state + 0x14) = PlayMobySound(0, 4, (char *)actor);
        index = *(int *)state;
        if (index != -1) {
            u8 *entry = g_moby_l19_array + index * 0x100;
            if (entry && entry[0x20] != 0xfe && entry[0x20] != 0xfd) {
                flags = g_moby_nibble_table[((int)(*(unsigned short *)(entry + 0xb2) << 16) >> 17) + g_current_map_index * 0x400];
                if (*(unsigned short *)(entry + 0xb2) & 1) {
                    if ((flags >> 4) & 7)
                        goto active;
                    break;
                } else {
                    flags &= 7;
                    goto test_active;
                }
            }
        } else {
            flags = flag_is_third_pending_set(actor);
        test_active:
            if (!flags)
                break;
        }
    active:
        *(float *)(state + 4) = 1.0f;
        actor[0x20] = 2;
        break; }
    case 2: {
        int index = *(int *)(state + 0x14);
        if (index != -1) {
            u8 *entry = g_sound_state + index * 0x70;
            if (*(u8 **)(entry + 0x88) == actor && entry[0x74])
                snd_stop_voice(index);
        }
        *(float *)(state + 4) -= 0.060000002f;
        *(int *)(state + 0x14) = -1;
        if (*(float *)(state + 4) < 0.0f)
            actor[0x20] = 3;
        else
            actor[0x23] = FloatToInt(*(float *)(state + 4) * 80.0f);
        break; }
    case 3:
        if (*(short *)(state + 0xa) != -1) {
            gfx_free_point_light(*(short *)(state + 0xa));
            *(short *)(state + 0xa) = -1;
        }
        g_marker_slot_table.slot[*(short *)(actor + 0xb2)] = actor[0xb0] + 2;
        if (actor[0xb0] == 0xff || (!(*(g_level_marker_flags + actor[0xb0]) & 0x80) &&
                (g_moby_group_flags[actor[0xb0] + g_current_map_index * 16] & 0x80)))
            g_trigger_active_table.slot[*(short *)(actor + 0xb2)] = actor[0xb0] + 2;
        moby_mark_spawned(actor);
        return;
    }
    step = 0x10;
    *(short *)(state + 8) += 0x10;
    if (*(short *)(state + 8) > 0x1000) {
        *(short *)(state + 8) -= 0x1000;
        step = -0xff0;
    } else if (*(short *)(state + 8) < 0) {
        *(short *)(state + 8) += 0x1000;
        step = 0x1010;
    }
    offset_moby_class_point_pairs(*(u8 **)(actor + 0x24), step, 0);
}
