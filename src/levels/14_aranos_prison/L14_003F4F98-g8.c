#include "include_asm.h"

extern int D_L14_001B17D8 __attribute__((sda));
extern int D_L14_001B17DC;
extern int D_001A72E0;

extern int func_00283D38(int a, int b, float c);
extern void func_385CB8(unsigned int reg, unsigned long value);
extern void func_3030C0(int, int, int, int, int, int);

/* Plays one sound effect derived from the owner's state block and then queues the level jingle. */
void func_L14_00427250(char *a0)
{
    char *v0;
    int s0;

    v0 = *(char **)(a0 + 0x68);
    s0 = func_00283D38(D_L14_001B17D8, D_L14_001B17DC, *(float *)v0);
    func_385CB8(0x42, 0x8000000044UL);
    func_3030C0(0, 0, 600, 500, s0, 0);
    func_385CB8(0x4E, 0x1000000UL | (D_001A72E0 >> 13));
}

extern float D_L14_001B17B8 __attribute__((sda));
extern float D_L14_001B17BC __attribute__((sda));

extern char D_00189EA0[];

extern void *func_L00_002D70A0(int size);

extern void func_L00_002D7140(void *block);

extern int func_002ACBC8(void *, int);

typedef struct {
    float x;
    float y;
} EffectPair;

/* Scans the four slot words at state+0x20; at the first one that is set and passes func_002ACBC8,
   makes sure the pool record at state+0x14 exists and writes D_L14_001B17B8/BC into its first two
   floats. If none passes, frees the record. */
void func_L14_00426E60(char *a0)
{
    char *state = *(char **)(a0 + 0x68);
    int *slot = (int *)(state + 0x20);
    int i;

    for (i = 0; i < 4; i++, slot++) {
        if (*slot != -1 && func_002ACBC8(D_00189EA0, *slot) != 0) {
            if (*(EffectPair **)(state + 0x14) == 0) {
                *(EffectPair **)(state + 0x14) = func_L00_002D70A0(5);
            }
            (*(EffectPair **)(state + 0x14))->x = D_L14_001B17B8;
            (*(EffectPair **)(state + 0x14))->y = D_L14_001B17BC;
            return;
        }
    }

    if (*(EffectPair **)(state + 0x14) != 0) {
        func_L00_002D7140(*(EffectPair **)(state + 0x14));
        *(EffectPair **)(state + 0x14) = 0;
    }
}

extern float D_L14_001B16B0 __attribute__((sda));
extern int func_002A9640(char *a0, int a1, int a2);
extern void func_002B0ED8(char *a0, char *a1, int a2);
extern void func_002AC728(char *a0, char *a1, float f12, float f13, int a2);
extern void func_002A6C58(char *a0, int a1, int a2);
extern void func_0029F338(char *a0);

/* Resets the moby's scale when its model says so, then lets it fall or die. */
void func_L14_00423240(char *a0)
{
    char *s0 = a0;
    char *s1;
    char *m;
    char *v;

    s1 = *(char **)(s0 + 0x68);
    v = (char *)func_002A9640(a0, 0x10000, 1);
    if (v != 0) {
        m = *(char **)(v + 0x20);
        if (m != 0 && *(short *)(m + 0xAA) == 0xB69) {
            if (*(unsigned char *)(s0 + 0x31) == 0)
                *(float *)(v + 0x2C) = 0.0f;
            else
                *(float *)(v + 0x2C) = 1.0f;
        }
    }
    func_002B0ED8(s0, s1 + 0x60, 0);
    if (*(float *)(s1 + 0x20) <= 0.0f) {
        func_002AC728(s0, s0 + 0x10, 1.0f, 13.0f, -1);
        func_002A6C58(s0, 0, 3);
        func_0029F338(s0);
    } else if (*(float *)(s0 + 0x18) < D_L14_001B16B0) {
        func_002A6C58(s0, 0, 3);
        func_0029F338(s0);
    }
}

