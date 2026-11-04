#include "include_asm.h"

extern void func_002A05A8(char *);

extern void func_002A7470(char *, int, int, int);

extern void func_002A7750(char *, int, int);

extern int func_002A77E0(int);

extern void func_002B9180(char *);

extern void func_00282A60(char *, int, int);

extern void func_0029F338(char *);

extern void func_0029F9F0(char *, char *);

extern void func_0029F978(char *, int, char *);

extern void *func_0029EFD0(int);

extern void func_002B0990(char *, char *, int, int, float);

extern void func_002AF1D0(char *, char *, int, int);

extern void func_L00_002E6EF8(void (*)(char *), char *);

extern void func_L02_003D5C20(char *);

extern void func_L02_003D5DF8(char *);

extern void func_L02_003D5F50(char *, int, int);

extern void func_L02_003D62F0(char *);

extern void func_L02_003D6348(char *);

extern void func_L02_003D6538(char *);

extern void func_L02_003D6388(char *, int, int);

extern void func_L02_003D6570(char *, int);

extern void func_L02_003DAE60(char *, int);

extern void func_L02_003DAF90(char *);

extern void func_L02_003DB030(char *);

extern void func_L02_003DB158(char *, int);

extern void func_002AB8C0(char *, char *);

extern void func_002A0488(char *, int, int, int);

extern void func_002A04B8(char *, int *, int *, int *);

extern void func_002A93B0(char *);

extern float func_00282E48(char *, char *);


extern void func_L00_003BAAD0(char *);

extern char D_L02_001BA500;

extern int D_L02_001B359C __attribute__((sda));

extern char *D_0018C2BC;

/* func_L02_003D26B0 is defined in L02_003D26B0-aim-g8.c. */

/* func_L02_003D2DE0 is defined in L02_003D2DE0-g16.c. */

/* func_L02_003D4308 is defined in L02_003D4308-g8.c. */

void func_L02_003D46B8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x95) == 2 ||
        *(unsigned char *)(arg0 + 0x20) == 0x12) {
        func_L02_003D5F50(arg0, 2, 0);
        func_L02_003D5F50(arg0, 3, 1);
    }
    func_L00_002E6EF8(func_L02_003D62F0, arg0);
    if (*(unsigned short *)(arg0 + 0x96) < 0xFFFF) {
        (*(unsigned short *)(arg0 + 0x96))++;
    }
    if (D_0018C2BC != 0 &&
        (D_0018C2BC == arg0 || *(short *)(D_0018C2BC + 0xAA) == 0x9F8)) {
        *(short *)(state + 0x32A) = -1;
    }
    *(unsigned short *)(state + 0x32A) = *(unsigned short *)(state + 0x32A) + 1;
    *(unsigned short *)(state + 0x32E) = *(unsigned short *)(state + 0x32E) + 1;
    func_002B0990(arg0, state + 0x340, 6, 1, 2.5f);
}

/* func_L02_003D47B0 is matched in L02_003D47B0-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

void func_L02_003D4900(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(int *)(state + 0x2A0) != 0) {
        func_L02_003D5C20(arg0);
    }
    func_002A7470(arg0, 0, 0, 3);
    func_002A05A8(arg0);
    func_002A7750(arg0, 1, 0);
    *(unsigned short *)(arg0 + 0x34) =
        (*(unsigned short *)(arg0 + 0x34) & 0xEFFF) | 3;
    *(int *)(arg0 + 0x98) = 0;
    *(unsigned char *)(arg0 + 0x31) = 0;
}

void func_L02_003D4980(char *arg0, int arg1) {
    *(int *)(*(char **)(arg0 + 0x68) + 0x310) = arg1;
}

/* Advances the actor's step counter until the float at +0x20 no longer lies below the share
   (3 - step) / 3 of the count at +0x24, then latches the done flag; once only. */
void func_L02_003D4990(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(short *)(state + 0x318) != 0)
        return;
    (*(short *)(state + 0x31A))++;
    while (*(float *)(state + 0x20) <
           (float)*(short *)(state + 0x24) * (3.0f - (float)*(short *)(state + 0x31A)) * 0.33333334f)
        (*(short *)(state + 0x31A))++;
    *(short *)(state + 0x318) = 1;
}

void func_L02_003D4A48(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(short *)(state + 0x318) != 0) {
        *(short *)(state + 0x318) = 0;
    }
}

