#include "include_asm.h"
#include "names.h"



extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, void *, int, int, int);
extern char g_hero_position[];
extern long g_pad_pressed_flags;
extern char g_str_tweak_toggle_label[];
extern char g_str_tweak_value_label_a[];
extern char g_str_tweak_value_label_b[];
extern char g_str_tweak_value_label_c[];
extern char g_str_tweak_value_label_d[];
extern char g_str_tweak_value_label_e[];
extern char g_str_tweak_color_label_a[];
extern char g_str_tweak_color_label_b[];
extern char g_str_tweak_color_label_c[];
extern char g_str_tweak_flag_label_a[];
extern char g_str_tweak_flag_label_b[];
extern char g_str_tweak_flag_label_c[];
char *museum_explosion_spawn(void *, float, int, int, int, int, int, int, int, int, int, int);

/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


void UpdateMuseumExplosionTester_us2(char *obj) {
    char *st = *(char **)(obj + 0x68);
    char *menu;
    long buttons;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(obj + 0x1C) = 0;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(st + 0x3C) != -1 && IsPointInCuboid(g_hero_position, *(int *)(st + 0x3C))) {
            ForceClaimNotice(1, 0x1338, 1);
            buttons = g_pad_pressed_flags;
            buttons &= 3;
            if (buttons == 3) moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(char **)(st + 0x2C) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 4, g_str_tweak_toggle_label, 1, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 12, g_str_tweak_value_label_a, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 16, g_str_tweak_value_label_b, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 20, g_str_tweak_value_label_c, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 24, g_str_tweak_value_label_d, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 28, g_str_tweak_value_label_e, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 32, g_str_tweak_color_label_a, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 36, g_str_tweak_color_label_b, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 40, g_str_tweak_color_label_c, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 48, g_str_tweak_flag_label_a, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 52, g_str_tweak_flag_label_b, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 8, g_str_tweak_flag_label_c, 0, 0, 1);

        }
        ForceClaimNotice(1, 0, 1);
        menu = *(char **)(st + 0x2C);
        if (!menu || *(short *)(menu + 0xAA) != 0x118A || *(unsigned char *)(menu + 0x20) == 0xFE || *(unsigned char *)(menu + 0x20) == 0xFD) {
            moby_set_state(obj, 1, -1);
        }
        break;
    }
    if (*(float *)(obj + 0x1C) >= 45.0f) {
        int color;
        *(int *)(obj + 0x1C) = 0;
        color = (*(int *)(st + 40) << 16) | (*(int *)(st + 36) << 8) | *(int *)(st + 32);
        *(char **)st = museum_explosion_spawn(obj + 0x10, *(float *)(st + 4), *(int *)(st + 8), *(int *)(st + 12), *(int *)(st + 16), *(int *)(st + 20), *(int *)(st + 24), *(int *)(st + 28), *(int *)(st + 48), *(int *)(st + 52), *(int *)(st + 56), color);
    }
    *(float *)(obj + 0x1C) += 1.0f;
}

