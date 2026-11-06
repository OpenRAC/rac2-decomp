/* func_PAL_0028C7C8, the PAL copy of func_0028BE00: the same C, where the timeout becomes 150 and the frame record is scaled to 50 Hz. */
#include "common.h"

typedef struct { char pad[0x14]; int name; char pad18[0x70]; unsigned short valid; char pad8a[4]; unsigned short ammo; char pad90[0x50]; } Info;
typedef struct { char pad[0x148]; float x, y; char pad150[0x70]; int held, pressed, pad1c8, inhibit, pad1d0, pad1d4, repeat; } Controller;
typedef struct { char pad[0xf0]; unsigned short uses; char padf2[2]; unsigned int maxFrame, levels; } Stats;
typedef struct { char pad[0x1248]; int selected; char pad124c[0x107c]; int pending; } Hero;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; } Slot;
typedef struct { char pad[0x64]; int handle; char pad68[4]; int timer; unsigned char fade[4]; int selected, state, timeout; } Selector;

extern int D_001A8C64;
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int D_001A8CFC;
extern int D_001A8D30 __attribute__((sda));
extern int D_001A8D48 __attribute__((sda));
extern int D_001A8D90[] __attribute__((sda));
extern int D_001B18D0;
extern Slot **D_001B18D4;
extern float D_001A8E10;
extern int D_001B1900;
extern int D_001B18FC;
extern int D_001B1598, D_001B18F8;
extern unsigned char D_00139568[];
extern int D_00139688[];
extern Info D_00239BA0[];
extern Controller D_00138180;
extern char D_0018C316[];
extern char D_001A8E18[];
extern Stats D_0018C750;
extern Hero D_00189E20;
extern unsigned int D_001A7390;
extern int D_001A79F0;
extern short D_001A63AC NOT_SDA;
extern int func_00287E48(void), func_00290748(void);
extern void func_00290730(void), func_00287E60(void);
extern void func_PAL_0034ED50(void *, int);
extern int func_00282978(void *);
extern float func_00282C10(float), func_00283248(float, float), func_00283CE0(int), func_00283BE0(float, float), func_00283C80(float, float), func_00283C28(float);
extern int func_00283CF0(float);
extern void func_0026FEB8(void *), func_002B7AD0(void), func_002E5E58(int, int, int);
extern int func_00294630(int);
extern void func_00294420(int), func_00287E18(void), func_00290728(void), func_00290720(void);
extern int func_0028B5D0(int);

static inline Info *InfoOf(int id)
{
    return &D_00239BA0[D_00139568[id]];
}

