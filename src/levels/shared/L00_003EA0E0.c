#include "include_asm.h"

extern int D_L00_001A8F00 __attribute__((sda));
extern void func_L00_002E54E0(float value);
extern float func_00282C48(float value);
extern char D_L00_001D9F00[];
extern char D_L00_001DA860[];
int func_L00_003D3DE0(char *a, char *b);
int func_L00_003EB610(char *a, char *b);
void func_L00_0035F180(char *a, int b, int c, char *d, int e);

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

extern int D_L00_001B0798[] __attribute__((sda));

extern void func_002A3F10(char *p, int one, int *w, char *out);

extern void func_00282D30_3(char *a, char *out, float f);

extern void func_00282CC0_4(char *a, char *b, char *c);

extern void func_00283098_2(char *a, char *b, char *c);

extern void func_002FDBD8_4(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern int func_002ACBC8(void *, int);

extern int func_L00_002E3B38(int);

extern void func_0026FEB8(void *, ...);

extern unsigned char D_00189EA0[];

extern unsigned char D_0019B2E8[];

extern int D_001A79F0 __attribute__((sda));

extern int D_001A7A10 __attribute__((sda));

extern int D_001A7A14 __attribute__((sda));

extern int D_L00_001C5480[][3];

extern int D_L00_001C5540[][3];

extern char D_L00_001B0700[];

extern char D_L00_001B8DC0[];

extern void func_00282CF0(char *, char *, char *);

extern float func_00283248(float, float);

extern float func_002A7878(float, float);

extern float func_002A78D8(float, float);

extern int func_00283CF0(float);

extern float func_00283B98(float, float);

extern void func_002AF000(float *, float, float, float);

extern void func_002C16C0(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);

/* Measured partial layouts; original type and game roles are unknown. */

/* scales a float field by 1/1024, passes a caller word and two 16/48-byte scratch buffers to a four-argument helper, then forwards the second buffer with the scaled float to one helper and two sub-objects of the same parameter to three more helpers */
void func_L00_003EA0E0(char *p, int v, char *a, char *b)
{
    char out0[48];
    char out48[16];
    int w;
    float f;

    f = *(float *)(p + 44) * 0.0009765625f;
    w = v;
    func_002A3F10(p, 1, &w, out0);
    func_00282D30_3(a, out48, f);
    func_00282CC0_4(a, a, b);
    func_00283098_2(a, a, p + 192);
    func_00282CC0_4(a, a, p + 16);
}

void func_L00_003EA408(char *p)
{
    float v;
    float x;
    float a;
    float b;
    float c;
    int *q;

    if (*(unsigned char *)(p + 0x20) == 0) {
        *(unsigned short *)(p + 0x32) = 0xAF0;
        *(unsigned char *)(p + 0x30) = 0xFF;
        *(unsigned char *)(p + 0x20) = 1;
        func_L00_002E54E0(3000.0f);
    }
    if (*(unsigned char *)(p + 0x20) != 1)
        return;
    if (D_L00_001A8F00 == 2)
        return;

    v = *(float *)(p + 0x14);
    v = v - 1.6666667f;
    *(float *)(p + 0x14) = v;
    x = func_00282C48(v);

    a = 3000.0f - x;
    b = 750.0f - a;
    c = 1.0f - b * (1.0f / 750.0f);
    if (c > 3.0f)
        c = 3.0f;
    if (c < 0.0f)
        c = 0.0f;

    q = *(int **)(p + 0x24);
    *(float *)(p + 0x2C) = *(float *)((char *)q + 0x24) * c;
    if (*(float *)(p + 0x14) <= -3000.0f)
        *(float *)(p + 0x14) = 3000.0f;
}


/* func_L00_003EA540 is defined in its own unit. */

/* shared native body of family 5a97ab89858c */
void func_L00_003EA860(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector D_L00_001B8C80;
extern void func_3EA860(char *);
extern int func_2E67A0(int);
extern float func_2EE7A8(float, float);
extern float func_2EE2E8(char *, char *);
extern float func_31A888(void);
extern void func_2EE970(char *, char *);
extern void func_2EE178(char *, char *, float);
extern void func_2EAC30(char *, char *, int);

/* Builds one aim/render packet: resets the work record, fills the colour and the blend words,
   takes the two aim angles from the level's aim vector, turns them into the packet's orientation
   and scales the packet's four basis vectors by the caller's alpha. */
void func_L00_003EA8C8(char *unused, char *position, int color, float alpha)
{
    unsigned char work[0xE0];
    float first;
    float second;

    func_3EA860((char *)work);
    *(int *)(work + 0x50) = 0;
    *(int *)(work + 0x54) = 0;
    *(int *)(work + 0x58) = 0;
    *(float *)(work + 0x5C) = 1.0f;
    *(float *)(work + 0x60) = 1.0f;
    *(int *)(work + 0x64) = 0;
    *(float *)(work + 0x68) = 1.0f;
    *(float *)(work + 0x6C) = 1.0f;
    *(long long *)(work + 0x78) = func_2E67A0(0x2C);
    *(long long *)(work + 0x80) = 0x0000FF9000000260LL;
    *(long long *)(work + 0x88) = 0x0000008000000048LL;
    *(int *)(work + 0x4C) = color;
    *(int *)(work + 0x48) = color;
    *(int *)(work + 0x44) = color;
    *(int *)(work + 0x40) = color;
    *(long long *)(work + 0x70) = 0;
    *(int *)(work + 0xDC) = 0;

    first = func_2EE7A8(D_L00_001B8C80.x_140 - *(float *)(position + 0),
                        D_L00_001B8C80.y_144 - *(float *)(position + 4));
    *(float *)(work + 0xD8) = first;

    second = func_2EE7A8(func_2EE2E8(position, &D_L00_001B8C80.x_140),
                         D_L00_001B8C80.z_148 - *(float *)(position + 8));
    *(float *)(work + 0xD4) = -second;
    *(float *)(work + 0xD0) = func_31A888();
    func_2EE970((char *)work + 0x90, (char *)work + 0xD0);

    *(float *)(work + 0xC0) = *(float *)(position + 0);
    *(float *)(work + 0xC4) = *(float *)(position + 4);
    *(float *)(work + 0xC8) = *(float *)(position + 8);
    *(float *)(work + 0xCC) = 1.0f;
    func_2EE178((char *)work, (char *)work, alpha);
    func_2EE178((char *)work + 16, (char *)work + 16, alpha);
    func_2EE178((char *)work + 32, (char *)work + 32, alpha);
    func_2EE178((char *)work + 48, (char *)work + 48, alpha);
    func_2EAC30((char *)work, (char *)work + 0x90, 0);
}

/* func_L00_003EAA58 is defined in L00_003EAA58.c. */

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_003EAC88(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_4(1.0f, context, context->vector_10, 0);
    }
}

void func_L00_003EAEF8(char *object) {
    int *state = *(int **)(object + 0x68);
    int result, index, shift;
    unsigned char *entry;

    if (!func_002ACBC8(D_00189EA0, state[1]))
        return;
    D_00189EA0[0x2246] = *(unsigned char *)(object + 0xB0);
    if (state[2])
        return;
    if ((D_0019B2E8[*(unsigned char *)(object + 0xB0) + D_001A79F0 * 16] >>
         (*(unsigned char *)(object + 0xB1) * 2)) & 3)
        return;
    state[2] = 1;
    result = func_L00_002E3B38(*(unsigned char *)(object + 0xB0));
    index = (*(unsigned char *)(object + 0xB0) & 15) + D_001A79F0 * 16;
    shift = (*(unsigned char *)(object + 0xB1) & 3) * 2;
    entry = D_0019B2E8 + index;
    if (!((*entry >> shift) & 3)) {
        *entry = (*entry & ~(3 << shift)) | (result << shift);
        D_001A7A10 += D_L00_001C5480[*(unsigned char *)(object + 0xB0) & 15]
                                   [*(unsigned char *)(object + 0xB1) & 3];
        D_001A7A14 += D_L00_001C5540[*(unsigned char *)(object + 0xB0) & 15]
                                   [*(unsigned char *)(object + 0xB1) & 3];
    }
    func_0026FEB8(D_L00_001B0700,
        D_L00_001C5480[*(unsigned char *)(object + 0xB0)][*(unsigned char *)(object + 0xB1)],
        D_L00_001C5540[*(unsigned char *)(object + 0xB0)][*(unsigned char *)(object + 0xB1)]);
}

extern int D_L00_001C9340;

extern void func_L00_00323448(char *, void *, int, int, int, int, int, int);

extern void func_0029F338(char *);

extern void func_002833F0(void *, void *);

extern float func_00283198(float);

extern void func_002AEE70(char *, void *, void *, float, float, float);

extern void func_002AEF28(char *, float, void *, float, void *, float);

extern void func_00283738(void *, void *, void *);

extern void func_002AB6D8(void *, void *);

extern void func_L00_00323958(char *, void *);

typedef struct {
    long long id;
    int flags;
    int level;
    float angles[3];
    int mode;
    float firstAngle;
    float firstVelocity;
    float secondAngle;
    float secondVelocity;
    float firstSpeed;
    float firstStep;
    float secondSpeed;
    float secondStep;
    char entries[0x4A];
    unsigned char present;
    char pad_8B[2];
    unsigned char update;
} L00_003EB0C0_State;

void func_L00_003EB0C0(char *self)
{
    float angles[4];
    char mat[48];
    L00_003EB0C0_State *st = *(L00_003EB0C0_State **)(self + 0x68);
    int i;
    int last;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (st->id == -1)
            break;
        {
            /* An int, not a byte constant: reload would otherwise reuse the -1 still in $v0. */
            int alpha = 255;
            *(unsigned char *)(self + 0x30) = alpha;
        }
        func_L00_00323448(self, st->entries, 0x50, *((int *)&st->id + 1), *(int *)&st->id, st->flags, 7, 0);
        if (!st->present) {
            func_0029F338(self);
            break;
        }
        if (!st->mode) {
            st->update = 1;
            *(unsigned short *)(self + 0x34) |= 0x104;
            func_002833F0(self + 0xC0, self + 0xF0);
        }
        if (st->firstAngle != 0.0f)
            st->firstAngle *= 0.01745329424738884f;
        st->firstVelocity = func_00283198(st->firstAngle) * st->firstSpeed;
        self[0x20] = 1;
        break;
    case 1:
        if (D_L00_001C9340 != st->level)
            break;
        if (st->firstStep > 0.0f)
            func_002AEE70(self, &st->firstAngle, &st->firstVelocity, st->firstSpeed,
                          st->firstStep * 0.0002908882452175021f, -1.0f);
        if (st->secondStep > 0.0f) {
            func_002AEF28(self, st->secondSpeed * 0.01745329424738884f, &st->secondAngle,
                          st->secondStep * 0.0002908882452175021f, &st->secondVelocity, 0.00581776537001133f);
            if (st->update)
                func_002833F0(self + 0xC0, self + 0xF0);
        }
        if (!st->mode) {
            angles[0] = st->angles[0] * 0.0002908882452175021f;
            angles[1] = st->angles[1] * 0.0002908882452175021f;
            angles[2] = st->angles[2] * 0.0002908882452175021f;
            func_002833F0(mat, angles);
            func_00283738(self + 0xC0, self + 0xC0, mat);
            if (st->secondStep > 0.0f)
                func_002AB6D8(self + 0xC0, self + 0xF0);
        } else {
            i = 0;
            do {
                angles[0] = st->angles[0] * 0.0002908882452175021f;
                angles[1] = st->angles[1] * 0.0002908882452175021f;
                angles[2] = st->angles[2] * 0.0002908882452175021f;
                func_002833F0(mat, angles);
                func_00283738(st->entries + i * 0x50, st->entries + i * 0x50, mat);
                last = *(unsigned char *)(st->entries + i * 0x50 + 0x4A);
                i++;
            } while (last != 1);
        }
        func_L00_00323958(self, st->entries);
        break;
    }
}

