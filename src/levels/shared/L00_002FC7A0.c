#include "common.h"

typedef u32 u128_04340 __attribute__((mode(TI), aligned(16)));
typedef struct ResidentRenderTextureDefinition_04340 {
    s32 unk0; /* unused here; a word, so the record is 4-byte aligned */
    s16 width;
    s16 height;
    s16 draw_control_count;
    s16 clut_block_offset; /* 0x0A: TEX0.CBP (bit 37) after adding the base */
    s16 mip_block_offset_0;
    s16 mip_block_offset_1;
} ResidentRenderTextureDefinition_04340;
typedef union MaterialMap_04340 {
    u128_04340 q;
    u8 b[16];
} MaterialMap_04340;
typedef struct {
    s16 width;
    s16 height;
    s16 draw_control_count;
    s16 texture_block_offset;
    s16 palette_block_offset;
    s16 mip_block_offset_0;
    s16 mip_block_offset_1;
    s16 mip_block_offset_2;
} ShrubMipTextureDefinition_04340;
typedef struct {
    s32 draw_high;
    s32 draw_shift;
    u8 pad8[8];
    s32 material_base;
    s32 material_shift;
    u8 pad18[8];
    s32 material_index;
    u8 pad24[0x1C];
} ShrubRenderPacket_04340;
typedef struct {
    u8 pad0[0x10];
    union {
        u64 d;
        s32 w[2];
    } tex1;
    u64 payload18;
    union {
        u64 d;
        s32 w[2];
    } tex0;
    u64 payload28;
    u64 miptbp1;
    u64 payload38;
} ShrubMipPacket_04340;
typedef struct {
    s32 count;
    s32 prefix_record_count;
} ShrubRenderGroupHeader_04340;
typedef struct {
    u8 pad0[0x10];
    ShrubRenderGroupHeader_04340 group_header;
} ShrubRenderGroup_04340;
typedef struct {
    ShrubRenderGroup_04340 *group;
    s32 pad4;
} ShrubRenderGroupReference_04340;
typedef struct {
    u8 pad0[0x10];
    f32 scale;
    u8 pad14[2];
    u16 instance_count;
    void *first_instance;
    ShrubMipPacket_04340 *mip_packet;
    u8 pad20[6];
    u16 class_slot;
    s16 group_count;
    u8 pad2A[2];
    s32 packed_geometry;
    u8 pad30[0x10];
    ShrubRenderGroupReference_04340 groups[1];
} ShrubRenderClass_04340;
extern ShrubRenderClass_04340 *D_L00_0021EA20[64];
extern s16 D_L00_0021EB20[64];
extern u8 D_L00_0021EBA0[0x400];
extern s32 D_L00_002203A0[64];
extern MaterialMap_04340 D_L00_002209A0[64];
extern s32 D_L00_001B23F0 __attribute__((sda));
/* Keep the absolute allocation-base loads in their measured form in this G0 unit. */
extern s32 D_001A72F4 __attribute__((sda));
extern u64 D_L00_001C91C0[0x30];
extern s32 FloatToInt(f32);
extern s32 log2dim(s32);
extern char D_L00_001A95A0[];
extern double __extendsfdf2(float);
extern void STUB_printf(const char *, ...);

#define MACRO_ADDR __attribute__((section(".sdata")))

typedef unsigned int Rac2Native_3e18d05650488ad4_FallbackU32;

typedef struct Slot0820eb11 {
    short          f00;    /* +0x00 */
    short          f02;    /* +0x02 */
    unsigned char  f04;    /* +0x04 */
    char           pad05[7];
    unsigned char *f0C;    /* +0x0C */
    int            f10;    /* +0x10 */
    int            f14;    /* +0x14 */
    int            f18;    /* +0x18 */
    int            f1C;    /* +0x1C */
    char           pad20[32];
} Slot0820eb11;

typedef struct Mid {
    char           pad00[0x1C];
    char          *f1C;    /* +0x1C */
} Mid;

typedef struct Ctx {
    char           pad00[0x24];
    Mid           *f24;    /* +0x24 */
    char           pad28[0x28];
    int            f50;    /* +0x50 */
} Ctx;

typedef struct LvlSlotNode {
    char                 pad00[0x1C];
    struct LvlSlotNode  *next;   /* +0x1C */
} LvlSlotNode;

typedef struct LvlSlotCtx {
    char          pad00[0x50];
    LvlSlotNode  *head;          /* +0x50 */
} LvlSlotCtx;

extern void load_start_disc_read(int value, char *target);

extern void snd_pump_music_and_disc_read(int value);

extern int D_L00_001BCAC0[];

extern int g_copy_setup_data[];

extern Rac2Native_3e18d05650488ad4_FallbackU32 g_save_menu_flags;

extern int D_001A7420_1;

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424_1;

extern int D_001A7420_2;

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424_2;

extern int D_001A7420_3;

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424_3;

extern int D_001A7420_4;

extern int D_L00_001A904C_1 __attribute__((sda));

extern void menu_set_screen_value_restart_four_fades(int value, int argument);

extern void object_set_field_first(int value, int argument);

extern void object_set_field_next(int value, int argument);

extern int D_L00_001A904C_2 __attribute__((sda));

extern void sub_object_get_value_first(int);

extern void sub_object_get_value_second(int);

extern void hud_update_subsystems(int);

extern void hud_item_bolt_draw(int);

extern int tab_menu_update(int a, int b);

extern void menu_set_screen_field_2bc(int value, int argument);

extern int D_L00_001A904C_7 __attribute__((sda));

extern int func_003387A0_1(int a, int b, int c);

extern int func_00338040_1(int a, int b, int c);

extern void level_clear_pending_pointer(int);

extern unsigned char *D_L05_001B2520 __attribute__((sda));

extern unsigned char *D_L05_001B2524 __attribute__((sda));

extern unsigned int D_L05_001B2048 __attribute__((sda));

extern unsigned int D_L05_001B2440 __attribute__((sda));

extern Slot0820eb11 D_L03_001D23C0[6];

extern unsigned char D_L03_001CA5C0[];

extern void func_00283658_1(char *a, char *b);

extern void func_002A3F10_3(char *a, int b, int c, char *d);

extern void func_00283788_5(char *a, char *b, char *c);