int func_L02_003D4A60(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *holder = *(char **)(state + 0x310);
    unsigned char mode;
    int hit = 0;

    if (holder != 0) {
        mode = *(unsigned char *)(holder + 0x20);
        if (mode != 0xFE) {
            if (mode != 0xFD) {
                if (mode >= 3) {
                    if (*(float *)(state + 0x20) <
                        (float)*(short *)(state + 0x24) *
                            (3.0f - (float)*(short *)(state + 0x31A)) * 0.33333334f) {
                        hit = 1;
                    }
                }
            }
        }
    }
    return hit;
}

int func_L02_003D4D00(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    short timer = *(short *)(state + 0x32E);
    int delta;

    if (timer < 0x12C) {
        return 0;
    }
    if (timer < 0x1F5) {
        delta = 0x1F4 - *(short *)(state + 0x32A);
        if (delta > 0) {
            if (func_002A77E0(delta) != 0) {
                return 0;
            }
        }
    }
    *(short *)(state + 0x32A) = 0;
    *(short *)(state + 0x32E) = 0;
    return 1;
}

/* func_L02_003D4E00 is matched in L02_003D4E00-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003D4ED0 is matched in L02_003D4ED0.c (built with -frac2-qcopy). */

typedef int TI128 __attribute__((mode(TI)));

extern void func_321E78(char *, char *, float, float, float, float);

extern void func_322330(char *, char *, float, float, float, float, int);

extern void func_327620(char *, char *, char *, float, float, float);

void func_L02_003D4FD0(char *arg0, TI128 *arg1, float arg2, float arg3) {
    char *state = *(char **)(arg0 + 0x68);
    TI128 vec = *arg1;
    float *v = (float *)&vec;

    func_321E78(arg0 + 0x10, state + 0x1B0, v[0], 0.025f, 0.025f, 1.5000001f);
    func_321E78(arg0 + 0x14, state + 0x1B4, v[1], 0.025f, 0.025f, 1.5000001f);
    func_321E78(arg0 + 0x18, state + 0x1B8, v[2], 0.025f, 0.025f, 1.5000001f);
    func_322330(arg0 + 0xF8, state + 0x1C4, arg2, 0.003490659f, 0.003490659f,
                0.22107507f, 0);
    func_322330(arg0 + 0xF4, state + 0x2F0, arg3, *(float *)(state + 0x124),
                *(float *)(state + 0x128), *(float *)(state + 0x12C), 0);
    func_327620(arg0, state + 0x2F4, state + 0x304, 0.5f, 0.087266475f, -1.0f);
}

/* func_L02_003D5118 is matched in L02_003D5118.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

void func_L02_003D5570(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char **slots = (char **)(state + 0x2A0);
    int i;

    func_00282A60(state + 0x260, 0, 0x40);
    func_0029F978(arg0, 1, state + 0x260);
    func_00282A60(state + 0x220, 0, 0x40);
    func_0029F978(arg0, 0, state + 0x220);
    for (i = 0; i < 5; i++) {
        char *node = func_0029EFD0(i + 0xA19);

        *slots = node;
        if (node != 0) {
            *(unsigned char *)(*slots + 0x30) = 0;
            *(unsigned short *)(*slots + 0x32) = *(unsigned short *)(arg0 + 0x32);
            *(unsigned long long *)(*slots + 0x38) =
                *(unsigned long long *)(arg0 + 0x38);
            *(unsigned short *)(*slots + 0x34) |= 1;
            *(unsigned char *)(*slots + 0x31) = 0;
        }
        slots++;
    }
}

void func_L02_003D5660(char *arg0, int arg1) {
    char *state = *(char **)(arg0 + 0x68);
    char **slots;
    int i;

    if (arg1 == 1) {
        *(unsigned char *)(state + 0x262) = arg1;
        *(float *)(state + 0x288) = 0.0001f;
        *(float *)(state + 0x284) = 0.0001f;
        *(float *)(state + 0x280) = 0.0001f;
    } else {
        *(unsigned char *)(state + 0x222) = 1;
        *(float *)(state + 0x248) = 0.0001f;
        *(float *)(state + 0x244) = 0.0001f;
        *(float *)(state + 0x240) = 0.0001f;
    }
    *(short *)(state + 0x320) = 0;
    {
        unsigned char one = 1;

        slots = (char **)(state + 0x2A0);
        for (i = 4; i >= 0; i--) {
            if (slots[0] != 0) {
                *(unsigned short *)(slots[0] + 0x34) =
                    *(unsigned short *)(slots[0] + 0x34) & 0xFFFE;
                *(unsigned char *)(slots[0] + 0x31) = one;
                func_002AF1D0(arg0, slots[0], arg1, 0);
            }
            slots++;
        }
    }
    *(short *)(state + 0x31E) = 0;
}

/* func_L02_003D5748 is defined in L02_003D5748-g8-dbg.c. */

