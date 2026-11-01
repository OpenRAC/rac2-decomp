#include "include_asm.h"



extern void func_0032C700(void *a0, int a1, int a2, int a3, int a4, int a5, int a6,
                          int a7, float f12, float f13, int s1, int s2, int s3,
                          int s4);
extern void func_002A8C28(char *, char *, int, int, float, float, float, int, int);
extern void func_0029F338(char *object);

/* func_L20_00449FD0 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

void func_PAL_L20_0044FD80(char *arg0, char *arg1) {
    func_0032C700(arg0 + 0x10, 0, 5, 4, 4, 4, 7, 0, 0.333f, 20.0f, 0, 0, 0, 0);
    if (arg1 != 0) {
        func_002A8C28(*(char **)(arg0 + 0xB8), arg0 + 0x10, (int)arg1, 0, 1.5f,
                      4.0f, 1.0f, 1, 0);
    }
    func_0029F338(arg0);
}






typedef int TI128 __attribute__((mode(TI)));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002E59F8(int);

/* func_L20_0044A658 is defined in L20_00449178-g8.c (it reaches data through $gp). */

/* func_L20_0044A838 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

/* func_L20_0044A8F0 is defined in L20_00449178-g8.c (it reaches data through $gp). */

/* func_L20_0044AA88 is defined in L20_00449178-g8.c (this unit has no $gp access for it). */

void func_PAL_L20_004507E0(char *arg0) {
    union {
        TI128 q;
        float f[4];
    } v;
    char *state;

    v.q = 0;
    v.f[2] = 0.3f;
    func_00283098(&v, &v, arg0 + 0xC0);
    func_00282CC0(&v, &v, arg0 + 0x10);
    func_0032C700(&v, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 0, 0.666f, 20.0f, 1, 0,
                  0, 0);
    state = *(char **)(arg0 + 0x68);
    if (*(int *)(state + 0x1B8) != -1) {
        func_002E59F8(*(int *)(state + 0x1B8));
        *(int *)(state + 0x1B8) = -1;
    }
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L20_00450D78);