extern void func_00282D30_21(char *a, char *b, float c);

extern void func_00282CC0_24(char *a, char *b, char *c);

extern void gfx_flush_light_part_indices(unsigned long long);

extern void CreatePointLight(unsigned long long);

extern void func_002F0D00(void *, void *, int);

extern unsigned char D_L00_001C7040[] __attribute__((nosda));

extern int r1_D_0015EE84_m __asm__("r1_D_0015EE84") MACRO_ADDR;

extern int r1_D_L00_001C47B8[];

extern int r1_D_L00_001792B8[];

extern void list_menu_draw_centered_rows(int);

extern void item_grid_menu_draw(int);

extern void menu_screen_large_draw_parts(int);

extern void mission_screen_draw_parts(int);

extern void list_screen_draw(int);

extern void map_screen_draw(int);

extern void radial_menu_destroy(int);

extern void menu_screen_draw_parts(int);

extern void tab_menu_draw(int);

extern void item_menu_draw(int);

extern void menu_get_sub_object_value(int);

extern void two_toggle_b_draw(int);

extern void four_option_menu_draw(int);

extern void two_toggle_a_draw(int);

extern void single_toggle_a_draw(int);

extern void onoff_menu_draw_with_help(int);

extern void onoff_menu_draw(int);

extern int UpdateFourOptionMenuInput(int, int);

extern int menu_handle_page_input_a(int, int);

extern int menu_handle_page_input_b(int, int);

extern int screen_adjust_menu_update(int, int);

extern int onoff_menu_update(int, int);

extern int list_page_update(int, int);

extern int audio_menu_update(int, int);

extern int menu_update_two_part_flags_a(int, int);

extern int list_menu_update(int, int);

extern int list_menu_set_selection(int, int);

extern int func_0033FB98(int, int);

extern int popup_update_position(int, int);

extern int list_screen_layout(int, int);

extern int map_screen_update_layout(int, int);

extern int info_panel_update(int, int);

extern int grid_menu_update(int, int);

extern int item_menu_update(int, int);

extern int simple_page_update(int, int);

extern int menu_handle_page_input_c(int, int);

extern void mem_clear(char *, int, int);

/* Measured partial layouts; original type and game roles are unknown. */

/* RAC2 family 0820eb1123250c0b - 192 bytes, 2 placements.
 * Slot0820eb11 allocator: find the first free of six 64-byte slots, fill it in and
 * link it at the head of the context's list.
 */

                    /* 64 bytes */

/* Does nothing. Empty placeholder. */
void level_do_nothing_stub(void)
{
}


/* func_L00_002FC980 is defined in its own unit. */


/* Sends the same 64-bit value to two sound or graphics helpers one after the other. */
void level_send_value_to_two_helpers(unsigned long long argument)
{
    gfx_flush_light_part_indices(argument);
    CreatePointLight(argument);
}

/* walks the eight thirty-two-byte entries: for the ones with both flags set it
   hands the two halfword offsets of the entry to the shared routine and clears
   them */
void level_flush_table_entry_offsets(void)
{
    unsigned char *entry = D_L00_001C7040;
    int i;
    int base;
    short first;

    for (i = 0; i < 8; i++) {
        if (*(int *)(entry + 0x10) != 0 && *(int *)(entry + 0xC) != 0) {
            base = *(int *)(entry + 0xC);
            first = *(short *)(entry + 0x8);
            func_002F0D00((void *)(base + (first << 1)),
                          (void *)(base + (first << 1) + (*(short *)(entry + 0xA) << 1)), i);
            *(short *)(entry + 0x8) = 0;
            *(short *)(entry + 0xA) = 0;
        }
        entry += 0x30;
    }
}

/* func_L00_002FD480 is matched in its own unit, src/levels/shared/L00_002FD480-g8-qcopy.c (-O2 -G8 -ffunction-sections -frac2-qcopy). */


/* func_L00_002FE268 is defined in L00_002FC7A0-g8.c (-G8 small data). */


/* Object render class: three LOD tables of 16-byte records, then 80-byte GS texture packets. */
typedef struct ObjectRenderLod_FF6A8 {
    u8 *data; /* relative to the table until registered */
    u8 pad04[12];
} ObjectRenderLod_FF6A8;
typedef union ObjectRenderPacketWord_FF6A8 {
    u64 d;
    s32 w[2];
} ObjectRenderPacketWord_FF6A8;
typedef struct ObjectRenderPacket_FF6A8 {
    u64 tex0;
    u64 tag0;
    ObjectRenderPacketWord_FF6A8 tex1; /* K in w[0], MMIN in w[1] until registered */
    u64 tag1;
    u64 miptbp1;
    u64 tag2;
    ObjectRenderPacketWord_FF6A8 clamp; /* two fields until registered, then packed with the material index */
    u64 tag3;
    u64 tail[2];
} ObjectRenderPacket_FF6A8;
typedef struct ObjectRenderClass_FF6A8 {
    ObjectRenderLod_FF6A8 *lod_tables[3];
    u8 lod_counts[3];
    u8 packet_count;
    u8 pad10[4];
    f32 lod_distance_1;
    f32 lod_distance_2;
    ObjectRenderPacket_FF6A8 *packets;
    void *first_instance;
    u8 pad24[12];
    s32 unk30;
    u8 *unk34;
    u8 pad38[6];
    s16 instance_count;
    u8 pad40[6];
    u16 class_slot;
    f32 scale;
} ObjectRenderClass_FF6A8;
extern s32 D_L00_001B2510 __attribute__((sda));
extern ObjectRenderClass_FF6A8 *D_L00_00226700[];
extern s16 D_L00_00226900[];
extern u8 D_L00_00226A00[];
extern s32 D_L00_0022DA00[];
extern MaterialMap_04340 D_L00_0022DE00[];

/* Registers an object (TIE) render class: slot and id tables, its fixed distance threshold,
 * relocates its LOD tables and packets, copies its material map and rewrites each packet's
 * TEX0/TEX1/MIPTBP1/CLAMP words from its texture (or from the resident material templates).
 * Adapted from RAC1 src/game/loaders.c, register_object_render_class; RAC2 adds the LOD
 * distance defaults and relocates one more pointer (unk34).
 */
