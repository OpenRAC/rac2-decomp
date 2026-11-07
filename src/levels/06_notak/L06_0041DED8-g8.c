#include "include_asm.h"
#include "common.h"

extern char *D_L06_001B281C __attribute__((sda));

extern u8 *D_L06_001FB3A0[];
extern void func_002A7750(char *, int, int);
extern void func_002A7470(char *, int, int, int);
extern int func_002A7820(int, int);
extern int func_002E5CF8(int, int, char *);
extern int D_001A79F0;
extern unsigned char D_0019B2E8[];
extern char *D_L06_001FE500[];
extern void func_L01_003377C8(char *);
extern void func_00282A60(char *, int, int);
extern int func_L06_00420080(char *);
extern int func_002B0ED8(char *, char *, int);
extern void func_L06_0041FD60(char *);
extern void func_002AEE70(char *, char *, char *, float, float, float);
extern void func_002AEF28(char *, char *, char *, float, float, float);
typedef struct {
    char pad00[0x1830]; unsigned char *player;
    char pad1834[0xA60]; int mode;
} ControllerGlobals;
extern ControllerGlobals D_00189E20;
extern char D_L06_00188660[], D_L06_001B9840[];
extern char D_L06_002AA500[], D_L06_00257CC0[], D_L06_002DF000[], D_L06_00257FC0[], D_L06_002DF060[];
extern int D_L06_001B1858[] SDATA(D_L06_001B1858);
extern int D_L06_001B187C SDATA(D_L06_001B187C);
extern int D_L06_001B1880 SDATA(D_L06_001B1880);
extern void func_L06_00456EE0(void), func_L00_002E6EF8(void);
extern int func_L00_0035F5A0(int, int, char *);
extern void func_002E59F8(int);
extern void func_L04_003A1A78(void *), func_L04_003A1C98(void *), func_L04_003A1FA0(void *), func_L04_003A1FE0(void *);
extern void func_L04_003A5C08(char *, float);
extern float func_00282C48(float);
extern void func_002AA548(char *, char *, float, float, float, float);
extern int func_002ACBC8(char *, int);
typedef struct {
    int kind, count; char *items, *models, *data; int *states; char *aux, *more;
    int *a, *b; unsigned char *owner; void (*update)(void), (*callback)(void);
} Context;

void func_L06_0041F798(u8 *arg0)
{
    char *a2;
    u8 *p;
    u8 *list;

    if (arg0[0x21] == 0xFF)
        return;
    list = D_L06_001FB3A0[arg0[0x21]];
    if (list == 0)
        return;
    p = list;
    a2 = D_L06_001B281C;
    for (;;) {
        char *q = a2 + ((*(unsigned short *)p & 0x7FFF) << 8);

        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xBBA) {
                *(int *)(*(char **)(q + 0x68) + 0x258) = 1;
            }
        }
        if (*(short *)p < 0)
            break;
        p += 2;
    }
}

extern int D_L06_001B2838;
extern char *D_L06_001B2480;
extern float D_L06_001B1090 __attribute__((sda));
extern char D_L06_002E20C8[];
extern char D_L06_002E2128[];
extern void func_0026FEB8(const char *, ...);
extern void func_00282A28(void);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_L06_00443E88(u8 *);
extern void func_L06_00443F30(char *);
extern void func_002A6C58(void *, int, int);
extern void func_002AC728(void *, void *, int, float, float);
extern void func_0029F338(void *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);

/* A Notak enemy's update (spawn-time setup, then the shared distance, target and ground
   checks). The fields are indexed through typed pointers so their MEMs are in-struct: the
   sda and table loads after the angle call may then move above the word stores, as in
   retail. The setup's store order is the one that gives retail's schedule and FP registers. */
#define B(o) (v[o])
#define H(o) (((short *)v)[(o) / 2])
#define I(o) (((int *)v)[(o) / 4])
#define F(o) (((float *)v)[(o) / 4])

