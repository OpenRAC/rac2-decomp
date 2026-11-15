#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float D_L01_001AF628 __attribute__((sda));

extern float func_00283B98(float, float);

extern void func_00283898(char *, int, float);

extern void func_0029F978(char *, int, char *);

extern float func_002A7940(void);

/* grows a moby out of the ground the first time, then spins it down */
/* Moby update: Megacorp Vendor Logo (class 1143, PS3 name). */
void func_L01_00399170(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(unsigned char *)(a0 + 0x20) = 1;
        *(unsigned char *)(a0 + 0x63) = 0x20;
        *(float *)(s1 + 0x40) = func_002A7940();
        AttachManipulator(a0, 1, s1);
        break;
    case 1: {
        float f = D_L01_001AF628 * 0.000290888245f;

        *(float *)(a0 + 0xF8) = FastAddRotations(*(float *)(a0 + 0xF8), f);
        *(float *)(s1 + 0x40) = FastAddRotations(*(float *)(s1 + 0x40), f * -2.0f);
        build_axis_rotation_quaternion(s1 + 0x10, 2, *(float *)(s1 + 0x40));
        break;
    }
    }
}

/* spins the moby's wheels down and leans them, then steps the frame counter */

extern float D_L01_001AF50C __attribute__((sda));

extern float D_L01_001AF510 __attribute__((sda));

extern float D_L01_001AF514 __attribute__((sda));

extern float D_L01_001AF528 __attribute__((sda));

extern int D_L01_001AF54C __attribute__((sda));

extern float func_002E3A60(float);


extern int func_003104E8(int);

extern void func_L01_00397A28(char *);



extern void func_002833F0(void *, void *);

extern void func_00282F20(void *, void *, float);

extern void func_002A0F48(void *);

/* turns each of the three carried objects with a swinging pitch */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

struct Carrier_00398938;

typedef struct {
    char pad0[0x10];
    Vec4 pos;
    char pad20[0x48];
    struct Carrier_00398938 *vars;
    char pad6C[0x54];
    Vec4 mtx;
    char padD0[0x20];
    Vec4 rot;
} Moby_00398938;

typedef struct Carrier_00398938 {
    char pad0[0x14];
    Moby_00398938 *list[3];
    float swing;
    float t;
} Carrier_00398938;

extern void func_00282CC0(void *, void *, void *);

/* The level's per-frame lift and heading: they sit at another address in every level. */
extern float ref_L01_00398938_00 __attribute__((sda));

extern float ref_L01_00398938_01 __attribute__((sda));

void func_L01_00398938(Moby_00398938 *a0)
{
    Carrier_00398938 *d = a0->vars;
    Moby_00398938 **list = d->list;
    Vec4 *src = &a0->pos;
    Vec4 v;
    float pitch;
    int i;

    for (i = 0; i < 3; i++) {
        if (list[i] != 0) {
            Vec4 *rot;

            qcopy_nc(&list[i]->pos, src);
            list[i]->pos.z = list[i]->pos.z + ref_L01_00398938_00;
            rot = &list[i]->rot;
            rot->y = ref_L01_00398938_01 * 0.017453294f;
            pitch = d->swing * 2.4f - 1.2f;
            euler_rotation_basis(&list[i]->mtx, &list[i]->rot);
            vec_scale_to_length(&v, &list[i]->mtx, pitch);
            FastVecAdd(&list[i]->pos, &list[i]->pos, &v);
            rot = &list[i]->rot;
            rot->y = d->t * -1.0471977f - 0.3490659f;
            euler_rotation_basis(&list[i]->mtx, &list[i]->rot);
            func_002A0F48(list[i]);
        }
    }
}

extern float D_L01_001B1A9C __attribute__((sda));

extern float D_L01_001B1AA0 __attribute__((sda));

extern float D_L01_001B1AA4 __attribute__((sda));

extern float D_L01_001B1AA8 __attribute__((sda));

extern unsigned char D_L01_001B1AAC __attribute__((sda));

extern int D_L01_001B1AB0 __attribute__((sda));

extern int D_L01_001B1AB4 __attribute__((sda));

extern float D_L01_001B1AB8 __attribute__((sda));

extern float D_L01_001B1ABC __attribute__((sda));


extern void func_00282D30(void *, void *, float);

extern void func_0029FCC0(void *, int, void *);

extern void func_002A7A00(void *, float, float);

extern int func_002A77E0(int);

extern void func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);

extern void func_00282CC0(void *, void *, void *);

