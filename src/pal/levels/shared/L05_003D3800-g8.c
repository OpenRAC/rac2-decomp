#include "include_asm.h"

extern int func_L05_003CFC28(int);
extern float D_L05_001AFB68 __attribute__((sda));
extern void func_002E5DA0(int, int, char *, int);
extern void func_L05_003CFB90(char *, char *);
extern float func_00282E48(void *, void *);
typedef struct {
    char pad000[0x140];
    float f140[4];
    char pad150[0x10];
    float f160;
    int f164;
    int f168;
    int f16C;
} ShakeCamera_003CFAB8;
extern ShakeCamera_003CFAB8 D_L05_001B9580;

/* When the camera is within the object's reach and the object is not class 0x956, passes the
 * camera position to func_L05_003CFB90, calls func_002E5DA0 and starts a camera shake (weaker
 * and shorter for class 0x955). The shake stores are the same in both arms; cross-jumping
 * shares them after scheduling. */
void func_PAL_L05_003D3800(char *obj)
{
    float reach = *(float *)((char *)&D_L05_001AFB68 + 4 * func_L05_003CFC28(*(short *)(obj + 0xAA)));

    if (func_00282E48(obj + 0x10, D_L05_001B9580.f140) <= reach && *(short *)(obj + 0xAA) != 0x956) {
        func_L05_003CFB90(obj, (char *)D_L05_001B9580.f140);
        func_002E5DA0(7, 0, obj, 0xFBF);
        if (*(short *)(obj + 0xAA) == 0x955) {
            D_L05_001B9580.f160 = 0.05f;
            D_L05_001B9580.f168 = 0x19;
            D_L05_001B9580.f16C = 0;
        } else {
            D_L05_001B9580.f160 = 0.15f;
            D_L05_001B9580.f168 = 0x32;
            D_L05_001B9580.f16C = 0;
        }
    }
}
