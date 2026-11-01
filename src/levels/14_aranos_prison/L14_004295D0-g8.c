/* -G8 for the $gp reads of the D_L14_001B1948/D_L14_001B1950 tuning values and the
 * D_L14_001B259C entity table. The level-14 counterpart of func_L07_003E69B8
 * (src/levels/07_siberius/L07_003E69B8-g8.c), written the same way: the vars block is
 * reached through offsets, except for the damage block at +0x140 that func_002B0ED8 takes,
 * which is typed. Its +0x10 and +0x48 are the animation and mode func_002B0ED8 passes to
 * func_002A7750 on a hit.
 */
#include "common.h"

#define INT_AT(p, n) (*(int *)((p) + (n)))
#define U16_AT(p, n) (*(unsigned short *)((p) + (n)))
#define FLOAT_AT(p, n) (*(float *)((p) + (n)))

typedef struct {
    char pad0[0x10];
    unsigned char hit_anim;   /* 0x10 */
    char pad11[0x30 - 0x11];
    float f30, f34;           /* 0x30 */
    char pad38[0x3C - 0x38];
    float f3c, f40;           /* 0x3C */
    char pad44[0x48 - 0x44];
    int hit_anim_mode;        /* 0x48 */
} DamageBlock;

#define DAMAGE(p) ((DamageBlock *)((p) + 0x140))

extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_00325B70(void *, void *, int, int);
extern float func_002B0178(void *, void *, void *);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_L14_003DF650(void *);
extern void func_002A93B0(void *);
extern float func_00282E48(void *, void *);
extern int func_002B0ED8(void *, void *, int);
extern void func_L14_00429A18(void *);
extern void func_00325D30(void *, void *);
extern int func_002B3BA8(void *, int, void *, int, float, float);
extern char D_L14_001B9500[];
extern int D_L14_001B259C __attribute__((sda));
extern float D_L14_001B1948 __attribute__((sda));
extern unsigned short D_L14_001B1950 __attribute__((sda));
extern unsigned short D_L14_001B1954[] __attribute__((sda));

/* Initializes the entity on its first frame, then handles the player coming close, damage
   and the state-2 update. */
int func_L14_004295D0(unsigned char *o)
{
    unsigned char *p = *(unsigned char **)(o + 0x68);
    float turn;
    if (o[0x20] == 0) {
        p[0x48] = func_00283CF0(15.0f);
        p[0x4A] = func_00283CF0(9.6f);
        DAMAGE(p)->hit_anim = 6;
        DAMAGE(p)->f3c = 0.15f;
        DAMAGE(p)->hit_anim_mode = 2;
        DAMAGE(p)->f34 = DAMAGE(p)->f30 = 1.0f;
        turn = D_L14_001B1948 * 0.017453294f;
        DAMAGE(p)->f40 = FLOAT_AT(o, 0x18) - 3.0f;
        FLOAT_AT(p, 0x54) = 0.3f;
        FLOAT_AT(p, 0x50) = 1.0f;
        FLOAT_AT(p, 0x78) = 0.10000001f;
        FLOAT_AT(p, 0x74) = FLOAT_AT(p, 0x70) = 0.005f;
        FLOAT_AT(p, 0x68) = FLOAT_AT(p, 0x64) = 0.0034906589f;
        FLOAT_AT(p, 0x60) = 3.1415927f;
        FLOAT_AT(p, 0x12C) = func_002A77E0(2) ? -turn : turn;
        U16_AT(p, 0x132) = D_L14_001B1950;
        U16_AT(p, 0x134) = D_L14_001B1954[0];
        p[0x2E] = 1;
        qcopy(p + 0x2E0, o + 0x10);
        INT_AT(p, 0x31C) = 1;
        FLOAT_AT(p, 0x2B4) = 4.0f;
        func_00325B70(o, p + 0x300, 0, 2);
        FLOAT_AT(p, 0x20) = 3.0f;
        U16_AT(p, 0x24) = 3;
        FLOAT_AT(o, 0x18) += 0.5f;
        func_002B0178(o + 0x10, o, o + 0x10);
        if (INT_AT(p, 0x2BC) != -1) {
            func_002A7750(o, 7, 3);
            if (o[0x43]) func_002A7470(o, 0, 0, 0);
        } else {
            func_002A7750(o, 1, 0);
            if (o[0x43] != 2) func_002A7470(o, 2, 0, 0);
        }
        if (INT_AT(p, 0x2B8) != -1)
            func_L14_003DF650((char *)D_L14_001B259C + INT_AT(p, 0x2B8) * 256);
    }
    if (o[0x31] && func_00282E48(o + 0x10, D_L14_001B9500) < 24.0f) {
        func_002A93B0(o);
        o[0x6F] = 22;
    }
    if (func_002B0ED8(o, (char *)DAMAGE(p), 0) && FLOAT_AT(p, 0x20) <= 0.0f) {
        func_L14_00429A18(o);
        return 1;
    }
    if (p[0x2E] == 2) {
        if (p + 0x300)
            func_00325D30(o, p + 0x300);
        return 1;
    }
    INT_AT(p, 0x2F0) = func_002B3BA8(o, INT_AT(p, 0x2B0), 0, 0, FLOAT_AT(p, 0x2B4), 1.5f);
    return 0;
}
