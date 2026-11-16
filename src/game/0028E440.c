#include "include_asm.h"
#include "common.h"

extern unsigned int ref_L00_002F9D30_00 __attribute__((sda));

/* Counts a timer down by one until it reaches zero. */
void hud_tick_countdown(void)
{
    if (ref_L00_002F9D30_00 != 0)
        --ref_L00_002F9D30_00;
}

typedef struct Task28E458 {
    u8 pad00[0x18];
    void (*update)(struct Task28E458 *);
    u8 pad1C[0x90 - 0x1C];
} Task28E458;

extern s32 g_weapon_wheel_slot_seven[] __attribute__((sda));
extern s32 g_cutscene_active_flag[] __attribute__((sda));
extern s32 g_hud_sprite_color_word[] __attribute__((sda));
extern s32 g_hud_record_active_a[] __attribute__((sda));
extern s32 g_hud_record_fade[] __attribute__((sda));
extern s32 g_hud_record_timer[] __attribute__((sda));
extern s32 g_current_game_mode[] __attribute__((sda));
extern Task28E458 g_hud_elements[];

/* Runs the update function of each of the thirteen HUD records, then fades the HUD overlay in or out. */
void hud_update_record_handlers(void) {
    Task28E458 *record;
    s32 i;

    if (g_weapon_wheel_slot_seven[1] != 0 || g_cutscene_active_flag[0] != 0) {
        g_weapon_wheel_slot_seven[1] = 0;
        return;
    }
    record = g_hud_elements;
    g_hud_sprite_color_word[0] = 0xFFFFF0;
    for (i = 12; i >= 0; i--) {
        if (record->update != 0) {
            record->update(record);
        }
        record++;
    }
    if ((g_hud_record_active_a[0] != 0 || g_hud_record_fade[0] != 0) && g_current_game_mode[0] == 0) {
        if (g_hud_record_active_a[0] != 0) {
            g_hud_record_fade[0] += 0x10;
            if (g_hud_record_fade[0] > 0x80) {
                g_hud_record_fade[0] = 0x80;
            }
        } else {
            g_hud_record_fade[0] -= 0x10;
            if (g_hud_record_fade[0] < 0) {
                g_hud_record_fade[0] = 0;
            }
        }
        if (g_hud_record_active_a[0] != 0) {
            g_hud_record_active_a[0]--;
        }
        if (g_hud_record_active_a[0] == 1000) {
            g_hud_record_active_a[0] = 0;
        }
    } else {
        g_hud_record_timer[0] = 100;
    }
}

extern int hud_find_entry_index(int);
extern unsigned short *g_hud_element_table;
extern short *g_hud_texture_pair_table;
extern unsigned int *g_hud_group_entries_b;
extern unsigned int *g_hud_group_entries_a;

/* Looks up the picture number for an icon and frame, or gives zero when it is missing. */
int GetIconFrame(int key, int index)
{
    int number = hud_find_entry_index(key);
    unsigned short *row = (unsigned short *)(number * 8 + (unsigned int)g_hud_element_table);
    if (row[0] == 65535)
        goto fail;
    if (index >= row[1])
        goto fail;
    {
        unsigned int mask = 0x80000000u;
        int offset = row[2] + index;
        short *pair = (short *)(offset * 4 + (unsigned int)*(short *volatile *)&g_hud_texture_pair_table);
        if (g_hud_group_entries_b[pair[0] * 2] & mask)
            goto fail;
        return (g_hud_group_entries_a[pair[1] * 2] & mask) ? 0 : offset;
    }
fail:
    return 0;
}


extern int *ref_L00_001B2608_00;
extern int ref_L00_001B1BBC_01;
extern int g_screen_offset_x;
extern int g_screen_offset_y;
extern int GetFrameTexture(int);

