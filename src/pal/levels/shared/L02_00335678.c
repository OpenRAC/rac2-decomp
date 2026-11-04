/* func_PAL_L02_00335678, the PAL copy of func_L02_00333480: the same C with the callee is PAL's
   func_PAL_L02_00334C78. */
#include "include_asm.h"
#include "common.h"

extern void *func_L00_0032C638(char *);
extern void func_L02_00332900(void);
extern void func_00283698(void *, void *);
extern void func_002AFFD8(char *, char *, int);
extern void func_L00_00325600(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_0032C5E8(char *, char *);
extern void func_L02_00333300(char *, char *);
extern void func_PAL_L02_00334C78(char *, char *, void *, void *, void *, void *, void *);
extern void func_L02_00332D28(char *, char *, void *, void *, void *);
extern void func_L02_00332EF0(char *, char *, void *, void *, void *);
extern int D_L02_001B30C8 __attribute__((sda));

int func_PAL_L02_00335678(char *object, void *target, void *input) {
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
    func_PAL_L02_00334C78(object, data, target, input, &output0, &output1, m);
    func_L02_00332D28(object, data, &previous, &output1, m);
    func_L02_00332EF0(object, data, target, &previous, m);
    return *(int *)(data + 0x94);
}
