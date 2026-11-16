#include "common.h"

extern char g_hero_state[];
extern s32 g_hero_mode_state[] __attribute__((sda));

extern void moby_mark_spawned(s32);
extern void set_animation_parameter(s32, s32);
extern void attachment_reset_all(void);
extern int hud_set_slot_contents(s32, s32, void *, void *, void *, s32, s32);
extern int level_run_slot_callback(s32);
extern void hero_clear_tracked_slots(void);
extern void hero_clear_queued_anim(void);
extern s32 anim_copy_entry_data(char *, s32, s32, char *);
extern int hero_l22_set_action(s32, s32);
extern char g_str_hud_slot_text_c[];
extern char g_str_hud_slot_text_b[];
extern char g_str_hud_slot_text_a[];
extern char g_hero_anim_buffer_upper[];
extern char g_hero_anim_buffer_lower[];

/* Resets the hero for a restart: drops the held objects, replays the entry sequence and rebinds the player's moby. */
void hero_reset_for_restart(void)
{
    char *hero = g_hero_state;
    char *hero2, *hero3;
    char *moby, *from;
    s32 mode;

    if (*(unsigned char *)(hero + 0x22B4) == 1) {
        *(s32 *)(hero + 0x24D0) = *(s32 *)(hero + 0x24CC);
        *(s32 *)(hero + 0x24CC) = *(short *)(hero + 0x24D4);
        if (*(s32 *)(hero + 0x1860) != 0) {
            moby_mark_spawned(*(s32 *)(hero + 0x1860));
            *(s32 *)(hero + 0x1860) = 0;
        }
        if (*(s32 *)(hero + 0x1864) != 0) {
            moby_mark_spawned(*(s32 *)(hero + 0x1864));
            *(s32 *)(hero + 0x1864) = 0;
        }
    }
    hero2 = g_hero_state;
    if (*(unsigned char *)(hero2 + 0x22B4) == 2) {
        if (*(short *)(hero2 + 0x1878) != -1) {
            set_animation_parameter(*(short *)(hero2 + 0x1878), 0);
            *(short *)(hero2 + 0x1878) = -1;
        }
    }
    attachment_reset_all();
    hero3 = g_hero_state;
    *(unsigned char *)(hero3 + 0x22B4) = 0;
    hud_set_slot_contents(0x23, 0, g_str_hud_slot_text_c, g_str_hud_slot_text_b, g_str_hud_slot_text_a, 0, 0);
    level_run_slot_callback(3);
    if (*(char **)(hero3 + 0xC14) != 0)
        *(unsigned short *)(*(char **)(hero3 + 0xC14) + 0x34) &= 0xFFF9;
    *(s32 *)(hero3 + 0xC14) = 0;
    hero_clear_tracked_slots();
    moby = *(char **)(hero3 + 0xC18);
    from = hero3 + 0x80;
    *(char **)(hero3 + 0x2290) = moby;
    qcopy(moby + 0x10, from);
    *(s32 *)(moby + 0x9C) = 0;
    *(float *)(hero3 + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    if (*(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x42) != 0xFF)
        *(s32 *)(*(char **)(hero3 + 0x2290) + 0x58) = anim_copy_entry_data(*(char **)(hero3 + 0x2290), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x42), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x40), g_hero_anim_buffer_upper);
    *(s32 *)(*(char **)(hero3 + 0x2290) + 0x5C) = anim_copy_entry_data(*(char **)(hero3 + 0x2290), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x43), *(unsigned char *)(*(char **)(hero3 + 0x2290) + 0x41), g_hero_anim_buffer_lower);
    if (*(s32 *)(hero3 + 0x2294) != 0x61 || ((mode = g_hero_mode_state[0]) != 2 && mode != 6))
        hero_l22_set_action(0, 1);
}
