#include "include_asm.h"

#include "common.h"
typedef struct {
    int a;
    float b;
    int c;
    int d;
} Quad_L26_0040C8A8;
extern void func_PAL_002B4D38(char *, char *, char *, char *, char *, char *, char *, char *,
                          char *, char *, char *);
extern void func_002A7750(char *, int, int);
extern void func_PAL_002B5050(char *, char *, int);
extern int func_PAL_00289730(int, int);
extern int D_L26_001A8FF0[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda)) NOT_SDA;
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern SubtitleHistory D_0018C958[];
extern int D_0018C0B4 NOT_SDA;
extern int D_L26_001B1748[] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));

typedef struct {
    int f0;
    char pad[0x20];
    int f24;
} D_L26_0027D5C8_t;

typedef struct {
    char pad[0x1A4];
    unsigned short f1a4;
    int f1a8;
} D_0018C750_t;

extern D_L26_0027D5C8_t D_L26_0027D5C8;
extern D_0018C750_t D_0018C750;

void func_PAL_L26_00411C98(char *a0) {
    char *s1 = a0;
    char *s0 = *(char **)(s1 + 0x68);
    Quad_L26_0040C8A8 v;

    switch (*(u8 *)(s1 + 0x20)) {
    case 0:
        qzero_nc(&v);
        if (*(int *)(s0 + 0x120) != 0)
            v.b = (float)*(int *)(s0 + 0x120) * 1.7f;
        func_PAL_002B4D38(s1, s0 + 0x60, (char *)&v, 0, 0, 0, 0, 0, 0, 0, 0);
        if (*(int *)(s0 + 0x120) != 0) {
            *(int *)(s0 + 0xD0) = 0;
            *(int *)(s0 + 0x100) = 0;
            *(int *)(s0 + 0xD4) = 0;
        }
        func_002A7750(s1, 1, -1);
        break;
    case 1:
        func_PAL_002B5050(s1, s0 + 0x60, 0);
        break;
    }
}

/* func_PAL_L26_0040C130, the PAL copy of func_L26_004070F8: the same C, where 0x1A5E0 becomes
   0x15F90, the frame counter is scaled to 50 Hz and 0x4B1 becomes 0x3E9. */
void func_PAL_L26_0040C130(char *a0) {
    char *m = a0;
    char *ctl = *(char **)(m + 0x68);
    u8 kind = *(u8 *)(m + 0x20);
    unsigned int mask;

    switch (kind) {
    case 0:
        *(u8 *)(m + 0x30) = 0xFF;
        *(int *)(ctl + 0x4) = 0;
        *(int *)(ctl + 0x10) = 0;
        func_002A7750(m, 1, -1);
        break;
    case 1:
        if (D_L26_001A8FF0[0] != 0) {
            if (D_L26_0027D5C8.f0 == 0 && D_L26_0027D5C8.f24 == -1) {
                unsigned int flags = D_0018C958[28].levels;
                flags &= (unsigned int)kind << D_001A79F0[0];
                if (flags == 0) {
                    func_PAL_00289730(0x9C5, 0x1C);
                }
            }
        }
        if (D_0018C750.f1a4 == 0 ||
            0x15F90u <
                (unsigned int)(((s32)(D_001A7390[0]) * 5 + 2) / 6 - D_0018C750.f1a8)) {
            if (D_0018C0B4 == 0 && D_L26_001B1748[0] >= 0x3E9) {
                unsigned int flags = D_0018C958[12].levels;
                mask = 1u << D_001A79F0[0];
                if ((flags & mask) == 0) {
                    func_PAL_00289730(0x9B5, 0xC);
                }
            }
        }
        break;
    }
}
