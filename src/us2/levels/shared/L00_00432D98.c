#include "include_asm.h"
#include "names.h"
extern unsigned char g_option_flag_a __attribute__((sda));
extern unsigned char g_option_flag_b __attribute__((sda));

extern int prompt_bar_destroy(char *p);

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_a_us2(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_b_us2(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_c_us2(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_d_us2(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}

extern void func_0033AE28_2(char *p);
extern void func_L00_00430948_3(char *p, float a, float b);
extern int func_002E5E58_3(int a, int b, int c);
extern volatile unsigned char g_toggle_option_a __attribute__((sda));
extern volatile unsigned char g_subtitles_option __attribute__((sda));

/* makes two float-binding calls, then toggles one of two global flag bytes selected by an object field and returns bit 6 of the flag word */
int menu_handle_page_input_a_us2(char *object, int buttons)
{
    char *bar = object + 8;
    float *vec;
    int value;

    func_0033AE28_2(bar);
    vec = *(float **)(object + 732);
    func_L00_00430948_3(bar, vec[0], vec[1]);
    if (buttons & 0x1000) {
        func_002E5E58_3(3, 0, 0);
        value = *(int *)(object + 728);
        *(int *)(object + 728) = (value + 1) % 2;
    } else if (buttons & 0x4000) {
        func_002E5E58_3(3, 0, 0);
        value = *(int *)(object + 728);
        *(int *)(object + 728) = (value + 1) % 2;
    } else if (buttons & 0x40) {
        func_002E5E58_3(4, 0, 0);
        switch (*(int *)(object + 728)) {
        case 0:
            g_toggle_option_a = g_toggle_option_a == 0;
            break;
        case 1:
            g_subtitles_option = g_subtitles_option == 0;
            break;
        }
    }
    return (buttons >> 6) & 1;
}

/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_e_us2(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}

extern void prompt_bar_update_us2 (char *object);
extern void mem_store_two_floats_through_cell (char *object, float x, float y);
extern int snd_play_from_global_bank (int a, int b, int c);

/* resets a sub-object, applies a two-float transform, and when bit 6 of flags is set and an int field is zero calls a mode setter and toggles a global byte */
int menu_handle_page_input_b_us2 (char *object, int flags)
{
  unsigned char *flag_ptr = &g_option_flag_a;
  float *vec;
  int sound_result;

  prompt_bar_update_us2 (object + 8);
  vec = *(float **) (object + 732);
  mem_store_two_floats_through_cell (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      sound_result = snd_play_from_global_bank (4, 0, 0);
      (void) sound_result;
      *flag_ptr = (*flag_ptr < 1);
    }

  return (flags >> 6) & 1;
}


/* Calls a helper with a pointer to the second 16-byte field of the record and returns the record pointer. */
char *menu_init_page_record_f_us2(char *object)
{
    prompt_bar_destroy(object + 8);
    return object;
}


extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern int Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

/* Updates the option page, handles left/right and cross presses, and toggles one of two option bytes; returns bit 6 of the buttons. */
int menu_handle_page_input_c_us2(char *object, int buttons)
{
    char *bar = object + 8;
    float *vec;
    int value;

    Fc558ca70_FUN_0033AE28(bar);
    vec = *(float **)(object + 732);
    Fc558ca70_FUN_0033B018(bar, vec[0], vec[1]);
    if (buttons & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        value = *(int *)(object + 728);
        *(int *)(object + 728) = (value + 1) % 2;
    } else if (buttons & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        value = *(int *)(object + 728);
        *(int *)(object + 728) = (value + 1) % 2;
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


extern int Ffb202470_FUN_0033AB50(char *p);

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Calls a helper on the record's second 16-byte field and returns the record pointer. */
char *menu_l00_init_page_record_g_us2_2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


extern void F5979c03f_FUN_0033AE28 (char *object);
extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);
extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

/* Updates the option page and, on a cross press with the selector at zero, plays a sound and toggles an option byte; returns bit 6 of the flags. */
int menu_handle_page_input_d_us2 (char *object, int flags)
{
  unsigned char *flag_ptr = &g_option_flag_b;
  float *vec;
  int sound_result;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      sound_result = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) sound_result;
      *flag_ptr = (*flag_ptr < 1);
    }

  return (flags >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Calls a helper on the record's second 16-byte field and returns the record pointer. */
char *menu_l00_init_page_record_h_us2_2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* Updates the option page and, on a cross press with the selector at zero, plays a sound and toggles an option byte; returns bit 6 of the flags. */
int menu_handle_page_input_e_us2 (char *object, int flags)
{
  unsigned char *flag_ptr = &g_option_flag_b;
  float *vec;
  int sound_result;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      sound_result = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) sound_result;
      *flag_ptr = (*flag_ptr < 1);
    }

  return (flags >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Calls a helper on the record's second 16-byte field and returns the record pointer. */
char *menu_l00_init_page_record_i_us2_2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* Updates the option page and, on a cross press with the selector at zero, plays a sound and toggles an option byte; returns bit 6 of the flags. */
int menu_handle_page_input_f_us2 (char *object, int flags)
{
  unsigned char *flag_ptr = &g_option_flag_b;
  float *vec;
  int sound_result;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      sound_result = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) sound_result;
      *flag_ptr = (*flag_ptr < 1);
    }

  return (flags >> 6) & 1;
}


extern void *prompt_bar_destroy_us2(void *);
extern unsigned long long menu_pass_through_handle(void *);

/* Destroys the page record and then its second sub-object; returns the object pointer. */
void *menu_init_two_sub_objects_us2(char *object) {
    prompt_bar_destroy_us2(object + 0x8);
    menu_pass_through_handle(object + 0x2E0);
    return object;
}


extern void *cam_init_object_table_d(void *);

/* Destroys the page record and initializes its second sub-object; returns the object pointer. */
void *menu_init_two_sub_objects_b_us2(char *object) {
    prompt_bar_destroy_us2(object + 0x8);
    cam_init_object_table_d(object + 0x2E0);
    return object;
}


extern void prompt_bar_draw(char *p);

void menu_get_sub_object_value_us2(char *p)
{
    prompt_bar_draw(p + 8);
}

