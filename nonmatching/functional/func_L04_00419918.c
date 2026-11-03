/* functional: medium. Written from the retail code path by path; quadword copies are 16-byte struct copies, retail's re-reads of the same global in branch delay slots are folded where no call or store sits between them, and the pv[1828] clear keeps retail's "only when non-zero" form. Uncertain: callee argument types for the three callees with no C yet (func_L04_0040BA68, func_L04_00412308, func_L04_00418BF0, taken from the call sites), and the meaning of the globals; the control flow and every read, write and call order were checked against the disassembly. */

#include "include_asm.h"

typedef signed char s8;
typedef short s16;
typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float f32;

typedef struct {
    u32 w[4];
} Q_L04_00419918;

/* boot data */
extern s32 D_001A79F0;              /* current level / mode word */
extern s32 D_001A7904;
extern u8 D_001A7B2E;
extern char D_00189E20[];           /* hero block: +0x80 position, +0x2290 hero moby, +0x2294 state, +0x229C, +0x22B5, +0x22B7 */
extern char D_00188660[];           /* 112-byte entries: +0x74 flag, +0x88 owner */
extern u32 D_00138320;              /* pad buttons */
extern u32 D_00138324;

/* level 4 data */
extern s32 D_L04_001A8F08;
extern s32 D_L04_001A8F00;
extern s32 D_L04_001A8ED0;
extern s32 D_L04_001A8EE4;
extern s32 D_L04_001A8FE4;
extern s32 D_L04_001A8FE8;
extern u32 D_L04_001AA6A0;
extern u32 D_L04_001AA6A4;
extern u32 D_L04_001AA6A8;
extern u32 D_L04_001AA6AC;
extern s32 D_L04_001A7CD0;
extern f32 D_L04_001A7CCC;
extern s32 D_L04_001A7CD4;
extern s32 D_L04_001B08F0;
extern char *D_L04_001B08F4;
extern s32 D_L04_001B08F8;
extern s32 D_L04_001B08FC;
extern s32 D_L04_001B0900;
extern s32 D_L04_001B0908;
extern s32 D_L04_001B090C;
extern s32 D_L04_001B0910;
extern char *D_L04_001B0914;
extern s32 D_L04_001B0918;
extern s32 D_L04_001B091C;
extern s32 D_L04_001B0924;
extern s32 D_L04_001B092C;
extern s32 D_L04_001B0930;
extern s32 D_L04_001B0934;
extern s32 D_L04_001B0938;
extern s32 D_L04_001B0BBC;
extern s32 D_L04_001B0BC0;
extern f32 D_L04_001B1F20;
extern s32 D_L04_001B2008;
extern char *D_L04_001B24DC;        /* moby array, 0x100 bytes each */
extern char *D_L04_001B25CC;        /* 0x80-byte position records: +0x30 position, +0x70 direction */
extern s32 D_L04_001B31D4;
extern char D_L04_001B31A0[];
extern char D_L04_001B9540[];
extern char D_L04_001B9680[];
extern f32 D_L04_001BDC30;
extern Q_L04_00419918 D_L04_001BFAF0;

