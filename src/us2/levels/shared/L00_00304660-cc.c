/* func_US2_L00_00304660, the USA v2.00 copy of func_L00_00303990: the same C, where rename func_00292888 becomes func_US2_00293138; rename func_0029D4D0 becomes func_US2_0029E308; rename func_00291DE0 becomes func_US2_00292650; rename func_L00_00300618 becomes func_US2_L00_003012A0. */
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

extern Blk D_L00_001BF140;
extern Blk D_L00_001C9340;
typedef struct { int stage, busy; int *archive0; int archive1; } ArchiveLoad;
extern ArchiveLoad D_001A7280 MACRO_ADDR;
typedef struct { int offset; unsigned short kind; unsigned short pad6; int pad8[2]; } TexRef;
typedef struct { short off; short count; } Span;
extern int g_current_map_index;
extern int D_001A72F4;
extern int D_001A7304;
extern unsigned char D_0019B2E8[];
extern unsigned char D_L00_001B1CE0[] MACRO_ADDR;
extern unsigned long long D_L00_001B1CF0[3];
extern unsigned long long D_L00_001B1D08[3];
extern int D_L00_001B24D8;
extern int D_L00_001B1E8C;
extern int D_L00_001B2550;
extern int D_L00_001B2410;
extern int D_L00_00225900[];
extern int D_L00_001DC980[];
extern int D_L00_0022D200[];
extern int D_L00_0021FBA0[];
extern Blk D_00152CD0;
extern Blk g_hero_moby_default;
extern int D_L00_001B1A40;
extern int D_L00_001B2420;
extern int D_L00_001B1A44;
extern int D_L00_001B1A48;
extern unsigned long long D_L00_001C91C0[3];
extern int D_L00_001A9520[4] __attribute__((sda));
extern int D_L00_001B1E80;
extern int D_L00_001DD180[];
extern short D_L00_001DA680[];
extern Bank *D_L00_001D9F00[];
extern unsigned char D_L00_001DA860[];
extern short D_001A7A18;
extern int D_001A7290;
extern int D_001A72C0;
extern int D_001A72C4;
extern unsigned char g_item_slot_to_record[];
extern ClassEntry g_weapon_l00_table[];
extern int D_L00_00226700[];
extern int D_L00_0021EA20[];
extern int D_L00_001B1944;
extern TI128 D_L00_001B1D20 MACRO_ADDR, D_L00_001B1D30 MACRO_ADDR, D_L00_001B1D40 MACRO_ADDR, D_L00_001B1D50 MACRO_ADDR;
extern int D_L00_001B1D60;
extern int D_L00_001B24D4;
extern Slot32 *D_L00_001B19EC;
extern int D_L00_001B19E8;
extern char D_L00_001A95B8[];
extern char D_L00_001A95D8[];
extern short D_00152CE4[];
typedef struct { unsigned char pad0[0xA]; unsigned char enabled; } Global001A7A00;
extern Global001A7A00 D_001A7A00 MACRO_ADDR;
typedef struct { int pad[2]; int f8; } SceneTrigger;
extern SceneTrigger D_L00_001B1AD0 MACRO_ADDR;
extern int D_L00_001B1E9C __attribute__((sda));
extern int D_L00_001B1EA0[] MACRO_ADDR;
extern int g_frame_l00_counter;

extern void func_US2_00293138(void);
extern void table_reset_entries(void);
extern void mem_fast_helper_c(void *, void *, int);
extern void mem_copy_aligned(void *, void *, int);
extern void UploadTextureImages(void *, int, int, void *);
extern void FlushCache(int);
extern int func_US2_0029E308(void *, char *);
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
extern void func_US2_00292650(void *, int);
extern void level_load_quadword_block(char *);
extern void tex_rebase_pack_fill_ranges(void *, char *, void *, int);
extern void STUB_printf(const char *, ...);
extern char *func_US2_L00_003012A0(int);
extern void tutorial_reset_record_values(void);
extern void level_update_object_visibility(int);
extern void RestoreSavedHeroState(void);
extern void mem_clear_work_areas(void);
extern void moby_scale_by_difficulty(int);
extern void moby_update_live_mobys(void);

