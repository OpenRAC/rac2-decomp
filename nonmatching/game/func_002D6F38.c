/* GPT-6.1 Sol (high), USA v1.01, game compiler -O2 -G8 -ffunction-sections.
 * Best check.py: 1708/1708 bytes, 0 of 28 places match.
 * Based on current RAC1 src/game/pause.c DrawMapScreen (Lombyte/OpenRAC,
 * GPL-3.0) and RaC2 retail. This is not a semantically validated native port.
 * All required declarations follow; compile this as a separate -g8.c unit.
 *
 * Measured improvements over the earlier 1648-byte draft:
 * - Real map/menu/header/disc structures replace the raw offset macros.
 * - Rejected warp requests return 1, not the back-button result.
 * - The visited-bitset is D_00139768, not the earlier draft's D_00149768.
 * - Disc request branches retain a pointer to the selected size word and
 *   share the read call. A distinct texture-base local fixes its lifetime.
 *
 * Remaining: the close/invalid-warp branches merge into the final return
 * rather than retail's backward branch to the earlier return-1 block;
 * menu/map bases, warp-save stores and streaming arguments allocate or
 * schedule differently. The first rejection is the saved register at +4.
 * The warp_map symbol is an alias of the same map state, expressing the
 * measured second selection read at retail 0x002D7060; it still gets a
 * different base lifetime from retail. Replacing that view with the ordinary
 * field folds the second signed guard and reload away.
 *
 * Negative trials: -g and the existing -frac2-keep-block-order profile do
 * not repair this body; pointer-typing the buffers is instruction-neutral.
 * Next: reconstruct the original warp helper/control-flow source boundary
 * and the streaming call's live argument/size-pointer arrangement. Avoid
 * repeating store-order changes or raw-offset rewrites without new evidence.
 *
 * Claude Opus 5.5 (xhigh), task v2091, body above left unchanged (still the
 * closest by size). Two measured findings for the next attempt:
 * - Put a label (close_map) on the first `return 1` inside the 0xD00/locked
 *   test and make the invalid-warp tests and the warp's final return
 *   `goto close_map`. That gives retail's backward branches into that block:
 *   if the warp keeps its own `return 1`, jump2 cross-jumps the labelled
 *   block away. On its own this is 1716 bytes.
 * - Drop warp_map. Use `MapState *warp = &D_001C4FA0;` assigned after the
 *   prev computation, and write that as
 *   `if (D_001C4FA0.level) { prev = D_001C4FA0.level; if (prev == 24)
 *   prev = 0; } else prev = 21;`. This gives retail's CSE boundary at the
 *   join: a fresh fp+0x4FA0 warp base in s1, a reload of level, and
 *   D_001F2840 rebuilt into s0 after the bitset test. But reorg then fills
 *   the beqz slot with the move. Retail has `beqz a1,J [li s2,21]; move
 *   s2,a1; xori; movz`, so jump.c's "if {x=a; goto l} x=b" hoist of
 *   prev = 21 must happen only in jump2. With `if (!level) prev = 21; else`
 *   the post-cse1 jump hoists it already, and cse2 then skips around the
 *   join and shares the bases. A ternary or a separate local in the else arm
 *   gives movn. 1720 bytes.
 */
