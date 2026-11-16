#include "include_asm.h"
#include "names.h"

typedef struct {
    unsigned int marker;
    unsigned char reserved04[0x38];
    unsigned short class_code;
    unsigned char reserved3E[0xa2];
} MappedClassEntry;
typedef unsigned char u8;
extern unsigned char g_item_slot_to_record[];
extern MappedClassEntry g_weapon_l00_table[];
typedef struct {
    void *slot[6];
    int flag;
} SlotTable;
extern SlotTable ref_L00_00288508_00;
extern unsigned short g_help_message_flag;
extern int subtitle_request_voice_line(int, int);
extern void value_set_entry_by_index(int, int);

/* Pick the action of the mapped class of PARAM, then hand it to the game. */
void help_show_message_for_id_pal(int param)
{
    SlotTable table;
    int code;
    int i;

    if (param == 10) {
        subtitle_request_voice_line(0x9F8, 0x4F);
    } else if (param == 27) {
        subtitle_request_voice_line(0x9F7, 0x4E);
    } else if (g_help_message_flag == 0) {
        subtitle_request_voice_line(0x9AA, 1);
    }

    code = -1;
    table = ref_L00_00288508_00;
    {
        MappedClassEntry *entry = &g_weapon_l00_table[g_item_slot_to_record[param]];
        int *p = 0;
        if (entry->reserved04[0] < 6) {
            p = (int *)table.slot[((u8 *)entry)[4]];
        }
        if (p) {
            for (i = 0; p[i] != -1; i += 2) {
                if (p[i] == param) { code = p[i + 1]; break; }
            }
        }
    }
    if (param == 10) {
        u8 *entry2 = (u8 *)&g_weapon_l00_table[g_item_slot_to_record[10]];
        int kind2 = entry2[4];
        if (kind2 >= 2) code = 0x1296;
        if (kind2 >= 3) code = 0x1297;
        if (kind2 >= 4) code = 0x1296;
        if (kind2 >= 5) code = 0x1297;
    }
    if (code >= 0)
        value_set_entry_by_index(code, -1);
    else
        value_set_entry_by_index(0, -1);
}

