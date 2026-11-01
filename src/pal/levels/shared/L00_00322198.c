#include "include_asm.h"

#include "common.h"
typedef struct { float f[4]; } BurstVector __attribute__((aligned(16)));
typedef struct { int values[6]; } BurstPalette;
typedef struct {
    float offset[4];
    unsigned char colors[16];
    float radius[3], intensity, falloff;
    int value34, value38;
    unsigned char options[4];
    unsigned short timers[4];
    unsigned char flags48, flags49;
} BurstFlashTemplate;
extern BurstPalette D_L00_001AA260[], D_L00_001AA278[];
extern BurstFlashTemplate D_L00_00281760[] __attribute__((aligned(16)));
extern void func_00282C88(void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern int func_002AAFA0(unsigned int, int);
extern int func_002A7820(int, int);
extern char *func_002BBCB0(void *, void *, int, int, float, int, int, int, int, float);
extern void func_002AAF40(int *, int *, int *, int);
extern char *func_PAL_003096D0(char *, char *, char *, float, int,
                          unsigned char, unsigned char, unsigned char, unsigned char);
extern char *func_00312B70(char *, void *, int, void *);

void func_PAL_L00_00322198(char *parent, char *position, float scale, float flash)
{
    BurstVector zero;
    BurstPalette first, second;
    int rgb[3];
    int i;
    float speed, size, glow;
    func_00282C88(&zero);
    for (i = 2; i >= 0; i--) {
        int firstColor, secondColor, life, fadeLife;
        speed = func_002A7878(8.0f, 10.0f) * 0.020000001f;
        size = scale * 500000.0f;
        first = D_L00_001AA260[0];
        second = D_L00_001AA278[0];
        firstColor = func_002AAFA0(first.values[func_002A77E0(6)], 1);
        secondColor = func_002AAFA0(second.values[func_002A77E0(6)], 1);
        life = func_002A7820(12, 17);
        fadeLife = func_002A7820(21, 25);
        func_002BBCB0(position, &zero, firstColor, secondColor,
                      size, life, fadeLife, 0, 0, speed * scale);
    }
    if (parent) {
        rgb[0] = 127; rgb[1] = 64; rgb[2] = 0;
        func_002AAF40(rgb, rgb + 1, rgb + 2, 1);
        glow = scale * 4.0f;
        func_PAL_003096D0(parent, position, (char *)&zero, glow, 17,
                      *(unsigned char *)&rgb[0], *(unsigned char *)&rgb[1],
                      *(unsigned char *)&rgb[2], 48);
        rgb[0] = 96; rgb[1] = 32; rgb[2] = 0;
        func_002AAF40(rgb, rgb + 1, rgb + 2, 1);
        glow = scale * 3.0f;
        func_PAL_003096D0(parent, position, (char *)&zero, glow, 24,
                      *(unsigned char *)&rgb[0], *(unsigned char *)&rgb[1],
                      *(unsigned char *)&rgb[2], 32);
    }
    if (flash != 0.0f) {
        if (flash > 0.0f) {
            D_L00_00281760[0].radius[1] = flash;
            D_L00_00281760[0].radius[2] = flash;
            D_L00_00281760[0].radius[0] = flash;
        } else {
            D_L00_00281760[0].radius[1] = 13.0f;
            D_L00_00281760[0].radius[2] = 13.0f;
            D_L00_00281760[0].radius[0] = 13.0f;
        }
        func_00312B70((char *)D_L00_00281760, position, 0, 0);
    }
}

