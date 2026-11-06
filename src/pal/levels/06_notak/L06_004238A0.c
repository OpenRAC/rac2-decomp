#include "common.h"

/* func_PAL_L06_004238A0, the PAL copy of func_L06_0041F558: the same C, where the three
   func_002AA3A8 rates are scaled by 1.2f at build time and the two func_002AEC48 rates by
   1.44f at run time. They stay in locals so that the product is not folded. */

extern int func_00282978(char *);
extern float func_00283248(float, float);
extern void func_002B0990(char *, char *, float, int, int);
extern void func_002AB8C0(char *, char *);
extern float func_002A89A8(char *, int, float);
extern float func_00282C48(float);
extern float func_002AA3A8(char *, float, float, float, float, char *);
extern float func_00283C80(float, float);
extern float func_00283BE0(float, float);
extern void func_002AEC48(char *, char *, int, float, float);

void func_PAL_L06_004238A0(char *obj)
{
    char *st = *(char **)(obj + 0x68);
    float height, angle, a, b;

    func_002AB8C0(obj, st + 0x50);
    func_00282978(st + 0x24A);
    if (*(unsigned short *)(obj + 0x96) <= 0xFFFE)
        ++*(unsigned short *)(obj + 0x96);
    height = func_002A89A8(obj + 0x10, 0, 0.5f);
    if (func_00282C48(*(float *)(obj + 0x18) - height) < 10.0f) {
        func_002AA3A8(obj + 0x18, height, 0.001f,
                      0.012000001f, 0.21600002f, st + 0x49C);
        if (*(float *)(obj + 0x18) < height)
            *(float *)(obj + 0x18) = height;
    }
    if (func_00283C80(*(float *)(obj + 0xF8),
                      func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                    *(float *)(st + 0x204) - *(float *)(obj + 0x14)))
            <= 2.6179940700531006f && (unsigned char)obj[0x95] == 2) {
        angle = func_00283BE0(
            func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                          *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
            *(float *)(obj + 0xF8));
        a = 0.02f;
        b = 0.3f;
        if (angle > 1.396263599395752f)
            angle = 1.396263599395752f;
        else if (angle < -1.396263599395752f)
            angle = -1.396263599395752f;
        *(float *)(st + 0x588) = angle * 0.75f;
        *(float *)(st + 0x508) = angle * 0.4f;
        func_002AEC48(obj, st + 0x4A0, 1, a * 1.44f, b * 1.44f);
        func_002AEC48(obj, st + 0x520, 2, a * 1.44f, b * 1.44f);
        func_002B0990(obj, st + 0x4A0, 2.5f, 1, 1);
    }
}