void func_L02_003D5B90(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *holder = *(char **)(state + 0x300);
    char **slots;
    char *node;
    int i;

    if (holder != 0) {
        func_L02_003D5DF8(holder);
        *(int *)(state + 0x300) = 0;
    }
    *(unsigned char *)(state + 0x222) = 0;
    *(float *)(state + 0x248) = 1.0f;
    *(float *)(state + 0x244) = 1.0f;
    *(float *)(state + 0x240) = 1.0f;
    *(float *)(state + 0x288) = 1.0f;
    *(float *)(state + 0x284) = 1.0f;
    *(float *)(state + 0x280) = 1.0f;
    *(unsigned char *)(state + 0x262) = 0;
    slots = (char **)(state + 0x2A0);
    for (i = 4; i >= 0; i--) {
        node = slots[0];
        if (node != 0) {
            *(unsigned short *)(node + 0x34) = *(unsigned short *)(node + 0x34) | 1;
            *(unsigned char *)(slots[0] + 0x31) = 0;
        }
        slots++;
    }
}

void func_L02_003D5C20(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *holder = *(char **)(state + 0x300);
    char **slots;
    char *s4;
    int i;

    if (holder != 0) {
        func_L02_003D5DF8(holder);
        *(int *)(state + 0x300) = 0;
    }
    s4 = state + 0x220;
    slots = (char **)(state + 0x2A0);
    for (i = 4; i >= 0; i--) {
        if (slots[0] != 0) {
            func_0029F338(slots[0]);
            slots[0] = 0;
        }
        slots++;
    }
    if (*(unsigned char *)(state + 0x261) != 0) {
        func_0029F9F0(arg0, state + 0x260);
    }
    if (*(unsigned char *)(state + 0x221) != 0) {
        func_0029F9F0(arg0, s4);
    }
    func_00282A60(s4, 0, 0x40);
    func_00282A60(s4, 0, 0x40);
}

/* func_L02_003D5CF0 is matched in L02_003D5CF0.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

extern void func_3366A8(char *);

void func_L02_003D5DF8(char *arg0) {
    char *cur;

    while (arg0 != 0) {
        cur = arg0;
        arg0 = *(char **)(arg0 + 0x34);
        func_3366A8(cur);
    }
}

/* func_L02_003D5E40 is matched in L02_003D5E40-g8.c. */

/* func_L02_003D5F50 is defined in L02_003D26B0-g8.c. */

void func_L02_003D62F0(char *arg0) {
    char *state = arg0;
    unsigned char mode;

    func_L02_003D6538(state);
    mode = *(unsigned char *)(state + 0x95);
    if (mode == 2) {
        func_L02_003D6348(state);
    }
    mode = *(unsigned char *)(state + 0x42);
    if (mode == 2) {
        func_L02_003D6A20(state);
    }
}

void func_L02_003D6348(char *arg0) {
    func_L02_003D6388(arg0, 2, 0);
    func_L02_003D6388(arg0, 3, 1);
}

/* func_L02_003D6388 is matched in L02_003D6388-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

void func_L02_003D6538(char *arg0) {
    func_L02_003D6570(arg0, 4);
    func_L02_003D6570(arg0, 5);
}

/* func_L02_003D6570 is matched in L02_003D6570-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003D6690 is defined in L02_003D6690-helpers-g8.c. */

/* func_L02_003D6A20 is matched in L02_003D6A20-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier -g). */

/* Whether the object's variant byte is one of the later ones. */
int func_L02_003D6BB0(char *arg0) {
    return *(unsigned char *)(arg0 + 0x20) >= 3;
}

/* func_L02_003D7330 is defined in L02_003D7330-g8.c. */

extern void func_00283098(void *, void *, void *);

extern void func_00282CC0(void *, void *, void *);

extern float func_00283248(float, float);

extern int func_00283CF0(float);

extern void func_L02_003D2248(char *, int);

