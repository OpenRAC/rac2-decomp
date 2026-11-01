#include "common.h"

/* The spawn ranges of the dust puffs, read through $gp. */
extern int D_L09_001B17A8 __attribute__((sda));
extern int D_L09_001B17AC __attribute__((sda));
extern float D_L09_001B17B0 __attribute__((sda));
extern float D_L09_001B17B4 __attribute__((sda));
extern float D_L09_001B17B8 __attribute__((sda));
extern float D_L09_001B17BC __attribute__((sda));
extern float D_L09_001B17C0 __attribute__((sda));
extern float D_L09_001B17C4 __attribute__((sda));
extern float D_L09_001B17C8 __attribute__((sda));
extern float D_L09_001B17CC __attribute__((sda));
extern float D_L09_001B17D0 __attribute__((sda));
extern float D_L09_001B17D4 __attribute__((sda));
extern int D_L09_001B17D8 __attribute__((sda));
extern int D_L09_001B17DC __attribute__((sda));
extern int D_L09_001B17E0 __attribute__((sda));
extern int D_L09_001B17E4 __attribute__((sda));
extern float D_L09_001B17E8 __attribute__((sda));
extern int D_L00_001A8FB4 __attribute__((sda));
extern int D_001A79F0 __attribute__((section(".sdata")));
/* Volatile: retail keeps its store out of the branch delay slot. */
extern volatile int D_L09_001B25A8 __attribute__((section(".sdata")));
extern int D_00138324 __attribute__((nosda));
extern char D_00188660[];
typedef struct {
    char pad0[0x33C];
    u8 *standing;
    char pad340[0x34E - 0x340];
    short busy;
    char pad350[0x22B4 - 0x350];
    u8 help;
} Player10200;

extern Player10200 D_00189E20;
extern u8 D_001395B8[];
extern char D_L09_001BFC00[];

extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CD8(void *, void *, void *);
extern int func_002A7820(int, int);
extern int func_00283D38(int, int, float);
extern int func_001163B0(void);
extern void func_002C2210(void *, int, float, float, int, int, int, void *, int, float);
extern void func_002A7750(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern void func_002B0C28(int, int, int);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern void func_00288CB0(int, int);
extern int func_002F5D10(void);

/* Throws one dust puff at a random point around the object, then runs its state: 0 arms it,
   1 keeps its sound slot and, while the player stands on it, shows a message on levels 9 and
   18 and moves on when bit 0x10 of D_00138324 is set and D_L00_001A8FB4 is 4; 2 waits for
   func_00288AA0 on D_L09_001BFC00; 3 and 4 finish it. The frame counter at +0x96 saturates.
   The vector clear is qzero_nc: retail clears through a register address. */
void func_L09_00410200(u8 *obj)
{
    float pos[4];
    float vel[4];
    float tmp[4];
    int *st = *(int **)(obj + 0x68);
    float r;
    float spin;
    float size;
    int life;
    int tex;
    int n;
    int dir;
    char *p;

    r = func_002A7878(D_L09_001B17B0, D_L09_001B17B4);
    pos[0] = func_00283180(func_002A7940()) * r;
    pos[1] = func_00283198(func_002A7940()) * r;
    pos[2] = 0.0f;
    func_00282CD8(tmp, pos, obj + 0x10);
    pos[2] -= D_L09_001B17E8;
    qzero_nc(vel);
    vel[2] = func_002A7878(D_L09_001B17B8, D_L09_001B17BC) * (1.0f / 60.0f);
    life = func_002A7820(D_L09_001B17A8, D_L09_001B17AC);
    spin = func_002A7878(D_L09_001B17C8, D_L09_001B17CC);
    size = func_002A7878(D_L09_001B17D0, D_L09_001B17D4);
    tex = func_00283D38(D_L09_001B17D8, D_L09_001B17DC, func_002A7878(0.0f, 1.0f));
    n = func_002A7820(D_L09_001B17E0, D_L09_001B17E4);
    dir = (func_001163B0() & 1) ? -n : n;
    func_002C2210(pos, life, spin, size, tex, 2, dir, vel, 0,
                  -(func_002A7878(D_L09_001B17C0, D_L09_001B17C4) * (1.0f / 3600.0f)));

    switch (obj[0x20]) {
    case 0:
        func_002A7750(obj, 1, -1);
        st[2] = -1;
        break;
    case 1:
        p = D_00188660 + st[2] * 0x70;
        if (*(u8 **)(p + 0x88) != obj || *(u8 *)(p + 0x74) == 0)
            st[2] = func_002E5CF8(0, 4, obj);
        if (D_00189E20.standing != obj || D_00189E20.busy != 0)
            break;
        if (D_00189E20.help == 0) {
            if (D_001A79F0 == 9)
                func_002B0C28(4, 0x27C6, 1);
            else if (D_001A79F0 == 18)
                func_002B0C28(4, 0x27ED, 1);
        } else if (D_00189E20.help == 2) {
            func_002B0C28(4, 0x27B4, 1);
        }
        if (!(D_00138324 & 0x10) || D_L00_001A8FB4 != 4)
            break;
        if (D_001A79F0 == 9 || D_001A79F0 == 18)
            func_002A7750(obj, 2, -1);
        else
            func_002A7750(obj, 4, -1);
        break;
    case 2:
        if (D_001A79F0 == 9) {
            if (func_00288AA0(D_L09_001BFC00, 100)) {
                func_00288BE8(D_L09_001BFC00);
                func_002A7750(obj, 3, -1);
            }
        } else if (D_001A79F0 == 18) {
            if (func_00288AA0(D_L09_001BFC00, 0x92)) {
                func_00288BE8(D_L09_001BFC00);
                func_002A7750(obj, 3, -1);
            }
        }
        break;
    case 3:
        if (func_002F5D10()) {
            D_L09_001B25A8 = 1;
            break;
        }
    case 4: {
        int lvl;

        D_L09_001B25A8 = 0;
        obj[0x31] = 1;
        lvl = D_001A79F0;
        *(u16 *)(obj + 0x34) &= ~1;
        if (lvl == 9) {
            D_001395B8[0x1D] = 1;
            D_001395B8[0x2D] = 1;
        } else if (lvl == 18) {
            D_001395B8[0x87] = 1;
            D_001395B8[0x9F] = 1;
        }
        func_00288CB0(st[0], 1);
        break;
    }
    case 5:
    case 6:
        break;
    }
    if (*(u16 *)(obj + 0x96) < 0xFFFF)
        *(u16 *)(obj + 0x96) += 1;
}
