#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern char D_L02_001B03F0[] SDATA(D_L02_001B03F0);
extern char *D_L02_001B359C;
typedef struct { char pad[0x80]; float x, y; } HeroPosition;
extern HeroPosition D_00189E20;
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern void func_0029FC20(void *, int, void *);
extern float func_00283248(float, float);
extern void func_PAL_002A0F68(void *);
extern void func_002A10E8(void *);
extern void func_00282A60(void *, int, int);
extern void func_0029F978(void *, int, void *);
extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_002A0488(void *, int, int, int);
#define PRIVATE (*(char **)(actor + 0x68))
#define ATTACHMENT (*(char **)(PRIVATE + 0x260))
#define CHILD (D_L02_001B359C + *(int *)(PRIVATE + 0x244) * 0x100)
typedef struct { char pad[0x34]; unsigned short flags; char pad36[0xC2]; float heading; } ActorFlags;

/* Reinitializes an actor and its child, attaching the three active effect slots. */
void func_PAL_L02_003DF498(char *actor, int alternate) {
    char *state = PRIVATE;
    Quad transform[4];
    int health;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(unsigned char *)(actor + 0x31) = 1;
    ((ActorFlags *)actor)->flags &= 0xFFFE;
    health = *(int *)(*(char **)(actor + 0x24) + 0x10);
    ((ActorFlags *)actor)->flags = (((ActorFlags *)actor)->flags | 0x1000) & 0xFFFD;
    *(int *)(actor + 0x98) = health;
    *(int *)(actor + 0x9C) = 0;
    *(unsigned char *)(actor + 0x7F) = 0;
    *(unsigned char *)(state + 0x2E) = 1;
    qcopy(actor + 0x10, D_L02_001B03F0);
    *(char **)(PRIVATE + 0x260) = func_0029EFD0(0xA4C);
    if (ATTACHMENT != 0) {
        *(unsigned char *)(ATTACHMENT + 0x30) = *(unsigned char *)(actor + 0x30);
        *(unsigned short *)(ATTACHMENT + 0x32) = *(unsigned short *)(actor + 0x32);
        *(unsigned char *)(ATTACHMENT + 0x31) = 1;
        *(long long *)(ATTACHMENT + 0x38) = *(long long *)(actor + 0x38);
        func_002A0F48(ATTACHMENT);
        *(int *)(ATTACHMENT + 0x98) = 0;
        ((ActorFlags *)ATTACHMENT)->flags |= 2;
        ((ActorFlags *)ATTACHMENT)->flags &= 0xFFFE;
        *(unsigned char *)(ATTACHMENT + 0x31) = 1;
    }
    func_0029FC20(actor, 0, transform);
    qcopy(CHILD + 0x10, &transform[3]);
    *(float *)(actor + 0xF8) = func_00283248(D_00189E20.x - *(float *)(actor + 0x10), D_00189E20.y - *(float *)(actor + 0x14));
    ((ActorFlags *)CHILD)->heading = func_00283248(D_00189E20.x - *(float *)(actor + 0x10), D_00189E20.y - *(float *)(actor + 0x14));
    func_PAL_002A0F68(CHILD);
    func_002A0F48(CHILD);
    func_002A10E8(CHILD);
    ((ActorFlags *)CHILD)->flags &= 0xFFFE;
    *(unsigned char *)(CHILD + 0x31) = 1;
    *(int *)(CHILD + 0x98) = *(int *)(*(char **)(CHILD + 0x24) + 0x10);
    if (*(unsigned char *)(state + 0x171) == 0) {
        func_00282A60(state + 0x170, 0, 0x40);
        func_0029F978(CHILD, 2, state + 0x170);
    }
    if (*(unsigned char *)(state + 0x1B1) == 0) {
        func_00282A60(state + 0x1B0, 0, 0x40);
        func_0029F978(CHILD, 3, state + 0x1B0);
    }
    if (*(unsigned char *)(state + 0x1F1) == 0) {
        func_00282A60(state + 0x1F0, 0, 0x40);
        func_0029F978(CHILD, 4, state + 0x1F0);
    }
    if (alternate == 0) {
        func_002A7750(actor, 2, 0);
        *(int *)(state + 0x264) = 0;
    } else func_002A7750(actor, 4, 0);
    *(short *)(state + 0x288) = ((s32)(func_00283CF0(func_002A7878(600.0f, 1200.0f))) * 5 + 2) / 6;
    *(short *)(state + 0x280) = 0;
    *(short *)(state + 0x282) = 0;
    if (*(short *)(state + 0x140) != 0) {
        *(short *)(state + 0x140) = 0;
        func_002A0488(actor, *(int *)(state + 0x270), *(int *)(state + 0x274), *(int *)(state + 0x278));
        *(short *)(state + 0x142) = 1;
    }
}