extern int func_002A8508(int, int);

extern unsigned char *D_L00_001B1E9C __attribute__((sda));

extern int D_L00_001FA920[];

extern int D_L00_001B0720[];

extern int D_L00_001B0738[];

/* Four-id switch: wait for the resident check, flip bit 0x43 of every record the first
   list of each of the four ids names and arm D_L00_001B0720; wait again, clear those bits
   and arm D_L00_001B0738. */
void func_L00_003EB400(char *self)
{
    int i;
    char *state = *(char **)(self + 0x68);

    if (*(unsigned char *)(self + 0x20) == 0) {
        if (func_002ACBC8(D_00189EA0, *(int *)(state + 0x10)))
            *(unsigned char *)(self + 0x20) = 1;
    }
    if (*(unsigned char *)(self + 0x20) == 1) {
        int i;
        for (i = 0; i < 4; i++) {
            int id;
            unsigned short *p;
            char *entry;
            char *records;
            char *row;

            row = (char *)state + i * 4;
            id = *(int *)row;
            if (D_L00_001FA920[id] == 0)
                continue;
            if (func_002A8508(id, -1) < 2)
                continue;
            records = D_L00_001B1E9C;
            p = (unsigned short *)D_L00_001FA920[*(int *)(state + i * 4)];
            do {
                entry = records + (*p & 0x7FFF) * 256;
                *(unsigned short *)(entry + 0x34) |= 0x43;
            } while ((short)*p++ >= 0);
        }
        func_0026FEB8(D_L00_001B0720);
        *(unsigned char *)(self + 0x20) = 2;
    }
    if (*(unsigned char *)(self + 0x20) == 2) {
        if (func_002ACBC8(D_00189EA0, *(int *)(state + 0x10)) == 0)
            *(unsigned char *)(self + 0x20) = 3;
    }
    if (*(unsigned char *)(self + 0x20) == 3) {
        int i;
        for (i = 0; i < 4; i++) {
            int id;
            unsigned short *p;
            char *entry;
            char *records;
            char *row;

            row = (char *)state + i * 4;
            id = *(int *)row;
            if (D_L00_001FA920[id] == 0)
                continue;
            if (func_002A8508(id, -1) < 2)
                continue;
            records = D_L00_001B1E9C;
            p = (unsigned short *)D_L00_001FA920[*(int *)(state + i * 4)];
            do {
                entry = records + (*p & 0x7FFF) * 256;
                *(unsigned short *)(entry + 0x34) &= 0xFFBC;
            } while ((short)*p++ >= 0);
        }
        func_0026FEB8(D_L00_001B0738);
        *(unsigned char *)(self + 0x20) = 0;
    }
}

