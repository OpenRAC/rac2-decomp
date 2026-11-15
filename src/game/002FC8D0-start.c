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
extern Transition g_object_preview_state __attribute__((sda));
extern int D_001AD7E4 SDATA(D_001AD7E4) __attribute__((sda));
extern int D_001AD7E8 SDATA(D_001AD7E8) __attribute__((sda));
/* Real preview vectors in the owning resident byte object. The model-slot
 * table is addressed from that complete object, without a made-up one-slot bound. */
typedef struct {
    unsigned char pad00[0x80];
    float previewFrom[4], previewTo[4];
} ResidentPreviewPrefix;
extern unsigned char g_hero_state[];
/* The voice player's request block (see 00289178.c). */
typedef struct {
    char pad00[0x24];
    int key, selection;
    char pad2C[0x3C];
    int active;
} VoiceRequest;
extern VoiceRequest g_music_state;
extern unsigned char g_item_slot_to_record[];
extern unsigned char g_weapon_table[];
extern float IntToFloat(int);
extern char *part_init_shared_effect_object(int, int);

/* Fills the transition from the preview vectors, asks the voice player for
   line 1511 (key 2000 + 1511) if it is idle, and picks the item's model. */
void BeginPreviewTransition(void)
{
    g_object_preview_state.count = D_001AD7F8;
    g_object_preview_state.rate = 1.0f / IntToFloat(g_object_preview_state.count);
    qcopy(g_object_preview_state.from, ((ResidentPreviewPrefix *)g_hero_state)->previewFrom);
    qcopy(g_object_preview_state.to, ((ResidentPreviewPrefix *)g_hero_state)->previewTo);
    g_object_preview_state.elapsed = 0;
    if (!g_music_state.active && g_music_state.key == -1) {
        /* key before selection: the second store of the pair then holds the
           base's death, so sched1 keeps both ahead of the flag stores, and
           sched2 (where $a1 has no known base) issues selection first. */
        g_music_state.key = 0xDB7;
        g_music_state.selection = 0;
        D_001AD7E4 = 1;
        D_001AD7E8 = 0;
    }
    g_object_preview_state.flag1C = 0;
    g_object_preview_state.flag1D = 0;
    if (g_object_preview_state.item == 31) {
        unsigned char *record = g_item_slot_to_record[31] * 0xE0 + g_weapon_table;
        g_object_preview_state.model = (unsigned char *)part_init_shared_effect_object(*(int *)(record + 0x14), 1);
        g_object_preview_state.owned = 0;
    } else if (g_object_preview_state.item == 45) {
        unsigned char *record = g_item_slot_to_record[45] * 0xE0 + g_weapon_table;
        g_object_preview_state.model = (unsigned char *)part_init_shared_effect_object(*(int *)(record + 0x14), -1);
        g_object_preview_state.owned = 0;
    } else if (g_object_preview_state.item == 9) {
        g_object_preview_state.model = (unsigned char *)part_init_shared_effect_object(601, 0);
        g_object_preview_state.owned = 0;
    } else {
        unsigned char *record;
        char *resident;
        g_object_preview_state.owned = 1;
        record = g_weapon_table + g_item_slot_to_record[g_object_preview_state.item] * 0xE0;
        resident = (char *)g_hero_state;
        g_object_preview_state.model = *(unsigned char **)(resident + *(int *)(record + 0xC) * 0x50 + 0x1220);
    }
}
