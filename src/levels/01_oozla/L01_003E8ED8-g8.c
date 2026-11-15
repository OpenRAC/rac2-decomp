#include "common.h"
typedef struct {
    s32 area[7];
    u8 messageActive;
    u8 initialFlag;
    s16 counter;
    s32 objectIndex;
    s32 unusedArea;
    s32 exitArea;
    s32 messageTimer;
    s32 weaponArea;
    s32 messageArg;
    u8 pad_38[4];
    s32 initialProgress;
    s32 repeatArea;
    s32 lateArea;
    s32 dialogueTimer;
    s32 dialogueIndex;
    s32 dialogueAreas[11];
    s32 specialArea;
    s32 missionArea;
    s32 dialogueActive;
    s32 dialogues[4];
    s32 specialDialogue;
    s32 lastDialogue;
    s32 completeArea0;
    s32 completeArea1;
    u8 pad_a8[4];
    s32 departureArea;
    s32 departed;
    s32 cameraIndex;
} OozlaHints;
typedef struct {
    u8 pad_00[72];
    u16 f48;
    u8 pad_4a[78];
    s32 f98;
    u16 f9c;
    u8 pad_9e[10];
    u16 fa8;
    u8 pad_aa[10];
    u16 fb4;
    u8 pad_b6[10];
    u16 fc0;
    u16 fc2;
    u32 fc4;
    u8 pad_c8[4];
    u16 fcc;
    u8 pad_ce[10];
    u16 fd8;
    u8 pad_da[10];
    u16 fe4;
    u8 pad_e6[2];
    u32 fe8;
    u8 pad_ec[460];
    u16 f2b8;
    u8 pad_2ba[6];
    s32 f2c0;
    u8 pad_2c4[36];
    u16 f2e8;
} OozlaSave;
typedef struct {
    u16 f0;
    u8 pad_02[10];
    u16 fc;
    u8 pad_0e[94];
    u16 f6c;
    u8 pad_6e[2];
    u32 f70;
    u8 pad_74[280];
    u16 f18c;
    u8 pad_18e[10];
    u16 f198;
    u8 pad_19a[34];
    u16 f1bc;
    u8 pad_1be[2];
    u32 f1c0;
} OozlaStats;
typedef struct {
    s32 key0;
    u8 pad_04[32];
    s32 key;
    s32 selection;
    u8 pad_2c[60];
    s32 busy;
    s16 id;
    u8 pad_6e[4];
    s16 state;
} HintScene;
typedef struct HintMoby HintMoby;
struct HintMoby {
    u8 pad_00[0x10];
    f32 position[4];
    u8 state;
    u8 pad_21[3];
    u8 *classData;
    HintMoby *next;
    u8 pad_2c[4];
    u8 alpha;
    u8 pad_31[3];
    u16 flags;
    u8 pad_36[0x32];
    void *pvars;
    u8 pad_6c[0x2c];
    s32 drawDistance;
    u8 pad_9c[14];
    s16 oClass;
    u8 pad_ac[0x54];
};
typedef struct {
    u8 pad00[0x80];
    f32 position[4];
    u8 pad90[0x190];
    s16 field220;
    u8 pad222[0x2072];
    s32 weapon;
    u8 pad2298[0x234];
    s32 field24cc;
} HintHero;
typedef struct {
    u8 pad00[0x75];
    u8 flags75;
    u8 pad76[5];
    union {
        u8 value;
        struct { unsigned char bit0:1, bit1:1, rest:6; } bits;
    } flags7b;
    u8 pad7c[0x1f];
    u8 flag9b;
} HintFlags;
extern OozlaSave D_0018C958;
extern OozlaStats D_0018C750;
extern HintScene D_L01_0027EAC8, D_001A63A8;
/* The game's flag bytes. They are read as D[k], a small symbol plus an offset, which the backend
   keeps as one two-instruction load, tied to its register and out of delay slots. */
extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern s32 D_001A79F0 MACRO_ADDR, D_001A7A00 MACRO_ADDR;
extern HintFlags D_001395B8;
extern HintHero D_00189E20;
extern u8 *D_L01_001B264C __attribute__((sda)), *D_L01_001B255C __attribute__((sda));
extern HintMoby *D_L01_001B2568 __attribute__((sda));
extern u32 D_001A7390 MACRO_ADDR;
extern s32 func_002A77E0(s32);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00312E10(void *);
extern s32 func_L01_00305E18(s32);
extern s32 func_00282948(void *);
extern f32 func_00282E48(void *, void *);
extern void func_L00_002B9D60(void *, void *, s32, s32);
extern void func_L00_003672F8(void);
extern void func_00288D90(void);
extern void func_L01_002EABA8(s32, s32, s32, s32, s32);
extern void func_0028A180(s32, s32);
extern s32 func_00288E18(s32, s32);
extern s32 func_002B6D28(void);
/* Each frame: tests the hero's position against the cuboids listed in the moby's pvars (IsPointInCuboid)
   and, from those and the saved counters, starts the numbered messages and scene dialogues. */
