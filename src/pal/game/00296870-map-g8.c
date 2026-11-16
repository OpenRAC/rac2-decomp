/* func_PAL_00296870, the PAL copy of func_00295F60 (src/game/00295F60-map-g8.c): the same C
 * and flags, where the "no map" message becomes localized text 0x1BD3 printed in a text window
 * built from PAL-only data, the label backdrop grows by 2 and 8 pixels, and the label window's
 * flags word becomes 0x11. The window and label buffers are block locals: retail's frame shares
 * one stack slot between the no-map window, the label window and the player marker position.
 */

#include "common.h"

/* Adapted from Lombyte's project (GPL-3.0): src/assembly/textbin/ui/map/draw_map_overlay.c. */
struct DmaTag_205E70 { u32 tag, addr, vif0, vif1; };
struct TagPtr_205E70 { struct DmaTag_205E70 *p; };
typedef struct { s32 flags; u8 pad4[12]; } MapIdFlags_205E70;

struct ScreenOffsets_205E70 {
    s32 width, height;
    u8 pad8[8];
    s32 x;
    s32 y;
};

typedef struct {
    s16 id; /* 0x00 */
    u16 pad02;
    u16 flags;       /* 0x04 */
    u16 texture_id;  /* 0x06 */
    s16 frame_index; /* 0x08 */
    u16 pad0A[2];
    s16 label_width;    /* 0x0E */
    s16 label_height;   /* 0x10 */
    s16 label_offset_x; /* 0x12 */
    s16 label_offset_y; /* 0x14 */
    u16 pad16;
    f32 x;      /* 0x18 */
    f32 y;      /* 0x1C */
    f32 angle;  /* 0x20 */
    s32 active; /* 0x24 */
} MapIcon_205E70;

typedef struct {
    s32 cell;
    s32 pad[3];
} MapHighlightedCell_205E70;

typedef struct {
    u8 pad0[0x8];
    s32 marks_enabled; /* 0x08 */
    u8 padC[0xC];
    s32 z;          /* 0x18 */
    s32 grid;       /* 0x1C */
    MapIcon_205E70 *icons; /* 0x20 */
    s32 enabled;    /* 0x24 */
    u8 pad28[0x4];
    s32 show_markers;            /* 0x2C */
    MapHighlightedCell_205E70 marks[8]; /* 0x30 */
    u8 padB0[0x4];
    f32 zoom[21];     /* 0xB4 */
    s32 offset_x[21]; /* 0x108 */
    s32 offset_y[21]; /* 0x15C */
    u8 pad1A4[0x84];
    s32 selected_map; /* 0x234 */
    u8 pad22C[0x14];
    s32 texture_address; /* 0x24C */
} MapOverlayState_205E70;

typedef struct {
    u8 pad0[0x80];
    f32 x; /* 0x80 */
    f32 y; /* 0x84 */
    u8 pad88[0x10];
    f32 angle; /* 0x98 */
    u8 pad9C[0x2200];
    s32 mode; /* 0x229C */
} MapPlayerState_205E70;

typedef struct {
    s16 pad0;
    s16 image_index;
} MapTextureReference_205E70;

typedef struct {
    u8 pad0[6];
    u8 width_exponent;
    u8 height_exponent;
} MapTextureInfo_205E70;

typedef struct {
    u8 pad0[0x20];
    MapTextureReference_205E70 *references; /* 0x20 */
    MapTextureInfo_205E70 *textures;        /* 0x24 */
} MapTextureTables_205E70;

typedef struct {
    s16 s[12];
} FontWindow_205E70;

typedef struct {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
} MapIconBounds_205E70;


