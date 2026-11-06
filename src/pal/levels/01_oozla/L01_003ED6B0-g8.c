#include "common.h"
/* func_PAL_L01_003ED6B0, the PAL copy of func_L01_003E8ED8: the same C, with its timers at 50 Hz. */
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
extern void func_PAL_L00_002B9CD8(void *, void *, s32, s32);
extern void func_L00_003672F8(void);
extern void func_00288D90(void);
extern void func_PAL_L01_002EBFB8(s32, s32, s32, s32, s32);
extern void func_0028A180(s32, s32);
extern s32 func_PAL_00289730(s32, s32);
extern s32 func_002B6D28(void);
/* Each frame: tests the hero's position against the cuboids listed in the moby's pvars (IsPointInCuboid)
   and, from those and the saved counters, starts the numbered messages and scene dialogues. */
void func_PAL_L01_003ED6B0(HintMoby *obj) {
    OozlaHints *s = obj->pvars;
    HintMoby *p;
    s32 t, i, found;

    if (!obj->state) {
        obj->alpha = 255;
        obj->state = 1;
        s->messageTimer = 17;
        s->messageActive = 0;
        s->counter = 0;
        s->initialProgress = D_0018C958.fc0 | D_001A7AF8[0x24];
        s->dialogueIndex = 0;
        s->departed = 0;
        s->lastDialogue = -1;
        s->dialogueTimer = 50;
        if (!func_002A77E0(1)) {
            t = s->dialogues[1];
            s->dialogues[1] = s->dialogues[3];
            s->dialogues[3] = t;
        }
        if (D_001A7AF8[0x24])
            s->initialFlag = 1;
        else
            s->initialFlag = 0;
        if (D_001A7AF8[0x2e] && !D_001395B8.flag9b && s->cameraIndex != -1) {
            u8 *camera = D_L01_001B264C + (s->cameraIndex << 7);
            func_PAL_L00_002B9CD8(camera + 0x30, camera + 0x70, 0, 1);
            func_L00_003672F8();
        }
    }
    if (s->objectIndex != -1) {
        HintMoby *door = (HintMoby *)(D_L01_001B255C + (s->objectIndex << 8));
        if (door) {
            HintMoby *child = *(HintMoby **)((u8 *)door->pvars + 0xc);
            if (!D_001A7AF8[0x13]) {
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
    if ((!D_0018C750.f6c || (u32)(((s32)D_001A7390 * 5 + 2) / 6 - D_0018C750.f70) > 90000U) &&
        ((D_0018C958.f98 & (1U << D_001A79F0)) < 1U))
        func_PAL_00289730(0x9b5, 12);
    if (!D_0018C958.f9c && func_002ACBC8(D_00189E20.position, s->area[0]) && !D_0018C750.fc)
        func_PAL_00289730(0x9b6, 13);
    if (func_002ACBC8(D_00189E20.position, s->area[1]) && !D_0018C958.fa8)
        func_PAL_00289730(0x9b7, 14);
    if (func_002ACBC8(D_00189E20.position, s->area[2])) {
        if (s->messageActive)
            func_00288D90();
        s->messageActive = 0;
    }
    if (func_002ACBC8(D_00189E20.position, s->area[4]))
        D_0018C958.fc0 = 0xffff;
    if (D_001A7AF8[0x24] && func_002ACBC8(D_00189E20.position, s->repeatArea) && !D_0018C958.fc0) {
        if (D_0018C958.fc4 + D_0018C958.fc2 >= ((s32)D_001A7390 * 5 + 2) / 6 - 2U) {
            D_0018C958.fc2++;
            if (D_0018C958.fc2 >= 150) {
                func_PAL_00289730(0x9b9, 16);
                D_0018C958.fc2 = 0;
            }
        } else {
            if (D_0018C958.fc4 < ((s32)D_001A7390 * 5 + 2) / 6)
                D_0018C958.fc4 = ((s32)D_001A7390 * 5 + 2) / 6;
            D_0018C958.fc2 = 0;
        }
    }
    if (D_001A7AF8[0x2e] && func_002ACBC8(D_00189E20.position, s->lateArea) &&
        (u32)(((s32)D_001A7390 * 5 + 2) / 6 - D_0018C958.fe8) > 3000U)
        func_PAL_00289730(0x9bc, 19);
    if (func_002ACBC8(D_00189E20.position, s->completeArea0) ||
        func_002ACBC8(D_00189E20.position, s->completeArea1)) {
        D_001395B8.flag9b = 1;
        D_0018C958.fe4 = 0xffff;
    }
    if (!D_0018C958.fb4 && func_002ACBC8(D_00189E20.position, s->area[3]) && D_0018C750.f18c < 100)
        func_PAL_00289730(0x9b8, 15);
    if (!D_0018C958.fcc && func_002ACBC8(D_00189E20.position, s->area[5]) && D_0018C750.f198 < 3)
        func_PAL_00289730(0x9ba, 17);
    if (!D_0018C958.fd8 && func_002ACBC8(D_00189E20.position, s->area[6]) && !D_0018C750.f0)
        func_PAL_00289730(0x9bb, 18);
    if (D_00189E20.weapon == 0x39 && func_002ACBC8(D_00189E20.position, s->weaponArea) &&
        !D_0018C958.f2b8 && !D_001395B8.flags7b.bits.bit1)
        D_0018C750.f1bc = 0;
    if (func_002ACBC8(D_00189E20.position, s->weaponArea) &&
        (!D_0018C750.f1bc || (u32)(((s32)D_001A7390 * 5 + 2) / 6 - D_0018C750.f1c0) > 60000U) &&
        D_00189E20.weapon != 0x6f && D_00189E20.weapon != 0x39 &&
        ((D_001395B8.flags7b.value ^ 1) & 1) && func_00282948(&s->messageTimer) &&
        D_0018C958.f2c0 >= 0)
        func_PAL_00289730(0x9e3, 0x3a);
    if (func_002ACBC8(D_00189E20.position, s->weaponArea) && D_00189E20.field220)
        D_001395B8.flags7b.bits.bit1 = 1;
    if (func_002ACBC8(D_00189E20.position, s->exitArea))
        D_001395B8.flags7b.bits.bit0 = 1;
    if (!func_002ACBC8(D_00189E20.position, s->departureArea))
        s->departed = 1;
    if (!D_001A7BC8[2] && s->departed)
        func_PAL_L01_002EBFB8(0x9e4, 0x3b, 1, s->messageArg, -1);
    if (!D_0018C958.f48) {
        for (p = D_L01_001B2568; p; p = p->next) {
            if (p->oClass == 0x326 && func_00282E48(p->position, D_00189E20.position) < 10.0f &&
                !D_L01_0027EAC8.key0 && D_L01_0027EAC8.key == -1 && !D_0018C958.f48 &&
                !func_00312E10(p)) {
                if (D_00189E20.field24cc < D_001A7A00)
                    func_PAL_00289730(0x9af, 6);
                else if (func_00282E48(p->position, D_00189E20.position) < 1.0f && !D_0018C958.f2e8)
                    func_PAL_00289730(0x9e7, 0x3e);
            }
        }
    }
    if (func_L01_00305E18(3) == 2 && func_L01_00305E18(1) != 2 && !(D_001395B8.flags75 & 2) &&
        func_002ACBC8(D_00189E20.position, s->missionArea)) {
        D_001395B8.flags75 |= 2;
        func_0028A180(0xa3c, 0x93);
    }
    for (i = 0; i < 11; i++) {
        if (func_002ACBC8(D_00189E20.position, s->dialogueAreas[i]))
            break;
    }
    found = i < 11;
    if (func_002ACBC8(D_00189E20.position, s->specialArea)) {
        if (s->lastDialogue != 4 && !D_001A63A8.busy && D_001A63A8.key == -1) {
            s32 key = s->specialDialogue;
            D_001A63A8.selection = 0;
            D_001A63A8.key = (key & 0x3fff) + 2000;
            s->lastDialogue = 4;
            s->dialogueTimer = 1500;
            s->dialogueActive = 1;
        }
    } else if (found && !D_001A63A8.busy && D_001A63A8.key == -1 && D_00189E20.weapon != 0x6f &&
               func_00282948(&s->dialogueTimer)) {
        s32 key = s->dialogues[s->dialogueIndex];
        D_001A63A8.selection = 0;
        D_001A63A8.key = (key & 0x3fff) + 2000;
        s->lastDialogue = s->dialogues[s->dialogueIndex];
        s->dialogueIndex = (s->dialogueIndex + 1) & 3;
        s->dialogueTimer = 1500;
        s->dialogueActive = 1;
    }
    if (s->dialogueActive == 1 && D_001A63A8.state == 3 && D_001A63A8.id < 6000) {
        func_002B6D28();
        s->dialogueActive = 0;
    }
}
