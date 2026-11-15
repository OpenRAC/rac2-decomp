#include "common.h"
#include "structs.h"

extern int mpeg_decode_picture_2(void *, int, int);

extern int mpeg_decode_field(void *, int, int);

extern int mpeg_decode_or_skip_frame(void *, int, int);

/* rac1-decomp src/core/0012AC80.c: func_0012C058 */
/* Hands the call on by the inner object's +0x174 mode: func_0012FD60 for
   mode 3, func_0012FEC0 otherwise, with the caller's arguments.

   Returns its callees' values: retail keeps the frame and calls both, and
   2.9-ee tail-calls each arm (bare `j`, SIZE 40/68) when it is void. */
/* Picks the frame or field decoder depending on the video mode and runs it. */
int mpeg_decode_picture_2(void *mpeg, int frame_index, int frame_limit) {
    Obj40 *decoder = ((Wrapper *)mpeg)->obj;
    if (decoder->unk174 != 3) {
        return mpeg_decode_field(mpeg, frame_index, frame_limit);
    } else {
        return mpeg_decode_or_skip_frame(mpeg, frame_index, frame_limit);
    }
}
