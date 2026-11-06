/* func_PAL_L18_0042D088, the PAL copy of func_L18_00428428: the same C, where rename-macro func_002ABBB8 becomes func_PAL_002AC718; rename func_002C27F0 becomes func_0026FEB8; rename func_0032C5E0 becomes func_0029FCC0; rename func_00336F00 becomes func_002A8C28; rename func_0033A400 becomes func_PAL_002AC718; rename func_002FB998 becomes func_00277F48; rename func_00308BD8 becomes func_00282F20; rename func_00308AD0 becomes func_00282E80. */
#include "common.h"

/* Built with -frac2-keep-block-order (config/cflags.txt): the shared `return 0`
   block stays behind the projectile arm, as in retail. */

extern float D_L18_001B1280 __attribute__((sda));
extern float D_L18_001B1284 __attribute__((sda));
extern float D_L18_001B1288 __attribute__((sda));
extern float D_L18_001B128C __attribute__((sda));
extern float D_L18_001B12C0 __attribute__((sda));
extern unsigned char D_L18_001B1338[];
/* The explosion table sits at another address in level 18; MACRO_ADDR keeps
   retail's adjacent lui/addiu pair. */
extern unsigned char ref_L18_00428428_00[] MACRO_ADDR;
extern void func_0026FEB8(void *, int);
extern void func_0029FCC0(void *, int, void *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_L18_004283F0(void *);
/* Argument layout of RAC1's spawn_explosion, with one more integer. */
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                          int, float, int, int, int, int, int);
extern void func_00277F48(void *, int, void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern float func_00282E80(void *, void *);
extern int func_L18_0043FFF8(void *, void *, void *, int, int, float, float, float);

/* Fires from joint side + 2. When the sphere test at that point reports contact, it
   spawns an explosion there and sends a hit record to nearby objects; otherwise it
   launches a projectile along the facing, aimed at the target's height unless the
   byte at 0xBC is set. */
int func_PAL_L18_0042D088(unsigned char *obj, int side) {
    unsigned char *state = *(unsigned char **)(obj + 0x68);
    float range = D_L18_001B1280;
    float speed = D_L18_001B1288;
    int mask;
    float pos[4] __attribute__((aligned(16)));
    struct { float vec[4]; void *owner; int flags; unsigned char a, b; unsigned short kind; float value; int one; } hit __attribute__((aligned(16)));

    switch (*(short *)(obj + 0xAA)) {
    case 0xEC0: func_0026FEB8(D_L18_001B1338, 0xEC0); break;
    case 0xEE1: range = D_L18_001B1284; speed = D_L18_001B128C; break;
    case 0xED4:
    default: range = D_L18_001B1280; speed = D_L18_001B1288; break;
    }
    func_0029FCC0(obj, side + 2, pos);
    mask = 1;
    if (!obj[0xBC])
        mask = 0x10000;
    if (func_002A8C28(obj, pos, mask, 1, 3, 0, 0.35f, (float)state[0x34], D_L18_001B12C0)) {
        hit.owner = obj;
        hit.flags = 0x810001;
        hit.value = (float)state[0x34];
        hit.one = 1;
        qzero_nc(hit.vec);
        hit.vec[2] = D_L18_001B12C0;
        hit.vec[3] = 5627.925f;
        hit.a = 2;
        hit.b = 3;
        hit.kind = *(unsigned short *)(obj + 0xAA);
        func_PAL_002AC718(obj, ref_L18_00428428_00, pos, 0.0f, 0.0f, 5, 2, 9, 0.0f, 0.0f, 9.0f, 1.1f, func_L18_004283F0(obj), 0.0f, 0, 1, -2, 0, 0x810001);
        func_00277F48(pos, 16, obj, &hit, 1.0f);
    } else {
        speed *= 0.020000001f;
        func_00282F20(hit.vec, obj + 0xC0, speed);
        if (!obj[0xBC]) {
            float t = func_00282E80(pos, state + 0x220) / speed;
            hit.vec[2] = (*(float *)(state + 0x228) - pos[2]) / t;
        }
        return func_L18_0043FFF8(pos, obj, hit.vec, 1, 3, (float)state[0x34], range, D_L18_001B12C0);
    }
    return 0;
}
