/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * GPT-6.1 Sol high tier, task v0932; pinned upstream compiler.
 * Best check.py: 948/948 bytes, 0/27 places. No linked match.
 * Profile: -O2 -G0 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier -frac2-zero-ti-por.
 * Integer-index traversal restores the retail loop. Shared hero storage at +0x2BC, the transition block at D_00152C00 +0x70 and boolean normalization restore the remaining control flow and final vector-transfer block. Five register differences remain in the key/table setup (0036040C/410/428/434/438). Local key pointer and direct indexed-access wordings tie byte-for-byte; stop after the three-form allocation tie.
 * Required declarations are included below.
 */

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef void (*DrawCallback)(void *);
extern int D_L00_001A8F00 __attribute__((sda));
extern char *D_L00_00220DA0[];
extern short D_L00_001A8F80[2];
extern unsigned int D_001A7AF0 __attribute__((sda));
extern Vector D_L00_001B8DC0;
extern char D_00189EA0[];

extern unsigned int D_00138324;
extern char D_00152C00[];
extern int D_L00_001B1AE0 __attribute__((sda));
extern void func_002E64A0(void *);
extern void func_L00_002E6EF8(DrawCallback, void *);
extern void func_L00_002E6CF0(DrawCallback, void *);
extern void func_002ECB70(void *);
extern void func_002E6B78(void *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283CE0(int);
extern float func_00283180(float);
extern int func_002B0C28(int, int, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A89A8(void *, int, float);
extern float func_00283B98(float, float);
extern int func_L00_003268E8(int);

void func_L00_003603C0(unsigned char *object) {
    Vector position;
    Vector offset;
    Vector angles;
    unsigned char *private = *(unsigned char **)(object + 0x68);
    char **slot;
    int index;
    short key;
    char *spawn;
    char *vehicle;
    float distance;
    unsigned int shade;
    int active_vehicle;
    int available;
    if (!D_L00_001A8F00) func_002E64A0(object);
    if ((unsigned char)object[0x31]) {
        private[0xE] = (unsigned char)private[0xE] + 2;
        key = D_L00_001A8F80[(D_001A7AF0 >> 4) & 1];
        for (index = 0; D_L00_00220DA0[index]; index++) {
            slot = D_L00_00220DA0 + index;
            if (*(short *)(D_L00_00220DA0[index] + 0xAA) == key) {
                shade = (int)(func_00283180(func_00283CE0((unsigned char)private[0xE] - 128) * 0.024543693f) * 50.0f) + 140;
                *(unsigned int *)(*slot + 0x78) = shade | (shade << 8) | (shade << 16);
                *(unsigned short *)(*slot + 0x34) |= 0x10;
                break;
            }
        }
        func_L00_002E6EF8(func_002ECB70, object);
        if (func_00282E80(object + 0x10, &D_L00_001B8DC0) < 32.0f)
            func_L00_002E6CF0(func_002E6B78, object);
    }
    if (*(short *)(private + 0xC) != 0) {
        if (func_00282E48(object + 0x10, &D_00189EA0) > 6.1f && !((*(unsigned char **)(D_00189EA0 + 0x2BC)) && *(short *)((*(unsigned char **)(D_00189EA0 + 0x2BC)) + 0xAA) == 0xD54 && (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 254 && (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 253))
            *(short *)(private + 0xC) = 0;
    } else {
        if (func_00282E80(object + 0x10, &D_00189EA0) < 8.0f || ((*(unsigned char **)(D_00189EA0 + 0x2BC)) && *(short *)((*(unsigned char **)(D_00189EA0 + 0x2BC)) + 0xAA) == 0xD54 && (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 254 && (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 253)) {
            if (func_00282E48(object + 0x10, &D_00189EA0) < 6.0f || ((*(unsigned char **)(D_00189EA0 + 0x2BC)) && *(short *)((*(unsigned char **)(D_00189EA0 + 0x2BC)) + 0xAA) == 0xD54 && (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 254 && (unsigned char)(*(unsigned char **)(D_00189EA0 + 0x2BC))[0x20] != 253))
                *(short *)(private + 0xC) = 1;
        }
    }
    if (*(unsigned short *)(object + 0x34) & 1) *(short *)(private + 0xC) = 0;
    if (*(short *)(private + 0xC)) {
        available = func_002B0C28(2, 0x2798, 1) != 0;
        if ((D_00138324 & 0x10) && available) {
            offset.q = 0;
            angles.q = 0;
            offset.f[0] = 1.48f;
            offset.f[1] = 2.64f;
            angles.f[0] = -0.021118486f;
            angles.f[1] = 0.0588176f;
            angles.f[2] = 1.2252212f;
            func_00283098(&position, &offset, object + 0xC0);
            func_00282CC0(&position, &position, object + 0x10);
            position.f[2] = func_002A89A8(&position, 0, 0.5f);
            angles.f[2] = func_00283B98(angles.f[2], *(float *)(object + 0xF8));
            spawn = D_00152C00 + 0x70;
            *(Quad *)spawn = position.q;
            *(Quad *)(spawn + 0x10) = angles.q;
            func_L00_003268E8(2);
            *(short *)(spawn - 0x4A) = 0;
            D_L00_001B1AE0 = 1;
        }
    }
}
