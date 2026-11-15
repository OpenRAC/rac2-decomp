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

/* Makes the equipped item glow and pulse in the hero's hand. Each item type has its own colors, speed and sparkle spots. */
void func_L00_002A7E60(void)
{
    u8 *moby;
    s32 maxAlpha;
    f32 *phase;
    f32 glowPos[4] __attribute__((aligned(16)));
    f32 glowPos2[4] __attribute__((aligned(16)));

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
    maxAlpha = HERO(s32, 0x1240) - 0xF;
    if (maxAlpha > 0x40) {
        maxAlpha = 0x40;
    }
    if (maxAlpha < 0) {
        maxAlpha = 0;
    }
    maxAlpha = (maxAlpha << 24) | 0xFFFFFF;
    phase = &HERO(f32, 0x124C);

    switch (HERO(s32, 0x1248)) {
    case 18: {
        f32 wave;
        s32 red, green, blue, color;
        f32 rate = 0.037815474f;
        if (HERO(u8, 0x22B8) != 0) {
            rate = 0.12217307f;
        }
        wave = FastAddRotations(*phase, rate);
        *phase = wave;
        if (HERO(u8, 0x22B8) != 0) {
            red = FloatToInt(FastSinOrCosB(wave) * 30.0f) + 0x32;
            green = FloatToInt(FastSinOrCosB(wave) * 30.0f) + 0x32;
            blue = FloatToInt(FastSinOrCosB(wave) * 90.0f) + 0xAA;
        } else {
            red = FloatToInt(FastSinOrCosB(wave) * 70.0f) + 0x64;
            green = FloatToInt(FastSinOrCosB(wave) * 40.0f) + 0x46;
            blue = FloatToInt(FastSinOrCosB(wave) * 40.0f) + 0x46;
        }
        color = (blue << 16) | 0x80000000;
        color |= green << 8;
        F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), color | red, 0.15f);
        break;
    }
    case 14: {
        f32 wave;
        s32 color;
        wave = FastAddRotations(*phase, 0.078539826f);
        *phase = wave;
        color = 0x2814D214;
        if (wave > 0.0f && wave < 2.0943954f) {
            color = 0x281414D2;
        }
        F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), color, 0.05f);
        TransformMobyJointToWorld(moby, 0, glowPos);
        QueueHeroGlowPoint(glowPos, F(moby, s32, 0x78), 0.1f, 0.03f);
        break;
    }
    case 42:
        if (ARMED(42)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF204090, 0xFF804040, FastSinOrCosB(wave) * 0.5f + 0.5f);
            *(TI128 *)glowPos = 0;
            glowPos[2] = 0.1263f;
            glowPos[0] = 0.423f;
            glowPos[1] = -0.0555f;
            SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & 0x40FFFFFF, 57750.0f, -1, 1, 0.15f, 2, 0, -1);
            *(TI128 *)glowPos2 = 0;
            glowPos2[0] = 0.423f;
            glowPos2[1] = -0.0555f;
            glowPos2[2] = -0.1263f;
            SpawnObjectFollowingEffect(glowPos2, moby, F(moby, s32, 0x78) & 0x40FFFFFF, 57750.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            f32 wave;
            wave = FastAddRotations(*phase, 0.052359886f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f);
            *(TI128 *)glowPos = 0;
            glowPos[0] = 0.333f;
            glowPos[1] = -0.05f;
            SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & 0x35FFFFFF, 73500.0f, -1, 1, 0.15f, 2, 0, -1);
        }
        break;
    case 30:
        if (ARMED(30)) {
            if (HERO(u8, 0x22B8) != 0) {
                f32 wave;
                wave = FastAddRotations(*phase, 0.20362177f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0040FF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f), 0.15f);
            } else {
                f32 wave;
                wave = FastAddRotations(*phase, 0.040724356f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0040AA, 0xFF104046, FastSinOrCosB(wave) * 0.5f + 0.5f), 0.15f);
            }
            F(moby, s32, 0x78) = FastTweenColor(0xFF0020FF, 0xFF104080, FastSinOrCosB(*phase) * 0.5f + 0.5f);
            *(TI128 *)glowPos = 0;
            glowPos[0] = -0.059f;
            glowPos[1] = -0.516f;
            {
                s32 alphaMask = 0x40FFFFFF;
                if (maxAlpha < alphaMask) {
                    alphaMask = maxAlpha;
                }
                SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 77700.0f, -1, 1, 0.2f, 2, 0, -1);
            }
        } else {
            *(TI128 *)glowPos = 0;
            glowPos[0] = 0.195f;
            glowPos[1] = -0.317f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 wave;
                wave = FastAddRotations(*phase, 0.1163553f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0040FF, 0xFF10BEBE, FastSinOrCosB(wave) * 0.5f + 0.5f), 0.22f);
                {
                    s32 alphaMask = 0x32FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 50400.0f, -1, 1, 0.15f, 2, 0, -1);
                }
            } else {
                f32 wave;
                wave = FastAddRotations(*phase, 0.040724356f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(F(moby, s32, 0x78), FastTweenColor(0xFF0028C8, 0xFF10B4B4, FastSinOrCosB(wave) * 0.5f + 0.5f), 0.15f);
                {
                    s32 alphaMask = 0x38FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 50400.0f, -1, 1, 0.15f, 2, 0, -1);
                }
            }
        }
        break;
    case 29:
        if (ARMED(29)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f);
            *(TI128 *)glowPos = 0;
            glowPos[0] = -0.07f;
            glowPos[1] = -0.67f;
            SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & 0x30FFFFFF, 99750.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)glowPos = 0;
            glowPos[0] = 0.06f;
            glowPos[1] = -0.509f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 wave;
                wave = FastAddRotations(*phase, 0.10762865f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x28FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 57750.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 wave;
                wave = FastAddRotations(*phase, 0.05817765f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00FFFF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x30FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 73500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 16:
        if (ARMED(16)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF00BFFF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f);
            *(TI128 *)glowPos = 0;
            glowPos[0] = 0.16f;
            glowPos[1] = -0.41f;
            SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & 0x30FFFFFF, 105000.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)glowPos = 0;
            glowPos[0] = 0.16f;
            glowPos[1] = -0.41f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 wave;
                wave = FastAddRotations(*phase, 0.10762865f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00BFEF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x28FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 wave;
                wave = FastAddRotations(*phase, 0.05817765f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFF00BFEF, 0xFF104080, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x30FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 22:
        if (ARMED(22)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFFFF20BF, 0xFFFF2070, FastSinOrCosB(wave) * 0.5f + 0.5f);
        } else {
            f32 wave;
            wave = FastAddRotations(*phase, 0.05817765f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFFFF20FF, 0xFFFF2090, FastSinOrCosB(wave) * 0.5f + 0.5f);
        }
        break;
    case 24:
        if (ARMED(24)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.046542123f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFEFEFEF, FastSinOrCosB(wave) * 0.5f + 0.5f);
            *(TI128 *)glowPos = 0;
            glowPos[0] = -0.158f;
            glowPos[1] = -0.194f;
            SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & 0x30FFFFFF, 109199.99f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)glowPos = 0;
            glowPos[0] = -0.158f;
            glowPos[1] = -0.194f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 wave;
                wave = FastAddRotations(*phase, 0.10762865f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFFFF2050, 0xFFFF2080, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x28FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 98700.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 wave;
                wave = FastAddRotations(*phase, 0.05817765f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFFFF2050, 0xFFFF2080, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x30FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 98700.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 25:
        if (ARMED(25)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.046542123f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFDFDFDF, FastSinOrCosB(wave) * 0.5f + 0.5f);
            *(TI128 *)glowPos = 0;
            glowPos[0] = 0.05f;
            glowPos[1] = -0.35f;
            SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & 0x15FFFFFF, 102900.0f, -1, 1, 0.15f, 2, 0, -1);
        } else {
            *(TI128 *)glowPos = 0;
            glowPos[0] = 0.05f;
            glowPos[1] = -0.45f;
            if (HERO(u8, 0x22B8) != 0) {
                f32 wave;
                wave = FastAddRotations(*phase, 0.10762865f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFDFDFDF, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x20FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            } else {
                f32 wave;
                wave = FastAddRotations(*phase, 0.06399541f);
                *phase = wave;
                F(moby, s32, 0x78) = FastTweenColor(0xFF5F5F5F, 0xFFDFDFDF, FastSinOrCosB(wave) * 0.5f + 0.5f);
                {
                    s32 alphaMask = 0x30FFFFFF;
                    if (maxAlpha < alphaMask) {
                        alphaMask = maxAlpha;
                    }
                    SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 94500.0f, -1, 1, 0.1f, 2, 0, -1);
                }
            }
        }
        break;
    case 26:
        if (ARMED(26)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.043633237f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFFDFDFDF, 0xFF20205F, FastSinOrCosB(wave) * 0.5f + 0.5f);
        } else {
            f32 wave;
            wave = FastAddRotations(*phase, 0.05817765f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFFDFDFDF, 0xFF20205F, FastSinOrCosB(wave) * 0.5f + 0.5f);
        }
        break;
    case 27:
        if (ARMED(27)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF20205F, 0xFFDFDFDF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        }
        break;
    case 28:
        if (ARMED(28)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF202020, 0xFFEFEFEF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        } else {
            f32 wave;
            wave = FastAddRotations(*phase, 0.05817765f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF202020, 0xFFEFEFEF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        }
        break;
    case 32:
        if (ARMED(32)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        } else {
            f32 wave;
            wave = FastAddRotations(*phase, 0.049451005f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        }
        break;
    case 41:
        if (ARMED(41)) {
            f32 wave;
            wave = FastAddRotations(*phase, 0.040724356f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        } else {
            f32 wave;
            wave = FastAddRotations(*phase, 0.049451005f);
            *phase = wave;
            F(moby, s32, 0x78) = FastTweenColor(0xFF505050, 0xFFEFEFEF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        }
        break;
    case 23:
        if (ARMED(23)) {
            TransformMobyJointToWorld(moby, 1, glowPos);
            QueueHeroGlowPoint(glowPos, 0x7F1010FF, 0.14f, 0.03f);
            *(TI128 *)glowPos2 = 0;
            glowPos2[0] = 0.399f;
            glowPos2[1] = 0.035f;
            SpawnObjectFollowingEffect(glowPos2, moby, 0x7F1010FF, 42000.0f, -1, 1, 0.0f, 2, 0, -1);
        } else {
            TransformMobyJointToWorld(moby, 2, glowPos);
            QueueHeroGlowPoint(glowPos, 0x3500FF10, 0.1f, 0.03f);
            TransformMobyJointToWorld(moby, 3, glowPos);
            QueueHeroGlowPoint(glowPos, 0x3500FF10, 0.1f, 0.03f);
        }
        break;
    case 43: {
        f32 wave;
        *(TI128 *)glowPos = 0;
        glowPos[0] = -0.1245f;
        glowPos[1] = -0.8f;
        wave = FastAddRotations(*phase, 0.06399541f);
        *phase = wave;
        F(moby, s32, 0x78) = FastTweenColor(0xFF9F4F7F, 0xFFDFDFDF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        {
            s32 alphaMask = 0x20FFFFFF;
            if (maxAlpha < alphaMask) {
                alphaMask = maxAlpha;
            }
            SpawnObjectFollowingEffect(glowPos, moby, F(moby, s32, 0x78) & alphaMask, 76650.0f, -1, 1, 0.1f, 2, 0, -1);
        }
        TransformMobyJointToWorld(moby, 0, glowPos2);
        QueueHeroGlowPoint(glowPos2, 0x421010FF, 0.031f, 0.03f);
        break;
    }
    case 44: {
        f32 wave;
        wave = FastAddRotations(*phase, 0.031997707f);
        *phase = wave;
        F(moby, s32, 0x78) = FastTweenColor(0xFFDF6060, 0xFFDFBFBF, FastSinOrCosB(wave) * 0.5f + 0.5f);
        break;
    }
    }
}
