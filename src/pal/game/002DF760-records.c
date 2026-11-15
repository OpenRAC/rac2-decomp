#include "common.h"

typedef unsigned int QuadDE990 __attribute__((mode(TI)));
typedef union RecordDE990 {
    QuadDE990 data[14];
    struct {
        char pad0[4];
        unsigned char kind;
        char pad5[0x67];
        int value;
        char pad70[0x1e];
        unsigned short cost;
    } f;
} RecordDE990;
typedef struct StateDE990 {
    int f0[4];
    short f10;
    unsigned char f12;
    unsigned char f13;
    int f14;
    int f18, f1c;
    short f20, f22;
    int f24;
    char f28[0x12];
    unsigned char f3a, f3b;
    int f3c;
} StateDE990;
extern StateDE990 g_player_bolts MACRO_ADDR;
extern int g_equipment_bits MACRO_ADDR;
extern int D_001A7AF0_gp SDATA(D_001A7AF0);
extern unsigned char g_subtitle_history[];
extern unsigned char g_item_owned_flags[] MACRO_ADDR;
extern int D_00139868[];
extern RecordDE990 g_weapon_table[];
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];
extern unsigned char D_001A7A60[] MACRO_ADDR;
extern unsigned char D_001A7A40[] MACRO_ADDR;
extern unsigned char D_001A7A80[] MACRO_ADDR;
extern unsigned char D_001A7AB8[] MACRO_ADDR;
extern unsigned char D_0019B278[];
extern unsigned char D_001395B8[];
extern int g_weapon_menu_slots[] MACRO_ADDR;
extern unsigned char D_001A7B94[] MACRO_ADDR;
extern unsigned char D_001A7B08 MACRO_ADDR;
extern unsigned char g_hero_state[];
extern unsigned char g_memcard_state[];
extern char D_001F2A40[];
extern void mem_copy_aligned(void *, void *, int);
extern void mem_clear(void *, int, int);
extern void save_load_game_data_reset_menu(void);
extern int menu_seek_chain_entry(int, int);
extern int help_copy_record_at_depth(RecordDE990 *, int, int);
extern void save_build_packet(char *);

void func_PAL_002DF760(int selected)
{
    struct {
        int flags[56];
        int words[56];
        int slots[56];
        RecordDE990 records[56];
    } saved;
    int saved32[32];
    unsigned char saved56[56];
    int saved12[12];
    StateDE990 savedState;
    unsigned char savedBlock[112];
    RecordDE990 first, second;
    int resident, hadCard, i, j, k;
    unsigned char control;
    StateDE990 *gameState;
    unsigned char *card, *block, *slots;
    int *words;
    unsigned char *state, *hud;
    card = g_subtitle_history;
    g_player_bolts.f12++;
    g_player_bolts.f3a = 1;
    g_player_bolts.f3b = 0;
    resident = g_equipment_bits;
    hadCard = *(unsigned short *)(card + 0x84);
    gameState = &g_player_bolts;
    savedState = *gameState;
    for (j = 0; j < 56; j++) {
        saved.flags[j] = g_item_owned_flags[j];
        saved.words[j] = D_00139868[j];
        *(saved.records + j) = g_weapon_table[j];
        saved.slots[j] = g_item_slot_to_record[j];
    }
    for (i = 0; i < 32; i++) saved32[i] = D_001A7A60[i];
    for (i = 0; i < 12; i++) saved12[i] = D_001A7A40[i];
    saved.flags[51] = 0;
    saved.flags[36] = 0;
    saved.flags[20] = 0;
    saved.flags[13] = 0;
    saved.flags[38] = 0;
    saved.flags[39] = 0;
    saved.flags[46] = 0;
    saved.flags[48] = 0;
    saved.flags[55] = 0;
    saved.flags[21] = 0;
    saved.flags[2] = 0;
    saved.flags[3] = 0;
    saved.flags[4] = 0;
    saved.flags[19] = 0;
    saved.flags[8] = 0;
    mem_copy_aligned(savedBlock, D_0019B278, 112);
    block = D_001395B8;
    control = block[0x90];
    for (i = 0; i < 56; i++) saved56[i] = D_001A7A80[i];
    save_load_game_data_reset_menu();
    mem_copy_aligned(D_0019B278, savedBlock, 112);
    block = D_001395B8;
    block[0x90] = control;
    mem_clear(D_001A7AB8, 0, 56);
    for (i = 0; i < 56; i++) D_001A7A80[i] = saved56[i];
    { int m; for (m = 7; m >= 0; m--) g_weapon_menu_slots[m] = 0; }
    g_player_bolts = savedState;
    g_weapon_menu_slots[0] = 30;
    g_weapon_menu_slots[1] = 42;
    g_player_bolts.f22 = 0;
    g_player_bolts.f24 = 0;
    g_player_bolts.f18 = 0;
    g_player_bolts.f1c = 0;
    D_001A7B94[0] = 0;
    D_001A7B94[1] = 0;
    if (hadCard) {
        card = g_subtitle_history;
        if (*(unsigned short *)(card + 0x84) == 0)
            *(unsigned short *)(card + 0x84) = 1;
    }
    for (k = 0; k < 56; k++) {
        g_item_owned_flags[k] = saved.flags[k];
        D_00139868[k] = saved.words[k];
        g_weapon_table[k] = *(saved.records + k);
        g_item_slot_to_record[k] = saved.slots[k];
        g_item_ammo_counts[k] = g_weapon_table[g_item_slot_to_record[k]].f.cost;
    }
    for (i = 0; i < 32; i++) D_001A7A60[i] = saved32[i];
    for (i = 0; i < 12; i++) D_001A7A40[i] = saved12[i];
    D_001A7B94[1] = 0;
    D_001A7B94[0] = 0;
    menu_seek_chain_entry(10, 3);
    if (D_001A7B08) {
        if (g_weapon_table[g_item_slot_to_record[0x10]].f.kind == 0)
            menu_seek_chain_entry(16, 2);
        else
            menu_seek_chain_entry(16, 3);
        if (g_weapon_table[g_item_slot_to_record[0x10]].f.kind == 0) {
            help_copy_record_at_depth(&first, 16, 2);
            help_copy_record_at_depth(&second, 16, 0);
            words = D_00139868;
            words[16] = (float)first.f.value * (float)words[16] / (float)second.f.value;
        }
    }
    hud = g_hero_state;
    *(short *)(hud + 0x24fc) = 1;
    D_001A7AF0_gp = resident;
    if (selected >= 0) {
        state = g_memcard_state;
        *(short *)(state + 0x18) = selected;
        *(int *)(state + selected * 28 + 0x30) = 0;
        save_build_packet(D_001F2A40);
        *(char **)(state + 0x174) = D_001F2A40;
        *(int *)(state + 0x148) = 0;
        if (*(int *)(state + 0x164) < 0) {
            *(int *)(state + 0x168) = 0;
            *(int *)(state + 0x164) = 19;
        }
    }
}
