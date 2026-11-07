/* func_PAL_00303950, the PAL copy of func_00302848: the same C, where scale func_002A7820(D_001AE900_blk[5], D_001AE900_blk[6]). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F302848;

extern s32 D_001AE930 __attribute__((sda));
extern s32 D_001AE900 SDATA(D_001AE900);
extern s32 D_001AE928 __attribute__((sda));
extern float D_001AE920[] SDATA(D_001AE920);
extern s32 D_001AE92C __attribute__((sda));
extern float D_001AE8F0 SDATA(D_001AE8F0);
extern float D_001AE8E8 SDATA(D_001AE8E8);
extern s32 D_001AE900_blk[] __asm__("D_001AE900") MACRO_ADDR;
extern float D_001AE920_blk[] __asm__("D_001AE920") MACRO_ADDR;
extern float D_001AE8E8_blk[] __asm__("D_001AE8E8") MACRO_ADDR;
extern float D_001AE8F0_blk[] __asm__("D_001AE8F0") MACRO_ADDR;
extern char D_001A8BD0[16] __attribute__((sda));
extern u8 *D_001F0000[];
extern s32 D_001B1688[4] __attribute__((sda));

extern s32 func_002A77E0(s32);
extern void *func_002C2210(char *, float, float, s32, s32, float, s32, s32, char *, s32);
extern char *func_002C2FD8(char *, s32, s32, s32, s32, s32, s32, float);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, char *);
extern float func_002A7878(float, float);
extern s32 func_002A7820(s32, s32);
extern s32 func_00283D38(s32, s32, float);
extern void *func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);

/* Spawns the object's trail puff; when not suppressed and flag one of the resident word is set it also emits the tinted streak. */
void func_PAL_00303950(char *obj, s32 quiet)
{
    V4_F302848 zero;
    V4_F302848 vec;
    char *rec = *(char **)(obj + 0x68);
    char *puff;
    char *pos;
    s32 tint, color;

    qzero(&zero);
    if (func_002A77E0(D_001AE930) == 0)
        func_002C2210(obj + 0x10, D_001AE920[0], D_001AE920_blk[1], D_001AE92C, D_001AE900_blk[1], 0.0f, 2, func_002A77E0(1) ? -D_001AE928 : D_001AE928, D_001A8BD0, 0);
    pos = obj + 0x10;
    puff = func_002C2FD8(pos, D_001AE900, *(u8 *)(rec + 0x41), 0, 0, 2, 0, D_001AE8F0);
    if (puff != 0)
        puff[2] = *D_001F0000[0x98E];
    if (quiet == 0 && (D_001B1688[0] & 1)) {
        func_002A7A00(&vec, 0.0f, 0.05f);
        func_00282CC0(&vec, &vec, pos);
        zero.f[2] = -(func_002A7878(D_001AE8E8, D_001AE8E8_blk[1]) * 0.020000001f);
        tint = (((int)(func_002A7820(D_001AE900_blk[5], D_001AE900_blk[6])) * 5 + 2) / 6);
        color = func_00283D38(D_001AE900_blk[2], D_001AE900_blk[3], func_002A7878(0.0f, 1.0f));
        func_002C3150(&vec, &zero, color, tint, func_002A77E0(0xFF), 0, D_001AE8F0_blk[2]);
    }
}