/* Draws a flat picture on the screen at a pixel position and size, with a see-through amount. */
void hud_draw_sprite(int texture, int x, int y, int width, int height, int alpha)
{
    short *row = (short *)((texture << 2) + (unsigned int)g_hud_texture_pair_table);
    unsigned char *entry = (unsigned char *)((unsigned int)g_hud_group_entries_a + (row[1] << 3));
    int mask6 = 1 << entry[6];
    int mask7 = 1 << entry[7];
    int *old_cursor;
    char *packet;
    int texture_word;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    old_cursor = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = old_cursor + 4;
    packet = (char *)ref_L00_001B2608_00;
    *(long long *)(old_cursor + 4) = 0x7400000000008001LL;
    *(long long *)(packet + 8) = 0x05353106;
    texture_word = GetFrameTexture(texture);
    *(long long *)(packet + 16) = texture_word;
    *(long long *)(packet + 24) = 0x156;
    *(long long *)(packet + 32) = ((long long)alpha << 24) | 0x7F7F7F;
    *(long long *)(packet + 40) = 0;
    *(long long *)(packet + 48) = ((x << 4) + g_screen_offset_x - 8) | ((long long)((y << 4) + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 56) = (mask7 << 20) + (mask6 << 4);
    *(long long *)(packet + 64) = (((x + width) << 4) + g_screen_offset_x - 8) | ((long long)(((y + height) << 4) + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}


/* Draws a picture on the screen like the one above, but the picture size is the size given. */
void hud_draw_sprite_sized_texture(int texture, int x, int y, int width, int height, int alpha)
{
    int *old_cursor;
    char *packet;
    int texture_word;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    old_cursor = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = old_cursor + 4;
    packet = (char *)ref_L00_001B2608_00;
    *(long long *)(old_cursor + 4) = 0x7400000000008001LL;
    *(long long *)(packet + 8) = 0x05353106;
    texture_word = GetFrameTexture(texture);
    *(long long *)(packet + 16) = texture_word;
    *(long long *)(packet + 24) = 0x156;
    *(long long *)(packet + 32) = ((long long)alpha << 24) | 0x7F7F7F;
    *(long long *)(packet + 40) = 0;
    *(long long *)(packet + 48) = ((x << 4) + g_screen_offset_x - 8) | ((long long)((y << 4) + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 56) = (height << 20) + (width << 4);
    *(long long *)(packet + 64) = (((x + width) << 4) + g_screen_offset_x - 8) | ((long long)(((y + height) << 4) + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}


/* Draws a picture on the screen at a finer-than-pixel position and size, with a see-through amount. */
void hud_draw_sprite_subpixel_no_color(int texture, int x, int y, int width, int height, int alpha)
{
    short *row = (short *)((texture << 2) + (unsigned int)g_hud_texture_pair_table);
    unsigned char *entry = (unsigned char *)((unsigned int)g_hud_group_entries_a + (row[1] << 3));
    int mask6 = 1 << entry[6];
    int mask7 = 1 << entry[7];
    int *old_cursor;
    char *packet;
    int texture_word;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    old_cursor = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = old_cursor + 4;
    packet = (char *)ref_L00_001B2608_00;
    *(long long *)(old_cursor + 4) = 0x7400000000008001LL;
    *(long long *)(packet + 8) = 0x05353106;
    texture_word = GetFrameTexture(texture);
    *(long long *)(packet + 16) = texture_word;
    *(long long *)(packet + 24) = 0x156;
    *(long long *)(packet + 32) = ((long long)alpha << 24) | 0x7F7F7F;
    *(long long *)(packet + 40) = 0;
    *(long long *)(packet + 48) = (x + g_screen_offset_x - 8) | ((long long)(y + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 56) = (mask7 << 20) + (mask6 << 4);
    *(long long *)(packet + 64) = (x + width + g_screen_offset_x - 8) | ((long long)(y + height + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}

/* Draws a picture on the screen at a finer-than-pixel position with a chosen colour and see-through amount. */
void DrawHudSpriteSubpixel(int a0, int a1, int a2, int a3, int a4, int a5, unsigned int color)
{
    short *row = (short *)((a0 << 2) + (unsigned int)g_hud_texture_pair_table);
    unsigned char *entry = (unsigned char *)((unsigned int)g_hud_group_entries_a + (row[1] << 3));
    int mask6 = 1 << entry[6];
    int mask7 = 1 << entry[7];
    int *p;
    char *q;
    int result;
    long long rgba;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    p = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = p + 4;
    q = (char *)ref_L00_001B2608_00;
    *(long long *)(p + 4) = 0x7400000000008001LL;
    *(long long *)(q + 8) = 0x05353106;
    result = GetFrameTexture(a0);
    *(long long *)(q + 16) = result;
    *(long long *)(q + 24) = 0x156;
    rgba = (unsigned char)color;
    rgba |= (unsigned int)(unsigned char)(color >> 8) << 8;
    rgba |= (long long)(unsigned char)(color >> 16) << 16;
    rgba |= (long long)a5 << 24;
    *(long long *)(q + 32) = rgba;
    *(long long *)(q + 40) = 0;
    *(long long *)(q + 48) = (a1 + g_screen_offset_x - 8) | ((long long)(a2 + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 56) = (mask7 << 20) + (mask6 << 4);
    *(long long *)(q + 64) = (a1 + a3 + g_screen_offset_x - 8) | ((long long)(a2 + a4 + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(q + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}

/* alpha is copied before a9 is reused for the texture height: retail loads the
   stack argument at the top and sign-extends it in place for the colour word.
   With a9 used only there, combine folds the load into the extension behind the
   header stores, and the colour loses $v1 to the cursor reloads. */
/* Draws part of a picture on the screen, choosing which piece of the picture to show. */
void hud_draw_sprite_region(long long texture_word, int x, int y, int u_width_log2, int v_height_log2, int width, int height, int u, int v, int a9)
{
    int *old_cursor;
    char *packet;
    int alpha = a9;

    a9 = 1 << (v_height_log2 + 4);
    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    old_cursor = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = old_cursor + 4;
    packet = (char *)ref_L00_001B2608_00;
    *(long long *)(old_cursor + 4) = 0x7400000000008001LL;
    *(long long *)(packet + 8) = 0x05353106;
    *(long long *)(packet + 16) = texture_word;
    *(long long *)(packet + 24) = 0x156;
    *(long long *)(packet + 32) = ((long long)alpha << 24) | 0x7F7F7F;
    *(long long *)(packet + 40) = u | ((long long)v << 16);
    *(long long *)(packet + 48) = (x + g_screen_offset_x - 8) | ((long long)(y + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 56) = (u + (1 << (u_width_log2 + 4))) | ((long long)(v + a9) << 16);
    *(long long *)(packet + 64) = (x + width + g_screen_offset_x - 8) | ((long long)(y + height + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}



/* The command cursor and the third coordinate word sit at a different address in
   every program, so they are per-level externals named after their level-00 place.
   The retail reaches them with lui+%lo, so they carry no sda attribute here: in this
   -G8 unit the bare symbol form would put them in small data and make the access
   $gp-relative. */
extern int *ref_L00_001B2608_00;
extern int ref_L00_001B1BBC_01;
extern int g_screen_offset_x;
extern int g_screen_offset_y;
extern int GetFrameTexture(int);

/* Draws a picture between two screen corners, using a chosen part of the picture. */
void hud_draw_quad_uv(int texture, int x0, int y0, int x1, int y1, int u0, int v0, int u1, int v1, int alpha)
{
    int *old_cursor;
    char *packet;
    int texture_word;

    *(int *)ref_L00_001B2608_00 = 0x10000005;
    *(int *)((char *)ref_L00_001B2608_00 + 4) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 8) = 0;
    *(int *)((char *)ref_L00_001B2608_00 + 12) = 0x50000005;
    old_cursor = ref_L00_001B2608_00;
    ref_L00_001B2608_00 = old_cursor + 4;
    packet = (char *)ref_L00_001B2608_00;
    *(long long *)(old_cursor + 4) = 0x7400000000008001LL;
    *(long long *)(packet + 8) = 0x05353106;
    texture_word = GetFrameTexture(texture);
    *(long long *)(packet + 16) = texture_word;
    *(long long *)(packet + 24) = 0x156;
    *(long long *)(packet + 32) = ((long long)alpha << 24) | 0x7F7F7F;
    *(long long *)(packet + 40) = u0 | ((long long)v0 << 16);
    *(long long *)(packet + 48) = (x0 + g_screen_offset_x - 8) | ((long long)(y0 + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 56) = u1 | ((long long)v1 << 16);
    *(long long *)(packet + 64) = (x1 + g_screen_offset_x - 8) | ((long long)(y1 + g_screen_offset_y - 8) << 16) | ((long long)ref_L00_001B1BBC_01 << 32);
    *(long long *)(packet + 72) = 0;
    ref_L00_001B2608_00 = (int *)((char *)ref_L00_001B2608_00 + 0x50);
}
