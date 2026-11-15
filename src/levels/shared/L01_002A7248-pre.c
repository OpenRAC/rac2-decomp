#include "names.h"
/* The weapon animation id without the hero's 0x1492 alternative. Own unit:
   -frac2-gcse-unsplit-edges lets PRE hoist the hero's high half above the first test,
   while each block forms its own low half. */
typedef unsigned char u8; typedef short s16; typedef unsigned short u16; typedef int s32; typedef unsigned int u32; typedef float f32;
typedef union { u8 b[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; } Hero;

extern char D_00189E20[];
extern u8 D_00139568[];
extern char D_L01_002637A0[];
extern int func_L00_002ADEA0(int);

typedef struct {
    u8 pad[0x28];
    int v;
} WeaponEntry;

int func_L01_002A7248(char *a0)
{
    if (a0 != 0 && ((Hero *)gHeroState)->b[0x22BA] != 0 && ((Hero *)gHeroState)->h[0x24EC / 2] == 0) {
        int idx = hero_slot_item_id(0);
        return ((WeaponEntry *)(D_L01_002637A0 + gItemSlotToRecord[idx] * 224))->v;
    }
    if (((Hero *)gHeroState)->i[0x24CC / 4] != 1)
        return 0;
    return 0x51;
}

/* One entry of the subtitle history (src/game/00289178.c): how often the selection was
   shown, the frame it was last shown, and a bit per level it was shown in (bit 31: any). */
typedef struct {
    unsigned short count, pad;
    unsigned int time;
    int levels;
} SubtitleHistory;

extern SubtitleHistory D_0018C958[];
extern unsigned int D_001A7390[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern char D_00189EA0[];
extern int func_002ACBC8(void *, int);
extern int func_00288E18(int, int);

/* Subtitle trigger: when the hero stands in area (and not in exclude), queue the subtitle
   selection by mode: 0 once, 1 again after 1080 frames, 2 first only recorded then like 1,
   3 unless already shown. Own unit, like func_L01_002A7248. The cases index the history table
   again instead of reusing entry: sharing the pointer changes the compiled code. */
void func_L01_002EABA8(int key, int selection, int mode, int area, int exclude)
{
    int limit = mode == 0 ? 1 : 65535;
    SubtitleHistory *entry = &gSubtitleHistory[selection];

    if (entry->count < limit) {
        if (exclude != -1 && IsPointInCuboid(gHeroPosition, exclude)) {
            entry->count = 65535;
            return;
        }
        if (IsPointInCuboid(gHeroPosition, area)) {
            switch (mode) {
            case 0:
                RequestSubtitleVoiceLine(key, selection);
                break;
            case 1:
                if (D_001A7390[0] - gSubtitleHistory[selection].time > 1080 || gSubtitleHistory[selection].time == 0)
                    RequestSubtitleVoiceLine(key, selection);
                else if (gSubtitleHistory[selection].time < D_001A7390[0])
                    gSubtitleHistory[selection].time = D_001A7390[0];
                break;
            case 2:
                if (gSubtitleHistory[selection].count != 0) {
                    if (D_001A7390[0] - gSubtitleHistory[selection].time > 1080 || gSubtitleHistory[selection].time == 0)
                        RequestSubtitleVoiceLine(key, selection);
                    else if (gSubtitleHistory[selection].time < D_001A7390[0])
                        gSubtitleHistory[selection].time = D_001A7390[0];
                    break;
                }
                gSubtitleHistory[selection].count++;
                if (gSubtitleHistory[selection].time < D_001A7390[0])
                    gSubtitleHistory[selection].time = D_001A7390[0];
                gSubtitleHistory[selection].levels = (gSubtitleHistory[selection].levels | (1 << gCurrentMapIndex[0])) | 0x80000000;
                break;
            case 3:
                if (gSubtitleHistory[selection].levels >= 0)
                    RequestSubtitleVoiceLine(key, selection);
                break;
            }
        }
    }
}
