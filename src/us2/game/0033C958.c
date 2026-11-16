#include "include_asm.h"
#include "names.h"
extern unsigned char g_option_flag_a __attribute__((sda));
extern unsigned char g_option_flag_b __attribute__((sda));


extern int Ffb202470_FUN_0033AB50(char *p);

char *map_screen_destroy_prompt_bar_us2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

extern void Fe524d931_FUN_0033AE28(char *p);
extern void Fe524d931_FUN_0033B018(char *p, float x, float y);
extern int Fe524d931_FUN_002E5E58(int a, int b, int c);
extern void Fe524d931_FUN_00284E40(void);
extern short Fe524d931_D_001A6480[];

int screen_adjust_menu_update_us2(char *object, int mask)
{
    char *sub = object + 8;
    short oldx;
    short oldy;
    int *v;

    Fe524d931_FUN_0033AE28(sub);
    v = *(int **)(object + 732);
    Fe524d931_FUN_0033B018(sub, *(float *)v, *(float *)(v + 1));
    if ((mask & 0x40) != 0 && *(int *)(object + 728) == 0)
        Fe524d931_FUN_002E5E58(4, 0, 0);
    if ((mask & 0xf000) != 0) {
        short *p = Fe524d931_D_001A6480;
        oldx = p[180];
        oldy = p[181];
        if ((mask & 0x1000) != 0) {
            ((unsigned short *)p)[181] = ((unsigned short *)p)[181] - 1;
            if ((short)((unsigned short *)p)[181] < -32)
                p[181] = -32;
        }
        if ((mask & 0x4000) != 0) {
            unsigned short *q = (unsigned short *)Fe524d931_D_001A6480;
            q[181] = q[181] + 1;
            if ((short)q[181] > 32)
                ((short *)q)[181] = 32;
        }
        if ((mask & 0x8000) != 0) {
            unsigned short *q = (unsigned short *)Fe524d931_D_001A6480;
            q[180] = q[180] - 1;
            if ((short)q[180] < -40)
                ((short *)q)[180] = -40;
        }
        if ((mask & 0x2000) != 0) {
            unsigned short *q = (unsigned short *)Fe524d931_D_001A6480;
            q[180] = q[180] + 1;
            if ((short)q[180] > 40)
                ((short *)q)[180] = 40;
        }
        {
            short *q = Fe524d931_D_001A6480;
            if (oldx != q[180] || oldy != q[181])
                Fe524d931_FUN_002E5E58(4, 0, 0);
        }
        Fe524d931_FUN_00284E40();
    }
    return (mask >> 6) & 1;
}


char *screen_adjust_menu_destroy_us2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


char *onoff_menu_destroy_us2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



char *four_option_menu_destroy_us2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern int Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

int two_toggle_a_update_us2(char *a0, int a1)
{
    char *p = a0 + 8;
    float *q;
    int v;

    Fc558ca70_FUN_0033AE28(p);
    q = *(float **)(a0 + 732);
    Fc558ca70_FUN_0033B018(p, q[0], q[1]);
    if (a1 & 0x1000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x4000) {
        Fc558ca70_FUN_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 728);
        *(int *)(a0 + 728) = (v + 1) % 2;
    } else if (a1 & 0x40) {
        Fc558ca70_FUN_002E5E58(4, 0, 0);
        switch (*(int *)(a0 + 728)) {
        case 0:
            Fc558ca70_D_001A7B95 = Fc558ca70_D_001A7B95 == 0;
            break;
        case 1:
            Fc558ca70_D_001A7B94 = Fc558ca70_D_001A7B94 == 0;
            break;
        }
    }
    return (a1 >> 6) & 1;
}


extern int prompt_bar_destroy(int);

