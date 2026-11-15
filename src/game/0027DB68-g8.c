/* Manual retail reconstruction, 2026-10-24.
 * Reference: lombyte-project/Lombyte, GPL-3.0,
 * c41bf1c324eecae8006bf82808ad19ed42ee5eb9. No SDK headers, qcopy.h,
 * symbol aliases or assembly devices are included. RAC2 retail supplies the
 * actual fields, descriptor extents, argument banks and packet constants.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long s64;
typedef unsigned long long u64;
typedef int QuadWord __attribute__((mode(TI)));
extern int D_001A7350;
extern int D_001A7354;
/* Adapted control-flow reference: src/rendering/draw_screen_effect.c.
 * Local changes: actual RAC2 viewport array, real pointer and observed 0x30-byte
 * settings prefix; canonical helpers, no aliases or undersized SDA object.
 * This no-argument procedure preserves 64-bit alpha masks and zero-extends each
 * 32-bit colour before the fifth overlay GPR. Helpers can change the settings
 * pointer, so later source reads address the live global again.
 */
typedef struct {
    u32 reserved00, background;
    u64 background_alpha;
    int first_step;
    u32 first_color;
    u64 first_alpha;
    int second_step;
    u32 second_color;
    u64 second_alpha;
} ScreenEffectSettingsView;
extern short D_001A6480[];
extern ScreenEffectSettingsView *ref_0027DB68_00 __attribute__((sda));
extern void func_002FC560(u32, u64);
extern void func_0027DE50(int, int, int, int, unsigned long);
/* Draws the background and the lines of text of a text box using colours and alphas from its description. */
void func_0027DB68(void)
{
    int line;
    short height;
    u64 background_alpha, first_alpha, second_alpha;
    u32 background_color, first_color, second_color;
    line = 0;
    height = D_001A6480[0xA9];
    background_alpha = ref_0027DB68_00->background_alpha;
    if (background_alpha != 0)
        func_002FC560(0x42, background_alpha & 0xFF000000FFULL);
    background_color = ref_0027DB68_00->background;
    if (background_color & 0xFF000000u)
        func_0027DE50(0, height, 0, D_001A6480[0xA8], (unsigned long)background_color);
    if (height > 0) {
        do {
            first_alpha = ref_0027DB68_00->first_alpha;
            if (first_alpha != 0)
                func_002FC560(0x42, first_alpha & 0xFF000000FFULL);
            first_color = ref_0027DB68_00->first_color;
            if (first_color & 0xFF000000u)
                func_0027DE50(line,
                    line + ref_0027DB68_00->first_step < height - 1
                        ? line + ref_0027DB68_00->first_step : height - 1,
                    0, D_001A6480[0xA8], (unsigned long)first_color);
            line += ref_0027DB68_00->first_step;
            second_alpha = ref_0027DB68_00->second_alpha;
            if (second_alpha != 0)
                func_002FC560(0x42, second_alpha & 0xFF000000FFULL);
            second_color = ref_0027DB68_00->second_color;
            if (second_color & 0xFF000000u)
                func_0027DE50(line,
                    line + ref_0027DB68_00->second_step < height - 1
                        ? line + ref_0027DB68_00->second_step : height - 1,
                    0, D_001A6480[0xA8], (unsigned long)second_color);
            line += ref_0027DB68_00->second_step;
        } while (line < height);
    }
}
