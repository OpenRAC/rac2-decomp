#include "include_asm.h"

/* func_L23_00422668 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy) for the grouped `lq`/`sq` of its else branch, and
   -frac2-no-annulled-wide-stores (docs/build/compiler-notes.md): reorg's search of that branch's
   target then stops at the 16-byte copy, so the `beqz` keeps an empty slot and `$a0 = $sp`
   stays on each path, as retail has it, where it would otherwise take the `$a0` move from
   behind the copy and fill the return test's `beql` slot from the epilogue. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

typedef int TI16 __attribute__((mode(TI)));

extern void func_00282F20(float *, float *, float);

typedef struct {
    u8 pad[0x18];
    u8 *f18;
} L23Block1C0A80;

extern L23Block1C0A80 D_L23_001C0A80;

/* a 16-byte vector, aligned for the quadword copies */
typedef struct {
    float v[4];
} L23Vec __attribute__((aligned(16)));

/* the 48-byte record func_002A8C00 fills and func_002A8E20 reads */
typedef struct {
    u8 pad[0x18];
    u8 b18;
    u8 b19;
    u16 h1A;
    u8 pad1C[0x14];
} L23Hit;

extern u8 *D_0018C0B0;

extern s32 func_002761F8(void *, void *, s32, void *, s32);

extern void func_002A8C00(float, L23Hit *, u8 *, s32, L23Vec *);

extern void func_002A8E20(u8 *, L23Hit *);

extern void func_L00_002D6900(s32);

extern void func_L22_0040E2B0(void *, s32, s32);

/* the object's first record is set up against the table entry, then its marker byte is set */
void func_L23_00422668(u8 *arg0, void *arg1) {
    u8 *payload = *(u8 **)(arg0 + 0x68);
    L23Vec dir;
    L23Hit hit;
    u8 *obj;

    if (func_002761F8(arg1, arg0 + 0x10, 0, arg0, 0) == 0) {
        return;
    }
    obj = D_L23_001C0A80.f18;
    if (obj != 0) {
        if (*(s16 *)(obj + 0xAA) == 0x7E5) {
            return;
        }
        func_00282F20(dir.v, (float *)payload, 1.0f);
        func_002A8C00(*(float *)(payload + 0x1C), &hit, arg0, 0x8B0003, &dir);
        hit.b18 = 5;
        hit.b19 = 3;
        hit.h1A = *(u16 *)(arg0 + 0xAA);
        if (D_L23_001C0A80.f18 == D_0018C0B0) {
            func_002A8E20(D_L23_001C0A80.f18, &hit);
            func_L00_002D6900(0x2B);
        }
        func_L22_0040E2B0(arg0 + 0x10, 0xA, 1);
    } else {
        *(TI16 *)&dir = *(TI16 *)(arg0 + 0x10);
        func_L22_0040E2B0(&dir, 0xF, 0);
    }
    arg0[0x20] = 2;
}
