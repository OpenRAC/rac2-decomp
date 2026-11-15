#include "include_asm.h"
#include "names.h"
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern long D_00138320 __attribute__((nosda));
extern char g_hero_position[];
extern int flag_set_first_pending(void *);
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, char *, int, int, int);
extern unsigned int D_L30_001B1F28;
extern float D_L30_001B1F04;
extern int math_is_value_within_step(void *, float);
extern void moby_transform_joint_point(void *, int, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern void museum_projectile_spawn(void *, void *, void *, int, float);
extern void moby_mark_spawned(void *);
extern char D_L30_001B1C38[];
extern char D_L30_001B1C48[];
extern char D_L30_001B1C58[];
extern char D_L30_001B1C68[];
extern char D_L30_001B1C78[];
extern char D_L30_001B1C88[];
extern char D_L30_001B1C98[];
extern char D_L30_001B1CA8[];
extern char D_L30_001B1CB8[];
extern char D_L30_001B1CC8[];
extern char D_L30_001B1CD8[];
extern char D_L30_001B1CE8[];
extern char D_L30_001B1CF0[];
extern char D_L30_001B1D00[];
extern char D_L30_001B1D10[];
extern char D_L30_001B1D20[];
extern char D_L30_001B1D30[];
extern char D_L30_001B1D40[];
extern char D_L30_001B1D50[];
extern char D_L30_001B1D60[];
extern char D_L30_001B1D70[];
extern char D_L30_001B1D80[];
extern char D_L30_001B1D90[];
extern char D_L30_001B1DA0[];
extern char D_L30_001B1DB0[];
extern char D_L30_001B1DC0[];
extern char D_L30_001B1DD0[];
extern char D_L30_001B1DE0[];
extern char D_L30_001B1DF0[];
extern char D_L30_001B1E00[];
extern char D_L30_001B1E10[];
extern char D_L30_001B1E18[];
extern char D_L30_001B1E20[];
extern int D_L30_001B1F10[] __attribute__((sda));
extern int D_L30_001B1F14[] __attribute__((sda));
extern int D_L30_001B1F18[] __attribute__((sda));
extern int D_L30_001B1F1C[] __attribute__((sda));
extern int D_L30_001B1F20[] __attribute__((sda));
extern int D_L30_001B1F24[] __attribute__((sda));
extern int D_L30_001B1F2C[] __attribute__((sda));
extern int D_L30_001B1F30[] __attribute__((sda));
extern int D_L30_001B1F34[] __attribute__((sda));
extern int D_L30_001B1F38[] __attribute__((sda));
extern int D_L30_001B1F3C[] __attribute__((sda));
extern int D_L30_001B1F40[] __attribute__((sda));
extern int D_L30_001B1F44[] __attribute__((sda));
extern int D_L30_001B1F48[] __attribute__((sda));
extern int D_L30_001B1F54[] __attribute__((sda));
extern int D_L30_001B1F58[] __attribute__((sda));
extern int D_L30_001B1F5C[] __attribute__((sda));
extern int D_L30_001B1F64[] __attribute__((sda));
extern int D_L30_001B1F68[] __attribute__((sda));
extern int D_L30_001B1F6C[] __attribute__((sda));
extern int D_L30_001B1F74[] __attribute__((sda));
extern int D_L30_001B1F78[] __attribute__((sda));
extern int D_L30_001B1F7C[] __attribute__((sda));
extern int D_L30_001B1F84[] __attribute__((sda));
extern int D_L30_001B1F88[] __attribute__((sda));
extern int D_L30_001B1F8C[] __attribute__((sda));
extern int D_L30_001B1F94[] __attribute__((sda));
extern int D_L30_001B1F98[] __attribute__((sda));
extern int D_L30_001B1F9C[] __attribute__((sda));

/* Updates the projectile tester: opens one of two tuning menus on a button press, then fires a test projectile when the camera check passes. */
void museum_projectile_tester_update(char *moby) {
    float matrix[16];
    float velocity[4];
    char *vars = *(char **)(moby+0x68);
    unsigned int color;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        color = D_L30_001B1F28;
        *(int *)(vars+0x10) = color & 0xff;
        *(int *)(vars+0x14) = (int)(color & 0xff00) >> 8;
        *(int *)(vars+0x18) = (color >> 16) & 0xff;
        *(int *)(vars+0x1c) = (unsigned int)color >> 24;
        D_L30_001B1F04 = 5.0f;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if (*(int *)(vars+4) != -1 && IsPointInCuboid(g_hero_position,*(int *)(vars+4))) {
            ForceClaimNotice(1,0x27e6,1);
            { long buttons = D_00138320;
              if ((buttons & 3) == 3) moby_set_state(moby,2,-1); }
        }
        if (*(int *)(vars+8) != -1 && IsPointInCuboid(g_hero_position,*(int *)(vars+8))) {
            ForceClaimNotice(1,0x27f1,1);
            { long buttons = D_00138320;
              if ((buttons & 3) == 3) moby_set_state(moby,3,-1); }
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            *(char **)(vars+0xc) = museum_tweak_menu_spawn(moby);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F10, D_L30_001B1C38, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F14, D_L30_001B1C48, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F18, D_L30_001B1C58, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F1C, D_L30_001B1C68, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F24, D_L30_001B1C78, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F38, D_L30_001B1C88, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F3C, D_L30_001B1C98, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F40, D_L30_001B1CA8, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F20, D_L30_001B1CB8, 0, 0, 60);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F44, D_L30_001B1CC8, 0, 0, 60);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F48, D_L30_001B1CD8, 0, 0, 60);
        }
        ForceClaimNotice(1,0,1);
        if (!*(char **)(vars+0xc) || *(short *)(*(char **)(vars+0xc)+0xaa) != 0x118a /* moby class 4490 */  || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfd)
            moby_set_state(moby,1,-1);
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            *(char **)(vars+0xc) = museum_tweak_menu_spawn(moby);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x10, D_L30_001B1CE8, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x14, D_L30_001B1CF0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x18, D_L30_001B1D00, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), vars+0x1c, D_L30_001B1D10, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F30, D_L30_001B1D20, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F2C, D_L30_001B1D30, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F34, D_L30_001B1D40, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F54, D_L30_001B1D50, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F64, D_L30_001B1D60, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F58, D_L30_001B1D70, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F68, D_L30_001B1D80, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F5C, D_L30_001B1D90, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F6C, D_L30_001B1DA0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F74, D_L30_001B1DB0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F84, D_L30_001B1DC0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F78, D_L30_001B1DD0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F88, D_L30_001B1DE0, 0, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F7C, D_L30_001B1DF0, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F8C, D_L30_001B1E00, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F94, D_L30_001B1E10, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F98, D_L30_001B1E18, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars+0xc), D_L30_001B1F9C, D_L30_001B1E20, 0, 0, 255);
        }
        ForceClaimNotice(1,0,1);
        if (!*(char **)(vars+0xc) || *(short *)(*(char **)(vars+0xc)+0xaa) != 0x118a /* moby class 4490 */  || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfe || (unsigned char)(*(char **)(vars+0xc))[0x20] == 0xfd)
            moby_set_state(moby,1,-1);
        break;
    }
    {
        unsigned int packed;
        packed = *(int *)(vars+0x1c) << 24;
        packed |= *(int *)(vars+0x18) << 16;
        packed |= *(int *)(vars+0x14) << 8;
        packed |= *(int *)(vars+0x1c);
        D_L30_001B1F28 = packed;
    }
    if (math_is_value_within_step(moby,1.0f)) {
        moby_transform_joint_point(moby,0,matrix);
        velocity[0] = math_fast_sin_or_cos_a(*(float *)(moby+0xf8));
        velocity[1] = math_fast_sin_or_cos_b(*(float *)(moby+0xf8));
        velocity[2] = 0;
        vec_scale_to_length(velocity,velocity,0.583333373f);
        if (*(int *)vars) {
            museum_projectile_spawn(moby,velocity,matrix+12,1,0.0f);
            moby_mark_spawned(moby);
        } else museum_projectile_spawn(moby,velocity,matrix+12,0,0.0f);
    }
}
