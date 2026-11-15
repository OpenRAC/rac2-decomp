#include "include_asm.h"
#include "names.h"
extern int D_L30_001B2A68 __attribute__((sda));
extern short D_0018A000;
extern unsigned long long g_pad_state[];
extern unsigned char D_L30_001B3D30[];
extern void *D_L30_00260E30[];
extern int D_L30_00260F30[][2];
extern void func_2EDB20(void *, void *);
extern void func_323FB0(void *, int, int);
extern void museum_tweak_menu_draw(char *);
extern int func_326868(void *, int);
extern int func_32B1B0(int, int, int);
extern void func_320FD0(void *, int, int);
extern int func_32C070(void *);
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

extern void VU1_addGSregister(int, int);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } g_screen_adjust_offsets;
extern void gfx_l05_draw_jittered_billboard_quad(void *, int, float, float, float, float, float, int);

extern void func_42C028(int);
extern void func_316DB8(char *);
extern int D_0018C0E8;

/* Restores a saved setting and removes the helper object this object created. */
void museum_effect_object_release(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    func_42C028(3);
    D_0018C0E8 = *(int *)(vars + 0x5C);
    func_316DB8(*(char **)(vars + 0x50));
}


/* Updates the tuning menu: draws it, moves the cursor, and changes the chosen value with left and right. */
void museum_tweak_menu_update(char *moby) {
    int *vars = *(int **)(moby + 0x68);
    int step = 0;
    D_L30_001B2A68 = 1;
    D_0018A000 = 5;
    func_2EDB20(museum_tweak_menu_draw, moby);
    if (g_pad_state[0x1A0 / 8] & 0x9000000000ULL) {
        func_316DB8(moby);
        return;
    }
    if (((int *)g_pad_state)[0x1A4 / 4] & 0x4000) {
        func_323FB0(vars, vars[1] - 1, 1);
        if (vars[2] < vars[0] - 15) vars[2]++;
    } else if (((int *)g_pad_state)[0x1A4 / 4] & 0x1000) {
        func_323FB0(vars, 0, 1);
        if (vars[0] < vars[2]) vars[2]--;
    } else if (((int *)g_pad_state)[0x1A0 / 4] & 0x2000) {
        step = (((int *)g_pad_state)[0x1A0 / 4] & 15) ? 5 : 1;
    } else if (((int *)g_pad_state)[0x1A0 / 4] & 0x8000) {
        step = (((int *)g_pad_state)[0x1A0 / 4] & 15) ? -5 : -1;
    }
    if (step && *(unsigned short *)(moby + 0x96) >= 5) {
        *(unsigned short *)(moby + 0x96) = 0;
        switch (D_L30_001B3D30[vars[0]]) {
        case 0: {
            int value = *(int *)D_L30_00260E30[vars[0]];
            value += step;
            if (value > D_L30_00260F30[vars[0]][1]) value = D_L30_00260F30[vars[0]][1];
            else if (value < D_L30_00260F30[vars[0]][0]) value = D_L30_00260F30[vars[0]][0];
            *(int *)D_L30_00260E30[vars[0]] = value;
            break;
        }
        case 1: {
            float value = *(float *)D_L30_00260E30[vars[0]] + step * 0.01f;
            if (value > D_L30_00260F30[vars[0]][1]) value = D_L30_00260F30[vars[0]][1];
            else if (value < D_L30_00260F30[vars[0]][0]) value = D_L30_00260F30[vars[0]][0];
            *(float *)D_L30_00260E30[vars[0]] = value;
            break;
        }
        case 2: {
            unsigned char value = *(unsigned char *)D_L30_00260E30[vars[0]];
            value += step;
            if (value > D_L30_00260F30[vars[0]][1]) value = D_L30_00260F30[vars[0]][1];
            else if (value < D_L30_00260F30[vars[0]][0]) value = D_L30_00260F30[vars[0]][0];
            *(unsigned char *)D_L30_00260E30[vars[0]] = value;
            break;
        }
        case 3: {
            short value = *(short *)D_L30_00260E30[vars[0]];
            value += step;
            if (value > D_L30_00260F30[vars[0]][1]) value = D_L30_00260F30[vars[0]][1];
            else if (value < D_L30_00260F30[vars[0]][0]) value = D_L30_00260F30[vars[0]][0];
            *(short *)D_L30_00260E30[vars[0]] = value;
            break;
        }
        }
    }
    (*(unsigned short *)(moby + 0x96))++;
}