/* builds the tilt of a hanging chain over three steps and draws it */
void func_L01_00417090(char *a0)
{
    TI128 m, v1, v2;
    int i;
    int b;

    if (*(unsigned char *)(a0 + 0x20) == 1) {
        FastVecScale(&m, a0, 0.0009765625f);
    } else {
        func_0029FCC0(a0, 0, &m);
    }
    i = 2;
    func_002A7A00(&v1, D_L01_001B1A9C * 0.016666668f, D_L01_001B1AA0 * 0.016666668f);
    b = D_L01_001B1AAC;
    func_002C3150(&m, &v1, D_L01_001B1AB0, b, func_002A77E0(255), 0, D_L01_001B1AB8);
    do {
        i--;
        func_002A7A00(&v2, D_L01_001B1AA4 * 0.016666668f, D_L01_001B1AA8 * 0.016666668f);
        FastVecAdd(&v1, &v1, &v2);
        b = D_L01_001B1AAC;
        func_002C3150(&m, &v1, D_L01_001B1AB4, b, func_002A77E0(255), 0, D_L01_001B1ABC);
    } while (i >= 0);
}

/* Same body as func_L01_00417090, with this function's own callees. */
extern float D_00189F08 __attribute__((nosda));

extern float ref_L01_00397EB0_00 __attribute__((sda));
extern float ref_L01_00397EB0_01 __attribute__((sda));
extern unsigned char ref_L01_00397EB0_02 __attribute__((sda));
extern int ref_L01_00397EB0_03 __attribute__((sda));
extern float ref_L01_00397EB0_04 __attribute__((sda));
extern float ref_L01_00397EB0_05 __attribute__((sda));
extern float ref_L01_00397EB0_06 __attribute__((sda));
extern int ref_L01_00397EB0_07 __attribute__((sda));
extern float ref_L01_00397EB0_08 __attribute__((sda));
void func_L01_00397EB0(char *a0)
{
    TI128 m, v1, v2;
    int i;
    int b;

    if (*(unsigned char *)(a0 + 0x20) == 1) {
        FastVecScale(&m, a0, 0.0009765625f);
    } else {
        func_0029FCC0(a0, 0, &m);
        if (((float *)&m)[2] < D_00189F08) return;
    }
    i = 2;
    func_002A7A00(&v1, ref_L01_00397EB0_00 * 0.016666668f, ref_L01_00397EB0_01 * 0.016666668f);
    b = ref_L01_00397EB0_02;
    func_002C3150(&m, &v1, ref_L01_00397EB0_03, b, func_002A77E0(255), 0, ref_L01_00397EB0_04);
    do {
        i--;
        func_002A7A00(&v2, ref_L01_00397EB0_05 * 0.016666668f, ref_L01_00397EB0_06 * 0.016666668f);
        FastVecAdd(&v1, &v1, &v2);
        b = ref_L01_00397EB0_02;
        func_002C3150(&m, &v1, ref_L01_00397EB0_07, b, func_002A77E0(255), 0, ref_L01_00397EB0_08);
    } while (i >= 0);
}


extern float D_L01_001AF638 __attribute__((sda));

extern float D_L01_001AF63C __attribute__((sda));

extern float D_L01_001B2EF0 __attribute__((sda));

extern float D_L01_001B2F00 __attribute__((sda));

extern float D_001B2EF4 __attribute__((nosda));

extern int D_001B2F04 __attribute__((nosda));

extern float func_00310580(float, float);

extern float func_002E35D0(char *);

extern float func_002E35A0(float *);


extern char *ref_L01_003E9CF8_00 MACRO_ADDR;

extern int ref_L01_003E9CF8_01 MACRO_ADDR;


extern char *func_0029EFD0(int);

extern void func_002A04B8(char *, int *, int *, int *);

/* makes sure a live moby of class 0xC41 exists, then queues this moby in one of its 0x40 slots
   with its colour and a callback; with the queue full it runs the callback or deletes the moby */
