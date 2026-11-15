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
    int errorFlag;
    char pad120[0x30];
    int pictureCodingType;
    int fullPelForward;
    int forwardFCode;
    int fullPelBackward;
    int backwardFCode;
    int fCode00;
    int fCode01;
    int fCode10;
    int fCode11;
    int pictureStructure;
    char pad178[4];
    int framePredFrameDct;
    int concealmentMvs;
    char pad184[0x2C];
    int unk1B0;
    int quantScale;
    char pad1B8[0x810 - 0x1B8];
    int curSlot;
    char pad814[0x848 - 0x814];
    int unk848;
} MbDec;

extern void mpeg_decode_motion_vector(int *, int, int, int, int);

/* rac1-decomp src/core/00125630.c: func_00127D40 */
/* Decodes one macroblock's modes and motion vectors through the IPU VLC engine (libmpeg _decMB0). Adapted from Lombyte (GPL-3.0) for PAL: sdk/library/_decMB0.c, _decMB0. */
int mpeg_decode_macroblock_modes(void *decoderPtr, int *mbTypeOut, int *motionTypeOut, int *dctTypeOut, void *pmvArg, void *mvfsOut, void *dmvectorOut) {
    MbDec *d = decoderPtr;
    int *mb = pmvArg;
    int *dctTypePtr;
    int *mvfsPtr;
    int mbTypeBits;
    int motionVectorCount;
    int mvFormat;
    int mvScale;
    int dualPrime;
    int fCodeFwd;
    int fCodeBwd;
    int codingType;
    int dctTypeValue;
    int two;
    unsigned int g1;
    unsigned int g2;

    IPU_CTRL = (IPU_CTRL & 0xF8FFFFFF) | (d->pictureCodingType << 24);
    dctTypePtr = dctTypeOut;
    mvfsPtr = mvfsOut;
    mbTypeBits = mpeg_read_ipu_vlc_code((int)d, 1);
    *mbTypeOut = mbTypeBits;
    if (mbTypeBits == 0) {
        r1_func_0012C468(d, r1_D_00153998);
        d->errorFlag = 1;
        return 0;
    }
    if (mbTypeBits & 0xC) {
        if (d->pictureStructure == 3 && d->framePredFrameDct != 0) {
            *motionTypeOut = 2;
        } else {
            *motionTypeOut = mpeg_read_bits(d, 2);
        }
    } else if ((mbTypeBits & 1) && d->concealmentMvs != 0) {
        *motionTypeOut = ((d->pictureStructure ^ 3) == 0) ? 2 : 1;
    }
    if (d->pictureStructure == 3) {
        motionVectorCount = ((*motionTypeOut ^ 1) == 0) ? 2 : 1;
        mvFormat = *motionTypeOut == 2;
    } else {
        two = 2;
        mvFormat = 0;
        motionVectorCount = ((*motionTypeOut ^ two) == 0) ? 2 : 1;
    }
    mvScale = 0;
    dualPrime = *motionTypeOut == 3;
    if (mvFormat == 0) {
        mvScale = d->pictureStructure == 3;
    }
    dctTypeValue = 0;
    if (d->pictureStructure == 3 && d->framePredFrameDct == 0 && (*mbTypeOut & 3) != 0) {
        dctTypeValue = mpeg_read_bits(d, 1);
    } else {
        dctTypeValue = 0;
    }
    *dctTypePtr = dctTypeValue;
    if (*mbTypeOut & 0x10) {
        d->quantScale = mpeg_read_bits(d, 5);
    }
    if ((*mbTypeOut & 8) || ((*mbTypeOut & 1) && d->concealmentMvs != 0)) {
        if (d->unk848 != 0) {
            r1_func_00128270_x(d, mb, dmvectorOut, mvfsPtr, 0, motionVectorCount, mvFormat, d->fCode00 - 1, d->fCode01 - 1, dualPrime, mvScale);
        } else {
            fCodeFwd = d->forwardFCode - 1;
            mpeg_read_motion_vector(d, mb, dmvectorOut, fCodeFwd, fCodeFwd, 0, 0, d->fullPelForward);
        }
    }
    if (d->errorFlag != 0) {
        return 0;
    }
    if (*mbTypeOut & 4) {
        if (d->unk848 != 0) {
            r1_func_00128270_x(d, mb, dmvectorOut, mvfsPtr, 1, motionVectorCount, mvFormat, d->fCode10 - 1, d->fCode11 - 1, 0, mvScale);
        } else {
            fCodeBwd = d->backwardFCode - 1;
            mpeg_read_motion_vector(d, mb + 2, dmvectorOut, fCodeBwd, fCodeBwd, 0, 0, d->fullPelBackward);
        }
    }
    if (d->errorFlag != 0) {
        return 0;
    }
    if ((*mbTypeOut & 1) && d->concealmentMvs != 0) {
        mpeg_skip_bits(d, 1);
    }
    if ((*mbTypeOut & 3) != 0) {
        mpeg_start_ipu_to_memory_dma(*(void **)((char *)d + d->curSlot * 0x140 + 0x594), 0x300);
        mpeg_wait_ipu_idle(d);
        g1 = ((*mbTypeOut & 1) << 27) | (d->quantScale << 16);
        g2 = (d->unk1B0 << 26) | 0x20000000;
        mpeg_send_ipu_command((char *)d, (g1 | g2) | (*dctTypePtr << 25));
    } else {
        *(int *)((char *)d + d->curSlot * 0x140 + 0x6CC) = 1;
    }
    d->unk1B0 = 0;
    if (d->errorFlag != 0) {
        return 0;
    }
    if (((*mbTypeOut & 1) || (d->unk1B0 = 1, (*mbTypeOut & 1) != 0)) && d->concealmentMvs == 0) {
        mb[5] = 0;
        mb[4] = 0;
        mb[1] = 0;
        mb[0] = 0;
        mb[7] = 0;
        mb[6] = 0;
        mb[3] = 0;
        mb[2] = 0;
    }
    codingType = d->pictureCodingType;
    if (codingType == 2) {
        if (!(*mbTypeOut & 9)) {
            mb[0] = (mb[1] = (mb[4] = (mb[5] = 0)));
            if (d->pictureStructure == 3) {
                *motionTypeOut = codingType;
            } else {
                *motionTypeOut = 1;
                *mvfsPtr = d->pictureStructure == 2;
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
void mpeg_read_motion_vectors(void *decoderPtr, int PMV[][2][2], int *dmvector, int mvfs[][2],
                    int s_idx, int motion_vector_count, int mv_format,
                    int h_r_size, int v_r_size, int dmv, int mvscale) {
    if (motion_vector_count == 1) {
        if (mv_format == 0 && dmv == 0) {
            mvfs[1][s_idx] = mvfs[0][s_idx] = mpeg_read_bits(decoderPtr, 1);
        }
        mpeg_read_motion_vector(decoderPtr, PMV[0][s_idx], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        PMV[1][s_idx][0] = PMV[0][s_idx][0];
        PMV[1][s_idx][1] = PMV[0][s_idx][1];
    } else {
        mvfs[0][s_idx] = mpeg_read_bits(decoderPtr, 1);
        mpeg_read_motion_vector(decoderPtr, PMV[0][s_idx], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        mvfs[1][s_idx] = mpeg_read_bits(decoderPtr, 1);
        mpeg_read_motion_vector(decoderPtr, PMV[1][s_idx], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
    }
}
