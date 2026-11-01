/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Retained complete C reconstruction; not linked or counted.
 * Tier: Claude Opus 5.5 xhigh (v1979), 1 November 2026. Replaces the GPT-6.1 Sol draft
 * (frame 0x80, -G16), which this one is closer than.
 * Profile: -O2 -G8 -ffunction-sections (name the unit *-g8.c; no cflags line needed).
 * Best check.py: 2292/2292 bytes, 0/1 USA v1.01 places, "instruction at +0x5b4 differs";
 * 573 instructions against 573, of which 2 differ.
 *
 * What differs: +0x5B4 and +0x5B8 are swapped. Retail is sw $v0,0x88($s1) then
 * swc1 $f3,0x60($s1); this draft is the reverse.
 * Why: source order f5C, flags88, f60, f80 gives the retail store order, but then
 * local-alloc gives 0.4 $f3 and 1.5708 $f7, where retail has the opposite (5 instructions
 * differ, at 17D20, 17D40, 17DA8, 17DB0, 17DBC). This draft uses f5C, f60, flags88, f80.
 * local-alloc model, tested by that swap: qty priority is
 * floor_log2(refs) * refs / (death - birth), first fit. Retail needs r(1.5708) above
 * r(0.4) above r(1.55), so 1.5708 takes $f3 (health in $f3 is dead by then), and 0.4,
 * which is live with $f3..$f6, takes $f7. With refs 2, 3, 2 that needs a shorter life for
 * 1.5708 than for 1.55, so sched1 needs one more insn between stores 0x60 and 0x80 that
 * emits no code; otherwise sw 0x88 needs one more INSN_DEPEND in sched2 under the current
 * source order. Neither was found.
 *
 * NOT ACCEPTABLE AS IT STANDS, even with exact bytes: "Quad v[10]" produces retail's frame
 * 0x100 and keeps origin and point at SP+0 and SP+0x10, but v[2..9] are never used. No
 * retail access or callee was seen touching SP+0x20..0x9F, so this is padding that the
 * guide forbids unless a real use is found for that storage.
 *
 * Forms that were needed, and need review:
 * - D_L23_001B3820 as int[2], stored [1] then [0]: gives the retail first block (store,
 *   addiu $a1,1, store, sw $a1). Two plain ints put the addiu first. The higher priority
 *   of the array stores is inferred from the result, not read from a priority dump.
 * - if (D_L23_001B279C < D_L23_001B27A0) { for (; &D_L23_001B279C[i] < D_L23_001B27A0; i++)
 *   ... }: a real runtime test that repeats the for's first test. cse_set_around_loop
 *   merges the loop-top load only for a REG_LOOP_TEST_P table register, which only
 *   duplicate_loop_exit_test sets; the guard supplies the load.
 * - i = 0 before the stores, a fresh counter for the tail parts loop (a shared counter
 *   leaves a final value that CSE reuses for game->f1E0 = 10).
 * - f58 before f5C, f5D0 before f5C8, QI/HI 255 with colour first: sched1 ties go by
 *   priority, then REG_DEAD/set weight, then LUID.
 * Tried and rejected: -fstrict-aliasing (2284 bytes, hoists first-block loads);
 * extern const bounds (hoists the tail's D_27A0 load); func_002B60B0 returning int (moves
 * sw 0x88 into the call's delay slot); dead default stores to raise 1.5708's refs (not
 * compiled: by the priority figures it would land in $f0).
 * Release checks for us2/pal were not run. Required declarations follow.
 */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));

typedef struct L23Class {
    char pad00[0x24];
    float scale;
} L23Class;

typedef struct L23Boss L23Boss;

typedef struct L23Moby {
    char pad00[0x10];
    Quad pos;
    unsigned char mode;
    char pad21[3];
    L23Class *cls;
    struct L23Moby *next;
    float scale;
    unsigned char alpha;
    char pad31;
    short colour;
    unsigned short flags;
    char pad36[0x68 - 0x36];
    void *vars;
    char pad6C[0x7C - 0x6C];
    short timer;
    char pad7E[0xAA - 0x7E];
    short kind;
    char padAC[0xC0 - 0xAC];
    Quad rot;
    char padD0[0x100 - 0xD0];
} L23Moby;

typedef struct L23Tint {
    char pad00[8];
    signed char r;
    char pad09;
    signed char g;
    char pad0B;
    signed char b;
} L23Tint;