/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


/* Updates the explosion tester: opens the tuning menu on a button press and spawns a test explosion every 45 frames. */
void UpdateMuseumExplosionTester(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *menu;
    long buttons;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(moby + 0x1C) = 0;
        func_320FD0(moby, 1, -1);
        break;
    case 1:
        if (*(int *)(vars + 0x3C) != -1 && func_326868(g_hero_position, *(int *)(vars + 0x3C))) {
            func_32B1B0(1, 0x27E6, 1);
            buttons = D_00138320;
            buttons &= 3;
            if (buttons == 3) func_320FD0(moby, 2, -1);
        }
        break;
    case 2:
        if (func_32C070(moby)) {
            *(char **)(vars + 0x2C) = museum_tweak_menu_spawn(moby);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 4, D_L30_001B1E28, 1, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 12, D_L30_001B1E30, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 16, D_L30_001B1E48, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 20, D_L30_001B1E60, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 24, D_L30_001B1E78, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 28, D_L30_001B1E90, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 32, D_L30_001B1EA0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 36, D_L30_001B1EA8, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 40, D_L30_001B1EB0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 48, D_L30_001B1EB8, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 52, D_L30_001B1ED0, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 8, D_L30_001B1EE0, 0, 0, 1);

        }
        func_32B1B0(1, 0, 1);
        menu = *(char **)(vars + 0x2C);
        if (!menu || *(short *)(menu + 0xAA) != 0x118A /* moby class 4490 */ || *(unsigned char *)(menu + 0x20) == 0xFE || *(unsigned char *)(menu + 0x20) == 0xFD) {
            func_320FD0(moby, 1, -1);
        }
        break;
    }
    if (*(float *)(moby + 0x1C) >= 45.0f) {
        int color;
        *(int *)(moby + 0x1C) = 0;
        color = (*(int *)(vars + 40) << 16) | (*(int *)(vars + 36) << 8) | *(int *)(vars + 32);
        *(char **)vars = museum_explosion_spawn(moby + 0x10, *(float *)(vars + 4), *(int *)(vars + 8), *(int *)(vars + 12), *(int *)(vars + 16), *(int *)(vars + 20), *(int *)(vars + 24), *(int *)(vars + 28), *(int *)(vars + 48), *(int *)(vars + 52), *(int *)(vars + 56), color);
    }
    *(float *)(moby + 0x1C) += 1.0f;
}

/* func_L30_004153D8 is defined in L30_004153D8.c. */

/* func_L30_004158B0 is defined in L30_004158B0-g8.c. */

/* func_L30_00416A88 is defined in L30_00416A88-g8.c. */

/* func_L30_00416D88 is defined in L30_00416D88-g8.c. */

/* func_L30_00417988 is defined in L30_00417988-g8.c. */

typedef unsigned short u16;

extern char *func_316A50(int);
extern void func_32BFF0(void *, void *);
extern void func_2F56B0(void *, void *);

/* Creates a helper effect object linked to this one and stores it in this object's variables. */
void museum_effect_object_spawn(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *spawned;

    spawned = func_316A50(0xB28 /* moby class 2856 */);
    if (spawned == 0) return;
    func_32BFF0(spawned, moby);
    func_2F56B0(spawned + 0xC0, spawned + 0xF0);
    *(u16 *)(spawned + 0x34) |= 0x100;
    *(char **)(vars + 0x50) = spawned;
}