/* func_L00_003EB610 is defined in L00_003EB610-g16.c. */


/* func_L00_003EB8E8 is defined in L00_003EB8E8-g8.c. */


/* func_L00_003EC078 is defined in L00_003EC078-zero-ti-por-g8.c. */


void func_L00_003ECB00(void)
{
    int i;

    for (i = 3; i >= 0; i--)
        D_L00_001B0798[i] = 0;
}

typedef struct { char pad[0x2290]; char *tbl; } Rac2Native_003ECB38_ConstBlock;

/* Calls the four table-driven float helpers over a 16-byte scratch record and a
   second record at +0x10, then when the probe result is not zero computes
   pi/2 - fn(angle / probe) and hands obj+0xF8, the third parameter and the
   three incoming floats to the renderer helper; original game role is unknown. */
void func_L00_003ECB38(char *obj, void *rec, char *mob, float fa, float fb, float fc)
{
    extern void func_2EE138(void *, void *, void *);
    extern float func_2EE1F8(char *, char *);
    extern void func_2EE178(char *, char *, float);
    extern float func_2EE238(char *);
    extern float func_2EE710(float);
    extern void func_31DE50(char *, float, char *, float, float, float, int);
    extern Rac2Native_003ECB38_ConstBlock D_00189E20;

    char buf1[0x10];
    char buf2[0x10];
    float zero;
    float angle;
    float denom;
    float r1;

    zero = 0.0f;

    func_2EE138(buf1, rec, obj + 0x10);

    r1 = func_2EE1F8(buf1, D_00189E20.tbl + 0xE0);
    func_2EE178(buf2, D_00189E20.tbl + 0xE0, r1);
    func_2EE138(buf1, buf1, buf2);

    angle = func_2EE1F8(buf1, D_00189E20.tbl + 0xC0);
    denom = func_2EE238(buf1);
    if (denom == zero)
        return;
    angle = 1.57079637050628662f - func_2EE710(angle / denom);
    if (func_2EE1F8(buf1, D_00189E20.tbl + 0xD0) < zero)
        angle = -angle;

    func_31DE50(obj + 0xF8, angle, mob, fa, fb, fc, 0);
}

