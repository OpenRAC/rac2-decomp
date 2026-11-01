#include "include_asm.h"

struct SolIds {
    int ids[2];
};
extern struct SolIds D_001ADDD0;
extern char D_001ADDD8[];
extern int D_001A7340 __attribute__((sda));
extern int D_001A7BB8 __attribute__((sda));
extern float D_001B23A4 __attribute__((sda));
extern void func_US2_0033BF90(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027FAA8(int, int, unsigned long, char *, int);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern void func_00280190(void *, unsigned long, char *, int);

void func_US2_0033D070(char *object)
{
    char buffer[64];
    struct SolIds pair;
    char scratch[32];
    char *format;
    char *first;
    char *second;
    float x;
    int w, h;

    func_US2_0033BF90(object + 8);
    pair = D_001ADDD0;
    format = D_001ADDD8;
    first = func_00288FB8(0x307B);
    second = func_00288FB8(pair.ids[D_001A7BB8 != 0]);
    func_00115DA8(buffer, format, first, second);
    func_0027FAA8(D_001A7340 >> 1, 0x8C, 0x80F0F0F0UL, buffer, -1);
    x = D_001B23A4;
    w = (int)(x * 170.0f + 0.5f);
    if (w != 0)
        h = (int)(x * 379.0f + 0.5f);
    else
        h = (int)(x * 379.0f + 0.5f);
    func_002802E0(scratch, w, h, 44, 468, 254, 222, 20, 3);
    func_00280190(scratch, 0x80F0F0F0UL, func_00288FB8(0x3136), -1);
}
