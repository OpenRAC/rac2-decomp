/* func_PAL_L05_003D2D78, the PAL copy of func_L05_003CF040: the same C, where rename func_L05_003CFAB8 becomes func_PAL_L05_003D3800; rename func_L05_003CF350 becomes func_PAL_L05_003D3098; wrap (D_L05_001AFBE4 - 1.0f) (({e}) * 1.2f). */
#include "common.h"
extern void func_L05_003CF9C8(char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float D_L05_001AFBE4 __attribute__((sda));
extern float D_L05_001AFB68[1] __attribute__((sda));
extern int func_002829D8(void *);
extern void func_0029F338(char *);
extern float func_00282C48(float);
extern int func_L05_003CFC28(int);
extern float func_00283B98(float, float);
extern void func_PAL_L05_003D3800(char *);
extern int func_PAL_L05_003D3098(char *);
extern int func_002E5DA0(int, int, char *, int);
extern int D_001A79F0;
extern unsigned char D_00139619[1] NOT_SDA;
extern void func_L05_003CFCF0(char *, int, int);
void func_PAL_L05_003D2D78(unsigned char *obj)
{
    char *s = *(char **)(obj + 0x68);
    int kind;
    switch ((unsigned char)obj[0x20]) {
    case 0:
        obj[0x20] = 1;
        func_L05_003CF9C8(obj);
    case 2:
    case 3:
        func_00282CC0(obj + 0x10, obj + 0x10, s + 0x10);
        func_00282D30(s + 0x10, s + 0x10, (((D_L05_001AFBE4 - 1.0f)) * 1.2f) + 1.0f);
        if ((unsigned char)obj[0x20] != 2) {
            if (func_002829D8(s + 0xC) && (unsigned char)obj[0x31] == 0) {
                func_0029F338(obj);
                return;
            }
        } else {
            if (func_00282C48(*(float *)(s + 0x10)) < 0.01f &&
                func_00282C48(*(float *)(s + 0x14)) < 0.01f &&
                func_00282C48(*(float *)(s + 0x18)) < 0.01f)
                obj[0x20] = 1;
        }
    case 1:
        kind = func_L05_003CFC28(*(short *)(obj + 0xAA));
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * D_L05_001AFB68[kind];
        *(float *)(obj + 0xF0) = func_00283B98(*(float *)s, *(float *)(obj + 0xF0));
        *(float *)(obj + 0xF4) = func_00283B98(*(float *)(s + 4), *(float *)(obj + 0xF4));
        *(float *)(obj + 0xF8) = func_00283B98(*(float *)(s + 8), *(float *)(obj + 0xF8));
        func_PAL_L05_003D3800(obj);
        if (func_PAL_L05_003D3098(obj) || *(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
            *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
            *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
            if (D_L05_001AFB68[kind] >= 5.0f) {
                func_002E5DA0(0, 0, obj, 0x956);
                if (D_001A79F0 == 5 && D_00139619[0] == 0)
                    func_L05_003CFCF0(obj, 1, 5);
                else
                    func_L05_003CFCF0(obj, 0, 5);
            } else {
                if (*(short *)(obj + 0xAA) == 0x954) func_002E5DA0(0, 0, obj, 0x954);
                if (*(short *)(obj + 0xAA) == 0x955) func_002E5DA0(0, 0, obj, 0x955);
            }
            func_0029F338(obj);
        }
        break;
    }
}
