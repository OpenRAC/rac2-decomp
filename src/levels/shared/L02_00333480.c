#include "include_asm.h"
#include "common.h"

/* Per-frame update of an object's controller record (func_L00_0032C638): runs at most once per
   frame counter value, keeps the record's previous result at +0x98, resets the record when a
   frame was skipped, then calls the three update steps with the object's inverse matrix.
   Built with -mno-split-addresses under -G0: the counter is small data, so only the copy reorg
   places in a delay slot is gp-relative. The matrix pointer m is set from the frame-offset-0
   array in a later extended basic block than its first use, so cse cannot turn it back into
   the frame pointer and it lives in a saved register across the calls, as in retail. */
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
extern int D_L02_001B30C8 __attribute__((sda));

int func_L02_00333480(char *object, void *target, void *input) {
    float inverse[16], direction[4], rotated[12];
    float previous[4], output0[4], output1[4];
    float *m;
    char *data = (char *)func_L00_0032C638(object);
    if (!data)
        return 8;
    if (D_L02_001B30C8 == *(int *)(data + 0xBC))
        return *(int *)(data + 0x94);
    func_L02_00332900();
    func_00283698(inverse, object + 0xC0);
    m = inverse;
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
    func_L02_00332A80(object, data, target, input, &output0, &output1, m);
    func_L02_00332D28(object, data, &previous, &output1, m);
    func_L02_00332EF0(object, data, target, &previous, m);
    return *(int *)(data + 0x94);
}
