#include "common.h"

typedef unsigned long PackedVector;
typedef struct {
    unsigned short reserved0, reserved2, reserved4, qwc;
    unsigned short baseBytes, scaleCount, scaleBytes, positionCount;
    PackedVector initial;
    PackedVector entries[0];
} PackedTransformPacket;
extern unsigned char *D_0018C0B0;
extern void func_L00_00316F60(unsigned char *);
extern PackedVector func_L00_002EE660(const void *, float);

/* Adapted from RAC1 pack_pose in overlays/shared/hero_idle_and_animation.c
 * (OpenRAC/rac1-decomp, GPL-3.0). */
/* Pack scratchpad joint transforms relative to the model's default pose. */
void func_L00_002AA200(int *indices, PackedTransformPacket *out, unsigned char *baseline,
                       int padding, unsigned char *object) {
    PackedVector *entry;
    PackedVector value;
    int count, scales, positions, i, ordinal, firstBytes;
    if (!object) object = D_0018C0B0;
    entry = (PackedVector *)(out + 1);
    func_L00_00316F60(object);
    out->initial = 0x7FFF000000000000UL;
    /* 0x70000000 is the EE scratchpad, not a level address. */
    count = 1;
    for (i = 1; indices[i] >= 0; i++) {
        *entry++ = pack_vector_s16((void *)((indices[i] << 6) + 0x70000000), 32768.0f);
        count++;
    }
    if (padding > 0) {
        int remaining = padding;
        do {
            *entry = 0x7FFF000000000000UL;
            remaining--;
            entry++;
            count++;
        } while (remaining != 0);
    }
    scales = 0;
    i = 1;
    firstBytes = count << 3;
    for (; indices[i] >= 0; i++) {
        value = pack_vector_s16((void *)(0x70000010 + (indices[i] << 6)), 4096.0f);
        if ((value & 0xFFFFFFFFFFFFUL) != 0x100010001000UL) {
            *entry = value & 0xFFFFFFFFFFFFUL;
            scales++;
            *(unsigned short *)((unsigned char *)entry + 6) = i | 0x8000;
            entry++;
        }
    }
    positions = 0;
    for (ordinal = 1; indices[ordinal] >= 0; ordinal++) {
        value = pack_vector_s16((void *)(0x70000020 + (indices[ordinal] << 6)), 1.0f);
        if ((value & 0xFFFFFFFFFFFFUL) !=
            (pack_vector_s16(*(unsigned char **)(baseline + 0x18) + (ordinal << 4), 1.0f) & 0xFFFFFFFFFFFFUL)) {
            *entry = value & 0xFFFFFFFFFFFFUL;
            positions++;
            *(unsigned short *)((unsigned char *)entry + 6) = ordinal;
            entry++;
        }
    }
    if ((unsigned int)entry & 15) *entry++ = 0;
    out->positionCount = positions;
    out->baseBytes = firstBytes;
    out->qwc = ((unsigned char *)entry - (unsigned char *)&out->initial) >> 4;
    out->scaleCount = scales;
    out->scaleBytes = (count + scales) << 3;
    out->reserved2 = 0;
    out->reserved4 = 0;
    out->reserved0 = 0;
}
