#include "common.h"
#include "include_asm.h"

extern int D_L00_001AFDA0 __attribute__((sda));

/* Reads the small counter in the shared data area and reports whether it equals two. */
int func_L00_003BB5F0(void)
{
    return D_L00_001AFDA0 == 2;
}

extern char D_L00_0023DDA0[] __attribute__((nosda));

extern char D_L00_0023F060[] __attribute__((nosda));

/* Clears one word of each of the thirty 0xA0-byte records that start at D_L00_0023DDA0,
   then one word of each of the sixteen 0xB0-byte records at D_L00_0023F060, walking down
   from the last record of each table, and finally the shared flag word. */
void func_L00_003BB600(void)
{
    char *base;
    char *p;
    int i;

    base = D_L00_0023DDA0;
    p = base + (0x1D * 0xA0 + 0x8C);
    i = 0x1D;
    do {
        *(int *)p = 0;
        i--;
        p -= 0xA0;
    } while (i >= 0);

    base = D_L00_0023F060;
    p = base + (0xF * 0xB0 + 0xA0);
    i = 0xF;
    do {
        *(int *)p = 0;
        i--;
        p -= 0xB0;
    } while (i >= 0);

    D_L00_001AFDA0 = 0;
}

extern int D_L04_001A8F00;

extern int D_L00_001AFF44 __attribute__((sda));

extern int D_L00_001AFF98 __attribute__((sda));

/* Clears the shared flag word this file's small-data area holds at 0x1AFF98. */
void func_L00_003C58E0(void)
{
    D_L00_001AFF98 = 0;
}

extern char D_0018C0B0[];

extern float func_L00_0037E668(void);

extern int func_L00_003C5B18(float f12);

extern void func_0029FCC0(char *a, int b, char *c);

extern void func_L00_003C48D0(char *p);

extern void func_L00_003C4B98(char *p);

extern void func_L00_003C4F78(char *p);

/* Gate followed by a fixed sequence of four bound helpers on the state record at offset 0x68. */
void func_L00_003C4850(char *p)
{
    char *q;

    if (D_L04_001A8F00 != 0)
        return;
    q = *(char **)(p + 0x68);
    if (func_L00_003C5B18(func_L00_0037E668()) == 0)
        return;
    if (D_L00_001AFF44 == 0x28)
        return;
    func_0029FCC0(*(char **)D_0018C0B0, 0xA, q + 0x30);
    func_L00_003C48D0(p);
    func_L00_003C4B98(p);
    func_L00_003C4F78(p);
}


extern char D_00139568[];

typedef struct {
    char prefix[0x760];
    float vector[4];
    char pad770[0xBF8 - 0x770];
    int mode;
    char padBFC[0x24EC - 0xBFC];
    short state;
} Player37;
extern Player37 D_00189E20_13;

extern char D_L00_00262570[];

/* A float in the boot's small data: the sda attribute and this unit's -G8 make the
   reference to it $gp-relative, the way retail has it. */
extern float D_001AFF08 __attribute__((sda));

extern void func_00282F20(void *a0, void *a1, float f);

extern void func_L00_003C3920(char *a0, char *a1, void *a2);

extern void func_L00_0032A1A8(int a0, char *a1, void *a2, float f);

extern float func_00282DF0(void *a0);

extern void *func_L00_003A98E8(char *a0, void *a1, char *a2, int a3, float f12, float f13, float f14);

/* Scales a direction by the current class record's speed (per frame at 60 Hz), negated from the
   object's own vector in player state 1, re-reads the record's second value, applies the
   optional mode adjustment, then spawns through func_L00_003A98E8 and links the result back to
   the object. The two record lookups use separate locals: one reused pointer becomes a global
   pseudo and loses the first lookup's tie to the multiply's register. */
void func_L00_003C37C8(char *a0, char *a1)
{
    char scratch[16];
    char *ctx = *(char **)(a0 + 0x68);
    char *rec;
    char *rec2;
    float f20;
    float f21;
    float f0;
    float f14;
    int mode;
    void *v;

    rec = D_L00_00262570 + (unsigned char)D_00139568[0x19] * 0xE0;
    f0 = *(float *)(rec + 0x50);
    f20 = f0 * 0.016666667f;
    mode = D_00189E20_13.state;
    if (mode == 1)
        func_00282F20(scratch, a0 + 0xD0, -f20);
    else
        func_00282F20(scratch, D_00189E20_13.vector, f20);

    rec2 = D_L00_00262570 + (unsigned char)D_00139568[0x19] * 0xE0;
    f21 = *(float *)(rec2 + 0x70);
    func_L00_003C3920(a0, a1, scratch);

    mode = D_00189E20_13.mode;
    if (mode != 0)
        func_L00_0032A1A8(mode, a1, scratch, f20);

    f0 = func_00282DF0(scratch);
    f14 = D_001AFF08;
    v = func_L00_003A98E8(a1, scratch, a0, 0, f0, f21, f14);
    *(int *)ctx = (int)v;
    if (v != 0) {
        *(int *)((char *)v + 0xB8) = (int)a0;
    }
}

