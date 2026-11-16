#include "include_asm.h"
#include "names.h"

typedef struct { int items[21]; } Table_002AF0A8;
extern const Table_002AF0A8 g_snd_indexed_table;
extern void value_set_entry_by_index_pal(int, int);
extern int ForceClaimNotice(int, int, int);

/* Plays the entry of the 21-entry table the clamped index picks; entry 3 goes through the
   other player. */
void snd_play_indexed_pal(int index)
{
    Table_002AF0A8 table = g_snd_indexed_table;

    if (index < 0)
        index = 0;
    if (index > 20)
        index = 20;
    if (index == 3)
        value_set_entry_by_index_pal(table.items[3], 0xC8);
    else
        ForceClaimNotice(8, table.items[index], 0x96);
}
