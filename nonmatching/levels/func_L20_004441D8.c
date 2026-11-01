/* func_L20_004441D8, 1744 bytes. USA v1.01, -O2 -G8 -ffunction-sections -frac2-zero-ti-por:
 * 1740/1744 bytes, opcodes aligned to the end. The group loops are real do/while loops entered by a
 * goto into the middle: that keeps the loop note and alignment nop, and loop.c refuses to hoist
 * because of the entry, which is why retail has no hoisted constants. Left:
 * - j++ in the last loop: reorg's forward scan from the third call there finds it past both qzero
 *   asms and a call and takes the slot; retail keeps the nop and j++ fills the last jal. So retail's
 *   forward search stops at a volatile asm, like redundant_insn's (3d046c95). Unproven: test with a
 *   private cc1 before believing it. Accounts for the missing word.
 * - the group index is $a1 here, $a0 in retail: sched1 sets the copy before the address add.
 * - t2 for func_002BAA28 is set before a3 here, after t1 in retail.
 */
#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { char pad[0x18]; float z; } Moby;
extern s16 **D_L20_001A9014;
extern s16 *D_L20_001FBB20[];
extern char *D_L20_001B3614, *D_L20_001B2F9C, *D_L20_001B308C;
extern u32 D_L20_001B2FA0;
extern s32 D_L20_001B2FB8 __attribute__((sda)), D_L20_001B220C __attribute__((sda)), D_L20_001B2248 __attribute__((sda));
extern s32 D_L20_001B222C __attribute__((sda));
extern s32 D_L20_001B2210[] __attribute__((sda)), D_L20_001B2230[] __attribute__((sda));
extern float D_L20_001B2240[] __attribute__((sda)), D_L20_001B2250[] __attribute__((sda));
extern s32 D_L20_001B2210_gp SDATA(D_L20_001B2210), D_L20_001B2230_gp SDATA(D_L20_001B2230);
extern float D_L20_001B2240_gp SDATA(D_L20_001B2240), D_L20_001B2250_gp SDATA(D_L20_001B2250);
extern float D_L20_001B2BE8 __attribute__((sda));
extern float D_L20_001B2220[2] __attribute__((sda));
extern s32 D_0018C0B0[];
extern char D_L20_001A8F20[];
extern void func_002E5CF8(int, int, void *);
extern float func_00282C48(float);
extern void func_0029F338(void *);
extern char *func_002AB1F0(void *);
extern void func_002A8F70(void *, int, int, float, void *, void *);
extern float func_002A89A8(void *, int, float);
extern void func_00282C90(void *), func_00282C88(void *);
extern float func_002A7878(float, float), func_002A7940(void);
extern void func_002830C0(void *, void *, void *);
extern int func_00283D38(int, int, float);
extern int func_002A77E0(int), func_002A7820(int, int);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern char *func_L20_00448A18(char *, char *, char *, char *);

typedef struct { char pad[0x21C]; int g1; int pad220; int groups[3]; int f230; int pad234[2]; int g2; char pad240[0x1858-0x240]; int current; } State;
#define I(p, o) (*(s32 *)((char *)(p) + (o)))
#define U(p, o) (*(u16 *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))

