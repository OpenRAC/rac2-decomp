#include "common.h"
#include "include_asm.h"

extern u8 D_L24_0025B710[];

extern void func_L00_002A5048(u8 *);

/* Measured partial layouts; original type and game roles are unknown. */
typedef int Rac2Native_6b0741c38bf00fee_s32;

typedef unsigned char Rac2Native_6b0741c38bf00fee_u8;

typedef long Rac2Native_6b0741c38bf00fee_s64;

typedef unsigned long Rac2Native_6b0741c38bf00fee_u64;

extern Rac2Native_6b0741c38bf00fee_u8 D_0018B2BC[];

extern void func_L00_002A61C8_1(Rac2Native_6b0741c38bf00fee_u64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s32);

extern void func_L00_002B9C58(short, short, short);

extern void *func_L00_002A4FE8(short);

extern void func_0029F9F0(void *, void *);

extern void func_00282C88(void *);

/* calls the measured element helper over a 0x1b80-byte array in 0xb0-byte steps */
void func_L00_002A5368(void) {
 u8 *p=D_L24_0025B710;
 u8 *end=p+0x1b80;
 do {func_L00_002A5048(p);p+=0xb0;}while((s32)p<(s32)end);
}

/* walks the 0x1b80-byte array in 0xb0-byte steps: a per-element callback, three
   sub-object walks and a 1.0f stamp (near miss: nonmatching/levels/func_L00_002A53B8.c) */
/* func_L00_002A53B8 is matched in L00_002A53B8.c (built with -fno-schedule-insns). */

/* func_L00_002A5480 is built in its G8 unit. */

/* func_L00_002A5518 is built in L00_002A5518-g8.c. */

/* func_L00_002A5840 is built in L00_002A5840-g8.c. */

/* func_L00_002A5CB0 is built in L00_002A5CB0.c. */

typedef int TI128 __attribute__((mode(TI)));

/* The hero block fields this body reads. */
typedef struct {
    u8 pad000[0x80];
    TI128 q080;
    TI128 q090;
    u8 pad0a0[0x1860 - 0xa0];
    u8 *p1860;
    u8 pad1864[0x2290 - 0x1864];
    u8 *p2290;
    s32 f2294;
} L00_002A6008_Hero;

extern L00_002A6008_Hero D_00189E20;

extern void *func_0029EFD0(int);
extern void func_0029FC20(void *, s32, void *);
extern void func_002A0F48(u8 *);
extern void func_00283678(u8 *, void *);
extern void func_002A7470(u8 *, s32, s32, s32);
extern void func_00283410(void *, void *);
extern void func_00283788(void *, void *, void *);

typedef struct {
    float matrix[4][4];
    float euler[4];
    float rotation[4][4];
} L00_002A6008_Scratch;

/* Keeps the hero's held object: creates it at the hero's position the first time,
   then poses it on the hand joint and picks its animation from the hero's state. */
void func_L00_002A6008(void) {
    L00_002A6008_Scratch s;
    u8 *obj;
    u8 *p;

    if (D_00189E20.p1860 == 0) {
        obj = func_0029EFD0(0x47A);
        D_00189E20.p1860 = obj;
        if (obj == 0) {
            return;
        }
        p = obj + 0x10;
        qcopy(p, &D_00189E20.q080);
        qcopy(obj + 0xF0, &D_00189E20.q090);
        *(u16 *)(obj + 0x32) = 0x40;
        *(u8 *)(D_00189E20.p1860 + 0x31) = 1;
        *(u8 *)(D_00189E20.p1860 + 0x30) = 0;
        *(u16 *)(D_00189E20.p1860 + 0x34) = 0;
        func_002A0F48(D_00189E20.p1860);
        if (D_00189E20.p1860 == 0) {
            return;
        }
    }
    {
        u8 *held;

        func_0029FC20(D_00189E20.p2290, 5, s.matrix);
        held = D_00189E20.p1860;
        qcopy(held + 0x10, s.matrix[3]);
        func_002A0F48(held);
        func_00282C88(s.euler);
        s.euler[2] = -((float *)&D_00189E20.q090)[2];
        func_00283410(s.rotation, s.euler);
        func_00283788(s.matrix, s.matrix, s.rotation);
        func_00283678(D_00189E20.p1860 + 0xC0, s.matrix);
        *(u64 *)(D_00189E20.p1860 + 0x38) = *(u64 *)(D_00189E20.p2290 + 0x38);
        if (D_00189E20.f2294 == 0x4B) {
            if (*(u8 *)(D_00189E20.p1860 + 0x43) != 1) {
                func_002A7470(D_00189E20.p1860, 1, 0, 0xA);
            }
        } else {
            p = D_00189E20.p1860;
            if (*(u8 *)(p + 0x43) != 0) {
                func_002A7470(D_00189E20.p1860, 0, 0, 0x11);
            }
        }
    }
}

/* passes the measured byte and constants to two callees */
void func_L00_002A6188(void) {
 func_L00_002A61C8_1(D_0018B2BC[1],0,1,0x32);
 func_L00_002B9C58(0x16,7,0);
}

