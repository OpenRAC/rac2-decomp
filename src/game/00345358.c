#include "include_asm.h"
#include "names.h"

extern float *object_get_first_field(char *);
extern void hud_meter_bar_update(char *);
extern void anim_update_keyframe(char *, int);
extern float ref_L00_001AEAC8_00 __attribute__((section(".sdata")));
extern float ref_L00_001AEACC_00 __attribute__((section(".sdata")));
extern float ref_L00_001AEAD0_00 __attribute__((section(".sdata")));
extern float ref_L00_001AEAD4_00 __attribute__((section(".sdata")));


extern void F6402b823_FUN_00336320(char *a);

extern void F6402b823_FUN_00336A78(char *a);

extern void F6402b823_FUN_00335E68(char *a, int b);

extern void F6402b823_FUN_00345268(char *a);

extern void F6402b823_FUN_00345088(char *a);

extern void F6402b823_FUN_00344F98(char *a);

extern void F6402b823_FUN_00345178(char *a);

extern void F6402b823_FUN_00344938(char *a);

extern void *F449e2f67_FUN_003361A8(char *p);

extern char *F449e2f67_FUN_00336968(char *p);

extern void *F449e2f67_FUN_003366D0(char *p);

extern void Fd1c2476b_FUN_00336320(char *p);

extern void Fd1c2476b_FUN_00336A78(char *p);

extern void Fd1c2476b_FUN_003462A8(char *p);

extern void Fd1c2476b_FUN_003463C8(char *p);

extern void Fd1c2476b_FUN_003464D0(char *p);

extern void *F5a9e4f98_FUN_003361A8(char *p);

extern void *F5a9e4f98_FUN_003363D0(char *p);

extern char *F5a9e4f98_FUN_00336968(char *p);

extern void *F5a9e4f98_FUN_003366D0(char *p);

extern unsigned long long menu_pass_through_handle(unsigned long long);

extern char *hud_construct_widget_base(unsigned long long);

typedef int s32;

typedef unsigned char u8;

typedef float f32;

extern void menu_set_entry_table(unsigned char *owner, float *records);

extern int menu_get_selected_index(unsigned char *);

extern void *Faac80289_FUN_003361A8(char *p);

extern char *Faac80289_FUN_00336968(char *p);

extern char *D_L00_001A904C_3 __attribute__((sda));

extern void object_set_helper_result(char *dst, char *src, int value);

extern char *func_00288FB8_2(int a);

extern void func_L00_0042C360_1(char *a, int b);

extern void func_003495D8_1(char *o, int n, float a, float b, float c, float d, float e);

extern void anim_set_key_range(char *o, int n, float a, float b);

typedef struct { f32 x, y, z, w; } JammingParameterRow;

typedef struct {
    u8 prefix[0x30];
    JammingParameterRow rows[4];
    f32 weights[3];
} JammingParameterRows;

#ifndef RAC2_T_S_F49AFCBFE
#define RAC2_T_S_F49AFCBFE
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    float f16;
    int i20;
    float f24;
    int i28;
    int i32;
    int i36;
    int i40;
} S_F49afcbfe;
#endif

extern void func_00349A70_1(S_F49afcbfe *x, int a, int b, float p, float q, float r, float s);

typedef struct { f32 x, y, z, w; } JammingGridRow;

typedef struct { JammingGridRow rows[3]; } JammingGridGroup;

typedef struct { u8 prefix[0x2c]; JammingGridGroup groups[2]; } JammingGridObject;

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_79744baad5ad7f65_ScalarChange48Owner {
    unsigned int field_00;
    int value_04;
    unsigned char gap_08[0x3ec];
    int counter_3f4;
    int counter_3f8;
    int previous_3fc;
} Rac2Native_79744baad5ad7f65_ScalarChange48Owner;

extern unsigned char g_screen_mode_flag[];

extern void func_00349630_2(char *, int);

/* func_0034CA68: owner ABI/declaration review retained. */
extern int *object_get_fourth_field(unsigned char *field);

extern void F72a1dff5_FUN_00349AB8(char *p, int a);

extern void F72a1dff5_FUN_00349630(char *p, int a);

extern void F72a1dff5_FUN_00336920(char *p, void *b, int c);

extern void F01bd4546_FUN_00335E68(char *p, int v);

extern void F01bd4546_FUN_00349630(char *p, int v);

extern void F01bd4546_FUN_00349678(char *p, float v);

extern void F076896f4_FUN_00349AB8(void *, int);

extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void gfx_draw_screen_element_stored(char *);
extern void hud_draw_progress_bar(char *);
extern void menu_grid_compute_tile_placement(char *, int, int, float *, float *, float *, int *);
extern void object_set_first_float4(char *, float, float, float, float);
extern void object_set_second_float4(char *, float, float, float, float);
extern char *g_resident_data_base __attribute__((section(".sdata")));