void func_L06_00443A38(u8 *m)
{
    u8 *v = *(u8 **)(m + 0x68);
    int hit;

    if (m[0x20] == 0) {
        char *rec;

        if (D_L06_001B2838 < m[0x21]) {
            func_0026FEB8(D_L06_002E20C8);
            func_0026FEB8(D_L06_002E2128);
            func_00282A28();
        }
        m[0x30] = 0x40;
        qcopy(v + 0x2E0, m + 0x10);
        F(0x324) = 1.0f;
        B(0x48) = func_00283CF0(15.0f);
        B(0x4A) = func_00283CF0(4.8f);
        H(0x88) = 0;
        B(0x60) = 8;
        I(0x98) = 3;
        F(0x108) = 0.5f;
        F(0x80) = 0.2f;
        F(0x84) = 0.2f;
        B(0x28) = 3;
        F(0x30) = 0.333f;
        F(0x8C) = 0.4f;
        F(0x100) = F(0x324) * 0.6f;
        F(0x134) = 0.05f;
        F(0x104) = F(0x324) * 0.5f;
        F(0x10C) = 0.5f;
        I(0x138) |= 0x80;
        F(0x110) = 1.57079649f;
        F(0x130) = 0.52359885f;
        F(0x1DC) = func_002A78D8(18.0f, 22.0f) * 0.0174532942f;
        B(0x1E8) = 7;
        B(0x1E9) = 6;
        H(0x1E2) = 120;
        H(0x1E4) = 180;
        F(0x1D4) = 3.0f;
        F(0x1D0) = D_L06_001B1090 * 0.0166666675f;
        rec = D_L06_001B2480 + I(0x210) * 0x30;
        if (*(short *)(rec + 0x30) != 0)
            I(0x13C) = **(int **)(rec + 0x3C);
        F(0x328) = func_002A7940();
        if (I(0x214) != 0) {
            *(int *)(m + 0x98) = 0;
            *(unsigned short *)(m + 0x34) = (*(unsigned short *)(m + 0x34) | 0x41) & 0xEFFF;
            func_002A7750((char *)m, 9, 4);
            if (m[0x43] != 10)
                func_002A7470((char *)m, 10, 0, 0);
        } else {
            func_002A7750((char *)m, 1, 0);
            if (m[0x43] != 0)
                func_002A7470((char *)m, 0, 0, 0);
        }
    }
    if (m[0x31] != 0 && func_00282E48(m + 0x10, D_L06_001B9840) < 24.0f) {
        func_002A93B0(m);
        m[0x6F] = 0x16;
    }
    hit = func_002B0ED8((char *)m, (char *)(v + 0x50), 0);
    if (hit != 0) {
        func_L06_00443E88(m);
        if (hit >= 4)
            func_L06_00443F30((char *)m);
    }
    if (*(float *)(m + 0x18) < 48.0f) {
        func_002A6C58(m, 0, 3);
        func_002AC728(m, m + 0x10, -1, 1.0f, 13.0f);
        func_0029F338(m);
    } else if (m[0x95] != 3 && m[0x95] != 4) {
        H(0x314) = func_002B3BA8(m, I(0x210), 16.0f, 0.0f, 0, 0);
    }
}

#undef B
#undef H
#undef I
#undef F

void func_L06_00443E88(u8 *arg0)
{
    char *a2;
    u8 *p;
    u8 *list;

    if (arg0[0x21] == 0xFF)
        return;
    list = D_L06_001FB3A0[arg0[0x21]];
    if (list == 0)
        return;
    p = list;
    a2 = D_L06_001B281C;
    for (;;) {
        char *q = a2 + ((*(unsigned short *)p & 0x7FFF) << 8);

        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xDB0) {
                *(short *)(*(int *)(q + 0x68) + 0x316) = 1;
            }
        }
        if (*(signed char *)(q + 0x20) >= 0) {
            if (*(short *)(q + 0xAA) == 0xBBA) {
                *(int *)(*(char **)(q + 0x68) + 0x258) = 1;
            }
        }
        if (*(short *)p < 0)
            break;
        p += 2;
    }
}

/* The id-list walks below read D_L06_001B281C as a bare symbol (a second name for the 4-byte
   `sda` pointer above, declared as a 12-byte array so the assembler keeps its loads absolute),
   while D_L06_001B2838 is a plain int: its `.extern` comes last in the file, which leaves a load
   in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern unsigned char *D_L06_001B281C_base[3] __asm__("D_L06_001B281C") __attribute__((sda));
extern int D_L06_001B2838;
extern int D_L06_001B2348;

/* Overlays for an owner (L06Obj) and the state block it points to (L06Cfg); only the fields the
   next two functions touch are named. */
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L06Cfg;

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L06Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L06Obj;