extern Rac2Native_003ECB38_ConstBlock D_00189E20;

void func_L00_003ECC90(char *a, int b)
{
    int done = 0;
    int i;
    char *pa;
    int bv;

    i = 0;
    pa = a;
    bv = b;
    do {
        if (bv == 0xB02) {
            if (func_L00_003D3DE0(D_00189E20.tbl, pa) != 0)
                done = 1;
        } else {
            if (func_L00_003EB610(D_00189E20.tbl, pa) != 0)
                done = 1;
        }
    } while (++i < 4);
    if (done != 0)
        return;
    func_L00_0035F180((char *)(*(int *)(*(int *)(D_L00_001D9F00 + *(unsigned char *)(D_L00_001DA860 + bv) * 4) + 0x28) + 0xC0),
                      0, 0, (char *)D_00189EA0, 0x400);
}



/* func_L00_003ED198 is defined in L00_003EA0E0-seeker.c. */


extern void func_00282CF0(char *local, char *first, char *second);

extern float func_00283248(float a, float b);

extern void func_00282D30(char *dst, char *src, float scale);

extern float func_002A7878(float a, float b);

extern float func_002A78D8(float a, float b);

extern int func_00283CF0(float f);

extern float func_00283CE0(int v);

extern float func_00283B98(float a, float b);

