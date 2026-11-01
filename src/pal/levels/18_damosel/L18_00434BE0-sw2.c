#include "include_asm.h"

#include "common.h"
extern float func_00283C80(float, float);
extern void func_PAL_002B5E30(u8 *, float);
extern void func_PAL_002B5E10(u8 *);
extern float func_002AAA00(void *, float, void *, float, float, float, int);
extern void func_L02_0032E998(void *, void *, void *, void *, int, void *, void *,
                              float, float);
extern int func_PAL_002B5C98(u8 *, void *, float);
extern int func_PAL_002B5BA8(u8 *, void *, float);
#define W(p, o) (*(int *)((p) + (o)))
#define H(p, o) (*(s16 *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))

/* A unit of its own: the switch's jump table is this unit's only .rodata. */
void func_PAL_L18_004370E8(u8 *a) {
    u8 *s = P(a, 0x68);
    int animation = a[0x42];

    /* The byte is widened before the test, so it never equals -1; retail keeps
       the lbu, li -1, bne and the fallback load all the same. */
    if (animation == -1) animation = a[0x43];
    switch (animation) {
    case 1:
        if (P(s, 0x7C0)) qcopy(P(s, 0x7C0) + 0xF0, a + 0xF0);
        break;
    case 3: case 4: case 5: case 6: case 7:
    case 10: case 11: case 12: case 13: case 14: case 15:
        if (H(s, 0x808) == 1) {
            if (func_00283C80(F(s, 0x7A4), F(a, 0xF8)) > 0.6108652949333191f) {
                func_PAL_002B5E30(a, F(s, 0x7A4));
            } else {
                if (P(s, 0x7C0))
                    func_002AAA00(P(s, 0x7C0) + 0xF8, F(s, 0x7A4), s + 0x7CC,
                                  0.010053098f, 0.010053098f,
                                  0.25132746f, 0);
                func_PAL_002B5E10(a);
            }
        } else {
            if (H(s, 0x808) == 2) func_PAL_002B5E30(a, F(s, 0x7A4));
            else func_PAL_002B5E10(a);
            if (P(s, 0x7C0))
                func_002AAA00(P(s, 0x7C0) + 0xF8, F(a, 0xF8), s + 0x7CC,
                              0.010053098f, 0.010053098f,
                              0.25132746f, 0);
        }
        break;
    case 8: case 9:
        if (W(s, 0x7D4) != -1) {
            func_L02_0032E998(a + 0x10, s + 0x750, s + 0x7DC, s + 0x210, W(s, 0x780),
                              s + 0x78C, s + 0x7D8, 0.0f, 0.4f);
            func_PAL_002B5C98(a, s + 0x750, F(s, 0x7DC));
        } else {
            func_PAL_002B5BA8(a, s + 0x750, F(s, 0x7A0));
        }
        if (P(s, 0x7C0)) {
            if (H(s, 0x808) == 1 &&
                func_00283C80(F(s, 0x7A4), F(a, 0xF8)) < 0.6108652949333191f) {
                func_002AAA00(P(s, 0x7C0) + 0xF8, F(s, 0x7A4), s + 0x7CC,
                              0.010053098f, 0.010053098f,
                              0.25132746f, 0);
            } else {
                func_002AAA00(P(s, 0x7C0) + 0xF8, F(a, 0xF8), s + 0x7CC,
                              0.010053098f, 0.010053098f,
                              0.25132746f, 0);
            }
        }
        break;
    }
}
