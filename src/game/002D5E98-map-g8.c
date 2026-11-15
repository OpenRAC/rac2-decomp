#include "include_asm.h"
#include "common.h"

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

/* Runs the map screen: handles buttons, loads the map picture for the chosen page and streams the next one from disc. */
int func_002D6F38(int arg)
{
    int prev, idx, id, slot, n, buf, pick, next, k;
    MapHeader *hdr;
    char *pix, *pal, *base, *a, *tex, *b, *c;
    int mapped;
    char *tbase;

    UpdateMapOverlayPanZoom();
    if (gPauseMenuState.current != (MapPage *)D_0025E680) {
        prev = gMapOverlayState.level;
        if ((gPadState[0x1C4 / 4] & 0xD00) && !gPauseMenuState.locked) {
close_map:
            return 1;
        }
        if (gPadState[0x1C4 / 4] & 0x10) {
            int result;
            if (gPauseMenuState.current->back)
                gPauseMenuState.next = gPauseMenuState.current->back;
            else if (!gPauseMenuState.locked) {
                result = -1;
                goto back_done;
            }
            result = 0;
back_done:
            return result;
        }
        if (gPadState[0x1C4 / 4] & 0x40)
            gPauseMenuState.next = (int)D_0025A498;
        if ((gPadState[0x1C4 / 4] & 0x20) && gMapOverlayState.level >= 0 && !gPauseMenuState.pending) {
            if (gMapOverlayState.level == 0)
                mapped = 21;
            else if (gMapOverlayState.level == 24)
                mapped = 0;
            else
                mapped = gMapOverlayState.level;
            if (gMapOverlayState.level < 0) goto close_map;
            {
                unsigned int word = (unsigned)gMapOverlayState.level >> 2;
                int bit = 1 << (gMapOverlayState.level & 0x1F);
                if (!(D_00139768[word] & bit)) goto close_map;
            }
            D_001A72D4 = gPauseMenuState.mode;
            RestoreSavedScreenImage(0);
            {
                int saved_mode = D_001A7478;
                gPauseMenuState.saved_page = gPauseMenuState.current;
                gPauseMenuState.saved_state = gPauseMenuState.state;
                gPauseMenuState.warp = gMapOverlayState.level;
                gPauseMenuState.saved_mode = saved_mode;
            }
            D_001A7478_sda = 2;
            PushRequestQueue(D_001BAD40, mapped);
            LaunchQueuedRequest(D_001BAD40);
            goto close_map;
        }
        idx = FindMapTableIndex(gMapOverlayState.level);
        if (idx >= 0) {
            if ((gPadState[0x1C4 / 4] & 8) && idx < 27) {
                if (D_001AA4F0[idx + 1]) SetCurrentMapAndRefresh(D_001AA4F0[idx + 1]);
            }
            if ((gPadState[0x1C4 / 4] & 4) && idx) {
                if (D_001AA4F0[idx - 1]) SetCurrentMapAndRefresh(D_001AA4F0[idx - 1]);
            }
        }
        if (gMapOverlayState.level != prev) {
            PlaySoundFromGlobalBank(3, 0, 0);
            UpdateEntryStates();
        }
    }
    if (gPauseMenuState.current == (MapPage *)D_0025E680)
        gMapOverlayState.stream = 1;
    id = gMapOverlayState.level;
    if (D_001A7AFD) id += 256;
    slot = FindMapCacheSlotById(id);
    if (gMapOverlayState.level != gMapOverlayState.loaded && slot != -1) {
        n = ChooseMapSlotToReuse();
        if (gMapOverlayState.slots[0] && n > 0) {
            MoveMapCacheSlot(n, 0);
            if (!slot) slot = n;
        }
        fast_decompress(gMapOverlayState.slots[slot], gMapOverlayState.header);
        hdr = gMapOverlayState.header;
        pix = (char *)hdr + hdr->pixels;
        pal = (char *)hdr + hdr->palette;
        buf = ClaimFreeStreamChunk(0);
        if (buf) {
            base = (char *)gMapOverlayState.header;
            a = base + hdr->mask + 8;
            if (gMapOverlayState.level == gCurrentMapIndex)
                compose_bitmap_from_mask(pal, pix, pal, gMapOverlayState.mask);
            else {
                if (D_001A7BE8[gMapOverlayState.level])
                    DecodeOcclusionMap(buf, D_0018D278 + (gMapOverlayState.level << 11), base + hdr->chunks);
                else
                    BuildMapMaskBitmap(buf, a, a);
                compose_bitmap_from_mask(pal, pix, pal, (void *)buf);
            }
        }
        tbase = (char *)gMapOverlayState.header;
        tex = tbase + hdr->texture;
        b = tbase + hdr->layer1 + 0x420;
        c = tbase + hdr->layer2 + 0x420;
        gMapOverlayState.texture[0] = register_8bit_texture(7, 7, tex + 32, tex + 0x420, gMapOverlayState.clut_vram, gMapOverlayState.texture_vram[0]);
        gMapOverlayState.texture[1] = register_8bit_texture(7, 7, tex + 32, b, gMapOverlayState.clut_vram, gMapOverlayState.texture_vram[1]);
        gMapOverlayState.texture[2] = register_8bit_texture(7, 7, tex + 32, c, gMapOverlayState.clut_vram, gMapOverlayState.texture_vram[2]);
        if (buf) register_8bit_texture(9, 9, pal, pal, 0x3FF000, gMapOverlayState.image_vram);
        func_0029D0E0();
        if (buf) ReleaseStreamChunk(buf);
        gMapOverlayState.slots[0] = (int)pix;
        gMapOverlayState.loaded = gMapOverlayState.level;
        func_0029DEA8(gMapOverlayState.level, 0);
    }
    if (!gMusicState.mode && gMapOverlayState.selected != -1) {
        gPauseMenuState.pending = 0;
        gMapOverlayState.ids[gMapOverlayState.selected] ^= 0x1000;
        gMapOverlayState.selected = -1;
    }
    pick = -1;
    if (gMapOverlayState.stream && !gMusicState.mode) {
        pick = SelectFirstUsableMapSlot();
        if (pick != -1) {
            next = PickNextMap();
            if (next != -1) {
                k = (gCurrentMapIndex + gMapOverlayState.source_level == 0) ? 0 : 256;
                if (k == next) {
                    UploadRecordsToBufferSlot(gMapOverlayState.slots[pick], gMapOverlayState.source, 0, gMapOverlayState.source_size, 0);
                    gMapOverlayState.sizes[pick] = gMapOverlayState.source_size;
                } else {
                    if (next & 256) {
                        int *size;
                        int sector, origin, read_buffer, sectors;
                        origin = gCopySetupData.base;
                        sector = gCopySetupData.alt_maps[next ^ 256].offset;
                        size = &gCopySetupData.alt_maps[next ^ 256].size;
                        read_buffer = gMapOverlayState.slots[pick];
                        sectors = *size;
                        StartDiscRead(read_buffer, sector + origin, sectors);
                        gMapOverlayState.sizes[pick] = (*size << 11) >> 4;
                    } else {
                        int *size;
                        int sector, origin, read_buffer, sectors;
                        origin = gCopySetupData.base;
                        sector = gCopySetupData.maps[next].offset;
                        size = &gCopySetupData.maps[next].size;
                        read_buffer = gMapOverlayState.slots[pick];
                        sectors = *size;
                        StartDiscRead(read_buffer, sector + origin, sectors);
                        gMapOverlayState.sizes[pick] = (*size << 11) >> 4;
                    }
                    gPauseMenuState.pending = 1;
                }
                gMapOverlayState.ids[pick] = next | 0x1000;
                gMapOverlayState.selected = pick;
            }
        }
    }
    slot = FindMapCacheSlotById(id);
    if (gMapOverlayState.level != gMapOverlayState.loaded && !gMusicState.mode && slot == -1 && pick == slot)
        ChooseMapSlotToReuse();
    return 0;
}
