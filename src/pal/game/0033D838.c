#include "include_asm.h"
#include "names.h"
extern unsigned char g_option_flag_c __attribute__((sda));


extern void prompt_bar_set_texts_pal(void *, char *, char *, char *);
extern void prompt_bar_update_pal(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern int snd_play_from_global_bank(int, int, int);
extern unsigned char g_option_toggle_b __attribute__((sda));
extern char *GetLocalizedString(int);
extern void prompt_bar_draw_pal(void *);
extern void gfx_reapply_display_layout(void);
extern void FontSetWindow(void *, int, int, int, int, int, int, int, int);
extern void text_draw_window_small(void *, unsigned long, char *, int);
extern short g_screen_adjust_offsets[];

extern int Ffb202470_FUN_0033AB50(char *p);

/* Destroys the prompt bar of the map screen and returns the object (PAL). */
char *map_screen_destroy_prompt_bar_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_PAL_0033DDC0, the PAL copy of func_0033BE98: the same C, with the three-string setup added. */
int screen_adjust_menu_update_pal(char *object, int mask)
{
    char *sub;
    char *text, *second;
    short old_x;
    short old_y;
    int *anchor;

    sub = object + 8;
    text = GetLocalizedString(0x1B73);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(sub, text, second, GetLocalizedString(0xB60));
    prompt_bar_update_pal(sub);
    anchor = *(int **)(object + 0x2DC);
    menu_set_anchor_pos(sub, *(float *)anchor, *(float *)(anchor + 1));
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2D8) == 0)
        snd_play_from_global_bank(4, 0, 0);
    if ((mask & 0xf000) != 0) {
        short *offsets = g_screen_adjust_offsets;
        old_x = offsets[180];
        old_y = offsets[181];
        if ((mask & 0x1000) != 0) {
            ((unsigned short *)offsets)[181] = ((unsigned short *)offsets)[181] - 1;
            if ((short)((unsigned short *)offsets)[181] < -32)
                offsets[181] = -32;
        }
        if ((mask & 0x4000) != 0) {
            unsigned short *offsets_b = (unsigned short *)g_screen_adjust_offsets;
            offsets_b[181] = offsets_b[181] + 1;
            if ((short)offsets_b[181] > 32)
                ((short *)offsets_b)[181] = 32;
        }
        if ((mask & 0x8000) != 0) {
            unsigned short *offsets_b = (unsigned short *)g_screen_adjust_offsets;
            offsets_b[180] = offsets_b[180] - 1;
            if ((short)offsets_b[180] < -40)
                ((short *)offsets_b)[180] = -40;
        }
        if ((mask & 0x2000) != 0) {
            unsigned short *offsets_b = (unsigned short *)g_screen_adjust_offsets;
            offsets_b[180] = offsets_b[180] + 1;
            if ((short)offsets_b[180] > 40)
                ((short *)offsets_b)[180] = 40;
        }
        {
            short *offsets_b = g_screen_adjust_offsets;
            if (old_x != offsets_b[180] || old_y != offsets_b[181])
                snd_play_from_global_bank(4, 0, 0);
        }
        gfx_reapply_display_layout();
    }
    return (mask >> 6) & 1;
}

/* func_PAL_0033DF90, the PAL copy of func_0033C028: only the box and its label remain. */
void onoff_menu_draw_with_help_pal(char *object)
{
    char scratch[32];

    prompt_bar_draw_pal(object + 8);
    FontSetWindow(scratch, 0x96, 0x167, 44, 468, 254, 180, 20, 3);
    text_draw_window_small(scratch, 0x80F0F0F0UL, GetLocalizedString(0x1B6E), -1);
}

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the screen adjust menu and returns the object (PAL). */
char *screen_adjust_menu_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

/* func_PAL_0033E160 is in 0033E160.c (-mno-split-addresses). */



/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the on/off menu and returns the object (PAL). */
char *onoff_menu_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}





/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the four-option menu and returns the object (PAL). */
char *four_option_menu_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern int Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