typedef struct {
    char *obj;
    int rgb;
    int arg;
    float scale;
    void (*cb)(char *);
    int pad[3];
} Ent_3E9CF8;
extern Ent_3E9CF8 ref_L01_003E9CF8_02[];
extern void func_0029F338(void *);
void func_L01_003E9CF8(char *a0, int a1, void (*a2)(char *))
{
    char *p = ref_L01_003E9CF8_00;
    int x;
    int y;
    int z;
    int count;
    if (p == 0 || *(short *)(p + 0xAA) != 0xC41 ||
        *(unsigned char *)(p + 0x20) == 0xFE || *(unsigned char *)(p + 0x20) == 0xFD) {
        char *q = CreateMoby(0xC41);
        ref_L01_003E9CF8_00 = q;
        *(unsigned char *)(q + 0x30) = 0xFF;
    }
    count = ref_L01_003E9CF8_01;
    *(unsigned short *)(a0 + 0x34) |= 2;
    *(int *)(a0 + 0x48) = 0;
    *(int *)(a0 + 0x44) = 0;
    if (count < 0x40) {
        int n;
        get_moby_color(a0, &x, &y, &z);
        n = ref_L01_003E9CF8_01;
        ref_L01_003E9CF8_02[n].obj = a0;
        ref_L01_003E9CF8_02[n].rgb = (z << 16) | (y << 8) | x;
        ref_L01_003E9CF8_02[n].arg = a1;
        ref_L01_003E9CF8_02[n].scale = 1.0f;
        ref_L01_003E9CF8_02[n].cb = a2;
        ref_L01_003E9CF8_01 = n + 1;
    } else if (a2 != 0) {
        a2(a0);
    } else {
        func_0029F338(a0);
    }
}


extern void func_L01_003EE8E0(char *);

extern void func_002A7470(char *, int, int, int);

extern void func_002A7398(char *, int, int);

extern int func_00282948(char *);

extern const int D_L01_001B0D10 __attribute__((sda));

extern const int D_L01_001B0D14 __attribute__((sda));

/* brings the ring out of the ground, then lets it spin and hand itself over */
void func_L01_003EE6F0(char *a0)
{
    char *s1;

    s1 = *(char **)(a0 + 0x68);
    func_L01_003EE8E0(a0);

    switch (*(unsigned char *)(a0 + 0x20)) {
    case 0:
        *(float *)(a0 + 0x18) = *(float *)(a0 + 0x18) + 1.0f;
        *(float *)(s1 + 0x14) = *(float *)(a0 + 0xF0);
        *(unsigned char *)(a0 + 0x20) = 1;
        if (*(unsigned char *)(a0 + 0x43) != 0)
            func_002A7470(a0, 0, 0, 0xC);
        *(int *)(s1 + 0x50) = 0;
        *(unsigned short *)(a0 + 0x34) |= 0x1000;
        break;
    case 1:
        if ((*(unsigned char *)(a0 + 0x60) & 2) != 0) {
            if (*(unsigned char *)(a0 + 0x43) != 0)
                func_002A7398(a0, 0, 0);
        }
        if (*(unsigned char *)(a0 + 0xBC) == 0)
            break;
        *(unsigned short *)(a0 + 0x34) &= 0xEFFF;
        func_002A7398(a0, 1, 0);
        if (*(int *)(s1 + 0x0) != 0) {
            *(int *)(s1 + 0x10) = 10;
            *(unsigned char *)(a0 + 0x20) = 2;
            *(int *)(s1 + 0xC) = *(int *)(s1 + 0x4);
        } else {
            *(unsigned char *)(a0 + 0x20) = 2;
            *(int *)(a0 + 0x78) = D_L01_001B0D14;
            *(int *)(s1 + 0xC) = 0;
        }
        break;
    case 2:
        if (*(int *)(s1 + 0x0) != 0) {
            if (func_00282948(s1 + 0x10) != 0) {
                if (*(int *)(a0 + 0x78) == D_L01_001B0D10)
                    *(int *)(a0 + 0x78) = D_L01_001B0D14;
                else
                    *(int *)(a0 + 0x78) = D_L01_001B0D10;
                *(int *)(s1 + 0x10) = 10;
            }
            if (func_00282948(s1 + 0xC) != 0)
                *(unsigned char *)(a0 + 0xBC) = 0;
        }
        if ((*(unsigned char *)(a0 + 0x60) & 2) != 0) {
            if (*(unsigned char *)(a0 + 0x43) == 1)
                func_002A7398(a0, 2, 0);
        }
        if (*(unsigned char *)(a0 + 0xBC) != 0)
            break;
        if ((*(unsigned char *)(a0 + 0x60) & 2) != 0) {
            *(unsigned short *)(a0 + 0x34) |= 0x1000;
            func_002A7398(a0, 3, 0);
            *(unsigned char *)(a0 + 0x20) = 1;
            *(int *)(a0 + 0x78) = D_L01_001B0D10;
        }
        break;
    }
}

extern float func_00283B98(float, float);
extern void func_00282CC0(void *, void *, void *);
extern char D_00189E20[];