extern void func_L02_003F17B0(char *, int);

extern void func_L02_0040B868(char *, int);

extern void func_L02_0040D080(char *, int);

typedef struct {
    char pad0[0x80];
    float x;
    float y;
} L02_003D7900_Hero;

extern L02_003D7900_Hero D_00189E20;

/* Builds a four-float vector and hands it to the two vector helpers, tints the three colour
   records of the actor's state from it, then walks the three actors the state points at:
   each gets the angle to the hero written at 0xF8 and the behaviour its type selects. */
void func_L02_003D7900(char *arg0) {
    float v[4];
    char *state = *(char **)(arg0 + 0x68);
    char *obj;
    int i;
    int count;

    v[0] = 0.0f;
    v[1] = -9.0f;
    v[2] = -3.3f;
    v[3] = 0.0f;
    func_00283098(v, v, arg0 + 0xC0);
    func_00282CC0(v, v, arg0 + 0x10);
    if (*(char **)(state + 0x10) != 0) {
        *(float *)(*(char **)(state + 0x10) + 0x10) = v[0] - 2.0f;
        *(float *)(*(char **)(state + 0x10) + 0x14) = v[1];
        *(float *)(*(char **)(state + 0x10) + 0x18) = v[2];
        *(float *)(*(char **)(state + 0x10) + 0x1C) = v[3];
    }
    if (*(char **)(state + 0x14) != 0) {
        *(float *)(*(char **)(state + 0x14) + 0x10) = v[0];
        *(float *)(*(char **)(state + 0x14) + 0x14) = v[1] + 1.0f;
        *(float *)(*(char **)(state + 0x14) + 0x18) = v[2];
        *(float *)(*(char **)(state + 0x14) + 0x1C) = v[3];
    }
    if (*(char **)(state + 0x18) != 0) {
        *(float *)(*(char **)(state + 0x18) + 0x10) = v[0];
        *(float *)(*(char **)(state + 0x18) + 0x14) = v[1] - 1.0f;
        *(float *)(*(char **)(state + 0x18) + 0x18) = v[2];
        *(float *)(*(char **)(state + 0x18) + 0x1C) = v[3];
    }
    obj = *(char **)(state + 0x10);
    for (count = 0, i = 0; i < 3; i++) {
        L02_003D7900_Hero *hero = &D_00189E20;

        if (i == 1) {
            obj = *(char **)(state + 0x14);
        }
        if (i == 2) {
            obj = *(char **)(state + 0x18);
        }
        if (obj == 0) {
            continue;
        }
        *(int *)(obj + 0xF0) = 0;
        *(int *)(obj + 0xF4) = 0;
        *(float *)(obj + 0xF8) =
            func_00283248(hero->x - *(float *)(obj + 0x10),
                          hero->y - *(float *)(obj + 0x14));
        *(int *)(obj + 0xFC) = 0;
        switch (*(short *)(obj + 0xAA)) {
        case 0x9CA:
            func_L02_003D2248(obj, 0);
            break;
        case 0xB22:
            func_L02_003F17B0(obj, 0);
            break;
        case 0xC3B:
            func_L02_0040B868(obj, 0);
            break;
        case 0xC3E:
            *(float *)(obj + 0x18) = *(float *)(obj + 0x18) + 0.5f;
            func_L02_0040D080(obj, func_00283CF0((float)count * 0.16666667f));
            break;
        }
    }
    *(int *)(state + 0x10) = 0;
    *(int *)(state + 0x14) = 0;
    *(int *)(state + 0x18) = 0;
}

/* func_L02_003D91A0 is defined in L02_003D91A0.c. */

void func_L02_003D9608(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    int a, b, c;

    func_002AB8C0(arg0, state + 0x140);
    if (*(short *)(state + 0x140) == 0) {
        if (*(short *)(state + 0x27E) == 0) {
            func_002A0488(arg0, *(int *)(state + 0x270),
                          *(int *)(state + 0x274), *(int *)(state + 0x278));
            *(short *)(state + 0x27E) = 1;
        }
    } else {
        *(short *)(state + 0x27E) = 0;
    }
    func_002A04B8(arg0, &a, &b, &c);
    func_002A0488(
        (char *)(D_L02_001B359C +
                 (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)),
        a, b, c);
    func_L00_002E6EF8(func_L00_003BAAD0, arg0);
    if (*(unsigned char *)(arg0 + 0x31) != 0) {
        if (func_00282E48(arg0 + 0x10, &D_L02_001BA500) < 64.0f) {
            func_002A93B0(arg0);
            *(unsigned char *)(arg0 + 0x6F) = 0x3C;
        }
    }
    *(float *)(arg0 + 0x74) = 1.0f;
    if (*(unsigned short *)(arg0 + 0x96) <= 0xFFFE) {
        *(unsigned short *)(arg0 + 0x96) += 1;
    }
}