extern float D_L14_001B1678 __attribute__((sda));
extern float D_L14_001B167C __attribute__((sda));
extern int D_L14_001B1660 __attribute__((sda));
extern int D_L14_001B1668 __attribute__((sda));
extern int D_L14_001B1690 __attribute__((sda));
extern int D_L14_001B1694 __attribute__((sda));
extern float D_L14_001B1698 __attribute__((sda));
extern float D_L14_001B169C __attribute__((sda));
extern float D_L14_001B16A0 __attribute__((sda));
extern float D_L14_001B16A4 __attribute__((sda));
extern char D_L14_002594F0[][0x280];
extern void func_L14_004229A0(char *, char *, int, int, int, float, float, float);

void func_L14_004228C0(char *object) {
    char *state = *(char **)(object + 0x68);

    D_L14_001B1678 -= D_L14_001B167C;
    if (D_L14_001B1678 <= -8.0f)
        D_L14_001B1678 += 8.0f;
    func_L14_004229A0(object, D_L14_002594F0[*(int *)(state + 0x38)],
        D_L14_001B1660, D_L14_001B1668, *(int *)(state + 0x2C) - 2,
        *(float *)(state + 0x40), *(float *)(state + 0x44), D_L14_001B16A0);
    func_L14_004229A0(object, D_L14_002594F0[*(int *)(state + 0x38)] + 0x140,
        D_L14_001B1690, D_L14_001B1694, *(int *)(state + 0x2C),
        D_L14_001B1698, D_L14_001B169C, D_L14_001B16A4);
}

extern int D_L14_001B259C __attribute__((sda));

extern int func_L00_00324120(char *self);
extern void func_L00_003294F0(int table, int mode);
extern void func_002A7750(char *self, int state, int mode);
extern int func_002B3868(char *self);
extern void func_002E5CF8(int a, int b, char *self);
extern float func_00283B98(float a, float b);
extern float func_00283198(float a);
extern int func_00283D38(int a, int b, float c);

/* Steps the owner's state block, then blends the two colours its state asks for. */
void func_L14_00409B20(char *self)
{
    char *v = *(char **)(self + 0x68);
    int c1 = 0x808C8C8C;
    int c2 = 0x80282828;
    int idx;
    float f;
    int r;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (func_L00_00324120(self) != 0) {
            idx = *(int *)(v + 0);
            if (idx != -1) {
                func_L00_003294F0(D_L14_001B259C + (idx << 8), 1);
            }
            func_002A7750(self, 1, -1);
        }
        break;
    case 1:
        if (func_002B3868(self) != 0) {
            func_002E5CF8(0, 0, self);
        }
        c1 = 0x80468CDC;
        c2 = 0x801E78AA;
        break;
    }
    f = func_00283B98(*(float *)(v + 4), 0.10762865f);
    *(float *)(v + 4) = f;
    r = func_00283D38(c1, c2, func_00283198(f) * 0.5f + 0.5f);
    *(int *)(self + 0x78) = func_00283D38(*(int *)(self + 0x78), r, 0.15f);
}

/* The id-list walks below (func_L14_00426D18, func_L14_00428A08, func_L14_00428BA0) read
   D_L14_001B259C as a bare symbol, while the `sda` int above reaches the same word through $gp.
   The assembler takes the last `.extern` size it has seen: the second name's 12 bytes (bare
   `lui`/`lw`) must come after the 4 bytes of the int's, so these functions follow
   func_L14_00409B20. D_L14_001B25B8 is a plain int: its `.extern` comes last in the file, which
   leaves a load in a branch delay slot on $gp and every other load on `lui`/`lw`. */
extern unsigned short *D_L14_001FB060[];
extern int D_L14_001B25B8;
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));

/* Sets the flag bit (+0xBE, 4) of every entity in the id list the state's group word names,
   unless the word is -1. */
void func_L14_00426D18(char *a0)
{
    char *state = *(char **)(a0 + 0x68);
    unsigned short *p;
    unsigned char *e;

    if (state != 0 && *(int *)(state + 0x38) != -1) {
        for (p = D_L14_001FB060[*(int *)(state + 0x38)];
             (*(int *)(state + 0x38) & 0xFF) != 0xFF && *(int *)(state + 0x38) <= D_L14_001B25B8 &&
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[*(int *)(state + 0x38)]);
             p++) {
            e = D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            func_L00_003294F0((int)e, 1);
        }
    }
}

