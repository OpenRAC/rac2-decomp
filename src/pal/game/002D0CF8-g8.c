#include "include_asm.h"

#include "common.h"
extern void func_0027C540(long);
extern void func_0027C660(void);
extern int func_00336D50(char *, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, u64, char *, int);
extern int func_0027FB40(int, int, u64, char *, int);
extern int func_001157AC(char *);
extern int func_0027F198(char *, int);
extern void func_002CF0A0(int, int);
extern void func_002CEBD0(void);
extern char *D_001A8CFC;
extern int D_001A7340;
extern float D_001B23A8;
extern void func_0027F120(void);
extern void func_0027F110(void);
extern int func_002B0E90(void);
extern int func_00115DA8(char *, char *, ...);
extern void func_0028FC48(int, int, int, int, u64, int);
extern int D_001AB9FC __attribute__((sda));
extern int D_001ABA00 __attribute__((sda));
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern short D_0026CF18[][3];
extern int func_0027F538(int, int, u64, char *, int);

int func_PAL_002D0CF8(void) {
    char buf[64];
    int r, i, y, k, color;
    char *text;
    float z;
    func_0027C540(0);
    z = 0.0f;
    r = func_00336D50(D_001A8CFC + 0x8710, 0xD7);
    func_00300A00(r, 0x60442D00, (float)(D_001A7340 / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xD8);
    func_00300A00(r, 0x60241700, (float)(D_001A7340 / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xD9);
    func_00300A00(r, 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xDA);
    func_00300A00(r, 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001ABA00, 1.0f, D_001B23A8, z);
    func_0027F120();
    func_0027FAA8(0xB9, 0x1B, 0x80F0F0F0ULL, func_00288FB8(0xC20), -1);
    text = func_00288FB8(0xE54);
    func_00115DA8(buf, text, func_002B0E90(), 30);
    func_0027F538(0x46, 0x175, 0x80F0F0F0ULL, buf, -1);
    func_0027F110();
    func_0027FAA8(0x1AD, 0x177, 0x80F0F0F0ULL, func_00288FB8(0xB60), -1);
    func_0028FC48(0x15E, 0xDA, 0x1E6, 0xDC, 0x55F0C070ULL, 0);
    if (D_0026CF18[D_001AB9FC][2] != -1)
        func_0027FB40(0x1A0, 0xE0, 0x80F0F0F0ULL, func_00288FB8(D_0026CF18[D_001AB9FC][2]), -1);
    func_002CEBD0();
    for (y = 0x112, i = 0; i < 5; i++, y += 20) {
        char *label;
        k = i + D_001AB9FC - 2;
        if (k < 0) k += 30;
        if (k >= 30) k -= 30;
        color = 0x80F0F0F0;
        label = func_00288FB8(D_0026CF18[k][0]);
        if (D_001A7A60[k]) color = 0x7029A1FF;
        color &= 0xFFFFFF;
        if (i == 0 || i == 4) color |= 0x10000000;
        else if (i == 1 || i == 3) color |= 0x50000000;
        else {
            color |= 0x70000000;
            func_002CF0A0(func_0027F198(label, func_001157AC(label)), color);
        }
        func_0027FB40(D_001A7340 / 2, y, color, label, -1);
    }
    func_0027C660();
    return 0;
}
