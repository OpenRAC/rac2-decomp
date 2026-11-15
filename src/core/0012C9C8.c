#include "common.h"
#include "structs.h"

extern void mpeg_wait_ipu_idle(void *);

extern int mpeg_peek_bits(void *, int);

extern void mpeg_skip_bits(void *, int);

extern void mpeg_skip_to_start_code(void *);

extern int mpeg_read_slice_header_extra(void *);

extern int mpeg_read_bits(void *, int);

extern void mpeg_skip_extra_info_bits(void *);

/* rac1-decomp src/core/00125630.c: func_00128BA8 */
/* Skips ahead in the video stream to the next start code. */
void mpeg_skip_to_start_code(void *decoder_ptr) {
    int pad;

    mpeg_wait_ipu_idle(decoder_ptr);
    pad = -(((int)IPU_BP) & 7) & 7;
    if (pad != 0) {
        mpeg_skip_bits(decoder_ptr, pad);
    }
    while (mpeg_peek_bits(decoder_ptr, 0x18) != 1) {
        mpeg_skip_bits(decoder_ptr, 8);
    }
}

/* rac1-decomp src/core/00125630.c: func_00128C28 */
/* Reads the rest of a slice header: the quantiser scale and any extra bytes. Always returns 0. */
int mpeg_read_slice_header_extra(void *decoder_ptr) {
    *(int *)((char *)decoder_ptr + 0x1B4) = mpeg_read_bits(decoder_ptr, 5);
    if (mpeg_read_bits(decoder_ptr, 1) != 0) {
        mpeg_read_bits(decoder_ptr, 1);
        mpeg_skip_bits(decoder_ptr, 7);
        mpeg_skip_extra_info_bits(decoder_ptr);
    }
    return 0;
}


extern int r1_func_00128A58_0012CBC0(void *, int);

extern void r1_func_00129180_0012CBC0(void *);

extern void mpeg_read_picture_header(void *);

extern void r1_func_00128E68_0012CBC0(void *);

extern void r1_func_001291C8_0012CBC0(void *, int);

extern int r1_func_00128A58_0012CBC0();

extern void r1_func_00128E68_0012CBC0();

extern void r1_func_00129180_0012CBC0();

extern void r1_func_001291C8_0012CBC0();

/* rac1-decomp src/core/00125630.c: func_00128DA0 */
/* pictureHeader (libmpeg.a:mpc.o): ISO/IEC 13818-2 6.2.3 picture_header().
 * temporal_reference (+bits 10) is kept live across the whole function to
 * feed r1_func_001291C8_0012CBC0 (updateTempTackData) at the end. picture_coding_type
 * (+0x150) is re-read from the struct at each use rather than kept in a
 * local -- it must survive calls that could (as far as the compiler
 * knows) touch the struct. P_TYPE/B_TYPE (2/3) is the classic
 * (x-2)<2u range check; B_TYPE alone is a plain ==3.
 */
/* Reads a picture header: its type and the precision of its motion vectors. */
void mpeg_read_picture_header(void *decoder_ptr) {
    char *s = (char *)decoder_ptr;
    int temporal_reference = r1_func_00128A58_0012CBC0(s, 10);

    *(int *)(s + 0x150) = r1_func_00128A58_0012CBC0(s, 3);   /* picture_coding_type */
    r1_func_00128A58_0012CBC0(s, 16);                         /* vbv_delay, discarded */

    if ((unsigned int)(*(int *)(s + 0x150) - 2) < 2) {
        *(int *)(s + 0x154) = r1_func_00128A58_0012CBC0(s, 1);  /* full_pel_forward_vector */
        *(int *)(s + 0x158) = r1_func_00128A58_0012CBC0(s, 3);  /* forward_f_code */
    }
    if (*(int *)(s + 0x150) == 3) {
        *(int *)(s + 0x15C) = r1_func_00128A58_0012CBC0(s, 1);  /* full_pel_backward_vector */
        *(int *)(s + 0x160) = r1_func_00128A58_0012CBC0(s, 3);  /* backward_f_code */
    }

    r1_func_00129180_0012CBC0(s);   /* extra_bit_information */
    r1_func_00128E68_0012CBC0(s);   /* extension_and_user_data */
    r1_func_001291C8_0012CBC0(s, temporal_reference);  /* Update_Temporal_Reference_Tacking_Data */
}


