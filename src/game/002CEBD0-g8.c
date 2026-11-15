#include "common.h"
extern int D_001B23A0;
extern float D_001B23A4;
extern float D_001AB9E4 __attribute__((sda));
extern float D_001AB9E8 __attribute__((sda));
extern float D_001B23A8;
extern char *D_001A8CFC;
extern int g_pad_state[];
extern int table_find_by_id(void *, int);
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void set_identity_matrix(void *);
extern void FastVecScale(void *, void *, float);
extern void AppendScreenRectPacket(int, int, int, int, u64, int);
extern void DrawNativeQuads(int, int, void *, float, float, float);
static __inline__ float menu_vector_offset(float value, float offset)
{
    if (D_001B23A0 == 1) value += offset;
    return value;
}

static __inline__ int menu_screen_y(float value, float offset)
{
    float y = value * D_001B23A4 + 0.5f;
    if (D_001B23A0 == 1) return (int)(y + offset);
    return (int)y;
}

/* Draws the up and down arrows and the frame beside the scrolling five-row menu list. */
void menu_draw_scroll_arrows_and_frame(void) {
    float vectors[16];
    int arrow_sprite, dim_color, arrow_color, top_y, bottom_y;
    arrow_sprite = table_find_by_id(D_001A8CFC + 0x8710, 74);
    dim_color = math_ping_pong_blend_values(0x60442D00, 0x55F0C070, 25, 0, 0);
    set_identity_matrix(vectors);
    vectors[0] = 0.0f;
    vectors[2] = menu_vector_offset(D_001B23A8, 0.07f);
    vectors[8] = menu_vector_offset(D_001B23A8, 0.07f);
    vectors[10] = 0.0f;
    FastVecScale(vectors, vectors, *(float *)((char *)arrow_sprite + 12));
    FastVecScale(vectors+8, vectors+8, *(float *)((char *)arrow_sprite + 12));
    arrow_color = g_pad_state[0x1c0/4] & 0x1000 ? 0x80F0F0F0 : dim_color;
    DrawNativeQuads(arrow_sprite, arrow_color, vectors, 58.0f, (float)menu_screen_y(457.0f, D_001AB9E4), 0.0f);
    vectors[0] = 0.0f;
    vectors[2] = menu_vector_offset(-D_001B23A8, -0.07f);
    vectors[8] = menu_vector_offset(-D_001B23A8, -0.07f);
    vectors[10] = 0.0f;
    FastVecScale(vectors, vectors, *(float *)((char *)arrow_sprite + 12));
    FastVecScale(vectors+8, vectors+8, *(float *)((char *)arrow_sprite + 12));
    arrow_color = g_pad_state[0x1c0/4] & 0x4000 ? 0x80F0F0F0 : dim_color;
    DrawNativeQuads(arrow_sprite, arrow_color, vectors, 44.0f, (float)menu_screen_y(187.0f, D_001AB9E4), 0.0f);
    top_y = menu_screen_y(278.0f, D_001AB9E8);
    bottom_y = menu_screen_y(369.0f, D_001AB9E8);
    AppendScreenRectPacket(39, top_y, 41, bottom_y, 0x55F0C070, 0);
    top_y = menu_screen_y(278.0f, D_001AB9E8);
    bottom_y = menu_screen_y(369.0f, D_001AB9E8);
    AppendScreenRectPacket(63, top_y, 65, bottom_y, 0x55F0C070, 0);
    top_y = menu_screen_y(277.0f, D_001AB9E8);
    bottom_y = menu_screen_y(279.0f, D_001AB9E8);
    AppendScreenRectPacket(39, top_y, 65, bottom_y, 0x55F0C070, 0);
    top_y = menu_screen_y(368.0f, D_001AB9E8);
    bottom_y = menu_screen_y(370.0f, D_001AB9E8);
    AppendScreenRectPacket(39, top_y, 65, bottom_y, 0x55F0C070, 0);
}
