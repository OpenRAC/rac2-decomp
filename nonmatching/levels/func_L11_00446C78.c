/* func_L11_00446C78 - 576 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Flags -O2 -G8 -ffunction-sections -Wa,-G32 (new unit L11_00446C78-g8.c).
   First loop matches only with a struct view (value[4],phase[4],rate[4] at
   0x90) so the giv base is 0xB0. Remaining: register numbers (retail
   state=s3, i=s1, vec ptr=s2, j=s4), the 'addiu s2,sp,0x10' is hoisted to the
   prologue in mine (retail: after blez), sq $zero store needs a pointer-
   variable address (array address gives por). Size 568/576. Counts from old
   d.sh unreliable. */

#include "common.h"

typedef int Quadword __attribute__((mode(TI)));

typedef struct {
    char pad[0x90];
    float value[4];
    float phase[4];
    float rate[4];
} FlickerState;

extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002C3150(void *, void *, int, int, int, int, float);

extern float D_L11_001B1590 __attribute__((sda));
extern float D_L11_001B1594;
extern float D_L11_001B1598 __attribute__((sda));
extern float D_L11_001B159C;
extern float D_L11_001B1900 __attribute__((sda));
extern float D_L11_001B1904;
extern float D_L11_001B1908 __attribute__((sda));
extern float D_L11_001B190C;
extern int D_L11_001B1910 __attribute__((sda));
extern int D_L11_001B1914;
extern int D_L11_001B1918 __attribute__((sda));
extern int D_L11_001B191C;
extern float D_L11_001B1920 __attribute__((sda));
extern float D_L11_001B1924;
extern int D_L11_001B1928 __attribute__((sda));
extern float D_L11_001B1930[4] __attribute__((sda));
extern char *D_L11_001B359C;

/* Advances the four flicker phases of the object and, once per frame of the burst count,
   fires one particle from the object's position. */
void func_L11_00446C78(char *object) {
    int i;
    char *state = *(char **)(object + 0x68);
    FlickerState *flicker = (FlickerState *)state;
    float pos[4];
    float vel[4];
    int j;

    for (i = 0; i < 4; i++) {
        flicker->phase[i] += flicker->rate[i];
        if (flicker->phase[i] >= 1.0f) {
            flicker->phase[i] = 0.0f;
            flicker->rate[i] = func_002A7878(D_L11_001B1590, D_L11_001B1594) * 0.016666668f;
            flicker->value[i] = func_002A7878(D_L11_001B1598, D_L11_001B159C);
        }
    }
    for (j = 0; j < D_L11_001B1928; j++) {
        float *vp = vel;
        float angle;
        float radius;
        int effect;
        int color;

        *(Quadword *)vp = 0;
        vel[2] = func_002A7878(D_L11_001B1900, D_L11_001B1904) * 0.016666668f;
        func_00283098(vp, vp, D_L11_001B359C + *(int *)(state + 0x1D0) * 256 + 0xC0);
        angle = func_002A7940();
        radius = func_002A7878(D_L11_001B1920, D_L11_001B1924);
        pos[0] = func_00283180(angle) * radius;
        pos[1] = func_00283198(angle) * radius;
        pos[2] = 0.0f;
        func_00283098(pos, pos, D_L11_001B359C + *(int *)(state + 0x1D0) * 256 + 0xC0);
        func_00282CC0(pos, pos, D_L11_001B359C + *(int *)(state + 0x1D0) * 256 + 0x10);
        func_00282CC0(pos, pos, D_L11_001B1930);
        color = func_002A7820(D_L11_001B1918, D_L11_001B191C);
        radius = func_002A7878(D_L11_001B1908, D_L11_001B190C);
        effect = D_L11_001B1910;
        if (func_002A77E0(2) == 0)
            effect = D_L11_001B1914;
        func_002C3150(pos, vp, effect, color & 0xFF, func_002A77E0(255) & 0xFF, 0, radius);
    }
}
