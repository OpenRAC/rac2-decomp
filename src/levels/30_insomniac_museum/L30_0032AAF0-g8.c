#include "common.h"

/* Small-data unit: every body here reaches a global through $gp, so the file is built
   with -G8 (the -g8.c name gives it that profile). */

extern float D_L30_001AEE90 __attribute__((sda));
extern float D_L30_001AEE94 __attribute__((sda));
extern char D_L30_001AEE98[];

extern void func_0026FEB8(const char *, ...);
extern void func_001163A0(unsigned int);
extern int func_002A77E0(int);
extern void func_002A7750(u8 *, int, int);
extern void func_002AEE70(u8 *, u8 *, u8 *, float, float, float);
extern float func_00283B98(float, float);

/* Steps one record: with the state byte clear it copies the record's own angle into the
   state block, and once the state index reaches thirteen it redraws the record with a fresh
   random duration, a timer sample and the state block's new bit mask. With the state byte
   set it folds the shared angle words into the record and the state block instead, and
   counts the frame in the record's halfword at 0x96. */
void func_L30_00386300(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 v;

    if (*(u8 *)(object + 0x20) == 0) {
        float f = *(float *)(object + 0x18);
        unsigned int w = *(unsigned int *)state;

        *(float *)(state + 0xC) = f;
        if (w >= 13) {
            short a1 = *(short *)(object + 0xAA);
            short a2 = *(short *)(object + 0xB2);
            unsigned int ticks = *(volatile unsigned int *)0x10000800;

            func_0026FEB8(D_L30_001AEE98, a1, a2);
            func_001163A0(ticks);
            *(int *)state = func_002A77E0(13);
        }
        *(u16 *)(object + 0x7C) = 1 << *(int *)state;
        func_002A7750(object, 1, -1);
    } else {
        float f0 = D_L30_001AEE94;

        func_002AEE70(object, state + 4, state + 8, D_L30_001AEE90,
                      f0 * 0.000290888245f, *(float *)(state + 0xC));
        *(float *)(object + 0xF8) =
            func_00283B98(*(float *)(object + 0xF8), 0.01745329424738884f);
        *(u16 *)(object + 0x96) = 0;
    }
    v = *(u16 *)(object + 0x96);
    *(u16 *)(object + 0x96) = v + 1;
}

typedef struct {
    unsigned char pad[0x1A0];
    unsigned int f1A0;
    unsigned int f1A4;
} D00138180_Flags;

extern D00138180_Flags D_00138180;
extern float D_001B35B8;
extern int D_001A79F0;
extern float D_L30_001AEC24 __attribute__((sda));
extern float D_L30_001AEC2C __attribute__((sda));
extern float D_L30_001AEC28 __attribute__((sda));
extern float D_L30_001AEC20 __attribute__((sda));
extern int D_L30_001AEC18 __attribute__((sda));
extern int D_L30_001AEC10 __attribute__((sda));
extern int D_L30_001AEC1C __attribute__((sda));
extern int D_L30_001AEC14 __attribute__((sda));
extern int D_L30_001AEC08 __attribute__((sda));
extern float D_L30_001AEC0C __attribute__((sda));
extern int D_L30_001AEBB8 __attribute__((sda));
extern float D_00233A60[][24][24];

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L30_00382F10(void);
extern void func_L30_003830D8(void);
extern float func_L30_00382EF0(float, float, float);
extern void func_L30_003831E8(int, int, float, float);
extern void func_L30_00383928(void *);

