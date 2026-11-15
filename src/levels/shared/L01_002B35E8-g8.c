/* func_L01_002B35E8 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;

extern char g_hero_state[];

extern void menu_init_panel_layout(char *);

extern void weapon_wheel_update_select(char *);

extern int weapon_wheel_draw(char *);

extern char D_L01_001B4B00[];

extern char D_L01_001B5100[];

extern int D_001A8F40;

extern void attachment_reset_all(void);

extern int hud_set_slot_contents(int, int, void (*)(char *), void (*)(char *), int (*)(char *), int, int);

extern int level_run_slot_callback(u32 a0);

extern void hero_clear_tracked_slots(void);

extern void hero_clear_queued_anim(void);

extern int anim_copy_entry_data(char *a0, int a1, int a2, char *a3);

extern void SetHeroMoveState(int a0, int a1);

/* Resets the hero when a new area starts: clears the old target, copies the spawn position from the spawn object and sets up the two attached objects. */
void hero_reset_for_area_start(void) {
    char *hero;
    char *heroMoby;
    int attachedItem;

    attachment_reset_all();
    hero = g_hero_state;
    hero[0x22B4] = 0;
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
    heroMoby = *(char **)(hero + 0x2290);
    if (*(unsigned char *)((char *)heroMoby + 0x42) != 0xFF) {
        attachedItem = anim_copy_entry_data(heroMoby, *(unsigned char *)((char *)heroMoby + 0x42),
                              *(unsigned char *)((char *)heroMoby + 0x40), D_L01_001B4B00);
        *(int *)(*(char **)(hero + 0x2290) + 0x58) = attachedItem;
    }
    heroMoby = *(char **)(hero + 0x2290);
    attachedItem = anim_copy_entry_data(heroMoby, *(unsigned char *)((char *)heroMoby + 0x43),
                          *(unsigned char *)((char *)heroMoby + 0x41), D_L01_001B5100);
    *(int *)(*(char **)(hero + 0x2290) + 0x5C) = attachedItem;
    if (*(int *)(hero + 0x2294) != 0x61 ||
        (D_001A8F40 != 2 && D_001A8F40 != 6))
        SetHeroMoveState(0, 1);
}
