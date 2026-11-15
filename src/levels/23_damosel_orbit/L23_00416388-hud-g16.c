#include "names.h"
/* Level 23 encounter HUD: three backing sprites, two EAA4 icons, the two ratio bars, the
 * EAA5 icon with its counter text and up to two counter icons, a pending prompt message and the
 * optional prompt panel. It is the one-sided counterpart of func_L22_003A5018 (levels 22 and
 * 23), whose layout and helpers it follows. Its 16-byte colour block D_L23_001B1770 is reached
 * through $gp, hence -G16 (with -g, which keeps the nop pairs before each div.s) in a unit of
 * its own.
 *
 * NOTE REVIEW: three sites use the accepted dead-test HUD idioms as written: label_y at the two
 * EAA4 icon y coordinates, and upstream's scaled_coord at the counter text y and at the panel's
 * box coordinate (the same func_002802E0 argument upstream rounds with it). Their tests leave no
 * instruction, but retail allocates and schedules those sites as if a block ended there. The
 * plain conversion and a one-pass group were measured at each site and do not match.
 */
#include "common.h"

typedef unsigned long long U64;
typedef union ColorView {
    U64 half[2];
    unsigned int word[4];
} ColorView;
typedef struct {
    char pad[0x18];
    int counter;
    int icons;
} HudCounters;

extern char *D_L23_001A904C;
extern char *g_mothership_boss_moby __attribute__((sda));
extern float D_L23_001B16D8 __attribute__((sda));
extern float D_L23_001B16D4 __attribute__((sda));
extern float D_L23_001B3004 MACRO_ADDR;
extern int D_L23_001B3000 MACRO_ADDR;
extern char g_hero_state[];
extern int g_screen_width MACRO_ADDR;
extern U64 D_L23_001B16E0 __attribute__((sda));
extern U64 D_L23_001B16E8 MACRO_ADDR;
extern U64 D_L23_001B16F0 __attribute__((sda));
extern U64 D_L23_001B16F8 MACRO_ADDR;
extern int D_L23_001B1770[4] __attribute__((sda));
extern char D_L23_001B1788[];
extern HudCounters D_L23_001B1F90;
extern int D_L23_001B374C MACRO_ADDR;
extern int D_L23_001B3750 MACRO_ADDR;
extern int D_L23_001B3754 MACRO_ADDR;
extern int D_L23_001B3748 __attribute__((sda));
extern int D_L23_001B1424 __attribute__((sda));
extern int D_L23_001B1700 __attribute__((sda));
extern int D_L23_001B1704 __attribute__((sda));
extern int D_L23_001B1708 __attribute__((sda));
extern int D_L23_001B170C __attribute__((sda));
extern int D_L23_001B1710 __attribute__((sda));
extern int D_L23_001B1714 __attribute__((sda));
extern int D_L23_001B1718 __attribute__((sda));
extern int D_L23_001B171C __attribute__((sda));
extern int D_L23_001B1720 __attribute__((sda));
extern int D_L23_001B1724 __attribute__((sda));
extern int D_L23_001B1728 __attribute__((sda));
extern int D_L23_001B172C __attribute__((sda));
extern int D_L23_001B1730 __attribute__((sda));
extern int D_L23_001B1734 __attribute__((sda));
extern int D_L23_001B1738 __attribute__((sda));
extern int D_L23_001B173C __attribute__((sda));
extern int D_L23_001B1740 __attribute__((sda));
extern int D_L23_001B1744 __attribute__((sda));
extern int D_L23_001B1748 __attribute__((sda));
extern int D_L23_001B174C __attribute__((sda));
extern int D_L23_001B1754 __attribute__((sda));
extern int D_L23_001B1758 __attribute__((sda));
extern int D_L23_001B175C __attribute__((sda));
extern int D_L23_001B1760 __attribute__((sda));
extern int D_L23_001B1764 __attribute__((sda));
extern int D_L23_001B1768 __attribute__((sda));
extern int D_L23_001B176C __attribute__((sda));
extern int D_L23_001B1780 __attribute__((sda));

