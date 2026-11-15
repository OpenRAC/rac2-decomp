#include "common.h"
#include "structs.h"

extern void mpeg_wait_ipu_idle(void *);

extern void r1_func_0012C468(void *, void *);

/* func_0012C508 returns a short: its epilogue sign-extends $v0. */
extern short mpeg_read_ipu_vlc_code(int, int);

extern void mpeg_skip_bits(void *, int);

extern int mpeg_decode_macroblock_modes(void *, int *, int *, int *, void *, void *, void *);

extern char r1_D_00153998[];

extern int mpeg_read_bits(void *, int);

extern void mpeg_read_motion_vector(void *, int *, int *, int, int, int, int, int);

extern void r1_func_00128270_x(void *, int *, int *, int *, int, int, int, int, int, int, int) __asm__("func_0012C090");

extern void mpeg_start_ipu_to_memory_dma(void *, int);

extern void mpeg_send_ipu_command(char *, unsigned int);

typedef struct {
    char pad000[0x11C];
    int error_flag;
    char pad120[0x30];
    int picture_coding_type;
    int full_pel_forward;
    int forward_f_code;
    int full_pel_backward;
    int backward_f_code;
    int f_code00;
    int f_code01;
    int f_code10;
    int f_code11;
    int picture_structure;
    char pad178[4];
    int frame_pred_frame_dct;
    int concealment_mvs;
    char pad184[0x2C];
    int unk1B0;
    int quant_scale;
    char pad1B8[0x810 - 0x1B8];
    int cur_slot;
    char pad814[0x848 - 0x814];
    int unk848;
} MbDec;

extern void mpeg_decode_motion_vector(int *, int, int, int, int);

/* rac1-decomp src/core/00125630.c: func_00127D40 */
/* Decodes one macroblock's modes and motion vectors through the IPU VLC engine (libmpeg _decMB0). Adapted from Lombyte (GPL-3.0) for PAL: sdk/library/_decMB0.c, _decMB0. */
int mpeg_decode_macroblock_modes(void *decoder_ptr, int *mb_type_out, int *motion_type_out, int *dct_type_out, void *pmv_arg, void *mvfs_out, void *dmvector_out) {
    MbDec *d = decoder_ptr;
    int *mb = pmv_arg;
    int *dct_type_ptr;
    int *mvfs_ptr;
    int mb_type_bits;
    int motionVectorCount;
    int mvFormat;
    int mv_scale;
    int dual_prime;
    int f_code_fwd;
    int f_code_bwd;
    int coding_type;
    int dct_type_value;
    int two;
    unsigned int g1;
    unsigned int g2;

    IPU_CTRL = (IPU_CTRL & 0xF8FFFFFF) | (d->picture_coding_type << 24);
    dct_type_ptr = dct_type_out;
    mvfs_ptr = mvfs_out;
    mb_type_bits = mpeg_read_ipu_vlc_code((int)d, 1);
    *mb_type_out = mb_type_bits;
    if (mb_type_bits == 0) {
        r1_func_0012C468(d, r1_D_00153998);
        d->error_flag = 1;
        return 0;
    }
    if (mb_type_bits & 0xC) {
        if (d->picture_structure == 3 && d->frame_pred_frame_dct != 0) {
            *motion_type_out = 2;
        } else {
            *motion_type_out = mpeg_read_bits(d, 2);
        }
    } else if ((mb_type_bits & 1) && d->concealment_mvs != 0) {
        *motion_type_out = ((d->picture_structure ^ 3) == 0) ? 2 : 1;
    }
    if (d->picture_structure == 3) {
        motionVectorCount = ((*motion_type_out ^ 1) == 0) ? 2 : 1;
        mvFormat = *motion_type_out == 2;
    } else {
        two = 2;
        mvFormat = 0;
        motionVectorCount = ((*motion_type_out ^ two) == 0) ? 2 : 1;
    }
    mv_scale = 0;
    dual_prime = *motion_type_out == 3;
    if (mvFormat == 0) {
        mv_scale = d->picture_structure == 3;
    }
    dct_type_value = 0;
    if (d->picture_structure == 3 && d->frame_pred_frame_dct == 0 && (*mb_type_out & 3) != 0) {
        dct_type_value = mpeg_read_bits(d, 1);
    } else {
        dct_type_value = 0;
    }
    *dct_type_ptr = dct_type_value;
    if (*mb_type_out & 0x10) {
        d->quant_scale = mpeg_read_bits(d, 5);
    }
    if ((*mb_type_out & 8) || ((*mb_type_out & 1) && d->concealment_mvs != 0)) {
        if (d->unk848 != 0) {
            r1_func_00128270_x(d, mb, dmvector_out, mvfs_ptr, 0, motionVectorCount, mvFormat, d->f_code00 - 1, d->f_code01 - 1, dual_prime, mv_scale);
        } else {
            f_code_fwd = d->forward_f_code - 1;
            mpeg_read_motion_vector(d, mb, dmvector_out, f_code_fwd, f_code_fwd, 0, 0, d->full_pel_forward);
        }
    }
    if (d->error_flag != 0) {
        return 0;
    }
    if (*mb_type_out & 4) {
        if (d->unk848 != 0) {
            r1_func_00128270_x(d, mb, dmvector_out, mvfs_ptr, 1, motionVectorCount, mvFormat, d->f_code10 - 1, d->f_code11 - 1, 0, mv_scale);
        } else {
            f_code_bwd = d->backward_f_code - 1;
            mpeg_read_motion_vector(d, mb + 2, dmvector_out, f_code_bwd, f_code_bwd, 0, 0, d->full_pel_backward);
        }
    }
    if (d->error_flag != 0) {
        return 0;
    }
    if ((*mb_type_out & 1) && d->concealment_mvs != 0) {
        mpeg_skip_bits(d, 1);
    }
    if ((*mb_type_out & 3) != 0) {
        mpeg_start_ipu_to_memory_dma(*(void **)((char *)d + d->cur_slot * 0x140 + 0x594), 0x300);
        mpeg_wait_ipu_idle(d);
        g1 = ((*mb_type_out & 1) << 27) | (d->quant_scale << 16);
        g2 = (d->unk1B0 << 26) | 0x20000000;
        mpeg_send_ipu_command((char *)d, (g1 | g2) | (*dct_type_ptr << 25));
    } else {
        *(int *)((char *)d + d->cur_slot * 0x140 + 0x6CC) = 1;
    }
    d->unk1B0 = 0;
    if (d->error_flag != 0) {
        return 0;
    }
    if (((*mb_type_out & 1) || (d->unk1B0 = 1, (*mb_type_out & 1) != 0)) && d->concealment_mvs == 0) {
        mb[5] = 0;
        mb[4] = 0;
        mb[1] = 0;
        mb[0] = 0;
        mb[7] = 0;
        mb[6] = 0;
        mb[3] = 0;
        mb[2] = 0;
    }
    coding_type = d->picture_coding_type;
    if (coding_type == 2) {
        if (!(*mb_type_out & 9)) {
            mb[0] = (mb[1] = (mb[4] = (mb[5] = 0)));
            if (d->picture_structure == 3) {
                *motion_type_out = coding_type;
            } else {
                *motion_type_out = 1;
                *mvfs_ptr = d->picture_structure == 2;
            }
        }
    }
    return 1;
}

