#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

/* lot10: privately byte-gated bodies. */
extern s32 func_00126470(u8 *, s32, s32, s32, s32, s32, s32, s32);

extern s32 FlushCache(s32);

extern s32 func_00126730(u8 *, u8 *);

extern s32 D_001A72E0[] __attribute__((sda));

extern s32 g_screen_width[] __attribute__((sda));

extern void gfx_wait_for_dma_status_bits(int);

extern void func_00284000_1(void);

extern void SetupFS_AA_buffer(int, int, int, int, int, int);

/* Copies a rectangle of the screen picture into the given buffer. */
void gfx_capture_screen_rect(s32 left, s32 top, s32 width, s32 height, u8 *destination) {
    u8 image[112];
    func_00126470(image, (D_001A72E0[0]<<8)>>16, (g_screen_width[0]<<10)>>16,
                0x30,(short)left,(short)top,(short)width,(short)height);
    FlushCache(0);
    func_00126730(image,destination);
}

typedef struct {
    char reserved[0x8C];
    int first, second;
} Limits_285788;
extern Limits_285788 g_modal_state;

/* Sets two size limits, using the defaults 64 and 16 when a value is zero. */
void menu_set_size_limits(int first, int second) {
    int first_limit = 64;
    int second_limit = 16;
    if (first != 0) first_limit = first;
    if (second != 0) second_limit = second;
    g_modal_state.first = first_limit;
    g_modal_state.second = second_limit;
}

extern int D_001A8A5C __attribute__((sda));

/* Returns the current menu mode. */
int menu_get_mode(void) {
    return D_001A8A5C;
}
