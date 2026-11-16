#include "include_asm.h"
#include "names.h"
extern unsigned char g_toggle_option_b __attribute__((sda));
typedef struct { int ids[2]; } SolTextPair;

extern SolTextPair g_audio_menu_text_pair;
extern char g_str_audio_menu_format[];
extern void hud_draw_progress_bar(void *);
extern void text_draw_right_aligned_medium(int, int, unsigned long, char *, int);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);

extern char g_str_toggle_menu_format[];
extern int DrawOptionText(int, int, unsigned long, char *, int) __asm__("func_0027FAA8");
extern void prompt_bar_draw(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);

extern void Fc558ca70_FUN_0033AE28(char *p);

extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);

extern int Fc558ca70_FUN_002E5E58(int a, int b, int c);

extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));

extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

extern int Ffb202470_FUN_0033AB50(char *p);

extern void F5979c03f_FUN_0033AE28 (char *object);

extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);

extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

extern void Fb7feb893_FUN_0033AE28(char *p);

extern void Fb7feb893_FUN_0033B018(char *p, float a, float b);

extern int Fb7feb893_FUN_002E5E58(int a, int b, int c);

extern volatile unsigned char Fb7feb893_D_001A7BB2 __attribute__((sda));

extern volatile unsigned char Fb7feb893_D_001A7BB3 __attribute__((sda));

extern void Fb1bbe20c_FUN_0033AE28(char *p);

extern void Fb1bbe20c_FUN_0033B018(char *p, float x, float y);

extern int Fb1bbe20c_FUN_002E5E58(int a, int b, int c);

extern volatile unsigned char Fb1bbe20c_D_001A7BB2 __attribute__((sda));

void* list_page_destroy(void* param_1);

extern int prompt_bar_destroy(int);

extern unsigned long long menu_pass_through_handle(unsigned long long);

extern int list_menu_get_selected_index(int);