void RegisterObjectRenderClass(ObjectRenderClass_FF6A8 *render_class, ResidentRenderTextureDefinition_04340 *textures,
                       u128_04340 *material_map, s32 class_id)
{
    s32 lod, j;
    s32 packet_index;
    s32 fixed_threshold;
    s32 slot;
    u8 *slot_materials;
    ObjectRenderPacket_FF6A8 *packet, *packets;

    D_L00_00226900[D_L00_001B2510] = class_id;
    D_L00_00226A00[class_id] = D_L00_001B2510;
    D_L00_00226700[D_L00_001B2510] = render_class;
    render_class->class_slot = D_L00_001B2510;
    fixed_threshold = FloatToInt(render_class->scale * 1024.0f);
    slot = D_L00_001B2510;
    D_L00_001B2510 = slot + 1;
    D_L00_0022DA00[slot] = fixed_threshold;
    render_class->first_instance = 0;
    render_class->instance_count = 0;
    for (lod = 0; lod < 3; lod++) {
        if (render_class->lod_tables[lod]) {
            render_class->lod_tables[lod] =
                (ObjectRenderLod_FF6A8 *)((s32)render_class->lod_tables[lod] + (s32)render_class);
            for (j = 0; j < render_class->lod_counts[lod]; j++) {
                ObjectRenderLod_FF6A8 *table = render_class->lod_tables[lod];
                table[j].data = (u8 *)((s32)table[j].data + (s32)table);
            }
        }
    }
    if (render_class->lod_counts[1] == 0) render_class->lod_distance_1 = 8190.0f;
    if (render_class->lod_counts[2] == 0) render_class->lod_distance_2 = 8192.0f;
    render_class->unk34 = (u8 *)((s32)render_class->unk34 + (s32)render_class);
    packets = render_class->packets = (ObjectRenderPacket_FF6A8 *)((s32)render_class->packets + (s32)render_class);
    render_class->unk30 = 0;
    slot_materials = (u8 *)&D_L00_0022DE00[D_L00_00226A00[class_id]];
    qcopy(slot_materials, material_map);
    packet = packets;
    for (packet_index = 0; packet_index < render_class->packet_count; packet_index++, packet++) {
        s32 material_index, draw_high, draw_shift, clamp_low, clamp_shift;

        material_index = slot_materials[packet_index];
        draw_high = packet->tex1.w[0];
        draw_shift = packet->tex1.w[1];
        clamp_low = packet->clamp.w[0];
        clamp_shift = packet->clamp.w[1];
        if (textures) {
            ResidentRenderTextureDefinition_04340 *texture = &textures[material_index];
            s32 width_bits, width_units_64, width_units_128, width_log2, height_log2, gs_block_base;
            s32 mip_block_0, mip_block_1, draw_control_count;
            u64 tex0_word, tex1_word, mip_word, clamp_word;

            width_bits = (u16)texture->width << 16;
            width_units_64 = width_bits >> 22;
            width_units_128 = width_bits >> 23;
            if (width_units_64 <= 0) width_units_64 = 1;
            if (width_units_128 <= 0) width_units_128 = 1;
            width_log2 = log2dim(width_bits >> 16);
            height_log2 = log2dim(texture->height);
            gs_block_base = D_001A72F4 >> 8;
            mip_block_1 = texture->mip_block_offset_1 + gs_block_base;
            mip_block_0 = texture->mip_block_offset_0 + gs_block_base;
            width_bits = texture->clut_block_offset + gs_block_base;
            draw_control_count = texture->draw_control_count;
            tex0_word = (s64)((u64)(((s64)width_units_64 << 14) | ((s64)0x13 << 20) | ((s64)width_log2 << 26)) | ((u64)height_log2 << 30) | ((u64)1 << 34) | ((u64)width_bits << 37)) | ((s64)4 << 61);
            tex1_word = (s64)(((u64)(draw_control_count - 1) << 2) | ((u64)1 << 5) | ((u64)draw_shift << 6)) | ((s64)draw_high << 32);
            mip_word = (s64)(((u64)width_units_128 << 14) | ((u64)mip_block_0 << 20) | ((u64)1 << 34) | ((u64)mip_block_1 << 40)) | ((s64)1 << 54);
            clamp_word = (u64)clamp_low | ((u64)clamp_shift << 2) | ((u64)material_index << 24);
            packet->tex0 = tex0_word;
            packet->tex1.d = tex1_word;
            packet->miptbp1 = mip_word;
            packet->clamp.d = clamp_word;
        } else {
            u64 template_tex0 = D_L00_001C91C0[material_index * 3];
            u64 template_tex1 = D_L00_001C91C0[material_index * 3 + 1];
            u64 template_mip = D_L00_001C91C0[material_index * 3 + 2];
            u64 draw_bits = ((u64)draw_shift << 6) | 0x20;
            u64 template_draw_word = (template_tex1 & 0x1C) | draw_bits | ((u64)draw_high << 32);
            u64 template_clamp_word = (u64)clamp_low | ((u64)clamp_shift << 2) | ((u64)material_index << 24);
            packet->tex0 = template_tex0;
            packet->tex1.d = template_draw_word;
            packet->miptbp1 = template_mip;
            packet->clamp.d = template_clamp_word;
        }
    }
}

/* Registers the class, relocates its streams, and builds its GS texture packets.
 * Adapted from RAC1 src/game/loaders.c, register_shrub_render_class, which
 * credits Lombyte's GPL-3.0 src/rendering/register_shrub_render_class.c
 * (RAC1 US 0x203B08).
 */