/* Updates the particle tester: opens the tuning menu on a button press and emits a test particle at random intervals. */
void UpdateMuseumParticleTester(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    MuseumParticleBounds *bounds = (MuseumParticleBounds *)vars;
    unsigned char *particle;

    switch ((unsigned char)moby[0x20]) {
    case 0:
        if (bounds->maximum < 0) bounds->maximum = 0;
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(vars + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (*(int *)(vars + 0x48) != -1 && IsPointInCuboid(g_hero_position, *(int *)(vars + 0x48))) {
            ForceClaimNotice(1, 0x27E6, 1);
            if ((D_00138320 & 3) == 3) moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            *(char **)(vars + 0x3C) = museum_tweak_menu_spawn(moby);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x00, D_L30_001B2110, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x04, D_L30_001B2120, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x08, D_L30_001B2130, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x10, D_L30_001B2140, 0, 1, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x14, D_L30_001B2150, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x18, D_L30_001B2158, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x1C, D_L30_001B2160, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x20, D_L30_001B2168, 0, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x24, D_L30_001B2178, 0, 0, 127);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x28, D_L30_001B2188, 0, 0, 127);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x2C, D_L30_001B2198, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x30, D_L30_001B21A8, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x34, D_L30_001B21B8, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x40, D_L30_001B21C0, 0, 0, 103);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x44, D_L30_001B21D0, 0, 0, 20);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x4C, D_L30_001B21E0, 3, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x4E, D_L30_001B21F0, 3, 0, 1000);
        }
        ForceClaimNotice(1, 0, 1);
        if (*(char **)(vars + 0x3C) == 0
            || *(short *)(*(char **)(vars + 0x3C) + 0xAA) != 0x118A /* moby class 4490 */
            || (unsigned char)(*(char **)(vars + 0x3C))[0x20] == 0xFE
            || (unsigned char)(*(char **)(vars + 0x3C))[0x20] == 0xFD) {
            moby_set_state(moby, 1, -1);
        }
        break;
    }

    if ((*(float *)(vars + 0xC))-- == 0.0f) {
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(vars + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        particle = part_spawn_gravity_fade(moby + 0x10, vars, *(int *)(vars + 0x10),
                                 (*(int *)(vars + 0x1C) << 16) | (*(int *)(vars + 0x18) << 8) | *(int *)(vars + 0x14),
                                 *(int *)(vars + 0x20), *(int *)(vars + 0x24), *(int *)(vars + 0x28),
                                 *(float *)(vars + 0x2C) * 210000.0f, *(float *)(vars + 0x30) * 210000.0f,
                                 *(float *)(vars + 0x34), *(int *)(vars + 0x38));
        if (particle) {
            particle[9] = 0xFF;
            particle[2] = D_L30_001FF940[*(int *)(vars + 0x40)][*(int *)(vars + 0x44)];
        }
    }
}

/* Draws a screen flash and fades a light near the end of a countdown. */
void museum_draw_countdown_effect(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    if (*(short *)(vars + 2) - *(short *)vars < 2 && *(short *)(vars + 4)) {
        if (*(int *)(vars + 0x1C)) {
            VU1_addGSregister(0x42, 0x48);
            gfx_draw_colored_rectangle(0, g_screen_adjust_offsets.y, 0, g_screen_adjust_offsets.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(vars + 0x18)) {
        if (*(short *)(vars + 2) - *(short *)vars < 10) {
            float blend = (*(short *)(vars + 2) - *(short *)vars) * 0.1f;
            gfx_l05_draw_jittered_billboard_quad(moby + 0x10, 0x3C, *(float *)(vars + 8) + (*(float *)(vars + 12) - *(float *)(vars + 8)) * blend, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)vars - 0x2E) < 4) {
            float blend = (*(short *)vars - 0x2D) * 0.1f;
            gfx_l05_draw_jittered_billboard_quad(moby + 0x10, 0x3C, *(float *)(vars + 8) + (*(float *)(vars + 12) - *(float *)(vars + 8)) * blend, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

extern int func_2F4B08(char *);
extern void func_2EDD78(void *, char *);
extern void screen_flash_and_glow_draw(char *);

/* Runs the next step once the first check passes, otherwise removes this object. */
void museum_run_follow_up_step(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (func_2F4B08(vars) == 0) {
        func_2F4B08(vars + 4);
        func_2EDD78((void *)screen_flash_and_glow_draw, moby);
    } else {
        func_316DB8(moby);
    }
}

/* func_L30_0041B848 is defined in L30_0041B848.c. */
