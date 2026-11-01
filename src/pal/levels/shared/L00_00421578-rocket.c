#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; char *p[0x980]; } Hero;
extern char D_00189E20[];
typedef struct {
    char pad0[4];
    u8 alt;
    char pad5[0x4B];
    float speed;
    char pad54[224 - 0x54];
} Kind;
typedef struct { char pad0[0x18]; char *who; } Hit;
typedef struct {
    float vel[4];
    s16 life;
    s16 kind;
    char *target;
    s16 h18, h1A;
    float scale;
    float v20, v24, v28;
    s16 h2C, h2E;
    int slot;
    s16 h34, h36;
    int i38;
    int id;
    float aim[4];
    int owner;
    int i54;
    float yaw;
    float f5C, f60, f64;
    int flag;
    int handle;
    float start[4];
} Rocket;
extern int func_002761F8(void *, void *, int, char *, int);
extern int func_00277F48(void *, int, char *, int, float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_002833F0(void *, void *);
extern void func_00283658(void *, void *);
extern void func_00283678(void *, void *);
extern void func_00283738(void *, void *, void *);
extern float func_00283B98(float, float);
extern char *func_0029EFD0(int);
extern void func_0029F338(void *);
extern char *func_002AB1F0(void *);
extern void func_002AB668(void *, void *, float);
extern void func_002AB6D8(void *, void *);
extern int func_002ABB78(void *);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002AF000(void *, float, float, float);
extern char *func_002AF580(void *, void *, float, float, int *, int, int, int, float, float, float, int, void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_002B37E8(void *, void *, int);
extern int func_002FED90(void *, float, float, float, void *);
extern void func_L00_002D3798(void *, void *, float);
extern void func_L00_00322A98(void *, void *);
extern void func_L00_00322AC0(void *, int, int, float);
extern char *func_L00_0032A088(int, int);
extern int *func_L00_0032A0B8(int, int);
typedef struct { char pad[0x16]; u8 x16; char pad2[0x100]; } Gs;
extern Gs D_00139568;
extern int D_L00_001A8FF0 MACRO_ADDR;
extern int D_L00_001ADB2C MACRO_ADDR;
extern unsigned int D_L00_001B2D5C MACRO_ADDR;
extern char D_L00_001B8C80[];
extern char D_L00_001B8FF0[];
extern Hit D_L00_001BF200;
extern Kind D_L00_00262570[];
#define HERO ((Hero *)D_00189E20)
typedef struct { char pad[0x150]; float v[4]; } View;
#define VIEW (((View *)D_L00_001B8C80)->v)
char *func_PAL_L00_00421578(char *owner, void *pos, int mode, int id, char *hint, int flag)
{
    float a[4], b[4], c[4], d[4], e[4], f[4];
    float unused60[8]; /* retail's frame keeps these 0x20 bytes; nothing in the body reaches them */
    float n[4], t[4], u[4];
    int outv;
    char *m, *r;
    Rocket *s;
    float speed, fr;
    char *base;
    int *tab, *pp;
    m = func_0029EFD0(0x87A);
    if (m) {
    s = *(Rocket **)(m + 0x68);
    s->life = 0xFA;
    s->kind = 0xA;
    s->h2E = 2;
    s->i38 = -1;
    s->id = id;
    s->h18 = 0;
    s->v20 = 0;
    s->v24 = 0;
    s->v28 = 0;
    s->h1A = 0;
    s->h2C = 0;
    s->h34 = 0;
    s->owner = *(s16 *)(owner + 0xAA);
    s->yaw = -1.2217306f;
    s->f5C = 0;
    s->f60 = 0;
    s->f64 = 0;
    s->flag = flag;
    func_002B37E8(m, owner, -1);
    ((u8 *)m)[0x30] = 0xFF;
    if ((D_L00_00262570 + D_00139568.x16)->alt)
        *(int *)(m + 0x78) = 0xFFFF0A0A;
    else
        *(int *)(m + 0x78) = 0xFF0A0AFF;
    if (flag) {
        func_00282D30(a, HERO->p[0x2290 / 4] + 0xE0, 0.3f);
        func_00282CC0(m + 0x10, m + 0x10, a);
        func_00282D30(b, HERO->p[0x2290 / 4] + 0xD0, 0.3f);
        func_00282CC0(m + 0x10, m + 0x10, b);
        func_00282D30(c, HERO->p[0x2290 / 4] + 0xC0, 0.5f);
        func_00282CC0(m + 0x10, m + 0x10, c);
        func_00282CC0(d, D_00189E20 + 0x80, a);
        if (func_002761F8(d, m + 0x10, 0x10, HERO->p[0x2290 / 4], 0)) {
            func_00282CF0(e, d, m + 0x10);
            func_00282D30(e, e, 0.75f);
            func_00282CC0(m + 0x10, m + 0x10, e);
        }
    } else
        qcopy(m + 0x10, pos);
    func_00282C88(s);
    speed = (D_L00_00262570 + D_00139568.x16)->speed * 0.020000001f;
    if (mode) {
        HERO->f[0xC04 / 4] = VIEW[2];
        HERO->f[0xC08 / 4] = func_00283B98(-VIEW[1], 0.12217305600643158f);
        func_002AF000(s, speed, HERO->f[0xC04 / 4], HERO->f[0xC08 / 4]);
    } else
        func_L00_002D3798(s, s, speed);
    func_00282C88(a);
    func_002833F0(b, a);
    if (mode) {
        a[0] = VIEW[0];
        a[1] = VIEW[1];
        a[2] = VIEW[2];
        func_002833F0(f, a);
        func_00283738(b, f, b);
    } else
        func_00283738(b, HERO->p[0x2290 / 4] + 0xC0, b);
    func_00283658(e, b);
    func_002AB6D8(e, m + 0xF0);
    func_00283678(m + 0xC0, e);
    *(float *)(m + 0xCC) = *(float *)(m + 0xDC) = *(float *)(m + 0xEC) = 0.0f;
    *(u16 *)(m + 0x34) |= 0x100;
    s->scale = 1.0f;
    if (func_00277F48(m + 0x10, 1, HERO->p[0x2290 / 4], 0, 1.0f) != 0
        && ((D_L00_001BF200.who != 0 && *(char **)(D_L00_001BF200.who + 0x24) != 0
             && *(s16 *)(*(char **)(D_L00_001BF200.who + 0x24) + 0x46) == 5)
            || func_002ABB78(D_L00_001BF200.who) != 0)) {
        s->target = D_L00_001BF200.who;
        r = func_002AB1F0(s->target);
        if (r) {
            func_002AFFD8(m + 0x10, n, 1);
            func_00282D30(t, n, *(float *)(r + 0x10));
            func_00282CC0(m + 0x10, s->target + 0x10, t);
        }
    } else if (flag == 0) {
        char *lock = HERO->p[0x1450 / 4];
        if (lock != 0 && ((u8 *)lock)[0x20] != 0xFE && ((u8 *)lock)[0x20] != 0xFD)
            s->target = lock;
        else
            s->target = func_002AF580(m + 0x10, e, 0.174532949924469f, 0.349065899848938f, &outv, 0, 0, 0, 30.0f, 0.0f, 0.0f, 0, 0);
    } else
        s->target = hint;
    if (s->target) {
        func_002AFFD8(m + 0x10, n, 1);
        fr = func_00282E48(m + 0x10, s->target + 0x10) * 0.033333335f;
        if (fr > 1.0f)
            fr = 1.0f;
        func_002ACEC0(s, s, n, -(fr * 0.43633235f));
        s->h36 = 0;
    } else {
        if (mode) {
            func_00282D30(s->aim, D_L00_001B8FF0, 64.0f);
            func_00282CC0(s->aim, s->aim, D_L00_001B8FF0 - 0x230);
        } else {
            func_00282D30(n, HERO->p[0x2290 / 4] + 0xC0, 64.0f);
            func_00282CC0(s->aim, m + 0x10, n);
        }
        if (D_L00_001A8FF0 != 0)
            s->h36 = 0;
        else {
            if ((HERO->i[0x1500 / 4] == 0 && HERO->i[0x2294 / 4] != 0x1D && HERO->i[0x2294 / 4] != 1)
                || ((*(u16 *)(HERO->p[0x2290 / 4] + 0x34) ^ 1) & 1)) {
                func_002AFFD8(m + 0x10, n, 1);
                func_002ACEC0(s, s, n, -0.43633235f);
            }
            s->h36 = 1;
        }
    }
    if (D_L00_001B2D5C >= 0x19)
        D_L00_001B2D5C = 0;
    s->slot = D_L00_001B2D5C;
    base = func_L00_0032A088(s->owner, s->id);
    if (base == 0) {
        func_0029F338(m);
        return 0;
    }
    tab = func_L00_0032A0B8(s->owner, s->id);
    pp = (int *)(base + tab[1]);
    if (pp[s->slot])
        s->slot = -1;
    else {
        D_L00_001B2D5C = (int)(D_L00_001B2D5C + 1) % 25;
        pp[s->slot] = 1;
        s->i54 = 0;
        base += tab[0];
        func_L00_00322A98(m, base + s->slot * 0x150);
        if (D_L00_001ADB2C != 0)
            func_L00_00322AC0(s->slot * 0x150 + base, 0x30, 1, 0.0f);
        else {
            func_L00_00322AC0(s->slot * 0x150 + base, 0x30, 2, 0.0f);
            func_L00_00322AC0(s->slot * 0x150 + base, 0x17, 3, 0.0f);
        }
    }
    func_002AB668(n, m + 0xC0, s->yaw);
    func_002ACDE8(m + 0xD0, m + 0xD0, n);
    func_002ACDE8(m + 0xE0, m + 0xE0, n);
    s->handle = func_002FED90(m, 1.0f, 1.0f, 1.0f, 0);
    qcopy(s->start, m + 0x10);
    if (D_L00_001A8FF0 != 0) {
        func_002AFFD8(m + 0x10, t, 1);
        fr = func_00282DB0(t, s);
        func_00282D30(u, t, fr);
        func_00282CF0(s, s, u);
    }
    }
    return m;
}
