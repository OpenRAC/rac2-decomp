#include "include_asm.h"


INCLUDE_ASM("asm/us2/game", func_US2_00345890);





extern void F6402b823_FUN_00336320(char *a);
extern void F6402b823_FUN_00336A78(char *a);
extern void F6402b823_FUN_00335E68(char *a, int b);
extern void F6402b823_FUN_00345268(char *a);
extern void F6402b823_FUN_00345088(char *a);
extern void F6402b823_FUN_00344F98(char *a);
extern void F6402b823_FUN_00345178(char *a);
extern void F6402b823_FUN_00344938(char *a);

void func_US2_003462C0(char *obj)
{
    if (*(int *)(obj + 1192) != 0) {
        char *s0 = obj + 456;

        F6402b823_FUN_00336320(obj);
        F6402b823_FUN_00336320(obj + 76);
        F6402b823_FUN_00336320(obj + 152);
        F6402b823_FUN_00336320(obj + 228);
        F6402b823_FUN_00336A78(s0);
        F6402b823_FUN_00336A78(obj + 696);
        F6402b823_FUN_00336A78(s0);
        F6402b823_FUN_00335E68(obj + 544, 0);
        F6402b823_FUN_00345268(obj);
        F6402b823_FUN_00345088(obj);
        F6402b823_FUN_00344F98(obj);
        F6402b823_FUN_00345178(obj);
        F6402b823_FUN_00344938(obj);
        F6402b823_FUN_00336320(obj + 380);
    }
}


extern void F449e2f67_FUN_003361A8(char *p);
extern void F449e2f67_FUN_00336968(char *p);
extern void F449e2f67_FUN_003366D0(char *p);

char *func_US2_00346368(char *p)
{
    F449e2f67_FUN_003361A8(p);
    F449e2f67_FUN_003361A8(p + 76);
    F449e2f67_FUN_003361A8(p + 152);
    F449e2f67_FUN_003361A8(p + 228);
    F449e2f67_FUN_003361A8(p + 304);
    F449e2f67_FUN_003361A8(p + 380);
    F449e2f67_FUN_00336968(p + 456);
    F449e2f67_FUN_00336968(p + 544);
    F449e2f67_FUN_003366D0(p + 632);
    F449e2f67_FUN_00336968(p + 696);
    F449e2f67_FUN_00336968(p + 784);
    F449e2f67_FUN_00336968(p + 872);
    F449e2f67_FUN_00336968(p + 960);
    F449e2f67_FUN_00336968(p + 1048);
    return p;
}


/* func_US2_003463F8, the USA v2.00 copy of func_00345490: the same C with the text elements 0x10 larger,
   new string ids, and two text flags set. */
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_003361E0(void *, void *, void *);
extern void func_US2_003377B0(void *, void *, void *);
extern void func_00336710(void *, void *, void *);
extern int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern void func_00335E68(void *, int);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00336A38(void *, void *);
extern void func_00336A30(void *, int);
extern void *func_00288FB8(int);
extern void func_US2_00346EF0(void *, int, void *);
extern char *D_001A8CFC[] __attribute__((sda));
extern char D_001ADC10[];
extern char D_001ADC18[];
extern char D_001ADC20[];
extern char D_001ADC28[];
extern char D_001ADFC0[];
extern char D_001ADFC8[];
extern char D_001ADD68[];
extern char D_001ADD60[];
extern char D_001AE3C8[];
extern char D_001AE3D8[];
extern char D_001AE3E8[];
extern char D_001ADD58[];
extern char D_001AE030[];
extern char D_001ADFD8[];

