#include "common.h"

/* func_PAL_00300130, the PAL copy of func_002FF0D8: the same C, where the
   transition's length is scaled to 50 Hz and read as the int it is. A unit of
   its own: it is built with -g, whose line label before the division keeps
   the two padding nops retail has in front of div.s. */

extern int D_001AD7F8 SDATA(D_001AD7F8);
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
#define PREVIEW ((ResidentPreviewPrefix *)D_00189E20)
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
void func_PAL_00300130(void)
{
    D_001B2310.count = ((s32)(D_001AD7F8) * 5 + 2) / 6;
    D_001B2310.rate = 1.0f / func_00283CE0(D_001B2310.count);
    qcopy(D_001B2310.from, PREVIEW->previewFrom);
    qcopy(D_001B2310.to, PREVIEW->previewTo);
    D_001B2310.elapsed = 0;
    if (!D_001A63A8.active && D_001A63A8.key == -1) {
        /* key before selection: the second store of the pair then holds the
           base's death, so sched1 keeps both ahead of the flag stores, and
           sched2 (where $a1 has no known base) issues selection first. */
        D_001A63A8.key = 0xDB7;
        D_001A63A8.selection = 0;
        D_001AD7E4 = 1;
        D_001AD7E8 = 0;
    }
    D_001B2310.flag1C = 0;
    D_001B2310.flag1D = 0;
    if (D_001B2310.item == 31) {
        unsigned char *record = D_00139568[31] * 0xE0 + D_00239BA0;
        D_001B2310.model = (unsigned char *)func_002FF300(*(int *)(record + 0x14), 1);
        D_001B2310.owned = 0;
    } else if (D_001B2310.item == 45) {
        unsigned char *record = D_00139568[45] * 0xE0 + D_00239BA0;
        D_001B2310.model = (unsigned char *)func_002FF300(*(int *)(record + 0x14), -1);
        D_001B2310.owned = 0;
    } else if (D_001B2310.item == 9) {
        D_001B2310.model = (unsigned char *)func_002FF300(601, 0);
        D_001B2310.owned = 0;
    } else {
        unsigned char *record;
        char *resident;
        D_001B2310.owned = 1;
        record = D_00239BA0 + D_00139568[D_001B2310.item] * 0xE0;
        resident = (char *)D_00189E20;
        D_001B2310.model = *(unsigned char **)(resident + *(int *)(record + 0xC) * 0x50 + 0x1220);
    }
}
