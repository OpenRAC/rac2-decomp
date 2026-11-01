#include "include_asm.h"

typedef unsigned char u8;
typedef float f32;
extern u8 D_00189E20_1[];
typedef struct {
    u8 pad0[0x98];
    f32 f98;
    u8 pad1[0x1A0 - 0x9C];
    f32 f1A0;
    f32 f1A4;
    f32 f1A8;
    u8 pad2[0x1B0 - 0x1AC];
    f32 f1B0;
    f32 f1B4;
    u8 pad3[0x1FC - 0x1B8];
    short a;
    u8 pad4[0xA70 - 0x1FE];
    f32 fA70;
    f32 fA74;
    f32 fA78;
    u8 pad4b[0x1FB0 - 0xA7C];
    f32 f1FB0;
    f32 f1FB4;
    u8 pad5[0x22C3 - 0x1FB8];
    u8 flag;
    u8 pad6[0x24F4 - 0x22C4];
    short b;
} D00189E20_Overlay;
extern D00189E20_Overlay D_00189E20;
extern void *D_L00_002A00A0[31];

/* Dispatches on the argument through the level's table: the five listed cases write
 * 0x46 at +0x1FC and 3 at +0x24F4 of the resident block, the other twenty-six and every
 * argument out of the range only return. */
void func_PAL_L00_002B1200(int a0)
{
    /* Keeps the two arms alive: the addresses land in the discarded .data. */
    static void *cases[31] = {
        &&arm, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&arm, &&arm, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret, &&ret,
        &&ret, &&ret, &&ret, &&ret, &&ret, &&arm, &&arm
    };

    if ((unsigned int)(a0 - 14) < 31) {
        goto *D_L00_002A00A0[a0 - 14];
    } else {
        goto ret;
    }
arm:
    D_00189E20.b = 3;
    D_00189E20.a = 0x3A;
ret:
    return;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002B1248);

extern void func_L00_002B1F90(void);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int D_L00_001B18D8[] __attribute__((sda)), D_L00_001B19C8[] __attribute__((sda));
extern void func_PAL_L00_002B1248(int);
extern int D_L00_001B18D8[] __attribute__((sda));

/* Per-frame pass over the seven 80-byte slots at +0x1220: an empty slot is released; in
 * state 2 a slot counts a tick, is released and, for a flagged entry whose animation set
 * allows it, starts animation 1; in state 3 it counts a byte tick and slots 0 and 1 (or a
 * flagged entry) are reinstalled with the shared value plus 2.  The entry's update
 * callback then runs, except for slot 6, a 253/254 sentinel entry, or slot 0 while the
 * block's word at +0x1500 is set and its mode at +0x1248 is not 10. */
void func_PAL_L00_002B1E88(void)
{
    int i;

    for (i = 0; i < 7; i++) {
        u8 *base = D_00189E20_1;
        u8 *slot = base + i * 80;
        u8 *entry = *(u8 **)(slot + 0x1220);
        void (*callback)(char *);

        if (entry != 0) {
            switch (*(int *)(slot + 0x1244)) {
            case 2:
                ++*(int *)(slot + 0x1240);
                func_PAL_L00_002B1248(i);
                if ((entry[0x60] & 2) && entry[0x43] == 0
                    && (*(u8 **)(entry + 0x24))[0xC] >= 2)
                    func_PAL_002A7E68(entry, 1, 0, 2);
                break;
            case 3:
                ++slot[0x123B];
                if ((entry[0x60] & 2) || i == 1 || i == 0)
                    func_L00_002B1230(i, D_L00_001B18D8[0] + 2);
                break;
            }
            {
                u8 *block = D_00189E20_1;

                if (*(int *)(block + 0x1500) != 0 && i == 0
                    && *(int *)(block + 0x1248) != 10)
                    continue;
            }
            if (entry != 0 && entry[0x20] != 254 && entry[0x20] != 253 && i != 6) {
                callback = *(void (**)(char *))(entry + 0x64);
                if (callback != 0)
                    callback((char *)entry);
            }
        } else {
            func_PAL_L00_002B1248(i);
        }
    }
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L00_002B20F8);

extern void func_PAL_L00_002AF6C0(void);
extern void func_PAL_L00_002B1E88(void);
extern void func_0028B3D0(int, int, char *, char *, char *, int, int);
extern void func_L00_00322EC8(char *);
extern void func_L00_002D2E68(void);
extern void func_L00_002A6708(void);
extern void func_L00_002A53B8(void);
extern void func_PAL_L00_002B3210(void);
extern void func_L00_002D24B8(void);
extern void func_002A677C(char *);
extern void func_PAL_L00_002C4480(int, int);
extern void func_L00_002F6B90(int);
extern int D_00138320[];
extern char D_L00_002F8588[];
extern char D_L00_002F85D0[];
extern char D_L00_002F8AD8[];
extern int D_00138320[];

/* Reset the hero update state, install the requested mode and object, and update the mode-one counters. */
void func_PAL_L00_002B2958(int mode, int value, char *object)
{
    char *p;
    char *current;
    int count;

    func_PAL_L00_002AF6C0();
    p = (char *)D_00189E20_1;
    p[0x22B6] = 1;
    func_PAL_L00_002B1E88();
    *(int *)(p + 0x2290) = *(int *)(p + 0xC18);
    func_L00_00322EC8(p + 0x18E0);
    func_L00_00322EC8(p + 0x1A30);
    current = *(char **)(p + 0x2290);
    *(int *)(current + 0x9C) = -1;
    if (mode != 4 || (unsigned char)p[0x22B4] != mode)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    {
        char *q = (char *)D_00189E20_1;

        q[0x22B4] = (char)mode;
        *(int *)(q + 0xC14) = (int)object;
        *(int *)(q + 0x2290) = (int)object;
        if ((unsigned char)mode == 1 && (D_00138320[0] & 0x10) != 0) {
            func_0028B3D0(0x23, 0, D_L00_002F8588,
                             D_L00_002F85D0, D_L00_002F8AD8, 0, 0);
            func_L00_002F6B90(3);
        }
        {
            char *r = (char *)D_00189E20_1;

            func_PAL_L00_002B3210();
            *(float *)(r + 0x250) = *(float *)(r + 0x258);
            *(float *)(r + 0x254) = *(float *)(r + 0x25C);
            *(unsigned short *)(*(char **)(r + 0x2290) + 0x34) |= 6;
            *(float *)(r + 0xC24) = *(float *)(r + 0xC20) = 1.0f;
            func_L00_002D24B8();
            func_002A677C(*(char **)(r + 0x2290));
            *(short *)(r + 0x24F2) = (short)value;
            if (mode == 1) {
                *(short *)(r + 0x24D4) = *(short *)(r + 0x24CC);
                count = *(int *)(r + 0x24D0);
                *(int *)(r + 0x24CC) = count;
                if (count >= 5)
                    *(int *)(r + 0x24CC) = 4;
            }
            func_PAL_L00_002C4480(value, 2);
        }
    }
}

