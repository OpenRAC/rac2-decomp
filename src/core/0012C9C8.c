#include "common.h"
#include "structs.h"

extern void func_0012C3B0(void *);

extern int func_0012C680(void *, int);

extern void func_0012C788(void *, int);

extern void func_0012C9C8(void *);

extern int func_0012CA48(void *);

extern int func_0012C878(void *, int);

extern void func_0012CFA0(void *);

/* rac1-decomp src/core/00125630.c: func_00128BA8 */
void func_0012C9C8(void *arg0) {
    int pad;

    func_0012C3B0(arg0);
    pad = -(((int)IPU_BP) & 7) & 7;
    if (pad != 0) {
        func_0012C788(arg0, pad);
    }
    while (func_0012C680(arg0, 0x18) != 1) {
        func_0012C788(arg0, 8);
    }
}

/* rac1-decomp src/core/00125630.c: func_00128C28 */
int func_0012CA48(void *arg0) {
    *(int *)((char *)arg0 + 0x1B4) = func_0012C878(arg0, 5);
    if (func_0012C878(arg0, 1) != 0) {
        func_0012C878(arg0, 1);
        func_0012C788(arg0, 7);
        func_0012CFA0(arg0);
    }
    return 0;
}


extern int r1_func_00128A58_0012CBC0(void *, int);

extern void r1_func_00129180_0012CBC0(void *);

extern void func_0012CBC0(void *);

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
void func_0012CBC0(void *arg0) {
    char *s = (char *)arg0;
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

void func_0012CDB0(void *arg) {
    PicExt_0012CDB0 *arg0 = arg;
    int temp_2_35;
    int temp_6_65;
    int temp_6_77;
    int temp_6_89;

    arg0->f_code00 = func_0012C878(arg0, 4);
    arg0->f_code01 = func_0012C878(arg0, 4);
    arg0->f_code10 = func_0012C878(arg0, 4);
    arg0->f_code11 = func_0012C878(arg0, 4);
    *(int *)0x10002010 = (*(int *)0x10002010 & 0xFFFCFFFF) | (func_0012C878(arg0, 2) << 0x10);
    temp_2_35 = func_0012C878(arg0, 2);
    arg0->picture_structure = temp_2_35;
    if (arg0->pict_struct0 == 0) {
        arg0->pict_struct0 = temp_2_35;
    }
    arg0->top_field_first = func_0012C878(arg0, 1);
    arg0->frame_pred_frame_dct = func_0012C878(arg0, 1);
    arg0->concealment_mvs = func_0012C878(arg0, 1);
    temp_6_65 = (IPU_CTRL & 0xFFBFFFFF) | (func_0012C878(arg0, 1) << 0x16);
    IPU_CTRL = temp_6_65;
    temp_6_77 = (IPU_CTRL & 0xFFDFFFFF) | (func_0012C878(arg0, 1) << 0x15);
    IPU_CTRL = temp_6_77;
    temp_6_89 = (IPU_CTRL & 0xFFEFFFFF) | (func_0012C878(arg0, 1) << 0x14);
    IPU_CTRL = temp_6_89;
    arg0->repeat_first_field = func_0012C878(arg0, 1);
    func_0012C878(arg0, 1);
    arg0->progressive_frame = func_0012C878(arg0, 1);
    if (func_0012C878(arg0, 1) != 0) {
        func_0012C878(arg0, 1);
        func_0012C878(arg0, 3);
        func_0012C878(arg0, 1);
        func_0012C878(arg0, 7);
        func_0012C878(arg0, 8);
    }
}
