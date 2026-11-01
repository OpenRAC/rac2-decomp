#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void func_00282C88(char *block);
extern float func_002A7878(float a, float b);
extern char *func_002ED688(char *object);
extern int func_L00_00367720(char *object);
extern void func_L05_00379E60(char *object, int a1, int a2, int a3);
extern void func_PAL_002A7E68(char *object, int a1, int a2, int a3);
extern void func_PAL_L05_0037E8E0(char *object);
extern void func_L05_0037B538(char *object, int a1, int a2, int a3);
extern void func_L05_0037B948(char *object, int a1, float a2);
extern int func_L05_0037B888(char *object);
extern void func_PAL_L05_0037DE20(char *object);
extern void func_00282948(char *block);
extern int func_00283DB8(char *buf, float value);
extern void func_L00_002E6EF8(void *fn, char *object);
extern void func_L00_003E4948(void);
extern char D_L05_002681E0[];
extern char *D_L05_001B251C __attribute__((sda));
extern void func_PAL_L05_00421928(char *object);
typedef struct {
    char pad0[0x104];
    int x104, x108, pad10C, mode, pad114, pad118;
    int has_target;
    char *target;
} Target05;
extern void func_PAL_L05_00421BC0(char *object);
extern void func_PAL_L05_00421830(char *obj);

/* Per-frame update. On the first frame it initializes the object and, if state+0x264 is set, clears
   the owners of the 128 interpolation records; afterwards it points the record at moby state+0x260
   and runs func_PAL_L05_00421BC0 unless func_00283DB8 returns -1 for the object's position. */
void func_PAL_L05_00421620(char *object)
{
    char *state = *(char **)(object + 0x68);
    Target05 *r;
    Vec buf;

    if (*(unsigned char *)(object + 0x20) == 0) {
        *(unsigned char *)(object + 0x30) = 0xFF;
        if (func_L00_00367720(object) == 0)
            return;
        func_PAL_L05_00421830(object);
        func_PAL_002A7E68(object, 1, 0, 0);
        func_00282C88((char *)&buf);
        *(float *)(object + 0x48) = func_002A7878(0.9f, 1.1f);
        if (*(int *)(state + 0x264) != 0) {
            char *base;
            int *p;
            int i;

            func_L05_00379E60(object, 0, 0, 0);
            base = D_L05_002681E0;
            p = (int *)(base + 0x27F0);
            i = 0x7F;
            do {
                *p = 0;
                p -= 0x14;
                i--;
            } while (i >= 0);
        }
        return;
    }
    r = (Target05 *)func_002ED688(object);
    if (r->mode == 0)
        return;
    {
        int one = 1;

        func_PAL_L05_0037E8E0(object);
        func_L05_0037B538(object, 0, 0, 0);
        func_L05_0037B948(object, one, 64.0f);
        if (r->mode == one) {
            if (*(int *)(state + 0x260) != -1) {
                r->has_target = 1;
                r->target = D_L05_001B251C + *(int *)(state + 0x260) * 256;
            }
            if (r->x108 != 0 && r->x104 != 0)
                func_PAL_L05_00421928(object);
            if (func_L05_0037B888(object) != 0)
                func_PAL_L05_0037DE20(object);
            func_00282948(state + 0x268);
            qcopy(&buf, object + 0x10);
            buf.f[3] = *(float *)(object + 0xC) * 0.00097656f;
            if (func_00283DB8((char *)&buf, 100.0f) != -1)
                func_PAL_L05_00421BC0(object);
        }
    }
    func_L00_002E6EF8(func_L00_003E4948, object);
}
