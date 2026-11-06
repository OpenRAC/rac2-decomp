/* func_US2_L30_00418D30, the USA v2.00 copy of func_L30_004186B0: the same C. */
extern char *func_L30_00413490(void *);
extern void func_L30_00413528(void *, void *, void *, int, int, int);
extern char D_00189EA0[];
extern long D_00138320;
extern int func_002A7820(int, int);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern int func_002B0CE0(int, int, int);
extern int func_002B3868(void *);
extern unsigned char *func_002C65A0(void *, void *, int, int, int, int, int, float, float, float, int);
extern unsigned char *D_L30_001FF940[];
extern char D_L30_001B2110[];
extern char D_L30_001B2120[];
extern char D_L30_001B2130[];
extern char D_L30_001B2140[];
extern char D_L30_001B2150[];
extern char D_L30_001B2158[];
extern char D_L30_001B2160[];
extern char D_L30_001B2168[];
extern char D_L30_001B2178[];
extern char D_L30_001B2188[];
extern char D_L30_001B2198[];
extern char D_L30_001B21A8[];
extern char D_L30_001B21B8[];
extern char D_L30_001B21C0[];
extern char D_L30_001B21D0[];
extern char D_L30_001B21E0[];
extern char D_L30_001B21F0[];
typedef struct { char pad[0x4c]; short minimum, maximum; } MuseumParticleBounds;

/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */

/* func_L30_004153D8 is defined in L30_004153D8.c. */

/* func_L30_004158B0 is defined in L30_004158B0-g8.c. */

/* func_L30_00416A88 is defined in L30_00416A88-g8.c. */

/* func_L30_00416D88 is defined in L30_00416D88-g8.c. */

/* func_L30_00417988 is defined in L30_00417988-g8.c. */

typedef unsigned short u16;

void func_US2_L30_00418D30(char *obj) {
    char *st = *(char **)(obj + 0x68);
    MuseumParticleBounds *bounds = (MuseumParticleBounds *)st;
    unsigned char *particle;

    switch ((unsigned char)obj[0x20]) {
    case 0:
        if (bounds->maximum < 0) bounds->maximum = 0;
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(st + 0xC) = func_002A7820(bounds->minimum, bounds->maximum);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(st + 0x48) != -1 && func_002ACBC8(D_00189EA0, *(int *)(st + 0x48))) {
            func_002B0CE0(1, 0x1338, 1);
            if ((D_00138320 & 3) == 3) func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(obj)) {
            *(char **)(st + 0x3C) = func_L30_00413490(obj);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x00, D_L30_001B2110, 1, -1000, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x04, D_L30_001B2120, 1, -1000, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x08, D_L30_001B2130, 1, -1000, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x10, D_L30_001B2140, 0, 1, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x14, D_L30_001B2150, 0, 0, 255);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x18, D_L30_001B2158, 0, 0, 255);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x1C, D_L30_001B2160, 0, 0, 255);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x20, D_L30_001B2168, 0, -1000, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x24, D_L30_001B2178, 0, 0, 127);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x28, D_L30_001B2188, 0, 0, 127);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x2C, D_L30_001B2198, 1, 0, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x30, D_L30_001B21A8, 1, 0, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x34, D_L30_001B21B8, 1, -1000, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x40, D_L30_001B21C0, 0, 0, 103);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x44, D_L30_001B21D0, 0, 0, 20);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x4C, D_L30_001B21E0, 3, 0, 1000);
            func_L30_00413528(*(char **)(st + 0x3C), st + 0x4E, D_L30_001B21F0, 3, 0, 1000);
        }
        func_002B0CE0(1, 0, 1);
        if (*(char **)(st + 0x3C) == 0
            || *(short *)(*(char **)(st + 0x3C) + 0xAA) != 0x118A
            || (unsigned char)(*(char **)(st + 0x3C))[0x20] == 0xFE
            || (unsigned char)(*(char **)(st + 0x3C))[0x20] == 0xFD) {
            func_002A7750(obj, 1, -1);
        }
        break;
    }

    if ((*(float *)(st + 0xC))-- == 0.0f) {
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(st + 0xC) = func_002A7820(bounds->minimum, bounds->maximum);
        particle = func_002C65A0(obj + 0x10, st, *(int *)(st + 0x10),
                                 (*(int *)(st + 0x1C) << 16) | (*(int *)(st + 0x18) << 8) | *(int *)(st + 0x14),
                                 *(int *)(st + 0x20), *(int *)(st + 0x24), *(int *)(st + 0x28),
                                 *(float *)(st + 0x2C) * 210000.0f, *(float *)(st + 0x30) * 210000.0f,
                                 *(float *)(st + 0x34), *(int *)(st + 0x38));
        if (particle) {
            particle[9] = 0xFF;
            particle[2] = D_L30_001FF940[*(int *)(st + 0x40)][*(int *)(st + 0x44)];
        }
    }
}

/* func_L30_0041B848 is defined in L30_0041B848.c. */