struct L23Boss {
    char pad000[0x20];
    float health;
    short maxHealth;
    char pad026[0x50 - 0x26];
    float f50, f54, f58, f5C, f60;
    char pad064[0x80 - 0x64];
    float f80, f84;
    int flags88;
    char pad08C[0x150 - 0x8C];
    unsigned char b150;
    char pad151[0x170 - 0x151];
    float f170, f174;
    char pad178[4];
    float f17C;
    char pad180[8];
    int i188;
    char pad18C[0x1B7 - 0x18C];
    unsigned char b1B7;
    char pad1B8[0x230 - 0x1B8];
    int t230[(0x2F4 - 0x230) / 4];
    short pad2F4;
    short h2F6;
    char pad2F8[0x308 - 0x2F8];
    float f308, f30C, f310, f314;
    char pad318[4];
    int i31C;
    float f320, f324, f328, f32C, f330;
    short h334, h336, h338;
    char pad33A[0x358 - 0x33A];
    L23Moby *parts[10];
    char pad380[0x390 - 0x380];
    short h390;
    char pad392[6];
    short h398, h39A, h39C, h39E;
    char pad3A0[0x408 - 0x3A0];
    int i408;
    char pad40C[4];
    Quad m410[(0x570 - 0x410) / 16];
    char pad570[8];
    int i578;
    float f57C;
    char pad580[8];
    float f588;
    char pad58C[4];
    int i590, i594;
    char pad598[4];
    int i59C;
    char pad5A0[0x5B0 - 0x5A0];
    int i5B0;
    char pad5B4[0x5C4 - 0x5B4];
    int i5C4;
    float f5C8;
    int i5CC;
    float f5D0;
    char pad5D4[4];
    int i5D8;
    char pad5DC[0x608 - 0x5DC];
    int i608, i60C;
    L23Moby *m610, *m614;
    char pad618[8];
    L23Moby *m620, *m624;
};