typedef struct {
    int a;
    int b;
} L06ColorPair;

extern void func_L06_00444300(L06Obj *);
extern L06ColorPair D_L06_001B1098[];
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_0029FC20(void *moby, int joint, void *out);
extern void func_L00_002E6CF0(void *, void *);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   colour pair and, when its stamp is not the current one, refreshes every live class-0xDB0
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L06_00444300 for the owner. */
void func_L06_00444168(L06Obj *self)
{
    L06Cfg *state = self->cfg;
    L06ColorPair colors = D_L06_001B1098[0];
    unsigned short *p;
    L06Obj *e;
    L06Cfg *s0;
    float angle;
    float blend;

    angle = func_00283B98(state->angle, 0.20943954f);
    state->angle = angle;
    blend = func_00283198(angle) * 0.5f + 0.5f;
    state->blend = blend;
    self->tint = func_00283D38(colors.a, colors.b, blend);
    if (state->stamp != D_L06_001B2348) {
        for (p = (unsigned short *)D_L06_001FB3A0[self->group];
             self->group != 0xFF && self->group <= D_L06_001B2838 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)D_L06_001FB3A0[self->group]);
             p++) {
            e = (L06Obj *)(D_L06_001B281C_base[0] + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->live != 0) {
                if (e->cls == 0xDB0) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (e->kind != 0xFE) {
                        if (e->kind != 0xFD) {
                            s0 = e->cfg;
                            func_0029FC20(e, 0, &s0->vec);
                            s0->stamp = D_L06_001B2348;
                        }
                    }
                }
            }
        }
        func_L00_002E6CF0((void *)func_L06_00444300, self);
    }
}

/* D_L06_001B10A0 is only used for its address, taken through $gp. D_L06_001B10B0 is one 8-byte
   object: its first word is loaded in a branch delay slot (so on $gp), its second as a bare
   symbol, which is how retail loads the two colours. */
extern int D_L06_001B10A0 __attribute__((sda));
extern int D_L06_001B10B0[2];
extern void func_00282D30(void *out, void *in, float scale);
extern void func_002830C0(void *a, void *b, void *c);
extern void func_L00_00325AE8(void *buf, int color, float f12, float f13);

/* For every live class-0xDB0 entity in the owner's group, builds the marker's vector from the
   entity's size and stored position and hands it to func_L00_00325AE8 with the colour pair
   blended by the entity's pulse. */
void func_L06_00444300(L06Obj *self)
{
    unsigned short *p;
    unsigned short *q;
    L06Obj *e;
    L06Cfg *s0;
    float buf[4];

    if (self->group == 0xFF)
        return;
    q = (unsigned short *)D_L06_001FB3A0[self->group];
    if (q == 0)
        return;
    for (p = q; self->group != 0xFF && self->group <= D_L06_001B2838 && p != 0 &&
                ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)D_L06_001FB3A0[self->group]);
         p++) {
        e = (L06Obj *)(D_L06_001B281C_base[0] + ((*p & 0x7FFF) << 8));
        if (e == 0)
            break;
        if (e->live != 0) {
            if (e->cls == 0xDB0) {
                if (e->kind != 0xFE) {
                    if (e->kind != 0xFD) {
                        s0 = e->cfg;
                        func_00282D30(buf, &D_L06_001B10A0, s0->scale);
                        func_002830C0(buf, buf, &s0->vec);
                        func_L00_00325AE8(buf,
                                          func_00283D38(D_L06_001B10B0[0], D_L06_001B10B0[1],
                                                        s0->blend),
                                          s0->scale * 0.2f, 0.08f);
                    }
                }
            }
        }
    }
}

/* The level's three turn angles, in degrees (37, 41 and 70); the step below turns them into
   radians per frame. The first one is read through $gp, the other two absolutely. */
extern float D_L06_001B18D0 __attribute__((sda));
extern float D_L06_001B18D4;
extern float D_L06_001B18D8;

