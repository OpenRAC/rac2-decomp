/* Closer B, 2026-11-01: PAL copy of func_L00_004212B8 (matched); 1916/1916, profile -O2 -G8 -ffunction-sections -g.
 * Only $s3/$s4 differ: retail gives the D_00189E20 high part and `use` s3, `out` s4; here the reverse. 50 Hz: the
 * 0xC and 0xD limits, and timers scaled by (D * 5 + 2) / 6 read as int. A static inline for the scale changes nothing.
 */
#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; } Hero;
extern char D_00189E20[];
typedef struct {
    float base[4];
    float a10[4];
    float a20[4];
    float a30[4];
    char pad40[0x20];
    float a60[4];
    char pad70[0x40];
    float rB0;
    char padB4[0x10];
    u8 st;
    char padC5;
    s16 tC6;
    float invC8;
    float rCC;
    float rD0;
    s16 tD4;
    u8 fD6;
    u8 fD7;
    s16 hD8;
    char padDA[0x12];
    s16 hEC;
    s16 hEE;
} Ctl;
extern int func_00277258(void *, int, void *, float);
extern int func_00282978(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00282DF0(void *);
extern void func_00334710(void *, void *);
extern int func_00334730(void *, int);
extern float func_003348A8(void *, float);
extern void func_003349E8(void *, int, float);
extern int D_L00_001A8FF0 MACRO_ADDR;
extern float D_L00_001B1500 __attribute__((sda));
extern float D_L00_001B1504 __attribute__((sda));
extern int D_L00_001B1518 __attribute__((sda));
extern u16 D_L00_001B1530 __attribute__((sda));
extern int D_L00_001B1534 __attribute__((sda));
extern u16 D_L00_001B1548 __attribute__((sda));
extern float D_L00_001B154C __attribute__((sda));
extern int D_L00_001B1560 __attribute__((sda));
extern float D_L00_001B1574 __attribute__((sda));
extern char D_L00_001B8E20[];
#define HERO ((Hero *)D_00189E20)
void func_PAL_L00_004266C8(char *moby, void *out)
{
    float sp[4], tmp[4];
    Ctl *s = (Ctl *)(*(char **)(moby + 0x70) + 0x60);
    char *cam = D_L00_001B8E20;
    char *c;
    char *v;
    int use;
    float d;
    if (HERO->h[0x348 / 2] != 0 || D_L00_001A8FF0 != 0 || (s->hEE != 0 && HERO->h[0x34E / 2] != 0)) {
        s->hEC = 0xC;
        s->fD6 = 1;
        s->hEE = 1;
        func_00282D30(s->a10, cam + 0x30, func_00282DB0(s, cam + 0x30));
        qcopy(s->a20, s->a10);
        if ((u32)(s->st - 5) < 3 || s->st == 3)
            func_003349E8(s->a30, 1, D_L00_001B154C * 0.5f);
    } else {
        short st = s->hEE;
        if (st == 1) {
            float r;
            func_00282D30(s->a10, cam + 0x30, func_00282DB0(s, cam + 0x30));
            qcopy(s->a20, s->a10);
            if ((u32)(s->st - 5) < 3 || s->st == 3)
                func_003349E8(s->a30, 1, D_L00_001B154C * 0.5f);
            r = func_00283CE0(s->hD8);
            r = r / func_00283CE0(0xC);
            s->hD8 = func_00283CF0(func_00283CE0(s->hEC) * r);
            s->hEE = 2;
        } else {
            if (st >= 2) {
                func_00282D30(s->a10, cam + 0x30, func_00282DB0(s, cam + 0x30));
                qcopy(s->a20, s->a10);
                if ((u32)(s->st - 5) < 3 || s->st == 3)
                    func_003349E8(s->a30, 1, D_L00_001B154C * 0.5f);
                s->hEE = s->hEE + 1;
                if (s->hEE >= 0xD)
                    s->hEE = 0;
            }
        }
    }
    c = cam + 0x30;
    func_00334710(moby, sp);
    if (HERO->i[0x2294 / 4] == 0x74) {
        func_00282D30(out, c, func_00282DB0(s, c));
        func_00282CF0(s, s, out);
        func_00282D30(out, c, func_00282DB0(c, s->a60));
        qcopy(s->a10, out);
        if (s->st != 0xB) {
            s->st = 0xB;
            {
                char *o;
                int t;
                qcopy(moby + 0x40, moby);
                o = *(char **)(moby + 0x70);
                t = (D_L00_001B1518 * 5 + 2) / 6;
                { char *m = o + 0x20;
                *(s16 *)m = t;
                *(float *)(m + 0x24) = 1.0f / func_00283CE0((s16)t); }
            }
        }
    } else {
        switch (s->st) {
        case 2:
            if (HERO->i[0x2294 / 4] == 0x11
                || (HERO->b[0x49E] != 0 && HERO->f[0x31C / 4] > 0.2f)) {
                u16 t;
                if (HERO->i[0x2294 / 4] != 0x11) {
                    d = func_003348A8(moby, s->rB0);
                    if (!(d < D_L00_001B1504) && !(D_L00_001B1500 < d))
                        goto next;
                }
                s->st = 1;
                t = D_L00_001B1530;
                s->tC6 = t;
                s->invC8 = 1.0f / func_00283CE0((s16)t);
            }
        next:
            use = 0;
            if (HERO->h[0x34C / 2] != 0 && (HERO->b[0x49E] == 0 || HERO->h[0x4AE / 2] >= 0x10)) {
                use = 1;
            } else {
                if (func_00334730(tmp, 1) != 1 || func_00282DB0(tmp, c) < func_00282DF0(s->a10))
                    use = 1;
            }
            v = (char *)tmp;
            if (use) {
                qcopy(out, s->a10);
                func_00282D30(v, c, func_00282DB0(sp, c));
                func_00282CF0(s, sp, v);
            } else {
                func_00334730(v, 1);
                func_00282D30(out, c, func_00282DB0(v, c));
                func_00282CF0(s, v, out);
            }
            break;
        case 3:
        case 5:
        case 6:
        case 7:
            {
                func_00282D08(s->a10, s->a30, s->a20, (float)s->tD4 * s->rCC);
                if (s->fD7 == 0 && func_00277258(moby + 0x30, 0x12, 0, 0.2f) != 0) {
                    qcopy(s->a30, s->a10);
                    s->fD7 = 1;
                }
                qcopy(out, s->a10);
                d = func_00282DB0(sp, c);
                v = (char *)tmp;
                func_00282D30(v, c, d);
                func_00282CF0(s, sp, v);
                if (func_00282978(&s->tD4) != 0) {
                    if (s->st == 9) {
                        s->st = 0xA;
                        s->tD4 = (D_L00_001B1560 * 5 + 2) / 6;
                        qcopy(s->a20, s->a10);
                        func_00282D30(v, c, s->rD0);
                        func_00282CF0(s->a30, s->a20, v);
                    } else if (s->st == 6) {
                        s->st = 7;
                        s->tD4 = (D_L00_001B1534 * 5 + 2) / 6;
                        qcopy(s->a30, s->a20);
                        qcopy(s->a20, s->a10);
                    } else {
                        u16 t;
                        s->st = 4;
                        t = D_L00_001B1548;
                        s->tC6 = t;
                        s->invC8 = 1.0f / func_00283CE0((s16)t);
                    }
                }
            }
            break;
        case 8:
            qcopy(out, s->a10);
            d = func_00282DB0(sp, c);
            v = (char *)tmp;
            func_00282D30(v, c, d);
            func_00282CF0(s, sp, v);
            break;
        case 9:
        case 10:
            func_00282D30(out, c, func_00282DB0(sp, c));
            func_00282CF0(s, sp, out);
            func_00282D08(out, out, s->a20, D_L00_001B1574);
            break;
        default:
            func_00282D30(out, c, func_00282DB0(sp, c));
            func_00282CF0(s, sp, out);
            break;
        }
    }
}