/* Updates the two-toggle menu: moves the selection and flips the chosen option on X (PAL). */
int two_toggle_a_update_pal(char *menu, int pad_flags)
{
    char *prompt_bar = menu + 8;
    float *anchor;
    int selection;

    Fc558ca70_FUN_0033AE28(prompt_bar);
    anchor = *(float **)(menu + 732);
    Fc558ca70_FUN_0033B018(prompt_bar, anchor[0], anchor[1]);
    if (pad_flags & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        selection = *(int *)(menu + 728);
        *(int *)(menu + 728) = (selection + 1) % 2;
    } else if (pad_flags & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        selection = *(int *)(menu + 728);
        *(int *)(menu + 728) = (selection + 1) % 2;
    } else if (pad_flags & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(menu + 728)) {
        case 0:
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (pad_flags >> 6) & 1;
}



extern void *prompt_bar_destroy_pal(int);

/* Destroys the audio menu: its prompt bar and two volume meters (PAL). */
char *two_toggle_a_destroy_pal(char *object)
{
    extern void *object_construct_derived_b(void *);
    prompt_bar_destroy_pal((int)(object + 8));
    object_construct_derived_b(object + 0x2DC);
    object_construct_derived_b(object + 0x324);
    return object;
}




typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair g_audio_menu_text_pair;
extern char g_str_audio_menu_format[];
extern void hud_draw_progress_bar(void *);
extern void text_draw_right_aligned_medium(int, int, unsigned long, char *, int);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);
extern char g_str_toggle_menu_format[];
extern void prompt_bar_draw_pal(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern SolTextPair g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
extern void prompt_bar_draw_pal(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);

/* func_0033D028 uses small data in 0033D028-g8.c. */

/* Draws the audio menu: two volume meters with labels and the third option with its value (PAL). */
void audio_menu_draw_pal(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *format, *first, *second;
    char *format2, *middle, *last;
    int color;
    prompt_bar_draw_pal(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_audio_menu_text_pair;
    format = g_str_audio_menu_format;
    first = GetLocalizedString(0xE34);
    sprintf(buffer, format, first);
    text_draw_right_aligned_medium(0x100, 0x91, color, buffer, -1);
    hud_draw_progress_bar(object + 0x2DC);
    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    middle = GetLocalizedString(0xE35);
    sprintf(buffer, format, middle);
    text_draw_right_aligned_medium(0x100, 0xBE, color, buffer, -1);
    hud_draw_progress_bar(object + 0x324);
    color = *(int *)(object + 0x2D8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    format2 = g_str_toggle_menu_format;
    last = GetLocalizedString(0xE36);
    second = GetLocalizedString(pair.ids[*(int *)0x1A7C20 != 0]);
    sprintf(buffer, format2, last, second);
    text_draw_centered_medium(0x100, 0xE1, color, buffer, -1);
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the single-toggle menu and returns the object (PAL). */
char *single_toggle_a_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



extern void F5979c03f_FUN_0033AE28 (char *object);
extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);
extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

/* Updates the single-toggle menu: flips its option on X (PAL). */
int single_toggle_a_update_pal (char *object, int flags)
{
  unsigned char *flag = &g_option_flag_c;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *flag = (*flag < 1);
    }

  return (flags >> 6) & 1;
}


extern int text_draw_centered_small(int, int, unsigned long, char *, int);

/* Draws the single-toggle menu: one option label with its current value (PAL). */
void single_toggle_a_draw_pal(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    int color;
    prompt_bar_draw_pal(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0xBAA);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7C1E != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, color, buffer, -1);
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the second single-toggle menu and returns the object (PAL). */
char *single_toggle_b_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}







/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the second two-toggle menu and returns the object (PAL). */
char *two_toggle_b_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_PAL_0033FB00, the PAL copy of func_0033DC30: the same C, with the three-string setup added. */
int single_toggle_c_update_pal(char *object, int flags)
{
    float *vec;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_update_pal(child);
    vec = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int discarded = snd_play_from_global_bank(4, 0, 0);
        (void)discarded;
        g_option_toggle_b = (g_option_toggle_b < 1);
    }

    return (flags >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the third single-toggle menu and returns the object (PAL). */
char *single_toggle_c_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_PAL_0033FDF8, the PAL copy of func_0033DEE0: the same C, with the three-string setup added. */
int single_toggle_d_update_pal(char *object, int flags)
{
    float *vec;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_update_pal(child);
    vec = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int discarded = snd_play_from_global_bank(4, 0, 0);
        (void)discarded;
        g_option_toggle_b = (g_option_toggle_b < 1);
    }

    return (flags >> 6) & 1;
}

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Destroys the prompt bar of the fourth single-toggle menu and returns the object (PAL). */
char *single_toggle_d_destroy_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_PAL_00340038, the PAL copy of func_0033E0D8: the same C, with the three-string setup added. */
int single_toggle_e_update_pal(char *object, int flags)
{
    float *vec;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text, second, GetLocalizedString(0xB60));
    prompt_bar_update_pal(child);
    vec = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int discarded = snd_play_from_global_bank(4, 0, 0);
        (void)discarded;
        g_option_toggle_b = (g_option_toggle_b < 1);
    }

    return (flags >> 6) & 1;
}



extern int list_menu_get_selected_index_pal(int);

/* Returns the address of the selected record in the list page owner (PAL). */
int list_page_get_selected_record_pal(int owner)
{
    int result;
    result = list_menu_get_selected_index_pal(owner);
    return *(int *)(owner + 0x3B8) + result * 0x14;
}




extern void *UpdateMenuListSelection_pal(char *, int);
extern void menu_set_position_pal(char *, float, float);

/* func_PAL_00340348, the PAL copy of func_0033E3A0: the same C, with the three-string setup added and the second child moved. */
int list_page_update_pal(char *object, int flags)
{
    char *prompt_bar = object + 8;
    char *list;
    float *position;
    char *text, *label;

    text = GetLocalizedString(0xBB1);
    label = GetLocalizedString(0xB86);
    prompt_bar_set_texts_pal(prompt_bar, text, label, GetLocalizedString(0xB60));
    prompt_bar_update_pal(prompt_bar);
    list = object + 0x2E0;
    position = *(float **)(object + 0x3BC);
    menu_set_anchor_pos(prompt_bar, position[0], position[1]);
    UpdateMenuListSelection_pal(list, flags);
    menu_set_position_pal(list, (*(float **)(object + 0x3BC))[0], (*(float **)(object + 0x3BC))[1]);
    return (flags >> 6) & 1;
}





void prompt_bar_draw(int);

/* Draws the frame menu: its prompt bar (PAL). */
void menu_draw_frame_pal(int menu) {
  prompt_bar_draw(menu + 8);
}

extern int func_0033AB50_1(void *);
extern char *cam_init_object_table_c(void *);
extern char *cam_init_object_table_d(void *);
extern char *cam_init_object_table_a(void *);

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
char *frame_text_page_destroy_pal(char *object)
{
    func_0033AB50_1(object + 8);
    cam_init_object_table_c(object + 732);
    cam_init_object_table_d(object + 792);
    cam_init_object_table_d(object + 880);
    cam_init_object_table_d(object + 968);
    cam_init_object_table_a(object + 1056);
    cam_init_object_table_d(object + 1136);
    cam_init_object_table_d(object + 1224);
    cam_init_object_table_d(object + 1312);
    cam_init_object_table_d(object + 1400);
    cam_init_object_table_d(object + 1488);
    cam_init_object_table_d(object + 1576);
    return object;
}