extern void func_0029FCC0(void *, int, void *);
extern int func_00282948(char *);
extern char D_00189E20[];
extern void func_002FDF40(void *, void *, int, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, char **, int *, float);
extern int func_00300540(int);
extern void func_002FE8D8(void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_L00_002D3F30(int, int);
extern int func_002B0CE0(int, int, int);
extern void func_L00_002AF568(void);
extern void func_L00_002AF7D0(void);
extern void func_002E5CF8(int, int, void *);
extern char *func_L00_003DE088(void *, void *);
extern void ref_L01_003B2598_00(void (*)(void *), void *);
extern void func_L00_003B8158(void *);
extern char *D_L01_001AFCE0 __attribute__((sda));
extern int D_L01_001A8F40 MACRO_ADDR;
extern int D_L01_001A8F48 MACRO_ADDR;
extern int D_L01_001A9034 MACRO_ADDR;
extern int D_00138324 NOT_SDA;

/* Moby update: Spiderbot Glove (class 2311). */
void func_L01_003B2598(char *m) {
    float pos[4], sweep_storage[4], normal[4];
    float *sweep;
    char *hit;
    int aux;
    char *d = *(char **)(m + 0x68);
    int result, state, ready;
    float height;

    {
        char *g = D_00189E20;

        if (*(int *)(g + 0x1244) == 3)
            D_L01_001AFCE0 = 0;
        func_0029FCC0(m, 0, pos);
        *(int *)(d + 0x2C) = 0;
        sweep = sweep_storage;
        height = (*(int *)(g + 0x2294) == 29) ? 11.0f : 4.5f;
        CalculateAimedLaunchVelocity(sweep, pos, 0, 0, 1.6f, height, 0.13333334028720856f, 0.003055555745959282f);
    }
    *(int *)(d + 0x24) = func_002FE5A0(pos, sweep, d, d + 0x10, m, &hit, &aux, 0.003055555745959282f);
    result = func_00300540(aux);
    if (D_L01_001A8F40 || D_L01_001A8F48 != -2)
        *(int *)(d + 0x2C) = 1;
    if (D_L01_001A9034 && *(float *)(d + 8) < 462.42999267578125f)
        *(int *)(d + 0x2C) = 1;
    if (result || !*(int *)(d + 0x24) || !*(int *)(d + 0x28))
        goto blocked;
    {
        char *g = D_00189E20;

        state = *(int *)(g + 0x2294);
        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6 ||
            state == 116 || state == 129)
            goto blocked;
        if (*(char **)(g + 0x33C) && (*(short *)(*(char **)(g + 0x33C) + 0xAA) == 0x330 ||
                                      *(short *)(*(char **)(g + 0x33C) + 0xAA) == 0xB21))
            goto blocked;
        if (hit && (*(short *)(hit + 0xAA) == 0xB21 || *(short *)(hit + 0xAA) == 0xB5B))
            goto blocked;
    }
    func_002FE8D8(d, normal);
    if (!(FastVecDot(d + 0x10, normal) < 0.75f))
        goto timer;
blocked:
    *(int *)(d + 0x2C) = 1;
timer:
    {
        char *g = D_00189E20;

        ready = 1;
        if (*(int *)(g + 0x2294) == 29) {
            if (!func_00282948(g + 0x2534))
                ready = 0;
        } else
            *(int *)(g + 0x2534) = 40;
    }
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        D_L01_001AFCE0 = m;
        *(unsigned char *)(m + 0x20) = 1;
        *(int *)(d + 0x28) = 1;
        *(int *)(d + 0x24) = 0;
        /* falls through */
    case 1: {
        char *g = D_00189E20;

        if ((D_00138324 & *(int *)(g + 0x1230)) && !*(unsigned char *)(g + 0x22BC) &&
            !*(int *)(d + 0x2C) && ready) {
            if (func_L00_002D3F30(-1, 1)) {
                *(short *)(g + 0x1E0) = 120;
                ForceClaimNotice(6, 0, 1);
                *(short *)(g + 0x1D2) = 0;
                start_equipped_item_animation();
                *(unsigned char *)(m + 0x20) = 2;
                *(int *)(d + 0x20) = 12;
                *(int *)(d + 0x28) = 0;
            } else
                PlayMobySound(0, 0, m);
        }
        break;
    }
    case 2:
        if (func_00282948(d + 0x20)) {
            char *p = func_L00_003DE088(pos, sweep);

            if (p)
                *(char **)(p + 0xB8) = m;
            PlayMobySound(1, 0, m);
            cancel_hero_item_animation();
            *(unsigned char *)(m + 0x20) = 3;
            *(int *)(d + 0x20) = 5;
        }
        break;
    case 3:
        if (func_00282948(d + 0x20))
            *(unsigned char *)(m + 0x20) = 1;
        break;
    }
    ref_L01_003B2598_00(func_L00_003B8158, m);
}
