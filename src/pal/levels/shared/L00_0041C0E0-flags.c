#include "include_asm.h"

#include "common.h"
typedef int Q16_F417A40 __attribute__((mode(TI)));
typedef union { Q16_F417A40 q; float f[4]; } V4_F417A40;
extern float func_002A7878(float low, float high);
extern float func_002A78D8(float low, float high);
extern void func_00282C88(void *p);
extern void func_00283098(void *out, void *in, void *matrix);
extern void func_00282CC0(void *out, void *a, void *b);
extern char D_L00_0025A920[];

/* Claims the first free record of the twenty-four 0xB0-byte records at D_L00_0025A920 for the
   owner, starts it at the owner (or at an offset from the owner's parent) and fills it with
   eighteen drawn values. */
void func_PAL_L00_0041CBB8(char *owner, char *vel, int life)
{
    char *base = D_L00_0025A920;
    char *info = *(char **)(owner + 0x68);
    char *origin = owner + 0x10;
    char *slot;
    V4_F417A40 pos, offset;
    int i;

    for (i = 0; i < 24; i++) {
        slot = base + i * 0xB0;
        if (*(int *)(slot + 0x9C) != 0)
            continue;
        *(char **)(slot + 0x9C) = owner;
        if (*(int *)(info + 4) == 0) {
            *(Q16_F417A40 *)(slot + 0x20) = *(Q16_F417A40 *)origin;
        } else {
            offset.q = 0;
            offset.f[0] = -0.15f;
            offset.f[1] = -0.8f;
            offset.f[3] = 1.0f;
            func_00283098(&pos, &offset, *(char **)(info + 8) + 0xC0);
            func_00282CC0(&pos, &pos, *(char **)(info + 8) + 0x10);
            *(Q16_F417A40 *)(slot + 0x20) = pos.q;
        }
        *(Q16_F417A40 *)(slot + 0x40) = *(Q16_F417A40 *)vel;
        *(float *)(slot + 0x20) += func_002A7878(-0.1f, 0.1f);
        *(float *)(slot + 0x24) += func_002A7878(-0.1f, 0.1f);
        *(float *)(slot + 0x28) += func_002A7878(-0.1f, 0.1f);
        *(float *)(slot + 0x50) = func_002A7878(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x54) = func_002A7878(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x58) = func_002A7878(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x74) = func_002A7878(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x78) = func_002A7878(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x7C) = func_002A7878(-3.14159274f, 3.14159274f);
        *(float *)(slot + 0x5C) = func_002A78D8(0.001f, 0.005f);
        *(float *)(slot + 0x60) = func_002A78D8(0.001f, 0.005f);
        *(float *)(slot + 0x64) = func_002A78D8(0.001f, 0.005f);
        *(float *)(slot + 0x80) = func_002A78D8(0.001f, 0.005f);
        *(float *)(slot + 0x84) = func_002A78D8(0.001f, 0.005f);
        *(float *)(slot + 0x88) = func_002A78D8(0.001f, 0.005f);
        *(float *)(slot + 0x68) = func_002A7878(3.25f, 4.75f);
        *(float *)(slot + 0x6C) = func_002A7878(3.25f, 4.75f);
        *(float *)(slot + 0x70) = func_002A7878(3.25f, 4.75f);
        *(float *)(slot + 0x8C) = func_002A7878(3.25f, 4.75f);
        *(float *)(slot + 0x90) = func_002A7878(3.25f, 4.75f);
        *(float *)(slot + 0x94) = func_002A7878(3.25f, 4.75f);
        func_00282C88(slot);
        func_00282C88(slot + 0x10);
        *(int *)(slot + 0x98) = 17;
        *(int *)(slot + 0xA8) = 0;
        *(int *)(slot + 0xA0) = life;
        *(int *)(slot + 0xA4) = life;
        break;
    }
}
