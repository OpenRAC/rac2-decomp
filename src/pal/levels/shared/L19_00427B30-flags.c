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

/* Shows a glowing level marker that fades out when its linked object is activated, then removes itself (PAL). */
void level_marker_update_fading_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float scale = 9.77f;
    int flags;
    int step;
    if (*(short *)(moby + 0xaa) == 0x1204)
        scale = 6.2f;
    switch (moby[0x20]) {
    case 0:
        *(int *)(vars + 0x14) = -1;
        moby[0x23] = 0x50;
        moby[0x20] = 1;
        *(unsigned short *)(moby + 0x34) |= 0xb0c;
        vec_scale_to_length(moby + 0xc0, moby + 0xc0, *(float *)(vars + 0xc) / scale);
        vec_scale_to_length(moby + 0xd0, moby + 0xd0, 0.8f);
        *(float *)(moby + 0xc) *= *(float *)(vars + 0xc) / scale;
        *(short *)(vars + 0xa) = -1;
        *(float *)(vars + 4) = 1.0f;
        set_moby_color(moby, 0x80, 0x80, 0x80);
        if (moby[0xb0] != 0xff && (g_moby_group_flags[moby[0xb0] + g_current_map_index * 16] & 0x80))
            moby_set_state(moby, 3, -1);
        break;
    case 1: {
        u8 *link = g_sound_state + *(int *)(vars + 0x14) * 0x70;
        int index;
        if (*(u8 **)(link + 0x88) != moby || link[0x74] == 0)
            *(int *)(vars + 0x14) = PlayMobySound(0, 4, (char *)moby);
        index = *(int *)vars;
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
            flags = flag_is_third_pending_set(moby);
        test_active:
            if (!flags)
                break;
        }
    active:
        *(float *)(vars + 4) = 1.0f;
        moby[0x20] = 2;
        break; }
    case 2: {
        int index = *(int *)(vars + 0x14);
        if (index != -1) {
            u8 *entry = g_sound_state + index * 0x70;
            if (*(u8 **)(entry + 0x88) == moby && entry[0x74])
                snd_stop_voice(index);
        }
        *(float *)(vars + 4) -= 0.060000002f;
        *(int *)(vars + 0x14) = -1;
        if (*(float *)(vars + 4) < 0.0f)
            moby[0x20] = 3;
        else
            moby[0x23] = FloatToInt(*(float *)(vars + 4) * 80.0f);
        break; }
    case 3:
        if (*(short *)(vars + 0xa) != -1) {
            gfx_free_point_light(*(short *)(vars + 0xa));
            *(short *)(vars + 0xa) = -1;
        }
        g_marker_slot_table.slot[*(short *)(moby + 0xb2)] = moby[0xb0] + 2;
        if (moby[0xb0] == 0xff || (!(*(g_level_marker_flags + moby[0xb0]) & 0x80) &&
                (g_moby_group_flags[moby[0xb0] + g_current_map_index * 16] & 0x80)))
            g_trigger_active_table.slot[*(short *)(moby + 0xb2)] = moby[0xb0] + 2;
        moby_mark_spawned(moby);
        return;
    }
    step = 0x10;
    *(short *)(vars + 8) += 0x10;
    if (*(short *)(vars + 8) > 0x1000) {
        *(short *)(vars + 8) -= 0x1000;
        step = -0xff0;
    } else if (*(short *)(vars + 8) < 0) {
        *(short *)(vars + 8) += 0x1000;
        step = 0x1010;
    }
    offset_moby_class_point_pairs(*(u8 **)(moby + 0x24), step, 0);
}
