#include "common.h"

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

void func_L06_0041F558(char *obj)
{
    char *st = *(char **)(obj + 0x68);
    float height, angle;

    func_002AB8C0(obj, st + 0x50);
    FastDecTimer(st + 0x24A);
    if (*(unsigned short *)(obj + 0x96) <= 0xFFFE)
        ++*(unsigned short *)(obj + 0x96);
    height = func_002A89A8(obj + 0x10, 0, 0.5f);
    if (func_00282C48(*(float *)(obj + 0x18) - height) < 10.0f) {
        func_002AA3A8(obj + 0x18, height, 0.00083333341171965f,
                      0.010000000707805157f, 0.18000000715255737f, st + 0x49C);
        if (*(float *)(obj + 0x18) < height)
            *(float *)(obj + 0x18) = height;
    }
    if (FastDiffRots(*(float *)(obj + 0xF8),
                      func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                                    *(float *)(st + 0x204) - *(float *)(obj + 0x14)))
            <= 2.6179940700531006f && (unsigned char)obj[0x95] == 2) {
        angle = fast_subtract_rotations(
            func_00283248(*(float *)(st + 0x200) - *(float *)(obj + 0x10),
                          *(float *)(st + 0x204) - *(float *)(obj + 0x14)),
            *(float *)(obj + 0xF8));
        if (angle > 1.396263599395752f)
            angle = 1.396263599395752f;
        else if (angle < -1.396263599395752f)
            angle = -1.396263599395752f;
        *(float *)(st + 0x588) = angle * 0.75f;
        *(float *)(st + 0x508) = angle * 0.4f;
        func_002AEC48(obj, st + 0x4A0, 1, 0.02f, 0.3f);
        func_002AEC48(obj, st + 0x520, 2, 0.02f, 0.3f);
        func_002B0990(obj, st + 0x4A0, 2.5f, 1, 1);
    }
}