int func_US2_L00_00304660(int load, int resume)
{
    Hdr *h = (Hdr *)D_L00_001BF140.p[0xC / 4];
    int *f = D_001A7280.archive0;
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
        func_US2_00293138();
    base = D_L00_001BF140.p[0x18 / 4];
    if (load) {
        table_reset_entries();
        D_L00_001C9340.i[0] = 0;
        mem_fast_helper_c(h, (char *)(f[2] + (int)f), f[3]);
        mem_copy_aligned(D_L00_001B1CE0, D_0019B2E8 + g_current_map_index * 16, 16);
        UploadTextureImages((char *)(f[4] + (int)f), h->i[0], h->i[0x84 / 4], (char *)h + h->i[1]);
        FlushCache(0);
        used = func_US2_0029E308((char *)(f[0x12] + (int)f), base);
        D_L00_001BF140.p[0x2C / 4] = base + h->i[0x60 / 4];
        fx = D_001A72F4;
        fy = D_001A7304;
        D_L00_001B1CF0[0] = (int)((fy + h->i[0x90 / 4] * 4) >> 8) | 0x1DB08000 | ((long long)0xB800 << 19) |
            ((long long)((fx + h->i[0x94 / 4]) >> 8) << 37) | 0x8000000000000000LL;
        D_L00_001B1CF0[1] = 0xFFA0000000E0ULL;
        D_L00_001B1CF0[2] = 0x40000400004000ULL;
        D_L00_001B1D08[0] = (int)((fy + h->i[0x98 / 4] * 4) >> 8) | 0x19B04000 | ((long long)0xB000 << 19) |
            ((long long)((fx + h->i[0x9C / 4]) >> 8) << 37) | 0x8000000000000000LL;
        D_L00_001B1D08[1] = 0xFFA0000000E0ULL;
        D_L00_001B1D08[2] = 0x40000400004000ULL;

        t1 = (TexRef *)((char *)h + h->i[0x34 / 4]);
        D_L00_001B24D8 = h->i[0x30 / 4];
        for (c1 = 0; c1 < D_L00_001B24D8; c1++)
            D_L00_00225900[c1] = D_L00_001BF140.i[0x2C / 4] + t1[c1].offset + (log2dim(t1[c1].kind) << 28);
        tex = (TexRef *)((char *)h + h->i[0x3C / 4]);
        D_L00_001B1E8C = h->i[0x38 / 4];
        for (c2 = 0; c2 < D_L00_001B1E8C; c2++) {
            int value = D_L00_001BF140.i[0x2C / 4] + tex[c2].offset + (log2dim(tex[c2].kind) << 28);
            D_L00_001DC980[c2] = value;
        }
        qcopy(&D_00152CD0, &tex[h->i[0x80 / 4]]);
        D_00152CD0.uh[0x10 / 2] = ((unsigned short *)h)[0x80 / 2];
        t3 = (TexRef *)((char *)h + h->i[0x44 / 4]);
        D_L00_001B2550 = h->i[0x40 / 4];
        for (c3 = 0; c3 < D_L00_001B2550; c3++) {
            int value = D_L00_001BF140.i[0x2C / 4] + t3[c3].offset + (log2dim(t3[c3].kind) << 28);
            D_L00_0022D200[c3] = value;
        }
        t4 = (TexRef *)((char *)h + h->i[0x4C / 4]);
        D_L00_001B2410 = h->i[0x48 / 4];
        for (c4 = 0; c4 < D_L00_001B2410; c4++) {
            int value = D_L00_001BF140.i[0x2C / 4] + t4[c4].offset + (log2dim(t4[c4].kind) << 28);
            D_L00_0021FBA0[c4] = value;
        }
        D_L00_001BF140.p[0x1C / 4] = base + h->i[0x8 / 4];
        initialize_tfrag_render_data(D_L00_001BF140.p[0x1C / 4], (char *)h + h->i[0x34 / 4]);
        D_L00_001C9340.p[0x8 / 4] = D_L00_001BF140.p[0x1C / 4];
        if (h->i[0xC / 4] != 0) {
            char *p = base + h->i[0xC / 4];
            D_L00_001BF140.p[0x20 / 4] = p;
            D_L00_001B1A40 = (int)p;
        } else {
            D_L00_001BF140.p[0x20 / 4] = 0;
            D_L00_001B1A40 = 0;
        }
        if (h->i[0x10 / 4] != 0) {
            char *p = base + h->i[0x10 / 4];
            D_L00_001BF140.p[0x24 / 4] = p;
            RelocateSkyDefinition(p);
        } else {
            D_L00_001B2420 = 0;
            D_L00_001BF140.p[0x24 / 4] = 0;
        }
        {
            char *p = base + h->i[0x14 / 4];
            D_L00_001BF140.p[0x28 / 4] = p;
            level_relocate_header_blocks(p);
        }
        D_L00_001C9340.p[0x4 / 4] = D_L00_001BF140.p[0x28 / 4];
        for (i = 0, q2 = (char *)h + h->i[0x1C / 4]; i < h->i[0x18 / 4]; i++, q2 += 0x20) {
            char *p = *(int *)q2 != 0 ? base + *(int *)q2 : 0;
            if (*(int *)(q2 + 8) != 0) {
                D_L00_001C91C0[0] = g_hero_moby_default.d[0x38 / 8];
                D_L00_001C91C0[1] = 0xFFA0000000E0ULL;
                D_L00_001C91C0[2] = 0x40000400004000ULL;
                load_register_class_cache_object(p, 0, D_L00_001A9520, *(int *)(q2 + 4));
                D_L00_001DD180[D_L00_001B1E80 - 1] = 0xFFFC0000;
            } else {
                load_register_class_cache_object(p, (char *)h + h->i[0x3C / 4], q2 + 0x10, *(int *)(q2 + 4));
            }
        }
        D_L00_001BF140.p[0x38 / 4] = (char *)D_L00_001D9F00[0];
        PrintMobyClassSizes((char *)h + h->i[0x1C / 4], h->i[0x18 / 4], (char *)h + h->i[0x24 / 4]);
        {
            int count = D_L00_001B1E80;
            g_hero_moby_default.i[0x1C / 4] = count++;
            D_L00_001DD180[g_hero_moby_default.i[0x1C / 4]] = 0xFFFC0000;
            D_L00_001DA680[g_hero_moby_default.i[0x1C / 4]] = 0xD54;
            D_L00_001D9F00[g_hero_moby_default.i[0x1C / 4]] = (Bank *)D_L00_001BF140.p[0x70 / 4];
            D_L00_001DA860[0xD54] = g_hero_moby_default.i[0x1C / 4];
            D_00152CD0.h[0x12 / 2] = count;
            D_L00_001B1E80 = count + 1;
        }
        if (D_001A7290 != D_001A7A18) {
            tex_build_draw_packets(D_001A7A18);
            D_001A7290 = D_001A7A18;
        }
        load_copy_header_relocate_pointers(D_L00_001D9F00[0], D_L00_001BF140.i[0x78 / 4]);
        D_L00_001DD180[0] = 0xFFFC0000;
        slot8 = D_L00_001DA860[0xD54];
        if (slot8 != 0xFF) {
            Bank *bank = D_L00_001D9F00[slot8];
            if (bank->b6 != 0) {
                Frame *fr = &bank->frames[bank->b7];
                char *pkt = fr->data + fr->count * 16;
                *(unsigned long long *)(pkt - 0x20) = D_L00_001B1CF0[0];
                *(unsigned long long *)(pkt - 0x10) = D_L00_001B1CF0[2];
            }
        }
        {
            int want = (g_item_slot_to_record[0xA] + g_weapon_l00_table)->b4;
            if (D_001A72C0 != want)
                gfx_send_gs_register_packet(want);
        }
        {
            int hero = D_L00_001DA860[0x47];
            D_001A72C4 = hero;
            load_copy_header_relocate_pointers(D_L00_001D9F00[hero], D_L00_001BF140.i[0x74 / 4]);
        }
        D_L00_001DD180[D_001A72C4] = 0xFFFC0000;
        us = (unsigned short *)((char *)h + h->i[0xAC / 4]);
        while ((short)*us >= 0) {
            int slot = D_L00_001DA860[(short)*us];
            if (slot != 0xFF)
                D_L00_001DD180[slot] = 0xFFF00000;
            us++;
        }
        for (sq = 0, p = (char *)h + h->i[0x78 / 4]; sq < D_L00_001D9F00[0]->bC; sq++, p += 4) {
            if (*(int *)p != 0) {
                D_L00_001D9F00[0]->f48[sq] = (int)(base + *(int *)p);
                relocate_asset_entry_pointers(D_L00_001D9F00[0], sq);
            }
        }
        D_L00_001BF140.i[0x44 / 4] = D_L00_001D9F00[0]->f48[0];
        for (i = 0, q2 = (char *)h + h->i[0x24 / 4]; i < h->i[0x20 / 4]; i++, q2 += 0x20)
            RegisterObjectRenderClass(base + *(int *)q2, (char *)h + h->i[0x44 / 4], q2 + 0x10, *(int *)(q2 + 4));
        if (D_L00_00226700[0] != 0)
            D_L00_001BF140.i[0x3C / 4] = D_L00_00226700[0];
        ref_L00_00303990_00((char *)h + h->i[0x24 / 4], h->i[0x20 / 4]);
        for (i = 0, q2 = (char *)h + h->i[0x2C / 4]; i < h->i[0x28 / 4]; i++, q2 += 0x30)
            RegisterShrubRenderClass(base + *(int *)q2, (char *)h + h->i[0x4C / 4], q2 + 0x10, q2 + 0x20, *(int *)(q2 + 4));
        if (D_L00_0021EA20[0] != 0)
            D_L00_001BF140.i[0x40 / 4] = D_L00_0021EA20[0];
        {
            char *p = base + h->i[0x68 / 4];
            D_L00_001BF140.p[0x34 / 4] = p;
            D_L00_001B1944 = (int)p;
        }
        func_US2_00292650((char *)h + h->i[0x5C / 4], h->i[0x58 / 4]);
        if (h->i[0xA4 / 4] != 0) {
            level_load_quadword_block(base + h->i[0xA4 / 4]);
        } else {
            qzero(&D_L00_001B1D20);
            qzero(&D_L00_001B1D30);
            qzero(&D_L00_001B1D40);
            qzero(&D_L00_001B1D50);
            D_L00_001B1D60 = 0;
        }
        if (h->i[0xA8 / 4] != 0)
            D_L00_001B1A44 = (int)(base + h->i[0xA8 / 4]);
        else
            D_L00_001B1A44 = 0;
        if (h->i[0xB0 / 4] != 0)
            D_L00_001B1A48 = (int)(base + h->i[0xB0 / 4]);
        else
            D_L00_001B1A48 = 0;
        {
            char *x1 = base + h->i[0x64 / 4];
            char *x2;
            D_L00_001BF140.p[0x30 / 4] = x1;
            x2 = (char *)h + h->i[0x54 / 4];
            tex_rebase_pack_fill_ranges((char *)h + h->i[0x6C / 4], x1, x2, h->i[0x50 / 4]);
        }
        base = (char *)((unsigned int)(base + used + 0x3F) & ~0x3F);
        if (D_L00_001B24D4 != D_L00_001C9340.i[0x18 / 4]) {
            char *dst;
            int size;
            do {
                D_L00_001C9340.p[0x10 / 4] = base;
                size = h->i[0x30 / 4];
            } while (0);
            dst = base;
            size *= 16;
            base += size;
            mem_fast_helper_c(dst, (char *)h + h->i[0x34 / 4], size);
            D_L00_001C9340.p[0x14 / 4] = base;
            base = (char *)(((unsigned int)(base + D_L00_001C9340.i[0x18 / 4] * 2) + 0x7F) & ~0x3F);
        }
        tab = (char *)h + h->i[0x70 / 4];
        span = (Span *)tab;
        {
            int nslots = span->count;
            D_L00_001B19EC = (Slot32 *)base;
            D_L00_001B19E8 = nslots;
            mem_copy_aligned(base, tab + span->off, nslots * 32);
            span++;
            base += nslots * 32;
        }
        e = tab + span->off;
        for (a3 = 0; a3 < D_L00_001B19E8; a3++) {
            if (D_L00_001B19EC[a3].h1A >= span->count) {
                STUB_printf(D_L00_001A95B8);
                D_L00_001B19EC[a3].h1A = -1;
            } else {
                D_L00_001B19EC[a3].h1A = *(unsigned short *)(e + D_L00_001B19EC[a3].h1A * 4);
            }
            D_L00_001B19EC[a3].i1C = 0;
        }
        end = base + 0x3F;
        span++;
        for (ci = 0, q = (char *)h + h->i[0x1C / 4]; ci < h->i[0x18 / 4]; ci++, span++, q += 0x20) {
            int cls = D_L00_001DA860[*(int *)(q + 4)];
            if (D_L00_001DA680[cls] == *(int *)(q + 4)) {
                if ((span->count != 0 || D_L00_001D9F00[cls]->bD != 0) && span->count - 1 != D_L00_001D9F00[cls]->bD)
                    STUB_printf(D_L00_001A95D8, D_L00_001DA680[cls], span->count - 1, D_L00_001D9F00[cls]->bD);
                {
                    int first;
                    e = tab + span->off;
                    first = *(int *)e;
                    e += 4;
                    for (k = 0; k < D_L00_001D9F00[cls]->bD; k++, e += 4) {
                        D_L00_001D9F00[cls]->slots[k].h1A = *(unsigned short *)e;
                        D_L00_001D9F00[cls]->slots[k].i1C = first + 1;
                    }
                }
            }
        }
        base = (char *)((unsigned int)end & ~0x3F);
        D_L00_001BF140.p[0x48 / 4] = base;
    }
    D_L00_001BF140.i[0x68 / 4] = func_US2_L00_003012A0(load);
    if (load)
        D_00152CE4[0] = -1;
    if (D_L00_001C9340.i[0xC / 4] != 0) {
        if (load)
            tutorial_reset_record_values();
        level_update_object_visibility(D_L00_001C9340.i[0]);
    }
    if (resume)
        RestoreSavedHeroState();
    else
        mem_clear_work_areas();
    D_L00_001B1AD0.f8 = 0;
    if (D_001A7A00.enabled != 0) {
        int m;
        for (m = D_L00_001B1E9C; m != D_L00_001B1EA0[0]; m += 0x100)
            moby_scale_by_difficulty(m);
    }
    moby_update_live_mobys();
    g_frame_l00_counter++;
    return 0;
}
