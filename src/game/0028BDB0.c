#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef int s32;

extern void weapon_menu_init_slots(void);

/* authored C for independently verified level-native body */
/* Sets up a pop-up menu panel with its size and starting values. */
void menu_init_panel_layout(u8 *panel) {
 weapon_menu_init_slots();
 *(s32 *)(panel+0x58)=210;*(s32 *)(panel+0x5c)=200;
 *(s32 *)(panel+0x74)=-2;*(s32 *)(panel+0x78)=30;
 *(u16 *)(panel+0x48)=0;*(u16 *)(panel+0x4a)=0;*(s32 *)(panel+0x70)=0;
}

/* func_0028C6D0 is defined in 0028BDB0-wheel-g8.c. */


/* func_0028CCE0 is defined in 0028BDB0-radial-g8.c. */

/* func_0028D1E8 is defined in 0028D1E8-radial-g8.c. */

extern int hud_screen_position(void *, int *, int *);
extern void hud_offset_element_for_slide(void *, int *, int *, int, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_sized_texture(int,int,int,int,int,int);
extern void hud_draw_sprite(int,int,int,int,int,int);
extern short g_progress_panel_flag;
/* Draws a progress bar panel whose fill width follows how far along the value is. */
int menu_draw_progress_bar_panel(char *panel) {
 int x=*(int *)(panel+0x50), y=*(int *)(panel+0x54);
 int fillWidth;
 *(int *)(panel+0x58)=256; *(int *)(panel+0x5c)=64;
 hud_screen_position(panel,&x,&y);
 hud_offset_element_for_slide(panel,&x,&y,*(int *)(panel+0x6c),0);
 fillWidth=*(int *)(panel+0x74)*221 / *(int *)(panel+8)+27;
 hud_draw_sprite_sized_texture(GetIconFrame(0x7558,1),x,y,fillWidth,64,128);
 hud_draw_sprite(GetIconFrame(0x7558,0),x,y,256,64,128);
 hud_draw_sprite(GetIconFrame(0x7558,2),x,y,32,32,g_progress_panel_flag?128:0);
 return *(int *)(panel+0x58);
}

/* Sets up a small menu panel with its size and timer. */
void menu_init_small_panel(char *panel) { extern void hud_init_counter_values(u8 *); *(int *)(panel + 0x58) = 0x20; *(int *)(panel + 0x7C) = 0x96; *(int *)(panel + 0x5C) = 0x20; hud_init_counter_values((u8 *)panel); }

/* Does nothing and returns zero. */
int hud_return_zero(void) {
    return 0;
}



/* The map's thirteen records, 0x90 bytes each: +0x04 flags, +0x14 handler,
   +0x68 busy, +0x6C position, +0x7C timer. */
extern char g_hud_elements[];

/* The retail loads this one through a lui/lw pair of its own. */
extern int g_hud_record_timer_flag __attribute__((sda));

extern void hud_finish_element_setup(char *);

extern void weapon_menu_update_entry(void);

/* Walks the records, caps their timers, moves their positions on, and lets a
   record run its own handler. */
/* Counts down the timers of the thirteen HUD records and runs each record's own handler when asked. */
int hud_update_record_timers(int runHandlers)
{
    char *record;
    char *recordsEnd;
    int count = 0;

    weapon_menu_update_entry();
    record = (char *)g_hud_elements;
    recordsEnd = (char *)g_hud_elements + 0x750;
    do {
        int timer;

        if ((*(int *)(record + 4) & 0x10) || g_hud_record_timer_flag) {
            timer = *(int *)(record + 0x7C);
            if (timer < 10) {
                *(int *)(record + 0x7C) = 10;
            }
            timer = *(int *)(record + 0x7C);
        } else {
            timer = *(int *)(record + 0x7C);
        }

        if (timer > 0) {
            timer = timer - 1;
            *(int *)(record + 0x7C) = timer;
            if (timer > 0) {
                count++;
                if (*(int *)(record + 0x6C) < 30) {
                    *(int *)(record + 0x6C) = *(int *)(record + 0x6C) + 1;
                }
            } else if (*(int *)(record + 0x6C) >= -5) {
                *(int *)(record + 0x6C) = *(int *)(record + 0x6C) - 1;
            }
        } else if (*(int *)(record + 0x6C) >= -5) {
            *(int *)(record + 0x6C) = *(int *)(record + 0x6C) - 1;
        }

        if (*(int *)(record + 0x68) != 0) {
            if (*(int *)(record + 0x6C) == -6) {
                hud_finish_element_setup(record);
            }
        }

        if (runHandlers != 0) {
            void (*handler)(char *) = *(void (**)(char *))(record + 0x14);
            if (handler) {
                handler(record);
            }
        }
        record += 0x90;
    } while ((int)record < (int)recordsEnd);
    return count;
}

typedef struct { char reserved00[0x1248]; int selected; char reserved124C[0x1068]; unsigned char blocked; } MapSelection;
typedef struct { char reserved00[0x88]; unsigned short valid; char reserved8A[0x56]; } MapRecord;
extern MapSelection g_hero_state;
extern unsigned char g_item_slot_to_record[];
extern MapRecord ref_L00_0028E260_00[];
/* Gives the selected weapon, or zero when it cannot be used right now. */
int weapon_get_usable_selected(void)
{
    int selected = g_hero_state.selected;
    int blocked = g_hero_state.blocked;
    unsigned int index = g_item_slot_to_record[selected];
    if (((MapRecord *)(index * 0xE0 + (unsigned int)ref_L00_0028E260_00))->valid == 0) selected = 0;
    if (blocked) selected = 0;
    return selected;
}

/* func_0028E2A8 is defined in 0028BDB0-menu-g8.c. */
