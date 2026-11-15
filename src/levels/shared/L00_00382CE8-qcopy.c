/* func_L00_00382CE8: seed the sparkle table (owner, per-slot colour, life, phase and scale).
 * The grey base colour is a local set after the index, so each case adds it in its own register. */
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
extern Sparkle D_L00_001B90C0;
/* Sets up the table of sparkles once: each gets a random colour, lifetime, phase and size. */
void func_L00_00382CE8(void *owner)
{
    int i, intensity, mode, component;
    unsigned int grey;
    int green;
    float value;
    if (D_L00_001B90C0.active == 1) return;
    D_L00_001B90C0.owner = owner;
    D_L00_001B90C0.active = 1;
    i = 1;
    grey = 0x202080;
    for (; i < 14; ++i) {
        intensity = RandomIntBelow(63) + 1;
        mode = RandomIntBelow(6);
        switch (mode) {
        case 0: D_L00_001B90C0.color[i] = intensity + grey - (intensity << 16); break;
        case 1: D_L00_001B90C0.color[i] = (intensity << 8) + (intensity + grey); break;
        case 2: D_L00_001B90C0.color[i] = (RandomIntBelow(intensity) << 8) + (intensity + grey); break;
        case 3:
            component = RandomIntBelow(intensity);
            green = (RandomIntBelow(intensity) << 8) + grey;
            D_L00_001B90C0.color[i] = (component << 16) + green + intensity; break;
        default: D_L00_001B90C0.color[i] = grey; break;
        }
        D_L00_001B90C0.life[i] = RandomIntBelow(30) / 10 + 1;
        value = RandomFloatRange(-0.95f, 2.4f);
        D_L00_001B90C0.phase[i] = value;
        value = FloatAbs(FastSinOrCosA(FastFloatHelperG(value + 1)));
        D_L00_001B90C0.scale[i] = value * value * value * 1.4f;
        D_L00_001B90C0.size[i] = 32;
    }
    D_L00_001B90C0.phase[0] = -1;
    D_L00_001B90C0.scale[0] = 2;
    D_L00_001B90C0.color[0] = 0x808080;
    D_L00_001B90C0.life[0] = 0;
    D_L00_001B90C0.size[0] = 127;
}
