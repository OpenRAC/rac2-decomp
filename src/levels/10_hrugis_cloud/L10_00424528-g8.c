#include "common.h"

/* Needs -frac2-zero-ti-por for the quadword clear of the up vector (config/cflags.txt). */

typedef int GateQuad __attribute__((mode(TI)));

typedef union {
    struct {
        float x, y, z, w;
    } v;
    GateQuad q;
} GateVec;

typedef struct GatePath {
    int count;
    char pad04[12];
    GateVec points[0];
} GatePath;

typedef struct GateObject {
    char pad00[0x10];
    GateVec position;
    char pad20[0x10];
    u8 opacity, pad31;
    u16 drawFlags, flags;
    char pad36[0x32];
    void *state;
    char pad6c[0x3e];
    short classId;
    char padac[0x14];
    GateVec forward, right, up;
} GateObject;

extern int D_L10_001B13A4 __attribute__((sda));
extern GateObject *D_L10_001B1400 __attribute__((sda));
extern GateObject *D_L10_001B1404 __attribute__((sda));
extern char *D_L10_001B1408 __attribute__((sda));
extern float D_L10_001B140C __attribute__((sda)), D_L10_001B1410 __attribute__((sda));
extern int D_L10_001B1414 __attribute__((sda)), D_L10_001B1418 __attribute__((sda));
extern int D_L10_001B141C __attribute__((sda));
extern int D_L10_001B1434 __attribute__((sda));
extern int D_L10_001B3550 MACRO_ADDR;

typedef struct {
    char pad[0x2c];
    int field2c;
    char pad30[8];
    int field38;
} GateGlobals;

extern GateGlobals D_L10_00221CD0;
extern GatePath *D_L10_001FE340[];
extern char *D_L10_001B251C[] __attribute__((sda));
extern char D_L10_001B9680[];
extern int D_001A79F0;
extern unsigned char D_0019B278[];