typedef struct {
    char pad0[0x1E0];
    short f1E0;
    char pad1E2[0x1870 - 0x1E2];
    char f1870[0xC];
    int f187C;
    char pad1880[0x2290 - 0x1880];
    void *f2290;
    int f2294;
} L23Game;
typedef struct {
    char pad0[0x1A4];
    unsigned int f1A4;
} L23Pad;
extern int D_L23_001B3820[2];
extern int D_L23_001B1424 __attribute__((sda));
extern int D_L23_001B13EC __attribute__((sda));
extern int D_L23_001B3718;
extern int D_L23_001B3714;
extern int D_L23_001B16A0 __attribute__((sda));
extern int D_L23_001B16A4 __attribute__((sda));
extern int D_L23_001B16A8 __attribute__((sda));
extern int D_L23_001B1694 __attribute__((sda));
extern int D_L23_001B3780;
extern int D_L23_001B1434 __attribute__((sda));
extern int D_L23_001B36F0;
extern float D_L23_001B36F4;
extern float D_L23_001B36F8;
extern float D_L23_001B3700;
extern float D_L23_001B3704 __attribute__((sda));
extern int D_L23_001B1650 __attribute__((sda));
extern float D_L23_001B3708;
extern float D_L23_001B370C;
extern int D_L23_001B3758;
extern int D_L23_001B36B0;
extern float D_L23_001B1490 __attribute__((sda));
extern int D_L23_001B374C;
extern int D_L23_001B3754;
extern int D_L23_001B3894;
extern int D_L23_001B3890;
extern int D_L23_001B36AC __attribute__((sda));
extern float D_L23_001B36A4;
extern float D_L23_001B14D0 __attribute__((sda));
extern float D_L23_001B36FC;
extern float D_L23_001B13C8;
extern float D_L23_001B13CC;
extern int D_L23_001B38C0;
extern int D_L23_001B166C __attribute__((sda));
extern float D_L23_001B14C4 __attribute__((sda));
extern float D_L23_001B1470 __attribute__((sda));
extern int D_L23_001B14A0 __attribute__((sda));
extern int D_L23_001B3748 MACRO_ADDR;
extern L23Moby *D_L23_001B1484 __attribute__((sda));
extern L23Moby *D_L23_001B14FC __attribute__((sda));
extern L23Moby *D_L23_001B13D0 __attribute__((sda));
extern L23Moby *D_L23_001B279C, *D_L23_001B27A0, *D_L23_001B27A8;
extern int *D_L23_001B36A8;
extern L23Moby *D_L23_001B3790[4] MACRO_ADDR;
extern int D_L23_001B17C0[4] MACRO_ADDR;
extern int D_L23_001B1658[4] SDATA(D_L23_001B1658);
extern Quad D_L23_001B13F0 SDATA(D_L23_001B13F0);
extern Quad D_L23_001B3760, D_L23_001B3770;
extern int D_L23_00259320[8][3];
extern L23Moby *D_L23_00259380[8][3];
extern Quad D_L23_002593E0[8][3];
extern L23Moby *D_L23_00259560[];
extern unsigned char D_L23_002595C8[0xFE0];
extern unsigned char D_00189E20[];
extern unsigned char D_00138180[];
extern int func_00282948(int *);
extern void func_001163A0(unsigned int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_L23_00418650(void *, float);
extern void func_002B60B0(L23Moby *, float, float, float, float);
extern void func_002A7750(L23Moby *, int, int);
extern void *func_00115484(void *, int, unsigned int);
extern void func_L23_004196B8(L23Moby *);
extern void func_L23_0041CA58(L23Moby *);
extern void func_L23_00419970(L23Moby *);
extern void func_0029B758(int, int);
extern int func_L23_0041B478(void);
extern int func_L23_0041DA48(void);
extern void func_L00_002AF7D0(void);
extern void func_L00_00310C88(void *, void *);
extern int func_L22_002C9898(int, int);
extern int func_00288FB8(int);
extern int func_L00_0030DD70(int, int);
extern void func_002AFFD8(void *, void *, int);
extern void func_L00_00325600(void *, void *, void *);
extern void func_L23_0041B9F0(L23Moby *);

/* Initialize the encounter objects and refresh their shared presentation state. */
void func_L23_004177F8(L23Moby *object) {
    Quad v[10];
#define origin v[0]
#define point v[1]
    L23Boss *state = object->vars;
    L23Moby *entity;
    L23Moby *scan;
    int i, j, id, n, m, mode;
    float health;

    func_00282948(&D_L23_001B3748);
    if (object->mode == 0) {
        D_L23_001B3820[1] = 0;
        D_L23_001B3820[0] = 0;
        D_L23_001B1424 = 1;
        D_L23_001B13EC = 0;
        D_L23_001B3718 = 0;
        D_L23_001B3714 = 0;
        D_L23_001B16A0 = 0;
        D_L23_001B16A4 = 0;
        D_L23_001B16A8 = 0;
        D_L23_001B1694 = 0;
        D_L23_001B3780 = 0;
        D_L23_001B1434 = 0;
        state->m620 = 0;
        state->m624 = 0;
        D_L23_001B1650 = 1;
        D_L23_001B1484 = object;
        state->i60C = 0;
        D_L23_001B36F0 = state->i31C;
        D_L23_001B36F4 = state->f308;
        D_L23_001B36F8 = state->f30C;
        D_L23_001B3700 = state->f310;
        D_L23_001B3704 = state->f314;
        if (state->h334 > 8) state->h334 = 8;
        state->h336 = 2;
        D_L23_001B3708 = state->f330;
        D_L23_001B370C = (float)state->h338;
        D_L23_001B3758 = 0;
        D_L23_001B36B0 = 0;
        state->i608 = 0;
        state->f5D0 = D_L23_001B1490;
        state->f5C8 = D_L23_001B1490;
        state->i5CC = 0;
        state->i5D8 = 0;
        state->i5B0 = 0;
        state->i5C4 = 0;
        state->i594 = 0;
        state->i590 = 0;
        state->i59C = 0;
        D_L23_001B36A8 = state->t230;
        state->b1B7 = 1;
        func_001163A0(*(volatile unsigned int *)0x10000800);
        D_L23_001B374C = -1;
        D_L23_001B3754 = 0;
        state->i408 = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                qzero(&origin);
                D_L23_00259320[i][j] = 0;
                D_L23_00259380[i][j] = 0;
                qcopy(&D_L23_002593E0[i][j], &origin);
            }
        }
        for (i = 0; i < 4; i++) D_L23_001B3790[i] = 0;
        i = 0;
        D_L23_001B3894 = 0;
        D_L23_001B3890 = 0;
        state->f57C = 0.098174773f;
        state->i578 = 0;
        D_L23_001B36AC = 0;
        n = 0;
        m = 0;
        if (D_L23_001B279C < D_L23_001B27A0) {
        for (; &D_L23_001B279C[i] < D_L23_001B27A0; i++) {
                entity = &D_L23_001B279C[i];
                id = entity->kind;
                if (id == 0x7E5) {
                    D_L23_00259560[n++] = entity;
                } else if (id == 0x27D) {
                    qcopy(&origin, &entity->pos);
                    qcopy(D_00189E20 + 0x80, &entity->pos);
                } else if (id == 0xF7E) {
                    state->parts[m++] = entity;
                } else if (id == 0x120F) {
                    state->m610 = entity;
                } else if (id == 0x123C) {
                    state->m614 = entity;
                } else if (id == 0xF7F) {
                    D_L23_001B14FC = entity;
                } else if (id == 0xF6E) {
                    L23Tint *tint;
                    D_L23_001B13D0 = entity;
                    entity->alpha = 255;
                    tint = D_L23_001B13D0->vars;
                    tint->r = 0;
                    tint->g = 0;
                    tint->b = -1;
                }
        }
        }
        func_00282CF0(&origin, &origin, D_00189E20 + 0xB0);
        D_L23_001B36A4 = func_00282DF0(&origin);
        point = 0;
        ((float *)&point)[0] = 500.0f;
        ((float *)&point)[1] = 500.0f;
        ((float *)&point)[2] = 430.0f;
        func_L23_00418650(&point, 0.0f);
        qcopy(&D_L23_001B3760, &point);
        point = 0;
        ((float *)&point)[0] = 500.0f;
        ((float *)&point)[1] = 500.0f;
        ((float *)&point)[2] = 552.0f;
        func_L23_00418650(&point, 0.0f);
        qcopy(&D_L23_001B3770, &point);
        qcopy(&object->pos, &D_L23_001B13F0);
        func_L23_00418650(&object->pos, D_L23_001B14D0);
        object->colour = 255;
        object->alpha = 255;
        object->flags |= 0x100;
        health = (float)state->h2F6;
        state->f17C = 0.15f;
        state->health = health;
        state->maxHealth = state->h2F6;
        state->f170 = 0.5f;
        state->f174 = 0.5f;
        state->b150 = 20;
        state->i188 = -1;
        D_L23_001B36FC = health * state->f328;
        {
            float share = health * state->f320 * 0.2f;
            D_L23_001B13CC = share * 0.083333336f;
            D_L23_001B13C8 = share;
        }
        state->f32C = 1.0f - (state->f324 + state->f320 + state->f328);
        state->f84 = 0.5f;
        state->f58 = 0.4f;
        state->f54 = -7.0f;
        state->f50 = 7.0f;
        state->f5C = 0.4f;
        state->f60 = 1.57079649f;
        state->flags88 |= 5;
        state->f80 = 1.55334318f;
        func_002B60B0(object, 0.019444445f, 0.6333334f, 0.0017453295f, 0.20943955f);
        func_002A7750(object, 2, 0);
        func_00115484(D_L23_002595C8, 0, 0xFE0);
        state->h390 = 0;
        state->h39C = -1;
        state->h39A = -1;
        state->h398 = -1;
        state->h39E = 0;
        D_L23_001B38C0 = 4;
        {
            int *dst = D_L23_001B1658;
            int *src = D_L23_001B17C0;
            int left;
            for (left = 4; left != 0; left--) *dst++ = *src++;
        }
        D_L23_001B166C = 0;
        func_L23_004196B8(object);
        func_L23_0041CA58(object);
        state->f588 = D_L23_001B14C4;
        state->flags88 |= 16;
        object->timer = 15;
    } else {
        func_L23_00419970(object);
        mode = object->mode;
        if (mode != 4 && mode != 10 && mode != 11) {
            int part;
            for (part = 5; part < 10; part++) {
                if (state->parts[part]) state->parts[part]->flags |= 0x41;
            }
        }
        if (!state->m620) {
            for (scan = D_L23_001B27A8; scan; scan = scan->next) {
                if (scan->kind == 0x1252) {
                    state->m620 = scan;
                    break;
                }
            }
        }
        if (!state->m624) {
            for (scan = D_L23_001B27A8; scan; scan = scan->next) {
                if (scan->kind == 0x1251) {
                    state->m624 = scan;
                    break;
                }
            }
        }
    }
    func_0029B758((int)func_L23_0041B478, (int)func_L23_0041DA48);
    object->scale = object->cls->scale * D_L23_001B1470;
    {
        int part;
        for (part = 0; part < 10; part++) {
            if (state->parts[part]) state->parts[part]->scale = state->parts[part]->cls->scale * D_L23_001B1470;
        }
    }
    if (state->m610) state->m610->scale = state->m610->cls->scale * D_L23_001B1470;
    if (state->m614) state->m614->scale = state->m614->cls->scale * D_L23_001B1470;
    if (D_L23_001B1424) {
        L23Game *game = (L23Game *)D_00189E20;
        L23Pad *pad = (L23Pad *)D_00138180;
        D_L23_001B1424++;
        game->f1E0 = 10;
        state->h390 = 0;
        if (pad->f1A4 & 0x50) {
            D_L23_001B1424 = 0;
            func_002A7750(object, 1, 0);
            game->f1E0 = 20;
            pad->f1A4 = 0;
            D_L23_001B3748 = D_L23_001B14A0;
            func_L00_0030DD70(func_00288FB8(0x3157), -1);
        } else if (D_L23_001B1424 < 30) {
            game->f2294 = 0;
            func_L00_002AF7D0();
            func_L00_00310C88(game->f2290, game->f1870);
            game->f187C = 0;
            func_L22_002C9898(0, 1);
        }
    }
    func_002AFFD8(&object->pos, state->m410, 0);
    func_L00_00325600(&object->rot, state->m410, 0);
    if (object->mode != 7) func_L23_00418650(&object->pos, state->f588);
    func_L23_0041B9F0(object);
}