extern float func_32E5D0(float, float);
extern void func_32DE28(void *, void *);
extern void func_32DA88(void *, void *, void *);
extern void func_32D650(char *, char *, float);
extern void func_32D5C8(char *, char *, char *);
extern void func_L03_0042B868(u8 *, void *, void *);

/* Turns the owner's three angles by the level's step, then walks the owner's eight records:
   each gets a fresh object, scaled and blended against the owner's own axes. `axes` is the
   scratch area func_32DE28 fills; its first vector is the one the objects are given. */
void func_L06_004577B0(char *a0)
{
    float axes[12];
    float v0[4];
    float v1[4];
    char *s0 = *(char **)(a0 + 0x68);
    char *s3 = s0 + 0xA0;
    char *s2 = s0 + 0x80;
    char *s4 = a0 + 0x10;
    float step = 0.000290888245f;
    float one = 1.0f;
    float two = 2.0f;
    int i;

    *(float *)(s0 + 0x120) = func_32E5D0(*(float *)(s0 + 0x120), D_L06_001B18D0 * step);
    *(float *)(s0 + 0x124) = func_32E5D0(*(float *)(s0 + 0x124), D_L06_001B18D4 * step);
    *(float *)(s0 + 0x128) = func_32E5D0(*(float *)(s0 + 0x128), D_L06_001B18D8 * step);
    func_32DE28(axes, s0 + 0x120);
    for (i = 7; i >= 0; i--) {
        func_32DA88(v0, s3, axes);
        s3 += 0x10;
        func_32D650((char *)v0, (char *)v0, 3.0f);
        func_32D650((char *)v1, (char *)v0, 3.3333335f);
        func_32D5C8((char *)v0, (char *)v0, s4);
        func_32D5C8((char *)v1, (char *)v1, s4);
        v0[3] = one;
        v1[3] = two;
        func_L03_0042B868(*(u8 **)s2, v0, v1);
        s2 += 4;
    }
}

int func_L06_00420230(unsigned char *obj)
{
    char *d = *(char **)(obj + 0x68);
    int hit, old;
    if (obj[0x20] == 0) {
        if ((D_0019B2E8[obj[0xB0] + (D_001A79F0 << 4)] & 0x80) && *(int *)(d + 0x33C)) return 1;
        *(int *)(d + 0x2AC) = 0;
        *(unsigned short *)(obj + 0x34) |= 0x800;
        *(int *)(d + 0x254) = -1;
        *(int *)(d + 0xA8) = 3;
        d[0x70] = 7; d[0x71] = 5; d[0x72] = 6; d[0x76] = 6; d[0x77] = 6;
        *(float *)(d + 0x7C) = 0.10000000894f;
        *(int *)(d + 0x80) = 0;
        *(float *)(d + 0x84) = 0.00416666688398f;
        *(float *)(d + 0x88) = 0.00833333376795f;
        *(float *)(d + 0x8C) = 0.00416666688398f;
        *(float *)(d + 0x90) = 2.5f; *(int *)(d + 0x94) = 0;
        *(float *)(d + 0x9C) = .4f;
        d[0xCC] = 4; d[0xCD] = 8; d[0xCE] = 4; d[0xCF] = 8;
        d[0xD2] = 4; d[0xD3] = 8; d[0xD4] = 0; d[0xD6] = 1;
        *(float *)(d + 0x2A8) = *(unsigned char *)(d + 0x34);
        d[0x28] = 3;
        *(int *)(d + 0x30) = 0; *(int *)(d + 0x258) = 0; *(int *)(d + 0x26C) = 0;
        qzero(d + 0x230);
        qcopy(d + 0x220, D_L06_001FE500[*(int *)(d + 0x274)] + 0x10);
        func_002A7750((char *)obj, 1, 0);
        if (obj[0x43] != 1) func_002A7470((char *)obj, 1, 0, 0);
        obj[0x30] = 0x80; *(short *)(obj + 0x32) = 0x80;
        func_L01_003377C8(D_L06_001FE500[*(int *)(d + 0x274)]);
        func_L01_003377C8(D_L06_001FE500[*(int *)(d + 0x270)]);
        func_00282A60(d + 0x2B0, 0, 0x80);
    }
    *(int *)(d + 0x258) = func_L06_00420080((char *)obj);
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24);
    old = obj[0x95];
    hit = func_002B0ED8((char *)obj, d + 0x60, 0);
    if (hit) {
        func_L06_0041FD60((char *)obj);
        if (hit < 4) func_002E5CF8(2, 0, (char *)obj);
        if (old == 1) *(int *)(d + 0x24C) = func_002A7820(300, 360);
        if ((unsigned int)(hit - 4) < 2) func_002A7750((char *)obj, 8, -1);
    }
    if (*(unsigned short *)(d + 0x98) & 3) *(int *)(obj + 0x98) = 0;
    func_002AEE70((char *)obj, d + 0x280, d + 0x284, .3f, .02327106148f, -1);
    func_002AEF28((char *)obj, d + 0x288, d + 0x28C, .1047197655f, .005235988647f, .006108653265982866f);
    return 0;
}

