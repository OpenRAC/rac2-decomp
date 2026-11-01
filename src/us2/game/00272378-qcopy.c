#include "include_asm.h"

#include "common.h"
extern char D_001B5200[];
extern char D_0018B2F0[];
extern unsigned char D_001A7A44[] __attribute__((sda));
extern void func_002721C8(void);
extern void func_00272280(void);
extern void func_00271FD8(void);
extern void func_00271B90(void);
extern int func_00270A48(void);
extern void func_00270EE0(void *);
extern int func_0026F7C0(void);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern void func_00271958(void *, int);
extern void func_00271E88(void);
extern void func_002735A0(void *);
extern void func_00270018(void);

void func_US2_00272378(void) {
    char *d = D_001B5200;
    char *obj;
    char *p;
    char *q;
    char *r;

    *(int *)(d + 0x404) = *(int *)(d + 0x404) + 1;
    func_002721C8();
    func_00272280();
    func_00271FD8();
    func_00271B90();
    func_00270A48();
    obj = *(char **)(d + 0x190);
    if ((unsigned)(*(unsigned short *)(d + 0x290) - 1) < 2)
        func_00270EE0(*(void **)(d + 0x194));
    if (*(short *)(d + 0x290) == 3) {
        func_002718B8(obj);
    } else {
        qcopy(d + 0x140, obj + 0x30);
        qcopy(d + 0x370, obj);
        qcopy(d + 0x380, obj + 0x10);
        qcopy(d + 0x390, obj + 0x20);
    }
    if (func_0026F7C0()) {
        p = D_001B5200 + 0x140;
        qcopy(p, D_0018B2F0);
        qcopy(p + 0x230, D_0018B2F0 + 0x10);
        func_00282DD8(p + 0x240, p + 0x230, D_0018B2F0 - 0x14B0);
        func_00282F20(p + 0x240, p + 0x240, 1.0f);
        func_00282DD8(p + 0x250, p + 0x240, p + 0x230);
        func_00282F20(p + 0x250, p + 0x250, 1.0f);
    }
    q = D_001B5200 + 0x370;
    func_002AB6D8(q, q - 0x220);
    func_00271958(q - 0x210, 0);
    func_00271958(q - 0x200, 1);
    func_00271958(q - 0x1F0, 2);
    func_00271E88();
    func_002735A0(q - 0x230);
    if (D_001A7A44[0])
        func_00282DD8(q + 0x10, q + 0x20, q);
    func_00270018();
    qzero(q + 0x50);
}
