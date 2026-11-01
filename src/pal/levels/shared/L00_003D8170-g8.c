#include "include_asm.h"

#include "common.h"
extern int ref_L00_003D40D8_00(float *);
extern int D_L00_001B19C8 __attribute__((sda));
extern float D_L00_001B0250 __attribute__((sda));
extern float D_L00_001B0254 __attribute__((sda));
extern float D_L00_001B0258 __attribute__((sda));
extern float D_L00_001B025C __attribute__((sda));
extern float D_L00_001B0260 __attribute__((sda));
extern int D_L00_001B029C __attribute__((sda));
extern float D_L00_001B02A0 __attribute__((sda));
extern float D_L00_001B02A4 __attribute__((sda));
extern float D_L00_001B02A8 __attribute__((sda));
extern char D_L00_001B8FF0[];
extern char D_00189EA0[];
extern char D_L00_001A8F20[] __attribute__((sda));
extern char D_L00_00262570[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern unsigned char D_00139587 __attribute__((nosda));
extern unsigned char *D_L00_001FEA14 __attribute__((nosda));
extern void ref_L00_003D40D8_01(char *,int,float *);
extern char *ref_L00_003D40D8_02(float *,char *,int,float,float,float,float,float);
extern void ref_L00_003D40D8_03(char *,int,int,int);
extern void ref_L00_003D40D8_04(float *,void *,void *);
extern float ref_L00_003D40D8_05(float *,void *);
extern char *ref_L00_003D40D8_06(char *);
extern int ref_L00_003D40D8_07(int);
extern char *ref_L00_003D40D8_08(float *,char *,int,int,int,int,int,float,float,float,int);
extern void ref_L00_003D40D8_09(float *,float *,float);
extern void ref_L00_003D40D8_10(float *,float *,float *);
extern float ref_L00_003D40D8_11(float *,float *,int,float,float);
extern char *ref_L00_003D40D8_12(char *,float *,float *,int,float);
extern int ref_L00_003D40D8_13(int,int,char *);
extern void ref_L00_003D40D8_14(float *,char *,char *);
extern float ref_L00_003D40D8_15(float,float);
typedef struct {
    char reserved[0x24];
    unsigned char alternate, shots;
    char reserved26[2];
    char *target;
    char reserved2c[0xc];
    int frame;
    float cooldown;
    int reserved40;
    short charges;
} EffectLauncherState;

/* Per-frame fire step: on its cooldown and frame slot, looks for a target (skipping some
 * classes), aims, spawns two particles, fires one of two shot kinds (the first while charges
 * remain) and restarts the cooldown from the weapon table's rate at +0x54. */
void func_PAL_L00_003D8170(unsigned char *p, EffectLauncherState *s)
{
    float pos[4], delta[4], target[4], step[4], velocity[4];
    char *obj;
    int n;
    float angle;

    if (!ref_L00_003D40D8_00(&s->cooldown))
        return;
    if (D_L00_001B19C8 % 4 != s->frame)
        return;
    ref_L00_003D40D8_01(p, 1, pos);
    s->alternate ^= 1;
    obj = ref_L00_003D40D8_02(pos, D_L00_001B8FF0, 0,
                              D_L00_001B0254 * 0.017453294f, D_L00_001B0258 * 0.017453294f,
                              D_L00_001B0250,
                              D_L00_001B0254 * 0.017453294f, D_L00_001B0258 * 0.017453294f);
    if (obj) {
        if ((*(short *)(obj + 0xaa) == 0xee1 || *(short *)(obj + 0xaa) == 0xec0
             || *(short *)(obj + 0xaa) == 0xed4)
            && *(unsigned char *)(*(char **)(obj + 0x68) + 0x3b1) == 255) {
            s->target = 0;
            return;
        }
        if (*(short *)(obj + 0xaa) == 0xef4) {
            s->target = 0;
            return;
        }
        s->target = obj;
        if ((unsigned char)p[0x43] != 2)
            ref_L00_003D40D8_03(p, 2, 0, 4);
        ref_L00_003D40D8_04(delta, p + 0x10, D_00189EA0);
        angle = ref_L00_003D40D8_05(delta, p + 0xe0);
        if (D_L00_001A8F00 == 2 || p[0x42] != p[0x43] || (unsigned char)p[0x42] != 2
            || !(angle > 1.1f))
            return;
        qcopy(target, obj + 0x10);
        {
            char *v = ref_L00_003D40D8_06(obj);

            if (v)
                target[2] += *(float *)(v + 0x10);
            else
                target[2] += D_L00_001B0260;
        }
        n = ref_L00_003D40D8_07(255);
        {
            char *result = ref_L00_003D40D8_08(pos, D_L00_001A8F20, 2, 0x202080, n, 127, 16,
                                               420000.0f, 420000.0f, 0.0f, 0);

            if (result)
                result[2] = *D_L00_001FEA14;
        }
        {
            char *result = ref_L00_003D40D8_08(pos, D_L00_001A8F20, 2, 0x601080, (n + 128) % 255,
                                               127, 16, 420000.0f, 420000.0f, 0.0f, 0);

            if (result)
                result[2] = *D_L00_001FEA14;
        }
        ref_L00_003D40D8_04(step, target, pos);
        ref_L00_003D40D8_09(step, step, D_L00_001B025C);
        ref_L00_003D40D8_10(pos, pos, step);
        if (s->charges && !ref_L00_003D40D8_07(D_L00_001B029C)) {
            float f;
            char *result;

            if (--s->charges < 0)
                s->charges = 0;
            f = ref_L00_003D40D8_11(pos, target, 0, D_L00_001B02A0 * 0.020000001f,
                                    -(D_L00_001B02A4 * 0.00040000002f));
            ref_L00_003D40D8_04(velocity, target, pos);
            velocity[2] = 0;
            ref_L00_003D40D8_09(velocity, velocity, D_L00_001B02A0 * 0.020000001f);
            velocity[2] = f;
            result = ref_L00_003D40D8_12(p, pos, velocity, 150, D_L00_001B02A4 * 0.00040000002f);
            ref_L00_003D40D8_13(3, 0, p);
            *(float *)(result + 0x2c) = D_L00_001B02A8;
        } else {
            ref_L00_003D40D8_14(pos, p, obj);
            ref_L00_003D40D8_13(0, 0, p);
        }
        {
            char *v = D_L00_00262570 + D_00139587 * 0xe0;
            float f = ref_L00_003D40D8_15(0.0f, 0.17f);
            float delay = 1.0f / *(float *)(v + 0x54);

            ++s->shots;
            s->cooldown = delay + f;
        }
        return;
    }
    s->target = 0;
}
