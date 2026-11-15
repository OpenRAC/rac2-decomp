#include "names.h"
/* func_002D3FA0 (2,468 bytes, 28 places): the options page with three rectangles and labels.
 * Own unit: -O2 -G8 -ffunction-sections -fno-gcse -frac2-frame-pointer-liveness -frac2-la-fp-const-first
 * (config/cflags.txt; docs/build/compiler-notes.md). Rectangle 2's two y values go through
 * hud_coord5, the dead-test rounding helper with five tests: cse follows at most 9 jumps per
 * path, so the colour copy cC survives to the call as retail. A compiler rule was tried first
 * (cse path length, copy-variable merges, argument-source rules) and did not close it; the
 * helper is allowed by owner ruling, 13 November 2026. y3 uses label_y3 on (void *)textResult.
 */
#include "include_asm.h"
#include "names.h"
typedef struct { char pad[0x1CC]; unsigned char *entries; int count; int timer; } MenuEntryState;
extern MenuEntryState g_pause_menu_state;
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];
extern unsigned int g_equipment_bits[] __attribute__((sda));
extern int D_001ABA74 __attribute__((sda));
extern int g_screen_width[] __attribute__((sda)), g_screen_height[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
typedef struct { unsigned char bytes[16]; } MenuCorners;
extern MenuCorners D_001ABA78;
extern char D_001AB998[];
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, MenuCorners *);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, unsigned long long, char *, int);
extern int text_draw_centered_small(int, int, unsigned long long, char *, int);
extern int sprintf(char *, char *, ...);
extern void DrawPreviewChoiceIcon(int, int);
extern void gfx_set_scissor_clamped(int, int, int, int);
extern void DrawMobysSetup(void), mem_fill_scratch_area(void), mem_save_scratch_area(void);
extern void tex_upload_object_textures(char *, int), mem_restore_scratch_area(void);
extern int tex_run_upload_and_setup(void);
extern void render_environment_mapped_object(char *);
extern void SetupGifPaging(int), DoGifPaging(void);
extern char *D_001A8CFC[] __attribute__((sda));
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
static __inline__ int label_y2(void *handle, float value, float scale, float half, int active)
{
    int mode = D_001B23A0;
    float scaled = value * scale + half;
    int result = (int)scaled;
    if (mode == active)
        scaled = scale;
    if (handle != 0)
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
static __inline__ int hud_coord5(float value, float scale, float half, int active)
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
    copy = result;
    if (copy != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
static __inline__ int label_y3(void *handle, float value, float scale, float half, int active)
{
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;
    int mode;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    mode = D_001B23A0;
    if (mode == active)
        scaled = scale;
    return result;
}
/* Draws the options screen: the titles, the framed boxes, the row of choice icons around the selected one, the help text and the live model preview. */
int options_menu_draw(void)
{
    MenuCorners corners = D_001ABA78;
    char text[32];
    int color = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 30, 0, 0);
    int x, index, i;
    char *first, *second;
    int texture, hintResult, textResult;
    int y1, y2, y3;
    int on2 = 1, on3 = 1;
    int one = 1;
    int one2 = 1;
    int one3 = 1;
    int ya, yb;
    unsigned long cB;
    unsigned long cC;
    float px, py;
    SetupGifPaging(0);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC[0] + 0x8710, 0XD0), 0x60442D00, (float)(g_screen_width[0] / 2), (float)hud_coord((float)(g_screen_height[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC[0] + 0x8710, 0XD1), 0x60241700, (float)(g_screen_width[0] / 2), (float)hud_coord((float)(g_screen_height[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC[0] + 0x8710, 0XD2), 0x55F0C070, (float)(g_screen_width[0] / 2), (float)hud_coord((float)(g_screen_height[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC[0] + 0x8710, 0XD3), 0x55F0C070, (float)(g_screen_width[0] / 2), (float)hud_coord((float)(g_screen_height[0] / 2), D_001B23A4[0], 0.5f, one), 1.0f, 1.0f, 0.0f);
    ya = hud_coord(326.0f, D_001B23A4[0], 0.5f, one);
    yb = hud_coord(387.0f, D_001B23A4[0], 0.5f, one);
    cB = color;
    cC = cB;
    AppendScreenRectPacket(228, ya, 230, yb, cB, 0);
    AppendScreenRectPacket(286, hud_coord5(326.0f, D_001B23A4[0], 0.5f, one), 288, hud_coord5(387.0f, D_001B23A4[0], 0.5f, one), cC, 0);
    AppendScreenRectPacket(228, hud_coord(325.0f, D_001B23A4[0], 0.5f, one), 288, hud_coord(327.0f, D_001B23A4[0], 0.5f, one), cC, 0);
    AppendScreenRectPacket(228, hud_coord(386.0f, D_001B23A4[0], 0.5f, one2), 288, hud_coord(388.0f, D_001B23A4[0], 0.5f, one2), cB, 0);
    texture = GetIconFrame(0xEAA8, 0); hud_draw_sprite_gradient(texture, 16, label_y((void *)texture, 36.0f, D_001B23A4[0], 0.5f, one2), 192, label_y((void *)texture, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    texture = GetIconFrame(0xEAA8, 0); hud_draw_sprite_gradient(texture, 400, label_y((void *)texture, 36.0f, D_001B23A4[0], 0.5f, one2), -192, label_y((void *)texture, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    texture = GetIconFrame(0xEAA8, 0); hud_draw_sprite_gradient(texture, 16, label_y((void *)texture, 228.0f, D_001B23A4[0], 0.5f, one2), 192, -label_y((void *)texture, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    texture = GetIconFrame(0xEAA8, 0); hud_draw_sprite_gradient(texture, 400, label_y((void *)texture, 228.0f, D_001B23A4[0], 0.5f, one2), -192, -label_y((void *)texture, 96.0f, D_001B23A4[0], 0.5f, one2), &corners);
    texture = GetIconFrame(0xEAA8, 1); hud_draw_sprite(texture, 402, label_y((void *)texture, 50.0f, D_001B23A4[0], 0.5f, one2), 89, label_y((void *)texture, 115.0f, D_001B23A4[0], 0.5f, one2), 64);
    y1 = hud_coord(116.0f, D_001B23A4[0], 0.5f, one2);
    textResult = text_draw_centered_medium(445, y1, 0x80F0F0F0ULL, GetLocalizedString(0x3212), -1);
    y2 = hud_coord(134.0f, D_001B23A4[0], 0.5f, one2);
    textResult = text_draw_centered_medium(445, y2, 0x80F0F0F0ULL, GetLocalizedString(0x3213), -1);
    textResult = sprintf(text, D_001AB998, GetLocalizedString(0x3213), GetLocalizedString(0x2D55));
    textResult = text_draw_centered_small(159, hud_coord(18.0f, D_001B23A4[0], 0.5f, on3), 0x80F0F0F0ULL, text, -1);
    do {
    y3 = label_y3((void *)textResult, 187.0f, D_001B23A4[0], 0.5f, on3);
    } while (0);
    hintResult = text_draw_centered_small(445, y3, 0x80F0F0F0ULL, GetLocalizedString(0x2D4F), -1);
    x = 235;
    for (i = 0; i < 12; i++) {
        index = D_001ABA74 - i;
        if (index >= 0 && index < 12) {
            while (index >= 0) {
                if ((g_equipment_bits[0] & D_0026CFD0[index].selectionMask) == D_0026CFD0[index].requiredBits)
                    break;
                index--;
                i++;
            }
            if (index < 0)
                continue;
            DrawPreviewChoiceIcon(index, x);
        }
        x -= 56;
    }
    x = 291;
    for (i = 1; i < 12; i++) {
        index = D_001ABA74 + i;
        if (index >= 0 && index < 12) {
            while (index < 12) {
                if ((g_equipment_bits[0] & D_0026CFD0[index].selectionMask) == D_0026CFD0[index].requiredBits)
                    break;
                index++;
                i++;
            }
            if (index >= 12)
                continue;
            DrawPreviewChoiceIcon(index, x);
        }
        x += 56;
    }
    DoGifPaging();
    gfx_set_scissor_clamped(30, 385, label_y2((void *)hintResult, 50.0f, D_001B23A4[0], 0.5f, on2), label_y((void *)i, 213.0f, D_001B23A4[0], 0.5f, on3));
    DrawMobysSetup();
    mem_fill_scratch_area();
    mem_save_scratch_area();
    tex_upload_object_textures(g_pause_menu_state.entries, g_pause_menu_state.count);
    mem_restore_scratch_area();
    tex_run_upload_and_setup();
    SetupGifPaging(0);
    render_environment_mapped_object(g_pause_menu_state.entries);
    DoGifPaging();
    gfx_set_scissor_clamped(0, g_screen_width[0] - 1, 0, g_screen_height[0] - 1);
    return 0;
}