extern int table_find_by_id(unsigned char *, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, int *);
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);
extern int text_draw_centered_medium(int, int, U64, unsigned char *, int);
extern int GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9(int, int);
extern void func_0029CC50(int, int, int);
extern int math_fast_float_d(void *);
extern void FontSetWindow(unsigned short *, int, int, int, int, int, int, int, int);
extern void level_forward_draw_args(int, int, int, int, int, int, int, int, int, int);
extern void module_l00_call_handler_2(void);

/* Screen-space y coordinates take an extra offset in display mode 1. */
static __inline__ int Y3(float y) {
    if (D_L23_001B3000 == 1)
        return (int)(y + 3.0f);
    return (int)y;
}
static __inline__ int Y1x(float y, int one, float unit) {
    if (D_L23_001B3000 == one)
        return (int)(y + unit);
    return (int)y;
}
static __inline__ int Coord(float value, float offset) {
    float scaled = value * D_L23_001B3004 + 0.5f;
    if (D_L23_001B3000 == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}

/* A coordinate scaled for the display and rounded to a whole pixel (upstream's scaled_coord,
   src/levels/02_maktar_nebula/L02_003FF6E8-g8.c, with this level's display-mode word). */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L23_001B3000;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* A text or sprite label's y, scaled for the display and rounded (the accepted label_y). */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L23_001B3000;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draw the encounter's meters, counters and optional prompt panel. */
int L23_DrawEncounterHud(void) {
    char textBuffer[64];
    char *text;
    ColorView color;
    unsigned short panel[16];
    char *state = *(char **)(g_mothership_boss_moby + 0x68);
    int x, y, right, width, width2;
    int one, one2;
    float half, half2, unit, round;
    float ratio, ratio2;
    HudCounters *hud;
    int label, hint;

    {
        int sprite = table_find_by_id((unsigned char *)D_L23_001A904C + 0x8710, 195);
        float sy = D_L23_001B16D8 * D_L23_001B3004 + 0.5f;
        sy = (float)Y3(sy);
        gfx_draw_scaled_object_two_axes((char *)sprite, 0x60442D00, D_L23_001B16D4, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        int sprite = table_find_by_id((unsigned char *)D_L23_001A904C + 0x8710, 196);
        float sy = D_L23_001B16D8 * D_L23_001B3004 + 0.5f;
        sy = (float)Y3(sy);
        gfx_draw_scaled_object_two_axes((char *)sprite, 0x60241700, D_L23_001B16D4, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        int sprite = table_find_by_id((unsigned char *)D_L23_001A904C + 0x8710, 197);
        float sy = D_L23_001B16D8 * D_L23_001B3004 + 0.5f;
        sy = (float)Y3(sy);
        unit = 1.0f;
        half = 0.5f;
        one = 1;
        gfx_draw_scaled_object_two_axes((char *)sprite, 0x55F0C070, D_L23_001B16D4, sy, unit, unit, 0.0f);
    }
    {
        int sprite = GetIconFrame(0xEAA4, one);
        int labelY = label_y((void *)sprite, (float)D_L23_001B1720, D_L23_001B3004, half, 1);
        hud_draw_sprite_gradient(sprite, D_L23_001B171C, labelY, D_L23_001B1724, D_L23_001B1728, D_L23_001B1770);
    }
    {
        int sprite = GetIconFrame(0xEAA4, 2);
        int labelY = label_y((void *)sprite, (float)D_L23_001B1730, D_L23_001B3004, half, 1);
        hud_draw_sprite_gradient(sprite, D_L23_001B172C, labelY, D_L23_001B1734, D_L23_001B1738, D_L23_001B1770);
    }
    ratio = (float)*(int *)(g_hero_state + 0x1874) / (float)*(short *)(state + 0x2F4);
    x = D_L23_001B1708 + D_L23_001B1700 + D_L23_001B1718;
    y = D_L23_001B170C + D_L23_001B1704 / 2 - D_L23_001B1710 / 2;
    width = D_L23_001B1714;
    color.half[0] = D_L23_001B16E0;
    color.half[1] = D_L23_001B16E8;
    color.word[1] = (color.word[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
    D_L23_001B1780++;
    gfx_draw_screen_rectangle(x, y, x + (int)(ratio * (float)width), y + D_L23_001B1710, 0xFFFFF1, &color);
    ratio2 = *(float *)(state + 0x20) / (float)*(short *)(state + 0x2F6);
    width2 = D_L23_001B1714;
    color.half[0] = D_L23_001B16F0;
    color.half[1] = D_L23_001B16F8;
    right = g_screen_width - D_L23_001B1708 - D_L23_001B1700 - 4;
    color.word[0] = (color.word[1] & 0xFFFF00FF) | ((int)(ratio2 * 255.0f) << 8);
    gfx_draw_screen_rectangle(right - (int)(ratio2 * (float)width2), y, right, y + D_L23_001B1710, 0xFFFFF1, &color);
    {
        int sprite = GetIconFrame(0xEAA5, 0);
        float sy = (float)D_L23_001B1740 * D_L23_001B3004 + half;
        hud_draw_sprite_gradient(sprite, D_L23_001B173C, Y1x(sy, one, unit), D_L23_001B1744, D_L23_001B1748, D_L23_001B1770);
    }
    one2 = 1;
    half2 = 0.5f;
    hud = &D_L23_001B1F90;
    sprintf(textBuffer, D_L23_001B1788, hud->counter);
    text = textBuffer;
    text_draw_centered_medium(D_L23_001B1754, scaled_coord(D_L23_001B1758, D_L23_001B3004, half2, 1),
                  D_L23_001B174C, (unsigned char *)text, func_001157AC(text));
    if (hud->icons) {
        int sprite = GetIconFrame(0xEAA5, one2);
        float sy = (float)D_L23_001B1760 * D_L23_001B3004 + half2;
        hud_draw_sprite_gradient(sprite, D_L23_001B175C, Y1x(sy, one2, 1.0f), D_L23_001B1764, D_L23_001B1768, D_L23_001B1770);
    }
    if (D_L23_001B1F90.icons >= 2) {
        int sprite = GetIconFrame(0xEAA5, 1);
        int x2 = D_L23_001B175C + D_L23_001B176C;
        hud_draw_sprite_gradient(sprite, x2, Coord((float)D_L23_001B1760, 1.0f), D_L23_001B1764, D_L23_001B1768, D_L23_001B1770);
    }
    if (D_L23_001B374C != -1 && D_L23_001B3748 == 0) {
        switch (D_L23_001B374C) {
        case 0:
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x2FA3), -1);
            break;
        case 2:
            GetLocalizedString(0x1241);
            func_0029CC50(0x1241, *(short *)(state + 0x2FC), -1);
            break;
        case 1:
            GetLocalizedString(0x1240);
            func_0029CC50(0x1240, D_L23_001B3750, -1);
            break;
        }
        D_L23_001B3754 = 0;
        math_fast_float_d(&D_L23_001B3754);
        if (D_L23_001B3754 <= 0)
            D_L23_001B374C = -1;
    }
    round = 0.5f;
    if (D_L23_001B1424) {
        FontSetWindow(panel, 240, 480, 44, 468, 256, scaled_coord(320, D_L23_001B3004, round, 1), 16, 3);
        label = GetLocalizedString(0x9FC);
        hint = GetLocalizedString(0x2F2C);
        level_forward_draw_args((int)panel, 0x80F0F0F0, label, 0, 0, -1, 0, hint, 0, 0);
    }
    module_l00_call_handler_2();
    return 1;
}
