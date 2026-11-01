#include "include_asm.h"

#include "common.h"
extern u8 D_L24_0025B710[];
extern void func_00282C88(void *);
typedef int TI128 __attribute__((mode(TI)));
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
extern void func_PAL_002A7E68(u8 *, s32, s32, s32);
extern void func_00283410(void *, void *);
extern void func_00283788(void *, void *, void *);
typedef struct {
    float matrix[4][4];
    float euler[4];
    float rotation[4][4];
} L00_002A6008_Scratch;

/* Keeps the hero's held object: creates it at the hero's position the first time,
   then poses it on the hand joint and picks its animation from the hero's state. */
void func_PAL_L00_002A5E98(void) {
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
                func_PAL_002A7E68(D_00189E20.p1860, 1, 0, 0x8);
            }
        } else {
            p = D_00189E20.p1860;
            if (*(u8 *)(p + 0x43) != 0) {
                func_PAL_002A7E68(D_00189E20.p1860, 0, 0, 0xE);
            }
        }
    }
}

typedef int Rac2Native_6b0741c38bf00fee_s32;
typedef unsigned char Rac2Native_6b0741c38bf00fee_u8;
typedef long Rac2Native_6b0741c38bf00fee_s64;
typedef unsigned long Rac2Native_6b0741c38bf00fee_u64;
extern Rac2Native_6b0741c38bf00fee_u8 D_0018B2BC[];
extern void func_PAL_L00_002A6058(Rac2Native_6b0741c38bf00fee_u64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s64, Rac2Native_6b0741c38bf00fee_s32);
extern void func_L00_002B9C58(short, short, short);

/* passes the measured byte and constants to two callees */
void func_PAL_L00_002A6018(void) {
 func_PAL_L00_002A6058(D_0018B2BC[1],0,1,0x32);
 func_L00_002B9C58(0x16,6,0);
}