void func_L20_004441D8(char *obj)
{
    Vec pos, a, b;
    State *s;
    float base;
    int i, j;

    func_002E5CF8(0x11, 0, obj);
    s = *(State **)(obj + 0x68);
    {
        int idx = s->groups[s->current];
        s16 *p = D_L20_001A9014[idx];

        if (p != 0) {
            do {
                char *e = D_L20_001B3614 + ((*p & 0x7FFF) << 5);

                if (e == 0)
                    break;
                p++;
                B(e, 0x1E) |= 4;
                if (p == 0)
                    break;
            } while (p[-1] >= 0 || p == D_L20_001A9014[s->groups[s->current]]);
        }
    }
    s->current++;
    {
    char *m;
    for (m = D_L20_001B2F9C; (u32)m <= D_L20_001B2FA0 && B(m, 0x20) != 0xFF; m += 0x100) {
        u16 id = U(m, 0xAA);

        if (id == 0x1233 || id == 0x1234 || (s16)id == 0x1231 || (s16)id == 0x1232 || (s16)id == 0x1357) {
            if (func_00282C48(((Moby *)obj)->z - ((Moby *)m)->z) < 10.0f)
                func_0029F338(m);
        }
    }
    }
    {
        s16 *p;
        float size = 0.0f;
        int g;

        p = D_L20_001FBB20[s->g1];
        goto test1;
        do {
            {
            char *m = D_L20_001B2F9C + ((*p & 0x7FFF) << 8);

            if (m == 0)
                goto end1;
            if ((U(m, 0x34) ^ 1) & 1) {
                if (size == 0.0f) {
                    char *c = func_002AB1F0(m);

                    if (c == 0)
                        goto next1;
                    size = *(s16 *)(c + 4) * 0.25f;
                }
                func_002A8F70(m, D_0018C0B0[0], 0x10000, size, m + 0x10, D_L20_001A8F20);
            }
        }
    next1:
        p++;
    test1:
            g = s->g1;
            if ((g & 0xFF) == 0xFF || g > D_L20_001B2FB8 || p == 0)
                goto end1;
        } while (p[-1] >= 0 || p == D_L20_001FBB20[g]);
    end1:;
    }
    {
        s16 *p;
        float size = 0.0f;
        int g;

        p = D_L20_001FBB20[s->g2];
        goto test2;
        do {
            {
            char *m = D_L20_001B2F9C + ((*p & 0x7FFF) << 8);

            if (m == 0)
                goto end2;
            if ((U(m, 0x34) ^ 1) & 1) {
                if (size == 0.0f) {
                    char *c = func_002AB1F0(m);

                    if (c == 0)
                        goto next2;
                    size = *(s16 *)(c + 4) * 0.25f;
                }
                func_002A8F70(m, D_0018C0B0[0], 0x10000, size, m + 0x10, D_L20_001A8F20);
            }
        }
    next2:
        p++;
    test2:
            g = s->g2;
            if ((g & 0xFF) == 0xFF || g > D_L20_001B2FB8 || p == 0)
                goto end2;
        } while (p[-1] >= 0 || p == D_L20_001FBB20[g]);
    end2:;
    }
    D_L20_001B2BE8 = func_002A89A8(obj + 0x10, 0, 0.5f) - 2.0f;
    base = ((Moby *)obj)->z - 0.5f;
    for (i = 0; i < D_L20_001B220C; i++) {
        int c1, c2, life, fade;
        float w;

        func_00282C90(pos);
        pos[0] = func_002A7878(-1.0f, 1.0f);
        pos[1] = func_002A7878(-1.0f, 1.0f);
        func_002830C0(pos, pos, D_L20_001B308C + (s->f230 << 7));
        pos[2] = base + func_002A7878(-0.5f, 0.5f);
        c1 = func_00283D38(D_L20_001B2210_gp, D_L20_001B2210[1], func_002A7878(0.0f, 1.0f));
        c2 = func_00283D38(D_L20_001B2210[2], D_L20_001B2210[3], func_002A7878(0.0f, 1.0f));
        w = D_L20_001B2220[func_002A77E0(2)];
        func_00282C88(a);
        a[3] = w;
        func_00282C88(b);
        b[3] = w;
        b[2] = func_002A7878(D_L20_001B2240_gp, D_L20_001B2240[1]) * 0.016666668f;
        life = func_002A7820(1, D_L20_001B2230_gp);
        fade = func_002A7820(D_L20_001B2230[1], D_L20_001B2230[2]);
        func_002BAA28(pos, a, b, c1, c2, life, fade, 60, D_L20_001B222C);
    }
    for (j = 0; j < D_L20_001B2248; j++) {
        func_00282C90(pos);
        pos[0] = func_002A7878(-1.0f, 1.0f);
        pos[1] = func_002A7878(-1.0f, 1.0f);
        func_002830C0(pos, pos, D_L20_001B308C + (s->f230 << 7));
        pos[2] = base + func_002A7878(-0.5f, 0.5f);
        qzero_nc(a);
        a[2] = func_002A7940();
        qzero_nc(b);
        b[2] = func_002A7878(D_L20_001B2250_gp, D_L20_001B2250[1]) * 0.016666668f;
        func_L20_00448A18(obj, (char *)pos, (char *)a, (char *)b);
    }
}
