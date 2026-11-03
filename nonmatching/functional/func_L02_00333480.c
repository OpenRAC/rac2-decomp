/* functional: high. Same reads, writes and calls with the same arguments as retail (read in full against level 02's code); the frame word is named D_L02_001B30C8 in both reads (retail takes the first by $gp, the second by lui; the same word). SAME on 1 call (level 22 copy), 107 of 113 instructions ran; the unrun ones (the no-data return 8 and the once-per-frame early return) were read against retail. */
/* func_L02_00333480 (452 bytes): per-frame update of an object's movement controller (data from func_L00_0032C638): once per frame (D_L02_001B30C8), inverts its matrix, rotates its position into the data's vector, resets the controller when more than a frame was missed, then runs the three stages func_L02_00332A80 / 00332D28 / 00332EF0; returns the controller's state word (+0x94), or 8 without data. */
/* GPT-6.1 Sol high, task v0502, 2026-10-28.
 * USA v1.01: 444/452 bytes, 0/9 places; pinned upstream game compiler.
 * Profile: -O2 -G8 -ffunction-sections -mno-split-addresses.
 * Uses common.h qcopy_nc/qzero_nc and the existing SDATA address-view macro.
 * Float scratch arrays now occupy retail's 0x00/0x40/0x50/0x80/0x90/0xA0.
 * Retail retains inverse in s7, spills input at +0xB0 and has a 0x110 frame;
 * this draft passes sp directly, keeps input in fp and has a 0x100 frame.
 * Retail also takes the fresh-frame counter through GP on the non-reset path;
 * an explicit GP/absolute phi retains both views but introduces a branch.
 * Clobbering qcopy, a combined scratch struct and force-addr did not retain inverse.
 * no-gcse and an explicit counter phi gave 456 bytes, still 0/9 places.
 * Reopen with a real matrix-pointer lifetime/stack address remedy, not padding.
 * All declarations are included below; no linked build run for this near miss.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void *func_L00_0032C638(char *);
extern void func_L02_00332900(void);
extern void func_00283698(void *, void *);
extern void func_002AFFD8(char *, char *, int);
extern void func_L00_00325600(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_0032C5E8(char *, char *);
extern void func_L02_00333300(char *, char *);
extern void func_L02_00332A80(char *, char *, void *, void *, void *, void *, void *);
extern void func_L02_00332D28(char *, char *, void *, void *, void *);
extern void func_L02_00332EF0(char *, char *, void *, void *, void *);
extern int D_L02_001B30C8 NOT_SDA;

int func_L02_00333480(char *object, void *target, void *input) {
    float inverse[16], direction[4], rotated[12];
    float previous[4], output0[4], output1[4];
    char *data = (char *)func_L00_0032C638(object);
    if (!data)
        return 8;
    if (D_L02_001B30C8 == *(int *)(data + 0xBC))
        return *(int *)(data + 0x94);
    func_L02_00332900();
    func_00283698(inverse, object + 0xC0);
    func_002AFFD8(object + 0x10, (char *)direction, 0);
    func_L00_00325600(object + 0xC0, direction, rotated);
    func_00283098(data + 0xA0, data + 0xA0, rotated);
    *(int *)(data + 0x98) = *(int *)(data + 0x94);
    *(int *)(data + 0x94) = 0;
    func_L00_0032C5E8(object, data);
    qcopy_nc(previous, object + 0x10);
    if (D_L02_001B30C8 - *(int *)(data + 0xBC) >= 2 || *(int *)(data + 0xBC) == 0) {
        func_L02_00333300(object, data);
        *(int *)(data + 0x80) = 0;
        *(unsigned char *)(data + 0xEA) = 0xFF;
        *(int *)(data + 0x9C) &= ~2;
        *(int *)(data + 0xB4) = 0;
        qzero_nc(data + 0xA0);
    }
    *(int *)(data + 0xBC) = D_L02_001B30C8;
    func_L02_00332A80(object, data, target, input, &output0, &output1, inverse);
    func_L02_00332D28(object, data, &previous, &output1, inverse);
    func_L02_00332EF0(object, data, target, &previous, inverse);
    return *(int *)(data + 0x94);
}
