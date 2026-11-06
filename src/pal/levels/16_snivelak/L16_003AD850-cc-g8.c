typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char D_00189E20[];
#define H ((Hero *)D_00189E20)

#include "include_asm.h"
extern char *D_L16_001B2B1C;

extern char D_00188660[];
extern int D_L16_001AF894 __attribute__((sda));
extern int D_L16_001AF898 __attribute__((sda));
extern int D_L16_001AF890 __attribute__((sda));
extern int D_L16_001AF89C __attribute__((sda));
extern int func_002ACBC8(void *, int);
extern void func_002E59F8(int);
extern int func_002A8508(int, int);
extern void func_PAL_L16_003ADB58(void *);
extern int func_00282978(void *);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L13_0041AB30(void *);
extern void func_L13_0041AD00(void *);
extern void func_L00_002E6EF8(void (*)(void *), void *);

static __inline__ void clear_link(char *state)
{
    int owner = **(int **)(state + 1640);
    int index;
    char *record;
    if (owner != 0) {
        index = **(int **)(state + 1636);
        if (index != -1) {
            record = D_00188660 + index * 112;
            if (*(int *)(record + 136) == owner && *(unsigned char *)(record + 116))
                func_002E59F8(index);
        }
        **(int **)(state + 1636) = -1;
    }
}

/* func_PAL_L16_003AD850, the PAL copy of func_L16_003AA108: the same C, with the 50 Hz scale on the two timers. */
/* Advances the object's timed activation states and maintains its linked effect. */
void func_PAL_L16_003AD850(char *object)
{
    char *state = *(char **)(object + 104);
    char *target;
    int index;
    char *record;
    if (*(unsigned char *)(object + 32) != 0) {
        if (*(unsigned char *)(object + 32) == 1) {
            target = D_L16_001B2B1C + *(int *)(state + 1576) * 256;
            if (target == 0 || *(unsigned char *)(target + 32) == 254 || *(unsigned char *)(target + 32) == 253) {
                if (func_002ACBC8((&H->c[128]), *(int *)(state + 1632))) {
                    clear_link(state);
                    *(unsigned char *)(object + 32) = 2;
                    goto active;
                }
            }
        } else if (func_002A8508(*(int *)(state + 1580), -1)) {
            goto active;
        }
        clear_link(state);
        return;
    }
active:
    if (D_L16_001AF894)
        return;
    switch (*(unsigned char *)(object + 32)) {
    case 0:
        func_PAL_L16_003ADB58(object);
        *(short *)(state + 16) = (*(int *)(state + 12) * 5 + 2) / 6;
        *(unsigned char *)(object + 32) = 1;
        *(float *)(state + 1572) = 2.5f;
        *(short *)(state + 8) = 1;
        *(short *)(state + 10) = 1;
        **(int **)(state + 1636) = -1;
        break;
    case 1:
        break;
    case 2:
        if (func_00282978(state + 16)) {
            *(unsigned char *)(object + 32) = 3;
            *(short *)(state + 16) = 100;
        }
        break;
    case 3:
        if (**(int **)(state + 1640) == 0 ||
            (index = **(int **)(state + 1636), record = D_00188660 + index * 112,
             *(int *)(record + 136) != **(int **)(state + 1640)) ||
            *(unsigned char *)(record + 116) == 0) {
            **(int **)(state + 1636) = func_002E5DA0(0, 4, object, 4347);
            **(char ***)(state + 1640) = object;
        }
        if (func_00282978(state + 16)) {
            if (*(short *)(state + 6))
                *(unsigned char *)(object + 32) = 2;
            *(short *)(state + 16) = 0;
        } else if (*(short *)(state + 18) == 0) {
            func_PAL_L16_003ADB58(object);
        }
        break;
    }
    if (*(short *)(state + 18)) {
        if (D_L16_001AF898 == 0)
            func_L13_0041AB30(object);
        if (D_L16_001AF890 < *(short *)(state + 18) && D_L16_001AF89C == 0)
            func_L00_002E6EF8(func_L13_0041AD00, object);
    }
}
