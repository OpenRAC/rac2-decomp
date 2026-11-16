#include "include_asm.h"
#include "common.h"

/* func_US2_L14_003F64DC, the USA v2.00 copy of func_L14_003F4F98: the same C, where the gadget
   level limit 2 becomes limit = func_00288D58() ? 5 : 2, and the two-armed func_00287FF8 call
   becomes func_00287FF8(10, limit). */

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

/* True once the gadget in slot 10 has been upgraded. */
static inline int prisonGadgetUpgraded(int limit)
{
    int level = (g_item_l14_materials + g_item_slot_to_record[10])->level;

    return level >= limit;
}

/* Shows help message MSG unless its history entry IDX says it was shown in the last 18 seconds. */
static inline void prisonHelpTimed(int msg, int idx)
{
    if (g_frame_counter - g_subtitle_history[idx].time > 1080 || !g_subtitle_history[idx].time)
        subtitle_request_voice_line(msg, idx);
    else if (g_subtitle_history[idx].time < g_frame_counter)
        g_subtitle_history[idx].time = g_frame_counter;
}

/* The first time only records history entry IDX as seen in this level; later times show MSG. */
static inline void prisonHelp(int msg, int idx)
{
    if (g_subtitle_history[idx].count) {
        prisonHelpTimed(msg, idx);
    } else {
        g_subtitle_history[idx].count++;
        if (g_subtitle_history[idx].time < g_frame_counter)
            g_subtitle_history[idx].time = g_frame_counter;
        g_subtitle_history[idx].levels = (g_subtitle_history[idx].levels | (1u << g_current_map_index)) | 0x80000000u;
    }
}

/* Drives the prison's help prompts: links the target moby, plays the hints at the trigger zones
   and records which help messages were already shown. */
void help_prompt_update_us2(char *moby)
{
    PrisonHelpState *vars = *(PrisonHelpState **)(moby + 0x68);
    float offset[4] __attribute__((aligned(16)));
    int limit = 2;

    if (flag_is_byte_set())
        limit = 5;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(short *)(moby + 0x96) = 0;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        if (vars->target >= 0)
            vars->moby = D_L14_001B259C_direct + (vars->target << 8);
        else
            vars->moby = 0;
        if (!prisonGadgetUpgraded(limit)) {
            if (vars->moby)
                vars->active = 1;
            else
                vars->active = 0;
        } else {
            if (vars->moby) {
                *(unsigned short *)(vars->moby + 0x34) |= 1;
                vars->moby[0x31] = 0;
            }
            vars->active = 0;
        }
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(moby))
            vars->count = 0;
        if (IsPointInCuboid(g_hero_position, vars->zone[0])) {
            if (!prisonGadgetUpgraded(limit))
                moby_set_state(moby, 2, -1);
        }
        if (vars->active) {
            qcopy(offset, g_identity_l14_matrix);
            offset[1] -= 0.1f;
            moby_rotate_about_point(vars->moby, offset, 0.05f, 0.0f, 0.0f);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby))
            vars->count = 0;
        if (g_shop_mode != 2 && vars->count >= 6) {
            menu_seek_chain_entry(10, limit);
            gfx_run_screen_update_steps(2);
            if (vars->moby) {
                *(unsigned short *)(vars->moby + 0x34) |= 1;
                vars->moby[0x31] = 0;
            }
            vars->active = 0;
            moby_set_state(moby, 1, -1);
        }
        break;
    }

    if (IsPointInCuboid(g_hero_position, vars->zone[1]) && !(g_help_prompt_flags & 2))
        prisonHelpTimed(0xA2C, 131);
    if (IsPointInCuboid(g_hero_position, vars->zone[2])) {
        prisonHelp(0xA09, 96);
        g_subtitle_history[97].count = 0xFFFF;
    }
    if (IsPointInCuboid(g_hero_position, vars->zone[3]) && g_help_l14_prompt_flags[2])
        prisonHelp(0xA0A, 97);
    if (IsPointInCuboid(g_hero_position, vars->hintZone) && !(g_moby_group_flags[vars->row + g_current_map_index * 16] & 0x80) &&
        g_subtitle_history[94].count < 2)
        prisonHelp(0xA07, 94);
    vars->count++;
}
