/* func_L00_002A7E60 (shared, 27 places): hero weapon-glow update, a switch on hero+0x1248 over 17 weapon ids.
 * One function (one prologue, one jr $ra); jump table jtbl_0029FEF0.
 * func_L00_0033E220 takes its two floats as the 4th and 7th parameters (EABI gives floats their own
 * registers, so the integer registers are unchanged): the argument moves are emitted in parameter order,
 * which is what puts case 42's first `mov.s $f12` / `mov.s $f13` among the integer moves.
 * Spellings that mattered: `ph = &hero->f124C` hoisted before the switch; one block-local `f32 t` per arm;
 * `m = M; if (alpha < m) m = alpha;` in its own block per arm; case 30 armed writes the whole outer statement
 * in each 22B8 arm so the arms cross-jump; case 18 builds the colour in a fresh temp over separate statements.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
#define F(b, T, o) (((struct { u8 pad[o]; T v; } *)(b))->v)
#define HERO(T, o) F(D_00189E20, T, o)
#define NULL ((void *)0)

extern u8 D_00189E20[];
extern u8 D_00139568[];
extern u8 D_L00_00262570[];

extern float func_00283198(float);
extern float func_00283B98(float, float);
extern int func_00283CF0(float);
extern int func_00283D38(int, int, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_L00_002A7DE8(void *, int, float, float);
extern void func_L00_0033E220(void *, void *, int, float, int, int, float, int, int, int);

#define ARMED(k) (F(D_L00_00262570 + D_00139568[k] * 0xE0, u8, 4) != 0)
#define CAP(a, m) ((a) < (m) ? (a) : (m))

void func_L00_002A7E60(void)
{
    u8 *moby;
    s32 alpha;
    f32 *ph;
    f32 v[4] __attribute__((aligned(16)));
    f32 w[4] __attribute__((aligned(16)));

    moby = HERO(u8 *, 0x1220);
    if (moby == NULL) {
        return;
    }
    if (HERO(s32, 0x2294) == 0x61) {
        return;
    }
    if (!((F(moby, u16, 0x34) ^ 1) & 1)) {
        return;
    }
    if (HERO(s32, 0x1240) < 0x17) {
        return;
    }
    alpha = HERO(s32, 0x1240) - 0xF;
    if (alpha > 0x40) {
        alpha = 0x40;
    }
    if (alpha < 0) {
        alpha = 0;
    }
    alpha = (alpha << 24) | 0xFFFFFF;
    ph = &HERO(f32, 0x124C);

    switch (HERO(s32, 0x1248)) {
    case 18: {
        f32 t;
        s32 r, g, b, c;
        f32 rate = 0.037815474f;
        if (HERO(u8, 0x22B8) != 0) {
            rate = 0.12217307f;
        }
        t = FastAddRotations(*ph, rate);
        *ph = t;
        if (HERO(u8, 0x22B8) != 0) {
            r = FloatToInt(func_00283198(t) * 30.0f) + 0x32;
            g = FloatToInt(func_00283198(t) * 30.0f) + 0x32;
            b = FloatToInt(func_00283198(t) * 90.0f) + 0xAA;
        } else {
            r = FloatToInt(func_00283198(t) * 70.0f) + 0x64;
            g = FloatToInt(func_00283198(t) * 40.0f) + 0x46;
            b = FloatToInt(func_00283198(t) * 40.0f) + 0x46;
        }
        c = (b << 16) | 0x80000000;
        c |= g << 8;
        F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), c | r, 0.15f);
        break;
    }
    case 14: {
        f32 t;
        s32 c;
        t = FastAddRotations(*ph, 0.078539826f);
        *ph = t;
        c = 0x2814D214;
        if (t > 0.0f && t < 2.0943954f) {
            c = 0x281414D2;
        }
        F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), c, 0.05f);
        func_0029FCC0(moby, 0, v);
        func_L00_002A7DE8(v, F(moby, s32, 0x78), 0.1f, 0.03f);
        break;
    }
    case 42:
        if (ARMED(42)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF204090, 0xFF804040, func_00283198(t) * 0.5f + 0.5f);
            *(TI128 *)v = 0;
            v[2] = 0.1263f;
            v[0] = 0.423f;
            v[1] = -0.0555f;
            func_L00_0033E220(v, moby, F(moby, s32, 0x78) & 0x40FFFFFF, 57750.0f, -1, 1, 0.15f, 2, 0, -1);
            *(TI128 *)w = 0;
            w[0] = 0.423f;
            w[1] = -0.0555f;
            w[2] = -0.1263f;
            func_L00_0033E220(w, moby, F(moby, s32, 0x78) & 0x40FFFFFF, 57750.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            f32 t;
            t = FastAddRotations(*ph, 0.052359886f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f);
            *(TI128 *)v = 0;
            v[0] = 0.333f;
            v[1] = -0.05f;
            func_L00_0033E220(v, moby, F(moby, s32, 0x78) & 0x35FFFFFF, 73500.0f, -1, 1, 0.15f, 2, 0, -1);
        }
        break;
    case 30:
        if (ARMED(30)) {
            if (HERO(u8, 0x22B8) != 0) {
                f32 t;
                t = FastAddRotations(*ph, 0.20362177f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0040FF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f), 0.15f);
            } else {
                f32 t;
                t = FastAddRotations(*ph, 0.040724356f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0040AA, 0xFF104046, func_00283198(t) * 0.5f + 0.5f), 0.15f);
            }
            F(moby, s32, 0x78) = FastTweenColor(0xFF0020FF, 0xFF104080, func_00283198(*ph) * 0.5f + 0.5f);
            *(TI128 *)v = 0;
            v[0] = -0.059f;
            v[1] = -0.516f;
            {
                s32 m = 0x40FFFFFF;
                if (alpha < m) {
                    m = alpha;
                }
                func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 77700.0f, -1, 1, 0.2f, 2, 0, -1);
            }
        } else {
            *(TI128 *)v = 0;
            v[0] = 0.195f;
            v[1] = -0.317f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 t;
                t = FastAddRotations(*ph, 0.1163553f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0040FF, 0xFF10BEBE, func_00283198(t) * 0.5f + 0.5f), 0.22f);
                {
                    s32 m = 0x32FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 50400.0f, -1, 1, 0.15f, 2, 0, -1);
                }
            } else {
                f32 t;
                t = FastAddRotations(*ph, 0.040724356f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0028C8, 0xFF10B4B4, func_00283198(t) * 0.5f + 0.5f), 0.15f);
                {
                    s32 m = 0x38FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 50400.0f, -1, 1, 0.15f, 2, 0, -1);
                }
            }
        }
        break;
    case 29:
        if (ARMED(29)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f);
            *(TI128 *)v = 0;
            v[0] = -0.07f;
            v[1] = -0.67f;
            func_L00_0033E220(v, moby, F(moby, s32, 0x78) & 0x30FFFFFF, 99750.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)v = 0;
            v[0] = 0.06f;
            v[1] = -0.509f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 t;
                t = FastAddRotations(*ph, 0.10762865f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x28FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 57750.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 t;
                t = FastAddRotations(*ph, 0.05817765f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x30FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 73500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 16:
        if (ARMED(16)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF00BFFF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f);
            *(TI128 *)v = 0;
            v[0] = 0.16f;
            v[1] = -0.41f;
            func_L00_0033E220(v, moby, F(moby, s32, 0x78) & 0x30FFFFFF, 105000.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)v = 0;
            v[0] = 0.16f;
            v[1] = -0.41f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 t;
                t = FastAddRotations(*ph, 0.10762865f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00BFEF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x28FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 t;
                t = FastAddRotations(*ph, 0.05817765f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00BFEF, 0xFF104080, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x30FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 22:
        if (ARMED(22)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFFFF20BF, 0xFFFF2070, func_00283198(t) * 0.5f + 0.5f);
        } else {
            f32 t;
            t = FastAddRotations(*ph, 0.05817765f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFFFF20FF, 0xFFFF2090, func_00283198(t) * 0.5f + 0.5f);
        }
        break;
    case 24:
        if (ARMED(24)) {
            f32 t;
            t = FastAddRotations(*ph, 0.046542123f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFEFEFEF, func_00283198(t) * 0.5f + 0.5f);
            *(TI128 *)v = 0;
            v[0] = -0.158f;
            v[1] = -0.194f;
            func_L00_0033E220(v, moby, F(moby, s32, 0x78) & 0x30FFFFFF, 109199.99f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)v = 0;
            v[0] = -0.158f;
            v[1] = -0.194f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 t;
                t = FastAddRotations(*ph, 0.10762865f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFFFF2050, 0xFFFF2080, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x28FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 98700.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 t;
                t = FastAddRotations(*ph, 0.05817765f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFFFF2050, 0xFFFF2080, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x30FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 98700.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 25:
        if (ARMED(25)) {
            f32 t;
            t = FastAddRotations(*ph, 0.046542123f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFDFDFDF, func_00283198(t) * 0.5f + 0.5f);
            *(TI128 *)v = 0;
            v[0] = 0.05f;
            v[1] = -0.35f;
            func_L00_0033E220(v, moby, F(moby, s32, 0x78) & 0x15FFFFFF, 102900.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)v = 0;
            v[0] = 0.05f;
            v[1] = -0.45f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 t;
                t = FastAddRotations(*ph, 0.10762865f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFDFDFDF, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x20FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 t;
                t = FastAddRotations(*ph, 0.06399541f);
                *ph = t;
                F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFDFDFDF, func_00283198(t) * 0.5f + 0.5f);
                {
                    s32 m = 0x30FFFFFF;
                    if (alpha < m) {
                        m = alpha;
                    }
                    func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 26:
        if (ARMED(26)) {
            f32 t;
            t = FastAddRotations(*ph, 0.043633237f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFFDFDFDF, 0xFF20205F, func_00283198(t) * 0.5f + 0.5f);
        } else {
            f32 t;
            t = FastAddRotations(*ph, 0.05817765f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFFDFDFDF, 0xFF20205F, func_00283198(t) * 0.5f + 0.5f);
        }
        break;
    case 27:
        if (ARMED(27)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF20205F, 0xFFDFDFDF, func_00283198(t) * 0.5f + 0.5f);
        }
        break;
    case 28:
        if (ARMED(28)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF202020, 0xFFEFEFEF, func_00283198(t) * 0.5f + 0.5f);
        } else {
            f32 t;
            t = FastAddRotations(*ph, 0.05817765f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF202020, 0xFFEFEFEF, func_00283198(t) * 0.5f + 0.5f);
        }
        break;
    case 32:
        if (ARMED(32)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, func_00283198(t) * 0.5f + 0.5f);
        } else {
            f32 t;
            t = FastAddRotations(*ph, 0.049451005f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, func_00283198(t) * 0.5f + 0.5f);
        }
        break;
    case 41:
        if (ARMED(41)) {
            f32 t;
            t = FastAddRotations(*ph, 0.040724356f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, func_00283198(t) * 0.5f + 0.5f);
        } else {
            f32 t;
            t = FastAddRotations(*ph, 0.049451005f);
            *ph = t;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, func_00283198(t) * 0.5f + 0.5f);
        }
        break;
    case 23:
        if (ARMED(23)) {
            func_0029FCC0(moby, 1, v);
            func_L00_002A7DE8(v, 0x7F1010FF, 0.14f, 0.03f);
            *(TI128 *)w = 0;
            w[0] = 0.399f;
            w[1] = 0.035f;
            func_L00_0033E220(w, moby, 0x7F1010FF, 42000.0f, -1, 1, 0.0f, 2, 0, -1);
        } else {
            func_0029FCC0(moby, 2, v);
            func_L00_002A7DE8(v, 0x3500FF10, 0.1f, 0.03f);
            func_0029FCC0(moby, 3, v);
            func_L00_002A7DE8(v, 0x3500FF10, 0.1f, 0.03f);
        }
        break;
    case 43: {
        f32 t;
        *(TI128 *)v = 0;
        v[0] = -0.1245f;
        v[1] = -0.8f;
        t = FastAddRotations(*ph, 0.06399541f);
        *ph = t;
        F(moby, s32, 0x78) = FastTweenColor(0xFF9F4F7F, 0xFFDFDFDF, func_00283198(t) * 0.5f + 0.5f);
        {
            s32 m = 0x20FFFFFF;
            if (alpha < m) {
                m = alpha;
            }
            func_L00_0033E220(v, moby, F(moby, s32, 0x78) & m, 76650.0f, -1, 1, 0.1f, 2, 0, -1);
        }
        func_0029FCC0(moby, 0, w);
        func_L00_002A7DE8(w, 0x421010FF, 0.031f, 0.03f);
        break;
    }
    case 44: {
        f32 t;
        t = FastAddRotations(*ph, 0.031997707f);
        *ph = t;
        F(moby, s32, 0x78) = FastTweenColor(0xFFDF6060, 0xFFDFBFBF, func_00283198(t) * 0.5f + 0.5f);
        break;
    }
    }
}
