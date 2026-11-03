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
