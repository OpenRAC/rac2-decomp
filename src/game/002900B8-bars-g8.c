/* func_002900B8 (1,388 bytes, 28 places): a HUD panel with two scale bars and three text rows.
 * Own unit: -O2 -G8 -fno-expensive-optimizations -ffunction-sections -frac2-keep-block-order
 * -frac2-cse2-keep-multi-set-reg -frac2-cse-arg-hard-reg -frac2-reload-cse-branch-to-next
 * (config/cflags.txt; docs/build/compiler-notes.md). Case 0 keeps the scale as in cases 1/2,
 * `s = 128.0f` before the upper bar's rounding, and edge/edge2 locals for the bar limits. The
 * hud_coord dead-test helper is allowed by owner ruling (7 November 2026). Owner standard of
 * 12 November 2026 for the switches (22 functions change when they are forced on).
 */
#include "common.h"

extern int D_001A9000 __attribute__((sda));
extern int D_001A9004 __attribute__((sda));
extern float D_001A9008 __attribute__((sda));
extern int D_001A900C __attribute__((sda));
extern int D_001A9010 __attribute__((sda));

typedef struct {
    int active;
    int timer;
    char pad08[0x18];
    int entryIndex;
    int unk24;
} Subtitle_002900B8;

typedef struct {
    char pad[0xB0];
    float opacity;
} Hud_002900B8;

extern char *D_001A8CFC[] __attribute__((sda));
extern Subtitle_002900B8 D_00254E78;
extern Hud_002900B8 D_001B9040;
extern float D_001B23A4[] __attribute__((sda));
extern int D_001A8D40 __attribute__((sda));
extern void func_0027AB40(void);
extern float func_00283CE0(int);
extern int func_00283D38(int, int, float);
extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_0027DE50(int, int, int, int, unsigned long);

extern int D_001B23A0;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
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

static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == active)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the gauge pop-up: a dark panel with scale bars filled up to the current amount. */
int func_002900B8(void)
{
    float savedOpacity;
    float blend;
    float scale;
    float zero;
    float y;
    char *panelTexture;
    int backColor;
    int frameColor;
    int one;
    float half;

    if (D_001A8CFC[0] != 0 && gSubtitleState.active == 0 && gSubtitleState.unk24 == -1) {
        one = 1;
        half = 0.5f;
        savedOpacity = D_001B9040.opacity;
        D_001B9040.opacity = 0.62f;
        UpdateViewContext();
        blend = IntToFloat(gGaugePopupBlend) * 0.1f;
        backColor = FastTweenColor(0x442D00, 0x60442D00, blend);
        frameColor = FastTweenColor(0xF0C070, 0x55F0C070, blend);
        panelTexture = FindTableEntryById(D_001A8CFC[0] + 0x8710, 0xA6);
        y = (float)label_y(panelTexture, 206.0f, D_001B23A4[0], half, one);
        scale = 1.0f;
        zero = 0.0f;
        DrawScaledObjectTwoAxes(panelTexture, backColor, 484.0f, y, scale, scale, zero);
        panelTexture = FindTableEntryById(D_001A8CFC[0] + 0x8710, 0xA7);
        DrawScaledObjectTwoAxes(panelTexture, frameColor, 484.0f, (float)label_y(panelTexture, 206.0f, D_001B23A4[0], half, one), 1.0f, 1.0f, 0.0f);
        switch (gGaugePopupMode) {
        case 0:
            if (zero <= gGaugePopupAmount && gGaugePopupAmount <= scale) {
                int color1;
                int color2;
                int top;
                int i;
                float step;
                float lower;
                float upper;
                float edge;
                float edge2;
                float s;

                color1 = FastTweenColor(gGaugePopupColorA & 0xFFFFFF, gGaugePopupColorA, blend);
                color2 = FastTweenColor(gGaugePopupColorB & 0xFFFFFF, gGaugePopupColorB, blend);
                s = D_001B23A4[0];
                top = hud_coord((float)(285 - (int)((scale - gGaugePopupAmount) * 157.0f)), s, half, one);
                s = (float)hud_coord(128.0f, D_001B23A4[0], half, one);
                step = s * 0.25f;
                lower = (float)hud_coord(285.0f, D_001B23A4[0], half, one);
                edge = lower - step;
                upper = edge + scale;
                for (i = 0; i < 5; i++) {
                    scale = (float)top;
                    if (upper <= scale)
                        upper = scale;
                    DrawColoredRectangle((int)upper, (int)lower, 477, 489, color1);
                    lower -= step;
                    upper -= step;
                    if (lower <= scale)
                        break;
                }
                s = 128.0f;
                upper = (float)hud_coord(s, D_001B23A4[0], 0.5f, 1);
                edge2 = upper + step;
                lower = edge2 - 1.0f;
                for (i = 0; i < 5; i++) {
                                        if ((float)top <= lower)
                        lower = (float)top;
                    DrawColoredRectangle((int)upper, (int)lower, 476, 488, color2);
                    upper += step;
                    lower += step;
                    if ((float)top <= upper)
                        break;
                }
            }
            break;
        case 1:
        case 2: {
            int color;
            int top;
            int i;
            float step;
            float lower;
            float upper;
            float limit;
            float s;
            float edge;

            color = FastTweenColor(gGaugePopupColorA & 0xFFFFFF, gGaugePopupColorA, blend);
            s = D_001B23A4[0];
            top = hud_coord((float)(285 - (int)((1.0f - gGaugePopupAmount) * 157.0f)), s, 0.5f, 1);
            s = (float)hud_coord(128.0f, D_001B23A4[0], 0.5f, 1);
            step = s * 0.25f;
            lower = (float)hud_coord(285.0f, D_001B23A4[0], 0.5f, 1);
            edge = lower - step;
            upper = edge + 1.0f;
            for (i = 0; i < 5; i++) {
                limit = (float)top;
                if (upper <= limit)
                    upper = limit;
                DrawColoredRectangle((int)upper, (int)lower, 476, 488, color);
                lower -= step;
                upper -= step;
                if (lower <= limit)
                    break;
            }
        }
        }
        D_001B9040.opacity = savedOpacity;
        UpdateViewContext();
    }
    return D_001A8D40;
}
