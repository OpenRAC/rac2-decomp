#include "include_asm.h"

#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char D_00189E20[];
#define H ((Hero *)D_00189E20)
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { char prefix[0x50]; float speed; char tail[0x8C]; } WeaponEntry;
extern WeaponEntry D_L00_00262570[];
extern unsigned char D_00139568[];
extern int D_L00_001ADB2C;
extern char *D_L00_001BF200[];
extern void func_0029FCC0(char *, int, char *);
extern void func_00282F20(void *, void *, float);
extern int func_00291308(void *, float, float, unsigned int);
extern void func_L00_0037FA90(char *, char *, float, float, float);
extern void func_L00_0032A1A8(char *, char *, char *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern char *func_PAL_L00_003F9060(void *, void *, int, int);
extern void func_PAL_L00_003F97D0(char *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277F48(void *, int, void *, void *, float);
extern int func_002ABB78(char *);
extern char *func_002C2210(void *, int, unsigned int, int, int, float, float, void *, float, int);

/* Aim and spawn a beam, then flash four layers around its muzzle. */
void func_PAL_L00_003E8788(char *moby)
{
    Vector origin, velocity, targetPosition, delta, unit;
    char *state = *(char **)(moby + 0x68);

    char *beam;
    float speed = (D_L00_00262570 + D_00139568[0x17])->speed * 0.020000001f;
    int mode;
    char *model;
    char *collision;
    if (H->h[4726] == 1) {
        func_0029FCC0(moby, 0, (char *)origin);
        func_00282F20(velocity, moby+0xD0, -speed);
    } else {
        func_0029FCC0(moby, 0, (char *)origin);
        func_00282F20(velocity, (&H->f[472]), speed);
    }
    *(int *)(state + 0x10) = func_00291308(origin, 10.0f, 0.0f, 0xFF0000FF);
    *(int *)(state + 0x14) = 25;
    mode = 0;
    if (H->i[1344]) {
        mode = 1;
        func_L00_0037FA90((char *)velocity, (char *)origin, speed, 128.0f, 0.34906590f);
    } else if (H->ptr[766]) {
        func_L00_0032A1A8(H->ptr[766], (char *)origin, (char *)velocity, speed);
    }
    if (D_L00_001ADB2C) {
        char *target = *(char **)(state + 0x2C);
        if ((target && H->i[1344]) || (H->ptr[766] && !H->i[1344])) {
            if (target)
                qcopy(targetPosition, (target + 0x10));
            else
                /* lq ignores the low four address bits: this reads the quadword holding +0xBF8. */
                qcopy(targetPosition, &H->ptr[766]);
            func_00282CF0(delta, targetPosition, origin);
            func_00282F20(unit, velocity, 1.0f);
            func_00282D30(velocity, unit, func_00282DB0(unit, delta) + 3.0f);
            mode = 2;
        }
    }
    func_00282D30(targetPosition, moby+0xD0, -1.5f);
    func_00282CC0(targetPosition, targetPosition, moby + 0x10);
    func_00282D30(delta, moby + 0xC0, 0.275f);
    func_00282CC0(targetPosition, targetPosition, delta);
    if (func_00277F48(targetPosition, 1, H->ptr[2212], 0, 1.0f) &&
        (((collision = D_L00_001BF200[6]) && (model = *(char **)(collision + 0x24)) && *(short *)(model + 0x46) == 5) ||
         func_002ABB78(D_L00_001BF200[6]))) {
        func_PAL_L00_003F97D0(moby, targetPosition);
    } else {
        beam = func_PAL_L00_003F9060(origin, velocity, *(int *)(state + 0x18), mode);
        if (beam)
            *(char **)(beam + 0xB8) = moby;
    }
    *(VectorBits *)unit = 0;
    func_002C2210(origin, 8, 0x401050FF, 2, 1, 7.0f, 0.1f, unit, 0.0f, 1);
    func_002C2210(origin, 8, 0x401050FF, 2, -1, 5.0f, 0.1f, unit, 0.0f, 1);
    func_002C2210(origin, 8, 0xC0FFFFFF, 2, 1, 3.5f, 0.1f, unit, 0.0f, 1);
    func_002C2210(origin, 8, 0xB0FFFFFF, 2, -1, 2.5f, 0.1f, unit, 0.0f, 1);
}
