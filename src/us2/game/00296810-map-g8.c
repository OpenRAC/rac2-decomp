/* func_US2_00296810: USA v2.00's map overlay renderer, the C of func_00295F60
 * (src/game/00295F60-map-g8.c, same flags) where the no-map message becomes
 * localized text (func_00288FB8(0x3163)) printed in a font window, the label box
 * is padded and its window flags gain 0x10, and the player marker also calls
 * func_US2_00298AA8 when D_001A7AF8[5] is set.
 *
 * Retail gives the no-map window, the label window and the marker position one
 * shared stack slot, so each lives in its own block. gcc 2.95 moves an
 * address-taken block local one binding level out after each expression
 * statement, so the no-map window sits one block below its if: that frees its
 * slot before the icons are drawn.
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


extern struct TagPtr_205E70 D_001B22A8 MACRO_ADDR;
extern struct ScreenOffsets_205E70 D_001A7340 MACRO_ADDR;
extern MapOverlayState_205E70 D_001C4FA0 NOT_SDA;
extern MapPlayerState_205E70 D_00189E20 NOT_SDA;
extern MapTextureTables_205E70 D_001B1870 MACRO_ADDR;
extern MapIdFlags_205E70 D_00139A34[] NOT_SDA;
extern s32 D_001A79F0 MACRO_ADDR;
extern s16 D_US2_001A95F8 __attribute__((sda));
extern s16 D_US2_001A95FC MACRO_ADDR;
extern s16 D_US2_001A9600 __attribute__((sda));
extern s16 D_US2_001A9604 __attribute__((sda));
extern u8 D_001A7AF8[] MACRO_ADDR;
extern s32 D_001A95F0 __attribute__((sda));
extern s32 D_001A960C __attribute__((sda));
extern s32 D_001A9614 __attribute__((sda));
extern s32 D_001A9610 __attribute__((sda));
extern s32 D_001A9618 __attribute__((sda));
extern s32 D_001C4F40 NOT_SDA;
extern s32 D_001A961C __attribute__((sda));
extern s32 D_001A9620 __attribute__((sda));
extern s32 D_001A9624 __attribute__((sda));
extern s32 D_001A9628 __attribute__((sda));
extern s32 D_001A962C __attribute__((sda));
extern s32 D_001A9630 __attribute__((sda));
extern s32 D_001A9638[10] __attribute__((sda));
extern u32 D_001A963C[] NOT_SDA;
extern f32 D_001A9660[4] __attribute__((sda));
extern f32 D_001A95D8 __attribute__((sda));
extern f32 D_001A95DC __attribute__((sda));
extern f32 D_001A95E0 __attribute__((sda));
extern f32 D_001A95E4 __attribute__((sda));
extern f32 D_001A95E8 __attribute__((sda));
extern f32 D_001A95EC __attribute__((sda));
extern void func_0027C540(s32);
extern void func_0027C660(void);
extern void func_002FC560(s32,s64);
extern void func_002FC620(s32,s32,s32,s32);
extern s32 func_0028E588(s32,s32);
extern u64 func_0028E640(s32);
extern void func_0028FC48(s32,s32,s32,s32,u64,s32);
extern f32 func_00283B98(f32,f32);
extern void func_0028F410(f32,f32,f32,f32,f32,s32,s32,u64);
extern void func_0028F078(s32,s32,s32,s32,s32,s32,s32);
extern void func_00297E00(s32,void *);
extern void *func_00115484(void *,s32,u32);
extern void func_00280200(void *,u64,void *,s32);
extern void func_00280190(FontWindow_205E70 *,u64,char *,s32);
extern char *func_00288FB8(s32);
extern void func_US2_00298AA8(f32,f32,f32,f32,f32);
extern s32 func_00297218(f32,f32,f32 *,f32 *,s32);
extern void func_00297FE8(f32,f32,f32 *,f32 *,s32);
extern s32 func_003005A0(void);

/* UNK_NoMapAvailable */
void func_US2_00296810(s32 paging, s32 set_clip) {
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

    if (D_001A95F0) return;
    if (D_001C4FA0.enabled == 0 || D_001C4FA0.selected_map >= 21) {
        {
            FontWindow_205E70 text_window;
            s16 window_fields[12];
            char *text = func_00288FB8(0x3163);

            if (paging) func_0027C540(0);
            func_00115484(window_fields, 0, sizeof(window_fields));
            window_fields[1] = 400;
            window_fields[2] = D_US2_001A9600;
            window_fields[3] = D_US2_001A9604;
            window_fields[4] = D_US2_001A95F8;
            window_fields[5] = D_US2_001A95FC;
            window_fields[8] = 16;
            text_window = *(FontWindow_205E70 *)window_fields;
            func_00280190(&text_window, 0x80F0F0F0, text, -1);
            if (paging) func_0027C660();
        }
        return;
    }
    if (D_001C4FA0.selected_map < 0) {
        return;
    }

    if (paging) func_0027C540(0);
    rx0 = 0x1000;
    ry0 = 0x800;
    mirror_sign = 1;
    {
        s32 selected = D_001C4FA0.selected_map;
        s32 ox = D_001C4FA0.offset_x[selected] >> 15;
        s32 oy = D_001C4FA0.offset_y[selected] >> 15;
        zoom = D_001C4FA0.zoom[selected];
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

    func_002FC560(8, 0);
    func_002FC560(0x47, 0);
    if (set_clip) func_002FC620(D_001A960C, D_001A9614, D_001A9610, D_001A9618);
    D_001B22A8.p->tag = 0x10000005;
    D_001B22A8.p->addr = 0;
    D_001B22A8.p->vif0 = 0;
    D_001B22A8.p->vif1 = 0x50000005;
    D_001B22A8.p++;
    background_tex0 =
        func_0028E640(func_0028E588(0xE999, D_001C4FA0.selected_map));
    packet_words = (u64 *)D_001B22A8.p;
    packet_words[0] = 0x7400000000008001;
    packet_words[1] = 0x5353106;
    packet_words[2] = background_tex0;
    packet_words[3] = 0x156;
    packet_words[4] = 0x80808080;
    packet_words[5] = 0;
    packet_words[6] = ((x0 + D_001A7340.x) - 8) | ((u64)((y0 + D_001A7340.y) - 8) << 16) |
                      ((u64)D_001C4FA0.z << 32);
    packet_words[7] = u | ((u64)v << 16);
    packet_words[8] = ((x1 + D_001A7340.x) - 8) | ((u64)((y1 + D_001A7340.y) - 8) << 16) |
                      ((u64)D_001C4FA0.z << 32);
    packet_words[9] = 0;
    D_001B22A8.p = (struct DmaTag_205E70 *)((u8 *)D_001B22A8.p + 0x50);
    func_002FC560(8, 5);
    func_002FC560(0x47, 0x60B);

    palette_block = (background_tex0 >> 37) & 0x3FFF;
    D_001B22A8.p->tag = 0x10000005;
    D_001B22A8.p->addr = 0;
    D_001B22A8.p->vif0 = 0;
    D_001B22A8.p->vif1 = 0x50000005;
    map_tex0 = (u64)((D_001C4FA0.texture_address >> 8) | (8 << 14) | (0x13 << 20) | (9 << 26)) |
               ((u64)9 << 30) | ((u64)1 << 34) | ((u64)palette_block << 37) |
               ((long)0x8000000000000000ULL);
    tag = D_001B22A8.p;
    D_001B22A8.p = tag + 1;
    packet_words = (u64 *)(tag + 1);
    packet_words[0] = 0x7400000000008001;
    packet_words[1] = 0x5353106;
    packet_words[2] = map_tex0;
    packet_words[3] = 0x156;
    packet_words[4] = 0x80808080;
    packet_words[5] = 0;
    packet_words[6] = ((rx0 + D_001A7340.x) - 8) | ((u64)((ry0 + D_001A7340.y) - 8) << 16) |
                      ((u64)D_001C4FA0.z << 32);
    packet_words[7] = 0x20002000;
    packet_words[8] = ((rx1 + D_001A7340.x) - 8) | ((u64)((ry1 + D_001A7340.y) - 8) << 16) |
                      ((u64)D_001C4FA0.z << 32);
    packet_words[9] = 0;
    D_001B22A8.p = (struct DmaTag_205E70 *)((u8 *)D_001B22A8.p + 0x50);
    func_002FC560(0x47, 0x360B);

    if (D_001C4FA0.show_markers != 0 && D_001C4FA0.marks_enabled != 0) {
        dx = rx1 - rx0;
        dy = ry1 - ry0;
        highlighted_cell = D_001C4FA0.marks;
        for (i = 0; i < 8; i++, highlighted_cell++) {
            cell = highlighted_cell->cell;
            if (cell >= 0) {
                cell_x = cell % 16;
                cell_y = cell / 16;
                func_0028FC48(rx0 + cell_x * dx / 16, ry0 + cell_y * dy / 16,
                                          rx0 + (cell_x + 1) * dx / 16,
                                          ry0 + (cell_y + 1) * dy / 16, 0x20000000, 1);
            }
        }
    }

    if (D_001C4FA0.icons != 0) {
        icon_bounds = ((MapIconBounds_205E70 *)0x70000000);
        icon_scale = (D_001C4FA0.zoom[D_001C4FA0.selected_map] * 2.0f + 5.0f) / 13.0f;
        if (!(D_001C4FA0.icons[0].flags & 4)) {
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
                if (D_001C4FA0.icons[i].active != 0 &&
                    (texture_id = D_001C4FA0.icons[i].texture_id) != 0 &&
                    !(D_001C4FA0.icons[i].flags & 1)) {
                    icon_size_multiplier = 1.0f;
                    if (D_001C4FA0.icons[i].flags & 0x80) {
                        icon_size_multiplier = 1.5f;
                    }
                    image_index = func_0028E588(texture_id,
                                                                   D_001C4FA0.icons[i].frame_index);
                    icon_center_x = (f32)rx0 + D_001C4FA0.icons[i].x * (f32)(rx1 - rx0);
                    icon_center_y = (f32)ry0 + D_001C4FA0.icons[i].y * (f32)(ry1 - ry0);
                    texture_info =
                        &D_001B1870.textures[D_001B1870.references[image_index].image_index];
                    if (D_001C4FA0.icons[i].flags & 0x200) {
                        s = D_001C4FA0.zoom[D_001C4FA0.selected_map];
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
            } while (!(D_001C4FA0.icons[i].flags & 4));
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
            if (!(D_001C4FA0.icons[1].flags & 4))
                do {
                    if (D_001C4FA0.icons[i].active == 0 || D_001C4FA0.icons[i].texture_id == 0 ||
                        (D_001C4FA0.icons[i].flags & 3)) {
                        goto next_outer_icon;
                    }
                    j = i + 1;
                    for (; !(D_001C4FA0.icons[j].flags & 4); j++) {
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
                        icon = (MapIcon_205E70 *)(inner_offset + (s32)D_001C4FA0.icons);
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
                } while (!(D_001C4FA0.icons[i + 1].flags & 4));
        }

        {
            s32 i;

            i = 0;
            if (!(D_001C4FA0.icons[0].flags & 4)) {
                do {
                    if (D_001C4FA0.icons[i].active != 0 && !(D_001C4FA0.icons[i].flags & 1)) {
                        id = D_001C4FA0.icons[i].texture_id;
                        sprite_word = D_001C4FA0.icons[i].frame_index;
                        if (id != 0) {
                            if (D_001C4FA0.icons[i].flags & 0x40) {
                                func_0028FC48(
                                    icon_bounds[i].x0 - 0x20, icon_bounds[i].y0 - 0x20,
                                    icon_bounds[i].x1 + 0x20, icon_bounds[i].y1 + 0x20, 0x80000000, 1);
                            }
                            if (D_001A961C && i == D_001A9620) {
                                icon_bounds[i].x0 = D_001A9624;
                                icon_bounds[i].y0 = D_001A9628;
                                icon_bounds[i].x1 = D_001A962C;
                                icon_bounds[i].y1 = D_001A9630;
                            }
                            if (D_001C4FA0.icons[i].flags & 0x200) {
                                s = D_001C4FA0.zoom[D_001C4FA0.selected_map];
                            } else {
                                s = icon_scale;
                            }
                            if (D_001C4FA0.icons[i].flags & 0x100) {
                                angle = D_001C4FA0.icons[i].angle;
                                texture_width = 0x20;
                                sprite_height = s * 256.0f;
                                sprite_width = sprite_height;
                                if (D_001C4FA0.icons[i].flags & 0x400) {
                                    angle = func_00283B98(angle, 1.5707964f);
                                    texture_width = 0x40;
                                    sprite_width = s * D_001A95E0;
                                    sprite_height = s * D_001A95E4;
                                    if (D_00139A34[D_001C4FA0.icons[i].id].flags & 2) {
                                        sprite_word++;
                                    }
                                }
                                if (D_001C4FA0.icons[i].flags & 0x800) {
                                    angle = func_00283B98(angle, 1.5707964f);
                                    texture_width = 0x40;
                                    sprite_width = s * D_001A95D8;
                                    sprite_height = s * D_001A95DC;
                                    if (D_00139A34[D_001C4FA0.icons[i].id].flags & 2) {
                                        sprite_word++;
                                    }
                                }
                                if (D_001C4FA0.icons[i].flags & 0x1000) {
                                    angle = func_00283B98(angle, 1.5707964f);
                                    sprite_width = s * D_001A95E8;
                                    sprite_height = s * D_001A95EC;
                                }
                                center_x = (f32)(icon_bounds[i].x0 + icon_bounds[i].x1) * 0.5f;
                                center_y = (f32)(icon_bounds[i].y0 + icon_bounds[i].y1) * 0.5f;
                                func_0028F410(center_x, center_y, sprite_width, sprite_height,
                                                    angle, texture_width, 0x20,
                                                    func_0028E640(func_0028E588(
                                                        id, sprite_word)));
                            } else {
                                u32 tint = 0x7f7f7f;
                                if (D_001C4FA0.icons[i].texture_id == 0xE99A &&
                                    (u32)((u16)D_001C4FA0.icons[i].frame_index - 11) < 4) {
                                    int k = 0;
                                    s32 *colors = D_001A9638;
                                    /* Entering at the test keeps the loop out of loop.c
                                     * (multiple entry points) and unpeeled. */
                                    goto test_tint;
                                    while (1) {
                                        k++;
                                    test_tint:
                                        if (colors[k * 2] == -1) {
                                            goto tint_done;
                                        }
                                        if (colors[k * 2] == D_001C4FA0.icons[i].frame_index) {
                                            tint = D_001A963C[k * 2];
                                            goto tint_done;
                                        }
                                    }
                                tint_done:
                                    func_0028F078(func_0028E588(id, sprite_word),
                                        icon_bounds[i].x0 - 8, icon_bounds[i].y0 - 8,
                                        icon_bounds[i].x1 - icon_bounds[i].x0 + 8,
                                        icon_bounds[i].y1 - icon_bounds[i].y0 + 8, 0x80, 0);
                                }
                                func_0028F078(func_0028E588(id, sprite_word),
                                    icon_bounds[i].x0, icon_bounds[i].y0,
                                    icon_bounds[i].x1 - icon_bounds[i].x0,
                                    icon_bounds[i].y1 - icon_bounds[i].y0, 0x80, tint);
                            }
                            if (D_001C4FA0.icons[i].flags & 0x10) {
                                u8 label_buffer[0x50];
                                FontWindow_205E70 text_window;

                                label_width = D_001C4FA0.icons[i].label_width;
                                label_offset_x = D_001C4FA0.icons[i].label_offset_x;
                                label_height = D_001C4FA0.icons[i].label_height;
                                label_offset_y = D_001C4FA0.icons[i].label_offset_y;
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
                                func_0028FC48(label_x - 2, label_y, label_x + label_width + 2,
                                              label_y + label_height + 8, 0x40000000, 0);
                                func_00297E00(i, &label_buffer);
                                func_00115484(&text_window, 0, sizeof(text_window));
                                text_window.s[1] = label_y + label_height;
                                text_window.s[3] = label_x + label_width;
                                text_window.s[4] = label_x + label_width / 2;
                                text_window.s[5] = label_y + 4;
                                text_window.s[8] = 0xF;
                                text_window.s[9] = 0x11;
                                text_window.s[0] = label_y;
                                text_window.s[2] = label_x;
                                func_00280200(&text_window, 0x80FFA888, &label_buffer, -1);
                            }
                        }
                    }
                    i++;
                } while (!(D_001C4FA0.icons[i].flags & 4));
            }
        }
    }

    {
        MapOverlayState_205E70 *m = &D_001C4FA0;

        if (D_001A79F0 == m->selected_map) {
            s32 image_index;
            f32 s;
            f32 angle;
            s32 flip;
            f32 pos[2];

            image_index = func_0028E588(0xE99A, 5);
            s = ((m->zoom[m->selected_map] * 4.0f + 10.0f) * 0.75f) / 13.0f;
            angle = D_00189E20.angle;
            flip = D_00189E20.mode == 0xF;
            if (flip) {
                angle = func_00283B98(angle, 1.5707964f);
            }
            if (D_001A79F0 == 20 && D_001C4F40 == 2)
                angle = 3.1415927f;
            else if (func_003005A0() >= 0 && D_001A79F0 == 7)
                angle = D_001A9660[func_003005A0()];
            if (!func_00297218(D_00189E20.x, D_00189E20.y,
                               &pos[0], &pos[1], D_001A79F0))
                func_00297FE8(D_00189E20.x, D_00189E20.y,
                              &pos[0], &pos[1], D_001A79F0);
            pos[0] = (f32)rx0 + pos[0] * (f32)(rx1 - rx0);
            pos[1] = (f32)ry0 + pos[1] * (f32)(ry1 - ry0);
            {
                f32 sz = s * 256.0f;

                func_0028F410(pos[0], pos[1], sz, sz, angle, 0x40, 0x40,
                                    func_0028E640(image_index));
            }
            if (D_001A7AF8[5]) {
                func_US2_00298AA8((f32)rx0, (f32)rx1, (f32)ry0, (f32)ry1, s);
            }
        }
    }
    func_002FC620(0, D_001A7340.width - 1, 0, D_001A7340.height - 1);
    if (paging) func_0027C660();
}