void func_PAL_0028C7C8(Selector *p)
{
    float x, y, mag, ang, a, f, r;
    int old, n, s, k, id;
    int active;
    unsigned char *c, *e;

    if (D_001A8C64) return;
    active = 0;
    if (!D_001A7BB0[3] || func_00287E48() || !D_001A7BB0[3]) {
        active = 1;
        if (!D_001A7BB0[3]) {
            func_00290730();
            if (!func_00290748()) active = 0;
        }
    }
    e = p->fade;
    if (active && D_001A8CFC) {
        func_PAL_0034ED50((char *)D_001A8CFC + 0x376C8, func_00287E48() ? D_001A8D30 : 2);
        func_00287E60();
    }
    p->timeout = 150;
    p->timer = 24;
    if (func_00282978(D_0018C316) && !D_001A7BB0[3]) D_00138180.inhibit = 2;
    x = D_00138180.x;
    y = D_00138180.y;
    mag = func_00282C10(x * x + y * y);
    if (mag != 0.0f) {
        x /= mag;
        y /= mag;
    }
    ang = func_00283248(x, y);
    if ((p->state >> 24) == 0) {
        if ((D_00138180.pressed & 0xF000) || mag < 0.5f || --p->state == -1) {
            p->selected = -1;
            p->state = 0x10000FF;
        }
    }
    n = 0;
    old = p->selected;
    if ((p->state >> 24) == 1 && (D_00138180.held & 0x10) && active) {
        if (mag > 0.9f) {
            a = ang + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)D_001B18D0;
            f = a * 0.15915494f * (float)D_001B18D0;
            r = (float)old * 6.2831855f / func_00283CE0(D_001B18D0) - 3.1415927f;
            if (old == -1 || func_00283C80(r, func_00283BE0(ang, 1.5707964f)) > 0.5890487f) {
                s = (int)f % D_001B18D0;
                if ((s ^ 1) & 1) {
                    float fr = f - (float)func_00283CF0(f);
                    if (fr > 0.8f) s++;
                    else if (fr < 0.2f) s--;
                    s = (s + D_001B18D0) % D_001B18D0;
                }
                p->selected = s;
                n = -1;
                D_001A8E10 = func_00283C28(a - ((float)s * 0.78539824f + 0.39269912f));
                if (D_001A8E10 > 0.0f) n = 1;
            }
        } else if (D_00138180.repeat == 0 && (D_00138180.pressed & 0xF000)) {
            int w;
            w = old;
            if (D_00138180.pressed & 0x1000) {
                int t;
                if (w == -1) t = D_001A8D90[4];
                else t = D_001B18D4[D_001A8D48][w].f10;
                w = t;
            }
            if (D_00138180.pressed & 0x4000) {
                int t;
                if (w == -1) t = D_001A8D90[5];
                else t = D_001B18D4[D_001A8D48][w].f14;
                w = t;
            }
            if (D_00138180.pressed & 0x8000) {
                int t;
                if (w == -1) t = D_001A8D90[2];
                else t = D_001B18D4[D_001A8D48][w].f8;
                w = t;
            }
            if (D_00138180.pressed & 0x2000) {
                int t;
                if (w == -1) t = D_001A8D90[3];
                else t = D_001B18D4[D_001A8D48][w].fC;
                w = t;
            }
            p->selected = w;
        }
        {
            Slot *t = D_001B18D4[D_001A8D48];
            int cur = p->selected;
            if (t[cur].f0 == 0 && n != 0) {
                k = (cur + n) % D_001B18D0;
                if (t[k].f0 != 0) p->selected = k;
            }
        }
    }
    c = p->fade;
    if (p->selected != old) {
        func_0026FEB8(D_001A8E18);
        func_002B7AD0();
        c[1] = 0;
        func_002E5E58(3, 0, 0);
    } else if (c[1] < 8) c[1]++;
    if (p->selected >= 0 && !func_00294630(InfoOf(D_001B18D4[D_001A8D48][p->selected].f18)->name)) {
        func_00294420(InfoOf(D_001B18D4[D_001A8D48][p->selected].f18)->name);
    } else {
        if (!(D_00138180.held & 0x10) && !D_001A63AC) {
            if (c[0]) c[0]--;
            if (c[0] == 0 && p->selected >= 0 && (id = D_001B18D4[D_001A8D48][p->selected].f18) != 0) {
                Info *rr;
                if (D_00189E20.selected != id && D_0018C750.uses < 0xFFFF) D_0018C750.uses++;
                if (D_0018C750.maxFrame < ((s32)(D_001A7390) * 5 + 2) / 6) D_0018C750.maxFrame = ((s32)(D_001A7390) * 5 + 2) / 6;
                D_0018C750.levels = D_0018C750.levels | (1 << D_001A79F0) | 0x80000000;
                D_00189E20.pending = id;
                rr = InfoOf(id);
                if (rr->valid && rr->ammo < D_00139688[id]) D_00139688[id] = rr->ammo;
            }
            if (D_001A7BB0[3]) func_00287E18();
            else {
                func_00290728();
                func_00290720();
            }
        } else if (c[0] < 8) c[0]++;
    }
    if (e[0] == 0) {
        {
            int state = p->state;
            D_001B1900 = p->selected;
            D_001B18FC = state;
        }
        func_0028B5D0(p->handle);
        p->timer = -6;
        D_001B18F8 = D_001B1598;
    }
}