void func_US2_003463F8(char *self, void *owner)
{
    int scratch;
    *(void **)(self + 0x474) = owner;
    if (owner) {
        int *p = func_00336DA8(16, func_00336E40(owner));
        *(int **)(self + 0x470) = p;
        p[1] = 0; p[2] = 0; p[3] = 0; p[0] = 0;
    }
    *(int *)(self + 0x4f8) = 1;
    (*(float **)(self + 0x470))[0] = 250.0f;
    (*(float **)(self + 0x470))[1] = 207.0f;
    func_003361E0(self + 0x0, D_001ADC10, owner);
    func_003361E0(self + 0x4c, D_001ADC18, owner);
    func_003361E0(self + 0x98, D_001ADC20, owner);
    func_003361E0(self + 0xe4, D_001ADC28, owner);
    func_003361E0(self + 0x130, D_001ADFC0, owner);
    func_003361E0(self + 0x17c, D_001ADFC8, owner);
    func_US2_003377B0(self + 0x2b8, D_001ADD68, owner);
    func_US2_003377B0(self + 0x310, D_001ADD60, owner);
    func_US2_003377B0(self + 0x368, D_001AE3C8, owner);
    func_US2_003377B0(self + 0x3c0, D_001AE3D8, owner);
    func_US2_003377B0(self + 0x418, D_001AE3E8, owner);
    func_US2_003377B0(self + 0x1c8, D_001ADD58, owner);
    func_US2_003377B0(self + 0x220, D_001AE030, owner);
    *func_00335E20(self + 0x0) = 0x60442d00;
    *func_00335E20(self + 0x98) = 0x55f0c070;
    *func_00335E20(self + 0xe4) = 0x55f0c070;
    *func_00335E20(self + 0x130) = 0x55f0c070;
    *func_00335E20(self + 0x17c) = 0x70fffeed;
    *func_00335E20(self + 0x4c) = 0x60241700;
    *func_00335E20(self + 0x310) = 0x80f0f0f0;
    *func_00335E20(self + 0x2b8) = 0x80f0f0f0;
    *func_00335E20(self + 0x368) = 0x80f0f0f0;
    *func_00335E20(self + 0x3c0) = 0x80f0f0f0;
    *func_00335E20(self + 0x418) = 0x80f0f0f0;
    func_00336390(self + 0x0, D_001A8CFC[0] + 0x8710, 0x59);
    func_00336390(self + 0x98, D_001A8CFC[0] + 0x8710, 0x5b);
    func_00336390(self + 0xe4, D_001A8CFC[0] + 0x8710, 0x5c);
    func_00336390(self + 0x130, D_001A8CFC[0] + 0x8710, 0x5d);
    func_00336390(self + 0x17c, D_001A8CFC[0] + 0x8710, 0x5e);
    func_00336390(self + 0x4c, D_001A8CFC[0] + 0x8710, 0x5a);
    func_00335E68(self + 0x17c, 0);
    *(int *)(self + 0x4fc) = 0;
    *(int *)(self + 0x500) = 0;
    *(int *)(self + 0x508) = 0;
    func_00336710(self + 0x278, D_001ADFD8, owner);
    *func_00335E20(self + 0x278) = 0x60f0f0b0;
    func_00335F88(self + 0x278, 32.0f, 32.0f, 0.0f, 0.0f);
    *func_00335E20(self + 0x1c8) = 0x80f0f0f0;
    *func_00335E20(self + 0x220) = 0x80f0f0f0;
    func_00336A38(self + 0x1c8, func_00288FB8(0x2be8));
    self[0x4b8] = 0;
    func_00336A38(self + 0x220, self + 0x4b8);
    *(int *)(self + 0x504) = 0;
    func_00336A38(self + 0x310, func_00288FB8(0x2be5));
    func_00336A38(self + 0x2b8, func_00288FB8(0x2bf1));
    func_00336A30(self + 0x310, 1);
    func_00336A30(self + 0x2b8, 1);
    func_00336A38(self + 0x368, func_00288FB8(0x2bed));
    func_00336A38(self + 0x3c0, func_00288FB8(0x2bee));
    func_00336A38(self + 0x418, func_00288FB8(0x2bf0));
    func_US2_00346EF0(self, 0, &scratch);
}
