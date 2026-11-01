#include "include_asm.h"

#include "common.h"
extern void func_0027C540(int);
extern void func_0027C660(void);
extern int func_00336D50(char *, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int,int,u64,char *,int);
extern int func_0027FB40(int,int,u64,char *,int);
extern int func_001157AC(char *);
extern int func_0027F198(char *,int);
extern void func_002CF0A0(int,int);
extern void func_002CEBD0(void);
extern char *D_001A8CFC;
extern int D_001A7340;
extern float D_001B23A8;
extern int D_001ABA20 __attribute__((sda));
extern int D_001ABA24 __attribute__((sda));
extern short D_00261858[][3];

int func_US2_002D1B20(void) {
    int i, y, k, color;
    int r;
    char *text;
    float z;
    func_0027C540(0);
    z = 0.0f;
    r = func_00336D50(D_001A8CFC + 0x8710, 0xD7);
    func_00300A00(r, 0x60442D00, (float)(D_001A7340 / 2), (float)D_001ABA24, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xD8);
    func_00300A00(r, 0x60241700, (float)(D_001A7340 / 2), (float)D_001ABA24, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xD9);
    func_00300A00(r, 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001ABA24, 1.0f, D_001B23A8, z);
    r = func_00336D50(D_001A8CFC + 0x8710, 0xDD);
    func_00300A00(r, 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001ABA24, 1.0f, D_001B23A8, z);
    func_0027FAA8(0xB3, 0x1B, 0x80F0F0F0ULL, func_00288FB8(0x2CA9), -1);
    func_0027FAA8(0x161, 0x177, 0x80F0F0F0ULL, func_00288FB8(0x2BE5), -1);
    func_0027FAA8(0xB5, 0x177, 0x80F0F0F0ULL, func_00288FB8(0x2C0B), -1);
    func_002CEBD0();
    for (i = 0, y = 0x112; i < 5; i++, y += 20) {
        k = i + D_001ABA20 - 2;
        if (k < 0) k += 33;
        if (k >= 33) k -= 33;
        text = func_00288FB8(D_00261858[k][2] ? D_00261858[k][0] : 0x2C56);
        if (i == 0 || i == 4) color = 0x10F0F0F0;
        else if (i == 1 || i == 3) color = 0x50F0F0F0;
        else {
            color = 0x70F0F0F0;
            func_002CF0A0(func_0027F198(text, func_001157AC(text)), 0x70F0F0F0);
        }
        func_0027FB40(D_001A7340 / 2, y, color, text, -1);
    }
    func_0027C660();
    return 0;
}