void func_L30_003840E0(char *object) {
    int state = *(unsigned char *)(object + 0x20);

    switch (state) {
    case 0:
        *(unsigned char *)(object + 0x20) = 1;
        *(float *)(object + 0x18) += D_001B35B8;
        func_L30_00382F10();
        *(unsigned char *)(object + 0x30) = 0xFF;
        break;
    case 1:
        if (!(D_00138180.f1A0 & 0x80))
            func_L30_003830D8();
        if (D_L30_001AEC24 >= D_L30_001AEC2C && func_002A77E0(200) == 1) {
            D_L30_001AEC24 = 0.0f;
            D_L30_001AEC18 += D_L30_001AEC10;
            D_L30_001AEC1C += D_L30_001AEC14;
            if (D_L30_001AEC18 < 4 || D_L30_001AEC18 > 20)
                D_L30_001AEC10 = -D_L30_001AEC10;
            if (D_L30_001AEC1C < 4 || D_L30_001AEC1C > 20)
                D_L30_001AEC14 = -D_L30_001AEC14;
            D_00233A60[D_L30_001AEBB8][D_L30_001AEC18][D_L30_001AEC1C] = D_L30_001AEC20;
        } else {
            func_00283CF0(func_L30_00382EF0(func_00283CE0(D_L30_001AEC18),
                                            func_00283CE0(D_L30_001AEC18 + D_L30_001AEC10),
                                            D_L30_001AEC24));
            func_00283CF0(func_L30_00382EF0(func_00283CE0(D_L30_001AEC1C),
                                            func_00283CE0(D_L30_001AEC1C + D_L30_001AEC14),
                                            D_L30_001AEC24));
        }
        D_L30_001AEC24 += D_L30_001AEC28;
        if (D_00138180.f1A0 & 0x20)
            func_L30_003831E8(12, 12, D_L30_001AEC08, D_L30_001AEC0C);
        func_L00_002E6CF0(func_L30_00383928, object);
        break;
    }
}

extern char D_00189E20[];
extern char *D_001B2D1C __attribute__((sda));
extern void func_002A7470(void *, int, int, int);
extern void func_L00_0042A500(int);
extern void func_002B0C28(int, int, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L30_003BE678(char *);

void func_L30_003BE478(char *object) {
    char *g;
    char *state = *(char **)(object + 0x68);
    int id;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (*(int *)(state + 4) != 0) {
            *(unsigned char *)(object + 0x20) = 1;
            if (*(unsigned char *)(object + 0x43) != 0)
                func_002A7470(object, 0, 0, 5);
        } else {
            *(unsigned char *)(object + 0x20) = 3;
            if (*(unsigned char *)(object + 0x43) != 2)
                func_002A7470(object, 2, 0, 5);
        }
        break;
    case 1:
        break;
    case 2:
        if (*(unsigned char *)(object + 0x60) & 2) {
            *(unsigned char *)(object + 0x20) = 5;
            if (*(unsigned char *)(object + 0x43) != 2)
                func_002A7470(object, 2, 0, 5);
            if (*(int *)(state + 0xC) != -1)
                func_L00_0042A500(*(int *)(state + 0xC));
        }
        break;
    case 3:
        id = -1;
        if (D_001A79F0 != 0x15 && D_001A79F0 != 0x1E) {
            switch (*(int *)(state + 8)) {
            case 0:
                id = 0x279C;
                break;
            case 1:
                id = 0x279D;
                break;
            }
        } else {
            id = 0x27ED;
        }
        g = D_00189E20;
        if (*(char **)(g + 0x33C) == object && *(int *)(g + 0x340) != 0) {
            func_002B0C28(8, id, 1);
            if (D_00138180.f1A4 & 0x10) {
                char *s0 = D_001B2D1C + (*(int *)state << 8);

                func_L30_003BE678(s0);
                func_L00_002B9D60(s0 + 0x10, s0 + 0xF0, 0x6F, 1);
                *(unsigned char *)(g + 0x22B5) = 1;
            }
        }
        break;
    case 4:
        break;
    case 5: {
        char *h = D_00189E20;

        if (*(int *)(h + 0x2294) == 0x6F) {
            *(unsigned char *)(h + 0x22B5) = 0;
            func_L00_002B9D60(h + 0x80, h + 0x90, 0, 0);
        }
        *(unsigned char *)(object + 0x20) = 3;
        break;
    }
    }
}
