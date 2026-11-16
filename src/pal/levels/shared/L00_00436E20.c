#include "include_asm.h"
#include "names.h"

extern int prompt_bar_destroy(char *p);

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_a_pal(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}

extern int Ffb202470_FUN_0033AB50(char *p);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_page_record_b_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_page_record_c_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_page_record_d_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern int Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

/* Input handler for a two-option toggle page: moves the selection with the d-pad and flips the selected option flag on X. */
int menu_handle_page_input_a_pal(char *object, int buttons)
{
    char *child = object + 8;
    float *pos;
    int choice;

    Fc558ca70_FUN_0033AE28(child);
    pos = *(float **)(object + 732);
    Fc558ca70_FUN_0033B018(child, pos[0], pos[1]);
    if (buttons & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        choice = *(int *)(object + 728);
        *(int *)(object + 728) = (choice + 1) % 2;
    } else if (buttons & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        choice = *(int *)(object + 728);
        *(int *)(object + 728) = (choice + 1) % 2;
    } else if (buttons & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(object + 728)) {
        case 0:
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (buttons >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_page_record_e_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_page_record_f_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}





/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_page_record_g_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


extern char *GetLocalizedString(int);
extern void prompt_bar_set_texts_pal(void *, int, int, int);
extern void prompt_bar_update_pal(void *);
extern void mem_store_two_floats_through_cell(void *, float, float);
extern int snd_play_from_global_bank(int a, int b, int c);
extern unsigned char g_option_toggle_b __attribute__((sda));

/* func_PAL_L00_00438CC0, the PAL copy of func_L00_00433560: the same C, with the child's three
   text_a ids set up first and the two object fields 0x30 further on. */
int menu_update_two_part_flags_a_pal(char *object, int buttons)
{
    float *pos;
    char *child = object + 8;
    int text_a, text_b;

    text_a = GetLocalizedString(0xB72);
    text_b = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text_a, text_b, GetLocalizedString(0xB60));
    prompt_bar_update_pal(child);
    pos = *(float **)(object + 0x2DC);
    mem_store_two_floats_through_cell(child, pos[0], pos[1]);

    if ((buttons & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int sound = snd_play_from_global_bank(4, 0, 0);
        (void)sound;
        g_option_toggle_b = (g_option_toggle_b < 1);
    }

    return (buttons >> 6) & 1;
}

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_sub_object_a_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* func_PAL_L00_00438FB8, the PAL copy of func_L00_00433810: the same C, with the child's three
   text_a ids set up first and the two object fields 0x30 further on. */
int menu_update_two_part_flags_b_pal(char *object, int buttons)
{
    float *pos;
    char *child = object + 8;
    int text_a, text_b;

    text_a = GetLocalizedString(0xB72);
    text_b = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text_a, text_b, GetLocalizedString(0xB60));
    prompt_bar_update_pal(child);
    pos = *(float **)(object + 0x2DC);
    mem_store_two_floats_through_cell(child, pos[0], pos[1]);

    if ((buttons & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int sound = snd_play_from_global_bank(4, 0, 0);
        (void)sound;
        g_option_toggle_b = (g_option_toggle_b < 1);
    }

    return (buttons >> 6) & 1;
}

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Tears down the prompt bar at +8 and returns the page object. */
char *menu_init_sub_object_b_pal(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_PAL_L00_004391F8, the PAL copy of func_L00_00433A08: as func_PAL_L00_00438FB8. */
int menu_update_two_part_flags_c_pal(char *object, int buttons)
{
    float *pos;
    char *child = object + 8;
    int text_a, text_b;

    text_a = GetLocalizedString(0xB72);
    text_b = GetLocalizedString(0xB5F);
    prompt_bar_set_texts_pal(child, text_a, text_b, GetLocalizedString(0xB60));
    prompt_bar_update_pal(child);
    pos = *(float **)(object + 0x2DC);
    mem_store_two_floats_through_cell(child, pos[0], pos[1]);

    if ((buttons & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int sound = snd_play_from_global_bank(4, 0, 0);
        (void)sound;
        g_option_toggle_b = (g_option_toggle_b < 1);
    }

    return (buttons >> 6) & 1;
}

extern void *prompt_bar_destroy_pal(void *);
extern unsigned long long menu_pass_through_handle(void *);

/* Tears down the prompt bar and the text_b sub-object of the page and returns the page object. */
void *menu_init_two_sub_objects_pal(char *object) {
    prompt_bar_destroy_pal(object + 0x8);
    menu_pass_through_handle(object + 0x2E0);
    return object;
}


extern void *cam_init_object_table_d(void *);

/* Tears down the prompt bar and the text_b sub-object of the page and returns the page object. */
void *menu_visit_two_sub_objects_pal(char *object) {
    prompt_bar_destroy_pal(object + 0x8);
    cam_init_object_table_d(object + 0x2E0);
    return object;
}


extern void prompt_bar_draw(char *p);

void menu_get_sub_object_value_pal(char *object)
{
    prompt_bar_draw(object + 8);
}

