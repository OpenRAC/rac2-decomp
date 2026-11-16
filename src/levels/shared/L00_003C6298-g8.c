#include "include_asm.h"
#include "names.h"

/* Measured partial layouts; original type and game roles are unknown. */

typedef struct Rac2Native_9cdc323a4d0c2fbd_Vector16 {
    unsigned int word_00;
    unsigned int word_04;
    unsigned int word_08;
    unsigned int word_0C;
} Rac2Native_9cdc323a4d0c2fbd_Vector16;

extern Rac2Native_9cdc323a4d0c2fbd_Vector16 g_sheepinator_slot_table[];

extern unsigned int g_sheepinator_record_count __attribute__((sda));

/* True when the shared mode word equals four. */
int sheepinator_is_mode_four(void)
{
    return (g_sheepinator_record_count ^ 4) == 0;
}

/* Clears the first word of five consecutive 16-byte records, from the last one down, then the mode word. */
void sheepinator_clear_records(void)
{
    int i;

    for (i = 4; i >= 0; i--)
        g_sheepinator_slot_table[i].word_00 = 0;

    g_sheepinator_record_count = 0;
}