void func_L06_00456BB0(unsigned char *obj)
{
    char *d;
    Context context;
    float position[4];
    int count, id, allowed;
    unsigned char *player = D_00189E20.player;
    if (player && *(short *)(player + 0xAA) == 0x45 && player[0x20] != 254 && player[0x20] != 253 && D_00189E20.mode == 49) return;
    d = *(char **)(obj + 0x68);
    if (!d) return;
    count = 1;
    if (*(int *)(d + 0x18) != -1) count = D_L06_001B1858[*(int *)(d + 0x18)];
    count += *(int *)(d + 0x10);
    context.kind = 48; context.count = count;
    context.a = &D_L06_001B187C; context.b = &D_L06_001B1880;
    context.items = D_L06_002AA500; context.models = D_L06_00257CC0; context.data = D_L06_002DF000;
    context.states = D_L06_001B1858; context.aux = D_L06_00257FC0; context.more = D_L06_002DF060;
    context.update = func_L06_00456EE0; context.callback = func_L00_002E6EF8;
    context.owner = obj;
    if (*(unsigned char *)(d + 0x14) == 0 && *(int *)(d + 0x18) != -1) {
        char *firstTarget = D_L06_00188660 + *(int *)(d + 0x38) * 0x70;
        if (*(unsigned char **)(firstTarget + 0x88) != obj || *(unsigned char *)(firstTarget + 0x74) == 0)
            *(int *)(d + 0x38) = func_L00_0035F5A0(20, 4, (char *)obj);
    } else {
        id = *(int *)(d + 0x38);
        if (id != -1) {
            char *secondTarget = D_L06_00188660 + id * 0x70;
            if (*(unsigned char **)(secondTarget + 0x88) == obj && *(unsigned char *)(secondTarget + 0x74)) func_002E59F8(id);
        }
        *(int *)(d + 0x38) = -1;
    }
    switch (obj[0x20]) {
    case 0:
        func_L04_003A1A78(&context);
        func_L04_003A5C08((char *)obj, *(float *)(d + 0x34));
        if (*(int *)(d + 0x28) != -1) {
            int alpha = 255;

            obj[0x30] = alpha;
        }
        /* fall through */
    case 1:
        func_L04_003A1C98(&context);
        break;
    case 2:
        func_L04_003A1FA0(&context);
        if (func_00282C48(*(float *)(obj + 0x18) - *(float *)(d + 0x2C)) <= 2 && *(int *)(d + 0x18) != -1)
            func_002AA548((char *)obj + 0x18, d + 0x30, *(float *)(d + 0x2C), .0016666667070239782f, .0016666667070239782f, .10000000894f);
        break;
    }
    func_L04_003A1FE0(&context);
    if (*(int *)(d + 0x28) != -1 && !func_002ACBC8(D_L06_001B9840, *(int *)(d + 0x28))) {
        allowed = 1;
        if (*(int *)(D_L06_001B9840 + 0x2C0)) {
            qcopy(position, D_L06_001B9840);
            position[2] = *(float *)d;
            if (func_002ACBC8((char *)position, *(int *)(d + 0x28))) allowed = 0;
        }
        if (allowed) {
            for (id = *(int *)(d + 0x10); id < context.count; ++id)
                *(short *)(context.items + id * 0x1190 + 0x1E) = 0;
        }
    }
}