typedef struct {
    char reserved[0xE0];
    int back;
} MapPage;
typedef struct {
    char reserved[8];
    int state;
    char reservedC[8];
    MapPage *current;
    int next;
    char reserved1C[0x28 - 0x1C];
    int mode;
    char reserved2C[0xDB - 0x2C];
    unsigned char pending;
    char reservedDC[0xF4 - 0xDC];
    int warp;
    char reservedF8[8];
    MapPage *saved_page;
    int saved_state;
    char reserved108[0x134 - 0x108];
    int locked;
    char reserved138[8];
    int saved_mode;
} MapMenu;
typedef struct {
    char reserved[4];
    short mode;
    char reserved6[0x78 - 6];
} MapRead;
typedef struct {
    int mask, chunks, pixels, palette, texture, layer1, layer2;
} MapHeader;
typedef struct {
    char reserved[0xC];
    void *mask;
    char reserved10[0x28 - 0x10];
    int stream;
    char reserved2C[0x230 - 0x2C];
    int level, loaded;
    void *source;
    int source_level;
    int source_size;
    int reserved244;
    MapHeader *header;
    int image_vram, clut_vram, texture_vram[3];
    char reserved260[8];
    long texture[3];
    char reserved280[8];
    int slots[5], ids[5], selected, sizes[5];
} MapState;
typedef struct { int offset, size; } MapEntry;
typedef struct {
    char reserved[0x36C];
    int base;
    char reserved370[0x14F0 - 0x370];
    MapEntry maps[28];
    MapEntry alt_maps[28];
} MapDisc;
extern MapMenu D_001F2840;
extern MapState D_001C4FA0;
extern MapState warp_map __asm__("D_001C4FA0");
extern MapRead D_001A63A8;
extern MapDisc D_0014B540;
extern int D_00138180[];
extern char D_0025E680[], D_0025A498[], D_001BAD40[];
extern int D_00139768[];
extern int D_001A72D4 __attribute__((sda));
extern int D_001A7478;
extern int D_001A7478_sda __attribute__((sda));
extern int *D_001AA4F0 __attribute__((sda));
extern int D_001A79F0;
extern unsigned char D_001A7AFD, D_001A7BE8[];
extern char D_0018D278[];
extern int func_00295D00(void);
extern void func_00295C50(int);
extern void func_0029D830(void);
extern void func_002E5E58(int, int, int), func_002C9E60(int);
extern int func_00288AA0(void *, int), func_00288BE8(void *);
extern int func_00295A10(int), func_00295828(int), func_00295A80(void);
extern void func_00295788(int, int), func_0029D4D0(int, void *);
extern int func_002DE550(int), func_002DE618(int);
extern void func_00295BE8(void *, void *, void *, void *);
extern void func_00297730(int, void *, void *), func_00297400(int, void *, void *);
extern long func_00294D80(int, int, void *, void *, int, int);
extern void func_0029D0E0(void), func_0029DEA8(int, int);
extern int func_002956E8(void), func_002958B8(void);
extern void func_002EEED0(int, void *, int, int, int);
extern int func_002B7B18(int, int, int);

