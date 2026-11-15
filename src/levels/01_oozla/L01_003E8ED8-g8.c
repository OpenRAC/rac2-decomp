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
extern OozlaSave g_subtitle_history;
extern OozlaStats g_progress_statistics;
extern HintScene D_L01_0027EAC8, g_music_state;
/* The game's flag bytes. They are read as D[k], a small symbol plus an offset, which the backend
   keeps as one two-instruction load, tied to its register and out of delay slots. */
extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern s32 g_current_map_index MACRO_ADDR, D_001A7A00 MACRO_ADDR;
extern HintFlags D_001395B8;
extern HintHero g_hero_state;
extern u8 *D_L01_001B264C __attribute__((sda)), *g_moby_l01_table __attribute__((sda));
extern HintMoby *D_L01_001B2568 __attribute__((sda));
extern u32 D_001A7390 MACRO_ADDR;
extern s32 math_random_int_below(s32);
extern s32 IsPointInCuboid(void *, s32);
extern s32 moby_is_state_one(void *);
extern s32 level_get_table_entry_short(s32);
extern s32 math_fast_float_d(void *);
extern f32 fast_vec_dist(void *, void *);
extern void hero_reset_position_and_direction(void *, void *, s32, s32);
extern void state_set_flag_one(void);
extern void subtitle_begin_close(void);
extern void TriggerSubtitleInCuboid(s32, s32, s32, s32, s32);
extern void hud_queue_hint_message(s32, s32);
extern s32 subtitle_request_voice_line(s32, s32);
extern s32 snd_resume_music_stream(void);
/* Each frame: tests the hero's position against the cuboids listed in the moby's pvars (IsPointInCuboid)
   and, from those and the saved counters, starts the numbered messages and scene dialogues. */
