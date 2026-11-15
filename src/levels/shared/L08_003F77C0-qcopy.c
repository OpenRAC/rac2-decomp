#include "include_asm.h"
/* func_L08_003F77C0: the level-08 sparkle seeding, the twin of func_L00_00382CE8 with its own
 * table, colour base, life and scale constants and twelve slots. */
#include "common.h"
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern float func_00283C80(float,float);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern float func_002A7940(void);
extern int func_002A77E0(int);
extern void func_002AF000(float *,float,float,float);
extern char *func_002C2210(void *,int,unsigned int,int,int,void *,int,float,float,float);
typedef struct {
    void *owner;
    int active;
    char pad08[8];
    short size[16];
    short life[16];
    unsigned int color[16];
    float phase[16];
    float scale[16];
} Sparkle;
extern Sparkle D_L08_001B9E00;
/* Starts a set of eleven randomly coloured sparkles for the owner (once only), picking each
   one's colour, lifetime and size. */
void func_L08_003F77C0(void *owner)
{
    int i, intensity, colorMode, red;
    unsigned int baseColor;
    int greenPart;
    float phase;
    if (D_L08_001B9E00.active == 1) return;
    D_L08_001B9E00.owner = owner;
    D_L08_001B9E00.active = 1;
    i = 1;
    baseColor = 0x706080;
    for (; i < 12; ++i) {
        intensity = RandomIntBelow(63) + 1;
        colorMode = RandomIntBelow(6);
        switch (colorMode) {
        case 0: D_L08_001B9E00.color[i] = intensity + baseColor - (intensity << 16); break;
        case 1: D_L08_001B9E00.color[i] = (intensity << 8) + (intensity + baseColor); break;
        case 2: D_L08_001B9E00.color[i] = (RandomIntBelow(intensity) << 8) + (intensity + baseColor); break;
        case 3:
            red = RandomIntBelow(intensity);
            greenPart = (RandomIntBelow(intensity) << 8) + baseColor;
            D_L08_001B9E00.color[i] = (red << 16) + greenPart + intensity; break;
        default: D_L08_001B9E00.color[i] = baseColor; break;
        }
        D_L08_001B9E00.life[i] = RandomIntBelow(3) + 1;
        phase = RandomFloatRange(-0.95f, 2.5f);
        D_L08_001B9E00.phase[i] = phase;
        phase = FloatAbs(FastSinOrCosA(FastFloatHelperG(phase + 1)));
        D_L08_001B9E00.scale[i] = phase * phase * phase * 1.7f;
        D_L08_001B9E00.size[i] = 23;
    }
    D_L08_001B9E00.phase[0] = -1;
    D_L08_001B9E00.scale[0] = 2;
    D_L08_001B9E00.color[0] = 0x808080;
    D_L08_001B9E00.life[0] = 0;
    D_L08_001B9E00.size[0] = 127;
}
