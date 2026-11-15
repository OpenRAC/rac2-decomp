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

extern StreamBank D_0014B540;
extern u8 *D_001A7278 MACRO_ADDR;

extern void func_0011AEA0(int);
extern int func_0011AFE0(SifDma *, int);
extern int func_0011AFC0(int);
extern int func_002B7BC0(void *, int, int, void (*)(int *, int), StreamLoad *);
extern void func_00294130(int *p, int a1);

/* Starts or ends a streamed read: with go set, builds the DMA header for the file's next sector run; with go clear, releases the file. */
void func_00294180(StreamLoad *load, s32 go) {
    SifDma dma;
    u8 *buf;
    s32 *hdr;
    s32 off;
    s32 id;

    if (go == 0) {
        load->file = -1;
    } else {
        if (D_0014B540.files[load->file].sectors != 0) {
            off = load->slot * 0xC800;
            buf = load->buf;
            hdr = (s32 *)(buf + 0x18);
            dma.size = D_0014B540.files[load->file].sectors << 11;
            dma.data = buf;
            dma.mode = 0;
            dma.addr = D_001A7278 + off;
            *(s32 *)(buf + 0x14) = 0xC000;
            hdr[0x28 / 4] = 0xC000;
            hdr[0x2C / 4] = 0xC000;
            func_0011AEA0(0);
            id = func_0011AFE0(&dma, 1);
            while (func_0011AFC0(id) >= 0) {
            }
        }
        func_002B7BC0(load->buf, D_0014B540.files[load->file].offset + D_0014B540.base,
                      D_0014B540.files[load->file].size, func_00294130, load);
    }
}