void RegisterShrubRenderClass(ShrubRenderClass_04340 *render_class, ResidentRenderTextureDefinition_04340 *textures,
                   u128_04340 *material_map, ShrubMipTextureDefinition_04340 *mip_texture, s32 class_id) {
    s32 group_index;
    s32 index;
    s32 fixed_threshold;
    MaterialMap_04340 *slot_materials;
    ShrubMipPacket_04340 *packed_mip_packet;
    ShrubMipPacket_04340 *mip_packet;
    ShrubRenderGroupHeader_04340 *group_header;
    ShrubRenderPacket_04340 *packet;

    D_L00_0021EBA0[class_id] = D_L00_001B23F0;
    D_L00_0021EB20[D_L00_001B23F0] = class_id;
    D_L00_0021EA20[D_L00_001B23F0] = render_class;
    render_class->class_slot = D_L00_001B23F0;
    fixed_threshold = FloatToInt(render_class->scale * 1024.0f);
    D_L00_002203A0[D_L00_001B23F0] = fixed_threshold;
    D_L00_001B23F0++;
    render_class->first_instance = 0;
    render_class->instance_count = 0;
    if (render_class->packed_geometry != 0) {
        render_class->packed_geometry += (s32)render_class;
    }
    for (group_index = 0; group_index < render_class->group_count; group_index++) {
        render_class->groups[group_index].group =
            (ShrubRenderGroup_04340 *)(((s32)render_class->groups[group_index].group) + ((s32)render_class));
    }

    packed_mip_packet = render_class->mip_packet;
    if (packed_mip_packet != 0) {
        s32 material_base;
        s32 material_shift;

        mip_packet = (ShrubMipPacket_04340 *)((s32)packed_mip_packet + (s32)render_class);
        render_class->mip_packet = mip_packet;
        material_base = mip_packet->tex1.w[0];
        material_shift = mip_packet->tex1.w[1];
        if (mip_texture != 0) {
            s32 mip_width_units[4];
            s32 width_log2;
            s32 height_log2;
            s32 gs_block_base;
            u64 draw_word;
            s32 width;
            s32 level;
            s32 draw_control_count;
            s32 palette_block;
            s32 texture_block;
            s32 mip_block_0;
            s32 mip_block_1;
            s32 mip_block_2;

            width = mip_texture->width;
            for (level = 0; level < 4; level++) {
                mip_width_units[level] = width >> (level + 6);
                if (mip_width_units[level] <= 0) {
                    mip_width_units[level] = 1;
                }
            }

            width_log2 = log2dim(mip_texture->width);
            height_log2 = log2dim(mip_texture->height);
            draw_control_count = mip_texture->draw_control_count;
            texture_block = mip_texture->texture_block_offset;
            gs_block_base = D_001A72F4 >> 8;
            palette_block = mip_texture->palette_block_offset + gs_block_base;
            mip_block_0 = mip_texture->mip_block_offset_0 + gs_block_base;
            mip_block_1 = mip_texture->mip_block_offset_1 + gs_block_base;
            mip_block_2 = mip_texture->mip_block_offset_2 + gs_block_base;
            mip_packet->tex1.d = (s64)(((u64)(draw_control_count - 1) << 2) | ((u64)1 << 5) | ((u64)material_shift << 6)) | ((s64)material_base << 32);
            mip_packet->tex0.d = (s64)((u64)((s64)palette_block | ((s64)mip_width_units[0] << 14) | ((s64)0x13 << 20) | ((s64)width_log2 << 26)) | ((u64)height_log2 << 30) | ((u64)1 << 34) | ((u64)(texture_block + gs_block_base) << 37)) | ((s64)4 << 61);
            draw_word = (u64)mip_block_0 | ((u64)mip_width_units[1] << 14);
            draw_word |= (u64)mip_block_1 << 20;
            draw_word |= (u64)mip_width_units[2] << 34;
            draw_word |= (u64)mip_block_2 << 40;
            draw_word |= (u64)mip_width_units[3] << 54;
            mip_packet->miptbp1 = draw_word;
        } else {
            s32 template_index;
            s32 template_slot;
            u64 template_tex0;
            u64 template_tex1;
            u64 template_mip;
            u64 draw_bits;
            u64 template_draw_word;

            for (template_index = 0; D_L00_001C91C0[(template_index + 1) * 3] != 0; template_index++) {
            }
            template_tex0 = D_L00_001C91C0[template_index * 3];
            template_slot = template_index * 3;
            template_tex1 = D_L00_001C91C0[template_slot + 1];
            template_mip = D_L00_001C91C0[template_slot + 2];
            draw_bits = ((u64)material_shift << 6) | 0x20;
            template_draw_word = (template_tex1 & 0x1C) | draw_bits | ((u64)material_base << 32);
            mip_packet->tex0.d = template_tex0;
            mip_packet->miptbp1 = template_mip;
            mip_packet->tex1.d = template_draw_word;
        }
    }
    slot_materials = &D_L00_002209A0[D_L00_0021EBA0[class_id]];
    qcopy(slot_materials, material_map);
    for (group_index = 0; group_index < render_class->group_count; group_index++) {
        group_header = &render_class->groups[group_index].group->group_header;
        packet = (ShrubRenderPacket_04340 *)((((u8 *)group_header) + (group_header->prefix_record_count * 16)) + 0x10);
        for (index = 0; index < group_header->count; index++) {
            s32 material_index;
            s32 material_base;
            s32 draw_shift;
            s32 draw_high;
            s32 material_shift;

            material_index = slot_materials->b[packet->material_index];
            draw_high = packet->draw_high;
            draw_shift = packet->draw_shift;
            material_base = packet->material_base;
            material_shift = packet->material_shift;
            if (textures != 0) {
                ResidentRenderTextureDefinition_04340 *texture;
                s32 width_bits;
                s32 width_units_64;
                s32 width_units_128;
                s32 width_log2;
                s32 height_log2;
                s32 gs_block_base;
                s32 mip_block_1;
                s32 mip_block_0;
                s32 draw_control_count;
                u64 tex0_word;
                u64 tex1_word;
                u64 mip_word;
                u64 clamp_word;

                texture = &textures[material_index];
                width_bits = (u16)texture->width << 16;
                width_units_64 = width_bits >> 22;
                width_units_128 = width_bits >> 23;
                if (width_units_64 <= 0) {
                    width_units_64 = 1;
                }
                if (width_units_128 <= 0) {
                    width_units_128 = 1;
                }
                width_log2 = log2dim(width_bits >> 16);
                height_log2 = log2dim(texture->height);
                gs_block_base = D_001A72F4 >> 8;
                draw_control_count = texture->draw_control_count;
                width_bits = texture->clut_block_offset + gs_block_base;
                mip_block_0 = texture->mip_block_offset_0 + gs_block_base;
                mip_block_1 = texture->mip_block_offset_1 + gs_block_base;
                tex1_word = (s64)(((u64)(draw_control_count - 1) << 2) | ((u64)1 << 5) | ((u64)draw_shift << 6)) | ((s64)draw_high << 32);
                clamp_word = (u64)material_base | ((u64)material_shift << 2) | ((u64)material_index << 24);
                mip_word = (s64)(((u64)width_units_128 << 14) | ((u64)mip_block_0 << 20) | ((u64)1 << 34) | ((u64)mip_block_1 << 40)) | ((s64)1 << 54);
                tex0_word = (s64)((u64)(((s64)width_units_64 << 14) | ((s64)0x13 << 20) | ((s64)width_log2 << 26)) | ((u64)height_log2 << 30) | ((u64)1 << 34) | ((u64)width_bits << 37)) | ((s64)4 << 61);
                *(u64 *)&packet->draw_high = tex1_word;
                *(u64 *)&packet->material_base = clamp_word;
                *(u64 *)&packet->material_index = mip_word;
                *(u64 *)((u8 *)packet + 0x30) = tex0_word;
            } else {
                s32 template_index;
                u64 template_tex0;
                u64 template_tex1;
                u64 template_mip;
                u64 draw_bits;
                u64 template_draw_word;
                u64 template_clamp_word;

                template_tex0 = D_L00_001C91C0[material_index * 3];
                template_index = material_index * 3;
                template_tex1 = D_L00_001C91C0[template_index + 1];
                template_mip = D_L00_001C91C0[template_index + 2];
                draw_bits = ((u64)draw_shift << 6) | 0x20;
                template_draw_word = (template_tex1 & 0x1C) | draw_bits | ((u64)draw_high << 32);
                template_clamp_word = (u64)material_base | ((u64)material_shift << 2) | ((u64)material_index << 24);
                *(u64 *)&packet->draw_high = template_draw_word;
                *(u64 *)&packet->material_base = template_clamp_word;
                *(u64 *)&packet->material_index = template_mip;
                *(u64 *)((u8 *)packet + 0x30) = template_tex0;
            }
            packet++;
        }
    }
}


