#include "include_asm.h"

#include "common.h"
extern void func_00282F20(float *, float *, float);
extern char D_0022B0A0[];
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

void func_PAL_0032A0E0(char *owner)
{
    int address = (int)D_0022B0A0;
    char *position = (char *)(address + 0x10);
    char *other = (char *)(address + 0x20);
    int remaining = 99;
    char *base = (char *)address;
    char *data = *(char **)(owner + 0x68);
    do {
        if (*(char **)(position + 0x24) == owner) {
            func_00283098(position, base, owner + 0xC0);
            func_00282F20((float *)other, (float *)position, 1.0f);
            func_00282CC0(position, position, owner + 0x10);
            *(float *)(position + 0x20) += 0.75398237f;
            if (*(float *)(position + 0x20) >= 6.2831854820251465f) {
                *(int *)(position + 0x24) = 0;
                --*(int *)(data + 0x48);
            }
        }
        base += 0x40;
        other += 0x40;
        position += 0x40;
    } while (--remaining >= 0);
}


extern float func_00283CE0(int);
extern float func_002A7798(float);
extern int func_002A7820(int, int);
extern void func_00328B68(char *);
extern void func_00328D98(char *, int, int, float, char *, int, char *, float);
extern void func_00328F18(char *, int, int, float, float, int, int, float);
extern void func_00329488(char *);

void func_PAL_0032A1E8(char *obj)
{
    char *data;
    float f;
    char *pos;

    data = *(char **)(obj + 0x68);
    if ((unsigned char)(*(unsigned char *)(obj + 0x20) - 2) < 2) {
        pos = data + 0x30;
        f = func_00283CE0(*(int *)(data + 0x44)) / func_00283CE0(0x11);
        func_00328D98(pos, 0x204080, *(int *)(data + 0x58),
                       func_002A7798(1.0f - f) * 0.75f, (char *)0x2E, 1,
                       data + 0x20, 0.0f);
    }
    func_00328B68(obj);
    func_00328F18(obj + 0x10, 0x7F7F7F, func_002A7820(0x20, 0x40), 0.125f, 0.0f, 0xB, 2, 0.3f);
    func_00328F18(obj + 0x10, 0x103080, func_002A7820(0x20, 0x40), 0.225f, 0.0f, 0xB, 2, 0.31f);
    func_00329488(obj);
}

