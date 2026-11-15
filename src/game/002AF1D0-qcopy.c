#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern void moby_transform_joint_point(char *, int, char *);
extern void FastVecScale(char *, char *, float);
extern void func_002A05A8(char *);
extern void func_002A0F48(char *);
extern void copy_matrix3x4(char *, char *);
extern void mat_normalize_columns(char *);
extern void func_002A10E8(char *);

/* Copies the position and facing of a joint of one object onto another, flipping axes as asked. */
void moby_copy_joint_transform_to_object(char *source, char *dest, int jointIndex, int flipMask) {
    TI128 jointMatrix[4];

    moby_transform_joint_point(source, jointIndex, (char *)&jointMatrix[0]);
    *(TI128 *)(dest + 0x10) = jointMatrix[3];
    if (flipMask & 1) {
        FastVecScale((char *)&jointMatrix[0], (char *)&jointMatrix[0], -1.0f);
    }
    if (flipMask & 2) {
        FastVecScale((char *)&jointMatrix[1], (char *)&jointMatrix[1], -1.0f);
    }
    if (flipMask & 4) {
        FastVecScale((char *)&jointMatrix[2], (char *)&jointMatrix[2], -1.0f);
    }
    func_002A05A8(dest);
    if ((*(unsigned short *)(dest + 0x34) & 4) == 0) {
        func_002A0F48(dest);
    }
    copy_matrix3x4(dest + 0xC0, (char *)&jointMatrix[0]);
    mat_normalize_columns(dest + 0xC0);
    func_002A10E8(dest);
    if (*(unsigned short *)(source + 0x34) & 1) {
        *(unsigned short *)(dest + 0x34) |= 0x41;
    } else {
        *(unsigned short *)(dest + 0x34) &= 0xFFBE;
    }
    *(unsigned short *)(dest + 0x34) |= 6;
}