typedef struct { float f[4]; } __attribute__((aligned(16))) UiHistoryPoint;
extern int D_L00_001B2940[] MACRO_ADDR;
extern UiHistoryPoint D_L00_0023FB80[][20];
extern UiHistoryPoint D_L00_001B2900[] MACRO_ADDR;
extern float D_L00_001AFF4C __attribute__((sda));
extern int D_L00_001AFF50 __attribute__((sda));
extern int D_L00_001AFF54 __attribute__((sda));
extern int D_L00_001AFF58 __attribute__((sda));
extern float D_L00_001AFF5C __attribute__((sda));
extern float D_L00_001AFF60 __attribute__((sda));
extern char D_L00_001FE940[] __attribute__((nosda));
extern void func_00282CC0(void *, void *, void *);
/* The second integer-bank input is forwarded as the axis vector pointer. */
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
typedef struct {
    char prefix[8];
    int flags;
    char pad[0x24];
    UiHistoryPoint origin;
} UiTrailState;
typedef struct {
    unsigned char prefix[2];
    unsigned char texture;
    unsigned char flags;
    int color;
    int unused;
    float size;
} UiTrailParticle;
extern UiTrailParticle *func_002C36D0(void *, int, int, int);
extern void ref_L00_003C4F78_00(void *, int, int, int, int, int, int, int,
                              int, int, int, float, float, float);

/* Ages the four trail histories (20 points each), turns and clamps each head point, builds the
   vertex strip around the owner's origin and spawns two particles at the tip. The point address
   is formed in its own group so the copy source keeps its own D - 16 base. */
void func_L00_003C4F78(char *owner)
{
    UiHistoryPoint vertices[20], origin, change;
    UiTrailState *state = *(UiTrailState **)(owner + 0x68);
    int i;
    qcopy(&origin, &state->origin);
    for (i = 0; i < 4; i++) {
        int last, j;
        UiHistoryPoint *head, *tip;
        float length, limit;
        UiTrailParticle *effect;
        D_L00_001B2940[i]++;
        if (D_L00_001B2940[i] >= 20)
            D_L00_001B2940[i] = 20;
        last = D_L00_001B2940[i] - 1;
        for (j = last; j > 0; j--) {
            int index = last - j;
            UiHistoryPoint *dst;
            do { dst = &D_L00_0023FB80[0][j]; dst += i * 20; } while (0);
            qcopy(dst, &D_L00_0023FB80[i][j - 1]);
            func_00282CC0(&vertices[index], &origin, dst);
            vertices[index].f[3] = 0.05f;
        }
        head = &D_L00_0023FB80[i][0];
        func_002AB668(&change, &D_L00_001B2900[i], 0.10471976548433304f);
        func_002ACDE8(head, head, &change);
        func_002ACB48(head->f, 0.025f);
        length = func_00282DF0(head);
        limit = D_L00_001AFF4C * 1.1f;
        if (length > limit)
            func_00282D30(head, head, limit / length);
        else {
            limit = D_L00_001AFF4C * 0.9f;
            if (length < limit)
                func_00282D30(head, head, limit / length);
        }
        func_00282CC0(&vertices[last], &origin, &D_L00_0023FB80[i][0]);
        vertices[last].f[3] = 0.05f;
        {
            int endpoint = D_L00_001B2940[i] - 1;
            tip = vertices + endpoint;
        }
        effect = func_002C36D0(tip, 2, 0, 1);
        if (effect != 0) {
            char *tables = D_L00_001FE940;
            effect->color = D_L00_001AFF50 | state->flags;
            effect->size = D_L00_001AFF5C * 210000.0f;
            effect->texture = (*(char **)(tables + 0xF8))[1];
        }
        effect = func_002C36D0(tip, 2, 0, 1);
        if (effect != 0) {
            effect->color = 0x407F7F7F;
            effect->size = D_L00_001AFF5C * 31500.001953125f;
        }
        ref_L00_003C4F78_00(vertices, 20, 14, 14,
                          D_L00_001AFF54, D_L00_001AFF54 & 0xFFFFFF,
                          D_L00_001AFF58 | state->flags, D_L00_001AFF58,
                          0, D_L00_001B2940[i] - 1, D_L00_001B2940[i],
                          0.02f, 0.07f, D_L00_001AFF60);
    }
}