/* func_L00_00300090 is defined in L00_002FC7A0-00300090-g8.c (-G8 small data). */

/* func_L00_00300378 is defined in L00_002FC7A0-g8.c. */

/* Debug listing of moby class sizes: takes the 32-byte class records with a nonzero
   data offset as (class id, offset) pairs, turns each offset into the kilobytes up to
   the next one (the last up to end), sorts them largest first and prints each with
   "moby %d:      %.1fK\n". */
void PrintMobyClassSizes(int *records, int count, int end)
{
    struct { float id, weight; } values[512];
    int n = 0;
    int sorted;
    int i;

    for (i = 0; i < count; i++) {
        if (records[i * 8] != 0) {
            values[n].id = records[i * 8 + 1];
            values[n].weight = records[i * 8];
            n++;
        }
    }
    {
        int k;
        for (k = 0; k < n - 1; k++)
            values[k].weight = (values[k + 1].weight - values[k].weight) / 1024.0f;
    }
    values[n - 1].weight = ((float)end - values[n - 1].weight) / 1024.0f;
    do {
        int k;
        sorted = 1;
        for (k = 0; k < n - 1; k++) {
            if (values[k].weight < values[k + 1].weight) {
                float id = values[k].id, weight = values[k].weight;
                values[k].id = values[k + 1].id;
                values[k].weight = values[k + 1].weight;
                values[k + 1].id = id;
                values[k + 1].weight = weight;
                sorted = 0;
            }
        }
    } while (!sorted);
    {
        int j;
        for (j = 0; j < n; j++)
            STUB_printf(D_L00_001A95A0, FloatToInt(values[j].id), __extendsfdf2(values[j].weight));
    }
}

/* Does nothing. Empty placeholder. */
void level_do_nothing_stub_b(void)
{
}

/* func_L00_00300618 is matched in L00_002FC7A0-00300618-g8.c (built with -G8). */

/* func_L00_003032F0 is matched in L00_003032F0.c (built with -fno-gcse). */

extern unsigned char D_L00_001C9340[];

extern int vec_fast_helper_f(void *, void *, void *);

/* Walks the level's sixteen-byte table entries downwards and returns the one-based
   index of the first entry the shared test accepts, zero when none does. */
int level_find_first_accepted_entry(unsigned char *object)
{
    unsigned char *data = D_L00_001C9340;
    int i = *(int *)(data + 0xC) - 1;

    if (i >= 0) {
        unsigned char *table = data + 0x20;
        unsigned char *p = table + (i << 4);
        unsigned char *q = table + ((i << 4) + 0x20);

        do {
            if (vec_fast_helper_f(object, p, q) != 0)
                return i + 1;
            q -= 0x10;
            p -= 0x10;
            i--;
        } while (i >= 0);
    }
    return 0;
}

/* func_L00_00303418 lives in L00_00303418-sdata.c. */

/* func_L00_00303530 is defined in its own unit. */

/* func_L00_00303990 is defined in its own unit. */

/* Reads a record count from a per-level data root, indexes a fixed 332-byte-stride table with it, and when the int after position index is greater than the one at position index calls two helpers with the entry value added to a per-level base; returns 1. */
int load_queue_level_data_chunk(int index)
{
    int j = index + 1;
    int *d = D_L00_001BCAC0;
    int *b = g_copy_setup_data;
    int *t = (int *)((char *)b + 25416);
    int n = d[12] * 332;
    int hold = d[28];
    int j4 = j * 4;
    int cur = *(int *)((char *)t + (n + index * 4));
    int next = *(int *)((char *)t + (j4 + n));

    n = next - cur;
    if (n > 0) {
        load_start_disc_read(hold, (char *)(cur + b[6341]));
        snd_pump_music_and_disc_read(0);
    }
    return 1;
}

/* func_L00_00304AE8 is defined in L00_002FC7A0-g8.c (-G8 small data). */


/* func_L00_003080D0 is defined in its own unit. */


extern int r1_func_L00_0024A798(int);
extern struct { int a, b, c; char *p; } r1_D_L07_001842F0;


