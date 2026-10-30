/* 30 October 2026 retained reconstruction; game compiler,
 * -O2 -G8 -ffunction-sections. USA v1.01 and v2.00: 756/764 bytes,
 * 0/1 placements each; PAL identity absent, not a successful placement.
 * A switch restores the retail state dispatch. Separate preceding-weight and
 * active-weight cursors restore the duplicated induction and complete loop
 * length. The position pointer still occupies a saved register instead of the
 * retail stack slot plus loop copy; allocation and the preheader differ.
 * The 16-byte copy uses the reviewed qcopy helper; no extents were shortened.
 * Historical 716-byte explicit-cursor form: alternatives/func_L16_00418E38-form-01.c.
 * Reopen with the real position and state-pointer lifetime model.
 */
#include "common.h"
typedef int quad __attribute__((mode(TI)));
extern f32 D_L16_001B1C40 __attribute__((sda));
extern f32 D_L16_001B1C50 __attribute__((sda));
extern f32 D_L16_001B1C5C __attribute__((sda));
extern char D_L16_001B9B00[];
extern void func_002AA548(char *, char *, f32, f32, f32, f32);
extern void func_00282CF0(char *, char *, char *);
extern void func_00282D30(char *, char *, f32);
extern void func_00282CC0(char *, char *, char *);
extern void func_L16_00419140(char *);
extern s32 func_002A9640(char *, u32, s32);
extern void func_0032C700(char *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32);
extern void func_0029F338(char *);
extern s32 func_00277258(char *, s32, char *, f32);
extern void func_002A7750(char *, s32, s32);
extern void func_00282F20(char *, char *, f32);
extern void func_0032DA58(char *, char *, char *, f32);
extern void func_002A8C28(char *, char *, u32, s32, s32, s32, f32, f32, f32);

/* Blends three motion segments and finishes with the object's destruction effect. */
void func_L16_00418E38(char *self) {
    char delta[16];
    char *st = *(char **)(self + 0x68);
    char *position;
    char *current;
    char *next;
    f32 *weight, *cursor, *rate, *limit, *gain;
    s32 i;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        position = self + 16;
        qcopy(position, st);
        current = st;
        next = st + 16;
        weight = (f32 *)(st + 0x40);
        cursor = (f32 *)(st + 0x40);
        rate = (f32 *)(st + 0x50);
        limit = &D_L16_001B1C40;
        gain = &D_L16_001B1C50;
        for (i = 0; i < 3; i++, current += 16, next += 16, weight++, rate++, limit++, gain++) {
            if (i == 0 || cursor[-1] > D_L16_001B1C5C)
                func_002AA548((char *)weight, (char *)rate, 1.0f, *limit * 0.00027777778450399637f,
                              *limit * 0.00027777778450399637f, *gain * 0.01666666753590107f);
            func_00282CF0(delta, next, current);
            func_00282D30(delta, delta, *cursor);
            cursor++;
            func_00282CC0(position, position, delta);
        }
        func_L16_00419140(self);
        if (func_002A9640(self, 0x10000, 0)) {
            func_0032C700(position, 0, 0, 0, 0, 20, 45, 1, 1, 0, 0, 0, 1.0f, 20.0f);
            func_0029F338(self);
        } else if (*(f32 *)(st + 0x48) >= 1.0f || (*(f32 *)(st + 0x44) >= 0.5f && func_00277258(position, 0, self, 0.5f)))
            func_002A7750(self, 1, -1);
        break;
    case 1:
        position = self + 16;
        func_00282CF0(delta, D_L16_001B9B00, position);
        func_00282F20(delta, delta, 1.0f);
        func_0032DA58(self, position, delta, 0.0f);
        func_002A8C28(self, position, 0x10001, 0, 1, 0, 2.0f, 5.0f, 1.0f);
        func_0029F338(self);
    }
}
