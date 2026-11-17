#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {
    u8 pad00[8];
    u8 f08;
    u8 pad09[0x3f];
    u32 *f48[8];
} EntryTable;
typedef struct {
    u8 pad00[0x10];
    u8 f10;
    u8 pad11[2];
    u8 f13;
    u8 pad14[8];
    u32 f1c[8];
} Entry;
typedef struct {
    u8 pad00[0x24];
    EntryTable *f24;
    u8 pad28[0x18];
    u8 f40;
    u8 f41;
    u8 f42;
    u8 f43;
    u8 pad44[0x14];
    char *f58;
    char *f5c;
} SlotObject;
extern void stub_empty_16(char *, long long);
extern void func_PAL_002A0F68(char *);
extern void func_002A1130(u32 *, u32, long long, u32);
extern void func_002A0F48(char *);

/* Links two menu slots to their picture data so they can be drawn (PAL). */
void menu_attach_slot_packets_pal(char *menu)
{
    char *slot_base = menu + 0xC00;
    SlotObject *slot = (SlotObject *)slot_base;

    stub_empty_16(slot_base, 0);
    func_PAL_002A0F68(slot_base);
    if (slot->f42 != 0xFF) {
        EntryTable *entry_table = slot->f24;
        Entry *slot_entry = entry_table->f48[slot->f42];
        u32 *packet_dest = (u32 *)((char *)&slot_entry->f1c[slot_entry->f10] + slot_entry->f13 * 4);
        func_002A1130(packet_dest, slot_entry->f1c[slot->f40], (long long)menu, entry_table->f08);
        slot->f58 = menu;
    }
    if (slot->f43 != 0xFF) {
        EntryTable *entry_table = slot->f24;
        Entry *slot_entry = entry_table->f48[slot->f43];
        u32 *packet_dest = (u32 *)((char *)&slot_entry->f1c[slot_entry->f10] + slot_entry->f13 * 4);
        func_002A1130(packet_dest, slot_entry->f1c[slot->f41], (long long)(menu + 0x600), entry_table->f08);
        slot->f5c = menu + 0x600;
    }
    func_002A0F48(slot_base);
}