/* rac1-decomp src/core/00125630.c: func_00128F90 (_pictureCodingExtension).
   Reached from the extension dispatcher func_0012CA68: extension id 0x8 calls
   this function (func_00130300's table) -- it parses an MPEG-2 picture coding
   extension: the four f_codes, intra DC precision, q_scale_type, intra VLC
   format and alternate scan go straight into IPU_CTRL (0x10002010), the rest
   into the decoder state. The composite display fields are skipped. */
typedef struct {
    unsigned char pad_0[0xD4];
    int pict_struct0;               /* 0xD4 */
    unsigned char pad_D8[0x8C];
    int f_code00;                   /* 0x164 */
    int f_code01;                   /* 0x168 */
    int f_code10;                   /* 0x16C */
    int f_code11;                   /* 0x170 */
    int picture_structure;          /* 0x174 */
    int top_field_first;            /* 0x178 */
    int frame_pred_frame_dct;       /* 0x17C */
    int concealment_mvs;            /* 0x180 */
    int repeat_first_field;         /* 0x184 */
    int progressive_frame;          /* 0x188 */
} PicExt_0012CDB0;

/* Reads the picture coding extension: motion vector precision, field or frame layout and scan settings. */
void mpeg_read_picture_coding_extension(void *decoder_ptr) {
    PicExt_0012CDB0 *dec = decoder_ptr;
    int picture_structure_bits;
    int q_scale_ctrl;
    int vlc_format_ctrl;
    int alt_scan_ctrl;

    dec->f_code00 = mpeg_read_bits(dec, 4);
    dec->f_code01 = mpeg_read_bits(dec, 4);
    dec->f_code10 = mpeg_read_bits(dec, 4);
    dec->f_code11 = mpeg_read_bits(dec, 4);
    *(int *)0x10002010 = (*(int *)0x10002010 & 0xFFFCFFFF) | (mpeg_read_bits(dec, 2) << 0x10);
    picture_structure_bits = mpeg_read_bits(dec, 2);
    dec->picture_structure = picture_structure_bits;
    if (dec->pict_struct0 == 0) {
        dec->pict_struct0 = picture_structure_bits;
    }
    dec->top_field_first = mpeg_read_bits(dec, 1);
    dec->frame_pred_frame_dct = mpeg_read_bits(dec, 1);
    dec->concealment_mvs = mpeg_read_bits(dec, 1);
    q_scale_ctrl = (IPU_CTRL & 0xFFBFFFFF) | (mpeg_read_bits(dec, 1) << 0x16);
    IPU_CTRL = q_scale_ctrl;
    vlc_format_ctrl = (IPU_CTRL & 0xFFDFFFFF) | (mpeg_read_bits(dec, 1) << 0x15);
    IPU_CTRL = vlc_format_ctrl;
    alt_scan_ctrl = (IPU_CTRL & 0xFFEFFFFF) | (mpeg_read_bits(dec, 1) << 0x14);
    IPU_CTRL = alt_scan_ctrl;
    dec->repeat_first_field = mpeg_read_bits(dec, 1);
    mpeg_read_bits(dec, 1);
    dec->progressive_frame = mpeg_read_bits(dec, 1);
    if (mpeg_read_bits(dec, 1) != 0) {
        mpeg_read_bits(dec, 1);
        mpeg_read_bits(dec, 3);
        mpeg_read_bits(dec, 1);
        mpeg_read_bits(dec, 7);
        mpeg_read_bits(dec, 8);
    }
}
