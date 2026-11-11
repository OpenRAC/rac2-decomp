/* func_US2_L00_002D6258: the v2.00 copy of func_L00_002D5EB8 (src/levels/shared/L00_002D3798-g8.c).
 * The same C; only callees that are the release's own functions differ:
 * func_00288508 is func_US2_00288F30,
 * func_L00_0030C7F8 is func_US2_L00_0030D9F8,
 * func_002B0A18 is func_US2_002B1880.
 */
#include "common.h"

/* The hero block: the two fields the loop tests. */
typedef struct {
    char pad0000[0x340];
    int f340;                   /* 0x0340 */
    char pad0344[0xF04];
    int weapon;                 /* 0x1248 */
} Hero5940;

extern Hero5940 D_00189E20;
extern int D_L00_001B19C8[] __attribute__((sda));
extern int D_0018C350[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_0018C2EC[];
extern unsigned char D_001A7A28[] MACRO_ADDR;
extern unsigned char D_00139568[];
extern int D_L00_001A903C;
extern unsigned short D_0018C958 __attribute__((section(".data")));
extern int D_00139868[];
extern int D_001A7398[] MACRO_ADDR;
extern unsigned char D_001A7AF8[] MACRO_ADDR;

/* One 0xE0-byte entry of D_L00_00262570, indexed through D_00139568. */
typedef struct {
    int exists;                 /* 0x00 */
    unsigned char state;        /* 0x04 */
    char pad05[0x7];
    int index;                  /* 0x0C */
    char pad10[0x3A];
    short value;                /* 0x4A */
    char pad4C[0x20];
    int limit;                  /* 0x6C */
    char pad70[0x70];
} Entry1269;

extern Entry1269 D_L00_00262570[];
extern int func_L00_002D5E30(int *, int *, int *);
extern void func_0028A180(int, int);
extern void func_L00_003F1300(void);
extern void func_US2_L00_0030D9F8(int);
extern void func_US2_002B1880(int, int);
extern int func_002E5E58(int, int, void *);
extern int func_00288D58(void);
extern int func_00287F60(int);
extern void func_L00_0037E6A8(int, int);
extern void func_00287EB0(int);
extern void func_US2_00288F30(int);
extern int ref_US2_L00_002D6258_00 __attribute__((sda));

static inline int special(int i)
{
    int r = 0;

    switch (i) {
    case 12:
    case 14:
    case 17:
    case 18:
    case 53:
        r = 1;
        break;
    }
    return r;
}

static inline int unlocked(Entry1269 *e, int i)
{
    if (e->state >= 2 || (e->state == 1 && special(i)))
        return 1;
    return 0;
}

static inline int owned(int i)
{
    if (D_L00_00262570[D_00139568[i]].exists) {
        int n = func_00287F60(i);
        if (n >= 2 || (n == 1 && special(i)))
            return 1;
    }
    return 0;
}

void func_US2_L00_002D6258(void)
{
    int count, i, j, ok;

    if ((D_L00_001B19C8[0] & 15) == 1 && D_L00_001B19C8[0] != 1)
        return;
    count = 4;
    {
        int *p = D_0018C350;
        func_L00_002D5E30(p, p - 1, &count);
    }
    for (j = 0; j < 10; j++)
        if (D_001A7A28[j])
            count++;
    if (*(int *)D_001A7A00 != count) {
        if (ref_US2_L00_002D6258_00 >= 11 && *(int *)D_001A7A00 < count) {
            if (!D_0018C958)
                func_0028A180(0x9A9, 0);
            func_L00_003F1300();
            func_US2_L00_0030D9F8(0x168);
            func_US2_002B1880(0x1235, -1);
            func_002E5E58(6, 0, 0);
        }
        D_0018C2EC[0] = count;
        *(int *)D_001A7A00 = count;
    }

    for (i = 0; i < 56; i++) {
        if ((D_L00_00262570 + D_00139568[i])->state) {
            if (!func_00288D58())
                continue;
            if (func_00287F60(i) == 1)
                continue;
        }
        {
            Entry1269 *e = &D_L00_00262570[D_00139568[i]];
            int sel = 0;
            if (e->exists)
                sel = e->state == 3;
            if (sel)
                continue;
        }
        if (func_00287F60(i) <= 0)
            continue;
        {
            Entry1269 *e = &D_L00_00262570[D_00139568[i]];
            if ((D_00139868[i] >> 5) < e->limit || e->limit <= 0)
                continue;
            if (i == 31 || i == 9 || i == 45) {
                func_L00_0037E6A8(i, D_L00_00262570[D_00139568[i]].value);
                continue;
            }
            if (D_00189E20.weapon == i) {
                if (!D_00189E20.f340)
                    continue;
                if (D_001A7398[e->index] != i)
                    continue;
                func_L00_0037E6A8(i, e->value);
                continue;
            }
        }
        if (func_00288D58()) {
            Entry1269 *e = &D_L00_00262570[D_00139568[i]];
            if (!e->exists)
                continue;
            if (unlocked(e, i)) {
                if (owned(i)) {
                    func_00287EB0(i);
                    func_US2_00288F30(i);
                }
            }
        } else {
            func_00287EB0(i);
            func_US2_00288F30(i);
        }
    }

    if ((D_L00_001B19C8[0] & 127) || D_001A7A00[0x7A])
        return;
    ok = 1;
    for (i = 0; i < 56; i++) {
        int ex = D_L00_00262570[D_00139568[i]].exists;
        if (ex && i == 10)
            continue;
        if (ex && i == 9)
            continue;
        if (ex) {
            if (!D_001A7AF8[i]) {
                ok = 0;
                break;
            }
            if (i == 14 || i == 12 || i == 17 || i == 18 || i == 53)
                continue;
            if (func_00287F60(i) <= 0)
                continue;
            if (!D_L00_00262570[D_00139568[i]].state) {
                ok = 0;
                break;
            }
        }
    }
    if (ok && !D_001A7A00[0x7A]) {
        D_001A7A00[0x7A] = 1;
        func_002E5E58(1, 0, 0);
        func_US2_002B1880(0x1233, -1);
        D_L00_001A903C = 1;
    }
}
