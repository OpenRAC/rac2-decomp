#include "include_asm.h"
#include "names.h"



extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, void *, int, int, int);
extern char g_hero_position[];
extern long D_00138320;
extern char D_L30_001B1E28[];
extern char D_L30_001B1E30[];
extern char D_L30_001B1E48[];
extern char D_L30_001B1E60[];
extern char D_L30_001B1E78[];
extern char D_L30_001B1E90[];
extern char D_L30_001B1EA0[];
extern char D_L30_001B1EA8[];
extern char D_L30_001B1EB0[];
extern char D_L30_001B1EB8[];
extern char D_L30_001B1ED0[];
extern char D_L30_001B1EE0[];
char *museum_explosion_spawn(void *, float, int, int, int, int, int, int, int, int, int, int);

/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


void func_US2_L30_00415710(char *obj) {
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
            buttons = D_00138320;
            buttons &= 3;
            if (buttons == 3) moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(char **)(st + 0x2C) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 4, D_L30_001B1E28, 1, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 12, D_L30_001B1E30, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 16, D_L30_001B1E48, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 20, D_L30_001B1E60, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 24, D_L30_001B1E78, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 28, D_L30_001B1E90, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 32, D_L30_001B1EA0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 36, D_L30_001B1EA8, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 40, D_L30_001B1EB0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 48, D_L30_001B1EB8, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 52, D_L30_001B1ED0, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(st + 0x2C), st + 8, D_L30_001B1EE0, 0, 0, 1);

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

