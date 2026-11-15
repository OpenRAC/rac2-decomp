#include "include_asm.h"
#include "names.h"
extern unsigned char D_001A7C1E __attribute__((sda));


extern void func_PAL_0033CF78(void *, char *, char *, char *);
extern void func_PAL_0033CD50(void *);
extern void menu_set_anchor_pos(void *, float, float);
extern int snd_play_from_global_bank(int, int, int);
extern unsigned char D_001A7BB2 __attribute__((sda));
extern char *GetLocalizedString(int);
extern void func_PAL_0033CE70(void *);
extern void gfx_reapply_display_layout(void);
extern void FontSetWindow(void *, int, int, int, int, int, int, int, int);
extern void text_draw_window_small(void *, unsigned long, char *, int);
extern short g_screen_adjust_offsets[];

extern int Ffb202470_FUN_0033AB50(char *p);

char *func_PAL_0033DC60(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}


/* func_PAL_0033DDC0, the PAL copy of func_0033BE98: the same C, with the three-string setup added. */
int func_PAL_0033DDC0(char *object, int mask)
{
    char *sub;
    char *text, *second;
    short oldx;
    short oldy;
    int *v;

    sub = object + 8;
    text = GetLocalizedString(0x1B73);
    second = GetLocalizedString(0xB5F);
    func_PAL_0033CF78(sub, text, second, GetLocalizedString(0xB60));
    func_PAL_0033CD50(sub);
    v = *(int **)(object + 0x2DC);
    menu_set_anchor_pos(sub, *(float *)v, *(float *)(v + 1));
    if ((mask & 0x40) != 0 && *(int *)(object + 0x2D8) == 0)
        snd_play_from_global_bank(4, 0, 0);
    if ((mask & 0xf000) != 0) {
        short *p = g_screen_adjust_offsets;
        oldx = p[180];
        oldy = p[181];
        if ((mask & 0x1000) != 0) {
            ((unsigned short *)p)[181] = ((unsigned short *)p)[181] - 1;
            if ((short)((unsigned short *)p)[181] < -32)
                p[181] = -32;
        }
        if ((mask & 0x4000) != 0) {
            unsigned short *q = (unsigned short *)g_screen_adjust_offsets;
            q[181] = q[181] + 1;
            if ((short)q[181] > 32)
                ((short *)q)[181] = 32;
        }
        if ((mask & 0x8000) != 0) {
            unsigned short *q = (unsigned short *)g_screen_adjust_offsets;
            q[180] = q[180] - 1;
            if ((short)q[180] < -40)
                ((short *)q)[180] = -40;
        }
        if ((mask & 0x2000) != 0) {
            unsigned short *q = (unsigned short *)g_screen_adjust_offsets;
            q[180] = q[180] + 1;
            if ((short)q[180] > 40)
                ((short *)q)[180] = 40;
        }
        {
            short *q = g_screen_adjust_offsets;
            if (oldx != q[180] || oldy != q[181])
                snd_play_from_global_bank(4, 0, 0);
        }
        gfx_reapply_display_layout();
    }
    return (mask >> 6) & 1;
}

