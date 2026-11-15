#include "include_asm.h"

#include "common.h"
typedef struct { u8 pad[6]; s16 index; u8 tail[2]; } InputEntry;
typedef struct { u8 pad[6]; s16 value; u8 tail[216]; } InputRecord;
extern InputEntry D_001AA7D8[];
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 g_item_slot_to_record[];
extern InputRecord g_weapon_table[];
extern int D_001F288C[];
extern int g_selected_item_material __attribute__((sda));
extern int snd_play_from_global_bank(int, int, int);

void func_US2_00346AF8(char *o, int buttons) {
#define I(off) (*(int *)(o+(off)))
    int index;
    if (buttons & 0x1000) {
        snd_play_from_global_bank(3,0,0); I(0x4FC)++; I(0x500)=1; I(0x508)=0;
    } else if (buttons & 0x4000) {
        snd_play_from_global_bank(3,0,0); I(0x4FC)++; I(0x508)=1; I(0x500)=0;
    } else if (buttons & 0x8000) {
        snd_play_from_global_bank(3,0,0); if (--I(0x4FC)<0) I(0x4FC)=1;
    } else if (buttons & 0x2000) {
        snd_play_from_global_bank(3,0,0); if (++I(0x4FC)>=2) I(0x4FC)=0;
    } else if (buttons & 0x40) {
        index=D_001AA7D8[I(0x4FC)].index;
        if (index && g_item_owned_flags[index]) { snd_play_from_global_bank(4,0,0); D_001F288C[0]=index; I(0x504)=index; }
        else snd_play_from_global_bank(5,0,0);
    }
    { int selected=D_001AA7D8[I(0x4FC)].index;
    I(0x504)=selected;
    if (selected && g_item_owned_flags[selected]) g_selected_item_material=((InputRecord *)(g_item_slot_to_record[selected]*224 + (char *)g_weapon_table))->value; }
#undef I
}