/* Draws every part of a menu screen (labels, icons and buttons) when the screen is switched on. */
void menu_screen_draw_parts(char *menu)
{
    if (*(int *)(menu + 1080) != 0) {
        char *titleLabel = menu + 456;

        F6402b823_FUN_00336320(menu);
        F6402b823_FUN_00336320(menu + 76);
        F6402b823_FUN_00336320(menu + 152);
        F6402b823_FUN_00336320(menu + 228);
        F6402b823_FUN_00336A78(titleLabel);
        F6402b823_FUN_00336A78(menu + 664);
        F6402b823_FUN_00336A78(titleLabel);
        F6402b823_FUN_00335E68(menu + 528, 0);
        F6402b823_FUN_00345268(menu);
        F6402b823_FUN_00345088(menu);
        F6402b823_FUN_00344F98(menu);
        F6402b823_FUN_00345178(menu);
        F6402b823_FUN_00344938(menu);
        F6402b823_FUN_00336320(menu + 380);
    }
}

/* Sets up all the sprites and labels of a menu screen. */
char *menu_screen_init_parts(char *menu)
{
    F449e2f67_FUN_003361A8(menu);
    F449e2f67_FUN_003361A8(menu + 76);
    F449e2f67_FUN_003361A8(menu + 152);
    F449e2f67_FUN_003361A8(menu + 228);
    F449e2f67_FUN_003361A8(menu + 304);
    F449e2f67_FUN_003361A8(menu + 380);
    F449e2f67_FUN_00336968(menu + 456);
    F449e2f67_FUN_00336968(menu + 528);
    F449e2f67_FUN_003366D0(menu + 600);
    F449e2f67_FUN_00336968(menu + 664);
    F449e2f67_FUN_00336968(menu + 736);
    F449e2f67_FUN_00336968(menu + 808);
    F449e2f67_FUN_00336968(menu + 880);
    F449e2f67_FUN_00336968(menu + 952);
    return menu;
}

/* func_00345490 is built from 00345358-init.c. */



/* func_00345F70 is built from 00345358-layout-g8.c. */

/* func_003462A8 is built from 00345358-descriptor-g8.c for small-data access. */

/* func_003463C8 and func_003464D0 are built from 00345358-g8.c for small-data access. */


/* Draws every part of a bigger menu screen when it is switched on. */
void menu_screen_large_draw_parts(char *menu)
{
    if (*(int *)(menu + 1160) == 0)
        return;
    Fd1c2476b_FUN_00336320(menu);
    Fd1c2476b_FUN_00336320(menu + 76);
    Fd1c2476b_FUN_00336320(menu + 152);
    Fd1c2476b_FUN_00336320(menu + 228);
    Fd1c2476b_FUN_00336A78(menu + 456);
    Fd1c2476b_FUN_003462A8(menu);
    Fd1c2476b_FUN_003463C8(menu);
    Fd1c2476b_FUN_003464D0(menu);
    Fd1c2476b_FUN_00336320(menu + 380);
    Fd1c2476b_FUN_00336A78(menu + 736);
    Fd1c2476b_FUN_00336A78(menu + 664);
    Fd1c2476b_FUN_00336A78(menu + 808);
    Fd1c2476b_FUN_00336A78(menu + 880);
    Fd1c2476b_FUN_00336A78(menu + 952);
}

/* Sets up all the sprites and labels of a menu screen with many parts. */
void *menu_screen_large_init_parts(char *menu)
{
    F5a9e4f98_FUN_003361A8(menu);
    F5a9e4f98_FUN_003361A8(menu + 0x4c);
    F5a9e4f98_FUN_003361A8(menu + 0x98);
    F5a9e4f98_FUN_003361A8(menu + 0xe4);
    F5a9e4f98_FUN_003361A8(menu + 0x130);
    F5a9e4f98_FUN_003361A8(menu + 0x17c);
    F5a9e4f98_FUN_003363D0(menu + 0x1c8);
    F5a9e4f98_FUN_00336968(menu + 0x210);
    F5a9e4f98_FUN_00336968(menu + 0x258);
    F5a9e4f98_FUN_00336968(menu + 0x2a0);
    F5a9e4f98_FUN_00336968(menu + 0x2e8);
    F5a9e4f98_FUN_00336968(menu + 0x330);
    F5a9e4f98_FUN_003366D0(menu + 0x378);
    F5a9e4f98_FUN_003361A8(menu + 0x3b4);
    F5a9e4f98_FUN_003361A8(menu + 0x400);
    F5a9e4f98_FUN_003361A8(menu + 0x44c);

    return menu;
}

/* The two menu labels at +0x2E8 and +0x330: shown according to the flags of the highlighted
   grid entry, and placed relative to the owner's position record. */
typedef struct { int x; int y; } MenuLabelOffset;
typedef struct { short a, b, c, id, e; } MenuGridEntry;
extern MenuGridEntry g_menu_item_table_first[];
extern u8 g_item_owned_flags[] __attribute__((section(".sdata")));
extern u8 g_movie_seen_flags[] __attribute__((section(".sdata")));
extern MenuLabelOffset ref_003472B8_00;
extern void object_set_flag_value(void *, int);

