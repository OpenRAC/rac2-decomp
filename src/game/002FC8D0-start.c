#include "common.h"

/* The start of the object preview's transition (func_002FF0D8), in a unit of
   its own: it is built with -g, whose line label before the division keeps
   the two padding nops retail has in front of div.s. */

extern u16 D_001AD7F8 SDATA(D_001AD7F8);
typedef struct {
    s16 elapsed;
    s16 count;
    float rate;
    s16 item;
    s16 pad1A;
    u8 flag1C;
    u8 flag1D;
    u8 pad1E[2];
    float from[4];
    float to[4];
    unsigned char *model;
    u8 pad44;
    u8 owned;
} Transition;
extern Transition D_001B2310 __attribute__((sda));
extern int D_001AD7E4 SDATA(D_001AD7E4) __attribute__((sda));
extern int D_001AD7E8 SDATA(D_001AD7E8) __attribute__((sda));
/* Real preview vectors in the owning resident byte object. The model-slot
 * table is addressed from that complete object, without a made-up one-slot bound. */
typedef struct {
    unsigned char pad00[0x80];
    float previewFrom[4], previewTo[4];
} ResidentPreviewPrefix;
extern unsigned char D_00189E20[];
/* The voice player's request block (see 00289178.c). */
typedef struct {
    char pad00[0x24];
    int key, selection;
    char pad2C[0x3C];
    int active;
} VoiceRequest;
extern VoiceRequest D_001A63A8;
extern unsigned char D_00139568[];
extern unsigned char D_00239BA0[];
extern float func_00283CE0(int);
extern char *func_002FF300(int, int);

/* Fills the transition from the preview vectors, asks the voice player for
   line 1511 (key 2000 + 1511) if it is idle, and picks the item's model. */
void func_002FF0D8(void)
{
    gObjectPreviewState.count = D_001AD7F8;
    gObjectPreviewState.rate = 1.0f / IntToFloat(gObjectPreviewState.count);
    qcopy(gObjectPreviewState.from, ((ResidentPreviewPrefix *)gHeroState)->previewFrom);
    qcopy(gObjectPreviewState.to, ((ResidentPreviewPrefix *)gHeroState)->previewTo);
    gObjectPreviewState.elapsed = 0;
    if (!gMusicState.active && gMusicState.key == -1) {
        /* key before selection: the second store of the pair then holds the
           base's death, so sched1 keeps both ahead of the flag stores, and
           sched2 (where $a1 has no known base) issues selection first. */
        gMusicState.key = 0xDB7;
        gMusicState.selection = 0;
        D_001AD7E4 = 1;
        D_001AD7E8 = 0;
    }
    gObjectPreviewState.flag1C = 0;
    gObjectPreviewState.flag1D = 0;
    if (gObjectPreviewState.item == 31) {
        unsigned char *record = gItemSlotToRecord[31] * 0xE0 + gWeaponTable_00239BA0;
        gObjectPreviewState.model = (unsigned char *)InitSharedEffectObject(*(int *)(record + 0x14), 1);
        gObjectPreviewState.owned = 0;
    } else if (gObjectPreviewState.item == 45) {
        unsigned char *record = gItemSlotToRecord[45] * 0xE0 + gWeaponTable_00239BA0;
        gObjectPreviewState.model = (unsigned char *)InitSharedEffectObject(*(int *)(record + 0x14), -1);
        gObjectPreviewState.owned = 0;
    } else if (gObjectPreviewState.item == 9) {
        gObjectPreviewState.model = (unsigned char *)InitSharedEffectObject(601, 0);
        gObjectPreviewState.owned = 0;
    } else {
        unsigned char *record;
        char *resident;
        gObjectPreviewState.owned = 1;
        record = gWeaponTable_00239BA0 + gItemSlotToRecord[gObjectPreviewState.item] * 0xE0;
        resident = (char *)gHeroState;
        gObjectPreviewState.model = *(unsigned char **)(resident + *(int *)(record + 0xC) * 0x50 + 0x1220);
    }
}
