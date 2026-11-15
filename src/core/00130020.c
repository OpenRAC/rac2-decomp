#include "common.h"
#include "structs.h"

extern void r1_func_0012C278();

extern int mpeg_stop_decoding(void *);

extern void r1_func_0012C278(void *);

extern void r1_func_00127378(int arg0);

extern void mpeg_restart_hardware(void *arg0);

extern void mpeg_set_scratchpad_buffers(void *);

extern int r1_func_0011D960(void);

extern void r1_func_0011D9A8(void);

extern void mpeg_reset_hardware(void *arg0);

extern void r1_func_0012CF98(int, int);

extern char r1_D_00153BD8[];

/* Unprototyped: r1_func_0011A6C8 is a varargs definition (blocked as such),
   but calling one is fine -- only defining one needs stdarg.h. */
extern void r1_func_0011A6C8();

extern void mpeg_print_error(void *);

extern void mpeg_report_error(void *, void *);

/* _errMessage (func_00130250) sprintf's its format and passes the
   format's arguments on untouched in $a1-$a3, so it is called here
   without a prototype, with the value the "%08x" reports. */
extern void mpeg_format_error();

extern void r1_func_00116248(void *);

/* rac1-decomp src/core/0012AC80.c: func_0012C200 */
/* Stops the current video decoding. Returns 1 if it was running. */
int mpeg_stop_decoding(void *mpeg) {
    Wrapper *wrapper = (Wrapper *)mpeg;
    Obj40 *decoder = wrapper->obj;
    int result = 0;

    if (decoder->unk004 != 0 && decoder->unk008 != 0) {
        r1_func_0012C278((void *)decoder);
        wrapper->unk08 = decoder->unk118 - decoder->unk0AC;
        decoder->unk004 = 0;
        result = 1;
    }
    return result;
}

/* rac1-decomp src/core/0012AC80.c: func_0012C268 */
/* Tail call: the constant argument setup lands in the jump's delay slot,
   so the field store precedes it. r1_func_00127378 is defined above. */
/* Marks the decoder as not started and restarts the picture hardware. */
void mpeg_restart_hardware(void *decoder) {
    *(int *)((char *)decoder + 0x848) = 0;
    r1_func_00127378(1);
}

extern char D_0013BDC8[];
extern void mpeg_report_error(void *, void *);
extern void mpeg_output_picture(void *, int, int);
extern void mpeg_output_field_pair(void *, int, int, int);

/* Finishes the last decoded picture, or reports an error if a decode was still in progress. */
void mpeg_finish_picture(char *decoder) {
    int frameNumber = *(int *)(decoder + 0x118);
    if (*(int *)(decoder + 0x120) != 0)
        mpeg_report_error(decoder, D_0013BDC8);
    else if (*(int *)(decoder + 0x174) == 3)
        mpeg_output_picture(decoder, *(int *)(decoder + 0x1BC), frameNumber - 1);
    else
        mpeg_output_field_pair(decoder, *(int *)(decoder + 0x1CC), *(int *)(decoder + 0x1DC), frameNumber - 1);
    *(int *)(decoder + 0x120) = 0;
}

/* rac1-decomp src/core/0012AC80.c: func_0012C2F8 */
/*
 * Point the object's four scratchpad pointers at 0x70000000 and clear a
 * flag. Exact under 2.9-ee. Under 2.95.3 it was 2 of 24 words off:
 * that compiler saved $ra before $s1 in the prologue, where retail (and
 * 2.9-ee) saves $s1 first -- the prologue-order residual of the core
 * spill rewrite, not a source question.
 *
 * What does matter: `int a = 0x70000000;` must be written
 * BEFORE the call. An earlier round reverted this at 8 bytes short
 * having tried binding the constants to locals declared AFTER the call,
 * which changes nothing because gcc folds them straight back into the
 * stores. Declared before the call, the pseudo's live range crosses the
 * call, so the allocator gives it a CALLEE-SAVED register and the
 * function pays retail's sd/ld $s1 pair -- 8 bytes. gcc still
 * rematerialises the `lui` after the call, exactly as retail does, so
 * the only trace of the earlier definition is the register class.
 *
 * That is the general point: a constant hoisted above a call does not
 * survive as a value (constant propagation puts it back), but it does
 * survive as a register-class decision. Where retail spends a
 * callee-saved register on something that looks like it needs no
 * register at all, the source defined it before the call.
 */
/* Points the decoder buffers at fast scratchpad memory and clears a flag. */
void mpeg_set_scratchpad_buffers(void *decoder) {
    char *bytes = (char *)decoder;
    int scratchpadBase = 0x70000000;

    r1_func_00127378(1);
    *(int *)(bytes + 0x590) = scratchpadBase;
    *(int *)(bytes + 0x594) = 0x70001800;
    *(int *)(bytes + 0x6D0) = 0x70001B00;
    *(int *)(bytes + 0x6D4) = 0x70003300;
    *(int *)(bytes + 0x810) = 0;
}

/* rac1-decomp src/core/0012AC80.c: func_0012C358 */
/*
 * _clearEach (libmpeg.a:init.o): per-stream hardware reset shared by
 * sceMpegInit's shape -- flag the bitstream state "in use" (+0x818 = 1),
 * clear its slice-address latch (+0x1B0), then the same SIF-flag toggle
 * (0x1000F590 set/cleared around bit 0x10000, re-reading 0x1000F520 fresh
 * each time) and three DMA channel registers zeroed (0x1000B000/B400/D400),
 * gated IOP kick via r1_func_0011D960/r1_func_0011D9A8, three more registers
 * zeroed (0x1000B020/B420/D420), IPU_CTRL (0x10002010) set to 0x40000000,
 * and a tail call into r1_func_0012CF98(0, 0).
 */
/* Resets the picture decoding hardware: its DMA channels and the picture unit. */
void mpeg_reset_hardware(void *decoder) {
    char *bytes = (char *)decoder;
    int interruptsWereOn;

    *(int *)(bytes + 0x818) = 1;
    *(int *)(bytes + 0x1B0) = 0;
    interruptsWereOn = r1_func_0011D960();

    D_ENABLEW =
        D_ENABLER | 0x10000;
    D3_CHCR = 0;
    D4_CHCR = 0;
    D9_CHCR = 0;
    D_ENABLEW =
        D_ENABLER & ~0x10000;

    if (interruptsWereOn != 0) {
        r1_func_0011D9A8();
    }

    D3_QWC = 0;
    D4_QWC = 0;
    D9_QWC = 0;
    IPU_CTRL = 0x40000000;
    r1_func_0012CF98(0, 0);
}

/* rac1-decomp src/core/0012AC80.c: func_0012C420 */
/* Prints a video error message with one value. */
void mpeg_print_error(void *value) {
    r1_func_0011A6C8(r1_D_00153BD8, value);
}

/* rac1-decomp src/core/0012AC80.c: func_0012C430 */
/* Builds a video error message and reports it. */
void mpeg_format_error(void *mpeg) {
    char message[0x100];
    r1_func_00116248(message);
    mpeg_report_error(mpeg, message);
}
