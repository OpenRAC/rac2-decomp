/* -G8 for the $gp reads of D_L14_001A8FF0 and D_L14_001B18B0; -frac2-qcopy for
 * the position copy into +0x2E0.
 * Absolute data uses incomplete sda arrays (tied lui/lw and a single la macro).
 * The state is a struct so its field stores do not alias D_L14_001B18B0.
 * Store order in the init block is the order sched1's register-weight tie-break
 * needs (shared constants' first uses first; 0.05 early so it gets $f0).
 */
#include "common.h"

#define W(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define UH(p, o) (*(unsigned short *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))

typedef int PrisonQword __attribute__((mode(TI)));

typedef struct {
    char pad0[0x28 - 0x0];
    unsigned char b28;
    char pad29[0x30 - 0x29];
    float f30;
    char pad34[0x48 - 0x34];
    unsigned char b48;
    char pad49[0x4A - 0x49];
    unsigned char b4A;
    char pad4B[0x50 - 0x4B];
    char area50[0x10];
    unsigned char b60;
    char pad61[0x80 - 0x61];
    float f80;
    float f84;
    char pad88[0x8C - 0x88];
    float f8C;
    float f90;
    char pad94[0x98 - 0x94];
    int i98;
    char pad9C[0x100 - 0x9C];
    float f100;
    float f104;
    float f108;
    float f10C;
    float f110;
    char pad114[0x130 - 0x114];
    float f130;
    float f134;
    int i138;
    int i13C;
    char pad140[0x1D0 - 0x140];
    float f1D0;
    float f1D4;
    int i1D8;
    float f1DC;
    char pad1E0[0x1E2 - 0x1E0];
    short h1E2;
    short h1E4;
    char pad1E6[0x1E8 - 0x1E6];
    unsigned char b1E8;
    unsigned char b1E9;
    char pad1EA[0x210 - 0x1EA];
    int i210;
    int i214;
    int i218;
    char pad21C[0x2E0 - 0x21C];
    PrisonQword v2E0;
    char pad2F0[0x300 - 0x2F0];
    char area300[0x10];
    char pad310[0x314 - 0x310];
    short h314;
    char pad316[0x324 - 0x316];
    float f324;
    float f328;
    char pad32C[0x338 - 0x32C];
    short h338;
} PrisonGuardVars;


extern float func_002B0178(void *position, void *owner, void *output);
extern float func_00282E48(void *, void *);
extern void func_0029F338(void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_002A93B0(void *);
extern int func_002B0ED8(char *object, char *state, int special);
extern void func_L14_004286F8(unsigned char *);
extern int func_002B3BA8(char *self, int index, void *point, int force, float range, float height);
extern void func_002AFFD8(char *a0, char *a1, int a2);

extern int D_001A79F0[] __attribute__((sda));
extern int D_L14_001A8FF0;
extern float D_L14_001B18B0 __attribute__((sda));
extern char *D_L14_001B2200[] __attribute__((sda));
extern char D_L14_001B2210[] __attribute__((sda));
extern char D_L14_001B9500[];

/* Shared guard logic: sets up its stats on the first frame, then checks for the player getting close, damage and the path to the player. */
void func_L14_004281D0(char *self)
{
    PrisonGuardVars *vars = *(PrisonGuardVars **)(self + 0x68);
    int hit;

    if (B(self, 0x20) == 0) {
        if (gCurrentMapIndex[0] == 2 && F(self, 0x18) > 400.0f) {
            if (D_L14_001A8FF0 == 0)
                return;
            GetGroundDistanceBelowPosition(self + 0x10, self, self + 0x10);
            vars->h338 = 1;
            W(self, 0x9C) = 3;
            UH(self, 0x34) |= 0x100;
            vars->f90 = fast_vec_dist(self + 0x10, D_L14_001B2210) - 1.5f;
        } else {
            W(self, 0x9C) = 12;
            vars->f90 = F(self, 0x18) - 1.0f;
        }
        if (vars->i210 == -1) {
            MarkMobySpawned(self);
            return;
        }
        {
            char *entry = D_L14_001B2200[0] + vars->i210 * 0x30;
            if (H(entry, 0x30) != 0) {
                vars->i13C = vars->i218 = **(int **)(entry + 0x3C);
            } else {
                vars->i218 = -1;
            }
        }
        vars->f324 = RandomFloatRange(1.0f, 1.333f);
        F(self, 0x2C) = F(*(char **)(self + 0x24), 0x24) * vars->f324;
        vars->b48 = FloatToInt(15.0f);
        vars->b4A = FloatToInt(6.4f);
        vars->i98 = 3;
        vars->f80 = 0.2f;
        vars->f84 = 0.2f;
        vars->f8C = 0.4f;
        vars->f108 = 0.4f;
        vars->f134 = 0.05f;
        vars->b60 = 11;
        vars->b28 = 3;
        vars->f30 = 0.333f;
        vars->f104 = vars->f324 * 0.2f;
        vars->f100 = vars->f324 * 0.3f;
        vars->f10C = 0.4f;
        vars->f110 = 1.5707964897155762f;
        vars->f130 = 0.523598849773407f;
        vars->i138 |= 0x280;
        vars->f1DC = RandomSignedFloatRange(18.0f, 22.0f) * 0.01745329424738884f;
        vars->b1E8 = 7;
        vars->b1E9 = 6;
        vars->h1E2 = 120;
        vars->h1E4 = 180;
        vars->f1D4 = 3.0f;
        vars->f1D0 = D_L14_001B18B0 * 0.01666666753590107f;
        vars->f328 = RandomAngle();
        if (vars->i214 != 0) {
            UH(self, 0x34) = (UH(self, 0x34) | 0x41) & ~0x1000;
            W(self, 0x98) = 0;
            SetMobyState(self, 13, 4);
            if (B(self, 0x43) != 10)
                StartAnimationBlended(self, 10, 0, 0);
        } else {
            SetMobyState(self, 1, 0);
            if (B(self, 0x43) != 0)
                StartAnimationBlended(self, 0, 0, 0);
        }
        vars->v2E0 = *(PrisonQword *)(self + 0x10);
    }

    if (B(self, 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, D_L14_001B9500) < 24.0f) {
            UpdateMobyGroundCheck(self);
            B(self, 0x6F) = 22;
        }
    }
    hit = ApplyDamageToObject(self, vars->area50, 0);
    if (hit != 0) {
        AlertGroupGuards((unsigned char *)self);
        if (hit >= 4)
            SetMobyState(self, 12, -1);
    }
    if (B(self, 0x20) != 12 && vars->i1D8 == 1)
        SetMobyState(self, 12, -1);
    if ((u8)(B(self, 0x95) - 3) >= 2)
        vars->h314 = SelectAimTarget_002B3BA8(self, vars->i210, 0, 0, 16.0f, 0.0f);
    if (vars->h338 != 0)
        ComputeViewDirection(self + 0x10, vars->area300, 0);
}