void UpdateMenuGridLabels(char *obj)
{
    MenuLabelOffset pad;
    char *a;
    char *b;
    float x, y, x2, y2;
    u8 *flags;
    int bits;
    int index = g_menu_item_table_first[*(int *)(obj + 0x4FC) + *(int *)(obj + 0x500) * 4].id;

    if (g_item_owned_flags[index] == 0)
        return;
    a = obj + 0x2E8;
    pad = ref_003472B8_00;
    flags = &g_movie_seen_flags[index];
    b = obj + 0x330;
    bits = flags[0] & 4;
    object_set_flag_value(a, (flags[0] & 1) | (bits != 0));
    {
        int b2 = flags[0] & 0x10;
        object_set_flag_value(b, b2 != 0);
    }
    x = (*(float **)(obj + 0x498))[0] + object_get_first_field(a)[0] + (float)pad.x;
    y = (*(float **)(obj + 0x498))[1] + object_get_first_field(a)[1] + (float)pad.y;
    object_set_first_float4(a, x, y, 0.0f, 0.0f);
    x2 = (*(float **)(obj + 0x498))[0] + object_get_first_field(b)[0] + (float)pad.x;
    y2 = (*(float **)(obj + 0x498))[1] + object_get_first_field(b)[1] + (float)pad.y;
    object_set_first_float4(b, x2, y2, 0.0f, 0.0f);
}

/* func_00347468 is built from 00345358-selection-g8.c. */

/* func_003478F0 is defined in 003478F0-grid-g8.c. */

/* Passes a value to a helper and gives the same value back. */
unsigned long long menu_pass_through_handle(unsigned long long handle)
{
    hud_construct_widget_base(handle);
    return handle;
}

extern void *pool_alloc_cell(void *);
extern void *ui_return_second_arg(int, int);
extern void hud_init_widget_defaults(void *, void *, void *);
extern char g_list_menu_attach_widget_defaults[];

/* Resets a list menu to its start state and attaches its item data. */
void list_menu_reset_attach_items(char *menu, void *items)
{
    int *cursorPos;
    *(int *)(menu + 0x50) = 0;
    *(int *)(menu + 0xB0) = 0;
    *(void **)(menu + 0x48) = items;
    if (items) {
        cursorPos = ui_return_second_arg(16, pool_alloc_cell(items));
        *(int **)(menu + 0x4C) = cursorPos;
        cursorPos[1] = 0; cursorPos[2] = 0; cursorPos[3] = 0; cursorPos[0] = 0;
    }
    hud_init_widget_defaults(menu, g_list_menu_attach_widget_defaults, items);
    *(int *)(menu + 0x9C) = 0x70FFFEED;
    *(int *)(menu + 0xA0) = 0x80F0F0F0;
    *(int *)(menu + 0xA4) = 0x80808080;
    *(int *)(menu + 0xAC) = 32;
    *(int *)(menu + 0xA8) = 0;
    *(int *)(menu + 0xB4) = 0;
    *(int *)(menu + 0xB8) = 0;
    *(int *)(menu + 0xBC) = -1;
}

/* func_00347F80 is built from 00345358-wrap.c. */


/* Points the menu at a table of entries and counts how many are in use. */
void menu_set_entry_table(u8 *menu,f32 *entries) {
 f32 *end;
 *(f32 **)(menu+0x58)=entries;
 *(s32 *)(menu+0xb0)=0;
 end=entries+0x50;
 if(entries[0]>0.0f) {
  do {
   entries+=5;
   (*(s32 *)(menu+0xb0))++;
  } while(*entries>0.0f && (s32)entries<(s32)end);
 }
 if(*(s32 *)(menu+0x50)>=*(s32 *)(menu+0xb0)) *(s32 *)(menu+0x50)=0;
}

/* Stores two settings on a menu object. */
void menu_set_settings(u8 *menu, s32 first, s32 second) { *(s32 *)(menu + 0xa8) = first; *(s32 *)(menu + 0xac) = second; }

/* Stores a value in a menu field. */
void menu_set_field_b8(int menu, unsigned int value)
{
  *(unsigned int *)(menu + 0xb8) = value;
  return;
}

/* Sets the first two numbers of the menu's position and clears the other two. */
void menu_set_position(u8 *menu,f32 posX,f32 posY) {
 (*(f32 **)(menu+0x4c))[0]=posX;
 (*(f32 **)(menu+0x4c))[1]=posY;
 (*(s32 **)(menu+0x4c))[2]=0;
 (*(s32 **)(menu+0x4c))[3]=0;
}

/* Measured target: byte-identical across all 27 levels. */
/* Sets the selected entry number of a menu. */
void menu_set_selected_index(u8 *menu, s32 index) { *(s32 *)(menu + 0x50) = index; }

/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in a menu field. */
void menu_set_field_bc(u8 *menu, s32 value) { *(s32 *)(menu + 0xbc) = value; }

/* Measured target: byte-identical across all 27 levels. */
/* Gives back the selected entry number of a menu. */
s32 menu_get_selected_index(u8 *menu) { return *(s32 *)(menu + 0x50); }

/* Measured target: byte-identical across all 27 levels. */
/* Gives back how many entries a menu has. */
s32 menu_get_entry_count(u8 *menu) { return *(s32 *)(menu + 0xb0); }

/* func_00348138 is built from 00345358-menu.c. */

