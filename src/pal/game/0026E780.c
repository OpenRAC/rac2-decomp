#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_0026E780);

typedef struct { char prefix[20]; int *data; } SplashState;
extern char D_001BAEC0[];
extern int D_001A72DC[] __attribute__((sda));
extern void func_PAL_0029DE68(int, void *);
extern int func_0011AEA0(int);
extern void func_PAL_0026E780(void);
extern void func_002FC1D8(void);
extern void func_002FCB00(void *, int, int, int);
extern void func_0027B858(void);
extern void func_0027DDC0(int, int, int, int);
extern void func_00284FC0(void);
extern void func_00285338(void);
extern void func_002FC280(void);
extern void func_002FC3C0(int);
extern int func_001244B8(int, int);
extern int func_001261F0(int);
extern void func_002FCD18(void);
extern void func_00284E18(int, int, int);
extern void func_00284EA8(void);
extern void func_00284F40(int);
extern void func_002FCDA8(void);

/* func_PAL_0026E838, the PAL copy of func_0026EA00: the same C with three more calls before the
   image draw (func_00284E18, func_00284EA8, func_00284F40) and func_PAL_0026E780() before the
   second func_0011AEA0(0). Draws the loaded splash image over 65 frames, fading its alpha from
   128 to 0. */
void func_PAL_0026E838(int arg)
{
    int *data;
    int count;

    func_PAL_0029DE68(arg, ((SplashState *)D_001BAEC0)->data);
    func_0011AEA0(0);
    for (count = 0x80; count >= 0; count -= 2) {
        func_002FC1D8();
        func_00284E18(0, 0, 0);
        func_00284EA8();
        func_00284F40(0);
        data = ((SplashState *)D_001BAEC0)->data;
        func_002FCB00(data + 4, D_001A72DC[0], data[0], data[1]);
        func_0027B858();
        func_0027DDC0(0, 0, 0, count);
        func_00284FC0();
        func_00285338();
        func_PAL_0026E780();
        func_0011AEA0(0);
        func_002FC280();
        func_002FC3C0(1);
        func_001244B8(0, 0);
        func_001261F0(0);
    }
}

/* func_PAL_0026E928, the PAL copy of func_0026EAC8: the same C with one more call,
   func_PAL_0026E780(), before the second func_0011AEA0(0). */

void func_PAL_0026E928(int arg)
{
    char *state = D_001BAEC0;
    int *data;
    func_PAL_0029DE68(arg, *(void **)(state + 20));
    func_0011AEA0(0);
    func_002FC1D8();
    func_002FCD18();
    func_00284E18(0, 0, 0);
    func_00284EA8();
    func_00284F40(0);
    data = *(int **)(state + 20);
    func_002FCB00(data + 4, D_001A72DC[0], data[0], data[1]);
    func_0027B858();
    func_00284FC0();
    func_00285338();
    func_PAL_0026E780();
    func_0011AEA0(0);
    func_002FC280();
    func_002FC3C0(1);
    func_001244B8(0, 0);
    func_001261F0(0);
    func_002FCDA8();
}
