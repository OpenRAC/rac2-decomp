/* func_L20_004441D8, 1744 bytes. USA v1.01, -O2 -G8 -ffunction-sections -frac2-zero-ti-por:
 * 1720/1744 bytes, opcodes mostly aligned, most rows register names. The two group loops have no
 * hoisted constants in retail, so they are written with labels; that alone took 325 rows to 167.
 * Left: the record is in $s3 in retail, $s4 here (0x1232 takes $s3), the group index needs $a0 (here
 * $a1, sched1 sets the copy before the address add), and the last two particle loops are not yet
 * compared. Try those next; 24 bytes are still missing from them.
 */
#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { char pad[0x18]; float z; } Moby;
extern s16 **D_L20_001A9014;
extern s16 *D_L20_001FBB20[];
extern char *D_L20_001B3614, *D_L20_001B2F9C, *D_L20_001B308C;
extern u32 D_L20_001B2FA0;
extern s32 D_L20_001B2FB8 __attribute__((sda)), D_L20_001B220C __attribute__((sda)), D_L20_001B2248 __attribute__((sda));
extern s32 D_L20_001B2210 __attribute__((sda)), D_L20_001B222C __attribute__((sda)), D_L20_001B2230 __attribute__((sda));
extern s32 D_L20_001B2214, D_L20_001B2218, D_L20_001B221C, D_L20_001B2234, D_L20_001B2238;
extern float D_L20_001B2240 __attribute__((sda)), D_L20_001B2244, D_L20_001B2250 __attribute__((sda)), D_L20_001B2254;
extern float D_L20_001B2BE8 __attribute__((sda));
extern float D_L20_001B3230[] __attribute__((sda));
extern s32 D_0018C0B0[];
extern char D_L20_001A8F20[];
extern void func_002E5CF8(int, int, void *);
extern float func_00282C48(float);
extern void func_0029F338(void *);
extern char *func_002AB1F0(void *);
extern void func_002A8F70(void *, int, int, void *, void *, float);
extern float func_002A89A8(void *, int, float);
extern void func_00282C90(void *), func_00282C88(void *);
extern float func_002A7878(float, float), func_002A7940(void);
extern void func_002830C0(void *, void *, void *);
extern int func_00283D38(int, int, float);
extern int func_002A77E0(int), func_002A7820(int, int);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern char *func_L20_00448A18(char *, char *, char *, char *);

#define I(p, o) (*(s32 *)((char *)(p) + (o)))
#define U(p, o) (*(u16 *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))

void func_L20_004441D8(char *obj)
{
    Vec pos, a, b;
    char *s;
    float base;
    int i;

    func_002E5CF8(0x11, 0, obj);
    s = *(char **)(obj + 0x68);
    {
        s32 *groups = (s32 *)(s + 0x224);
        s16 *p = D_L20_001A9014[*(groups + I(s, 0x1858))];

        if (p != 0) {
            do {
                char *e = D_L20_001B3614 + ((*p & 0x7FFF) << 5);

                if (e == 0)
                    break;
                p++;
                B(e, 0x1E) |= 4;
                if (p == 0)
                    break;
            } while (p[-1] >= 0 || p == D_L20_001A9014[groups[I(s, 0x1858)]]);
        }
    }
    I(s, 0x1858)++;
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

        p = D_L20_001FBB20[I(s, 0x21C)];
        g = I(s, 0x21C);

        goto test1;
    body1:
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
                func_002A8F70(m, D_0018C0B0[0], 0x10000, m + 0x10, D_L20_001A8F20, size);
            }
        }
    next1:
        g = I(s, 0x21C);
        p++;
    test1:
        if ((g & 0xFF) == 0xFF || g > D_L20_001B2FB8 || p == 0)
            goto end1;
        if (p[-1] >= 0 || p == D_L20_001FBB20[g])
            goto body1;
    end1:;
    }
    {
        s16 *p;
        float size = 0.0f;
        int g;

        p = D_L20_001FBB20[I(s, 0x23C)];
        g = I(s, 0x23C);

        goto test2;
    body2:
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
                func_002A8F70(m, D_0018C0B0[0], 0x10000, m + 0x10, D_L20_001A8F20, size);
            }
        }
    next2:
        g = I(s, 0x23C);
        p++;
    test2:
        if ((g & 0xFF) == 0xFF || g > D_L20_001B2FB8 || p == 0)
            goto end2;
        if (p[-1] >= 0 || p == D_L20_001FBB20[g])
            goto body2;
    end2:;
    }
    D_L20_001B2BE8 = func_002A89A8(obj + 0x10, 0, 0.5f) - 2.0f;
    base = ((Moby *)obj)->z - 0.5f;
    for (i = 0; i < D_L20_001B220C; i++) {
        int c1, c2, life;
        float w;

        func_00282C90(pos);
        pos[0] = func_002A7878(-1.0f, 1.0f);
        pos[1] = func_002A7878(-1.0f, 1.0f);
        func_002830C0(pos, pos, D_L20_001B308C + (I(s, 0x230) << 7));
        pos[2] = base + func_002A7878(-0.5f, 0.5f);
        c1 = func_00283D38(D_L20_001B2210, D_L20_001B2214, func_002A7878(0.0f, 1.0f));
        c2 = func_00283D38(D_L20_001B2218, D_L20_001B221C, func_002A7878(0.0f, 1.0f));
        w = D_L20_001B3230[func_002A77E0(2)];
        func_00282C88(a);
        a[3] = w;
        func_00282C88(b);
        b[3] = w;
        b[2] = func_002A7878(D_L20_001B2240, D_L20_001B2244) * 0.016666668f;
        life = func_002A7820(1, D_L20_001B2230);
        func_002BAA28(pos, a, b, c1, c2, life, func_002A7820(D_L20_001B2234, D_L20_001B2238), 60, D_L20_001B222C);
    }
    for (i = 0; i < D_L20_001B2248; i++) {
        func_00282C90(pos);
        pos[0] = func_002A7878(-1.0f, 1.0f);
        pos[1] = func_002A7878(-1.0f, 1.0f);
        func_002830C0(pos, pos, D_L20_001B308C + (I(s, 0x230) << 7));
        pos[2] = base + func_002A7878(-0.5f, 0.5f);
        qzero(a);
        a[2] = func_002A7940();
        qzero(b);
        b[2] = func_002A7878(D_L20_001B2250, D_L20_001B2254) * 0.016666668f;
        func_L20_00448A18(obj, (char *)pos, (char *)a, (char *)b);
    }
}