/* Sets up the seven sprites and seven labels of a menu screen. */
char *menu_init_seven_labels(char *menu)
{
    char *label = menu + 536;
    int i;

    Faac80289_FUN_003361A8(menu);
    Faac80289_FUN_003361A8(menu + 76);
    Faac80289_FUN_003361A8(menu + 152);
    Faac80289_FUN_003361A8(menu + 228);
    Faac80289_FUN_003361A8(menu + 304);
    Faac80289_FUN_003361A8(menu + 380);
    Faac80289_FUN_003361A8(menu + 456);

    for (i = 6; i != -1; i--) {
        Faac80289_FUN_00336968(label);
        label += 72;
    }
    return menu;
}


/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in a menu field. */
void menu_set_field_448(u8 *menu, s32 value) { *(s32 *)(menu + 0x448) = value; }

/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in another menu field. */
void menu_set_field_44c(u8 *menu, s32 value) { *(s32 *)(menu + 0x44c) = value; }

/* Forwards one shared global pointer plus a fixed byte offset, together with five distinct fixed offsets of the first object, into the same callee five times, reading one distinct word of the second object each call. */
/* Loads five menu sprites from the shared sprite data, one for each given value. */
void menu_load_sprites_from_values(char *menu, int *spriteIds)
{
    object_set_helper_result(menu,       D_L00_001A904C_3 + 0x8710, spriteIds[0]);
    object_set_helper_result(menu + 304, D_L00_001A904C_3 + 0x8710, spriteIds[2]);
    object_set_helper_result(menu + 76,  D_L00_001A904C_3 + 0x8710, spriteIds[4]);
    object_set_helper_result(menu + 152, D_L00_001A904C_3 + 0x8710, spriteIds[8]);
    object_set_helper_result(menu + 228, D_L00_001A904C_3 + 0x8710, spriteIds[6]);
}

/* Stores a value in a slot of a small table in the menu. */
void menu_set_table_slot(u8 *menu, s32 slot, s32 value) { menu += slot * 4; *(s32 *)(menu + 0x418) = value; }

/* stores the count in a field, then loops count times calling one helper on each successive 72-byte slot and passing the result to a second helper. */
/* Sets how many icons the menu shows and prepares each icon from a list. */
void menu_set_icon_count_and_icons(char *menu, int count, int *iconIds)
{
    int i;

    *(int *)(menu + 1092) = count;
    for (i = 0; i < count; i++)
        func_L00_0042C360_1(menu + 536 + i * 72, func_00288FB8_2(iconIds[i]));
}

/* func_003486A8 is built from 00345358-children.c. */

/* func_003489E8 is built from 00345358-list-g8.c. */


/* Gives back the object it was given. */
void *menu_return_object(void *object) {
    return object;
}

/* Clears a menu and sets all its sixteen entries to empty. */
void menu_clear_entries(s32 *menu) {
 u8 *entry=(u8 *)menu+0x50; s32 empty=-1; s32 i=15;
 menu[0]=0;menu[0x52]=0;
 do {
  *(s32 *)(entry-12)=empty;*(s32 *)(entry-8)=empty;*(s32 *)(entry-4)=empty;*(s32 *)entry=empty;
  i--;entry+=16;
 }while(i>=0);
 menu[0x54]=0;menu[0x55]=0;
}

/* func_00349190 is built from 00345358-input-g8.c. */

/* Clears a menu field. */
void menu_clear_field_150(int *menu)
{
    menu[0x150 / sizeof(int)] = 0;
}

/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in a menu field. */
void menu_set_field_144(u8 *menu, s32 value) { *(s32 *)(menu + 0x144) = value; }

/* Clears sixteen words of a block to zero and gives the block back. */
u8 *menu_clear_sixteen_words(u8 *block) {
 s32 *word=(s32 *)(block+0x30);s32 i=3;
 do {
  word[0]=0;word[1]=0;word[2]=0;word[3]=0;
  i--;word+=4;
 }while(i!=-1);
 return block;
}