/* rac1-decomp src/overlays/l07_umbris/menu_cache_entry.c: func_L00_00308408 */
/* Clears each set bit in a rectangle of a per-row bit grid, notifying for each. */
void level_clear_grid_bits_in_rect(int x, int y0, int w, int h) {
    int y = y0;
    for (; y < y0 + h; y++) {
        int rowbase = (y >> 5) << 4;
        int i;
        for (i = x; i < x + w; i++) {
            unsigned char *p = (unsigned char *)r1_D_L07_001842F0.p + (y << 6) + i / 8;
            if (*p != 0) {
                int bit = 1 << (i & 7);
                if (*p & bit) {
                    r1_func_L00_0024A798((i >> 5) + rowbase);
                    *p = *p & ~bit;
                }
            }
        }
    }
}

/* func_L00_00308538 is defined in its own unit. */

typedef int Q128 __attribute__((mode(TI)));

typedef union {
    struct {
        int key;
        int age;
        unsigned char *data;
        int pad;
    } s;
    Q128 q;
} Ent_308700;

typedef struct {
    unsigned char *base;
    short *info;
    char pad8[0x28 - 8];
    int active;
    int pad2C;
    Ent_308700 e[8];
} Cache_308700;

extern Cache_308700 D_L00_001C93A0;
extern int D_L00_001B18D8[] __attribute__((sda));
extern void decode_map_rle_row(unsigned char *, int, unsigned char *, short *);

/* Looks for a key in a small cache of eight entries. If it is missing, it loads it over the oldest entry. Then it moves the entry to the front and returns 1 if it had to load it. */
int level_lookup_cache_entry(int key)
{
    int found;
    int best;
    int i;

    if (D_L00_001C93A0.active == 0)
        return 0;
    do {
        found = 0;
        best = 0;
        for (i = 0; i < 8; ++i) {
            if (D_L00_001C93A0.e[i].s.key == key)
                break;
            if (D_L00_001C93A0.e[i].s.age < *(int *)((unsigned char *)&D_L00_001C93A0 + 0x34 + best * 16))
                best = i;
        }
        do {
            if (i == 8) {
                Cache_308700 *c = &D_L00_001C93A0;
                unsigned char **dp = &c->e[0].s.data;
                Ent_308700 *e;
                Ent_308700 *e0;
                int off = best << 4;
                decode_map_rle_row(*(unsigned char **)((char *)dp + off), key, D_L00_001C93A0.base, c->info);
                e0 = c->e;
                e = (Ent_308700 *)((char *)e0 + off);
                e->s.key = key;
                i = best;
                found = 1;
            }
        } while (0);
        if (i != 0) {
            Ent_308700 *base = D_L00_001C93A0.e;
            Ent_308700 *other = base + i;
            Q128 tmp = other->q;
            other->q = base->q;
            base->q = tmp;
        }
    } while (0);
    D_L00_001C93A0.e[0].s.age = D_L00_001B18D8[0];
    return found;
}


/* rac1-decomp src/overlays/shared/menu_00249720.c: func_L00_0024B1B0 */
/* stores a value into a table slot chosen by the current index */
void level_store_value_in_table_slot(int value, int slotIndex) {
    int i = r1_D_0015EE84_m;
    if (i < 19) {
        slotIndex += r1_D_L00_001C47B8[i];
        r1_D_L00_001792B8[slotIndex] = value;
    }
}

/* Does nothing. Empty placeholder. */
void level_do_nothing_stub_c(void)
{
}

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void func_L00_0030C710(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        menu_set_screen_value_restart_four_fades(value + 0x376C8, argument);
}

/* Passes both arguments to a handler in the loaded module, if a module is loaded. */
void module_l00_call_handler_with_arg(int first, int second)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        menu_set_screen_value_restart_fades(value + 0x376C8, first, second);
}

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void module_l00_call_handler_with_arg_2(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        object_set_field_first(value + 0x376C8, argument);
}

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void module_l00_call_handler_with_arg_3(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        object_set_field_next(value + 0x376C8, argument);
}