extern void *func_0029FCC0(char *, int, void *);

extern void func_L00_0031BDC0(void *, void *, void *, char *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282D30(void *, void *, float);

extern void func_002A8C00(void *, char *, int, void *, float);

extern int func_00277F48(float, void *, int, char *, void *);

typedef struct {
    char pad0[0x18];
    unsigned char b18;
    unsigned char b19;
    unsigned short h1a;
    char pad1c[0x14];
} L02_003DAB68_Rec;

/* Runs only while the state's target pointer (+0x240) is set.  The word at +0x98 of the object
   table entry the state selects (+0x244) is zeroed for the duration and put back at the end.
   Four rounds, for the joint pairs (1, 2), (3, 4), (5, 6) and (7, 8): the two joint positions
   (func_0029FCC0), func_L00_0031BDC0 on them and the target's position, the offset from the
   actor's position to its result, a vector made of the offset's first two floats turned a
   quarter turn, scaled by func_00282D30 (2.0) and completed with 1.0 and 5627.925, an effect
   record started from it (func_002A8C00), and two func_00277F48 calls on that record (0.65 and
   0.95). */
void func_L02_003DAB68(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    float v0[4];
    float v1[4];
    float hit[4];
    float diff[4];
    float perp[4];
    L02_003DAB68_Rec rec;
    char *obj;
    int saved;
    char *pos;
    float *offset;
    int i;
    int a;
    int b;
    float one;

    if (*(int *)(state + 0x240) != 0) {
        obj = (char *)((*(int *)(state + 0x244) << 8) + D_L02_001B359C);
        one = 1.0f;
        saved = *(int *)(obj + 0x98);
        *(int *)(obj + 0x98) = 0;
        offset = diff;
        pos = arg0 + 0x10;
        for (i = 0; i < 4; i++) {
            a = i * 2 + 1;
            b = i * 2 + 2;
            func_0029FCC0(arg0, a, v0);
            func_0029FCC0(arg0, b, v1);
            func_L00_0031BDC0(hit, v0, v1, *(char **)(state + 0x240) + 0x10);
            func_00282CF0(offset, hit, pos);
            perp[0] = -diff[1];
            perp[1] = diff[0];
            perp[2] = 0.0f;
            func_00282D30(perp, perp, 2.0f);
            perp[2] = one;
            perp[3] = 5627.925f;
            func_002A8C00(&rec, arg0, 0x10001, perp, (float)*(unsigned char *)(state + 0x35));
            rec.b18 = 0;
            rec.b19 = 1;
            rec.h1a = *(unsigned short *)(arg0 + 0xAA);
            func_00277F48(0.65f, hit, 0, arg0, &rec);
            func_00277F48(0.95f, v1, 0, arg0, &rec);
        }
        *(int *)((*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8) + D_L02_001B359C + 0x98) = saved;
    }
}

void func_L02_003DAD88(char *arg0) {
    func_L02_003DAE60(
        (char *)(D_L02_001B359C +
                 (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)), 0);
    func_L02_003DAE60(
        (char *)(D_L02_001B359C +
                 (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)), 1);
    func_L02_003DB158(
        (char *)(D_L02_001B359C +
                 (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)), 5);
    func_L02_003DB158(
        (char *)(D_L02_001B359C +
                 (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)), 6);
    func_L02_003DAF90(
        (char *)(D_L02_001B359C +
                 (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)));
    func_L02_003DB030(
        (char *)(D_L02_001B359C +
                 (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)));
}

/* func_L02_003DAE60 is matched in L02_003DAE60-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003DAF90 uses its dedicated G16 vector unit. */



/* func_L02_003DB030 is matched in L02_003DB030-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_003DB158 is matched in L02_003DB158-g8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */



/* func_L02_003DB200 is matched in L02_003DB200-g8.c (built with -frac2-zero-ti-por). */

void func_L02_003DB2F0(char *arg0) {
    func_002A7750(arg0, 7, -1);
}
