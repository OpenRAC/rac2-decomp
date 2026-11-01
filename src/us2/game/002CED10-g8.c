#include "include_asm.h"

#include "common.h"
typedef struct {
    short ids[4];
    short name;
    short value;
    short description;
    short detail;
    short stats[4];
} Item;
extern char *D_001A8CFC;
extern int D_001A7340;
extern int D_001AB9B0 __attribute__((sda));
extern int D_001AB9B8 __attribute__((sda));
extern int D_001AB9BC __attribute__((sda));
extern unsigned short D_00188510[][2];
extern Item D_00264630[];
extern int D_00138340 NOT_SDA;
extern float D_001B23A8;
extern int D_001B23A0;
extern char D_001AB9C0[], D_001AB9C8[], D_001AB9D8[];
extern int func_002A9588(int, int, int, int, int);
extern void func_0027C540(long), func_0027C660(void);
extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern void func_0027F5B8(int, int, u64, char *, int);
extern int func_0027FAA8(int, int, u64, char *, int);
extern int func_0027FB40(int, int, u64, char *, int);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern void func_0028FC48(int, int, int, int, u64, int);
extern void func_0027F120(void), func_0027F110(void);
extern void func_0027FA10(int, int, u64, char *, int);

int func_US2_002CED10(void)
{
    char text[64];
    int inactive, color, width, center, count;
    char *format, *count_format;
    int active = 1;
    float alpha, zero = 0.0f;

    inactive = func_002A9588(0x60442D00, 0x80FFDE8D, 25, 0, 0);
    func_0027C540(0);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xAE), 0x60442D00, (float)(D_001A7340 / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xAF), 0x60241700, (float)(D_001A7340 / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xB0), 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xB1), 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001AB9BC, 1.0f, D_001B23A8, zero);
    func_0027F5B8(31, 62, 0x80F0F0F0ULL, func_00288FB8(0x3089), -1);
    func_0027F5B8(31, 92, 0x80F0F0F0ULL, func_00288FB8(0x308A), -1);
    func_0027F5B8(31, 122, 0x80F0F0F0ULL, func_00288FB8(0x3088), -1);
    func_0027F5B8(31, 152, 0x80F0F0F0ULL, func_00288FB8(0x308B), -1);

    format = D_001AB9C0;
    func_00115DA8(text, format, func_00288FB8(0x308C));
    count = func_001157AC(text);
    func_0027F5B8(31, 184, 0x80F0F0F0ULL, text, count);
    func_00115DA8(text, format, func_00288FB8(0x308D));
    count = func_001157AC(text);
    func_0027F5B8(31, 201, 0x80F0F0F0ULL, text, count);
    func_0027FA10(475, 373, 0x80F0F0F0ULL, func_00288FB8(0x2DD8), -1);
    func_0027FAA8(154, 26, 0x80F0F0F0ULL, func_00288FB8(0x305C), -1);

    if (D_00188510[D_001AB9B0][0] != 0 || D_00188510[D_001AB9B0][1] != 0) {
        width = (int)((float)D_00264630[D_001AB9B0].stats[0] * 2.44f);
        if (width > 244)
            width = 244;
        func_0028FC48(31, 78, width + 31, 88, 0x55F0C070ULL, 0);
        width = (int)((float)D_00264630[D_001AB9B0].stats[1] * 2.44f);
        if (width > 244)
            width = 244;
        func_0028FC48(31, 108, width + 31, 118, 0x55F0C070ULL, 0);
        width = (int)((float)D_00264630[D_001AB9B0].stats[2] * 2.44f);
        if (width > 244)
            width = 244;
        func_0028FC48(31, 139, width + 31, 150, 0x55F0C070ULL, 0);
        width = (int)((float)D_00264630[D_001AB9B0].stats[3] * 2.44f);
        if (width > 244)
            width = 244;
        func_0028FC48(31, 169, width + 31, 180, 0x55F0C070ULL, 0);
        if (D_001AB9B0 < D_001AB9B8) {
            color = (D_00138340 & 0x2000) ? 0x80F0F0F0 : inactive;
            {
                char *sprite = func_00336D50(D_001A8CFC + 0x8710, 0x4A);
                {
                    float factor = 0.8f;
                    alpha = D_001B23A8 * factor;
                }
                if (D_001B23A0 == active)
                    alpha += -0.05f;
                func_00300A00(sprite, color, 316.0f, 278.0f, 1.0f, alpha, zero);
            }
            func_0027FA10(470, 276, 0x80F0F0F0ULL, func_00288FB8(0x2DD7), -1);
        }
        if (D_001AB9B0 >= 2) {
            color = (D_00138340 & 0x8000) ? 0x80F0F0F0 : inactive;
            {
                char *sprite = func_00336D50(D_001A8CFC + 0x8710, 0x4B);
                {
                    float factor = 0.8f;
                    alpha = D_001B23A8 * factor;
                }
                if (D_001B23A0 == 1)
                    alpha += -0.05f;
                func_00300A00(sprite, color, 207.0f, 278.0f, 1.0f, alpha, zero);
            }
            func_0027F5B8(55, 276, 0x80F0F0F0ULL, func_00288FB8(0x2DD6), -1);
        }
        func_0027F120();
        center = D_001A7340 / 2;
        func_0027FB40(center, 276, 0x80F0F0F0ULL, func_00288FB8(D_00264630[D_001AB9B0].name), -1);
        func_0027F110();
        func_0027F5B8(156, 185, 0x80F0F0F0ULL, func_00288FB8(D_00264630[D_001AB9B0].description), -1);
        if (D_00264630[D_001AB9B0].detail == -1) {
            func_00115DA8(text, D_001AB9C8);
            count = func_001157AC(text);
            func_0027F5B8(156, 202, 0x80F0F0F0ULL, text, count);
        } else {
            func_0027F5B8(156, 202, 0x80F0F0F0ULL, func_00288FB8(D_00264630[D_001AB9B0].detail), -1);
        }
        count = D_00188510[D_001AB9B0][0];
        count_format = D_001AB9D8;
        func_00115DA8(text, count_format, count, func_00288FB8(0x2DF7));
        count = func_001157AC(text);
        func_0027FB40(152, 228, 0x80F0F0F0ULL, text, count);
    }
    func_0027C660();
    return 0;
}
