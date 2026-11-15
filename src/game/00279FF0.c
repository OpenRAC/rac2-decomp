#include "names.h"
/* func_00279FF0: copies one of two display configurations (the one at 0x1AD584 while
 * the flag at 0x1B5600 is set, else the one at 0x1B1640) into the settings block at
 * 0x1B9040, sets the mode word and applies it. The sources and the mode words are sda
 * objects: -G0 addresses them with the assembler macros, and the mode store in the
 * branch delay slot becomes the $gp form, as retail has it. */
typedef struct {
    unsigned char a, b, c, pad;
    float x, y, z, w;
} Config;

typedef struct {
    char pad000[0x218];
    float x;
    float y;
    char pad220[8];
    float z;
    float w;
    int a;
    int b;
    int c;
} Settings;

extern int D_001B5600;
extern Config D_001AD584 __attribute__((sda));
extern Config D_001B1640 __attribute__((sda));
extern Settings D_001B9040;
extern int D_001B1DA0 __attribute__((sda));
extern int D_001B1654 __attribute__((sda));
extern void func_0027AB40(void);

/* Loads one of two display settings into the live settings block and applies it. */
void func_00279FF0(void)
{
    if (D_001B5600 != 0) {
        D_001B9040.a = D_001AD584.a;
        D_001B9040.b = D_001AD584.b;
        D_001B9040.c = D_001AD584.c;
        D_001B9040.x = D_001AD584.x;
        D_001B9040.y = D_001AD584.y;
        D_001B9040.z = D_001AD584.z;
        D_001B9040.w = D_001AD584.w;
        D_001B1DA0 = 0x40000;
    } else {
        D_001B9040.a = D_001B1640.a;
        D_001B9040.b = D_001B1640.b;
        D_001B9040.c = D_001B1640.c;
        D_001B9040.x = D_001B1640.x;
        D_001B9040.y = D_001B1640.y;
        D_001B9040.z = D_001B1640.z;
        D_001B9040.w = D_001B1640.w;
        D_001B1DA0 = 0x1F4000;
    }
    UpdateViewContext();
    D_001B1654 = 0;
}