extern void func_002B7320(void), func_L10_00425798(void), func_L05_0037B210(void);
extern void func_L05_00379F28(int), func_L05_00379F18(int);
extern GateObject **func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern GateObject *func_L05_00379ED0(int);
extern int func_L00_0042B730(void *);
extern void func_L05_0037B280(void *, int);
extern GateObject *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *), func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *), func_00282E48(void *, void *);
extern void func_L10_00423DC8(void *, int), func_L10_00423500(void *);
extern int func_00282948(int *);
extern char *func_00288FB8(int);
extern void func_L00_0030DD70(void *, int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_L05_0037ADD8(float);
extern void func_L05_00424980(void *, int), func_L05_00424970(void *, int);
extern char *func_L05_0042C928(void *, int, int, int);

/* Runs the gate course: keeps the next two gate markers ahead, scores the player when passing
   through one and shows a warning after too many misses. */
void func_L10_00424528(GateObject *controller)
{
    GateVec up, viewPos, toPlayer, toView;
    char *vars = controller->state, *player;
    GatePath *path;
    GateObject *gate;
    GateObject **mobyList;
    int count, i;
    float playerDot, viewDot;

    up.q = 0;
    up.v.z = 1;

    if (!gMissionInitialized) {
        D_L10_001B140C = -1;
        D_L10_001B1410 = -1;
        gMissionInitialized = 1;
        D_L10_001B1400 = 0;
        D_L10_001B1404 = 0;
        D_L10_001B1414 = 0;
        D_L10_001B1418 = 0;
        D_L10_001B141C = 0;
        D_L10_001B3550 = 0;
        D_L10_00221CD0.field2c = 0;
        music_Unpause();
        DestroyLeftoverCloudObjects();
        if (D_L10_001B1408)
            MarkMobySpawned(D_L10_001B1408);
        InitAllRegisteredEntries();
        D_L10_001B1408 = 0;
        SetPlayerStateField15(1);
        D_L10_00221CD0.field38 = *(int *)(vars + 0x20);
        SetPlayerStateField13(0);
        mobyList = GetLevelObjectList();
        count = GetLevelSavedValue();
        for (i = 0; i < count; i++) {
            if (mobyList[i]->classId == 0xf82 /* moby class 3970 */)
                SpawnEntryListObjectsWithFlag(mobyList[i], 1);
        }
        path = D_L10_001FE340[*(int *)(vars + 0x20)];
        while ((!D_L10_001B1400 || !D_L10_001B1404) && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                gate = CreateMoby(0x114a /* moby class 4426 */);
                gate->opacity = 255;
                gate->drawFlags = 0x1ff;
                gate->flags |= 0x100;
                if (!D_L10_001B1400)
                    D_L10_001B1400 = gate;
                else
                    D_L10_001B1404 = gate;
                if (D_L10_001B1418 == path->count - 1) {
                    FastVecSub(&gate->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1);
                } else {
                    FastVecSub(&gate->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1);
                }
                FastVecCross(&gate->right, &gate->forward, &up);
                vec_scale_to_length(&gate->right, &gate->right, 1);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                gate->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    if (!D_L10_001B1400 && !D_L10_001B1404 && !D_L10_001B1434) {
        FinishMissionAndGrantReward(controller, 3);
        return;
    }

    if (GetLevelSavedValueB(FindLevelObjectByClassId(0xf82 /* moby class 3970 */))) {
        D_L10_001B1434 = 1;
        if (FastFloatHelperD((int *)(vars + 0x50))) {
            D_L10_001B1434 = 0;
            *(int *)(vars + 0x50) = 240;
            ResetHrugisMissionState(controller);
            InitAllRegisteredEntries();
        } else
            goto warning;
    } else if (D_L10_001B141C >= 12) {
        D_L10_001B1434 = 1;
        if (!FastFloatHelperD((int *)(vars + 0x50))) {
        warning:
            CallLoadedModuleHandlerWithArg_003387A0_1(GetLocalizedString(0x31de), -1);
        } else {
            D_L10_001B1434 = 0;
            ResetHrugisMissionState(controller);
            InitAllRegisteredEntries();
            *(int *)(vars + 0x50) = 240;
        }
    }

    if (D_L10_001B1434)
        return;
    D_L10_001B3550 = D_L10_001B3550 + 1;
    if (D_L10_001B3550 < 2)
        return;

    player = D_L10_001B251C[0] + (*(int *)(vars + 0x24) << 8);
    qcopy(&viewPos, D_L10_001B9680);
    FastVecSub(&toView, &viewPos, &D_L10_001B1400->position);
    vec_scale_to_length(&toView, &toView, 1);
    FastVecSub(&toPlayer, player + 0x10, &D_L10_001B1400->position);
    vec_scale_to_length(&toPlayer, &toPlayer, 1);
    playerDot = FastVecDot(&D_L10_001B1400->forward, &toPlayer);
    viewDot = FastVecDot(&D_L10_001B1400->forward, &toView);

    if ((playerDot != D_L10_001B140C && playerDot > 0) || (viewDot != D_L10_001B1410 && viewDot > 0)) {
        path = D_L10_001FE340[*(int *)(vars + 0x20)];
        if (fast_vec_dist(&viewPos, &D_L10_001B1400->position) <= 1.25f
            || fast_vec_dist(player + 0x10, &D_L10_001B1400->position) <= 1.25f) {
            PlaySoundFromClassBank(15, 0, controller, 0xfbf);
            AddClampedStatValue(0.5f);
        } else {
            AddClampedStatValue(-0.75f);
            D_L10_001B141C++;
        }
        MarkMobySpawned(D_L10_001B1400);
        D_L10_001B1400 = D_L10_001B1404;
        D_L10_001B1404 = 0;
        while (!D_L10_001B1404 && D_L10_001B1418 != path->count) {
            if (path->points[D_L10_001B1418].v.w != -1) {
                gate = CreateMoby(0x114a /* moby class 4426 */);
                gate->opacity = 255;
                gate->drawFlags = 0x1ff;
                gate->flags |= 0x100;
                D_L10_001B1404 = gate;
                if (D_L10_001B1418 == path->count - 1) {
                    FastVecSub(&gate->forward, (char *)path + D_L10_001B1418 * 16,
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, -1);
                } else {
                    FastVecSub(&gate->forward, (char *)path + (D_L10_001B1418 * 16 + 0x20),
                                  (char *)path + (D_L10_001B1418 * 16 + 0x10));
                    gate->forward.v.w = 0;
                    vec_scale_to_length(&gate->forward, &gate->forward, 1);
                }
                FastVecCross(&gate->right, &gate->forward, &up);
                vec_scale_to_length(&gate->right, &gate->right, 1);
                FastVecCross(&gate->up, &gate->right, &gate->forward);
                qcopy(&gate->position, (char *)path + (D_L10_001B1418 * 16 + 0x10));
                gate->position.v.w = 0;
            }
            D_L10_001B1418++;
        }
    }

    D_L10_001B140C = playerDot;
    D_L10_001B1410 = viewDot;

    if (D_L10_001B1400) {
        SetEffectEnabled(D_L10_001B1400, 1);
        if (D_L10_001B1404)
            SetEffectColor(D_L10_001B1400, 0x40008000);
        else
            SetEffectColor(D_L10_001B1400, 0x4000c6ff);
    }

    if (D_L10_001B1404) {
        SetEffectEnabled(D_L10_001B1404, 1);
        SetEffectColor(D_L10_001B1404, 0x40808000);
    } else if (!D_L10_001B141C && !D_L10_001B1408 && !D_0019B278[gCurrentMapIndex * 4]) {
        D_L10_001B1408 = SpawnCollectibleIfNotTaken(&D_L10_001B1400->position, 0, -1, -1);
    }
}
