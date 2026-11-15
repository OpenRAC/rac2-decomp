#include "common.h"

extern int D_001B23A0;
extern float D_001B23A4;
extern float D_001AB9E0 __attribute__((sda));
extern float D_001B23A8 __attribute__((sda));
extern char *D_001A8CFC;
extern struct { int w0, w1, w2; } D_00138340;
extern int table_find_by_id(void *, int);
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void AppendScreenRectPacket(int, int, int, int, u64, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);

static __inline__ int menu_screen_y(float value, float offset)
{
    float y = value * D_001B23A4 + 0.5f;
    if (D_001B23A0 != 1)
        return (int)y;
    return (int)(y + offset);
}

/* Draws the two small frames at the bottom and the left and right arrows used to page through a menu. */
void DrawMenuNavigationFramesAndLabels(int showLeft, int showRight)
{
    int dimColor, sprite;

    AppendScreenRectPacket(42, menu_screen_y(318.0f, D_001AB9E0), 44, menu_screen_y(343.0f, D_001AB9E0), 0x55F0C070, 0);
    AppendScreenRectPacket(64, menu_screen_y(318.0f, D_001AB9E0), 66, menu_screen_y(343.0f, D_001AB9E0), 0x55F0C070, 0);
    AppendScreenRectPacket(42, menu_screen_y(317.0f, D_001AB9E0), 66, menu_screen_y(319.0f, D_001AB9E0), 0x55F0C070, 0);
    AppendScreenRectPacket(42, menu_screen_y(342.0f, D_001AB9E0), 66, menu_screen_y(344.0f, D_001AB9E0), 0x55F0C070, 0);
    AppendScreenRectPacket(463, menu_screen_y(318.0f, D_001AB9E0), 465, menu_screen_y(343.0f, D_001AB9E0), 0x55F0C070, 0);
    AppendScreenRectPacket(485, menu_screen_y(318.0f, D_001AB9E0), 487, menu_screen_y(343.0f, D_001AB9E0), 0x55F0C070, 0);
    AppendScreenRectPacket(463, menu_screen_y(317.0f, D_001AB9E0), 487, menu_screen_y(319.0f, D_001AB9E0), 0x55F0C070, 0);
    AppendScreenRectPacket(463, menu_screen_y(342.0f, D_001AB9E0), 487, menu_screen_y(344.0f, D_001AB9E0), 0x55F0C070, 0);
    dimColor = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 25, 0, 0);
    if (showLeft) {
        char *root = D_001A8CFC;
        int selected = 0x80F0F0F0;
        if (!(D_00138340.w0 & 0x8000))
            selected = dimColor;
        sprite = table_find_by_id(root + 0x8710, 75);
        gfx_draw_scaled_object_two_axes((char *)sprite, selected, 213.0f, 322.0f, 1.0f, D_001B23A8, 0.0f);
    }
    if (showRight) {
        char *root = D_001A8CFC;
        int selected = 0x80F0F0F0;
        if (!(D_00138340.w0 & 0x2000))
            selected = dimColor;
        sprite = table_find_by_id(root + 0x8710, 74);
        gfx_draw_scaled_object_two_axes((char *)sprite, selected, 311.0f, 322.0f, 1.0f, D_001B23A8, 0.0f);
    }
}