/* Passes its argument to a handler in the loaded module, if a module is loaded. */
void module_l00_call_handler_with_arg_4(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        menu_set_flag_restart_fades(value + 0x37EB0, argument);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void module_l00_call_handler(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        sub_object_get_value_first(value + 0x36F28);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void module_l00_call_handler_2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        sub_object_get_value_second(value + 0x36F28);
}

/* Does nothing. Empty placeholder. */
void level_do_nothing_stub_d(void)
{
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void func_L00_0030D1B0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        hud_update_subsystems(value + 0x36F28);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void module_l00_call_handler_3(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        hud_item_bolt_draw(value + 0x36F28);
}

/* The wrappers below dispatch to a handler the object table names: the object's base word lives
 * in a shared global, the handler for it at a fixed byte offset from that base. Same family as
 * the one in src/game/0029BCC8.c, which reads D_001A8CFC instead. */

/* The value-returning half of the same family: the handler is called with the object base,
 * the fixed byte offset added and the caller's argument, and its result is returned. */

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_4(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_menu_draw_centered_rows(value + 0x39140);
}

/* Passes its argument to a handler in the loaded module and returns the result. Returns 0 if no module is loaded. */
int module_l00_call_handler_with_arg_5(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return UpdateMenuChoiceListWidgets(value + 0x39140, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_5(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        item_grid_menu_draw(value + 0x39590);
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_6(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_screen_large_draw_parts(value + 0x39A98);
}

/* Passes its argument to a handler in the loaded module and returns the result. Returns 0 if no module is loaded. */
int module_l00_call_handler_with_arg_6(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return UpdateItemGridMenu(value + 0x39590, argument);
    return 0;
}

/* Passes its argument to a handler in the loaded module and returns the result. Returns 0 if no module is loaded. */
int module_l00_call_handler_with_arg_7(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return mission_screen_place_parts(value + 0x3B1F0, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_7(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        mission_screen_draw_parts(value + 0x3B1F0);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_8(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return list_screen_layout(value + 0x3ADE8, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_screen_draw(value + 0x3ADE8);
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_9(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        map_screen_draw(value + 0x3B490);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_9(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return map_screen_update_layout(value + 0x3B490, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_10(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        radial_menu_destroy(value + 0x3B7C0);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_10(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return info_panel_update(value + 0x3B7C0, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_11(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_screen_draw_parts(value + 0x39F38);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_11(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return grid_menu_update(value + 0x39F38, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_12(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        tab_menu_draw(value + 0x3BE08);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_12(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return tab_menu_update(value + 0x3BE08, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_13(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        tab_menu_draw(value + 0x3BE08);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_13(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return tab_menu_update(value + 0x3BE08, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_14(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        item_menu_draw(value + 0x3C108);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_14(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return item_menu_update(value + 0x3C108, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_15(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_get_sub_object_value(value + 0x3C440);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_15(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return simple_page_update(value + 0x3C440, argument);
    }
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_16(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        two_toggle_b_draw(value + 0x3CDB0);
}

/* Reads a bound global word; when it is non-zero it calls a helper with that value plus a fixed base offset as the first argument and the function's own argument as the second, otherwise returns 0. */
int module_l00_call_handler_with_arg_16(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0) {
        return menu_handle_page_input_c(value + 0x3CDB0, argument);
    }
    return 0;
}

/* Reads a bound global word; when it is non-zero it calls the object's handler with that value
 * plus a fixed base offset as the first argument and the function's own argument as the second,
 * returning the handler's result, otherwise returns 0. */
int module_l00_call_handler_with_arg_17(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return UpdateFourOptionMenuInput(value + 0x3D060, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_17(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        four_option_menu_draw(value + 0x3D060);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int module_l00_call_handler_with_arg_18(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_handle_page_input_a(value + 0x3D310, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_18(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        two_toggle_a_draw(value + 0x3D310);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int module_l00_call_handler_with_arg_19(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_handle_page_input_b(value + 0x3D900, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void module_l00_call_handler_19(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        single_toggle_a_draw(value + 0x3D900);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int module_l00_call_handler_with_arg_20(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return screen_adjust_menu_update(value + 0x3DBB0, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void level_l00_call_module_handler(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        onoff_menu_draw_with_help(value + 0x3DBB0);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return onoff_menu_update(value + 0x3DE60, argument);
    return 0;
}

/* Reads the object base from a shared global and, when it is non-zero, calls the handler at a
 * fixed byte offset in it. */
void level_l00_call_module_handler_2(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        onoff_menu_draw(value + 0x3DE60);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_2(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_page_update(value + 0x3EDB8, argument);
    return 0;
}

/* Calls a handler in the currently loaded module, if a module is loaded. */
void level_l00_call_module_handler_3(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        list_page_draw(value + 0x3EDB8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_3(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return audio_menu_update(value + 0x3D5C0, argument);
    return 0;
}

/* Calls a handler in the currently loaded module, if a module is loaded. */
void level_l00_call_module_handler_4(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        audio_menu_draw(value + 0x3D5C0);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_4(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return menu_update_two_part_flags_a(value + 0x3E5A8, argument);
    return 0;
}

/* Calls a handler in the currently loaded module, if a module is loaded. */
void level_l00_call_module_handler_5(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        single_toggle_c_draw(value + 0x3E5A8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_5(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_menu_update(value + 0x3E1D8, argument);
    return 0;
}

/* Calls a handler in the currently loaded module, if a module is loaded. */
void level_l00_call_module_handler_6(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_draw_if_active(value + 0x3E1D8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_6(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return list_menu_set_selection(value + 0x3E430, argument);
    return 0;
}

/* Calls a handler in the currently loaded module, if a module is loaded. */
void level_l00_call_module_handler_7(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        small_list_menu_draw_rows(value + 0x3E430);
}

/* Call the registered handler with a table pointer built from one module base word plus the constant 36808, forwarding the incoming argument; do nothing when the base word is zero. */
void level_l00_call_module_handler_with_arg_7(int argument)
{
    int value = D_L00_001A904C_1;

    if (value != 0)
        menu_set_screen_field_2bc(value + 0x376C8, argument);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_8(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return func_0033FB98(value + 0x3A388, argument);
    return 0;
}

/* Calls a handler in the currently loaded module, if a module is loaded. */
void level_l00_call_module_handler_8(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        radial_menu_draw(value + 0x3A388);
}

/* Reads a bound global word; when it is zero it returns its first argument, otherwise it calls a helper with that value plus a fixed base offset and both of its arguments. */
int level_l00_call_module_handler_with_arg_9(int fallback, int extra)
{
    int value = D_L00_001A904C_7;

    if (value == 0) return fallback;
    return func_003387A0_1(value + 0x36F28, fallback, extra);
}

/* Reads a bound global word; when it is zero it returns its first argument, otherwise it calls a helper with that value plus a fixed base offset and both of its arguments. */
int level_l00_call_module_handler_with_arg_10(int fallback, int extra)
{
    int value = D_L00_001A904C_7;

    if (value == 0) return fallback;
    return func_00338040_1(value + 0x36F28, fallback, extra);
}

/* Reads a word from a shared global; when it is non-zero, calls a one-argument helper with that word plus a fixed byte offset. */
void level_l00_call_module_handler_9(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        level_clear_pending_pointer(value + 0x36F28);
}

/* Does nothing. Empty placeholder. */
void nop_l00_stub(void)
{
}


/* Calls a handler in the currently loaded module, if a module is loaded. */
void func_L00_0030DFE0(void)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        menu_draw_with_prompts(value + 0x3CAA8);
}

/* Same bound-global dispatch as its neighbours, with its own base offset and handler. */
int level_l00_call_module_handler_with_arg_11(int argument)
{
    int value = D_L00_001A904C_2;

    if (value != 0)
        return popup_update_position(value + 0x3CAA8, argument);
    return 0;
}

/* shared native body of family e7046bc951256c7e */
/* Counts the entries in a list of 256-byte records that are active up to the current limit, and stores the count. */
void level_count_active_records(void)
{
    unsigned char *p;
    int seen = 0;

    D_L05_001B2440 = 0;
    for (p = D_L05_001B2520; p < D_L05_001B2524; p += 256) {
        if ((p[32] >= 254 && *(unsigned int *)(p + 160) <= D_L05_001B2048) || seen) {
            D_L05_001B2440++;
            if (p[32] == 0xff)
                seen = 1;
        }
    }
}


/* rac1-decomp src/overlays/shared/mobyfunc_0024FD50.c: func_L00_0024FFE8 */
/* Shifts every point in a set of coordinate lists by the given x and y amounts. */
void offset_moby_class_point_pairs(unsigned char *object, int dx, int dy) {
    int i;
    int listCount = object[4] + object[5];
    int *entries = *(int **)object;
    for (i = 0; i < listCount; i++, entries += 4) {
        unsigned short *coords = *(unsigned short **)entries;
        int count = ((unsigned char *)coords)[2]; int remaining; coords += 2; if (count != 0) { remaining = count; do { coords[0] = coords[0] + dx; coords[1] = coords[1] + dy; coords += 2; remaining--; } while (remaining != 0); }
    }
}

/* shared native body of family 0820eb1123250c0b */
/* Takes the first free slot out of six, fills it in for the given index and links it into the list. */
Slot0820eb11 *allocate_moby_animation_slot(Ctx *ctx, int index)
{
    int i;
    Slot0820eb11 *slot;
    unsigned char *p;

    for (i = 0; i < 6; i++) {
        if (D_L03_001D23C0[i].f04 == 0) {
            break;
        }
    }
    slot = &D_L03_001D23C0[i];
    slot->f04 = 1;
    slot->f00 = index;
    slot->f10 = (int)(D_L03_001CA5C0 + i * 5376);
    slot->f14 = (int)ctx->f24;
    p = (unsigned char *)*(unsigned int *)(ctx->f24->f1C + (short)index * 4 + 4);
    slot->f02 = p[2];
    slot->f0C = p + (p[0] + 4);
    slot->f1C = ctx->f50;
    ctx->f50 = (int)slot;
    return slot;
}

/* The free half of the allocator above: unlinks the slot the caller's handle points at from
 * the context's slot list, wipes the sixty-four bytes and nulls the handle. The handle is
 * re-read at every mention (no local copy) - that is what keeps the retail allocation. */
void release_moby_animation_slot(LvlSlotCtx *ctx, LvlSlotNode **handle)
{
    LvlSlotNode *cur;

    if (*handle == 0)
        return;

    if (ctx->head == *handle) {
        ctx->head = (*handle)->next;
    } else {
        cur = ctx->head;
        while (cur->next != 0 && cur->next != *handle)
            cur = cur->next;
        if (cur->next == *handle)
            cur->next = (*handle)->next;
    }
    mem_clear((char *)*handle, 0, 0x40);
    *handle = 0;
}

/* func_L00_00310D30 is defined in its own unit. */

extern void mem_fast_helper_b(void *buf, int size);

extern void mem_copy_aligned(void *target, void *base, int len);

extern int FlushCache(int code);

/* The record the table entry points at: three shorts and an array of 64-bit slots. */
typedef struct L110E8Rec {
    char          pad00[0x06];
    short         f06;
    char          pad08[2];
    short         f0A;
    char          pad0C[2];
    short         f0E;
    unsigned long long slots[1];
} L110E8Rec;

/* What the function writes: five shorts and the same array of 64-bit slots. */
typedef struct L110E8Out {
    char          pad00[0x06];
    short         f06;
    short         f08;
    short         f0A;
    short         f0C;
    short         f0E;
    unsigned long long slots[1];
} L110E8Out;

/* The object the two table pointers come from. */
typedef struct L110E8Src {
    char          pad00[0x14];
    char         *f14;
    char         *f18;
} L110E8Src;



/* Builds a new data block from two tables: copies the entry data and rewrites the sizes and offsets in its header. */
void level_build_data_block(L110E8Src *source, int listIndex, int entryIndex, L110E8Out *outBuffer)
{
    char *tableB = source->f18;
    char *tableA = source->f14;
    unsigned char countB = (unsigned char)tableB[8];
    unsigned char countA = (unsigned char)tableA[8];
    int *entryList;
    L110E8Rec *rec;
    unsigned short *uf;
    unsigned short uhA;
    unsigned short uhE;
    L110E8Out *out = outBuffer;
    short hA;
    short hE;
    int destinationOffset;
    int v;
    int len;

    tableB += listIndex * 4;
    entryList = *(int **)(tableB + 0x48);
    entryList += entryIndex;
    rec = ((L110E8Rec **)entryList)[7];
    uf = (unsigned short *)rec;
    mem_fast_helper_b(out, ((countA + 3) * 8) & 0xFF0);

    destinationOffset = countA * 8;
    {
        char *msrc = (char *)rec + (countB * 8 + 0x10);

        hA = rec->f0A;
        hE = rec->f0E;
        out->f08 = (short)destinationOffset;
        v = countA + hA;
        v += hE;
        v += 1;
        out->f06 = (short)(v >> 1);
        uhA = uf[5];
        out->f0A = uhA;
        out->f0C = (short)((uhA + countA) * 8);
        uhE = uf[7];
        out->f0E = uhE;

        len = rec->f06 * 16 - countB * 8;
        if (len != 0)
            mem_copy_aligned((char *)out + (destinationOffset + 0x10), msrc, len);
    }

    {
        unsigned char *table = (unsigned char *)(*(int *)(source->f18 + 0x1C)) + 4;
        int i;
        unsigned long long *src = (unsigned long long *)((char *)rec + 0x10);

        if (countB != 0) {
            i = countB;

            while (i != 0) {
                *(unsigned long long *)((char *)out + table[0] * 8 + 0x10) = src[0];
                table++;
                src++;
                i--;
            }
        }
    }
    {
        unsigned long long *p = (unsigned long long *)((char *)out + out->f06 * 16);

        if (*p == 0)
            *p = 1;
    }
    FlushCache(0);
}

/* scales a float field by 1/1024, fills a 64-byte stack buffer from the object, then applies three per-element helper calls over n 64-byte records. */
void mat_transform_array(char *object, int count, int extraArg, char *matrices)
{
    char buf[64];
    float scale;
    int i;

    scale = *(float *)(object + 44) * 0.0009765625f;
    func_00283658_1(buf, object + 192);
    func_002A3F10_3(object, count, extraArg, matrices);
    for (i = 0; i < count; i++) {
        func_00283788_5(matrices + i * 64, buf, matrices + i * 64);
        func_00282D30_21(matrices + i * 64 + 48, matrices + i * 64 + 48, scale);
        func_00282CC0_24(matrices + i * 64 + 48, matrices + i * 64 + 48, object + 16);
    }
}


ASM_FUNC("asm/levels", func_L00_00314D40);
