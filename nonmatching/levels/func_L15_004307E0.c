/* func_L15_004307E0: near miss, 848/848 bytes, 0 of 1 place (USA v1.01, 2 November 2026).

   Profile: its own unit, `-O2 -G8 -ffunction-sections -frac2-qcopy`.

   Gorn's cutscene controller: on the first frame it starts the scene and wakes every 0x1211
   object, then, once the timer runs out, it builds the camera from the object D_L15_001B261C
   points at (a ray towards it, the distance halved or pulled to -32, a basis from the facing
   and the up vector) and later hands control back. 11 rows differ, 5 of them relocations.
   What mattered: the camera position is taken $gp-relative (an SDATA view) but its z is read
   and written absolutely (MACRO_ADDR), D_L15_00221E3C is NOT_SDA, and the basis w components
   are one chained `= 0.0f` in the order 0, 1, 2 (retail stores a float zero with swc1).
   What differs: the D_L15_001B1520 decrement before the hand-back call has the counter in $v0
   and the table pointer in $v1; retail has them the other way round. The instruction order is
   retail's, only local-alloc's choice differs. Tried, unchanged: --, -= 1, = x + -1, an array
   view of D_L15_001B1520, the table as 0x100-byte structs, swapped operands, the pointer in a
   local first (worse); volatile is 4 bytes over. */

#include "common.h"

typedef float Vector[4] __attribute__((aligned(16)));
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; u8 *target; char pad1C[4]; Vector pos; } Hit;

extern int D_L15_001B1534 __attribute__((sda));
extern int D_L15_001B1520 __attribute__((sda));
extern int D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B15D0 __attribute__((sda));
extern int D_L15_001B15AC __attribute__((sda));
extern float D_L15_001B1540[4] SDATA(D_L15_001B1540);
/* Retail takes the camera position's address $gp-relative and reaches its z absolutely. */
extern float D_L15_001B1550[4] MACRO_ADDR;
extern float camera_pos[4] SDATA(D_L15_001B1550);
extern int D_L15_00221E3C NOT_SDA;
extern int D_L15_001B2148;
extern u8 *D_L15_001B261C;
extern Hit D_L15_001BFC00;

extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(s32 a0);
extern u8 **func_L05_00379EB8(void);
extern s32 func_L00_004272A0(void);
extern void func_L05_0037B280(u8 *a0, s32 a1);
extern void *func_L05_00379ED0(int);
extern int func_L10_0037D200(void *);
extern int func_00282948(void *);
extern void func_L05_0037B108(void);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_L05_00442828(void *, void *, int);
extern void func_L15_00432008(void);
extern void func_0029B3E0(int, int);
extern void func_L00_003294F0(void *, int);
extern void func_L05_00379F48(int);
extern void func_002AD7B8(int);
extern void func_L15_00430590(void *, int);

void func_L15_004307E0(u8 *self)
{
    Vector step;
    Vector ahead;
    Vec up;
    Vector basis[3];
    u8 *vars = *(u8 **)(self + 0x68);

    if (D_L15_001B1534 == 0) {
        u8 **list;
        int i, count;

        D_L15_00221E3C = 0;
        D_L15_001B1534 = 1;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        *(int *)(vars + 0x6C) = 30;
        list = func_L05_00379EB8();
        count = func_L00_004272A0();
        for (i = 0; i < count; i++) {
            if (*(short *)(list[i] + 0xAA) == 0x1211)
                func_L05_0037B280(list[i], 1);
        }
    }
    if (func_L10_0037D200(func_L05_00379ED0(0x1211)) != 0)
        return;
    if (D_L15_001B2148 < 6)
        return;
    if (D_L15_001B15BC == 0) {
        u8 *obj;
        u8 *pos;
        float dist;

        if (func_00282948(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 60;
        func_L05_0037B108();
        obj = D_L15_001B261C + (*(int *)(vars + 0x20) << 8);
        pos = obj + 0x10;
        qcopy(camera_pos, pos);
        func_00282F20(step, obj + 0xC0, 196.0f);
        dist = 25.0f;
        func_00282CC0(ahead, pos, step);
        if (func_002761F8(pos, ahead, 0, obj, 0) != 0) {
            Hit *hit = &D_L15_001BFC00;

            if (hit->target != 0 && *(short *)(hit->target + 0xAA) == 0x1211)
                dist = func_00282E48(hit->pos, pos);
        }
        if (dist < 16.0f)
            dist = -32.0f;
        else
            dist = dist * 0.5f;
        func_00282F20(step, obj + 0xC0, dist);
        func_00282CC0(camera_pos, camera_pos, step);
        D_L15_001B1550[2] -= 16.0f;
        up.q = 0;
        up.f[2] = 1.0f;
        qcopy(basis[0], obj + 0xC0);
        qcopy(basis[2], up.f);
        func_00282DD8(basis[1], basis[0], basis[2]);
        basis[0][3] = basis[1][3] = basis[2][3] = 0.0f;
        func_002AB6D8(basis, D_L15_001B1540);
        func_L05_00442828(camera_pos, D_L15_001B1540, 300);
        self[0x20] = 3;
        D_L15_001B15BC = 1;
    } else if (D_L15_001B15D0 != 0) {
        if (func_00282948(vars + 0x6C) == 0)
            return;
        *(int *)(vars + 0x6C) = 10;
        D_L15_001B1520++;
        func_L15_00432008();
        func_0029B3E0(0, -1);
        D_L15_001B1520--;
        func_L00_003294F0(D_L15_001B261C + (*(int *)(vars + 0x28) << 8), 1);
        D_L15_001B15AC = 0;
        D_L15_001B15D0 = 0;
        func_L05_00379F48(1);
        func_002AD7B8(0x10);
    } else if (func_00282948(vars + 0x6C) != 0) {
        func_L05_0037B210();
        func_L15_00430590(self, 0);
    }
}
