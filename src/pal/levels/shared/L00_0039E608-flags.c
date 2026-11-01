#include "include_asm.h"

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
typedef struct {
    char prefix[0x760];
    float aimAxis[4];
    char pad770[0xAC0];
    unsigned int buttons;
    char pad1234[0xC];
    int resource;
    char pad1244[0x1050];
    int level;
    char pad2298[0x24];
    unsigned char busy;
    char pad22BD[0x277];
    int cooldown;
} LaunchHero;
extern LaunchHero D_00189E20;
extern unsigned int D_00138320;
extern void func_0029FCC0(char *, int, char *);
extern void func_002FDF40(void *, void *, void *, float, float, float, float, void *);
extern int func_PAL_002FF5F8(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(int *), func_L00_002D3F30(int, int);
extern void func_PAL_L00_002AF6C0(void), func_PAL_L00_002AF458(void);
extern int func_002E5CF8(int, int, char *);
extern char *func_L00_00398810(char *, char *);
extern void ref_L00_0039D110_00(void *, void *);
extern void func_PAL_L00_003A06F8(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* func_L00_0039B288 is defined in L00_0039B288-g8.c. */


/* Aims and launches the actor's projectile in response to the shared input gate. */
void func_PAL_L00_003A04C8(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16], direction[16];
    int ready;
    func_0029FCC0(actor, 0, position);
    func_002FDF40(direction, position, 0, 1.5f, D_00189E20.level == 29 ? 11.0f : 5.0f, 0.20000002f, 0.0044f, 0);
    ready = 1;
    *(int *)(state + 0x24) = func_PAL_002FF5F8(position, direction, state, state + 0x10, actor, 0, 0, 0.0044f);
    if (D_00189E20.level == 29) {
        if (!func_00282948(&D_00189E20.cooldown)) ready = 0;
    }
    else D_00189E20.cooldown = 33;
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(unsigned char *)(actor + 0x20) = 1;
        *(int *)(state + 0x24) = 0;
    case 1:
        if ((D_00138320 & D_00189E20.buttons) == 0 || D_00189E20.busy || D_00189E20.resource < 8 || !ready) break;
        if (func_L00_002D3F30(-1, 1)) {
            func_PAL_L00_002AF458();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 17;
            break;
        }
        func_002E5CF8(2, 0, actor);
        break;
    case 2:
        if (!func_00282948((int *)(state + 0x20))) break;
        *(char **)(func_L00_00398810(position, direction) + 0xB8) = actor;
        func_PAL_L00_002AF6C0();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 8;
        break;
    case 3:
        if (func_00282948((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_0039D110_00(func_PAL_L00_003A06F8, actor);
}
