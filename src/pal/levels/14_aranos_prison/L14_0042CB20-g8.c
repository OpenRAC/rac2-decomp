#include "include_asm.h"

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
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A93B0(void *);
extern int func_PAL_002B1A50(char *object, char *state, int special);
extern void func_L14_004286F8(unsigned char *);
extern int func_002B3BA8(char *self, int index, void *point, int force, float range, float height);
extern void func_002AFFD8(char *a0, char *a1, int a2);
extern int D_001A79F0[] __attribute__((sda));
extern int D_L14_001A8FF0;
extern float D_L14_001B18B0 __attribute__((sda));
extern char *D_L14_001B2200[] __attribute__((sda));
extern char D_L14_001B2210[] __attribute__((sda));
extern char D_L14_001B9500[];

void func_PAL_L14_0042D918(char *self)
{
    PrisonGuardVars *s = *(PrisonGuardVars **)(self + 0x68);
    int hit;

    if (B(self, 0x20) == 0) {
        if (D_001A79F0[0] == 2 && F(self, 0x18) > 400.0f) {
            if (D_L14_001A8FF0 == 0)
                return;
            func_002B0178(self + 0x10, self, self + 0x10);
            s->h338 = 1;
            W(self, 0x9C) = 3;
            UH(self, 0x34) |= 0x100;
            s->f90 = func_00282E48(self + 0x10, D_L14_001B2210) - 1.5f;
        } else {
            W(self, 0x9C) = 12;
            s->f90 = F(self, 0x18) - 1.0f;
        }
        if (s->i210 == -1) {
            func_0029F338(self);
            return;
        }
        {
            char *e = D_L14_001B2200[0] + s->i210 * 0x30;
            if (H(e, 0x30) != 0) {
                s->i13C = s->i218 = **(int **)(e + 0x3C);
            } else {
                s->i218 = -1;
            }
        }
        s->f324 = func_002A7878(1.0f, 1.333f);
        F(self, 0x2C) = F(*(char **)(self + 0x24), 0x24) * s->f324;
        s->b48 = func_00283CF0(15.0f);
        s->b4A = func_00283CF0(6.4f);
        s->i98 = 3;
        s->f80 = 0.2f;
        s->f84 = 0.2f;
        s->f8C = 0.4f;
        s->f108 = 0.4f;
        s->f134 = 0.05f;
        s->b60 = 11;
        s->b28 = 3;
        s->f30 = 0.333f;
        s->f104 = s->f324 * 0.2f;
        s->f100 = s->f324 * 0.3f;
        s->f10C = 0.4f;
        s->f110 = 1.5707964897155762f;
        s->f130 = 0.523598849773407f;
        s->i138 |= 0x280;
        s->f1DC = func_002A78D8(18.0f, 22.0f) * 0.01745329424738884f;
        s->b1E8 = 7;
        s->b1E9 = 6;
        s->h1E2 = 100;
        s->h1E4 = 150;
        s->f1D4 = 3.0f;
        s->f1D0 = D_L14_001B18B0 * 0.020000001f;
        s->f328 = func_002A7940();
        if (s->i214 != 0) {
            UH(self, 0x34) = (UH(self, 0x34) | 0x41) & ~0x1000;
            W(self, 0x98) = 0;
            func_002A7750(self, 13, 4);
            if (B(self, 0x43) != 10)
                func_PAL_002A7E68(self, 10, 0, 0);
        } else {
            func_002A7750(self, 1, 0);
            if (B(self, 0x43) != 0)
                func_PAL_002A7E68(self, 0, 0, 0);
        }
        s->v2E0 = *(PrisonQword *)(self + 0x10);
    }

    if (B(self, 0x31) != 0) {
        if (func_00282E48(self + 0x10, D_L14_001B9500) < 24.0f) {
            func_002A93B0(self);
            B(self, 0x6F) = 22;
        }
    }
    hit = func_PAL_002B1A50(self, s->area50, 0);
    if (hit != 0) {
        func_L14_004286F8((unsigned char *)self);
        if (hit >= 4)
            func_002A7750(self, 12, -1);
    }
    if (B(self, 0x20) != 12 && s->i1D8 == 1)
        func_002A7750(self, 12, -1);
    if ((u8)(B(self, 0x95) - 3) >= 2)
        s->h314 = func_002B3BA8(self, s->i210, 0, 0, 16.0f, 0.0f);
    if (s->h338 != 0)
        func_002AFFD8(self + 0x10, s->area300, 0);
}