/* func_PAL_0033DF90, the PAL copy of func_0033C028: only the box and its label remain. */
void func_PAL_0033DF90(char *object)
{
    char scratch[32];

    func_PAL_0033CE70(object + 8);
    FontSetWindow(scratch, 0x96, 0x167, 44, 468, 254, 180, 20, 3);
    text_draw_window_small(scratch, 0x80F0F0F0UL, GetLocalizedString(0x1B6E), -1);
}

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033E000(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

/* func_PAL_0033E160 is in 0033E160.c (-mno-split-addresses). */



/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033E300(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}





/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033E888(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



extern void Fc558ca70_FUN_0033AE28(char *p);
extern void Fc558ca70_FUN_0033B018(char *p, float a, float b);
extern int Fc558ca70_FUN_002E5E58(int a, int b, int c);
extern volatile unsigned char Fc558ca70_D_001A7B95 __attribute__((sda));
extern volatile unsigned char Fc558ca70_D_001A7B94 __attribute__((sda));

int func_PAL_0033E9E8(char *a0, int a1)
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



extern void *func_PAL_0033CA78(int);

char *func_PAL_0033EC50(char *object)
{
    extern void *object_construct_derived_b(void *);
    func_PAL_0033CA78((int)(object + 8));
    object_construct_derived_b(object + 0x2DC);
    object_construct_derived_b(object + 0x324);
    return object;
}




typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair D_L00_001AE1A8;
extern char D_L00_001AE1B0[];
extern void hud_draw_progress_bar(void *);
extern void text_draw_right_aligned_medium(int, int, unsigned long, char *, int);
extern int text_draw_centered_medium(int, int, unsigned long, char *, int);
extern char D_L00_001AE118[];
extern void func_PAL_0033CE70(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern SolTextPair D_L00_001AE110;
extern char D_L00_001AE118[];
extern void func_PAL_0033CE70(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);

/* func_0033D028 uses small data in 0033D028-g8.c. */

void func_PAL_0033F190(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *format, *first, *second;
    char *format2, *middle, *last;
    int color;
    func_PAL_0033CE70(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE1A8;
    format = D_L00_001AE1B0;
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
    format2 = D_L00_001AE118;
    last = GetLocalizedString(0xE36);
    second = GetLocalizedString(pair.ids[*(int *)0x1A7C20 != 0]);
    sprintf(buffer, format2, last, second);
    text_draw_centered_medium(0x100, 0xE1, color, buffer, -1);
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033F310(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



extern void F5979c03f_FUN_0033AE28 (char *object);
extern void F5979c03f_FUN_0033B018 (char *object, float x, float y);
extern int F5979c03f_FUN_002E5E58 (int a, int b, int c);

int func_PAL_0033F470 (char *object, int flags)
{
  unsigned char *g = &D_001A7C1E;
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

void func_PAL_0033F508(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    int color;
    func_PAL_0033CE70(object + 8);
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0xBAA);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x1A7C1E != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, color, buffer, -1);
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033F5D8(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}







/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033F9A0(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_PAL_0033FB00, the PAL copy of func_0033DC30: the same C, with the three-string setup added. */
int func_PAL_0033FB00(char *object, int flags)
{
    float *vec;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    func_PAL_0033CF78(child, text, second, GetLocalizedString(0xB60));
    func_PAL_0033CD50(child);
    vec = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int discarded = snd_play_from_global_bank(4, 0, 0);
        (void)discarded;
        D_001A7BB2 = (D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}


/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033FC98(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_PAL_0033FDF8, the PAL copy of func_0033DEE0: the same C, with the three-string setup added. */
int func_PAL_0033FDF8(char *object, int flags)
{
    float *vec;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    func_PAL_0033CF78(child, text, second, GetLocalizedString(0xB60));
    func_PAL_0033CD50(child);
    vec = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int discarded = snd_play_from_global_bank(4, 0, 0);
        (void)discarded;
        D_001A7BB2 = (D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


char *func_PAL_0033FED8(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



/* func_PAL_00340038, the PAL copy of func_0033E0D8: the same C, with the three-string setup added. */
int func_PAL_00340038(char *object, int flags)
{
    float *vec;
    char *child;
    char *text, *second;

    child = object + 8;
    text = GetLocalizedString(0xB72);
    second = GetLocalizedString(0xB5F);
    func_PAL_0033CF78(child, text, second, GetLocalizedString(0xB60));
    func_PAL_0033CD50(child);
    vec = *(float **)(object + 0x2DC);
    menu_set_anchor_pos(child, vec[0], vec[1]);

    if ((flags & 0x40) && *(int *)(object + 0x2D8) == 0) {
        int discarded = snd_play_from_global_bank(4, 0, 0);
        (void)discarded;
        D_001A7BB2 = (D_001A7BB2 < 1);
    }

    return (flags >> 6) & 1;
}



extern int func_PAL_003402F0(int);

int func_PAL_003402B8(int owner)
{
    int result;
    result = func_PAL_003402F0(owner);
    return *(int *)(owner + 0x3B8) + result * 0x14;
}




extern void *func_PAL_0034A148(char *, int);
extern void func_PAL_0034A2B8(char *, float, float);

/* func_PAL_00340348, the PAL copy of func_0033E3A0: the same C, with the three-string setup added and the second child moved. */
int func_PAL_00340348(char *object, int flags)
{
    char *first = object + 8;
    char *second;
    float *position;
    char *text, *label;

    text = GetLocalizedString(0xBB1);
    label = GetLocalizedString(0xB86);
    func_PAL_0033CF78(first, text, label, GetLocalizedString(0xB60));
    func_PAL_0033CD50(first);
    second = object + 0x2E0;
    position = *(float **)(object + 0x3BC);
    menu_set_anchor_pos(first, position[0], position[1]);
    func_PAL_0034A148(second, flags);
    func_PAL_0034A2B8(second, (*(float **)(object + 0x3BC))[0], (*(float **)(object + 0x3BC))[1]);
    return (flags >> 6) & 1;
}





void prompt_bar_draw(int);

void func_PAL_00340610(int param_1) {
  prompt_bar_draw(param_1 + 8);
}

extern int func_0033AB50_1(void *);
extern char *cam_init_object_table_c(void *);
extern char *cam_init_object_table_d(void *);
extern char *cam_init_object_table_a(void *);

/* Calls twelve sub-object handlers in sequence, each with the object base plus a fixed byte offset (8, 684, 744, 816, 888, 960, 1040, 1112, 1184, 1256, 1328, 1400), then returns the object pointer. */
char *func_PAL_00340630(char *object)
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