/* Overlays for an owner (L14Obj) and the state block it points to (L14Cfg); only the fields the
   next two functions touch are named. Typed member accesses are what give retail's order of the
   compare's two loads (the scalar global first): with `*(int *)(p + off)` casts the field load
   is scheduled ahead of it. */
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L14Cfg;

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L14Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L14Obj;

typedef struct {
    int a;
    int b;
} L14ColorPair;

extern void func_L14_00428BA0(L14Obj *);
extern L14ColorPair D_L14_001B18C0[];
extern int D_L14_001B20C8;
extern void func_0029FC20(void *moby, int joint, void *out);
extern void func_L00_002E6CF0(void *, void *);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   first colour pair and, when its stamp is not the current one, refreshes every live class-0x112B
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L14_00428BA0 for the owner. */
void func_L14_00428A08(L14Obj *self)
{
    L14Cfg *state = self->cfg;
    L14ColorPair colors = D_L14_001B18C0[0];
    unsigned short *p;
    L14Obj *e;
    L14Cfg *s0;
    float angle;
    float blend;

    angle = func_00283B98(state->angle, 0.20943954f);
    state->angle = angle;
    blend = func_00283198(angle) * 0.5f + 0.5f;
    state->blend = blend;
    self->tint = func_00283D38(colors.a, colors.b, blend);
    if (state->stamp != D_L14_001B20C8) {
        for (p = D_L14_001FB060[self->group];
             self->group != 0xFF && self->group <= D_L14_001B25B8 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[self->group]);
             p++) {
            e = (L14Obj *)(D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->live != 0) {
                if (e->cls == 0x112B) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (e->kind != 0xFE) {
                        if (e->kind != 0xFD) {
                            s0 = e->cfg;
                            func_0029FC20(e, 0, &s0->vec);
                            s0->stamp = D_L14_001B20C8;
                        }
                    }
                }
            }
        }
        func_L00_002E6CF0((void *)func_L14_00428BA0, self);
    }
}

/* D_L14_001B18D0 is only used for its address, taken through $gp. D_L14_001B18E0 is one 8-byte
   object: its first word is loaded in a branch delay slot (so on $gp), its second as a bare
   symbol, which is how retail loads the two colours. */
extern int D_L14_001B18D0 __attribute__((sda));
extern int D_L14_001B18E0[2];
extern void func_00282D30(void *out, void *in, float scale);
extern void func_002830C0(void *a, void *b, void *c);
extern void func_L00_00325AE8(void *buf, int color, float f12, float f13);

/* For every live class-0x112B entity in the owner's group, builds the marker's vector from the
   entity's size and stored position and hands it to func_L00_00325AE8 with the second colour
   pair blended by the entity's pulse. */
void func_L14_00428BA0(L14Obj *self)
{
    unsigned short *p;
    unsigned short *q;
    L14Obj *e;
    L14Cfg *s0;
    float buf[4];

    if (self->group == 0xFF)
        return;
    q = D_L14_001FB060[self->group];
    if (q == 0)
        return;
    for (p = q; self->group != 0xFF && self->group <= D_L14_001B25B8 && p != 0 &&
                ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[self->group]);
         p++) {
        e = (L14Obj *)(D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8));
        if (e == 0)
            break;
        if (e->live != 0) {
            if (e->cls == 0x112B) {
                if (e->kind != 0xFE) {
                    if (e->kind != 0xFD) {
                        s0 = e->cfg;
                        func_00282D30(buf, &D_L14_001B18D0, s0->scale);
                        func_002830C0(buf, buf, &s0->vec);
                        func_L00_00325AE8(buf,
                                          func_00283D38(D_L14_001B18E0[0], D_L14_001B18E0[1],
                                                        s0->blend),
                                          s0->scale * 0.2f, 0.08f);
                    }
                }
            }
        }
    }
}
