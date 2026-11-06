#include "include_asm.h"
#include "common.h"

extern short *D_L06_001FB3A0[];
extern char *D_L06_001B281C[] __attribute__((sda));
extern float func_35A780(void);
extern void func_458138(char *);

extern int func_00282948(char *);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_002AB8C0(char *, char *);
extern int func_002A7820(int, int);
/* EE argument banks preserve position/count/velocity/color/flags and four floats. */
extern char *func_002BDCE8(char *, float, float, float, int, char *, float, unsigned int, int);

extern char D_L06_002AA500[];

extern void func_32D268(char *);
extern void func_366160(char *, char *, float, int, int);
extern void func_36C158();
extern void func_36C1B0(float);
extern void func_3BFBB8(char *, int);

extern char D_L06_00189EA0[];
extern char D_L06_001B13B0[];
extern char D_L06_001B13F0[];
extern char D_L06_001B1330[];
extern char D_L06_001B1370[];
extern char D_L06_001395CE;
extern char D_L06_001395CF;
extern char D_L06_001395D0;

/* The two flags the re-arm sets, at 0x001395B8. */
typedef struct {
    char pad_000[0x13];
    char flag_013;
    char flag_014;
} L06ArmFlags;

extern L06ArmFlags D_L06_001395B8;

extern int func_333898(void);
extern void func_2E3EF0(char *);
extern int func_360F58(char *, int);
extern void func_35A550(char *, int, int);
extern void func_35B810(int, int);
extern int func_35CBA0(char *, int, int);
extern int func_3A0948(int, int, char *);
extern void func_3661E0(char *, int, float);
extern void func_350388(char *);
extern void func_32D650(char *, char *, float);
extern void func_L06_00457C00(char *, int, void *, int, float, float, float, float);
extern void func_32D5F8(char *, char *, char *);
extern void func_365030(char *, char *, char *, int);
extern float func_32DC80(float, float);
extern float func_32D740(char *);
extern void func_32D5C8(char *, char *, char *);
extern int func_32E728(float);
extern void func_352000(char *, int, int, int);
extern void func_32D8A8(char *, char *, float);
extern void func_00310C88();
extern int D_L06_001B375C __attribute__((sda));
extern int D_L06_001B3758 __attribute__((sda));
extern void func_L06_003DDCA8();
extern int func_32D238(char *);
extern int func_35A620(int);
extern void func_35A270(char *, int, int, int);
extern void *D_L06_002E1F00[];
extern char *func_31B0D0(char *, int, int, int, float, float, char *, char *, char *,
                         int);
extern char D_L06_001A8F20[];
extern void func_L06_004579C8(char *);

extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DF0(float *);
extern void func_00282F20(float *, float *, float);
extern int func_002A7EA0(char *, char *, char *, int, float, float, float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_002AA548(float *, char *, float, float, float, float);
extern void func_002AAA00(char *, float, float, float, float, char *, int);
extern float func_00283C80(float, float);
extern int func_L02_0032E998(char *, int, float *, char *, int, char *, char *, float,
                             float);


void func_L06_0041FAF8(char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    if (*(int *)(o + 0x5A0) == 1) {
        if (*(int *)(o + 0x23C) == -1) {
            if (func_32D238(o + 0x25C)) {
                func_35A550(a0, 7, 2);
                if (*(unsigned char *)(a0 + 0x43) != 0x13) {
                    func_35A270(a0, 0x13, 0, 20);
                }
                o[0x48] = func_32E728(20.0f);
                o[0x4A] = func_32E728(24.0f);
            }
        } else {
            func_35A550(a0, 8, 2);
            if (*(unsigned char *)(a0 + 0x43) != 0x12) {
                func_35A270(a0, 0x12, 0, 20);
            }
            o[0x48] = func_32E728(20.0f);
            o[0x4A] = func_32E728(24.0f);
        }
    } else if (*(short *)(o + 0x492) != 0 && func_32D238(o + 0x25C)) {
        *(short *)(o + 0x492) = 0;
        func_35A550(a0, 7, 2);
        if (!func_35A620(2)) {
            if (*(unsigned char *)(a0 + 0x43) != 0x11) {
                func_35A270(a0, 0x11, 0, 20);
            }
            o[0x48] = func_32E728(20.0f);
            o[0x4A] = func_32E728(24.0f);
        } else {
            if (*(unsigned char *)(a0 + 0x43) != 0x13) {
                func_35A270(a0, 0x13, 0, 20);
            }
            o[0x48] = func_32E728(20.0f);
            o[0x4A] = func_32E728(24.0f);
        }
    } else if (*(short *)(o + 0x492) == 0 && func_32D238(o + 0x25C)) {
        func_35A550(a0, 9, 2);
        if (*(unsigned char *)(a0 + 0x43) != 0x12) {
            func_35A270(a0, 0x12, 0, 20);
        }
        o[0x48] = func_32E728(20.0f);
        o[0x4A] = func_32E728(24.0f);
    }
}

void func_L06_004579C8(char *a0)
{
    char *s2 = *(char **)(a0 + 0x68);
    int v;

    func_32D5C8(a0 + 0x10, a0 + 0x10, s2);
    v = func_32E728((float)D_L06_001B375C * 1.5f);
    func_352000(a0, v, func_32E728((float)D_L06_001B375C * 1.25f), D_L06_001B375C);
    if (D_L06_001B3758 != 0) {
        func_32D8A8(s2, s2, 0.11666667461395264f);
        *(float *)(s2 + 0x8) = *(float *)(s2 + 0x8) + 0.18333333730697632f;
        *(unsigned int *)(a0 + 0x64) = (unsigned int)func_L06_003DDCA8;
        *(float *)(a0 + 0x2C) = *(float *)(a0 + 0x2C) * 0.75f;
        func_352000(a0, 0x10, 0x10, 0x10);
    }
}

void func_L06_00444068(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    float v[3];

    func_32D5F8((char *)v, D_L06_00189EA0, a0 + 0x10);
    func_365030(a0, (char *)v, (char *)v, 0);
    *(float *)(s1 + 0x2C0) = func_32DC80(v[0], v[1]);
    if (*(float *)(s1 + 0x2C0) > 0.78539825f) {
        *(float *)(s1 + 0x2C0) = 0.78539825f;
    } else if (*(float *)(s1 + 0x2C0) < -0.78539825f) {
        *(float *)(s1 + 0x2C0) = -0.78539825f;
    }
    *(float *)(s1 + 0x2C8) = -func_32DC80(func_32D740((char *)v), v[2]);
    if (*(float *)(s1 + 0x2C8) > 0.52359885f) {
        *(float *)(s1 + 0x2C8) = 0.52359885f;
    } else if (*(float *)(s1 + 0x2C8) < -0.52359885f) {
        *(float *)(s1 + 0x2C8) = -0.52359885f;
    }
}

void func_L06_00457AD0(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        func_35A550((char *)a0, 1, -1);
        break;
    case 1:
        if (func_35CBA0((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                func_35A550((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        func_32D650(tmp, (char *)(a0 + 0xD0), -0.033333335f);
        func_L06_00457C00((char *)a0, 7, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_3A0948(0, 0, (char *)a0);
        func_3661E0((char *)a0, 1, 0.0f);
        func_350388((char *)a0);
        break;
    }
    }
}

void func_L06_00457DA0(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        func_35A550((char *)a0, 1, -1);
        break;
    case 1:
        if (func_35CBA0((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                func_35A550((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        func_32D650(tmp, (char *)(a0 + 0xD0), -0.033333335f);
        func_L06_00457C00((char *)a0, 7, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_3A0948(0, 0, (char *)a0);
        func_3661E0((char *)a0, 1, 0.0f);
        func_350388((char *)a0);
        break;
    }
    }
}

void func_L06_0041FD60(char *a0)
{
    if (*(unsigned char *)(a0 + 0x21) != 0xFF)
        func_35B810(*(unsigned char *)(a0 + 0x21), 1);
}

/* func_L06_0041DED8 is defined in L06_0041DED8-update.c. */

extern char D_L06_001B0820[];
extern char D_L06_001B9840[];
extern int func_L02_0032E508(void *, int, void *, int);
extern void func_0026FEB8(const char *, ...);
extern float func_002A78D8(float, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L06_0041F798(u8 *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern void func_002A6C58(void *, int, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029F338(void *);

/* A Notak enemy's update, the same shape as func_L06_00443A38: spawn-time setup, then the
   distance, target and ground checks. The fields are indexed through typed pointers (in-struct
   MEMs), and the setup's store order is the one that gives retail's schedule and registers.
   qzero_nc's bare volatile asm flushes cse, so the later `m[0x43] != 3` test builds a fresh 3
   rather than keeping the setup's 3 in a saved register across the calls, as retail does. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void func_L06_0041EF08(u8 *m)
{
    u8 *v = *(u8 **)(m + 0x68);
    int hit;

    if (m[0x20] == 0) {
        I(0x480) = func_L02_0032E508(m, I(0x230), v + 0x260, 16);
        func_0026FEB8(D_L06_001B0820, I(0x480));
        qcopy(v + 0x460, m + 0x10);
        F(0x46C) = *(float *)(m + 0xF8);
        B(0x70) = 15;
        I(0xA8) = 3;
        B(0x71) = 12;
        F(0x90) = 0.5f;
        B(0x28) = 1;
        B(0xD4) = 0;
        H(0x26) = 0;
        B(0x72) = 16;
        B(0x76) = 14;
        B(0x77) = 15;
        F(0x7C) = 0.20000002f;
        F(0x80) = 0.125f;
        F(0x84) = 0.00555555569f;
        F(0x88) = 0.00972222257f;
        F(0x8C) = 0.00416666688f;
        F(0x94) = 0.5f;
        F(0x9C) = 0.4f;
        B(0xCC) = 7;
        B(0xCD) = 12;
        B(0xCE) = 3;
        B(0xCF) = 5;
        B(0xD2) = 10;
        B(0xD3) = 17;
        F(0x5AC) = (float)B(0x34);
        B(0x29) = 1;
        F(0x30) = 0.75f;
        F(0x47C) = func_002A78D8(10.0f, 25.0f) * 0.0174532942f;
        I(0x478) = 0;
        H(0x24C) = func_002A7820(0, 0x5F);
        I(0x498) = -1;
        I(0x5A0) = H(0x490);
        qzero_nc(v + 0x5B0);
        func_002A7750(m, 1, 0);
        if (m[0x43] != 1)
            func_002A7470(m, 1, 0, 0);
        B(0x48) = func_00283CF0(20.0f);
        B(0x4A) = func_00283CF0(8.0f);
        if (H(0x492) != 0) {
            if (m[0x43] != 3)
                func_002A7470(m, 3, 0, 0);
            B(0x48) = func_00283CF0(20.0f);
            B(0x4A) = func_00283CF0(24.0f);
        }
    }
    if (m[0x31] != 0 && func_00282E48(m + 0x10, D_L06_001B9840) < 24.0f) {
        func_002A93B0(m);
        m[0x6F] = 0x16;
    }
    hit = func_002B0ED8(m, v + 0x60, 0);
    if (hit != 0) {
        if (B(0x37) == 10)
            B(0xD7) = 1;
        if (hit == 5) {
            I(0xF0) = 0;
            F(0xF4) = 0.837758183f;
        }
        func_L06_0041F798(m);
        m[0xA8] = 0xFF;
    }
    I(0x228) = func_002B3BA8(m, I(0x220), F(0x240), 10.0f, 0, 0);
    I(0x22C) = func_002B3BA8(m, I(0x224), F(0x244), 10.0f, 0, 0);
    if (*(float *)(m + 0x18) < 48.0f) {
        func_002A6C58(m, 0, 3);
        func_002AC728(m, m + 0x10, -1, 1.0f, 13.0f);
        func_0029F338(m);
    }
}

#undef B
#undef H
#undef I
#undef F

/* Turns the actor toward its target and keeps the two angles it stores at +0x470 and
   +0x474 of its state; returns 1 when the actor's state changed. */
int func_L06_0041F2A0(char *a0, char *a1, float f1, float f2, float f3, float f4)
{
    char *st = *(char **)(a0 + 0x68);
    float v[4];
    float w[4];
    float x[4];
    float d = 0.0f;
    float out;
    float f24;
    float t;
    int ret = 0;

    func_00282CF0(v, (float *)a1, (float *)(a0 + 0x10));
    v[2] = 0.0f;
    f24 = func_00282DF0(v);
    t = f2 * 0.0008333333535119891f;
    if (f3 < f24) {
        int c = *(int *)(st + 0x480);

        out = 0.0f;
        func_L02_0032E998(a0 + 0x10, (int)a1, &out, st + 0x260, c, st + 0x488,
                          st + 0x48C, f4, 0.5f);
        func_002AAA00(a0 + 0xF8, out, 0.0037815470714122057f,
                      0.0037815470714122057f, 0.29670602083206177f, st + 0x474, 0);
        if (func_00283C80(*(float *)(a0 + 0xF8), out) < 1.3089970350265503f) {
            func_002AA548(&d, st + 0x470, f24, t, t, f2 * 0.01666666753590107f);
        } else {
            *(float *)(st + 0x470) = 0.0f;
        }
    } else {
        func_002AAA00(a0 + 0xF8, f1, 0.0037815470714122057f,
                      0.0037815470714122057f, 0.29670602083206177f, st + 0x474, 0);
        func_002AA2E8((float *)(st + 0x470), 0.0f, t);
        if (*(float *)(st + 0x470) == 0.0f) {
            if (func_00283C80(*(float *)(a0 + 0xF8), f1) < 0.0872664749622345f) {
                *(float *)(st + 0x474) = 0.0f;
                ret = 1;
            }
        }
    }
    func_00282F20(w, (float *)(a0 + 0xC0), *(float *)(st + 0x470));
    func_00282CC0(x, w, (float *)(a0 + 0x10));
    if (func_002A7EA0(a0, a0 + 0x10, (char *)x, 0, 0.8999999761581421f, 1.0f, 0.5f,
                     0.7853982448577881f) == 0) {
        *(int *)(st + 0x5A8) = *(int *)(st + 0x5A8) + 1;
    }
    /* The counter at +0x5A8 wraps at 0x14, and the actor then reports the change. */
    if (*(int *)(st + 0x5A8) < 0x14) {
        goto done;
    }
    *(int *)(st + 0x5A8) = 0;
    ret = 1;
done:
    return ret;
}

/* func_L06_0041F558 is defined in L06_0041F558.c. */

extern char D_L06_001B9840[];
extern int func_35A620(int);
extern float func_35A718(float, float);
extern void func_361300(void *, void *, void *, float);
extern char *func_37A018(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_32E728(float);
extern float func_35A6B8(float, float);

void func_L06_0041F818(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_32D5F8((char *)direction, (char *)D_L06_001B9840, (char *)pos);
    func_32D8A8((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_35A6B8(0.5f, 2.0f);
        sign = func_35A620(2);
        if (!sign) sign--;
        angle = func_35A6B8(-1.0471977f, 1.0471977f);
        func_361300(velocity, direction, axis, angle);
        func_32D8A8((char *)velocity, (char *)velocity, func_35A6B8(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = func_35A6B8(1.0f, 5.0f) * 0.0166666675f;
        func_32D5C8((char *)origin, (char *)pos, (char *)offset);
        pos[0] += func_35A718(0, 0.15f);
        pos[1] += func_35A718(0, 0.15f);
        pos[2] += func_35A718(0, 0.15f);
        particle = func_37A018(origin, 20, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_32E728(4.0f) + 0x70;
        particle = func_37A018(origin, 20, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = func_32E728(4.0f) + 0x70;
    }
}



/* func_L06_0041FC58 is matched in its own unit, src/levels/06_notak/L06_0041FC58-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

void func_L06_0041FD90(unsigned char *obj)
{
    char *data = *(char **)(obj + 0x68);
    float velocity[4], position[4];
    int count;
    unsigned char *first, *particle;
    func_002AB8C0(obj, data + 0x50);
    if (obj[0xBC]) {
        obj[0xBC] = 0;
        if (*(int *)(data + 0x248) < 300)
            *(int *)(data + 0x248) = func_002A7820(480, 600);
    }
    if (func_00282948(data + 0x24C) && *(int *)(data + 0x204) != 2)
        func_00282948(data + 0x248);
    func_00282948(data + 0x240);
    if (*(unsigned short *)(obj + 0x96) < 65534) ++*(unsigned short *)(obj + 0x96);
    if (func_00282948(data + 0x250)) *(float *)(data + 0x290) = *(float *)(data + 0x298);
    velocity[0] = 0;
    velocity[2] = -0.05f;
    velocity[3] = 1;
    velocity[1] = 0;
    count = func_002A77E0(16);
    if (func_002A77E0(2)) count = -count;
    qcopy(position, obj + 0x10);
    position[2] -= 0.2f;
    first = func_002BDCE8((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
    if (first) {
        unsigned char *state;
        *(short *)(first + 0xA) = 9;
        state = first + 0x20;
        first[9] = func_00283CF0(4) + 0x70;
        *(int *)(state + 4) = 2;
        state[0xA] = 0xDF;
        state[0xB] = first[0xA];
    }
    {
        unsigned char *second = func_002BDCE8((char *)position, .1f, 1, .9f, count, (char *)velocity, 315000, 0xDF204080, 0);
        if (second) {
            unsigned char *state = second + 0x20;
            /* Retail reuses the first particle header here. */
            *(short *)(first + 0xA) = 9;
            first[9] = func_00283CF0(4) + 0x70;
            *(int *)(state + 4) = 2;
            state[0xA] = 0xDF;
            state[0xB] = first[0xA];
        }
    }
    particle = func_002BDCE8((char *)position, .05f, 1, .97f, 16, (char *)velocity, 157500, 0x8FFFFFFF, 0);
    if (particle) {
        unsigned char *state;
        state = particle + 0x20;
        particle[9] = func_00283CF0(4) + 0x70;
        *(short *)(particle + 0xA) = 23;
        particle[8] = func_002A77E0(255);
        *(int *)(state + 4) = 2;
        state[0xA] = 0x8F;
        state[0xB] = first[0xA];
    }
}

/* func_L06_00420080 is defined in L06_00420080.c. */


/* func_L06_00420548 is defined in L06_00420548-g.c. */

/* func_L06_00420740 is defined in L06_00420740.c. */

/* func_L06_00420AE8 is defined in L06_00420AE8-g8.c. */

/* The object runs through five states. The dispatch reads the level's own jump table (five
   words in the level's data at 0x2E1F00); `cases` only keeps the labels alive. */
void func_L06_0042B868(char *a0)
{
    static void *cases[5] = {&&c0, &&c1, &&c2, &&c3, &&c4};
    char *s0 = a0;
    char *s1;
    unsigned int sel;

    sel = *(unsigned char *)(s0 + 0x20);
    s1 = *(char **)(s0 + 0x68);
    if (sel < 5)
        goto *D_L06_002E1F00[sel];
    goto done;
c0:
    *(unsigned char *)(s0 + 0x20) = 1;
    *(int *)s1 = 0x5DC;
    goto done;
c1:
    if (*(unsigned char *)(s0 + 0xBC) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 2;
    if (*(unsigned char *)(s0 + 0x43) != 1)
        func_35A270(s0, 1, 0, 0);
    *(int *)(s0 + 0x98) = 0;
    goto done;
c2:
    if ((*(unsigned char *)(s0 + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 3;
    if (*(unsigned char *)(s0 + 0x43) == 2)
        goto done;
    func_35A270(s0, 2, 0, 0);
    goto done;
c3:
    if (func_32D238(s1) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 4;
    if (*(unsigned char *)(s0 + 0x43) == 3)
        goto done;
    func_35A270(s0, 3, 0, 0);
    goto done;
c4:
    if ((*(unsigned char *)(s0 + 0x60) & 2) == 0)
        goto done;
    *(unsigned char *)(s0 + 0x20) = 1;
    if (*(unsigned char *)(s0 + 0x43) == 0)
        goto tail;
    func_35A270(s0, 0, 0, 0);
tail:
    *(int *)(s0 + 0x98) = *(int *)(*(int *)(s0 + 0x24) + 0x10);
    *(int *)s1 = 0x5DC;
    func_35B810(*(unsigned char *)(s0 + 0x21), 0);
    goto done;
done:
    return;
}

/* func_L06_00430318 is defined in L06_00430318-g8.c. */


/* func_L06_00443280 is defined in L06_00443280-g8.c. */

INCLUDE_ASM("asm/levels", func_L06_00443A38);

/* func_L06_00443A38 is defined in L06_0041DED8-g8.c. */

void func_L06_00443DE0(char *a0, int a1, int a2)
{
    char *p = *(char **)(a0 + 0x68);

    if (a2 == 0) {
        func_36C158();
    } else {
        func_36C1B0(*(float *)(p + 0x31C));
    }
}

void func_L06_00443E18(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    unsigned int v;

    func_32D268(s1 + 0x310);
    func_32D268(s1 + 0x312);
    v = *(unsigned short *)(a0 + 0x96);
    if (v <= 0xFFFE)
        *(unsigned short *)(a0 + 0x96) = v + 1;
    func_366160(a0, s1 + 0x260, 2.5f, 0, 1);
}


/* func_L06_00444168 and func_L06_00444300 live in L06_0041DED8-g8.c (func_L06_00444300 reaches
 * its constants through $gp; the pair is the level 6 twin of func_L14_00428A08/func_L14_00428BA0). */

/* The same re-arm, with two probe addresses and two flags. */
void func_L06_0044B250(char *arg0)
{
    int h;

    if (*(unsigned char *)(arg0 + 0x20) != 0)
        return;
    h = *(int *)(*(int *)(arg0 + 0x68));
    if (h == -1)
        return;
    if (func_360F58(D_L06_00189EA0, h) == 0)
        return;
    func_2E3EF0(D_L06_001B1330);
    func_2E3EF0(D_L06_001B1370);
    D_L06_001395B8.flag_013 = 1;
    D_L06_001395B8.flag_014 = 1;
    func_35A550(arg0, 1, -1);
}

/* Re-arms the object when the shared probe accepts its live handle. */
void func_L06_0044B2D8(char *arg0)
{
    int h;

    if (*(unsigned char *)(arg0 + 0x20) != 0)
        return;
    h = *(int *)(*(int *)(arg0 + 0x68));
    if (h == -1)
        return;
    if (func_360F58(D_L06_00189EA0, h) == 0)
        return;
    func_2E3EF0(D_L06_001B13B0);
    D_L06_001395CE = 1;
    func_35A550(arg0, 1, -1);
}

/* The same re-arm, with the level's second probe address. */
void func_L06_0044B350(char *arg0)
{
    int h;

    if (*(unsigned char *)(arg0 + 0x20) != 0)
        return;
    h = *(int *)(*(int *)(arg0 + 0x68));
    if (h == -1)
        return;
    if (func_360F58(D_L06_00189EA0, h) == 0)
        return;
    func_2E3EF0(D_L06_001B13F0);
    D_L06_001395CF = 1;
    func_35A550(arg0, 1, -1);
}

/* The same re-arm, gated on the shared live-object probe. */
void func_L06_004504C8(char *arg0)
{
    int h;

    if (*(unsigned char *)(arg0 + 0x20) != 0)
        return;
    h = *(int *)(*(int *)(arg0 + 0x68));
    if (h == -1)
        return;
    if (func_360F58(D_L06_00189EA0, h) == 0)
        return;
    if (func_333898() == 0)
        return;
    D_L06_001395D0 = 1;
    func_35A550(arg0, 1, -1);
}

/* func_L06_00455BC0 is in L06_0041DED8-f7-g8.c. */

/* func_L06_00456278 is in L06_00456278.c. */


void func_L06_00456EE0(void)
{
    func_3BFBB8(D_L06_002AA500, 0x30);
}

/* func_L06_00456F08 is defined in L06_00456F08.c. */

/* func_L06_00457270 is in L06_00457270.c: its zeroed vector is a por. */

/* func_L06_004573E8 is in L06_004573E8-g8.c. */


/* func_L06_004577B0 lives in L06_0041DED8-g8.c: it reads its first angle through $gp. */



extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_00273730(char *, int, int, int, char *, char *,
                           float *, int, float, float);

void func_L06_00457C00(char *object, int mask, void *offset, int color,
                      float speed_min, float speed_max,
                      float vertical_min, float vertical_max)
{
    float velocity[3];
    float angle, speed, life, size;
    char *particle;
    unsigned char shade = color;
    int i;

    for (i = 0; i < 15; i++) {
        if (((mask >> i) ^ 1) & 1)
            continue;
        angle = func_002A7940();
        speed = func_002A7878(speed_min, speed_max) * (1.0f / 60.0f);
        velocity[0] = func_00283180(angle) * speed;
        velocity[1] = func_00283198(angle) * speed;
        velocity[2] = 0.0f;
        velocity[2] = func_002A7878(vertical_min, vertical_max) * (1.0f / 60.0f);
        func_00282CC0(velocity, velocity, offset);
        life = func_002A7878(90.0f, 270.0f);
        size = func_002A7878(10.0f, 20.0f);
        particle = func_00273730(object, 2, *(short *)(object + 0xAA), i,
                                object + 0x10, object + 0xF0, velocity, shade,
                                life, size);
        if (particle)
            *(unsigned short *)(particle + 0x34) |= 0x10;
    }
}

void func_L06_00457ED0(unsigned char *obj)
{
    char *data;
    char *hit;
    short *list, *cursor;
    char *target;
    char *state;
    if (obj[0x20] == 0) {
        *(unsigned short *)(obj + 0x34) |= 0x800;
        obj[0x20] = 1;
    }
    data = *(char **)(obj + 0x68);
    hit = (char *)func_35CBA0((char *)obj, 0x10000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        if (*(int *)data == 255) { func_458138((char *)obj); return; }
        {
            list = D_L06_001FB3A0[*(int *)data];
            if (list == 0) { func_458138((char *)obj); return; }
            {
                cursor = list;
                do {
                    target = D_L06_001B281C[0] + ((*cursor & 0x7FFF) << 8);
                    if (*(signed char *)(target + 0x20) >= 0 && *(short *)(target + 0xAA) == 0xBBA) {
                        state = *(char **)(target + 0x68);
                        if (*(float *)(state + 0x20) > 0.0f) {
                            *(float *)(state + 0x5A4) = func_35A780();
                            qcopy(state + 0x5B0, state + 0x460);
                            *(short *)(state + 0x24C) = 0x10E;
                            target[0x20] = 4;
                            func_35A270(target, 6, 0, 10);
                            *(int *)(state + 0x5A0) = 0;
                            *(short *)(state + 0x492) = 0;
                            target[0x20] = 5;
                            target[0x95] = 1;
                        }
                    }
                } while (*cursor++ >= 0);
            }
        }
        if (*(int *)(data + 4) == 255) goto destroy;
        list = D_L06_001FB3A0[*(int *)(data + 4)];
        if (list == 0) {
 destroy:
            func_458138((char *)obj); return;
        }
        {
            cursor = list;
            do {
                target = D_L06_001B281C[0] + ((*cursor & 0x7FFF) << 8);
                if (*(signed char *)(target + 0x20) >= 0 && *(short *)(target + 0xAA) == 0xBBA) {
                    state = *(char **)(target + 0x68);
                    *(float *)(state + 0x5A4) = func_35A780();
                    qcopy(state + 0x5B0, state + 0x460);
                    *(short *)(state + 0x24C) = 0x10E;
                    target[0x20] = 4;
                    func_35A270(target, 6, 0, 10);
                    target[0x20] = 5;
                    target[0x95] = 1;
                }
            } while (*cursor++ >= 0);
        }
        func_458138((char *)obj);
    }
    obj[0xA8] = 255;
}
