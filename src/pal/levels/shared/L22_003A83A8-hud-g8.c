#include "names.h"
/* func_PAL_L22_003A83A8 (3,008 bytes, levels 22 and 23): the PAL copy of the HUD counters panel,
 * func_L22_003A5018 in v1.01 (src/levels/shared/L22_003A5018-hud-g8.c), with the same C and flags
 * (-O2 -G8 -ffunction-sections -g -frac2-sched-global-yield, config/cflags.txt). Only the two text
 * ids change: 0x2FA3 and 0x2F2C become 0xEC8 and 0xE51.
 */
#include "common.h"

extern u8 * D_L22_001A904C MACRO_ADDR;
extern int D_L22_001B2980 MACRO_ADDR;
extern float D_L22_001B2984 MACRO_ADDR;
extern int D_0018B694 NOT_SDA;
extern int D_L22_001B2AA8 MACRO_ADDR;
extern int g_screen_width MACRO_ADDR;
typedef struct HudCounters {
    int unknown[2];
    int rightCount;
    int rightIcons;
    int unknown10[2];
    int leftCount;
    int leftIcons;
} HudCounters;
extern HudCounters D_L22_001B1910 NOT_SDA;
extern char D_L22_001AF4D8[] NOT_SDA;
extern int D_L22_001B2AC8 MACRO_ADDR;
extern int D_L22_001B2ACC MACRO_ADDR;
extern int D_L22_001B2AD0 MACRO_ADDR;
extern u64 D_L22_001AF418 MACRO_ADDR;
extern u64 D_L22_001AF428 MACRO_ADDR;
extern u8 *ref_L22_003A5018_00 __attribute__((sda));
extern float ref_L22_003A5018_01 __attribute__((sda)), ref_L22_003A5018_02 __attribute__((sda));
extern u64 ref_L22_003A5018_03 __attribute__((sda)), ref_L22_003A5018_04 __attribute__((sda));
extern int ref_L22_003A5018_05 __attribute__((sda));
extern float ref_L22_003A5018_06 __attribute__((sda));
extern int ref_L22_003A5018_07 __attribute__((sda));
extern int ref_L22_003A5018_08 __attribute__((sda));
extern int ref_L22_003A5018_09 __attribute__((sda));
extern int ref_L22_003A5018_10 __attribute__((sda));
extern int ref_L22_003A5018_11 __attribute__((sda));
extern int ref_L22_003A5018_12 __attribute__((sda));
extern int ref_L22_003A5018_13 __attribute__((sda));
extern int ref_L22_003A5018_14 __attribute__((sda));
extern int ref_L22_003A5018_15 __attribute__((sda));
extern int ref_L22_003A5018_16 __attribute__((sda));
extern int ref_L22_003A5018_17 __attribute__((sda));
extern int ref_L22_003A5018_18 __attribute__((sda));
extern int ref_L22_003A5018_19 __attribute__((sda));
extern int ref_L22_003A5018_20 __attribute__((sda));
extern int ref_L22_003A5018_21 __attribute__((sda));
extern int ref_L22_003A5018_22 __attribute__((sda));
extern int ref_L22_003A5018_23 __attribute__((sda));
extern int ref_L22_003A5018_24 __attribute__((sda));
extern int ref_L22_003A5018_25 __attribute__((sda));
extern int ref_L22_003A5018_26 __attribute__((sda));
extern int ref_L22_003A5018_27 __attribute__((sda));
extern int ref_L22_003A5018_28 __attribute__((sda));
extern int ref_L22_003A5018_29 __attribute__((sda));
extern int ref_L22_003A5018_30 __attribute__((sda));
extern int ref_L22_003A5018_31 __attribute__((sda));
extern int ref_L22_003A5018_32 __attribute__((sda));
extern int ref_L22_003A5018_33 __attribute__((sda));
extern int ref_L22_003A5018_34 __attribute__((sda));
extern int ref_L22_003A5018_35 __attribute__((sda));
extern int ref_L22_003A5018_36 __attribute__((sda));
extern int ref_L22_003A5018_37 __attribute__((sda));
extern int ref_L22_003A5018_38 __attribute__((sda));
extern int ref_L22_003A5018_39 __attribute__((sda));
extern int ref_L22_003A5018_40 __attribute__((sda));
extern int ref_L22_003A5018_41 __attribute__((sda));
extern u8 ref_L22_003A5018_42[] SDATA(ref_L22_003A5018_42);
extern int ref_L22_003A5018_43 __attribute__((sda));
extern int ref_L22_003A5018_44 __attribute__((sda));

