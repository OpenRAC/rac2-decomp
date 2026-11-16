#include "include_asm.h"
#include "names.h"

extern void *pool_alloc_cell(void *);
extern void *ui_return_second_arg(int, int);
extern void hud_init_widget_defaults_us2(void *, void *, void *);
extern char g_list_menu_attach_widget_defaults[];

/* func_US2_00348BF8, the USA v2.00 copy of func_00347EC8: the same C, where the fields move 0x10 on
   and the new field at 0x54 is cleared too. */
void list_menu_reset_attach_items_us2(char *object, void *data)
{
    int *position;
    *(int *)(object + 0x60) = 0;
    *(int *)(object + 0xC0) = 0;
    *(void **)(object + 0x58) = data;
    if (data) {
        position = ui_return_second_arg(16, pool_alloc_cell(data));
        *(int **)(object + 0x5C) = position;
        position[1] = 0; position[2] = 0; position[3] = 0; position[0] = 0;
    }
    hud_init_widget_defaults_us2(object, g_list_menu_attach_widget_defaults, data);
    *(int *)(object + 0xAC) = 0x70FFFEED;
    *(int *)(object + 0xB0) = 0x80F0F0F0;
    *(int *)(object + 0xB4) = 0x80808080;
    *(int *)(object + 0xBC) = 32;
    *(int *)(object + 0x54) = 0;
    *(int *)(object + 0xB8) = 0;
    *(int *)(object + 0xC4) = 0;
    *(int *)(object + 0xC8) = 0;
    *(int *)(object + 0xCC) = -1;
}


typedef int s32;
typedef unsigned char u8;
typedef float f32;
extern void menu_set_entry_table(unsigned char *owner, float *records);
extern u8 g_item_owned_flags[] __attribute__((section(".sdata")));
extern u8 g_movie_seen_flags[] __attribute__((section(".sdata")));

/* func_00347F80 is built from 00345358-wrap.c. */


/* Sets the list menu's record table, counts its records (stopping at a non-positive first value or the table end),
   and resets the selection to 0 if it is now past the count. */
void list_menu_set_entry_records_us2(u8 *object,f32 *records) {
 f32 *records_end;
 *(f32 **)(object+0x68)=records;
 *(s32 *)(object+0xC0)=0;
 records_end=records+0x50;
 if(records[0]>0.0f) {
  do {
   records+=5;
   (*(s32 *)(object+0xC0))++;
  } while(*records>0.0f && (s32)records<(s32)records_end);
 }
 if(*(s32 *)(object+0x60)>=*(s32 *)(object+0xC0)) *(s32 *)(object+0x60)=0;
}


void func_US2_00348E10(u8 *a0, s32 a1, s32 a2) { *(s32 *)(a0 + 0xB8) = a1; *(s32 *)(a0 + 0xBC) = a2; }



/* Sets the menu position pair (x, y) and clears the two words after it. */
void list_menu_set_position_us2(u8 *object,f32 x,f32 y) {
 (*(f32 **)(object+0x5C))[0]=x;
 (*(f32 **)(object+0x5C))[1]=y;
 (*(s32 **)(object+0x5C))[2]=0;
 (*(s32 **)(object+0x5C))[3]=0;
}






/* func_US2_00348E70 is built from 00348E70-menu.c. */

extern void *Faac80289_FUN_003361A8(char *p);
extern char *Faac80289_FUN_00336968(char *p);

/* func_00348138 is built from 00345358-menu.c. */

/* Destroys the seven labels and seven rows of a menu page and returns it. */
char *menu_page_destruct_us2(char *page)
{
    char *row = page + 536;
    int i;

    Faac80289_FUN_003361A8(page);
    Faac80289_FUN_003361A8(page + 76);
    Faac80289_FUN_003361A8(page + 152);
    Faac80289_FUN_003361A8(page + 228);
    Faac80289_FUN_003361A8(page + 304);
    Faac80289_FUN_003361A8(page + 380);
    Faac80289_FUN_003361A8(page + 456);

    for (i = 6; i != -1; i--) {
        Faac80289_FUN_00336968(row);
        row += 88;
    }
    return page;
}



