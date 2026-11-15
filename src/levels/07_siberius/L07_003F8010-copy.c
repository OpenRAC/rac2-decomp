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
/* Keeps the two parts attached to the object in place: copies position and rotation to the first and places the second using the object transform. */
void func_L07_003F8010(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *mainPart = *(u8 **)(vars + 0x410);
    struct { u8 basis[48]; u8 translation[16]; } __attribute__((aligned(16))) transform;
    if (mainPart != 0) {
        qcopy(mainPart + 0x10, moby + 0x10);
        qcopy(mainPart + 0xF0, moby + 0xF0);
        UpdateMobyGroundCheck(mainPart);
    }
    func_002A0F48(*(u8 **)(vars + 0x410));
    if (*(u8 **)(vars + 0x414) != 0) {
        TransformMobyJointPoint((char *)moby, 0, (char *)&transform);
        copy_matrix3x4(*(u8 **)(vars + 0x414) + 0xC0, transform.basis);
        qcopy(*(u8 **)(vars + 0x414) + 0x10, transform.translation);
    }
    func_002A0F48(*(u8 **)(vars + 0x414));
}