extern int func_00132028(void);
extern void func_00132B28(int);
extern void func_L00_002B30E8(void);
extern void func_L00_002B9D60(void *position, void *direction, int sound, int refresh);
extern s32 func_L04_002E7C08(s32 action, s32 animate);
extern void func_00272198(f32);
extern int func_00277258(void *, int, void *, float);
extern void func_0027AB40(void);
extern void func_L00_002E6EF8(void (*fn)(), void *arg);
extern void func_0027D330(int frames);
extern int func_00282948(void *);
extern float func_00282E48(void *a, void *b);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00283360(float *m);
extern f32 func_00283CE0(s32);
extern int func_00283CF0(f32);
extern void func_00288308(int);
extern int func_00288E18(int key, int selection);
extern void func_L00_00303530(int index, int argument);
extern void func_0029B758(int a0, void (*a1)());
extern void func_0029F338(void *object);
extern void func_0029F978(u8 *a0, u32 a1, u8 *a2);
extern void func_002A05A8(char *m);
extern void func_002A0F48(void *object);
extern void func_002A7398(s8 *arg0, s32 arg1, s32 arg2);
extern f32 func_002A7878(f32 a0, f32 a1);
extern void func_002A91F0(void *a0, float *a1);
extern void func_002A93B0(char *o);
extern void func_002AD7B8(int index);
extern int func_002B0C28(int a0, int a1, int a2);
extern int func_L00_003268E8(int value);
extern s32 func_002B38B8(u8 *m);
extern void func_L01_00323310(int a0, int a1);
extern void func_002C96F8(float t, float step, void *track, int *idx, float *frac, float *out);
extern void func_002DF3F8(void *a, void *b);
extern s32 func_002E4AC8(void);
extern s32 func_002E59B0(s32 a0, s32 a1);
extern void func_002E59F8(s32 a0);
extern int func_002E5CF8(int index, int a1, char *a2);
extern int func_002E5E58(int index, int value, void *object);
extern int func_L00_0035F5A0(int index, int a1, int a2);
extern int func_L01_00355BA0(int index, int value);
extern void func_L00_003672F8(void);
extern int func_L04_00400AB0(void *moby, void *path, int clamp);
extern int func_L04_0040A1D0(int);
extern unsigned int func_L04_0040A268(int);
extern void func_L04_0040A310(void);
extern void func_L04_0040A3B8(void *m, int keep);
extern void func_L04_0040A5C0(void *arg0);
extern void func_L04_0040A958(char *m, int hidden);
extern void func_L04_0040AC30(char *a0, char *a1);
extern void func_L04_0040BA68(char *moby, char *pv);
extern void func_L04_0040E248(char *a0, char *a1);
extern void func_L04_0040F5D0(void *m);
extern void func_L04_00410518(void *object, void *state, int *link, int *point, float *result, int mode);
extern int func_L04_00410E48(int a0, int a1, float f12);
extern int func_L04_00412308(char *moby, char *pv);
extern void func_L04_00412E38(void *arg0, void *arg1, float fparg0, float fparg1);
extern void func_L04_00415EA8(s32 arg0);
extern void func_L04_00418A58(char *obj, char *aux);
extern void func_L04_00418BF0(char *moby, char *pv);
extern void func_L04_004195E0(char *obj);
extern void func_L04_0043ABE0(void);

/* only their addresses are taken */
extern void func_L04_0040AC80();
extern void func_L04_0040AC98();
extern void func_L04_0040ACA8();
extern void func_L04_0040AD28();
extern void func_L04_0040CDD0();
extern void func_L04_00411298();
extern void func_L04_00417308();

/* Update of the Barlow race controller moby. moby+0x20 is the main state (0 setup,
   1 waiting for the hero, 2 race running with the sub-state at +0xBC, 3 route
   follow / exit, 4 leaving), the vars block is at moby+0x68. */
