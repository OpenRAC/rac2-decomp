#include "include_asm.h"
#include "names.h"

extern void func_00336320_6(char *);

extern void func_00336A78_7(char *);

extern void tab_menu_draw_part(char *);

extern void func_00341A68_1(char *);

extern void tab_menu_draw_icons(char *);

typedef int s32;

typedef unsigned char u8;

extern void menu_set_entry_table(unsigned char *owner, float *records);

void option_list_draw_rows(int);

void option_list_draw_rows(int param_1);

/* Reads a word at +544 of the object; returns when it is zero, otherwise calls a repeated callee four times with the object and the objects at +152, +76 and +228, then one callee each with +464, the object, the object and the object. */
/* Draws the tabbed menu when it is turned on. */
void tab_menu_draw(char *self)
{
    if (*(int *)(self + 544) == 0)
        return;
    func_00336320_6(self);
    func_00336320_6(self + 152);
    func_00336320_6(self + 76);
    func_00336320_6(self + 228);
    func_00336A78_7(self + 464);
    tab_menu_draw_part(self);
    func_00341A68_1(self);
    tab_menu_draw_icons(self);
}

/* Sets up the three parts of a small list menu and returns it. */
char *small_list_menu_construct(char *self) {
    extern unsigned long long menu_pass_through_handle(void *);
    extern void *object_construct_derived_a(char *);
    menu_pass_through_handle(self + 0x10);
    object_construct_derived_a(self + 0xDC);
    object_construct_derived_a(self + 0x128);
    return self;
}


/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in the menu. */
void menu_set_value(u8 *self, s32 value) { *(s32 *)(self + 0x8) = value; }




/* Returns which entry of the list is selected. */
extern s32 list_menu_get_selection(char *);


extern s32 menu_get_selected_index(u8 *);

s32 list_menu_get_selection(char *object) {
    return menu_get_selected_index((u8 *)object + 0x10);
}

/* Gives the list its table of entries. */
void list_menu_set_records(unsigned char *owner, float *records)
{
    menu_set_entry_table(owner + 0x10, records);
    *(float **)(owner + 0xD8) = records;
}

extern void *UpdateMenuListSelection(char *, int);
extern void menu_set_position(char *, float, float);

/* Sets the selected entry of the list and moves the list to the menu position. */
int list_menu_set_selection(char *object, int arg)
{
    char *child = object + 0x10;
    UpdateMenuListSelection(child, arg);
    menu_set_position(child, (*(float **)object)[0], (*(float **)object)[1]);
    return 0;
}


/* Sets up the parts of a list menu and returns it. */
char *list_menu_construct_parts(char *object) {
    extern void *object_construct_derived_a(char *);
    extern void *object_construct_derived_c(char *);
    extern unsigned long long menu_pass_through_handle(void *);
    object_construct_derived_a(object);
    object_construct_derived_a(object + 0x4C);
    object_construct_derived_a(object + 0x98);
    object_construct_derived_a(object + 0xE4);
    object_construct_derived_c(object + 0x130);
    menu_pass_through_handle(object + 0x188);
    return object;
}

/* func_00342118 is in 00341C20-g8.c (it reaches small data through $gp). */

/* Gives the list its table of entries. */
void list_menu_set_record_table(unsigned char *owner, float *records)
{
    *(float **)(owner + 0x250) = records;
    menu_set_entry_table(owner + 0x188, records);
}

/* Measured target: byte-identical across all 27 levels. */
/* Turns the list on or off by storing a flag. */
void list_menu_set_enabled(u8 *self, s32 value) { *(s32 *)(self + 0x170) = value; }

/* multiplies the index by 20 and adds it to a base; byte-identical across all 27 levels. */
/* Returns the address of the selected entry in the list table. */
s32 list_menu_get_selected_record(u8 *self) { return *(s32 *)(self + 0x250) + *(s32 *)(self + 0x16C) * 20; }



/* Does nothing. */
void list_menu_noop_hook(void)
{
}





/* Draws the selection cursor, playing a sound if a direction button was pressed. */
void list_menu_draw_cursor(char *object)
{
    extern int math_ping_pong_blend_values(unsigned int, unsigned int, int, int, int);
    extern int *object_get_fourth_field(char *);
    extern void gfx_draw_screen_element_stored(char *);
    extern int g_menu_input_flags;
    int *slot;
    if (g_menu_input_flags & 0x5000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    object += 0xE4;
    slot = object_get_fourth_field(object);
    *slot = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);
    gfx_draw_screen_element_stored(object);
}

/* Draws the scrolling part of the list menu. */
void list_menu_draw_scroller(int object)
{
  option_list_draw_rows(object + 0x188);
  return;
}
