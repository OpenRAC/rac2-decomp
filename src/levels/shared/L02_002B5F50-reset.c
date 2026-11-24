/* func_L02_002B5F50: func_L02_002B5F50 behind a reset of the hero's carried objects. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern char g_hero_state[];

extern void menu_init_panel_layout(char *);

extern void weapon_wheel_update_select(char *);

extern int weapon_wheel_draw(char *);

extern char g_str_carried_object_a[];

extern char g_str_carried_object_b[];

extern int g_area_start_mode;

extern void attachment_reset_all(void);

extern void moby_mark_spawned(void *);

extern int hud_set_slot_contents(int, int, void (*)(char *), void (*)(char *), int (*)(char *), int, int);

extern int level_run_slot_callback(u32 a0);

extern void hero_clear_tracked_slots(void);

extern void hero_clear_queued_anim(void);

extern int anim_copy_entry_data(char *a0, int a1, int a2, char *a3);

extern s32 hero_l00_set_move_state(int a0, int a1);

/* Clears the hero's carried objects and state, then restores the normal setup. */
void hero_reset_carried_objects(void) {
    char *hero;
    char *hero_moby;
    int handle;

    hero = g_hero_state;
    if (*(u8 *)(hero + 0x22B4) == 1) {
        *(int *)(hero + 0x24D0) = *(int *)(hero + 0x24CC);
        *(int *)(hero + 0x24CC) = *(short *)(hero + 0x24D4);
        if (*(char **)(hero + 0x1860) != 0) {
            moby_mark_spawned(*(char **)(hero + 0x1860));
            *(char **)(hero + 0x1860) = 0;
        }
        if (*(char **)(hero + 0x1864) != 0) {
            moby_mark_spawned(*(char **)(hero + 0x1864));
            *(char **)(hero + 0x1864) = 0;
        }
    }
    attachment_reset_all();
    g_hero_state[0x22B4] = 0;
    hero = g_hero_state;
    hud_set_slot_contents(0x23, 0, menu_init_panel_layout, weapon_wheel_update_select, weapon_wheel_draw, 0, 0);
    level_run_slot_callback(3);
    {
        char *oldActor = *(char **)(hero + 0xC14);
        if (oldActor != 0)
            *(u16 *)(oldActor + 0x34) &= 0xFFF9;
    }
    *(int *)(hero + 0xC14) = 0;
    hero_clear_tracked_slots();
    {
        char *actor = *(char **)(hero + 0xC18);
        *(char **)(hero + 0x2290) = actor;
        qcopy(actor + 0x10, hero + 0x80);
        *(int *)(actor + 0x9C) = 0;
    }
    *(float *)(hero + 0xC24) = 1.0f;
    hero_clear_queued_anim();
    hero_moby = *(char **)(hero + 0x2290);
    if (*(unsigned char *)((char *)hero_moby + 0x42) != 0xFF) {
        handle = anim_copy_entry_data(hero_moby, *(unsigned char *)((char *)hero_moby + 0x42),
                              *(unsigned char *)((char *)hero_moby + 0x40), g_str_carried_object_a);
        *(int *)(*(char **)(hero + 0x2290) + 0x58) = handle;
    }
    hero_moby = *(char **)(hero + 0x2290);
    handle = anim_copy_entry_data(hero_moby, *(unsigned char *)((char *)hero_moby + 0x43),
                          *(unsigned char *)((char *)hero_moby + 0x41), g_str_carried_object_b);
    *(int *)(*(char **)(hero + 0x2290) + 0x5C) = handle;
    if (*(int *)(hero + 0x2294) != 0x61 ||
        (g_area_start_mode != 2 && g_area_start_mode != 6))
        hero_l00_set_move_state(0, 1);
}