/* Handles input for the two-switch option menu: up/down moves the cursor and the confirm button flips the chosen switch. */
int two_toggle_a_update(char *object, int flags)
{
    char *child = object + 8;
    float *position;
    int selected;

    Fc558ca70_FUN_0033AE28(child);
    position = *(float **)(object + 684);
    Fc558ca70_FUN_0033B018(child, position[0], position[1]);
    if (flags & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(object + 680)) {
        case 0:
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (flags >> 6) & 1;
}

/* Cleans up the two-switch option menu. */
char *two_toggle_a_destroy(char *object)
{
    extern void *object_construct_derived_b(void *);
    prompt_bar_destroy((int)(object + 8));
    object_construct_derived_b(object + 0x2AC);
    object_construct_derived_b(object + 0x2F4);
    return object;
}




/* func_0033D028 uses small data in 0033D028-g8.c. */

/* Draws the audio options menu: the two volume sliders and the sound mode line. */
void audio_menu_draw(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *format, *first, *second;
    char *format2, *middle, *last;
    int color;
    prompt_bar_draw(object + 8);
    color = *(int *)(object + 0x2A8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_audio_menu_text_pair;
    format = g_str_audio_menu_format;
    first = GetLocalizedString(0x2F0F);
    sprintf(buffer, format, first);
    text_draw_right_aligned_medium(0x100, 0x91, color, buffer, -1);
    hud_draw_progress_bar(object + 0x2AC);
    color = *(int *)(object + 0x2A8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    middle = GetLocalizedString(0x2F10);
    sprintf(buffer, format, middle);
    text_draw_right_aligned_medium(0x100, 0xBE, color, buffer, -1);
    hud_draw_progress_bar(object + 0x2F4);
    color = *(int *)(object + 0x2A8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    format2 = g_str_toggle_menu_format;
    last = GetLocalizedString(0x2F11);
    second = GetLocalizedString(pair.ids[*(int *)0x001A7B98 != 0]);
    sprintf(buffer, format2, last, second);
    text_draw_centered_medium(0x100, 0xE1, color, buffer, -1);
}

/* Cleans up the one-switch option menu. */
char *single_toggle_a_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int single_toggle_a_update (char *object, int flags)
{
  unsigned char *setting = &g_toggle_option_b;
  float *position;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  position = *(float **) (object + 684);
  F5979c03f_FUN_0033B018 (object + 8, position[0], position[1]);

  if ((flags & 0x40) && *(int *) (object + 680) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *setting = (*setting < 1);
    }

  return (flags >> 6) & 1;
}


extern SolTextPair g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
/* Resident byte at 0x001A7BB2 is shared by all programs. */
extern void prompt_bar_draw(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

/* Draws the one-switch option line with its current on/off text. */
void single_toggle_a_draw(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    int color;
    prompt_bar_draw(object + 8);
    color = *(int *)(object + 0x2A8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x2D99);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x001A7B96 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, color, buffer, -1);
}


/* Cleans up a one-switch option menu. */
char *single_toggle_b_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for the second two-switch option menu: up/down moves the cursor and confirm flips a switch. */
int two_toggle_b_update(char *object, int flags)
{
    char *child = object + 8;
    float *position;
    int selected;

    Fb7feb893_FUN_0033AE28(child);
    position = *(float **)(object + 684);
    Fb7feb893_FUN_0033B018(child, position[0], position[1]);
    if (flags & 0x1000) {
        Fb7feb893_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x4000) {
        Fb7feb893_FUN_002E5E58(3, 0, 0);
        selected = *(int *)(object + 680);
        *(int *)(object + 680) = (selected + 1) % 2;
    } else if (flags & 0x40) {
        Fb7feb893_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(object + 680)) {
        case 0:
            Fb7feb893_D_001A7BB2 = Fb7feb893_D_001A7BB2 == 0;
            break;
        case 1:
            Fb7feb893_D_001A7BB3 = Fb7feb893_D_001A7BB3 == 0;
            break;
        }
    }
    return (flags >> 6) & 1;
}


/* Cleans up the two-switch option menu. */
char *two_toggle_b_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int single_toggle_c_update(char *object, int flags)
{
    float *vec;

    Fb1bbe20c_FUN_0033AE28(object + 8);
    vec = *(float **)(object + 684);
    Fb1bbe20c_FUN_0033B018(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = Fb1bbe20c_FUN_002E5E58(4, 0, 0);
        (void)discarded;
        Fb1bbe20c_D_001A7BB2 = (Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}


/* Draws the one-switch option line with its current on/off text. */
void single_toggle_c_draw(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    prompt_bar_draw(object + 8);
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x2D9A);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x001A7BB2 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}



/* Cleans up a one-switch option menu. */
char *single_toggle_c_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int single_toggle_d_update(char *object, int flags)
{
    float *vec;

    Fb1bbe20c_FUN_0033AE28(object + 8);
    vec = *(float **)(object + 684);
    Fb1bbe20c_FUN_0033B018(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = Fb1bbe20c_FUN_002E5E58(4, 0, 0);
        (void)discarded;
        Fb1bbe20c_D_001A7BB2 = (Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* Cleans up a one-switch option menu. */
char *single_toggle_d_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}




/* Handles input for a one-switch option menu: the confirm button flips the switch. */
int single_toggle_e_update(char *object, int flags)
{
    float *vec;

    Fb1bbe20c_FUN_0033AE28(object + 8);
    vec = *(float **)(object + 684);
    Fb1bbe20c_FUN_0033B018(object + 8, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 680) == 0) {
        int discarded = Fb1bbe20c_FUN_002E5E58(4, 0, 0);
        (void)discarded;
        Fb1bbe20c_D_001A7BB2 = (Fb1bbe20c_D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* Cleans up a menu page that has a scrolling list. */
void* list_page_destroy(void* object)
{
  prompt_bar_destroy((int)object + 8);
  menu_pass_through_handle((int)object + 0x2b0);
  return object;
}




/* Returns the list entry that is currently selected. */
int list_page_get_selected_record(int owner)
{
    int result;
    result = list_menu_get_selected_index(owner);
    return *(int *)(owner + 0x378) + result * 0x14;
}