extern void func_002AF000(float *p, float a, float b, float c);

extern char *func_002BDCE8(char *p, float fa, float fb, float fc, float fd, int v, char *local,
                            unsigned int color, int flag);

extern void func_002C16C0(float *out, float *dir, int a, int b, unsigned int color, int id,
                           float fa, float fb, float fc, float fd, float fe);

extern char D_L00_001B8DC0[];

extern char D_0018A0E0[];

/* Twenty times over: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   scale the hero facing direction by a random small amount, spawn a particle at the point
   jittered by a random amount on each axis and fill the new record's fields, then spawn a
   second particle along a random direction with a random magnitude; the original game role
   is unknown. */
void func_L00_003EDB98(float *p)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float scale;
    float mag;
    float angle;
    float f;
    int id;
    int i;
    char *r;
    char *q;

    func_00282CF0((char *)v, D_L00_001B8DC0, (char *)p);
    ang = func_00283248(v[0], v[1]);

    for (i = 19; i >= 0; i--) {
        f = func_002A7878(0.2f, 3.0f);
        func_00282D30((char *)dir, D_0018A0E0, -(f * 0.01666666753590107f));
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        f = func_002A7878(0.3f, 0.75f) * 210000.0f;
        out[0] = p[0] + func_002A78D8(0.0f, 0.2f);
        out[1] = p[1] + func_002A78D8(0.0f, 0.2f);
        out[2] = p[2] + func_002A78D8(0.0f, 0.2f);
        r = func_002BDCE8((char *)out, 0.0f, 1.0f, 1.01f, f, id, (char *)dir, 0x7F202020, 1);
        if (r != 0) {
            q = r + 32;
            *(unsigned char *)(r + 3) = 0x44;
            *(short *)(r + 10) = 0x5A;
            *(unsigned char *)(r + 9) = func_00283CF0(4.0f) + 0x40;
            *(float *)(q + 0x1C) = func_00283CE0(5);
            *(int *)(q + 4) = 3;
            *(unsigned char *)(q + 0xA) = 0x30;
            *(unsigned char *)(q + 0xB) = *(unsigned char *)(r + 10);
        }
        scale = func_002A7878(1.0f, 2.0f);
        mag = func_002A7878(0.0f, 1.396263599395752f);
        angle = func_00283B98(ang, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.01666666753590107f, angle, mag);
        out[0] = p[0] + func_002A78D8(0.0f, 0.1f);
        out[1] = p[1] + func_002A78D8(0.0f, 0.1f);
        out[2] = p[2] + func_002A78D8(0.0f, 0.1f);
        func_002C16C0(out, dir, 30, 127, 0x007F7F7F, id,
                      func_002A7878(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}

/* Twenty rounds: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   build a direction from a random step and a random magnitude, jitter the point by a
   random small amount on each axis and hand the result to the spawn helper with
   210000.0f, 500.0f, 1.0f, 0.0f and 1.0f; the original game role is unknown. */
void func_L00_003EDEE0(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float angle;
    float scale;
    float mag;
    float speed;
    int id;
    int i;

    func_00282CF0((char *)v, D_L00_001B8DC0, (char *)pos);
    ang = func_00283248(v[0], v[1]);

    for (i = 19; i >= 0; i--) {
        scale = func_002A7878(0.5f, 1.0f);
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        func_002A7878(0.05f, 0.2f);
        speed = 210000.0f;
        mag = func_002A7878(0.0f, 1.396263599395752f);
        angle = func_00283B98(ang, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.01666666753590107f, angle, mag);
        out[0] = pos[0] + func_002A78D8(0.0f, 0.1f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.1f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.1f);
        func_002C16C0(out, dir, 30, 127, 0x007F7F7F, id,
                      func_002A7878(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}
