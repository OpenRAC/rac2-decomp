/* Fuse an object with up to three linked objects: record each link, its offset and
   relative angles in the inverse frame, then reset the object to the new pose.
   The object fields are written as expressions at each use. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
extern u8 *func_0029EFD0(int);
extern int func_L02_003272D8(char *);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AE730(float *, int *);
extern void func_00283738(void *, void *, void *);
extern void func_002AB6D8(float *, float *);
extern void func_002833F0(void *, void *);

typedef struct {
    char pad00[0x10];
    u8 *owner[4];         /* 0x10: [0] the object, [1..3] the links */
    unsigned int flags[4];/* 0x20 */
    int handle[4];        /* 0x30 */
    int offset[3];        /* 0x40 */
    int angle[3];         /* 0x4C */
} FuseData;
int func_L02_002EF388(u8 *object, TI128 *position, TI128 *rotation, u8 **links, int count) {
    float inverse[16] __attribute__((aligned(16)));
    float relative[4] __attribute__((aligned(16)));
    /* The three-row product occupies rows 0..2; the angle output shares row 3.
     * The angle reader consumes all 64 bytes before writing its three results. */
    union {
        float full[16];
        struct { float rows[12]; float angles[4]; } view;
    } rotationWork __attribute__((aligned(16)));
    u8 *fused = func_0029EFD0(0x9BB);
    FuseData *data;
    u8 *originalMatrix;
    int i;
    if (fused) {
    *(u8 **)(fused + 0xB8) = object;
    fused[0x30] = 0xFF;
    qcopy(fused + 0x10, position);
    data = *(FuseData **)(fused + 0x68);
    data->owner[0] = object;
    data->flags[0] = *(u16 *)(object + 0x34);
    data->handle[0] = func_L02_003272D8((char *)object);
    func_00283698(inverse, object + 0xC0);
    for (i = 0; i < count && i < 3; i++) {
        if (links[i]) {
            data->owner[i + 1] = links[i];
            data->flags[i + 1] = *(u16 *)(links[i] + 0x34);
            data->handle[i + 1] = func_L02_003272D8((char *)links[i]);
            func_00282CF0(relative, links[i] + 0x10, (TI128 *)(object + 0x10));
            func_00283098(relative, relative, inverse);
            func_002AE730(relative, &data->offset[i]);
            func_00283738(rotationWork.full, inverse, links[i] + 0xC0);
            func_002AB6D8(rotationWork.full, rotationWork.view.angles);
            func_002AE730(rotationWork.view.angles, &data->angle[i]);
            *(u16 *)(links[i] + 0x34) |= 0x102;
            *(u16 *)(links[i] + 0x34) |= 1;
            links[i][0x31] = 0;
            *(int *)(links[i] + 0x98) = 0;
        }
    }
    qcopy((TI128 *)(object + 0x10), position);
    qcopy((TI128 *)(object + 0xF0), rotation);
    func_002833F0(object + 0xC0, (TI128 *)(object + 0xF0));
    *(int *)(object + 0x98) = 0;
    object[0x31] = 0;
    *(u16 *)(object + 0x34) |= 0x103;
    return 1;
    }
    return 0;
}
