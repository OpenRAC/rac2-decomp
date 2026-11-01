#include "include_asm.h"

typedef unsigned char u8;
typedef int s32;
typedef float f32;
extern u8 D_00189E20_7[];
extern void func_002AA3A8(f32 *a, f32 *b, f32 c, f32 d, f32 e, f32 f);
extern f32 func_00282C48(f32 v);
extern void func_002AA2E8(f32 *p, f32 v, f32 w);
typedef struct {
    u8 pad000[0x88];
    f32 f088;
    u8 pad08C[0x1B8 - 0x08C];
    s32 i1B8;
    u8 pad1BC[0x330 - 0x1BC];
    f32 f330;
    u8 pad334[0x790 - 0x334];
    f32 f790;
    f32 f794;
    u8 pad798[4];
    f32 f79C;
    f32 f7A0;
    u8 pad7A4[0x9B0 - 0x7A4];
    f32 f9B0;
    u8 pad9B4[0xA3C - 0x9B4];
    f32 fA3C;
    u8 padA40[0x2294 - 0xA40];
    s32 i2294;
    u8 pad2298[4];
    s32 i229C;
    u8 pad22A0[4];
    s32 i22A4;
    u8 pad22A8[8];
    s32 i22B0;
} Res_F458c670e;

/* func_L00_002C8CB0 is built in its dedicated unit. */

/* func_L00_002C8E10 is built in its dedicated G8 unit. */

/* Drives one effect state: branches on several resource fields, decays and integrates two float components through three float helpers, and writes back the summed value. */
void func_PAL_L00_002C95C0(void)
{
    f32 old, v, r, sum;

    if (((Res_F458c670e *)D_00189E20_7)->i1B8 >= 9
        || ((Res_F458c670e *)D_00189E20_7)->f790 < 0.0f
        || ((Res_F458c670e *)D_00189E20_7)->i22A4 == 17
        || ((Res_F458c670e *)D_00189E20_7)->i22B0 == 17) {
        if (((Res_F458c670e *)D_00189E20_7)->i2294 == 53) {
            func_002AA3A8(&((Res_F458c670e *)D_00189E20_7)->f790,
                    &((Res_F458c670e *)D_00189E20_7)->fA3C,
                    0.0f, 0.0432f, 0.43200004f, 0.030000001f);
            ((Res_F458c670e *)D_00189E20_7)->f794 = 0.0f;
        } else {
            old = ((Res_F458c670e *)D_00189E20_7)->f790;
            v = ((Res_F458c670e *)D_00189E20_7)->f794;
            ((Res_F458c670e *)D_00189E20_7)->f794 =
                v - (old * 0.0072000003f + v * 0.054000005f);
            r = func_00282C48(old);
            if (r < 0.001f) {
                if (((Res_F458c670e *)D_00189E20_7)->f794 < 0.0001f)
                    ((Res_F458c670e *)D_00189E20_7)->f794 = 0.0f;
            }
        }
    }
    sum = ((Res_F458c670e *)D_00189E20_7)->f790
        + ((Res_F458c670e *)D_00189E20_7)->f794;
    ((Res_F458c670e *)D_00189E20_7)->f790 = sum;
    if (((Res_F458c670e *)D_00189E20_7)->i2294 == 53) {
        if (sum > 0.0f) {
            if (((Res_F458c670e *)D_00189E20_7)->f794 > 0.0f)
                ((Res_F458c670e *)D_00189E20_7)->f794 = 0.0f;
            func_002AA2E8(&((Res_F458c670e *)D_00189E20_7)->f790,
                    0.0f, 0.014f);
        }
    }
    if (((Res_F458c670e *)D_00189E20_7)->i2294 != 124) {
        f32 x = ((Res_F458c670e *)D_00189E20_7)->f330;
        if (((Res_F458c670e *)D_00189E20_7)->i229C == 22)
            x = ((Res_F458c670e *)D_00189E20_7)->f9B0;
        func_002AA3A8(&((Res_F458c670e *)D_00189E20_7)->f79C,
                &((Res_F458c670e *)D_00189E20_7)->f7A0,
                x, 0.03888f, 0.43200004f, 0.0f);
    }
    ((Res_F458c670e *)D_00189E20_7)->f088 =
        (((Res_F458c670e *)D_00189E20_7)->f79C + (-0.12f))
        + ((Res_F458c670e *)D_00189E20_7)->f790;
}



extern char D_00189E20_4[];
extern void func_L00_002C42E0(int a0, int a1);
extern int func_L00_0032EF10(int, int, int *);
extern int func_L00_002C3A40(void);
extern int func_L00_0032EFB0(int, int, int, int);
extern int D_00138320[];

/* Looks the object up in the shared table and stops when the lookup fails; otherwise the state
 * machine's offset advances the object and a second lookup asks for a transition when it
 * succeeds.  A set state word, a timer past 0.9 and a state other than the idle one ask for the
 * same transition, and a zero second argument asks for it with another code. */
int func_PAL_L00_002CA360(int arg0, int arg1)
{
    int index;
    int r;
    char *p;

    if (func_L00_0032EF10(0x40, arg0, &index) == 0)
        return 0;
    r = func_L00_002C3A40();
    if ((D_00138320[0] & 8) && r > 0) {
        if (func_L00_0032EFB0(0x40, 0x1F000, arg0 + r, r) != 0) {
            func_L00_002C42E0(0xB, 1);
            return 1;
        }
    }
    p = D_00189E20_4;
    if (*(short *)(p + 0x1454) != 0) {
        if (0.9f < *(float *)(p + 0x24B8)) {
            if (func_L00_002C3A78() != 2) {
                func_L00_002C42E0(0xB, 1);
                return 1;
            }
        }
    }
    if (arg1 != 0)
        return 0;
    func_L00_002C42E0(7, 1);
    return 1;
}

