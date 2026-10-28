#include "common.h"
typedef int ControllerQuad __attribute__((mode(TI)));
extern unsigned int ref_L13_004095F8_00(unsigned int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283698(void *, void *);
extern void ref_L13_004095F8_01(char *, char *, int);
extern void func_L13_004095A8(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_L13_00409AB8(char *, char *);
extern void func_L13_00409B08(char *, char *);
extern void func_L13_00409C40(char *, char *, void *, ControllerQuad *, void *, void *, char *);
extern void func_L13_00409EE8(char *, char *, void *, void *, char *);
extern void func_L13_0040A0A0(char *, char *, char *, char *, char *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int D_L13_001B2448 MACRO_ADDR;
extern char D_L13_001BFD00[];
/* 0x40 inverse basis, 0x30 rotation and complete 16-byte vectors correspond
 * to the extents read/written by the current helper implementations. The two
 * reserved vector arguments are forwarded but never dereferenced by either
 * helper; they are not read before initialization or cleared artificially. */
int func_L13_004095F8(char *object, char *target)
{
    float difference[4];
    float inverse[4][4];
    float normal[4];
    float rotation[3][4];
    float previous[4];
    float reserved0[4], reserved1[4];
    float start[4], end[4];
    char *transform;
    char *data = (char *)ref_L13_004095F8_00((unsigned int)object);
    if (!data) return 8;
    if (D_L13_001B2448 == *(int *)(data + 0xbc)) return *(int *)(data + 0x94);
    func_00282CF0(difference, target, object + 0x10);
    transform = (char *)inverse;
    func_00283698(transform, object + 0xc0);
    ref_L13_004095F8_01(object, (char *)normal, 0);
    func_L13_004095A8(object + 0xc0, normal, rotation);
    func_00283098(data + 0xa0, data + 0xa0, rotation);
    *(int *)(data + 0x98) = *(int *)(data + 0x94);
    *(int *)(data + 0x94) = 0;
    func_L13_00409AB8(object, data);
    qcopy(previous, object + 0x10);
    if (D_L13_001B2448 - *(int *)(data + 0xbc) >= 2 || !*(int *)(data + 0xbc)) {
        func_L13_00409B08(object, data);
        *(int *)(data + 0xb4) = 0;
        *(int *)(data + 0x9c) |= -3;
        ((unsigned char *)data)[0xea] = 255;
        qzero(data + 0xa0);
    }
    *(int *)(data + 0xbc) = D_L13_001B2448;
    func_L13_00409C40(object, data, target, (ControllerQuad *)difference, reserved0, reserved1, transform);
    func_L13_00409EE8(object, data, previous, reserved1, transform);
    func_L13_0040A0A0(object, data, target, (char *)previous, transform);
    func_00282F20(start, object + 0xe0, 0.1f);
    func_00282F20(end, object + 0xe0, -3.0f);
    func_00282CC0(start, start, object + 0x10);
    func_00282CC0(end, end, object + 0x10);
    if (func_002761F8(start, end, 2, object, 0)) qcopy(object + 0x10, D_L13_001BFD00 + 0x20);
    return *(int *)(data + 0x94);
}