extern int table_find_by_id(void *, int);
extern void gfx_draw_scaled_object_two_axes(void *, unsigned int, float, float, float, float, float);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(void *, int, int, int, int, void *);
extern void gfx_draw_screen_rectangle(int, int, int, int, int, void *);
extern int sprintf(char *, char *, ...);
extern int func_001157AC(char *);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9(int, int);
extern void func_0029CC50(int, int, int);
extern int math_fast_float_d(void *);
extern void FontSetWindow(void *, int, int, int, int, int, int, int, int);
extern void level_forward_draw_args(void *, unsigned int, char *, int, int, int, int, char *, int, int);
extern void module_l00_call_handler_2(void);

extern int D_L22_001B2980;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L22_001B2980;
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

static __inline__ int screen_coord(int mode, float value, float offset)
{
    float scaled = value * D_L22_001B2984 + 0.5f;

    if (mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_PAL_L22_003A83A8(void) {
    char textBuffer[64];
    char *text;
    union { u64 d[2]; u32 w[4]; } colours;
    u8 box[32];
    u8 *obj = ref_L22_003A5018_00;
    u8 *ctl = *(u8 **)(obj + 0x68);
    int y;
    int one, one2;
    int colour;
    char *label, *hint;

    {
        void *sprite = (void *)(u32)table_find_by_id(D_L22_001A904C + 0x8710, 0xC3);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)table_find_by_id(D_L22_001A904C + 0x8710, 0xC4);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        gfx_draw_scaled_object_two_axes(sprite, 0x60241700, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)table_find_by_id(D_L22_001A904C + 0x8710, 0xC5);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, ref_L22_003A5018_01, sy, 1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)table_find_by_id(D_L22_001A904C + 0x8710, 0xC3);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        gfx_draw_scaled_object_two_axes(sprite, 0x60442D00, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)table_find_by_id(D_L22_001A904C + 0x8710, 0xC4);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        gfx_draw_scaled_object_two_axes(sprite, 0x60241700, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    {
        void *sprite = (void *)(u32)table_find_by_id(D_L22_001A904C + 0x8710, 0xC5);
        float sy = (float)screen_coord(D_L22_001B2980, ref_L22_003A5018_02, 3.0f);
        gfx_draw_scaled_object_two_axes(sprite, 0x55F0C070, ref_L22_003A5018_01, sy, -1.0f, 1.0f, 0.0f);
    }
    one = 1;
    { void *sprite = (void *)(u32)GetIconFrame(0xEAA4, one);
    hud_draw_sprite_gradient(sprite, ref_L22_003A5018_14, label_y(sprite, (float)ref_L22_003A5018_15, D_L22_001B2984, 0.5f, 1), ref_L22_003A5018_16, ref_L22_003A5018_17, ref_L22_003A5018_42); }
    { void *sprite = (void *)(u32)GetIconFrame(0xEAA4, 0);
    hud_draw_sprite_gradient(sprite, ref_L22_003A5018_18, label_y(sprite, (float)ref_L22_003A5018_19, D_L22_001B2984, 0.5f, 1), ref_L22_003A5018_20, ref_L22_003A5018_21, ref_L22_003A5018_42); }

    {
        float ratio = (float)D_0018B694 / (float)*(short *)(ctl + 0x324);
        int x, width;
        colours.d[0] = ref_L22_003A5018_03;
        width = ref_L22_003A5018_12;
        x = ref_L22_003A5018_09 + ref_L22_003A5018_07 + ref_L22_003A5018_13;
        y = ref_L22_003A5018_10 + ref_L22_003A5018_08 / 2 - ref_L22_003A5018_11 / 2;
        ref_L22_003A5018_43++;
        colours.d[1] = D_L22_001AF418;
        colours.w[1] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        gfx_draw_screen_rectangle(x, y, x + (int)(ratio * (float)width), y + ref_L22_003A5018_11, 0xFFFFF1, &colours);
    }
    {
        float ratio = *(float *)(ctl + 0x20) / (float)D_L22_001B2AA8;
        int right, width, height;
        colours.d[0] = ref_L22_003A5018_04;
        width = ref_L22_003A5018_12;
        right = g_screen_width - ref_L22_003A5018_09 - ref_L22_003A5018_07 - 4;
        colours.w[0] = (colours.w[1] & 0xFFFF00FF) | ((int)(ratio * 255.0f) << 8);
        height = ref_L22_003A5018_11;
        colours.d[1] = D_L22_001AF428;
        gfx_draw_screen_rectangle(right - (int)(ratio * (float)width), y, right, y + height, 0xFFFFF1, &colours);
    }

    {
        void *sprite = (void *)(u32)GetIconFrame(0xEAA5, 0);
        hud_draw_sprite_gradient(sprite, ref_L22_003A5018_22, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_23, 1.0f), ref_L22_003A5018_24, ref_L22_003A5018_25, ref_L22_003A5018_42);
    }
    {
        void *sprite = (void *)(u32)GetIconFrame(0xEAA5, 0);
        hud_draw_sprite_gradient(sprite, ref_L22_003A5018_26, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_27, 1.0f), ref_L22_003A5018_28, ref_L22_003A5018_29, ref_L22_003A5018_42);
    }
    one2 = 1;
    sprintf(textBuffer, D_L22_001AF4D8, D_L22_001B1910.leftCount);
    text = textBuffer;
    {
    int value = label_y(obj, (float)ref_L22_003A5018_33, D_L22_001B2984, 0.5f, 1);
    colour = ref_L22_003A5018_30;
    text_draw_centered_medium(ref_L22_003A5018_32, value, colour, text, func_001157AC(text));
    }
    sprintf(text, D_L22_001AF4D8, D_L22_001B1910.rightCount);
    {
    int value = label_y((void *)colour, (float)ref_L22_003A5018_35, D_L22_001B2984, 0.5f, 1);
    colour = ref_L22_003A5018_30;
    text_draw_centered_medium(ref_L22_003A5018_34, value, colour, text, func_001157AC(text));
    }
    if (D_L22_001B1910.leftIcons) {
        void *sprite = (void *)(u32)GetIconFrame(0xEAA5, one2);
        hud_draw_sprite_gradient(sprite, ref_L22_003A5018_36, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_37, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.leftIcons >= 2) {
        void *sprite = (void *)(u32)GetIconFrame(0xEAA5, 1);
        int x = ref_L22_003A5018_36 + ref_L22_003A5018_44;
        hud_draw_sprite_gradient(sprite, x, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_37, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.rightIcons) {
        void *sprite = (void *)(u32)GetIconFrame(0xEAA5, 1);
        hud_draw_sprite_gradient(sprite, ref_L22_003A5018_38, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_39, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B1910.rightIcons >= 2) {
        void *sprite = (void *)(u32)GetIconFrame(0xEAA5, 1);
        int x = ref_L22_003A5018_38 - ref_L22_003A5018_44;
        hud_draw_sprite_gradient(sprite, x, screen_coord(D_L22_001B2980, (float)ref_L22_003A5018_39, 1.0f), ref_L22_003A5018_40, ref_L22_003A5018_41, ref_L22_003A5018_42);
    }
    if (D_L22_001B2AC8 != -1 && obj[0x95] != 10) {
        switch (D_L22_001B2AC8) {
        case 0: level_l00_call_module_handler_with_arg_9((int)GetLocalizedString(0xEC8), -1); break;
        case 2: GetLocalizedString(0x1241); func_0029CC50(0x1241, *(short *)(ctl + 0x32C), -1); break;
        case 1: GetLocalizedString(0x1240); func_0029CC50(0x1240, D_L22_001B2ACC, -1); break;
        }
        ref_L22_003A5018_05 = 0;
        math_fast_float_d(&D_L22_001B2AD0);
        if (D_L22_001B2AD0 <= 0) D_L22_001B2AC8 = -1;
    }
    if (ref_L22_003A5018_31) {
        FontSetWindow(box, 240, 480, 44, 468, 256, label_y(ctl, 320.0f, ref_L22_003A5018_06, 0.5f, 1), 16, 3);
        label = GetLocalizedString(0x9FC);
        hint = GetLocalizedString(0xE51);
        level_forward_draw_args(box, 0x80F0F0F0, label, 0, 0, -1, 0, hint, 0, 0);
    }
    module_l00_call_handler_2();
    return 1;
}
