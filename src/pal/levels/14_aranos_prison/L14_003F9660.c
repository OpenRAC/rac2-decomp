#include "include_asm.h"
#include "common.h"

extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern int IsPointInCuboid(void *, int);
extern void moby_rotate_about_point(void *, void *, float, float, float);
extern int subtitle_request_voice_line(int, int);
extern int flag_is_byte_set(void);
extern int menu_seek_chain_entry(int, int);
extern void gfx_run_screen_update_steps(int);
extern char g_hero_position[];
extern char g_identity_l14_matrix[] __attribute__((sda));
extern char *D_L14_001B259C_direct __asm__("D_L14_001B259C") __attribute__((sda));

/* Help-message (subtitle) history: how often each message was shown, when, and in which levels. */
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
typedef struct {
    char pad[4];
    unsigned char level;
    char rest[0xDB];
} PrisonGadget;
typedef struct {
    int zone[4];
    int row;
    int hintZone;
    int count;
    int pad1C;
    int target;
    char *moby;
    int active;
} PrisonHelpState;
extern SubtitleHistory g_subtitle_history[];
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_help_prompt_flags;
extern u8 g_moby_group_flags[];
extern PrisonGadget g_item_l14_materials[];
extern int g_shop_mode __attribute__((sda));
extern short g_help_l14_prompt_flags[] __attribute__((sda));
extern unsigned int g_frame_counter __attribute__((sda));
extern int g_current_map_index __attribute__((sda));

/* True once the gadget in slot 10 has reached level MAX. */
static inline int prisonGadgetUpgraded(int max)
{
    int level = (g_item_l14_materials + g_item_slot_to_record[10])->level;
    return level >= max;
}

/* Shows help message MSG unless its history entry IDX says it was shown in the last 18 seconds. */
static inline void prisonHelpTimed(int msg, int idx)
{
    if (((int)g_frame_counter * 5 + 2) / 6 - g_subtitle_history[idx].time > 900 || !g_subtitle_history[idx].time)
        subtitle_request_voice_line(msg, idx);
    else if (g_subtitle_history[idx].time < ((int)g_frame_counter * 5 + 2) / 6)
        g_subtitle_history[idx].time = ((int)g_frame_counter * 5 + 2) / 6;
}

/* The first time only records history entry IDX as seen in this level; later times show MSG. */
static inline void prisonHelp(int msg, int idx)
{
    if (g_subtitle_history[idx].count) {
        prisonHelpTimed(msg, idx);
    } else {
        g_subtitle_history[idx].count++;
        if (g_subtitle_history[idx].time < ((int)g_frame_counter * 5 + 2) / 6)
            g_subtitle_history[idx].time = ((int)g_frame_counter * 5 + 2) / 6;
        g_subtitle_history[idx].levels = (g_subtitle_history[idx].levels | (1u << g_current_map_index)) | 0x80000000u;
    }
}

/* func_PAL_L14_003F9660, the PAL copy of func_L14_003F4F98: the same C, where the help timers
   run on the 50 Hz scale and the gadget level comes from func_00288D58. */
void func_PAL_L14_003F9660(char *obj)
{
    PrisonHelpState *st = *(PrisonHelpState **)(obj + 0x68);
    float vel[4] __attribute__((aligned(16)));
    int max = flag_is_byte_set() ? 5 : 2;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(short *)(obj + 0x96) = 0;
        *(unsigned char *)(obj + 0x30) = 0xFF;
        if (st->target >= 0)
            st->moby = D_L14_001B259C_direct + (st->target << 8);
        else
            st->moby = 0;
        if (!prisonGadgetUpgraded(max)) {
            if (st->moby)
                st->active = 1;
            else
                st->active = 0;
        } else {
            if (st->moby) {
                *(unsigned short *)(st->moby + 0x34) |= 1;
                st->moby[0x31] = 0;
            }
            st->active = 0;
        }
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(obj))
            st->count = 0;
        if (IsPointInCuboid(g_hero_position, st->zone[0])) {
            if (!prisonGadgetUpgraded(max))
                moby_set_state(obj, 2, -1);
        }
        if (st->active) {
            qcopy(vel, g_identity_l14_matrix);
            vel[1] -= 0.1f;
            moby_rotate_about_point(st->moby, vel, 0.05f, 0.0f, 0.0f);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj))
            st->count = 0;
        if (g_shop_mode != 2 && st->count >= 6) {
            menu_seek_chain_entry(10, max);
            gfx_run_screen_update_steps(2);
            if (st->moby) {
                *(unsigned short *)(st->moby + 0x34) |= 1;
                st->moby[0x31] = 0;
            }
            st->active = 0;
            moby_set_state(obj, 1, -1);
        }
        break;
    }

    if (IsPointInCuboid(g_hero_position, st->zone[1]) && !(g_help_prompt_flags & 2))
        prisonHelpTimed(0xA2C, 131);
    if (IsPointInCuboid(g_hero_position, st->zone[2])) {
        prisonHelp(0xA09, 96);
        g_subtitle_history[97].count = 0xFFFF;
    }
    if (IsPointInCuboid(g_hero_position, st->zone[3]) && g_help_l14_prompt_flags[2])
        prisonHelp(0xA0A, 97);
    if (IsPointInCuboid(g_hero_position, st->hintZone) && !(g_moby_group_flags[st->row + g_current_map_index * 16] & 0x80) &&
        g_subtitle_history[94].count < 2)
        prisonHelp(0xA07, 94);
    st->count++;
}