void func_L04_00419918(char *moby)
{
    char *pv = *(char **)(moby + 0x68);
    s32 lvl_a;
    s32 lvl;
    s32 i;
    char *s0;
    char *t;
    Q_L04_00419918 sp[2];

    if (*(u8 *)(moby + 49) != 0) {
        if (func_00282E48(moby + 16, D_L04_001B9680) < 24.0f) {
            func_002A93B0(moby);
            *(u8 *)(moby + 111) = 22;
        }
    }
    lvl_a = D_L04_001A8F08;

    if (lvl_a == 2 || D_L04_001A8F00 == 2) {
        if (D_L04_001B0BC0 == 0 && D_001A79F0 != 11) {
            u16 h = *(u16 *)(moby + 52);
            *(s32 *)(moby + 152) = 0;
            *(u16 *)(moby + 52) = (h | 0x41) & 0xEFFF;
            D_L04_001B0BC0 = 1;
            return;
        }
    }
    if (lvl_a != 2 && D_L04_001A8F00 != 2 && D_L04_001B0BC0 != 0) {
        u16 h = *(u16 *)(moby + 52);
        char *cls = *(char **)(moby + 36);
        *(u16 *)(moby + 52) = (h & 0xFFBE) | 0x1000;
        *(s32 *)(moby + 152) = *(s32 *)(cls + 16);
        D_L04_001B0BC0 = 0;
    }

    switch (*(u8 *)(moby + 32)) {
    case 0: {
        char *mobys;

        *(s32 *)(pv + 820) = -1;
        *(s32 *)(pv + 1864) = -1;
        *(s32 *)(pv + 1868) = -1;
        *(s32 *)(pv + 1812) = -1;
        *(s32 *)(pv + 956) = -1;
        *(s32 *)(pv + 808) = -1;
        *(s32 *)(pv + 816) = -1;
        D_L04_001AA6A0 = (u32)func_L04_0040AC80;
        D_L04_001AA6A8 = (u32)func_L04_0040ACA8;
        D_L04_001AA6AC = (u32)func_L04_0040AC98;
        D_L04_001AA6A4 = (u32)func_L04_0040AC98;
        func_00283360((float *)D_L04_001B31A0);
        D_L04_001B0914 = moby;
        func_L04_0043ABE0();
        *(u8 *)(moby + 48) = 64;
        *(s16 *)(moby + 50) = 64;
        *(u8 *)(moby + 32) = 1;
        func_L04_0040F5D0(moby);
        {
            u16 h = *(u16 *)(moby + 52);
            s32 v = D_001A7904;
            *(u16 *)(moby + 52) = h | 0x400;
            if (v == 3) {
                s32 idx = *(s32 *)(pv + 412);
                D_L04_001B08FC = 1;
                t = D_L04_001B25CC + idx * 128;
                func_L00_002B9D60(t + 48, t + 112, 0, 1);
                D_001A7904 = 0;
                func_L00_003672F8();
            } else {
                D_L04_001B08FC = 0;
            }
        }
        *(Q_L04_00419918 *)(pv + 720) = *(Q_L04_00419918 *)(moby + 16);
        *(Q_L04_00419918 *)(pv + 736) = *(Q_L04_00419918 *)(moby + 240);
        ((u32 *)(pv + 656))[0] = 0;
        ((u32 *)(pv + 656))[1] = 0;
        ((u32 *)(pv + 656))[2] = 0;
        ((u32 *)(pv + 656))[3] = 0;
        ((u32 *)(pv + 672))[0] = 0;
        ((u32 *)(pv + 672))[1] = 0;
        ((u32 *)(pv + 672))[2] = 0;
        ((u32 *)(pv + 672))[3] = 0;
        lvl = D_001A79F0;
        *(s32 *)(pv + 1172) = -1;
        *(f32 *)(pv + 1632) = 0.00999999978f;
        *(f32 *)(pv + 1636) = 0.0199999996f;
        *(f32 *)(pv + 1640) = 0.0299999993f;
        *(f32 *)(pv + 1644) = 0.0399999991f;
        *(s32 *)(pv + 788) = -1;
        *(s32 *)(pv + 792) = 0;
        *(s32 *)(pv + 1176) = 0;
        *(s32 *)(pv + 1600) = 0;
        if (lvl == 4) {
            *(s32 *)(pv + 1608) = 72;
            *(s32 *)(pv + 1604) = 77;
        } else {
            *(s32 *)(pv + 1608) = 65;
            *(s32 *)(pv + 1604) = 66;
        }
        *(s32 *)(pv + 1896) = 0;
        *(s32 *)(pv + 1892) = 40;

        mobys = D_L04_001B24DC;
        for (i = 0; i < 21; i++) {
            s32 idx = *(s32 *)(pv + 484 + i * 4);
            if (idx != -1) {
                char *v = *(char **)(mobys + idx * 256 + 104);
                *(s32 *)(v + 456) = 0;
                *(s32 *)(v + 288) = -1;
                *(s32 *)(v + 292) = 0;
                *(s32 *)(v + 452) = -1;
            }
        }

        *(s32 *)(pv + 832) = 0;
        *(s32 *)(pv + 836) = 0;
        for (i = 0; i < 5; i++) {
            s32 r = func_L04_0040A1D0(i);
            *(s32 *)(pv + 836) += r;
            r = func_L04_0040A268(i);
            *(s32 *)(pv + 832) += r;
        }
        for (i = 0; i < 6; i++) {
            *(f32 *)(pv + 880 + i * 4) = func_002A7878(0.0f, 1.0f);
        }

        lvl = D_001A79F0;
        if (lvl == 11) {
            s32 r = func_L04_0040A1D0(0);
            lvl = D_001A79F0;
            if (r > 0 && D_001A7B2E == 0) {
                func_00288308(54);
                goto setup_tail;
            }
        }
        if (lvl == 4 && func_L04_0040A1D0(0) > 0) {
            func_002AD7B8(5);
        }
    setup_tail:
        if (*(u8 *)(pv + 1089) == 0) {
            func_0029F978((u8 *)moby, 5, (u8 *)(pv + 1088));
        }
        return;
    }

    case 1: {
        s32 near;
        f32 dist;
        s32 idx = *(s32 *)(pv + 568);

        near = D_L04_001B08FC != 0;
        if (idx == -1 || func_002B38B8((u8 *)(D_L04_001B24DC + idx * 256)) != 0) {
            float vec[4];
            char *mobys;

            near = 1;
            func_L04_00412E38(moby, pv, 0.0199999996f, 0.000289999996f);
            *(f32 *)(moby + 24) = *(f32 *)(pv + 728) + func_00283198(*(f32 *)(pv + 908)) * 0.0399999991f;
            vec[0] = 0.0f;
            vec[1] = 0.0f;
            vec[2] = 0.0f;
            vec[3] = 0.0f;
            vec[0] = *(f32 *)(pv + 908);
            func_002A91F0(pv + 1104, vec);
            idx = *(s32 *)(pv + 568);
            mobys = D_L04_001B24DC;
            if (idx != -1) {
                char *m = mobys + idx * 256;
                u16 h = *(u16 *)(m + 52);
                *(s32 *)(m + 152) = 0;
                *(u16 *)(m + 52) = h | 0x43;
                idx = *(s32 *)(pv + 480);
                if (idx != -1) {
                    m = mobys + idx * 256;
                    h = *(u16 *)(m + 52);
                    *(s32 *)(m + 152) = 0;
                    *(u16 *)(m + 52) = h | 0x43;
                }
            }
        }

        dist = func_00282E48(D_00189E20 + 0x80, moby + 16);
        if (D_L04_001B08FC == 0) {
            s32 st;

            if (!near) {
                return;
            }
            if (!(dist < 5.5f)) {
                return;
            }
            if (D_L04_001B2008 < 4) {
                return;
            }
            if (*(s32 *)(D_00189E20 + 0x229C) == 31) {
                return;
            }
            st = *(s32 *)(D_00189E20 + 0x2294);
            if (st == 29 || st == 28 || st == 1) {
                return;
            }
            if (D_L04_001A8F00 == 2) {
                return;
            }
            if (D_L04_001A8F08 == 2) {
                return;
            }
            if (D_L04_001B0924 == 0 && func_002E59B0((s32)moby, *(s32 *)(pv + 816)) == 0) {
                s32 snd = (D_001A79F0 ^ 4) != 0 ? 26 : 22;
                s32 h = func_L00_0035F5A0(snd, 5, (s32)moby);
                f32 f;
                *(s32 *)(pv + 816) = h;
                f = func_00283CE0(1024);
                func_L01_00355BA0(*(s32 *)(pv + 816), func_00283CF0(f * 0.75f));
            }
        }

        func_002B0C28(4, 10145, 1);
        if (D_L04_001B08FC == 0 && D_L04_001B0924 == 0 && (D_00138324 & 0x10) == 0) {
            return;
        }
        {
            s32 h = *(s32 *)(pv + 816);
            if (h != -1) {
                char *e = D_00188660 + h * 112;
                if (*(s32 *)(e + 136) == (s32)moby && *(u8 *)(e + 116) != 0) {
                    func_002E59F8(h);
                }
            }
        }
        lvl = D_001A79F0;
        *(s32 *)(pv + 816) = -1;
        if (lvl == 206) {
            func_L04_002E7C08(134, 1);
        } else {
            if (*(s32 *)(pv + 408) != -1) {
                s32 p = *(s32 *)(pv + 412);
                char *tbl;

                if (p != -1) {
                    t = D_L04_001B25CC + p * 128;
                    func_002DF3F8(t + 48, t + 112);
                } else {
                    func_002DF3F8(moby + 16, moby + 240);
                }
                func_0027D330(16);
                t = D_L04_001B25CC + *(s32 *)(pv + 408) * 128;
                func_L00_002B9D60(t + 48, t + 112, 49, 1);
                tbl = D_L04_001B25CC;
                *(Q_L04_00419918 *)(moby + 16) = *(Q_L04_00419918 *)(tbl + *(s32 *)(pv + 408) * 128 + 48);
                *(Q_L04_00419918 *)(moby + 240) = *(Q_L04_00419918 *)(tbl + *(s32 *)(pv + 408) * 128 + 112);
            }
            func_L04_002E7C08(49, 1);
            func_L00_00303530(1, *(s32 *)(pv + 1160));
            {
                s32 fl = *(s32 *)(pv + 88);
                *(s32 *)(pv + 88) = fl | 1;
            }
            *(f32 *)(pv + 36) = 0.100000001f;
            *(f32 *)(pv + 32) = 0.25f;
            *(f32 *)(pv + 44) = 2.0f;
            *(f32 *)(pv + 48) = 1.0f;
            *(f32 *)(pv + 68) = 0.00833333377f;
            *(f32 *)(pv + 72) = 0.5f;
            *(f32 *)(pv + 76) = 0.00333333341f;
            *(s32 *)(pv + 832) = 0;
            *(f32 *)(pv + 40) = 2.0f;
            *(s32 *)(pv + 84) = 0;
            *(f32 *)(pv + 64) = 0.00833333377f;
            *(s32 *)(pv + 624) = 0;
            D_L04_001A8FE4 = 0;
            D_L04_001A8FE8 = 0;
            D_L04_001B0918 = 0;
            *(s32 *)(pv + 796) = 0;
        }
        *(u16 *)(moby + 52) |= 0x41;
        {
            s32 idx2 = *(s32 *)(pv + 476);
            char *m = 0;
            char *other;

            if (idx2 != -1) {
                m = D_L04_001B24DC + idx2 * 256;
            }
            other = D_L04_001B08F4;
            if (m != 0) {
                *(u16 *)(m + 52) |= 0x41;
                if (other != 0) {
                    *(u16 *)(other + 52) |= 0x41;
                }
            }
        }
        *(u8 *)(moby + 32) = 2;
        if (D_L04_001B0924 != 0) {
            *(u8 *)(moby + 188) = 2;
        } else {
            func_0029B758(0, func_L04_0040AD28);
            *(u8 *)(moby + 188) = 0;
        }
        D_L04_001B08FC = 0;
        *(s32 *)(pv + 916) = 150;
        *(u8 *)(moby + 48) = 255;
        func_L00_003268E8(4);
        {
            char *hero = *(char **)(D_00189E20 + 0x2290);
            *(u8 *)(D_00189E20 + 0x22B5) = 1;
            *(s32 *)(hero + 152) = 0;
        }
        func_L01_00323310(*(s32 *)(pv + 1160), -1);
        return;
    }

    case 2:
        if (*(s32 *)(D_00189E20 + 0x2294) == 134) {
            char *hero = *(char **)(D_00189E20 + 0x2290);
            char *mc = *(char **)(moby + 36);
            char *hc = *(char **)(hero + 36);
            f32 hs = *(f32 *)(hero + 44);
            f32 hb = *(f32 *)(hc + 36);
            f32 mb = *(f32 *)(mc + 36);
            *(f32 *)(moby + 44) = mb * (hs / hb);
            return;
        }
        if (D_L04_001B0908 != 0) {
            D_L04_001A8ED0 = 2;
            func_002E4AC8();
            func_0027D330(16);
            if (D_L04_001B0908 == 2) {
                func_L04_0040A958(moby, 1);
            } else {
                func_L04_0040A958(moby, 0);
            }
            D_L04_001B0908 = 0;
            return;
        }
        if (D_L04_001B0910 != 0) {
            u16 h = *(u16 *)(moby + 52);
            D_L04_001A8ED0 = 1;
            *(u16 *)(moby + 52) = h & 0xFFBE;
            func_L04_0040AC30(moby, pv);
            *(s32 *)(pv + 800) = -1;
            *(u8 *)(moby + 32) = 4;
            D_L04_001B0910 = 0;
            return;
        }

        switch (*(u8 *)(moby + 188)) {
        case 0:
            D_L04_001B0BBC = 0;
            func_L04_0040BA68(moby, pv);
            func_0029B758(0, func_L04_0040AD28);
            return;

        case 1:
            func_L04_00418A58(moby, pv);
            if (*(u8 *)&D_00138324 == 0) {
                return;
            }
            func_002E5E58(4, 0, 0);
            *(u8 *)(moby + 188) = 3;
            return;

        case 2: {
            s32 idx = *(s32 *)(pv + 476);
            char *other;

            s0 = 0;
            D_L04_001A8ED0 = 0;
            if (idx != -1) {
                s0 = D_L04_001B24DC + idx * 256;
            }
            other = D_L04_001B08F4;
            if (s0 != 0) {
                *(u16 *)(s0 + 52) &= 0xFFBE;
                if (other != 0) {
                    *(u16 *)(other + 52) &= 0xFFBE;
                }
                *(Q_L04_00419918 *)(s0 + 16) = *(Q_L04_00419918 *)(moby + 16);
                *(u8 *)(s0 + 48) = 0;
                *(Q_L04_00419918 *)(s0 + 240) = *(Q_L04_00419918 *)(moby + 240);
                func_002A7398((s8 *)s0, 0, 0);
                func_002A05A8(s0);
                func_002A0F48(s0);
            }
            *(u16 *)(moby + 52) &= 0xFFBE;
            D_L04_001B091C = 0;
            D_L04_001B31D4 = 0;
            func_0029B758(0, func_L04_00417308);
            D_L04_001B0930 = 0;
            D_L04_001B0938 = 0;
            func_L04_00415EA8(0);
            D_L04_001B08F0 = 0;
            func_L04_004195E0(moby);
            {
                char *hero;
                *(u8 *)(D_00189E20 + 0x22B5) = 1;
                hero = *(char **)(D_00189E20 + 0x2290);
                *(s32 *)(hero + 152) = 0;
            }
            if (D_L04_001B0924 != 0) {
                *(u8 *)(moby + 188) = 1;
                *(s16 *)(moby + 150) = 120;
                D_L04_001B0924 = 0;
                return;
            }
            *(u8 *)(moby + 188) = 3;
        }
            /* fall through */
        case 3:
            D_L04_001B092C = 0;
            func_L04_0040A5C0(moby);
            func_L04_0040A310();
            *(u8 *)(moby + 188) = 4;
            /* fall through */
        case 4: {
            s32 c;

            func_L04_00418A58(moby, pv);
            if (*(s32 *)(pv + 916) < 120 && D_L04_001B31D4 == 0) {
                goto say_count;
            }
            c = *(s32 *)(pv + 916);
            if (c < 90 && D_L04_001B31D4 == 1) {
                goto say_count;
            }
            if (c < 60 && D_L04_001B31D4 == 2) {
                goto say_count;
            }
            if (c < 30 && D_L04_001B31D4 == 3) {
                goto say_count;
            }
            goto count_down;
        say_count:
            func_002E5CF8(13, 0, moby);
            D_L04_001B31D4 = D_L04_001B31D4 + 1;
        count_down:
            func_00282948(pv + 916);
            if (*(s32 *)(pv + 916) != 0) {
                return;
            }
            func_002E5CF8(14, 0, moby);
            *(u8 *)(moby + 188) = 5;
            if (D_00138320 & 0x40) {
                D_L04_001B0930 = 0;
            } else {
                D_L04_001B0930 = 1;
            }
            return;
        }

        case 5:
            func_L04_00418A58(moby, pv);
            if (D_L04_001B0934 != 0) {
                func_00288E18(2598, 125);
                D_L04_001B0934 = 0;
            }
            if (func_L04_00412308(moby, pv) != 0) {
                return;
            }
            func_L04_00418BF0(moby, pv);
            func_L00_002E6EF8(func_L04_0040CDD0, moby);
            {
                f32 z = *(f32 *)(moby + 24);
                if (z < *(f32 *)(pv + 620)
                    || func_L04_00410E48(*(s32 *)(pv + 788), *(s32 *)(pv + 792), z) != 0) {
                    func_L04_0040E248(moby, pv);
                    *(u8 *)(moby + 188) = 6;
                    *(s16 *)(moby + 150) = 1;
                }
            }
            if (D_L04_001B0900 == 0) {
                return;
            }
            func_0027D330(16);
            func_L04_0040A958(moby, 1);
            *(s32 *)(pv + 832) = 0;
            D_L04_001B0900 = 0;
            return;

        case 6: {
            s32 idx;
            char *other;
            char *tbl;
            s32 pt;
            u16 cnt;

            if (*(s32 *)(pv + 1220) != 0) {
                char *v = *(char **)(*(char **)(pv + 1220) + 104);
                *(s32 *)(v + 448) = 0;
                *(s32 *)(pv + 1220) = 0;
            }
            if (*(s32 *)(pv + 1828) != 0) {
                *(s32 *)(pv + 1828) = 0;
            }
            *(s32 *)(pv + 1824) = 0;
            func_L00_002E6EF8(func_L04_0040CDD0, moby);
            s0 = 0;
            idx = *(s32 *)(pv + 476);
            *(s32 *)(pv + 780) = 0;
            *(s32 *)(pv + 636) = 0;
            if (idx != -1) {
                s0 = D_L04_001B24DC + idx * 256;
            }
            func_L04_0040E248(moby, pv);
            other = D_L04_001B08F4;
            if (s0 != 0) {
                f32 sc;

                *(u16 *)(s0 + 52) |= 0x41;
                if (other != 0) {
                    *(u16 *)(other + 52) |= 0x41;
                }
                sc = *(f32 *)(*(char **)(s0 + 36) + 36) * 0.25f;
                *(u8 *)(s0 + 49) = 1;
                *(s16 *)(s0 + 50) = 127;
                *(f32 *)(s0 + 44) = sc;
                *(Q_L04_00419918 *)(s0 + 16) = *(Q_L04_00419918 *)(moby + 16);
                *(u8 *)(s0 + 48) = 0;
                *(Q_L04_00419918 *)(s0 + 240) = *(Q_L04_00419918 *)(moby + 240);
                func_002A05A8(s0);
                func_002A0F48(s0);
                *(u16 *)(s0 + 52) |= 6;
            }

            cnt = *(u16 *)(moby + 150) - 1;
            *(u16 *)(moby + 150) = cnt;
            if (cnt != 0) {
                return;
            }
            func_0027D330(16);
            pt = *(s32 *)(pv + 272 + *(s32 *)(pv + 624) * 4);
            tbl = D_L04_001B25CC;
            if (pt != -1) {
                sp[0] = *(Q_L04_00419918 *)(tbl + pt * 128 + 48);
                pt = *(s32 *)(pv + 272 + *(s32 *)(pv + 624) * 4);
                sp[1] = *(Q_L04_00419918 *)(tbl + pt * 128 + 112);
            } else {
                if (*(s32 *)(pv + 408) == -1) {
                    func_L00_002B30E8();
                    return;
                }
                sp[0] = *(Q_L04_00419918 *)(tbl + *(s32 *)(pv + 408) * 128 + 48);
                sp[1] = *(Q_L04_00419918 *)(tbl + *(s32 *)(pv + 408) * 128 + 112);
            }
            D_L04_001B1F20 = 1.0f;
            func_00272198(10.0f);
            if (func_00277258(&sp[0], 4, moby, *(f32 *)(pv + 32)) != 0) {
                sp[0] = D_L04_001BFAF0;
            }
            func_L04_0040A3B8(moby, 1);
            func_L04_00415EA8((s32)moby);
            func_L00_002B9D60(&sp[0], &sp[1], 49, 1);
            *(u8 *)(D_00189E20 + 0x22B5) = 1;
            *(u8 *)(D_00189E20 + 0x22B7) = 1;
            *(s32 *)(pv + 1184) = -1;
            *(s32 *)(pv + 1180) = -1;
            *(f32 *)(pv + 1188) = -1.0f;
            *(s32 *)(pv + 1200) = 0;
            *(s32 *)(pv + 1192) = 0;
            *(s32 *)(pv + 1196) = 0;
            {
                s32 mode = D_L04_001A8FE4;
                *(Q_L04_00419918 *)(moby + 16) = sp[0];
                *(Q_L04_00419918 *)(moby + 240) = sp[1];
                func_L04_00410518(moby, pv, (int *)(pv + 788), (int *)(pv + 792), (float *)(pv + 784), mode);
            }
            *(u16 *)(moby + 52) &= 0xFFBE;
            if (s0 != 0) {
                u16 h;

                *(Q_L04_00419918 *)(s0 + 16) = *(Q_L04_00419918 *)(moby + 16);
                *(Q_L04_00419918 *)(s0 + 240) = *(Q_L04_00419918 *)(moby + 240);
                func_002A7398((s8 *)s0, 0, 0);
                func_002A05A8(s0);
                func_002A0F48(s0);
                h = *(u16 *)(s0 + 52);
                other = D_L04_001B08F4;
                *(u16 *)(s0 + 52) = h & 0xFFBE;
                if (other != 0) {
                    *(u16 *)(other + 52) &= 0xFFBE;
                }
            }
            {
                u16 h = *(u16 *)(moby + 52);
                *(u8 *)(moby + 188) = 5;
                *(u8 *)(moby + 48) = 255;
                *(u16 *)(moby + 52) = h | 0x400;
            }
            return;
        }
        }
        return;

    case 3: {
        f32 z;

        D_L04_001A8ED0 = 1;
        func_L04_00418A58(moby, pv);
        z = *(f32 *)(moby + 24);
        D_L04_001B08F8 = D_L04_001B08F8 + 1;
        if (z < *(f32 *)(pv + 620)
            || func_L04_00410E48(*(s32 *)(pv + 788), *(s32 *)(pv + 792), z) != 0) {
            char *route = *(char **)(pv + 1744);
            s32 k = func_L04_00400AB0(moby, route, 1);
            f32 tpos;

            route = *(char **)(pv + 1744);
            *(Q_L04_00419918 *)(moby + 16) = *(Q_L04_00419918 *)(route + k * 16 + 16);
            tpos = func_00283CE0(k);
            route = *(char **)(pv + 1744);
            tpos = tpos * *(f32 *)(route + 28);
            if (D_L04_001B08F0 != 0) {
                tpos = tpos + 15.0f;
            } else {
                tpos = tpos + 5.0f;
            }
            *(f32 *)(pv + 1752) = tpos;
            func_002C96F8(tpos, *(f32 *)(route + 28), route, (int *)(pv + 1620), (float *)(pv + 1748),
                          (float *)(pv + 1696));
            {
                s32 mode = D_L04_001A8FE4;
                func_L04_00410518(moby, pv, (int *)(pv + 788), (int *)(pv + 792), (float *)(pv + 784), mode);
            }
        }
        func_0029B758(0, func_L04_00411298);
        func_00282948(pv + 920);
        if (D_L04_001A7CD0 == 0) {
            if (*(s32 *)(pv + 920) > 0) {
                return;
            }
            if ((D_00138324 & 0x10) == 0) {
                return;
            }
            D_L04_001A7CD0 = 1;
            D_L04_001A7CCC = 0.0500000007f;
            D_L04_001A7CD4 = 0;
        }
        if (D_L04_001A7CD4 != 1) {
            return;
        }
        func_00132B28(93);
        func_00132028();
        D_L04_001A8EE4 = 0;
        func_L04_0040AC30(moby, pv);
        *(u8 *)(moby + 32) = 4;
        func_L01_00323310(*(s32 *)(pv + 1160), -1);
        return;
    }

    case 4: {
        s32 v;
        s32 s5;
        f32 ang;
        f32 tn;
        char *hero;

        v = D_L04_001A7CD0;
        *(s32 *)(D_L04_001B9540 + 364) = 0;
        D_L04_001A8ED0 = 1;
        *(s32 *)(D_L04_001B9540 + 352) = 0;
        *(s32 *)(D_L04_001B9540 + 360) = 0;
        *(s32 *)(D_L04_001B9540 + 384) = 0;
        *(s32 *)(D_L04_001B9540 + 392) = 0;
        if (v == 0) {
            D_L04_001A7CD0 = 1;
            D_L04_001A7CCC = 0.0500000007f;
            D_L04_001A7CD4 = 0;
        }
        if ((u32)(D_L04_001A7CD4 - 1) >= 2) {
            return;
        }
        func_L04_0040A310();
        {
            u16 h = *(u16 *)(moby + 52);
            D_L04_001A8ED0 = 0;
            *(u16 *)(moby + 52) = h & 0xFFBE;
        }
        func_0029B758(0, 0);
        if (*(s32 *)(pv + 412) == -1) {
            func_L04_0040A958(moby, 1);
            D_L04_001B0900 = 0;
            return;
        }
        if (*(s32 *)(pv + 800) != -1) {
            if (D_L04_001B090C != 0 || func_L04_0040A1D0(0) != 1) {
                if (func_L04_0040A1D0(D_L04_001B090C) == 1) {
                    s32 n = D_L04_001B090C + 1;
                    D_L04_001B090C = n;
                    if (n >= 5) {
                        D_L04_001B090C = 4;
                    }
                }
                func_L04_0040A958(moby, 1);
                return;
            }
        }

        s5 = *(s32 *)(pv + 1152);
        if (D_001A79F0 == 11) {
            s5 = *(s32 *)(pv + 1156);
        }
        {
            s32 bb = D_L04_001B0BBC;
            sp[0] = *(Q_L04_00419918 *)(D_L04_001B25CC + *(s32 *)(pv + 412) * 128 + 112);
            if (bb != 0) {
                ((f32 *)&sp[0])[2] = 0.920000017f;
            }
        }
        {
            s32 m800 = *(s32 *)(pv + 800);
            if (m800 == 1 && D_L04_001B090C == 0) {
                D_L04_001B090C = m800;
            }
        }
        if (D_L04_001B08F4 != 0) {
            func_0029F338(D_L04_001B08F4);
            D_L04_001B08F4 = 0;
        }
        {
            char *tbl = D_L04_001B25CC;
            hero = *(char **)(D_00189E20 + 0x2290);
            *(u8 *)(D_00189E20 + 0x22B5) = 0;
            ang = 0.562170565f;
            *(s32 *)(hero + 152) = *(s32 *)(*(char **)(hero + 36) + 16);
            func_L00_002B9D60(tbl + *(s32 *)(pv + 412) * 128 + 48, &sp[0], 0, 1);
        }
        hero = *(char **)(D_00189E20 + 0x2290);
        *(f32 *)(hero + 44) = *(f32 *)(*(char **)(hero + 36) + 36);
        {
            char *cls;
            *(Q_L04_00419918 *)(moby + 16) = *(Q_L04_00419918 *)(pv + 720);
            cls = *(char **)(moby + 36);
            *(Q_L04_00419918 *)(moby + 240) = *(Q_L04_00419918 *)(pv + 736);
            *(u8 *)(moby + 32) = 1;
            *(f32 *)(moby + 44) = *(f32 *)(cls + 36);
        }
        func_L00_00303530(0, s5);
        tn = func_00283198(ang);
        tn = tn / func_00283180(ang);
        D_L04_001BDC30 = tn;
        func_0027AB40();
        for (i = 0; i < 21; i++) {
            s32 idx = *(s32 *)(pv + 484 + i * 4);
            char *mobys = D_L04_001B24DC;
            if (idx != -1) {
                char *vv = *(char **)(mobys + idx * 256 + 104);
                s32 obj = *(s32 *)(vv + 140);
                *(s32 *)(vv + 712) = 0;
                *(u8 *)(vv + 593) = 0;
                if (obj != 0) {
                    func_0029F338((void *)obj);
                    *(s32 *)(vv + 140) = 0;
                }
            }
        }
        return;
    }
    }
}
