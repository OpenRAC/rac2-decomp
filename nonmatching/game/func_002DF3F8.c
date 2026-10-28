/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections -frac2-qcopy.
 * Compiled 540 bytes; retail 564 bytes.
 * Carrying checks: 0/28 in us, pal and us2. No strict linked qualification.
 * The complete byte-copy, nibble-counter update and record stores are represented. Separate measured byte/float globals improved 524 to 540 bytes. Base lifetimes, loop index/value allocation and store scheduling still differ. Reopen using allocator evidence and a verified original record view.
 */
#include "common.h"
extern unsigned char D_00189E20[];
extern int D_001A79F0;
extern unsigned char D_0019B2E8[];
extern unsigned char D_0019B4A8[];
extern unsigned char D_00188660[];
extern unsigned char D_001A63A8[];
extern unsigned char ref_L00_002DF3F8_00[];
extern unsigned char ref_L00_002DF3F8_01[];
extern unsigned char ref_L00_002DF3F8_02[];
extern unsigned char ref_L00_002DF3F8_03[] __attribute__((sda));
extern unsigned char ref_L00_002DF3F8_05[] __attribute__((sda));
extern unsigned char ref_L00_002DF3F8_06[] __attribute__((sda));
extern float ref_L00_002DF3F8_07[] __attribute__((sda));
extern float ref_L00_002DF3F8_08[] __attribute__((sda));
extern float ref_L00_002DF3F8_09[] __attribute__((sda));
extern float ref_L00_002DF3F8_10[] __attribute__((sda));
extern int ref_L00_002DF3F8_04;
extern void func_00282AB0(void *, void *, int);

void func_002DF3F8(void *first, void *second)
{
    unsigned char *owner = D_00189E20;
    unsigned char *destination;
    unsigned char *source;
    unsigned char *packet;
    unsigned char *context;
    int i;
    int bank;
    if (owner[0x22B4] == 4)
        return;
    destination = ref_L00_002DF3F8_00;
    source = ref_L00_002DF3F8_01;
    func_00282AB0(destination, source, 0x404);
    destination += 0x404;
    source += 0x404;
    bank = D_001A79F0;
    for (i = 0; i < 0x7FF; i++, source++) {
        unsigned char value = *source;
        if (value && (value == 1 || (D_0019B2E8[(bank << 4) - 2 + value] & 0x80))) {
            unsigned char *counter;
            unsigned char bits;
            destination[i] = value;
            counter = D_0019B4A8 + (bank << 10) + (i >> 1);
            bits = *counter;
            if (i & 1) {
                if (((bits >> 4) & 7) != 7)
                    *counter = bits + 0x10;
            } else if ((bits & 7) != 7) {
                *counter = bits + 1;
            }
        }
    }
    packet = ref_L00_002DF3F8_02;
    *(int *)packet = 1;
    qcopy(packet + 0x10, first);
    qcopy(packet + 0x20, second);
    context = *(unsigned char **)(owner + 0x2290);
    *(int *)(packet + 0x30) = *(int *)(context + 0x38);
    *(int *)(packet + 0x34) = *(int *)(context + 0x3C);
    *(int *)(packet + 0x54) = owner[0x22B4];
    *(unsigned char **)(packet + 0x58) = context;
    *(int *)(packet + 0x5C) = *(short *)(owner + 0x24F2);
    *(int *)(packet + 0x38) = *(int *)(D_00188660 + 0x64);
    packet[0x3C] = D_00188660[0x68];
    packet[0x3D] = D_00188660[0x69];
    packet[0x3E] = D_00188660[0x6A];
    *(int *)(packet + 0xC64) = *(short *)(D_001A63A8 + 0x48);
    *(int *)(packet + 0xC68) = ref_L00_002DF3F8_04;
    packet[0x3F] = ref_L00_002DF3F8_03[0];
    packet[0x40] = ref_L00_002DF3F8_05[0];
    packet[0x41] = ref_L00_002DF3F8_06[0];
    *(float *)(packet + 0x44) = ref_L00_002DF3F8_07[0];
    *(float *)(packet + 0x48) = ref_L00_002DF3F8_08[0];
    *(float *)(packet + 0x4C) = ref_L00_002DF3F8_09[0];
    *(float *)(packet + 0x50) = ref_L00_002DF3F8_10[0];
}