/* rac1-decomp src/core/00125630.c: func_001281E8 */
/* decode_motion_vector (libmpeg.a:mpc.o): ISO/IEC 13818-2 motion_vector()
 * component reconstruction, matching mpeg2decode reference source
 * (motion.c) decode_motion_vector() line for line. full_pel_vector is
 * MPEG-1 (ISO/IEC 11172-1) support; called from func_0012C230
 * (motionVector, already matched in this file).
 */
/* Adds a motion vector change read from the stream to the previous vector, wrapping it around when it goes out of range. */
void mpeg_decode_motion_vector(int *pred, int r_size, int motion_code, int motion_residual, int full_pel_vector) {
    int lim, vec;

    lim = 16 << r_size;
    vec = full_pel_vector ? (*pred >> 1) : (*pred);

    if (motion_code > 0) {
        vec += ((motion_code - 1) << r_size) + motion_residual + 1;
        if (vec >= lim)
            vec -= lim + lim;
    } else if (motion_code < 0) {
        vec -= ((-motion_code - 1) << r_size) + motion_residual + 1;
        if (vec < -lim)
            vec += lim + lim;
    }
    *pred = full_pel_vector ? (vec << 1) : vec;
}

/* rac1-decomp src/core/00125630.c: func_00128270 */
/* motionVectors (libmpeg.a:mpc.o): ISO/IEC 13818-2 6.2.5.2/6.3.17.2/7.6.3
 * motion_vectors(), matching mpeg2decode reference source (motion.c)
 * almost line for line, with the bitstream-state pointer threaded through
 * explicitly as the new first argument (this file's convention) instead
 * of read from a global. func_0012C230 is motionVector (already matched
 * in this file); func_0012C878 is Get_Bits.
 */
/* Reads the motion vectors of one macroblock for forward or backward prediction and stores them in the vector table. */
void mpeg_read_motion_vectors(void *decoder_ptr, int PMV[][2][2], int *dmvector, int mvfs[][2],
                    int s_idx, int motion_vector_count, int mv_format,
                    int h_r_size, int v_r_size, int dmv, int mvscale) {
    if (motion_vector_count == 1) {
        if (mv_format == 0 && dmv == 0) {
            mvfs[1][s_idx] = mvfs[0][s_idx] = mpeg_read_bits(decoder_ptr, 1);
        }
        mpeg_read_motion_vector(decoder_ptr, PMV[0][s_idx], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        PMV[1][s_idx][0] = PMV[0][s_idx][0];
        PMV[1][s_idx][1] = PMV[0][s_idx][1];
    } else {
        mvfs[0][s_idx] = mpeg_read_bits(decoder_ptr, 1);
        mpeg_read_motion_vector(decoder_ptr, PMV[0][s_idx], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        mvfs[1][s_idx] = mpeg_read_bits(decoder_ptr, 1);
        mpeg_read_motion_vector(decoder_ptr, PMV[1][s_idx], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
    }
}
