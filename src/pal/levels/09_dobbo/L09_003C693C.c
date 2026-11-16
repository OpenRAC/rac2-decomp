#include "include_asm.h"


#include "common.h"
extern float FastAddRotations(float, float);
extern void BuildObjectAttachmentTransforms();
extern void moby_update_attached_transforms(unsigned char *, unsigned char *);

/* func_L09_003C0DF8 is defined in L09_002F8BA0-mover.c (its own MACRO_ADDR declarations). */

/* Two-state gate on the record's byte 0x20. In state 0, as long as the live
   word the sub-object opens with is not -1, the record is stamped 0xFF, the
   shared eight-argument starter is run on the sub-object's track block and the
   record flips to state 1. In state 1 the sub-object's first float is scaled by
   2*pi/21600 (a per-frame 1/100 s turn rate) and folded into the record's own
   angle before its track block is stepped again. */
void turn_record_update_pal(unsigned char *a0) {
    unsigned char *s0 = a0;
    unsigned char *s1 = *(unsigned char **)(s0 + 0x68);
    switch (s0[0x20]) {
    case 0:
        if (*(long long *)s1 == -1) {
            break;
        }
        {
            unsigned char stamp = 0xFF;
            *(unsigned char *)(s0 + 0x30) = stamp;
        }
        BuildObjectAttachmentTransforms(s0, s1 + 0x30, 0x64, *(int *)(s1 + 4), *(int *)s1,
                          -1, 7, 0);
        s1[0xC5A] = 1;
        s0[0x20] = 1;
        break;
    case 1:
        *(float *)(s0 + 0xF0) = FastAddRotations(
            *(float *)(s0 + 0xF0), *(float *)(s1 + 8) * 0.0003490659f);
        moby_update_attached_transforms(s0, s1 + 0x30);
        break;
    }
}