void func_L01_003E8ED8(HintMoby *obj) {
    OozlaHints *hints = obj->pvars;
    HintMoby *other;
    s32 temp, i, found;

    if (!obj->state) {
        obj->alpha = 255;
        obj->state = 1;
        hints->messageTimer = 20;
        hints->messageActive = 0;
        hints->counter = 0;
        hints->initialProgress = gSubtitleHistory.fc0 | gItemOwnedFlags[0x24];
        hints->dialogueIndex = 0;
        hints->departed = 0;
        hints->lastDialogue = -1;
        hints->dialogueTimer = 60;
        if (!RandomIntBelow(1)) {
            temp = hints->dialogues[1];
            hints->dialogues[1] = hints->dialogues[3];
            hints->dialogues[3] = temp;
        }
        if (gItemOwnedFlags[0x24])
            hints->initialFlag = 1;
        else
            hints->initialFlag = 0;
        if (gItemOwnedFlags[0x2e] && !D_001395B8.flag9b && hints->cameraIndex != -1) {
            u8 *camera = D_L01_001B264C + (hints->cameraIndex << 7);
            ResetHeroPositionAndDirection(camera + 0x30, camera + 0x70, 0, 1);
            SetFlagToOne();
        }
    }
    if (hints->objectIndex != -1) {
        HintMoby *door = (HintMoby *)(gMobyTable_L01 + (hints->objectIndex << 8));
        if (door) {
            HintMoby *child = *(HintMoby **)((u8 *)door->pvars + 0xc);
            if (!gItemOwnedFlags[0x13]) {
                door->drawDistance = 0;
                door->flags |= 0x43;
                if (child) {
                    child->drawDistance = 0;
                    child->flags |= 0x43;
                }
            } else {
                door->flags &= 0xffbc;
                door->drawDistance = *(s32 *)(door->classData + 0x10);
                if (child) {
                    child->flags &= 0xffbc;
                    child->drawDistance = *(s32 *)(child->classData + 0x10);
                }
            }
        }
    }
    if ((!gProgressStatistics.f6c || (u32)(D_001A7390 - gProgressStatistics.f70) > 108000U) &&
        ((gSubtitleHistory.f98 & (1U << gCurrentMapIndex)) < 1U))
        RequestSubtitleVoiceLine(0x9b5, 12);
    if (!gSubtitleHistory.f9c && IsPointInCuboid(gHeroState.position, hints->area[0]) && !gProgressStatistics.fc)
        RequestSubtitleVoiceLine(0x9b6, 13);
    if (IsPointInCuboid(gHeroState.position, hints->area[1]) && !gSubtitleHistory.fa8)
        RequestSubtitleVoiceLine(0x9b7, 14);
    if (IsPointInCuboid(gHeroState.position, hints->area[2])) {
        if (hints->messageActive)
            BeginSubtitleClose();
        hints->messageActive = 0;
    }
    if (IsPointInCuboid(gHeroState.position, hints->area[4]))
        gSubtitleHistory.fc0 = 0xffff;
    if (gItemOwnedFlags[0x24] && IsPointInCuboid(gHeroState.position, hints->repeatArea) && !gSubtitleHistory.fc0) {
        if (gSubtitleHistory.fc4 + gSubtitleHistory.fc2 >= D_001A7390 - 2U) {
            gSubtitleHistory.fc2++;
            if (gSubtitleHistory.fc2 >= 180) {
                RequestSubtitleVoiceLine(0x9b9, 16);
                gSubtitleHistory.fc2 = 0;
            }
        } else {
            if (gSubtitleHistory.fc4 < D_001A7390)
                gSubtitleHistory.fc4 = D_001A7390;
            gSubtitleHistory.fc2 = 0;
        }
    }
    if (gItemOwnedFlags[0x2e] && IsPointInCuboid(gHeroState.position, hints->lateArea) &&
        (u32)(D_001A7390 - gSubtitleHistory.fe8) > 3600U)
        RequestSubtitleVoiceLine(0x9bc, 19);
    if (IsPointInCuboid(gHeroState.position, hints->completeArea0) ||
        IsPointInCuboid(gHeroState.position, hints->completeArea1)) {
        D_001395B8.flag9b = 1;
        gSubtitleHistory.fe4 = 0xffff;
    }
    if (!gSubtitleHistory.fb4 && IsPointInCuboid(gHeroState.position, hints->area[3]) && gProgressStatistics.f18c < 100)
        RequestSubtitleVoiceLine(0x9b8, 15);
    if (!gSubtitleHistory.fcc && IsPointInCuboid(gHeroState.position, hints->area[5]) && gProgressStatistics.f198 < 3)
        RequestSubtitleVoiceLine(0x9ba, 17);
    if (!gSubtitleHistory.fd8 && IsPointInCuboid(gHeroState.position, hints->area[6]) && !gProgressStatistics.f0)
        RequestSubtitleVoiceLine(0x9bb, 18);
    if (gHeroState.weapon == 0x39 && IsPointInCuboid(gHeroState.position, hints->weaponArea) &&
        !gSubtitleHistory.f2b8 && !D_001395B8.flags7b.bits.bit1)
        gProgressStatistics.f1bc = 0;
    if (IsPointInCuboid(gHeroState.position, hints->weaponArea) &&
        (!gProgressStatistics.f1bc || (u32)(D_001A7390 - gProgressStatistics.f1c0) > 72000U) &&
        gHeroState.weapon != 0x6f && gHeroState.weapon != 0x39 &&
        ((D_001395B8.flags7b.value ^ 1) & 1) && FastFloatHelperD(&hints->messageTimer) &&
        gSubtitleHistory.f2c0 >= 0)
        RequestSubtitleVoiceLine(0x9e3, 0x3a);
    if (IsPointInCuboid(gHeroState.position, hints->weaponArea) && gHeroState.field220)
        D_001395B8.flags7b.bits.bit1 = 1;
    if (IsPointInCuboid(gHeroState.position, hints->exitArea))
        D_001395B8.flags7b.bits.bit0 = 1;
    if (!IsPointInCuboid(gHeroState.position, hints->departureArea))
        hints->departed = 1;
    if (!D_001A7BC8[2] && hints->departed)
        TriggerSubtitleInCuboid(0x9e4, 0x3b, 1, hints->messageArg, -1);
    if (!gSubtitleHistory.f48) {
        for (other = D_L01_001B2568; other; other = other->next) {
            if (other->oClass == 0x326 && fast_vec_dist(other->position, gHeroState.position) < 10.0f &&
                !D_L01_0027EAC8.key0 && D_L01_0027EAC8.key == -1 && !gSubtitleHistory.f48 &&
                !IsMobyInState1_00312E10(other)) {
                if (gHeroState.field24cc < D_001A7A00)
                    RequestSubtitleVoiceLine(0x9af, 6);
                else if (fast_vec_dist(other->position, gHeroState.position) < 1.0f && !gSubtitleHistory.f2e8)
                    RequestSubtitleVoiceLine(0x9e7, 0x3e);
            }
        }
    }
    if (GetTableEntryShort(3) == 2 && GetTableEntryShort(1) != 2 && !(D_001395B8.flags75 & 2) &&
        IsPointInCuboid(gHeroState.position, hints->missionArea)) {
        D_001395B8.flags75 |= 2;
        QueueHintMessage(0xa3c, 0x93);
    }
    for (i = 0; i < 11; i++) {
        if (IsPointInCuboid(gHeroState.position, hints->dialogueAreas[i]))
            break;
    }
    found = i < 11;
    if (IsPointInCuboid(gHeroState.position, hints->specialArea)) {
        if (hints->lastDialogue != 4 && !gMusicState.busy && gMusicState.key == -1) {
            s32 key = hints->specialDialogue;
            gMusicState.selection = 0;
            gMusicState.key = (key & 0x3fff) + 2000;
            hints->lastDialogue = 4;
            hints->dialogueTimer = 1800;
            hints->dialogueActive = 1;
        }
    } else if (found && !gMusicState.busy && gMusicState.key == -1 && gHeroState.weapon != 0x6f &&
               FastFloatHelperD(&hints->dialogueTimer)) {
        s32 key = hints->dialogues[hints->dialogueIndex];
        gMusicState.selection = 0;
        gMusicState.key = (key & 0x3fff) + 2000;
        hints->lastDialogue = hints->dialogues[hints->dialogueIndex];
        hints->dialogueIndex = (hints->dialogueIndex + 1) & 3;
        hints->dialogueTimer = 1800;
        hints->dialogueActive = 1;
    }
    if (hints->dialogueActive == 1 && gMusicState.state == 3 && gMusicState.id < 6000) {
        ResumeMusicStream();
        hints->dialogueActive = 0;
    }
}
