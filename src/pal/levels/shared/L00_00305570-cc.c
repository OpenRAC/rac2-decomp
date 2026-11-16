/* func_PAL_L00_00305570, the PAL copy of func_L00_00303990: the same C, where rename func_0029D4D0 becomes func_PAL_0029DE68; rename func_L00_00300618 becomes func_PAL_L00_003021B0; rename func_L00_00358B30 becomes func_PAL_L00_0035B058. */
/* Level loader: unpacks the level archive, uploads textures, builds the GS template words and
 * the class/texture tables, and returns the next free heap pointer. The store into the load block goes before the
 * fx/fy loads so combine keeps the first GS word's low half a DI register (retail's or tie). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef union { unsigned char b[0x400]; short h[0x200]; unsigned short uh[0x200]; int i[0x100];
                char *p[0x100]; unsigned long long d[0x80]; TI128 q[0x40]; } Blk;
typedef struct { int i[0x40]; } Hdr;
typedef struct {
    unsigned char pad0[4];
    unsigned char b4;
    unsigned char pad5[0xDB];
} ClassEntry;
typedef struct {
    unsigned char pad0[0x1A];
    short h1A;
    int i1C;
} Slot32;
typedef struct { char *data; int count; int pad8[2]; } Frame;
typedef struct {
    Frame *frames;
    unsigned char pad4[2];
    unsigned char b6;
    unsigned char b7;
    unsigned char pad8[4];
    unsigned char bC;
    unsigned char bD;
    unsigned char padE[0x28 - 0xE];
    Slot32 *slots;
    unsigned char pad2C[0x48 - 0x2C];
    int f48[1];
} Bank;

extern Blk g_level_load_context;
extern Blk g_tutorial_points;
typedef struct { int stage, busy; int *archive0; int archive1; } ArchiveLoad;
extern ArchiveLoad g_loader_archives MACRO_ADDR;
typedef struct { int offset; unsigned short kind; unsigned short pad6; int pad8[2]; } TexRef;
typedef struct { short off; short count; } Span;
extern int g_current_map_index;
extern int g_vram_clut_third;
extern int g_vram_pixel_base;
extern unsigned char g_moby_group_flags[];
extern unsigned char g_class_l00_flags_table[] MACRO_ADDR;
extern unsigned long long g_gif_packet_template_first[3];
extern unsigned long long g_gif_packet_template_second[3];
extern int g_level_chunk_count_c;
extern int g_level_chunk_count_a;
extern int g_level_chunk_count_d;
extern int g_level_chunk_count_b;
extern int g_class_offsets_table[];
extern int g_class_values_a[];
extern int g_class_values_c[];
extern int g_class_values_b[];
extern Blk g_load_slots;
extern Blk g_hero_moby_default;
extern int g_level_header_extra_ptr;
extern int g_level_reset_word;
extern int g_level_block_ptr_first;
extern int g_level_block_ptr_second;
extern unsigned long long g_gs_register_packet[3];
extern int g_register_class_cache_args[4] __attribute__((sda));
extern int g_level_fixup_count;
extern int g_class_l00_flags_table_2[];
extern short g_class_ids_by_slot[];
extern Bank *g_sound_bank_table[];
extern unsigned char g_class_slot_indices[];
extern short g_current_texture_pack;
extern int g_iop_block_table;
extern int g_current_weapon_channel;
extern int g_gfx_hero_slot;
extern unsigned char g_item_slot_to_record[];
extern ClassEntry g_weapon_l00_table[];
extern int g_tie_class_table[];
extern int g_shrub_l00_class_table[];
extern int g_level_chunk_base;
extern TI128 g_level_quad_first MACRO_ADDR, g_level_quad_second MACRO_ADDR, g_level_quad_third MACRO_ADDR, g_level_quad_fourth MACRO_ADDR;
extern int g_level_quad_source;
extern int g_tfrag_count;
extern Slot32 *g_slot_table;
extern int g_slot_count;
extern char g_str_register_class_debug[];
extern char g_str_register_class_span_format[];
extern short g_load_entry_index[];
typedef struct { unsigned char pad0[0xA]; unsigned char enabled; } Global001A7A00;
extern Global001A7A00 g_player_stats MACRO_ADDR;
typedef struct { int pad[2]; int f8; } SceneTrigger;
extern SceneTrigger g_scene_trigger MACRO_ADDR;
extern int g_moby_array_base __attribute__((sda));
extern int g_moby_array_end_sentinel[] MACRO_ADDR;
extern int g_frame_l00_counter;

extern void hud_load_banks(void);
extern void table_reset_entries(void);
extern void mem_fast_helper_c(void *, void *, int);
extern void mem_copy_aligned(void *, void *, int);
extern void UploadTextureImages(void *, int, int, void *);
extern void FlushCache(int);
extern int fast_decompress_pal(void *, char *);
extern int log2dim(int);
extern void initialize_tfrag_render_data(char *, void *);
extern void RelocateSkyDefinition(char *);
extern void level_relocate_header_blocks(char *);
extern void load_register_class_cache_object(char *, void *, void *, int);
extern void PrintMobyClassSizes(void *, int, void *);
extern void tex_build_draw_packets(int);
extern void load_copy_header_relocate_pointers(Bank *, int);
extern void gfx_send_gs_register_packet(int);
extern void relocate_asset_entry_pointers(Bank *, int);
extern void RegisterObjectRenderClass(char *, void *, void *, int);
extern void ref_L00_00303990_00();
extern void RegisterShrubRenderClass(char *, void *, void *, void *, int);
extern void func_00291DE0(void *, int);
extern void level_load_quadword_block(char *);
extern void tex_rebase_pack_fill_ranges(void *, char *, void *, int);
extern void STUB_printf(const char *, ...);
extern char *func_PAL_L00_003021B0(int);
extern void tutorial_reset_record_values(void);
extern void level_update_object_visibility(int);
extern void RestoreSavedHeroState_pal(void);
extern void mem_clear_work_areas(void);
extern void moby_scale_by_difficulty(int);
extern void moby_update_live_mobys(void);

int LoadLevelArchiveResources_pal(int load, int resume)
{
    Hdr *h = (Hdr *)g_level_load_context.p[0xC / 4];
    int *f = g_loader_archives.archive0;
    char *base;
    char *end;
    int used;
    int i;
    int c1, c2, c3, c4;
    int fx;
    int fy;
    char *e;
    TexRef *t1, *tex, *t3, *t4;
    int slot8;
    int *list;
    int j;
    char *tab;
    Span *span;
    unsigned short *us;
    char *q2, *q, *p;
    int sq, a3, ci, k;

    if (load)
        hud_load_banks();
    base = g_level_load_context.p[0x18 / 4];
    if (load) {
        table_reset_entries();
        g_tutorial_points.i[0] = 0;
        mem_fast_helper_c(h, (char *)(f[2] + (int)f), f[3]);
        mem_copy_aligned(g_class_l00_flags_table, g_moby_group_flags + g_current_map_index * 16, 16);
        UploadTextureImages((char *)(f[4] + (int)f), h->i[0], h->i[0x84 / 4], (char *)h + h->i[1]);
        FlushCache(0);
        used = fast_decompress_pal((char *)(f[0x12] + (int)f), base);
        g_level_load_context.p[0x2C / 4] = base + h->i[0x60 / 4];
        fx = g_vram_clut_third;
        fy = g_vram_pixel_base;
        g_gif_packet_template_first[0] = (int)((fy + h->i[0x90 / 4] * 4) >> 8) | 0x1DB08000 | ((long long)0xB800 << 19) |
            ((long long)((fx + h->i[0x94 / 4]) >> 8) << 37) | 0x8000000000000000LL;
        g_gif_packet_template_first[1] = 0xFFA0000000E0ULL;
        g_gif_packet_template_first[2] = 0x40000400004000ULL;
        g_gif_packet_template_second[0] = (int)((fy + h->i[0x98 / 4] * 4) >> 8) | 0x19B04000 | ((long long)0xB000 << 19) |
            ((long long)((fx + h->i[0x9C / 4]) >> 8) << 37) | 0x8000000000000000LL;
        g_gif_packet_template_second[1] = 0xFFA0000000E0ULL;
        g_gif_packet_template_second[2] = 0x40000400004000ULL;

        t1 = (TexRef *)((char *)h + h->i[0x34 / 4]);
        g_level_chunk_count_c = h->i[0x30 / 4];
        for (c1 = 0; c1 < g_level_chunk_count_c; c1++)
            g_class_offsets_table[c1] = g_level_load_context.i[0x2C / 4] + t1[c1].offset + (log2dim(t1[c1].kind) << 28);
        tex = (TexRef *)((char *)h + h->i[0x3C / 4]);
        g_level_chunk_count_a = h->i[0x38 / 4];
        for (c2 = 0; c2 < g_level_chunk_count_a; c2++) {
            int value = g_level_load_context.i[0x2C / 4] + tex[c2].offset + (log2dim(tex[c2].kind) << 28);
            g_class_values_a[c2] = value;
        }
        qcopy(&g_load_slots, &tex[h->i[0x80 / 4]]);
        g_load_slots.uh[0x10 / 2] = ((unsigned short *)h)[0x80 / 2];
        t3 = (TexRef *)((char *)h + h->i[0x44 / 4]);
        g_level_chunk_count_d = h->i[0x40 / 4];
        for (c3 = 0; c3 < g_level_chunk_count_d; c3++) {
            int value = g_level_load_context.i[0x2C / 4] + t3[c3].offset + (log2dim(t3[c3].kind) << 28);
            g_class_values_c[c3] = value;
        }
        t4 = (TexRef *)((char *)h + h->i[0x4C / 4]);
        g_level_chunk_count_b = h->i[0x48 / 4];
        for (c4 = 0; c4 < g_level_chunk_count_b; c4++) {
            int value = g_level_load_context.i[0x2C / 4] + t4[c4].offset + (log2dim(t4[c4].kind) << 28);
            g_class_values_b[c4] = value;
        }
        g_level_load_context.p[0x1C / 4] = base + h->i[0x8 / 4];
        initialize_tfrag_render_data(g_level_load_context.p[0x1C / 4], (char *)h + h->i[0x34 / 4]);
        g_tutorial_points.p[0x8 / 4] = g_level_load_context.p[0x1C / 4];
        if (h->i[0xC / 4] != 0) {
            char *p = base + h->i[0xC / 4];
            g_level_load_context.p[0x20 / 4] = p;
            g_level_header_extra_ptr = (int)p;
        } else {
            g_level_load_context.p[0x20 / 4] = 0;
            g_level_header_extra_ptr = 0;
        }
        if (h->i[0x10 / 4] != 0) {
            char *p = base + h->i[0x10 / 4];
            g_level_load_context.p[0x24 / 4] = p;
            RelocateSkyDefinition(p);
        } else {
            g_level_reset_word = 0;
            g_level_load_context.p[0x24 / 4] = 0;
        }
        {
            char *p = base + h->i[0x14 / 4];
            g_level_load_context.p[0x28 / 4] = p;
            level_relocate_header_blocks(p);
        }
        g_tutorial_points.p[0x4 / 4] = g_level_load_context.p[0x28 / 4];
        for (i = 0, q2 = (char *)h + h->i[0x1C / 4]; i < h->i[0x18 / 4]; i++, q2 += 0x20) {
            char *p = *(int *)q2 != 0 ? base + *(int *)q2 : 0;
            if (*(int *)(q2 + 8) != 0) {
                g_gs_register_packet[0] = g_hero_moby_default.d[0x38 / 8];
                g_gs_register_packet[1] = 0xFFA0000000E0ULL;
                g_gs_register_packet[2] = 0x40000400004000ULL;
                load_register_class_cache_object(p, 0, g_register_class_cache_args, *(int *)(q2 + 4));
                g_class_l00_flags_table_2[g_level_fixup_count - 1] = 0xFFFC0000;
            } else {
                load_register_class_cache_object(p, (char *)h + h->i[0x3C / 4], q2 + 0x10, *(int *)(q2 + 4));
            }
        }
        g_level_load_context.p[0x38 / 4] = (char *)g_sound_bank_table[0];
        PrintMobyClassSizes((char *)h + h->i[0x1C / 4], h->i[0x18 / 4], (char *)h + h->i[0x24 / 4]);
        {
            int count = g_level_fixup_count;
            g_hero_moby_default.i[0x1C / 4] = count++;
            g_class_l00_flags_table_2[g_hero_moby_default.i[0x1C / 4]] = 0xFFFC0000;
            g_class_ids_by_slot[g_hero_moby_default.i[0x1C / 4]] = 0xD54;
            g_sound_bank_table[g_hero_moby_default.i[0x1C / 4]] = (Bank *)g_level_load_context.p[0x70 / 4];
            g_class_slot_indices[0xD54] = g_hero_moby_default.i[0x1C / 4];
            g_load_slots.h[0x12 / 2] = count;
            g_level_fixup_count = count + 1;
        }
        if (g_iop_block_table != g_current_texture_pack) {
            tex_build_draw_packets(g_current_texture_pack);
            g_iop_block_table = g_current_texture_pack;
        }
        load_copy_header_relocate_pointers(g_sound_bank_table[0], g_level_load_context.i[0x78 / 4]);
        g_class_l00_flags_table_2[0] = 0xFFFC0000;
        slot8 = g_class_slot_indices[0xD54];
        if (slot8 != 0xFF) {
            Bank *bank = g_sound_bank_table[slot8];
            if (bank->b6 != 0) {
                Frame *fr = &bank->frames[bank->b7];
                char *pkt = fr->data + fr->count * 16;
                *(unsigned long long *)(pkt - 0x20) = g_gif_packet_template_first[0];
                *(unsigned long long *)(pkt - 0x10) = g_gif_packet_template_first[2];
            }
        }
        {
            int want = (g_item_slot_to_record[0xA] + g_weapon_l00_table)->b4;
            if (g_current_weapon_channel != want)
                gfx_send_gs_register_packet(want);
        }
        {
            int hero = g_class_slot_indices[0x47];
            g_gfx_hero_slot = hero;
            load_copy_header_relocate_pointers(g_sound_bank_table[hero], g_level_load_context.i[0x74 / 4]);
        }
        g_class_l00_flags_table_2[g_gfx_hero_slot] = 0xFFFC0000;
        us = (unsigned short *)((char *)h + h->i[0xAC / 4]);
        while ((short)*us >= 0) {
            int slot = g_class_slot_indices[(short)*us];
            if (slot != 0xFF)
                g_class_l00_flags_table_2[slot] = 0xFFF00000;
            us++;
        }
        for (sq = 0, p = (char *)h + h->i[0x78 / 4]; sq < g_sound_bank_table[0]->bC; sq++, p += 4) {
            if (*(int *)p != 0) {
                g_sound_bank_table[0]->f48[sq] = (int)(base + *(int *)p);
                relocate_asset_entry_pointers(g_sound_bank_table[0], sq);
            }
        }
        g_level_load_context.i[0x44 / 4] = g_sound_bank_table[0]->f48[0];
        for (i = 0, q2 = (char *)h + h->i[0x24 / 4]; i < h->i[0x20 / 4]; i++, q2 += 0x20)
            RegisterObjectRenderClass(base + *(int *)q2, (char *)h + h->i[0x44 / 4], q2 + 0x10, *(int *)(q2 + 4));
        if (g_tie_class_table[0] != 0)
            g_level_load_context.i[0x3C / 4] = g_tie_class_table[0];
        ref_L00_00303990_00((char *)h + h->i[0x24 / 4], h->i[0x20 / 4]);
        for (i = 0, q2 = (char *)h + h->i[0x2C / 4]; i < h->i[0x28 / 4]; i++, q2 += 0x30)
            RegisterShrubRenderClass(base + *(int *)q2, (char *)h + h->i[0x4C / 4], q2 + 0x10, q2 + 0x20, *(int *)(q2 + 4));
        if (g_shrub_l00_class_table[0] != 0)
            g_level_load_context.i[0x40 / 4] = g_shrub_l00_class_table[0];
        {
            char *p = base + h->i[0x68 / 4];
            g_level_load_context.p[0x34 / 4] = p;
            g_level_chunk_base = (int)p;
        }
        func_00291DE0((char *)h + h->i[0x5C / 4], h->i[0x58 / 4]);
        if (h->i[0xA4 / 4] != 0) {
            level_load_quadword_block(base + h->i[0xA4 / 4]);
        } else {
            qzero(&g_level_quad_first);
            qzero(&g_level_quad_second);
            qzero(&g_level_quad_third);
            qzero(&g_level_quad_fourth);
            g_level_quad_source = 0;
        }
        if (h->i[0xA8 / 4] != 0)
            g_level_block_ptr_first = (int)(base + h->i[0xA8 / 4]);
        else
            g_level_block_ptr_first = 0;
        if (h->i[0xB0 / 4] != 0)
            g_level_block_ptr_second = (int)(base + h->i[0xB0 / 4]);
        else
            g_level_block_ptr_second = 0;
        {
            char *x1 = base + h->i[0x64 / 4];
            char *x2;
            g_level_load_context.p[0x30 / 4] = x1;
            x2 = (char *)h + h->i[0x54 / 4];
            tex_rebase_pack_fill_ranges((char *)h + h->i[0x6C / 4], x1, x2, h->i[0x50 / 4]);
        }
        base = (char *)((unsigned int)(base + used + 0x3F) & ~0x3F);
        if (g_tfrag_count != g_tutorial_points.i[0x18 / 4]) {
            char *dst;
            int size;
            do {
                g_tutorial_points.p[0x10 / 4] = base;
                size = h->i[0x30 / 4];
            } while (0);
            dst = base;
            size *= 16;
            base += size;
            mem_fast_helper_c(dst, (char *)h + h->i[0x34 / 4], size);
            g_tutorial_points.p[0x14 / 4] = base;
            base = (char *)(((unsigned int)(base + g_tutorial_points.i[0x18 / 4] * 2) + 0x7F) & ~0x3F);
        }
        tab = (char *)h + h->i[0x70 / 4];
        span = (Span *)tab;
        {
            int nslots = span->count;
            g_slot_table = (Slot32 *)base;
            g_slot_count = nslots;
            mem_copy_aligned(base, tab + span->off, nslots * 32);
            span++;
            base += nslots * 32;
        }
        e = tab + span->off;
        for (a3 = 0; a3 < g_slot_count; a3++) {
            if (g_slot_table[a3].h1A >= span->count) {
                STUB_printf(g_str_register_class_debug);
                g_slot_table[a3].h1A = -1;
            } else {
                g_slot_table[a3].h1A = *(unsigned short *)(e + g_slot_table[a3].h1A * 4);
            }
            g_slot_table[a3].i1C = 0;
        }
        end = base + 0x3F;
        span++;
        for (ci = 0, q = (char *)h + h->i[0x1C / 4]; ci < h->i[0x18 / 4]; ci++, span++, q += 0x20) {
            int cls = g_class_slot_indices[*(int *)(q + 4)];
            if (g_class_ids_by_slot[cls] == *(int *)(q + 4)) {
                if ((span->count != 0 || g_sound_bank_table[cls]->bD != 0) && span->count - 1 != g_sound_bank_table[cls]->bD)
                    STUB_printf(g_str_register_class_span_format, g_class_ids_by_slot[cls], span->count - 1, g_sound_bank_table[cls]->bD);
                {
                    int first;
                    e = tab + span->off;
                    first = *(int *)e;
                    e += 4;
                    for (k = 0; k < g_sound_bank_table[cls]->bD; k++, e += 4) {
                        g_sound_bank_table[cls]->slots[k].h1A = *(unsigned short *)e;
                        g_sound_bank_table[cls]->slots[k].i1C = first + 1;
                    }
                }
            }
        }
        base = (char *)((unsigned int)end & ~0x3F);
        g_level_load_context.p[0x48 / 4] = base;
    }
    g_level_load_context.i[0x68 / 4] = func_PAL_L00_003021B0(load);
    if (load)
        g_load_entry_index[0] = -1;
    if (g_tutorial_points.i[0xC / 4] != 0) {
        if (load)
            tutorial_reset_record_values();
        level_update_object_visibility(g_tutorial_points.i[0]);
    }
    if (resume)
        RestoreSavedHeroState_pal();
    else
        mem_clear_work_areas();
    g_scene_trigger.f8 = 0;
    if (g_player_stats.enabled != 0) {
        int m;
        for (m = g_moby_array_base; m != g_moby_array_end_sentinel[0]; m += 0x100)
            moby_scale_by_difficulty(m);
    }
    moby_update_live_mobys();
    g_frame_l00_counter++;
    return 0;
}
