/* func_L17_003C5C28 - 456 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Needs -g8 sibling (L17_003C5C28-g8.c). Same size (456 with separate Quad
   locals: 460 vs 456 before; v[2] form differs).
   Diff: retail keeps s0=&delta (sp+0x10, hoisted into branch delay slots) and
   recomputes `addiu a1,s1,0x10` for obj+0x10 each time (s2=state ptr).
   Mine CSEs obj+0x10 into s0 (separate Quad locals, delta at sp+0 instead of
   sp+0x10) or into a 4th saved reg (Quad v[2]). Tried: decl order, struct,
   array. Switch layout and all case bodies match. */

#include "common.h"

extern float func_002A89A8(void *, int, float);
extern void func_00282CF0(void *, void *, void *);
extern int func_00282948(void *, void *);
extern void func_0029F338(void *);
extern void func_002A7398(void *, int, int);
extern void func_002AD6F0(void *, void *, void *, void *);
extern float D_L17_001B0328 __attribute__((sda));
extern int D_001C0018;
extern u8 D_L17_001DBF81;
extern char *D_L17_001DAD00[];

typedef unsigned int Quad __attribute__((mode(TI)));

void func_L17_003C5C28(u8 *obj) {
    Quad v[2];
    u8 *st = *(u8 **)(obj + 0x68);

    v[0] = *(Quad *)(obj + 0x10);
    switch (obj[0x20]) {
    case 0:
        if (*(int *)(st + 0x90) != -1) {
            f32 f = func_002A89A8(obj + 0x10, 0, 0.5f);

            *(int *)(st + 0x9C) = D_001C0018;
            if (f < *(f32 *)(obj + 0x18)) {
                f32 g = *(f32 *)(st + 0x98) + D_L17_001B0328 * 0.00027777778f;

                *(f32 *)(st + 0x98) = g;
                *(f32 *)(obj + 0x18) = *(f32 *)(obj + 0x18) - g;
            } else {
                *(int *)(st + 0x98) = 0;
                *(f32 *)(obj + 0x18) = f;
            }
        }
        break;
    case 1:
        if (obj[0x42] == 1 && (obj[0x60] & 2)) {
            *(s16 *)(obj + 0xAA) = 0x921;
            obj[0x22] = D_L17_001DBF81;
            *(char **)(obj + 0x24) = D_L17_001DAD00[obj[0x22]];
            *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
            func_002A7398(obj, 0, 0);
            obj[0x20] = 2;
            if (*(int *)(st + 0x90) != -1) {
                *(int *)(st + 0x94) = 0x258;
            }
        }
        break;
    case 2:
        if (*(int *)(st + 0x90) != -1) {
            if (func_00282948(st + 0x94, obj + 0x10)) {
                func_0029F338(obj);
                return;
            }
        }
        break;
    }
    func_00282CF0(&v[1], obj + 0x10, &v[0]);
    func_002AD6F0(st + 0x50, &v[1], obj + 0xF0, obj + 0xF0);
}