char *two_toggle_a_destroy_us2(char *object)
{
    extern void *object_construct_derived_b(void *);
    prompt_bar_destroy((int)(object + 8));
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
extern void prompt_bar_draw_us2(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern SolTextPair g_toggle_menu_text_pair;
extern char g_str_toggle_menu_format[];
extern void prompt_bar_draw_us2(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);

/* func_0033D028 uses small data in 0033D028-g8.c. */

void audio_menu_draw_us2(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *format, *first, *second;
    char *format2, *middle, *last;
    int color;
    prompt_bar_draw_us2(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_audio_menu_text_pair;
    format = g_str_audio_menu_format;
    first = GetLocalizedString(0x2DA5);
    sprintf(buffer, format, first);
    text_draw_right_aligned_medium(0x100, 0x91, color, buffer, -1);
    hud_draw_progress_bar(object + 0x2DC);
    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    middle = GetLocalizedString(0x2DA6);
    sprintf(buffer, format, middle);
    text_draw_right_aligned_medium(0x100, 0xBE, color, buffer, -1);
    hud_draw_progress_bar(object + 0x324);
    color = *(int *)(object + 0x2D8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    format2 = g_str_toggle_menu_format;
    last = GetLocalizedString(0x2DA7);
    second = GetLocalizedString(pair.ids[*(int *)0x1A7BA0 != 0]);
    sprintf(buffer, format2, last, second);
    text_draw_centered_medium(0x100, 0xE1, color, buffer, -1);
}


char *single_toggle_a_destroy_us2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

extern void F5979c03f_FUN_0033AE28 (char *object);
extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);
extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

int single_toggle_a_update_us2 (char *object, int flags)
{
  unsigned char *g = &g_option_flag_a;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}


extern int text_draw_centered_small(int, int, unsigned long, char *, int);

void single_toggle_a_draw_us2(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    int color;
    prompt_bar_draw_us2(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = g_toggle_menu_text_pair;
    format = g_str_toggle_menu_format;
    first = GetLocalizedString(0x2C2F);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7B9E != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, color, buffer, -1);
}


char *single_toggle_b_destroy_us2(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_US2_0033EB20(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



int func_US2_0033EC80 (char *object, int flags)
{
  unsigned char *g = &g_option_flag_b;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}



/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_US2_0033EDD0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



int func_US2_0033EF30 (char *object, int flags)
{
  unsigned char *g = &g_option_flag_b;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_US2_0033EFC8(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



int func_US2_0033F128 (char *object, int flags)
{
  unsigned char *g = &g_option_flag_b;
  float *vec;
  int discarded;

  F5979c03f_FUN_0033AE28 (object + 8);
  vec = *(float **) (object + 732);
  F5979c03f_FUN_0033B018 (object + 8, vec[0], vec[1]);

  if ((flags & 0x40) && *(int *) (object + 728) == 0)
    {
      discarded = F5979c03f_FUN_002E5E58 (4, 0, 0);
      (void) discarded;
      *g = (*g < 1);
    }

  return (flags >> 6) & 1;
}




extern int func_US2_0033F398(int);

int func_US2_0033F360(int owner)
{
    int result;
    result = func_US2_0033F398(owner);
    return *(int *)(owner + 0x3B8) + result * 0x14;
}



void func_US2_0033F3B8(unsigned char *owner, float *records)
{
    extern void func_US2_00348DA0(unsigned char *, float *);
    func_US2_00348DA0(owner + 0x2E0, records);
    *(float **)(owner + 0x3B8) = records;
}


extern void prompt_bar_update_us2(char *);
extern void menu_set_anchor_pos(char *, float, float);
extern int func_US2_00348CB8(char *, int);
extern void func_US2_00348E28(char *, float, float);
extern void prompt_bar_update_us2(char *p);
extern void menu_set_anchor_pos(char *p, float x, float y);

int func_US2_0033F3F0(char *object, int flags)
{
    char *first = object + 8;
    char *second;
    float *position;
    prompt_bar_update_us2(first);
    second = object + 0x2E0;
    position = *(float **)(object + 0x3BC);
    menu_set_anchor_pos(first, position[0], position[1]);
    func_US2_00348CB8(second, flags);
    func_US2_00348E28(second, (*(float **)(object + 0x3BC))[0], (*(float **)(object + 0x3BC))[1]);
    return (flags >> 6) & 1;
}





int func_US2_0033F610(char *object, int flags)
{
    char *p = object + 8;
    float *v;
    prompt_bar_update_us2(p);
    v = *(float **)(object + 0x2D8);
    menu_set_anchor_pos(p, v[0], v[1]);
    return (flags >> 6) & 1;
}


void prompt_bar_draw(int);

void menu_draw_frame_us2(int param_1) {
  prompt_bar_draw(param_1 + 8);
}

extern int func_0033AB50_1(void *);
extern char *cam_init_object_table_c(void *);
extern char *cam_init_object_table_d(void *);
extern char *cam_init_object_table_a(void *);

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
char *frame_text_page_destroy_us2(char *object)
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





