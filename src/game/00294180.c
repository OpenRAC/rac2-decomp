#include "include_asm.h"
#include "common.h"

typedef struct {
    s32 offset;
    s32 size;
    s32 pad08;
    s32 sectors;
    s32 pad10;
} StreamFile;

typedef struct {
    u8 pad[0x4B3C];
    s32 base;
    s32 pad4B40;
    StreamFile files[1];
} StreamBank;

typedef struct {
    s32 file;
    s32 slot;
    u8 *buf;
    s32 *hdr;
} StreamLoad;

typedef struct {
    void *data;
    void *addr;
    s32 size;
    s32 mode;
} SifDma;

extern StreamBank g_copy_setup_data;
extern u8 *D_001A7278 MACRO_ADDR;

extern void FlushCache(int);
extern int sceSifSetDma(SifDma *, int);
extern int sceSifDmaStat(int);
extern int load_start_disc_read_with_callback(void *, int, int, void (*)(int *, int), StreamLoad *);
extern void load_release_class_cache_slot(int *p, int a1);

/* Continues a streamed disc load. With go set to 0 it marks the load as finished; otherwise it sends the first chunk to the sound processor and starts reading the file. */
void load_continue_stream(StreamLoad *load, s32 go) {
    SifDma dma;
    u8 *buf;
    s32 *hdr;
    s32 slot_offset;
    s32 dma_id;

    if (go == 0) {
        load->file = -1;
    } else {
        if (g_copy_setup_data.files[load->file].sectors != 0) {
            slot_offset = load->slot * 0xC800;
            buf = load->buf;
            hdr = (s32 *)(buf + 0x18);
            dma.size = g_copy_setup_data.files[load->file].sectors << 11;
            dma.data = buf;
            dma.mode = 0;
            dma.addr = D_001A7278 + slot_offset;
            *(s32 *)(buf + 0x14) = 0xC000;
            hdr[0x28 / 4] = 0xC000;
            hdr[0x2C / 4] = 0xC000;
            FlushCache(0);
            dma_id = sceSifSetDma(&dma, 1);
            while (sceSifDmaStat(dma_id) >= 0) {
            }
        }
        load_start_disc_read_with_callback(load->buf, g_copy_setup_data.files[load->file].offset + g_copy_setup_data.base,
                      g_copy_setup_data.files[load->file].size, load_release_class_cache_slot, load);
    }
}