void hint_message_controller_update(HintMoby *obj) {
    OozlaHints *hints = obj->pvars;
    HintMoby *other;
    s32 temp, i, found;

    if (!obj->state) {
        obj->alpha = 255;
        obj->state = 1;
        hints->messageTimer = 20;
        hints->messageActive = 0;
        hints->counter = 0;
        hints->initialProgress = g_subtitle_history.fc0 | g_item_owned_flags[0x24];
        hints->dialogueIndex = 0;
        hints->departed = 0;
        hints->lastDialogue = -1;
        hints->dialogueTimer = 60;
        if (!math_random_int_below(1)) {
            temp = hints->dialogues[1];
            hints->dialogues[1] = hints->dialogues[3];
            hints->dialogues[3] = temp;
        }
        if (g_item_owned_flags[0x24])
            hints->initialFlag = 1;
        else
            hints->initialFlag = 0;
        if (g_item_owned_flags[0x2e] && !D_001395B8.flag9b && hints->cameraIndex != -1) {
            u8 *camera = D_L01_001B264C + (hints->cameraIndex << 7);
            hero_reset_position_and_direction(camera + 0x30, camera + 0x70, 0, 1);
            state_set_flag_one();
        }
    }
    if (hints->objectIndex != -1) {
        HintMoby *door = (HintMoby *)(g_moby_l01_table + (hints->objectIndex << 8));
        if (door) {
            HintMoby *child = *(HintMoby **)((u8 *)door->pvars + 0xc);
            if (!g_item_owned_flags[0x13]) {
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
    if ((!g_progress_statistics.f6c || (u32)(D_001A7390 - g_progress_statistics.f70) > 108000U) &&
        ((g_subtitle_history.f98 & (1U << g_current_map_index)) < 1U))
        subtitle_request_voice_line(0x9b5, 12);
    if (!g_subtitle_history.f9c && IsPointInCuboid(g_hero_state.position, hints->area[0]) && !g_progress_statistics.fc)
        subtitle_request_voice_line(0x9b6, 13);
    if (IsPointInCuboid(g_hero_state.position, hints->area[1]) && !g_subtitle_history.fa8)
        subtitle_request_voice_line(0x9b7, 14);
    if (IsPointInCuboid(g_hero_state.position, hints->area[2])) {
        if (hints->messageActive)
            subtitle_begin_close();
        hints->messageActive = 0;
    }
    if (IsPointInCuboid(g_hero_state.position, hints->area[4]))
        g_subtitle_history.fc0 = 0xffff;
    if (g_item_owned_flags[0x24] && IsPointInCuboid(g_hero_state.position, hints->repeatArea) && !g_subtitle_history.fc0) {
        if (g_subtitle_history.fc4 + g_subtitle_history.fc2 >= D_001A7390 - 2U) {
            g_subtitle_history.fc2++;
            if (g_subtitle_history.fc2 >= 180) {
                subtitle_request_voice_line(0x9b9, 16);
                g_subtitle_history.fc2 = 0;
            }
        } else {
            if (g_subtitle_history.fc4 < D_001A7390)
                g_subtitle_history.fc4 = D_001A7390;
            g_subtitle_history.fc2 = 0;
        }
    }
    if (g_item_owned_flags[0x2e] && IsPointInCuboid(g_hero_state.position, hints->lateArea) &&
        (u32)(D_001A7390 - g_subtitle_history.fe8) > 3600U)
        subtitle_request_voice_line(0x9bc, 19);
    if (IsPointInCuboid(g_hero_state.position, hints->completeArea0) ||
        IsPointInCuboid(g_hero_state.position, hints->completeArea1)) {
        D_001395B8.flag9b = 1;
        g_subtitle_history.fe4 = 0xffff;
    }
    if (!g_subtitle_history.fb4 && IsPointInCuboid(g_hero_state.position, hints->area[3]) && g_progress_statistics.f18c < 100)
        subtitle_request_voice_line(0x9b8, 15);
    if (!g_subtitle_history.fcc && IsPointInCuboid(g_hero_state.position, hints->area[5]) && g_progress_statistics.f198 < 3)
        subtitle_request_voice_line(0x9ba, 17);
    if (!g_subtitle_history.fd8 && IsPointInCuboid(g_hero_state.position, hints->area[6]) && !g_progress_statistics.f0)
        subtitle_request_voice_line(0x9bb, 18);
    if (g_hero_state.weapon == 0x39 && IsPointInCuboid(g_hero_state.position, hints->weaponArea) &&
        !g_subtitle_history.f2b8 && !D_001395B8.flags7b.bits.bit1)
        g_progress_statistics.f1bc = 0;
    if (IsPointInCuboid(g_hero_state.position, hints->weaponArea) &&
        (!g_progress_statistics.f1bc || (u32)(D_001A7390 - g_progress_statistics.f1c0) > 72000U) &&
        g_hero_state.weapon != 0x6f && g_hero_state.weapon != 0x39 &&
        ((D_001395B8.flags7b.value ^ 1) & 1) && math_fast_float_d(&hints->messageTimer) &&
        g_subtitle_history.f2c0 >= 0)
        subtitle_request_voice_line(0x9e3, 0x3a);
    if (IsPointInCuboid(g_hero_state.position, hints->weaponArea) && g_hero_state.field220)
        D_001395B8.flags7b.bits.bit1 = 1;
    if (IsPointInCuboid(g_hero_state.position, hints->exitArea))
        D_001395B8.flags7b.bits.bit0 = 1;
    if (!IsPointInCuboid(g_hero_state.position, hints->departureArea))
        hints->departed = 1;
    if (!D_001A7BC8[2] && hints->departed)
        TriggerSubtitleInCuboid(0x9e4, 0x3b, 1, hints->messageArg, -1);
    if (!g_subtitle_history.f48) {
        for (other = D_L01_001B2568; other; other = other->next) {
            if (other->oClass == 0x326 && fast_vec_dist(other->position, g_hero_state.position) < 10.0f &&
                !D_L01_0027EAC8.key0 && D_L01_0027EAC8.key == -1 && !g_subtitle_history.f48 &&
                !moby_is_state_one(other)) {
                if (g_hero_state.field24cc < D_001A7A00)
                    subtitle_request_voice_line(0x9af, 6);
                else if (fast_vec_dist(other->position, g_hero_state.position) < 1.0f && !g_subtitle_history.f2e8)
                    subtitle_request_voice_line(0x9e7, 0x3e);
            }
        }
    }
    if (level_get_table_entry_short(3) == 2 && level_get_table_entry_short(1) != 2 && !(D_001395B8.flags75 & 2) &&
        IsPointInCuboid(g_hero_state.position, hints->missionArea)) {
        D_001395B8.flags75 |= 2;
        hud_queue_hint_message(0xa3c, 0x93);
    }
    for (i = 0; i < 11; i++) {
        if (IsPointInCuboid(g_hero_state.position, hints->dialogueAreas[i]))
            break;
    }
    found = i < 11;
    if (IsPointInCuboid(g_hero_state.position, hints->specialArea)) {
        if (hints->lastDialogue != 4 && !g_music_state.busy && g_music_state.key == -1) {
            s32 key = hints->specialDialogue;
            g_music_state.selection = 0;
            g_music_state.key = (key & 0x3fff) + 2000;
            hints->lastDialogue = 4;
            hints->dialogueTimer = 1800;
            hints->dialogueActive = 1;
        }
    } else if (found && !g_music_state.busy && g_music_state.key == -1 && g_hero_state.weapon != 0x6f &&
               math_fast_float_d(&hints->dialogueTimer)) {
        s32 key = hints->dialogues[hints->dialogueIndex];
        g_music_state.selection = 0;
        g_music_state.key = (key & 0x3fff) + 2000;
        hints->lastDialogue = hints->dialogues[hints->dialogueIndex];
        hints->dialogueIndex = (hints->dialogueIndex + 1) & 3;
        hints->dialogueTimer = 1800;
        hints->dialogueActive = 1;
    }
    if (hints->dialogueActive == 1 && g_music_state.state == 3 && g_music_state.id < 6000) {
        snd_resume_music_stream();
        hints->dialogueActive = 0;
    }
}