extern struct TagPtr_205E70 g_dma_packet_cursor MACRO_ADDR;
extern struct ScreenOffsets_205E70 g_screen_width MACRO_ADDR;
extern MapOverlayState_205E70 g_map_overlay_state NOT_SDA;
extern MapPlayerState_205E70 g_hero_state NOT_SDA;
extern MapTextureTables_205E70 g_hud_state MACRO_ADDR;
extern MapIdFlags_205E70 g_map_id_flags[] NOT_SDA;
extern s32 g_current_map_index MACRO_ADDR;
/* PAL-only placement of the no-map text window: anchor x, anchor y, left, right. */
extern s32 g_map_window_field_4 __attribute__((sda));
extern s32 g_map_window_field_5 MACRO_ADDR;
extern s32 g_map_window_field_2 __attribute__((sda));
extern s32 g_map_window_field_3 __attribute__((sda));
extern s32 g_map_icons_hidden __attribute__((sda));
extern s32 g_map_scissor_a __attribute__((sda));
extern s32 g_map_scissor_c __attribute__((sda));
extern s32 g_map_scissor_b __attribute__((sda));
extern s32 g_map_scissor_d __attribute__((sda));
extern s32 g_map_mode NOT_SDA;
extern s32 g_map_highlight_active __attribute__((sda));
extern s32 g_map_highlight_index __attribute__((sda));
extern s32 g_map_icon_x0 __attribute__((sda));
extern s32 g_map_icon_y0 __attribute__((sda));
extern s32 g_map_icon_x1 __attribute__((sda));
extern s32 g_map_icon_y1 __attribute__((sda));
extern s32 g_map_color_table[10] __attribute__((sda));
extern u32 g_map_tint_table[] NOT_SDA;
extern f32 g_map_variant_angles[4] __attribute__((sda));
extern f32 g_map_sprite_width_scale_a __attribute__((sda));
extern f32 g_map_sprite_height_scale_a __attribute__((sda));
extern f32 g_map_sprite_width_scale_b __attribute__((sda));
extern f32 g_map_sprite_height_scale_b __attribute__((sda));
extern f32 g_map_sprite_width_scale_c __attribute__((sda));
extern f32 g_map_sprite_height_scale_c __attribute__((sda));
extern void SetupGifPaging(s32);
extern void DoGifPaging(void);
extern char *GetLocalizedString(s32);
extern void text_draw_window_small(FontWindow_205E70 *,u64,char *,s32);
extern void VU1_addGSregister(s32,s64);
extern void gfx_set_scissor_clamped(s32,s32,s32,s32);
extern s32 GetIconFrame(s32,s32);
extern u64 GetFrameTexture(s32);
extern void AppendScreenRectPacket(s32,s32,s32,s32,u64,s32);
extern f32 FastAddRotations(f32,f32);
extern void DrawRotatedSprite(f32,f32,f32,f32,f32,s32,s32,u64);
extern void DrawHudSpriteSubpixel(s32,s32,s32,s32,s32,s32,s32);
extern void text_format_localized_amount(s32,void *);
extern void *memset(void *,s32,u32);
extern void text_draw_window_medium(void *,u64,void *,s32);
extern s32 GetSpecialMapCoordinates(f32,f32,f32 *,f32 *,s32);
extern void map_convert_world_to_map_position(f32,f32,f32 *,f32 *,s32);
extern s32 moby_get_current_variant_index(void);