int func_002D6F38(void)
{
    int prev, idx, id, slot, n, buf, pick, next, k;
    MapHeader *hdr;
    char *pix, *pal, *base, *a, *tex, *b, *c;
    int *size;
    int sector, origin, read_buffer, sectors, mask;
    char *tbase;

    func_00295D00();
    if (D_001F2840.current != (MapPage *)D_0025E680) {
        prev = D_001C4FA0.level;
        if ((D_00138180[0x1C4 / 4] & 0xD00) && !D_001F2840.locked) {
close_map:
            return 1;
        }
        if (D_00138180[0x1C4 / 4] & 0x10) {
            int result;
            if (D_001F2840.current->back)
                D_001F2840.next = D_001F2840.current->back;
            else if (!D_001F2840.locked) {
                result = -1;
                goto back_done;
            }
            result = 0;
back_done:
            return result;
        }
        if (D_00138180[0x1C4 / 4] & 0x40)
            D_001F2840.next = (int)D_0025A498;
        if ((D_00138180[0x1C4 / 4] & 0x20) && D_001C4FA0.level >= 0 && !D_001F2840.pending) {
            MapState *warp = &warp_map;
            if (!D_001C4FA0.level)
                prev = 21;
            else {
                prev = D_001C4FA0.level;
                if (prev == 24) prev = 0;
            }
            if (warp->level < 0) goto close_map;
            mask = D_00139768[(unsigned)warp->level >> 2] & (1 << (warp->level & 31));
            if (mask == 0) goto close_map;
            D_001A72D4 = D_001F2840.mode;
            func_002C9E60(0);
            {
                int warp_level = warp->level;
                int saved_mode = D_001A7478;
                MapPage *saved_page = D_001F2840.current;
                int saved_state = D_001F2840.state;
                D_001F2840.saved_mode = saved_mode;
                D_001F2840.saved_page = saved_page;
                D_001F2840.saved_state = saved_state;
                D_001F2840.warp = warp_level;
            }
            D_001A7478_sda = 2;
            func_00288AA0(D_001BAD40, prev);
            func_00288BE8(D_001BAD40);
            return 1;
        }
        idx = func_00295A10(D_001C4FA0.level);
        if (idx >= 0) {
            if ((D_00138180[0x1C4 / 4] & 8) && idx < 27) {
                if (D_001AA4F0[idx + 1]) func_00295C50(D_001AA4F0[idx + 1]);
            }
            if ((D_00138180[0x1C4 / 4] & 4) && idx) {
                if (D_001AA4F0[idx - 1]) func_00295C50(D_001AA4F0[idx - 1]);
            }
        }
        if (D_001C4FA0.level != prev) {
            func_002E5E58(3, 0, 0);
            func_0029D830();
        }
    }
    if (D_001F2840.current == (MapPage *)D_0025E680)
        D_001C4FA0.stream = 1;
    id = D_001C4FA0.level;
    if (D_001A7AFD) id += 256;
    slot = func_00295828(id);
    if (D_001C4FA0.level != D_001C4FA0.loaded && slot != -1) {
        n = func_00295A80();
        if (D_001C4FA0.slots[0] && n > 0) {
            func_00295788(n, 0);
            if (!slot) slot = n;
        }
        func_0029D4D0(D_001C4FA0.slots[slot], D_001C4FA0.header);
        hdr = D_001C4FA0.header;
        pix = (char *)hdr + hdr->pixels;
        pal = (char *)hdr + hdr->palette;
        buf = func_002DE550(0);
        if (buf) {
            base = (char *)D_001C4FA0.header;
            a = base + hdr->mask + 8;
            if (D_001C4FA0.level == D_001A79F0)
                func_00295BE8(pal, pix, pal, D_001C4FA0.mask);
            else {
                if (D_001A7BE8[D_001C4FA0.level])
                    func_00297730(buf, D_0018D278 + (D_001C4FA0.level << 11), base + hdr->chunks);
                else
                    func_00297400(buf, a, a);
                func_00295BE8(pal, pix, pal, (void *)buf);
            }
        }
        tbase = (char *)D_001C4FA0.header;
        tex = tbase + hdr->texture;
        b = tbase + hdr->layer1 + 0x420;
        c = tbase + hdr->layer2 + 0x420;
        D_001C4FA0.texture[0] = func_00294D80(7, 7, tex + 32, tex + 0x420, D_001C4FA0.clut_vram, D_001C4FA0.texture_vram[0]);
        D_001C4FA0.texture[1] = func_00294D80(7, 7, tex + 32, b, D_001C4FA0.clut_vram, D_001C4FA0.texture_vram[1]);
        D_001C4FA0.texture[2] = func_00294D80(7, 7, tex + 32, c, D_001C4FA0.clut_vram, D_001C4FA0.texture_vram[2]);
        if (buf) func_00294D80(9, 9, pal, pal, 0x3FF000, D_001C4FA0.image_vram);
        func_0029D0E0();
        if (buf) func_002DE618(buf);
        D_001C4FA0.slots[0] = (int)pix;
        D_001C4FA0.loaded = D_001C4FA0.level;
        func_0029DEA8(D_001C4FA0.level, 0);
    }
    if (!D_001A63A8.mode && D_001C4FA0.selected != -1) {
        D_001F2840.pending = 0;
        D_001C4FA0.ids[D_001C4FA0.selected] ^= 0x1000;
        D_001C4FA0.selected = -1;
    }
    pick = -1;
    if (D_001C4FA0.stream && !D_001A63A8.mode) {
        pick = func_002956E8();
        if (pick != -1) {
            next = func_002958B8();
            if (next != -1) {
                k = (D_001A79F0 + D_001C4FA0.source_level == 0) ? 0 : 256;
                if (k == next) {
                    func_002EEED0(D_001C4FA0.slots[pick], D_001C4FA0.source, 0, D_001C4FA0.source_size, 0);
                    D_001C4FA0.sizes[pick] = D_001C4FA0.source_size;
                } else {
                    if (next & 256) {
                        sector = D_0014B540.alt_maps[next ^ 256].offset;
                        size = &D_0014B540.alt_maps[next ^ 256].size;
                        origin = D_0014B540.base;
                        read_buffer = D_001C4FA0.slots[pick];
                        sectors = *size;
                    } else {
                        sector = D_0014B540.maps[next].offset;
                        size = &D_0014B540.maps[next].size;
                        origin = D_0014B540.base;
                        read_buffer = D_001C4FA0.slots[pick];
                        sectors = *size;
                    }
                    func_002B7B18(read_buffer, origin + sector, sectors);
                    D_001C4FA0.sizes[pick] = (*size << 11) >> 4;
                }
                D_001F2840.pending = 1;
                D_001C4FA0.ids[pick] = next | 0x1000;
                D_001C4FA0.selected = pick;
            }
        }
    }
    slot = func_00295828(id);
    if (D_001C4FA0.level != D_001C4FA0.loaded && !D_001A63A8.mode && slot == -1 && pick == slot)
        func_00295A80();
    return 0;
}