/* Zeroes six word fields of an object, reads back the first one as a float, calls a helper twice with that float (then with 1.0f) over five float arguments, sets two more int fields, and calls a second helper with two float arguments. */
/* Sets up a fade effect with its starting values. */
void fade_init(char *fade)
{
    float start;

    *(int *)(fade + 24) = 0;
    *(float *)(fade + 40) = 0.0f;
    start = *(float *)(fade + 24);
    *(float *)(fade + 44) = 0.0f;
    *(float *)(fade + 128) = 0.0f;
    *(float *)(fade + 36) = 0.005f;
    func_003495D8_1(fade, 0, start, start, start, start, start);
    func_003495D8_1(fade, 1, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    *(int *)(fade + 132) = 2;
    anim_set_key_range(fade, 0, start, start);
    *(int *)(fade + 32) = 0;
    *(int *)(fade + 28) = 1;
}


/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in a fade field. */
void fade_set_field_2c(u8 *fade, s32 value) { *(s32 *)(fade + 0x2c) = value; }


typedef struct {
    char reserved[0x18];
    float value;
    char gap[0xC];
    int mode;
} Value_3495A0;

/* Resets the fade amount to zero and returns the old amount. */
float fade_reset_amount(Value_3495A0 *fade) {
    float previous = fade->value;
    fade->value = 0.0f;
    fade->mode = 1;
    return previous;
}

/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in a fade field. */
void fade_set_field_80(u8 *fade, s32 value) { *(s32 *)(fade + 0x80) = value; }

/* Swaps in a new value and returns the old one. */
s32 fade_swap_field_28(u8 *fade, s32 newValue) { s32 oldValue = *(s32 *)(fade + 0x28); *(s32 *)(fade + 0x28) = newValue; return oldValue; }

/* Store an indexed four-component parameter row and its float weight */
void fade_set_parameter_row(f32 weight, f32 x, f32 y, f32 z, f32 w, JammingParameterRows *object, s32 index) {
    object->rows[index].x = x;
    object->rows[index].y = y;
    object->rows[index].z = z;
    object->rows[index].w = w;
    object->weights[index] = weight;
}

/* Stores a value in a field of an effect. */
void effect_set_field_84(int effect, int value) {
    *(int *)(effect + 0x84) = value;
}

/* Starts a fade in one direction, unless one is already running. */
void fade_start_direction(u8 *fade,s32 direction) {
 *(s32 *)(fade+0x1c)=direction;
 if(*(s32 *)(fade+0x28)==0) {
  if(direction==1) *(f32 *)(fade+0x18)=0.0f;
  else *(f32 *)(fade+0x18)=1.0f;
  *(s32 *)(fade+0x28)=1;
 }
}

/* Stores a value in a field of an effect. */
void effect_set_field_20(int effect, unsigned int value)
{
  *(unsigned int *)(effect + 32) = value;
  return;
}

/* Measured target: byte-identical across all 27 levels. */
/* Sets the speed of a fade. */
void fade_set_speed(u8 *fade, f32 speed) { *(f32 *)(fade + 0x24) = speed; }

/* func_00349680 is built with float min/max in 00345358-interpolation.c. */

/* Clears two groups of three rows to zero and gives the block back. */
u8 *effect_clear_row_groups(u8 *block) {
 s32 *word=(s32 *)(block+0x2c); s32 i=1;
 do {
  s32 *groupEnd=word+12;
  s32 remaining=i-1;
  s32 j=2;
  do {
   word[0]=0;word[1]=0;word[2]=0;word[3]=0;
   j--;word+=4;
  } while(j!=-1);
  i=remaining;word=groupEnd;
 } while(i!=-1);
 return block;
}


/* Initialises a record of four 1.0 floats, one zero, one small constant and four zero words, then runs the same four-argument setup four times with two selector flags swept over 0 and 1. */
/* Sets up a color effect with default values for all four combinations of its two switches. */
void color_effect_init(S_F49afcbfe *effect)
{
    float zero;

    effect->f0 = 1.0f;
    effect->f4 = 1.0f;
    effect->f8 = 1.0f;
    effect->f12 = 1.0f;
    effect->f16 = 0.0f;
    effect->f24 = 6.6665999591350555419922e-02f;
    effect->i28 = 0;
    effect->i32 = 0;
    effect->i36 = 0;
    effect->i40 = 0;
    zero = effect->f16;
    func_00349A70_1(effect, 0, 0, zero, zero, zero, zero);
    func_00349A70_1(effect, 0, 1, zero, zero, zero, zero);
    func_00349A70_1(effect, 1, 0, zero, zero, zero, zero);
    func_00349A70_1(effect, 1, 1, zero, zero, zero, zero);
}


/* Stores a value in a slot of a small table. */
void effect_set_table_slot(u8 *effect, s32 slot, s32 value) { effect += slot * 4; *(s32 *)(effect + 0x20) = value; }

/* Store four float components in a selected row of a parameter group */
void color_effect_set_grid_row(f32 x, f32 y, f32 z, f32 w, JammingGridObject *object, s32 row, s32 group) {
    object->groups[group].rows[row].x = x;
    object->groups[group].rows[row].y = y;
    object->groups[group].rows[row].z = z;
    object->groups[group].rows[row].w = w;
}

/* Stores a value in a slot of a small table. */
void effect_set_table_slot_8c(u8 *effect, s32 slot, s32 value) { effect += slot * 4; *(s32 *)(effect + 0x8C) = value; }

/* Starts a fade-in or fade-out going forward, from fully off or fully on. */
void fade_start_forward(u8 *fade,s32 startFull) {
 if(startFull!=0) *(f32 *)(fade+0x10)=1.0f;
 else *(f32 *)(fade+0x10)=0.0f;
 *(s32 *)(fade+0x14)=1;
 *(s32 *)(fade+0x1c)=1;
}

/* Starts a fade going backward, from fully on or fully off. */
void fade_start_backward(u8 *fade,s32 startEmpty) {
 if(startEmpty!=0) *(f32 *)(fade+0x10)=0.0f;
 else *(f32 *)(fade+0x10)=1.0f;
 *(s32 *)(fade+0x14)=-1;
 *(s32 *)(fade+0x1c)=1;
}

/* Measured target: byte-identical across all 27 levels. */
/* Sets the current amount of a fade. */
void fade_set_amount(u8 *fade, f32 amount) { *(f32 *)(fade + 0x18) = amount; }

extern void *object_construct_derived_a(char *);
extern void *object_construct_derived_b(char *);
extern char *object_init_type_pointer(char *);
extern char g_meter_vtable_b[] __attribute__((sda));
extern char g_meter_vtable_a[] __attribute__((sda));

/* Sets up the sprites, labels and fade effects of a meter screen. */
char *meter_screen_init_parts(char *meter)
{
    object_construct_derived_a(meter + 0x10);
    object_construct_derived_a(meter + 0x5C);
    object_construct_derived_a(meter + 0xA8);
    object_construct_derived_b(meter + 0xF4);
    menu_clear_sixteen_words(meter + 0x140);
    object_init_type_pointer(meter + 0x1CC);
    *(char **)(meter + 0x1CC) = g_meter_vtable_b;
    object_init_type_pointer(meter + 0x1D0);
    *(char **)(meter + 0x1D0) = g_meter_vtable_a;
    menu_clear_sixteen_words(meter + 0x1D4);
    menu_clear_sixteen_words(meter + 0x25C);
    menu_clear_sixteen_words(meter + 0x2E4);
    menu_clear_sixteen_words(meter + 0x36C);
    return meter;
}


/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in the first field of an object. */
void menu_set_first_field(u8 *object, s32 value) { *(s32 *)(object + 0x0) = value; }

/* Replace the value at offset 0x04 and, when it changes while the bound debug byte is zero, retain the previous value and set the two counters to 180 and 300; original game role is unknown. */
void meter_set_value_start_timers(Rac2Native_79744baad5ad7f65_ScalarChange48Owner *owner, int value)
{
    int previous = owner->value_04;
    if (previous != value && g_screen_mode_flag[0] == 0) {
        owner->previous_3fc = previous;
        owner->counter_3f8 = 180;
        owner->counter_3f4 = 300;
    }
    owner->value_04 = value;
}

typedef struct { char bytes[0x4C]; } StageSprite;
typedef struct { char prefix[0x5C]; StageSprite left, right; } StageOwner;
typedef struct { float values[3]; } StageFloatTable;
typedef struct { int values[3]; } StageIntTable;
extern const StageFloatTable g_item_grid_spacing_table, g_item_grid_result_table;
extern const StageIntTable g_item_grid_x_offsets, g_item_grid_y_offsets;
extern void object_set_value_float(char *widget, float position);

/* Works out the layout of the item grid for the given item number and sets up its two arrow sprites. */
float item_grid_layout(char *screen, int type, int *columns, int *rows,
                    float *spacing, int *xOffset, int *yOffset, int *flag,
                    float *extra)
{
    StageOwner *owner = (StageOwner *)screen;
    StageFloatTable spacings, results;
    StageIntTable xOffsets, yOffsets;
    int index, tier;
    float position, result = 0.0f;

    spacings = g_item_grid_spacing_table;
    results = g_item_grid_result_table;
    *flag = 0;
    index = type - 1;
    xOffsets = g_item_grid_x_offsets;
    tier = 1;
    if (type > 20) tier = 2;
    *rows = tier;
    if (index < 0) index = 0;
    yOffsets = g_item_grid_y_offsets;
    if (type >= 1 && type <= 20) {
        position = (float)(index / 4);
        *columns = 6;
        *spacing = spacings.values[0];
        *xOffset = xOffsets.values[0];
        *yOffset = yOffsets.values[0];
        result = results.values[0];
        *extra = 0.0f;
        object_set_value_float((char *)&owner->left, position);
        object_set_value_float((char *)&owner->right, position);
        object_set_helper_result((char *)&owner->left, g_resident_data_base + 0x8710, 17);
        object_set_helper_result((char *)&owner->right, g_resident_data_base + 0x8710, 18);
    } else if (type >= 21 && type <= 40) {
        int row = index / 4 - 5;
        if (row < 0) row = 0;
        position = (float)row;
        *columns = 10;
        *spacing = spacings.values[1];
        *xOffset = xOffsets.values[1];
        *yOffset = yOffsets.values[1];
        *extra = -0.5f;
        result = results.values[1];
        object_set_value_float((char *)&owner->left, position);
        object_set_value_float((char *)&owner->right, position);
        object_set_helper_result((char *)&owner->left, g_resident_data_base + 0x8710, 19);
        object_set_helper_result((char *)&owner->right, g_resident_data_base + 0x8710, 20);
    } else if (type >= 41 && type <= 80) {
        int row = index / 4 - 10;
        if (row < 0) row = 0;
        position = (float)row;
        *columns = 10;
        *spacing = spacings.values[2];
        *xOffset = xOffsets.values[2];
        *yOffset = yOffsets.values[2];
        *extra = -0.5f;
        *flag = 1;
        result = results.values[2];
        object_set_value_float((char *)&owner->left, position);
        object_set_value_float((char *)&owner->right, position);
        object_set_helper_result((char *)&owner->left, g_resident_data_base + 0x8710, 21);
        object_set_helper_result((char *)&owner->right, g_resident_data_base + 0x8710, 22);
    }
    return result;
}

/* func_0034A808 is in 0034A808.c. */

/* func_0034AA30 is built from 0034AA30.c. */

/* Moves the labels to follow the screen position, updates the meter and counts down the show timer. */
void meter_screen_update(char *meter)
{
    float *labelPos = object_get_first_field(meter + 0x5C);

    {
        float x = ref_L00_001AEAC8_00;
        float px = (*(float **)(meter + 8))[0];
        float y = ref_L00_001AEACC_00;
        labelPos[0] = x + px;
        labelPos[1] = y + (*(float **)(meter + 8))[1];
    }

    labelPos = object_get_first_field(meter + 0xA8);
    {
        float x = ref_L00_001AEAD0_00;
        float px = (*(float **)(meter + 8))[0];
        float y = ref_L00_001AEAD4_00;
        labelPos[0] = x + px;
        labelPos[1] = y + (*(float **)(meter + 8))[1];
    }

    hud_meter_bar_update(meter);
    anim_update_keyframe(meter + 0x140, 1);

    if (*(int *)(meter + 0x3F4) != 0) {
        int timeLeft = *(int *)(meter + 0x3F4) - 1;
        *(int *)(meter + 0x3F4) = timeLeft;
        if (timeLeft == 0) {
            *(int *)(meter + 0x0C) = 0;
            *(int *)(meter + 0x3F8) = 0;
            *(int *)(meter + 0x400) = 1;
            func_00349630_2(meter + 0x1D4, -1);
            func_00349630_2(meter + 0x25C, -1);
            func_00349630_2(meter + 0x2E4, -1);
            func_00349630_2(meter + 0x36C, -1);
        }
    }
}

void DrawSegmentedRingMeter(char *o)
{
    if (*(int *)(o + 0xC)) {
        float x, y, size;
        int mode, color = 0, i;

        gfx_draw_screen_element_stored(o + 0x5C);
        gfx_draw_screen_element_stored(o + 0xA8);
        hud_draw_progress_bar(o + 0xF4);
        x = 0;
        y = 0;
        size = 0;
        mode = 0;
        if (*(int *)(o + 0x3F8)) {
            color = math_ping_pong_blend_values(-1, 0x22222222, 10, 0, 0);
            --*(int *)(o + 0x3F8);
        }
        for (i = 0; i < *(int *)(o + 4); i++) {
            int flash = 0;
            float sx, sy;

            if (*(int *)(o + 0x3F8) && i >= *(int *)(o + 0x3FC))
                flash = 1;
            menu_grid_compute_tile_placement(o, *(int *)(o + 4), i, &x, &y, &size, &mode);
            object_set_first_float4(o + 0x10, x, y, 0, 0);
            sx = size;
            sy = size;
            switch (mode) {
            case 0:
                break;
            case 1:
                sx = -size;
                break;
            case 2:
                sy = -size;
                break;
            case 3:
                sy = -size;
                sx = -sx;
                break;
            }
            object_set_second_float4(o + 0x10, sx, sy, 0, 0);
            if (*(int *)(o + 4) < 21) {
                if (*(int *)o >= i + 1) {
                    object_set_helper_result(o + 0x10, g_resident_data_base + 0x8710, 26);
                    if (flash)
                        *(int *)object_get_fourth_field((unsigned char *)o + 0x10) = color;
                    else
                        *(float *)object_get_fourth_field((unsigned char *)o + 0x10) = **(float **)(o + 0x1C8);
                    gfx_draw_screen_element_stored(o + 0x10);
                }
                object_set_helper_result(o + 0x10, g_resident_data_base + 0x8710, 25);
                *(int *)object_get_fourth_field((unsigned char *)o + 0x10) = 0x55F0C070;
                gfx_draw_screen_element_stored(o + 0x10);
            } else {
                if (*(int *)o >= i + 1) {
                    object_set_helper_result(o + 0x10, g_resident_data_base + 0x8710, 27);
                    if (flash)
                        *(int *)object_get_fourth_field((unsigned char *)o + 0x10) = color;
                    else
                        *(float *)object_get_fourth_field((unsigned char *)o + 0x10) = **(float **)(o + 0x1C8);
                    gfx_draw_screen_element_stored(o + 0x10);
                }
                object_set_helper_result(o + 0x10, g_resident_data_base + 0x8710, 24);
                *(int *)object_get_fourth_field((unsigned char *)o + 0x10) = 0x55F0C070;
                gfx_draw_screen_element_stored(o + 0x10);
            }
        }
    }
}

/* Sets the position of the object to the two given numbers. */
void menu_set_object_position(u8 *object, f32 posX, f32 posY) {
    *(f32 *)*(u8 **)(object + 0x8) = posX;
    *(f32 *)(*(u8 **)(object + 0x8) + 0x4) = posY;
}

/* Stores an argument at +1012; if the word at +1024 is zero it returns, else it clears +1024, sets +12 to 1 and calls one callee four times on this+468/604/740/876 with argument 1. */
/* Stores a value, and if a pending flag is set, clears it and restarts four fades. */
void menu_set_flag_restart_fades(char *menu, int value)
{
    *(int *)(menu + 1012) = value;
    if (*(int *)(menu + 1024) == 0)
        return;
    *(int *)(menu + 1024) = 0;
    *(int *)(menu + 12) = 1;
    func_00349630_2(menu + 468, 1);
    func_00349630_2(menu + 604, 1);
    func_00349630_2(menu + 740, 1);
    func_00349630_2(menu + 876, 1);
}



/* func_0034B2C8 is defined in 0034B2C8-hud.c. */

/* Reads the top byte of the color of the label at the end of the screen. */
unsigned int menu_get_label_color_alpha(unsigned char *screen)
{
    unsigned int address = (unsigned int)object_get_fourth_field(screen + 0x358);
    return *(unsigned int *)address & 0xff000000u;
}

extern void hud_set_widget_value_pair(char *, int, int);
/* Switches the screen mode and starts the matching sound. */
void menu_set_screen_mode_and_sound(char *screen, int mode)
{
    *(int *)(screen + 0x1584) = mode;
    switch (mode) {
    case 0:
        hud_set_widget_value_pair(screen + 0x280, 0x7567, 0);
        break;
    case 1:
        hud_set_widget_value_pair(screen + 0x280, 0xEAA2, 0);
        break;
    }
}

/* Stores a value and, when a pending flag is set, restarts the screen fades and sound. */
void menu_set_screen_value_restart_fades(char *screen, void *sound, int value)
{
    *(int *)(screen + 0x1564) = value;
    if (*(int *)(screen + 0x1568) != 0) {
        *(int *)(screen + 0x1568) = 0;
        F72a1dff5_FUN_00349AB8(screen + 0xf1c, 0);
        F72a1dff5_FUN_00349AB8(screen + 0xfb0, 0);
        F72a1dff5_FUN_00349AB8(screen + 0x1044, 0);
        F72a1dff5_FUN_00349630(screen + 0x10d8, 1);
        F72a1dff5_FUN_00349AB8(screen + 0x1160, 0);
        F72a1dff5_FUN_00336920(screen + 0x148, sound, 0);
    }
    if (*(int *)(screen + 0x157c) != 0) {
        F72a1dff5_FUN_00336920(screen + 0x148, sound, 0);
    }
}

/* Stores a value and, when a pending flag is set, restarts six fades with a speed that depends on a setting. */
void menu_set_screen_value_restart_six_fades(char *screen, int value)
{
    char *fade1, *fade2, *fade3, *fade4, *fade5, *fade6;

    *(s32 *)(screen + 5492) = value;
    if (*(s32 *)(screen + 5496) != 0) {
        *(s32 *)(screen + 5496) = 0;
        F01bd4546_FUN_00335E68(screen + 1464, 0);
        fade1 = screen + 3052;
        fade2 = screen + 3188;
        fade3 = screen + 3324;
        fade4 = screen + 3460;
        fade5 = screen + 3596;
        fade6 = screen + 3732;
        F01bd4546_FUN_00349630(fade1, 1);
        F01bd4546_FUN_00349630(fade2, 1);
        F01bd4546_FUN_00349630(fade3, 1);
        F01bd4546_FUN_00349630(fade4, 1);
        F01bd4546_FUN_00349630(fade5, 1);
        F01bd4546_FUN_00349630(fade6, 1);
        F01bd4546_FUN_00349678(fade1, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(fade2, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(fade3, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(fade4, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(fade5, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
        F01bd4546_FUN_00349678(fade6, *(s32 *)0x1A7B90 ? 0.14f : 0.116666675f);
    }
}

extern int g_menu_input_flags;
extern int math_ping_pong_blend_values(int, int, int, int, int);

extern float *object_get_field_a(void *);
extern void object_set_flag_value(void *, int);
/* Shows a label with a new color and value, and makes a sound if a button is held. */
void menu_show_colored_label(char *screen, int text, float value)
{
    int *color;
    char *label;
    if (g_menu_input_flags & 0xF000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    label = screen + 0x5B8;
    color = (int *)object_get_fourth_field((unsigned char *)label);
    *color = math_ping_pong_blend_values(0x60442D00, 0x70FFFEED, 20, 0, 0);
    *object_get_field_a(label) = value;
    object_set_flag_value(label, text);
}

/* Stores a value and, when a pending flag is set, restarts four fades. */
void menu_set_screen_value_restart_four_fades(int *screen, int value)
{
    screen[1371] = value;
    if (screen[1372] != 0) {
        screen[1372] = 0;
        F076896f4_FUN_00349AB8((char *)screen + 4596, 0);
        F076896f4_FUN_00349AB8((char *)screen + 4744, 0);
        F076896f4_FUN_00349AB8((char *)screen + 4892, 0);
        F076896f4_FUN_00349AB8((char *)screen + 5040, 0);
    }
}

/* Measured target: byte-identical across all 27 levels. */
/* Stores a value in a screen field. */
void menu_set_screen_field_2bc(u8 *screen, s32 value) { *(s32 *)(screen + 0x2bc) = value; }
