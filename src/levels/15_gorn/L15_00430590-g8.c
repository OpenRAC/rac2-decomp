#include "common.h"
extern char *D_L15_001B261C;
extern char D_00188660[];

typedef struct { char pad[0x270]; int id; } GornData;
extern int D_L15_001A8F00 MACRO_ADDR;
extern int D_L15_001A904C __attribute__((sda));
extern int D_L15_001B15CC __attribute__((sda));
extern int D_L15_001B1520[4] __attribute__((sda));
extern int D_L15_001B15D8[4][3] __attribute__((sda));
extern int D_L15_001B157C __attribute__((sda)), D_L15_001B1578 __attribute__((sda));
extern int D_L15_001B15C8 __attribute__((sda)), D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B36A4, D_001A79F8;
extern unsigned char D_001A7A0A;
extern int D_00138324 NOT_SDA;
/* Absolute suffix view shared with func_L15_00432008. */
extern int D_L15_001B1520_4[] MACRO_ADDR;
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0027D330(int);
extern void func_0029B758(int, void *);
extern void func_L15_00430168(void);
extern void func_L15_00432008(void);
extern void func_0029B3E0(int,int);
extern void func_L05_00379F48(int);
extern void func_L15_0042FD40(void *);
extern void func_002B49E0(int,int,int,int,int);
/* Ends a Gorn challenge stage: stops its sound, pays the reward, shows the reward panel and then picks the next menu entry. */
void func_L15_00430590(char *moby, int stageNum)
{
    char *vars = *(char **)(moby + 0x68);
    char *targetMoby = D_L15_001B261C + (*(int *)(vars + 0x20) << 8);
    GornData *data = *(GornData **)(targetMoby + 0x68);
    int soundId = data->id;
    if (soundId != -1) {
        char *entry = gSoundState + soundId * 0x70;
        if (*(char **)(entry + 0x88) == targetMoby && *(unsigned char *)(entry + 0x74))
            StopSoundVoice(soundId);
    }
    data->id = -1;
    if (D_L15_001A8F00 == 2) {
        return;
    }
    if (!FastFloatHelperD(vars + 0x6C)) {
        return;
    }
    if (D_L15_001A904C && !D_L15_001B15CC) {
        int timesDone, reward;
        FadeToBlack(30);
        StoreLevelObjectValuePair(0, DrawGornRewardPanel);
        timesDone = D_L15_001B1520[stageNum];
        reward = D_L15_001B15D8[stageNum][timesDone < 3 ? timesDone : 2];
        D_L15_001B15CC = 1;
        D_L15_001B36A4 = stageNum;
        D_L15_001B157C = 0;
        D_L15_001B1578 = 0;
        if (D_001A7A0A) reward *= 10;
        D_L15_001B1520[stageNum] = timesDone + 1;
        gPlayerBolts = gPlayerBolts + reward;
        ClampAndCopyVolumeSettings();
        MemcardSave(0, -1);
    }
    SetPlayerStateField18(1);
    if (!FastFloatHelperD(vars + 0x50)) {
        if (D_00138324 & 0x40) {
            D_L15_001B15CC = 0;
            *(int *)(vars + 0x50) = 5400;
            FadeToBlack(30);
            SetPlayerStateField18(0);
            *(int *)(vars + 0x6C) = 120;
            if (D_L15_001B1520[0]) {
                if (D_L15_001B1520_4[1] && D_L15_001B1520_4[2]) {
                    D_L15_001B15C8 = 3;
                } else if (D_L15_001B1520[0]) {
                    if (D_L15_001B1520_4[1]) {
                        D_L15_001B15C8 = 2;
                    } else {
                        D_L15_001B15C8 = 1;
                    }
                }
            }
            D_L15_001B15BC = 0;
            ResetGornStageCounters(moby);
        } else if (D_00138324 & 0x10) {
            BeginSlotRequest(3, 1, 4, 0, 0);
        }
    } else {
        *(int *)(vars + 0x50) = 5400;
    }
}
