#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002AFDD8(char *, char *, char *, char *);
extern void func_002A93B0(void *);
extern void func_002A0F48(void *);
extern void func_0029FC20(char *, int, char *);
extern void func_00283678(void *, void *);
/* The third argument to func_0029FC20 is a full 64-byte affine matrix. */
void func_L07_003F8010(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    u8 *child = *(u8 **)(state + 0x410);
    struct { u8 basis[48]; u8 translation[16]; } __attribute__((aligned(16))) transform;
    if (child != 0) {
        qcopy(child + 0x10, self + 0x10);
        qcopy(child + 0xF0, self + 0xF0);
        func_002A93B0(child);
    }
    func_002A0F48(*(u8 **)(state + 0x410));
    if (*(u8 **)(state + 0x414) != 0) {
        func_0029FC20((char *)self, 0, (char *)&transform);
        copy_matrix3x4(*(u8 **)(state + 0x414) + 0xC0, transform.basis);
        qcopy(*(u8 **)(state + 0x414) + 0x10, transform.translation);
    }
    func_002A0F48(*(u8 **)(state + 0x414));
}
