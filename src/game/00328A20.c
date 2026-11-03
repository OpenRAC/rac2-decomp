#include "include_asm.h"
extern float func_00283CE0(int);
extern float func_00283180(float);
extern int func_00283CF0(float);
extern float func_002A7798(float);
extern int func_002A7820(int, int);
extern void func_00328B68(char *);
extern void func_00328D98(char *, int, int, float, char *, int, char *, float);
extern void func_00328F18(char *, int, int, float, float, int, int, float);
extern void func_00329488(char *);
extern char D_0022B0A0[];

void func_00328A20(char *obj)
{
    char *data;
    float f;
    char *pos;

    data = *(char **)(obj + 0x68);
    if ((unsigned char)(*(unsigned char *)(obj + 0x20) - 2) < 2) {
        pos = data + 0x30;
        f = func_00283CE0(*(int *)(data + 0x44)) / func_00283CE0(0x14);
        func_00328D98(pos, 0x204080, *(int *)(data + 0x58),
                       func_002A7798(1.0f - f) * 0.75f, (char *)0x2E, 1,
                       data + 0x20, 0.0f);
    }
    func_00328B68(obj);
    func_00328F18(obj + 0x10, 0x7F7F7F, func_002A7820(0x20, 0x40), 0.125f, 0.0f, 0xB, 2, 0.3f);
    func_00328F18(obj + 0x10, 0x103080, func_002A7820(0x20, 0x40), 0.225f, 0.0f, 0xB, 2, 0.31f);
    func_00329488(obj);
}

/* Draws the glow of every particle record (100 x 0x40 bytes at D_0022B0A0) owned by obj:
 * the record's +0x30 angle, shifted by pi, gives a 0..1 sine level; 128 times that
 * becomes the shared intensity of two func_00328F18 quads. */
void func_00328B68(char *obj)
{
    int i;
    float s;
    int n;

    for (i = 0; i < 100; i++) {
        char *e = D_0022B0A0 + i * 0x40;
        if (*(char **)(e + 0x34) == obj) {
            s = (func_00283180(*(float *)(e + 0x30) - 3.1415927f) + 1.0f) * 0.5f;
            n = func_00283CF0(s * 128.0f);
            func_00328F18(e + 0x10, 0x103080, n, 0.125f, 0.0f, 0x2E, 2, 0.011f);
            func_00328F18(e + 0x10, 0x7F7F7F, n, 0.0625f, 0.0f, 0x2E, 2, 0.011f);
        }
    }
}
