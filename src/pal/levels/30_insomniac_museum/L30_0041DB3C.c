#include "include_asm.h"
#include "names.h"
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, void *, int, int, int);
extern char g_hero_position[];
extern long D_00138320;
extern int math_random_int_range(int, int);
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern int flag_set_first_pending(void *);
extern unsigned char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern unsigned char *D_L30_001FF940[];
extern char D_L30_001B2110[];
extern char D_L30_001B2120[];
extern char D_L30_001B2130[];
extern char D_L30_001B2140[];
extern char D_L30_001B2150[];
extern char D_L30_001B2158[];
extern char D_L30_001B2160[];
extern char D_L30_001B2168[];
extern char D_L30_001B2178[];
extern char D_L30_001B2188[];
extern char D_L30_001B2198[];
extern char D_L30_001B21A8[];
extern char D_L30_001B21B8[];
extern char D_L30_001B21C0[];
extern char D_L30_001B21D0[];
extern char D_L30_001B21E0[];
extern char D_L30_001B21F0[];
typedef struct { char pad[0x4c]; short minimum, maximum; } MuseumParticleBounds;

/* func_PAL_L30_0041DB3C, the PAL copy of func_L30_004186B0: the same C, where the third argument is scaled to 50 Hz
   and the colour is computed in a local before the call, so its first two loads come before the division. */
void func_PAL_L30_0041DB3C(char *obj) {
    char *st = *(char **)(obj + 0x68);
    MuseumParticleBounds *bounds = (MuseumParticleBounds *)st;
    unsigned char *particle;
    int color;

    switch ((unsigned char)obj[0x20]) {
    case 0:
        if (bounds->maximum < 0) bounds->maximum = 0;
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(st + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(st + 0x48) != -1 && IsPointInCuboid(g_hero_position, *(int *)(st + 0x48))) {
            ForceClaimNotice(1, 0x1338, 1);
            if ((D_00138320 & 3) == 3) moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(char **)(st + 0x3C) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x00, D_L30_001B2110, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x04, D_L30_001B2120, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x08, D_L30_001B2130, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x10, D_L30_001B2140, 0, 1, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x14, D_L30_001B2150, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x18, D_L30_001B2158, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x1C, D_L30_001B2160, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x20, D_L30_001B2168, 0, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x24, D_L30_001B2178, 0, 0, 127);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x28, D_L30_001B2188, 0, 0, 127);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x2C, D_L30_001B2198, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x30, D_L30_001B21A8, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x34, D_L30_001B21B8, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x40, D_L30_001B21C0, 0, 0, 103);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x44, D_L30_001B21D0, 0, 0, 20);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x4C, D_L30_001B21E0, 3, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(st + 0x3C), st + 0x4E, D_L30_001B21F0, 3, 0, 1000);
        }
        ForceClaimNotice(1, 0, 1);
        if (*(char **)(st + 0x3C) == 0
            || *(short *)(*(char **)(st + 0x3C) + 0xAA) != 0x118A
            || (unsigned char)(*(char **)(st + 0x3C))[0x20] == 0xFE
            || (unsigned char)(*(char **)(st + 0x3C))[0x20] == 0xFD) {
            moby_set_state(obj, 1, -1);
        }
        break;
    }

    if ((*(float *)(st + 0xC))-- == 0.0f) {
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(st + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        color = (*(int *)(st + 0x1C) << 16) | (*(int *)(st + 0x18) << 8) | *(int *)(st + 0x14);
        particle = part_spawn_gravity_fade(obj + 0x10, st, (*(int *)(st + 0x10) * 5 + 2) / 6,
                                 color,
                                 *(int *)(st + 0x20), *(int *)(st + 0x24), *(int *)(st + 0x28),
                                 *(float *)(st + 0x2C) * 210000.0f, *(float *)(st + 0x30) * 210000.0f,
                                 *(float *)(st + 0x34), *(int *)(st + 0x38));
        if (particle) {
            particle[9] = 0xFF;
            particle[2] = D_L30_001FF940[*(int *)(st + 0x40)][*(int *)(st + 0x44)];
        }
    }
}
