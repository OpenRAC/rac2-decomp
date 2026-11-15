#include "include_asm.h"
#include "names.h"

extern int list_menu_get_selected_index(int);

extern int menu_get_selected_index(unsigned char *);

/* Qwen draft (branch qwen/autonomy, 4419d477), checked by tools/check.py */
void prompt_bar_draw(int);

extern void func_0033AB50_1(void *);

extern void cam_init_object_table_c(void *);

extern void cam_init_object_table_d(void *);

extern void cam_init_object_table_a(void *);

/* Returns the index of the selected entry in the menu list. */
int list_menu_get_selected_index(int owner)
{
    return menu_get_selected_index((unsigned char *)(owner + 0x2b0));
}

/* Gives the menu list its entries and remembers where they are. */
void list_page_set_records(unsigned char *owner, float *records)
{
    extern void menu_set_entry_table(unsigned char *, float *);
    menu_set_entry_table(owner + 0x2B0, records);
    *(float **)(owner + 0x378) = records;
}

extern void prompt_bar_update(char *);
extern void menu_set_anchor_pos(char *, float, float);
extern char *UpdateMenuListSelection(char *, int);
extern void menu_set_position(char *, float, float);

/* Handles input for the list menu page and keeps the list in place. */
int list_page_update(char *object, int flags)
{
    char *first = object + 8;
    char *second;
    float *position;
    prompt_bar_update(first);
    second = object + 0x2B0;
    position = *(float **)(object + 0x37C);
    menu_set_anchor_pos(first, position[0], position[1]);
    UpdateMenuListSelection(second, flags);
    menu_set_position(second, (*(float **)(object + 0x37C))[0], (*(float **)(object + 0x37C))[1]);
    return (flags >> 6) & 1;
}



extern void prompt_bar_destroy(void *);
extern void *hud_construct_widget_base(void *);

/* Cleans up a menu page that has a list. */
char *simple_list_page_destroy(char *object) {
    prompt_bar_destroy(object + 8);
    hud_construct_widget_base(object + 0x2B0);
    return object;
}




extern void prompt_bar_update(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);

/* Keeps the simple menu page in place and reports if confirm was pressed. */
int simple_page_update(char *object, int flags)
{
    char *p = object + 8;
    float *v;
    prompt_bar_update(p);
    v = *(float **)(object + 0x2A8);
    menu_set_anchor_pos(p, v[0], v[1]);
    return (flags >> 6) & 1;
}

/* Draws the frame of a menu page. */
void menu_draw_frame(int object) {
  prompt_bar_draw(object + 8);
}

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
/* Cleans up a menu page made of a frame and eleven text parts. */
char *frame_text_page_destroy(char *object)
{
    func_0033AB50_1(object + 8);
    cam_init_object_table_c(object + 684);
    cam_init_object_table_d(object + 744);
    cam_init_object_table_d(object + 816);
    cam_init_object_table_d(object + 888);
    cam_init_object_table_a(object + 960);
    cam_init_object_table_d(object + 1040);
    cam_init_object_table_d(object + 1112);
    cam_init_object_table_d(object + 1184);
    cam_init_object_table_d(object + 1256);
    cam_init_object_table_d(object + 1328);
    cam_init_object_table_d(object + 1400);
    return object;
}
