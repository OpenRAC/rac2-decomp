#include "common.h"
#include "structs.h"

extern void r1_func_00127378(int arg0);

extern void mpeg_report_error(void *, void *);

extern int r1_func_00128A58(void *, int);

extern char r1_D_00153C00[];

extern char r1_D_00153C28[];

extern void r1_func_00113968(void);

extern void r1_func_00114438(void *, void *);

/* rac1-decomp src/core/0012AC80.c: func_0012CA70 */
/*
 * _sequenceExtension (libmpeg.a:init.o): ISO/IEC 13818-2 6.2.2.3
 * sequence_extension(), matching mpeg2decode's gethdr.c almost line for
 * line but reading two combined bitfields with r1_func_00128A58: a 28-bit
 * fetch covers profile_and_level_indication(8) + progressive_sequence(1)
 * + chroma_format(2) + horizontal_size_extension(2) +
 * vertical_size_extension(2) + bit_rate_extension(12) + marker_bit(1); a
 * 16-bit fetch covers vbv_buffer_size_extension(8) + low_delay(1) +
 * frame_rate_extension_n(2) + frame_rate_extension_d(5) (the last three
 * read and dropped). chroma_format must be 1 (4:2:0) and
 * profile_and_level_indication one of three literal bytes (0x48/0x58/
 * 0x44); either failing reports through func_00130288. Ends by folding
 * the extension bits into sequenceHeader's fields exactly as the
 * reference decoder's
 * `horizontal_size = (horizontal_size_extension<<12) | (horizontal_size&0xfff)`
 * et al.
 */
void mpeg_read_sequence_extension(void *decoder) {
    char *bytes = (char *)decoder;
    unsigned int bits1, bits2;
    unsigned int chroma_format, h_ext, v_ext, bitrate_ext;
    unsigned int progressive, profile, vbv_ext;

    *(int *)(bytes + 0x848) = 1;
    r1_func_00127378(0);

    bits1 = r1_func_00128A58(bytes, 0x1C);
    bitrate_ext = (bits1 >> 1) & 0xFFF;
    chroma_format = (bits1 >> 17) & 3;
    v_ext = (bits1 >> 13) & 3;
    h_ext = (bits1 >> 15) & 3;

    *(unsigned int *)(bytes + 0x140) = chroma_format;
    if (chroma_format != 1) {
        mpeg_report_error(bytes, r1_D_00153C00);
    }

    progressive = (bits1 >> 19) & 1;
    *(unsigned int *)(bytes + 0x13C) = progressive;
    profile = bits1 >> 20;

    bits2 = r1_func_00128A58(bytes, 0x10);
    vbv_ext = bits2 >> 8;

    if (profile != 0x48 && profile != 0x58 && profile != 0x44) {
        mpeg_report_error(bytes, r1_D_00153C28);
    }

    *(int *)(bytes + 0x124) = (h_ext << 12) | (*(int *)(bytes + 0x124) & 0xFFF);
    *(int *)(bytes + 0x128) = (v_ext << 12) | (*(int *)(bytes + 0x128) & 0xFFF);
    *(int *)(bytes + 0x134) += bitrate_ext << 18;
    *(int *)(bytes + 0x138) += vbv_ext << 10;
}

/* rac1-decomp src/core/0012AC80.c: func_0012CBA0 */
/*
 * MPEG-2 sequence_display_extension(): video_format (3 bits), then
 * colour_description (1) and, when set, colour_primaries,
 * transfer_characteristics and matrix_coefficients (8 each; the last is
 * kept at +0x144); display_horizontal_size (14) to +0x148, a marker
 * bit, display_vertical_size (14) to +0x14C.
 *
 * Plain C, exact under 2.9-ee. (Under 2.95.3 it needed the marker bit's
 * read to go through a void view of the reader, `r1_func_00128A58_v`: as a
 * value call it reset $v0's readers and the +0x148 store lost the
 * scheduler tie to the next call's argument setup, 8/140.)
 */
void mpeg_read_sequence_display_ext(void *decoder) {
    char *bytes = (char *)decoder;

    r1_func_00128A58(bytes, 3);
    if (r1_func_00128A58(bytes, 1) != 0) {
        r1_func_00128A58(bytes, 8);
        r1_func_00128A58(bytes, 8);
        *(int *)(bytes + 0x144) = r1_func_00128A58(bytes, 8);
    }
    *(int *)(bytes + 0x148) = r1_func_00128A58(bytes, 0xE);
    r1_func_00128A58(bytes, 1);
    *(int *)(bytes + 0x14C) = r1_func_00128A58(bytes, 0xE);
}

/* rac1-decomp src/core/00113A70.c: func_00113AC8 */
/* Retail is a bare tail jump: Sony's 2.9-ee, which builds this SDK object,
   emits it for a void function that ends in a call. */
/* Hands the object on to a handler together with a fixed callback. */
void mpeg_call_handler_with_callback(void *mpeg) {
    r1_func_00114438(mpeg, r1_func_00113968);
}
extern void mpeg_report_error_fixed_a(void *arg0);
extern char D_0013BE88[];

/* Reports a fixed video error message. */
void mpeg_report_error_fixed_a(void *decoder) {
    mpeg_report_error(decoder, D_0013BE88);
}

extern void mpeg_report_error_fixed_b(void *arg0);
extern char D_0013BEA0[];

/* Reports a fixed video error message. */
void mpeg_report_error_fixed_b(void *decoder) {
    mpeg_report_error(decoder, D_0013BEA0);
}

extern void mpeg_report_error_fixed_c(void *arg0);
extern char D_0013BED8[];

/* Reports a fixed video error message. */
void mpeg_report_error_fixed_c(void *decoder) {
    mpeg_report_error(decoder, D_0013BED8);
}


/* Its entry is four bytes into the catalogued row, after one word of 0xCDCDCDCD fill. */
extern void sceIpuStopDMA(void *arg0);

/* Stops the picture DMA for this decoder and saves its state. */
void mpeg_stop_dma(void *mpeg) {
    sceIpuStopDMA(*(char **)((char *)mpeg + 0x40) + 0x4C);
}
