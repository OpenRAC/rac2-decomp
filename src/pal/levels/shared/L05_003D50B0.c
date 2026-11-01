#include "include_asm.h"


#include "common.h"
struct Sub_003D15E8 {
      char pad000[0x104];
      int f104;
      int f108;
      int pad10C;
      int mode;
      int pad114[2];
      int targetMode;
      char *target;
};
extern char *D_L05_001B251C MACRO_ADDR;
extern char D_00188660[];
extern int func_L00_00367720(char *);
extern struct Sub_003D15E8 *func_002ED688(char *);
extern void func_PAL_L05_003D5628(char *);
extern void func_00282C88(void *);
extern void func_L05_00379E60(char *, void *, int, int);
extern void func_L00_003CD158(void);
extern void func_0029F978(char *, int, void *);
extern void func_PAL_L05_0037E8E0(char *);
extern void func_L05_0037B538(char *, int, int, int);
extern void func_L05_0037B948(char *, int, float);
extern float func_00282E48(void *, void *);
extern int func_002A77E0(int);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002EE6A8(char *);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_PAL_L05_003D5738(char *);
extern int func_L05_0037B888(char *);
extern int func_L05_0037CE08(char *, int);
extern void func_L05_0037CDD8(char *, int);
extern void func_PAL_L05_0037DE20(char *);
extern void func_00282948(void *);
extern void func_PAL_L05_003D5800(char *);

/* The object's update: on its first frame it sets itself up; afterwards, while its record is
   active, it aims at the object its state names (with a chance of a sound when close), turns
   its two vectors, may take its next step, and keeps its looping sound playing. */
void func_PAL_L05_003D5330(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    struct Sub_003D15E8 *sub;
    float tmp[4];
    int one, mode;

    if (!*(unsigned char *)(obj + 0x20)) {
        *(unsigned char *)(obj + 0x30) = 0xff;
        if (!func_L00_00367720(obj))
            return;
        func_PAL_L05_003D5628(obj);
        func_00282C88(tmp);
        if (*(int *)(state + 0x264))
            func_L05_00379E60(obj, func_L00_003CD158, 0, 0);
        func_0029F978(obj, 2, state + 0x270);
        func_0029F978(obj, 3, state + 0x2b0);
        return;
    }
    sub = func_002ED688(obj);
    if (!sub->mode)
        return;
    one = 1;
    func_PAL_L05_0037E8E0(obj);
    func_L05_0037B538(obj, 0, 0, 0);
    func_L05_0037B948(obj, 1, 32.0f);
    mode = sub->mode;
    if (mode == one) {
        if (*(int *)(state + 0x260) != -1) {
            sub->targetMode = mode;
            sub->target = D_L05_001B251C + (*(int *)(state + 0x260) << 8);
            if (func_00282E48(sub->target + 0x10, obj + 0x10) < 10.0f) {
                char *sound1 = D_00188660 + *(int *)(state + 0x2f4) * 0x70;

                if ((*(char **)(sound1 + 0x88) != obj || !*(unsigned char *)(sound1 + 0x74))
                    && !func_002A77E0(750))
                    *(int *)(state + 0x2f4) = func_002E5DA0(14, 0, obj, 0xfbf);
            }
        }
        func_00282C88(state + 0x280);
        func_00282C88(state + 0x2c0);
        if (func_002EE6A8(obj) == 8) {
            *(float *)(state + 0x284) = func_00283198(0.78539824f);
            *(float *)(state + 0x28c) = func_00283180(0.78539824f);
            *(float *)(state + 0x2c4) = func_00283198(0.78539824f);
            *(float *)(state + 0x2cc) = func_00283180(0.78539824f);
            if (sub->f108)
                func_PAL_L05_003D5738(obj);
        } else {
            *(float *)(state + 0x2cc) = *(float *)(state + 0x28c) = 1.0f;
            if (sub->f108 && sub->f104)
                func_PAL_L05_003D5738(obj);
        }
        if (func_L05_0037B888(obj)) {
            if (func_L05_0037CE08(obj, 5) <= 0)
                func_L05_0037CDD8(obj, 5);
            else
                func_L05_0037CDD8(obj, 1);
            func_PAL_L05_0037DE20(obj);
        }
        func_00282948(state + 0x268);
        func_PAL_L05_003D5800(obj);
    }
    {
        char *sound2 = D_00188660 + *(int *)(state + 0x2f0) * 0x70;

        if (*(char **)(sound2 + 0x88) != obj || !*(unsigned char *)(sound2 + 0x74))
            *(int *)(state + 0x2f0) = func_002E5DA0(1, 6, obj, 0x97c);
    }
}



extern char *func_379CA0(char *);
extern void func_379FA0(char *, int, int, int, float, float, float, float, int, int, int);
extern int func_332AB8(int);
extern void func_3719A8(int, int, char *, int);

/* Spawns the object's effect after three guards, then runs the timer. */
void func_PAL_L05_003D5738(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *r;

    r = func_379CA0(object);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x268) != 0)
        return;
    func_379FA0(object, 0x60000090, 1, 0, 0.6f, 2.0f, 1.0f, 1.3f, 0, -1, 0);
    if (func_332AB8(3) == 0)
        func_3719A8(0, 0, object, 0x97C);
    *(int *)(s1 + 0x268) = 0x32;
}