/* UNK_NoMapAvailable */
void DrawMapOverlay_pal(s32 paging, s32 set_clip) {
    s32 rx0, ry0, rx1, ry1;
    struct DmaTag_205E70 *tag;
    u64 *packet_words;
    u64 background_tex0;
    u64 map_tex0;
    s32 palette_block;
    s32 mirror_sign;
    s32 tile_size;
    s32 left_tile_count, top_tile_count, right_tile_count, bottom_tile_count;
    s32 x0, y0, x1, y1;
    s32 u, v;
    s32 dx, dy;
    s32 i, j;
    s32 cell, cell_y, cell_x;
    MapHighlightedCell_205E70 *highlighted_cell;
    MapIconBounds_205E70 *r;
    MapIconBounds_205E70 *icon_bounds;
    MapIcon_205E70 *icon;
    MapTextureInfo_205E70 *texture_info;
    f32 zoom;
    f32 icon_scale;
    f32 icon_size_multiplier;
    f32 s;
    f32 icon_center_x, icon_center_y;
    s32 pan_x, map_extent, pan_y, oy1;
    s32 ax, ay, bx, by;
    s32 id, sprite_word, texture_width;
    f32 angle, sprite_width, sprite_height, center_x, center_y;
    s16 label_width;
    s32 label_height, label_offset_x, label_offset_y;
    s32 label_x, label_y;
    s32 image_index;
    s32 flip;
    s32 texture_id;
    s32 tile_limit;

    if (g_map_icons_hidden) return;
    if (g_map_overlay_state.enabled == 0 || g_map_overlay_state.selected_map >= 21) {
        /* The inner block lets the window's stack slots go before the label code reuses them. */
        {
            FontWindow_205E70 text_window;
            s16 window_fields[12];
            char *text = GetLocalizedString(0x1BD3);

            if (paging) SetupGifPaging(0);
            memset(window_fields, 0, sizeof(window_fields));
            window_fields[1] = 400;
            window_fields[2] = g_map_window_field_2;
            window_fields[3] = g_map_window_field_3;
            window_fields[4] = g_map_window_field_4;
            window_fields[5] = g_map_window_field_5;
            window_fields[8] = 16;
            text_window = *(FontWindow_205E70 *)window_fields;
            text_draw_window_small(&text_window, 0x80F0F0F0, text, -1);
            if (paging) DoGifPaging();
            return;
        }
    }
    if (g_map_overlay_state.selected_map < 0) {
        return;
    }

    if (paging) SetupGifPaging(0);
    rx0 = 0x1000;
    ry0 = 0x800;
    mirror_sign = 1;
    {
        s32 selected = g_map_overlay_state.selected_map;
        s32 ox = g_map_overlay_state.offset_x[selected] >> 15;
        s32 oy = g_map_overlay_state.offset_y[selected] >> 15;
        zoom = g_map_overlay_state.zoom[selected];
        pan_x = zoom * (f32)ox;
        tile_size = zoom * 512.0f;
        pan_y = zoom * (f32)oy;
        map_extent = zoom * 8192.0f;
    }
    tile_limit = tile_size + 0x2000;
    rx0 -= pan_x * mirror_sign;
    ry0 -= pan_y;
    rx1 = rx0 + map_extent * mirror_sign;
    ry1 = ry0 + map_extent;
    left_tile_count = (rx0 + tile_size - 1) / tile_size;
    top_tile_count = (ry0 + tile_size - 1) / tile_size;
    right_tile_count = (tile_limit - rx1 - 1) / tile_size;
    bottom_tile_count = (tile_limit - ry1 - 1) / tile_size;
    x0 = rx0 - tile_size * left_tile_count;
    y0 = ry0 - tile_size * top_tile_count;
    x1 = rx1 + tile_size * right_tile_count;
    y1 = ry1 + tile_size * bottom_tile_count;
    u = ((left_tile_count + right_tile_count) << 9) + 0x2000;
    v = ((top_tile_count + bottom_tile_count) << 9) + 0x2000;

    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x47, 0);
    if (set_clip) gfx_set_scissor_clamped(g_map_scissor_a, g_map_scissor_c, g_map_scissor_b, g_map_scissor_d);
    g_dma_packet_cursor.p->tag = 0x10000005;
    g_dma_packet_cursor.p->addr = 0;
    g_dma_packet_cursor.p->vif0 = 0;
    g_dma_packet_cursor.p->vif1 = 0x50000005;
    g_dma_packet_cursor.p++;
    background_tex0 =
        GetFrameTexture(GetIconFrame(0xE999, g_map_overlay_state.selected_map));
    packet_words = (u64 *)g_dma_packet_cursor.p;
    packet_words[0] = 0x7400000000008001;
    packet_words[1] = 0x5353106;
    packet_words[2] = background_tex0;
    packet_words[3] = 0x156;
    packet_words[4] = 0x80808080;
    packet_words[5] = 0;
    packet_words[6] = ((x0 + g_screen_width.x) - 8) | ((u64)((y0 + g_screen_width.y) - 8) << 16) |
                      ((u64)g_map_overlay_state.z << 32);
    packet_words[7] = u | ((u64)v << 16);
    packet_words[8] = ((x1 + g_screen_width.x) - 8) | ((u64)((y1 + g_screen_width.y) - 8) << 16) |
                      ((u64)g_map_overlay_state.z << 32);
    packet_words[9] = 0;
    g_dma_packet_cursor.p = (struct DmaTag_205E70 *)((u8 *)g_dma_packet_cursor.p + 0x50);
    VU1_addGSregister(8, 5);
    VU1_addGSregister(0x47, 0x60B);

    palette_block = (background_tex0 >> 37) & 0x3FFF;
    g_dma_packet_cursor.p->tag = 0x10000005;
    g_dma_packet_cursor.p->addr = 0;
    g_dma_packet_cursor.p->vif0 = 0;
    g_dma_packet_cursor.p->vif1 = 0x50000005;
    map_tex0 = (u64)((g_map_overlay_state.texture_address >> 8) | (8 << 14) | (0x13 << 20) | (9 << 26)) |
               ((u64)9 << 30) | ((u64)1 << 34) | ((u64)palette_block << 37) |
               ((long)0x8000000000000000ULL);
    tag = g_dma_packet_cursor.p;
    g_dma_packet_cursor.p = tag + 1;
    packet_words = (u64 *)(tag + 1);
    packet_words[0] = 0x7400000000008001;
    packet_words[1] = 0x5353106;
    packet_words[2] = map_tex0;
    packet_words[3] = 0x156;
    packet_words[4] = 0x80808080;
    packet_words[5] = 0;
    packet_words[6] = ((rx0 + g_screen_width.x) - 8) | ((u64)((ry0 + g_screen_width.y) - 8) << 16) |
                      ((u64)g_map_overlay_state.z << 32);
    packet_words[7] = 0x20002000;
    packet_words[8] = ((rx1 + g_screen_width.x) - 8) | ((u64)((ry1 + g_screen_width.y) - 8) << 16) |
                      ((u64)g_map_overlay_state.z << 32);
    packet_words[9] = 0;
    g_dma_packet_cursor.p = (struct DmaTag_205E70 *)((u8 *)g_dma_packet_cursor.p + 0x50);
    VU1_addGSregister(0x47, 0x360B);

    if (g_map_overlay_state.show_markers != 0 && g_map_overlay_state.marks_enabled != 0) {
        dx = rx1 - rx0;
        dy = ry1 - ry0;
        highlighted_cell = g_map_overlay_state.marks;
        for (i = 0; i < 8; i++, highlighted_cell++) {
            cell = highlighted_cell->cell;
            if (cell >= 0) {
                cell_x = cell % 16;
                cell_y = cell / 16;
                AppendScreenRectPacket(rx0 + cell_x * dx / 16, ry0 + cell_y * dy / 16,
                                          rx0 + (cell_x + 1) * dx / 16,
                                          ry0 + (cell_y + 1) * dy / 16, 0x20000000, 1);
            }
        }
    }

    if (g_map_overlay_state.icons != 0) {
        icon_bounds = ((MapIconBounds_205E70 *)0x70000000);
        icon_scale = (g_map_overlay_state.zoom[g_map_overlay_state.selected_map] * 2.0f + 5.0f) / 13.0f;
        if (!(g_map_overlay_state.icons[0].flags & 4)) {
            MapIconBounds_205E70 *r;
            s32 i;
            MapIcon_205E70 *icon;
            f32 icon_size_multiplier;
            s32 image_index;
            f32 icon_center_x, icon_center_y;
            MapTextureInfo_205E70 *texture_info;
            f32 s, scaled;
            s32 texture_id;

            i = 0;
            do {
                if (g_map_overlay_state.icons[i].active != 0 &&
                    (texture_id = g_map_overlay_state.icons[i].texture_id) != 0 &&
                    !(g_map_overlay_state.icons[i].flags & 1)) {
                    icon_size_multiplier = 1.0f;
                    if (g_map_overlay_state.icons[i].flags & 0x80) {
                        icon_size_multiplier = 1.5f;
                    }
                    image_index = GetIconFrame(texture_id,
                                                                   g_map_overlay_state.icons[i].frame_index);
                    icon_center_x = (f32)rx0 + g_map_overlay_state.icons[i].x * (f32)(rx1 - rx0);
                    icon_center_y = (f32)ry0 + g_map_overlay_state.icons[i].y * (f32)(ry1 - ry0);
                    texture_info =
                        &g_hud_state.textures[g_hud_state.references[image_index].image_index];
                    if (g_map_overlay_state.icons[i].flags & 0x200) {
                        s = g_map_overlay_state.zoom[g_map_overlay_state.selected_map];
                    } else {
                        s = icon_scale;
                    }
                    scaled = icon_size_multiplier * s;
                    icon_bounds[i].x0 =
                        icon_center_x -
                        scaled * (f32)(1 << (texture_info->width_exponent + 3));
                    icon_bounds[i].x1 =
                        (f32)icon_bounds[i].x0 +
                        scaled * (f32)(1 << (texture_info->width_exponent + 4));
                    icon_bounds[i].y0 =
                        icon_center_y -
                        scaled * (f32)(1 << (texture_info->height_exponent + 3));
                    icon_bounds[i].y1 =
                        (f32)icon_bounds[i].y0 +
                        scaled * (f32)(1 << (texture_info->height_exponent + 4));
                }
                i++;
            } while (!(g_map_overlay_state.icons[i].flags & 4));
        }

        {
            s32 i, j;
            s32 pan_x, map_extent, pan_y, oy1;
            s32 ax, ay, bx, by;
            MapIcon_205E70 *icon;
            s32 inner_offset;

            /* The flag-4 entry terminates the list. Separate overlapping icon
               bounds before either icon is drawn, using half of the smallest
               positive edge distance for each pair. */
            i = 0;
            if (!(g_map_overlay_state.icons[1].flags & 4))
                do {
                    if (g_map_overlay_state.icons[i].active == 0 || g_map_overlay_state.icons[i].texture_id == 0 ||
                        (g_map_overlay_state.icons[i].flags & 3)) {
                        goto next_outer_icon;
                    }
                    j = i + 1;
                    for (; !(g_map_overlay_state.icons[j].flags & 4); j++) {
                        inner_offset = j * sizeof(MapIcon_205E70);
                        pan_x = icon_bounds[j].x1 - icon_bounds[i].x0;
                        if (pan_x <= 0)
                            continue;
                        map_extent = icon_bounds[i].x1 - icon_bounds[j].x0;
                        if (map_extent <= 0)
                            continue;
                        pan_y = icon_bounds[j].y1 - icon_bounds[i].y0;
                        if (pan_y <= 0)
                            continue;
                        oy1 = icon_bounds[i].y1 - icon_bounds[j].y0;
                        if (oy1 <= 0)
                            continue;
                        icon = (MapIcon_205E70 *)(inner_offset + (s32)g_map_overlay_state.icons);
                        if (icon->active == 0 || icon->texture_id == 0 || (icon->flags & 3)) {
                            continue;
                        }
                        ax = 0;
                        ay = 0;
                        bx = 0;
                        by = 0;
                        if (pan_x <= map_extent && pan_x <= pan_y && pan_x <= oy1) {
                            ax = pan_x >> 1;
                            bx = ax - pan_x;
                        } else if (map_extent <= pan_y && map_extent <= oy1) {
                            bx = map_extent >> 1;
                            ax = bx - map_extent;
                        } else if (pan_y <= oy1) {
                            ay = pan_y >> 1;
                            by = ay - pan_y;
                        } else {
                            by = oy1 >> 1;
                            ay = by - oy1;
                        }
                        icon_bounds[i].x0 += ax;
                        icon_bounds[i].x1 += ax;
                        icon_bounds[i].y0 += ay;
                        icon_bounds[i].y1 += ay;
                        icon_bounds[j].x0 += bx;
                        icon_bounds[j].x1 += bx;
                        icon_bounds[j].y0 += by;
                        icon_bounds[j].y1 += by;
                    }
                next_outer_icon:
                    i++;
                } while (!(g_map_overlay_state.icons[i + 1].flags & 4));
        }

        {
            s32 i;
            FontWindow_205E70 text_window;
            u8 label_buffer[0x50];

            i = 0;
            if (!(g_map_overlay_state.icons[0].flags & 4)) {
                do {
                    if (g_map_overlay_state.icons[i].active != 0 && !(g_map_overlay_state.icons[i].flags & 1)) {
                        id = g_map_overlay_state.icons[i].texture_id;
                        sprite_word = g_map_overlay_state.icons[i].frame_index;
                        if (id != 0) {
                            if (g_map_overlay_state.icons[i].flags & 0x40) {
                                AppendScreenRectPacket(
                                    icon_bounds[i].x0 - 0x20, icon_bounds[i].y0 - 0x20,
                                    icon_bounds[i].x1 + 0x20, icon_bounds[i].y1 + 0x20, 0x80000000, 1);
                            }
                            if (g_map_highlight_active && i == g_map_highlight_index) {
                                icon_bounds[i].x0 = g_map_icon_x0;
                                icon_bounds[i].y0 = g_map_icon_y0;
                                icon_bounds[i].x1 = g_map_icon_x1;
                                icon_bounds[i].y1 = g_map_icon_y1;
                            }
                            if (g_map_overlay_state.icons[i].flags & 0x200) {
                                s = g_map_overlay_state.zoom[g_map_overlay_state.selected_map];
                            } else {
                                s = icon_scale;
                            }
                            if (g_map_overlay_state.icons[i].flags & 0x100) {
                                angle = g_map_overlay_state.icons[i].angle;
                                texture_width = 0x20;
                                sprite_height = s * 256.0f;
                                sprite_width = sprite_height;
                                if (g_map_overlay_state.icons[i].flags & 0x400) {
                                    angle = FastAddRotations(angle, 1.5707964f);
                                    texture_width = 0x40;
                                    sprite_width = s * g_map_sprite_width_scale_b;
                                    sprite_height = s * g_map_sprite_height_scale_b;
                                    if (g_map_id_flags[g_map_overlay_state.icons[i].id].flags & 2) {
                                        sprite_word++;
                                    }
                                }
                                if (g_map_overlay_state.icons[i].flags & 0x800) {
                                    angle = FastAddRotations(angle, 1.5707964f);
                                    texture_width = 0x40;
                                    sprite_width = s * g_map_sprite_width_scale_a;
                                    sprite_height = s * g_map_sprite_height_scale_a;
                                    if (g_map_id_flags[g_map_overlay_state.icons[i].id].flags & 2) {
                                        sprite_word++;
                                    }
                                }
                                if (g_map_overlay_state.icons[i].flags & 0x1000) {
                                    angle = FastAddRotations(angle, 1.5707964f);
                                    sprite_width = s * g_map_sprite_width_scale_c;
                                    sprite_height = s * g_map_sprite_height_scale_c;
                                }
                                center_x = (f32)(icon_bounds[i].x0 + icon_bounds[i].x1) * 0.5f;
                                center_y = (f32)(icon_bounds[i].y0 + icon_bounds[i].y1) * 0.5f;
                                DrawRotatedSprite(center_x, center_y, sprite_width, sprite_height,
                                                    angle, texture_width, 0x20,
                                                    GetFrameTexture(GetIconFrame(
                                                        id, sprite_word)));
                            } else {
                                u32 tint = 0x7f7f7f;
                                if (g_map_overlay_state.icons[i].texture_id == 0xE99A &&
                                    (u32)((u16)g_map_overlay_state.icons[i].frame_index - 11) < 4) {
                                    int k = 0;
                                    s32 *colors = g_map_color_table;
                                    /* Entering at the test keeps the loop out of loop.c
                                     * (multiple entry points) and unpeeled. */
                                    goto test_tint;
                                    while (1) {
                                        k++;
                                    test_tint:
                                        if (colors[k * 2] == -1) {
                                            goto tint_done;
                                        }
                                        if (colors[k * 2] == g_map_overlay_state.icons[i].frame_index) {
                                            tint = g_map_tint_table[k * 2];
                                            goto tint_done;
                                        }
                                    }
                                tint_done:
                                    DrawHudSpriteSubpixel(GetIconFrame(id, sprite_word),
                                        icon_bounds[i].x0 - 8, icon_bounds[i].y0 - 8,
                                        icon_bounds[i].x1 - icon_bounds[i].x0 + 8,
                                        icon_bounds[i].y1 - icon_bounds[i].y0 + 8, 0x80, 0);
                                }
                                DrawHudSpriteSubpixel(GetIconFrame(id, sprite_word),
                                    icon_bounds[i].x0, icon_bounds[i].y0,
                                    icon_bounds[i].x1 - icon_bounds[i].x0,
                                    icon_bounds[i].y1 - icon_bounds[i].y0, 0x80, tint);
                            }
                            if (g_map_overlay_state.icons[i].flags & 0x10) {
                                label_width = g_map_overlay_state.icons[i].label_width;
                                label_offset_x = g_map_overlay_state.icons[i].label_offset_x;
                                label_height = g_map_overlay_state.icons[i].label_height;
                                label_offset_y = g_map_overlay_state.icons[i].label_offset_y;
                                if (label_offset_x == 0) {
                                    label_x = ((icon_bounds[i].x0 + icon_bounds[i].x1) >> 5) -
                                              label_width / 2;
                                } else {
                                    if (label_offset_x > 0) {
                                        label_x = (icon_bounds[i].x1 >> 4) - label_width / 2 + label_offset_x;
                                    } else {
                                        label_x = (icon_bounds[i].x0 >> 4) - label_width / 2 + label_offset_x;
                                    }
                                }
                                if (label_offset_y == 0) {
                                    label_y = ((icon_bounds[i].y0 + icon_bounds[i].y1) >> 5) -
                                              label_height / 2;
                                } else {
                                    if (label_offset_y > 0) {
                                        label_y = (icon_bounds[i].y1 >> 4) - label_height / 2 + label_offset_y;
                                    } else {
                                        label_y = (icon_bounds[i].y0 >> 4) - label_height / 2 + label_offset_y;
                                    }
                                }
                                AppendScreenRectPacket(label_x - 2, label_y, label_x + label_width + 2,
                                              label_y + label_height + 8, 0x40000000, 0);
                                text_format_localized_amount(i, label_buffer);
                                memset(&text_window, 0, sizeof(text_window));
                                text_window.s[1] = label_y + label_height;
                                text_window.s[3] = label_x + label_width;
                                text_window.s[4] = label_x + label_width / 2;
                                text_window.s[5] = label_y + 4;
                                text_window.s[8] = 0xF;
                                text_window.s[9] = 0x11;
                                text_window.s[0] = label_y;
                                text_window.s[2] = label_x;
                                text_draw_window_medium(&text_window, 0x80FFA888, label_buffer, -1);
                            }
                        }
                    }
                    i++;
                } while (!(g_map_overlay_state.icons[i].flags & 4));
            }
        }
    }

    {
        MapOverlayState_205E70 *m = &g_map_overlay_state;

        if (g_current_map_index == m->selected_map) {
            s32 image_index;
            f32 s;
            f32 angle;
            s32 flip;
            f32 pos[2];

            image_index = GetIconFrame(0xE99A, 5);
            s = ((m->zoom[m->selected_map] * 4.0f + 10.0f) * 0.75f) / 13.0f;
            angle = g_hero_state.angle;
            flip = g_hero_state.mode == 0xF;
            if (flip) {
                angle = FastAddRotations(angle, 1.5707964f);
            }
            if (g_current_map_index == 20 && g_map_mode == 2)
                angle = 3.1415927f;
            else if (moby_get_current_variant_index() >= 0 && g_current_map_index == 7)
                angle = g_map_variant_angles[moby_get_current_variant_index()];
            if (!GetSpecialMapCoordinates(g_hero_state.x, g_hero_state.y,
                               &pos[0], &pos[1], g_current_map_index))
                map_convert_world_to_map_position(g_hero_state.x, g_hero_state.y,
                              &pos[0], &pos[1], g_current_map_index);
            pos[0] = (f32)rx0 + pos[0] * (f32)(rx1 - rx0);
            pos[1] = (f32)ry0 + pos[1] * (f32)(ry1 - ry0);
            {
                f32 sz = s * 256.0f;

                DrawRotatedSprite(pos[0], pos[1], sz, sz, angle, 0x40, 0x40,
                                    GetFrameTexture(image_index));
            }
        }
    }
    gfx_set_scissor_clamped(0, g_screen_width.width - 1, 0, g_screen_width.height - 1);
    if (paging) DoGifPaging();
}
