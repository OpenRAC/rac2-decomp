#include "common.h"

/* Incomplete SDA arrays preserve the measured absolute accesses in this G8 unit. */
extern int D_L19_001A8F00[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));
typedef struct {
    char pad[0x73C];
    unsigned int time;
} GrelbinTimestamp;
extern GrelbinTimestamp D_0018C958;
extern char D_00188660[];
extern int D_00138324 NOT_SDA;
extern unsigned short D_0018D090 NOT_SDA;
extern char D_L19_001B2424[] __attribute__((sda));
extern int D_L19_001B2728[] __attribute__((sda));
extern void *D_L19_001AC000[] __attribute__((sda));
extern int D_L19_001B06E8 __attribute__((sda));
extern int D_L19_001B06F0 __attribute__((sda));
extern unsigned short D_L19_001B06F4 __attribute__((sda));
extern unsigned short D_L19_001B06F8 __attribute__((sda));
extern float D_L19_001B070C __attribute__((sda));

extern void func_002A7750(char *, int, int);
extern void func_002AA2E8(void *, float, float);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_002E5F40(int, int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282978(void *);
extern void func_0029F338(void *);
extern int func_002B3868(void *);
extern void func_002B4B70(int, int);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L03_003E3A00(void);
extern void func_L03_003E5218(void *);
extern void func_L19_003D3358(void *);
extern void func_L19_003D3CA8(void *);
extern void func_L19_003D3B58(void *);
extern void func_L19_003D4308(void *);
extern void func_L19_003D40C0(void *);
extern void func_L19_003D5218(void *);
extern int func_L19_003D4490(void *);
extern void func_00288E18(int, int);

typedef struct {
    char pad[0x40];
    unsigned char kind;
    char gap[0xF];
    short field50, field52, field54, field56;
    float field58;
    short field5c, field5e, field60, field62, field64, field66, field68, field6a;
    char tail[0x10];
    int sound;
} GrelbinState;

/* Per-frame update for the Infiltrator Ball moby. It steps through its states, tracks its charge level and sounds, and removes itself when the sequence ends. */
void func_L19_003D2E38(char *moby)
{
    GrelbinState *vars;
    int i, sound, kind;

    vars = *(GrelbinState **)(moby + 0x68);
    if (D_L19_001A8F00[0] != 7) {
        if (*(unsigned char *)(moby + 0x20))
            SetMobyState(moby, 0, -1);
        return;
    }
    ApproachValue(D_L19_001B2424, 0.0f, 1.0f / 6.0f);
    D_L19_001B2728[0] = 1;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        for (i = 0; i < 52; i++)
            StopSoundVoice(i);
        func_L19_003D3358(moby);
        *(unsigned short *)(moby + 0x34) |= 0x100;
        func_L19_003D3CA8(moby);
        SetMobyState(moby, gCurrentMapIndex[0] == 11 ? 1 : 3, -1);
        break;
    case 1:
        if (D_001A7390[0] - gSubtitleHistory.time > 1080 || !gSubtitleHistory.time)
            RequestSubtitleVoiceLine(0xA43, 0x9A);
        else if (gSubtitleHistory.time < D_001A7390[0])
            gSubtitleHistory.time = D_001A7390[0];
        SetMobyState(moby, 3, -1);
        break;
    case 2:
        if (!vars->field68) {
            SetMobyState(moby, 4, -1);
            break;
        }
        if (func_L19_003D4490(moby)) {
            vars->field6a = 1;
            func_L19_003D3B58(moby);
            PlayMobySound(4, 0, moby);
            SetMobyState(moby, 3, -1);
        }
        break;
    case 3:
        func_L19_003D4308(moby);
        if (vars->field56) {
            if (vars->field66 != -1) {
                vars->field52 = (unsigned short)vars->field66;
                vars->field66 = -1;
            } else {
                func_L19_003D40C0(moby);
            }
            kind = vars->kind;
            kind ^= 255;
            if (kind == 0) {
                PlayMobySound(0, 0, moby);
            } else {
                sound = PlayMobySound(1, 0, moby);
                if (sound != -1)
                    SetVoicePitchBend(sound, FloatToInt(
                        IntToFloat(vars->field5e) / IntToFloat(D_L19_001B06E8)
                        * 1024.0f) + 1024);
            }
            if (vars->field5e > vars->field60) {
                vars->field60 = (unsigned short)vars->field5e;
                vars->field68 = (unsigned short)vars->field68 + D_L19_001B06F8;
                if (vars->field68 > D_L19_001B06F0)
                    vars->field68 = D_L19_001B06F0;
            }
            if (vars->field5e == D_L19_001B06E8) {
                PlayMobySound(5, 0, moby);
                SetMobyState(moby, 5, -1);
            } else {
                SetMobyState(moby, 2, -1);
            }
        }
        break;
    case 4:
        if (vars->field56) {
            if (vars->field5c != vars->field50) {
                vars->field52 = (unsigned short)vars->field5c;
                func_L19_003D3B58(moby);
                PlayMobySound(2, 0, moby);
            } else {
                vars->field6a = 0;
                vars->field60 = 0;
                vars->field68 = D_L19_001B06F4;
                SetMobyState(moby, 2, -1);
            }
        } else {
            func_L19_003D4308(moby);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(moby))
            *(unsigned short *)(moby + 0x96) = 120;
        if (!*(unsigned short *)(moby + 0x96)) {
            D_0018D090 = 65535;
            SetMobyFlagOn(D_L19_001AC000[0]);
            goto destroy;
        }
        (*(unsigned short *)(moby + 0x96))--;
        break;
    }
    if (D_00138324 & 16) {
        if (*(unsigned char *)(moby + 0x20) == 5)
            SetMobyFlagOn(D_L19_001AC000[0]);
    destroy:
        EndSlotRequest(0, 0);
        MarkMobySpawned(moby);
        return;
    }
    if (*(unsigned char *)(moby + 0x20) != 5 && vars->field6a)
        FastDecTimer(&vars->field68);
    if (vars->field6a && vars->field68) {
        char *soundSlot = gSoundState + vars->sound * 0x70;
        if (*(char **)(soundSlot + 0x88) != moby || !*(unsigned char *)(soundSlot + 0x74))
            vars->sound = PlayMobySound(3, 4, moby);
    } else {
        if (vars->sound != -1) {
            char *soundSlot = gSoundState + vars->sound * 0x70;
            if (*(char **)(soundSlot + 0x88) == moby && *(unsigned char *)(soundSlot + 0x74))
                StopSoundVoice(vars->sound);
        }
        vars->sound = -1;
    }
    func_L19_003D5218(moby);
    vars->field58 -= D_L19_001B070C * (1.0f / 60.0f);
    if (vars->field58 < -1.0f)
        vars->field58 += 1.0f;
    AddDrawCallbackToList1(DrawPathPuzzleHud, moby);
}
