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
extern void func_0029FCC0(char *, int, char *);
extern void func_002FDF40(void *, void *, void *, float, float, float, float, void *);
extern int func_PAL_002FF5F8(void *, void *, void *, void *, void *, int, int, float);
extern int func_00282948(int *), func_L00_002D3F30(int, int);
extern void func_PAL_L00_002AF6C0(void), func_PAL_L00_002AF458(void);
extern int func_002E5CF8(int, int, char *);
typedef struct { float value[3]; } QuerySettings;
extern QuerySettings D_L00_001AF410;
typedef struct { char prefix[0x1A0]; unsigned int held, pressed; } LaunchInput;
extern LaunchInput D_00138180;
extern char *func_002AF580(void *, void *, int *, void *, int, int, float, float, float, float, float, int, void *);
extern char *func_PAL_L00_00390608(char *, char *);
extern void ref_L00_00397E60_00(void *, void *);
extern void func_PAL_L00_0039B490(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* func_L00_003959C0 is defined in L00_003959C0-g8.c. */

/* func_L00_00395A88 is defined in L00_00395A88-g8.c. */

/* func_L00_00396078 is defined in L00_00396078-g64.c. */


/* func_L00_003973E8 is defined in L00_003973E8-g8.c. */

/* Selects an aim target before advancing the projectile launcher state. */
void func_PAL_L00_0039B1D8(char *actor)
{
    char *state = *(char **)(actor + 0x68);
    char position[16];
    QuerySettings settings;
    char direction[16];
    int foundCount;
    char *target;
    int ready;
    func_0029FCC0(actor, 0, position);
    settings = D_L00_001AF410;
    target = func_002AF580(actor + 0x10, D_00189E20.aimAxis, &foundCount, 0, 0, 0,
                          0.3926991f, 0.7853982f, 11.1f, 0.0f, 0.0f, 0, &settings);
    func_002FDF40(direction, position, target, 1.5f, D_00189E20.level == 29 ? 11.0f : 10.0f, 0.20000002f, 0.0044f, 0);
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
        if ((D_00138180.held & D_00189E20.buttons) == 0 || D_00189E20.busy || D_00189E20.resource < 19 || !ready) break;
        if (func_L00_002D3F30(-1, 1)) {
            func_PAL_L00_002AF458();
            *(unsigned char *)(actor + 0x20) = 2;
            *(int *)(state + 0x20) = 17;
            break;
        }
        if (D_00138180.pressed & D_00189E20.buttons) func_002E5CF8(2, 0, actor);
        break;
    case 2:
        if (!func_00282948((int *)(state + 0x20))) break;
        *(char **)(func_PAL_L00_00390608(position, direction) + 0xB8) = actor;
        func_PAL_L00_002AF6C0();
        *(unsigned char *)(actor + 0x20) = 3;
        *(int *)(state + 0x20) = 8;
        break;
    case 3:
        if (func_00282948((int *)(state + 0x20))) *(unsigned char *)(actor + 0x20) = 1;
        break;
    }
    ref_L00_00397E60_00(func_PAL_L00_0039B490, actor);
}


typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;
extern void func_PAL_002FEC30(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);
extern void func_L00_00398118(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *);

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_PAL_L00_0039B490(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_PAL_002FEC30(1.0f, context, context->vector_10, 0);
    }
}


