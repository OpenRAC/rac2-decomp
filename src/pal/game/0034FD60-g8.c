#include "names.h"
/* func_PAL_0034FD60, the PAL copy of func_0034DB98: the same C, where panel100 grows by 0x10 and
   the padding after the text element by another 0x10, callee func_00336A78 becomes
   func_PAL_00338770 and func_0027F640 becomes func_PAL_0027FB48. PAL's languages change the
   thousands separator: language 4 also takes the dot, the dot's offsets are 11 and -35, and
   language 2 draws no separator at all. */

extern void gfx_draw_screen_element_stored(void *);
extern void hud_draw_colored_quad_widget(void *);
extern void text_label_draw_pal(void *);
extern float *object_get_second_field(void *);
extern float *object_get_first_field(void *);
extern unsigned int *object_get_fourth_field(void *);
extern void DrawSegmentedRingMeter(void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern void FontPrintScaled_pal(float, float, unsigned long, char *, int, float, unsigned long, unsigned char *);
extern int text_draw_centered_large(int, int, unsigned long, char *, int);
extern int sprintf(char *, char *, ...);
extern int g_notice_owner[] __attribute__((sda));
extern int g_player_bolts[] __attribute__((sda)); /* the player's bolts */
extern unsigned char g_language_settings[] __attribute__((sda));
extern unsigned char g_bolt_multiplier[] __attribute__((sda)); /* bolt multiplier */
extern char g_str_apostrophe[], g_str_period[], g_str_multiplier_format[]; /* "'", ".", "x%d" */
extern int g_movie_text_x __attribute__((sda));
extern int g_movie_text_y __attribute__((sda));
extern unsigned int g_mpeg_foreground_color __attribute__((sda));

/* A g++ 2.95 vtable entry: this-adjustment, index, function. */
typedef struct HudVEntry {
    short delta;
    short index;
    void (*fn)(void *);
} HudVEntry;

typedef struct HudElem4C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x18];
} HudElem4C;

typedef struct HudElem3C {
    char pad0[0x30];
    HudVEntry *vtable; /* 0x30 */
    char pad34[0x8];
} HudElem3C;

typedef struct HudText {
    char pad0[0x34];
    unsigned char *metrics; /* 0x34 */
    long long style;        /* 0x38 */
} HudText;

typedef struct HudOwner {
    HudElem4C top[3];       /* 0x0 */
    char pad0E4[0x1C];
    char panel100[0x58];    /* 0x100 */
    char panel148[0x3C];    /* 0x158 */
    HudElem4C mid[2];       /* 0x194 */
    char pad22C[0x1C];
    HudText text;           /* 0x248 */
    char pad288[0x2A0 - 0x248 - sizeof(HudText)];
    char panel2A0[0x40];    /* 0x2A0 */
    HudElem4C side[2];      /* 0x2E0 */
    HudElem4C a[8];         /* 0x378 */
    HudElem4C b;            /* 0x5D8 */
    HudElem3C c[8];         /* 0x624 */
    char pad804[4];
    char final[4];          /* 0x808 */
} HudOwner;

/* Draws the bolt counter panel: thousands separators by language (as RAC1's
 * bolt counter) and the "x%d" multiplier. The vtable pointers are read through
 * &a[i] + 0x30 so that every induction value is object-relative, and each
 * loop keeps its own vtable local, as in RAC2's DRAW idiom (00337210.c). */
void draw_bolt_counter_panel_pal(void *owner)
{
    HudOwner *object = owner;
    char separator[32];
    char multiplier_text[16];
    float *scale;
    float x, y, step;
    unsigned int color;
    int foreground, shadow;
    int i, j, digits, n, apostrophe, yoffset, xoffset;

    gfx_draw_screen_element_stored(&object->top[0]);
    gfx_draw_screen_element_stored(&object->top[1]);
    gfx_draw_screen_element_stored(&object->top[2]);
    hud_draw_colored_quad_widget(object->panel148);
    text_label_draw_pal(object->panel100);
    if (!g_notice_owner[0]) {
        HudElem4C *left = &object->side[0];
        HudElem4C *right = &object->side[1];
        gfx_draw_screen_element_stored(left);
        gfx_draw_screen_element_stored(right);
        { float *value = object_get_second_field(left); *value = -*value; }
        { float *value = object_get_second_field(right); *value = -*value; }
        gfx_draw_screen_element_stored(left);
        gfx_draw_screen_element_stored(right);
        { float *value = object_get_second_field(left); *value = -*value; }
        { float *value = object_get_second_field(right); *value = -*value; }
        for (i = 0; i < 8; i++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->a[i] + 0x30);
            vt[1].fn((char *)&object->a[i] + vt[1].delta);
        }
        for (j = 0; j < 8; j++) {
            HudVEntry *vt = *(HudVEntry **)((char *)&object->c[j] + 0x30);
            vt[1].fn((char *)&object->c[j] + vt[1].delta);
        }
        gfx_draw_screen_element_stored(&object->b);
        *object_get_fourth_field(&object->b) = 0x70FFFEED;
    }
    gfx_draw_screen_element_stored(&object->mid[0]);
    gfx_draw_screen_element_stored(&object->mid[1]);
    text_label_draw_pal(&object->text);
    hud_draw_colored_quad_widget(object->panel2A0);
    x = object_get_first_field(&object->text)[0];
    y = object_get_first_field(&object->text)[1];
    x += 32.0f;
    y += -10.0f;
    color = *object_get_fourth_field(&object->text);
    digits = 1;
    n = g_player_bolts[0];
    while (n >= 10) { n /= 10; digits++; }
    apostrophe = g_language_settings[4] != 3 && g_language_settings[4] != 5 && g_language_settings[4] != 4;
    sprintf(separator, apostrophe ? g_str_apostrophe : g_str_period);
    yoffset = apostrophe ? 21 : 11;
    xoffset = apostrophe ? -34 : -35;
    if (g_language_settings[4] != 2) {
        step = 3.0f;
        if (step < (float)digits) {
            float start = x + (float)xoffset;
            do {
                HudText *t = &object->text;
                float draw_x = start - (float)(int)(step * 11.6f);
                long long style;
                unsigned long texture;
                step += 3.0f;
                scale = object_get_second_field(t);
                style = t->style;
                texture = GetEffectTextureDescriptor((int)style);
                FontPrintScaled_pal(draw_x, y + (float)yoffset, color, separator, -1, *scale, texture, t->metrics);
            } while (step < (float)digits);
        }
    }
    if (g_bolt_multiplier[0] >= 2) {
        sprintf(multiplier_text, g_str_multiplier_format, g_bolt_multiplier[0]);
        foreground = (g_mpeg_foreground_color & 0xFFFFFF) | (color & 0xFF000000);
        shadow = color & 0xFF000000;
        text_draw_centered_large(g_movie_text_x, g_movie_text_y + 2, shadow, multiplier_text, -1);
        text_draw_centered_large(g_movie_text_x + 2, g_movie_text_y, shadow, multiplier_text, -1);
        text_draw_centered_large(g_movie_text_x + 2, g_movie_text_y + 2, shadow, multiplier_text, -1);
        text_draw_centered_large(g_movie_text_x, g_movie_text_y, foreground, multiplier_text, -1);
    }
    DrawSegmentedRingMeter(object->final);
}
