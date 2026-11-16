#include "names.h"
/* func_US2_00292650, the USA v2.00 copy of func_00291DE0: the same C, where each entry's last two
   shorts become byte log2 dimensions and a pixel format (the layout func_US2_002ECC48 reads). A
   negative width marks a 4-bit texture (GS PSMT4, 0x14, against PSMT8, 0x13), and both dimensions
   then go through func_00282C30 first. This unit has no strength reduction, as the template's. */
typedef struct {
    long long clear;
} Pad8;

typedef struct {
    Pad8 head;
    short image;
    short palette;
    unsigned char width;
    unsigned char height;
    short format;
} Entry_001B9740;

extern int g_gfx_entry_count __attribute__((sda));
extern Entry_001B9740 g_texture_upload_params[];
extern int log2dim(int);
extern int subtract_integer_with_clamp(int);

void func_US2_00292650(int *p, int count) {
    for (g_gfx_entry_count = 0; g_gfx_entry_count < count; g_gfx_entry_count++) {
        int w0 = *p++;
        int w1 = *p++;
        int w2 = *p++;
        int w3 = *p++;
        g_texture_upload_params[g_gfx_entry_count].palette = w0 >> 4;
        g_texture_upload_params[g_gfx_entry_count].image = w1 >> 4;
        g_texture_upload_params[g_gfx_entry_count].format = 0x13;
        if (w2 < 0) {
            g_texture_upload_params[g_gfx_entry_count].format = 0x14;
            w2 = subtract_integer_with_clamp(w2);
            w3 = subtract_integer_with_clamp(w3);
        }
        g_texture_upload_params[g_gfx_entry_count].width = log2dim(w2);
        g_texture_upload_params[g_gfx_entry_count].height = log2dim(w3);
        g_texture_upload_params[g_gfx_entry_count].head.clear = 0;
    }
}
